/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "VoiceChatMgr.h"
#include "VoiceChatChannel.h"
#include "Chat/ChannelMgr.h"
#include "BattleGround/BattleGroundMgr.h"
#include "World/World.h"
#include "Config/Config.h"

#include "Network/AsyncConnector.hpp"
#include <boost/thread/thread.hpp>
#include <memory>

void VoiceSocketThread()
{
    sVoiceChatMgr.VoiceSocketThread();
}

void ActivateVoiceSocketThread()
{
    boost::thread t(VoiceSocketThread);
    t.detach();
}

INSTANTIATE_SINGLETON_1(VoiceChatMgr);

VoiceChatMgr::VoiceChatMgr()
{
    enabled = false;
    server_address = 0;
    server_port = 0;
    voice_port = 0;
    maxConnectAttempts = 0;
    new_request_id = 1;
    new_session_id = time(nullptr);// 1;
    curReconnectAttempts = 0;
    m_socket = nullptr;
    m_requestSocket = nullptr;
    next_connect = time(nullptr);
    next_ping = time(nullptr) + 5;
    last_pong = time(nullptr);
    lastUpdate = time(nullptr);
    state = VOICECHAT_DISCONNECTED;
}

void VoiceChatMgr::LoadConfigs()
{
    enabled = sConfig.GetBoolDefault("VoiceChat.Enabled", false);

    server_address_string = sConfig.GetStringDefault("VoiceChat.ServerAddress", "127.0.0.1");
    server_address = inet_addr(server_address_string.c_str());
    server_port = sConfig.GetIntDefault("VoiceChat.ServerPort", 3725);

    std::string voice_address_string = sConfig.GetStringDefault("VoiceChat.VoiceAddress", "127.0.0.1");
    voice_address = inet_addr(voice_address_string.c_str());
    voice_port = sConfig.GetIntDefault("VoiceChat.VoicePort", 3724);

    maxConnectAttempts = sConfig.GetIntDefault("VoiceChat.MaxConnectAttempts", -1);
}

void VoiceChatMgr::Init()
{
    LoadConfigs();

    next_ping = time(nullptr) + 5;
    last_pong = time(nullptr);
    lastUpdate = time(nullptr);
    curReconnectAttempts = 0;

    state = enabled ? VOICECHAT_NOT_CONNECTED : VOICECHAT_DISCONNECTED;
}

void VoiceChatMgr::Update()
{
    if (!enabled)
        return;

    GetMessager().Execute(this);

    std::deque<std::unique_ptr<VoiceChatServerPacket>> recvQueueCopy;
    {
        std::lock_guard<std::mutex> guard(m_recvQueueLock);
        std::swap(recvQueueCopy, m_recvQueue);
    }

    while (m_socket && !m_socket->IsClosed() && !recvQueueCopy.empty())
    {
        auto const packet = std::move(recvQueueCopy.front());
        recvQueueCopy.pop_front();

        try
        {
            HandleVoiceChatServerPacket(*packet);
        }
        catch (const ByteBufferException&)
        {
            ProcessByteBufferException(*packet);
        }
    }

    if (state == VOICECHAT_DISCONNECTED)
        return;

    if (time(nullptr) - lastUpdate < 1)
        return;

    lastUpdate = time(nullptr);

    if (m_requestSocket)
    {
        m_socket = m_requestSocket;
        m_requestSocket = nullptr;
        return;
    }

    // connecting / reconnecting
    if (!m_socket)
    {
        // lost connection
        if (state == VOICECHAT_CONNECTED)
        {
            sLog.outError("VoiceChatMgr: Socket disconnected");
            SocketDisconnected();
            SendVoiceChatServiceDisconnect();
            state = VOICECHAT_RECONNECTING;
            next_connect = time(nullptr) + 10;
            return;
        }

        // reconnecting
        if (state == VOICECHAT_RECONNECTING)
        {
            // max attempts reached or disabled
            if (maxConnectAttempts >= 0 && curReconnectAttempts >= maxConnectAttempts)
            {
                if (maxConnectAttempts > 0)
                    sLog.outError("VoiceChatMgr: Disconnected! Max reconnect attempts reached");
                else
                    sLog.outError("VoiceChatMgr: Disconnected! Reconnecting disabled");

                DeleteAllChannels();
                SendVoiceChatStatus(false);
                SendVoiceChatServiceConnectFail();
                curReconnectAttempts = 0;
                state = VOICECHAT_DISCONNECTED;
                return;
            }
        }

        // try to connect
        if (time(nullptr) > next_connect)
        {
            if (NeedConnect() || NeedReconnect())
            {
                ActivateVoiceSocketThread();
            }

            if (curReconnectAttempts > 0)
            {
                if (state == VOICECHAT_NOT_CONNECTED)
                    sLog.outError("VoiceChatMgr: Connect failed, will try again later");
                if (state == VOICECHAT_RECONNECTING)
                    sLog.outError("VoiceChatMgr: Reconnect failed, will try again later");
            }

            // count attempts
            if (state == VOICECHAT_NOT_CONNECTED || state == VOICECHAT_RECONNECTING)
                curReconnectAttempts++;

            // wait for socket to open
            next_connect = time(nullptr) + 10;
            return;
        }
    }
    else
    {
        if (m_socket->IsClosed()) // lost connection
        {
            if (state == VOICECHAT_CONNECTED)
            {
                SocketDisconnected();
                SendVoiceChatServiceDisconnect();
                state = VOICECHAT_RECONNECTING;
                return;
            }

            // try to connect
            if (time(nullptr) > next_connect)
            {
                if (!m_requestSocket && (state == VOICECHAT_NOT_CONNECTED || state == VOICECHAT_RECONNECTING))
                {
                    ActivateVoiceSocketThread();
                    next_connect = time(nullptr) + 5;
                }
            }
            return;
        }

        // connecting / reconnecting
        if (state == VOICECHAT_NOT_CONNECTED || state == VOICECHAT_RECONNECTING)
        {
            if (state == VOICECHAT_NOT_CONNECTED)
                sLog.outBasic("VoiceChatMgr: Connected to %s:%u.", m_socket->GetRemoteAddress().c_str(), m_socket->GetRemotePort());
            if (state == VOICECHAT_RECONNECTING)
                sLog.outBasic("VoiceChatMgr: Reconnected to %s:%u", m_socket->GetRemoteAddress().c_str(), m_socket->GetRemotePort());

            SendVoiceChatStatus(true);
            RestoreVoiceChatChannels();
            if (state == VOICECHAT_RECONNECTING)
            {
                SendVoiceChatServiceReconnected();
            }

            state = VOICECHAT_CONNECTED;
            curReconnectAttempts = 0;
            last_pong = time(nullptr);
        }
        else // connected
        {
            if (time(nullptr) >= next_ping)
            {
                next_ping = time(nullptr) + 5;
                VoiceChatServerPacket data(VOICECHAT_CMSG_PING, 4);
                data << uint32(0);
                m_socket->SendPacket(data);
            }
            // because the above might kill m_socket
            if (m_socket && (time(nullptr) - last_pong) > 10)
            {
                // ping timeout
                sLog.outError("VoiceChatMgr: Ping timeout!");
                SocketDisconnected();
                SendVoiceChatServiceDisconnect();
                state = VOICECHAT_RECONNECTING;
                next_connect = time(nullptr) + 10;
            }
        }
    }
}

void VoiceChatMgr::HandleVoiceChatServerPacket(VoiceChatServerPacket& pck)
{
    uint32 request_id;
    uint8 error;
    uint16 channel_id;

    switch(pck.GetOpcode())
    {
        case VOICECHAT_SMSG_PONG:
        {
            last_pong = time(nullptr);
            break;
        }
        case VOICECHAT_SMSG_CHANNEL_CREATED:
        {
            pck >> request_id;
            pck >> error;

            for(auto request = m_requests.begin(); request != m_requests.end();)
            {
                if (request->id == request_id)
                {
                    if (error == 0)
                    {
                        pck >> channel_id;
                    }
                    else
                    {
                        sLog.outError("VoiceChatMgr: Error creating voice channel");
                        request = m_requests.erase(request);
                        return;
                    }

                    if (request->groupid)
                    {
                        if (request->type == VOICECHAT_CHANNEL_GROUP || request->type == VOICECHAT_CHANNEL_RAID)
                        {
                            Group* grp = sObjectMgr.GetGroupById(request->groupid);
                            if (grp)
                            {
                                auto* v_channel = new VoiceChatChannel(VoiceChatChannelTypes(request->type), channel_id, grp->GetId());
                                m_VoiceChatChannels.insert(std::make_pair((uint32)channel_id, v_channel));
                                v_channel->AddMembersAfterCreate();
                            }
                        }
                        else if (request->type == VOICECHAT_CHANNEL_BG)
                        {
                            BattleGround* bg = sBattleGroundMgr.GetBattleGround(request->groupid, BATTLEGROUND_TYPE_NONE);
                            if (bg)
                            {
                                // for BG use bg's instanceID as groupID
                                auto* v_channel = new VoiceChatChannel(VoiceChatChannelTypes(request->type), channel_id, request->groupid, "", request->team);
                                m_VoiceChatChannels.insert(std::make_pair((uint32)channel_id, v_channel));
                                v_channel->AddMembersAfterCreate();
                            }
                        }
                    }
                    else if (request->type == VOICECHAT_CHANNEL_CUSTOM)
                    {
                        if (ChannelMgr* cMgr = channelMgr(request->team))
                        {
                            Channel* chan = cMgr->GetChannel(request->channel_name, nullptr, false);
                            if (chan)
                            {
                                auto* v_channel = new VoiceChatChannel(VoiceChatChannelTypes(request->type), channel_id, 0, request->channel_name, request->team);
                                m_VoiceChatChannels.insert(std::make_pair((uint32)channel_id, v_channel));
                                v_channel->AddMembersAfterCreate();
                            }
                        }
                    }

                    request = m_requests.erase(request);
                }
                else
                    request++;
            }
            break;
        }
        default:
        {
            sLog.outError("VoiceChatMgr: received unknown opcode %u!\n", pck.GetOpcode());
            break;
        }
    }
}

void VoiceChatMgr::SocketDisconnected()
{
    sLog.outBasic("VoiceChatMgr: VoiceChatServerSocket disconnected");

    if (m_socket)
    {
        if (!m_socket->IsClosed())
            m_socket->Close();
    }
    m_voiceService.stop();
    m_socket = nullptr;
    m_requests.clear();

    DeleteAllChannels();

    curReconnectAttempts = 0;
}

bool VoiceChatMgr::NeedConnect()
{
    return enabled && !m_socket && !m_requestSocket && state == VOICECHAT_NOT_CONNECTED && time(nullptr) > next_connect;
}

bool VoiceChatMgr::NeedReconnect()
{
    return enabled && !m_socket && !m_requestSocket && state == VOICECHAT_RECONNECTING && time(nullptr) > next_connect;
}

int32 VoiceChatMgr::GetReconnectAttempts() const
{
    if (maxConnectAttempts < 0 || (maxConnectAttempts > 0 && curReconnectAttempts < maxConnectAttempts))
    {
        return maxConnectAttempts;
    }

    return 0;
}

bool VoiceChatMgr::RequestNewSocket(VoiceChatServerSocket* socket)
{
    if (m_requestSocket)
        return false;

    m_requestSocket = socket->shared_from_this();
    return true;
}

// Add an incoming packet to the queue
void VoiceChatMgr::QueuePacket(std::unique_ptr<VoiceChatServerPacket> new_packet)
{
    std::lock_guard<std::mutex> guard(m_recvQueueLock);
    m_recvQueue.push_back(std::move(new_packet));
}

void VoiceChatMgr::ProcessByteBufferException(VoiceChatServerPacket const& packet)
{
    sLog.outError("VoiceChatMgr::Update ByteBufferException occured while parsing a packet (opcode: %u).",
                  packet.GetOpcode());

    if (sLog.HasLogLevelOrHigher(LOG_LVL_DEBUG))
    {
        DEBUG_LOG("Dumping error-causing voice server packet:");
        packet.hexlike();
    }

    DETAIL_LOG("Disconnecting voice server [address %s] for badly formatted packet.",
               GetVoiceServerConnectAddressString().c_str());

    GetMessager().AddMessage([](VoiceChatMgr* mgr)
                             {
                                 mgr->SocketDisconnected();
                             });
}

void VoiceChatMgr::VoiceSocketThread()
{
    m_voiceService.stop();
    m_voiceService.restart();
    std::unique_ptr<MaNGOS::AsyncConnector<VoiceChatServerSocket>> voiceSocket;
    voiceSocket = std::make_unique<MaNGOS::AsyncConnector<VoiceChatServerSocket>>(m_voiceService, sVoiceChatMgr.GetVoiceServerConnectAddressString(), int32(sVoiceChatMgr.GetVoiceServerConnectPort()), false);
    m_voiceService.run();
}

// enabled and connected to voice server
bool VoiceChatMgr::CanUseVoiceChat()
{
    return (enabled && m_socket);
}

// enabled and is connected or trying to connect to voice server
bool VoiceChatMgr::CanSeeVoiceChat()
{
    return (enabled && state != VOICECHAT_DISCONNECTED);
}

void VoiceChatMgr::CreateVoiceChatChannel(VoiceChatChannelTypes type, uint32 groupId, const std::string& name, Team team)
{
    if (!m_socket)
        return;

    if (type == VOICECHAT_CHANNEL_NONE)
        return;

    if (!groupId && name.empty())
        return;

    Team newTeam = GetCustomChannelTeam(team);

    if (IsVoiceChatChannelBeingCreated(type, groupId, name, newTeam))
        return;

    sLog.outDebug("VoiceChatMgr: CreateVoiceChannel type: %u, name: %s, team: %u, group: %u", type, name.c_str(), newTeam, groupId);
    VoiceChatChannelRequest req;
    req.id = new_request_id++;
    req.type = type;
    req.channel_name = name;
    req.team = newTeam;
    req.groupid = groupId;
    m_requests.push_back(req);

    VoiceChatServerPacket data(VOICECHAT_CMSG_CREATE_CHANNEL, 5);
    data << req.type;
    data << req.id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::DeleteVoiceChatChannel(VoiceChatChannel* channel)
{
    if (!channel)
        return;

    sLog.outDebug("VoiceChatMgr: DeleteVoiceChannel id: %u type: %u", channel->GetChannelId(), channel->GetType());

    uint8 type = channel->GetType();
    uint16 id = channel->GetChannelId();

    // disable voice in custom channel
    if (type == VOICECHAT_CHANNEL_CUSTOM)
    {
        if (ChannelMgr* cMgr = channelMgr(channel->GetTeam()))
        {
            if (Channel* chn = cMgr->GetChannel(channel->GetChannelName(), nullptr, false))
            {
                if (chn->IsVoiceEnabled())
                    chn->ToggleVoice();
            }
        }
    }

    m_VoiceChatChannels.erase(channel->GetChannelId());
    delete channel;

    if (m_socket)
    {
        VoiceChatServerPacket data(VOICECHAT_CMSG_DELETE_CHANNEL, 5);
        data << type;
        data << id;
        m_socket->SendPacket(data);
    }
}

// check if channel request has already been created
bool VoiceChatMgr::IsVoiceChatChannelBeingCreated(VoiceChatChannelTypes type, uint32 groupId, const std::string& name, Team team)
{
    for (const auto& req : m_requests)
    {
        if (req.type != type)
            continue;
        if (groupId && req.groupid != groupId)
            continue;
        if (!name.empty() && req.channel_name != name)
            continue;
        if (req.team != team)
            continue;

        return true;
    }
    return false;
}

void VoiceChatMgr::CreateGroupVoiceChatChannel(uint32 groupId)
{
    if (GetGroupVoiceChatChannel(groupId))
        return;

    CreateVoiceChatChannel(VOICECHAT_CHANNEL_GROUP, groupId);
}

void VoiceChatMgr::CreateRaidVoiceChatChannel(uint32 groupId)
{
    if (GetRaidVoiceChatChannel(groupId))
        return;

    CreateVoiceChatChannel(VOICECHAT_CHANNEL_RAID, groupId);
}

void VoiceChatMgr::CreateBattlegroundVoiceChatChannel(uint32 instanceId, Team team)
{
    if (GetBattlegroundVoiceChatChannel(instanceId, team))
        return;

    CreateVoiceChatChannel(VOICECHAT_CHANNEL_BG, instanceId, "", team);
}

void VoiceChatMgr::CreateCustomVoiceChatChannel(const std::string& name, Team team)
{
    if (GetCustomVoiceChatChannel(name, team))
        return;

    CreateVoiceChatChannel(VOICECHAT_CHANNEL_CUSTOM, 0, name, team);
}

void VoiceChatMgr::DeleteGroupVoiceChatChannel(uint32 groupId)
{
    if (!groupId)
        return;

    if (VoiceChatChannel* channel = GetGroupVoiceChatChannel(groupId))
    {
        DeleteVoiceChatChannel(channel);
    }
}

void VoiceChatMgr::DeleteRaidVoiceChatChannel(uint32 groupId)
{
    if (!groupId)
        return;

    if (VoiceChatChannel* channel = GetRaidVoiceChatChannel(groupId))
    {
        DeleteVoiceChatChannel(channel);
    }
}

void VoiceChatMgr::DeleteBattlegroundVoiceChatChannel(uint32 instanceId, Team team)
{
    if (!instanceId)
        return;

    if (VoiceChatChannel* channel = GetBattlegroundVoiceChatChannel(instanceId, team))
    {
        DeleteVoiceChatChannel(channel);
    }
}

void VoiceChatMgr::DeleteCustomVoiceChatChannel(const std::string& name, Team team)
{
    if (name.empty())
        return;

    if (VoiceChatChannel* v_channel = GetCustomVoiceChatChannel(name, team))
    {
        DeleteVoiceChatChannel(v_channel);
    }
}

void VoiceChatMgr::ConvertToRaidChannel(uint32 groupId)
{
    if (VoiceChatChannel* chn = GetGroupVoiceChatChannel(groupId))
    {
        chn->ConvertToRaid();
    }
}

VoiceChatChannel* VoiceChatMgr::GetVoiceChatChannel(uint16 channel_id)
{
    auto itr = m_VoiceChatChannels.find(channel_id);
    if (itr == m_VoiceChatChannels.end())
        return nullptr;

    return itr->second;
}

VoiceChatChannel* VoiceChatMgr::GetGroupVoiceChatChannel(uint32 group_id)
{
    for (auto& channel : m_VoiceChatChannels)
    {
        VoiceChatChannel* chn = channel.second;
        if (chn->GetType() == VOICECHAT_CHANNEL_GROUP && chn->GetGroupId() == group_id)
            return chn;
    }

    return nullptr;
}

VoiceChatChannel* VoiceChatMgr::GetRaidVoiceChatChannel(uint32 group_id)
{
    for (auto& channel : m_VoiceChatChannels)
    {
        VoiceChatChannel* chn = channel.second;
        if (chn->GetType() == VOICECHAT_CHANNEL_RAID && chn->GetGroupId() == group_id)
            return chn;
    }

    return nullptr;
}

VoiceChatChannel* VoiceChatMgr::GetBattlegroundVoiceChatChannel(uint32 instanceId, Team team)
{
    for (auto& channel : m_VoiceChatChannels)
    {
        // for BG use bg's instanceID as groupID
        VoiceChatChannel* chn = channel.second;
        if (chn->GetType() == VOICECHAT_CHANNEL_BG && chn->GetGroupId() == instanceId && chn->GetTeam() == team)
            return chn;
    }

    return nullptr;
}

VoiceChatChannel* VoiceChatMgr::GetCustomVoiceChatChannel(const std::string& name, Team team)
{
    for (auto& channels : m_VoiceChatChannels)
    {
        VoiceChatChannel* v_chan = channels.second;
        if (v_chan->GetType() == VOICECHAT_CHANNEL_CUSTOM && v_chan->GetChannelName() == name && v_chan->GetTeam() == GetCustomChannelTeam(team))
            return v_chan;
    }

    return nullptr;
}

// get possible voice channels after login or voice chat enable
std::vector<VoiceChatChannel*> VoiceChatMgr::GetPossibleVoiceChatChannels(ObjectGuid guid)
{
    std::vector<VoiceChatChannel*> channel_list;
    Player* plr = sObjectMgr.GetPlayer(guid, false);
    if (!plr)
        return channel_list;

    for (auto& channel : m_VoiceChatChannels)
    {
        VoiceChatChannel* chn = channel.second;
        if (chn->GetType() != VOICECHAT_CHANNEL_CUSTOM)
            continue;

        if (chn->GetTeam() != GetCustomChannelTeam(plr->GetTeam()))
            continue;

        if (ChannelMgr* cMgr = channelMgr(plr->GetTeam()))
        {
            Channel* chan = cMgr->GetChannel(chn->GetChannelName(), nullptr, false);
            if (chan && chan->IsOn(guid) && !chan->IsBanned(guid) && chan->IsVoiceEnabled())
            {
                channel_list.push_back(chn);
            }
        }
    }

    return channel_list;
}

// create group/raid/bg channels after (re)connect to voice server
void VoiceChatMgr::RestoreVoiceChatChannels()
{
    sWorld.GetMessager().AddMessage([](World* world)
    {
        world->ExecuteForAllSessions([](auto& data)
        {
            const WorldSession& sess = data;
            if (sess.IsVoiceChatEnabled())
            {
                if (Player* plr = sess.GetPlayer())
                {
                    if (Group* grp = plr->GetGroup())
                    {
                        if (!grp->IsBattleGroup())
                        {
                            if (grp->IsRaidGroup())
                                sVoiceChatMgr.AddToRaidVoiceChatChannel(plr->GetObjectGuid(), grp->GetId());
                            else
                                sVoiceChatMgr.AddToGroupVoiceChatChannel(plr->GetObjectGuid(), grp->GetId());
                        }
                        else
                        {
                            sVoiceChatMgr.AddToBattlegroundVoiceChatChannel(plr->GetObjectGuid());
                        }
                    }
                    if (Group* grp = plr->GetOriginalGroup())
                    {
                        if (!grp->IsBattleGroup())
                        {
                            if (grp->IsRaidGroup())
                                sVoiceChatMgr.AddToRaidVoiceChatChannel(plr->GetObjectGuid(), grp->GetId());
                            else
                                sVoiceChatMgr.AddToGroupVoiceChatChannel(plr->GetObjectGuid(), grp->GetId());
                        }
                        else
                        {
                            sVoiceChatMgr.AddToBattlegroundVoiceChatChannel(plr->GetObjectGuid());
                        }
                    }
                }
            }
        });
    });
}

void VoiceChatMgr::DeleteAllChannels()
{
    for (auto& channel : m_VoiceChatChannels)
    {
        DeleteVoiceChatChannel(channel.second);
    }
    m_VoiceChatChannels.clear();
}

// if cross faction channels are enabled, team is always ALLIANCE
Team VoiceChatMgr::GetCustomChannelTeam(Team team)
{
    if (sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_CHANNEL))
        return ALLIANCE;
    else
        return team;
}

void VoiceChatMgr::AddToGroupVoiceChatChannel(ObjectGuid guid, uint32 groupId)
{
    if (!groupId)
        return;

    VoiceChatChannel* v_channel = GetGroupVoiceChatChannel(groupId);
    if (!v_channel)
    {
        CreateGroupVoiceChatChannel(groupId);
        return;
    }

    v_channel->AddVoiceChatMember(guid);
}

void VoiceChatMgr::AddToRaidVoiceChatChannel(ObjectGuid guid, uint32 groupId)
{
    if (!groupId)
        return;

    VoiceChatChannel* v_channel = GetRaidVoiceChatChannel(groupId);
    if (!v_channel)
    {
        CreateRaidVoiceChatChannel(groupId);
        return;
    }

    v_channel->AddVoiceChatMember(guid);
}

void VoiceChatMgr::AddToBattlegroundVoiceChatChannel(ObjectGuid guid)
{
    Player* plr = sObjectMgr.GetPlayer(guid);
    if (!plr)
        return;

    if (!plr->InBattleGround())
        return;

    // for BG use bg's instanceID as groupID
    VoiceChatChannel* v_channel = GetBattlegroundVoiceChatChannel(plr->GetBattleGroundId(), plr->GetBGTeam());
    if (!v_channel)
    {
        CreateBattlegroundVoiceChatChannel(plr->GetBattleGroundId(), plr->GetBGTeam());
        return;
    }

    v_channel->AddVoiceChatMember(guid);
}

void VoiceChatMgr::AddToCustomVoiceChatChannel(ObjectGuid guid, const std::string& name, Team team)
{
    if (name.empty())
        return;

    VoiceChatChannel* v_channel = GetCustomVoiceChatChannel(name, team);
    if (!v_channel)
    {
        CreateCustomVoiceChatChannel(name, team);
        return;
    }

    v_channel->AddVoiceChatMember(guid);
}

void VoiceChatMgr::RemoveFromGroupVoiceChatChannel(ObjectGuid guid, uint32 groupId)
{
    if (!groupId)
        return;

    if (VoiceChatChannel* v_channel = GetGroupVoiceChatChannel(groupId))
    {
        v_channel->RemoveVoiceChatMember(guid);
    }
}

void VoiceChatMgr::RemoveFromRaidVoiceChatChannel(ObjectGuid guid, uint32 groupId)
{
    if (!groupId)
        return;

    if (VoiceChatChannel* v_channel = GetRaidVoiceChatChannel(groupId))
    {
        v_channel->RemoveVoiceChatMember(guid);
    }
}

void VoiceChatMgr::RemoveFromBattlegroundVoiceChatChannel(ObjectGuid guid)
{
    Player* plr = sObjectMgr.GetPlayer(guid);
    if (!plr)
        return;

    if (!plr->InBattleGround())
        return;

    if (VoiceChatChannel* v_channel = GetBattlegroundVoiceChatChannel(plr->GetBattleGroundId(), plr->GetBGTeam()))
    {
        v_channel->RemoveVoiceChatMember(guid);
    }
}

void VoiceChatMgr::RemoveFromCustomVoiceChatChannel(ObjectGuid guid, const std::string& name, Team team)
{
    if (name.empty())
        return;

    if (VoiceChatChannel* v_channel = GetCustomVoiceChatChannel(name, team))
    {
        v_channel->RemoveVoiceChatMember(guid);
    }
}

void VoiceChatMgr::EnableChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if(!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u activate slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_ADD_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::DisableChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if(!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u deactivate slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_REMOVE_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::VoiceChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if (!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u voice slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_VOICE_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::DevoiceChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if (!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u devoice slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_DEVOICE_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::MuteChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if (!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u mute slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_MUTE_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::UnmuteChannelSlot(uint16 channel_id, uint8 slot_id)
{
    if (!m_socket)
        return;

    sLog.outDebug("VoiceChatMgr: Channel %u unmute slot %u", (int)channel_id, (int)slot_id);

    VoiceChatServerPacket data(VOICECHAT_CMSG_UNMUTE_MEMBER, 5);
    data << channel_id;
    data << slot_id;
    m_socket->SendPacket(data);
}

void VoiceChatMgr::JoinAvailableVoiceChatChannels(WorldSession* session)
{
    if (!CanUseVoiceChat())
        return;

    // send available voice channels
    if (Player* player = session->GetPlayer())
    {
        if (Group* grp = player->GetGroup())
        {
            if (!grp->IsBattleGroup())
            {
                if (grp->IsRaidGroup())
                    AddToRaidVoiceChatChannel(player->GetObjectGuid(), grp->GetId());
                else
                    AddToGroupVoiceChatChannel(player->GetObjectGuid(), grp->GetId());
            }
            else
            {
                AddToBattlegroundVoiceChatChannel(player->GetObjectGuid());
            }
        }
        if (Group* grp = player->GetOriginalGroup())
        {
            if (grp->IsRaidGroup())
                AddToRaidVoiceChatChannel(player->GetObjectGuid(), grp->GetId());
            else
                AddToGroupVoiceChatChannel(player->GetObjectGuid(), grp->GetId());
        }

        std::vector<VoiceChatChannel*> channel_list = GetPossibleVoiceChatChannels(player->GetObjectGuid());
        for (const auto& channel : channel_list)
        {
            channel->AddVoiceChatMember(player->GetObjectGuid());
        }
    }
}

// Not used currently
void VoiceChatMgr::SendAvailableVoiceChatChannels(WorldSession* session)
{
    if (!CanUseVoiceChat())
        return;

    // send available voice channels
    if (Player* player = session->GetPlayer())
    {
        if (Group* grp = player->GetGroup())
        {
            if (!grp->IsBattleGroup())
            {
                if (grp->IsRaidGroup())
                {
                    if (VoiceChatChannel* chn = GetRaidVoiceChatChannel(grp->GetId()))
                    {
                        chn->SendAvailableVoiceChatChannel(session);
                    }
                }
                else
                {
                    if (VoiceChatChannel* chn = GetGroupVoiceChatChannel(grp->GetId()))
                    {
                        chn->SendAvailableVoiceChatChannel(session);
                    }
                }
            }
            else
            {
                if (VoiceChatChannel* chn = GetBattlegroundVoiceChatChannel(player->GetBattleGroundId(), player->GetBGTeam()))
                {
                    chn->SendAvailableVoiceChatChannel(session);
                }
            }
        }
        if (Group* grp = player->GetOriginalGroup())
        {
            if (grp->IsRaidGroup())
            {
                if (VoiceChatChannel* chn = GetRaidVoiceChatChannel(grp->GetId()))
                {
                    chn->SendAvailableVoiceChatChannel(session);
                }
            }
            else
            {
                if (VoiceChatChannel* chn = GetGroupVoiceChatChannel(grp->GetId()))
                {
                    chn->SendAvailableVoiceChatChannel(session);
                }
            }
        }

        std::vector<VoiceChatChannel*> channel_list = GetPossibleVoiceChatChannels(player->GetObjectGuid());
        for (auto channel : channel_list)
        {
            channel->SendAvailableVoiceChatChannel(session);
        }
    }
}

void VoiceChatMgr::RemoveFromVoiceChatChannels(ObjectGuid guid)
{
    for (const auto& channel : m_VoiceChatChannels)
    {
        VoiceChatChannel* chn = channel.second;
        chn->RemoveVoiceChatMember(guid);
    }
}

void VoiceChatMgr::SendVoiceChatStatus(bool status)
{
    WorldPacket data(SMSG_VOICE_CHAT_STATUS, 1);
    data << uint8(status);
    sWorld.SendGlobalMessage(data);
}

void VoiceChatMgr::SendVoiceChatServiceMessage(Opcodes opcode)
{
    WorldPacket data(opcode);
    sWorld.ExecuteForAllSessions([data](WorldSession& worldSession)
    {
        if (worldSession.IsVoiceChatEnabled())
            worldSession.SendPacket(data);
    });
}

// command handlers

void VoiceChatMgr::DisableVoiceChat()
{
    if (!m_voiceService.stopped() || (m_socket && !m_socket->IsClosed()))
    {
        SocketDisconnected();
    }

    enabled = false;
    state = VOICECHAT_DISCONNECTED;
    SendVoiceChatStatus(false);
}

void VoiceChatMgr::EnableVoiceChat()
{
    if (enabled)
        return;

    enabled = true;
    Init();
    SendVoiceChatStatus(true);
}

VoiceChatStatistics VoiceChatMgr::GetStatistics()
{
    VoiceChatStatistics stats;

    // amount of channels
    stats.channels = 0;
    for (const auto& chn : m_VoiceChatChannels)
    {
        stats.channels++;
    }

    // amount of active users
    stats.active_users = 0;
    stats.totalVoiceChatEnabled = 0;
    stats.totalVoiceMicEnabled = 0;
    sWorld.ExecuteForAllSessions([&](WorldSession const& session)
    {
        if (session.IsVoiceChatEnabled())
            stats.totalVoiceChatEnabled++;
        if (session.IsMicEnabled())
            stats.totalVoiceMicEnabled++;
        if (session.GetCurrentVoiceChannelId())
            stats.active_users++;
    });

    return stats;
}

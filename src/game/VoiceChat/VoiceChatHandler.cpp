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

#include "Common.h"
#include "VoiceChatMgr.h"
#include "VoiceChatChannel.h"
#include "Chat/ChannelMgr.h"
#include "Social/SocialMgr.h"
#include "World/World.h"
#include "Server/WorldSession.h"
#include "Tools/Language.h"

void WorldSession::HandleVoiceSessionEnableOpcode(WorldPacket & recv_data)
{
    sLog.outDebug("WORLD: Received CMSG_VOICE_SESSION_ENABLE");

    if (!sVoiceChatMgr.CanSeeVoiceChat())
        return;

    // comes from in game voice chat settings
    // is sent during login or when changing settings
    uint8 voiceEnabled, micEnabled;
    recv_data >> voiceEnabled;
    recv_data >> micEnabled;

    if(!voiceEnabled)
    {
        if (_player)
        {
            sVoiceChatMgr.RemoveFromVoiceChatChannels(_player->GetObjectGuid());
            SetCurrentVoiceChannelId(0);
        }
    }
    else
    {
        // send available voice channels
        if (_player && _player->IsInWorld() && !m_voiceEnabled)
        {
            // enable it here to allow joining channels
            m_voiceEnabled = voiceEnabled;
            m_micEnabled = micEnabled;
            sVoiceChatMgr.JoinAvailableVoiceChatChannels(this);
        }
    }

    if (!micEnabled)
    {
        if (_player)
        {
            if (GetCurrentVoiceChannelId())
            {
                VoiceChatChannel* current_channel = sVoiceChatMgr.GetVoiceChatChannel(GetCurrentVoiceChannelId());
                if (current_channel)
                    current_channel->MuteMember(_player->GetObjectGuid());
            }
        }
    }
    else
    {
        if (_player)
        {
            if (GetCurrentVoiceChannelId())
            {
                VoiceChatChannel* current_channel = sVoiceChatMgr.GetVoiceChatChannel(GetCurrentVoiceChannelId());
                if (current_channel)
                    current_channel->UnmuteMember(_player->GetObjectGuid());
            }
        }
    }

    m_micEnabled = micEnabled;
    m_voiceEnabled = voiceEnabled;
}

void WorldSession::HandleSetActiveVoiceChannelOpcode(WorldPacket & recv_data)
{
    sLog.outDebug("WORLD: Received CMSG_SET_ACTIVE_VOICE_CHANNEL");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    if (!_player || !_player->IsInWorld())
        return;

    uint32 type;
    std::string name;
    recv_data >> type;

    // leave current voice channel if player selects different one
    VoiceChatChannel* current_channel = nullptr;
    if (GetCurrentVoiceChannelId())
        current_channel = sVoiceChatMgr.GetVoiceChatChannel(GetCurrentVoiceChannelId());

    switch (type)
    {
        case VOICECHAT_CHANNEL_CUSTOM:
        {
            recv_data >> name;
            // custom channel
            if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
            {
                Channel* chan = cMgr->GetChannel(name, nullptr, false);
                if (!chan || !chan->IsOn(_player->GetObjectGuid()) || chan->IsBanned(_player->GetObjectGuid()) || !chan->IsVoiceEnabled())
                    return;
            }
            else
                return;

            if (VoiceChatChannel* v_channel = sVoiceChatMgr.GetCustomVoiceChatChannel(name, _player->GetTeam()))
            {
                if (current_channel)
                {
                    // if same channel, just update roster
                    if (v_channel == current_channel)
                    {
                        v_channel->SendVoiceRosterUpdate();
                        return;
                    }
                    else
                        current_channel->DevoiceMember(_player->GetObjectGuid());
                }

                v_channel->AddVoiceChatMember(_player->GetObjectGuid());
                if (v_channel->IsOn(_player->GetObjectGuid()))
                {
                    // change speaker icon from grey to color
                    v_channel->VoiceMember(_player->GetObjectGuid());
                    // allow to speak depending on settings
                    if (IsMicEnabled())
                        v_channel->UnmuteMember(_player->GetObjectGuid());
                    else
                        v_channel->MuteMember(_player->GetObjectGuid());

                    SetCurrentVoiceChannelId(v_channel->GetChannelId());
                }
            }

            break;
        }
        case VOICECHAT_CHANNEL_GROUP:
        case VOICECHAT_CHANNEL_RAID:
        {
            // group
            Group* grp = _player->GetGroup();
            if (grp && grp->IsBattleGroup())
                grp = _player->GetOriginalGroup();

            if (grp)
            {
                VoiceChatChannel* v_channel = nullptr;
                if (grp->IsRaidGroup())
                    v_channel = sVoiceChatMgr.GetRaidVoiceChatChannel(grp->GetId());
                else
                    v_channel = sVoiceChatMgr.GetGroupVoiceChatChannel(grp->GetId());

                if (v_channel)
                {
                    if (current_channel)
                    {
                        // if same channel, just update roster
                        if (v_channel == current_channel)
                        {
                            v_channel->SendVoiceRosterUpdate();
                            return;
                        }
                        else
                            current_channel->DevoiceMember(_player->GetObjectGuid());
                    }

                    v_channel->AddVoiceChatMember(_player->GetObjectGuid());
                    if (v_channel->IsOn(_player->GetObjectGuid()))
                    {
                        // change speaker icon from grey to color
                        v_channel->VoiceMember(_player->GetObjectGuid());
                        // allow to speak depending on settings
                        if (IsMicEnabled())
                            v_channel->UnmuteMember(_player->GetObjectGuid());
                        else
                            v_channel->MuteMember(_player->GetObjectGuid());

                        SetCurrentVoiceChannelId(v_channel->GetChannelId());
                    }
                }
            }

            break;
        }
        case VOICECHAT_CHANNEL_BG:
        {
            // bg
            if (_player->InBattleGround())
            {
                VoiceChatChannel* v_channel = sVoiceChatMgr.GetBattlegroundVoiceChatChannel(_player->GetBattleGroundId(), _player->GetBGTeam());
                if (v_channel)
                {
                    if (current_channel)
                    {
                        // if same channel, just update roster
                        if (v_channel == current_channel)
                        {
                            v_channel->SendVoiceRosterUpdate();
                            return;
                        }
                        else
                            current_channel->DevoiceMember(_player->GetObjectGuid());
                    }

                    v_channel->AddVoiceChatMember(_player->GetObjectGuid());
                    if (v_channel->IsOn(_player->GetObjectGuid()))
                    {
                        // change speaker icon from grey to color
                        v_channel->VoiceMember(_player->GetObjectGuid());
                        // allow to speak depending on settings
                        if (IsMicEnabled())
                            v_channel->UnmuteMember(_player->GetObjectGuid());
                        else
                            v_channel->MuteMember(_player->GetObjectGuid());

                        SetCurrentVoiceChannelId(v_channel->GetChannelId());
                    }
                }
            }

            break;
        }
        case VOICECHAT_CHANNEL_NONE:
        {
            // leave current channel
            if (current_channel)
            {
                current_channel->DevoiceMember(_player->GetObjectGuid());
            }
            SetCurrentVoiceChannelId(0);

            break;
        }
        default:
            break;
    }
}

void WorldSession::HandleChannelVoiceOnOpcode(WorldPacket& recv_data)
{
    sLog.outDebug("WORLD: Received CMSG_CHANNEL_VOICE_ON");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    std::string name;
    recv_data >> name;

    if (!_player)
        return;

    // custom channel
    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        Channel* chn = cMgr->GetChannel(name, _player);
        if (!chn)
            return;

        if (chn->IsLFG() || chn->IsConstant())
        {
            sLog.outError("VoiceChat: Channel is LFG or constant, can't use voice!");
            return;
        }

        // already enabled
        if (chn->IsVoiceEnabled())
            return;

        chn->ToggleVoice(_player);

        sVoiceChatMgr.CreateCustomVoiceChatChannel(chn->GetName(), _player->GetTeam());
    }
}

void WorldSession::HandleChannelVoiceOffOpcode(WorldPacket& recv_data)
{
    sLog.outDebug("WORLD: Received CMSG_CHANNEL_VOICE_OFF");

    // todo check if possible to send with chat commands
}

void WorldSession::HandleAddVoiceIgnoreOpcode(WorldPacket& recvData)
{
    sLog.outDebug("WORLD: Received opcode CMSG_ADD_VOICE_IGNORE");

    std::string IgnoreName = GetMangosString(LANG_FRIEND_IGNORE_UNKNOWN);

    recvData >> IgnoreName;

    if (!normalizePlayerName(IgnoreName))
        return;

    CharacterDatabase.escape_string(IgnoreName);

    DEBUG_LOG("WORLD: %s asked to Ignore: '%s'",
        GetPlayer()->GetName(), IgnoreName.c_str());

    CharacterDatabase.AsyncPQuery(&WorldSession::HandleAddMutedOpcodeCallBack, GetAccountId(), "SELECT guid FROM characters WHERE name = '%s'", IgnoreName.c_str());
}

void WorldSession::HandleAddMutedOpcodeCallBack(QueryResult* result, uint32 accountId)
{
    if (!result)
        return;

    uint32 ignoreLowGuid = (*result)[0].GetUInt32();
    ObjectGuid ignoreGuid = ObjectGuid(HIGHGUID_PLAYER, ignoreLowGuid);

    delete result;

    WorldSession* session = sWorld.FindSession(accountId);
    if (!session)
        return;

    Player* player = session->GetPlayer();
    if (!player)
        return;

    FriendsResult ignoreResult = FRIEND_MUTE_NOT_FOUND;
    if (ignoreGuid)
    {
        if (ignoreGuid == player->GetObjectGuid())
            ignoreResult = FRIEND_MUTE_SELF;
        else if (player->GetSocial()->HasMute(ignoreGuid))
            ignoreResult = FRIEND_MUTE_ALREADY;
        else
        {
            ignoreResult = FRIEND_MUTE_ADDED;

            // mute list full
            if (!player->GetSocial()->AddToSocialList(ignoreGuid, false, true))
                ignoreResult = FRIEND_MUTE_FULL;
        }
    }

    sSocialMgr.SendFriendStatus(player, ignoreResult, ignoreGuid, false);

    sLog.outDebug("WORLD: Sent (SMSG_FRIEND_STATUS)");
}

void WorldSession::HandleDelVoiceIgnoreOpcode(WorldPacket& recvData)
{
    ObjectGuid ignoreGuid;

    sLog.outDebug("WORLD: Received opcode CMSG_DEL_VOICE_IGNORE");

    recvData >> ignoreGuid;

    _player->GetSocial()->RemoveFromSocialList(ignoreGuid, false, true);

    sSocialMgr.SendFriendStatus(GetPlayer(), FRIEND_MUTE_REMOVED, ignoreGuid, false);

    sLog.outDebug("WORLD: Sent motd (SMSG_FRIEND_STATUS)");
}

void WorldSession::HandlePartySilenceOpcode(WorldPacket& recvData)
{
    sLog.outDebug("WORLD: Received CMSG_PARTY_SILENCE");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    ObjectGuid ignoreGuid;
    recvData >> ignoreGuid;

    if (!_player)
        return;

    Group* grp = _player->GetGroup();
    if (!grp)
        return;

    if (!grp->IsMember(ignoreGuid))
        return;

    if (!grp->IsLeader(GetPlayer()->GetObjectGuid()) && grp->GetMainAssistantGuid() != GetPlayer()->GetObjectGuid())
        return;

    VoiceChatChannel* v_channel = nullptr;
    if (!grp->IsBattleGroup())
    {
        if (grp->IsRaidGroup())
            v_channel = sVoiceChatMgr.GetRaidVoiceChatChannel(grp->GetId());
        else
            v_channel = sVoiceChatMgr.GetGroupVoiceChatChannel(grp->GetId());
    }
    else if (_player->InBattleGround())
        v_channel = sVoiceChatMgr.GetBattlegroundVoiceChatChannel(_player->GetBattleGroundId(), _player->GetBGTeam());

    if (!v_channel)
        return;

    v_channel->ForceMuteMember(ignoreGuid);
}

void WorldSession::HandlePartyUnsilenceOpcode(WorldPacket& recvData)
{
    sLog.outDebug("WORLD: Received CMSG_PARTY_UNSILENCE");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    ObjectGuid ignoreGuid;
    recvData >> ignoreGuid;

    if (!_player)
        return;

    Group* grp = _player->GetGroup();
    if (!grp)
        return;

    if (!grp->IsMember(ignoreGuid))
        return;

    if (!grp->IsLeader(GetPlayer()->GetObjectGuid()) && grp->GetMainAssistantGuid() != GetPlayer()->GetObjectGuid())
        return;

    VoiceChatChannel* v_channel = nullptr;
    if (!grp->IsBattleGroup())
    {
        if (grp->IsRaidGroup())
            v_channel = sVoiceChatMgr.GetRaidVoiceChatChannel(grp->GetId());
        else
            v_channel = sVoiceChatMgr.GetGroupVoiceChatChannel(grp->GetId());
    }
    else if (_player->InBattleGround())
        v_channel = sVoiceChatMgr.GetBattlegroundVoiceChatChannel(_player->GetBattleGroundId(), _player->GetBGTeam());

    if (!v_channel)
        return;

    v_channel->ForceUnmuteMember(ignoreGuid);
}

void WorldSession::HandleChannelSilenceOpcode(WorldPacket& recvData)
{
    sLog.outDebug("WORLD: Received CMSG_CHANNEL_SILENCE");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    if (!_player)
        return;

    std::string channelName, playerName;
    recvData >> channelName >> playerName;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        Channel* chan = cMgr->GetChannel(channelName, nullptr, false);
        if (chan && chan->IsVoiceEnabled())
        {
            ObjectGuid plrGuid = sObjectMgr.GetPlayerGuidByName(playerName);
            if (!plrGuid)
                return;

            if (VoiceChatChannel* v_channel = sVoiceChatMgr.GetCustomVoiceChatChannel(channelName, _player->GetTeam()))
            {
                if (v_channel->IsOn(plrGuid))
                {
                    v_channel->ForceMuteMember(plrGuid);
                    chan->SetMicMute(_player, playerName.c_str(), true);
                }
            }
        }
    }
}

void WorldSession::HandleChannelUnsilenceOpcode(WorldPacket& recvData)
{
    sLog.outDebug("WORLD: Received CMSG_CHANNEL_UNSILENCE");

    if (!sVoiceChatMgr.CanUseVoiceChat())
        return;

    if (!_player)
        return;

    std::string channelName, playerName;
    recvData >> channelName >> playerName;

    if (ChannelMgr* cMgr = channelMgr(_player->GetTeam()))
    {
        Channel* chan = cMgr->GetChannel(channelName, nullptr, false);
        if (chan && chan->IsVoiceEnabled())
        {
            ObjectGuid plrGuid = sObjectMgr.GetPlayerGuidByName(playerName);
            if (!plrGuid)
                return;

            if (VoiceChatChannel* v_channel = sVoiceChatMgr.GetCustomVoiceChatChannel(channelName, _player->GetTeam()))
            {
                if (v_channel->IsOn(plrGuid))
                {
                    v_channel->ForceUnmuteMember(plrGuid);
                    chan->SetMicMute(_player, playerName.c_str(), false);
                }
            }
        }
    }
}

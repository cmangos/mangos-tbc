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

#ifndef _VOICECHATMGR_H
#define _VOICECHATMGR_H

#include "VoiceChatServerSocket.h"
#include "VoiceChatDefines.h"
#include "Server/Opcodes.h"
class VoiceChatChannel;

class VoiceChatMgr
{
public:

    VoiceChatMgr();
    void Init();
    void LoadConfigs();
    void Update();
    void SocketDisconnected();
    bool RequestNewSocket(VoiceChatServerSocket* socket);
    void QueuePacket(std::unique_ptr<VoiceChatServerPacket> new_packet);

    void VoiceSocketThread();

    bool NeedConnect();
    bool NeedReconnect();
    int32 GetReconnectAttempts() const;

    bool IsEnabled() const { return enabled; }
    bool CanUseVoiceChat();
    bool CanSeeVoiceChat();

    // configs
    uint32 GetVoiceServerConnectAddress() const { return server_address; }
    uint16 GetVoiceServerConnectPort() const { return server_port; }
    uint32 GetVoiceServerVoiceAddress() const { return voice_address; }
    uint16 GetVoiceServerVoicePort() const { return voice_port; }
    std::string GetVoiceServerConnectAddressString() { return server_address_string; }

    // manage voice channels
    void CreateVoiceChatChannel(VoiceChatChannelTypes type, uint32 groupId = 0, const std::string& name = "", Team team = TEAM_BOTH_ALLOWED);
    void DeleteVoiceChatChannel(VoiceChatChannel* channel);
    bool IsVoiceChatChannelBeingCreated(VoiceChatChannelTypes type, uint32 groupId = 0, const std::string& name = "", Team team = TEAM_BOTH_ALLOWED);

    void CreateGroupVoiceChatChannel(uint32 groupId);
    void CreateRaidVoiceChatChannel(uint32 groupId);
    void CreateBattlegroundVoiceChatChannel(uint32 instanceId, Team team);
    void CreateCustomVoiceChatChannel(const std::string& name, Team team);

    void DeleteGroupVoiceChatChannel(uint32 groupId);
    void DeleteRaidVoiceChatChannel(uint32 groupId);
    void DeleteBattlegroundVoiceChatChannel(uint32 instanceId, Team team);
    void DeleteCustomVoiceChatChannel(const std::string& name, Team team);

    void ConvertToRaidChannel(uint32 groupId);

    VoiceChatChannel* GetVoiceChatChannel(uint16 channel_id);
    VoiceChatChannel* GetGroupVoiceChatChannel(uint32 group_id);
    VoiceChatChannel* GetRaidVoiceChatChannel(uint32 group_id);
    VoiceChatChannel* GetBattlegroundVoiceChatChannel(uint32 instanceId, Team team);
    VoiceChatChannel* GetCustomVoiceChatChannel(const std::string& name, Team team);
    std::vector<VoiceChatChannel*> GetPossibleVoiceChatChannels(ObjectGuid guid);

    // restore after reconnect
    static void RestoreVoiceChatChannels();
    // delete after disconnect
    void DeleteAllChannels();

    // get proper team if cross faction channels enabled
    static Team GetCustomChannelTeam(Team team);

    // manage users
    void AddToGroupVoiceChatChannel(ObjectGuid guid, uint32 groupId);
    void AddToRaidVoiceChatChannel(ObjectGuid guid, uint32 groupId);
    void AddToBattlegroundVoiceChatChannel(ObjectGuid guid);
    void AddToCustomVoiceChatChannel(ObjectGuid guid, const std::string& name, Team team);

    void RemoveFromGroupVoiceChatChannel(ObjectGuid guid, uint32 groupId);
    void RemoveFromRaidVoiceChatChannel(ObjectGuid guid, uint32 groupId);
    void RemoveFromBattlegroundVoiceChatChannel(ObjectGuid guid);
    void RemoveFromCustomVoiceChatChannel(ObjectGuid guid, const std::string& name, Team team);

    // change user state on voice server
    void EnableChannelSlot(uint16 channel_id, uint8 slot_id);
    void DisableChannelSlot(uint16 channel_id, uint8 slot_id);
    void VoiceChannelSlot(uint16 channel_id, uint8 slot_id);
    void DevoiceChannelSlot(uint16 channel_id, uint8 slot_id);
    void MuteChannelSlot(uint16 channel_id, uint8 slot_id);
    void UnmuteChannelSlot(uint16 channel_id, uint8 slot_id);

    void JoinAvailableVoiceChatChannels(WorldSession* session);
    void SendAvailableVoiceChatChannels(WorldSession* session); // Not used currently

    // remove from all channels
    void RemoveFromVoiceChatChannels(ObjectGuid guid);

    uint64 GetNewSessionId() { return new_session_id++; }

    Messager<VoiceChatMgr>& GetMessager() { return m_messager; }

    // Command Handlers
    void DisableVoiceChat();
    void EnableVoiceChat();
    VoiceChatStatistics GetStatistics();

private:

    static void SendVoiceChatStatus(bool status);
    static void SendVoiceChatServiceMessage(Opcodes opcode);
    static void SendVoiceChatServiceDisconnect() { SendVoiceChatServiceMessage(SMSG_COMSAT_DISCONNECT); }
    static void SendVoiceChatServiceConnectFail() { SendVoiceChatServiceMessage(SMSG_COMSAT_CONNECT_FAIL); }
    static void SendVoiceChatServiceReconnected() { SendVoiceChatServiceMessage(SMSG_COMSAT_RECONNECT_TRY); }

    void HandleVoiceChatServerPacket(VoiceChatServerPacket& pck);
    void ProcessByteBufferException(VoiceChatServerPacket const& packet);

    // socket to voice server
    std::shared_ptr<VoiceChatServerSocket> m_socket;
    std::shared_ptr<VoiceChatServerSocket> m_requestSocket;
    std::vector<VoiceChatChannelRequest> m_requests;
    uint32 new_request_id;
    uint64 new_session_id;

    // configs
    uint32 server_address;
    uint16 server_port;
    std::string server_address_string;

    // voice server address and udp port for client
    uint32 voice_address;
    uint16 voice_port;

    // next connect attempt
    time_t next_connect;
    time_t next_ping;
    time_t last_pong;

    // enabled in config
    bool enabled;

    // how many attemps to reconnect
    int8 maxConnectAttempts;
    // how many reconnect attempts have been made
    uint8 curReconnectAttempts;

    // voice channels
    std::map<uint16, VoiceChatChannel*> m_VoiceChatChannels;

    // state of connection
    VoiceChatState state;

    uint32 lastUpdate;

    // Thread safety mechanisms
    std::mutex m_recvQueueLock;
    std::deque<std::unique_ptr<VoiceChatServerPacket>> m_recvQueue;

    Messager<VoiceChatMgr> m_messager;

    boost::asio::io_service m_voiceService;
};

#define sVoiceChatMgr MaNGOS::Singleton<VoiceChatMgr>::Instance()

#endif

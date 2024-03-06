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

#include "Server/WorldSession.h"
#include "Globals/ObjectMgr.h"
#include "Log/Log.h"
#include "World/World.h"


static inline void LookingForGroupMakeMeetingStoneQueueLeftFor(WorldPacket& data, uint32 entry)
{
    data.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    data << uint32(entry);
    data << uint8(0x00);
}

static inline void LookingForGroupMakeMeetingStoneQueueJoinedFor(WorldPacket& data, uint32 entry)
{
    data.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    data << uint32(entry);
    data << uint8(0x01);
}

static inline void LookingForGroupMakeMeetingStoneQueueMatchedFor(WorldPacket& data, uint32 entry, bool asLeader = false)
{
    data.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    data << uint32(entry);
    data << uint8(0x05);
    data << uint8(asLeader);
}

static inline void LookingForGroupMakeMeetingStoneMemberAdded(WorldPacket& data, ObjectGuid guid)
{
    data.Initialize(SMSG_MEETINGSTONE_SETQUEUE, 8);
    data << guid;
}

static inline const Player* LookingForGroupGetCurrentLeader(Player* _this)
{
    if (Group* group = _this->GetGroup())
    {
        if (!group->IsBattleGroup() && !group->IsFull() && !group->IsLeader(_this->GetObjectGuid()))
        {
            for (const GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
            {
                if (Player* member = itr->getSource())
                {
                    if (group->IsLeader(member->GetObjectGuid()))
                        return member;
                }
            }
        }
    }
    return _this;
}

static inline void LookingForGroupUpdateChannelStatus(Player* _this)
{
    const Player* leader = LookingForGroupGetCurrentLeader(_this);

    if (leader->m_lookingForGroup.isEmpty())
    {
        if (sWorld.getConfig(CONFIG_BOOL_CHANNEL_RESTRICTED_LFG) && _this->GetSession()->GetSecurity() == SEC_PLAYER)
            _this->LeaveLFGChannel();
    }
}

static inline bool LookingForGroupUpdateQueueStatus(Player* _this, WorldSession* _session)
{
    Group* _group = _this->GetGroup();

    const bool autojoin = (_this->m_lookingForGroup.isAutoJoin() && _session->LookingForGroup_auto_join);
    const bool autofill = (_this->m_lookingForGroup.isAutoFill() && _session->LookingForGroup_auto_add);
    const bool notraid = (!_group || (!_group->IsRaidGroup() && _group->IsLeader(_this->GetObjectGuid())));

    const bool status = ((autojoin && !_group) || (autofill && notraid));

    if (_session->LookingForGroup_queue == status)
        return false;

    _session->LookingForGroup_queue = status;

    // Sync client's UI queue status

    const Player* pov = LookingForGroupGetCurrentLeader(_this);
    const bool queued = pov->GetSession()->LookingForGroup_queue;
    auto const& info = pov->m_lookingForGroup;

    WorldPacket data(SMSG_LFG_UPDATE_QUEUED, 1);
    data << uint8(queued);

    WorldPacket message;
    if (queued)
        LookingForGroupMakeMeetingStoneQueueJoinedFor(message, info.more.entry);
    else
        LookingForGroupMakeMeetingStoneQueueLeftFor(message, info.more.entry);

    if (!_group || !notraid)
    {
        _session->SendPacket(data);

        if (info.isLFM())
            _session->SendPacket(message);
    }
    else
    {
        _group->BroadcastPacket(data, true);

        if (info.isLFM())
            _group->BroadcastPacket(message, true);
    }
    return true;
}

static inline void LookingForGroupUpdateUI(Player* _this, WorldSession* _session, bool completed = false)
{
    Group* _group = _this->GetGroup();

    if (!_group || !_group->IsLeader(_this->GetObjectGuid()))
    {
        if (completed)
            _session->SendMeetingStoneComplete();
        else
            _session->SendLFGUpdate();

        LookingForGroupUpdateChannelStatus(_this);
        return;
    }

    for (const GroupReference* itr = _group->GetFirstMember(); itr; itr = itr->next())
    {
        if (Player* member = itr->getSource())
        {
            if (completed)
                member->GetSession()->SendMeetingStoneComplete();
            else
                member->GetSession()->SendLFGUpdate();

            LookingForGroupUpdateChannelStatus(member);
        }
    }
}

static inline void LookingForGroupUpdate(Player* _this, WorldSession* _session, bool completed = false)
{
    LookingForGroupUpdateQueueStatus(_this, _session);
    LookingForGroupUpdateUI(_this, _session, completed);
}

static inline void LookingForGroupClearLFG(Player* _this, WorldSession* _session)
{
    if (!_this->m_lookingForGroup.isLFG())
        return;

    // Unset LFG serverside and force client to update
    for (int i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
        _this->m_lookingForGroup.group[i].clear();

    LookingForGroupUpdate(_this, _session);
}

static inline void LookingForGroupClearLFM(Player* _this, WorldSession* _session)
{
    if (!_this->m_lookingForGroup.isLFM())
        return;

    // Unset LFM serverside and force client to update
    _this->m_lookingForGroup.more.clear();

    LookingForGroupUpdate(_this, _session);
}

static inline void LookingForGroupClear(Player* _this, WorldSession* _session, bool completed = false)
{
    // Unset all serverside and force client to update
    _this->m_lookingForGroup.clear();
    LookingForGroupUpdate(_this, _session, completed);
}

static inline bool LookingForGroupAddMemberFor(Player* _this, WorldSession* _session, Player* member, uint32 entry, Group*& _group)
{
    const bool create = !_group;

    if (create)
    {
        _group = new Group;

        if (!_group->Create(_this->GetObjectGuid(), _this->GetName()))
        {
            delete _group;
            _group = nullptr;
            return false;
        }

        sObjectMgr.AddGroup(_group);
    }

    const ObjectGuid _guid = member->GetObjectGuid();

    if (!_group->AddMember(_guid, member->GetName()))
        return false;  

    WorldPacket data;

    if (create)
    {
        LookingForGroupMakeMeetingStoneQueueMatchedFor(data, entry, true);
        _session->SendPacket(data);
    }

    LookingForGroupMakeMeetingStoneMemberAdded(data, _guid);
    _group->BroadcastPacket(data, true, -1, _guid);

    WorldSession* session = member->GetSession();

    LookingForGroupMakeMeetingStoneQueueMatchedFor(data, entry);
    session->SendPacket(data);

    LookingForGroupClear(member, session);

    if (_group->IsFull())
    {
        LookingForGroupClear(_this, _this->GetSession(), true);
        return false;
    }

    return true;
}

static void LookingForGroupTryJoin(Player* _player, bool initial = false)
{
    WorldSession* _session = _player->GetSession();  

    // skip not can autojoin cases and player group case
    if (Group* _group = _player->GetGroup())
    {
        if (_group->IsBattleGroup() || _group->IsFull() || !_group->IsLeader(_player->GetObjectGuid()))
            LookingForGroupClear(_player, _session);
        else
            LookingForGroupClearLFG(_player, _session);
    }

    LookingForGroupUpdateQueueStatus(_player, _session);

    if (!_session->LookingForGroup_queue || !_player->m_lookingForGroup.isLFG())
        return;

    bool attempted = false;

    // TODO: Guard Player Map
    HashMapHolder<Player>::MapType const& players = sObjectAccessor.GetPlayers();
    for (HashMapHolder<Player>::MapType::const_iterator iter = players.begin(); iter != players.end(); ++iter)
    {
        Player* plr = iter->second;

        // skip enemies and self
        if (!plr || plr == _player || plr->GetTeam() != _player->GetTeam())
            continue;

        WorldSession* session = plr->GetSession();

        // skip players not in world or reconnecting
        if (!plr->IsInWorld() || session->IsOffline())
            continue;

        Group* grp = plr->GetGroup();

        // skip players in not compatinle groups and dequeue them if discovered
        if (grp && (grp->IsBattleGroup() || grp->IsFull() || !grp->IsLeader(_player->GetObjectGuid())))
        {
            LookingForGroupClear(plr, session);
            continue;
        }

        LookingForGroupUpdateQueueStatus(plr, session);

        // skip not queued
        if (!session->LookingForGroup_queue || plr->m_lookingForGroup.more.empty())
            continue;

        // skip not fitting slots
        if (!_player->m_lookingForGroup.isLFG(plr->m_lookingForGroup, true))
            continue;

        Group* result = grp;

        // stop at join success
        if (LookingForGroupAddMemberFor(plr, session, _player, plr->m_lookingForGroup.more.entry, result))
            break;
        else if (!grp)
            attempted = true;
        // group is full or cant join for other reasons, continue
    }

    if (!initial && attempted && _session->LookingForGroup_queue)
        _session->SendMeetingStoneInProgress();
}

static void LookingForGroupTryFill(Player* _player, bool initial = false)
{
    WorldSession* _session = _player->GetSession();

    Group* _group = _player->GetGroup();

    // skip non auto-join slot or player in a battleground, not group leader, group is full cases
    if (_group && (_group->IsBattleGroup() || _group->IsFull() || !_group->IsLeader(_player->GetObjectGuid())))
    {
        LookingForGroupClear(_player, _session);
        return;
    }

    LookingForGroupUpdateQueueStatus(_player, _session);

    if (!_session->LookingForGroup_queue || _player->m_lookingForGroup.more.empty())
        return;

    bool attempted = false;

    // TODO: Guard Player map
    HashMapHolder<Player>::MapType const& players = sObjectAccessor.GetPlayers();
    for (HashMapHolder<Player>::MapType::const_iterator iter = players.begin(); iter != players.end(); ++iter)
    {
        Player* plr = iter->second;

        // skip enemies and self
        if (!plr || plr == _player || plr->GetTeam() != _player->GetTeam())
            continue;

        WorldSession* session = plr->GetSession();

        // skip players not in world or reconnecting
        if (!plr->IsInWorld() || session->IsOffline())
            continue;

        // skip players in groups, dequeue and remove them from LFG if discovered
        if (Group* grp = plr->GetGroup())
        {
            if (grp->IsBattleGroup() || grp->IsFull() || !grp->IsLeader(plr->GetObjectGuid()))
                LookingForGroupClear(plr, session);
            else
                LookingForGroupClearLFG(plr, session);
            continue;
        }

        LookingForGroupUpdateQueueStatus(plr, session);

        // skip not queued
        if (!session->LookingForGroup_queue || !plr->m_lookingForGroup.isLFG())
            continue;

        // skip not fitting slots
        if (!plr->m_lookingForGroup.isLFG(_player->m_lookingForGroup, true))
            continue;

        Group* result = _group;

        // stop at false result (full?)
        if (!LookingForGroupAddMemberFor(_player, _session, plr, _player->m_lookingForGroup.more.entry, result))
        {
            attempted = true;
            break;
        }
        // group is not full yet, continue
    }

    if (!initial && attempted && _session->LookingForGroup_queue)
        _session->SendMeetingStoneInProgress();
}

static inline void LookingForGroupSetAutoJoin(Player* _player, WorldSession* _session, bool enabled)
{
    if (LookingForGroupUpdateQueueStatus(_player, _session))
    {
        if (enabled)
            LookingForGroupTryJoin(_player, true);
        return;
    }

    if (!enabled)
        return;

    uint8 result = 0x00;                                    // No message

    WorldPacket data(SMSG_MEETINGSTONE_JOINFAILED, 1);
    data << uint8(result);
    _session->SendPacket(data);
}

static inline void LookingForGroupSetAutoFill(Player* _player, WorldSession* _session, bool enabled)
{
    if (LookingForGroupUpdateQueueStatus(_player, _session))
    {
        if (enabled)
            LookingForGroupTryFill(_player, true);
        return;
    }

    if (!enabled)
        return;

    uint8 result = 0x00;                                    // No message

    if (Group* _group = _player->GetGroup())
    {
        if (_group->IsRaidGroup())
            result = 0x03;                                  // NO_RAID_GROUP
        else if (!_group->IsLeader(_player->GetObjectGuid()))
            result = 0x01;                                  // MUST_BE_LEADER
        else
            result = 0x02;                                  // No message, failure for other reason related to groups?
    }

    WorldPacket data(SMSG_MEETINGSTONE_JOINFAILED, 1);
    data << uint8(result);
    _session->SendPacket(data);
}

void WorldSession::HandleLfgSetAutoJoinOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFG_SET_AUTOJOIN");

    LookingForGroup_auto_join = true;

    if (!_player)                                           // needed because STATUS_AUTHED
        return;

    LookingForGroupSetAutoJoin(_player, _player->GetSession(), true);
}

void WorldSession::HandleLfgClearAutoJoinOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFG_CLEAR_AUTOJOIN");

    LookingForGroup_auto_join = false;

    LookingForGroupSetAutoJoin(_player, _player->GetSession(), false);
}

void WorldSession::HandleLfmSetAutoFillOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFM_SET_AUTOFILL");

    LookingForGroup_auto_add = true;

    if (!_player)                                           // needed because STATUS_AUTHED
        return;

    LookingForGroupSetAutoFill(_player, _player->GetSession(), true);
}

void WorldSession::HandleLfmClearAutoFillOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFM_CLEAR_AUTOFILL");

    LookingForGroup_auto_add = false;

    LookingForGroupSetAutoFill(_player, _player->GetSession(), false);
}

void WorldSession::HandleLfgClearOpcode(WorldPacket& /*recv_data */)
{
    DEBUG_LOG("CMSG_CLEAR_LOOKING_FOR_GROUP");

    LookingForGroupClearLFG(_player, this);
}

void WorldSession::HandleSetLfgOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LOOKING_FOR_GROUP");

    uint32 slot, data;

    recv_data >> slot >> data;

    if (slot >= MAX_LOOKING_FOR_GROUP_SLOT)
        return;

    if (Group* _group = _player->GetGroup())
    {
        const Player* pov = LookingForGroupGetCurrentLeader(_player);

        if (pov != _player && pov->m_lookingForGroup.isLFM())
        {
            WorldPacket data(SMSG_LFG_LEADER_IS_LFM);
            SendPacket(data);
            return;
        }

        SendLFGUpdate();
        return;
    }

    uint16 entry = (data & 0xFFFF);
    uint16 type = ((data >> 24) & 0xFFFF);

    DEBUG_LOG("LFG set: looknumber %u, temp %X, type %u, entry %u", slot, data, type, entry);
    _player->m_lookingForGroup.group[slot].set(entry, type);
    LookingForGroupClearLFM(_player, this);

    LookingForGroupUpdateQueueStatus(_player, this);

    if (LookingForGroup_auto_join)
        LookingForGroupTryJoin(_player);
}

void WorldSession::HandleLfmClearOpcode(WorldPacket& /*recv_data */)
{
    DEBUG_LOG("CMSG_CLEAR_LOOKING_FOR_MORE");

    LookingForGroupClearLFM(_player, this);
}

void WorldSession::HandleSetLfmOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LOOKING_FOR_MORE");

    uint32 data;

    recv_data >> data;

    if (Group* _group = _player->GetGroup())
    {
        ObjectGuid _guid = _player->GetObjectGuid();

        if (_group->IsBattleGroup() || _group->IsFull() || !_group->IsLeader(_guid))
        {
            SendLFGUpdate();
            return;
        }
    }

    uint16 entry = (data & 0xFFFF);
    uint16 type = ((data >> 24) & 0xFFFF);

    DEBUG_LOG("LFM set: temp %u, zone %u, type %u", data, entry, type);
    _player->m_lookingForGroup.more.set(entry, type);
    LookingForGroupClearLFG(_player, this);

    // TODO broadcast LFM preference to party as well instead of full ui update?
    LookingForGroupUpdateUI(_player, this);

    LookingForGroup_queue = false;                      // FIXME: this is to cause requeue message
    LookingForGroupUpdateQueueStatus(_player, this);

    if (LookingForGroup_auto_add)
        LookingForGroupTryFill(_player);
}

void WorldSession::HandleSetLfgCommentOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LFG_COMMENT");

    std::string comment;

    recv_data >> comment;

    _player->m_lookingForGroup.comment = comment;
    DEBUG_LOG("LFG comment %s", comment.c_str());
}

void WorldSession::HandleLFGListQuery(WorldPacket& recv_data)
{
    DEBUG_LOG("MSG_LOOKING_FOR_GROUP");
    uint32 type, entry, unk;

    recv_data >> type >> entry >> unk;
    DEBUG_LOG("MSG_LOOKING_FOR_GROUP: type %u, entry %u, unk %u", type, entry, unk);

    if (LookingForGroup_auto_add)
        LookingForGroupTryFill(_player);

    if (LookingForGroup_auto_join)
        LookingForGroupTryJoin(_player);

    SendLFGListQueryResponse(LfgType(type), entry);
}

void WorldSession::SendMeetingStoneComplete()
{
    WorldPacket data(SMSG_MEETINGSTONE_COMPLETE);
    SendPacket(data);
}

void WorldSession::SendMeetingStoneInProgress()
{
    WorldPacket data(SMSG_MEETINGSTONE_IN_PROGRESS);
    SendPacket(data);
}

void WorldSession::SendLFGListQueryResponse(LfgType type, uint32 entry)
{
    // start prepare packet
    WorldPacket data(MSG_LOOKING_FOR_GROUP);
    data << uint32(type);                                   // type
    data << uint32(entry);                                  // entry from LFGDungeons.dbc
    data << uint32(0);                                      // displayed players count, placeholder
    data << uint32(0);                                      // found players count, placeholder

    uint32 displayed = 0;
    uint32 found = 0;

    // TODO: Guard Player map
    HashMapHolder<Player>::MapType const& players = sObjectAccessor.GetPlayers();
    for (const auto& i : players)
    {
        Player* plr = i.second;

        if (!plr || plr->GetTeam() != _player->GetTeam())
            continue;

        if (!plr->IsInWorld() || plr->GetSession()->IsOffline())
            continue;

        if (!plr->m_lookingForGroup.isLFG(entry, type, false) && !plr->m_lookingForGroup.isLFM(entry, type))
            continue;

        const Group* grp = plr->GetGroup();

        if (grp && (grp->IsBattleGroup() || grp->IsFull() || !grp->IsLeader(plr->GetObjectGuid())))
            continue;

        ++found;

        // Client hardcoded limitation on amount of players sent in the packet handler and UI:
        if (found > 50)
            continue;

        ++displayed;

        const bool isLFM = plr->m_lookingForGroup.isLFM(entry, type);

        data << plr->GetPackGUID();                         // packed guid
        data << uint32(plr->GetLevel());                    // level
        data << uint32(plr->GetZoneId());                   // current zone
        data << uint8(isLFM);                               // 0x00 - LFG, 0x01 - LFM

        if (isLFM)
        {
            data << uint32(plr->m_lookingForGroup.more.entry | (plr->m_lookingForGroup.more.type << 24));
            data << uint32(0x1000000);
            data << uint32(0x1000000);
        }
        else
        {
            for (uint8 j = 0; j < MAX_LOOKING_FOR_GROUP_SLOT; ++j)
                data << uint32(plr->m_lookingForGroup.group[j].entry | (plr->m_lookingForGroup.group[j].type << 24));
        }

        data << plr->m_lookingForGroup.comment;

        data << uint32(0);                                  // other group members count, placeholder

        if (grp)
        {
            const size_t offset = (data.wpos() - 4);        // other group members count, offset
            uint32 count = 0;                               // other group members count

            for (const GroupReference* itr = grp->GetFirstMember(); itr != nullptr; itr = itr->next())
            {
                if (const Player* member = itr->getSource())
                {
                    if (member->GetObjectGuid() != plr->GetObjectGuid())
                    {
                        data << member->GetPackGUID();      // packed guid
                        data << uint32(member->GetLevel()); // player level
                        ++count;
                    }
                }
            }

            data.put<uint32>(offset, count);            // other group members count, fill the placeholder
        }
    }

    // fill count placeholders
    data.put<uint32>(4 + 4,  displayed);
    data.put<uint32>(4 + 4 + 4, found);

    SendPacket(data);
}

void WorldSession::SendLFGUpdate()
{
    const Player* pov = LookingForGroupGetCurrentLeader(_player);
    auto const& info = pov->m_lookingForGroup;
    const bool queued = pov->GetSession()->LookingForGroup_queue;
    const bool isLFM = info.isLFM();

    WorldPacket data(SMSG_LFG_UPDATE);
    data << uint8(queued);
    data << uint8(info.isLFG());
    data << uint8(isLFM);
    if (isLFM)
        data << uint32(info.more.entry | (info.more.type << 24));
    SendPacket(data);
}

void WorldSession::SendLFGUpdateLFG()
{
    // Syncs player's own LFG UI selection with what we send here
    auto const& selection = _player->m_lookingForGroup.group;

    WorldPacket data(SMSG_LFG_UPDATE_LFG, (4 * MAX_LOOKING_FOR_GROUP_SLOT));
    for (uint8 i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
        data << uint32(selection[i].entry | (selection[i].type << 24));
    SendPacket(data);
}

void WorldSession::SendLFGUpdateLFM()
{
    // Syncs player's own LFG UI selection with what we send here
    auto const& info = _player->m_lookingForGroup;
    const bool isLFM = info.isLFM();
    auto const& selection = _player->m_lookingForGroup.more;

    WorldPacket data(SMSG_LFG_UPDATE_LFM);
    data << uint8(isLFM);
    if (isLFM)
        data << uint32(selection.entry | (selection.type << 24));
    SendPacket(data);
}

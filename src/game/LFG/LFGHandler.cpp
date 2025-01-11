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
#include "LFG/LFGDefines.h"
#include "LFG/LFGQueue.h"

void WorldSession::HandleLfgSetAutoJoinOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFG_SET_AUTOJOIN");

    m_lfgInfo.autojoin = true;

    if (_player)
    {
        sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
        {
            queue->SetAutoJoin(playerGuid, true);
        });
    }

    uint8 result = uint8(MeetingstoneFailedStatus::MEETINGSTONE_FAIL_NONE);

    WorldPacket data(SMSG_MEETINGSTONE_JOINFAILED, 1);
    data << uint8(result);
    SendPacket(data);
}

void WorldSession::HandleLfgClearAutoJoinOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFG_CLEAR_AUTOJOIN");

    m_lfgInfo.autojoin = false;

    if (_player)
    {
        sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
        {
            queue->SetAutoJoin(playerGuid, false);
        });
    }
}

void WorldSession::HandleLfmSetAutoFillOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFM_SET_AUTOFILL");

    MeetingstoneFailedStatus result = MeetingstoneFailedStatus::MEETINGSTONE_FAIL_NONE;

    if (_player) // can be sent during login
    {
        if (Group* _group = _player->GetGroup())
        {
            if (_group->IsRaidGroup())
                result = MeetingstoneFailedStatus::MEETINGSTONE_FAIL_RAID_GROUP;
            else if (!_group->IsLeader(_player->GetObjectGuid()))
                result = MeetingstoneFailedStatus::MEETINGSTONE_FAIL_PARTYLEADER;
            else
                result = MeetingstoneFailedStatus::MEETINGSTONE_FAIL_FULL_GROUP;
        }

        if (result == MeetingstoneFailedStatus::MEETINGSTONE_FAIL_NONE)
        {
            m_lfgInfo.autofill = true;
            sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
            {
                queue->SetAutoFill(playerGuid, true);
            });
        }
    }
    else
        m_lfgInfo.autofill = true;

    WorldPacket data(SMSG_MEETINGSTONE_JOINFAILED, 1);
    data << uint8(result);
    SendPacket(data);
}

void WorldSession::HandleLfmClearAutoFillOpcode(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_LFM_CLEAR_AUTOFILL");

    m_lfgInfo.autofill = false;

    if (_player)
    {
        sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
        {
            queue->SetAutoFill(playerGuid, false);
        });
    }
}

void WorldSession::HandleLfgClearOpcode(WorldPacket& /*recv_data */)
{
    DEBUG_LOG("CMSG_CLEAR_LOOKING_FOR_GROUP");

    ObjectGuid leaderGuid = _player->GetObjectGuid();
    if (Group* group = _player->GetGroup())
        leaderGuid = group->GetLeaderGuid();

    sWorld.GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->StopLookingForGroup(leaderGuid, playerGuid);
    });
}

void WorldSession::HandleSetLfgOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LOOKING_FOR_GROUP");

    uint32 slot, data;

    recv_data >> slot >> data;

    if (slot >= MAX_LOOKING_FOR_GROUP_SLOT)
        return;

    LFGPlayerQueueInfo info;

    ObjectGuid leaderGuid = _player->GetObjectGuid();
    if (Group* _group = _player->GetGroup())
    {
        if (Group* group = _player->GetGroup())
        {
            if (!group->IsBattleGroup() && !group->IsFull() && !group->IsLeader(_player->GetObjectGuid()))
            {
                leaderGuid = group->GetLeaderGuid();
                for (const GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
                {
                    if (Player* member = itr->getSource())
                    {
                        if (!group->IsLeader(member->GetObjectGuid()))
                        {
                            info.members.push_back(LFGGroupQueueInfo(member->GetObjectGuid(), member->GetLevel()));
                        }
                    }
                }
            }
        }
    }

    uint16 entry = (data & 0xFFFF);
    uint16 type = ((data >> 24) & 0xFFFF);

    if (m_lfgInfo.queued) // setting a slot instead of starting lfg entirely
    {
        sWorld.GetLFGQueue().GetMessager().AddMessage([leaderGuid, slot, entry, type](LFGQueue* queue)
        {
            queue->SetLfgSlot(leaderGuid, slot, entry, type);
        });
        return;
    }

    info.leaderGuid = leaderGuid;
    info.group[slot].set(entry, type);
    info.team = _player->GetTeam();
    info.level = _player->GetLevel();
    info.zoneId = _player->GetZoneId();
    info.autoJoin = m_lfgInfo.autojoin;

    DEBUG_LOG("LFG set: looknumber %u, temp %X, type %u, entry %u", slot, data, type, entry);
    sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid(), info](LFGQueue* queue)
    {
        queue->StartLookingForGroup(info, playerGuid);
    });
}

void WorldSession::HandleLfmClearOpcode(WorldPacket& /*recv_data */)
{
    DEBUG_LOG("CMSG_CLEAR_LOOKING_FOR_MORE");

    sWorld.GetLFGQueue().GetMessager().AddMessage([playerGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->StopLookingForMore(playerGuid);
    });
}

void WorldSession::HandleSetLfmOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LOOKING_FOR_MORE");

    uint32 data;

    recv_data >> data;

    LFGPlayerQueueInfo info;

    ObjectGuid leaderGuid = _player->GetObjectGuid();
    if (Group* _group = _player->GetGroup())
    {
        if (Group* group = _player->GetGroup())
        {
            if (!group->IsBattleGroup() && !group->IsFull() && !group->IsLeader(_player->GetObjectGuid()))
            {
                leaderGuid = group->GetLeaderGuid();
                for (const GroupReference* itr = group->GetFirstMember(); itr; itr = itr->next())
                {
                    if (Player* member = itr->getSource())
                    {
                        if (!group->IsLeader(member->GetObjectGuid()))
                        {
                            info.members.push_back(LFGGroupQueueInfo(member->GetObjectGuid(), member->GetLevel()));
                        }
                    }
                }
            }
            else
            {
                SendLFGUpdate();
                return;
            }
        }
    }

    uint16 entry = (data & 0xFFFF);
    uint16 type = ((data >> 24) & 0xFFFF);

    if (m_lfgInfo.queued) // setting a slot instead of starting lfg entirely
    {
        sWorld.GetLFGQueue().GetMessager().AddMessage([leaderGuid, entry, type](LFGQueue* queue)
        {
            queue->SetLfmData(leaderGuid, entry, type);
        });
        return;
    }

    info.leaderGuid = leaderGuid;
    info.more.set(entry, type);
    info.team = _player->GetTeam();
    info.level = _player->GetLevel();
    info.zoneId = _player->GetZoneId();
    info.autoFill = m_lfgInfo.autofill;

    DEBUG_LOG("LFM set: temp %u, zone %u, type %u", data, entry, type);
    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid(), info](LFGQueue* queue)
    {
        queue->StartLookingForMore(objectGuid, info);
    });
}

void WorldSession::HandleSetLfgCommentOpcode(WorldPacket& recv_data)
{
    DEBUG_LOG("CMSG_SET_LFG_COMMENT");

    std::string comment;

    recv_data >> comment;

    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid(), comment = comment](LFGQueue* queue)
    {
        queue->SetComment(objectGuid, comment);
    });

    DEBUG_LOG("LFG comment %s", comment.c_str());
}

void WorldSession::HandleLFGListQuery(WorldPacket& recv_data)
{
    DEBUG_LOG("MSG_LOOKING_FOR_GROUP");
    uint32 type, entry, unk;

    recv_data >> type >> entry >> unk;
    DEBUG_LOG("MSG_LOOKING_FOR_GROUP: type %u, entry %u, unk %u", type, entry, unk);

    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid(), team = _player->GetTeam(), type, entry](LFGQueue* queue)
    {
        queue->SendLFGListQueryResponse(objectGuid, team, LfgType(type), entry);
    });
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

void WorldSession::SendLFGUpdate()
{
    ObjectGuid leaderGuid = _player->GetObjectGuid();
    if (Group* group = _player->GetGroup())
        leaderGuid = group->GetLeaderGuid();
    sWorld.GetLFGQueue().GetMessager().AddMessage([leaderGuid, objectGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->SendLFGUpdate(leaderGuid, objectGuid);
    });
}

void WorldSession::SendLFGUpdateLFG()
{
    // Syncs player's own LFG UI selection with what we send here
    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->SendLFGUpdateLFG(objectGuid);
    });
}

void WorldSession::SendLFGUpdateLFM()
{
    // Syncs player's own LFG UI selection with what we send here
    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->SendLFGUpdateLFM(objectGuid);
    });
}

void WorldSession::HandleLfgAcceptLfgMatch(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_ACCEPT_LFG_MATCH");
    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->HandlePendingJoin(objectGuid);
    });
}

void WorldSession::HandleLfgDeclineLfgMatch(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_DECLINE_LFG_MATCH");
    sWorld.GetLFGQueue().GetMessager().AddMessage([objectGuid = _player->GetObjectGuid()](LFGQueue* queue)
    {
        queue->HandlePendingJoin(objectGuid);
    });
}

void WorldSession::HandleLfgCancelPendingLfg(WorldPacket& /*recv_data*/)
{
    DEBUG_LOG("CMSG_CANCEL_PENDING_LFG");
    // UNK use
}

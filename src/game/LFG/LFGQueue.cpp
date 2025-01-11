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

#include "LFG/LFGQueue.h"
#include "World/World.h"

void LFGQueue::Update()
{
    TimePoint previously = sWorld.GetCurrentClockTime();
    while (!World::IsStopped())
    {
        GetMessager().Execute(this);

        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    };
}

void LFGQueue::SetComment(ObjectGuid playerGuid, std::string const& comment)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end())
        return;

    itr->second.comment = comment;
}

void LFGQueue::SetAutoFill(ObjectGuid playerGuid, bool state)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end())
        return;

    itr->second.autoFill = state;
    TryFill(playerGuid, false);
}

void LFGQueue::SetAutoJoin(ObjectGuid playerGuid, bool state)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end())
        return;

    itr->second.autoJoin = state;
    TryJoin(playerGuid, false);
}

void LFGQueue::StartLookingForMore(ObjectGuid playerGuid, LFGPlayerQueueInfo info)
{
    auto itr = m_queuedPlayers.find(info.leaderGuid);
    if (itr != m_queuedPlayers.end())
    {
        sWorld.GetMessager().AddMessage([leaderGuid = info.leaderGuid, playerGuid](World* /*world*/)
        {
            Player* player = sObjectMgr.GetPlayer(playerGuid);

            if (leaderGuid != playerGuid)
            {
                WorldPacket data(SMSG_LFG_LEADER_IS_LFM);
                player->GetSession()->SendPacket(data);
            }
        });

        SendLFGUpdate(info.leaderGuid, playerGuid);
        return;
    }

    m_queuedPlayers.emplace(info.leaderGuid, info);

    sWorld.GetMessager().AddMessage([playerGuid](World* /*world*/)
    {
        Player* player = sObjectMgr.GetPlayer(playerGuid);

        if (player)
            player->GetSession()->m_lfgInfo.queued = true;
    });

    // TODO broadcast LFM preference to party as well instead of full ui update?
    GroupUpdateUI(playerGuid, false);
    GroupUpdateQueueStatus(playerGuid, playerGuid);

    TryFill(playerGuid, true);
}

void LFGQueue::StopLookingForMore(ObjectGuid playerGuid)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end())
        return;

    m_queuedPlayers.erase(itr);

    sWorld.GetMessager().AddMessage([playerGuid](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->m_lfgInfo.queued = false;
    });
}

void LFGQueue::StartLookingForGroup(LFGPlayerQueueInfo info, ObjectGuid invokerPlayer)
{
    auto itr = m_queuedPlayers.find(info.leaderGuid);
    if (itr != m_queuedPlayers.end())
    {
        sWorld.GetMessager().AddMessage([leaderGuid = info.leaderGuid, invokerPlayer](World* /*world*/)
        {
            Player* player = sObjectMgr.GetPlayer(invokerPlayer);
            if (leaderGuid != invokerPlayer && player)
            {
                WorldPacket data(SMSG_LFG_LEADER_IS_LFM);
                player->GetSession()->SendPacket(data);
            }
        });

        SendLFGUpdate(info.leaderGuid, invokerPlayer);
        return;
    }

    m_queuedPlayers.emplace(info.leaderGuid, info);

    sWorld.GetMessager().AddMessage([invokerPlayer](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(invokerPlayer))
            player->GetSession()->m_lfgInfo.queued = true;
    });

    SendLFGUpdate(info.leaderGuid, invokerPlayer);

    GroupUpdateQueueStatus(info.leaderGuid, invokerPlayer);

    TryJoin(info.leaderGuid, true);
}

void LFGQueue::StopLookingForGroup(ObjectGuid leaderGuid, ObjectGuid playerGuid)
{
    auto itr = m_queuedPlayers.find(leaderGuid);
    bool success = false;
    if (itr != m_queuedPlayers.end())
    {
        m_queuedPlayers.erase(itr);
    }

    GroupUpdateUI(leaderGuid, false);

    sWorld.GetMessager().AddMessage([playerGuid](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->m_lfgInfo.queued = false;
    });
}

void LFGQueue::SetLfgSlot(ObjectGuid leaderGuid, uint32 slot, uint16 entry, uint16 type)
{
    auto itr = m_queuedPlayers.find(leaderGuid);
    if (itr == m_queuedPlayers.end())
        return;

    auto& info = itr->second;
    info.group[slot].set(entry, type);

    bool found = false;
    for (auto& slot : info.group)
    {
        if (!slot.empty())
        {
            found = true;
            break;
        }
    }

    if (!found) // last slot cleared
        m_queuedPlayers.erase(itr);

    GroupUpdateUI(leaderGuid, false);

    if (!found)
    {
        sWorld.GetMessager().AddMessage([leaderGuid](World* /*world*/)
        {
            if (Player* player = sObjectMgr.GetPlayer(leaderGuid))
                player->GetSession()->m_lfgInfo.queued = false;
        });
    }
}

void LFGQueue::SetLfmData(ObjectGuid leaderGuid, uint16 entry, uint16 type)
{
    auto itr = m_queuedPlayers.find(leaderGuid);
    if (itr == m_queuedPlayers.end())
        return;

    auto& info = itr->second;
    info.more.set(entry, type);

    bool found = !info.more.empty();
    if (!found) // last slot cleared
        m_queuedPlayers.erase(itr);

    GroupUpdateUI(leaderGuid, false);

    if (!found)
    {
        sWorld.GetMessager().AddMessage([leaderGuid](World* /*world*/)
        {
            if (Player* player = sObjectMgr.GetPlayer(leaderGuid))
                player->GetSession()->m_lfgInfo.queued = false;
        });
    }
}

void LFGQueue::TryJoin(ObjectGuid playerGuid, bool initial)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end() || itr->second.autoJoin == false)
        return;

    auto& info = itr->second;

    bool attempted = false;

    for (auto& queueData : m_queuedPlayers)
    {
        if (!queueData.second.autoFill)
            continue;

        // skip not fitting slots
        if (!info.isLFG(queueData.second, true))
            continue;

        // stop at join success
        if (AddMember(queueData.second, info, queueData.second.more.entry))
            break;
        else if (info.members.empty())
            attempted = true;
    }

    if (!initial && attempted)
    {
        sWorld.GetMessager().AddMessage([playerGuid](World* /*world*/)
        {
            if (Player* player = sObjectMgr.GetPlayer(playerGuid))
                player->GetSession()->SendMeetingStoneInProgress();
        });
    }
}

void LFGQueue::TryFill(ObjectGuid leaderGuid, bool initial)
{
    auto itr = m_queuedPlayers.find(leaderGuid);
    if (itr == m_queuedPlayers.end() || itr->second.autoFill == false)
        return;

    auto& info = itr->second;

    bool attempted = false;

    for (auto& queueData : m_queuedPlayers)
    {
        if (!queueData.second.autoJoin)
            continue;

        // skip not fitting slots
        if (!queueData.second.isLFG(info, true))
            continue;

        // stop at false result (full?)
        if (!AddMember(info, queueData.second, info.more.entry))
        {
            attempted = true;
            break;
        }
    }

    if (!initial && attempted)
    {
        sWorld.GetMessager().AddMessage([leaderGuid](World* /*world*/)
        {
            if (Player* player = sObjectMgr.GetPlayer(leaderGuid))
                player->GetSession()->SendMeetingStoneInProgress();
        });
    }
}

bool LFGQueue::AddMember(LFGPlayerQueueInfo& info, LFGPlayerQueueInfo& playerInfo, uint32 entry)
{
    const bool create = info.members.empty();

    ObjectGuid playerGuid = playerInfo.leaderGuid;

    info.pendingMembers.push_back(playerGuid);

    playerInfo.pendingTransfer = true;
    playerInfo.pendingLeaderGuid = info.leaderGuid;
    playerInfo.pendingEntry = entry;

    sWorld.GetMessager().AddMessage([leaderGuid = info.leaderGuid, playerGuid, entry](World* world)
    {
        Player* player = sObjectMgr.GetPlayer(playerGuid);
        Player* leader = sObjectMgr.GetPlayer(leaderGuid);
        Group* grp = leader ? leader->GetGroup() : nullptr;

        if (grp && grp->IsFull())
        {
            world->GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid](LFGQueue* queue)
            {
                queue->RemovePendingJoin(leaderGuid, playerGuid);
            });
            return;
        }

        WorldPacket data;
        PendingInvite(data, entry);
        player->GetSession()->SendPacket(data);

        PendingMatch(data, entry);
        leader->GetSession()->SendPacket(data);
    });

    return true;
}

void LFGQueue::HandlePendingJoin(ObjectGuid playerGuid, bool accept)
{
    auto itr = m_queuedPlayers.find(playerGuid);
    if (itr == m_queuedPlayers.end())
        return;

    auto& info = itr->second;
    if (info.pendingTransfer == false)
        return;

    sWorld.GetMessager().AddMessage([leaderGuid = info.pendingLeaderGuid, playerGuid = info.leaderGuid, entry = info.pendingEntry](World* world)
    {
        Player* player = sObjectMgr.GetPlayer(playerGuid);
        Player* leader = sObjectMgr.GetPlayer(leaderGuid);
        if (!leader)
        {
            auto playerString = playerGuid.GetString(); auto leaderString = leaderGuid.GetString();
            sLog.outError("LFGQueue::HandlePendingJoin failed for guids %s %s due to offline leader", playerString.c_str(), leaderString.c_str());
            return;
        }

        if (!player)
        {
            auto playerString = playerGuid.GetString(); auto leaderString = leaderGuid.GetString();
            sLog.outError("LFGQueue::HandlePendingJoin failed for guids %s %s due to offline player", playerString.c_str(), leaderString.c_str());
            return;
        }

        Group* grp = leader->GetGroup();

        Group* group = player->GetGroup();
        if (group && group != grp)
            group->RemoveMember(player->GetObjectGuid(), 0);

        bool created = false;
        if (!grp)
        {
            grp = new Group();
            if (!grp->Create(leaderGuid, leader->GetName()))
            {
                delete grp;
                grp = nullptr;
                world->GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid](LFGQueue* queue)
                {
                    queue->RemovePendingJoin(leaderGuid, playerGuid);
                });
                return;
            }

            created = true;
            ObjectGuid gguid = grp->GetObjectGuid();
            sObjectMgr.AddGroup(grp);
            bool result = grp->AddMember(player->GetObjectGuid(), player->GetName());
            MANGOS_ASSERT(result); // should never fail - group was empty
        }
        else if (group != grp)
        {
            if (!grp->AddMember(player->GetObjectGuid(), player->GetName()))
            {
                world->GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid](LFGQueue* queue)
                {
                    queue->RemovePendingJoin(leaderGuid, playerGuid);
                });
                return;
            }
        }

        WorldPacket data;

        if (created)
        {
            GroupMakeMeetingStoneQueueMatchedFor(data, entry, true);
            leader->GetSession()->SendPacket(data);
        }

        GroupMakeMeetingStoneMemberAdded(data, player->GetObjectGuid());
        grp->BroadcastPacket(data, true, -1, player->GetObjectGuid());

        GroupMakeMeetingStoneQueueMatchedFor(data, entry);
        player->GetSession()->SendPacket(data);

        if (grp->IsFull())
        {
            // completely clear from lfg
            world->GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid](LFGQueue* queue)
            {
                queue->PendingJoinSuccess(leaderGuid, playerGuid, true);
            });
        }
        else
        {
            // only clear pending transfer and merge infos
            world->GetLFGQueue().GetMessager().AddMessage([leaderGuid, playerGuid](LFGQueue* queue)
            {
                queue->PendingJoinSuccess(leaderGuid, playerGuid, false);
            });
        }
    });
}

void LFGQueue::RemovePendingJoin(ObjectGuid leaderGuid, ObjectGuid playerGuid)
{
    auto leaderItr = m_queuedPlayers.find(leaderGuid);
    if (leaderItr != m_queuedPlayers.end())
    {
        leaderItr->second.pendingMembers.erase(std::remove(leaderItr->second.pendingMembers.begin(), leaderItr->second.pendingMembers.end(), playerGuid), leaderItr->second.pendingMembers.end());
    }
    auto playerItr = m_queuedPlayers.find(playerGuid);
    if (playerItr != m_queuedPlayers.end())
    {
        playerItr->second.pendingTransfer = false;
    }
}

void LFGQueue::PendingJoinSuccess(ObjectGuid leaderGuid, ObjectGuid playerGuid, bool full)
{
    auto leaderItr = m_queuedPlayers.find(leaderGuid);
    auto playerItr = m_queuedPlayers.find(playerGuid);
    bool erasedPlayer = false;
    if (leaderItr != m_queuedPlayers.end())
    {
        leaderItr->second.pendingMembers.erase(std::remove(leaderItr->second.pendingMembers.begin(), leaderItr->second.pendingMembers.end(), playerGuid), leaderItr->second.pendingMembers.end());
        if (playerItr != m_queuedPlayers.end())
        {
            leaderItr->second.members.emplace_back(playerGuid, playerItr->second.level);
            m_queuedPlayers.erase(playerItr);
            erasedPlayer = true;
        }
    }
    else if (playerItr != m_queuedPlayers.end()) // async nature
    {
        playerItr->second.pendingTransfer = false;
    }

    if (full && leaderItr != m_queuedPlayers.end())
        m_queuedPlayers.erase(leaderItr);

    GroupUpdate(leaderGuid, playerGuid, full);

    if (erasedPlayer)
    {
        sWorld.GetMessager().AddMessage([playerGuid](World* /*world*/)
        {
            if (Player* player = sObjectMgr.GetPlayer(playerGuid))
                player->GetSession()->m_lfgInfo.queued = false;
        });
    }
}

void LFGQueue::SendLFGUpdate(ObjectGuid leaderGuid, ObjectGuid playerGuid) const
{
    auto itr = m_queuedPlayers.find(leaderGuid);
    bool queued = true;
    bool lfm = false;
    bool lfg = false;
    uint32 data = 0;
    if (itr == m_queuedPlayers.end())
        queued = false;
    else
    {
        auto& info = itr->second;
        lfm = info.isLFM();
        lfg = info.isLFG();
        data = uint32(info.more.entry | (info.more.type << 24));
    }

    WorldPacket response(SMSG_LFG_UPDATE);
    response << uint8(queued);
    response << uint8(lfg);
    response << uint8(lfm);
    if (lfm)
        response << data;

    sWorld.GetMessager().AddMessage([playerGuid, response](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->SendPacket(response);
    });
}

void LFGQueue::SendLFGUpdateLFG(ObjectGuid playerGuid) const
{
    auto itr = m_queuedPlayers.find(playerGuid);
    uint32 data[3];
    memset(data, 0, sizeof(data));
    if (itr != m_queuedPlayers.end())
        for (uint8 i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
            data[i] = uint32(itr->second.group[i].entry | (itr->second.group[i].type << 24));

    WorldPacket response(SMSG_LFG_UPDATE_LFG, (4 * MAX_LOOKING_FOR_GROUP_SLOT));
    for (uint8 i = 0; i < MAX_LOOKING_FOR_GROUP_SLOT; ++i)
        response << data[i];

    sWorld.GetMessager().AddMessage([playerGuid, response](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->SendPacket(response);
    });
}

void LFGQueue::SendLFGUpdateLFM(ObjectGuid playerGuid) const
{
    auto itr = m_queuedPlayers.find(playerGuid);
    bool lfm = false;
    uint32 data = 0;
    if (itr != m_queuedPlayers.end())
    {
        auto const& info = itr->second;
        lfm = info.isLFM();
        data = uint32(info.more.entry | (info.more.type << 24));
    }

    WorldPacket response(SMSG_LFG_UPDATE_LFM);
    response << uint8(lfm);
    if (lfm)
        response << data;

    sWorld.GetMessager().AddMessage([playerGuid, response](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->SendPacket(response);
    });
}

void LFGQueue::SendLFGListQueryResponse(ObjectGuid playerGuid, Team playerTeam, LfgType type, uint32 entry) const
{
    WorldPacket response(MSG_LOOKING_FOR_GROUP);
    response << uint32(type);                                   // type
    response << uint32(entry);                                  // entry from LFGDungeons.dbc
    response << uint32(0);                                      // displayed players count, placeholder
    response << uint32(0);                                      // found players count, placeholder

    uint32 displayed = 0;
    uint32 found = 0;

    for (const auto& data : m_queuedPlayers)
    {
        auto const& info = data.second;
        if (info.team != playerTeam)
            continue;

        if (!info.isLeader || info.full)
            continue;

        ++found;

        // Client hardcoded limitation on amount of players sent in the packet handler and UI:
        if (found > 50)
            continue;

        ++displayed;

        const bool isLFM = info.isLFM(entry, type);

        response << data.first.WriteAsPacked();                 // packed guid
        response << uint32(info.level);                         // level
        response << uint32(info.zoneId);                        // current zone
        response << uint8(isLFM);                               // 0x00 - LFG, 0x01 - LFM

        if (isLFM)
        {
            response << uint32(info.more.entry | (info.more.type << 24));
            response << uint32(0x1000000);
            response << uint32(0x1000000);
        }
        else
        {
            for (uint8 j = 0; j < MAX_LOOKING_FOR_GROUP_SLOT; ++j)
                response << uint32(info.group[j].entry | (info.group[j].type << 24));
        }

        response << info.comment;

        response << uint32(0);                                  // other group members count, placeholder

        if (!info.members.empty())
        {
            const size_t offset = (response.wpos() - 4);        // other group members count, offset
            uint32 count = 0;                               // other group members count

            for (auto& member : info.members)
            {
                if (member.partyMember != data.first)
                {
                    response << member.partyMember.WriteAsPacked(); // packed guid
                    response << uint32(member.level); // player level
                    ++count;
                }
            }

            response.put<uint32>(offset, count);            // other group members count, fill the placeholder
        }
    }

    // fill count placeholders
    response.put<uint32>(4 + 4, displayed);
    response.put<uint32>(4 + 4 + 4, found);

    sWorld.GetMessager().AddMessage([playerGuid, response](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(playerGuid))
            player->GetSession()->SendPacket(response);
    });
}

void LFGQueue::GroupUpdate(ObjectGuid playerGuid, ObjectGuid leaderGuid, bool completed)
{
    GroupUpdateQueueStatus(playerGuid, leaderGuid);
    GroupUpdateUI(leaderGuid, completed);
}

bool LFGQueue::GroupUpdateQueueStatus(ObjectGuid /*playerGuid*/, ObjectGuid leaderGuid)
{
    bool lfm = false;
    std::vector<ObjectGuid> members;
    auto itr = m_queuedPlayers.find(leaderGuid);
    if (itr == m_queuedPlayers.end())
        return false;
    auto& info = itr->second;
    lfm = info.isLFM();
    for (auto& member : info.members)
        members.push_back(member.partyMember);

    const bool autojoin = info.isAutoJoin();
    const bool autofill = info.isAutoFill();

    const bool status = ((autojoin && info.members.empty()) || (autofill && !info.members.empty()));

    if (info.status == status)
        return false;

    info.status = status;

    // Sync client's UI queue status
    const bool queued = itr != m_queuedPlayers.end();


    WorldPacket data(SMSG_LFG_UPDATE_QUEUED, 1);
    data << uint8(queued);

    WorldPacket message;
    if (queued)
        GroupMakeMeetingStoneQueueJoinedFor(message, info.more.entry);
    else
        GroupMakeMeetingStoneQueueLeftFor(message, info.more.entry);

    sWorld.GetMessager().AddMessage([leaderGuid, data, message, lfm, members](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(leaderGuid))
        {
            player->GetSession()->SendPacket(data);
            if (lfm)
                player->GetSession()->SendPacket(message);
        }

        for (auto& memberGuid : members) // TODO: Ignore players in bg here?
        {
            if (Player* member = sObjectMgr.GetPlayer(memberGuid))
            {
                member->GetSession()->SendPacket(data);

                if (lfm)
                    member->GetSession()->SendPacket(message);
            }
        }
    });
    return true;
}

void LFGQueue::GroupUpdateUI(ObjectGuid leaderGuid, bool completed)
{
    std::vector<ObjectGuid> members;
    
    auto itr = m_queuedPlayers.find(leaderGuid);
    if (itr != m_queuedPlayers.end())
    {
        auto& info = itr->second;

        for (auto& member : info.members)
            members.push_back(member.partyMember);
    }

    sWorld.GetMessager().AddMessage([leaderGuid, completed, members](World* /*world*/)
    {
        if (Player* player = sObjectMgr.GetPlayer(leaderGuid))
        {
            if (completed)
            {
                player->GetSession()->SendMeetingStoneComplete();
                if (sWorld.getConfig(CONFIG_BOOL_CHANNEL_RESTRICTED_LFG) && player->GetSession()->GetSecurity() == SEC_PLAYER)
                    player->LeaveLFGChannel();
            }
            else
                player->GetSession()->SendLFGUpdate();
        }

        for (auto& memberGuid : members)
        {
            if (Player* member = sObjectMgr.GetPlayer(memberGuid))
            {
                if (completed)
                {
                    member->GetSession()->SendMeetingStoneComplete();
                    if (sWorld.getConfig(CONFIG_BOOL_CHANNEL_RESTRICTED_LFG) && member->GetSession()->GetSecurity() == SEC_PLAYER)
                        member->LeaveLFGChannel();
                }
                else
                    member->GetSession()->SendLFGUpdate();
            }
        }
    });
}

void LFGQueue::GroupMakeMeetingStoneQueueJoinedFor(WorldPacket& message, uint16 entry)
{
    message.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    message << uint32(entry);
    message << uint8(MeetingstoneSetqueue::IN_QUEUE);
}

void LFGQueue::GroupMakeMeetingStoneQueueLeftFor(WorldPacket& message, uint16 entry)
{
    message.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    message << uint32(entry);
    message << uint8(MeetingstoneSetqueue::LEFT_QUEUE);
}

void LFGQueue::GroupMakeMeetingStoneQueueMatchedFor(WorldPacket& message, uint32 entry, bool asLeader)
{
    message.Initialize(SMSG_MEETINGSTONE_SETQUEUE);
    message << uint32(entry);
    message << uint8(MeetingstoneSetqueue::JOINED_GROUP);
    message << uint8(asLeader);
}

void LFGQueue::GroupMakeMeetingStoneMemberAdded(WorldPacket& data, ObjectGuid guid)
{
    data.Initialize(SMSG_MEETINGSTONE_MEMBER_ADDED, 8);
    data << guid;
}

void LFGQueue::PendingInvite(WorldPacket& data, uint32 entry)
{
    data.Initialize(SMSG_LFG_PENDING_INVITE, 4);
    data << uint32(entry);
}

void LFGQueue::PendingMatch(WorldPacket& data, uint32 entry)
{
    data.Initialize(SMSG_LFG_PENDING_MATCH, 4);
    data << uint32(entry);
}

void LFGQueue::PendingMatchDone(WorldPacket& data)
{
    // UNK usage
    data.Initialize(SMSG_LFG_PENDING_INVITE);
}

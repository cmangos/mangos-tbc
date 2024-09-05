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

#ifndef _LFG_QUEUE_H
#define _LFG_QUEUE_H

#include "LFG/LFGDefines.h"

struct LFGGroupQueueInfo
{
    ObjectGuid partyMember;
    uint32 level;

    LFGGroupQueueInfo(ObjectGuid partyMember, uint32 level) : partyMember(partyMember), level(level) {}
};

struct LFGPlayerQueueInfo
{
    struct Slot
    {
        bool empty() const { return (!type || !entry); }
        void clear() { entry = 0; }
        bool set(uint16 _entry, uint16 _type) { entry = _entry; type = _type; return !empty(); }
        bool is(uint16 _entry, uint16 _type) const { return entry == _entry && type == _type; }
        bool isAuto() const { return entry && (type == LFG_TYPE_DUNGEON || type == LFG_TYPE_HEROIC_DUNGEON); }

        uint16 entry = 0;
        uint16 type = LFG_TYPE_DUNGEON;
    };

    inline void clear()
    {
        more.clear();
        for (auto& slot : group)
            slot.clear();
    }
    inline bool isAutoFill() const { return more.isAuto(); }
    inline bool isAutoJoin() const
    {
        for (auto& slot : group)
            if (slot.isAuto())
                return true;
        return false;
    }
    inline bool isEmpty() const { return (!isLFM() && !isLFG()); }
    inline bool isLFG() const
    {
        for (auto& slot : group)
            if (!slot.empty())
                return true;
        return false;
    }
    inline bool isLFG(uint32 entry, uint32 type, bool autoOnly) const
    {
        for (auto& slot : group)
            if (slot.is(uint16(entry), uint16(type)) && (!autoOnly || slot.isAuto()))
                return true;
        return false;
    }
    inline bool isLFG(LFGPlayerQueueInfo const& info, bool autoOnly) const { return isLFG(uint16(info.more.entry), uint16(info.more.type), autoOnly); }
    inline bool isLFM() const { return !more.empty(); }
    inline bool isLFM(uint32 entry, uint32 type) const { return more.is(uint16(entry), uint16(type)); }

    // bool queued = false;
    Slot group[MAX_LOOKING_FOR_GROUP_SLOT];
    Slot more;
    std::string comment;
    Team team = TEAM_NONE;
    bool isLeader = true;
    bool full = false;
    uint32 level = 0;
    uint32 zoneId = 0;
    bool status = false;
    ObjectGuid leaderGuid;

    bool autoFill = false;
    bool autoJoin = false;

    bool pendingTransfer = false;
    ObjectGuid pendingLeaderGuid;
    uint32 pendingEntry = 0;

    std::vector<LFGGroupQueueInfo> members;
    std::vector<ObjectGuid> pendingMembers;
};

class LFGQueue
{
    public:
        void Update();

        void SetComment(ObjectGuid playerGuid, std::string const& comment);
        void SetAutoFill(ObjectGuid playerGuid, bool state);
        void SetAutoJoin(ObjectGuid playerGuid, bool state);

        void StartLookingForMore(ObjectGuid playerGuid, LFGPlayerQueueInfo info);
        void StopLookingForMore(ObjectGuid playerGuid);

        void StartLookingForGroup(LFGPlayerQueueInfo info, ObjectGuid invokerPlayer);
        void StopLookingForGroup(ObjectGuid leaderGuid, ObjectGuid playerGuid);
        void SetLfgSlot(ObjectGuid leaderGuid, uint32 slot, uint16 entry, uint16 type);
        void SetLfmData(ObjectGuid leaderGuid, uint16 entry, uint16 type);

        void TryJoin(ObjectGuid playerGuid, bool initial);
        void TryFill(ObjectGuid leaderGuid, bool initial);

        bool AddMember(LFGPlayerQueueInfo& info, LFGPlayerQueueInfo& playerInfo, uint32 entry);

        void HandlePendingJoin(ObjectGuid playerGuid, bool accept);
        void RemovePendingJoin(ObjectGuid leaderGuid, ObjectGuid playerGuid);
        void PendingJoinSuccess(ObjectGuid leaderGuid, ObjectGuid playerGuid, bool full);

        void SendLFGUpdate(ObjectGuid leaderGuid, ObjectGuid playerGuid) const;
        void SendLFGUpdateLFG(ObjectGuid playerGuid) const;
        void SendLFGUpdateLFM(ObjectGuid playerGuid) const;
        void SendLFGListQueryResponse(ObjectGuid playerGuid, Team playerTeam, LfgType type, uint32 entry) const;

        void GroupUpdate(ObjectGuid playerGuid, ObjectGuid leaderGuid, bool completed = false);
        bool GroupUpdateQueueStatus(ObjectGuid playerGuid, ObjectGuid leaderGuid);
        void GroupUpdateUI(ObjectGuid leaderGuid, bool completed = false);
        static void GroupMakeMeetingStoneQueueJoinedFor(WorldPacket& message, uint16 entry);
        static void GroupMakeMeetingStoneQueueLeftFor(WorldPacket& message, uint16 entry);
        static void GroupMakeMeetingStoneQueueMatchedFor(WorldPacket& message, uint32 entry, bool asLeader = false);
        static void GroupMakeMeetingStoneMemberAdded(WorldPacket& data, ObjectGuid guid);
        static void PendingInvite(WorldPacket& data, uint32 entry);
        static void PendingMatch(WorldPacket& data, uint32 entry);
        static void PendingMatchDone(WorldPacket& data);

        Messager<LFGQueue>& GetMessager() { return m_messager; }

    private:
        typedef std::map<ObjectGuid, LFGPlayerQueueInfo> QueuedPlayersMap;
        QueuedPlayersMap m_queuedPlayers;

        Messager<LFGQueue> m_messager;
};

#endif
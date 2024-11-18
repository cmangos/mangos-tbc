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

#ifndef _LFG_DEFINES_H
#define _LFG_DEFINES_H

#include "Common.h"

#define MAX_LOOKING_FOR_GROUP_SLOT 3

enum LfgType : uint32
{
    LFG_TYPE_NONE           = 0,
    LFG_TYPE_DUNGEON        = 1,
    LFG_TYPE_RAID           = 2,
    LFG_TYPE_QUEST          = 3,
    LFG_TYPE_ZONE           = 4,
    LFG_TYPE_HEROIC_DUNGEON = 5
};

enum class MeetingstoneFailedStatus : uint8
{
    MEETINGSTONE_FAIL_NONE                                  = 0, // custom, not to be sent
    MEETINGSTONE_FAIL_PARTYLEADER                           = 1,
    MEETINGSTONE_FAIL_FULL_GROUP                            = 2,
    MEETINGSTONE_FAIL_RAID_GROUP                            = 3,
};

enum class MeetingstoneSetqueue : uint8
{
    LEFT_QUEUE          = 0,
    IN_QUEUE            = 1,
    UNK                 = 2,
    OTHER_MEMBER_LEFT   = 3,
    KICKED_FROM_QUEUE   = 4,
    JOINED_GROUP        = 5,
};

struct LfgPlayerInfo
{
    std::string comment;
    bool autojoin = false;
    bool autofill = false;
    bool queued = false; // cached async information
};

#endif
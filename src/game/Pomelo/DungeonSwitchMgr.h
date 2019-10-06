/**
 *
 * @File : DungeonSwitchMgr.h
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#ifndef MANGOS_DUNGEON_SWITCH_MGR_H
#define MANGOS_DUNGEON_SWITCH_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include <string>

class DungeonSwitchMgr
{
    public:
        void LoadFromDB();
        bool IsLocked(uint32 mapId);
        bool IsSupportTenPlayersDifficulty(uint32 mapId);
};

#define sDungeonSwitchMgr MaNGOS::Singleton<DungeonSwitchMgr>::Instance()

#endif
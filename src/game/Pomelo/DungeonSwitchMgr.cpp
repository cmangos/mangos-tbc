/**
 *
 * @File : DungeonSwitchMgr.cpp
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#include "DungeonSwitchMgr.h"

std::unordered_set<uint32> map;

void DungeonSwitchMgr::LoadFromDB()
{
    map.clear();
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry` "
        "FROM `pomelo_dungeon_switch` "
        "WHERE `disabled` = TRUE;");

    if (result)
	{
		do
		{
			Field* field = result->Fetch(); 
            map.insert(field[0].GetUInt32());
		} while (result->NextRow());
	}
}

bool DungeonSwitchMgr::IsLocked(uint32 mapId)
{
    return map.find(mapId) != map.end();
}
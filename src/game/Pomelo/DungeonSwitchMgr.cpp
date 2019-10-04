/**
 *
 * @File : DungeonSwitchMgr.cpp
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#include "DungeonSwitchMgr.h"

std::unordered_set<uint32> m_dungeonSwitch;

void DungeonSwitchMgr::LoadFromDB()
{
    m_dungeonSwitch.clear();
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry` "
        "FROM `pomelo_dungeon_switch` "
        "WHERE `disabled` = TRUE;");

    if (result)
	{
		do
		{
			Field* field = result->Fetch(); 
            m_dungeonSwitch.insert(field[0].GetUInt32());
		} while (result->NextRow());
	}
}

bool DungeonSwitchMgr::IsLocked(uint32 mapId)
{
    return m_dungeonSwitch.find(mapId) != m_dungeonSwitch.end();
}
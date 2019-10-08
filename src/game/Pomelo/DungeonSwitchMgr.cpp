/**
 *
 * @File : DungeonSwitchMgr.cpp
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#include "DungeonSwitchMgr.h"

std::unordered_set<uint32> m_dungeonSwitch;
std::unordered_set<uint32> m_tenPlayersSwitch;

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
    delete result;

    m_tenPlayersSwitch.clear();
    QueryResult* result2 = WorldDatabase.PQuery(
        "SELECT `entry` "
        "FROM `pomelo_dungeon_switch` "
        "WHERE `ten_players_enabled` = TRUE;");
    if (result2)
    {
        do
        {
            Field* field = result2->Fetch();
            m_tenPlayersSwitch.insert(field[0].GetUInt32());
        } while (result2->NextRow());
    }
    delete result2;
}

bool DungeonSwitchMgr::IsLocked(uint32 mapId)
{
    return m_dungeonSwitch.find(mapId) != m_dungeonSwitch.end();
}

bool DungeonSwitchMgr::IsSupportTenPlayersDifficulty(uint32 mapId)
{
    return m_tenPlayersSwitch.find(mapId) != m_tenPlayersSwitch.end();
}
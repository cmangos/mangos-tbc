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
std::unordered_map<uint32, float> m_heroicHp;
std::unordered_map<uint32, float> m_normalHp;
std::unordered_map<uint32, float> m_heroicDamage;
std::unordered_map<uint32, float> m_normalDamage;

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

    m_heroicHp.clear();
    QueryResult* result3 = WorldDatabase.PQuery(
        "SELECT `entry`, `heroic_hp` "
        "FROM `pomelo_dungeon_switch`;");
    if (result3)
    {
        do
        {
            Field* field = result3->Fetch();
            m_heroicHp[field[0].GetUInt32()] = field[1].GetFloat();
        } while (result3->NextRow());
    }
    delete result3;

    m_heroicDamage.clear();
    QueryResult* result4 = WorldDatabase.PQuery(
        "SELECT `entry`, `heroic_damage` "
        "FROM `pomelo_dungeon_switch`;");
    if (result4)
    {
        do
        {
            Field* field = result4->Fetch();
            m_heroicDamage[field[0].GetUInt32()] = field[1].GetFloat();
        } while (result4->NextRow());
    }
    delete result4;


    m_normalHp.clear();
    QueryResult* result5 = WorldDatabase.PQuery(
        "SELECT `entry`, `normal_hp` "
        "FROM `pomelo_dungeon_switch`;");
    if (result5)
    {
        do
        {
            Field* field = result5->Fetch();
            m_normalHp[field[0].GetUInt32()] = field[1].GetFloat();
        } while (result5->NextRow());
    }
    delete result5;

    m_normalDamage.clear();
    QueryResult* result6 = WorldDatabase.PQuery(
        "SELECT `entry`, `normal_damage` "
        "FROM `pomelo_dungeon_switch`;");
    if (result6)
    {
        do
        {
            Field* field = result6->Fetch();
            m_normalDamage[field[0].GetUInt32()] = field[1].GetFloat();
        } while (result6->NextRow());
    }
    delete result6;
}

bool DungeonSwitchMgr::IsLocked(uint32 mapId)
{
    return m_dungeonSwitch.find(mapId) != m_dungeonSwitch.end();
}

bool DungeonSwitchMgr::IsSupportTenPlayersDifficulty(uint32 mapId)
{
    return m_tenPlayersSwitch.find(mapId) != m_tenPlayersSwitch.end();
}

float DungeonSwitchMgr::GetDamageRate(uint32 mapId, Difficulty difficulty)
{
    if (m_heroicDamage.find(mapId) == m_heroicDamage.end())
        return 1.f;
    return m_heroicDamage[mapId];
}

float DungeonSwitchMgr::GetHpRate(uint32 mapId, Difficulty difficulty)
{
    if (m_heroicHp.find(mapId) == m_heroicHp.end())
        return 1.f;
    return m_heroicHp[mapId];
}
/**
 *
 * @File : DBConfigMgr.cpp
 * @Authors : yukozh
 * @Date : 09/20/2019
 *
 **/

#include "DBConfigMgr.h"
#include <unordered_map>
#include <iostream>
#include <sstream>

std::unordered_map<std::string, std::string> m_dbConfig;

template <class Type> 
Type StringToType(const std::string& str){ 
    std::istringstream iss(str); 
    Type num; 
    iss >> num; 
    return num;     
} 

void DBConfigMgr::LoadFromDB()
{
    m_dbConfig.clear();
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry`, `value` "
        "FROM `pomelo_config`;");

    if (result)
	{
		do
		{
			Field* field = result->Fetch();
            m_dbConfig[field[0].GetCppString()] = field[1].GetCppString();
		} while (result->NextRow());
	}
}

uint32 DBConfigMgr::GetUInt32(std::string entry)
{
    return StringToType<uint32>(m_dbConfig[entry]);
}

uint64 DBConfigMgr::GetUInt64(std::string entry)
{
    return StringToType<uint64>(m_dbConfig[entry]);
}

float DBConfigMgr::GetFloat(std::string entry)
{
    return StringToType<float>(m_dbConfig[entry]);
}

std::string DBConfigMgr::GetString(std::string entry)
{
    return m_dbConfig[entry];
}
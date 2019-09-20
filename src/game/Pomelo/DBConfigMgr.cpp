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

std::unordered_map<std::string, std::string> map;

template <class Type> 
Type StringToType(const std::string& str){ 
    std::istringstream iss(str); 
    Type num; 
    iss >> num; 
    return num;     
} 

void DBConfigMgr::LoadFromDB()
{
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry`, `value` "
        "FROM `pomelo_config`;");

    if (result)
	{
		do
		{
			Field* field = result->Fetch();
            map[field[0].GetCppString()] = field[1].GetCppString();
		} while (result->NextRow());
	}
}

uint32 DBConfigMgr::GetUInt32(std::string entry)
{
    return StringToType<uint32>(map[entry]);
}

uint64 DBConfigMgr::GetUInt64(std::string entry)
{
    return StringToType<uint64>(map[entry]);
}

float DBConfigMgr::GetFloat(std::string entry)
{
    return StringToType<float>(map[entry]);
}

std::string DBConfigMgr::GetString(std::string entry)
{
    return map[entry];
}
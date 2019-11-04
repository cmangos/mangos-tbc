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

template <class Type> 
Type StringToType(const std::string& str){ 
    std::istringstream iss(str); 
    Type num; 
    iss >> num; 
    return num;     
} 

void DBConfigMgr::LoadFromDB()
{
    m_configUInt32.clear();
    m_configUInt64.clear();
    m_configString.clear();
    m_configFloat.clear();
    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry`, `value`, `type` "
        "FROM `pomelo_config`;");

    if (result)
	{
		do
		{
			Field* field = result->Fetch();
            uint8 type = field[2].GetUInt8();
            switch (DBConfigType(type))
            {
            case DBCONF_TYPE_UINT32:
                m_configUInt32[field[0].GetCppString()] = StringToType<uint32>(field[1].GetCppString());
                break;
            case DBCONF_TYPE_UINT64:
                m_configUInt64[field[0].GetCppString()] = StringToType<uint64>(field[1].GetCppString());
                break;
            case DBCONF_TYPE_STRING:
                m_configString[field[0].GetCppString()] = field[1].GetCppString();
                break;
            case DBCONF_TYPE_FLOAT:
                m_configFloat[field[0].GetCppString()] = StringToType<float>(field[1].GetCppString());
                break;
            default:
                break;
            }
		} while (result->NextRow());
	}
}

uint32 DBConfigMgr::GetUInt32(std::string entry)
{
    return m_configUInt32[entry];
}

uint64 DBConfigMgr::GetUInt64(std::string entry)
{
    return m_configUInt64[entry];
}

float DBConfigMgr::GetFloat(std::string entry)
{
    return m_configFloat[entry];
}

std::string DBConfigMgr::GetString(std::string entry)
{
    return m_configString[entry];
}
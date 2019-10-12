/**
 *
 * @File : DBConfigMgr.h
 * @Authors : yukozh
 * @Date : 09/20/2019
 *
 **/

#ifndef MANGOS_DB_CONFIG_MGR_H
#define MANGOS_DB_CONFIG_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include <string>

enum DBConfigType
{
    DBCONF_TYPE_UINT32,
    DBCONF_TYPE_UINT64,
    DBCONF_TYPE_STRING,
    DBCONF_TYPE_FLOAT
};

class DBConfigMgr
{
public:
    void LoadFromDB();
    uint32 GetUInt32(std::string entry);
    uint64 GetUInt64(std::string entry);
    std::string GetString(std::string entry);
    float GetFloat(std::string entry);
private:
    std::unordered_map<std::string, uint32> m_configUInt32;
    std::unordered_map<std::string, uint64> m_configUInt64;
    std::unordered_map<std::string, std::string> m_configString;
    std::unordered_map<std::string, float> m_configFloat;
};

#define sDBConfigMgr MaNGOS::Singleton<DBConfigMgr>::Instance()

#endif
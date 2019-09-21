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

class DBConfigMgr
{
public:
    void LoadFromDB();
    uint32 GetUInt32(std::string entry);
    uint64 GetUInt64(std::string entry);
    std::string GetString(std::string entry);
    float GetFloat(std::string entry);
};

#define sDBConfigMgr MaNGOS::Singleton<DBConfigMgr>::Instance()

#endif
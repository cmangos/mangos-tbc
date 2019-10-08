/**
 *
 * @File : DBConfigMgr.h
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#ifndef MANGOS_ANNOUNCE_MGR_H
#define MANGOS_ANNOUNCE_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include <string>

class AnnounceMgr
{
public:
    void LoadFromDB();
    std::string NextAnnouncement();
};

#define sAnnounceMgr MaNGOS::Singleton<AnnounceMgr>::Instance()

#endif
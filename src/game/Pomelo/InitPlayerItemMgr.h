/**
 *
 * @File : InitPlayerItemMgr.h
 * @Authors : yukozh
 * @Date : 09/24/2019
 *
 **/

#ifndef MANGOS_INIT_PLAYER_ITEM_MGR_H
#define MANGOS_INIT_PLAYER_ITEM_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"

struct InitPlayerItem
{
    uint32 id;
    uint32 amount;
};

class InitPlayerItemMgr
{
public:
    void LoadFromDB();
    std::vector<InitPlayerItem> ListItems();
};

#define sInitPlayerItemMgr MaNGOS::Singleton<InitPlayerItemMgr>::Instance()

#endif
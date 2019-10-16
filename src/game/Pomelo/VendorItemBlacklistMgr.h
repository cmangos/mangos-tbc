/**
 *
 * @File : VendorItemBlacklistMgr.h
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include "Entities/Player.h"

#ifndef MANGOS_VENDOR_ITEM_BLACKLIST_MGR_H
#define MANGOS_VENDOR_ITEM_BLACKLIST_MGR_H

class VendorItemBlacklistMgr
{
public:
    void LoadFromDB();
    bool IsInBlacklist(uint32 item);
};

#define sVendorItemBlacklistMgr MaNGOS::Singleton<VendorItemBlacklistMgr>::Instance()

#endif
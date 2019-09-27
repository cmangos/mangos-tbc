/**
 *
 * @File : PetLoyaltyMgr.h
 * @Authors : yukozh
 * @Date : 09/27/2019
 *
 **/

#ifndef MANGOS_PET_LOYALTY_MGR_H
#define MANGOS_PET_LOYALTY_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"

class PetLoyaltyMgr
{
public:
    void LoadFromDB();
    const uint32* GetLevelUp();
    const uint32* GetLevelStart();
};

#define sPetLoyaltyMgr MaNGOS::Singleton<PetLoyaltyMgr>::Instance()

#endif
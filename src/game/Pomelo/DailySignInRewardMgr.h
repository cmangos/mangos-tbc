/**
 *
 * @File : DailySignInReward.h
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#ifndef MANGOS_DAILY_SIGN_IN_REWARD_MGR_H
#define MANGOS_DAILY_SIGN_IN_REWARD_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"

class DailySignInRewardMgr
{
    public:
        bool ClaimReward(Player* pPlayer);
};

#define sDailySignInRewardMgr MaNGOS::Singleton<DailySignInRewardMgr>::Instance()

#endif
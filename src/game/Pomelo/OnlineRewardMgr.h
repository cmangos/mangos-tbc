/**
 *
 * @File : OnlineRewardMgr.h
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#ifndef MANGOS_ONLINE_REWARD_MGR_H
#define MANGOS_ONLINE_REWARD_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include <string>

enum RewardType
{
    REWARD_TYPE_MONEY,
    REWARD_TYPE_CUSTOM_CURRENCY,
    REWARD_TYPE_ITEM,
    REWARD_TYPE_XP
};

struct RewardItem
{
    uint32      entry;
    RewardType  type;
    uint32      index;
    uint32      amount;
    uint32      interval;
};

class OnlineRewardMgr
{
public:
    void LoadFromDB();
    const std::vector<RewardItem> GetRewardItems();
};

#define sOnlineRewardMgr MaNGOS::Singleton<OnlineRewardMgr>::Instance()

#endif
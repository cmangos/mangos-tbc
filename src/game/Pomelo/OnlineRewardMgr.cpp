/**
 *
 * @File : OnlineRewardMgr.cpp
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#include "OnlineRewardMgr.h"

std::vector<RewardItem> m_rewardItems;

void OnlineRewardMgr::LoadFromDB()
{
    m_rewardItems.clear();

    QueryResult* result = WorldDatabase.PQuery(
        "SELECT `entry`, `type`, `amount`, `index`, `interval` "
        "FROM `pomelo_online_reward`; ");

    if (result)
	{
		do
		{
			Field* field = result->Fetch(); 
            RewardItem item;
            item.entry = field[0].GetUInt32();
            item.type = (RewardType)field[1].GetUInt32();
            item.amount = field[2].GetUInt32();
            item.index = field[3].GetUInt32();
            item.interval = field[4].GetUInt32();
            m_rewardItems.push_back(item);
		} while (result->NextRow());
	}

    delete result;
}

const std::vector<RewardItem> OnlineRewardMgr::GetRewardItems()
{
    return m_rewardItems;
}
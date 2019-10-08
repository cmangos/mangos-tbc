/**
 *
 * @File : InitPlayerItemMgr.cpp
 * @Authors : yukozh
 * @Date : 09/24/2019
 *
 **/

#include "InitPlayerItemMgr.h"

std::vector<InitPlayerItem> items;

void InitPlayerItemMgr::LoadFromDB()
{
    items.clear();
    QueryResult* result = WorldDatabase.PQuery(
    "SELECT `itemid`, `amount` "
    "FROM `playercreateinfo_item` "
    "WHERE `race` = 0 AND `class` = 0; ");

    if (result)
	{
		do
		{
			Field* field = result->Fetch();
            InitPlayerItem item;
            item.id = field[0].GetUInt32();
            item.amount = field[1].GetUInt32();
            items.push_back(item);
		} while (result->NextRow());
	}

    delete result;
}

std::vector<InitPlayerItem> InitPlayerItemMgr::ListItems()
{
    return items;
}
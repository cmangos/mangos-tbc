/**
 *
 * @File : VendorItemBlacklistMgr.cpp
 * @Authors : yukozh
 * @Date : 10/04/2019
 *
 **/

#include "VendorItemBlacklistMgr.h"

std::unordered_set<uint32> blacklist;

void VendorItemBlacklistMgr::LoadFromDB()
{
    blacklist.clear();
    
    QueryResult* result = WorldDatabase.PQuery(
    "SELECT `entry` "
    "FROM `pomelo_vendor_item_ban`; ");
    
	if (result)
	{
		do
		{
			Field* field = result->Fetch();
            blacklist.insert(field[0].GetUInt32());
		} while (result->NextRow());
	}

    delete result;
}

bool VendorItemBlacklistMgr::IsInBlacklist(uint32 item)
{
    return blacklist.find(item) != blacklist.end();
}
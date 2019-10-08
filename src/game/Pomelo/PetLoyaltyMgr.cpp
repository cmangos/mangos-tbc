/**
 *
 * @File : PetLoyaltyMgr.h
 * @Authors : yukozh
 * @Date : 09/27/2019
 *
 **/

#include "PetLoyaltyMgr.h"

uint32 LevelUpLoyalty[6] =
{
    5500,
    11500,
    17000,
    23500,
    31000,
    39500,
};

uint32 LevelStartLoyalty[6] =
{
    2000,
    4500,
    7000,
    10000,
    13500,
    17500,
};

void PetLoyaltyMgr::LoadFromDB()
{
    QueryResult* result = WorldDatabase.PQuery(
    "SELECT `level_up`, `start` "
    "FROM `pomelo_pet_loyalty` "
    "ORDER BY `level` ASC;");
    
	if (result)
	{
        if (result->GetRowCount() != 6)
        {
            return;
        }
        size_t i = 0;
		do
		{
			Field* field = result->Fetch();
            LevelUpLoyalty[i] = field[0].GetUInt32();
            LevelStartLoyalty[i] = field[0].GetUInt32();
            ++i;
		} while (result->NextRow());
	}

    delete result;
}

const uint32* PetLoyaltyMgr:: GetLevelUp()
{
    return LevelUpLoyalty;
}

const uint32* PetLoyaltyMgr::GetLevelStart()
{
    return LevelStartLoyalty;
}
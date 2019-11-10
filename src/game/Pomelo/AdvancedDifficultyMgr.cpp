/**
 *
 * @File : AdvancedDifficultyMgr.cpp
 * @Authors : yukozh
 * @Date : 10/08/2019
 *
 **/

#include "AdvancedDifficultyMgr.h"

void AdvancedDifficultyMgr::LoadFromDB()
{
    m_banListTenPlrs.clear();

	QueryResult* result = WorldDatabase.PQuery(
	" SELECT `guid` "
	" FROM `pomelo_tenplayersban` ");

	if (result)
	{
		do
		{
			Field* field = result->Fetch();
            m_banListTenPlrs.insert(field[0].GetUInt32());
		} while (result->NextRow());
	}

    delete result;
}

bool AdvancedDifficultyMgr::IsGuidBannedInTenPlayersDiff(uint32 guid)
{
    return m_banListTenPlrs.find(guid) != m_banListTenPlrs.end();
}
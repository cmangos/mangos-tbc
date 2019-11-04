/**
 *
 * @File : MultiTalentMgr.cpp
 * @Authors : yukozh
 * @Date : 09/19/2019
 *
 **/

#include "MultiTalentMgr.h"
#include "Globals/ObjectMgr.h"

void MultiTalentMgr::AddLearnRecord(Player* pPlayer, uint32 talentId, uint32 talentRank)
{
	uint32 template_id = pPlayer->GetCurrentTalentTemplate();
	uint32 character_id = pPlayer->GetGUIDLow();
	CharacterDatabase.DirectPExecute(
		"INSERT INTO `pomelo_multi_talent` "
		"(`character_id`, `template`, `talent_id`, `talent_rank`) "
		"VALUES (%u, %u, %u, %u);", character_id, template_id, talentId, talentRank);
}

void MultiTalentMgr::ResetTemplate(Player* pPlayer)
{
	uint32 template_id = pPlayer->GetCurrentTalentTemplate();
	uint32 character_id = pPlayer->GetGUIDLow();
	CharacterDatabase.PExecute(
		"DELETE FROM `pomelo_multi_talent` "
		"WHERE `character_id` = %u AND `template` = %u;",
		character_id, template_id);
}

void MultiTalentMgr::IncreaseMaxTemplate(Player* pPlayer)
{
	++pPlayer->m_maxTalentTemplate;
}

void MultiTalentMgr::SwichTemplate(Player* pPlayer, uint32 templateId)
{
	if (templateId > pPlayer->GetMaxTalentTemplate())
		return;

	uint32 character_id = pPlayer->GetGUIDLow();
	QueryResult* result = CharacterDatabase.PQuery(
	"SELECT `character_id`, `template`, `talent_id`, `talent_rank` "
	"FROM `pomelo_multi_talent` "
	"WHERE `character_id` = %u AND `template` = %u",
	character_id, templateId);

	pPlayer->m_currentTalentTemplate = templateId;
	pPlayer->resetTalentsInternal(true, false);

	if (result)
	{
		do
		{
			Field* field = result->Fetch();
			uint32 id = field[2].GetUInt32();
			uint32 rank = field[3].GetUInt32();
			// Trust the talents records in DB, so learn in force mode to avoid querying for saving time.
			pPlayer->LearnTalentInternal(id, rank, true);
		} while (result->NextRow());
	}

    delete result;
}
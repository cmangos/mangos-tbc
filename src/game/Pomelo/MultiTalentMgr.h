/**
 *
 * @File : MultiTalentMgr.h
 * @Authors : yukozh
 * @Date : 09/19/2019
 *
 **/

#ifndef MANGOS_MULTI_TALENT_MGR_H
#define MANGOS_MULTI_TALENT_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"

class MultiTalentMgr
{
public:
	void AddLearnRecord(Player* pPlayer, uint32 talentId, uint32 talentRank);
	void ResetTemplate(Player* pPlayer);
	void IncreaseMaxTemplate(Player* pPlayer);
	void SwichTemplate(Player* pPlayer, uint32 templateId);
};

#define sMultiTalentMgr MaNGOS::Singleton<MultiTalentMgr>::Instance()

#endif
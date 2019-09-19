/**
 *
 * @File : item_transmogrification.cpp
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#include "item_multi_talent.h"
#include "Pomelo/MultiTalentMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"

void GenerateMultiTalentGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	for (uint32 i = 0; i <= pPlayer->GetMaxTalentTemplate(); ++i)
	{
		auto str = "Template #" + std::to_string(i + 1) + " ";
		if (i == pPlayer->GetCurrentTalentTemplate())
		{
			str.append("(Current)");
		}
		pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80006, i);
	}

	pPlayer->ADD_GOSSIP_ITEM(0, "Request turn on a new template", 80007, 0);

	pPlayer->SEND_GOSSIP_MENU(100000 - 1000, guid);
}

bool HandleMultiTalentGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender == 80006)
	{
		if (action > pPlayer->GetMaxTalentTemplate())
		{
			return false;
		}

		if (pPlayer->GetCurrentTalentTemplate() == action)
		{
			// TODO: Notify
			return true;
		}

		sMultiTalentMgr.SwichTemplate(pPlayer, action);
		// TODO: Notify

		return true;
	}
	else if (sender == 80007)
	{
		// TODO: Check limitation
		sMultiTalentMgr.IncreaseMaxTemplate(pPlayer);
		return true;
	}
	else
	{
		return false;
	}
}
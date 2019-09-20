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
		auto str = pPlayer->GetSession()->GetMangosString(LANG_MULTI_TALENT_TEMPLATE_NUM) + std::to_string(i + 1) + " ";
		if (i == pPlayer->GetCurrentTalentTemplate())
		{
			str.append(pPlayer->GetSession()->GetMangosString(LANG_MULTI_TALENT_TEMPLATE_CURRENT));
		}
		pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80006, i);
	}

	pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_MULTI_TALENT_CREATE), 80007, 0);

	pPlayer->SEND_GOSSIP_MENU(100000 - 1000, guid);
}

bool HandleMultiTalentGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender == 80006)
	{
		if (action > pPlayer->GetMaxTalentTemplate())
		{
            pPlayer->PlayerTalkClass->CloseGossip();
			return true;
		}

		if (pPlayer->GetCurrentTalentTemplate() == action)
		{
            pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_TEMPLATE_IN_USE);
            pPlayer->PlayerTalkClass->CloseGossip();
			return true;
		}

		sMultiTalentMgr.SwichTemplate(pPlayer, action);
        pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_SWITCH_OK);
        pPlayer->PlayerTalkClass->CloseGossip();

		return true;
	}
	else if (sender == 80007)
	{
		// TODO: Check limitation
        //pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_CREATE_EXCEED);
		sMultiTalentMgr.IncreaseMaxTemplate(pPlayer);
        sMultiTalentMgr.SwichTemplate(pPlayer, pPlayer->GetMaxTalentTemplate());
        pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_CREATE_EXCEED);
        pPlayer->PlayerTalkClass->CloseGossip();
		return true;
	}
	else
	{
		return false;
	}
}
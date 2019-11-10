/**
 *
 * @File : item_transmogrification.cpp
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#include "item_multi_talent.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/MultiTalentMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
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

bool CheckCreateTalentTemplatePermission(Player* pPlayer)
{
    uint32 permission = sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_PERMISSION);
    return pPlayer->GetSession()->GetSecurity() >= (AccountTypes)permission;
}

bool HandleMultiTalentGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender < 80006 || sender > 80007) return false;

	if (!CheckCreateTalentTemplatePermission(pPlayer))
	{
		pPlayer->PlayerTalkClass->CloseGossip();
		pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
		return true;
	}

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
		// Check limitation
		uint32 limit = sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_MAX);
		if (pPlayer->GetMaxTalentTemplate() >= limit - 1)
		{
        	pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_CREATE_EXCEED);
			pPlayer->PlayerTalkClass->CloseGossip();
			return true;
		}
		// Cost
		uint32 cost = 0;
		uint32 balance = 0;
		uint32 currency_id;
		const char* currency_name = nullptr;
		switch(sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_COST_TYPE))
		{
			case MULTI_TALENT_COST_MONEY:
				cost = sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_COST_VALUE);
				if (pPlayer->GetMoney() < cost)
				{
					pPlayer->PlayerTalkClass->CloseGossip();
					pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_NO_MONEY);
					return true;
				}
				pPlayer->ModifyMoney(-1 * cost);
				break;
			case MULTI_TALENT_COST_CUSTOM_CURRENCY:
				cost = sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_COST_VALUE);
				currency_id = sDBConfigMgr.GetUInt32(CONFIG_MULTI_TALENT_COST_CURRENCY);
				balance = sCustomCurrencyMgr.GetAccountCurrency(pPlayer->GetSession()->GetAccountId(), currency_id);
                currency_name = sCustomCurrencyMgr.GetCurrencyInfo(currency_id)->name.c_str();
				if (balance < cost)
				{
					pPlayer->PlayerTalkClass->CloseGossip();
					pPlayer->GetSession()->SendNotification(
						LANG_TELE_STORE_NO_CURRENCY_TO_BUY, 
						cost,
                        currency_name,
						balance,
                        currency_name);
					return true;
				}
				sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), currency_id, -1 * cost);
				pPlayer->GetSession()->SendNotification(
					LANG_TELE_STORE_PAID_WITH_CURRENCY, 
                    currency_name,
					cost,
                    currency_name,
					balance - cost);
				break;
			case MULTI_TALENT_COST_FREE:
			default:
				break;
		}

		sMultiTalentMgr.IncreaseMaxTemplate(pPlayer);
        sMultiTalentMgr.SwichTemplate(pPlayer, pPlayer->GetMaxTalentTemplate());
        pPlayer->GetSession()->SendNotification(LANG_MULTI_TALENT_CREATE_OK);
        pPlayer->PlayerTalkClass->CloseGossip();
		return true;
	}
	else
	{
		return false;
	}
}
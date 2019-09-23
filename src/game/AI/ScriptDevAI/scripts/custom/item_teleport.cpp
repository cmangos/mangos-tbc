/**
 *
 * @File : item_teleport.cpp
 * @Authors : yukozh
 * @Date : 09/09/2019
 *
 **/

#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "AI/ScriptDevAI/include/sc_item_teleport.h"
#include "Tools/Language.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "Pomelo/TransmogrificationMgr.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/DailySignInRewardMgr.h"
#include "item_transmogrification.h"
#include "item_multi_talent.h"

#define SPELL_VISUAL_TELEPORT   35517

using namespace Teleport;

std::unordered_map<ObjectGuid, Creature*> npc_container;

void AddFilteredGossipMenuForPlayer(uint32 menu_id, Player* pPlayer, ObjectGuid guid, TELE_ORDER order)
{
	for (size_t i = 0; i < map_item[menu_id].size(); ++i)
	{
		auto item = map_item[menu_id][i];
		if (order != item.faction_order) continue;
		pPlayer->ADD_GOSSIP_ITEM(item.icon, item.text, menu_id, item.action_id);
	}
}

bool IsAlliance(uint8 race)
{
	return race == 1 || race == 3 || race == 4 || race == 7 || race == 11;
}

bool DetectAttacks(Player* pPlayer)
{
	if (pPlayer->getAttackers().size() > 0)
	{
		pPlayer->GetSession()->SendNotification(LANG_TELE_CANNOT_USE_WHEN_ATTACK);
		pPlayer->PlayerTalkClass->CloseGossip();
		return true;
	}

	return false;
}

void GenerateGossipMenu(uint32 menu_id, Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	if (map_order[menu_id])
	{
		if (IsAlliance(pPlayer->getRace()))
		{
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::ALLIANCE);
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::HORDE);
		}
		else
		{
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::HORDE);
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::ALLIANCE);
		}
	}
	AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::NONE);
	pPlayer->SEND_GOSSIP_MENU(100000 - menu_id, guid);
}

void TeleportTo(Player* const player, const uint16& map,
	const float& X, const float& Y, const float& Z, const float& orient)
{
	// Play the teleport spell before teleport player
	player->Unmount();
	player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
	player->CastSpell(player, SPELL_VISUAL_TELEPORT, TRIGGERED_OLD_TRIGGERED);
	player->TeleportTo(map, X, Y, Z, orient);
}

bool FindActionItem(uint32 menu_id, uint32 action, TELE_ITEM& item)
{
	for (size_t i = 0; i < map_item[menu_id].size(); ++i)
	{
		if (map_item[menu_id][i].action_id == action)
		{
			item = map_item[menu_id][i];
			return true;
		}
	}

	return false;
}

void LearnAllGreenClassSpells(Player* pPlayer, Creature* pCreature)
{
    TrainerSpellData const* spells = pCreature->GetTrainerTemplateSpells();
    if (!spells) return;
    for (const auto& itr : spells->spellList)
    {
        TrainerSpell const* tSpell = &itr.second;

        uint32 reqLevel = 0;
        if (!pPlayer->IsSpellFitByClassAndRace(tSpell->learnedSpell, &reqLevel))
            continue;

        if (tSpell->conditionId && !sObjectMgr.IsPlayerMeetToCondition(tSpell->conditionId, pPlayer, pCreature->GetMap(), pCreature, CONDITION_FROM_TRAINER))
            continue;

        reqLevel = tSpell->isProvidedReqLevel ? tSpell->reqLevel : std::max(reqLevel, tSpell->reqLevel);

        TrainerSpellState state = pPlayer->GetTrainerSpellState(tSpell, reqLevel);

        if (state == TrainerSpellState::TRAINER_SPELL_GREEN)
        {
            pPlayer->learnSpell(itr.first, true);
        }
    }
}

bool GossipSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	TELE_ITEM item;

	// Delete previous store npc
	if (pObj && pObj->GetObjectGuid() && npc_container[pObj->GetObjectGuid()])
	{
		try // Need enable /EHa in VC 
		{
            auto pCreature = npc_container[pObj->GetObjectGuid()];
            if (pCreature)
            {
                pCreature->RemoveFromWorld();
            }
            npc_container.erase(pObj->GetObjectGuid());
		}
		catch (...) 
		{
		}
	}

	if (HandleTransmogrificationGossipMenuSelect(pPlayer, pObj, sender, action)) // Transmogrification
	{
		return true;
	}
	else if (HandleMultiTalentGossipMenuSelect(pPlayer, pObj, sender, action))
	{
		return true;
	}
	else if (!FindActionItem(sender, action, item))
	{
		return false;
	}

	if (DetectAttacks(pPlayer))
	{
		return true;
	}

	std::vector<CustomCurrencyOwnedPair> currencies;
    uint8 classId;
    uint32 npcId;

	// TODO: Support more functions
	switch (item.function)
	{
	case TELE_FUNC::SHOW_SUB_MENU:
		GenerateGossipMenu(item.trigger_menu, pPlayer, pObj->GetObjectGuid());
		break;
	case TELE_FUNC::TELEPORT:
		// Permission check
		if (pPlayer->GetSession()->GetSecurity() < (AccountTypes)item.permission_required)
		{
			pPlayer->PlayerTalkClass->CloseGossip();
			pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
			return true;
		}

		// Level check
		if (pPlayer->getLevel() < item.level_required)
		{
			pPlayer->PlayerTalkClass->CloseGossip();
			pPlayer->GetSession()->SendNotification(LANG_LEVEL_NOT_REACHED, item.level_required);
			return true;
		}

		// Cost
		if (item.cost_type == TELE_COST::COST_MONEY)
		{
			if (pPlayer->GetMoney() < item.cost_amount)
			{
				pPlayer->GetSession()->SendNotification(LANG_TELE_NO_MONEY_TO_USE);
				pPlayer->PlayerTalkClass->CloseGossip();
			}
			else
			{
				pPlayer->ModifyMoney(-1 * item.cost_amount);	
			}
		}
		else if (item.cost_type == TELE_COST::COST_CUSTOM_CURRENCY)
		{
			uint32 balance = sCustomCurrencyMgr.GetAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id);
			auto currency_info = sCustomCurrencyMgr.GetCurrencyInfo(item.cost_currency_id);
			if (item.cost_amount > balance)
			{
				pPlayer->PlayerTalkClass->CloseGossip();
				pPlayer->GetSession()->SendNotification(
					LANG_TELE_STORE_NO_CURRENCY_TO_BUY, 
					item.cost_amount,
					currency_info.name,
					balance,
					currency_info.name);
				return true;
			}
			else
			{
				sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id, -1 * item.cost_amount);
				pPlayer->GetSession()->SendNotification(
					LANG_TELE_STORE_PAID_WITH_CURRENCY, 
					currency_info.name,
					item.cost_amount,
					currency_info.name,
					balance - item.cost_amount);
			}
		}

		// Teleport
		TeleportTo(pPlayer, item.teleport_map, item.teleport_x, item.teleport_y, item.teleport_z, 0);
		pPlayer->PlayerTalkClass->CloseGossip();
		break;
	case TELE_FUNC::STORE:
		Creature* pStoreNpc;
		pStoreNpc = pPlayer->SummonCreature(item.trigger_menu, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 60000);
		pStoreNpc->SetObjectScale(0.000001f);
        pPlayer->GetSession()->SendListInventory(pStoreNpc->GetObjectGuid());
		npc_container[pObj->GetObjectGuid()] = pStoreNpc;
		break;
    case TELE_FUNC::TRAIN:
        // Permission check
        if (pPlayer->GetSession()->GetSecurity() < (AccountTypes)item.permission_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
            return true;
        }

        // Level check
        if (pPlayer->getLevel() < item.level_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_LEVEL_NOT_REACHED, item.level_required);
            return true;
        }

        // Cost
        if (item.cost_type == TELE_COST::COST_MONEY)
        {
            if (pPlayer->GetMoney() < item.cost_amount)
            {
                pPlayer->GetSession()->SendNotification(LANG_TELE_NO_MONEY_TO_USE);
                pPlayer->PlayerTalkClass->CloseGossip();
            }
            else
            {
                pPlayer->ModifyMoney(-1 * item.cost_amount);
            }
        }
        else if (item.cost_type == TELE_COST::COST_CUSTOM_CURRENCY)
        {
            uint32 balance = sCustomCurrencyMgr.GetAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id);
            auto currency_info = sCustomCurrencyMgr.GetCurrencyInfo(item.cost_currency_id);
            if (item.cost_amount > balance)
            {
                pPlayer->PlayerTalkClass->CloseGossip();
                pPlayer->GetSession()->SendNotification(
                    LANG_TELE_STORE_NO_CURRENCY_TO_BUY,
                    item.cost_amount,
                    currency_info.name,
                    balance,
                    currency_info.name);
                return true;
            }
            else
            {
                sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id, -1 * item.cost_amount);
                pPlayer->GetSession()->SendNotification(
                    LANG_TELE_STORE_PAID_WITH_CURRENCY,
                    currency_info.name,
                    item.cost_amount,
                    currency_info.name,
                    balance - item.cost_amount);
            }
        }

        Creature* pTrainNpc;
        pTrainNpc = pPlayer->SummonCreature(item.trigger_menu, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 10000);
        pTrainNpc->SetObjectScale(0.000001f);
        pPlayer->PlayerTalkClass->CloseGossip();
		LearnAllGreenClassSpells(pPlayer, pTrainNpc);
        npc_container[pObj->GetObjectGuid()] = pTrainNpc;
        break;
    case TELE_FUNC::TRAIN_CLASS:
        // Permission check
        if (pPlayer->GetSession()->GetSecurity() < (AccountTypes)item.permission_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
            return true;
        }

        // Level check
        if (pPlayer->getLevel() < item.level_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_LEVEL_NOT_REACHED, item.level_required);
            return true;
        }

        // Cost
        if (item.cost_type == TELE_COST::COST_MONEY)
        {
            if (pPlayer->GetMoney() < item.cost_amount)
            {
                pPlayer->GetSession()->SendNotification(LANG_TELE_NO_MONEY_TO_USE);
                pPlayer->PlayerTalkClass->CloseGossip();
            }
            else
            {
                pPlayer->ModifyMoney(-1 * item.cost_amount);
            }
        }
        else if (item.cost_type == TELE_COST::COST_CUSTOM_CURRENCY)
        {
            uint32 balance = sCustomCurrencyMgr.GetAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id);
            auto currency_info = sCustomCurrencyMgr.GetCurrencyInfo(item.cost_currency_id);
            if (item.cost_amount > balance)
            {
                pPlayer->PlayerTalkClass->CloseGossip();
                pPlayer->GetSession()->SendNotification(
                    LANG_TELE_STORE_NO_CURRENCY_TO_BUY,
                    item.cost_amount,
                    currency_info.name,
                    balance,
                    currency_info.name);
                return true;
            }
            else
            {
                sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), item.cost_currency_id, -1 * item.cost_amount);
                pPlayer->GetSession()->SendNotification(
                    LANG_TELE_STORE_PAID_WITH_CURRENCY,
                    currency_info.name,
                    item.cost_amount,
                    currency_info.name,
                    balance - item.cost_amount);
            }
        }

        Creature* pTrainClassNpc;
		classId = pPlayer->getClass();
		if (IsAlliance(pPlayer->getRace())) 
		{
			npcId = sDBConfigMgr.GetUInt32("stone.trainer.alliance." + std::to_string(classId));
		}
		else
		{
			npcId = sDBConfigMgr.GetUInt32("stone.trainer.horde." + std::to_string(classId));
		}
        pTrainClassNpc = pPlayer->SummonCreature(npcId, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 10000);
        pTrainClassNpc->SetObjectScale(0.000001f);
		pPlayer->PlayerTalkClass->CloseGossip();
		LearnAllGreenClassSpells(pPlayer, pTrainClassNpc);
        npc_container[pObj->GetObjectGuid()] = pTrainClassNpc;
        break;
	case TELE_FUNC::BANK:
		pPlayer->GetSession()->SendShowBank(pObj->GetObjectGuid());
		pPlayer->PlayerTalkClass->CloseGossip();
		break;
	case TELE_FUNC::QUERY_CURRENCY:
		currencies = pPlayer->GetOwnedCustomCurrencies();
		if (!currencies.size())
		{
			pPlayer->GetSession()->SendNotification(LANG_TELE_CURR_NO_RESULT);
		}
		else
		{
			for (size_t i = 0; i < currencies.size(); ++i)
			{
				ChatHandler(pPlayer).PSendSysMessage(
					LANG_TELE_CURR_QUERY_RESULT,
					sCustomCurrencyMgr.GetCurrencyInfo(currencies[i].curid).name.c_str(),
					currencies[i].amount);
			}
		}

		pPlayer->PlayerTalkClass->CloseGossip();
		break;
	case TELE_FUNC::TRANSMOGRIFY_MENU:
		GenerateTransmogrificationGossipMenu(pPlayer, pObj->GetObjectGuid());
		break;
	case TELE_FUNC::MULTI_TALENT_MENU:
		GenerateMultiTalentGossipMenu(pPlayer, pObj->GetObjectGuid());
		break;
	case TELE_FUNC::DAILY_REWARD:
        // Permission check
        if (pPlayer->GetSession()->GetSecurity() < (AccountTypes)item.permission_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
            return true;
        }

        // Level check
        if (pPlayer->getLevel() < item.level_required)
        {
            pPlayer->PlayerTalkClass->CloseGossip();
            pPlayer->GetSession()->SendNotification(LANG_LEVEL_NOT_REACHED, item.level_required);
            return true;
        }

		if (sDailySignInRewardMgr.ClaimReward(pPlayer))
		{
    		uint32 amount = sDBConfigMgr.GetUInt32("reward.daily.amount");
    		uint32 currencyId = sDBConfigMgr.GetUInt32("reward.daily.currency");
			ChatHandler(pPlayer).PSendSysMessage(
				LANG_CLAIM_DAILY_REWARD_OK,
				sCustomCurrencyMgr.GetCurrencyInfo(currencyId).name.c_str(),
				amount);
            pPlayer->PlayerTalkClass->CloseGossip();
		}
		else
		{
            pPlayer->GetSession()->SendNotification(LANG_CLAIM_DAILY_REWARD_FAIL);
            pPlayer->PlayerTalkClass->CloseGossip();
		}

		break;
	default:
		return false;
		break;
	}

	return true;
}

bool GossipHello(Player* pPlayer, Creature* pCreature)
{
	GenerateGossipMenu(0, pPlayer, pCreature->GetObjectGuid());
	return true;
}

bool GossipItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
	if (!DetectAttacks(pPlayer))
	{
		GenerateGossipMenu(0, pPlayer, pItem->GetObjectGuid());
	}
	return true;
}

bool GossipSelectCreature(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
	return GossipSelect(pPlayer, pCreature, sender, action);
}

bool GossipSelectItem(Player* pPlayer, Item* pItem, uint32 sender, uint32 action)
{
	return GossipSelect(pPlayer, pItem, sender, action);
}

void AddSC_item_teleport()
{
	// Load data from DB
	BuildTeleportMenuMap();

	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_teleport";
	newscript->pItemUse = &GossipItemUse;
	newscript->pGossipHello = &GossipHello;
	newscript->pGossipSelect = &GossipSelectCreature;
	newscript->pGossipSelectItem = &GossipSelectItem;
    newscript->RegisterSelf();
}

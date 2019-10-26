/**
 *
 * @File : item_transmogrification.cpp
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#include "item_transmogrification.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/TransmogrificationMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"

#define MODEL_VENDOR_ID 80037

std::string GetQualityColor(uint32 quality)
{
    switch(quality)
    {
        case 0:
            return "|cff9d9d9d";
        case 1:
            return "|cffffffff";
        case 2:
            return "|cff1eff00";
        case 3:
            return "|cff0081ff";
        case 4:
            return "|cffc600ff";
        case 5:
            return "|cffff8000";
        case 6:
            return "|cffe5cc80";
        default:
            return "";
    }
}

std::string GenerateItemText(std::string name, uint32 quality)
{
    return GetQualityColor(quality) + "[" + name + "]|r";
}

void GenerateTransmogrificationGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_TRANSMOG_SELECT_MODEL), 80002, 0);
	pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_TRANSMOG_UNSELECT_MODEL), 80002, 1);
	pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_TRANSMOG_APPLY), 80002, 2);
	pPlayer->ADD_GOSSIP_ITEM(0, pPlayer->GetSession()->GetMangosString(LANG_TRANSMOG_REMOVE), 80002, 3);
    pPlayer->ADD_GOSSIP_ITEM(1, pPlayer->GetSession()->GetMangosString(LANG_TRANSMOG_BUY_WEAPON), 80002, 4);
	
	pPlayer->SEND_GOSSIP_MENU(100000 - 1000, guid);
}

void GenerateTransmogrificationSelectModelGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	for (uint8 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
	{
		Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
		if (!pItem) continue;
		if (sTransmogrificationMgr.IsItemTransmogrified(pItem->GetGUIDLow())) continue;
        auto pProto = pItem->GetProto();
		pPlayer->ADD_GOSSIP_ITEM(0, GenerateItemText(pProto->Name1, pProto->Quality), 80003, i);
	}
	
	pPlayer->SEND_GOSSIP_MENU(100000 - 1001, guid);
}

void GenerateTransmogrificationApplyModelGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	std::vector<TransmogrificationTempStore> stored = sTransmogrificationMgr.GetStoredDisplays(pPlayer);
	for (auto i = stored.begin(); i != stored.end(); ++i) 
	{
		Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, i->slot);
		if (pItem)
		{
            auto pProto = pItem->GetProto();
            auto str = GenerateItemText(pProto->Name1, pProto->Quality) + " -> " + GenerateItemText(i->name, i->quality);
			pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80004, i->slot);
		}
	}
	
	pPlayer->SEND_GOSSIP_MENU(100000 - 1002, guid);
}

void GenerateTransmogrificationRestoreModelGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	std::vector<TransmogrificationTempStore> stored = sTransmogrificationMgr.GetTransmogrifiedItems(pPlayer);
	for (auto i = stored.begin(); i != stored.end(); ++i)
	{
		auto str = GenerateItemText(i->name, i->quality);
		pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80005, i->item_template_id);
	}

	pPlayer->SEND_GOSSIP_MENU(100000 - 1003, guid);
}

bool CheckTransmogrificationPermission(Player* pPlayer)
{
    uint32 permission = sDBConfigMgr.GetUInt32(CONFIG_TRANSMOG_PERMISSION);
    return pPlayer->GetSession()->GetSecurity() >= (AccountTypes)permission;
}

bool HandleTransmogrificationGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender < 80002 || sender > 80005) return false;

	if (!CheckTransmogrificationPermission(pPlayer))
	{
		pPlayer->PlayerTalkClass->CloseGossip();
		pPlayer->GetSession()->SendNotification(LANG_NO_PERMISSION_TO_USE);
		return true;
	}

    if (sender == 80002)
	{
		switch(action)
		{
			case 0:
				GenerateTransmogrificationSelectModelGossipMenu(pPlayer, pObj->GetObjectGuid());
				break;
			case 1:
				sTransmogrificationMgr.ClearStoredDisplays(pPlayer);
				pPlayer->PlayerTalkClass->CloseGossip();
				pPlayer->GetSession()->SendNotification(LANG_TRANSMOG_UNSELECT_MODEL_OK);
				break;
			case 2:
				GenerateTransmogrificationApplyModelGossipMenu(pPlayer, pObj->GetObjectGuid());
				break;
			case 3:
				GenerateTransmogrificationRestoreModelGossipMenu(pPlayer, pObj->GetObjectGuid());
				break;
            case 4:
                Creature * pStoreNpc;
                pStoreNpc = pPlayer->SummonCreature(MODEL_VENDOR_ID, pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ(), 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 60000);
                pPlayer->GetSession()->SendListInventory(pStoreNpc->GetObjectGuid());
                break;
			default:
				return false;
		}
		return true;
	}
	else if (sender == 80003)
	{
		Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, uint8(action));
		if (pItem)
		{
			sTransmogrificationMgr.StoreDisplay(pPlayer, pItem);
			pPlayer->PlayerTalkClass->CloseGossip();
			pPlayer->GetSession()->SendNotification(LANG_TRANSMOG_SELECT_MODEL_OK);
		}
		return true;
	}
	else if (sender == 80004)
	{
		Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, uint8(action));
		if (pItem)
		{
			uint32 cost = 0;
			uint32 balance = 0;
			uint32 currency_id;
			const char* currency_name = nullptr;
			switch(sDBConfigMgr.GetUInt32(CONFIG_TRANSMOG_COST_TYPE))
			{
				case TRANSMOG_COST_MONEY:
					cost = sDBConfigMgr.GetUInt32(CONFIG_TRANSMOG_COST_VALUE);
					if (pPlayer->GetMoney() < cost)
					{
						pPlayer->PlayerTalkClass->CloseGossip();
						pPlayer->GetSession()->SendNotification(LANG_TRANSMOG_NO_MONEY);
						return true;
					}
					pPlayer->ModifyMoney(-1 * cost);
					break;
				case TRANSMOG_COST_CUSTOM_CURRENCY:
					cost = sDBConfigMgr.GetUInt32(CONFIG_TRANSMOG_COST_VALUE);
					currency_id = sDBConfigMgr.GetUInt32(CONFIG_TRANSMOG_COST_CURRENCY);
					balance = sCustomCurrencyMgr.GetAccountCurrency(pPlayer->GetSession()->GetAccountId(), currency_id);
					if (balance < cost)
					{
						pPlayer->PlayerTalkClass->CloseGossip();
                        currency_name = sCustomCurrencyMgr.GetCurrencyInfo(currency_id)->name.c_str();
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
				case TRANSMOG_COST_FREE:
				default:
					break;
			}
			sTransmogrificationMgr.TransmogrifyItemFromTempStore(pItem, (EquipmentSlots)action);
			pPlayer->PlayerTalkClass->CloseGossip();
			pPlayer->GetSession()->SendNotification(LANG_TRANSMOG_APPLY_OK);
		}
		return true;
	}
	else if (sender == 80005)
	{
		Item* pItem = pPlayer->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, action));
		if (pItem)
		{
			sTransmogrificationMgr.RestoreTransmogrification(pPlayer, pItem->GetGUIDLow());
			pPlayer->PlayerTalkClass->CloseGossip();
			pPlayer->GetSession()->SendNotification(LANG_TRANSMOG_RESTORE_OK);
		}
		return true;
	}
	else
	{
		return false;
	}
}
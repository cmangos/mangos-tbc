/**
 *
 * @File : item_currency.cpp
 * @Authors : yukozh
 * @Date : 10/26/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

using namespace Teleport;

#define POMELO_CURRENCY_100   83510
#define POMELO_CURRENCY_500   83511
#define POMELO_CURRENCY_1000  83512
#define POMELO_CURRENCY_5000  83513

#define POMELO_CURRENCY_B_1   83520
#define POMELO_CURRENCY_B_5   83521
#define POMELO_CURRENCY_B_10  83522
#define POMELO_CURRENCY_B_50  83523
#define POMELO_CURRENCY_B_100 83524

#define POMELO_CURRENCY_C_30    83530
#define POMELO_CURRENCY_C_150   83531
#define POMELO_CURRENCY_C_1500  83532

bool CurrencyItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    uint32 item = pItem->GetProto()->ItemId;
    if (item == POMELO_CURRENCY_100)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 2, 100);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(2)->name.c_str(),
            100);
    }
    else if (item == POMELO_CURRENCY_500)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 2, 500);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(2)->name.c_str(),
            500);
    }
    else if (item == POMELO_CURRENCY_1000)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 2, 1000);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(2)->name.c_str(),
            1000);
    }
    else if (item == POMELO_CURRENCY_5000)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 2, 5000);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(2)->name.c_str(),
            5000);
    }
    else if (item == POMELO_CURRENCY_B_1)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 1, 1);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(1)->name.c_str(),
            1);
    }
    else if (item == POMELO_CURRENCY_B_5)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 1, 5);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(1)->name.c_str(),
            5);
    }
    else if (item == POMELO_CURRENCY_B_10)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 1, 10);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(1)->name.c_str(),
            10);
    }
    else if (item == POMELO_CURRENCY_B_50)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 1, 50);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(1)->name.c_str(),
            50);
    }
    else if (item == POMELO_CURRENCY_B_100)
    {
        sCustomCurrencyMgr.ModifyAccountCurrency(pPlayer->GetSession()->GetAccountId(), 1, 100);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_CURRENCY_GAIN,
            sCustomCurrencyMgr.GetCurrencyInfo(1)->name.c_str(),
            100);
    }
    else if (item == POMELO_CURRENCY_C_30)
    {
        pPlayer->ModifyMoney(200000);
    }
    else if (item == POMELO_CURRENCY_C_150)
    {
        pPlayer->ModifyMoney(1000000);
    }
    else if (item == POMELO_CURRENCY_C_1500)
    {
        pPlayer->ModifyMoney(10000000);
    }
    else 
    {
        return false;
    }

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_currency()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_currency";
	newscript->pItemUse = &CurrencyItemUse;
    newscript->RegisterSelf();
}

/**
 *
 * @File : item_soldier.cpp
 * @Authors : yukozh
 * @Date : 10/13/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

bool SoliderItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    if (pPlayer->isInCombat() || !pPlayer->isAlive())
    {
        pPlayer->GetSession()->SendNotification(LANG_CANNOT_USE_IN_COMBAT);
        return true;
    }
    
    uint32 max = sDBConfigMgr.GetUInt32("soldier.max");
    if (pPlayer->GetMaxSoldier() >= max)
    {
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_PLAYERBOT_EXCEED_CAP);
        return true;
    }

    pPlayer->IncreaseMaxSoldier();
    ChatHandler(pPlayer).PSendSysMessage(
        LANG_PLAYERBOT_INCREASED_CAP, pPlayer->GetMaxSoldier());

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_soldier()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_soldier";
	newscript->pItemUse = &SoliderItemUse;
    newscript->RegisterSelf();
}

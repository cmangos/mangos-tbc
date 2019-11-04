/**
 *
 * @File : item_tradeskill.cpp
 * @Authors : yukozh
 * @Date : 10/26/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

using namespace Teleport;

bool TradeSkillItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    pPlayer->m_addTradeSkills = 1;

    ChatHandler(pPlayer).PSendSysMessage(
        LANG_ADDITIONAL_TRADE_SKILL);

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_tradeskill()
{
    // Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_tradeskill";
	newscript->pItemUse = &TradeSkillItemUse;
    newscript->RegisterSelf();
}

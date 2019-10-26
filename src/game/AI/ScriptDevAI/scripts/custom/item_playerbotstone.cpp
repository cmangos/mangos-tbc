/**
 *
 * @File : item_playerbotstone.cpp
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
#include "item_playerbot.h"

bool PlayerbotStoneItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    GeneratePlayerBotGossipMenu(pPlayer, pItem->GetObjectGuid());
    return true;
}

bool PlayerbotStoneGossipSelectItem(Player* pPlayer, Item* pItem, uint32 sender, uint32 action)
{
    return HandlePlayerBotGossipMenuSelect(pPlayer, pItem, sender, action);
}

void AddSC_item_playerbotstone()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_playerbotstone";
	newscript->pItemUse = &PlayerbotStoneItemUse;
    newscript->pGossipSelectItem = &PlayerbotStoneGossipSelectItem;
    newscript->RegisterSelf();
}

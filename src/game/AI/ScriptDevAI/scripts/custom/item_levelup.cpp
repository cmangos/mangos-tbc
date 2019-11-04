/**
 *
 * @File : item_levelup.cpp
 * @Authors : yukozh
 * @Date : 09/28/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

using namespace Teleport;

uint32 levelup_max_item;
uint32 levelup_1_item;
uint32 levelup_5_item;

void DoLevelupForLevelupItem(Player* pPlayer, uint32 level)
{
    uint32 max = sWorld.getConfig(CONFIG_UINT32_MAX_PLAYER_LEVEL);
    if (pPlayer->getLevel() + level > max)
    {
        level = max - pPlayer->getLevel();
    }

    if (level == 0)
    {
        return;
    }

    ChatHandler(pPlayer).HandleCharacterLevel(pPlayer, pPlayer->GetObjectGuid(), pPlayer->getLevel(), pPlayer->getLevel() + level);
}

bool LevelupItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    uint32 item = pItem->GetProto()->ItemId;
    if (item == levelup_max_item)
    {
        DoLevelupForLevelupItem(pPlayer, 120);
    }
    else if (item == levelup_1_item)
    {
        DoLevelupForLevelupItem(pPlayer, 1);
    }
    else if (item == levelup_5_item)
    {
        DoLevelupForLevelupItem(pPlayer, 5);
    }
    else 
    {
        return false;
    }

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_levelup()
{
	// Load data from DB
    levelup_max_item = sDBConfigMgr.GetUInt32("item.levelup.max.id");
    levelup_1_item = sDBConfigMgr.GetUInt32("item.levelup.1.id");
    levelup_5_item = sDBConfigMgr.GetUInt32("item.levelup.5.id");

	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_levelup";
	newscript->pItemUse = &LevelupItemUse;
    newscript->RegisterSelf();
}

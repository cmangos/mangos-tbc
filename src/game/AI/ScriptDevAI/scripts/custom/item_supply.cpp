/**
 *
 * @File : item_revive.cpp
 * @Authors : yukozh
 * @Date : 10/09/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"
#include "Pomelo/DBConfigMgr.h"
#include "Chat/Chat.h"
#include "World/World.h"

#define SUPPLY_HEAL_DRUG 22829
#define SUPPLY_MANA_DRUG 22832

bool IsManaClass(uint32 classId)
{
    return classId == 2 || classId == 3 || classId == 5 || classId == 7 || classId == 8 || classId == 9 || classId == 11;
}

bool SupplyItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    if (pPlayer->isInCombat() || !pPlayer->isAlive())
    {
        pPlayer->GetSession()->SendNotification(LANG_CANNOT_USE_IN_COMBAT);
        return true;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (!pGroup)
    {
        pPlayer->GetSession()->SendNotification(LANG_MUST_IN_TEAM_OR_GROUP);
        return true;
    }

    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* pMember = itr->getSource();
        uint32 mapId = pPlayer->GetMapId();

        if (pMember->GetMapId() != mapId)
            continue;

        float distance = pPlayer->GetDistance(pMember);
        if (distance > 200)
            continue;

        // Add items for players
        ItemPosCountVec dest;
        if (pMember->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, SUPPLY_HEAL_DRUG, 5) != EQUIP_ERR_OK)
            continue;
        std::string command = std::to_string(SUPPLY_HEAL_DRUG) + " 5";
        ChatHandler(pMember).HandleAddItemCommandInternal((char*)command.c_str(), true);

        if (IsManaClass(pMember->getClass()))
        {
            if (pMember->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, SUPPLY_MANA_DRUG, 5) != EQUIP_ERR_OK)
                continue;
            command = std::to_string(SUPPLY_MANA_DRUG) + " 5";
            ChatHandler(pMember).HandleAddItemCommandInternal((char*)command.c_str(), true);
        }
    }

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_supply()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_supply";
	newscript->pItemUse = &SupplyItemUse;
    newscript->RegisterSelf();
}

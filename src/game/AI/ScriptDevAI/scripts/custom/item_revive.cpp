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

bool ReviveItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
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

    size_t count = 0;
    for (GroupReference* itr = pGroup->GetFirstMember(); itr != nullptr; itr = itr->next())
    {
        Player* pMember = itr->getSource();
        uint32 mapId = pPlayer->GetMapId();

        if (!pMember->IsInWorld() || !pMember->isDead())
            continue;

        if (pMember->GetMapId() != mapId)
            continue;

        float distance = pPlayer->GetDistance(pMember);
        if (distance > 100)
            continue;

        pPlayer->CastSpell(pMember, 24341, TRIGGERED_OLD_TRIGGERED);
        ++count;
    }

    if (count == 0)
    {
        pPlayer->GetSession()->SendNotification(LANG_NO_BODY_TO_REVIVE);
        return true;
    }

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_revive()
{
	// Register script
    Script *newscript;
    newscript = new Script;
    newscript->Name="item_revive";
	newscript->pItemUse = &ReviveItemUse;
    newscript->RegisterSelf();
}

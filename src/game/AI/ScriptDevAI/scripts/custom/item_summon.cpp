/**
 *
 * @File : item_summon.cpp
 * @Authors : yukozh
 * @Date : 10/09/2019
 *
 **/

#include "item_multi_talent.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/MultiTalentMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"

bool SummonOnePlayer(Player* pCaster, Player* pTarget)
{
    if (pTarget->GetDummyAura(23445))
        return false;

    float x, y, z;
    pCaster->GetPosition(x, y, z);

    pTarget->SetSummonPoint(pCaster->GetMapId(), x, y, z);

    WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
    data << pCaster->GetObjectGuid();                      // summoner guid
    data << uint32(pCaster->GetZoneId());                  // summoner zone
    data << uint32(MAX_PLAYER_SUMMON_DELAY * IN_MILLISECONDS); // auto decline after msecs
    pTarget->GetSession()->SendPacket(data);
    return true;
}

bool SummonItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
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

        if (!pMember->IsInWorld())
            continue;

        if (pMember->GetGUIDLow() == pPlayer->GetGUIDLow())
            continue;

        SummonOnePlayer(pPlayer, pMember);
    }

    pPlayer->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
    return true;
}

void AddSC_item_summon()
{
    // Register script
    Script* newscript;
    newscript = new Script;
    newscript->Name = "item_summon";
    newscript->pItemUse = &SummonItemUse;
    newscript->RegisterSelf();
}

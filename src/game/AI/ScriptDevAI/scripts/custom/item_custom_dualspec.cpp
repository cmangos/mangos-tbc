/*
* ScriptData
* SDName:      item_custom_dualspec
* SD%Complete: 100
* SDComment:
* EndScriptData
*/

#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"

enum
{
    TEXT_ID_GEM = 50701,
};

enum DualSpecMessages
{
    DUAL_SPEC_DESCRIPTION = 12000,
    DUAL_SPEC_COST_IS,
    DUAL_SPEC_CHANGE_MY_SPEC,
    DUAL_SPEC_NO_GOLD_UNLOCK,
    DUAL_SPEC_ARE_YOU_SURE_BEGIN,
    DUAL_SPEC_ARE_YOU_SURE_END,
    DUAL_SPEC_ALREADY_ON_SPEC,
    DUAL_SPEC_ACTIVATE,
    DUAL_SPEC_RENAME,
    DUAL_SPEC_UNNAMED,
    DUAL_SPEC_ACTIVE,
    DUAL_SPEC_ERR_COMBAT,
    DUAL_SPEC_ERR_INSTANCE,
    DUAL_SPEC_ERR_MOUNT,
    DUAL_SPEC_ERR_DEAD,
    DUAL_SPEC_ERR_UNLOCK,
    DUAL_SPEC_ERR_LEVEL,
    DUAL_SPEC_ACTIVATE_COLOR,
    DUAL_SPEC_RENAME_COLOR,
    DUAL_SPEC_ARE_YOU_SURE_SWITCH,
    DUAL_SPEC_PURCHASE,
};

bool GossipItemUse_custom_dualspec(Player* pPlayer, Item* pItem, const SpellCastTargets& /*pTargets*/)
{
    pPlayer->GetPlayerMenu()->ClearMenus();

    if (pPlayer->IsInCombat())
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_COMBAT);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    if (pPlayer->GetMap()->IsBattleGroundOrArena() || pPlayer->GetMap()->IsDungeon() || pPlayer->GetMap()->IsRaid())
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_INSTANCE);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    if (pPlayer->IsFlying() || pPlayer->IsTaxiFlying() || pPlayer->IsMounted())
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_MOUNT);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    if (pPlayer->IsDead())
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_DEAD);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    if (pPlayer->GetSpecsCount() < MAX_TALENT_SPECS)
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_UNLOCK);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    if (pPlayer->GetLevel() < 10)
    {
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ERR_LEVEL);
        pPlayer->GetSession()->SendNotification(msg.c_str());
        return false;
    }

    uint8 specCount = pPlayer->GetSpecsCount();
    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ACTIVATE_COLOR);
        if (pPlayer->GetSpecName(i) == "NULL")
            specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_UNNAMED);
        else
            specNameString << pPlayer->GetSpecName(i);
        if (i == pPlayer->GetActiveSpec())
            specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ACTIVE);
        else
            specNameString << "";

        specNameString << "|r";
 
        const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ARE_YOU_SURE_SWITCH);
        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (1 + i), msg, 0, false);
    }

    for (uint8 i = 0; i < specCount; ++i)
    {
        std::stringstream specNameString;
        specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_RENAME_COLOR);
        if (pPlayer->GetSpecName(i) == "NULL")
            specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_UNNAMED);
        else
            specNameString << pPlayer->GetSpecName(i);
        if (i == pPlayer->GetActiveSpec())
            specNameString << pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ACTIVE);

        specNameString << "|r";

        pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_BATTLE, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (10 + i), "", 0, true);
    }

    pPlayer->SEND_GOSSIP_MENU(TEXT_ID_GEM, pItem->GetObjectGuid());
    return true;
}

bool GossipSelectItem_custom_dualspec(Player* pPlayer, Item* pItem, uint32 sender, uint32 action)
{
    switch (action)
    {
        case GOSSIP_ACTION_INFO_DEF + 1:
        {
            if (pPlayer->GetActiveSpec() == 0)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ALREADY_ON_SPEC);
                pPlayer->GetSession()->SendNotification(msg.c_str());
                break;
            }
            pPlayer->ActivateSpec(0);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 2:
        {
            if (pPlayer->GetActiveSpec() == 1)
            {
                pPlayer->CLOSE_GOSSIP_MENU();
                const std::string msg = pPlayer->GetSession()->GetMangosString(DUAL_SPEC_ALREADY_ON_SPEC);
                pPlayer->GetSession()->SendNotification(msg.c_str());
                break;
            }
            pPlayer->ActivateSpec(1);
            break;
        }
        case GOSSIP_ACTION_INFO_DEF + 999:
        {
            pPlayer->CLOSE_GOSSIP_MENU();
            break;
        }
        default:
            break;
    }

    return true;
}

bool GossipSelectItemWithCode_custom_dualspec(Player* pPlayer, Item* pItem, uint32 sender, uint32 action, const char* sCode)
{
    if (action == GOSSIP_ACTION_INFO_DEF + 10)
        pPlayer->SetSpecName(0, sCode);
    else if (action == GOSSIP_ACTION_INFO_DEF + 11)
        pPlayer->SetSpecName(1, sCode);

    pPlayer->CLOSE_GOSSIP_MENU();
    return true;
}

void AddSC_item_custom_dualspec()
{
    Script* pNewScript;
    pNewScript = new Script;
    pNewScript->Name = "item_custom_dualspec";
    pNewScript->pItemUse = &GossipItemUse_custom_dualspec;
    pNewScript->pGossipSelectItem = &GossipSelectItem_custom_dualspec;
    pNewScript->pGossipSelectItemWithCode = &GossipSelectItemWithCode_custom_dualspec;
    pNewScript->RegisterSelf(false);
}

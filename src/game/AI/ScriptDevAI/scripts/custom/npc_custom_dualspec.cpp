/*
* ScriptData
* SDName:      npc_custom_dualspec
* SD%Complete: 100
* SDComment:
* EndScriptData
*/

#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "World.h"

enum
{
    TEXT_ID_CRYSTAL = 50700,
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
    DUAL_SPEC_ERR_ITEM_CREATE,
};

bool Add_dualspec_item(Player* player)
{
    if (!player)
        return false;

    WorldSession* session = player->GetSession();

    uint32 itemId = sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_ITEM_ID);
    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(itemId);
    if (!pProto)
    {
        session->SendAreaTriggerMessage("%s", DUAL_SPEC_ERR_ITEM_CREATE);
        return false;
    }

    uint32 count = 1;

    // Adding items
    uint32 noSpaceForCount = 0;

    // check space and find places
    ItemPosCountVec dest;
    uint8 msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemId, count, &noSpaceForCount);
    if (msg != EQUIP_ERR_OK)                                // convert to possible store amount
        count -= noSpaceForCount;

    if (count == 0 || dest.empty())                         // can't add any
    {
        session->SendAreaTriggerMessage("%s", DUAL_SPEC_ERR_ITEM_CREATE);
        return false;
    }

    Item* item = player->StoreNewItem(dest, itemId, true, Item::GenerateItemRandomPropertyId(itemId));

    if (count > 0 && item)
    {
        player->SendNewItem(item, count, false, true);
    }

    if (noSpaceForCount > 0)
        session->SendAreaTriggerMessage("%s", DUAL_SPEC_ERR_ITEM_CREATE);

    return true;
}

bool GossipHello_custom_dualspec(Player* player, Creature* creature)
{
    const std::string purchase = player->GetSession()->GetMangosString(DUAL_SPEC_PURCHASE);
    const std::string areYouSure = player->GetSession()->GetMangosString(DUAL_SPEC_ARE_YOU_SURE_BEGIN) + std::to_string(uint32(sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_COST) / 10000)) + player->GetSession()->GetMangosString(DUAL_SPEC_ARE_YOU_SURE_END);
    const std::string changeSpec = player->GetSession()->GetMangosString(DUAL_SPEC_CHANGE_MY_SPEC);
    uint8 specCount = player->GetSpecsCount();
    if (specCount < MAX_TALENT_SPECS)
    {
        player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_CHAT, purchase, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 0, areYouSure, sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_COST), false);
    }
    else
    {
        player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, changeSpec, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
        if (!player->GetItemCount(sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_ITEM_ID), true))
            Add_dualspec_item(player);
    }

    player->SEND_GOSSIP_MENU(TEXT_ID_CRYSTAL, creature->GetObjectGuid());
    return true;
}

bool GossipSelect_custom_dualspec(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    switch (action)
    {
    case GOSSIP_ACTION_INFO_DEF + 0:
    {
        if (player->GetMoney() >= sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_COST))
        {
            player->ModifyMoney(-int32(sWorld.getConfig(CONFIG_UINT32_DUAL_SPEC_COST)));
            player->SetSpecsCount(player->GetSpecsCount() + 1);
            GossipSelect_custom_dualspec(player, creature, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            Add_dualspec_item(player);
        }
        else
        {
            const std::string msg = player->GetSession()->GetMangosString(DUAL_SPEC_NO_GOLD_UNLOCK);
            player->GetSession()->SendNotification(msg.c_str());
        }
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 1:
    {
        if (player->GetActiveSpec() == 0)
        {
            player->CLOSE_GOSSIP_MENU();
            const std::string msg = player->GetSession()->GetMangosString(DUAL_SPEC_ALREADY_ON_SPEC);
            player->GetSession()->SendNotification(msg.c_str());
            GossipSelect_custom_dualspec(player, creature, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            break;
        }
        player->ActivateSpec(0);
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 2:
    {
        if (player->GetActiveSpec() == 1)
        {
            player->CLOSE_GOSSIP_MENU();
            const std::string msg = player->GetSession()->GetMangosString(DUAL_SPEC_ALREADY_ON_SPEC);
            player->GetSession()->SendNotification(msg.c_str());
            GossipSelect_custom_dualspec(player, creature, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
            break;
        }
        player->ActivateSpec(1);
        break;
    }
    case GOSSIP_ACTION_INFO_DEF + 5:
    {
        uint8 specCount = player->GetSpecsCount();
        for (uint8 i = 0; i < specCount; ++i)
        {
            std::stringstream specNameString;
            specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_ACTIVATE);
            if (player->GetSpecName(i) == "NULL")
                specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_UNNAMED);
            else
                specNameString << player->GetSpecName(i);
            if (i == player->GetActiveSpec())
                specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_ACTIVE);
            else
                specNameString << "";
            player->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (1 + i));
        }

        for (uint8 i = 0; i < specCount; ++i)
        {
            std::stringstream specNameString;
            specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_RENAME);
            if (player->GetSpecName(i) == "NULL")
                specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_UNNAMED);
            else
                specNameString << player->GetSpecName(i);
            if (i == player->GetActiveSpec())
                specNameString << player->GetSession()->GetMangosString(DUAL_SPEC_ACTIVE);
            else
                specNameString << "";
            player->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_TALK, specNameString.str(), GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + (10 + i), "", 0, true);
        }
        player->SEND_GOSSIP_MENU(TEXT_ID_CRYSTAL, creature->GetObjectGuid());
        break;
    }
    }
    return true;
}

bool GossipSelectWithCode_custom_dualspec(Player* player, Creature* creature, uint32 sender, uint32 action, const char* sCode)
{
    std::string strCode = sCode;
    CharacterDatabase.escape_string(strCode);

    if (action == GOSSIP_ACTION_INFO_DEF + 10)
        player->SetSpecName(0, strCode.c_str());
    else if (action == GOSSIP_ACTION_INFO_DEF + 11)
        player->SetSpecName(1, strCode.c_str());

    player->CLOSE_GOSSIP_MENU();
    GossipSelect_custom_dualspec(player, creature, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 5);
    return true;
}

void AddSC_npc_custom_dualspec()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_custom_dualspec";
    pNewScript->pGossipHello = &GossipHello_custom_dualspec;
    pNewScript->pGossipSelect = &GossipSelect_custom_dualspec;
    pNewScript->pGossipSelectWithCode = &GossipSelectWithCode_custom_dualspec;
    pNewScript->RegisterSelf();
}

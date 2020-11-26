#include "AI/ScriptDevAI/include/sc_common.h"
#include "Globals/SharedDefines.h"
#include <cstring>
#include <string>

bool GossipHello_welcome(Player* player, Creature* creature)
{
    if (player->getLevel() < 58)
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Set your level", 1, 1, "Max level 58", 0, true);

    if (player->getClass() == CLASS_WARRIOR)
    {
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get Arms stuff", 100+CLASS_WARRIOR, 0, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get Fury stuff", 100+CLASS_WARRIOR, 1, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get Protection stuff", 100+CLASS_WARRIOR, 2, "", 0, false);
    }
    else if (player->getClass() == CLASS_PALADIN)
    {
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get holy stuff", 100+CLASS_PALADIN, 0, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get retri stuff", 100+CLASS_PALADIN, 1, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get idk stuff", 100+CLASS_PALADIN, 2, "", 0, false);
    }
    else if (player->getClass() == CLASS_HUNTER)
    {
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get mm stuff", 100+CLASS_HUNTER, 0, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get survival stuff", 100+CLASS_HUNTER, 1, "", 0, false);
        player->PlayerTalkClass->GetGossipMenu().AddMenuItem(0, "Get bm stuff", 100+CLASS_HUNTER, 2, "", 0, false);
    }


    player->PlayerTalkClass->SendGossipMenu(123456, creature->GetObjectGuid()); // edit this text in database if you want some text

    return true;
}

bool GossipSelect_welcome(Player* player, Creature* creature, uint32 sender, uint32 action)
{
    if (sender == 100+CLASS_WARRIOR && 0) // Arms
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_WARRIOR && 1) // Fury
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_WARRIOR && 2) // Protection
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_PALADIN&& 0) // holy
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_PALADIN&& 1) // retri
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_PALADIN&& 2) // idk
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_HUNTER&& 0) // marksmanship
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_HUNTER&& 1) //survival
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    else if (sender == 100+CLASS_HUNTER&& 2) // beast mastery
    {
        player->StoreNewItemInBestSlots(123, 1);
        player->StoreNewItemInBestSlots(123, 1);
    }
    return true;
}

bool GossipSelectWithCode_welcomenpc(Player* player, Creature* creature, uint32 sender, uint32 action, const char* ccode)
{
    if (sender == 1 && action == 1)
    {
        std::string code = ccode;
        uint64 level = player->getLevel();
        bool error = false;
        try {
            level = std::stoll(code);
        } catch (...) {
            error = true;
        }
        if (level < player->getLevel() || level > 58 || error)
        {
            ChatHandler(player->GetSession()).PSendSysMessage("Invalid level");
            return true;
        }
        player->SetLevel(level);
    }
    return true;
}

void AddSC_welcomenpc()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "welcomenpc";
    pNewScript->pGossipHello = &GossipHello_welcome;
    pNewScript->pGossipSelect = &GossipSelect_welcome;
    pNewScript->pGossipSelectWithCode = &GossipSelectWithCode_welcomenpc;
    pNewScript->RegisterSelf(false);
}

#include "Config/Config.h"
#include "precompiled.h"
#include "system/system.h" // For SD Database
#include "PlayerStartMgr.h"

INSTANTIATE_SINGLETON_1(PlayerStartMgr);

PlayerStartMgr::PlayerStartMgr()
{
}

PlayerStartMgr::~PlayerStartMgr()
{
}

void PlayerStartMgr::load()
{
    spells.clear();
    equip.clear();

    // 1 - Spells
    QueryResult* result = SD2Database.Query(
                              "SELECT spell, class, race, reqLevel"
                              " FROM playerstart_spell ");
    if (result)
    {
        uint32 uiSpellCount = 0;

        do
        {
            Field* pFields = result->Fetch();

            PlayerStartSpell* pTemp = new PlayerStartSpell;

            pTemp->spellId   = pFields[0].GetUInt32();
            uint32 uiEntry          = uiSpellCount;//pTemp->spellId*1000+pFields[1].GetUInt32();
            pTemp->playerClass         = pFields[1].GetUInt32();
            pTemp->playerRace          = pFields[2].GetUInt32();
            pTemp->reqLevel            = pFields[3].GetUInt32();

            spells[uiEntry] = pTemp;
            ++uiSpellCount;
        }
        while (result->NextRow());

        delete result;

        outstring_log("");
        outstring_log(">> %u spells loaded", uiSpellCount);
    }
    else
    {
        outstring_log("");
        outstring_log(">> 0 spells loaded. DB table empty.");
    }

    // 2 - equipment
    QueryResult* resultEquip = SD2Database.Query(
                                   "SELECT item, slot, class"
                                   " FROM playerstart_equip ");
    if (resultEquip)
    {
        uint32 uiSpellCount = 0;

        do
        {
            Field* pFields = resultEquip->Fetch();

            PlayerStartEquip* pTemp = new PlayerStartEquip;

            pTemp->itemId   = pFields[0].GetUInt32();
            pTemp->equipmentSlot  = pFields[1].GetUInt8();
            pTemp->playerClass    = pFields[2].GetUInt8();
            uint32 uiEntry       = pTemp->itemId * 10000 + pTemp->equipmentSlot * 100 + pTemp->playerClass;

            equip[uiEntry] = pTemp;
            ++uiSpellCount;
        }
        while (resultEquip->NextRow());

        delete resultEquip;

        outstring_log("");
        outstring_log(">> %u equipment items loaded. DB Table empty.", uiSpellCount);
    }
    else
    {
        outstring_log("");
        outstring_log(">> 0 equipment items loaded. DB Table empty.");
    }
}

void PlayerStartMgr::AddItems(Player* player)
{
    std::map<uint32, PlayerStartEquip*>::const_iterator iterEquip;
    for (iterEquip = equip.begin(); iterEquip != equip.end(); ++iterEquip)
    {
        uint8 playerClass   = iterEquip->second->playerClass;
        uint32 itemId       = iterEquip->second->itemId;
        uint32 itemAmount   = iterEquip->second->itemAmount;
        uint8 equipmentSlot = iterEquip->second->equipmentSlot;

        if (player->getClass() != iterEquip->second->playerClass)
            continue;

        if (!player->GetItemByPos(INVENTORY_SLOT_BAG_0, iterEquip->second->equipmentSlot)
                && iterEquip->second->equipmentSlot <= 20)
        {
            // Free slot: equip item
            player->EquipNewItem(iterEquip->second->equipmentSlot, iterEquip->second->itemId, true);
        }
        else // Equipment slot not free. Add item to bag slot.
        {
            ItemPosCountVec dest;
            InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, iterEquip->second->itemId, 1);
            if (msg != 0)
                player->SendEquipError(msg, NULL, NULL);
            else if (Item* item = player->StoreNewItem(dest, iterEquip->second->itemId, true))
                player->SendNewItem(item, 1, true, false);
        }
    }
    player->SaveToDB();
}

void PlayerStartMgr::AddSpells(Player* player)
{
    std::map<uint32, PlayerStartSpell*>::const_iterator iter;
    for (iter = spells.begin(); iter != spells.end(); ++iter)
    {
        if (player->getClass() != iter->second->playerClass)
            continue;
        else if (player->getRace() != iter->second->playerRace && iter->second->playerRace)
            continue;
        else if (player->getLevel() < iter->second->reqLevel)
            continue;

        if (!player->HasSpell(iter->second->spellId))
            player->learnSpell(iter->second->spellId, false);
    }

    if (player->getClass() == CLASS_SHAMAN)
    {
        player->SetSkill(160, 300, 300);
        player->SetSkill(172, 300, 300);
    }
    else if (player->getClass() == CLASS_PRIEST)
    {
        switch (player->getRace())
        {
            case RACE_DWARF:
                player->learnSpell(19243, false);
                player->learnSpell(6346, false);
                break;
            case RACE_HUMAN:
                player->learnSpell(19243, false);
                player->learnSpell(19275, false);
                break;
            case RACE_NIGHTELF:
                player->learnSpell(19305, false);
                player->learnSpell(19293, false);
                break;
            case RACE_UNDEAD:
                player->learnSpell(19280, false);
                player->learnSpell(19266, false);
                break;
            case RACE_TROLL:
                player->learnSpell(19312, false);
                player->learnSpell(19285, false);
                break;
        }
    }
}

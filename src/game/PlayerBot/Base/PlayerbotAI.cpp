/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <stdarg.h>
#include "Common.h"
#include "Log.h"
#include "WorldPacket.h"
#include "Database/DatabaseEnv.h"
#include "PlayerbotAI.h"
#include "PlayerbotMgr.h"
#include "ProgressBar.h"

#include "../../AuctionHouse/AuctionHouseMgr.h"
#include "../../Chat/Chat.h"
#include "../../Entities/GossipDef.h"
#include "../../Entities/ItemPrototype.h"
#include "../../Entities/Player.h"
#include "../../Entities/Unit.h"
#include "../../Globals/SharedDefines.h"
#include "../../Globals/ObjectMgr.h"

#include "../../Grids/GridNotifiers.h"
#include "../../Grids/GridNotifiersImpl.h"
#include "../../Grids/CellImpl.h"
#include "../../Guilds/Guild.h"
#include "../../Guilds/GuildMgr.h"
#include "../../Loot/LootMgr.h"
#include "../../Mails/Mail.h"
#include "../../MotionGenerators/MotionMaster.h"
#include "../../Spells/Spell.h"
#include "../../Spells/SpellAuras.h"
#include "../../Spells/SpellMgr.h"
#include "../../Tools/Language.h"
#include "../../World/World.h"

#include "../AI/PlayerbotDruidAI.h"
#include "../AI/PlayerbotHunterAI.h"
#include "../AI/PlayerbotMageAI.h"
#include "../AI/PlayerbotPaladinAI.h"
#include "../AI/PlayerbotPriestAI.h"
#include "../AI/PlayerbotRogueAI.h"
#include "../AI/PlayerbotShamanAI.h"
#include "../AI/PlayerbotWarlockAI.h"
#include "../AI/PlayerbotWarriorAI.h"

#include <iomanip>
#include <iostream>

// returns a float in range of..
float rand_float(float low, float high)
{
    return (rand() / (static_cast<float>(RAND_MAX) + 1.0)) * (high - low) + low;
}

enum NPCFlags VENDOR_MASK = (enum NPCFlags)(UNIT_NPC_FLAG_VENDOR
                            | UNIT_NPC_FLAG_VENDOR_AMMO
                            | UNIT_NPC_FLAG_VENDOR_FOOD
                            | UNIT_NPC_FLAG_VENDOR_POISON
                            | UNIT_NPC_FLAG_VENDOR_REAGENT);

// ChatHandler already implements some useful commands the master can call on bots
// These commands are protected inside the ChatHandler class so this class provides access to the commands
// we'd like to call on our bots
class PlayerbotChatHandler : protected ChatHandler
{
    public:
        explicit PlayerbotChatHandler(Player* pMasterPlayer) : ChatHandler(pMasterPlayer) {}
        bool revive(Player& botPlayer) { return HandleReviveCommand((char*) botPlayer.GetName()); }
        bool teleport(Player& botPlayer) { return HandleNamegoCommand((char*) botPlayer.GetName()); }
        void sysmessage(const char* str) { SendSysMessage(str); }
        bool dropQuest(char* str) { return HandleQuestRemoveCommand(str); }
};

PlayerbotAI::PlayerbotAI(PlayerbotMgr* const mgr, Player* const bot) :
    m_mgr(mgr), m_bot(bot), m_classAI(0), m_ignoreAIUpdatesUntilTime(CurrentTime()),
    m_combatOrder(ORDERS_NONE), m_ScenarioType(SCENARIO_PVE),
    m_CurrentlyCastingSpellId(0), m_CraftSpellId(0), m_spellIdCommand(0),
    m_targetGuidCommand(ObjectGuid()),
    m_taxiMaster(ObjectGuid()),
    m_AutoEquipToggle(false),
    m_bDebugCommandChat(false),
    m_ignoreNeutralizeEffect(false)
{
    // set bot state
    m_botState = BOTSTATE_LOADING;

    // reset some pointers
    m_targetChanged = false;
    m_targetType = TARGET_NORMAL;
    m_targetCombat = 0;
    m_targetAssist = 0;
    m_targetProtect = 0;

    // set collection options
    m_collectionFlags = 0;
    m_collectDist = m_mgr->m_confCollectDistance;
    if (m_mgr->m_confCollectCombat)
        SetCollectFlag(COLLECT_FLAG_COMBAT);
    if (m_mgr->m_confCollectQuest)
        SetCollectFlag(COLLECT_FLAG_QUEST);
    if (m_mgr->m_confCollectProfession)
        SetCollectFlag(COLLECT_FLAG_PROFESSION);
    if (m_mgr->m_confCollectLoot)
        SetCollectFlag(COLLECT_FLAG_LOOT);
    if (m_mgr->m_confCollectSkin && m_bot->HasSkill(SKILL_SKINNING))
        SetCollectFlag(COLLECT_FLAG_SKIN);
    if (m_mgr->m_confCollectObjects)
        SetCollectFlag(COLLECT_FLAG_NEAROBJECT);

    // set needed item list
    SetQuestNeedItems();
    SetQuestNeedCreatures();

    // start following master (will also teleport bot to master)
    m_FollowAutoGo = FOLLOWAUTOGO_OFF; //turn on bot auto follow distance can be turned off by player
    DistOverRide = 0; //set initial adjustable follow settings
    IsUpOrDown = 0;
    gTempDist = 0.5f;
    gTempDist2 = 1.0f;
    SetMovementOrder(MOVEMENT_FOLLOW, GetMaster());
    BotDataRestore();
    m_DelayAttackInit = CurrentTime();

    // get class specific ai
    ReloadAI();
}

PlayerbotAI::~PlayerbotAI()
{
    if (m_classAI) delete m_classAI;
}

Player* PlayerbotAI::GetMaster() const
{
    return m_mgr->GetMaster();
}

bool PlayerbotAI::CanReachWithSpellAttack(Unit* target)
{
    bool inrange = false;
    float dist = m_bot->GetDistance(target, true, DIST_CALC_COMBAT_REACH_WITH_MELEE);

    for (SpellRanges::iterator itr = m_spellRangeMap.begin(); itr != m_spellRangeMap.end(); ++itr)
    {
        uint32 spellId = itr->first;

        // ignore positive spells
        if (IsPositiveSpell(spellId))
            continue;

        // ignore active auras
        if (target->HasAura(spellId, EFFECT_INDEX_0))
            continue;

        const SpellEntry* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!spellInfo)
            continue;

        // ignore non-ranged spells
        if (!spellInfo->HasAttribute(SPELL_ATTR_RANGED))
            continue;

        float maxrange = itr->second;

        // DEBUG_LOG("[%s] spell (%s) : dist (%f) < maxrange (%f)",m_bot->GetName(), spellInfo->SpellName[0], dist, maxrange);

        if (dist < maxrange)
        {
            inrange = true;
            break;
        }
    }
    return inrange;
}

bool PlayerbotAI::In_Reach(Unit* Target, uint32 spellId)
{
    if (!Target)
        return false;

    float range = 0;
    float dist = m_bot->GetDistance(Target, true, DIST_CALC_COMBAT_REACH_WITH_MELEE);
    SpellRanges::iterator it;
    it = m_spellRangeMap.find(spellId);
    (it != m_spellRangeMap.end()) ? range = it->second : range = 0;

    // DEBUG_LOG("spell (%u) : range (%f)", spellId, range);

    if (dist > range)
        return false;

    return true;
}

// finds spell ID for matching substring args
// in priority of full text match, spells not taking reagents, and highest rank
uint32 PlayerbotAI::getSpellId(const char* args, bool master) const
{
    if (!*args)
        return 0;

    std::string namepart = args;
    std::wstring wnamepart;

    if (!Utf8toWStr(namepart, wnamepart))
        return 0;

    // converting string that we try to find to lower case
    wstrToLower(wnamepart);

    int loc = 0;
    if (master)
        loc = GetMaster()->GetSession()->GetSessionDbcLocale();
    else
        loc = m_bot->GetSession()->GetSessionDbcLocale();

    uint32 foundSpellId = 0;
    bool foundExactMatch = false;
    bool foundMatchUsesNoReagents = false;

    for (PlayerSpellMap::iterator itr = m_bot->GetSpellMap().begin(); itr != m_bot->GetSpellMap().end(); ++itr)
    {
        uint32 spellId = itr->first;

        if (itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
            continue;

        const SpellEntry* pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!pSpellInfo)
            continue;

        const std::string name = pSpellInfo->SpellName[loc];
        if (name.empty() || !Utf8FitTo(name, wnamepart))
            continue;

        bool isExactMatch = (name.length() == wnamepart.length()) ? true : false;
        bool usesNoReagents = (pSpellInfo->Reagent[0] <= 0) ? true : false;

        // if we already found a spell
        bool useThisSpell = true;
        if (foundSpellId > 0)
        {
            if (isExactMatch && !foundExactMatch) {}
            else if (usesNoReagents && !foundMatchUsesNoReagents) {}
            else if (spellId > foundSpellId) {}
            else
                useThisSpell = false;
        }
        if (useThisSpell)
        {
            foundSpellId = spellId;
            foundExactMatch = isExactMatch;
            foundMatchUsesNoReagents = usesNoReagents;
        }
    }

    return foundSpellId;
}


uint32 PlayerbotAI::getPetSpellId(const char* args) const
{
    if (!*args)
        return 0;

    Pet* pet = m_bot->GetPet();
    if (!pet)
        return 0;

    std::string namepart = args;
    std::wstring wnamepart;

    if (!Utf8toWStr(namepart, wnamepart))
        return 0;

    // converting string that we try to find to lower case
    wstrToLower(wnamepart);

    int loc = GetMaster()->GetSession()->GetSessionDbcLocale();

    uint32 foundSpellId = 0;
    bool foundExactMatch = false;
    bool foundMatchUsesNoReagents = false;

    for (PetSpellMap::iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
    {
        uint32 spellId = itr->first;

        if (itr->second.state == PETSPELL_REMOVED || IsPassiveSpell(spellId))
            continue;

        const SpellEntry* pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!pSpellInfo)
            continue;

        const std::string name = pSpellInfo->SpellName[loc];
        if (name.empty() || !Utf8FitTo(name, wnamepart))
            continue;

        bool isExactMatch = (name.length() == wnamepart.length()) ? true : false;
        bool usesNoReagents = (pSpellInfo->Reagent[0] <= 0) ? true : false;

        // if we already found a spell
        bool useThisSpell = true;
        if (foundSpellId > 0)
        {
            if (isExactMatch && !foundExactMatch) {}
            else if (usesNoReagents && !foundMatchUsesNoReagents) {}
            else if (spellId > foundSpellId) {}
            else
                useThisSpell = false;
        }
        if (useThisSpell)
        {
            foundSpellId = spellId;
            foundExactMatch = isExactMatch;
            foundMatchUsesNoReagents = usesNoReagents;
        }
    }

    return foundSpellId;
}


uint32 PlayerbotAI::initSpell(uint32 spellId)
{
    // Check if bot knows this spell
    if (!m_bot->HasSpell(spellId))
        return 0;

    uint32 next = 0;
    SpellChainMapNext const& nextMap = sSpellMgr.GetSpellChainNext();
    for (SpellChainMapNext::const_iterator itr = nextMap.lower_bound(spellId); itr != nextMap.upper_bound(spellId); ++itr)
    {
        SpellChainNode const* node = sSpellMgr.GetSpellChainNode(itr->second);
        // If next spell is a requirement for this one then skip it
        if (node->req == spellId)
            continue;
        if (node->prev == spellId)
        {
            next = initSpell(itr->second);
            break;
        }
    }
    if (next == 0)
    {
        const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!pSpellInfo)
            return spellId;

        DEBUG_LOG("[PlayerbotAI]: initSpell - Playerbot spell init: %s is %u", pSpellInfo->SpellName[0], spellId);

        // Add spell to spellrange map
        Spell* spell = new Spell(m_bot, pSpellInfo, false);
        SpellRangeEntry const* srange = sSpellRangeStore.LookupEntry(pSpellInfo->rangeIndex);
        float range = GetSpellMaxRange(srange);
        if (Player* modOwner = m_bot->GetSpellModOwner())
            modOwner->ApplySpellMod(pSpellInfo->Id, SPELLMOD_RANGE, range, spell);
        m_spellRangeMap.insert(std::pair<uint32, float>(spellId, range));
        delete spell;
    }
    return (next == 0) ? spellId : next;
}


// Pet spells do not form chains like player spells.
// One of the options to initialize a spell is to use spell icon id
uint32 PlayerbotAI::initPetSpell(uint32 spellIconId)
{
    Pet* pet = m_bot->GetPet();

    if (!pet)
        return 0;

    for (PetSpellMap::iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
    {
        const uint32 spellId = itr->first;

        if (itr->second.state == PETSPELL_REMOVED || IsPassiveSpell(spellId))
            continue;

        const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!pSpellInfo)
            continue;

        if (pSpellInfo->SpellIconID == spellIconId)
            return spellId;
    }

    // Nothing found
    return 0;
}

/*
* Send list of the equipment in bot's inventory not currently equipped.
* This is called when the master is inspecting the bot.
*/
void PlayerbotAI::SendNotEquipList(Player& /*player*/)
{
    // find all unequipped items and put them in
    // a vector of dynamically created lists where the vector index is from 0-18
    // and the list contains Item* that can be equipped to that slot
    // Note: each dynamically created list in the vector must be deleted at end
    // so NO EARLY RETURNS!
    // see enum EquipmentSlots in Player.h to see what equipment slot each index in vector
    // is assigned to. (The first is EQUIPMENT_SLOT_HEAD=0, and last is EQUIPMENT_SLOT_TABARD=18)
    std::list<Item*>* equip[19];
    for (uint8 i = 0; i < 19; ++i)
        equip[i] = nullptr;

    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!pItem)
            continue;

        uint16 dest;
        InventoryResult msg = m_bot->CanEquipItem(NULL_SLOT, dest, pItem, !pItem->IsBag());
        if (msg != EQUIP_ERR_OK)
            continue;

        // the dest looks like it includes the old loc in the 8 higher bits
        // so casting it to a uint8 strips them
        int8 equipSlot = uint8(dest);
        if (!(equipSlot >= 0 && equipSlot < 19))
            continue;

        // create a list if one doesn't already exist
        if (equip[equipSlot] == nullptr)
            equip[equipSlot] = new std::list<Item*>;

        std::list<Item*>* itemListForEqSlot = equip[equipSlot];
        itemListForEqSlot->push_back(pItem);
    }

    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (!pItem)
                    continue;

                uint16 dest;
                InventoryResult msg = m_bot->CanEquipItem(NULL_SLOT, dest, pItem, !pItem->IsBag());
                if (msg != EQUIP_ERR_OK)
                    continue;

                int8 equipSlot = uint8(dest);
                if (!(equipSlot >= 0 && equipSlot < 19))
                    continue;

                // create a list if one doesn't already exist
                if (equip[equipSlot] == nullptr)
                    equip[equipSlot] = new std::list<Item*>;

                std::list<Item*>* itemListForEqSlot = equip[equipSlot];
                itemListForEqSlot->push_back(pItem);
            }
    }

    TellMaster("Here's all the items in my inventory that I can equip.");
    ChatHandler ch(GetMaster());

    const std::string descr[] = { "head", "neck", "shoulders", "body", "chest",
                                  "waist", "legs", "feet", "wrists", "hands", "finger1", "finger2",
                                  "trinket1", "trinket2", "back", "mainhand", "offhand", "ranged",
                                  "tabard"
                                };

    // now send client all items that can be equipped by slot
    for (uint8 equipSlot = 0; equipSlot < 19; ++equipSlot)
    {
        if (equip[equipSlot] == nullptr)
            continue;
        std::list<Item*>* itemListForEqSlot = equip[equipSlot];
        std::ostringstream out;
        out << descr[equipSlot] << ": ";
        for (std::list<Item*>::iterator it = itemListForEqSlot->begin(); it != itemListForEqSlot->end(); ++it)
            if ((*it))
                MakeItemLink((*it), out, true);
        ch.SendSysMessage(out.str().c_str());

        delete itemListForEqSlot; // delete list of Item*
    }
}

void PlayerbotAI::FollowAutoReset()
{
    if (m_FollowAutoGo != FOLLOWAUTOGO_OFF)
    {
        m_FollowAutoGo = FOLLOWAUTOGO_RESET;
        SetMovementOrder(MOVEMENT_FOLLOW, GetMaster());
        WorldObject* distTarget = m_followTarget;
        for (uint8 i = 0; i < 1; ++i)
        {
            if (m_bot->GetDistance(distTarget) < 3.0f)
                i = 1;
            else
                i = 0;
        }
    }
}

void PlayerbotAI::AutoUpgradeEquipment() // test for autoequip
{
    if (!m_AutoEquipToggle)
        return;

    ChatHandler ch(GetMaster());
    std::ostringstream out;
    std::ostringstream msg;

    // Find equippable items in main backpack one at a time
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);

        if (!pItem)
            continue;

        uint32 spellId = 0;

        for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            if (pItem->GetProto()->Spells[i].SpellId > 0)
            {
                spellId = pItem->GetProto()->Spells[i].SpellId;
                break;
            }
        }

        if (pItem->GetProto()->Flags & ITEM_FLAG_HAS_LOOT && spellId == 0)
        {
            std::string oops = "Oh... Look! Theres something inside!!!";
            m_bot->Say(oops, LANG_UNIVERSAL);
            UseItem(pItem);
            continue;
        }

        if (uint32 questid = pItem->GetProto()->StartQuest)
        {
            Quest const* qInfo = sObjectMgr.GetQuestTemplate(questid);
            if (m_bot->GetQuestStatus(questid) == QUEST_STATUS_COMPLETE)
                continue;
            else if (!m_bot->CanTakeQuest(qInfo, false))
            {
                std::string oops = "Great, more junk... Can I get rid of this please?";
                m_bot->Say(oops, LANG_UNIVERSAL);
                continue;
            }

            UseItem(pItem);
        }

        uint16 equipSlot;
        InventoryResult msg = m_bot->CanEquipItem(NULL_SLOT, equipSlot, pItem, !pItem->IsBag());
        if (msg != EQUIP_ERR_OK)
            continue;

        // do we have anything equipped of this type?
        Item* const pItem2 = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, (uint8)equipSlot);
        if (!pItem2) // no item to compare to see if has stats useful for this bots class/style so check for stats and equip if possible
        {
            ItemPrototype const* pProto2 = pItem->GetProto();
            if (ItemStatsCount(pProto2) > 0)
            {
                if (!ItemStatComparison(pProto2, pProto2))
                    continue;
            }
            EquipItem(pItem); // no item equipped so equip new one and go to next item.
            continue;
        }

        // we have an equippable item, so lets send it to the comparison function to see if it's better than we have on
        AutoEquipComparison(pItem, pItem2); // pItem is new item, pItem2 is equipped item.
    }

    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (!pItem)
                    continue;

                uint16 dest;
                InventoryResult msg = m_bot->CanEquipItem(NULL_SLOT, dest, pItem, !pItem->IsBag());
                if (msg != EQUIP_ERR_OK)
                    continue;

                uint8 equipSlot = uint8(dest);
                Item* const pItem2 = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, equipSlot); // do we have anything equipped of this type?
                if (!pItem2)
                {
                    ItemPrototype const* pProto2 = pItem->GetProto();
                    if (ItemStatsCount(pProto2) > 0)
                    {
                        if (!ItemStatComparison(pProto2, pProto2))
                            continue;
                    }

                    EquipItem(pItem); //no item equipped so equip new one if useable stats and go to next item.
                    continue;
                }

                // we have an equippable item but something else is equipped so lets send it to the comparison function to see if it's better than we have on
                AutoEquipComparison(pItem, pItem2); //pItem is new item, pItem2 is equipped item.
            }
    }
}

uint32 PlayerbotAI::ItemStatsCount(ItemPrototype const* proto)
{
    uint32 count = 0;

    for (int i = 0; i < MAX_ITEM_PROTO_STATS; ++i)
        if (proto && (proto->ItemStat[i].ItemStatType || proto->ItemStat[i].ItemStatValue))
            count++;

    return count;
}

float PlayerbotAI::getItemDPS(ItemPrototype const* proto) const
{
    if (proto->Delay == 0)
        return 0;
    float temp = 0;
    for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES; ++i)
        temp += proto->Damage[i].DamageMin + proto->Damage[i].DamageMax;
    return temp * 500 / proto->Delay;
}

void PlayerbotAI::AutoEquipComparison(Item* pItem, Item* pItem2)
{
    const static uint32 item_armor_skills[MAX_ITEM_SUBCLASS_ARMOR] =
    {
        0, SKILL_CLOTH, SKILL_LEATHER, SKILL_MAIL, SKILL_PLATE_MAIL, 0, SKILL_SHIELD, 0, 0, 0
    };
    ItemPrototype const* pProto = pItem2->GetProto(); // equipped item if any
    ItemPrototype const* pProto2 = pItem->GetProto(); // new item to compare
    // DEBUG_LOG("Item Class (%s)",(pProto->Class == ITEM_CLASS_WEAPON ? "Weapon" : "Not Weapon"));
    switch (pProto->Class)
    {
        case ITEM_CLASS_WEAPON:
        {
            // DEBUG_LOG("Current Item DPS (%f) Equippable Item DPS (%f)",getItemDPS(pProto),getItemDPS(pProto2));
            // m_bot->GetSkillValue(pProto->RequiredSkill) < m_bot->GetSkillValue(pProto2->RequiredSkill)
            if (getItemDPS(pProto) < getItemDPS(pProto2))   // if new item has a better DPS
            {
                EquipItem(pItem);
                pProto = pProto2; // ensure that the item with the highest DPS is equipped
            }
            break;
        }
        case ITEM_CLASS_ARMOR:
        {
            // now in case they are same itemlevel, but one is better than the other..
            if (pProto->ItemLevel == pProto2->ItemLevel && pProto->Quality < pProto2->Quality && pProto->Armor <= pProto2->Armor &&
                    m_bot->HasSkill(item_armor_skills[pProto2->SubClass]) && !m_bot->HasSkill(item_armor_skills[pProto2->SubClass + 1])) // itemlevel + armour + armour class
            {
                // First check to see if this item has stats, and if the bot REALLY wants to lose its old item
                if (ItemStatsCount(pProto2) > 0)
                {
                    if (!ItemStatComparison(pProto, pProto2))
                        return; // stats on equipped item are better, OR stats are not useful for this bots class/style
                }
                EquipItem(pItem);
                break;
            }
            if (pProto->ItemLevel <= pProto2->ItemLevel && pProto->Quality < pProto2->Quality && pProto->Armor > pProto2->Armor &&
                    m_bot->HasSkill(item_armor_skills[pProto2->SubClass]) && !m_bot->HasSkill(item_armor_skills[pProto2->SubClass + 1])) // itemlevel + armour + armour class
            {
                // First check to see if this item has stats, and if the bot REALLY wants to lose its old item
                if (ItemStatsCount(pProto2) > 0)
                {
                    if (!ItemStatComparison(pProto, pProto2))
                        return; // stats on equipped item are better, OR stats are not useful for this bots class/style
                }
                EquipItem(pItem);
                break;
            }
            if (pProto->ItemLevel <= pProto2->ItemLevel && pProto->Armor <= pProto2->Armor && m_bot->HasSkill(item_armor_skills[pProto2->SubClass]) &&
                    !m_bot->HasSkill(item_armor_skills[pProto2->SubClass + 1])) // itemlevel + armour + armour class
            {
                // First check to see if this item has stats, and if the bot REALLY wants to lose its old item
                if (ItemStatsCount(pProto2) > 0)
                {
                    if (!ItemStatComparison(pProto, pProto2))
                        return; // stats on equipped item are better, OR stats are not useful for this bots class/style
                }
                EquipItem(pItem);
                break;
            }
        }
    }
}

bool PlayerbotAI::ItemStatComparison(const ItemPrototype* pProto, const ItemPrototype* pProto2)
{
    uint8 isclass = 0; // 1= caster 2 = hybrid 3 = melee
    uint8 ishybrid = 0;
    uint8 olditemscore = 0;
    uint8 newitemscore = 0;
    // get class and style to make it easier to compare later
    switch (m_bot->getClass())
    {
        case CLASS_PRIEST:
        case CLASS_MAGE:
        case CLASS_WARLOCK:
            isclass = 1;
            break;

        case CLASS_PALADIN:
        case CLASS_SHAMAN:
        case CLASS_DRUID:
            isclass = 2;
            ishybrid = 1;
            break;

        case CLASS_WARRIOR:
        case CLASS_ROGUE:
            isclass = 3; // melee
            break;

        case CLASS_HUNTER:
            isclass = 2;
            ishybrid = 2;
            break;
    }

    for (int i = 0; i < MAX_ITEM_PROTO_STATS; ++i) // item can only have 10 stats. We check each stat slot available for stat and type.
    {
        uint32 itemmod = pProto->ItemStat[i].ItemStatType; // equipped item stats if any
        uint32 itemmod2 = pProto2->ItemStat[i].ItemStatType; // newitem stats
        if (!itemmod) // if no stat type in this slot, continue to next slot
        {
            if (!itemmod2)
                continue;
        }
        // caster stats
        if (itemmod == ITEM_MOD_MANA || itemmod == ITEM_MOD_INTELLECT || itemmod == ITEM_MOD_SPIRIT || itemmod == ITEM_MOD_HIT_SPELL_RATING ||
                itemmod == ITEM_MOD_CRIT_SPELL_RATING || itemmod == ITEM_MOD_HASTE_SPELL_RATING ||
                itemmod2 == ITEM_MOD_MANA || itemmod2 == ITEM_MOD_INTELLECT || itemmod2 == ITEM_MOD_SPIRIT || itemmod2 == ITEM_MOD_HIT_SPELL_RATING ||
                itemmod2 == ITEM_MOD_CRIT_SPELL_RATING || itemmod2 == ITEM_MOD_HASTE_SPELL_RATING)
        {
            switch (isclass) // 1 caster, 2 hybrid, 3 melee
            {
                case 1:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                case 2:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (ishybrid != 2) //not a hunter
                    {
                        if (itemmod == itemmod2) //same stat type
                        {
                            if (pProto == pProto2) // same item
                            {
                                if (olditemscore > 0)
                                    olditemscore = (olditemscore - 1);
                                newitemscore = (newitemscore + 1);
                            }
                            if (itemmodval < itemmodval2) // which one has the most
                            {
                                if (olditemscore > 0)
                                    olditemscore = (olditemscore - 1);
                                newitemscore = (newitemscore + 1);
                            }
                            else if (itemmodval > itemmodval2)
                            {
                                if (newitemscore > 0)
                                    newitemscore = (newitemscore - 1);
                                olditemscore = (olditemscore + 1);
                            }
                        }
                        else
                        {
                            if (itemmod > 0)
                                olditemscore = (olditemscore + 1);
                            if (itemmod2 > 0)
                                newitemscore = (newitemscore + 1);
                        }
                    }
                    else //is a hunter
                    {
                        if (itemmod > 0)
                        {
                            if (olditemscore > 0) //we dont want any negative returns
                                olditemscore = (olditemscore - 1);
                        }
                        if (itemmod2 > 0)
                        {
                            if (newitemscore > 0) //we dont want any negative returns
                                newitemscore = (newitemscore - 1);
                        }
                    }
                    break;
                }  // pure melee need nothing from this list.
                case 3:
                {
                    if (itemmod > 0)
                    {
                        if (olditemscore > 0) //we dont want any negative returns
                            olditemscore = (olditemscore - 1);
                    }
                    if (itemmod2 > 0)
                    {
                        if (newitemscore > 0) //we dont want any negative returns
                            newitemscore = (newitemscore - 1);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        // melee only stats (warrior/rogue) or stats that only apply to melee style combat
        if (itemmod == ITEM_MOD_HEALTH || itemmod == ITEM_MOD_AGILITY || itemmod == ITEM_MOD_STRENGTH ||
                itemmod == ITEM_MOD_DEFENSE_SKILL_RATING || itemmod == ITEM_MOD_DODGE_RATING || itemmod == ITEM_MOD_PARRY_RATING ||
                itemmod == ITEM_MOD_BLOCK_RATING || itemmod == ITEM_MOD_HIT_MELEE_RATING || itemmod == ITEM_MOD_CRIT_MELEE_RATING ||
                itemmod == ITEM_MOD_HIT_TAKEN_MELEE_RATING || itemmod == ITEM_MOD_HIT_TAKEN_RANGED_RATING || itemmod == ITEM_MOD_HIT_TAKEN_SPELL_RATING ||
                itemmod == ITEM_MOD_CRIT_TAKEN_MELEE_RATING || itemmod == ITEM_MOD_CRIT_TAKEN_RANGED_RATING ||
                itemmod == ITEM_MOD_CRIT_TAKEN_SPELL_RATING || itemmod == ITEM_MOD_HASTE_MELEE_RATING ||
                itemmod == ITEM_MOD_HIT_TAKEN_RATING || itemmod == ITEM_MOD_CRIT_TAKEN_RATING ||
                itemmod2 == ITEM_MOD_HEALTH || itemmod2 == ITEM_MOD_AGILITY || itemmod2 == ITEM_MOD_STRENGTH ||
                itemmod2 == ITEM_MOD_DEFENSE_SKILL_RATING || itemmod2 == ITEM_MOD_DODGE_RATING || itemmod2 == ITEM_MOD_PARRY_RATING ||
                itemmod2 == ITEM_MOD_BLOCK_RATING || itemmod2 == ITEM_MOD_HIT_MELEE_RATING || itemmod2 == ITEM_MOD_CRIT_MELEE_RATING ||
                itemmod2 == ITEM_MOD_HIT_TAKEN_MELEE_RATING || itemmod2 == ITEM_MOD_HIT_TAKEN_RANGED_RATING || itemmod2 == ITEM_MOD_HIT_TAKEN_SPELL_RATING ||
                itemmod2 == ITEM_MOD_CRIT_TAKEN_MELEE_RATING || itemmod2 == ITEM_MOD_CRIT_TAKEN_RANGED_RATING ||
                itemmod2 == ITEM_MOD_CRIT_TAKEN_SPELL_RATING || itemmod2 == ITEM_MOD_HASTE_MELEE_RATING ||
                itemmod2 == ITEM_MOD_HIT_TAKEN_RATING || itemmod2 == ITEM_MOD_CRIT_TAKEN_RATING)
        {
            switch (isclass) // 1 caster, 2 hybrid, 3 melee
            {
                case 1:
                {
                    if (itemmod > 0)
                    {
                        if (olditemscore > 0) //we dont want any negative returns
                            olditemscore = (olditemscore - 1);
                    }
                    if (itemmod2 > 0)
                    {
                        if (newitemscore > 0) //we dont want any negative returns
                            newitemscore = (newitemscore - 1);
                    }
                    break;
                }
                case 2:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                case 3:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        // stats which aren't strictly caster or melee (hybrid perhaps or style dependant)
        if (itemmod == ITEM_MOD_HIT_RATING || itemmod == ITEM_MOD_CRIT_RATING || itemmod == ITEM_MOD_RESILIENCE_RATING ||
                itemmod == ITEM_MOD_HASTE_RATING || itemmod == ITEM_MOD_EXPERTISE_RATING || itemmod == ITEM_MOD_STAMINA ||
                itemmod2 == ITEM_MOD_HIT_RATING || itemmod2 == ITEM_MOD_CRIT_RATING || itemmod2 == ITEM_MOD_RESILIENCE_RATING ||
                itemmod2 == ITEM_MOD_HASTE_RATING || itemmod2 == ITEM_MOD_EXPERTISE_RATING || itemmod2 == ITEM_MOD_STAMINA)
        {
            switch (isclass) // 1 caster, 2 hybrid, 3 melee
            {
                case 1:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                case 2:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                case 3:
                {
                    uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                    uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                    if (itemmod == itemmod2) //same stat type
                    {
                        if (pProto == pProto2) // same item
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        if (itemmodval < itemmodval2) // which one has the most
                        {
                            if (olditemscore > 0)
                                olditemscore = (olditemscore - 1);
                            newitemscore = (newitemscore + 1);
                        }
                        else if (itemmodval > itemmodval2)
                        {
                            if (newitemscore > 0)
                                newitemscore = (newitemscore - 1);
                            olditemscore = (olditemscore + 1);
                        }
                    }
                    else
                    {
                        if (itemmod > 0)
                            olditemscore = (olditemscore + 1);
                        if (itemmod2 > 0)
                            newitemscore = (newitemscore + 1);
                    }
                    break;
                }
                default:
                    break;
            }
        }
        // stats relating to ranged only
        if (itemmod == ITEM_MOD_HIT_RANGED_RATING || itemmod == ITEM_MOD_CRIT_RANGED_RATING || itemmod == ITEM_MOD_HASTE_RANGED_RATING ||
                itemmod2 == ITEM_MOD_HIT_RANGED_RATING || itemmod2 == ITEM_MOD_CRIT_RANGED_RATING || itemmod2 == ITEM_MOD_HASTE_RANGED_RATING)
        {
            switch (isclass) // 1 caster, 2 hybrid, 3 melee
            {
                case 1:
                {
                    if (itemmod > 0)
                    {
                        if (olditemscore > 0) //we dont want any negative returns
                            olditemscore = (olditemscore - 1);
                    }
                    if (itemmod2 > 0)
                    {
                        if (newitemscore > 0) //we dont want any negative returns
                            newitemscore = (newitemscore - 1);
                    }
                    break;
                }
                case 2:
                {
                    if (ishybrid != 2) //not a hunter
                    {
                        if (itemmod > 0)
                        {
                            if (olditemscore > 0) //we dont want any negative returns
                                olditemscore = (olditemscore - 1);
                        }
                        if (itemmod2 > 0)
                        {
                            if (newitemscore > 0) //we dont want any negative returns
                                newitemscore = (newitemscore - 1);
                        }
                    }
                    else //is a hunter
                    {
                        uint32 itemmodval = pProto->ItemStat[i].ItemStatValue; // equipped item stats if any
                        uint32 itemmodval2 = pProto2->ItemStat[i].ItemStatValue;  // newitem stats
                        if (itemmod == itemmod2) //same stat type
                        {
                            if (pProto == pProto2) // same item
                            {
                                if (olditemscore > 0)
                                    olditemscore = (olditemscore - 1);
                                newitemscore = (newitemscore + 1);
                            }
                            if (itemmodval < itemmodval2) // which one has the most
                            {
                                if (olditemscore > 0)
                                    olditemscore = (olditemscore - 1);
                                newitemscore = (newitemscore + 1);
                            }
                            else if (itemmodval > itemmodval2)
                            {
                                if (newitemscore > 0)
                                    newitemscore = (newitemscore - 1);
                                olditemscore = (olditemscore + 1);
                            }
                        }
                        else
                        {
                            if (itemmod > 0)
                                olditemscore = (olditemscore + 1);
                            if (itemmod2 > 0)
                                newitemscore = (newitemscore + 1);
                        }
                    }
                    break;
                }
                case 3:
                {
                    if (itemmod > 0)
                    {
                        if (olditemscore > 0) //we dont want any negative returns
                            olditemscore = (olditemscore - 1);
                    }
                    if (itemmod2 > 0)
                    {
                        if (newitemscore > 0) //we dont want any negative returns
                            newitemscore = (newitemscore - 1);
                    }
                    break;
                }
                default:
                    break;
            }
        }
    }
    if (olditemscore <= newitemscore)
        return true;
    else
        return false;
}

void PlayerbotAI::SendQuestNeedList()
{
    std::ostringstream out;

    for (BotNeedItem::iterator itr = m_needItemList.begin(); itr != m_needItemList.end(); ++itr)
    {
        ItemPrototype const* pItemProto = sObjectMgr.GetItemPrototype(itr->first);
        if (pItemProto)
        {
            std::string itemName = pItemProto->Name1;
            ItemLocalization(itemName, pItemProto->ItemId);

            out << " " << itr->second << "x|cffffffff|Hitem:" << pItemProto->ItemId
                << ":0:0:0:0:0:0:0" << "|h[" << itemName
                << "]|h|r";
        }
    }

    for (BotNeedItem::iterator itr = m_needCreatureOrGOList.begin(); itr != m_needCreatureOrGOList.end(); ++itr)
    {
        CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(itr->first);
        if (cInfo)
        {
            std::string creatureName = cInfo->Name;
            CreatureLocalization(creatureName, cInfo->Entry);
            out << " " << itr->second << "x|cFFFFFF00|Hcreature_entry:" << itr->first << "|h[" << creatureName << "]|h|r";
        }

        if (m_bot->HasQuestForGO(itr->first))
        {
            GameObjectInfo const* gInfo = ObjectMgr::GetGameObjectInfo(itr->first);
            if (gInfo)
            {
                std::string gameobjectName = gInfo->name;
                GameObjectLocalization(gameobjectName, gInfo->id);
                out << " " << itr->second << "x|cFFFFFF00|Hgameobject_entry:" << itr->first << "|h[" << gameobjectName << "]|h|r";
            }
        }
    }

    TellMaster("Here's a list of all things needed for quests:");
    if (!out.str().empty())
        TellMaster(out.str().c_str());
}

bool PlayerbotAI::IsItemUseful(uint32 itemid)
{
    const static uint32 item_weapon_skills[MAX_ITEM_SUBCLASS_WEAPON] =
    {
        SKILL_AXES,     SKILL_2H_AXES,  SKILL_BOWS,          SKILL_GUNS,      SKILL_MACES,
        SKILL_2H_MACES, SKILL_POLEARMS, SKILL_SWORDS,        SKILL_2H_SWORDS, 0,
        SKILL_STAVES,   0,              0,                   SKILL_UNARMED,   0,
        SKILL_DAGGERS,  SKILL_THROWN,   SKILL_ASSASSINATION, SKILL_CROSSBOWS, SKILL_WANDS,
        SKILL_FISHING
    };

    const static uint32 item_armor_skills[MAX_ITEM_SUBCLASS_ARMOR] =
    {
        0, SKILL_CLOTH, SKILL_LEATHER, SKILL_MAIL, SKILL_PLATE_MAIL, 0, SKILL_SHIELD, 0, 0, 0
    };

    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(itemid);
    if (!pProto || pProto->Quality < ITEM_QUALITY_NORMAL)
        return false;

    // do we already have the max allowed of item if more than zero?
    if (pProto->MaxCount > 0 && m_bot->HasItemCount(itemid, pProto->MaxCount, true))
        return false;

    // quest related items
    if (pProto->StartQuest > 0 && HasCollectFlag(COLLECT_FLAG_QUEST))
        return true;

    switch (pProto->Class)
    {
        case ITEM_CLASS_WEAPON:
            if (pProto->SubClass >= MAX_ITEM_SUBCLASS_WEAPON)
                return false;
            else
                return m_bot->HasSkill(item_weapon_skills[pProto->SubClass]);
            break;
        case ITEM_CLASS_ARMOR:
            if (pProto->SubClass >= MAX_ITEM_SUBCLASS_ARMOR)
                return false;
            else
                return (m_bot->HasSkill(item_armor_skills[pProto->SubClass]) && !m_bot->HasSkill(item_armor_skills[pProto->SubClass + 1]));
            break;
        case ITEM_CLASS_QUEST:
            if (!HasCollectFlag(COLLECT_FLAG_QUEST))
                break;
        case ITEM_CLASS_KEY:
            return true;
        case ITEM_CLASS_GEM:
            if (m_bot->HasSkill(SKILL_BLACKSMITHING) ||
                    m_bot->HasSkill(SKILL_ENGINEERING) ||
                    m_bot->HasSkill(SKILL_JEWELCRAFTING))
                return true;
            break;
        case ITEM_CLASS_TRADE_GOODS:
            if (!HasCollectFlag(COLLECT_FLAG_PROFESSION))
                break;

            switch (pProto->SubClass)
            {
                case ITEM_SUBCLASS_PARTS:
                case ITEM_SUBCLASS_EXPLOSIVES:
                case ITEM_SUBCLASS_DEVICES:
                    if (m_bot->HasSkill(SKILL_ENGINEERING))
                        return true;
                    break;
                case ITEM_SUBCLASS_JEWELCRAFTING:
                    if (m_bot->HasSkill(SKILL_JEWELCRAFTING))
                        return true;
                    break;
                case ITEM_SUBCLASS_CLOTH:
                    if (m_bot->HasSkill(SKILL_TAILORING))
                        return true;
                    break;
                case ITEM_SUBCLASS_LEATHER:
                    if (m_bot->HasSkill(SKILL_LEATHERWORKING))
                        return true;
                    break;
                case ITEM_SUBCLASS_METAL_STONE:
                    if (m_bot->HasSkill(SKILL_BLACKSMITHING) ||
                            m_bot->HasSkill(SKILL_ENGINEERING) ||
                            m_bot->HasSkill(SKILL_MINING))
                        return true;
                    break;
                case ITEM_SUBCLASS_MEAT:
                    if (m_bot->HasSkill(SKILL_COOKING))
                        return true;
                    break;
                case ITEM_SUBCLASS_HERB:
                    if (m_bot->HasSkill(SKILL_HERBALISM) ||
                            m_bot->HasSkill(SKILL_ALCHEMY))
                        return true;
                    break;
                case ITEM_SUBCLASS_ELEMENTAL:
                    return true;    // pretty much every profession uses these a bit
                case ITEM_SUBCLASS_ENCHANTING:
                    if (m_bot->HasSkill(SKILL_ENCHANTING))
                        return true;
                    break;
                default:
                    break;
            }
            break;
        case ITEM_CLASS_RECIPE:
        {
            if (!HasCollectFlag(COLLECT_FLAG_PROFESSION))
                break;

            // skip recipes that we have
            if (m_bot->HasSpell(pProto->Spells[2].SpellId))
                break;

            switch (pProto->SubClass)
            {
                case ITEM_SUBCLASS_LEATHERWORKING_PATTERN:
                    if (m_bot->HasSkill(SKILL_LEATHERWORKING))
                        return true;
                    break;
                case ITEM_SUBCLASS_TAILORING_PATTERN:
                    if (m_bot->HasSkill(SKILL_TAILORING))
                        return true;
                    break;
                case ITEM_SUBCLASS_ENGINEERING_SCHEMATIC:
                    if (m_bot->HasSkill(SKILL_ENGINEERING))
                        return true;
                    break;
                case ITEM_SUBCLASS_BLACKSMITHING:
                    if (m_bot->HasSkill(SKILL_BLACKSMITHING))
                        return true;
                    break;
                case ITEM_SUBCLASS_COOKING_RECIPE:
                    if (m_bot->HasSkill(SKILL_COOKING))
                        return true;
                    break;
                case ITEM_SUBCLASS_ALCHEMY_RECIPE:
                    if (m_bot->HasSkill(SKILL_ALCHEMY))
                        return true;
                    break;
                case ITEM_SUBCLASS_FIRST_AID_MANUAL:
                    if (m_bot->HasSkill(SKILL_FIRST_AID))
                        return true;
                    break;
                case ITEM_SUBCLASS_ENCHANTING_FORMULA:
                    if (m_bot->HasSkill(SKILL_ENCHANTING))
                        return true;
                    break;
                case ITEM_SUBCLASS_FISHING_MANUAL:
                    if (m_bot->HasSkill(SKILL_FISHING))
                        return true;
                    break;
                case ITEM_SUBCLASS_JEWELCRAFTING_RECIPE:
                    if (m_bot->HasSkill(SKILL_JEWELCRAFTING))
                        return true;
                    break;
                default:
                    break;
            }
        }
        default:
            break;
    }
    return false;
}

void PlayerbotAI::ReloadAI()
{
    switch (m_bot->getClass())
    {
        case CLASS_PRIEST:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_RANGED;
            m_classAI = (PlayerbotClassAI*) new PlayerbotPriestAI(GetMaster(), m_bot, this);
            break;
        case CLASS_MAGE:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_RANGED;
            m_classAI = (PlayerbotClassAI*) new PlayerbotMageAI(GetMaster(), m_bot, this);
            break;
        case CLASS_WARLOCK:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_RANGED;
            m_classAI = (PlayerbotClassAI*) new PlayerbotWarlockAI(GetMaster(), m_bot, this);
            break;
        case CLASS_WARRIOR:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_MELEE;
            m_classAI = (PlayerbotClassAI*) new PlayerbotWarriorAI(GetMaster(), m_bot, this);
            break;
        case CLASS_SHAMAN:
            if (m_classAI) delete m_classAI;
            if (m_bot->GetSpec() == SHAMAN_SPEC_ENHANCEMENT)
            {
                m_combatStyle = COMBAT_MELEE;
            }
            else
                m_combatStyle = COMBAT_RANGED;            m_classAI = (PlayerbotClassAI*) new PlayerbotShamanAI(GetMaster(), m_bot, this);
            break;
        case CLASS_PALADIN:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_MELEE;
            m_classAI = (PlayerbotClassAI*) new PlayerbotPaladinAI(GetMaster(), m_bot, this);
            break;
        case CLASS_ROGUE:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_MELEE;
            m_classAI = (PlayerbotClassAI*) new PlayerbotRogueAI(GetMaster(), m_bot, this);
            break;
        case CLASS_DRUID:
            if (m_classAI) delete m_classAI;
            if (m_bot->GetSpec() == DRUID_SPEC_FERAL)
            {
                m_combatStyle = COMBAT_MELEE;
            }
            else
                m_combatStyle = COMBAT_RANGED;
            m_classAI = (PlayerbotClassAI*) new PlayerbotDruidAI(GetMaster(), m_bot, this);
            break;
        case CLASS_HUNTER:
            if (m_classAI) delete m_classAI;
            m_combatStyle = COMBAT_RANGED;
            m_classAI = (PlayerbotClassAI*) new PlayerbotHunterAI(GetMaster(), m_bot, this);
            break;
    }

    HERB_GATHERING      = initSpell(HERB_GATHERING_1);
    MINING              = initSpell(MINING_1);
    SKINNING            = initSpell(SKINNING_1);
}

void PlayerbotAI::SendOrders(Player& /*player*/)
{
    std::ostringstream out;

    if (!m_combatOrder)
        out << "Got no combat orders!";
    else if (m_combatOrder & ORDERS_TANK)
        out << "I TANK";
    else if (m_combatOrder & ORDERS_MAIN_TANK)
        out << "I MAIN TANK";
    else if (m_combatOrder & ORDERS_ASSIST)
        out << "I ASSIST " << (m_targetAssist ? m_targetAssist->GetName() : "unknown");
    else if (m_combatOrder & ORDERS_HEAL)
        out << "I HEAL and DISPEL";
    else if (m_combatOrder & ORDERS_MAIN_HEAL)
        out << "I MAIN HEAL and DISPEL";
    else if (m_combatOrder & ORDERS_NODISPEL)
        out << "I HEAL and WON'T DISPEL";
    else if (m_combatOrder & ORDERS_PASSIVE)
        out << "I'm PASSIVE";
    if ((m_combatOrder & ORDERS_PRIMARY) && (m_combatOrder & (ORDERS_PROTECT | ORDERS_RESIST)))
    {
        out << " and ";
        if (m_combatOrder & ORDERS_PROTECT)
            out << "I PROTECT " << (m_targetProtect ? m_targetProtect->GetName() : "unknown");
        if (m_combatOrder & ORDERS_RESIST)
        {
            if (m_combatOrder & ORDERS_RESIST_FIRE)
                out << "I RESIST FIRE";
            if (m_combatOrder & ORDERS_RESIST_NATURE)
                out << "I RESIST NATURE";
            if (m_combatOrder & ORDERS_RESIST_FROST)
                out << "I RESIST FROST";
            if (m_combatOrder & ORDERS_RESIST_SHADOW)
                out << "I RESIST SHADOW";
        }
    }
    out << ".";

    if (m_mgr->m_confDebugWhisper)
    {
        out << " " << (IsInCombat() ? "I'm in COMBAT! " : "Not in combat. ");
        out << "Current state is ";
        if (m_botState == BOTSTATE_NORMAL)
            out << "NORMAL";
        else if (m_botState == BOTSTATE_COMBAT)
            out << "COMBAT";
        else if (m_botState == BOTSTATE_TAME)
            out << "TAMING";
        else if (m_botState == BOTSTATE_DEAD)
            out << "DEAD";
        else if (m_botState == BOTSTATE_DEADRELEASED)
            out << "RELEASED";
        else if (m_botState == BOTSTATE_LOOTING)
            out << "LOOTING";
        else if (m_botState == BOTSTATE_FLYING)
            out << "FLYING";
        out << ". Movement order is ";
        if (m_movementOrder == MOVEMENT_NONE)
            out << "NONE";
        else if (m_movementOrder == MOVEMENT_FOLLOW)
            out << "FOLLOW " << (m_followTarget ? m_followTarget->GetName() : "unknown");
        else if (m_movementOrder == MOVEMENT_STAY)
            out << "STAY";
        out << ". Got " << m_attackerInfo.size() << " attacker(s) in list.";
        out << " Next action in " << m_ignoreAIUpdatesUntilTime - CurrentTime() << "sec.";
    }

    TellMaster(out.str().c_str());
    if (m_DelayAttack)
        TellMaster("My combat delay is '%u'", m_DelayAttack);
}

// handle outgoing packets the server would send to the client
void PlayerbotAI::HandleBotOutgoingPacket(const WorldPacket& packet)
{
    switch (packet.GetOpcode())
    {
        case SMSG_DUEL_WINNER:
        {
            m_bot->HandleEmoteCommand(EMOTE_ONESHOT_APPLAUD);
            return;
        }
        case SMSG_DUEL_COMPLETE:
        {
            SetIgnoreUpdateTime(4);
            m_ScenarioType = SCENARIO_PVE;
            ReloadAI();
            m_bot->GetMotionMaster()->Clear(true);
            return;
        }
        case SMSG_DUEL_OUTOFBOUNDS:
        {
            m_bot->HandleEmoteCommand(EMOTE_ONESHOT_CHICKEN);
            return;
        }
        case SMSG_DUEL_REQUESTED:
        {
            SetIgnoreUpdateTime(0);
            WorldPacket p(packet);
            ObjectGuid flagGuid;
            p >> flagGuid;
            ObjectGuid playerGuid;
            p >> playerGuid;
            Player* const pPlayer = ObjectAccessor::FindPlayer(playerGuid);
            if (canObeyCommandFrom(*pPlayer))
            {
                m_bot->GetMotionMaster()->Clear(true);
                std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_DUEL_ACCEPTED, 8));
                *packet << flagGuid;
                m_bot->GetSession()->QueuePacket(std::move(packet)); // queue the packet to get around race condition

                // follow target in casting range
                float angle = rand_float(0, M_PI_F);
                float dist = rand_float(4, 10);

                m_bot->GetMotionMaster()->Clear(true);
                m_bot->GetMotionMaster()->MoveFollow(pPlayer, dist, angle);

                m_bot->SetSelectionGuid(ObjectGuid(playerGuid));
                SetIgnoreUpdateTime(4);
                m_ScenarioType = SCENARIO_PVP_DUEL;
            }
            return;
        }

        case SMSG_PET_TAME_FAILURE:
        {
            // DEBUG_LOG("SMSG_PET_TAME_FAILURE");
            WorldPacket p(packet);
            uint8 reason;
            p >> reason;

            switch (reason)
            {
                case PETTAME_INVALIDCREATURE:           // = 1,
                    DEBUG_LOG("Invalid Creature");
                    break;
                case PETTAME_TOOMANY:                   // = 2,
                    DEBUG_LOG("Too many Creature");
                    break;
                case PETTAME_CREATUREALREADYOWNED:      // = 3,
                    DEBUG_LOG("Creature already owned");
                    break;
                case PETTAME_NOTTAMEABLE:               // = 4,
                    DEBUG_LOG("Creature not tameable");
                    break;
                case PETTAME_ANOTHERSUMMONACTIVE:       // = 5,
                    DEBUG_LOG("Another summon active");
                    break;
                case PETTAME_UNITSCANTTAME:             // = 6,
                    DEBUG_LOG("Unit cant tame");
                    break;
                case PETTAME_NOPETAVAILABLE:            // = 7,    // not used in taming
                    DEBUG_LOG("No pet available");
                    break;
                case PETTAME_INTERNALERROR:             // = 8,
                    DEBUG_LOG("Internal error");
                    break;
                case PETTAME_TOOHIGHLEVEL:              // = 9,
                    DEBUG_LOG("Creature level too high");
                    break;
                case PETTAME_DEAD:                      // = 10,   // not used in taming
                    DEBUG_LOG("Creature dead");
                    break;
                case PETTAME_NOTDEAD:                   // = 11,   // not used in taming
                    DEBUG_LOG("Creature not dead");
                    break;
                case PETTAME_UNKNOWNERROR:              // = 13
                    DEBUG_LOG("Unknown error");
                    break;
            }
            return;
        }

        case SMSG_BUY_FAILED:
        {
            WorldPacket p(packet); // 8+4+4+1
            ObjectGuid vendorguid;
            p >> vendorguid;
            uint32 itemid;
            p >> itemid;
            uint8 msg;
            p >> msg; // error msg
            p.resize(13);

            switch (msg)
            {
                case BUY_ERR_CANT_FIND_ITEM:
                    break;
                case BUY_ERR_ITEM_ALREADY_SOLD:
                    break;
                case BUY_ERR_NOT_ENOUGHT_MONEY:
                {
                    Announce(CANT_AFFORD);
                    break;
                }
                case BUY_ERR_SELLER_DONT_LIKE_YOU:
                    break;
                case BUY_ERR_DISTANCE_TOO_FAR:
                    break;
                case BUY_ERR_ITEM_SOLD_OUT:
                    break;
                case BUY_ERR_CANT_CARRY_MORE:
                {
                    Announce(INVENTORY_FULL);
                    break;
                }
                case BUY_ERR_RANK_REQUIRE:
                    break;
                case BUY_ERR_REPUTATION_REQUIRE:
                    break;
            }
            return;
        }

        case SMSG_AUCTION_COMMAND_RESULT:
        {
            uint32 auctionId, Action, ErrorCode;
            std::string action[3] = {"Creating", "Cancelling", "Bidding"};
            std::ostringstream out;

            WorldPacket p(packet);
            p >> auctionId;
            p >> Action;
            p >> ErrorCode;
            p.resize(12);

            switch (ErrorCode)
            {
                case AUCTION_OK:
                {
                    out << "|cff1eff00|h" << action[Action] << " was successful|h|r";
                    break;
                }
                case AUCTION_ERR_INVENTORY:
                {
                    out << "|cffff0000|h Item cannot be auctioned|h|r";
                    break;
                }
                case AUCTION_ERR_DATABASE:
                {
                    out << "|cffff0000|hWhile" << action[Action] << ", an internal error occured|h|r";
                    break;
                }
                case AUCTION_ERR_NOT_ENOUGH_MONEY:
                {
                    out << "|cffff0000|hWhile " << action[Action] << ", I didn't have enough money|h|r";
                    break;
                }
                case AUCTION_ERR_ITEM_NOT_FOUND:
                {
                    out << "|cffff0000|hItem was not found!|h|r";
                    break;
                }
                case AUCTION_ERR_BID_OWN:
                {
                    out << "|cffff0000|hI cannot bid on my own auctions!|h|r";
                    break;
                }
                default:
                    out << "|cffff0000|hAuction Error code (" << ErrorCode << ")|h|r";
            }
            TellMaster(out.str().c_str());
            return;
        }

        case SMSG_INVENTORY_CHANGE_FAILURE:
        {
            WorldPacket p(packet);
            uint8 err;
            p >> err;

            if (err != EQUIP_ERR_OK)
            {
                switch (err)
                {
                    case EQUIP_ERR_CANT_CARRY_MORE_OF_THIS:
                        TellMaster("I can't carry anymore of those.");
                        return;
                    case EQUIP_ERR_MISSING_REAGENT:
                        TellMaster("I'm missing some reagents for that.");
                        return;
                    case EQUIP_ERR_ITEM_LOCKED:
                        TellMaster("That item is locked.");
                        return;
                    case EQUIP_ERR_ALREADY_LOOTED:
                        TellMaster("That is already looted.");
                        return;
                    case EQUIP_ERR_INVENTORY_FULL:
                    {
                        if (m_lootCurrent.IsGameObject())
                            if (GameObject* go = m_bot->GetMap()->GetGameObject(m_lootCurrent))
                                m_collectObjects.remove(go->GetEntry());

                        if (m_inventory_full)
                            return;

                        TellMaster("My inventory is full.");
                        m_inventory_full = true;
                        return;
                    }
                    case EQUIP_ERR_NOT_IN_COMBAT:
                        TellMaster("I can't use that in combat.");
                        return;
                    case EQUIP_ERR_LOOT_CANT_LOOT_THAT_NOW:
                        TellMaster("I can't get that now.");
                        return;
                    case EQUIP_ERR_ITEM_UNIQUE_EQUIPABLE:
                        TellMaster("I can only have one of those equipped.");
                        return;
                    case EQUIP_ERR_BANK_FULL:
                        TellMaster("My bank is full.");
                        return;
                    case EQUIP_ERR_ITEM_NOT_FOUND:
                        TellMaster("I can't find the item.");
                        return;
                    case EQUIP_ERR_TOO_FAR_AWAY_FROM_BANK:
                        TellMaster("I'm too far from the bank.");
                        return;
                    case EQUIP_ERR_NONE:
                        TellMaster("I can't use it on that");
                        return;
                    default:
                        TellMaster("I can't use that.");
                        DEBUG_LOG("[PlayerbotAI]: HandleBotOutgoingPacket - SMSG_INVENTORY_CHANGE_FAILURE: %u", err);
                        return;
                }
            }
        }

        /*    case SMSG_CAST_FAILED:
                {
                    WorldPacket p(packet);
                    uint8 castCount;
                    uint32 spellId;
                    uint8 result;
                    std::ostringstream out;

                    p >> spellId >> result >> castCount;

                    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                    if (!spellInfo)
                        return;

                    if (result != SPELL_CAST_OK)
                    {
                        switch (result)
                        {
                        case SPELL_FAILED_INTERRUPTED:  // 40
                        {
                            DEBUG_LOG("spell %s interrupted (%u)",spellInfo->SpellName[0],result);
                            return;
                        }
                        case SPELL_FAILED_UNIT_NOT_INFRONT:  // 134
                            if (m_targetCombat)
                                m_bot->SetInFront(m_targetCombat);
                        case SPELL_FAILED_BAD_TARGETS:  // 12
                            {
                                // DEBUG_LOG("[%s]bad target / not in front(%u) for spellId (%u) & m_CurrentlyCastingSpellId (%u)",m_bot->GetName(),result,spellId,m_CurrentlyCastingSpellId);
                                Spell* const pSpell = GetCurrentSpell();
                                if (pSpell)
                                    pSpell->cancel();
                                break;
                            }
                            case SPELL_FAILED_TOTEM_CATEGORY:
                            {
                                for (uint8 i = 0; i < MAX_SPELL_TOTEM_CATEGORIES; i++)
                                    if (!HasTool(spellInfo->TotemCategory[i]))
                                        break;

                                m_lootCurrent = ObjectGuid();
                                break;
                            }
                        case SPELL_FAILED_REQUIRES_SPELL_FOCUS: // 102
                            {
                                switch(spellInfo->RequiresSpellFocus) // SpellFocusObject.dbc id
                                {
                                    case 1 : // need an anvil
                                        out << "|cffff0000I require an anvil.";
                                        break;
                                    case 2 : // need a loom
                                        out << "|cffff0000I require a loom.";
                                        break;
                                    case 3 : // need forge
                                        out << "|cffff0000I require a forge.";
                                        break;
                                    case 4 : // need cooking fire
                                        out << "|cffff0000I require a cooking fire.";
                                        break;
                                    default:
                                        out << "|cffff0000I Require Spell Focus on " << spellInfo->RequiresSpellFocus;
                                }
                                break;
                            }
                        case SPELL_FAILED_CANT_BE_DISENCHANTED:  // 14
                            {
                                out << "|cffff0000Item cannot be disenchanted.";
                                break;
                            }
                            case SPELL_FAILED_CANT_BE_PROSPECTED:  // 17
                            {
                                out << "|cffff0000There are no gems in this.";
                                break;
                            }
                        case SPELL_FAILED_EQUIPPED_ITEM_CLASS:  // 29
                            {
                                out << "|cffff0000That item is not a valid target.";
                                break;
                            }
                            case SPELL_FAILED_NEED_MORE_ITEMS:  // 55
                            {
                                ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(m_itemTarget);
                                if (!pProto)
                                    return;

                                out << "|cffff0000Requires 5 " << pProto->Name1 << ".";
                                m_itemTarget = 0;
                                break;
                            }
                            case SPELL_FAILED_REAGENTS:
                            {
                                out << "|cffff0000I don't have the reagents";
                                break;
                            }
                            default:
                                DEBUG_LOG ("[%s] SMSG_CAST_FAIL: %s err (%u)",m_bot->GetName(), spellInfo->SpellName[0], result);
                                return;
                        }
                    }
                    TellMaster(out.str().c_str());
                    return;
                }*/

        case SMSG_SPELL_FAILURE:
        {
            WorldPacket p(packet);
            uint8 castCount;
            uint32 spellId;
            ObjectGuid casterGuid;

            p >> casterGuid.ReadAsPacked();
            if (casterGuid != m_bot->GetObjectGuid())
                return;

            p >> castCount >> spellId;
            if (m_CurrentlyCastingSpellId == spellId)
            {
                SetIgnoreUpdateTime(0);
                m_CurrentlyCastingSpellId = 0;
            }
            return;
        }

        // If master dismounted, do so
        case SMSG_DISMOUNT:
        {
            if (!GetMaster()->IsMounted() && m_bot->IsMounted())    // only execute code if master is the one who dismounted
            {
                WorldPacket emptyPacket;
                m_bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);  //updated code
            }
            return;
        }
        // if a change in speed was detected for the master
        // make sure we have the same mount status
        case SMSG_SPLINE_SET_RUN_SPEED:
        {
            WorldPacket p(packet);
            ObjectGuid guid;

            p >> guid.ReadAsPacked();
            if (guid != GetMaster()->GetObjectGuid())
                return;
            if (GetMaster()->IsMounted() && !m_bot->IsMounted())
            {
                // Player Part
                if (!GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).empty())
                {
                    int32 master_speed1 = 0;
                    int32 master_speed2 = 0;
                    master_speed1 = GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[1];
                    master_speed2 = GetMaster()->GetAurasByType(SPELL_AURA_MOUNTED).front()->GetSpellProto()->EffectBasePoints[2];

                    // Bot Part
                    // Step 1: find spell in bot spellbook that matches the speed change from master
                    uint32 spellMount = 0;
                    for (PlayerSpellMap::iterator itr = m_bot->GetSpellMap().begin(); itr != m_bot->GetSpellMap().end(); ++itr)
                    {
                        uint32 spellId = itr->first;
                        if (itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
                            continue;
                        const SpellEntry* pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                        if (!pSpellInfo)
                            continue;

                        if (pSpellInfo->EffectApplyAuraName[0] == SPELL_AURA_MOUNTED)
                        {
                            if (pSpellInfo->EffectApplyAuraName[1] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
                            {
                                if (pSpellInfo->EffectBasePoints[1] == master_speed1)
                                {
                                    spellMount = spellId;
                                    break;
                                }
                            }
                            else if (pSpellInfo->EffectApplyAuraName[2] == SPELL_AURA_MOD_INCREASE_MOUNTED_SPEED)
                                if (pSpellInfo->EffectBasePoints[2] == master_speed2)
                                {
                                    spellMount = spellId;
                                    break;
                                }
                        }
                    }
                    if (spellMount > 0 && m_bot->CastSpell(m_bot, spellMount, TRIGGERED_NONE) == SPELL_CAST_OK)
                        return;

                    // Step 2: no spell found or cast failed -> search for an item in inventory (mount)
                    // We start with the fastest mounts as bot will not be able to outrun its master since it is following him/her
                    uint32 skillLevels[] = { 375, 300, 225, 150, 75 };
                    for (uint32 level : skillLevels)
                    {
                        Item* mount = FindMount(level);
                        if (mount)
                        {
                            UseItem(mount);
                            return;
                        }
                    }
                }
            }
            return;
        }

        // handle flying acknowledgement
        case SMSG_MOVE_SET_CAN_FLY:
        {
            WorldPacket p(packet);
            ObjectGuid guid;

            p >> guid.ReadAsPacked();
            if (guid != m_bot->GetObjectGuid())
                return;
            m_bot->m_movementInfo->AddMovementFlag(MOVEFLAG_FLYING);
            //m_bot->SetSpeed(MOVE_RUN, GetMaster()->GetSpeed(MOVE_FLIGHT) +0.1f, true);
            return;
        }

        // handle dismount flying acknowledgement
        case SMSG_MOVE_UNSET_CAN_FLY:
        {
            WorldPacket p(packet);
            ObjectGuid guid;

            p >> guid.ReadAsPacked();
            if (guid != m_bot->GetObjectGuid())
                return;
            m_bot->m_movementInfo->RemoveMovementFlag(MOVEFLAG_FLYING);
            //m_bot->SetSpeed(MOVE_RUN,GetMaster()->GetSpeedRate(MOVE_RUN),true);
            return;
        }

        // Handle chat messages here
        case SMSG_MESSAGECHAT:
        {
            WorldPacket p(packet);
            uint8 msgtype;
            uint32 language;

            p >> msgtype;           // 1 type
            p >> language;          // 4 language

            if (language == LANG_ADDON)
                return;

            switch (msgtype)
            {
                case CHAT_MSG_RAID:
                case CHAT_MSG_RAID_LEADER:
                case CHAT_MSG_PARTY:
                case CHAT_MSG_WHISPER:
                {
                    ObjectGuid senderGuid;
                    std::string channelName;
                    uint32 length;
                    std::string text;
                    uint8 chattag;

                    p >> senderGuid;        // 8 player from guid
                    p.read_skip<uint32>();  // 4 chat msg group
                    p.read_skip<uint64>();  // 8 player from guid
                    p >> length;            // 4 length of text
                    p >> text;              // string message
                    p >> chattag;           // 1 AFK/DND/WHISPER_INFORM

                    Player* sender = sObjectMgr.GetPlayer(senderGuid);
                    if (!sender)            // couldn't find player that sent message
                        return;

                    // do not listen to other bots
                    if (sender != m_bot && sender->GetPlayerbotAI())
                        return;
                    HandleCommand(text, *sender);
                    return;
                }
                default:
                    return;
            }

            return;
        }

        // If the leader role was given to the bot automatically give it to the master
        // if the master is in the group, otherwise leave group
        case SMSG_GROUP_SET_LEADER:
        {
            WorldPacket p(packet);
            std::string name;
            p >> name;
            if (m_bot->GetGroup() && name == m_bot->GetName())
            {
                if (m_bot->GetGroup()->IsMember(GetMaster()->GetObjectGuid()))
                {
                    p.resize(8);
                    p << GetMaster()->GetObjectGuid();
                    m_bot->GetSession()->HandleGroupSetLeaderOpcode(p);
                }
                else
                {
                    p.clear(); // not really needed
                    m_bot->GetSession()->HandleGroupDisbandOpcode(p); // packet not used updated code
                }
            }
            return;
        }

        // If the master leaves the group, then the bot leaves too
        case SMSG_PARTY_COMMAND_RESULT:
        {
            WorldPacket p(packet);
            uint32 operation;
            p >> operation;
            std::string member;
            p >> member;
            uint32 result;
            p >> result;
            p.clear();
            if (operation == PARTY_OP_LEAVE)
                if (member == GetMaster()->GetName())
                    m_bot->GetSession()->HandleGroupDisbandOpcode(p);  // packet not used updated code
            return;
        }

        // Handle Group invites (auto accept if master is in group, otherwise decline & send message
        case SMSG_GROUP_INVITE:
        {
            if (m_bot->GetGroupInvite())
            {
                const Group* const grp = m_bot->GetGroupInvite();
                if (!grp)
                    return;

                Player* const inviter = sObjectMgr.GetPlayer(grp->GetLeaderGuid());
                if (!inviter)
                    return;

                WorldPacket p;
                if (!canObeyCommandFrom(*inviter))
                {
                    std::string buf = "I can't accept your invite unless you first invite my master ";
                    buf += GetMaster()->GetName();
                    buf += ".";
                    SendWhisper(buf, *inviter);
                    m_bot->GetSession()->HandleGroupDeclineOpcode(p); // packet not used
                }
                else
                    m_bot->GetSession()->HandleGroupAcceptOpcode(p);  // packet not used
            }
            return;
        }

        case SMSG_GUILD_INVITE:
        {
            Guild* guild = sGuildMgr.GetGuildById(m_bot->GetGuildIdInvited());
            if (!guild || m_bot->GetGuildId())
                return;

            // not let enemies sign guild charter
            if (!sWorld.getConfig(CONFIG_BOOL_ALLOW_TWO_SIDE_INTERACTION_GUILD) && m_bot->GetTeam() != sObjectMgr.GetPlayerTeamByGUID(guild->GetLeaderGuid()))
                return;

            if (!guild->AddMember(m_bot->GetObjectGuid(), guild->GetLowestRank()))
                return;
            // Put record into guild log
            guild->LogGuildEvent(GUILD_EVENT_LOG_JOIN_GUILD, m_bot->GetObjectGuid());

            guild->BroadcastEvent(GE_JOINED, m_bot->GetObjectGuid(), m_bot->GetName());
        }

        // Handle when another player opens the trade window with the bot
        // also sends list of tradable items bot can trade if bot is allowed to obey commands from
        case SMSG_TRADE_STATUS:
        {
            if (m_bot->GetTrader() == nullptr)
                break;

            WorldPacket p(packet);
            uint32 status;
            p >> status;
            p.resize(4);

            //4 == TRADE_STATUS_TRADE_ACCEPT
            if (status == 4)
            {
                m_bot->GetSession()->HandleAcceptTradeOpcode(p);  // packet not used
                SetQuestNeedItems();
                AutoUpgradeEquipment();
            }

            //1 == TRADE_STATUS_BEGIN_TRADE
            else if (status == 1)
            {
                m_bot->GetSession()->HandleBeginTradeOpcode(p); // packet not used

                if (!canObeyCommandFrom(*(m_bot->GetTrader())))
                {
                    // TODO: Really? What if I give a bot all my junk so it's inventory is full when a nice green/blue/purple comes along?
                    SendWhisper("I'm not allowed to trade you any of my items, but you are free to give me money or items.", *(m_bot->GetTrader()));
                    return;
                }

                // list out items
                std::ostringstream out;
                std::ostringstream outT;
                std::ostringstream outNT;
                uint8 countTotalTradeable = 0;
                uint8 countTradeable = 0;
                uint8 countNonTradeable = 0;

                outT << "Tradeable:";
                outNT << "Non-tradeable:";
                // list out items in main backpack
                for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
                {
                    const Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
                    if (pItem)
                    {
                        if (pItem->CanBeTraded())
                        {
                            countTradeable++;
                            MakeItemLink(pItem, outT, true);
                        }
                        else
                        {
                            countNonTradeable++;
                            MakeItemLink(pItem, outNT, true);
                        }
                    }
                }

                countTotalTradeable = countTradeable;
                out << "Backpack (" << countTradeable + countNonTradeable << "/16) ";
                if (countTradeable > 0)
                    out << outT.str();
                if (countNonTradeable > 0)
                    out << "\r" << outNT.str();
                SendWhisper(out.str().c_str(), *(m_bot->GetTrader()));

                // list out items in other removable backpacks
                for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
                {
                    const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
                    if (pBag)
                    {
                        countTradeable = 0;
                        countNonTradeable = 0;
                        std::ostringstream outbagT;
                        std::ostringstream outbagNT;
                        outbagT << "Tradeable:";
                        outbagNT << "Non-tradeable:";

                        for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
                        {
                            const Item* const pItem = m_bot->GetItemByPos(bag, slot);
                            if (pItem)
                            {
                                if (pItem->CanBeTraded())
                                {
                                    countTradeable++;
                                    MakeItemLink(pItem, outbagT, true);
                                }
                                else
                                {
                                    countNonTradeable++;
                                    MakeItemLink(pItem, outbagNT, true);
                                }
                            }
                        }

                        countTotalTradeable += countTradeable;
                        std::ostringstream outbag;
                        const ItemPrototype* const pBagProto = pBag->GetProto();
                        std::string bagName = pBagProto->Name1;
                        ItemLocalization(bagName, pBagProto->ItemId);
                        outbag << bagName << " (";
                        outbag << countTradeable + countNonTradeable << "/" << pBag->GetBagSize();
                        outbag << ") ";
                        if (countTradeable > 0)
                            outbag << outbagT.str();
                        if (countNonTradeable > 0)
                            outbag << "\r" << outbagNT.str();
                        SendWhisper(outbag.str().c_str(), *(m_bot->GetTrader()));
                    }
                }
                if (countTotalTradeable == 0)
                    SendWhisper("I have no items to give you.", *(m_bot->GetTrader()));

                // calculate how much money bot has
                // send bot the message
                uint32 copper = m_bot->GetMoney();
                out.str("");
                out << "I have |cff00ff00" << Cash(copper) << "|r";
                SendWhisper(out.str().c_str(), *(m_bot->GetTrader()));
            }
            return;
        }

        case SMSG_SPELL_START:
        {

            WorldPacket p(packet);

            ObjectGuid castItemGuid;
            p >> castItemGuid.ReadAsPacked();
            ObjectGuid casterGuid;
            p >> casterGuid.ReadAsPacked();
            if (casterGuid != m_bot->GetObjectGuid())
                return;

            uint32 spellId;
            p >> spellId;
            uint8 cast_count;
            p >> cast_count;
            uint16 castFlags;
            p >> castFlags;
            uint32 msTime;
            p >> msTime;

            // DEBUG_LOG("castItemGuid (%s) casterItemGuid(%s) spellId (%u) cast_count (%u) castFlags (%u) msTime (%u)",castItemGuid.GetString().c_str(),casterGuid.GetString().c_str(), spellId, cast_count, castFlags, msTime);

            const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
            if (!pSpellInfo)
                return;

            if (pSpellInfo->AuraInterruptFlags & AURA_INTERRUPT_FLAG_NOT_SEATED)
                return;

            uint32 CastingTime = !IsChanneledSpell(pSpellInfo) ? GetSpellCastTime(pSpellInfo) : GetSpellDuration(pSpellInfo);

            SetIgnoreUpdateTime((msTime / 1000) + 1);

            return;
        }

        case SMSG_SPELL_GO:
        {
            WorldPacket p(packet);

            ObjectGuid castItemGuid;
            p >> castItemGuid.ReadAsPacked();
            ObjectGuid casterGuid;
            p >> casterGuid.ReadAsPacked();
            if (casterGuid != m_bot->GetObjectGuid())
                return;

            uint32 spellId;
            p >> spellId;
            uint16 castFlags;
            p >> castFlags;

            // use this spell, 836 login effect, as a signal from server that we're in world
            if (spellId == 836 && m_botState == BOTSTATE_LOADING)
                SetState(BOTSTATE_NORMAL);

            return;
        }

        // if someone tries to resurrect, then accept
        case SMSG_RESURRECT_REQUEST:
        {
            if (!m_bot->isAlive())
            {
                WorldPacket p(packet);
                ObjectGuid guid;
                p >> guid;

                std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_RESURRECT_RESPONSE, 8 + 1));
                *packet << guid;
                *packet << uint8(1);                        // accept
                m_bot->GetSession()->QueuePacket(std::move(packet));   // queue the packet to get around race condition

                // set back to normal
                SetState(BOTSTATE_NORMAL);
                SetIgnoreUpdateTime(0);
            }
            return;
        }

        case SMSG_LOOT_RESPONSE:
        {
            WorldPacket p(packet); // (8+1+4+1+1+4+4+4+4+4+1)
            ObjectGuid guid;
            uint8 loot_type;
            uint32 gold;
            uint8 items;

            p >> guid;      // 8 corpse guid
            p >> loot_type; // 1 loot type
            p >> gold;      // 4 gold
            p >> items;     // 1 items count

            if (gold > 0)
            {
                WorldPacket* const packet = new WorldPacket(CMSG_LOOT_MONEY, 0);
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(packet)));
            }

            for (uint8 i = 0; i < items; ++i)
            {
                uint32 itemid;
                uint32 itemcount;
                uint8 lootslot_type;
                uint8 itemindex;

                p >> itemindex;         // 1 counter
                p >> itemid;            // 4 itemid
                p >> itemcount;         // 4 item stack count
                p.read_skip<uint32>();  // 4 item model
                p.read_skip<uint32>();  // 4 randomSuffix
                p.read_skip<uint32>();  // 4 randomPropertyId
                p >> lootslot_type;     // 1 LootSlotType

                ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(itemid);
                if (!pProto)
                    continue;

                if (lootslot_type != LOOT_SLOT_NORMAL && lootslot_type != LOOT_SLOT_OWNER)
                    continue;

                // skinning or collect loot flag = just auto loot everything for getting object
                // corpse = run checks
                if (loot_type == LOOT_SKINNING || HasCollectFlag(COLLECT_FLAG_LOOT) ||
                        (loot_type == LOOT_CORPSE && (IsInQuestItemList(itemid) || IsItemUseful(itemid))))
                {
                    ItemPosCountVec dest;
                    if (m_bot->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, itemid, itemcount) == EQUIP_ERR_INVENTORY_FULL)
                    {
                        if (GetManager()->m_confDebugWhisper)
                            TellMaster("I can't take %; my inventory is full.", pProto->Name1);
                        m_inventory_full = true;
                        continue;
                    }

                    if (GetManager()->m_confDebugWhisper)
                        TellMaster("Store loot item %s", pProto->Name1);

                    WorldPacket* const packet = new WorldPacket(CMSG_AUTOSTORE_LOOT_ITEM, 1);
                    *packet << itemindex;
                    m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(packet)));
                }
                else
                {
                    if (GetManager()->m_confDebugWhisper)
                        TellMaster("Skipping loot item %s", pProto->Name1);
                }
            }

            if (GetManager()->m_confDebugWhisper)
                TellMaster("Releasing loot");
            // release loot
            m_lootPrev = m_lootCurrent;
            m_lootCurrent = ObjectGuid();
            WorldPacket* const packet = new WorldPacket(CMSG_LOOT_RELEASE, 8);
            *packet << guid;
            m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(packet)));

            return;
        }

        case SMSG_LOOT_RELEASE_RESPONSE:
        {
            WorldPacket p(packet);
            ObjectGuid guid;

            p >> guid;

            if (guid == m_lootPrev)
            {
                Creature* c = m_bot->GetMap()->GetCreature(m_lootPrev);

                if (c && c->GetCreatureInfo()->SkinningLootId && c->GetLootStatus() != CREATURE_LOOT_STATUS_LOOTED)
                {
                    uint32 reqSkill = c->GetCreatureInfo()->GetRequiredLootSkill();
                    // check if it is a leather skin and if it is to be collected (could be ore or herb)
                    if (m_bot->HasSkill(reqSkill) && ((reqSkill != SKILL_SKINNING) ||
                                                      (HasCollectFlag(COLLECT_FLAG_SKIN) && reqSkill == SKILL_SKINNING)))
                    {
                        // calculate skill requirement
                        uint32 skillValue = m_bot->GetSkillValue(reqSkill);
                        uint32 targetLevel = c->getLevel();
                        uint32 reqSkillValue = targetLevel < 10 ? 0 : targetLevel < 20 ? (targetLevel - 10) * 10 : targetLevel * 5;
                        if (skillValue >= reqSkillValue)
                        {
                            m_lootCurrent = m_lootPrev;
                            if (GetManager()->m_confDebugWhisper)
                                TellMaster("I will try to skin next loot attempt.");

                            SetIgnoreUpdateTime(1);
                            return; // so that the DoLoot function is called again to get skin
                        }
                        else
                            TellMaster("My skill is %u but it requires %u", skillValue, reqSkillValue);
                    }
                }

                // clear movement
                m_bot->GetMotionMaster()->Clear(false);
                m_bot->GetMotionMaster()->MoveIdle();
                SetIgnoreUpdateTime(0);
            }

            return;
        }

        case SMSG_LOOT_ROLL_WON:
        {
            WorldPacket p(packet);   // (8+4+4+4+4+8+1+1)
            ObjectGuid guid;
            uint32 itemid;

            p.read_skip<ObjectGuid>(); // creature guid what we're looting
            p.read_skip<uint32>();   // item slot in loot
            p >> itemid;             // the itemEntryId for the item that shall be rolled fo
            p.read_skip<uint32>();   // randomSuffix
            p.read_skip<uint32>();   // Item random property
            p >> guid;               // guid of the player who won
            p.read_skip<uint8>();    // rollnumber related to SMSG_LOOT_ROLL
            p.read_skip<uint8>();    // Rolltype related to SMSG_LOOT_ROLL

            if (m_bot->GetObjectGuid() != guid)
                return;

            SetState(BOTSTATE_DELAYED);

            /*            ItemPrototype const *pProto = ObjectMgr::GetItemPrototype(itemid);
                        if(pProto)
                        {
                            std::ostringstream out;
                            out << "|cff009900" << "I won: |r";
                            MakeItemLink(pProto,out);
                            if (FindItem(itemid,true))
                                out << "and have the item";
                            TellMaster(out.str().c_str());
                        }*/
            return;
        }

        case SMSG_PARTYKILLLOG:
        {
            // reset AI delay so bots immediately respond to next combat target & or looting/skinning
            SetIgnoreUpdateTime(0);
            return;
        }

        case SMSG_ITEM_PUSH_RESULT:
        {
            WorldPacket p(packet);  // (8+4+4+4+1+4+4+4+4+4+4)
            ObjectGuid guid;

            p >> guid;              // 8 player guid
            if (m_bot->GetObjectGuid() != guid)
                return;

            uint8 bagslot;
            uint32 itemslot, itemid, count, totalcount, received, created;

            p >> received;          // 4 0=looted, 1=from npc
            p >> created;           // 4 0=received, 1=created
            p.read_skip<uint32>();  // 4 IsShowChatMessage
            p >> bagslot;           // 1 bagslot
            p >> itemslot;          // 4 item slot, but when added to stack: 0xFFFFFFFF
            p >> itemid;            // 4 item entry id
            p.read_skip<uint32>();  // 4 SuffixFactor
            p.read_skip<uint32>();  // 4 random item property id
            p >> count;             // 4 count of items
            p >> totalcount;        // 4 count of items in inventory

            ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(itemid);
            if (pProto)
            {
                std::ostringstream out;
                if (received == 1)
                {
                    if (created == 1)
                        out << "|cff009900" << "I created: |r";
                    else
                        out << "|cff009900" << "I received: |r";
                    MakeItemLink(pProto, out);
                    TellMaster(out.str().c_str());
                    SetState(BOTSTATE_DELAYED);
                }
            }

            if (IsInQuestItemList(itemid))
            {
                m_needItemList[itemid] = (m_needItemList[itemid] - count);
                if (m_needItemList[itemid] <= 0)
                    m_needItemList.erase(itemid);
            }

            return;
        }

        case MSG_MOVE_TELEPORT_ACK:
        {
            WorldPacket rp(packet);
            ObjectGuid guid;
            rp >> guid.ReadAsPacked();

            if (guid != m_bot->GetObjectGuid())
                return;

            uint32 counter;
            rp >> counter;
            // movement location to teleport to
            MovementInfo mi;
            rp >> mi;

            if (GetManager()->m_confDebugWhisper)
                TellMaster("Preparing to teleport");

            if (m_bot->IsBeingTeleportedNear())
            {
                // simulate same packets that are sent for client
                WorldPacket* const p = new WorldPacket(MSG_MOVE_TELEPORT_ACK, 8 + 4 + 4);
                *p << m_bot->GetObjectGuid();
                *p << counter;
                *p << (uint32) time(0); // time - not currently used
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(p)));

                // send movement info using received movement packet, pops in location
                WorldPacket* const p2 = new WorldPacket(MSG_MOVE_HEARTBEAT, 28);
                *p2 << mi;
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(p2)));

                WorldPacket* const p3 = new WorldPacket(MSG_MOVE_FALL_LAND, 28);
                *p3 << mi;
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(p3)));

                // resume normal state if was loading
                if (m_botState == BOTSTATE_LOADING)
                    SetState(BOTSTATE_NORMAL);
            }
            return;
        }
        case SMSG_TRANSFER_PENDING:
        {
            if (GetManager()->m_confDebugWhisper)
                TellMaster("World transfer is pending");
            SetState(BOTSTATE_LOADING);
            SetIgnoreUpdateTime(1);
            m_bot->GetMotionMaster()->Clear(true);
            return;
        }
        case SMSG_NEW_WORLD:
        {
            if (GetManager()->m_confDebugWhisper)
                TellMaster("Preparing to teleport far");

            if (m_bot->IsBeingTeleportedFar())
            {
                // simulate client canceling trade before worldport
                WorldPacket* const pt1 = new WorldPacket(CMSG_CANCEL_TRADE);
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(pt1)));

                WorldPacket* const p = new WorldPacket(MSG_MOVE_WORLDPORT_ACK);
                m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(p)));
                SetState(BOTSTATE_NORMAL);
            }
            return;
        }

        /* uncomment this and your bots will tell you all their outgoing packet opcode names
           case SMSG_MONSTER_MOVE:
           case SMSG_UPDATE_WORLD_STATE:
           case SMSG_COMPRESSED_UPDATE_OBJECT:
           case MSG_MOVE_SET_FACING:
           case MSG_MOVE_STOP:
           case MSG_MOVE_HEARTBEAT:
           case MSG_MOVE_STOP_STRAFE:
           case MSG_MOVE_START_STRAFE_LEFT:
           case SMSG_UPDATE_OBJECT:
           case MSG_MOVE_START_FORWARD:
           case MSG_MOVE_START_STRAFE_RIGHT:
           case SMSG_DESTROY_OBJECT:
           case MSG_MOVE_START_BACKWARD:
           case SMSG_AURA_UPDATE_ALL:
           case MSG_MOVE_FALL_LAND:
           case MSG_MOVE_JUMP:
            return;*/

        default:
        {
            /*const char* oc = LookupOpcodeName(packet.GetOpcode());

            std::ostringstream out;
            out << "botout: " << oc;
            sLog.outError(out.str().c_str());

            TellMaster(oc);*/
        }
    }
}

uint8 PlayerbotAI::GetHealthPercent(const Unit& target) const
{
    return (static_cast<float>(target.GetHealth()) / target.GetMaxHealth()) * 100;
}

uint8 PlayerbotAI::GetHealthPercent() const
{
    return GetHealthPercent(*m_bot);
}

uint8 PlayerbotAI::GetManaPercent(const Unit& target) const
{
    return (static_cast<float>(target.GetPower(POWER_MANA)) / target.GetMaxPower(POWER_MANA)) * 100;
}

uint8 PlayerbotAI::GetManaPercent() const
{
    return GetManaPercent(*m_bot);
}

uint8 PlayerbotAI::GetRageAmount(const Unit& target) const
{
    return (static_cast<float>(target.GetPower(POWER_RAGE)));
}

uint8 PlayerbotAI::GetRageAmount() const
{
    return GetRageAmount(*m_bot);
}

uint8 PlayerbotAI::GetEnergyAmount(const Unit& target) const
{
    return (static_cast<float>(target.GetPower(POWER_ENERGY)));
}

uint8 PlayerbotAI::GetEnergyAmount() const
{
    return GetEnergyAmount(*m_bot);
}

bool PlayerbotAI::HasAura(uint32 spellId, const Unit& player) const
{
    if (spellId <= 0)
        return false;

    for (Unit::SpellAuraHolderMap::const_iterator iter = player.GetSpellAuraHolderMap().begin(); iter != player.GetSpellAuraHolderMap().end(); ++iter)
    {
        if (iter->second->GetId() == spellId)
            return true;
    }
    return false;
}

bool PlayerbotAI::HasAura(const char* spellName) const
{
    return HasAura(spellName, *m_bot);
}

bool PlayerbotAI::HasAura(const char* spellName, const Unit& player) const
{
    uint32 spellId = getSpellId(spellName);
    return (spellId) ? HasAura(spellId, player) : false;
}

// looks through all items / spells that bot could have to get a mount
Item* PlayerbotAI::FindMount(uint32 matchingRidingSkill) const
{
    // list out items in main backpack

    Item* partialMatch = nullptr;

    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();
            if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK || pItemProto->RequiredSkill != SKILL_RIDING)
                continue;

            // Ignore items that can not be used in the current situation (have requirements)
            uint32 spellId = 0;
            for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
            {
                if (pItemProto->Spells[i].SpellId > 0)
                {
                    spellId = pItemProto->Spells[i].SpellId;
                    break;
                }
            }
            const SpellEntry* const spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
            if (spellInfo)
            {
                Spell* spell = new Spell(m_bot, spellInfo, false);
                if (spell && spell->CheckCast(false) != SPELL_CAST_OK)
                    continue;
            }

            if (pItemProto->RequiredSkillRank == matchingRidingSkill)
                return pItem;

            else if (!partialMatch || (partialMatch && partialMatch->GetProto()->RequiredSkillRank < pItemProto->RequiredSkillRank))
                partialMatch = pItem;
        }
    }

    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();
                    if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK || pItemProto->RequiredSkill != SKILL_RIDING)
                        continue;

                    // Ignore items that can not be used in the current situation (have requirements)
                    uint32 spellId = 0;
                    for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
                    {
                        if (pItemProto->Spells[i].SpellId > 0)
                        {
                            spellId = pItemProto->Spells[i].SpellId;
                            break;
                        }
                    }
                    const SpellEntry* const spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                    if (spellInfo)
                    {
                        Spell* spell = new Spell(m_bot, spellInfo, false);
                        if (spell && spell->CheckCast(false) != SPELL_CAST_OK)
                            continue;
                    }

                    if (pItemProto->RequiredSkillRank == matchingRidingSkill)
                        return pItem;

                    else if (!partialMatch || (partialMatch && partialMatch->GetProto()->RequiredSkillRank < pItemProto->RequiredSkillRank))
                        partialMatch = pItem;
                }
            }
    }
    return partialMatch;
}

Item* PlayerbotAI::FindFood() const
{
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();
            if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                continue;

            if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD)
                // if is FOOD
                // this enum is no longer defined in mangos. Is it no longer valid?
                // according to google it was 11
                if (pItemProto->Spells[0].SpellCategory == 11)
                    return pItem;
        }
    }
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();

                    if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                        continue;

                    // this enum is no longer defined in mangos. Is it no longer valid?
                    // according to google it was 11
                    if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD)
                        // if is FOOD
                        // this enum is no longer defined in mangos. Is it no longer valid?
                        // according to google it was 11
                        // if (pItemProto->Spells[0].SpellCategory == SPELL_CATEGORY_FOOD)
                        if (pItemProto->Spells[0].SpellCategory == 11)
                            return pItem;
                }
            }
    }
    return nullptr;
}

Item* PlayerbotAI::FindDrink() const
{
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();

            if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                continue;

            if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD)
                // if (pItemProto->Spells[0].SpellCategory == SPELL_CATEGORY_DRINK)

                // this enum is no longer defined in mangos. Is it no longer valid?
                // according to google it was 59
                // if (pItemProto->Spells[0].SpellCategory == 59)
                if (pItemProto->Spells[0].SpellCategory == 59)
                    return pItem;
        }
    }
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();

                    if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                        continue;

                    if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_FOOD)
                        // if is WATER
                        // SPELL_CATEGORY_DRINK is no longer defined in an enum in mangos
                        // google says the valus is 59. Is this still valid?
                        // if (pItemProto->Spells[0].SpellCategory == SPELL_CATEGORY_DRINK)
                        if (pItemProto->Spells[0].SpellCategory == 59)
                            return pItem;
                }
            }
    }
    return nullptr;
}

Item* PlayerbotAI::FindBandage() const
{
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();

            if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                continue;

            if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_BANDAGE)
                return pItem;
        }
    }
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();

                    if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                        continue;

                    if (pItemProto->Class == ITEM_CLASS_CONSUMABLE && pItemProto->SubClass == ITEM_SUBCLASS_BANDAGE)
                        return pItem;
                }
            }
    }
    return nullptr;
}

Item* PlayerbotAI::FindConsumable(uint32 displayId) const
{
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();

            if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                continue;

            if ((pItemProto->Class == ITEM_CLASS_CONSUMABLE || pItemProto->Class == ITEM_SUBCLASS_BANDAGE) && pItemProto->DisplayInfoID == displayId)
                return pItem;
        }
    }
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();

                    if (!pItemProto || m_bot->CanUseItem(pItemProto) != EQUIP_ERR_OK)
                        continue;

                    if ((pItemProto->Class == ITEM_CLASS_CONSUMABLE || pItemProto->Class == ITEM_SUBCLASS_BANDAGE) && pItemProto->DisplayInfoID == displayId)
                        return pItem;
                }
            }
    }
    return nullptr;
}

static const uint32 uPriorizedSharpStoneIds[8] =
{
    ADAMANTITE_SHARPENING_DISPLAYID, FEL_SHARPENING_DISPLAYID, ELEMENTAL_SHARPENING_DISPLAYID, DENSE_SHARPENING_DISPLAYID,
    SOLID_SHARPENING_DISPLAYID, HEAVY_SHARPENING_DISPLAYID, COARSE_SHARPENING_DISPLAYID, ROUGH_SHARPENING_DISPLAYID
};

static const uint32 uPriorizedWeightStoneIds[7] =
{
    ADAMANTITE_WEIGHTSTONE_DISPLAYID, FEL_WEIGHTSTONE_DISPLAYID, DENSE_WEIGHTSTONE_DISPLAYID, SOLID_WEIGHTSTONE_DISPLAYID,
    HEAVY_WEIGHTSTONE_DISPLAYID, COARSE_WEIGHTSTONE_DISPLAYID, ROUGH_WEIGHTSTONE_DISPLAYID
};

/**
 * FindStoneFor()
 * return Item* Returns sharpening/weight stone item eligible to enchant a bot weapon
 *
 * params:weapon Item* the weapôn the function should search and return a enchanting item for
 * return nullptr if no relevant item is found in bot inventory, else return a sharpening or weight
 * stone based on the weapon subclass
 *
 */
Item* PlayerbotAI::FindStoneFor(Item* weapon) const
{
    Item* stone;
    ItemPrototype const* pProto = weapon->GetProto();
    if (pProto && (pProto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD || pProto->SubClass == ITEM_SUBCLASS_WEAPON_SWORD2
                   || pProto->SubClass == ITEM_SUBCLASS_WEAPON_AXE || pProto->SubClass == ITEM_SUBCLASS_WEAPON_AXE2
                   || pProto->SubClass == ITEM_SUBCLASS_WEAPON_DAGGER))
    {
        for (uint8 i = 0; i < countof(uPriorizedSharpStoneIds); ++i)
        {
            stone = FindConsumable(uPriorizedSharpStoneIds[i]);
            if (stone)
                return stone;
        }
    }
    else if (pProto && (pProto->SubClass == ITEM_SUBCLASS_WEAPON_MACE || pProto->SubClass == ITEM_SUBCLASS_WEAPON_MACE2))
    {
        for (uint8 i = 0; i < countof(uPriorizedWeightStoneIds); ++i)
        {
            stone = FindConsumable(uPriorizedWeightStoneIds[i]);
            if (stone)
                return stone;
        }
    }

    return nullptr;
}

static const uint32 uPriorizedManaPotionIds[12] =
{
    FEL_MANA_POTION, CRYSTAL_MANA_POTION, SUPER_MANA_POTION, UNSTABLE_MANA_POTION,
    MAJOR_MANA_POTION, MAJOR_REJUVENATION_POTION, SUPERIOR_MANA_POTION,
    GREATER_MANA_POTION, MANA_POTION, LESSER_MANA_POTION,
    MINOR_MANA_POTION, MINOR_REJUVENATION_POTION
};

/**
 * FindManaRegenItem()
 * return Item* Returns items like runes or potion that can help the bot to instantly resplenish some of its mana
 *
 * return nullptr if no relevant item is found in bot inventory, else return a consumable item providing mana
 *
 */
Item* PlayerbotAI::FindManaRegenItem() const
{
    Item* manaRegen;
    // If bot has enough health, try to use a Demonic or Dark Rune
    // to avoid triggering the health potion cooldown with a mana potion
    if (m_bot->GetHealth() > 1500)
    {
        // First try a Demonic Rune as they are BoP
        manaRegen = FindConsumable(DEMONIC_RUNE);
        if (manaRegen)
            return manaRegen;
        else
        {
            manaRegen = FindConsumable(DARK_RUNE);
            if (manaRegen)
                return manaRegen;
        }
    }
    // Else use mana potion (and knowingly trigger the health potion cooldown)
    for (uint8 i = 0; i < countof(uPriorizedManaPotionIds); ++i)
    {
        manaRegen = FindConsumable(uPriorizedManaPotionIds[i]);
        if (manaRegen)
            return manaRegen;
    }

    return nullptr;
}

bool PlayerbotAI::FindAmmo() const
{
    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    {
        Item* pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();

            if (pItemProto->Class == ITEM_CLASS_PROJECTILE && m_bot->CheckAmmoCompatibility(pItemProto))
            {
                m_bot->SetAmmo(pItem->GetEntry());
                return true;
            }
        }
    }
    for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
    {
        if (Bag* pBag = (Bag*)m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
            {
                Item* pItem = m_bot->GetItemByPos(i, j);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();

                    if (pItemProto->Class == ITEM_CLASS_PROJECTILE && m_bot->CheckAmmoCompatibility(pItemProto))
                    {
                        m_bot->SetAmmo(pItem->GetEntry());
                        return true;
                    }
                }
            }
        }
    }
    return false;
}

void PlayerbotAI::InterruptCurrentCastingSpell()
{
    // TellMaster("I'm interrupting my current spell!");
    std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_CANCEL_CAST, 5));  //changed from thetourist suggestion
    *packet << m_CurrentlyCastingSpellId;
    *packet << m_targetGuidCommand;   //changed from thetourist suggestion
    m_CurrentlyCastingSpellId = 0;
    m_bot->GetSession()->QueuePacket(std::move(packet));
}

// intelligently sets a reasonable combat order for this bot
// based on its class / level / etc
void PlayerbotAI::Attack(Unit* forcedTarget)
{
    // set combat state, and clear looting, etc...
    if (m_botState != BOTSTATE_COMBAT)
    {
        SetState(BOTSTATE_COMBAT);
        // m_lootCurrent = ObjectGuid(); This was clearing loot target, causing bots to leave corpses unlooted if interupted by combat. Needs testing.
        // using this caused bot to remove current loot target, and add this new threat to the loot list.  Now it remembers the loot target and adds a new one.
        // Bot will still clear the target if the master gets too far away from it.
        m_targetCombat = 0;
        m_DelayAttackInit = CurrentTime(); // Combat started, new start time to check CombatDelay for.
    }

    GetCombatTarget(forcedTarget);

    if (!m_targetCombat)
        return;

    m_bot->Attack(m_targetCombat, true);

    // add thingToAttack to loot list to loot after combat
    if (HasCollectFlag(COLLECT_FLAG_COMBAT))
        m_lootTargets.push_back(m_targetCombat->GetObjectGuid());
}

// intelligently sets a reasonable combat order for this bot
// based on its class / level / etc
// Function will try to avoid returning crowd controlled (neutralised) unit
// unless told so by using forcedTarget parameter
void PlayerbotAI::GetCombatTarget(Unit* forcedTarget)
{
    // update attacker info now
    UpdateAttackerInfo();

    Unit* candidateTarget;

    // check for attackers on protected unit, and make it a forcedTarget if any
    if (!forcedTarget && (m_combatOrder & ORDERS_PROTECT) && m_targetProtect)
    {
        candidateTarget = FindAttacker((ATTACKERINFOTYPE)(AIT_VICTIMNOTSELF | AIT_HIGHESTTHREAT), m_targetProtect);
        if (candidateTarget && candidateTarget != m_targetCombat && !IsNeutralized(candidateTarget))
        {
            forcedTarget = candidateTarget;
            m_targetType = TARGET_THREATEN;
            if (m_mgr->m_confDebugWhisper)
                TellMaster("Changing target to %s to protect %s", forcedTarget->GetName(), m_targetProtect->GetName());
        }
    }

    // are we forced on a target?
    if (forcedTarget)
    {
        // forced to change target to current target == null operation
        if (forcedTarget && forcedTarget == m_targetCombat)
            return;

        if (m_mgr->m_confDebugWhisper)
            TellMaster("Changing target to %s by force!", forcedTarget->GetName());
        m_targetCombat = forcedTarget;
        m_ignoreNeutralizeEffect = true;    // Bypass IsNeutralized() checks on next updates
        m_targetChanged = true;
        m_targetType = (m_combatOrder & (ORDERS_TANK | ORDERS_MAIN_TANK) ? TARGET_THREATEN : TARGET_NORMAL);
    }

    // we already have a target and we are not forced to change it
    if (m_targetCombat)
    {
        // We have a target but it is neutralised and we are not forced to attack it: clear it for now
        if ((IsNeutralized(m_targetCombat) && !m_ignoreNeutralizeEffect))
        {
            m_targetCombat = nullptr;
            m_targetType = TARGET_NORMAL;
            m_targetChanged = true;
            return;
        }
        else
        {
            if (!IsNeutralized(m_targetCombat) && m_ignoreNeutralizeEffect)
                m_ignoreNeutralizeEffect = false;                           // target is no longer neutralised, clear ignore order
            return;                                                         // keep on attacking target
        }
    }

    // No target for now, try to get one
    // do we have to assist someone?
    if (!m_targetCombat && (m_combatOrder & ORDERS_ASSIST) && m_targetAssist)
    {
        candidateTarget = FindAttacker((ATTACKERINFOTYPE)(AIT_VICTIMNOTSELF | AIT_LOWESTTHREAT), m_targetAssist);
        if (candidateTarget && !IsNeutralized(candidateTarget))
        {
            m_targetCombat = candidateTarget;
            if (m_mgr->m_confDebugWhisper)
                TellMaster("Attacking %s to assist %s", m_targetCombat->GetName(), m_targetAssist->GetName());
            m_targetType = (m_combatOrder & (ORDERS_TANK | ORDERS_MAIN_TANK) ? TARGET_THREATEN : TARGET_NORMAL);
            m_targetChanged = true;
        }
    }
    // are there any other attackers?
    if (!m_targetCombat)
    {
        candidateTarget = FindAttacker();
        if (candidateTarget && !IsNeutralized(candidateTarget))
        {
            m_targetCombat = candidateTarget;
            m_targetType = (m_combatOrder & (ORDERS_TANK | ORDERS_MAIN_TANK) ? TARGET_THREATEN : TARGET_NORMAL);
            m_targetChanged = true;
        }
    }
    // no attacker found anyway
    if (!m_targetCombat)
    {
        m_targetType = TARGET_NORMAL;
        m_targetChanged = false;
        return;
    }

    // if thing to attack is in a duel, then ignore and don't call updateAI for 6 seconds
    // this method never gets called when the bot is in a duel and this code
    // prevents bot from helping
    if (m_targetCombat->GetTypeId() == TYPEID_PLAYER && dynamic_cast<Player*>(m_targetCombat)->duel)
    {
        SetIgnoreUpdateTime(6);
        return;
    }

    m_bot->SetSelectionGuid((m_targetCombat->GetObjectGuid()));
    SetIgnoreUpdateTime(1);

    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);
}

void PlayerbotAI::GetDuelTarget(Unit* forcedTarget)
{
    // set combat state, and clear looting, etc...
    if (m_botState != BOTSTATE_COMBAT)
    {
        SetState(BOTSTATE_COMBAT);
        m_targetChanged = true;
        m_targetCombat = forcedTarget;
        m_targetType = TARGET_THREATEN;
        m_combatStyle = COMBAT_MELEE;
    }
    m_bot->Attack(m_targetCombat, true);
}

void PlayerbotAI::DoNextCombatManeuver()
{
    if (!GetClassAI())
        return; // error, error...

    if (m_combatOrder == ORDERS_PASSIVE)
        return;

    // check for new targets
    if (m_ScenarioType == SCENARIO_PVP_DUEL)
        GetDuelTarget(GetMaster()); // TODO: Wow... wait... what? So not right.
    else
        Attack();

    // clear orders if current target for attacks doesn't make sense anymore
    if (!m_targetCombat || m_targetCombat->isDead() || !m_targetCombat->IsInWorld() || !m_bot->CanAttack(m_targetCombat) || !m_bot->IsInMap(m_targetCombat))
    {
        m_bot->AttackStop();
        m_bot->SetSelectionGuid(ObjectGuid());
        MovementReset();
        m_bot->InterruptNonMeleeSpells(true);
        m_targetCombat = 0;
        m_targetChanged = false;
        m_targetType = TARGET_NORMAL;
        SetQuestNeedCreatures();
        if (GetCombatOrder() & ORDERS_TEMP)
        {
            if (GetCombatOrder() & ORDERS_TEMP_WAIT_TANKAGGRO)
                TellMaster("I was still waiting for the tank to gain aggro, but that doesn't make sense anymore...");
            if (GetCombatOrder() & ORDERS_TEMP_WAIT_OOC)
                TellMaster("I was still waiting OOC but that was way off...");
            ClearCombatOrder(ORDERS_TEMP);
        }
        return;
    }

    // new target -> DoFirstCombatManeuver
    if (m_targetChanged)
    {
        switch (GetClassAI()->DoFirstCombatManeuver(m_targetCombat))
        {
            case RETURN_CONTINUE: // true needed for rogue stealth attack
                break;

            case RETURN_NO_ACTION_ERROR:
                TellMaster("FirstCombatManeuver: No action performed due to error. Heading onto NextCombatManeuver.");
            case RETURN_FINISHED_FIRST_MOVES: // false default
            case RETURN_NO_ACTION_UNKNOWN:
            case RETURN_NO_ACTION_OK:
            default: // assume no action -> no return
                m_targetChanged = false;
        }
    }

    // do normal combat movement
    DoCombatMovement();

    if (!m_targetChanged)
    {
        // if m_targetChanged = false
        switch (GetClassAI()->DoNextCombatManeuver(m_targetCombat))
        {
            case RETURN_NO_ACTION_UNKNOWN:
            case RETURN_NO_ACTION_OK:
            case RETURN_CONTINUE:
            case RETURN_NO_ACTION_ERROR:
            default:
                return;
        }
    }
}

void PlayerbotAI::DoCombatMovement()
{
    if (!m_targetCombat) return;

    bool meleeReach = m_bot->CanReachWithMeleeAttack(m_targetCombat);

    if (m_combatStyle == COMBAT_MELEE
            && !m_bot->hasUnitState(UNIT_STAT_CHASE)
            && ((m_movementOrder == MOVEMENT_STAY && meleeReach) || m_movementOrder != MOVEMENT_STAY)
            && GetClassAI()->GetWaitUntil() == 0)  // Not waiting
    {
        // melee combat - chase target if in range or if we are not forced to stay
        m_bot->GetMotionMaster()->Clear(false);
        m_bot->GetMotionMaster()->MoveChase(m_targetCombat);
    }
    else if (m_combatStyle == COMBAT_RANGED
             && m_movementOrder != MOVEMENT_STAY
             && GetClassAI()->GetWaitUntil() == 0)  // Not waiting
    {
        // ranged combat - just move within spell range if bot does not have heal orders
        if (!CanReachWithSpellAttack(m_targetCombat) && !IsHealer())
        {
            m_bot->GetMotionMaster()->Clear(false);
            m_bot->GetMotionMaster()->MoveChase(m_targetCombat);
        }
        else
            MovementClear();
    }
}

/*
 * IsGroupReady()
 *
 * return false if any member of the group is in combat or (error handling only) occupied in some way
 * return true otherwise
 */
bool PlayerbotAI::IsGroupReady()
{
    if (!m_bot) return true;
    if (!m_bot->isAlive() || m_bot->IsInDuel()) return false; // Let's just say you're otherwise occupied
    if (m_bot->isInCombat()) return false;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (groupMember && groupMember->isAlive())
            {
                if (groupMember->IsInDuel() || groupMember->isInCombat())            // all occupied in some way
                    return false;
            }
        }
    }

    return true;
}

Player* PlayerbotAI::GetGroupTank()
{
    if (!m_bot) return nullptr;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        // First loop: we look for a main tank (only bots with JOB_MAIN_TANK) can announce themselves as main tank
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI())
                continue;
            if (groupMember->GetPlayerbotAI()->IsMainTank())
                return groupMember;
        }
        // Second loop: we look for any tank (bots with JOB_TANK or human players with the right class/spec combination)
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (groupMember)
            {
                if (!groupMember->GetPlayerbotAI() && m_bot->GetPlayerbotAI()->GetClassAI()->GetTargetJob(groupMember) & JOB_TANK)
                    return groupMember;
                else if (groupMember->GetPlayerbotAI() && groupMember->GetPlayerbotAI()->IsTank())
                    return groupMember;
            }
        }
    }

    return nullptr;
}

void PlayerbotAI::SetGroupCombatOrder(CombatOrderType co)
{
    if (!m_bot) return;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI())
                continue;
            groupMember->GetPlayerbotAI()->SetCombatOrder(co);
        }
    }
    else
        SetCombatOrder(co);
}

void PlayerbotAI::ClearGroupCombatOrder(CombatOrderType co)
{
    if (!m_bot) return;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI())
                continue;
            groupMember->GetPlayerbotAI()->ClearCombatOrder(co);
        }
    }
    else
        ClearCombatOrder(co);
}

void PlayerbotAI::SetGroupIgnoreUpdateTime(uint8 t)
{
    if (!m_bot) return;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI())
                continue;
            groupMember->GetPlayerbotAI()->SetIgnoreUpdateTime(t);
        }
    }
    else
        SetIgnoreUpdateTime(t);
}

bool PlayerbotAI::GroupHoTOnTank()
{
    if (!m_bot) return false;

    bool bReturn = false;

    if (m_bot->GetGroup())
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI())
                continue;
            if (groupMember->GetPlayerbotAI()->GetClassAI()->CastHoTOnTank())
                bReturn = true;
        }

        if (bReturn)
        {
            for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
            {
                Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
                if (!groupMember || !groupMember->GetPlayerbotAI())
                    continue;
                groupMember->GetPlayerbotAI()->SetIgnoreUpdateTime(1);
            }
        }
    }
    else // No group
    {
        if (GetClassAI()->CastHoTOnTank())
        {
            SetIgnoreUpdateTime(1);
            return true;
        }
    }

    return bReturn;
}

bool PlayerbotAI::CanPull(Player& fromPlayer)
{
    if (!m_bot) return false;
    if (!GetClassAI()) return false;

    if (!m_bot->GetGroup() || fromPlayer.GetGroup() != m_bot->GetGroup())
    {
        SendWhisper("I can't pull - we're not in the same group.", fromPlayer);
        return false;
    }

    if (!IsGroupReady()) // TODO: add raid support
    {
        SendWhisper("Unable to pull - the group or one of its member is somehow busy.", fromPlayer);
        return false;
    }

    if (!IsTank())
    {
        SendWhisper("I cannot pull as I do not have combat orders to tank.", fromPlayer);
        return false;
    }

    switch (m_bot->getClass())
    {
        case CLASS_PALADIN:
            if (((PlayerbotPaladinAI*)GetClassAI())->CanPull() == false)
            {
                SendWhisper("I cannot pull, I do not have the proper spell or it's not ready yet.", fromPlayer);
                return false;
            }
            break;

        case CLASS_DRUID:
            if (((PlayerbotDruidAI*)GetClassAI())->CanPull() == false)
            {
                SendWhisper("I cannot pull, I do not have the proper spell or it's not ready yet.", fromPlayer);
                return false;
            }
            break;

        case CLASS_WARRIOR:
            if (((PlayerbotWarriorAI*)GetClassAI())->CanPull() == false)
            {
                SendWhisper("I cannot pull, I do not have the proper weapon and/or ammo.", fromPlayer);
                return false;
            }
            break;

        default:
            SendWhisper("I cannot pull, I am not a tanking class.", fromPlayer);
            return false;
    }

    return true;
}

// This function assumes a "CanPull()" call was preceded (not doing so will result in odd behavior)
bool PlayerbotAI::CastPull()
{
    if (!m_bot) return false;
    if (!GetClassAI()) return false;
    if (!GetCurrentTarget()) return false;

    if (!IsTank()) return false;

    switch (m_bot->getClass())
    {
        case CLASS_PALADIN:
            return ((PlayerbotPaladinAI*)GetClassAI())->Pull();

        case CLASS_DRUID:
            return ((PlayerbotDruidAI*)GetClassAI())->Pull();

        case CLASS_WARRIOR:
            return ((PlayerbotWarriorAI*)GetClassAI())->Pull();

        default:
            return false;
    }

    return false;
}

bool PlayerbotAI::GroupTankHoldsAggro()
{
    if (!m_bot) return false;

    // update attacker info now
    UpdateAttackerInfo();

    if (m_bot->GetGroup())
    {
        Unit* newTarget = FindAttacker((ATTACKERINFOTYPE)(AIT_VICTIMNOTSELF), GetGroupTank());
        if (newTarget)
        {
            return false;
        }
    }
    else
        return false; // no group -> no group tank to hold aggro

    return true;
}

// Wrapper for the UpdateAI cast subfunction
// Each bot class neutralize function will return a spellId
// depending on the creatureType of the target
bool PlayerbotAI::CastNeutralize()
{
    if (!m_bot) return false;
    if (!GetClassAI()) return false;
    if (!m_targetGuidCommand) return false;

    Unit* pTarget = ObjectAccessor::GetUnit(*m_bot, m_targetGuidCommand);
    if (!pTarget) return false;

    Creature* pCreature = (Creature*) pTarget;
    if (!pCreature) return false;

    // Define the target's creature type, so the bot AI will now if
    // it can neutralize it
    uint8 creatureType = 0;
    creatureType = pCreature->GetCreatureInfo()->CreatureType;

    switch (m_bot->getClass())
    {
        case CLASS_DRUID:
            m_spellIdCommand = ((PlayerbotDruidAI*)GetClassAI())->Neutralize(creatureType);
            break;
        case CLASS_PRIEST:
            m_spellIdCommand = ((PlayerbotPriestAI*)GetClassAI())->Neutralize(creatureType);
            break;
        case CLASS_MAGE:
            m_spellIdCommand = ((PlayerbotMageAI*)GetClassAI())->Neutralize(creatureType);
            break;
        case CLASS_WARLOCK:
            m_spellIdCommand = ((PlayerbotWarlockAI*)GetClassAI())->Neutralize(creatureType);
            break;
        default:
            return false;
    }

    // A spellId was found
    if (m_spellIdCommand != 0)
        return true;

    return false;
}

void PlayerbotAI::SetQuestNeedCreatures()
{
    // reset values first
    m_needCreatureOrGOList.clear();

    // run through accepted quests, get quest info and data
    for (int qs = 0; qs < MAX_QUEST_LOG_SIZE; ++qs)
    {
        uint32 questid = m_bot->GetQuestSlotQuestId(qs);
        if (questid == 0)
            continue;

        QuestStatusData& qData = m_bot->getQuestStatusMap()[questid];
        // only check quest if it is incomplete
        if (qData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        Quest const* qInfo = sObjectMgr.GetQuestTemplate(questid);
        if (!qInfo)
            continue;

        // All creature/GO slain/casted (not required, but otherwise it will display "Creature slain 0/10")
        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
        {
            if (!qInfo->ReqCreatureOrGOCount[i] || (qInfo->ReqCreatureOrGOCount[i] - qData.m_creatureOrGOcount[i]) <= 0)
                continue;
            m_needCreatureOrGOList[qInfo->ReqCreatureOrGOId[i]] = (qInfo->ReqCreatureOrGOCount[i] - qData.m_creatureOrGOcount[i]);
        }
    }
}

void PlayerbotAI::SetQuestNeedItems()
{
    // reset values first
    m_needItemList.clear();
    m_botQuestLoot.clear();

    // run through accepted quests, get quest info and data
    for (int qs = 0; qs < MAX_QUEST_LOG_SIZE; ++qs)
    {
        uint32 questid = m_bot->GetQuestSlotQuestId(qs);
        if (questid == 0)
            continue;

        QuestStatusData& qData = m_bot->getQuestStatusMap()[questid];
        // only check quest if it is incomplete
        if (qData.m_status != QUEST_STATUS_INCOMPLETE)
            continue;

        Quest const* qInfo = sObjectMgr.GetQuestTemplate(questid);
        if (!qInfo)
            continue;

        // check for items we not have enough of
        for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; i++)
        {
            if (!qInfo->ReqItemCount[i] || (qInfo->ReqItemCount[i] - qData.m_itemcount[i]) <= 0)
                continue;

            m_needItemList[qInfo->ReqItemId[i]] = (qInfo->ReqItemCount[i] - qData.m_itemcount[i]);

            // collect flags not set to gather quest objects skip remaining section
            if (!HasCollectFlag(COLLECT_FLAG_NEAROBJECT) && !HasCollectFlag(COLLECT_FLAG_QUEST))
                continue;

            // TODO: find faster way to handle this look up instead of using SQL lookup for each item
            QueryResult* result;
            result = WorldDatabase.PQuery("SELECT gt.entry FROM gameobject_template gt "
                                          "LEFT JOIN gameobject_loot_template glt ON gt.data1 = glt.entry WHERE glt.item = '%u'", qInfo->ReqItemId[i]);

            if (result)
            {
                do
                {
                    Field* fields = result->Fetch();
                    uint32 entry = fields[0].GetUInt32();

                    GameObjectInfo const* gInfo = ObjectMgr::GetGameObjectInfo(entry);
                    if (!gInfo)
                        continue;

                    // add this GO to our collection list if is chest/ore/herb
                    if (gInfo->type == GAMEOBJECT_TYPE_CHEST)
                    {
                        m_botQuestLoot.push_back(std::pair<uint32, uint32>(gInfo->GetLootId(), qInfo->ReqItemId[i]));
                        m_botQuestLoot.unique();
                        m_collectObjects.push_back(entry);
                        m_collectObjects.sort();
                        m_collectObjects.unique();
                    }
                }
                while (result->NextRow());

                delete result;
            }
        }
    }
}

void PlayerbotAI::SetState(BotState state)
{
    // DEBUG_LOG ("[PlayerbotAI]: SetState - %s switch state %d to %d", m_bot->GetName(), m_botState, state );
    m_botState = state;
}

uint32 PlayerbotAI::GetFreeBagSpace() const
{
    uint32 totalused = 0;
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        const Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
            totalused++;
    }
    uint32 totalfree = 16 - totalused;
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
                totalfree =  totalfree + pBag->GetFreeSlots();
        }
    }
    return totalfree;
}

void PlayerbotAI::DoFlight()
{
    // DEBUG_LOG("[PlayerbotAI]: DoFlight - %s : %s", m_bot->GetName(), m_taxiMaster.GetString().c_str());

    Creature* npc = m_bot->GetNPCIfCanInteractWith(m_taxiMaster, UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!npc)
    {
        DEBUG_LOG("[PlayerbotAI]: DoFlight - %s not found or you can't interact with it.", m_taxiMaster.GetString().c_str());
        return;
    }

    m_bot->ActivateTaxiPathTo(m_taxiNodes, npc);
}

void PlayerbotAI::DoLoot()
{
    // clear BOTSTATE_LOOTING if no more loot targets
    if (m_lootCurrent.IsEmpty() && m_lootTargets.empty())
    {
        // DEBUG_LOG ("[PlayerbotAI]: DoLoot - %s is going back to idle", m_bot->GetName());
        SetState(BOTSTATE_NORMAL);
        m_bot->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_LOOTING);
        m_inventory_full = false;
        AutoUpgradeEquipment();
        return;
    }

    // set first in list to current
    if (m_lootCurrent.IsEmpty())
    {
        m_lootCurrent = m_lootTargets.front();
        m_lootTargets.pop_front();
    }

    WorldObject* wo = m_bot->GetMap()->GetWorldObject(m_lootCurrent);

    // clear invalid object or object that is too far from master
    if (!wo || GetMaster()->GetDistance(wo) > float(m_mgr->m_confCollectDistanceMax))
    {
        m_lootCurrent = ObjectGuid();
        if (GetManager()->m_confDebugWhisper)
            TellMaster("Object is too far away.");
        return;
    }

    Creature* c = nullptr;
    GameObject* go = nullptr;
    if (m_lootCurrent.IsAnyTypeCreature())
        c = static_cast<Creature*>(wo);
    else if (m_lootCurrent.IsGameObject())
        go = static_cast<GameObject*>(wo);

    // clear creature or object that is not spawned or if not creature or object
    if ((c && c->IsDespawned()) || (go && !go->IsSpawned()) || (!c && !go))
    {
        m_lootCurrent = ObjectGuid();
        if (GetManager()->m_confDebugWhisper)
            TellMaster("Object is not spawned.");
        return;
    }

    uint32 skillId = 0;

    if (c)
    {
        if (c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            skillId = c->GetCreatureInfo()->GetRequiredLootSkill();

        // not a lootable creature, clear it
        if ((!c->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) &&
                !c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE)) ||
                (c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE) && !m_bot->HasSkill(skillId)))
        {
            m_lootCurrent = ObjectGuid();
            // clear movement target, take next target on next update
            m_bot->GetMotionMaster()->Clear(false);
            m_bot->GetMotionMaster()->MoveIdle();
            return;
        }
        else if (c->loot && !c->loot->CanLoot(m_bot) && !c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
        {
            if (GetManager()->m_confDebugWhisper)
                TellMaster("%s is not lootable by me.", wo->GetName());
            m_lootCurrent = ObjectGuid();
            // clear movement target, take next target on next update
            m_bot->GetMotionMaster()->Clear(false);
            m_bot->GetMotionMaster()->MoveIdle();
            return;
        }
    }

    if (m_bot->GetDistance(wo) > CONTACT_DISTANCE + wo->GetObjectBoundingRadius())
    {
        m_bot->GetMotionMaster()->MovePoint(wo->GetMapId(), wo->GetPositionX(), wo->GetPositionY(), wo->GetPositionZ());
        // give time to move to point before trying again
        SetIgnoreUpdateTime(1);
        if (GetManager()->m_confDebugWhisper)
            TellMaster("Moving to loot %s", go ? go->GetName() : wo->GetName());
    }

    if (m_bot->GetDistance(wo) < INTERACTION_DISTANCE)
    {
        uint32 reqSkillValue = 0;
        uint32 SkillValue = 0;
        bool keyFailed = false;
        bool skillFailed = false;
        bool forceFailed = false;

        if (GetManager()->m_confDebugWhisper)
            TellMaster("Beginning to loot %s", go ? go->GetName() : wo->GetName());

        if (c)  // creature
        {
            if (c->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) && !c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            {
                // loot the creature
                std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_LOOT, 8));
                *packet << m_lootCurrent;
                m_bot->GetSession()->QueuePacket(std::move(packet));
                return; // no further processing is needed
                // m_lootCurrent is reset in SMSG_LOOT_RESPONSE/SMSG_LOOT_RELEASE_RESPONSE
            }
            else if (c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
                // not all creature skins are leather, some are ore or herb
                if (m_bot->HasSkill(skillId) && ((skillId != SKILL_SKINNING) ||
                                                 (HasCollectFlag(COLLECT_FLAG_SKIN) && skillId == SKILL_SKINNING)))
                {
                    // calculate skinning skill requirement
                    uint32 targetLevel = c->getLevel();
                    reqSkillValue = targetLevel < 10 ? 0 : targetLevel < 20 ? (targetLevel - 10) * 10 : targetLevel * 5;
                }

            // creatures cannot be unlocked or forced open
            keyFailed = true;
            forceFailed = true;
        }

        if (go) // object
        {

            // add this GO to our collection list if active and is chest/ore/herb
            if (go && HasCollectFlag(COLLECT_FLAG_NEAROBJECT) && go->GetGoType() == GAMEOBJECT_TYPE_CHEST)
            {
                m_collectObjects.push_back(go->GetEntry());
                m_collectObjects.sort();
                m_collectObjects.unique();
            }

            uint32 reqItem = 0;

            // check skill or lock on object
            uint32 lockId = go->GetGOInfo()->GetLockId();
            LockEntry const* lockInfo = sLockStore.LookupEntry(lockId);
            if (lockInfo)
                for (int i = 0; i < 8; ++i)
                {
                    if (lockInfo->Type[i] == LOCK_KEY_ITEM)
                    {
                        if (lockInfo->Index[i] > 0)
                        {
                            reqItem = lockInfo->Index[i];
                            if (m_bot->HasItemCount(reqItem, 1))
                                break;
                            continue;
                        }
                    }
                    else if (lockInfo->Type[i] == LOCK_KEY_SKILL)
                    {
                        switch (LockType(lockInfo->Index[i]))
                        {
                            case LOCKTYPE_OPEN:
                                if (CastSpell(3365) == SPELL_CAST_OK)    // Opening
                                    return;
                                break;
                            case LOCKTYPE_CLOSE:
                                if (CastSpell(6233) == SPELL_CAST_OK)    // Closing
                                    return;
                                break;
                            case LOCKTYPE_QUICK_OPEN:
                                if (CastSpell(6247) == SPELL_CAST_OK)    // Opening
                                    return;
                                break;
                            case LOCKTYPE_QUICK_CLOSE:
                                if (CastSpell(6247) == SPELL_CAST_OK)    // Closing
                                    return;
                                break;
                            case LOCKTYPE_OPEN_TINKERING:
                                if (CastSpell(6477) == SPELL_CAST_OK)    // Opening
                                    return;
                                break;
                            case LOCKTYPE_OPEN_KNEELING:
                                if (CastSpell(22810) == SPELL_CAST_OK)    // Opening; listed with 17667 and 22810
                                    return;
                                break;
                            case LOCKTYPE_OPEN_ATTACKING:
                                if (CastSpell(8386) == SPELL_CAST_OK)    // Attacking
                                    return;
                                break;
                            case LOCKTYPE_SLOW_OPEN:
                                if (CastSpell(21651) == SPELL_CAST_OK)   // Opening; also had 26868
                                    return;
                                break;
                            case LOCKTYPE_SLOW_CLOSE:
                                if (CastSpell(21652) == SPELL_CAST_OK)   // Closing
                                    return;
                                break;
                            default:
                                if (SkillByLockType(LockType(lockInfo->Index[i])) > 0)
                                {
                                    skillId = SkillByLockType(LockType(lockInfo->Index[i]));
                                    reqSkillValue = lockInfo->Skill[i];
                                }
                        }
                    }
                }

            // use key on object if available
            if (reqItem > 0 && m_bot->HasItemCount(reqItem, 1))
            {
                UseItem(FindItem(reqItem), TARGET_FLAG_OBJECT, m_lootCurrent);
                m_lootCurrent = ObjectGuid();
                return;
            }
            else
                keyFailed = true;
        }

        // determine bot's skill value for object's required skill
        if (skillId != SKILL_NONE)
            SkillValue = uint32(m_bot->GetSkillValue(skillId));

        // bot has the specific skill or object requires no skill at all
        if ((m_bot->HasSkill(skillId) && skillId != SKILL_NONE) || (skillId == SKILL_NONE && go))
        {
            if (SkillValue < reqSkillValue)
            {
                TellMaster("My skill is not high enough. It requires %u, but mine is %u.",
                           reqSkillValue, SkillValue);
                skillFailed = true;
            }
            switch (skillId)
            {
                case SKILL_MINING:
                    if (HasTool(TC_MINING_PICK) && CastSpell(MINING) == SPELL_CAST_OK)
                        return;
                    else
                        skillFailed = true;
                    break;
                case SKILL_HERBALISM:
                    if (CastSpell(HERB_GATHERING) == SPELL_CAST_OK)
                        return;
                    else
                        skillFailed = true;
                    break;
                case SKILL_SKINNING:
                    if (c && HasCollectFlag(COLLECT_FLAG_SKIN) &&
                            HasTool(TC_SKINNING_KNIFE) && CastSpell(SKINNING, *c) == SPELL_CAST_OK)
                        return;
                    else
                        skillFailed = true;
                    break;
                case SKILL_LOCKPICKING:
                    if (CastSpell(PICK_LOCK_1) == SPELL_CAST_OK)
                        return;
                    else
                        skillFailed = true;
                    break;
                case SKILL_NONE:
                    if (CastSpell(3365) == SPELL_CAST_OK) //Spell 3365 = Opening?
                        return;
                    else
                        skillFailed = true;
                    break;
                default:
                    TellMaster("I'm not sure how to get that.");
                    skillFailed = true;
                    DEBUG_LOG("[PlayerbotAI]:DoLoot Skill %u is not implemented", skillId);
                    break;
            }
        }
        else
        {
            TellMaster("I do not have the required skill.");
            skillFailed = true;
        }

        if (go) // only go's can be forced
        {
            // if pickable, check if a forcible item is available for the bot
            if (skillId == SKILL_LOCKPICKING && (m_bot->HasSkill(SKILL_BLACKSMITHING) ||
                                                 m_bot->HasSkill(SKILL_ENGINEERING)))
            {
                // check for skeleton keys appropriate for lock value
                if (m_bot->HasSkill(SKILL_BLACKSMITHING))
                {
                    Item* kItem = FindKeyForLockValue(reqSkillValue);
                    if (kItem)
                    {
                        TellMaster("I have a skeleton key that can open it!");
                        UseItem(kItem, TARGET_FLAG_OBJECT, m_lootCurrent);
                        return;
                    }
                    else
                    {
                        TellMaster("I have no skeleton keys that can open that lock.");
                        forceFailed = true;
                    }
                }

                // check for a charge that can blast it open
                if (m_bot->HasSkill(SKILL_ENGINEERING))
                {
                    Item* bItem = FindBombForLockValue(reqSkillValue);
                    if (bItem)
                    {
                        TellMaster("I can blast it open!");
                        UseItem(bItem, TARGET_FLAG_OBJECT, m_lootCurrent);
                        return;
                    }
                    else
                    {
                        TellMaster("I have nothing to blast it open with.");
                        forceFailed = true;
                    }
                }
            }
            else
                forceFailed = true;
        }

        // DEBUG_LOG ("[PlayerbotAI]%s: keyFailed [%s]", m_bot->GetName(), keyFailed ? "true" : "false");
        // DEBUG_LOG ("[PlayerbotAI]%s: skillFailed [%s]", m_bot->GetName(), skillFailed ? "true" : "false");
        // DEBUG_LOG ("[PlayerbotAI]%s: forceFailed [%s]", m_bot->GetName(), forceFailed ? "true" : "false");

        // if all attempts failed in some way then clear because it won't get SMSG_LOOT_RESPONSE
        if (keyFailed && skillFailed && forceFailed)
        {
            DEBUG_LOG("[PlayerbotAI]: DoLoot attempts failed on [%s]",
                      go ? go->GetGOInfo()->name : c->GetCreatureInfo()->Name);
            m_lootCurrent = ObjectGuid();

            // remove this GO from our list using the same settings that it was added with earlier
            if (go && HasCollectFlag(COLLECT_FLAG_NEAROBJECT) && go->GetGoType() == GAMEOBJECT_TYPE_CHEST)
                m_collectObjects.remove(go->GetEntry());
        }
        // clear movement target, take next target on next update
        m_bot->GetMotionMaster()->Clear(false);
        m_bot->GetMotionMaster()->MoveIdle();
    }
}

void PlayerbotAI::AcceptQuest(Quest const* qInfo, Player* pGiver)
{
    if (!qInfo || !pGiver)
        return;

    uint32 quest = qInfo->GetQuestId();

    if (!pGiver->CanShareQuest(qInfo->GetQuestId()))
    {
        // giver can't share quest
        m_bot->ClearDividerGuid();
        return;
    }

    if (!m_bot->CanTakeQuest(qInfo, false))
    {
        // can't take quest
        m_bot->ClearDividerGuid();
        return;
    }

    if (m_bot->GetDividerGuid())
    {
        // send msg to quest giving player
        pGiver->SendPushToPartyResponse(m_bot, QUEST_PARTY_MSG_ACCEPT_QUEST);
        m_bot->ClearDividerGuid();
    }

    if (m_bot->CanAddQuest(qInfo, false))
    {
        m_bot->AddQuest(qInfo, pGiver);

        if (m_bot->CanCompleteQuest(quest))
            m_bot->CompleteQuest(quest);

        // build needed items if quest contains any
        for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; i++)
            if (qInfo->ReqItemCount[i] > 0)
            {
                SetQuestNeedItems();
                break;
            }

        // build needed creatures if quest contains any
        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
            if (qInfo->ReqCreatureOrGOCount[i] > 0)
            {
                SetQuestNeedCreatures();
                break;
            }

        // Runsttren: did not add typeid switch from WorldSession::HandleQuestgiverAcceptQuestOpcode!
        // I think it's not needed, cause typeid should be TYPEID_PLAYER - and this one is not handled
        // there and there is no default case also.

        if (qInfo->GetSrcSpell() > 0)
            m_bot->CastSpell(m_bot, qInfo->GetSrcSpell(), TRIGGERED_OLD_TRIGGERED);
    }
}

void PlayerbotAI::TurnInQuests(WorldObject* questgiver)
{
    ObjectGuid giverGUID = questgiver->GetObjectGuid();

    if (!m_bot->IsInMap(questgiver))
        TellMaster("hey you are turning in quests without me!");
    else
    {
        m_bot->SetSelectionGuid(giverGUID);

        // auto complete every completed quest this NPC has
        m_bot->PrepareQuestMenu(giverGUID);
        QuestMenu& questMenu = m_bot->PlayerTalkClass->GetQuestMenu();
        for (uint32 iI = 0; iI < questMenu.MenuItemCount(); ++iI)
        {
            QuestMenuItem const& qItem = questMenu.GetItem(iI);
            uint32 questID = qItem.m_qId;
            Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);

            std::ostringstream out;
            std::string questTitle  = pQuest->GetTitle();
            QuestLocalization(questTitle, questID);

            QuestStatus status = m_bot->GetQuestStatus(questID);

            // if quest is complete, turn it in
            if (status == QUEST_STATUS_COMPLETE)
            {
                // if bot hasn't already turned quest in
                if (!m_bot->GetQuestRewardStatus(questID))
                {
                    // auto reward quest if no choice in reward
                    if (pQuest->GetRewChoiceItemsCount() == 0)
                    {
                        if (m_bot->CanRewardQuest(pQuest, false))
                        {
                            m_bot->RewardQuest(pQuest, 0, questgiver, false);
                            out << "Quest complete: |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
                        }
                        else
                            out << "|cffff0000Unable to turn quest in:|r |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
                    }

                    // auto reward quest if one item as reward
                    else if (pQuest->GetRewChoiceItemsCount() == 1)
                    {
                        int rewardIdx = 0;
                        ItemPrototype const* pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
                        std::string itemName = pRewardItem->Name1;
                        ItemLocalization(itemName, pRewardItem->ItemId);
                        if (m_bot->CanRewardQuest(pQuest, rewardIdx, false))
                        {
                            m_bot->RewardQuest(pQuest, rewardIdx, questgiver, true);

                            std::string itemName = pRewardItem->Name1;
                            ItemLocalization(itemName, pRewardItem->ItemId);

                            out << "Quest complete: "
                                << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel()
                                << "|h[" << questTitle << "]|h|r reward: |cffffffff|Hitem:"
                                << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                        }
                        else
                            out << "|cffff0000Unable to turn quest in:|r "
                                << "|cff808080|Hquest:" << questID << ':'
                                << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r"
                                << " reward: |cffffffff|Hitem:"
                                << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                    }

                    // else multiple rewards - let master pick
                    else
                    {
                        out << "What reward should I take for |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel()
                            << "|h[" << questTitle << "]|h|r? ";
                        for (uint8 i = 0; i < pQuest->GetRewChoiceItemsCount(); ++i)
                        {
                            ItemPrototype const* const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[i]);
                            std::string itemName = pRewardItem->Name1;
                            ItemLocalization(itemName, pRewardItem->ItemId);
                            out << "|cffffffff|Hitem:" << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r";
                        }
                    }
                }
            }

            else if (status == QUEST_STATUS_INCOMPLETE)
                out << "|cffff0000Quest incomplete:|r "
                    << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";

            else if (status == QUEST_STATUS_AVAILABLE)
                out << "|cff00ff00Quest available:|r "
                    << " |cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";

            if (!out.str().empty())
                TellMaster(out.str());
        }
        AutoUpgradeEquipment();
    }
}

bool PlayerbotAI::IsInCombat()
{
    Pet* pet;
    bool inCombat = false;
    inCombat |= m_bot->isInCombat();
    pet = m_bot->GetPet();
    if (pet)
        inCombat |= pet->isInCombat();
    inCombat |= GetMaster()->isInCombat();
    if (m_bot->GetGroup())
    {
        GroupReference* ref = m_bot->GetGroup()->GetFirstMember();
        while (ref)
        {
            inCombat |= ref->getSource()->isInCombat();
            pet = ref->getSource()->GetPet();
            if (pet)
                inCombat |= pet->isInCombat();
            ref = ref->next();
        }
    }
    return inCombat;
}

bool PlayerbotAI::IsRegenerating()
{
    Unit::SpellAuraHolderMap& auras = m_bot->GetSpellAuraHolderMap();
    for (Unit::SpellAuraHolderMap::iterator aura = auras.begin(); aura != auras.end(); aura++)
    {
        SpellEntry const* spell = aura->second->GetSpellProto();
        if (!spell)
            continue;
        if (spell->Category == 59 || spell->Category == 11)
        {
            return true;
        }
    }
    if (m_bot->getStandState() != UNIT_STAND_STATE_STAND)
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);
    return false;
}

void PlayerbotAI::UpdateAttackersForTarget(Unit* victim)
{
    HostileReference* ref = victim->getHostileRefManager().getFirst();
    while (ref)
    {
        ThreatManager* target = ref->getSource();
        ObjectGuid guid = target->getOwner()->GetObjectGuid();
        m_attackerInfo[guid].attacker = target->getOwner();
        m_attackerInfo[guid].victim = target->getOwner()->getVictim();
        m_attackerInfo[guid].threat = target->getThreat(victim);
        m_attackerInfo[guid].count = 1;
        //m_attackerInfo[guid].source = 1; // source is not used so far.
        ref = ref->next();
    }
}

void PlayerbotAI::UpdateAttackerInfo()
{
    // clear old list
    m_attackerInfo.clear();

    // check own attackers
    UpdateAttackersForTarget(m_bot);
    Pet* pet = m_bot->GetPet();
    if (pet)
        UpdateAttackersForTarget(pet);

    // check master's attackers
    UpdateAttackersForTarget(GetMaster());
    pet = GetMaster()->GetPet();
    if (pet)
        UpdateAttackersForTarget(pet);

    // check all group members now
    if (m_bot->GetGroup())
    {
        GroupReference* gref = m_bot->GetGroup()->GetFirstMember();
        while (gref)
        {
            if (gref->getSource() == m_bot || gref->getSource() == GetMaster())
            {
                gref = gref->next();
                continue;
            }

            UpdateAttackersForTarget(gref->getSource());
            pet = gref->getSource()->GetPet();
            if (pet)
                UpdateAttackersForTarget(pet);

            gref = gref->next();
        }
    }

    // get highest threat not caused by bot for every entry in AttackerInfoList...
    for (AttackerInfoList::iterator itr = m_attackerInfo.begin(); itr != m_attackerInfo.end(); ++itr)
    {
        if (!itr->second.attacker)
            continue;
        Unit* a = itr->second.attacker;
        float t = 0.00;
        std::list<HostileReference*>::const_iterator i = a->getThreatManager().getThreatList().begin();
        for (; i != a->getThreatManager().getThreatList().end(); ++i)
        {
            if ((*i)->getThreat() > t && (*i)->getTarget() != m_bot)
                t = (*i)->getThreat();
        }
        m_attackerInfo[itr->first].threat2 = t;
    }

    // DEBUG: output attacker info
    //sLog.outBasic( "[PlayerbotAI]: %s m_attackerInfo = {", m_bot->GetName() );
    //for( AttackerInfoList::iterator i=m_attackerInfo.begin(); i!=m_attackerInfo.end(); ++i )
    //    sLog.outBasic( "[PlayerbotAI]:     [%016I64X] { %08X, %08X, %.2f, %.2f, %d, %d }",
    //        i->first,
    //        (i->second.attacker?i->second.attacker->GetGUIDLow():0),
    //        (i->second.victim?i->second.victim->GetGUIDLow():0),
    //        i->second.threat,
    //        i->second.threat2,
    //        i->second.count,
    //        i->second.source );
    //sLog.outBasic( "[PlayerbotAI]: };" );
}

uint32 PlayerbotAI::EstRepairAll()
{
    uint32 TotalCost = 0;
    // equipped, backpack, bags itself
    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
        TotalCost += EstRepair(((INVENTORY_SLOT_BAG_0 << 8) | i));

    // bank, buyback and keys not repaired

    // items in inventory bags
    for (int j = INVENTORY_SLOT_BAG_START; j < INVENTORY_SLOT_BAG_END; ++j)
        for (int i = 0; i < MAX_BAG_SIZE; ++i)
            TotalCost += EstRepair(((j << 8) | i));
    return TotalCost;
}

uint32 PlayerbotAI::EstRepair(uint16 pos)
{
    Item* item = m_bot->GetItemByPos(pos);

    uint32 TotalCost = 0;
    if (!item)
        return TotalCost;

    uint32 maxDurability = item->GetUInt32Value(ITEM_FIELD_MAXDURABILITY);
    if (!maxDurability)
        return TotalCost;

    uint32 curDurability = item->GetUInt32Value(ITEM_FIELD_DURABILITY);

    uint32 LostDurability = maxDurability - curDurability;
    if (LostDurability > 0)
    {
        ItemPrototype const* ditemProto = item->GetProto();

        DurabilityCostsEntry const* dcost = sDurabilityCostsStore.LookupEntry(ditemProto->ItemLevel);
        if (!dcost)
        {
            sLog.outError("RepairDurability: Wrong item lvl %u", ditemProto->ItemLevel);
            return TotalCost;
        }

        uint32 dQualitymodEntryId = (ditemProto->Quality + 1) * 2;
        DurabilityQualityEntry const* dQualitymodEntry = sDurabilityQualityStore.LookupEntry(dQualitymodEntryId);
        if (!dQualitymodEntry)
        {
            sLog.outError("RepairDurability: Wrong dQualityModEntry %u", dQualitymodEntryId);
            return TotalCost;
        }

        uint32 dmultiplier = dcost->multiplier[ItemSubClassToDurabilityMultiplierId(ditemProto->Class, ditemProto->SubClass)];
        uint32 costs = uint32(LostDurability * dmultiplier * double(dQualitymodEntry->quality_mod));

        if (costs == 0)                                 //fix for ITEM_QUALITY_ARTIFACT
            costs = 1;

        TotalCost = costs;
    }
    return TotalCost;
}

Unit* PlayerbotAI::FindAttacker(ATTACKERINFOTYPE ait, Unit* victim)
{
    // list empty? why are we here?
    if (m_attackerInfo.empty())
        return nullptr;

    // not searching something specific - return first in list
    if (!ait)
        return (m_attackerInfo.begin())->second.attacker;

    float t = ((ait & AIT_HIGHESTTHREAT) ? 0.00 : 9999.00);
    Unit* a = nullptr;
    AttackerInfoList::iterator itr = m_attackerInfo.begin();
    for (; itr != m_attackerInfo.end(); ++itr)
    {
        if ((ait & AIT_VICTIMSELF) && !(ait & AIT_VICTIMNOTSELF) && itr->second.victim != m_bot)
            continue;

        if (!(ait & AIT_VICTIMSELF) && (ait & AIT_VICTIMNOTSELF) && itr->second.victim == m_bot)
            continue;

        if ((ait & AIT_VICTIMNOTSELF) && victim && itr->second.victim != victim)
            continue;

        if (!(ait & (AIT_LOWESTTHREAT | AIT_HIGHESTTHREAT)))
            return itr->second.attacker;
        else
        {
            if ((ait & AIT_HIGHESTTHREAT) && /*(itr->second.victim==m_bot) &&*/ itr->second.threat >= t)
            {
                t = itr->second.threat;
                a = itr->second.attacker;
            }
            else if ((ait & AIT_LOWESTTHREAT) && /*(itr->second.victim==m_bot) &&*/ itr->second.threat <= t)
            {
                t = itr->second.threat;
                a = itr->second.attacker;
            }
        }
    }
    return a;
}

/**
* BotDataRestore()
* Restores autoequip - the toggle status for the 'equip auto' command.
* Restores gDelayAttack - the other attributes need a valid target. This function is to be called when the targets
* may or may not be online (such as upon login). See CombatOrderRestore() for full orders restore.
* Restores m_DelayAttack - the other attributes need a valid target. This function is to be called when the targets
*/
void PlayerbotAI::BotDataRestore()
{
    QueryResult* result = CharacterDatabase.PQuery("SELECT combat_delay,autoequip FROM playerbot_saved_data WHERE guid = '%u'", m_bot->GetGUIDLow());

    if (!result)
    {
        sLog.outString();
        sLog.outString(">> [BotDataRestore()] Loaded `playerbot_saved_data`, found no match for guid %u.", m_bot->GetGUIDLow());
        m_DelayAttack = 0;
        return;
    }
    else
    {
        Field* fields = result->Fetch();
        m_DelayAttack = fields[0].GetUInt8();
        m_AutoEquipToggle = fields[1].GetBool();
        delete result;
    }
}

/**
* CombatOrderRestore()
* Restores all saved attributes. This function is to be called when the targets are assumed to be online.
*/

void PlayerbotAI::CombatOrderRestore()
{
    QueryResult* result = CharacterDatabase.PQuery("SELECT combat_order,primary_target,secondary_target,pname,sname,combat_delay,auto_follow FROM playerbot_saved_data WHERE guid = '%u'", m_bot->GetGUIDLow());

    if (!result)
    {
        sLog.outString();
        sLog.outString(">> [CombatOrderRestore()] Loaded `playerbot_saved_data`, found no match for guid %u.", m_bot->GetGUIDLow());
        TellMaster("I have no orders");
        return;
    }

    Field* fields = result->Fetch();
    CombatOrderType combatOrders = (CombatOrderType)fields[0].GetUInt32();
    ObjectGuid PrimtargetGUID = ObjectGuid(fields[1].GetUInt64());
    ObjectGuid SectargetGUID = ObjectGuid(fields[2].GetUInt64());
    std::string pname = fields[3].GetString();
    std::string sname = fields[4].GetString();
    m_DelayAttack = fields[5].GetUInt8();
    gPrimtarget = ObjectAccessor::GetUnit(*m_bot->GetMap()->GetWorldObject(PrimtargetGUID), PrimtargetGUID);
    gSectarget = ObjectAccessor::GetUnit(*m_bot->GetMap()->GetWorldObject(SectargetGUID), SectargetGUID);
    delete result;

    //Unit* target = nullptr;
    //ObjectGuid NoTargetGUID = m_bot->GetObjectGuid();
    //target = ObjectAccessor::GetUnit(*m_bot, NoTargetGUID);

    if (combatOrders & ORDERS_PRIMARY) SetCombatOrder(combatOrders, gPrimtarget);
    if (combatOrders & ORDERS_SECONDARY) SetCombatOrder(combatOrders, gSectarget);
}

void PlayerbotAI::SetCombatOrderByStr(std::string str, Unit* target)
{
    CombatOrderType co;
    if (str == "tank")              co = ORDERS_TANK;
    else if (str == "maintank")     co = ORDERS_MAIN_TANK;
    else if (str == "assist")       co = ORDERS_ASSIST;
    else if (str == "heal")         co = ORDERS_HEAL;
    else if (str == "mainheal")     co = ORDERS_MAIN_HEAL;
    else if (str == "protect")      co = ORDERS_PROTECT;
    else if (str == "passive")      co = ORDERS_PASSIVE;
    else if (str == "pull")         co = ORDERS_TEMP_WAIT_TANKAGGRO;
    else if (str == "nodispel")     co = ORDERS_NODISPEL;
    else if (str == "resistfrost")  co = ORDERS_RESIST_FROST;
    else if (str == "resistnature") co = ORDERS_RESIST_NATURE;
    else if (str == "resistfire")   co = ORDERS_RESIST_FIRE;
    else if (str == "resistshadow") co = ORDERS_RESIST_SHADOW;
    else                            co = ORDERS_RESET;

    SetCombatOrder(co, target);
    if (m_FollowAutoGo != FOLLOWAUTOGO_OFF)
        m_FollowAutoGo = FOLLOWAUTOGO_INIT;
}

void PlayerbotAI::SetCombatOrder(CombatOrderType co, Unit* target)
{
    uint32 gTempTarget;
    std::string gname;
    if (target)
    {
        gTempTarget = target->GetGUIDLow();
        gname = target->GetName();
    }

    // reset m_combatOrder after ORDERS_PASSIVE
    if (m_combatOrder == ORDERS_PASSIVE)
    {
        m_combatOrder = ORDERS_NONE;
        m_targetAssist = 0;
        m_targetProtect = 0;
    }

    switch (co)
    {
        case ORDERS_ASSIST: // 2(10)
        {
            if (!target)
            {
                TellMaster("The assist command requires a target.");
                return;
            }
            else m_targetAssist = target;
            break;
        }
        case ORDERS_PROTECT: // 10(10000)
        {
            if (!target)
            {
                TellMaster("The protect command requires a target.");
                return;
            }
            else m_targetProtect = target;
            break;
        }
        case ORDERS_PASSIVE: // 20(100000)
        {
            m_combatOrder = ORDERS_PASSIVE;
            m_targetAssist = 0;
            m_targetProtect = 0;
            return;
        }
        case ORDERS_RESET: // FFFF(11111111)
        {
            m_combatOrder = ORDERS_NONE;
            m_targetAssist = 0;
            m_targetProtect = 0;
            m_DelayAttackInit = CurrentTime();
            m_DelayAttack = 0;
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_order = 0, primary_target = 0, secondary_target = 0, pname = '',sname = '', combat_delay = 0 WHERE guid = '%u'", m_bot->GetGUIDLow());
            TellMaster("Orders are cleaned!");
            return;
        }
        default:
            break;
    }

    // Do your magic
    if ((co & ORDERS_PRIMARY))
    {
        m_combatOrder = (CombatOrderType)(((uint32) m_combatOrder & (uint32) ORDERS_SECONDARY) | (uint32) co);
        if (target)
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_order = '%u', primary_target = '%u', pname = '%s' WHERE guid = '%u'", (m_combatOrder & ~ORDERS_TEMP), gTempTarget, gname.c_str(), m_bot->GetGUIDLow());
        else
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_order = '%u' WHERE guid = '%u'", (m_combatOrder & ~ORDERS_TEMP), m_bot->GetGUIDLow());
    }
    else
    {
        m_combatOrder = (CombatOrderType)((uint32)m_combatOrder | (uint32)co);
        if (target)
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_order = '%u', secondary_target = '%u', sname = '%s' WHERE guid = '%u'", (m_combatOrder & ~ORDERS_TEMP), gTempTarget, gname.c_str(), m_bot->GetGUIDLow());
        else
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_order = '%u' WHERE guid = '%u'", (m_combatOrder & ~ORDERS_TEMP), m_bot->GetGUIDLow());
    }
}

void PlayerbotAI::ClearCombatOrder(CombatOrderType co)
{
    m_combatOrder = (CombatOrderType)((uint32) m_combatOrder & (uint32) ~co);

    switch (co)
    {
        case ORDERS_NONE:
        case ORDERS_TANK:
        case ORDERS_MAIN_TANK:
        case ORDERS_ASSIST:
        case ORDERS_HEAL:
        case ORDERS_MAIN_HEAL:
        case ORDERS_PASSIVE:
        case ORDERS_PRIMARY:
        case ORDERS_RESET:
        case ORDERS_SECONDARY:
            SetCombatOrder(ORDERS_RESET);
            return;

        default:
            return;
    }
}

void PlayerbotAI::SetMovementOrder(MovementOrderType mo, Unit* followTarget)
{
    m_movementOrder = mo;
    m_followTarget = followTarget;
    if (m_botState != BOTSTATE_LOADING)
        MovementReset();
}

void PlayerbotAI::MovementReset()
{
    // stop moving...
    MovementClear();
    if (m_movementOrder == MOVEMENT_FOLLOW)
    {
        if (!m_followTarget)
            return;

        // don't follow while in combat
        if (m_bot->isInCombat())
            return;

        Player* pTarget;                            // target is player
        if (m_followTarget->GetTypeId() == TYPEID_PLAYER)
            pTarget = ((Player*) m_followTarget);

        if (pTarget)
        {
            // check player for follow situations
            if (pTarget->IsBeingTeleported() || pTarget->IsTaxiFlying() || pTarget->GetCorpse())
                return;
        }

        // is bot too far from the follow target
        if (!m_bot->IsWithinDistInMap(m_followTarget, 50))
        {
            DoTeleport(*m_followTarget);
            return;
        }

        if (m_bot->isAlive() && !m_bot->IsBeingTeleported())
        {
            if (DistOverRide != 0)
            {
                if (m_FollowAutoGo == FOLLOWAUTOGO_OFF)
                {
                    if (IsUpOrDown < DistOverRide)
                    {
                        IsUpOrDown = DistOverRide;
                        gTempDist = (gTempDist + 1.0);
                        gTempDist2 = (gTempDist2 + 1.0);
                    }
                    if (IsUpOrDown > DistOverRide)
                    {
                        if (IsUpOrDown >= 2)
                        {
                            IsUpOrDown = DistOverRide;
                            gTempDist = (gTempDist - 1.0);
                            gTempDist2 = (gTempDist2 - 1.0);
                        }
                    }
                }
                else
                {
                    if (IsUpOrDown < DistOverRide)
                    {
                        gTempDist = 1.0;
                        gTempDist2 = 2.0;
                        IsUpOrDown = 0;
                        for (IsUpOrDown = 0; IsUpOrDown < DistOverRide; ++IsUpOrDown)
                        {
                            gTempDist = (gTempDist + 1.0);
                            gTempDist2 = (gTempDist2 + 1.0);
                        }
                        IsUpOrDown = DistOverRide;
                    }
                    else if (IsUpOrDown > DistOverRide)
                    {
                        uint8 getdowndist = (IsUpOrDown - DistOverRide);
                        for (uint8 getdowndistb = 0; getdowndistb < getdowndist; ++getdowndistb)
                        {
                            gTempDist = (gTempDist - 1.0);
                            gTempDist2 = (gTempDist2 - 1.0);
                        }
                        IsUpOrDown = DistOverRide;
                    }
                }
                if (m_FollowAutoGo != FOLLOWAUTOGO_RESET)
                {
                    gDist[0] = gTempDist;
                    gDist[1] = gTempDist2;
                }
                else
                {
                    gDist[0] = 0.5f;
                    gDist[1] = 1.0f;
                    SetIgnoreUpdateTime(3);
                    m_FollowAutoGo = FOLLOWAUTOGO_INIT;
                }
            }
            float dist = rand_float(m_mgr->m_confFollowDistance[0], m_mgr->m_confFollowDistance[1]);
            float bdist = rand_float(gDist[0], gDist[1]);
            float angle = rand_float(0, M_PI_F);
            float bangle = rand_float(2.8f, 3.6f); // angle is based on radians
            float TankAngle = 3.1f;
            float AssistAngle = 2.8f;
            if (DistOverRide != 0)
            {
                if (m_combatOrder & ORDERS_TANK)
                    m_bot->GetMotionMaster()->MoveFollow(m_followTarget, bdist, TankAngle);
                else if (m_combatOrder & ORDERS_ASSIST)
                    m_bot->GetMotionMaster()->MoveFollow(m_followTarget, bdist, AssistAngle);
                else
                    m_bot->GetMotionMaster()->MoveFollow(m_followTarget, bdist, bangle);
            }
            else
                m_bot->GetMotionMaster()->MoveFollow(m_followTarget, dist, angle);
            if (m_FollowAutoGo == FOLLOWAUTOGO_RUN)
                m_FollowAutoGo = FOLLOWAUTOGO_INIT;
        }
    }
}

void PlayerbotAI::MovementClear()
{
    // stop...
    m_bot->GetMotionMaster()->Initialize();

    // stand up...
    if (!m_bot->IsStandState())
        m_bot->SetStandState(UNIT_STAND_STATE_STAND);
}

void PlayerbotAI::PlaySound(uint32 soundid)
{
    WorldPacket data(SMSG_PLAY_SOUND, 4);
    data << soundid;
    GetMaster()->GetSession()->SendPacket(data);
}

// PlaySound data from SoundEntries.dbc
void PlayerbotAI::Announce(AnnounceFlags msg)
{
    switch (m_bot->getRace())
    {
        case RACE_HUMAN:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(1908) : PlaySound(2032); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(1875) : PlaySound(1999); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(1924) : PlaySound(2048); break;
                default: break;
            }
            break;
        case RACE_ORC:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(2319) : PlaySound(2374); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(2284) : PlaySound(2341); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(2335) : PlaySound(2390); break;
                default: break;
            }
            break;
        case RACE_DWARF:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(1630) : PlaySound(1686); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(1581) : PlaySound(1654); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(1636) : PlaySound(1702); break;
                default: break;
            }
            break;
        case RACE_NIGHTELF:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(2151) : PlaySound(2262); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(2118) : PlaySound(2229); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(2167) : PlaySound(2278); break;
                default: break;
            }
            break;
        case RACE_UNDEAD:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(2096) : PlaySound(2207); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(2054) : PlaySound(2173); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(2112) : PlaySound(2223); break;
                default: break;
            }
            break;
        case RACE_TAUREN:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(2463) : PlaySound(2462); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(2396) : PlaySound(2397); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(2495) : PlaySound(2494); break;
                default: break;
            }
            break;
        case RACE_GNOME:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(1743) : PlaySound(1798); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(1708) : PlaySound(1709); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(1759) : PlaySound(1814); break;
                default: break;
            }
            break;
        case RACE_TROLL:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(1853) : PlaySound(1963); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(1820) : PlaySound(1930); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(1869) : PlaySound(1993); break;
                default: break;
            }
            break;
        case RACE_BLOODELF:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(9583) : PlaySound(9584); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(9549) : PlaySound(9550); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(9565) : PlaySound(9566); break;
                default: break;
            }
            break;
        case RACE_DRAENEI:
            switch (msg)
            {
                case CANT_AFFORD: m_bot->getGender() == GENDER_MALE ? PlaySound(9498) : PlaySound(9499); break;
                case INVENTORY_FULL: m_bot->getGender() == GENDER_MALE ? PlaySound(9465) : PlaySound(9466); break;
                case CANT_USE_TOO_FAR: m_bot->getGender() == GENDER_MALE ? PlaySound(9481) : PlaySound(9482); break;
                default: break;
            }
            break;
        default:
            break;
    }
}

// some possible things to use in AI
// GetRandomContactPoint
// GetPower, GetMaxPower
// HasSpellCooldown
// IsAffectedBySpellmod
// isMoving
// hasUnitState(FLAG) FLAG like: UNIT_STAT_ROOT, UNIT_STAT_CONFUSED, UNIT_STAT_STUNNED
// hasAuraType

void PlayerbotAI::UpdateAI(const uint32 /*p_time*/)
{
    if (GetClassAI()->GetWaitUntil() <= CurrentTime())
        GetClassAI()->ClearWait();

    if (CurrentTime() < m_ignoreAIUpdatesUntilTime)
        return;

    // default updates occur every two seconds
    SetIgnoreUpdateTime(2);
    
    if (m_botState == BOTSTATE_LOADING)
    {
        if (m_bot->IsBeingTeleported())
            return;
        else
        {
            // is bot too far from the follow target
            if (!m_bot->IsWithinDistInMap(m_followTarget, 50))
            {
                DoTeleport(*m_followTarget);
                return;
            }
            else
                SetState(BOTSTATE_NORMAL);

            return;
        }
    }

    if (m_bot->IsBeingTeleported() || m_bot->GetTrader())
        return;

    if (m_FollowAutoGo == FOLLOWAUTOGO_INIT)
    {
        if (m_combatOrder & ORDERS_TANK)
            DistOverRide = 1;
        else if (m_combatOrder & ORDERS_ASSIST)
            DistOverRide = 3;
        else
            DistOverRide = 4;
        m_FollowAutoGo = FOLLOWAUTOGO_SET;
        SetMovementOrder(MOVEMENT_FOLLOW, GetMaster());
    }

    if (!m_bot->isAlive())
    {
        if (m_botState == BOTSTATE_DEAD)
        {
            // become ghost
            if (m_bot->GetCorpse())
            {
                // DEBUG_LOG ("[PlayerbotAI]: UpdateAI - %s already has a corpse...", m_bot->GetName());
                SetState(BOTSTATE_DEADRELEASED);
                return;
            }
            m_bot->SetBotDeathTimer();
            m_bot->BuildPlayerRepop();
            // relocate ghost
            WorldLocation loc;
            Corpse* corpse = m_bot->GetCorpse();
            corpse->GetPosition(loc);
            m_bot->TeleportTo(loc.mapid, loc.coord_x, loc.coord_y, loc.coord_z, m_bot->GetOrientation());
            // set state to released
            SetState(BOTSTATE_DEADRELEASED);

            return;
        }

        if (m_botState == BOTSTATE_DEADRELEASED)
        {
            // get bot's corpse
            Corpse* corpse = m_bot->GetCorpse();
            if (!corpse)
                // DEBUG_LOG ("[PlayerbotAI]: UpdateAI - %s has no corpse!", m_bot->GetName());
                return;

            // check if we are allowed to resurrect now
            time_t resurrect_time = corpse->GetGhostTime() + m_bot->GetCorpseReclaimDelay(corpse->GetType() == CORPSE_RESURRECTABLE_PVP);
            if (resurrect_time > CurrentTime())
            {
                SetIgnoreUpdateTime(resurrect_time);
                // DEBUG_LOG ("[PlayerbotAI]: UpdateAI - %s has to wait for %d seconds to revive...", m_bot->GetName(), m_ignoreAIUpdatesUntilTime-CurrentTime() );
                return;
            }
            // resurrect now
            // DEBUG_LOG ("[PlayerbotAI]: UpdateAI - Reviving %s to corpse...", m_bot->GetName() );

            SetIgnoreUpdateTime(6);

            PlayerbotChatHandler ch(GetMaster());
            if (!ch.revive(*m_bot))
            {
                ch.sysmessage(".. could not be revived ..");
                return;
            }
            // set back to normal
            SetState(BOTSTATE_NORMAL);

            return;
        }

        // if (m_botState != BOTSTATE_DEAD && m_botState != BOTSTATE_DEADRELEASED)
        // DEBUG_LOG ("[PlayerbotAI]: UpdateAI - %s died and is not in correct state...", m_bot->GetName() );
        // clear loot list on death
        m_lootTargets.clear();
        m_lootCurrent = ObjectGuid();
        // clear combat orders
        m_bot->SetSelectionGuid(ObjectGuid());
        m_bot->GetMotionMaster()->Clear(true);
        // set state to dead
        SetState(BOTSTATE_DEAD);
        // wait 30sec
        SetIgnoreUpdateTime(30);

        return;
    }

    // bot still alive
    if (!m_findNPC.empty())
        findNearbyCreature();

    // if we are casting a spell then interrupt it
    // unless it is a positive spell then bot is helping a friendly unit and the death of an enemy target should not prevent this
    // make sure any actions that cast a spell set a proper m_ignoreAIUpdatesUntilTime!
    Spell* const pSpell = GetCurrentSpell();
    if (pSpell && !(pSpell->IsChannelActive() || pSpell->IsAutoRepeat()) && !IsPositiveSpell(pSpell->m_spellInfo->Id))
    {
        // DEBUG_LOG("spell (%s) is being interrupted",pSpell->m_spellInfo->SpellName[0]);
        InterruptCurrentCastingSpell();
        return;
    }

    if (m_botState == BOTSTATE_TAME)
    {
        Unit* pTarget = ObjectAccessor::GetUnit(*m_bot, m_targetGuidCommand);
        if (!pTarget)
            return;

        m_bot->SetSelectionGuid(m_targetGuidCommand);

        if (!In_Range(pTarget, TAME_BEAST_1))
            m_bot->clearUnitState(UNIT_STAT_CHASE);

        if (!m_bot->hasUnitState(UNIT_STAT_CHASE))
        {
            m_bot->GetMotionMaster()->MoveChase(pTarget);
            return;
        }

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(TAME_BEAST_1);
        if (!spellInfo)
            return;

        Spell* spell = new Spell(m_bot, spellInfo, false);
        if (!spell)
            return;

        if (m_bot->GetPetGuid() || spell->CheckCast(true) != SPELL_CAST_OK || !pTarget ||
                pTarget->isDead() || !m_bot->IsInMap(pTarget) || !(((Creature*) pTarget)->GetCreatureInfo()->CreatureTypeFlags & CREATURE_TYPEFLAGS_TAMEABLE))
        {
            MovementReset();
            m_bot->SetSelectionGuid(ObjectGuid());
            SetState(BOTSTATE_NORMAL);
            SetIgnoreUpdateTime(0);
        }
        else if (!m_bot->HasAura(TAME_BEAST_1, EFFECT_INDEX_1))
        {
            m_bot->SetFacingTo(m_bot->GetAngle(pTarget));
            SpellCastTargets targets;
            targets.setUnitTarget(pTarget);
            spell->SpellStart(&targets);
            SetIgnoreUpdateTime(10);
        }
        return;
    }

    // direct cast command from master
    if (m_spellIdCommand != 0)
    {
        Unit* pTarget = ObjectAccessor::GetUnit(*m_bot, m_targetGuidCommand);
        if (pTarget)
        {
            // Face the target to avoid facing casting error
            FaceTarget(pTarget);
            CastSpell(m_spellIdCommand, *pTarget);
        }
        m_spellIdCommand = 0;
        m_targetGuidCommand = ObjectGuid();

        return;
    }

    if (m_botState == BOTSTATE_DELAYED)
    {
        if (m_CraftSpellId == 0)
        {
            SetState(BOTSTATE_NORMAL);
            AutoUpgradeEquipment();
            return;
        }

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(m_CraftSpellId);
        if (!spellInfo)
            return;

        Spell* spell = new Spell(m_bot, spellInfo, false);
        if (!spell)
            return;

        if (GetSpellCharges(m_CraftSpellId) == 0 || spell->CheckCast(true) != SPELL_CAST_OK)
        {
            SetState(BOTSTATE_NORMAL);
            SetIgnoreUpdateTime(0);
            AutoUpgradeEquipment();
            m_CraftSpellId = 0;
        }
        else
        {
            SpellCastTargets targets;
            spell->SpellStart(&targets);
            SetIgnoreUpdateTime(6);
        }

        return;
    }

    //if master is unmounted, unmount the bot
    if (!GetMaster()->IsMounted() && m_bot->IsMounted())
    {
        WorldPacket emptyPacket;
        m_bot->GetSession()->HandleCancelMountAuraOpcode(emptyPacket);  //updated code

        return;
    }

    // handle combat (either self/master/group in combat, or combat state and valid target)
    if (IsInCombat() || (m_botState == BOTSTATE_COMBAT && m_targetCombat) ||  m_ScenarioType == SCENARIO_PVP_DUEL)
    {
        //check if the bot is Mounted
        if (!m_bot->IsMounted())
        {
            if (!pSpell || !pSpell->IsChannelActive())
            {
                // DEBUG_LOG("m_DelayAttackInit (%li) + m_DelayAttack (%u) > time(%li)", m_DelayAttackInit, m_DelayAttack, CurrentTime());
                if (m_DelayAttackInit + m_DelayAttack > CurrentTime())
                    return SetIgnoreUpdateTime(1); // short bursts of delay

                return DoNextCombatManeuver();
            }
            else // channelling a spell
                return SetIgnoreUpdateTime(0);  // It's better to update AI more frequently during combat
        }

        return;
    }

    // bot was in combat recently - loot now
    if (m_botState == BOTSTATE_COMBAT)
    {
        if (GetCombatOrder() & ORDERS_TEMP)
        {
            if (GetCombatOrder() & ORDERS_TEMP_WAIT_TANKAGGRO)
                TellMaster("I was still waiting for the tank to gain aggro, but that doesn't make sense anymore...");
            if (GetCombatOrder() & ORDERS_TEMP_WAIT_OOC)
                TellMaster("I was still waiting OOC but I just got out of combat...");
            ClearCombatOrder(ORDERS_TEMP);
        }
        SetState(BOTSTATE_LOOTING);
        m_attackerInfo.clear();
        if (HasCollectFlag(COLLECT_FLAG_COMBAT))
            m_lootTargets.unique();
        else
            m_lootTargets.clear();
    }

    if (m_botState == BOTSTATE_LOOTING)
        return DoLoot();

    if (m_botState == BOTSTATE_FLYING)
    {
        /* std::ostringstream out;
        out << "Taxi: " << m_bot->GetName() << m_ignoreAIUpdatesUntilTime;
        TellMaster(out.str().c_str());*/
        DoFlight();
        SetState(BOTSTATE_NORMAL);
        SetIgnoreUpdateTime(0);
        return;
    }

    // if commanded to follow master and not already following master then follow master
    if (!m_bot->isInCombat() && !m_bot->IsMoving())
        return MovementReset();

    // do class specific non combat actions
    if (GetClassAI() && !m_bot->IsMounted() && !IsRegenerating())
    {
        GetClassAI()->DoNonCombatActions();

        // have we been told to collect loot after combat
        if (HasCollectFlag(COLLECT_FLAG_LOOT))
        {
            findNearbyCorpse();
            // start looting if have targets
            if (!m_lootTargets.empty())
                SetState(BOTSTATE_LOOTING);
        }

        // have we been told to collect GOs
        if (HasCollectFlag(COLLECT_FLAG_NEAROBJECT))
        {
            findNearbyGO();
            // start looting if have targets
            if (!m_lootTargets.empty())
                SetState(BOTSTATE_LOOTING);
        }

        return;
    }
}

Spell* PlayerbotAI::GetCurrentSpell() const
{
    if (m_CurrentlyCastingSpellId == 0)
        return nullptr;

    Spell* const pSpell = m_bot->FindCurrentSpellBySpellId(m_CurrentlyCastingSpellId);
    return pSpell;
}

void PlayerbotAI::TellMaster(const std::string& text) const
{
    SendWhisper(text, *GetMaster());
}

void PlayerbotAI::TellMaster(const char* fmt, ...) const
{
    char temp_buf[2048];
    va_list ap;
    va_start(ap, fmt);
    (void) vsnprintf(temp_buf, 2048, fmt, ap);
    va_end(ap);
    std::string str = temp_buf;
    TellMaster(str);
}

void PlayerbotAI::SendWhisper(const std::string& text, Player& player) const
{
    if (player.GetPlayerbotAI())
        return;

    WorldPacket* const packet = new WorldPacket(CMSG_MESSAGECHAT, 200);
    *packet << uint32(CHAT_MSG_WHISPER);
    *packet << uint32(LANG_UNIVERSAL);
    *packet << player.GetName();
    *packet << text;
    m_bot->GetSession()->QueuePacket(std::move(std::unique_ptr<WorldPacket>(packet))); // queue the packet to get around race condition
}

bool PlayerbotAI::canObeyCommandFrom(const Player& player) const
{
    return player.GetSession()->GetAccountId() == GetMaster()->GetSession()->GetAccountId();
}

bool PlayerbotAI::In_Range(Unit* Target, uint32 spellId)
{
    const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!pSpellInfo)
        return false;

    SpellRangeEntry const* TempRange = GetSpellRangeStore()->LookupEntry(pSpellInfo->rangeIndex);

    //Spell has invalid range store so we can't use it
    if (!TempRange)
        return false;

    if (TempRange->minRange == 0.0f && TempRange->maxRange == 0.0f)
        return true;

    //Unit is out of range of this spell
    if (!m_bot->IsInRange(Target, TempRange->minRange, TempRange->maxRange))
        return false;

    return true;
}

SpellCastResult PlayerbotAI::CheckBotCast(const SpellEntry* sInfo)
{
    if (!sInfo)
        return SPELL_FAILED_ERROR;

    // check DoLoot() spells before casting
    Spell* tmp_spell = new Spell(m_bot, sInfo, false);
    if (tmp_spell)
    {
        if (m_lootCurrent.IsCreature())
        {
            if (Creature* obj = m_bot->GetMap()->GetCreature(m_lootCurrent))
                tmp_spell->m_targets.setUnitTarget(obj);
        }
        else if (m_lootCurrent.IsGameObject())
        {
            if (GameObject* obj = m_bot->GetMap()->GetGameObject(m_lootCurrent))
                tmp_spell->m_targets.setGOTarget(obj);
        }

        // DEBUG_LOG("CheckBotCast SpellCastResult res(%u)", res);
        SpellCastResult res = tmp_spell->CheckCast(false);
        return tmp_spell->CheckCast(false);
    }
    return SPELL_FAILED_ERROR;
}

SpellCastResult PlayerbotAI::CastSpell(const char* args)
{
    uint32 spellId = getSpellId(args);
    return (spellId) ? CastSpell(spellId) : SPELL_NOT_FOUND;
}

SpellCastResult PlayerbotAI::CastSpell(uint32 spellId, Unit& target)
{
    ObjectGuid oldSel = m_bot->GetSelectionGuid();
    m_bot->SetSelectionGuid(target.GetObjectGuid());
    SpellCastResult rv = CastSpell(spellId);
    m_bot->SetSelectionGuid(oldSel);
    return rv;
}

SpellCastResult PlayerbotAI::CastSpell(uint32 spellId)
{
    // some AIs don't check if the bot doesn't have spell before using it
    // so just return false when this happens
    if (spellId == 0)
        return SPELL_FAILED_NOT_KNOWN;

    // see Creature.cpp 1738 for reference
    // don't allow bot to cast damage spells on friends
    const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!pSpellInfo)
    {
        TellMaster("missing spell entry in CastSpell for spellid %u.", spellId);
        return SPELL_NOT_FOUND;
    }

    // check spell cooldown
    if (!m_bot->IsSpellReady(*pSpellInfo))
        return SPELL_FAILED_NOT_READY;

    // for AI debug purpose: uncomment the following line and bot will tell Master of every spell they attempt to cast
    // TellMaster("I'm trying to cast %s (spellID %u)", pSpellInfo->SpellName[0], spellId);

    // Power check
    // We use Spell::CheckPower() instead of UnitAI::CanCastSpell() because bots are players and have more requirements than mere units
    Spell* tmp_spell = new Spell(m_bot, pSpellInfo, false);
    SpellCastResult res = tmp_spell->CheckPower();
    if (res != SPELL_CAST_OK)
        return res;

    // set target
    ObjectGuid targetGUID = m_bot->GetSelectionGuid();
    Unit* pTarget = ObjectAccessor::GetUnit(*m_bot, targetGUID);

    if (!pTarget)
        pTarget = m_bot;

    if (IsPositiveSpell(spellId))
    {
        if (pTarget && m_bot->CanAttack(pTarget))
            pTarget = m_bot;
    }
    else
    {
        if (pTarget && m_bot->CanAssist(pTarget))    // Can't cast hostile spell on friendly unit
            return SPELL_FAILED_TARGET_FRIENDLY;

        m_bot->SetInFront(pTarget);
    }

    float CastTime = 0.0f;

    // stop movement to prevent cancel spell casting
    SpellCastTimesEntry const* castTimeEntry = sSpellCastTimesStore.LookupEntry(pSpellInfo->CastingTimeIndex);
    // stop movement to prevent cancel spell casting
    if (castTimeEntry && castTimeEntry->CastTime)
    {
        CastTime = (castTimeEntry->CastTime / 1000);
        DEBUG_LOG("[PlayerbotAI]: CastSpell - Bot movement reset for casting %s (%u)", pSpellInfo->SpellName[0], spellId);
        // m_bot->clearUnitState(UNIT_STAT_MOVING);
        m_bot->StopMoving();
    }

    uint32 target_type = TARGET_FLAG_UNIT;

    if (pSpellInfo->Effect[0] == SPELL_EFFECT_OPEN_LOCK)
        target_type = TARGET_FLAG_OBJECT;

    m_CurrentlyCastingSpellId = spellId;

    if (pSpellInfo->Effect[0] == SPELL_EFFECT_OPEN_LOCK ||
            pSpellInfo->Effect[0] == SPELL_EFFECT_SKINNING)
    {
        if (m_lootCurrent)
        {
            SpellCastResult castResult = CheckBotCast(pSpellInfo);
            if (castResult != SPELL_CAST_OK)
                return castResult;

            std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_CAST_SPELL, 4 + 1 + 4 + 8));
            *packet << spellId;
            *packet << uint8(0);                            // spells cast count;
            *packet << target_type;
            *packet << m_lootCurrent.WriteAsPacked();
            m_bot->GetSession()->QueuePacket(std::move(packet));       // queue the packet to get around race condition */

            if (target_type == TARGET_FLAG_OBJECT)
            {
                std::unique_ptr<WorldPacket> packetgouse(new WorldPacket(CMSG_GAMEOBJ_USE, 8));
                *packetgouse << m_lootCurrent;
                m_bot->GetSession()->QueuePacket(std::move(packetgouse));  // queue the packet to get around race condition

                GameObject* obj = m_bot->GetMap()->GetGameObject(m_lootCurrent);
                if (!obj)
                    return SPELL_FAILED_BAD_TARGETS;

                // add other go types here, i.e.:
                // GAMEOBJECT_TYPE_CHEST - loot quest items of chest
                if (obj->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
                {
                    TurnInQuests(obj);

                    // auto accept every available quest this NPC has
                    m_bot->PrepareQuestMenu(m_lootCurrent);
                    QuestMenu& questMenu = m_bot->PlayerTalkClass->GetQuestMenu();
                    for (uint32 iI = 0; iI < questMenu.MenuItemCount(); ++iI)
                    {
                        QuestMenuItem const& qItem = questMenu.GetItem(iI);
                        uint32 questID = qItem.m_qId;
                        if (!AddQuest(questID, obj))
                            TellMaster("Couldn't take quest");
                    }
                    m_lootCurrent = ObjectGuid();
                    m_bot->GetMotionMaster()->Clear(false);
                    m_bot->GetMotionMaster()->MoveIdle();
                }
            }
            return SPELL_CAST_OK;
        }
        else
            return SPELL_FAILED_BAD_IMPLICIT_TARGETS;
    }
    else
    {
        // Check spell range
        if (!In_Range(pTarget, spellId))
            return SPELL_FAILED_OUT_OF_RANGE;

        // Check line of sight
        if (!m_bot->IsWithinLOSInMap(pTarget))
            return SPELL_FAILED_LINE_OF_SIGHT;

        // Some casting times are negative so set ignore update time to 1 sec to avoid stucking the bot AI
        SetIgnoreUpdateTime(std::max(CastTime, 0.0f) + 1);

        if (IsAutoRepeatRangedSpell(pSpellInfo))
            return m_bot->CastSpell(pTarget, pSpellInfo, TRIGGERED_OLD_TRIGGERED); // cast triggered spell
        else
            return m_bot->CastSpell(pTarget, pSpellInfo, TRIGGERED_NONE);          // uni-cast spell
    }
}

SpellCastResult PlayerbotAI::CastPetSpell(uint32 spellId, Unit* target)
{
    if (spellId == 0)
        return SPELL_FAILED_NOT_KNOWN;

    Pet* pet = m_bot->GetPet();
    if (!pet)
        return SPELL_FAILED_NO_PET;

    const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!pSpellInfo)
    {
        TellMaster("Missing spell entry in CastPetSpell()");
        return SPELL_NOT_FOUND;
    }

    if (!pet->IsSpellReady(*pSpellInfo))
        return SPELL_FAILED_NOT_READY;

    // set target
    Unit* pTarget;
    if (!target)
    {
        ObjectGuid targetGUID = m_bot->GetSelectionGuid();
        pTarget = ObjectAccessor::GetUnit(*m_bot, targetGUID);
    }
    else
        pTarget = target;

    if (IsPositiveSpell(spellId))
    {
        if (pTarget && m_bot->CanAttack(pTarget))
            pTarget = m_bot;
    }
    else
    {
        if (pTarget && m_bot->CanAssist(pTarget))    // Can cast hostile spell on friendly unit
            return SPELL_FAILED_TARGET_FRIENDLY;

        if (!pet->isInFrontInMap(pTarget, 10)) // distance probably should be calculated
            pet->SetFacingTo(pet->GetAngle(pTarget));
    }

    pet->CastSpell(pTarget, pSpellInfo, TRIGGERED_NONE);

    Spell* const pSpell = pet->FindCurrentSpellBySpellId(spellId);
    if (!pSpell)
        return SPELL_FAILED_NOT_KNOWN;

    return SPELL_CAST_OK;
}

// Perform sanity checks and cast spell
SpellCastResult PlayerbotAI::Buff(uint32 spellId, Unit* target, void (*beforeCast)(Player*))
{
    if (spellId == 0)
        return SPELL_FAILED_NOT_KNOWN;

    // Target already has aura from spellId, skip for speed. May need to add exceptions
    if (target->HasAura(spellId))
        return SPELL_FAILED_AURA_BOUNCED;

    SpellEntry const* spellProto = sSpellTemplate.LookupEntry<SpellEntry>(spellId);

    if (!spellProto)
        return SPELL_NOT_FOUND;

    if (!target)
        return SPELL_FAILED_BAD_IMPLICIT_TARGETS;

    // Select appropriate spell rank for target's level
    spellProto = sSpellMgr.SelectAuraRankForLevel(spellProto, target->getLevel());
    if (!spellProto)
        return SPELL_NOT_FOUND;

    // Check if spell will boost one of already existent auras
    bool willBenefitFromSpell = false;
    for (uint8 i = 0; i < MAX_EFFECT_INDEX; ++i)
    {
        if (spellProto->EffectApplyAuraName[i] == SPELL_AURA_NONE)
            break;

        bool sameOrBetterAuraFound = false;
        int32 bonus = m_bot->CalculateSpellDamage(target, spellProto, SpellEffectIndex(i));
        Unit::AuraList const& auras = target->GetAurasByType(AuraType(spellProto->EffectApplyAuraName[i]));
        for (Unit::AuraList::const_iterator it = auras.begin(); it != auras.end(); ++it)
            if ((*it)->GetModifier()->m_miscvalue == spellProto->EffectMiscValue[i] && (*it)->GetModifier()->m_amount >= bonus)
            {
                sameOrBetterAuraFound = true;
                break;
            }
        willBenefitFromSpell = willBenefitFromSpell || !sameOrBetterAuraFound;
    }

    if (!willBenefitFromSpell)
        return SPELL_FAILED_AURA_BOUNCED;

    // Druids may need to shapeshift before casting
    if (beforeCast)
        (*beforeCast)(m_bot);

    return CastSpell(spellProto->Id, *target);
}

// Can be used for personal buffs like Mage Armor and Inner Fire
SpellCastResult PlayerbotAI::SelfBuff(uint32 spellId)
{
    if (spellId == 0)
        return SPELL_FAILED_NOT_KNOWN;

    if (m_bot->HasAura(spellId))
        return SPELL_FAILED_AURA_BOUNCED;

    return CastSpell(spellId, *m_bot);
}

// Checks if spell is single per target per caster and will make any effect on target
bool PlayerbotAI::CanReceiveSpecificSpell(uint8 spec, Unit* target) const
{
    if (IsSpellSpecificUniquePerCaster(SpellSpecific(spec)))
    {
        Unit::SpellAuraHolderMap holders = target->GetSpellAuraHolderMap();
        Unit::SpellAuraHolderMap::iterator it;
        for (it = holders.begin(); it != holders.end(); ++it)
            if ((*it).second->GetCasterGuid() == m_bot->GetObjectGuid() && GetSpellSpecific((*it).second->GetId()) == SpellSpecific(spec))
                return false;
    }
    return true;
}

uint8 PlayerbotAI::_findItemSlot(Item* target)
{
    // list out items equipped & in main backpack
    //INVENTORY_SLOT_ITEM_START = 23
    //INVENTORY_SLOT_ITEM_END = 39

    for (uint8 slot = EQUIPMENT_SLOT_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        // DEBUG_LOG ("[PlayerbotAI]: FindItem - [%s's]backpack slot = %u",m_bot->GetName(),slot); // 23 to 38 = 16
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);  // 255, 23 to 38
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();
            if (!pItemProto)
                continue;

            if (pItemProto->ItemId == target->GetProto()->ItemId)   // have required item
                return slot;
        }
    }
    // list out items in other removable backpacks
    //INVENTORY_SLOT_BAG_START = 19
    //INVENTORY_SLOT_BAG_END = 23

    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)  // 20 to 23 = 4
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);    // 255, 20 to 23
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                // DEBUG_LOG ("[PlayerbotAI]: FindItem - [%s's]bag[%u] slot = %u", m_bot->GetName(), bag, slot);  // 1 to bagsize = ?
                Item* const pItem = m_bot->GetItemByPos(bag, slot); // 20 to 23, 1 to bagsize
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();
                    if (!pItemProto)
                        continue;

                    if (pItemProto->ItemId == target->GetProto()->ItemId)        // have required item
                        return slot;
                }
            }
    }
    return 0;
}

Item* PlayerbotAI::FindItem(uint32 ItemId, bool Equipped_too /* default = false */)
{
    uint8 first_slot;
    Equipped_too ? first_slot = EQUIPMENT_SLOT_START : first_slot = INVENTORY_SLOT_ITEM_START;

    // list out items equipped &/OR in main backpack
    //EQUIPMENT_SLOT_START = 0
    //INVENTORY_SLOT_ITEM_START = 23
    //INVENTORY_SLOT_ITEM_END = 39

    for (uint8 slot = first_slot; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        // DEBUG_LOG ("[PlayerbotAI]: FindItem - [%s's]backpack slot = %u",m_bot->GetName(),slot); // 23 to 38 = 16
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);  // 255, 23 to 38
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();
            if (!pItemProto)
                continue;

            if (pItemProto->ItemId == ItemId)   // have required item
                return pItem;
        }
    }
    // list out items in other removable backpacks
    //INVENTORY_SLOT_BAG_START = 19
    //INVENTORY_SLOT_BAG_END = 23

    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)  // 20 to 23 = 4
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);    // 255, 20 to 23
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                DEBUG_LOG("[PlayerbotAI]: FindItem - [%s's]bag[%u] slot = %u", m_bot->GetName(), bag, slot);   // 1 to bagsize = ?
                Item* const pItem = m_bot->GetItemByPos(bag, slot); // 20 to 23, 1 to bagsize
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();
                    if (!pItemProto)
                        continue;

                    if (pItemProto->ItemId == ItemId)        // have required item
                        return pItem;
                }
            }
    }
    return nullptr;
}

Item* PlayerbotAI::FindItemInBank(uint32 ItemId)
{
    // list out items in bank item slots

    for (uint8 slot = BANK_SLOT_ITEM_START; slot < BANK_SLOT_ITEM_END; slot++)
    {
        // sLog.outDebug("[%s's]backpack slot = %u",m_bot->GetName(),slot);
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
        {
            const ItemPrototype* const pItemProto = pItem->GetProto();
            if (!pItemProto)
                continue;

            if (pItemProto->ItemId == ItemId)   // have required item
                return pItem;
        }
    }
    // list out items in bank bag slots

    for (uint8 bag = BANK_SLOT_BAG_START; bag < BANK_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                // sLog.outDebug("[%s's]bag[%u] slot = %u", m_bot->GetName(), bag, slot);
                Item* const pItem = m_bot->GetItemByPos(bag, slot);
                if (pItem)
                {
                    const ItemPrototype* const pItemProto = pItem->GetProto();
                    if (!pItemProto)
                        continue;

                    if (pItemProto->ItemId == ItemId)        // have required item
                        return pItem;
                }
            }
    }
    return nullptr;
}

Item* PlayerbotAI::FindKeyForLockValue(uint32 reqSkillValue)
{
    if (reqSkillValue <= 25 && m_bot->HasItemCount(SILVER_SKELETON_KEY, 1))
        return FindItem(SILVER_SKELETON_KEY);
    if (reqSkillValue <= 125 && m_bot->HasItemCount(GOLDEN_SKELETON_KEY, 1))
        return FindItem(GOLDEN_SKELETON_KEY);
    if (reqSkillValue <= 200 && m_bot->HasItemCount(TRUESILVER_SKELETON_KEY, 1))
        return FindItem(TRUESILVER_SKELETON_KEY);
    if (reqSkillValue <= 300 && m_bot->HasItemCount(ARCANITE_SKELETON_KEY, 1))
        return FindItem(ARCANITE_SKELETON_KEY);

    return nullptr;
}

Item* PlayerbotAI::FindBombForLockValue(uint32 reqSkillValue)
{
    if (reqSkillValue <= 150 && m_bot->HasItemCount(SMALL_SEAFORIUM_CHARGE, 1))
        return FindItem(SMALL_SEAFORIUM_CHARGE);
    if (reqSkillValue <= 250 && m_bot->HasItemCount(LARGE_SEAFORIUM_CHARGE, 1))
        return FindItem(LARGE_SEAFORIUM_CHARGE);
    if (reqSkillValue <= 300 && m_bot->HasItemCount(POWERFUL_SEAFORIUM_CHARGE, 1))
        return FindItem(POWERFUL_SEAFORIUM_CHARGE);
    if (reqSkillValue <= 350 && m_bot->HasItemCount(ELEMENTAL_SEAFORIUM_CHARGE, 1))
        return FindItem(ELEMENTAL_SEAFORIUM_CHARGE);

    return nullptr;
}

bool PlayerbotAI::HasTool(uint32 TC)
{
    std::ostringstream out;

    switch (TC)
    {
        case TC_MINING_PICK:                //  = 165

            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a MINING PICK!";
            break;

        case TC_ARCLIGHT_SPANNER:          //  = 14

            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have an ARCLIGHT SPANNER!";
            break;

        case TC_BLACKSMITH_HAMMER:         //  = 162

            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a BLACKSMITH's HAMMER!";
            break;

        case TC_SKINNING_KNIFE:            //  = 166

            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a SKINNING KNIFE!";
            break;

        case TC_COPPER_ROD:                //  = 6,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED COPPER ROD!";
            break;

        case TC_SILVER_ROD:                //  = 7,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED SILVER ROD!";
            break;

        case TC_GOLDEN_ROD:                //  = 8,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED GOLDEN ROD!";
            break;

        case TC_TRUESILVER_ROD:            //  = 9,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED TRUESILVER ROD!";
            break;

        case TC_ARCANITE_ROD:              //  = 10,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED ARCANITE ROD!";
            break;

        case TC_FEL_IRON_ROD:              //  = 41,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED FEL IRON ROD!";
            break;

        case TC_ADAMANTITE_ROD:            //  = 62,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED ADAMANTITE ROD!";
            break;

        case TC_ETERNIUM_ROD:              //  = 63,
            if (m_bot->HasItemTotemCategory(TC))
                return true;
            else
                out << "|cffff0000I do not have a RUNED ETERNIUM ROD!";
            break;
        default:
            out << "|cffffffffI do not know what tool that needs! TC (" << TC << ")";
    }
    TellMaster(out.str().c_str());
    return false;
}

bool PlayerbotAI::PickPocket(Unit* pTarget)
{
    if (!pTarget)
        return false;

    ObjectGuid markGuid = pTarget->GetObjectGuid();
    Creature* c = m_bot->GetMap()->GetCreature(markGuid);
    if (c)
    {
        Loot*& loot = c->loot;
        if (!loot)
            loot = new Loot(m_bot, c, LOOT_PICKPOCKETING);
        else
        {
            if (loot->GetLootType() != LOOT_PICKPOCKETING)
            {
                delete loot;
                loot = new Loot(m_bot, c, LOOT_PICKPOCKETING);
            }
        }

        if (loot->GetGoldAmount())
        {
            m_bot->ModifyMoney(loot->GetGoldAmount());

            if (m_mgr->m_confDebugWhisper)
            {
                std::ostringstream out;

                // calculate how much money bot loots
                uint32 copper = loot->GetGoldAmount();
                uint32 gold = uint32(copper / 10000);
                copper -= (gold * 10000);
                uint32 silver = uint32(copper / 100);
                copper -= (silver * 100);

                out << "|r|cff009900" << m_bot->GetName() << " loots: " << "|h|cffffffff[|r|cff00ff00" << gold
                    << "|r|cfffffc00g|r|cff00ff00" << silver
                    << "|r|cffcdcdcds|r|cff00ff00" << copper
                    << "|r|cff993300c"
                    << "|h|cffffffff]";

                TellMaster(out.str().c_str());
            }

            // send the money to the bot and remove it from the creature
            loot->SendGold(m_bot);
        }

        if (!loot->AutoStore(m_bot, false, NULL_BAG, NULL_SLOT))
            sLog.outDebug("PLAYERBOT Debug: Failed to get loot from pickpocketed NPC");

        // release the loot whatever happened
        loot->Release(m_bot);
    }
    return false; // ensures that the rogue only pick pockets target once
}

bool PlayerbotAI::HasSpellReagents(uint32 spellId)
{
    const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!pSpellInfo)
        return false;

    if (m_bot->CanNoReagentCast(pSpellInfo))
        return true;

    for (uint32 i = 0; i < MAX_SPELL_REAGENTS; ++i)
    {
        if (pSpellInfo->Reagent[i] <= 0)
            continue;

        uint32 itemid = pSpellInfo->Reagent[i];
        uint32 count = pSpellInfo->ReagentCount[i];

        if (!m_bot->HasItemCount(itemid, count))
            return false;
    }

    return true;
}

uint32 PlayerbotAI::GetSpellCharges(uint32 spellId)
{
    const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!pSpellInfo)
        return 0;

    if (m_bot->CanNoReagentCast(pSpellInfo))
        return 0;

    uint32 charges = 0;
    std::list<uint32> chargeList;
    for (uint32 i = 0; i < MAX_SPELL_REAGENTS; ++i)
    {
        if (pSpellInfo->Reagent[i] <= 0)
            continue;

        uint32 totalcount = 0;
        uint32 itemid = pSpellInfo->Reagent[i];
        uint32 count = pSpellInfo->ReagentCount[i];
        ItemCountInInv(itemid, totalcount);
        chargeList.push_back((totalcount / count));
    }

    for (uint32 i = 0; i < MAX_SPELL_TOTEM_CATEGORIES; ++i)
    {
        if (pSpellInfo->TotemCategory[i] == 0)
            continue;

        if (!m_bot->HasItemTotemCategory(pSpellInfo->TotemCategory[i]))
        {
            m_noToolList.push_back(pSpellInfo->TotemCategory[i]);
            return 0;
        }
    }

    if (!chargeList.empty())
    {
        charges = chargeList.front();
        chargeList.pop_front();
        for (std::list<uint32>::iterator it = chargeList.begin(); it != chargeList.end(); ++it)
            if (*it < charges)
                charges = *it;
    }
    return charges;
}

void PlayerbotAI::ItemCountInInv(uint32 itemid, uint32& count)
{
    for (int i = EQUIPMENT_SLOT_START; i < INVENTORY_SLOT_ITEM_END; ++i)
    {
        Item* pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i);
        if (pItem && pItem->GetEntry() == itemid && !pItem->IsInTrade())
            count += pItem->GetCount();
    }

    for (int i = INVENTORY_SLOT_BAG_START; i < INVENTORY_SLOT_BAG_END; ++i)
    {
        if (Bag* pBag = (Bag*)m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, i))
        {
            for (uint32 j = 0; j < pBag->GetBagSize(); ++j)
            {
                Item* pItem = m_bot->GetItemByPos(i, j);
                if (pItem && pItem->GetEntry() == itemid && !pItem->IsInTrade())
                    count += pItem->GetCount();
            }
        }
    }
}

// extracts all item ids in format below
// I decided to roll my own extractor rather then use the one in ChatHandler
// because this one works on a const string, and it handles multiple links
// |color|linkType:key:something1:...:somethingN|h[name]|h|r
void PlayerbotAI::extractItemIds(const std::string& text, std::list<uint32>& itemIds) const
{
    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hitem:", pos);
        if (i == -1)
            break;
        pos = i + 6;
        int endPos = text.find(':', pos);
        if (endPos == -1)
            break;
        std::string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            itemIds.push_back(id);
    }
}

void PlayerbotAI::extractMailIds(const std::string& text, std::list<uint32>& mailIds) const
{
    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hmail:", pos);
        if (i == -1)
            break;
        pos = i + 6;
        int endPos = text.find('|', pos);
        if (endPos == -1)
            break;
        std::string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            mailIds.push_back(id);
    }
}

void PlayerbotAI::extractQuestIds(const std::string& text, std::list<uint32>& questIds) const
{
    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hquest:", pos);
        if (i == -1)
            break;
        pos = i + 7;
        int endPos = text.find(':', pos);
        if (endPos == -1)
            break;
        std::string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            questIds.push_back(id);
    }
}

// Build an hlink for Weapon skills in Aqua
void PlayerbotAI::MakeWeaponSkillLink(const SpellEntry* sInfo, std::ostringstream& out, uint32 skillid)
{
    int loc = GetMaster()->GetSession()->GetSessionDbcLocale();
    out << "|cff00ffff|Hspell:" << sInfo->Id << "|h[" << sInfo->SpellName[loc] << " : " << m_bot->GetSkillValue(skillid) << " /" << m_bot->GetSkillMax(skillid) << "]|h|r";
}

// Build an hlink for spells in White
void PlayerbotAI::MakeSpellLink(const SpellEntry* sInfo, std::ostringstream& out)
{
    int    loc = GetMaster()->GetSession()->GetSessionDbcLocale();
    out << "|cffffffff|Hspell:" << sInfo->Id << "|h[" << sInfo->SpellName[loc] << "]|h|r";
}

// Builds a hlink for an item, but since its
// only a ItemPrototype, we cant fill in everything
void PlayerbotAI::MakeItemLink(const ItemPrototype* item, std::ostringstream& out)
{
    // Color
    out << "|c";
    switch (item->Quality)
    {
        case ITEM_QUALITY_POOR:     out << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   out << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: out << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     out << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     out << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY: out << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: out << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    out << "ffff0000"; break;  //Don't know color, so red?
    }
    out << "|Hitem:";

    // Item Id
    out << item->ItemId << ":";

    // Permanent enchantment, gems, 4 unknowns, and reporter_level
    // ->new items wont have enchantments or gems so..
    out << "0:0:0:0:0:0:0:0:0";

    // Name
    std::string name = item->Name1;
    ItemLocalization(name, item->ItemId);
    out << "|h[" << name << "]|h|r";
}

// Builds a hlink for an item, includes everything
// |color|Hitem:item_id:perm_ench_id:gem1:gem2:gem3:0:0:0:0:reporter_level|h[name]|h|r
void PlayerbotAI::MakeItemLink(const Item* item, std::ostringstream& out, bool IncludeQuantity /*= true*/)
{
    const ItemPrototype* proto = item->GetProto();
    // Color
    out << "|c";
    switch (proto->Quality)
    {
        case ITEM_QUALITY_POOR:     out << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   out << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: out << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     out << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     out << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY: out << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: out << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    out << "ffff0000"; break;  //Don't know color, so red?
    }
    out << "|Hitem:";

    // Item Id
    out << proto->ItemId << ":";

    // Permanent enchantment
    out << item->GetEnchantmentId(PERM_ENCHANTMENT_SLOT) << ":";

    // Gems
    uint32 g1 = 0, g2 = 0, g3 = 0;
    for (uint32 slot = SOCK_ENCHANTMENT_SLOT; slot < SOCK_ENCHANTMENT_SLOT + MAX_GEM_SOCKETS; ++slot)
    {
        uint32 eId = item->GetEnchantmentId(EnchantmentSlot(slot));
        if (!eId) continue;

        SpellItemEnchantmentEntry const* entry = sSpellItemEnchantmentStore.LookupEntry(eId);
        if (!entry) continue;

        switch (slot - SOCK_ENCHANTMENT_SLOT)
        {
            case 1: g1 = entry->GemID; break;
            case 2: g2 = entry->GemID; break;
            case 3: g3 = entry->GemID; break;
        }
    }
    out << g1 << ":" << g2 << ":" << g3 << ":";

    // Temp enchantment, Bonus Enchantment, Prismatic Enchantment?
    // Other stuff, don't know what it is
    out << "0:0:0:0:";

    // Reporter Level
    out << "0";

    // Name
    std::string name = proto->Name1;
    ItemLocalization(name, proto->ItemId);
    out << "|h[" << name << "]|h|r";

    // Stacked items
    if (item->GetCount() > 1 && IncludeQuantity)
        out << "x" << item->GetCount() << ' ';
}

// Builds a string for an item   |color[name]|r
void PlayerbotAI::MakeItemText(const Item* item, std::ostringstream& out, bool IncludeQuantity /*= true*/)
{
    const ItemPrototype* proto = item->GetProto();
    // Color
    out << "|c";
    switch (proto->Quality)
    {
        case ITEM_QUALITY_POOR:     out << "ff9d9d9d"; break;  //GREY
        case ITEM_QUALITY_NORMAL:   out << "ffffffff"; break;  //WHITE
        case ITEM_QUALITY_UNCOMMON: out << "ff1eff00"; break;  //GREEN
        case ITEM_QUALITY_RARE:     out << "ff0070dd"; break;  //BLUE
        case ITEM_QUALITY_EPIC:     out << "ffa335ee"; break;  //PURPLE
        case ITEM_QUALITY_LEGENDARY: out << "ffff8000"; break;  //ORANGE
        case ITEM_QUALITY_ARTIFACT: out << "ffe6cc80"; break;  //LIGHT YELLOW
        default:                    out << "ffff0000"; break;  //Don't know color, so red?
    }

    // Name
    std::string name = proto->Name1;
    ItemLocalization(name, proto->ItemId);
    out << "[" << name << "]|r";

    // Stacked items
    if (item->GetCount() > 1 && IncludeQuantity)
        out << "x" << item->GetCount() << ' ';
}

void PlayerbotAI::extractAuctionIds(const std::string& text, std::list<uint32>& auctionIds) const
{
    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Htitle:", pos);
        if (i == -1)
            break;
        pos = i + 7;
        int endPos = text.find('|', pos);
        if (endPos == -1)
            break;
        std::string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos;
        if (id)
            auctionIds.push_back(id);
    }
}

void PlayerbotAI::extractSpellId(const std::string& text, uint32& spellId) const
{

    //   Link format
    //   |cffffffff|Hspell:" << spellId << ":" << "|h[" << pSpellInfo->SpellName[loc] << "]|h|r";
    //   cast |cff71d5ff|Hspell:686|h[Shadow Bolt]|h|r";
    //   012345678901234567890123456
    //        base = 16 >|  +7 >|

    uint8 pos = 0;

    int i = text.find("Hspell:", pos);
    if (i == -1)
        return;

    // DEBUG_LOG("[PlayerbotAI]: extractSpellId - first pos %u i %u",pos,i);
    pos = i + 7;     // start of window in text 16 + 7 = 23
    int endPos = text.find('|', pos);
    if (endPos == -1)
        return;

    // DEBUG_LOG("[PlayerbotAI]: extractSpellId - second endpos : %u pos : %u",endPos,pos);
    std::string idC = text.substr(pos, endPos - pos);     // 26 - 23
    spellId = atol(idC.c_str());
    pos = endPos;     // end
}

void PlayerbotAI::extractSpellIdList(const std::string& text, BotEntryList& m_spellsToLearn) const
{

    //   Link format
    //   |cffffffff|Hspell:" << spellId << ":" << "|h[" << pSpellInfo->SpellName[loc] << "]|h|r";
    //   cast |cff71d5ff|Hspell:686|h[Shadow Bolt]|h|r";
    //   012345678901234567890123456
    //        base = 16 >|  +7 >|

    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Hspell:", pos);
        if (i == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - first pos %u i %u",pos,i);
        pos = i + 7;     // start of window in text 16 + 7 = 23
        int endPos = text.find('|', pos);
        if (endPos == -1)
            break;

        // DEBUG_LOG("[PlayerbotAI]: extractSpellIdList - second endpos : %u pos : %u",endPos,pos);
        std::string idC = text.substr(pos, endPos - pos);     // 26 - 23
        uint32 spellId = atol(idC.c_str());
        pos = endPos;     // end

        if (spellId)
            m_spellsToLearn.push_back(spellId);
    }
}

void PlayerbotAI::extractGOinfo(const std::string& text, BotObjectList& m_lootTargets) const
{

    //    Link format
    //    |cFFFFFF00|Hfound:" << guid << ':'  << entry << ':'  <<  "|h[" << gInfo->name << "]|h|r";
    //    |cFFFFFF00|Hfound:9582:1731|h[Copper Vein]|h|r

    uint8 pos = 0;
    while (true)
    {
        // extract GO guid
        int i = text.find("Hfound:", pos);     // base H = 11
        if (i == -1)     // break if error
            break;

        pos = i + 7;     //start of window in text 11 + 7 = 18
        int endPos = text.find(':', pos);     // end of window in text 22
        if (endPos == -1)     //break if error
            break;
        std::string guidC = text.substr(pos, endPos - pos);     // get string within window i.e guid 22 - 18 =  4
        uint32 guid = atol(guidC.c_str());     // convert ascii to long int

        // extract GO entry
        pos = endPos + 1;
        endPos = text.find(':', pos);     // end of window in text
        if (endPos == -1)     //break if error
            break;

        std::string entryC = text.substr(pos, endPos - pos);     // get string within window i.e entry
        uint32 entry = atol(entryC.c_str());     // convert ascii to float

        ObjectGuid lootCurrent = ObjectGuid(HIGHGUID_GAMEOBJECT, entry, guid);

        if (GameObject* gob = m_bot->GetMap()->GetGameObject(lootCurrent))
            m_lootTargets.push_back(gob->GetObjectGuid());
    }
}

void PlayerbotAI::extractTalentIds(const std::string& text, std::list<talentPair>& talentIds) const
{
    // Link format:
    // |color|Htalent:talent_id:rank|h[name]|h|r
    // |cff4e96f7|Htalent:1396:4|h[Unleashed Fury]|h|r

    uint8 pos = 0;
    while (true)
    {
        int i = text.find("Htalent:", pos);
        if (i == -1)
            break;
        pos = i + 8;
        // DEBUG_LOG("extractTalentIds first pos %u i %u",pos,i);
        // extract talent_id
        int endPos = text.find(':', pos);
        if (endPos == -1)
            break;
        // DEBUG_LOG("extractTalentId second endpos : %u pos : %u",endPos,pos);
        std::string idC = text.substr(pos, endPos - pos);
        uint32 id = atol(idC.c_str());
        pos = endPos + 1;
        // extract rank
        endPos = text.find('|', pos);
        if (endPos == -1)
            break;
        // DEBUG_LOG("extractTalentId third endpos : %u pos : %u",endPos,pos);
        std::string rankC = text.substr(pos, endPos - pos);
        uint32 rank = atol(rankC.c_str());
        pos = endPos + 1;

        // DEBUG_LOG("extractTalentId second id : %u  rank : %u",id,rank);

        if (id)
            talentIds.push_back(std::pair<uint32, uint32>(id, rank));
    }
}

// extracts currency in #g#s#c format
uint32 PlayerbotAI::extractMoney(const std::string& text) const
{
    // if user specified money in ##g##s##c format
    std::string acum = "";
    uint32 copper = 0;
    for (uint8 i = 0; i < text.length(); i++)
    {
        if (text[i] == 'g')
        {
            copper += (atol(acum.c_str()) * 100 * 100);
            acum = "";
        }
        else if (text[i] == 'c')
        {
            copper += atol(acum.c_str());
            acum = "";
        }
        else if (text[i] == 's')
        {
            copper += (atol(acum.c_str()) * 100);
            acum = "";
        }
        else if (text[i] == ' ')
            break;
        else if (text[i] >= 48 && text[i] <= 57)
            acum += text[i];
        else
        {
            copper = 0;
            break;
        }
    }
    return copper;
}

// finds items in equipment and adds Item* to foundItemList
// also removes found item IDs from itemIdSearchList when found
void PlayerbotAI::findItemsInEquip(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList) const
{
    for (uint8 slot = EQUIPMENT_SLOT_START; itemIdSearchList.size() > 0 && slot < EQUIPMENT_SLOT_END; slot++)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!pItem)
            continue;

        for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
        {
            if (pItem->GetProto()->ItemId != *it)
                continue;

            foundItemList.push_back(pItem);
            itemIdSearchList.erase(it);
            break;
        }
    }
}

// finds items in inventory and adds Item* to foundItemList
// also removes found item IDs from itemIdSearchList when found
void PlayerbotAI::findItemsInInv(std::list<uint32>& itemIdSearchList, std::list<Item*>& foundItemList) const
{

    // look for items in main bag
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; itemIdSearchList.size() > 0 && slot < INVENTORY_SLOT_ITEM_END; ++slot)
    {
        Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (!pItem)
            continue;

        for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
        {
            if (pItem->GetProto()->ItemId != *it)
                continue;

            if (m_bot->GetTrader() && m_bot->GetTradeData()->HasItem(pItem->GetObjectGuid()))
                continue;

            foundItemList.push_back(pItem);
            itemIdSearchList.erase(it);
            break;
        }
    }

    // for all for items in other bags
    for (uint8 bag = INVENTORY_SLOT_BAG_START; itemIdSearchList.size() > 0 && bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (!pBag)
            continue;

        for (uint8 slot = 0; itemIdSearchList.size() > 0 && slot < pBag->GetBagSize(); ++slot)
        {
            Item* const pItem = m_bot->GetItemByPos(bag, slot);
            if (!pItem)
                continue;

            for (std::list<uint32>::iterator it = itemIdSearchList.begin(); it != itemIdSearchList.end(); ++it)
            {
                if (pItem->GetProto()->ItemId != *it)
                    continue;

                if (m_bot->GetTrader() && m_bot->GetTradeData()->HasItem(pItem->GetObjectGuid()))
                    continue;

                foundItemList.push_back(pItem);
                itemIdSearchList.erase(it);
                break;
            }
        }
    }
}

void PlayerbotAI::findNearbyGO()
{
    if (m_collectObjects.empty())
        return;

    GameObjectList tempTargetGOList;

    for (BotEntryList::iterator itr = m_collectObjects.begin(); itr != m_collectObjects.end(); ++itr)
    {
        uint32 entry = *(itr);
        GameObjectInfo const* gInfo = ObjectMgr::GetGameObjectInfo(entry);

        uint32 lootid = gInfo->GetLootId();

        if (gInfo->GetLootId() > 0)
            for (BotLootList::iterator it = m_botQuestLoot.begin(); it != m_botQuestLoot.end(); ++it)
                if (it->first == lootid)
                    if (!IsInQuestItemList(it->second))
                    {
                        it = m_botQuestLoot.erase(it);
                        m_collectObjects.remove(entry); // remove gameobject from collect list
                        return;
                    }

        // search for GOs with entry, within range of m_bot
        MaNGOS::GameObjectEntryInPosRangeCheck go_check(*m_bot, entry, m_bot->GetPositionX(), m_bot->GetPositionY(), m_bot->GetPositionZ(), float(m_collectDist));
        MaNGOS::GameObjectListSearcher<MaNGOS::GameObjectEntryInPosRangeCheck> checker(tempTargetGOList, go_check);
        Cell::VisitGridObjects(m_bot, checker, float(m_collectDist));

        // no objects found, continue to next entry
        if (tempTargetGOList.empty())
            continue;

        // add any objects found to our lootTargets
        for (GameObjectList::iterator iter = tempTargetGOList.begin(); iter != tempTargetGOList.end(); iter++)
        {
            GameObject* go = (*iter);

            TerrainInfo const* map = go->GetTerrain();

            float ground_z = map->GetHeightStatic(go->GetPositionX(), go->GetPositionY(), go->GetPositionZ());
            // DEBUG_LOG("ground_z (%f) > INVALID_HEIGHT (%f)",ground_z,INVALID_HEIGHT);
            if ((ground_z > INVALID_HEIGHT) && go->IsSpawned())
                m_lootTargets.push_back(go->GetObjectGuid());
        }
    }
}

void PlayerbotAI::findNearbyCorpse()
{
    UnitList corpseList;
    float radius = float(m_mgr->m_confCollectDistance);
    MaNGOS::AnyDeadUnitCheck corpse_check(m_bot);
    MaNGOS::UnitListSearcher<MaNGOS::AnyDeadUnitCheck> reaper(corpseList, corpse_check);
    Cell::VisitAllObjects(m_bot, reaper, radius);

    //if (!corpseList.empty())
    //    TellMaster("Found %i Corpse(s)", corpseList.size());

    for (UnitList::const_iterator i = corpseList.begin(); i != corpseList.end(); ++i)
    {
        Creature* corpse = (Creature*)*i;
        if (!corpse)
            continue;

        if (!corpse->IsCorpse() || corpse->IsDespawned() || m_bot->CanAssist(corpse) || !corpse->loot)
            continue;

        if (!corpse->loot->CanLoot(m_bot) && !corpse->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            continue;

        uint32 skillId = 0;
        if (corpse->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            skillId = corpse->GetCreatureInfo()->GetRequiredLootSkill();

        if (corpse->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) ||
                (corpse->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE) && m_bot->HasSkill(skillId)))
        {
            m_lootTargets.push_back(corpse->GetObjectGuid());
            m_lootTargets.unique();
        }
    }
}

void PlayerbotAI::findNearbyCreature()
{
    // Do not waste time finding a creature if bot has nothing to do
    // and clear list (sanity check)
    if (m_tasks.empty())
    {
        m_findNPC.clear();
        return;
    }
    CreatureList creatureList;
    float radius = INTERACTION_DISTANCE;

    CellPair pair(MaNGOS::ComputeCellPair(m_bot->GetPositionX(), m_bot->GetPositionY()));
    Cell cell(pair);

    MaNGOS::AnyUnitInObjectRangeCheck go_check(m_bot, radius);
    MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck> go_search(creatureList, go_check);
    TypeContainerVisitor<MaNGOS::CreatureListSearcher<MaNGOS::AnyUnitInObjectRangeCheck>, GridTypeMapContainer> go_visit(go_search);

    // Get Creatures
    cell.Visit(pair, go_visit, *(m_bot->GetMap()), *(m_bot), radius);

    // if (!creatureList.empty())
    //    TellMaster("Found %i Creatures & size of m_findNPC (%i)", creatureList.size(),m_findNPC.size());

    for (CreatureList::iterator iter = creatureList.begin(); iter != creatureList.end(); iter++)
    {
        Creature* currCreature = *iter;

        for (std::list<enum NPCFlags>::iterator itr = m_findNPC.begin(); itr != m_findNPC.end(); itr = m_findNPC.erase(itr))
        {
            uint32 npcflags = currCreature->GetUInt32Value(UNIT_NPC_FLAGS);

            if (!(*itr & npcflags))
            {
                ++itr;
                continue;
            }

            if ((*itr == UNIT_NPC_FLAG_TRAINER) && !currCreature->CanTrainAndResetTalentsOf(m_bot))
                break;

            WorldObject* wo = m_bot->GetMap()->GetWorldObject(currCreature->GetObjectGuid());

            if (m_bot->GetDistance(wo) > CONTACT_DISTANCE + wo->GetObjectBoundingRadius())
            {
                float x, y, z;
                wo->GetContactPoint(m_bot, x, y, z, wo->GetObjectBoundingRadius());
                m_bot->GetMotionMaster()->MovePoint(wo->GetMapId(), x, y, z, false);
                // give time to move to point before trying again
                SetIgnoreUpdateTime(1);
            }

            if (m_bot->GetDistance(wo) < INTERACTION_DISTANCE)
            {
                // DEBUG_LOG("%s is interacting with (%s)",m_bot->GetName(),currCreature->GetCreatureInfo()->Name);
                // Stop moving as soon as bot is in range
                m_bot->GetMotionMaster()->Clear(false);
                m_bot->GetMotionMaster()->MoveIdle();
                GossipMenuItemsMapBounds pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(currCreature->GetCreatureInfo()->GossipMenuId);

                // prepares quest menu when true
                bool canSeeQuests = currCreature->GetCreatureInfo()->GossipMenuId == m_bot->GetDefaultGossipMenuForSource(wo);

                // if canSeeQuests (the default, top level menu) and no menu options exist for this, use options from default options
                if (pMenuItemBounds.first == pMenuItemBounds.second && canSeeQuests)
                    pMenuItemBounds = sObjectMgr.GetGossipMenuItemsMapBounds(0);

                for (GossipMenuItemsMap::const_iterator it = pMenuItemBounds.first; it != pMenuItemBounds.second; it++)
                {
                    if (!(it->second.npc_option_npcflag & npcflags))
                        continue;

                    switch (it->second.option_id)
                    {
                        case GOSSIP_OPTION_AUCTIONEER:
                        case GOSSIP_OPTION_BANKER:
                        case GOSSIP_OPTION_TAXIVENDOR:
                        case GOSSIP_OPTION_GOSSIP:
                        case GOSSIP_OPTION_INNKEEPER:
                        case GOSSIP_OPTION_TRAINER:
                        case GOSSIP_OPTION_QUESTGIVER:
                        case GOSSIP_OPTION_VENDOR:
                        case GOSSIP_OPTION_UNLEARNTALENTS:
                        case GOSSIP_OPTION_ARMORER:
                        {
                            // Manage questgiver, trainer, banker, auctioneer, innkeeper & vendor actions
                            if (!m_tasks.empty())
                                for (std::list<taskPair>::iterator ait = m_tasks.begin(); ait != m_tasks.end(); ait = m_tasks.erase(ait))
                                {
                                    switch (ait->first)
                                    {
                                        // add new auction item
                                        case ADD_AUCTION:
                                        {
                                            // TellMaster("Creating auction");
                                            AddAuction(ait->second, currCreature);
                                            ListAuctions();
                                            break;
                                        }
                                        // cancel active auction
                                        case REMOVE_AUCTION:
                                        {
                                            // TellMaster("Cancelling auction");
                                            if (!RemoveAuction(ait->second))
                                                DEBUG_LOG("RemoveAuction: Couldn't remove auction (%u)", ait->second);
                                            ListAuctions();
                                            break;
                                        }
                                        // list active auctions
                                        case LIST_AUCTION:
                                        {
                                            // TellMaster("Listing auction");
                                            ListAuctions();
                                            break;
                                        }
                                        // withdraw items
                                        case BANK_WITHDRAW:
                                        {
                                            // TellMaster("Withdraw items");
                                            if (!Withdraw(ait->second))
                                                DEBUG_LOG("Withdraw: Couldn't withdraw (%u)", ait->second);
                                            BankBalance();
                                            break;
                                        }
                                        // deposit items
                                        case BANK_DEPOSIT:
                                        {
                                            // TellMaster("Deposit items");
                                            if (!Deposit(ait->second))
                                                DEBUG_LOG("Deposit: Couldn't deposit (%u)", ait->second);
                                            BankBalance();
                                            break;
                                        }
                                        // bank balance
                                        case BANK_BALANCE:
                                        {
                                            // TellMaster("Bank Balance");
                                            BankBalance();
                                            break;
                                        }
                                        // reset talents
                                        case RESET_TALENTS:
                                        {
                                            // TellMaster("Reset all talents");
                                            if (Talent(currCreature))
                                                InspectUpdate();
                                            break;
                                        }
                                        // take new quests
                                        case TAKE_QUEST:
                                        {
                                            // TellMaster("Accepting quest");
                                            if (!AddQuest(ait->second, wo))
                                                DEBUG_LOG("AddQuest: Couldn't add quest (%u)", ait->second);
                                            break;
                                        }
                                        // list npc quests
                                        case LIST_QUEST:
                                        {
                                            // TellMaster("Show available npc quests");
                                            ListQuests(wo);
                                            break;
                                        }
                                        // end quests
                                        case END_QUEST:
                                        {
                                            // TellMaster("Turn in available quests");
                                            TurnInQuests(wo);
                                            break;
                                        }
                                        // sell items
                                        case SELL_ITEMS:
                                        {
                                            // TellMaster("Selling items");
                                            Sell(ait->second);
                                            break;
                                        }
                                        // buy items
                                        case BUY_ITEMS:
                                        {
                                            // TellMaster("Buying items");
                                            Buy(currCreature, ait->second);
                                            break;
                                        }
                                        // repair items
                                        case REPAIR_ITEMS:
                                        {
                                            TellMaster("Repairing items");
                                            Repair(ait->second, currCreature);
                                            break;
                                        }
                                        default:
                                            break;
                                    }
                                }
                            break;
                        }
                        default:
                            DEBUG_LOG("Unknown - GOSSIP_OPTION (%u)", it->second.option_id);
                            break;
                    }
                    AutoUpgradeEquipment();
                    m_bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
                }
            }
        }
    }
}

/**
 * IsElite()
 * Playerbot wrapper to know if a target is elite or not. This is used by the AI to switch from one action to another
 * return bool Returns true if bot's target is a creature with elite rank (elite rare, elite, worldboss)
 *
 * params:pTarget Unit* the target to check if it is elite
 * params:isWorldBoss bool if true, the function will return true only if the target is a worldboss. This allow to enable specific code if the target is a worldboss
 * return false if the target is not elite/rare elite/worldboss or if isWorldBoss was provided as true and that the target is not a worldboss
 *
 */
bool PlayerbotAI::IsElite(Unit* pTarget, bool isWorldBoss) const
{
    if (!pTarget)
        return false;

    if (Creature* pCreature = (Creature*) pTarget)
    {
        if (isWorldBoss)
            return pCreature->IsWorldBoss();
        else
            return (pCreature->IsElite() || pCreature->IsWorldBoss());
    }

    return false;
}

// Check if bot target has one of the following auras: Sap, Polymorph, Shackle Undead, Banish, Seduction, Freezing Trap, Hibernate
// This is used by the AI to prevent bots from attacking crowd control targets

static const uint32 uAurasIds[21] =
{
    118, 12824, 12825, 12826,   // polymorph
    28272, 28271,               // polymorph pig, turtle
    9484, 9485, 10955,          // shackle
    6358,                       // seduction
    710, 18647,                 // banish
    6770, 2070, 11297,          // sap
    3355, 14308, 14309,         // freezing trap (effect auras IDs, not spell IDs)
    2637, 18657, 18658          // hibernate
};

bool PlayerbotAI::IsNeutralized(Unit* pTarget)
{
    if (!pTarget)
        return false;

    for (uint8 i = 0; i < countof(uAurasIds); ++i)
    {
        if (pTarget->HasAura(uAurasIds[i], EFFECT_INDEX_0))
            return true;
    }

    return false;
}

// Utility function to make the bots face their target
// Useful to ensure bots can cast spells/abilities
// without getting facing target errors
void PlayerbotAI::FaceTarget(Unit* pTarget)
{
    if (!pTarget)
        return;

    // Only update orientation if not already facing target
    if (!m_bot->HasInArc(pTarget))
        m_bot->SetFacingTo(m_bot->GetAngle(pTarget));

    return;
}

/**
 * IsImmuneToSchool()
 * Playerbot wrapper to know if a target is immune or not to a specific damage school. This is used by the AI to prevent using an ability the target is immuned to
 * return bool Returns true if bot's target is a creature with immunity to specified damage school
 *
 * params:target Unit* the target to check if it is immune
 * params:schoolMask the school mask to be checked against the creature template or current spell immunity
 * return false if the target is not immune, also return false by default
 *
 */
bool PlayerbotAI::IsImmuneToSchool(Unit* target, SpellSchoolMask schoolMask)
{
    if (!target)
        return false;

    if (Creature* creature = (Creature*) target)
            return creature->IsImmuneToDamage(schoolMask);

    return false;
}

bool PlayerbotAI::CanStore()
{
    uint32 totalused = 0;
    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; slot++)
    {
        const Item* const pItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (pItem)
            totalused++;
    }
    uint32 totalfree = 16 - totalused;
    // list out items in other removable backpacks
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag)
    {
        const Bag* const pBag = (Bag*) m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag);
        if (pBag)
        {
            ItemPrototype const* pBagProto = pBag->GetProto();
            if (pBagProto->Class == ITEM_CLASS_CONTAINER && pBagProto->SubClass == ITEM_SUBCLASS_CONTAINER)
                totalfree =  totalfree + pBag->GetFreeSlots();
        }
    }
    return totalfree > 0;
}

// use item on self
void PlayerbotAI::UseItem(Item* item)
{
    UseItem(item, m_bot);
}

// use item on equipped item
void PlayerbotAI::UseItem(Item* item, uint8 targetInventorySlot)
{
    if (targetInventorySlot >= EQUIPMENT_SLOT_END)
        return;

    Item* const targetItem = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, targetInventorySlot);
    if (!targetItem)
        return;

    UseItem(item, TARGET_FLAG_ITEM, targetItem->GetObjectGuid());
}

// use item on unit
void PlayerbotAI::UseItem(Item* item, Unit* target)
{
    if (!target)
        return;

    UseItem(item, TARGET_FLAG_UNIT, target->GetObjectGuid());
}

// generic item use method
void PlayerbotAI::UseItem(Item* item, uint32 targetFlag, ObjectGuid targetGUID)
{
    if (!item)
        return;

    uint8 bagIndex = item->GetBagSlot();
    uint8 slot = item->GetSlot();
    uint8 cast_count = 0;
    ObjectGuid item_guid = item->GetObjectGuid();

    if (uint32 questid = item->GetProto()->StartQuest)
    {
        std::ostringstream report;

        Quest const* qInfo = sObjectMgr.GetQuestTemplate(questid);
        if (qInfo)
        {
            m_bot->GetMotionMaster()->Clear(true);
            std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_QUESTGIVER_ACCEPT_QUEST, 8 + 4 + 4));
            *packet << item_guid;
            *packet << questid;
            *packet << uint32(0);
            m_bot->GetSession()->QueuePacket(std::move(packet)); // queue the packet to get around race condition
            report << "|cffffff00Quest taken |r" << qInfo->GetTitle();
            TellMaster(report.str());
        }
        return;
    }

    uint32 spellId = 0;
    uint8 spell_index = 0;
    for (uint8 i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
    {
        if (item->GetProto()->Spells[i].SpellId > 0)
        {
            spellId = item->GetProto()->Spells[i].SpellId;
            spell_index = i;
            break;
        }
    }

    if (item->GetProto()->Flags & ITEM_FLAG_HAS_LOOT && spellId == 0)
    {
        // Open quest item in inventory, containing related items (e.g Gnarlpine necklace, containing Tallonkai's Jewel)
        std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_OPEN_ITEM, 2));
        *packet << item->GetBagSlot();
        *packet << item->GetSlot();
        m_bot->GetSession()->QueuePacket(std::move(packet)); // queue the packet to get around race condition
        return;
    }

    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!spellInfo)
    {
        TellMaster("Can't find spell entry for spell %u on item %u", spellId, item->GetEntry());
        return;
    }

    SpellCastTimesEntry const* castingTimeEntry = sSpellCastTimesStore.LookupEntry(spellInfo->CastingTimeIndex);
    if (!castingTimeEntry)
    {
        TellMaster("Can't find casting time entry for spell %u with index %u", spellId, spellInfo->CastingTimeIndex);
        return;
    }
    // stop movement to prevent cancel spell casting
    else if (castingTimeEntry && castingTimeEntry->CastTime)
    {
        DEBUG_LOG("[PlayerbotAI]: UseItem - Bot movement reset for casting %s (%u)", spellInfo->SpellName[0], spellId);
        MovementClear();
    }

    if (!m_bot->IsSpellReady(*spellInfo))
        return;
    // spell not on cooldown: mark it as next spell to cast whenever possible for bot
    m_CurrentlyCastingSpellId = spellId;

    std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_USE_ITEM, 20));
    *packet << bagIndex;
    *packet << slot;
    *packet << spell_index;
    *packet << cast_count;
    *packet << item_guid;
    *packet << targetFlag;

    if (targetFlag & (TARGET_FLAG_UNIT | TARGET_FLAG_ITEM | TARGET_FLAG_OBJECT))
        *packet << targetGUID.WriteAsPacked();

    m_bot->GetSession()->QueuePacket(std::move(packet));
}

static const uint32 uPriorizedHealingItemIds[19] =
{
    HEALTHSTONE_DISPLAYID, FEL_REGENERATION_POTION, SUPER_HEALING_POTION, CRYSTAL_HEALING_POTION, MAJOR_DREAMLESS_SLEEP_POTION, VOLATILE_HEALING_POTION,
    MAJOR_HEALING_POTION, WHIPPER_ROOT_TUBER, NIGHT_DRAGON_BREATH, LIMITED_INVULNERABILITY_POTION, GREATER_DREAMLESS_SLEEP_POTION,
    SUPERIOR_HEALING_POTION, CRYSTAL_RESTORE, DREAMLESS_SLEEP_POTION, GREATER_HEALING_POTION, HEALING_POTION, LESSER_HEALING_POTION, DISCOLORED_HEALING_POTION, MINOR_HEALING_POTION,
};

/**
 * TryEmergency()
 * Playerbot function to select an item that the bot will use to heal itself on low health without waiting for a heal from a healer
 *
 * params:pAttacker Unit* the creature that is attacking the bot
 * return nothing
 */
void PlayerbotAI::TryEmergency(Unit* pAttacker)
{
    // Do not use consumable if bot can heal self
    if (IsHealer() && GetManaPercent() > 20)
        return;

    // If bot does not have aggro: use bandage instead of potion/stone/crystal
    if (!pAttacker && !m_bot->HasAura(11196)) // Recently bandaged
    {
        Item* bandage = FindBandage();
        if (bandage)
        {
            SetIgnoreUpdateTime(8);
            UseItem(bandage);
            return;
        }
    }

    // Else loop over the list of health consumable to pick one
    Item* healthItem;
    for (uint8 i = 0; i < countof(uPriorizedHealingItemIds); ++i)
    {
        healthItem = FindConsumable(uPriorizedHealingItemIds[i]);
        if (healthItem)
        {
            UseItem(healthItem);
            return;
        }
    }

    return;
}

// submits packet to use an item
void PlayerbotAI::EquipItem(Item* src_Item)
{
    uint8 src_bagIndex = src_Item->GetBagSlot();
    uint8 src_slot = src_Item->GetSlot();

    DEBUG_LOG("PlayerbotAI::EquipItem: %s in srcbag = %u, srcslot = %u", src_Item->GetProto()->Name1, src_bagIndex, src_slot);

    uint16 dest;
    InventoryResult msg = m_bot->CanEquipItem(NULL_SLOT, dest, src_Item, !src_Item->IsBag());
    if (msg != EQUIP_ERR_OK)
    {
        m_bot->SendEquipError(msg, src_Item, nullptr);
        return;
    }

    uint16 src = src_Item->GetPos();
    if (dest == src)                                        // prevent equip in same slot, only at cheat
        return;

    Item* dest_Item = m_bot->GetItemByPos(dest);
    if (!dest_Item)                                          // empty slot, simple case
    {
        m_bot->RemoveItem(src_bagIndex, src_slot, true);
        m_bot->EquipItem(dest, src_Item, true);
        m_bot->AutoUnequipOffhandIfNeed();
    }
    else                                                    // have currently equipped item, not simple case
    {
        uint8 dest_bagIndex = dest_Item->GetBagSlot();
        uint8 dest_slot = dest_Item->GetSlot();

        msg = m_bot->CanUnequipItem(dest, false);
        if (msg != EQUIP_ERR_OK)
        {
            m_bot->SendEquipError(msg, dest_Item, nullptr);
            return;
        }

        // check dest->src move possibility
        ItemPosCountVec sSrc;
        if (m_bot->IsInventoryPos(src))
        {
            msg = m_bot->CanStoreItem(src_bagIndex, src_slot, sSrc, dest_Item, true);
            if (msg != EQUIP_ERR_OK)
                msg = m_bot->CanStoreItem(src_bagIndex, NULL_SLOT, sSrc, dest_Item, true);
            if (msg != EQUIP_ERR_OK)
                msg = m_bot->CanStoreItem(NULL_BAG, NULL_SLOT, sSrc, dest_Item, true);
        }

        if (msg != EQUIP_ERR_OK)
        {
            m_bot->SendEquipError(msg, dest_Item, src_Item);
            return;
        }

        // now do moves, remove...
        m_bot->RemoveItem(dest_bagIndex, dest_slot, false);
        m_bot->RemoveItem(src_bagIndex, src_slot, false);

        // add to dest
        m_bot->EquipItem(dest, src_Item, true);

        // add to src
        if (m_bot->IsInventoryPos(src))
            m_bot->StoreItem(sSrc, dest_Item, true);

        m_bot->AutoUnequipOffhandIfNeed();
    }
}

// submits packet to trade an item (trade window must already be open)
// default slot is -1 which means trade slots 0 to 5. if slot is set
// to TRADE_SLOT_NONTRADED (which is slot 6) item will be shown in the
// 'Will not be traded' slot.
bool PlayerbotAI::TradeItem(const Item& item, int8 slot)
{
    // DEBUG_LOG ("[PlayerbotAI]: TradeItem - slot=%d, hasTrader=%d, itemInTrade=%d, itemTradeable=%d",
    //    slot,
    //    (m_bot->GetTrader() ? 1 : 0),
    //    (item.IsInTrade() ? 1 : 0),
    //    (item.CanBeTraded() ? 1 : 0)
    //    );

    if (!m_bot->GetTrader() || item.IsInTrade() || (!item.CanBeTraded() && slot != TRADE_SLOT_NONTRADED))
        return false;

    int8 tradeSlot = -1;

    TradeData* pTrade = m_bot->GetTradeData();
    if ((slot >= 0 && slot < TRADE_SLOT_COUNT) && pTrade->GetItem(TradeSlots(slot)) == nullptr)
        tradeSlot = slot;
    else
        for (uint8 i = 0; i < TRADE_SLOT_TRADED_COUNT && tradeSlot == -1; i++)
        {
            if (pTrade->GetItem(TradeSlots(i)) == nullptr)
            {
                tradeSlot = i;
                // reserve trade slot to allow multiple items to be traded
                pTrade->SetItem(TradeSlots(i), const_cast<Item*>(&item));
            }
        }

    if (tradeSlot == -1) return false;

    std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_SET_TRADE_ITEM, 3));
    *packet << (uint8) tradeSlot << (uint8) item.GetBagSlot()
            << (uint8) item.GetSlot();
    m_bot->GetSession()->QueuePacket(std::move(packet));
    return true;
}

// submits packet to trade copper (trade window must be open)
bool PlayerbotAI::TradeCopper(uint32 copper)
{
    if (copper > 0)
    {
        std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_SET_TRADE_GOLD, 4));
        *packet << copper;
        m_bot->GetSession()->QueuePacket(std::move(packet));
        return true;
    }
    return false;
}

bool PlayerbotAI::DoTeleport(WorldObject& /*obj*/)
{
    SetIgnoreUpdateTime(6);
    PlayerbotChatHandler ch(GetMaster());
    if (!ch.teleport(*m_bot))
    {
        m_ignoreAIUpdatesUntilTime = time(0) + 6;
        PlayerbotChatHandler ch(GetMaster());
        if (!ch.teleport(*m_bot))
        {
            ch.sysmessage(".. could not be teleported ..");
            // DEBUG_LOG ("[PlayerbotAI]: DoTeleport - %s failed to teleport", m_bot->GetName() );
            return false;
        }
    }
    return true;
}

// Localization support
void PlayerbotAI::ItemLocalization(std::string& itemName, const uint32 itemID) const
{
    uint32 loc = GetMaster()->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    ItemLocale const* pItemInfo = sObjectMgr.GetItemLocale(itemID);
    if (pItemInfo)
        if (pItemInfo->Name.size() > loc && !pItemInfo->Name[loc].empty())
        {
            const std::string name = pItemInfo->Name[loc];
            if (Utf8FitTo(name, wnamepart))
                itemName = name.c_str();
        }
}

void PlayerbotAI::QuestLocalization(std::string& questTitle, const uint32 questID) const
{
    uint32 loc = GetMaster()->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    QuestLocale const* pQuestInfo = sObjectMgr.GetQuestLocale(questID);
    if (pQuestInfo)
        if (pQuestInfo->Title.size() > loc && !pQuestInfo->Title[loc].empty())
        {
            const std::string title = pQuestInfo->Title[loc];
            if (Utf8FitTo(title, wnamepart))
                questTitle = title.c_str();
        }
}

void PlayerbotAI::CreatureLocalization(std::string& creatureName, const uint32 entry) const
{
    uint32 loc = GetMaster()->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    CreatureLocale const* pCreatureInfo = sObjectMgr.GetCreatureLocale(entry);
    if (pCreatureInfo)
        if (pCreatureInfo->Name.size() > loc && !pCreatureInfo->Name[loc].empty())
        {
            const std::string title = pCreatureInfo->Name[loc];
            if (Utf8FitTo(title, wnamepart))
                creatureName = title.c_str();
        }
}

void PlayerbotAI::GameObjectLocalization(std::string& gameobjectName, const uint32 entry) const
{
    uint32 loc = GetMaster()->GetSession()->GetSessionDbLocaleIndex();
    std::wstring wnamepart;

    GameObjectLocale const* pGameObjectInfo = sObjectMgr.GetGameObjectLocale(entry);
    if (pGameObjectInfo)
        if (pGameObjectInfo->Name.size() > loc && !pGameObjectInfo->Name[loc].empty())
        {
            const std::string title = pGameObjectInfo->Name[loc];
            if (Utf8FitTo(title, wnamepart))
                gameobjectName = title.c_str();
        }
}

// Helper function for automatically selling poor quality items to the vendor
void PlayerbotAI::_doSellItem(Item* const item, std::ostringstream& report, std::ostringstream& canSell, uint32& TotalCost, uint32& TotalSold)
{
    if (!item)
        return;

    uint8 autosell = 0;

    std::ostringstream mout;
    if (item->CanBeTraded() && item->GetProto()->Quality == ITEM_QUALITY_POOR) // trash sells automatically.
        autosell = 1;

    ItemPrototype const* pProto = item->GetProto();

    if (SellWhite == 1) // set this with the command 'sell all'
    {
        // here we'll do some checks for other items that are safe to automatically sell such as
        // white items that are a number of levels lower than anything we could possibly use.
        // We'll check to make sure its not a tradeskill tool, quest item etc, things that we don't want to lose.
        if (pProto->SellPrice > 0 && (pProto->Quality == ITEM_QUALITY_NORMAL || pProto->Quality == ITEM_QUALITY_UNCOMMON) && pProto->SubClass != ITEM_SUBCLASS_QUEST)
        {
            if (pProto->RequiredLevel < (m_bot->getLevel() - m_mgr->gConfigSellLevelDiff) && pProto->SubClass != ITEM_SUBCLASS_WEAPON_MISC && pProto->FoodType == 0)
            {
                if (pProto->Class == ITEM_CLASS_WEAPON)
                    autosell = 1;
                if (pProto->Class == ITEM_CLASS_ARMOR)
                    autosell = 1;
            }
            if (pProto->SubClass == ITEM_SUBCLASS_FOOD && (pProto->RequiredLevel < (m_bot->getLevel() - m_mgr->gConfigSellLevelDiff)))
            {
                autosell = 1;
            }
        }
    }

    if (autosell == 1) // set this switch above and this item gets sold automatically. Only set this for automatic sales e.g junk etc.
    {
        uint32 cost = pProto->SellPrice * item->GetCount();

        // handle spell charge if any
        for (auto i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            auto const& spell = pProto->Spells[i];

            // if spell charges for this item are negative, it means that the item should be destroyed once the charges are consumed.
            // it also means that the value of this item is relative to how many charges are remaining.
            if (spell.SpellId != 0 && spell.SpellCharges < 0)
            {
                auto const multiplier = static_cast<float>(item->GetSpellCharges(i)) / spell.SpellCharges;
                cost *= multiplier;
                break;
            }
        }

        m_bot->MoveItemFromInventory(item->GetBagSlot(), item->GetSlot(), true);
        m_bot->AddItemToBuyBackSlot(item, cost);
        m_bot->ModifyMoney(cost);

        ++TotalSold;
        TotalCost += cost;

        report << "Sold ";
        MakeItemLink(item, report, true);
        report << " for " << Cash(cost);
    }
    else if (pProto->SellPrice > 0)
        MakeItemLink(item, canSell, true);
}

bool PlayerbotAI::Withdraw(const uint32 itemid)
{
    Item* pItem = FindItemInBank(itemid);
    if (pItem)
    {
        std::ostringstream report;

        ItemPosCountVec dest;
        InventoryResult msg = m_bot->CanStoreItem(NULL_BAG, NULL_SLOT, dest, pItem, false);
        if (msg != EQUIP_ERR_OK)
        {
            m_bot->SendEquipError(msg, pItem, nullptr);
            return false;
        }

        m_bot->RemoveItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
        m_bot->StoreItem(dest, pItem, true);

        report << "Withdrawn ";
        MakeItemLink(pItem, report, true);

        TellMaster(report.str());
    }
    return true;
}

bool PlayerbotAI::Deposit(const uint32 itemid)
{
    Item* pItem = FindItem(itemid);
    if (pItem)
    {
        std::ostringstream report;

        ItemPosCountVec dest;
        InventoryResult msg = m_bot->CanBankItem(NULL_BAG, NULL_SLOT, dest, pItem, false);
        if (msg != EQUIP_ERR_OK)
        {
            m_bot->SendEquipError(msg, pItem, nullptr);
            return false;
        }

        m_bot->RemoveItem(pItem->GetBagSlot(), pItem->GetSlot(), true);
        m_bot->BankItem(dest, pItem, true);

        report << "Deposited ";
        MakeItemLink(pItem, report, true);

        TellMaster(report.str());
    }
    return true;
}

void PlayerbotAI::BankBalance()
{
    std::ostringstream report;

    report << "In my bank\n ";
    report << "My item slots: ";

    for (uint8 slot = BANK_SLOT_ITEM_START; slot < BANK_SLOT_ITEM_END; ++slot)
    {
        Item* const item = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (item)
            MakeItemLink(item, report, true);
    }
    TellMaster(report.str());

    // and each of my bank bags
    for (uint8 bag = BANK_SLOT_BAG_START; bag < BANK_SLOT_BAG_END; ++bag)
    {
        std::ostringstream goods;
        const Bag* const pBag = static_cast<Bag*>(m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag));
        if (pBag)
        {
            goods << "\nMy ";
            const ItemPrototype* const pBagProto = pBag->GetProto();
            std::string bagName = pBagProto->Name1;
            ItemLocalization(bagName, pBagProto->ItemId);
            goods << bagName << " slot: ";

            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const item = m_bot->GetItemByPos(bag, slot);
                if (item)
                    MakeItemLink(item, goods, true);
            }
            TellMaster(goods.str());
        }
    }
}

bool PlayerbotAI::Talent(Creature* trainer)
{
    if (!(m_bot->resetTalents()))
    {
        std::unique_ptr<WorldPacket> packet(new WorldPacket(MSG_TALENT_WIPE_CONFIRM, 8 + 4));    //you do not have any talent
        *packet << uint64(0);
        *packet << uint32(0);
        m_bot->GetSession()->QueuePacket(std::move(packet));
        return false;
    }

    trainer->CastSpell(m_bot, 14867, TRIGGERED_OLD_TRIGGERED);                  //spell: "Untalent Visual Effect"
    return true;
}

void PlayerbotAI::Repair(const uint32 itemid, Creature* rCreature)
{
    uint32 cost = 0;
    uint8 UseGuild = (m_bot->GetGuildId() != 0) ? uint8(1) : uint8(0);
    Item* rItem = FindItem(itemid, true); // if item equipped or in bags
    if (rItem)
        cost = EstRepair(rItem->GetPos());
    else
        cost = EstRepairAll();

    Guild* pGuild = sGuildMgr.GetGuildById(m_bot->GetGuildId());

    if (pGuild)
    {
        // Check whether bot can use the guildbank first
        if (!pGuild->HasRankRight(m_bot->GetRank(), GR_RIGHT_WITHDRAW_REPAIR))
        {
            DEBUG_LOG("You do not have rights to withdraw for repairs");
            UseGuild = 0;
        }

        if (pGuild->GetGuildBankMoney() < cost)
        {
            DEBUG_LOG("There is not enough money in the guild bank");
            UseGuild = 0;
        }
    }

    // If guildbank unavailable, check pockets
    if (UseGuild == 0)
        if (m_bot->GetMoney() < cost)
        {
            TellMaster("I do not have enough money to repair");
            return;
        }

    ObjectGuid itemGuid = (rItem) ? rItem->GetObjectGuid() : ObjectGuid();

    std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_REPAIR_ITEM, 8 + 8 + 1));
    *packet << rCreature->GetObjectGuid();  // repair npc guid
    *packet << itemGuid; // if item specified then repair this, else repair all
    *packet << UseGuild;  // guildbank yes=1 no=0
    m_bot->GetSession()->QueuePacket(std::move(packet));  // queue the packet to get around race condition
}

bool PlayerbotAI::RemoveAuction(const uint32 auctionid)
{
    QueryResult* result = CharacterDatabase.PQuery(
                              "SELECT houseid,itemguid,item_template,itemowner,buyoutprice,time,buyguid,lastbid,startbid,deposit FROM auction WHERE id = '%u'", auctionid);

    AuctionEntry* auction;

    if (result)
    {
        Field* fields = result->Fetch();

        auction = new AuctionEntry;
        auction->Id = auctionid;
        uint32 houseid  = fields[0].GetUInt32();
        auction->itemGuidLow = fields[1].GetUInt32();
        auction->itemTemplate = fields[2].GetUInt32();
        auction->owner = fields[3].GetUInt32();
        auction->buyout = fields[4].GetUInt32();
        auction->expireTime = fields[5].GetUInt32();
        auction->bidder = fields[6].GetUInt32();
        auction->bid = fields[7].GetUInt32();
        auction->startbid = fields[8].GetUInt32();
        auction->deposit = fields[9].GetUInt32();
        auction->auctionHouseEntry = nullptr;                  // init later

        // check if sold item exists for guid
        // and item_template in fact (GetAItem will fail if problematic in result check in AuctionHouseMgr::LoadAuctionItems)
        Item* pItem = sAuctionMgr.GetAItem(auction->itemGuidLow);
        if (!pItem)
        {
            auction->DeleteFromDB();
            sLog.outError("Auction %u has not a existing item : %u, deleted", auction->Id, auction->itemGuidLow);
            delete auction;
            delete result;
            return false;
        }

        auction->auctionHouseEntry = sAuctionHouseStore.LookupEntry(houseid);

        // Attempt send item back to owner
        std::ostringstream msgAuctionCanceledOwner;
        msgAuctionCanceledOwner << auction->itemTemplate << ":0:" << AUCTION_CANCELED << ":0:0";

        // item will deleted or added to received mail list
        MailDraft(msgAuctionCanceledOwner.str(), "")    // TODO: fix body
        .AddItem(pItem)
        .SendMailTo(MailReceiver(ObjectGuid(HIGHGUID_PLAYER, auction->owner)), auction, MAIL_CHECK_MASK_COPIED);

        if (sAuctionMgr.RemoveAItem(auction->itemGuidLow))
            m_bot->GetSession()->SendAuctionCommandResult(auction, AUCTION_REMOVED, AUCTION_OK);

        auction->DeleteFromDB();

        delete auction;
        delete result;
    }
    return true;
}

// Subject - 9360:0:2
// Subject - item:0:MailAuctionAnswer
// Body - 0:2650:2650:120:132
// Body - 0:High Bid:Buyout:Deposit:AuctionHouse Cut

std::string PlayerbotAI::AuctionResult(std::string subject, std::string body)
{
    std::ostringstream out;
    std::string winner;
    int pos;

    subject.append(":");
    if (body.size() > 0)
    {
        pos = body.find_first_not_of(" ");
        subject.append(body, pos, body.size() - pos);
        subject.append(":");
    }

    // DEBUG_LOG("Auctions string (%s)",subject.c_str());
    pos = 0;
    uint32 a_info[15];
    int i = 0;
    while (true)
    {
        int endpos = subject.find(':', pos);
        if (endpos == -1)
            break;

        std::string idc = subject.substr(pos, endpos - pos);
        a_info[i] = atol(idc.c_str());
        // DEBUG_LOG("a_info[%d] = (%u)",i,a_info[i]);
        pos = endpos + 1;
        ++i;
    }

    if (i == 0)
    {
        out << "This mail is empty";
        return out.str();
    }

    if (a_info[4] != a_info[5])
        winner =  "High Bidder";
    else
        winner =  "Buyout";

    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(a_info[0]);
    if (!pProto)
        return out.str();

    switch (a_info[2])
    {
        case AUCTION_OUTBIDDED:           //= 0,
            out << "Subject: Outbid on: " << pProto->Name1;
            break;
        case AUCTION_WON:                 //= 1,
            out << "Subject: Auction won: " << pProto->Name1 << "\n";
            out << "Item Purchased: " << pProto->Name1 << "\n";
            break;
        case AUCTION_SUCCESSFUL:          //= 2,
        {
            out << "Subject: Auction successful: " << pProto->Name1 << "\n";
            out << "Item Sold: " << pProto->Name1 << "\n";
            out << "\n[" << winner << " Sale: " << Cash(a_info[4]) << "]";
            out << "\n( |cff1eff00Deposit:|cffccffff " << Cash(a_info[6]) << " |cffff0000- Tax:|cffccffff " << Cash(a_info[7]) << " ) |cff1eff00+|cffccffff";
            break;
        }
        case AUCTION_EXPIRED:             //= 3,
            out << "Subject: Auction expired: " << pProto->Name1;
            break;
        case AUCTION_CANCELLED_TO_BIDDER: //= 4,
            out << "Subject: Auction cancelled to bidder: " << pProto->Name1;
            break;
        case AUCTION_CANCELED:            //= 5,
            out << "Subject: Auction cancelled: " << pProto->Name1;
            break;
        case AUCTION_SALE_PENDING:        //= 6
            out << "Subject: Auction sale pending: " << pProto->Name1;
            break;
    }
    return out.str();
}

std::string PlayerbotAI::Cash(uint32 copper)
{
    using namespace std;
    std::ostringstream change;

    uint32 gold = uint32(copper / 10000);
    copper -= (gold * 10000);
    uint32 silver = uint32(copper / 100);
    copper -= (silver * 100);

    if (gold > 0)
        change << gold <<  " |TInterface\\Icons\\INV_Misc_Coin_01:8|t";
    if (silver > 0)
        change << std::setfill(' ') << std::setw(2) << silver << " |TInterface\\Icons\\INV_Misc_Coin_03:8|t";
    change << std::setfill(' ') << std::setw(2) << copper << " |TInterface\\Icons\\INV_Misc_Coin_05:8|t";

    return change.str();
}

void PlayerbotAI::ListQuests(WorldObject* questgiver)
{
    if (!questgiver)
        return;

    // list all bot quests this NPC has
    m_bot->PrepareQuestMenu(questgiver->GetObjectGuid());
    QuestMenu& questMenu = m_bot->PlayerTalkClass->GetQuestMenu();
    std::ostringstream out;
    for (uint32 iI = 0; iI < questMenu.MenuItemCount(); ++iI)
    {
        QuestMenuItem const& qItem = questMenu.GetItem(iI);
        uint32 questID = qItem.m_qId;
        Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);

        std::string questTitle  = pQuest->GetTitle();
        QuestLocalization(questTitle, questID);

        if (m_bot->SatisfyQuestStatus(pQuest, false))
        {
            if (gQuestFetch != 1)
            {
                out << "|cff808080|Hquest:" << questID << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
            }
            else
            {
                if (!AddQuest(questID, questgiver))
                    continue;
            }
        }
    }
    if (!out.str().empty())
        TellMaster(out.str());
}

bool PlayerbotAI::AddQuest(const uint32 entry, WorldObject* questgiver)
{
    std::ostringstream out;

    Quest const* qInfo = sObjectMgr.GetQuestTemplate(entry);
    if (!qInfo)
    {
        ChatHandler(GetMaster()).PSendSysMessage(LANG_COMMAND_QUEST_NOTFOUND, entry);
        return false;
    }

    if (m_bot->GetQuestStatus(entry) == QUEST_STATUS_COMPLETE)
    {
        TellMaster("I already completed that quest.");
        return false;
    }
    else if (!m_bot->CanTakeQuest(qInfo, false))
    {
        if (!m_bot->SatisfyQuestStatus(qInfo, false))
            TellMaster("I already have that quest.");
        else
            TellMaster("I can't take that quest.");
        return false;
    }
    else if (!m_bot->SatisfyQuestLog(false))
    {
        TellMaster("My quest log is full.");
        return false;
    }
    else if (m_bot->CanAddQuest(qInfo, false))
    {
        m_bot->AddQuest(qInfo, questgiver);

        std::string questTitle  = qInfo->GetTitle();
        QuestLocalization(questTitle, entry);

        out << "|cffffff00Quest taken " << "|cff808080|Hquest:" << entry << ':' << qInfo->GetQuestLevel() << "|h[" << questTitle << "]|h|r";

        if (m_bot->CanCompleteQuest(entry))
            m_bot->CompleteQuest(entry);

        // build needed items if quest contains any
        for (int i = 0; i < QUEST_ITEM_OBJECTIVES_COUNT; i++)
            if (qInfo->ReqItemCount[i] > 0)
            {
                SetQuestNeedItems();
                break;
            }

        // build needed creatures if quest contains any
        for (int i = 0; i < QUEST_OBJECTIVES_COUNT; i++)
            if (qInfo->ReqCreatureOrGOCount[i] > 0)
            {
                SetQuestNeedCreatures();
                break;
            }

        if (qInfo->GetSrcSpell() > 0)
            m_bot->CastSpell(m_bot, qInfo->GetSrcSpell(), TRIGGERED_OLD_TRIGGERED);

        TellMaster(out.str());
        return true;
    }
    return false;
}

void PlayerbotAI::ListAuctions()
{
    std::ostringstream report;

    QueryResult* result = CharacterDatabase.PQuery(
                              "SELECT id,itemguid,item_template,time,buyguid,lastbid FROM auction WHERE itemowner = '%u'", m_bot->GetObjectGuid().GetCounter());
    if (result)
    {
        report << "My active auctions are: \n";
        do
        {
            Field* fields = result->Fetch();

            uint32 Id = fields[0].GetUInt32();
            uint32 itemGuidLow = fields[1].GetUInt32();
            uint32 itemTemplate = fields[2].GetUInt32();
            time_t expireTime = fields[3].GetUInt32();
            uint32 bidder = fields[4].GetUInt32();
            uint32 bid = fields[5].GetUInt32();

            time_t remtime = expireTime - CurrentTime();

            tm* aTm = gmtime(&remtime);

            if (expireTime > CurrentTime())
            {
                Item* aItem = sAuctionMgr.GetAItem(itemGuidLow);
                if (aItem)
                {
                    // Name
                    uint32 count = aItem->GetCount();
                    std::string name = aItem->GetProto()->Name1;
                    ItemLocalization(name, itemTemplate);
                    report << "\n|cffffffff|Htitle:" << Id << "|h[" << name;
                    if (count > 1)
                        report << "|cff00ff00x" << count << "|cffffffff" << "]|h|r";
                    else
                        report << "]|h|r";
                }

                if (bidder)
                {
                    ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, bidder);
                    std::string bidder_name;
                    if (sObjectMgr.GetPlayerNameByGUID(guid, bidder_name))
                        report << " " << bidder_name << ": ";

                    report << Cash(bid);
                }
                if (aItem)
                    report << " ends: " << aTm->tm_hour << "|cff0070dd|hH|h|r " << aTm->tm_min << "|cff0070dd|hmin|h|r";
            }
        }
        while (result->NextRow());

        delete result;
        TellMaster(report.str().c_str());
    }
}

void PlayerbotAI::AddAuction(const uint32 itemid, Creature* aCreature)
{
    Item* aItem = FindItem(itemid);
    if (aItem)
    {
        std::ostringstream out;
        srand(CurrentTime());
        uint32 duration[3] = { 720, 1440, 2880 };  // 720 = 12hrs, 1440 = 24hrs, 2880 = 48hrs
        uint32 etime = duration[rand() % 3];

        uint32 min = urand(aItem->GetProto()->SellPrice * aItem->GetCount(), aItem->GetProto()->BuyPrice * aItem->GetCount()) * (aItem->GetProto()->Quality + 1);
        uint32 max = urand(aItem->GetProto()->SellPrice * aItem->GetCount(), aItem->GetProto()->BuyPrice * aItem->GetCount()) * (aItem->GetProto()->Quality + 1);

        out << "Auctioning ";
        MakeItemLink(aItem, out, true);
        out << " with " << aCreature->GetCreatureInfo()->Name;
        TellMaster(out.str().c_str());

        std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_AUCTION_SELL_ITEM, 8 + 8 + 4 + 4 + 4));
        *packet << aCreature->GetObjectGuid();     // auctioneer guid
        *packet << aItem->GetObjectGuid();         // item guid
        *packet << uint32((min < max) ? min : max);  // starting bid
        *packet << uint32((max > min) ? max : min);  // buyout
        *packet << uint32(etime);  // auction duration

        m_bot->GetSession()->QueuePacket(std::move(packet));  // queue the packet to get around race condition
    }
}

void PlayerbotAI::Buy(Creature* vendor, const uint32 itemid)
{
    if (!vendor)
        return;

    // DEBUG_LOG("vendor (%s) itemid (%u)",vendor->GetName(),itemid);

    VendorItemData const* vItems = vendor->GetVendorItems();
    VendorItemData const* tItems = vendor->GetVendorTemplateItems();

    uint8 customitems = vItems ? vItems->GetItemCount() : 0;
    uint8 numitems = customitems + (tItems ? tItems->GetItemCount() : 0);

    for (uint8 vendorslot = 0; vendorslot < numitems; ++vendorslot)
    {
        VendorItem const* crItem = vendorslot < customitems ? vItems->GetItem(vendorslot) : tItems->GetItem(vendorslot - customitems);

        if (crItem)
        {
            if (itemid != crItem->item)
                continue;

            ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(itemid);
            if (pProto)
            {
                // class wrong item skip only for bindable case
                if ((pProto->AllowableClass & m_bot->getClassMask()) == 0 && pProto->Bonding == BIND_WHEN_PICKED_UP)
                    continue;

                if ((pProto->AllowableRace & m_bot->getRaceMask()) == 0)
                    continue;

                m_bot->BuyItemFromVendor(vendor->GetObjectGuid(), itemid, 1, NULL_BAG, NULL_SLOT);
                return;
            }
        }
    }
}

void PlayerbotAI::Sell(const uint32 itemid)
{
    Item* pItem = FindItem(itemid);
    if (pItem)
    {
        std::ostringstream report;

        ItemPrototype const* pProto = pItem->GetProto();

        if (!pProto)
            return;

        uint32 cost = pItem->GetProto()->SellPrice * pItem->GetCount();

        // handle spell charge if any
        for (auto i = 0; i < MAX_ITEM_PROTO_SPELLS; ++i)
        {
            auto const& spell = pProto->Spells[i];

            // if spell charges for this item are negative, it means that the item should be destroyed once the charges are consumed.
            // it also means that the value of this item is relative to how many charges are remaining.
            if (spell.SpellId != 0 && spell.SpellCharges < 0)
            {
                auto const multiplier = static_cast<float>(pItem->GetSpellCharges(i)) / spell.SpellCharges;
                cost *= multiplier;
                break;
            }
        }

        m_bot->MoveItemFromInventory(pItem->GetBagSlot(), pItem->GetSlot(), true);
        m_bot->AddItemToBuyBackSlot(pItem, cost);
        m_bot->ModifyMoney(cost);

        report << "Sold ";
        MakeItemLink(pItem, report, true);
        report << " for " << Cash(cost);

        TellMaster(report.str());
    }
}

void PlayerbotAI::SellGarbage(Player& /*player*/, bool bListNonTrash, bool bDetailTrashSold, bool bVerbose)
{
    uint32 SoldCost = 0;
    uint32 SoldQuantity = 0;
    bool sellableItems = false;
    std::ostringstream report, goods;

    // list out items in main backpack
    for (uint8 slot = INVENTORY_SLOT_ITEM_START; slot < INVENTORY_SLOT_ITEM_END; ++slot)
    {
        Item* const item = m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
        if (item)
            _doSellItem(item, report, goods, SoldCost, SoldQuantity);
    }
    if (goods.str().size() > 0)
        sellableItems = true;
    if (bVerbose && bListNonTrash && goods.str().size() > 0)    // Tell master of unsold items
        TellMaster("Unsold items in my main backpack: %s", goods.str().c_str());

    // and each of our other packs
    for (uint8 bag = INVENTORY_SLOT_BAG_START; bag < INVENTORY_SLOT_BAG_END; ++bag) // check for extra bags
    {
        std::ostringstream subBagGoods;
        const Bag* const pBag = static_cast<Bag*>(m_bot->GetItemByPos(INVENTORY_SLOT_BAG_0, bag));
        if (pBag)
        {
            for (uint8 slot = 0; slot < pBag->GetBagSize(); ++slot)
            {
                Item* const item = m_bot->GetItemByPos(bag, slot);
                if (item)
                    _doSellItem(item, report, subBagGoods, SoldCost, SoldQuantity);
            }
            if (subBagGoods.str().size() > 0)
                sellableItems = true;
            if (bVerbose && bListNonTrash && subBagGoods.str().size() > 0)  // Tell master of unsold items
            {
                const ItemPrototype* const bagProto = pBag->GetProto();     // Get bag name to help master retrieve it
                std::string bagName = bagProto->Name1;
                ItemLocalization(bagName, bagProto->ItemId);
                TellMaster("Unsold items in my %s: %s", bagName.c_str(), subBagGoods.str().c_str());
            }
        }
    }

    if (!bDetailTrashSold) // no trash got sold
        report.str(""); // clear ostringstream

    if (SoldCost > 0)
    {
        if (bDetailTrashSold)
            report << "Sold total " << SoldQuantity << " item(s) for ";
        else
            report << "Sold " << SoldQuantity << " trash item(s) for ";
        report << Cash(SoldCost);

        if (bVerbose)
            TellMaster(report.str());
    }

    // For all bags, non-gray sellable items
    if (bVerbose)
    {
        if (SoldQuantity == 0 && !sellableItems)
            TellMaster("No items to sell, trash or otherwise.");
    }
}

std::string PlayerbotAI::DropItem(const uint32 itemid)
{
    Item* pItem = FindItem(itemid);
    if (pItem)
    {
        std::ostringstream report;

        // Yea, that's right, get the item info BEFORE you destroy it :)
        MakeItemText(pItem, report, true);

        m_bot->DestroyItem(pItem->GetBagSlot(), pItem->GetSlot(), true);

        return report.str();
    }

    return "";
}

void PlayerbotAI::GetTaxi(ObjectGuid guid, BotTaxiNode& nodes)
{
    // DEBUG_LOG("[PlayerbotAI]: GetTaxi - %s node[0] %d node[1] %d", m_bot->GetName(), nodes[0], nodes[1]);

    Creature* unit = m_bot->GetNPCIfCanInteractWith(guid, UNIT_NPC_FLAG_FLIGHTMASTER);
    if (!unit)
    {
        DEBUG_LOG("[PlayerbotAI]: GetTaxi - %s not found or you can't interact with it.", guid.GetString().c_str());
        return;
    }

    if (m_bot->m_taxi.IsTaximaskNodeKnown(nodes[0]) ? 0 : 1)
        return;

    if (m_bot->m_taxi.IsTaximaskNodeKnown(nodes[nodes.size() - 1]) ? 0 : 1)
        return;

    if (m_bot->GetPlayerbotAI()->GetMovementOrder() != MOVEMENT_STAY)
    {
        m_taxiNodes = nodes;
        m_taxiMaster = guid;
        SetState(BOTSTATE_FLYING);
    }
}

void PlayerbotAI::InspectUpdate()
{
    WorldPacket data(CMSG_INSPECT, 8);
    data << m_bot->GetObjectGuid();
    GetMaster()->GetSession()->HandleInspectOpcode(data);
}

// handle commands sent through chat channels
void PlayerbotAI::HandleCommand(const std::string& text, Player& fromPlayer)
{
    // prevent bot task spam
    m_inventory_full = false;
    m_tasks.unique();
    m_findNPC.unique();

    if (m_bDebugCommandChat)
    {
        DEBUG_LOG("chat(%s)", text.c_str());
        TellMaster(text);
    }

    // ignore any messages from Addons
    if (text.empty()                                   ||
            text.find("X-Perl")      != std::wstring::npos ||
            text.find("HealBot")     != std::wstring::npos ||
            text.find("HealComm")    != std::wstring::npos ||   // "HealComm    99990094"
            text.find("LOOT_OPENED") != std::wstring::npos ||
            text.find("CTRA")        != std::wstring::npos ||
            text.find("GathX")       == 0)                      // Gatherer
        return;

    // if message is not from a player in the masters account auto reply and ignore
    if (!canObeyCommandFrom(fromPlayer))
    {
        // only tell the player once instead of endlessly nagging them
        if (m_ignorePlayersChat.find(fromPlayer.GetObjectGuid()) == m_ignorePlayersChat.end())
        {
            std::string msg = "I can't talk to you. Please speak to my master ";
            msg += GetMaster()->GetName();
            SendWhisper(msg, fromPlayer);
            m_bot->HandleEmoteCommand(EMOTE_ONESHOT_NO);
            m_ignorePlayersChat.insert(fromPlayer.GetObjectGuid());
        }
        return;
    }

    // Passed along to ExtractCommand, if (sub)command is found "input" will only contain the rest of the string (or "")
    std::string input = text.c_str();

    // if in the middle of a trade, and player asks for an item/money
    // WARNING: This makes it so you can't use any other commands during a trade!
    if (m_bot->GetTrader() && m_bot->GetTrader()->GetObjectGuid() == fromPlayer.GetObjectGuid())
    {
        uint32 copper = extractMoney(text);
        if (copper > 0)
            TradeCopper(copper);

        std::list<uint32> itemIds;
        extractItemIds(text, itemIds);
        if (itemIds.size() == 0)
            SendWhisper("Show me what item you want by shift clicking the item in the chat window.", fromPlayer);
        else if (!strncmp(text.c_str(), "nt ", 3))
        {
            if (itemIds.size() > 1)
                SendWhisper("There is only one 'Will not be traded' slot. Shift-click just one item, please!", fromPlayer);
            else
            {
                std::list<Item*> itemList;
                findItemsInEquip(itemIds, itemList);
                findItemsInInv(itemIds, itemList);
                if (itemList.size() > 0)
                    TradeItem((**itemList.begin()), TRADE_SLOT_NONTRADED);
                else
                    SendWhisper("I do not have this item equipped or in my bags!", fromPlayer);
            }
        }
        else
        {
            std::list<Item*> itemList;
            findItemsInInv(itemIds, itemList);
            for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
                TradeItem(**it);
        }
    }

    else if (ExtractCommand("help", input))
        _HandleCommandHelp(input, fromPlayer);

    // debug can be enabled without needing to change playerbot.conf file
    else if (text == "debug")
    {
        TellMaster("Debugging is on. Type 'no debug' to disable.");
        GetManager()->m_confDebugWhisper = true;
    }
    else if (text == "no debug")
    {
        TellMaster("Debugging is off.");
        GetManager()->m_confDebugWhisper = false;
    }

    else if (fromPlayer.GetSession()->GetSecurity() > SEC_PLAYER && ExtractCommand("gm", input))
        _HandleCommandGM(input, fromPlayer);

    else if (ExtractCommand("reset", input))
        _HandleCommandReset(input, fromPlayer);
    else if (ExtractCommand("orders", input))
        _HandleCommandOrders(input, fromPlayer);
    else if (ExtractCommand("follow", input) || ExtractCommand("come", input))
        _HandleCommandFollow(input, fromPlayer);
    else if (ExtractCommand("stay", input) || ExtractCommand("stop", input))
        _HandleCommandStay(input, fromPlayer);
    else if (ExtractCommand("attack", input))
        _HandleCommandAttack(input, fromPlayer);
    else if (ExtractCommand("pull", input))
        _HandleCommandPull(input, fromPlayer);

    else if (ExtractCommand("neutralize", input) || ExtractCommand("neutral", input))
        _HandleCommandNeutralize(input, fromPlayer);

    else if (ExtractCommand("cast", input, true)) // true -> "cast" OR "c"
        _HandleCommandCast(input, fromPlayer);

    else if (ExtractCommand("sell", input))
        _HandleCommandSell(input, fromPlayer);

    else if (ExtractCommand("buy", input))
        _HandleCommandBuy(input, fromPlayer);

    else if (ExtractCommand("drop", input))
        _HandleCommandDrop(input, fromPlayer);

    else if (ExtractCommand("repair", input))
        _HandleCommandRepair(input, fromPlayer);

    else if (ExtractCommand("auction", input))
        _HandleCommandAuction(input, fromPlayer);

    else if (ExtractCommand("mail", input))
        _HandleCommandMail(input, fromPlayer);

    else if (ExtractCommand("bank", input))
        _HandleCommandBank(input, fromPlayer);

    else if (ExtractCommand("talent", input))
        _HandleCommandTalent(input, fromPlayer);

    else if (ExtractCommand("use", input, true)) // true -> "use" OR "u"
        _HandleCommandUse(input, fromPlayer);

    else if (ExtractCommand("equip", input, true)) // true -> "equip" OR "e"
        _HandleCommandEquip(input, fromPlayer);

    else if (ExtractCommand("resumeorders", input)) // restore previous combat orders if any
        BotDataRestore();

    // find project: 20:50 02/12/10 rev.4 item in world and wait until ordered to follow
    else if (ExtractCommand("find", input, true)) // true -> "find" OR "f"
        _HandleCommandFind(input, fromPlayer);

    // get project: 20:50 02/12/10 rev.4 compact edition, handles multiple linked gameobject & improves visuals
    else if (ExtractCommand("get", input, true)) // true -> "get" OR "g"
        _HandleCommandGet(input, fromPlayer);

    // Handle all collection related commands here
    else if (ExtractCommand("collect", input))
        _HandleCommandCollect(input, fromPlayer);

    else if (ExtractCommand("quest", input))
        _HandleCommandQuest(input, fromPlayer);

    else if (ExtractCommand("craft", input))
        _HandleCommandCraft(input, fromPlayer);

    else if (ExtractCommand("enchant", input))
        _HandleCommandEnchant(input, fromPlayer);

    else if (ExtractCommand("process", input))
        _HandleCommandProcess(input, fromPlayer);

    else if (ExtractCommand("pet", input))
        _HandleCommandPet(input, fromPlayer);

    else if (ExtractCommand("spells", input))
        _HandleCommandSpells(input, fromPlayer);

    // survey project: 20:50 02/12/10 rev.4 compact edition
    else if (ExtractCommand("survey", input))
        _HandleCommandSurvey(input, fromPlayer);

    // Handle class & professions training:
    else if (ExtractCommand("skill", input))
        _HandleCommandSkill(input, fromPlayer);

    // stats project: 11:30 15/12/10 rev.2 display bot statistics
    else if (ExtractCommand("stats", input))
        _HandleCommandStats(input, fromPlayer);

    else
    {
        // if this looks like an item link, reward item it completed quest and talking to NPC
        std::list<uint32> itemIds;
        extractItemIds(text, itemIds);
        if (!itemIds.empty())
        {
            uint32 itemId = itemIds.front();
            bool wasRewarded = false;
            ObjectGuid questRewarderGUID = m_bot->GetSelectionGuid();
            Object* const pNpc = (WorldObject*) m_bot->GetObjectByTypeMask(questRewarderGUID, TYPEMASK_CREATURE_OR_GAMEOBJECT);
            if (!pNpc)
                return;

            QuestMenu& questMenu = m_bot->PlayerTalkClass->GetQuestMenu();
            for (uint32 iI = 0; !wasRewarded && iI < questMenu.MenuItemCount(); ++iI)
            {
                QuestMenuItem const& qItem = questMenu.GetItem(iI);

                uint32 questID = qItem.m_qId;
                Quest const* pQuest = sObjectMgr.GetQuestTemplate(questID);
                QuestStatus status = m_bot->GetQuestStatus(questID);

                // if quest is complete, turn it in
                if (status == QUEST_STATUS_COMPLETE &&
                        !m_bot->GetQuestRewardStatus(questID) &&
                        pQuest->GetRewChoiceItemsCount() > 1 &&
                        m_bot->CanRewardQuest(pQuest, false))
                    for (uint8 rewardIdx = 0; !wasRewarded && rewardIdx < pQuest->GetRewChoiceItemsCount(); ++rewardIdx)
                    {
                        ItemPrototype const* const pRewardItem = sObjectMgr.GetItemPrototype(pQuest->RewChoiceItemId[rewardIdx]);
                        if (itemId == pRewardItem->ItemId)
                        {
                            m_bot->RewardQuest(pQuest, rewardIdx, pNpc, false);

                            std::string questTitle  = pQuest->GetTitle();
                            m_bot->GetPlayerbotAI()->QuestLocalization(questTitle, questID);
                            std::string itemName = pRewardItem->Name1;
                            m_bot->GetPlayerbotAI()->ItemLocalization(itemName, pRewardItem->ItemId);

                            std::ostringstream out;
                            out << "|cffffffff|Hitem:" << pRewardItem->ItemId << ":0:0:0:0:0:0:0" << "|h[" << itemName << "]|h|r rewarded";
                            SendWhisper(out.str(), fromPlayer);
                            wasRewarded = true;
                        }
                    }
            }
        }
        else
        {
            // TODO: make this only in response to direct whispers (chatting in party chat can in fact be between humans)
            std::string msg = "What is [";
            std::string textsub;
            if (text.length() > 10)
                textsub = text.substr(0, 10) + "...";
            else
                textsub = text;
            msg += textsub.c_str();
            msg += "]? For a list of commands, ask for 'help'.";
            SendWhisper(msg, fromPlayer);
            m_bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
        }
    }
}

/**
* ExtractCommand looks for a command in a text string
* sLookingFor       - string you're looking for (e.g. "help")
* text              - string which may or may not start with sLookingFor
* bUseShort         - does this command accept the shorthand command? If true, "help" would ALSO look for "h"
*
* returns true if the string has been found
* returns false if the string has not been found
*/
bool PlayerbotAI::ExtractCommand(const std::string sLookingFor, std::string& text, bool bUseShort)
{
    // ("help" + " ") < "help X"  AND  text's start (as big as sLookingFor) == sLookingFor
    // Recommend AGAINST adapting this for non-space situations (thinking MangosZero)
    // - unknown would risk being (short for "use") 'u' + "nknown"
    if (sLookingFor.size() + 1 < text.size() && text.at(sLookingFor.size()) == ' '
            && 0 == text.substr(0, sLookingFor.size()).compare(sLookingFor))
    {
        text = text.substr(sLookingFor.size() + 1);
        return true;
    }

    if (0 == text.compare(sLookingFor))
    {
        text = "";
        return true;
    }

    if (bUseShort)
    {
        if (text.size() > 1 && sLookingFor.at(0) == text.at(0) && text.at(1) == ' ')
        {
            text = text.substr(2);
            return true;
        }
        else if (text.size() == 1 && sLookingFor.at(0) == text.at(0))
        {
            text = "";
            return true;
        }
    }

    return false;
}

void PlayerbotAI::_HandleCommandReset(std::string& text, Player& fromPlayer)
{
    if (text != "")
    {
        SendWhisper("reset does not have a subcommand.", fromPlayer);
        return;
    }
    SetState(BOTSTATE_NORMAL);
    MovementReset();
    SetQuestNeedItems();
    SetQuestNeedCreatures();
    UpdateAttackerInfo();
    m_lootTargets.clear();
    m_lootCurrent = ObjectGuid();
    m_targetCombat = 0;
}

void PlayerbotAI::_HandleCommandOrders(std::string& text, Player& fromPlayer)
{
    if (ExtractCommand("delay", text))
    {
        uint32 gdelay;
        sscanf(text.c_str(), "%d", &gdelay);
        if (gdelay <= 10)
        {
            m_DelayAttack = gdelay;
            TellMaster("Combat delay is now '%u' ", m_DelayAttack);
            CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET combat_delay = '%u' WHERE guid = '%u'", m_DelayAttack, m_bot->GetGUIDLow());
            return;
        }
        else
            SendWhisper("Invalid delay. choose a number between 0 and 10", fromPlayer);
        return;
    }
    else if (ExtractCommand("resume", text))
        CombatOrderRestore();
    else if (ExtractCommand("combat", text, true))
    {
        Unit* target = nullptr;

        if (text == "")
        {
            SendWhisper("|cffff0000Syntax error:|cffffffff orders combat <botName> <reset | tank | heal | passive><assist | protect [targetPlayer]>", fromPlayer);
            return;
        }

        QueryResult* resultlvl = CharacterDatabase.PQuery("SELECT guid FROM playerbot_saved_data WHERE guid = '%u'", m_bot->GetObjectGuid().GetCounter());
        if (!resultlvl)
            CharacterDatabase.DirectPExecute("INSERT INTO playerbot_saved_data (guid,combat_order,primary_target,secondary_target,pname,sname,combat_delay) VALUES ('%u',0,0,0,'','',0)", m_bot->GetObjectGuid().GetCounter());
        else
            delete resultlvl;

        size_t protect = text.find("protect");
        size_t assist = text.find("assist");

        if (ExtractCommand("protect", text) || ExtractCommand("assist", text))
        {
            ObjectGuid targetGUID = fromPlayer.GetSelectionGuid();
            if (text == "" && !targetGUID)
            {
                SendWhisper("|cffff0000Combat orders protect and assist expect a target either by selection or by giving target player in command string!", fromPlayer);
                return;
            }

            if (text != "")
            {
                ObjectGuid targ_guid = sObjectMgr.GetPlayerGuidByName(text.c_str());
                targetGUID.Set(targ_guid.GetRawValue());
            }
            target = ObjectAccessor::GetUnit(fromPlayer, targetGUID);
            if (!target)
                return SendWhisper("|cffff0000Invalid target for combat order protect or assist!", fromPlayer);

            if (protect != std::string::npos)
                SetCombatOrder(ORDERS_PROTECT, target);
            else if (assist != std::string::npos)
                SetCombatOrder(ORDERS_ASSIST, target);
        }
        else
            SetCombatOrderByStr(text, target);
    }
    else if (text != "")
    {
        SendWhisper("See help for details on using 'orders'.", fromPlayer);
        return;
    }
    SendOrders(*GetMaster());
}

void PlayerbotAI::_HandleCommandFollow(std::string& text, Player& fromPlayer)
{
    if (ExtractCommand("auto", text)) // switch to automatic follow distance
    {
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'follow'", fromPlayer);
            return;
        }
        DistOverRide = 0; // this resets follow distance to config default
        IsUpOrDown = 0;
        std::ostringstream msg;
        gTempDist = 1;
        gTempDist2 = 2;

        if (m_FollowAutoGo != FOLLOWAUTOGO_SET)
        {
            m_FollowAutoGo = FOLLOWAUTOGO_INIT;
            msg << "Automatic Follow Distance is now |h|cff1eff00ON|h|r";
            SendWhisper(msg.str(), fromPlayer);
        }
        else
        {
            m_FollowAutoGo = FOLLOWAUTOGO_OFF;
            msg << "Automatic Follow Distance is now |h|cffff0000OFF|h|r";
            SendWhisper(msg.str(), fromPlayer);
        }
        CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET auto_follow = '%u' WHERE guid = '%u'", m_FollowAutoGo, m_bot->GetGUIDLow());
    }
    else if (ExtractCommand("reset", text)) // switch to reset follow distance
    {
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'follow'", fromPlayer);
            return;
        }
        DistOverRide = 0; // this resets follow distance to config default
        IsUpOrDown = 0;
        std::ostringstream msg;
        gTempDist = 1;
        gTempDist2 = 2;
        msg << "Bit crowded isn't it?";
        SendWhisper(msg.str(), fromPlayer);
    }
    else if (ExtractCommand("far", text)) // switch to increment follow distance
    {
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'follow'", fromPlayer);
            return;
        }
        DistOverRide = (DistOverRide + 1); // this increments follow distance
        std::ostringstream msg;
        msg << "Increasing My follow distance";
        SendWhisper(msg.str(), fromPlayer);
    }
    else if (ExtractCommand("near", text)) // switch to increment follow distance
    {
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'follow'", fromPlayer);
            return;
        }
        if (DistOverRide > 0)
            DistOverRide = (DistOverRide - 1); // this increments follow distance,

        std::ostringstream msg;
        if (DistOverRide == 0)
        {
            IsUpOrDown = 0;
            DistOverRide = 0;
            gTempDist = 1;
            gTempDist2 = 2;
            msg << "I'm NOT getting any closer than this";
        }
        if (DistOverRide != 0)
            msg << "Decreasing My follow distance";
        SendWhisper(msg.str(), fromPlayer);
    }
    else if (ExtractCommand("info", text))
    {
        std::ostringstream msg;

        msg << "Automatic Follow Distance is ";

        switch (DistOverRide)
        {
            case 0: msg << "|h|cffff0000" << m_bot->GetDistance(GetMaster()) << "|h|r"; break; //red
            case 1: msg << "|h|cffff8000" << m_bot->GetDistance(GetMaster()) << "|h|r"; break; //yellow
            case 2: msg << "|h|cffe6cc80" << m_bot->GetDistance(GetMaster()) << "|h|r"; break; //orange
            case 3: msg << "|h|cff1eff00" << m_bot->GetDistance(GetMaster()) << "|h|r"; break; //green
            case 4:
            default: msg << "|h|cff0070dd" << m_bot->GetDistance(GetMaster()) << "|h|r"; break; //blue
        }

        m_FollowAutoGo ?  SendWhisper(msg.str(), fromPlayer) : SendWhisper("Automatic Follow Distance is |h|cffff0000OFF|h|r", fromPlayer);
        return;
    }
    else if (text != "")
    {
        SendWhisper("see help for details on using follow.", fromPlayer);
        return;
    }
    SetMovementOrder(MOVEMENT_FOLLOW, GetMaster());
}

void PlayerbotAI::_HandleCommandStay(std::string& text, Player& fromPlayer)
{
    if (text != "")
    {
        SendWhisper("stay cannot have a subcommand.", fromPlayer);
        return;
    }
    SetMovementOrder(MOVEMENT_STAY);
}

void PlayerbotAI::_HandleCommandAttack(std::string& text, Player& fromPlayer)
{
    if (text != "")
    {
        SendWhisper("attack cannot have a subcommand.", fromPlayer);
        return;
    }
    ObjectGuid attackOnGuid = fromPlayer.GetSelectionGuid();
    if (attackOnGuid)
    {
        if (Unit* thingToAttack = ObjectAccessor::GetUnit(*m_bot, attackOnGuid))
        {
            if (m_bot->CanAttack(thingToAttack))
            {
                if (!m_bot->IsWithinLOSInMap(thingToAttack))
                    DoTeleport(*m_followTarget);
                if (m_bot->IsWithinLOSInMap(thingToAttack))
                    Attack(thingToAttack);
            }
        }
    }
    else
    {
        SendWhisper("No target is selected.", fromPlayer);
        m_bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
    }
}

void PlayerbotAI::_HandleCommandPull(std::string& text, Player& fromPlayer)
{
    bool bReadyCheck = false;

    if (!m_bot) return;

    if (ExtractCommand("test", text)) // switch to automatic follow distance
    {
        if (CanPull(fromPlayer))
            SendWhisper("Looks like I am capable of pulling. Ask me 'pull ready' with a target for a more precise check.", fromPlayer);
        return;
    }
    if (ExtractCommand("ready", text)) // switch to automatic follow distance
    {
        bReadyCheck = true;
    }
    else if (text != "")
    {
        SendWhisper("See 'help pull' for details on using the pull command.", fromPlayer);
        return;
    }

    // This function also takes care of error reporting
    if (!CanPull(fromPlayer))
        return;

    // Check for valid target
    m_bot->SetSelectionGuid(fromPlayer.GetSelectionGuid());
    ObjectGuid attackOnGuid = m_bot->GetSelectionGuid();
    if (!attackOnGuid)
    {
        SendWhisper("No target is selected.", fromPlayer);
        return;
    }

    Unit* thingToAttack = ObjectAccessor::GetUnit(*m_bot, attackOnGuid);
    if (!thingToAttack)
    {
        SendWhisper("No target is selected.", fromPlayer);
        return;
    }

    if (m_bot->CanAssist(thingToAttack))
    {
        SendWhisper("Where I come from we don't attack our friends.", fromPlayer);
        return;
    }
    // TODO: Okay, this one should actually be fixable. InMap should return, but LOS (Line of Sight) should result in moving, well, into LoS.
    if (!m_bot->IsWithinLOSInMap(thingToAttack))
    {
        SendWhisper("I can't see that target!", fromPlayer);
        return;
    }
    GetCombatTarget(thingToAttack);
    if (!GetCurrentTarget())
    {
        SendWhisper("Failed to set target, cause unknown.", fromPlayer);
        return;
    }
    if (bReadyCheck)
    {
        SendWhisper("All checks have been passed and I am ready to pull! ... Are you sure you wouldn't like a smaller target?", fromPlayer);
        return;
    }

    // All healers which have it available will cast any applicable HoT (Heal over Time) spell on the tank
    GroupHoTOnTank();

    /* Technically the tank should wait a bit if/until the HoT has been applied
       but the above function immediately casts it rather than wait for an UpdateAI tick

       There is no need to take into account that GroupHoTOnTank() may fail due to global cooldown. Either you're prepared for a difficult
       pull in which case it won't fail due to global cooldown, or you're chaining easy pulls in which case you don't care.
       */
    /* So have the group wait for the tank to take action (and aggro) - this way it will be easy to see if tank has aggro or not without having to
       worry about tank not being the first to have UpdateAI() called
       */

    // Need to have a group and a tank, both checked in "CanPull()" call above
    //if (!(GetGroupTank()->GetPlayerbotAI()->GetClassAI()->Pull()))
    // I've been told to pull and a check was done above whether I'm actually a tank, so *I* will try to pull:
    if (!CastPull())
    {
        SendWhisper("I did my best but I can't actually pull. How odd.", fromPlayer);
        return;
    }

    // Sets Combat Orders to PULL
    SetGroupCombatOrder(ORDERS_TEMP_WAIT_TANKAGGRO);

    SetGroupIgnoreUpdateTime(2);

    // Set all group members (save this tank) to wait 10 seconds. They will wait until the tank says so, until any non-tank gains aggro or 10 seconds - whichever is shortest
    if (m_bot->GetGroup()) // one last sanity check, should be unnecessary
    {
        Group::MemberSlotList const& groupSlot = m_bot->GetGroup()->GetMemberSlots();
        for (Group::member_citerator itr = groupSlot.begin(); itr != groupSlot.end(); itr++)
        {
            Player* groupMember = sObjectMgr.GetPlayer(itr->guid);
            if (!groupMember || !groupMember->GetPlayerbotAI() || groupMember == m_bot)
                continue;
            groupMember->GetPlayerbotAI()->GetClassAI()->SetWait(10);
        }
    }

    //(4a) if tank, deactivate any attack (such as 'shoot (bow/gun)' for warriors), wait until in melee range, attack
    //(4b) if dps, wait until the target is in melee range of the tank +2seconds or until tank no longer holds aggro
    //(4c) if healer, do healing checks
    //(5) when target is in melee range of tank, wait 2 seconds (healers continue to do group heal checks, all do self-heal checks), then return to normal functioning
}

void PlayerbotAI::_HandleCommandNeutralize(std::string& text, Player& fromPlayer)
{
    if (!m_bot) return;

    if (text != "")
    {
        SendWhisper("See 'help neutralize' for details on using the neutralize command.", fromPlayer);
        return;
    }

    // Check for valid target
    m_bot->SetSelectionGuid(fromPlayer.GetSelectionGuid());
    ObjectGuid selectOnGuid = m_bot->GetSelectionGuid();
    if (!selectOnGuid)
    {
        SendWhisper("No target is selected.", fromPlayer);
        return;
    }

    Unit* thingToNeutralize = ObjectAccessor::GetUnit(*m_bot, selectOnGuid);
    if (!thingToNeutralize)
    {
        SendWhisper("No valid target is selected.", fromPlayer);
        return;
    }

    if (m_bot->CanAssist(thingToNeutralize))
    {
        SendWhisper("I can't neutralize that target: this is a friend to me.", fromPlayer);
        return;
    }

    if (!m_bot->IsWithinLOSInMap(thingToNeutralize))
    {
        SendWhisper("I can't see that target!", fromPlayer);
        return;
    }

    if (IsNeutralized(thingToNeutralize))
    {
        SendWhisper("Target is already neutralized.", fromPlayer);
        return;
    }

    m_targetGuidCommand = selectOnGuid;

    // All checks passed: call the Neutralize function of each bot class
    // to define what spellid to use if available and if creature type is correct
    // m_spellIdCommand will be defined there and UpdateAI will then handle the cast
    if (!CastNeutralize())
    {
        SendWhisper("Something went wrong: I can't neutralize that target.", fromPlayer);
        return;
    }
}

void PlayerbotAI::_HandleCommandCast(std::string& text, Player& fromPlayer)
{
    if (text == "")
    {
        SendWhisper("cast must be used with a single spell link (shift + click the spell).", fromPlayer);
        return;
    }

    std::string spellStr = text;
    uint32 spellId = (uint32) atol(spellStr.c_str());

    // try and get spell ID by name
    if (spellId == 0)
    {
        spellId = getSpellId(spellStr.c_str(), true);

        // try link if text NOT (spellid OR spellname)
        if (spellId == 0)
            extractSpellId(text, spellId);
    }

    if (m_bot->HasAura(spellId))
    {
        m_bot->RemoveAurasByCasterSpell(spellId, m_bot->GetObjectGuid());
        return;
    }

    ObjectGuid castOnGuid = fromPlayer.GetSelectionGuid();
    if (spellId != 0 && m_bot->HasSpell(spellId))
    {
        m_spellIdCommand = spellId;
        if (castOnGuid)
            m_targetGuidCommand = castOnGuid;
        else
            m_targetGuidCommand = m_bot->GetObjectGuid();
    }
}

// _HandleCommandSell: Handle selling items
// sell [Item Link][Item Link] .. -- Sells bot(s) items from inventory
void PlayerbotAI::_HandleCommandSell(std::string& text, Player& fromPlayer)
{
    FollowAutoReset();
    if (ExtractCommand("all", text)) // switch to auto sell low level white items
    {
        std::ostringstream msg;
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'sell all'", fromPlayer);
            return;
        }
        SellWhite = !SellWhite;
        msg << "I will " << (SellWhite ? "" : "no longer ") << "sell my low level normal items.";
        SendWhisper(msg.str(), fromPlayer);
        return;
    }
    if (text == "")
    {
        SendWhisper("sell must be used with one or more item links (shift + click the item).", fromPlayer);
        return;
    }

    std::list<uint32> itemIds;
    extractItemIds(text, itemIds);
    for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(SELL_ITEMS, *it));
    m_findNPC.push_back(VENDOR_MASK);
}

// _HandleCommandBuy: Handle buying items
// buy [Item Link][Item Link] .. -- Buys items from vendor
void PlayerbotAI::_HandleCommandBuy(std::string& text, Player& fromPlayer)
{
    if (text == "")
    {
        SendWhisper("buy must be used with one or more item links (shift + click the item).", fromPlayer);
        return;
    }

    FollowAutoReset();
    /*    ObjectGuid vendorguid = fromPlayer.GetSelectionGuid();
        if (!vendorguid)
        {
            SendWhisper("No vendor is selected.", fromPlayer);
            m_bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
            return;
        }*/

    std::list<uint32> itemIds;
    extractItemIds(text, itemIds);
    for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(BUY_ITEMS, *it));
    m_findNPC.push_back(VENDOR_MASK);
}

// _HandleCommandDrop: Handle dropping items
// drop [Item Link][Item Link] .. -- Drops item(s) from bot's inventory
void PlayerbotAI::_HandleCommandDrop(std::string& text, Player& fromPlayer)
{
    if (text == "")
    {
        SendWhisper("drop must be used with one or more item links (shift + click the item).", fromPlayer);
        return;
    }

    std::ostringstream report;
    std::list<uint32> itemIds;
    extractItemIds(text, itemIds);
    report << "Dropped ";
    for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
        report << DropItem(*it);

    if (report.str() == "Dropped ")
    {
        SendWhisper("No items were dropped. It would appear something has gone hinky.", fromPlayer);
        return;
    }
    SetQuestNeedItems();
    report << ".";
    SendWhisper(report.str(), fromPlayer);
}

// _HandleCommandRepair: Handle repair items
// repair  all                      -- repair all bot(s) items
// repair [Item Link][Item Link] .. -- repair select bot(s) items
void PlayerbotAI::_HandleCommandRepair(std::string& text, Player& fromPlayer)
{
    FollowAutoReset();
    if (ExtractCommand("all", text))
    {
        if (text != "")
        {
            SendWhisper("Invalid subcommand for 'repair all'", fromPlayer);
            return;
        }
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(REPAIR_ITEMS, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_REPAIR);
        return;
    }

    std::list<uint32> itemIds;
    extractItemIds(text, itemIds);

    for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); it++)
    {
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(REPAIR_ITEMS, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_REPAIR);
    }
}

// _HandleCommandAuction: Handle auctions:
// auction                                        -- Lists bot(s) active auctions.
// auction add [Item Link][Item Link] ..          -- Create bot(s) active auction.
// auction remove [Auction Link][Auction Link] .. -- Cancel bot(s) active auction. ([Auction Link] from auction)
void PlayerbotAI::_HandleCommandAuction(std::string& text, Player& fromPlayer)
{
    FollowAutoReset();
    if (text == "")
    {
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(LIST_AUCTION, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_AUCTIONEER); // list all bot auctions
    }
    else if (ExtractCommand("add", text))
    {
        std::list<uint32> itemIds;
        extractItemIds(text, itemIds);
        for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
            m_tasks.push_back(std::pair<enum TaskFlags, uint32>(ADD_AUCTION, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_AUCTIONEER);
    }
    else if (ExtractCommand("remove", text))
    {
        std::list<uint32> auctionIds;
        extractAuctionIds(text, auctionIds);
        for (std::list<uint32>::iterator it = auctionIds.begin(); it != auctionIds.end(); ++it)
            m_tasks.push_back(std::pair<enum TaskFlags, uint32>(REMOVE_AUCTION, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_AUCTIONEER);
    }
    else
    {
        SendWhisper("I don't understand what you're trying to do", fromPlayer);
    }
}

void PlayerbotAI::_HandleCommandMail(std::string& text, Player& fromPlayer)
{
    ChatHandler ch(&fromPlayer);

    if (text == "")
    {
        ch.SendSysMessage("Syntax: mail <inbox [Mailbox] | getcash [mailid].. | getitem [mailid].. | delete [mailid]..>");
        return;
    }
    else if (ExtractCommand("inbox", text))
    {
        uint32 mail_count = 0;
        extractGOinfo(text, m_lootTargets);

        if (m_lootTargets.empty())
        {
            ch.SendSysMessage("Syntax: mail <inbox [Mailbox]>");
            return;
        }

        ObjectGuid m_mailboxGuid = m_lootTargets.front();
        m_lootTargets.pop_front();
        m_lootTargets.clear();

        if (!m_bot->GetGameObjectIfCanInteractWith(m_mailboxGuid, GAMEOBJECT_TYPE_MAILBOX))
        {
            Announce(CANT_USE_TOO_FAR);
            return;
        }

        TellMaster("Inbox:\n");

        for (PlayerMails::reverse_iterator itr = m_bot->GetMailRBegin(); itr != m_bot->GetMailREnd(); ++itr)
        {
            std::ostringstream msg;
            ++mail_count;
            std::string body = "";

            QueryResult* result = CharacterDatabase.PQuery("SELECT text FROM item_text WHERE id = '%u'", (*itr)->itemTextId);
            if (result)
            {
                Field* fields = result->Fetch();

                body  = fields[0].GetString();
            }
            delete result;

            msg  << "|cffffcccc|Hmail:" << (*itr)->messageID << "|h[" << (*itr)->messageID << "]|h|r ";

            switch ((*itr)->messageType)
            {
                case MAIL_NORMAL:
                {
                    msg << "|cffffffff"; // white
                    if ((*itr)->subject != "")
                        msg << "Subject: " << (*itr)->subject << "\n";

                    if (body != "")
                        msg << body << "\n";
                    break;
                }
                case MAIL_CREATURE:
                    msg << "|cffccffccMAIL_CREATURE\n"; // green
                    break;
                case MAIL_GAMEOBJECT:
                    msg << "|cffccffccMAIL_GAMEOBJECT\n"; // green
                    break;
                case MAIL_AUCTION:
                {
                    msg << "|cffccffff"; // blue
                    msg << AuctionResult((*itr)->subject, body) << "\n";
                    break;
                }
                case MAIL_ITEM:
                    msg << "|cffccffccMAIL_ITEM\n"; // green
                    break;
            }

            std::string subject = (*itr)->subject;
            subject.append(":");

            int pos = 0, i = 0;
            uint32 element[10];
            while (true)
            {
                int endpos = subject.find(':', pos);
                if (endpos == -1)
                    break;

                std::string idc = subject.substr(pos, endpos - pos);
                element[i] = atol(idc.c_str());
                DEBUG_LOG("element[%d] = (%u)", i, element[i]);
                pos = endpos + 1;
                ++i;
            }

            if (element[2] == 6) // mail pending
            {
                tm* timeinfo;
                time_t eta = (*itr)->deliver_time + HOUR;
                timeinfo = gmtime(&eta);

                msg << "Estimated delivery time " << asctime(timeinfo);
            }

            if ((*itr)->money)
                msg << "[To Collect: " << Cash((*itr)->money) << " ]\n";

            uint8 item_count = (*itr)->items.size(); // max count is MAX_MAIL_ITEMS (12)
            if (item_count > 0)
            {
                msg << "Items: ";
                for (uint8 i = 0; i < item_count; ++i)
                {
                    Item* item = m_bot->GetMItem((*itr)->items[i].item_guid);
                    if (item)
                        MakeItemLink(item, msg, true);
                }
            }
            msg << "\n";
            ch.SendSysMessage(msg.str().c_str());
        }

        if (mail_count == 0)
            ch.SendSysMessage("|cff009900My inbox is empty.");
    }
    else if (ExtractCommand("getcash", text))
    {
        std::ostringstream msg;
        std::list<uint32> mailIds;
        extractMailIds(text, mailIds);
        mailIds.unique();
        mailIds.sort();
        uint32 total = 0;

        if (mailIds.empty())
        {
            ch.SendSysMessage("Syntax: mail <getcash [mailId]..>");
            return;
        }

        for (std::list<uint32>::iterator it = mailIds.begin(); it != mailIds.end(); ++it)
        {
            Mail* m = m_bot->GetMail(*it);
            if (!m || m->state == MAIL_STATE_DELETED || m->deliver_time > CurrentTime())
            {
                m_bot->SendMailResult(*it, MAIL_MONEY_TAKEN, MAIL_ERR_INTERNAL_ERROR);
                return;
            }

            m_bot->SendMailResult(*it, MAIL_MONEY_TAKEN, MAIL_OK);
            m_bot->ModifyMoney(m->money);
            total += m->money;
            m->money = 0;
            m->state = MAIL_STATE_CHANGED;
            m_bot->m_mailsUpdated = true;
            m_bot->UpdateMail();
        }
        if (total > 0)
        {
            msg << "|cff009900" << "I received: |r" << Cash(total);
            ch.SendSysMessage(msg.str().c_str());
        }
    }
    else if (ExtractCommand("getitem", text))
    {
        std::list<uint32> mailIds;
        extractMailIds(text, mailIds);
        mailIds.unique();
        mailIds.sort();

        if (mailIds.empty())
        {
            ch.SendSysMessage("Syntax: mail <getitem [mailId]..>");
            return;
        }

        for (std::list<uint32>::iterator it = mailIds.begin(); it != mailIds.end(); it++)
        {
            Mail* m = m_bot->GetMail(*it);
            if (!m || m->state == MAIL_STATE_DELETED || m->deliver_time > CurrentTime())
            {
                m_bot->SendMailResult(*it, MAIL_ITEM_TAKEN, MAIL_ERR_INTERNAL_ERROR);
                return;
            }

            // prevent cheating with skip client money check
            if (m_bot->GetMoney() < m->COD)
            {
                m_bot->SendMailResult(*it, MAIL_ITEM_TAKEN, MAIL_ERR_NOT_ENOUGH_MONEY);
                return;
            }

            if (m->HasItems())
            {
                bool has_items = true;
                std::ostringstream msg;

                msg << "|cff009900" << "I received item: |r";
                for (MailItemInfoVec::const_iterator itr = m->items.begin(); itr != m->items.end();)
                {
                    has_items = true;
                    Item* item = m_bot->GetMItem(itr->item_guid);
                    if (!item)
                    {
                        ch.SendSysMessage("item not found");
                        return;
                    }

                    ItemPosCountVec dest;

                    InventoryResult res = m_bot->CanStoreItem(NULL_BAG, NULL_SLOT, dest, item, false);
                    if (res == EQUIP_ERR_OK)
                    {
                        m->removedItems.push_back(itr->item_guid);

                        if (m->COD > 0)  // if there is COD, take COD money from player and send them to sender by mail
                        {
                            ObjectGuid sender_guid = ObjectGuid(HIGHGUID_PLAYER, m->sender);
                            Player* sender = sObjectMgr.GetPlayer(sender_guid);

                            uint32 sender_accId = 0;

                            if (GetMaster()->GetSession()->GetSecurity() > SEC_PLAYER && sWorld.getConfig(CONFIG_BOOL_GM_LOG_TRADE))
                            {
                                std::string sender_name;
                                if (sender)
                                {
                                    sender_accId = sender->GetSession()->GetAccountId();
                                    sender_name = sender->GetName();
                                }
                                else if (sender_guid)
                                {
                                    // can be calculated early
                                    sender_accId = sObjectMgr.GetPlayerAccountIdByGUID(sender_guid);

                                    if (!sObjectMgr.GetPlayerNameByGUID(sender_guid, sender_name))
                                        sender_name = sObjectMgr.GetMangosStringForDBCLocale(LANG_UNKNOWN);
                                }
                                sLog.outCommand(GetMaster()->GetSession()->GetAccountId(), "GM %s (Account: %u) receive mail item: %s (Entry: %u Count: %u) and send COD money: %u to player: %s (Account: %u)",
                                                GetMaster()->GetSession()->GetPlayerName(), GetMaster()->GetSession()->GetAccountId(), item->GetProto()->Name1, item->GetEntry(), item->GetCount(), m->COD, sender_name.c_str(), sender_accId);
                            }
                            else if (!sender)
                                sender_accId = sObjectMgr.GetPlayerAccountIdByGUID(sender_guid);

                            // check player existence
                            if (sender || sender_accId)
                            {
                                MailDraft(m->subject, "")
                                .SetMoney(m->COD)
                                .SendMailTo(MailReceiver(sender, sender_guid), m_bot, MAIL_CHECK_MASK_COD_PAYMENT);
                            }

                            m_bot->ModifyMoney(-int32(m->COD));
                        }
                        m->COD = 0;
                        m->state = MAIL_STATE_CHANGED;
                        m_bot->m_mailsUpdated = true;
                        m_bot->RemoveMItem(item->GetGUIDLow());

                        uint32 count = item->GetCount(); // save counts before store and possible merge with deleting
                        m_bot->MoveItemToInventory(dest, item, true);
                        m_bot->UpdateMail();
                        m_bot->SendMailResult(*it, MAIL_ITEM_TAKEN, MAIL_OK, 0, itr->item_guid, count);
                        if (m->RemoveItem(itr->item_guid))
                        {
                            MakeItemLink(item, msg, true);
                            has_items = false;
                        }
                    }
                    else
                        m_bot->SendMailResult(*it, MAIL_ITEM_TAKEN, MAIL_ERR_EQUIP_ERROR, res);
                }

                if (!has_items)
                {
                    CharacterDatabase.BeginTransaction();
                    CharacterDatabase.PExecute("UPDATE mail SET has_items = 0 WHERE id = %u", *it);
                    CharacterDatabase.CommitTransaction();
                }
                msg << "\n";
                ch.SendSysMessage(msg.str().c_str());
            }
        }
    }
    else if (ExtractCommand("delete", text))
    {
        std::ostringstream msg;
        std::list<uint32> mailIds;
        extractMailIds(text, mailIds);
        mailIds.unique();
        mailIds.sort();

        if (mailIds.empty())
        {
            ch.SendSysMessage("Syntax: mail <delete [mailId]..>");
            return;
        }

        msg << "|cff009900Mail ";
        for (std::list<uint32>::iterator it = mailIds.begin(); it != mailIds.end(); ++it)
        {
            m_bot->m_mailsUpdated = true;

            Mail* m = m_bot->GetMail(*it);

            if (m)
            {
                // delete shouldn't show up for COD mails
                if (m->COD)
                {
                    m_bot->SendMailResult(*it, MAIL_DELETED, MAIL_ERR_INTERNAL_ERROR);
                    return;
                }
                m->state = MAIL_STATE_DELETED;

                m_bot->SendMailResult(*it, MAIL_DELETED, MAIL_OK);
                CharacterDatabase.BeginTransaction();
                CharacterDatabase.PExecute("DELETE FROM mail WHERE id = '%u'", *it);
                CharacterDatabase.PExecute("DELETE FROM mail_items WHERE mail_id = '%u'", *it);
                CharacterDatabase.PExecute("DELETE FROM item_text WHERE id = '%u'", m->itemTextId);
                CharacterDatabase.CommitTransaction();
                m_bot->RemoveMail(*it);
                msg << "|cffffcccc|h[" << *it << "]|h|r";
            }
        }
        msg << "|cff009900 has been deleted..";
        ch.SendSysMessage(msg.str().c_str());
    }
}

// _HandleCommandBank: Handle bank:
// bank                                        -- Lists bot(s) bank balance.
// bank deposit [Item Link][Item Link] ..      -- Deposit item(s) in bank.
// bank withdraw [Item Link][Item Link] ..     -- Withdraw item(s) from bank. ([Item Link] from bank)
void PlayerbotAI::_HandleCommandBank(std::string& text, Player& fromPlayer)
{
    FollowAutoReset();
    if (text == "")
    {
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(BANK_BALANCE, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_BANKER); // list all bot balance
    }
    else if (ExtractCommand("deposit", text))
    {
        std::list<uint32> itemIds;
        extractItemIds(text, itemIds);
        for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
            m_tasks.push_back(std::pair<enum TaskFlags, uint32>(BANK_DEPOSIT, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_BANKER);
    }
    else if (ExtractCommand("withdraw", text))
    {
        std::list<uint32> itemIds;
        extractItemIds(text, itemIds);
        for (std::list<uint32>::iterator it = itemIds.begin(); it != itemIds.end(); ++it)
            m_tasks.push_back(std::pair<enum TaskFlags, uint32>(BANK_WITHDRAW, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_BANKER);
    }
    else
    {
        SendWhisper("I don't understand what you're trying to do", fromPlayer);
    }
}

// _HandleCommandTalent: Handle talents:
// talent                           -- Lists bot(s) unspent points & cost to reset
// talent learn                     -- Lists available bot talents [TALENT LINK], as long as the bot has unspent points.
// talent learn [TALENT LINK] ..    -- Learn selected talent [TALENT LINK] from 'talent learn' output (shift click icon/link)
// talent reset                     -- Resets all talents (Must visit a suitable class trainer to reset talents)
void PlayerbotAI::_HandleCommandTalent(std::string& text, Player& fromPlayer)
{
    std::ostringstream out;
    uint32 CurTalentPoints = m_bot->GetFreeTalentPoints();

    if (ExtractCommand("learn", text))
    {
        if (text.size() > 0)
        {

            std::list<talentPair>talents;
            extractTalentIds(text, talents);

            for (std::list<talentPair>::iterator itr = talents.begin(); itr != talents.end(); itr++)
            {
                uint32 talentid;
                uint32 rank;

                talentid = itr->first;
                rank = itr->second;

                m_bot->learnSpell(talentid, false);

                if (m_bot->HasSpell(talentid))
                {
                    WorldPacket data(SMSG_PLAY_SPELL_IMPACT, 12);            // visual effect on player
                    data << m_bot->GetObjectGuid();
                    data << uint32(0x016A);                                 // index from SpellVisualKit.dbc
                    GetMaster()->GetSession()->SendPacket(data);

                    InspectUpdate();
                }

                // DEBUG_LOG("TalentID: %u Rank: %u\n", talentid, rank);
            }
        }
        // Handle: List class or profession skills, spells & abilities for selected trainer
        else
        {
            if (CurTalentPoints == 0)
            {
                out << "I have no free talent points to spend!";
                SendWhisper(out.str(), fromPlayer);
                return;
            }
            else
                out << "I have " << CurTalentPoints << " free talent points to spend\r";

            out << "The talents I can learn:\r";

            // find class talent tabs (all players have 3 talent tabs)
            uint32 const* talentTabIds = GetTalentTabPages(m_bot->getClass());

            for (uint32 i = 0; i < 3; ++i)
            {
                uint32 talentTabId = talentTabIds[i];
                uint32 classMask = m_bot->getClassMask();

                for (uint32 ts = 0; ts < sTalentStore.GetNumRows(); ++ts)
                {
                    TalentEntry const* talentInfo = sTalentStore.LookupEntry(ts);
                    if (!talentInfo)
                        continue;

                    TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
                    if (!talentTabInfo)
                        continue;

                    // if talent not right for bot class, continue
                    if ((classMask & talentTabInfo->ClassMask) == 0)
                        continue;

                    // if talent not on same tab, continue
                    if (talentInfo->TalentTab != talentTabId)
                        continue;
                    // find current max talent rank
                    int curtalent_maxrank = 0;
                    for (int k = MAX_TALENT_RANK - 1; k > -1; --k)
                    {
                        if (talentInfo->RankID[k] && m_bot->HasSpell(talentInfo->RankID[k]))
                        {
                            curtalent_maxrank = k + 1;
                            break;
                        }
                    }

                    // Check if it requires another previous talent
                    if (talentInfo->DependsOn > 0)
                    {
                        if (TalentEntry const* depTalentInfo = sTalentStore.LookupEntry(talentInfo->DependsOn))
                        {
                            bool hasEnoughRank = false;
                            for (int dor = talentInfo->DependsOnRank; dor < MAX_TALENT_RANK; ++dor)
                            {
                                if (depTalentInfo->RankID[dor] != 0)
                                    if (m_bot->HasSpell(depTalentInfo->RankID[dor]))
                                        hasEnoughRank = true;
                            }

                            if (!hasEnoughRank)
                                continue;
                        }
                    }

                    // Check if it requires spell
                    if (talentInfo->DependsOnSpell && !m_bot->HasSpell(talentInfo->DependsOnSpell))
                        continue;

                    // Find out how many points we have in this field
                    uint32 spentPoints = 0;

                    uint32 tTab = talentInfo->TalentTab;
                    if (talentInfo->Row > 0)
                    {
                        unsigned int numRows = sTalentStore.GetNumRows();
                        for (unsigned int i = 0; i < numRows; ++i)          // Loop through all talents.
                        {
                            // Someday, someone needs to revamp
                            const TalentEntry* tmpTalent = sTalentStore.LookupEntry(i);
                            if (tmpTalent)                                  // the way talents are tracked
                            {
                                if (tmpTalent->TalentTab == tTab)
                                {
                                    for (int j = 0; j < MAX_TALENT_RANK; ++j)
                                    {
                                        if (tmpTalent->RankID[j] != 0)
                                        {
                                            if (m_bot->HasSpell(tmpTalent->RankID[j]))
                                                spentPoints += j + 1;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    // not have required min points spent in talent tree
                    if (spentPoints < (talentInfo->Row * MAX_TALENT_RANK))
                        continue;

                    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(talentInfo->RankID[curtalent_maxrank]);
                    if (!spellInfo || !SpellMgr::IsSpellValid(spellInfo, m_bot, false))
                        continue;

                    out << "|cff4e96f7|Htalent:" << talentInfo->RankID[curtalent_maxrank] << ":" << curtalent_maxrank << "|h[" << spellInfo->SpellName[GetMaster()->GetSession()->GetSessionDbcLocale()] << "]|h|r";
                }
            }
            SendWhisper(out.str(), fromPlayer);
        }
    }
    else if (ExtractCommand("reset", text))
    {
        FollowAutoReset();
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(RESET_TALENTS, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_TRAINER);
    }
    else
    {
        uint32 gold = uint32(m_bot->resetTalentsCost() / 10000);

        out << "I have " << CurTalentPoints << " free talent points to spend.\r";

        if (gold > 0)
            out << "Cost to reset all Talents is " << gold << " |TInterface\\Icons\\INV_Misc_Coin_01:8|t";

        SendWhisper(out.str(), fromPlayer);
    }
}

void PlayerbotAI::_HandleCommandProcess(std::string& text, Player& fromPlayer)
{
    uint32 spellId;

    if (ExtractCommand("disenchant", text, true)) // true -> "process disenchant" OR "process d"
    {
        if (m_bot->HasSkill(SKILL_ENCHANTING))
        {
            spellId = DISENCHANTING_1;
        }
        else
        {
            SendWhisper("|cffff0000I can't disenchant, I don't have the skill.", fromPlayer);
            return;
        }
    }
    else if (ExtractCommand("prospect", text, true)) // true -> "process prospect" OR "process p"
    {
        if (m_bot->HasSkill(SKILL_JEWELCRAFTING) && m_bot->GetSkillValuePure(SKILL_JEWELCRAFTING) >= 20)
        {
            spellId = PROSPECTING_1;
        }
        else
        {
            SendWhisper("|cffff0000I can't prospect, I don't have the skill.", fromPlayer);
            return;
        }
    }
    else
        return;

    std::list<uint32> itemIds;
    std::list<Item*> itemList;
    extractItemIds(text, itemIds);
    findItemsInInv(itemIds, itemList);

    if (itemList.empty())
    {
        SendWhisper("|cffff0000I can't process that!", fromPlayer);
        return;
    }

    Item* reagent = itemList.back();
    itemList.pop_back();

    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
    if (!spellInfo)
        return;

    if (reagent)
    {
        SpellCastTargets targets;
        m_itemTarget = reagent->GetProto()->ItemId;
        targets.setItemTarget(reagent);
        Spell* spell = new Spell(m_bot, spellInfo, false);
        spell->SpellStart(&targets);
    }
}

void PlayerbotAI::_HandleCommandUse(std::string& text, Player& fromPlayer)
{
    std::list<uint32> itemIds;
    std::list<Item*> itemList;
    extractItemIds(text, itemIds);
    findItemsInInv(itemIds, itemList);

    if (itemList.empty())
    {
        SendWhisper("|cffff0000I can't use that!", fromPlayer);
        return;
    }

    Item* tool = itemList.back();
    itemList.pop_back();
    if (tool)
    {
        // set target
        Unit* unit = ObjectAccessor::GetUnit(*m_bot, fromPlayer.GetSelectionGuid());
        findItemsInEquip(itemIds, itemList);
        extractGOinfo(text, m_lootTargets);
        // DEBUG_LOG("tool (%s)",tool->GetProto()->Name1);

        if (!itemList.empty())
        {
            Item* itarget = itemList.back();
            if (itarget)
            {
                // DEBUG_LOG("target (%s)",itarget->GetProto()->Name1);
                UseItem(tool, _findItemSlot(itarget)); // on equipped item
                SetState(BOTSTATE_DELAYED);
                SetIgnoreUpdateTime(1);
            }
        }
        else if (!m_lootTargets.empty())
        {
            ObjectGuid gotarget = m_lootTargets.front();
            m_lootTargets.pop_front();

            GameObject* go = m_bot->GetMap()->GetGameObject(gotarget);
            if (go)
            {
                // DEBUG_LOG("tool (%s) on target gameobject (%s)",tool->GetProto()->Name1,go->GetGOInfo()->name);
                UseItem(tool, TARGET_FLAG_OBJECT, gotarget); // on gameobject
            }
        }
        else if (unit)
        {
            // DEBUG_LOG("tool (%s) on selected target unit",tool->GetProto()->Name1);
            UseItem(tool, unit); // on unit
        }
        else
        {
            // DEBUG_LOG("tool (%s) on self",tool->GetProto()->Name1);
            UseItem(tool); // on self
            SetIgnoreUpdateTime(3);
        }
    }
    return;
}

void PlayerbotAI::_HandleCommandEquip(std::string& text, Player& fromPlayer)
{
    if (ExtractCommand("auto", text))
    {
        bool bOnce = false;
        bool bWasToggleOn = m_AutoEquipToggle;

        // run autoequip cycle once - right now - turning off after
        if (ExtractCommand("once", text))
        {
            bWasToggleOn = m_AutoEquipToggle;
            m_AutoEquipToggle = true;
            bOnce = true;
        }
        else if (ExtractCommand("on", text))
            m_AutoEquipToggle = true;
        else if (ExtractCommand("off", text))
            m_AutoEquipToggle = false;
        else // subcommand not found, assume toggle
            m_AutoEquipToggle = !m_AutoEquipToggle;

        CharacterDatabase.DirectPExecute("UPDATE playerbot_saved_data SET autoequip = '%u' WHERE guid = '%u'", m_AutoEquipToggle, m_bot->GetGUIDLow());

        if (m_AutoEquipToggle)
            AutoUpgradeEquipment();

        // feedback
        if (bOnce)
        {
            if (bWasToggleOn)
                SendWhisper("Equip Auto has run once, switching it off.", fromPlayer);
            else
                SendWhisper("Running Equip Auto once.", fromPlayer);

            m_AutoEquipToggle = false;
        }
        else if (m_AutoEquipToggle)
        {
            SendWhisper("Equip Auto has run and is |h|cff1eff00ON|h|r", fromPlayer);
        }
        else
            SendWhisper("Equip Auto is |h|cffff0000OFF|h|r", fromPlayer);
        return;
    }
    else if (ExtractCommand("info", text))
    {
        m_AutoEquipToggle ?  SendWhisper("Auto Equip is |h|cff1eff00ON|h|r", fromPlayer) : SendWhisper("Auto Equip is |h|cffff0000OFF|h|r", fromPlayer);
        return;
    }

    // handle 'equip' command, expected in the form of 'equip [ITEM(s)]'
    std::list<uint32> itemIds;
    std::list<Item*> itemList;
    extractItemIds(text, itemIds);
    findItemsInInv(itemIds, itemList);
    for (std::list<Item*>::iterator it = itemList.begin(); it != itemList.end(); ++it)
        EquipItem(*it);
    SendNotEquipList(*m_bot);
}

void PlayerbotAI::_HandleCommandFind(std::string& text, Player& /*fromPlayer*/)
{
    extractGOinfo(text, m_lootTargets);

    if (m_lootTargets.empty())
        return;

    m_lootCurrent = m_lootTargets.front();
    m_lootTargets.pop_front();

    GameObject* go = m_bot->GetMap()->GetGameObject(m_lootCurrent);
    if (!go)
    {
        m_lootTargets.clear();
        m_lootCurrent = ObjectGuid();
        return;
    }

    SetMovementOrder(MOVEMENT_STAY);
    m_bot->GetMotionMaster()->MovePoint(go->GetMapId(), go->GetPositionX(), go->GetPositionY(), go->GetPositionZ());
    m_lootTargets.clear();
    m_lootCurrent = ObjectGuid();
}

void PlayerbotAI::_HandleCommandGet(std::string& text, Player& fromPlayer)
{
    if (text != "")
    {
        extractGOinfo(text, m_lootTargets);
        SetState(BOTSTATE_LOOTING);
        return;
    }

    // get a selected lootable corpse
    ObjectGuid getOnGuid = fromPlayer.GetSelectionGuid();
    if (getOnGuid)
    {
        Creature* c = m_bot->GetMap()->GetCreature(getOnGuid);
        if (!c)
            return;

        uint32 skillId = 0;
        if (c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE))
            skillId = c->GetCreatureInfo()->GetRequiredLootSkill();

        if (c->HasFlag(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_LOOTABLE) ||
                (c->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE) && m_bot->HasSkill(skillId)))
        {
            m_lootTargets.push_back(getOnGuid);
            SetState(BOTSTATE_LOOTING);
        }
        else
            SendWhisper("Target is not lootable by me.", fromPlayer);
    }
    else
    {
        SendWhisper("No target is selected.", fromPlayer);
        m_bot->HandleEmoteCommand(EMOTE_ONESHOT_TALK);
    }
}

void PlayerbotAI::_HandleCommandCollect(std::string& text, Player& fromPlayer)
{
    while (text.size() > 0)
    {
        if (ExtractCommand("combat", text))
            SetCollectFlag(COLLECT_FLAG_COMBAT);
        else if (ExtractCommand("loot", text))
            SetCollectFlag(COLLECT_FLAG_LOOT);
        else if (ExtractCommand("quest", text))
            SetCollectFlag(COLLECT_FLAG_QUEST);
        else if (ExtractCommand("profession", text) || ExtractCommand("skill", text))
            SetCollectFlag(COLLECT_FLAG_PROFESSION);
        else if (ExtractCommand("skin", text) && m_bot->HasSkill(SKILL_SKINNING)) // removes skin even if bot does not have skill
            SetCollectFlag(COLLECT_FLAG_SKIN);
        else if (ExtractCommand("objects", text) || ExtractCommand("nearby", text))
        {
            SetCollectFlag(COLLECT_FLAG_NEAROBJECT);
            if (!HasCollectFlag(COLLECT_FLAG_NEAROBJECT))
                m_collectObjects.clear();
        }
        else if (ExtractCommand("distance:", text))
        {
            uint32 distance;
            sscanf(text.c_str(), "distance:%u", &distance);
            if (distance > 0 && distance <= m_mgr->m_confCollectDistanceMax)
            {
                m_collectDist = distance;
                std::ostringstream oss;
                oss << "I will now collect items within " << m_collectDist << " yards.";
                SendWhisper(oss.str(), fromPlayer);
            }
            else
            {
                m_collectDist = m_mgr->m_confCollectDistanceMax;
                std::stringstream oss;
                oss << "I will now collect items within " << m_mgr->m_confCollectDistanceMax << " yards. " << distance << " yards is just too far away.",
                    SendWhisper(oss.str(), fromPlayer);
            }
        }
        else if (ExtractCommand("none", text) || ExtractCommand("nothing", text))
        {
            m_collectionFlags = 0;
            m_collectObjects.clear();
            break;  // because none is an exclusive choice
        }
        else
        {
            std::ostringstream oss;
            oss << "Collect <collectable(s)>: none | distance:<1-" << m_mgr->m_confCollectDistanceMax << ">, combat, loot, quest, profession, objects";
            if (m_bot->HasSkill(SKILL_SKINNING))
                oss << ", skin";
            // TODO: perhaps change the command syntax, this way may be lacking in ease of use
            SendWhisper(oss.str(), fromPlayer);
            break;
        }
    }

    std::string collset = "";
    if (HasCollectFlag(COLLECT_FLAG_LOOT))
        collset += ", all loot";
    if (HasCollectFlag(COLLECT_FLAG_PROFESSION))
        collset += ", profession";
    if (HasCollectFlag(COLLECT_FLAG_QUEST))
        collset += ", quest";
    if (HasCollectFlag(COLLECT_FLAG_SKIN))
        collset += ", skin";
    if (collset.length() > 1)
    {
        if (HasCollectFlag(COLLECT_FLAG_COMBAT))
            collset += " items after combat";
        else
            collset += " items";
    }

    if (HasCollectFlag(COLLECT_FLAG_NEAROBJECT))
    {
        if (collset.length() > 1)
            collset += " and ";
        else
            collset += " ";    // padding for substr
        collset += "nearby objects (";
        if (!m_collectObjects.empty())
        {
            std::string strobjects = "";
            for (BotEntryList::iterator itr = m_collectObjects.begin(); itr != m_collectObjects.end(); ++itr)
            {
                uint32 objectentry = *(itr);
                GameObjectInfo const* gInfo = ObjectMgr::GetGameObjectInfo(objectentry);
                strobjects += ", ";
                strobjects += gInfo->name;
            }
            collset += strobjects.substr(2);
        }
        else
            collset += "use survey and get to set";
        collset += ")";
    }

    if (collset.length() > 1)
        SendWhisper("I'm collecting " + collset.substr(2), fromPlayer);
    else
        SendWhisper("I'm collecting nothing.", fromPlayer);
}

void PlayerbotAI::_HandleCommandEnchant(std::string& text, Player& fromPlayer)
{
    // DEBUG_LOG("Enchant (%s)",text.c_str());

    if (!m_bot->HasSkill(SKILL_ENCHANTING))
    {
        SendWhisper("|cffff0000I can't enchant, I don't have the skill.", fromPlayer);
        return;
    }

    if (text.size() > 0)
    {
        uint32 spellId;
        extractSpellId(text, spellId);

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!spellInfo)
            return;

        std::list<uint32> itemIds;
        std::list<Item*> itemList;
        extractItemIds(text, itemIds);
        findItemsInEquip(itemIds, itemList);
        findItemsInInv(itemIds, itemList);

        if (itemList.empty())
        {
            SendWhisper("|cffff0000I can't enchant that!", fromPlayer);
            return;
        }

        Item* iTarget = itemList.back();
        itemList.pop_back();

        if (iTarget)
        {
            SpellCastTargets targets;
            targets.setItemTarget(iTarget);
            Spell* spell = new Spell(m_bot, spellInfo, false);
            spell->SpellStart(&targets);
            SetState(BOTSTATE_DELAYED);
            SetIgnoreUpdateTime(1);
        }
        return;
    }
    else
    {
        std::ostringstream msg;
        uint32 charges;
        uint32 linkcount = 0;

        m_spellsToLearn.clear();
        m_bot->skill(m_spellsToLearn);
        SendWhisper("I can enchant:\n", fromPlayer);
        ChatHandler ch(&fromPlayer);
        for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); ++it)
        {
            SkillLineEntry const* SkillLine = sSkillLineStore.LookupEntry(*it);

            if (SkillLine->categoryId == SKILL_CATEGORY_PROFESSION && *it == SKILL_ENCHANTING)
            {
                for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
                {
                    SkillLineAbilityEntry const* SkillAbility = sSkillLineAbilityStore.LookupEntry(j);
                    if (!SkillAbility)
                        continue;

                    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(SkillAbility->spellId);
                    if (!spellInfo)
                        continue;

                    if (IsPrimaryProfessionSkill(*it) && spellInfo->Effect[EFFECT_INDEX_0] != SPELL_EFFECT_ENCHANT_ITEM)
                        continue;

                    if (SkillAbility->skillId == *it && m_bot->HasSpell(SkillAbility->spellId) && SkillAbility->forward_spellid == 0 && ((SkillAbility->classmask & m_bot->getClassMask()) == 0))
                    {
                        MakeSpellLink(spellInfo, msg);
                        ++linkcount;
                        if ((charges = GetSpellCharges(SkillAbility->spellId)) > 0)
                            msg << "[" << charges << "]";
                        if (linkcount >= 10)
                        {
                            ch.SendSysMessage(msg.str().c_str());
                            linkcount = 0;
                            msg.str("");
                        }
                    }
                }
            }
        }
        m_noToolList.unique();
        for (std::list<uint32>::iterator it = m_noToolList.begin(); it != m_noToolList.end(); it++)
            HasTool(*it);
        ch.SendSysMessage(msg.str().c_str());
        m_noToolList.clear();
        m_spellsToLearn.clear();
    }
}

void PlayerbotAI::_HandleCommandCraft(std::string& text, Player& fromPlayer)
{
    DEBUG_LOG("Craft (%s)", text.c_str());

    std::ostringstream msg;
    uint32 charges;
    uint32 skill;
    int32 category;
    uint32 linkcount = 0;
    m_CraftSpellId = 0;

    if (ExtractCommand("alchemy", text, true)) // true -> "craft alchemy" OR "craft a"
    {
        if (m_bot->HasSkill(SKILL_ALCHEMY))
        {
            skill = SKILL_ALCHEMY;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("blacksmithing", text, true)) // true -> "craft blacksmithing" OR "craft b"
    {
        if (m_bot->HasSkill(SKILL_BLACKSMITHING))
        {
            skill = SKILL_BLACKSMITHING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("cooking", text, true)) // true -> "craft cooking" OR "craft c"
    {
        if (m_bot->HasSkill(SKILL_COOKING))
        {
            skill = SKILL_COOKING;
            category = SKILL_CATEGORY_SECONDARY;
        }
        else
            return;
    }
    else if (ExtractCommand("engineering", text, true)) // true -> "craft engineering" OR "craft e"
    {
        if (m_bot->HasSkill(SKILL_ENGINEERING))
        {
            skill = SKILL_ENGINEERING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("firstaid", text, true)) // true -> "craft firstaid" OR "craft f"
    {
        if (m_bot->HasSkill(SKILL_FIRST_AID))
        {
            skill = SKILL_FIRST_AID;
            category = SKILL_CATEGORY_SECONDARY;
        }
        else
            return;
    }
    else if (ExtractCommand("jewelcrafting", text, true)) // true -> "craft jewelcrafting" OR "craft j"
    {
        if (m_bot->HasSkill(SKILL_JEWELCRAFTING))
        {
            skill = SKILL_JEWELCRAFTING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("leatherworking", text, true)) // true -> "craft leatherworking" OR "craft l"
    {
        if (m_bot->HasSkill(SKILL_LEATHERWORKING))
        {
            skill = SKILL_LEATHERWORKING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("magic", text, true)) // true -> "craft magic" OR "craft m"
    {
        if (m_bot->HasSkill(SKILL_ENCHANTING))
        {
            skill = SKILL_ENCHANTING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("smelting", text, true)) // true -> "craft smelting" OR "craft s"
    {
        if (m_bot->HasSkill(SKILL_MINING))
        {
            skill = SKILL_MINING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else if (ExtractCommand("tailoring", text, true)) // true -> "craft tailoring" OR "craft t"
    {
        if (m_bot->HasSkill(SKILL_TAILORING))
        {
            skill = SKILL_TAILORING;
            category = SKILL_CATEGORY_PROFESSION;
        }
        else
            return;
    }
    else
    {
        uint32 spellId;
        extractSpellId(text, spellId);

        if (!m_bot->HasSpell(spellId))
        {
            SendWhisper("|cffff0000I don't have that spell.", fromPlayer);
            return;
        }

        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!spellInfo)
            return;

        SpellCastTargets targets;
        Spell* spell = new Spell(m_bot, spellInfo, false);

        if (text.find("all", 0) != std::string::npos)
        {
            SpellCastResult result = spell->CheckCast(true);

            if (result != SPELL_CAST_OK)
            {
                spell->SendCastResult(result);
            }
            else
            {
                spell->SpellStart(&targets);
                m_CraftSpellId = spellId;
                SetState(BOTSTATE_DELAYED);
                SetIgnoreUpdateTime(6);
            }
        }
        else
            spell->SpellStart(&targets);
        return;
    }

    m_spellsToLearn.clear();
    m_bot->skill(m_spellsToLearn);
    SendWhisper("I can create:\n", fromPlayer);
    ChatHandler ch(&fromPlayer);
    for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); ++it)
    {
        SkillLineEntry const* SkillLine = sSkillLineStore.LookupEntry(*it);

        if (SkillLine->categoryId == category && *it == skill)
        {
            for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
            {
                SkillLineAbilityEntry const* SkillAbility = sSkillLineAbilityStore.LookupEntry(j);
                if (!SkillAbility)
                    continue;

                SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(SkillAbility->spellId);
                if (!spellInfo)
                    continue;

                if (IsPrimaryProfessionSkill(*it) && spellInfo->Effect[EFFECT_INDEX_0] != SPELL_EFFECT_CREATE_ITEM)
                    continue;

                if (SkillAbility->skillId == *it && m_bot->HasSpell(SkillAbility->spellId) && SkillAbility->forward_spellid == 0 && ((SkillAbility->classmask & m_bot->getClassMask()) == 0))
                {
                    MakeSpellLink(spellInfo, msg);
                    ++linkcount;
                    if ((charges = GetSpellCharges(SkillAbility->spellId)) > 0)
                        msg << "[" << charges << "]";
                    if (linkcount >= 10)
                    {
                        ch.SendSysMessage(msg.str().c_str());
                        linkcount = 0;
                        msg.str("");
                    }
                }
            }
        }
    }
    m_noToolList.unique();
    for (std::list<uint32>::iterator it = m_noToolList.begin(); it != m_noToolList.end(); it++)
        HasTool(*it);
    ch.SendSysMessage(msg.str().c_str());
    m_noToolList.clear();
    m_spellsToLearn.clear();
}

void PlayerbotAI::_HandleCommandQuest(std::string& text, Player& fromPlayer)
{
    std::ostringstream msg;

    if (ExtractCommand("add", text, true)) // true -> "quest add" OR "quest a"
    {
        FollowAutoReset();
        std::list<uint32> questIds;
        extractQuestIds(text, questIds);
        for (std::list<uint32>::iterator it = questIds.begin(); it != questIds.end(); it++)
            m_tasks.push_back(std::pair<enum TaskFlags, uint32>(TAKE_QUEST, *it));
        m_findNPC.push_back(UNIT_NPC_FLAG_QUESTGIVER);
    }
    else if (ExtractCommand("drop", text, true)) // true -> "quest drop" OR "quest d"
    {
        fromPlayer.SetSelectionGuid(m_bot->GetObjectGuid());
        PlayerbotChatHandler ch(GetMaster());
        int8 linkStart = text.find("|");
        if (text.find("|") != std::string::npos)
        {
            if (!ch.dropQuest((char*) text.substr(linkStart).c_str()))
            {
                ch.sysmessage("ERROR: could not drop quest");
            }
            else
            {
                SetQuestNeedItems();
                SetQuestNeedCreatures();
            }
        }
    }
    else if (ExtractCommand("fetch", text, true)) // true -> "quest fetch"
    {
        FollowAutoReset();
        gQuestFetch = 1;
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(LIST_QUEST, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_QUESTGIVER);
    }
    else if (ExtractCommand("list", text, true)) // true -> "quest list" OR "quest l"
    {
        FollowAutoReset();
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(LIST_QUEST, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_QUESTGIVER);
    }
    else if (ExtractCommand("report", text))
    {
        SendQuestNeedList();
    }
    else if (ExtractCommand("end", text, true)) // true -> "quest end" OR "quest e"
    {
        FollowAutoReset();
        m_tasks.push_back(std::pair<enum TaskFlags, uint32>(END_QUEST, 0));
        m_findNPC.push_back(UNIT_NPC_FLAG_QUESTGIVER);
    }
    else
    {
        bool hasIncompleteQuests = false;
        std::ostringstream incomout;
        incomout << "my incomplete quests are:";
        bool hasCompleteQuests = false;
        std::ostringstream comout;
        comout << "my complete quests are:";
        for (int slot = 0; slot < MAX_QUEST_LOG_SIZE; ++slot)
        {
            if (uint32 questId = m_bot->GetQuestSlotQuestId(slot))
            {
                Quest const* pQuest = sObjectMgr.GetQuestTemplate(questId);

                std::string questTitle  = pQuest->GetTitle();
                m_bot->GetPlayerbotAI()->QuestLocalization(questTitle, questId);

                if (m_bot->GetQuestStatus(questId) == QUEST_STATUS_COMPLETE)
                {
                    hasCompleteQuests = true;
                    comout << " |cFFFFFF00|Hquest:" << questId << ':' << pQuest->GetQuestLevel() << "|h[" << questTitle << "]|h|r";
                }
                else
                {
                    Item* qitem = FindItem(pQuest->GetSrcItemId());
                    if (qitem)
                        incomout << " use " << "|cffffffff|Hitem:" << qitem->GetProto()->ItemId << ":0:0:0:0:0:0:0" << "|h[" << qitem->GetProto()->Name1 << "]|h|r" << " on ";
                    hasIncompleteQuests = true;
                    incomout << " |cFFFFFF00|Hquest:" << questId << ':' << pQuest->GetQuestLevel() << "|h[" <<  questTitle << "]|h|r";
                }
            }
        }
        if (hasCompleteQuests)
            SendWhisper(comout.str(), fromPlayer);
        if (hasIncompleteQuests)
            SendWhisper(incomout.str(), fromPlayer);
        if (!hasCompleteQuests && !hasIncompleteQuests)
            SendWhisper("I have no quests.", fromPlayer);
    }
}

void PlayerbotAI::_HandleCommandPet(std::string& text, Player& fromPlayer)
{
    if (ExtractCommand("tame", text))
    {
        if (m_bot->GetPetGuid())
        {
            SendWhisper("I already have a pet!", fromPlayer);
            return;
        }

        ObjectGuid castOnGuid = fromPlayer.GetSelectionGuid();
        if (castOnGuid && m_bot->HasSpell(TAME_BEAST_1))
        {
            if (ASPECT_OF_THE_MONKEY > 0 && !m_bot->HasAura(ASPECT_OF_THE_MONKEY, EFFECT_INDEX_0))
                CastSpell(ASPECT_OF_THE_MONKEY, *m_bot);
            m_targetGuidCommand = castOnGuid;
            SetState(BOTSTATE_TAME);
        }
        else
            SendWhisper("I can't tame that!", fromPlayer);
        return;
    }

    Pet* pet = m_bot->GetPet();
    if (!pet)
    {
        SendWhisper("I have no pet.", fromPlayer);
        return;
    }

    if (ExtractCommand("abandon", text))
    {
        // abandon pet
        std::unique_ptr<WorldPacket> packet(new WorldPacket(CMSG_PET_ABANDON, 8));
        *packet << pet->GetObjectGuid();
        m_bot->GetSession()->QueuePacket(std::move(packet));

    }
    else if (ExtractCommand("react", text))
    {
        if (ExtractCommand("aggressive", text, true))
            pet->AI()->SetReactState(REACT_AGGRESSIVE);
        else if (ExtractCommand("defensive", text, true))
            pet->AI()->SetReactState(REACT_DEFENSIVE);
        else if (ExtractCommand("passive", text, true))
            pet->AI()->SetReactState(REACT_PASSIVE);
        else
            _HandleCommandHelp("pet react", fromPlayer);
    }
    else if (ExtractCommand("state", text))
    {
        if (text != "")
        {
            SendWhisper("'pet state' does not support subcommands.", fromPlayer);
            return;
        }

        std::string state;
        switch (pet->GetCharmInfo()->GetAI()->GetReactState())
        {
            case REACT_AGGRESSIVE:
                SendWhisper("My pet is aggressive.", fromPlayer);
                break;
            case REACT_DEFENSIVE:
                SendWhisper("My pet is defensive.", fromPlayer);
                break;
            case REACT_PASSIVE:
                SendWhisper("My pet is passive.", fromPlayer);
        }
    }
    else if (ExtractCommand("cast", text))
    {
        if (text == "")
        {
            _HandleCommandHelp("pet cast", fromPlayer);
            return;
        }

        uint32 spellId = (uint32) atol(text.c_str());

        if (spellId == 0)
        {
            spellId = getPetSpellId(text.c_str());
            if (spellId == 0)
                extractSpellId(text, spellId);
        }

        if (spellId != 0 && pet->HasSpell(spellId))
        {
            if (pet->HasAura(spellId))
            {
                pet->RemoveAurasByCasterSpell(spellId, pet->GetObjectGuid());
                return;
            }

            ObjectGuid castOnGuid = fromPlayer.GetSelectionGuid();
            Unit* pTarget = ObjectAccessor::GetUnit(*m_bot, castOnGuid);
            CastPetSpell(spellId, pTarget);
        }
    }
    else if (ExtractCommand("toggle", text))
    {
        if (text == "")
        {
            _HandleCommandHelp("pet toggle", fromPlayer);
            return;
        }

        uint32 spellId = (uint32) atol(text.c_str());

        if (spellId == 0)
        {
            spellId = getPetSpellId(text.c_str());
            if (spellId == 0)
                extractSpellId(text, spellId);
        }

        if (spellId != 0 && pet->HasSpell(spellId))
        {
            PetSpellMap::iterator itr = pet->m_spells.find(spellId);
            if (itr != pet->m_spells.end())
            {
                if (itr->second.active == ACT_ENABLED)
                {
                    pet->ToggleAutocast(spellId, false);
                    if (pet->HasAura(spellId))
                        pet->RemoveAurasByCasterSpell(spellId, pet->GetObjectGuid());
                }
                else
                    pet->ToggleAutocast(spellId, true);
            }
        }
    }
    else if (ExtractCommand("spells", text))
    {
        if (text != "")
        {
            SendWhisper("'pet spells' does not support subcommands.", fromPlayer);
            return;
        }

        int loc = GetMaster()->GetSession()->GetSessionDbcLocale();

        std::ostringstream posOut;
        std::ostringstream negOut;

        for (PetSpellMap::iterator itr = pet->m_spells.begin(); itr != pet->m_spells.end(); ++itr)
        {
            const uint32 spellId = itr->first;

            if (itr->second.state == PETSPELL_REMOVED || IsPassiveSpell(spellId))
                continue;

            const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
            if (!pSpellInfo)
                continue;

            std::string color;
            switch (itr->second.active)
            {
                case ACT_ENABLED:
                    color = "cff35d22d"; // Some flavor of green
                    break;
                default:
                    color = "cffffffff";
            }

            if (IsPositiveSpell(spellId))
                posOut << " |" << color << "|Hspell:" << spellId << "|h["
                       << pSpellInfo->SpellName[loc] << "]|h|r";
            else
                negOut << " |" << color << "|Hspell:" << spellId << "|h["
                       << pSpellInfo->SpellName[loc] << "]|h|r";
        }

        ChatHandler ch(&fromPlayer);
        SendWhisper("Here's my pet's non-attack spells:", fromPlayer);
        ch.SendSysMessage(posOut.str().c_str());
        SendWhisper("and here's my pet's attack spells:", fromPlayer);
        ch.SendSysMessage(negOut.str().c_str());
    }
}

void PlayerbotAI::_HandleCommandSpells(std::string& /*text*/, Player& fromPlayer)
{
    int loc = GetMaster()->GetSession()->GetSessionDbcLocale();

    std::ostringstream posOut;
    std::ostringstream negOut;

    typedef std::map<std::string, uint32> spellMap;

    spellMap posSpells, negSpells;
    std::string spellName;

    uint32 ignoredSpells[] = {1843, 5019, 2479, 6603, 3365, 8386, 21651, 21652, 6233, 6246, 6247,
                              61437, 22810, 22027, 45927, 7266, 7267, 6477, 6478, 7355, 68398
                             };
    uint32 ignoredSpellsCount = sizeof(ignoredSpells) / sizeof(uint32);

    for (PlayerSpellMap::iterator itr = m_bot->GetSpellMap().begin(); itr != m_bot->GetSpellMap().end(); ++itr)
    {
        const uint32 spellId = itr->first;

        if (itr->second.state == PLAYERSPELL_REMOVED || itr->second.disabled || IsPassiveSpell(spellId))
            continue;

        const SpellEntry* const pSpellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spellId);
        if (!pSpellInfo)
            continue;

        spellName = pSpellInfo->SpellName[loc];

        SkillLineAbilityMapBounds const bounds = sSpellMgr.GetSkillLineAbilityMapBoundsBySpellId(spellId);

        bool isProfessionOrRidingSpell = false;
        for (SkillLineAbilityMap::const_iterator skillIter = bounds.first; skillIter != bounds.second; ++skillIter)
        {
            if (IsProfessionOrRidingSkill(skillIter->second->skillId) && skillIter->first == spellId)
            {
                isProfessionOrRidingSpell = true;
                break;
            }
        }
        if (isProfessionOrRidingSpell)
            continue;

        bool isIgnoredSpell = false;
        for (uint8 i = 0; i < ignoredSpellsCount; ++i)
        {
            if (spellId == ignoredSpells[i])
            {
                isIgnoredSpell = true;
                break;
            }
        }
        if (isIgnoredSpell)
            continue;

        if (IsPositiveSpell(spellId))
        {
            if (posSpells.find(spellName) == posSpells.end())
                posSpells[spellName] = spellId;
            else if (posSpells[spellName] < spellId)
                posSpells[spellName] = spellId;
        }
        else
        {
            if (negSpells.find(spellName) == negSpells.end())
                negSpells[spellName] = spellId;
            else if (negSpells[spellName] < spellId)
                negSpells[spellName] = spellId;
        }
    }

    for (spellMap::const_iterator iter = posSpells.begin(); iter != posSpells.end(); ++iter)
    {
        posOut << " |cffffffff|Hspell:" << iter->second << "|h[" << iter->first << "]|h|r";
    }

    for (spellMap::const_iterator iter = negSpells.begin(); iter != negSpells.end(); ++iter)
    {
        negOut << " |cffffffff|Hspell:" << iter->second << "|h[" << iter->first << "]|h|r";
    }

    ChatHandler ch(&fromPlayer);
    SendWhisper("here's my non-attack spells:", fromPlayer);
    ch.SendSysMessage(posOut.str().c_str());
    SendWhisper("and here's my attack spells:", fromPlayer);
    ch.SendSysMessage(negOut.str().c_str());
}

void PlayerbotAI::_HandleCommandSurvey(std::string& /*text*/, Player& fromPlayer)
{
    uint32 count = 0;
    std::ostringstream detectout;
    QueryResult* result;
    GameEventMgr::ActiveEvents const& activeEventsList = sGameEventMgr.GetActiveEventList();
    std::ostringstream eventFilter;
    eventFilter << " AND (event IS NULL ";
    bool initString = true;

    for (GameEventMgr::ActiveEvents::const_iterator itr = activeEventsList.begin(); itr != activeEventsList.end(); ++itr)
    {
        if (initString)
        {
            eventFilter <<  "OR event IN (" << *itr;
            initString = false;
        }
        else
            eventFilter << "," << *itr;
    }

    if (!initString)
        eventFilter << "))";
    else
        eventFilter << ")";

    result = WorldDatabase.PQuery("SELECT gameobject.guid, id, position_x, position_y, position_z, map, "
                                  "(POW(position_x - %f, 2) + POW(position_y - %f, 2) + POW(position_z - %f, 2)) AS order_ FROM gameobject "
                                  "LEFT OUTER JOIN game_event_gameobject on gameobject.guid=game_event_gameobject.guid WHERE map = '%i' %s ORDER BY order_ ASC LIMIT 10",
                                  m_bot->GetPositionX(), m_bot->GetPositionY(), m_bot->GetPositionZ(), m_bot->GetMapId(), eventFilter.str().c_str());

    if (result)
    {
        do
        {
            Field* fields = result->Fetch();
            uint32 guid = fields[0].GetUInt32();
            uint32 entry = fields[1].GetUInt32();

            GameObject* go = m_bot->GetMap()->GetGameObject(ObjectGuid(HIGHGUID_GAMEOBJECT, entry, guid));
            if (!go)
                continue;

            if (!go->IsSpawned())
                continue;

            detectout << "|cFFFFFF00|Hfound:" << guid << ":" << entry  << ":" <<  "|h[" << go->GetGOInfo()->name << "]|h|r";
            ++count;
        }
        while (result->NextRow());

        delete result;
    }
    SendWhisper(detectout.str().c_str(), fromPlayer);
}

// _HandleCommandSkill: Handle class & professions training:
// skill                           -- Lists bot(s) Primary profession skills & weapon skills
// skill learn                     -- List available class or profession (Primary or Secondary) skills, spells & abilities from selected trainer.
// skill learn all                 -- Learn all skills and spells available from selected trainer.
// skill learn [HLINK][HLINK] ..   -- Learn selected skill and spells, from selected trainer ([HLINK] from skill learn).
// skill unlearn [HLINK][HLINK] .. -- Unlearn selected primary profession skill(s) and all associated spells ([HLINK] from skill)
void PlayerbotAI::_HandleCommandSkill(std::string& text, Player& fromPlayer)
{
    uint32 rank[8] = {0, 75, 150, 225, 300, 375, 450, 525};

    std::ostringstream msg;
    if (ExtractCommand("learn", text))
    {
        uint32 totalCost = 0;

        Unit* unit = ObjectAccessor::GetUnit(*m_bot, fromPlayer.GetSelectionGuid());
        if (!unit)
        {
            SendWhisper("Please select the trainer!", fromPlayer);
            return;
        }

        if (!unit->isTrainer())
        {
            SendWhisper("This is not a trainer!", fromPlayer);
            return;
        }

        Creature* creature =  m_bot->GetMap()->GetCreature(fromPlayer.GetSelectionGuid());
        if (!creature)
            return;

        if (!creature->IsTrainerOf(m_bot, false))
        {
            SendWhisper("This trainer can not teach me anything!", fromPlayer);
            return;
        }

        // check present spell in trainer spell list
        TrainerSpellData const* cSpells = creature->GetTrainerSpells();
        TrainerSpellData const* tSpells = creature->GetTrainerTemplateSpells();
        TrainerSpellMap allSpells;

        if (cSpells && tSpells)
        {
            allSpells.insert(cSpells->spellList.begin(), cSpells->spellList.end());
            allSpells.insert(tSpells->spellList.begin(), tSpells->spellList.end());
        }
        else if (cSpells)
            allSpells.insert(cSpells->spellList.begin(), cSpells->spellList.end());
        else if (tSpells)
            allSpells.insert(tSpells->spellList.begin(), tSpells->spellList.end());
        else
        {
            SendWhisper("No spells can be learnt from this trainer", fromPlayer);
            return;
        }

        // reputation discount
        float fDiscountMod =  m_bot->GetReputationPriceDiscount(creature);

        // Handle: Learning class or profession (primary or secondary) skill & spell(s) for selected trainer, skill learn [HLINK][HLINK][HLINK].. ([HLINK] from skill train)
        if (text.size() > 0)
        {
            msg << "I have learned the following spells:\n";
            uint32 totalSpellLearnt = 0;
            bool visuals = true;
            m_spellsToLearn.clear();
            if (ExtractCommand("all", text))
            {
                for (TrainerSpellMap::const_iterator itr =  allSpells.begin(); itr !=  allSpells.end(); ++itr)
                {
                    TrainerSpell const* trainer_spell = &itr->second;

                    uint32 spellId = trainer_spell->spell;

                    if (!spellId)
                        break;

                    // apply reputation discount
                    uint32 cost = uint32(floor(trainer_spell->spellCost * fDiscountMod));
                    if (!_HandleCommandSkillLearnHelper(trainer_spell, spellId, cost))
                        continue;

                    ++totalSpellLearnt;
                    totalCost += cost;
                    const SpellEntry* const pSpellInfo =  sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                    if (!pSpellInfo)
                        continue;

                    if (visuals)
                    {
                        visuals = false;
                        WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);           // visual effect on trainer
                        data << ObjectGuid(fromPlayer.GetSelectionGuid());
                        data << uint32(0xB3);                                   // index from SpellVisualKit.dbc
                        GetMaster()->GetSession()->SendPacket(data);

                        data.Initialize(SMSG_PLAY_SPELL_IMPACT, 12);            // visual effect on player
                        data << m_bot->GetObjectGuid();
                        data << uint32(0x016A);                                 // index from SpellVisualKit.dbc
                        GetMaster()->GetSession()->SendPacket(data);
                    }

                    WorldPacket data(SMSG_TRAINER_BUY_SUCCEEDED, 12);
                    data << ObjectGuid(fromPlayer.GetSelectionGuid());
                    data << uint32(spellId);                                // should be same as in packet from client
                    GetMaster()->GetSession()->SendPacket(data);
                    MakeSpellLink(pSpellInfo, msg);
                    msg << " ";
                    msg << Cash(cost) << " ";
                }
            }
            else
            {
                extractSpellIdList(text, m_spellsToLearn);

                for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); it++)
                {
                    uint32 spellId = *it;

                    if (!spellId)
                        break;

                    // Try find spell in npc_trainer
                    TrainerSpell const* trainer_spell = cSpells ? cSpells->Find(spellId) : nullptr;

                    // Not found, try find in npc_trainer_template
                    if (!trainer_spell && tSpells)
                        trainer_spell = tSpells->Find(spellId);

                    // apply reputation discount
                    uint32 cost = uint32(floor(trainer_spell->spellCost * fDiscountMod));

                    if (!_HandleCommandSkillLearnHelper(trainer_spell, spellId, cost))
                        continue;

                    ++totalSpellLearnt;
                    totalCost += cost;
                    const SpellEntry* const pSpellInfo =  sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                    if (!pSpellInfo)
                        continue;

                    if (visuals)
                    {
                        visuals = false;
                        WorldPacket data(SMSG_PLAY_SPELL_VISUAL, 12);           // visual effect on trainer
                        data << ObjectGuid(fromPlayer.GetSelectionGuid());
                        data << uint32(0xB3);                                   // index from SpellVisualKit.dbc
                        GetMaster()->GetSession()->SendPacket(data);

                        data.Initialize(SMSG_PLAY_SPELL_IMPACT, 12);            // visual effect on player
                        data << m_bot->GetObjectGuid();
                        data << uint32(0x016A);                                 // index from SpellVisualKit.dbc
                        GetMaster()->GetSession()->SendPacket(data);
                    }

                    WorldPacket data(SMSG_TRAINER_BUY_SUCCEEDED, 12);
                    data << ObjectGuid(fromPlayer.GetSelectionGuid());
                    data << uint32(spellId);                                // should be same as in packet from client
                    GetMaster()->GetSession()->SendPacket(data);
                    MakeSpellLink(pSpellInfo, msg);
                    msg << " ";
                    msg << Cash(cost) << " ";
                }
            }
            ReloadAI();
            if (totalSpellLearnt == 0) msg.clear();
            else msg << "\n";
            msg << "Total of " << totalSpellLearnt << " spell";
            if (totalSpellLearnt != 1) msg << "s";
            msg << " learnt, ";
            msg << Cash(totalCost) << " spent.";
        }
        // Handle: List class or profession skills, spells & abilities for selected trainer
        else
        {
            msg << "The spells I can learn and their cost:\r";

            for (TrainerSpellMap::const_iterator itr =  allSpells.begin(); itr !=  allSpells.end(); ++itr)
            {
                TrainerSpell const* tSpell = &itr->second;

                if (!tSpell)
                    break;

                uint32 reqLevel = 0;
                if (!tSpell->learnedSpell && !m_bot->IsSpellFitByClassAndRace(tSpell->learnedSpell, &reqLevel))
                    continue;

                if (sSpellMgr.IsPrimaryProfessionFirstRankSpell(tSpell->learnedSpell) && m_bot->HasSpell(tSpell->learnedSpell))
                    continue;

                reqLevel = tSpell->isProvidedReqLevel ? tSpell->reqLevel : std::max(reqLevel, tSpell->reqLevel);

                TrainerSpellState state =  m_bot->GetTrainerSpellState(tSpell, reqLevel);
                if (state != TRAINER_SPELL_GREEN)
                    continue;

                uint32 spellId = tSpell->spell;
                const SpellEntry* const pSpellInfo =  sSpellTemplate.LookupEntry<SpellEntry>(spellId);
                if (!pSpellInfo)
                    continue;
                uint32 cost = uint32(floor(tSpell->spellCost *  fDiscountMod));
                totalCost += cost;
                MakeSpellLink(pSpellInfo, msg);
                msg << " ";
                msg << Cash(cost) << " ";
            }

            if (totalCost == 0)
            {
                msg.clear();
                msg << "I have learned all I can from this trainer. Perhaps I can learn more once I grow stronger.";
            }
            else
            {
                int32 moneyDiff = m_bot->GetMoney() - totalCost;
                if (moneyDiff >= 0)
                    msg << "\n" << Cash(moneyDiff) << " left after learning all the spells.";
                else
                {
                    Announce(CANT_AFFORD);
                    moneyDiff *= -1;
                    msg << "\nI need " << Cash(moneyDiff) << " more to learn all the spells!";
                }
            }
        }
    }
    // Handle: Unlearning selected primary profession skill(s) and all associated spells, skill unlearn [HLINK][HLINK].. ([HLINK] from skill)
    else if (ExtractCommand("unlearn", text))
    {
        m_spellsToLearn.clear();
        extractSpellIdList(text, m_spellsToLearn);
        for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); ++it)
        {
            if (sSpellMgr.IsPrimaryProfessionSpell(*it))
            {
                SpellLearnSkillNode const* spellLearnSkill = sSpellMgr.GetSpellLearnSkill(*it);

                uint32 prev_spell = sSpellMgr.GetPrevSpellInChain(*it);
                if (!prev_spell)                                    // first rank, remove skill
                    GetPlayer()->SetSkill(spellLearnSkill->skill, 0, 0);
                else
                {
                    // search prev. skill setting by spell ranks chain
                    SpellLearnSkillNode const* prevSkill = sSpellMgr.GetSpellLearnSkill(prev_spell);
                    while (!prevSkill && prev_spell)
                    {
                        prev_spell = sSpellMgr.GetPrevSpellInChain(prev_spell);
                        prevSkill = sSpellMgr.GetSpellLearnSkill(sSpellMgr.GetFirstSpellInChain(prev_spell));
                    }
                    if (!prevSkill)                                 // not found prev skill setting, remove skill
                        GetPlayer()->SetSkill(spellLearnSkill->skill, 0, 0);
                }
            }
        }
    }
    // Handle: Lists bot(s) primary profession skills & weapon skills.
    else
    {
        m_spellsToLearn.clear();
        m_bot->skill(m_spellsToLearn);
        msg << "My Primary Professions: ";
        for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); ++it)
        {
            if (IsPrimaryProfessionSkill(*it))
                for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
                {
                    SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
                    if (!skillLine)
                        continue;

                    // has skill
                    if (skillLine->skillId == *it && skillLine->learnOnGetSkill == 0)
                    {
                        uint32 SpellId;
                        m_bot->HasSpell(skillLine->forward_spellid) ? SpellId = skillLine->forward_spellid : SpellId = skillLine->spellId;

                        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(SpellId);
                        if (!spellInfo)
                            continue;

                        if (m_bot->GetSkillValue(*it) <= rank[sSpellMgr.GetSpellRank(SpellId)] && m_bot->HasSpell(SpellId))
                        {
                            // DEBUG_LOG ("[PlayerbotAI]: HandleCommand - skill (%u)(%u)(%u):",skillLine->spellId, rank[sSpellMgr.GetSpellRank(skillLine->spellId)], m_bot->GetSkillValue(*it));
                            msg << "\n[" << m_bot->GetSkillValue(*it) << " / " << rank[sSpellMgr.GetSpellRank(SpellId)] << "]: ";
                            MakeSpellLink(spellInfo, msg);
                            break;
                        }
                    }
                }
        }

        msg << "\nMy Weapon skills: ";
        for (std::list<uint32>::iterator it = m_spellsToLearn.begin(); it != m_spellsToLearn.end(); ++it)
        {
            SkillLineEntry const* SkillLine = sSkillLineStore.LookupEntry(*it);
            // has weapon skill
            if (SkillLine->categoryId == SKILL_CATEGORY_WEAPON)
            {
                for (uint32 j = 0; j < sSkillLineAbilityStore.GetNumRows(); ++j)
                {
                    SkillLineAbilityEntry const* skillLine = sSkillLineAbilityStore.LookupEntry(j);
                    if (!skillLine)
                        continue;

                    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(skillLine->spellId);
                    if (!spellInfo)
                        continue;

                    if (skillLine->skillId == *it && spellInfo->Effect[0] == SPELL_EFFECT_WEAPON)
                        MakeWeaponSkillLink(spellInfo, msg, *it);
                }
            }
        }
    }
    SendWhisper(msg.str(), fromPlayer);
    m_spellsToLearn.clear();
    m_bot->GetPlayerbotAI()->GetClassAI();
}

bool PlayerbotAI::_HandleCommandSkillLearnHelper(TrainerSpell const* tSpell, uint32 spellId, uint32 cost)
{
    // Not found anywhere, cheating?
    if (!tSpell)
        return false;

    uint32 reqLevel = 0;
    if (!tSpell->learnedSpell && !m_bot->IsSpellFitByClassAndRace(tSpell->learnedSpell, &reqLevel))
        return false;

    if (sSpellMgr.IsPrimaryProfessionFirstRankSpell(tSpell->learnedSpell) && m_bot->HasSpell(tSpell->learnedSpell))
        return false;

    reqLevel = tSpell->isProvidedReqLevel ? tSpell->reqLevel : std::max(reqLevel, tSpell->reqLevel);

    TrainerSpellState state =  m_bot->GetTrainerSpellState(tSpell, reqLevel);
    if (state != TRAINER_SPELL_GREEN)
        return false;

    // check money requirement
    if (m_bot->GetMoney() < cost)
    {
        Announce(CANT_AFFORD);
        return false;
    }

    m_bot->ModifyMoney(-int32(cost));
    // learn explicitly
    m_bot->learnSpell(spellId, false);

    return true;
}

void PlayerbotAI::_HandleCommandStats(std::string& text, Player& fromPlayer)
{
    if (text != "")
    {
        SendWhisper("'stats' does not have subcommands", fromPlayer);
        return;
    }

    std::ostringstream out;

    uint32 totalfree = GetFreeBagSpace();

    // estimate how much item damage the bot has
    out << "|cffffffff[|h|cff00ffff" << m_bot->GetName() << "|h|cffffffff] has |cff00ff00";
    out << totalfree << " |h|cffffffff bag slots,|h" << " |cff00ff00";
    out << Cash(EstRepairAll());

    // calculate how much money bot has
    uint32 copper = m_bot->GetMoney();
    out << "|h|cffffffff item damage & has " << "|r|cff00ff00";
    out << Cash(copper);
    ChatHandler ch(&fromPlayer);
    ch.SendSysMessage(out.str().c_str());
}

void PlayerbotAI::_HandleCommandGM(std::string& text, Player& fromPlayer)
{
    // Check should happen OUTSIDE this function, but this is account security we're talking about, so let's be doubly sure
    if (fromPlayer.GetSession()->GetSecurity() <= SEC_PLAYER)
        return;  // no excuses, no warning

    if (text == "")
    {
        SendWhisper("gm must have a subcommand.", fromPlayer);
        return;
    }
    else if (ExtractCommand("target", text))
    {
        if (ExtractCommand("combat", text))
        {
            for (AttackerInfoList::iterator i = m_attackerInfo.begin(); i != m_attackerInfo.end(); ++i)
                DEBUG_LOG("[Attacker]:{ %s, victim:%s, threat:%.2f, highest-threat:%.2f, count:%d }",
                          i->second.attacker->GetName(),
                          i->second.victim->GetName(),
                          i->second.threat,
                          i->second.threat2,
                          i->second.count);
            DEBUG_LOG("[Attacker]:{ };");
        }
        else if (ExtractCommand("loot", text))
        {
            for (std::list<ObjectGuid>::iterator it = m_lootTargets.begin(); it != m_lootTargets.end(); ++it)
                DEBUG_LOG("[Looter]:{ %s loots [%s] }", m_bot->GetName(), (*it).GetString().c_str());
            DEBUG_LOG("[Looter]:{ }");
        }
        else
            SendWhisper("'gm target' does not have that subcommand.", fromPlayer);
    }
    else if (ExtractCommand("chat", text))
    {
        m_bDebugCommandChat = !m_bDebugCommandChat;
        if (m_bDebugCommandChat)
            SendWhisper("I will now output all commands received.", fromPlayer);
        else
            SendWhisper("I will no longer output commands received.", fromPlayer);
    }
    else
        SendWhisper("'gm' does not have that subcommand.", fromPlayer);
}

void PlayerbotAI::_HandleCommandHelp(std::string& text, Player& fromPlayer)
{
    ChatHandler ch(&fromPlayer);

    // "help help"? Seriously?
    if (ExtractCommand("help", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("help", "Lists all the things you can order me to do... But it's up to me whether to follow your orders... Or not.").c_str());
        return;
    }

    bool bMainHelp = (text == "") ? true : false;
    const std::string sInvalidSubcommand = "That's not a valid subcommand.";
    std::string msg = "";
    // All of these must contain the 'bMainHelp' clause -> help lists all major commands
    // Further indented 'ExtractCommand("subcommand")' conditionals make sure these aren't printed for basic "help"
    if (bMainHelp || ExtractCommand("attack", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("attack", "Attack the selected target. Which would, of course, require a valid target.", HL_TARGET).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("pull", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("pull", "Pull the target in a coordinated party/raid manner.", HL_TARGET).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("pull", text))
    {
        SendWhisper(_HandleCommandHelpHelper("pull", "Pull the target in a coordinated party/raid manner.", HL_TARGET), fromPlayer);

        if (!bMainHelp)
        {
            SendWhisper(_HandleCommandHelpHelper("pull test", "I'll tell you if I could pull at all. Can be used anywhere."), fromPlayer);
            SendWhisper(_HandleCommandHelpHelper("pull ready", "I'll tell you if I'm ready to pull *right now*. To be used on location with valid target."), fromPlayer);
            if (text != "") SendWhisper(sInvalidSubcommand, fromPlayer);
            return;
        }
    }
    if (bMainHelp || ExtractCommand("neutralize", text))
    {
        SendWhisper(_HandleCommandHelpHelper("neutralize|neutral", "The bot will try to put its master's target out of combat with crowd control abilities like polymorph, banish, hibernate, shackles and the like.", HL_TARGET), fromPlayer);

        if (!bMainHelp)
        {
            if (text != "") SendWhisper(sInvalidSubcommand, fromPlayer);
            return;
        }
    }
    if (bMainHelp || ExtractCommand("follow", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("follow", "I will follow you - this also revives me if dead and teleports me if I'm far away.").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("follow auto", "Toggles Automatic Follow Distance (ON/OFF).").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("follow info", "I will show my Automatic Follow Distance, toggle status (ON/OFF).").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("follow far", "I will follow at a father distance away from you.").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("follow near", "I will follow at a closer distance to you.").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("follow reset", "I will reset my follow distance to its original state.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("stay", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("stay", "I will stay put until told otherwise.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("assist", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("assist", "I will assist the character listed, attacking as they attack.", HL_NAME).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("spells", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("spells", "I will list all the spells I know.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("craft", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("craft", "I will create a single specified recipe", HL_RECIPE).c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("craft [RECIPE] all", "I will create all specified recipes").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < alchemy | a >", "List all learnt alchemy recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < blacksmithing | b >", "List all learnt blacksmith recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < cooking | c >", "List all learnt cooking recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < engineering | e >", "List all learnt engineering recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < firstaid | f >", "List all learnt firstaid recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < jewelcrafting | j >", "List all learnt jewelcrafting recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < leatherworking | l >", "List all learnt leatherworking recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < magic | m >", "List all learnt enchanting recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < smelting | s >", "List all learnt mining recipes").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("craft < tailoring | t >", "List all learnt tailoring recipes").c_str());
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("process", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("process < disenchant | d >", "Disenchants a green coloured [ITEM] or better", HL_ITEM).c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("process < prospect | p >", "Searches 5 metal ore [ITEM] for precious gems", HL_ITEM).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("enchant", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("enchant", "Lists all enchantments [SPELL] learnt by the bot").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("enchant [SPELL]", "Enchants selected tradable [ITEM] either equipped or in bag", HL_ITEM).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("cast", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("cast", "I will cast the spell or ability listed.", HL_SPELL).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("use", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("use", "I will use the linked item.", HL_ITEM).c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("use [ITEM]", "I will use the first linked item on a selected TARGET.", HL_TARGET).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("use [ITEM]", "I will use the first linked item on an equipped linked item.", HL_ITEM).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("use [ITEM]", "I will use the first linked item on a linked gameobject.", HL_GAMEOBJECT).c_str());

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("equip", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("equip auto", "I will automatically equip items I acquire if they are better than what I'm wearing. Acts as toggle (ON/OFF) if used without subcommand. Fashion sense not included.", HL_ITEM, true).c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("equip info", "I will tell you my equip auto toggle status (ON/OFF).").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("equip", "I will equip the linked item(s).", HL_ITEM, true).c_str());

        if (!bMainHelp || ExtractCommand("auto", text))
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("equip auto on", "Turns auto equip ON, also does an immediate check (like once).").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("equip auto off", "Turns auto equip OFF.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("equip auto once", "Runs auto equip once, then turns it off.").c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("on", text, true)) {}
            else if (ExtractCommand("off", text, true)) {}
            else if (ExtractCommand("once", text, true)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("reset", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("reset", "I will reset all my states, orders, loot list, talent spec, ... Hey, that's kind of like memory loss.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("stats", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("stats", "This will inform you of my wealth, free bag slots and estimated equipment repair costs.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("survey", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("survey", "Lists all available game objects near me.").c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("find", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("find", "I will find said game object, walk right up to it, and wait.", HL_GAMEOBJECT).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("get", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("get", "I will get said game object and return to your side.", HL_GAMEOBJECT).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("quest", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("quest", "Lists my current quests.").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("quest add", "Adds this quest to my quest log.", HL_QUEST).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("quest drop", "Removes this quest from my quest log.", HL_QUEST).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("quest end", "Turns in my completed quests.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("quest list", "Lists the quests offered to me by this target.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("quest report", "This will give you a full report of all the items, creatures or gameobjects I still need to finish my quests.", HL_QUEST).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("add", text, true)) {}
            else if (ExtractCommand("drop", text, true)) {}
            else if (ExtractCommand("end", text, true)) {}
            else if (ExtractCommand("list", text, true)) {}
            else if (ExtractCommand("report", text, true)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("orders", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("orders", "Shows you my orders. Free will is overrated, right?").c_str());

        if (!bMainHelp)
        {
            SendWhisper(_HandleCommandHelpHelper("orders combat <tank | heal | assist | protect | reset> [targetPlayer]", "Sets general orders I should follow. Assist and Protect require a target."), fromPlayer);
            SendWhisper(_HandleCommandHelpHelper("orders delay <0-10>", "Activates a delay before I start fighting."), fromPlayer);
            SendWhisper(_HandleCommandHelpHelper("orders resume", "Resume combat orders to what they were before logout."), fromPlayer);

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("combat", text, true))
            {
                SendWhisper(_HandleCommandHelpHelper("orders combat tank", "Order me to tank. Best used on paladins, warriors or druids."), fromPlayer);
                SendWhisper(_HandleCommandHelpHelper("orders combat heal", "Order me to heal. Best used on shamans, priests, druids or paladins."), fromPlayer);
                SendWhisper(_HandleCommandHelpHelper("orders combat assist", "Assist the linked target focusing our killing power.", HL_TARGET), fromPlayer);
                SendWhisper(_HandleCommandHelpHelper("orders combat protect", "Protect the listed target, attempting to keep aggro away from the target.", HL_TARGET), fromPlayer);
                SendWhisper(_HandleCommandHelpHelper("orders combat reset", "Resets my combat orders as though you'd never given me any at all."), fromPlayer);

                if (ExtractCommand("tank", text, true)) {}
                else if (ExtractCommand("heal", text, true)) {}
                else if (ExtractCommand("assist", text, true)) {}
                else if (ExtractCommand("protect", text, true)) {}
                else if (ExtractCommand("reset", text, true)) {}

                else if (text != "") SendWhisper(sInvalidSubcommand.c_str(), fromPlayer);
            }
            else if (ExtractCommand("delay", text, true)) {}
            else if (ExtractCommand("resume", text, true)) {}

            else if (text != "") SendWhisper(sInvalidSubcommand.c_str(), fromPlayer);
            return;
        }
    }
    if (bMainHelp || ExtractCommand("pet", text))
    {
        if (bMainHelp)
            ch.SendSysMessage(_HandleCommandHelpHelper("pet", "Helps command my pet. Must always be used with a subcommand.").c_str());
        else if (text == "") // not "help" AND "help pet"
            ch.SendSysMessage(_HandleCommandHelpHelper("pet", "This by itself is not a valid command. Just so you know. To be used with a subcommand, such as...").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("pet abandon", "Abandons active hunter pet.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet cast", "Has my pet cast this spell. May require a treat. Or at least ask nicely.", HL_SPELL).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet react", "Sets my pet's aggro mode.", HL_PETAGGRO).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet spells", "Shows you the spells my pet knows.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet state", "Shows my pet's aggro mode.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet tame", "Allows a hunter to acquire a pet.", HL_TARGET).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("pet toggle", "Toggles autocast for this spell.", HL_SPELL).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("spells", text)) {}
            else if (ExtractCommand("tame", text)) {}
            else if (ExtractCommand("abandon", text)) {}
            else if (ExtractCommand("cast", text)) {}
            else if (ExtractCommand("toggle", text)) {}
            else if (ExtractCommand("state", text)) {}
            else if (ExtractCommand("react", text))
            {
                ch.SendSysMessage(_HandleCommandHelpHelper("pet react", "has three modes.").c_str());
                ch.SendSysMessage(_HandleCommandHelpHelper("aggressive", "sets it so my precious attacks everything in sight.", HL_NONE, false, true).c_str());
                ch.SendSysMessage(_HandleCommandHelpHelper("defensive", "sets it so it automatically attacks anything that attacks me, or anything I attack.", HL_NONE, false, true).c_str());
                ch.SendSysMessage(_HandleCommandHelpHelper("passive", "makes it so my pet won't attack anything unless directly told to.", HL_NONE, false, true).c_str());

                // Catches all valid subcommands, also placeholders for potential future sub-subcommands
                if (ExtractCommand("aggressive", text, true)) {}
                else if (ExtractCommand("defensive", text, true)) {}
                else if (ExtractCommand("passive", text, true)) {}
                if (text != "")
                    ch.SendSysMessage(sInvalidSubcommand.c_str());
            }

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("collect", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("collect", "Tells you what my current collect status is. Also lists possible options.").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("collect", "Sets what I collect. Obviously the 'none' option should be used alone, but all the others can be mixed.", HL_OPTION, true).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("sell", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("sell", "Adds this to my 'for sale' list.", HL_ITEM, true).c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("sell all", "The next time you sell, I'll sell all my low level white items.").c_str());
        ch.SendSysMessage(_HandleCommandHelpHelper("sell all", "This command must be called each time before you sell, OR I won't auto sell white items.").c_str());
        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("buy", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("buy", "Adds this to my 'purchase' list.", HL_ITEM, true).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("drop", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("drop", "Drops the linked item(s). Permanently.", HL_ITEM, true).c_str());

        if (!bMainHelp)
        {
            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("auction", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("auction", "Lists all my active auctions. With pretty little links and such. Hi hi hi... I'm gonna be sooo rich!").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("auction add", "Adds the item to my 'auction off later' list. I have a lot of lists, you see...", HL_ITEM).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("auction remove", "Adds the item to my 'Don't auction after all' list. Hope it hasn't sold by then!", HL_AUCTION).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("add", text, true)) {}
            else if (ExtractCommand("remove", text, true)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("repair", text))
    {
        if (!bMainHelp && text == "")
            ch.SendSysMessage(_HandleCommandHelpHelper("repair", "This by itself is not a valid command. Just so you know. To be used with a subcommand, such as...").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("repair", "Has me find an armorer and repair the items you listed.", HL_ITEM).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("repair all", "Has me find an armorer and repair all my items, be they equipped or just taking up bagspace.").c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("all", text)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("talent", text))
    {
        msg = _HandleCommandHelpHelper("talent", "Lists unspent talent points and the cost to reset all talents.");
        msg = _HandleCommandHelpHelper("talent learn", "Lists linked talents, that can be learnt with unspent talent points");
        ch.SendSysMessage(msg.c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("talent learn", "Has me learn the linked talent.", HL_TALENT).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("talent reset", "Resets my talents. Assuming I have the appropriate amount of sparkly gold, shiny silver, and... unrusted copper.").c_str());

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
        if (!bMainHelp) return;
    }
    if (bMainHelp || ExtractCommand("bank", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("bank", "Gives you my bank balance. I thought that was private.").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("bank deposit", "Deposits the listed items in my bank.", HL_ITEM, true).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("bank withdraw", "Withdraw the listed items from my bank.", HL_ITEM, true).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("deposit", text)) {}
            else if (ExtractCommand("withdraw", text)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("skill", text))
    {
        msg = _HandleCommandHelpHelper("skill", "Lists my primary professions & weapon skills.");
        ch.SendSysMessage(msg.c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("skill learn", "Lists the things this trainer can teach me. If you've targeted a trainer, that is.", HL_TARGET).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("skill learn", "Have me learn this skill from the selected trainer.", HL_SKILL).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("skill unlearn", "Unlearn the linked (primary) profession and everything that goes with it.", HL_PROFESSION).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("learn", text))
            {
                ch.SendSysMessage(_HandleCommandHelpHelper("skill learn all", "Learn everything this trainer can teach me.", HL_TARGET).c_str());
                if (ExtractCommand("all", text)) {}
            }
            else if (ExtractCommand("unlearn", text)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (fromPlayer.GetSession()->GetSecurity() > SEC_PLAYER && (bMainHelp || ExtractCommand("gm", text)))
    {
        msg = _HandleCommandHelpHelper("gm", "Lists actions available to GM account level and up.");
        ch.SendSysMessage(msg.c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("gm target", "Lists target items that can be monitored.").c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("gm chat", "Outputs all commands the bot receives - including those it feels it can't obey.").c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("target", text))
            {
                ch.SendSysMessage(_HandleCommandHelpHelper("gm target combat", "Lists current attacking targets.").c_str());
                ch.SendSysMessage(_HandleCommandHelpHelper("gm target loot", "Lists current lootable targets.").c_str());
            }
            if (ExtractCommand("chat", text)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }
    if (bMainHelp || ExtractCommand("mail", text))
    {
        ch.SendSysMessage(_HandleCommandHelpHelper("mail inbox |cFFFFFF00|h[Mailbox]|h|r", "Lists all bot mail from selected [Mailbox]").c_str());

        if (!bMainHelp)
        {
            ch.SendSysMessage(_HandleCommandHelpHelper("mail getcash", "Gets money from all selected [Mailid]..", HL_MAIL, true).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("mail getitem", "Gets items from all selected [Mailid]..", HL_MAIL, true).c_str());
            ch.SendSysMessage(_HandleCommandHelpHelper("mail delete", "Delete all selected [Mailid]..", HL_MAIL, true).c_str());

            // Catches all valid subcommands, also placeholders for potential future sub-subcommands
            if (ExtractCommand("inbox", text, true)) {}
            else if (ExtractCommand("getcash", text, true)) {}
            else if (ExtractCommand("getitem", text, true)) {}
            else if (ExtractCommand("delete", text, true)) {}

            if (text != "") ch.SendSysMessage(sInvalidSubcommand.c_str());
            return;
        }
    }

    if (bMainHelp)
        ch.SendSysMessage(_HandleCommandHelpHelper("help", "Gives you this listing of main commands... But then, you know that already don't you.").c_str());

    if (text != "")
        ch.SendSysMessage("Either that is not a valid command, or someone forgot to add it to my help journal. I mean seriously, they can't expect me to remember *all* this stuff, can they?");
}

std::string PlayerbotAI::_HandleCommandHelpHelper(std::string sCommand, std::string sExplain, HELPERLINKABLES reqLink, bool bReqLinkMultiples, bool bCommandShort)
{
    if (sCommand == "")
    {
        DEBUG_LOG("[PlayerbotAI] _HandleCommandHelpHelper called with an empty sCommand. Ignoring call.");
        return "";
    }

    std::ostringstream oss;
    oss << "'|cffffffff";
    if (bCommandShort)
        oss << "(" << sCommand.at(0) << ")" << sCommand.substr(1);
    else
        oss << sCommand;

    if (reqLink != HL_NONE)
    {
        if (reqLink == HL_PROFESSION)
        {
            oss << " [PROFESSION]";
            if (bReqLinkMultiples)
                oss << " [PROFESSION] ..";
        }
        else if (reqLink == HL_ITEM)
        {
            oss << " [ITEM]";
            if (bReqLinkMultiples)
                oss << " [ITEM] ..";
        }
        else if (reqLink == HL_TALENT)
        {
            oss << " [TALENT]";
            if (bReqLinkMultiples)
                oss << " [TALENT] ..";
        }
        else if (reqLink == HL_SKILL)
        {
            oss << " [SKILL]";
            if (bReqLinkMultiples)
                oss << " [SKILL] ..";
        }
        else if (reqLink == HL_OPTION)
        {
            oss << " <OPTION>";
            if (bReqLinkMultiples)
                oss << " <OPTION> ..";
        }
        else if (reqLink == HL_PETAGGRO)
        {
            oss << " <(a)ggressive | (d)efensive | (p)assive>";
            if (bReqLinkMultiples)
                DEBUG_LOG("[PlayerbotAI] _HandleCommandHelpHelper: sCommand \"pet\" with bReqLinkMultiples \"true\". ... Why? Bug, surely.");
        }
        else if (reqLink == HL_QUEST)
        {
            oss << " [QUEST]";
            if (bReqLinkMultiples)
                oss << " [QUEST] ..";
        }
        else if (reqLink == HL_GAMEOBJECT)
        {
            oss << " [GAMEOBJECT]";
            if (bReqLinkMultiples)
                oss << " [GAMEOBJECT] ..";
        }
        else if (reqLink == HL_SPELL)
        {
            oss << " <Id# | (part of) name | [SPELL]>";
            if (bReqLinkMultiples)
                oss << " <Id# | (part of) name | [SPELL]> ..";
        }
        else if (reqLink == HL_TARGET)
        {
            oss << " (TARGET)";
            if (bReqLinkMultiples)
                oss << " (TARGET) ..";
        }
        else if (reqLink == HL_NAME)
        {
            oss << " <NAME>";
            if (bReqLinkMultiples)
                oss << " <NAME> ..";
        }
        else if (reqLink == HL_AUCTION)
        {
            oss << " [AUCTION]";
            if (bReqLinkMultiples)
                oss << " [AUCTION] ..";
        }
        else if (reqLink == HL_RECIPE)
        {
            oss << " [RECIPE]";
            if (bReqLinkMultiples)
                oss << " [RECIPE] ..";
        }
        else if (reqLink == HL_MAIL)
        {
            oss << " [MAILID]";
            if (bReqLinkMultiples)
                oss << " [MAILID] ..";
        }
        else
        {
            oss << " {unknown}";
            if (bReqLinkMultiples)
                oss << " {unknown} ..";
            DEBUG_LOG("[PlayerbotAI]: _HandleCommandHelpHelper - Uncaught case");
        }
    }

    oss << "|r': " << sExplain;

    return oss.str();
}

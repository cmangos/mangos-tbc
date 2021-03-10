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

#ifndef MANGOS_SQLSTORAGES_H
#define MANGOS_SQLSTORAGES_H

#include "Database/SQLStorage.h"
#include "DBCStructure.h"

extern SQLStorage<CreatureInfo>                       sCreatureStorage;
extern SQLStorage<CreatureDataAddon>                  sCreatureDataAddonStorage;
extern SQLStorage<CreatureDataAddon>                  sCreatureInfoAddonStorage;
extern SQLStorage<CreatureModelInfo>                  sCreatureModelStorage;
extern SQLStorage<EquipmentInfo>                      sEquipmentStorage;
extern SQLStorage<EquipmentInfoRaw>                   sEquipmentStorageRaw;
extern SQLStorage<PageText>                           sPageTextStore;
extern SQLStorage<ItemPrototype>                      sItemStorage;
extern SQLStorage<InstanceTemplate>                   sInstanceTemplate;
extern SQLStorage<WorldTemplate>                      sWorldTemplate;
extern SQLStorage<ConditionEntry>                     sConditionStorage;
extern SQLStorage<SpellEntry>                         sSpellTemplate;
extern SQLStorage<SpellCone>                          sSpellCones;
extern SQLStorage<DungeonEncounterEntry>              sDungeonEncounterStore;
extern SQLStorage<FactionEntry>                       sFactionStore;
extern SQLStorage<CreatureConditionalSpawn>           sCreatureConditionalSpawnStore;
extern SQLStorage<WorldSafeLocsEntry>                 sWorldSafeLocsStore;

extern SQLHashStorage<GameObjectInfo>                 sGOStorage;
extern SQLMultiStorage<SpellTargetEntry>              sSpellScriptTargetStorage;

// DBC stores in db
extern SQLStorage<AreaTableEntry>                     sAreaTableStore;
extern SQLStorage<AreaTriggerEntry>                   sAreaTriggerStore;
extern SQLStorage<AuctionHouseEntry>                  sAuctionHouseStore;
extern SQLStorage<BankBagSlotPricesEntry>             sBankBagSlotPricesStore;
extern SQLStorage<BattlemasterListEntry>              sBattlemasterListStore;
extern SQLStorage<CharStartOutfitEntry>               sCharStartOutfitStore;
extern SQLStorage<CharTitlesEntry>                    sCharTitlesStore;
extern SQLStorage<ChatChannelsEntry>                  sChatChannelsStore;
extern SQLStorage<ChrClassesEntry>                    sChrClassesStore;
extern SQLStorage<ChrRacesEntry>                      sChrRacesStore;
extern SQLStorage<CinematicCameraEntry>               sCinematicCameraStore;
extern SQLStorage<CinematicSequencesEntry>            sCinematicSequencesStore;
extern SQLStorage<CreatureDisplayInfoEntry>           sCreatureDisplayInfoStore;
extern SQLStorage<CreatureDisplayInfoExtraEntry>      sCreatureDisplayInfoExtraStore;
extern SQLStorage<CreatureFamilyEntry>                sCreatureFamilyStore;
extern SQLStorage<CreatureModelDataEntry>             sCreatureModelDataStore;
extern SQLStorage<CreatureSpellDataEntry>             sCreatureSpellDataStore; // todo not used?
extern SQLStorage<CreatureTypeEntry>                  sCreatureTypeStore;
extern SQLStorage<DurabilityCostsEntry>               sDurabilityCostsStore;
extern SQLStorage<DurabilityQualityEntry>             sDurabilityQualityStore;
extern SQLStorage<EmotesEntry>                        sEmotesStore;
extern SQLStorage<EmotesTextEntry>                    sEmotesTextStore;
extern SQLStorage<FactionTemplateEntry>               sFactionTemplateStore;
extern SQLStorage<GameObjectDisplayInfoEntry>         sGameObjectDisplayInfoStore;
extern SQLStorage<GemPropertiesEntry>                 sGemPropertiesStore;
extern SQLStorage<GMSurveyCurrentSurveyEntry>         sGMSurveyCurrentSurveyStore;
extern SQLStorage<GMSurveyQuestionsEntry>             sGMSurveyQuestionsStore;
extern SQLStorage<GMSurveyEntry>                      sGMSurveySurveysStore;
extern SQLStorage<GMTicketCategoryEntry>              sGMTicketCategoryStore;
extern SQLStorage<GtCombatRatingsEntry>               sgtCombatRatingsStore;
extern SQLStorage<GtChanceToMeleeCritBaseEntry>       sgtChanceToMeleeCritBaseStore;
extern SQLStorage<GtChanceToMeleeCritEntry>           sgtChanceToMeleeCritStore;
extern SQLStorage<GtChanceToSpellCritBaseEntry>       sgtChanceToSpellCritBaseStore;
extern SQLStorage<GtChanceToSpellCritEntry>           sgtChanceToSpellCritStore;
extern SQLStorage<GtOCTRegenHPEntry>                  sgtOCTRegenHPStore;
extern SQLStorage<GtNPCManaCostScalerEntry>           sgtNPCManaCostScalerStore;
extern SQLStorage<GtRegenHPPerSptEntry>               sgtRegenHPPerSptStore;
extern SQLStorage<GtRegenMPPerSptEntry>               sgtRegenMPPerSptStore;
extern SQLStorage<ItemEntry>                          sItemStore;
extern SQLStorage<ItemBagFamilyEntry>                 sItemBagFamilyStore;
extern SQLStorage<ItemClassEntry>                     sItemClassStore;
extern SQLStorage<ItemExtendedCostEntry>              sItemExtendedCostStore;
extern SQLStorage<ItemRandomPropertiesEntry>          sItemRandomPropertiesStore;
extern SQLStorage<ItemRandomSuffixEntry>              sItemRandomSuffixStore;
extern SQLStorage<ItemSetEntry>                       sItemSetStore;
extern SQLStorage<LiquidTypeEntry>                    sLiquidTypeStore;
extern SQLStorage<LockEntry>                          sLockStore;
extern SQLStorage<MailTemplateEntry>                  sMailTemplateStore;
extern SQLStorage<MapEntry>                           sMapStore;
extern SQLStorage<QuestSortEntry>                     sQuestSortStore;
extern SQLStorage<RandomPropertiesPointsEntry>        sRandPropPointsStore;
extern SQLStorage<SkillLineEntry>                     sSkillLineStore;
extern SQLStorage<SkillLineAbilityEntry>              sSkillLineAbilityStore;
extern SQLStorage<SkillRaceClassInfoEntry>            sSkillRaceClassInfoStore;
extern SQLStorage<SkillTiersEntry>                    sSkillTiersStore;
extern SQLStorage<SoundEntriesEntry>                  sSoundEntriesStore;
extern SQLStorage<SpellCastTimesEntry>                sSpellCastTimesStore;
extern SQLStorage<SpellDurationEntry>                 sSpellDurationStore;
extern SQLStorage<SpellFocusObjectEntry>              sSpellFocusObjectStore;
extern SQLStorage<SpellItemEnchantmentEntry>          sSpellItemEnchantmentStore;
extern SQLStorage<SpellItemEnchantmentConditionEntry> sSpellItemEnchantmentConditionStore;
extern SQLStorage<SpellRadiusEntry>                   sSpellRadiusStore;
extern SQLStorage<SpellRangeEntry>                    sSpellRangeStore;
extern SQLStorage<SpellShapeshiftFormEntry>           sSpellShapeshiftFormStore;
extern SQLStorage<SpellVisualEntry>                   sSpellVisualStore;
extern SQLStorage<StableSlotPricesEntry>              sStableSlotPricesStore;
extern SQLStorage<SummonPropertiesEntry>              sSummonPropertiesStore;
extern SQLStorage<TalentEntry>                        sTalentStore;
extern SQLStorage<TalentTabEntry>                     sTalentTabStore;
extern SQLStorage<TaxiNodesEntry>                     sTaxiNodesStore;
extern SQLStorage<TaxiPathEntry>                      sTaxiPathStore;
extern SQLStorage<TaxiPathNodeEntry>                  sTaxiPathNodeStore;
extern SQLStorage<TransportAnimationEntry>            sTransportAnimationStore;
extern SQLStorage<TotemCategoryEntry>                 sTotemCategoryStore;
extern SQLStorage<WorldMapAreaEntry>                  sWorldMapAreaStore;
extern SQLStorage<WMOAreaTableEntry>                  sWMOAreaTableStore;

// following are mostly helper store to get fast lookup of some other stores
typedef std::map<uint16, uint32> AreaFlagByAreaID;
typedef std::map<uint32, uint32> AreaFlagByMapID;

struct WMOAreaTableTripple
{
    WMOAreaTableTripple(int32 r, int32 a, int32 g) : groupId(g), rootId(r), adtId(a)
    {
    }

    bool operator <(const WMOAreaTableTripple& b) const
    {
        return memcmp(this, &b, sizeof(WMOAreaTableTripple)) < 0;
    }

    // ordered by entropy; that way memcmp will have a minimal medium runtime
    int32 groupId;
    int32 rootId;
    int32 adtId;
};

typedef std::map<WMOAreaTableTripple, std::vector<WMOAreaTableEntry const*>> WMOAreaInfoByTripple;

extern AreaFlagByAreaID             sAreaFlagByAreaID;
extern AreaFlagByMapID              sAreaFlagByMapID;                   // for instances without generated *.map files

extern WMOAreaInfoByTripple         sWMOAreaInfoByTripple;

extern SpellCategoryStore           sSpellCategoryStore;
extern ItemSpellCategoryStore       sItemSpellCategoryStore;
extern PetFamilySpellsStore         sPetFamilySpellsStore;
extern TaxiMask                     sTaxiNodesMask;
extern TaxiPathSetBySource          sTaxiPathSetBySource;
extern TaxiPathNodesByPath          sTaxiPathNodesByPath;

typedef std::map<uint32, uint32> TalentInspectMap;
extern TalentInspectMap             sTalentTabSizeInInspect;
extern TalentInspectMap             sTalentPosInInspect;
extern uint32 sTalentTabPages[12/*MAX_CLASSES*/][3];
extern TalentSpellPosMap            sTalentSpellPosMap;

void LoadDBCTables();

SQLStorage<SpellEntry>   const* GetSpellStore();

#endif

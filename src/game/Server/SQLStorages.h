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

extern SQLStorage<CreatureInfo> sCreatureStorage;
extern SQLStorage<CreatureDataAddon> sCreatureDataAddonStorage;
extern SQLStorage<CreatureDataAddon> sCreatureInfoAddonStorage;
extern SQLStorage<CreatureModelInfo> sCreatureModelStorage;
extern SQLStorage<EquipmentInfo> sEquipmentStorage;
extern SQLStorage<EquipmentInfoRaw> sEquipmentStorageRaw;
extern SQLStorage<PageText> sPageTextStore;
extern SQLStorage<ItemPrototype> sItemStorage;
extern SQLStorage<InstanceTemplate> sInstanceTemplate;
extern SQLStorage<WorldTemplate> sWorldTemplate;
extern SQLStorage<ConditionEntry> sConditionStorage;
extern SQLStorage<SpellEntry> sSpellTemplate;
extern SQLStorage<SpellCone> sSpellCones;
extern SQLStorage<DungeonEncounterEntry> sDungeonEncounterStore;
extern SQLStorage<FactionEntry> sFactionStore;
extern SQLStorage<CreatureConditionalSpawn> sCreatureConditionalSpawnStore;
extern SQLStorage<WorldSafeLocsEntry> sWorldSafeLocsStore;


extern SQLHashStorage<GameObjectInfo> sGOStorage;

extern SQLMultiStorage<SpellTargetEntry> sSpellScriptTargetStorage;


// DBC stores in <>db
extern SQLStorage<AreaTableEntry> sDBCAreaTable;
extern SQLStorage<AreaTriggerEntry> sDBCAreaTrigger;
extern SQLStorage<AuctionHouseEntry> sDBCAuctionHouse;
extern SQLStorage<BankBagSlotPricesEntry> sDBCBankBagSlotPrices;
extern SQLStorage<BattlemasterListEntry> sDBCBattlemasterList;
extern SQLStorage<CharStartOutfitEntry> sDBCCharStartOutfit;
extern SQLStorage<CharTitlesEntry> sDBCCharTitles;
extern SQLStorage<ChatChannelsEntry> sDBCChatChannels;
extern SQLStorage<ChrClassesEntry> sDBCChrClasses;
extern SQLStorage<ChrRacesEntry> sDBCChrRaces;
extern SQLStorage<CinematicCameraEntry> sDBCCinematicCamera;
extern SQLStorage<CinematicSequencesEntry> sDBCCinematicSequences;
extern SQLStorage<CreatureDisplayInfoEntry> sDBCCreatureDisplayInfo;
extern SQLStorage<CreatureDisplayInfoExtraEntry> sDBCCreatureDisplayInfoExtra;
extern SQLStorage<CreatureFamilyEntry> sDBCCreatureFamily;
extern SQLStorage<CreatureModelDataEntry> sDBCCreatureModelData;
extern SQLStorage<CreatureSpellDataEntry> sDBCCreatureSpellData;
extern SQLStorage<CreatureTypeEntry> sDBCCreatureType;
extern SQLStorage<DurabilityCostsEntry> sDBCDurabilityCosts;
extern SQLStorage<DurabilityQualityEntry> sDBCDurabilityQuality;
extern SQLStorage<EmotesEntry> sDBCEmotes;
extern SQLStorage<EmotesTextEntry> sDBCEmotesText;
extern SQLStorage<FactionTemplateEntry> sDBCFactionTemplate;
extern SQLStorage<GameObjectDisplayInfoEntry> sDBCGameObjectDisplayInfo;
extern SQLStorage<GemPropertiesEntry> sDBCGemProperties;
extern SQLStorage<GMSurveyCurrentSurveyEntry> sDBCGMSurveyCurrentSurvey;
extern SQLStorage<GMSurveyQuestionsEntry> sDBCGMSurveyQuestions;
extern SQLStorage<GMSurveyEntry> sDBCGMSurveySurveys;
extern SQLStorage<GMTicketCategoryEntry> sDBCGMTicketCategory;
extern SQLStorage<GtCombatRatingsEntry> sDBCgtCombatRatings;
extern SQLStorage<GtChanceToMeleeCritBaseEntry> sDBCgtChanceToMeleeCritBase;
extern SQLStorage<GtChanceToMeleeCritEntry> sDBCgtChanceToMeleeCrit;
extern SQLStorage<GtChanceToSpellCritBaseEntry> sDBCgtChanceToSpellCritBase;
extern SQLStorage<GtChanceToSpellCritEntry> sDBCgtChanceToSpellCrit;
extern SQLStorage<GtOCTRegenHPEntry> sDBCgtOCTRegenHP;
extern SQLStorage<GtNPCManaCostScalerEntry> sDBCgtNPCManaCostScaler;
extern SQLStorage<GtRegenHPPerSptEntry> sDBCgtRegenHPPerSpt;
extern SQLStorage<GtRegenMPPerSptEntry> sDBCgtRegenMPPerSpt;
extern SQLStorage<ItemEntry> sDBCItem;
extern SQLStorage<ItemBagFamilyEntry> sDBCItemBagFamily;
extern SQLStorage<ItemClassEntry> sDBCItemClass;
extern SQLStorage<ItemExtendedCostEntry> sDBCItemExtendedCost;
extern SQLStorage<ItemRandomPropertiesEntry> sDBCItemRandomProperties;
extern SQLStorage<ItemRandomSuffixEntry> sDBCItemRandomSuffix;
extern SQLStorage<ItemSetEntry> sDBCItemSet;
extern SQLStorage<LiquidTypeEntry> sDBCLiquidType;
extern SQLStorage<LockEntry> sDBCLock;
extern SQLStorage<MailTemplateEntry> sDBCMailTemplate;
extern SQLStorage<MapEntry> sDBCMap;
extern SQLStorage<QuestSortEntry> sDBCQuestSort;
extern SQLStorage<RandomPropertiesPointsEntry> sDBCRandPropPoints;
extern SQLStorage<SkillLineEntry> sDBCSkillLine;
extern SQLStorage<SkillLineAbilityEntry> sDBCSkillLineAbility;
extern SQLStorage<SkillRaceClassInfoEntry> sDBCSkillRaceClassInfo;
extern SQLStorage<SkillTiersEntry> sDBCSkillTiers;
extern SQLStorage<SoundEntriesEntry> sDBCSoundEntries;
extern SQLStorage<SpellCastTimesEntry> sDBCSpellCastTimes;
extern SQLStorage<SpellDurationEntry> sDBCSpellDuration;
extern SQLStorage<SpellFocusObjectEntry> sDBCSpellFocusObject;
extern SQLStorage<SpellItemEnchantmentEntry> sDBCSpellItemEnchantment;
extern SQLStorage<SpellItemEnchantmentConditionEntry> sDBCSpellItemEnchantmentCondition;
extern SQLStorage<SpellRadiusEntry> sDBCSpellRadius;
extern SQLStorage<SpellRangeEntry> sDBCSpellRange;
extern SQLStorage<SpellShapeshiftFormEntry> sDBCSpellShapeshiftForm;
extern SQLStorage<SpellVisualEntry> sDBCSpellVisual;
extern SQLStorage<StableSlotPricesEntry> sDBCStableSlotPrices;
extern SQLStorage<SummonPropertiesEntry> sDBCSummonProperties;
extern SQLStorage<TalentEntry> sDBCTalent;
extern SQLStorage<TalentTabEntry> sDBCTalentTab;
extern SQLStorage<TaxiNodesEntry> sDBCTaxiNodes;
extern SQLStorage<TaxiPathEntry> sDBCTaxiPath;
extern SQLStorage<TaxiPathNodeEntry> sDBCTaxiPathNode;
extern SQLStorage<TransportAnimationEntry> sDBCTransportAnimation;
extern SQLStorage<TotemCategoryEntry> sDBCTotemCategory;
extern SQLStorage<WorldMapAreaEntry> sDBCWorldMapArea;
extern SQLStorage<WMOAreaTableEntry> sDBCWMOAreaTable;

void LoadDBCTables();



SQLStorage<SpellEntry>   const* GetSpellStore();

#endif

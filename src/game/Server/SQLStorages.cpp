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

#include "Server/SQLStorages.h"
#include "DBCStructure.h"
#include "World/World.h"

const char CreatureInfosrcfmt[]               = "nsssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiss";
const char CreatureInfodstfmt[]               = "nsssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiisi";
const char CreatureDataAddonInfofmt[]         = "niibbiis";
const char CreatureConditionalSpawnSrcFmt[]   = "niix";
const char CreatureConditionalSpawnDstFmt[]   = "nii";
const char CreatureModelfmt[]                 = "nffffbii";
const char CreatureInfoAddonInfofmt[]         = "niibbiis";
const char EquipmentInfofmt[]                 = "niii";
const char EquipmentInfoRawfmt[]              = "niiiiiiiii";
const char GameObjectInfosrcfmt[]             = "niisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiis";
const char GameObjectInfodstfmt[]             = "niisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char ItemPrototypesrcfmt[]              = "niiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifsiiiiii";
const char ItemPrototypedstfmt[]              = "niiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiii";
const char PageTextfmt[]                      = "nsi";
const char InstanceTemplatesrcfmt[]           = "niiiiisl";
const char InstanceTemplatedstfmt[]           = "niiiiiil";
const char WorldTemplatesrcfmt[]              = "ns";
const char WorldTemplatedstfmt[]              = "ni";
const char ConditionsFmt[]                    = "niiiiiix";
const char SpellScriptTargetFmt[]             = "niii";
const char SpellEntryfmt[]                    = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiifffiiiissssssssssssssssssssssssssssssssiiiiiLiiiifffiiiiiiiii";
const char SpellConefmt[]                     = "ni";
const char DungeonEncounterFmt[]              = "niiiissssssssssssssssii";
const char FactionEntryfmt[]                  = "niiiiiiiiiiiiiiiiiiffiissssssssssssssss";
const char WorldSafeLocsFmt[]                 = "niffffs";

SQLStorage<CreatureInfo>                      sCreatureStorage(CreatureInfosrcfmt, CreatureInfodstfmt, "", "creature_template");
SQLStorage<CreatureDataAddon>                 sCreatureDataAddonStorage(CreatureDataAddonInfofmt, "creature_addon");
SQLStorage<CreatureDataAddon>                 sCreatureInfoAddonStorage(CreatureInfoAddonInfofmt, "creature_template_addon");
SQLStorage<CreatureModelInfo>                 sCreatureModelStorage(CreatureModelfmt, "creature_model_info");
SQLStorage<EquipmentInfo>                     sEquipmentStorage(EquipmentInfofmt, "creature_equip_template");
SQLStorage<EquipmentInfoRaw>                  sEquipmentStorageRaw(EquipmentInfoRawfmt, "creature_equip_template_raw");
SQLStorage<PageText>                          sPageTextStore(PageTextfmt, "page_text");
SQLStorage<ItemPrototype>                     sItemStorage(ItemPrototypesrcfmt, ItemPrototypedstfmt, "", "item_template");
SQLStorage<InstanceTemplate>                  sInstanceTemplate(InstanceTemplatesrcfmt, InstanceTemplatedstfmt, "", "instance_template");
SQLStorage<WorldTemplate>                     sWorldTemplate(WorldTemplatesrcfmt, WorldTemplatedstfmt, "", "world_template");
SQLStorage<ConditionEntry>                    sConditionStorage(ConditionsFmt, "conditions");
SQLStorage<SpellEntry>                        sSpellTemplate(SpellEntryfmt, "spell_template");
SQLStorage<SpellCone>                         sSpellCones(SpellConefmt, "spell_cone");
SQLStorage<DungeonEncounterEntry>             sDungeonEncounterStore(DungeonEncounterFmt, "instance_dungeon_encounters");
SQLStorage<FactionEntry>                      sFactionStore(FactionEntryfmt, "faction_store");
SQLStorage<CreatureConditionalSpawn>          sCreatureConditionalSpawnStore(CreatureConditionalSpawnSrcFmt, CreatureConditionalSpawnDstFmt, "", "creature_conditional_spawn");
SQLStorage<WorldSafeLocsEntry>                sWorldSafeLocsStore(WorldSafeLocsFmt, "world_safe_locs");

SQLHashStorage<GameObjectInfo>                sGOStorage(GameObjectInfosrcfmt, GameObjectInfodstfmt, "entry", "gameobject_template");
SQLMultiStorage<SpellTargetEntry>             sSpellScriptTargetStorage(SpellScriptTargetFmt, "entry", "spell_script_target");

SQLStorage<SpellEntry> const*                 GetSpellStore() { return &sSpellTemplate; }


// DBC store in database
const char AreaTablefmt[]                     = "iiiniwwwwwisssssssssssssssswiiiiiww";
const char AreaTriggerfmt[]                   = "niffffffff";
const char AuctionHousefmt[]                  = "niiiwwwwwwwwwwwwwwwww";
const char BankBagSlotPricesfmt[]             = "ni";
const char BattlemasterListfmt[]              = "niiiiiiiiiiiiwwssssssssssssssssww";
const char CharStartOutfitfmt[]               = "dbbbbiiiiiiiiiiiiwwwwwwwwwwwwwwwwwwwwwwww";
const char CharTitlesfmt[]                    = "nwsssssssssssssssswwwwwwwwwwwwwwwwwwi";
const char ChatChannelsfmt[]                  = "niwsssssssssssssssswwwwwwwwwwwwwwwwww";
const char ChrClassesfmt[]                    = "nwiwsssssssssssssssswwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwiw";
const char ChrRacesfmt[]                      = "nwiwiiwwiwwwwisssssssssssssssswwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwi";
const char CinematicCamerafmt[]               = "nsiffff";
const char CinematicSequencesfmt[]            = "nwiwwwwwww";
const char CreatureDisplayInfofmt[]           = "niwifwwwwwwwww";
const char CreatureDisplayInfoExtrafmt[]      = "niwwwwwwwwwwwwwwwwwww";
const char CreatureFamilyfmt[]                = "nfifiiiissssssssssssssssww";
const char CreatureModelDatafmt[]             = "niwwfwwwwwwwwwwffwwwwwww";
const char CreatureSpellDatafmt[]             = "niiiiwwww";
const char CreatureTypefmt[]                  = "nwwwwwwwwwwwwwwwwww";
const char DurabilityCostsfmt[]               = "niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[]             = "nf";
const char Emotesfmt[]                        = "nwwiiiw";
const char EmotesTextfmt[]                    = "nwiwwwwwwwwwwwwwwww";
const char FactionTemplatefmt[]               = "niiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[]         = "nswwwwwwwwwwffffff";
const char GemPropertiesfmt[]                 = "niwwi";
const char GMSurveyCurrentSurveyfmt[]         = "ni";
const char GMSurveyQuestionsfmt[]             = "nssssssssssssssssw";
const char GMSurveySurveysfmt[]               = "niiiiiiiiii";
const char GMTicketCategoryfmt[]              = "nssssssssssssssssw";
const char gtCombatRatingsfmt[]               = "f";
const char gtChanceToMeleeCritBasefmt[]       = "f";
const char gtChanceToMeleeCritfmt[]           = "f";
const char gtChanceToSpellCritBasefmt[]       = "f";
const char gtChanceToSpellCritfmt[]           = "f";
const char gtOCTRegenHPfmt[]                  = "f";
const char gtNPCManaCostScalerfmt[]           = "f";
const char gtRegenHPPerSptfmt[]               = "f";
const char gtRegenMPPerSptfmt[]               = "f";
const char Itemfmt[]                          = "niii";
const char ItemBagFamilyfmt[]                 = "nwwwwwwwwwwwwwwwww";
const char ItemClassfmt[]                     = "nwwssssssssssssssssw";
const char ItemExtendedCostfmt[]              = "niiiiiiiiiiiii";
const char ItemRandomPropertiesfmt[]          = "nwiiiwwssssssssssssssssw";
const char ItemRandomSuffixfmt[]              = "nsssssssssssssssswwiiiiii";
const char ItemSetfmt[]                       = "nsssssssssssssssswwwwwwwwwwwwwwwwwwiiiiiiiiiiiiiiiiii";
const char LiquidTypefmt[]                    = "niii";
const char Lockfmt[]                          = "niiiiiiiiiiiiiiiiiiiiiiiiwwwwwwww";
const char MailTemplatefmt[]                  = "nwwwwwwwwwwwwwwwwwssssssssssssssssw";
const char Mapfmt[]                           = "nwiwsssssssssssssssswwwwwwwiwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwiwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwiffiiwwi";
const char QuestSortfmt[]                     = "nwwwwwwwwwwwwwwwww";
const char RandPropPointsfmt[]                = "niiiiiiiiiiiiiii";
const char SkillLinefmt[]                     = "niwsssssssssssssssswwwwwwwwwwwwwwwwwwi";
const char SkillLineAbilityfmt[]              = "niiiiwwiiiiiwwi";
const char SkillRaceClassInfofmt[]            = "wiiiiiiw";
const char SkillTiersfmt[]                    = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char SoundEntriesfmt[]                  = "nwwwwwwwwwwwwwwwwwwwwwwwwwwww";
const char SpellCastTimesfmt[]                = "niii";
const char SpellDurationfmt[]                 = "niii";
const char SpellFocusObjectfmt[]              = "nwwwwwwwwwwwwwwwww";
const char SpellItemEnchantmentfmt[]          = "niiiiiiwwwiiisssssssssssssssswiiii";
const char SpellItemEnchantmentConditionfmt[] = "nbbbbbwwwwwbbbbbbbbbbiiiiiwwwww";
const char SpellRadiusfmt[]                   = "nfww";
const char SpellRangefmt[]                    = "nffiwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww";
const char SpellShapeshiftFormfmt[]           = "nwwwwwwwwwwwwwwwwwwiiwiiwwwiiiiiiii";
const char SpellVisualfmt[]                   = "nwwwwwiiwwwwwwwwwwwwwwwww";
const char StableSlotPricesfmt[]              = "ni";
const char SummonPropertiesfmt[]              = "niiiii";
const char Talentfmt[]                        = "niiiiiiiiwwwwiwwiwwwi";
const char TalentTabfmt[]                     = "nwwwwwwwwwwwwwwwwwwwiiw";
const char TaxiNodesfmt[]                     = "nifffsssssssssssssssswii";
const char TaxiPathfmt[]                      = "niii";
const char TaxiPathNodefmt[]                  = "diiifffiiii";
const char TransportAnimationfmt[]            = "diifffw";
const char TotemCategoryfmt[]                 = "nwwwwwwwwwwwwwwwwwii";
const char WorldMapAreafmt[]                  = "diiwffffi";
const char WMOAreaTablefmt[]                  = "niiiwwwwwiiwwwwwwwwwwwwwwwww";

SQLStorage<AreaTableEntry>                      sDBCAreaTable(AreaTablefmt, "dbc_areatable");
SQLStorage<AreaTriggerEntry>                    sDBCAreaTrigger(AreaTriggerfmt, "dbc_areatrigger");
SQLStorage<AuctionHouseEntry>                   sDBCAuctionHouse(AuctionHousefmt, "dbc_auctionhouse");
SQLStorage<BankBagSlotPricesEntry>              sDBCBankBagSlotPrices(BankBagSlotPricesfmt, "dbc_bankbagslotprices");
SQLStorage<BattlemasterListEntry>               sDBCBattlemasterList(BattlemasterListfmt, "dbc_battlemasterlist");
SQLStorage<CharStartOutfitEntry>                sDBCCharStartOutfit(CharStartOutfitfmt, "dbc_charstartoutfit");
SQLStorage<CharTitlesEntry>                     sDBCCharTitles(CharTitlesfmt, "dbc_chartitles");
SQLStorage<ChatChannelsEntry>                   sDBCChatChannels(ChatChannelsfmt, "dbc_chatchannels");
SQLStorage<ChrClassesEntry>                     sDBCChrClasses(ChrClassesfmt, "dbc_chrclasses");
SQLStorage<ChrRacesEntry>                       sDBCChrRaces(ChrRacesfmt, "dbc_chrraces");
SQLStorage<CinematicCameraEntry>                sDBCCinematicCamera(CinematicCamerafmt, "dbc_cinematiccamera");
SQLStorage<CinematicSequencesEntry>             sDBCCinematicSequences(CinematicSequencesfmt, "dbc_cinematicsequences");
SQLStorage<CreatureDisplayInfoEntry>            sDBCCreatureDisplayInfo(CreatureDisplayInfofmt, "dbc_creaturedisplayinfo");
SQLStorage<CreatureDisplayInfoExtraEntry>       sDBCCreatureDisplayInfoExtra(CreatureDisplayInfoExtrafmt, "dbc_creaturedisplayinfoextra");
SQLStorage<CreatureFamilyEntry>                 sDBCCreatureFamily(CreatureFamilyfmt, "dbc_creaturefamily");
SQLStorage<CreatureModelDataEntry>              sDBCCreatureModelData(CreatureModelDatafmt, "dbc_creaturemodeldata");
SQLStorage<CreatureSpellDataEntry>              sDBCCreatureSpellData(CreatureSpellDatafmt, "dbc_creaturespelldata");
SQLStorage<CreatureTypeEntry>                   sDBCCreatureType(CreatureTypefmt, "dbc_creaturetype");
SQLStorage<DurabilityCostsEntry>                sDBCDurabilityCosts(DurabilityCostsfmt, "dbc_durabilitycosts");
SQLStorage<DurabilityQualityEntry>              sDBCDurabilityQuality(DurabilityQualityfmt, "dbc_durabilityquality");
SQLStorage<EmotesEntry>                         sDBCEmotes(Emotesfmt, "dbc_emotes");
SQLStorage<EmotesTextEntry>                     sDBCEmotesText(EmotesTextfmt, "dbc_emotestext");
SQLStorage<FactionTemplateEntry>                sDBCFactionTemplate(FactionTemplatefmt, "dbc_factiontemplate");
SQLStorage<GameObjectDisplayInfoEntry>          sDBCGameObjectDisplayInfo(GameObjectDisplayInfofmt, "dbc_gameobjectdisplayinfo");
SQLStorage<GemPropertiesEntry>                  sDBCGemProperties(GemPropertiesfmt, "dbc_gemproperties");
SQLStorage<GMSurveyCurrentSurveyEntry>          sDBCGMSurveyCurrentSurvey(GMSurveyCurrentSurveyfmt, "dbc_gmsurveycurrentsurvey");
SQLStorage<GMSurveyQuestionsEntry>              sDBCGMSurveyQuestions(GMSurveyQuestionsfmt, "dbc_gmsurveyquestions");
SQLStorage<GMSurveyEntry>                       sDBCGMSurveySurveys(GMSurveySurveysfmt, "dbc_gmsurveysurveys");
SQLStorage<GMTicketCategoryEntry>               sDBCGMTicketCategory(GMTicketCategoryfmt, "dbc_gmticketcategory");
SQLStorage<GtCombatRatingsEntry>                sDBCgtCombatRatings(gtCombatRatingsfmt, "dbc_gtcombatratings");
SQLStorage<GtChanceToMeleeCritBaseEntry>        sDBCgtChanceToMeleeCritBase(gtChanceToMeleeCritBasefmt, "dbc_gtchancetomeleecritbase");
SQLStorage<GtChanceToMeleeCritEntry>            sDBCgtChanceToMeleeCrit(gtChanceToMeleeCritfmt, "dbc_gtchancetomeleecrit");
SQLStorage<GtChanceToSpellCritBaseEntry>        sDBCgtChanceToSpellCritBase(gtChanceToSpellCritBasefmt, "dbc_gtchancetospellcritbase");
SQLStorage<GtChanceToSpellCritEntry>            sDBCgtChanceToSpellCrit(gtChanceToSpellCritfmt, "dbc_gtchancetospellcrit");
SQLStorage<GtOCTRegenHPEntry>                   sDBCgtOCTRegenHP(gtOCTRegenHPfmt, "dbc_gtoctregenhp");
SQLStorage<GtNPCManaCostScalerEntry>            sDBCgtNPCManaCostScaler(gtNPCManaCostScalerfmt, "dbc_gtnpcmanacostscaler");
SQLStorage<GtRegenHPPerSptEntry>                sDBCgtRegenHPPerSpt(gtRegenHPPerSptfmt, "dbc_gtregenhpperspt");
SQLStorage<GtRegenMPPerSptEntry>                sDBCgtRegenMPPerSpt(gtRegenMPPerSptfmt, "dbc_gtregenmpperspt");
SQLStorage<ItemEntry>                           sDBCItem(Itemfmt, "dbc_item");
SQLStorage<ItemBagFamilyEntry>                  sDBCItemBagFamily(ItemBagFamilyfmt, "dbc_itembagfamily");
SQLStorage<ItemClassEntry>                      sDBCItemClass(ItemClassfmt, "dbc_itemclass");
SQLStorage<ItemExtendedCostEntry>               sDBCItemExtendedCost(ItemExtendedCostfmt, "dbc_itemextendedcost");
SQLStorage<ItemRandomPropertiesEntry>           sDBCItemRandomProperties(ItemRandomPropertiesfmt, "dbc_itemrandomproperties");
SQLStorage<ItemRandomSuffixEntry>               sDBCItemRandomSuffix(ItemRandomSuffixfmt, "dbc_itemrandomsuffix");
SQLStorage<ItemSetEntry>                        sDBCItemSet(ItemSetfmt, "dbc_itemset");
SQLStorage<LiquidTypeEntry>                     sDBCLiquidType(LiquidTypefmt, "dbc_liquidtype");
SQLStorage<LockEntry>                           sDBCLock(Lockfmt, "dbc_lock");
SQLStorage<MailTemplateEntry>                   sDBCMailTemplate(MailTemplatefmt, "dbc_mailtemplate");
SQLStorage<MapEntry>                            sDBCMap(Mapfmt, "dbc_map");
SQLStorage<QuestSortEntry>                      sDBCQuestSort(QuestSortfmt, "dbc_questsort");
SQLStorage<RandomPropertiesPointsEntry>         sDBCRandPropPoints(RandPropPointsfmt, "dbc_randproppoints");
SQLStorage<SkillLineEntry>                      sDBCSkillLine(SkillLinefmt, "dbc_skillline");
SQLStorage<SkillLineAbilityEntry>               sDBCSkillLineAbility(SkillLineAbilityfmt, "dbc_skilllineability");
SQLStorage<SkillRaceClassInfoEntry>             sDBCSkillRaceClassInfo(SkillRaceClassInfofmt, "dbc_skillraceclassinfo");
SQLStorage<SkillTiersEntry>                     sDBCSkillTiers(SkillTiersfmt, "dbc_skilltiers");
SQLStorage<SoundEntriesEntry>                   sDBCSoundEntries(SoundEntriesfmt, "dbc_soundentries");
SQLStorage<SpellCastTimesEntry>                 sDBCSpellCastTimes(SpellCastTimesfmt, "dbc_spellcasttimes");
SQLStorage<SpellDurationEntry>                  sDBCSpellDuration(SpellDurationfmt, "dbc_spellduration");
SQLStorage<SpellFocusObjectEntry>               sDBCSpellFocusObject(SpellFocusObjectfmt, "dbc_spellfocusobject");
SQLStorage<SpellItemEnchantmentEntry>           sDBCSpellItemEnchantment(SpellItemEnchantmentfmt, "dbc_spellitemenchantment");
SQLStorage<SpellItemEnchantmentConditionEntry>  sDBCSpellItemEnchantmentCondition(SpellItemEnchantmentConditionfmt, "dbc_spellitemenchantmentcondition");
SQLStorage<SpellRadiusEntry>                    sDBCSpellRadius(SpellRadiusfmt, "dbc_spellradius");
SQLStorage<SpellRangeEntry>                     sDBCSpellRange(SpellRangefmt, "dbc_spellrange");
SQLStorage<SpellShapeshiftFormEntry>            sDBCSpellShapeshiftForm(SpellShapeshiftFormfmt, "dbc_spellshapeshiftform");
SQLStorage<SpellVisualEntry>                    sDBCSpellVisual(SpellVisualfmt, "dbc_spellvisual");
SQLStorage<StableSlotPricesEntry>               sDBCStableSlotPrices(StableSlotPricesfmt, "dbc_stableslotprices");
SQLStorage<SummonPropertiesEntry>               sDBCSummonProperties(SummonPropertiesfmt, "dbc_summonproperties");
SQLStorage<TalentEntry>                         sDBCTalent(Talentfmt, "dbc_talent");
SQLStorage<TalentTabEntry>                      sDBCTalentTab(TalentTabfmt, "dbc_talenttab");
SQLStorage<TaxiNodesEntry>                      sDBCTaxiNodes(TaxiNodesfmt, "dbc_taxinodes");
SQLStorage<TaxiPathEntry>                       sDBCTaxiPath(TaxiPathfmt, "dbc_taxipath");
SQLStorage<TaxiPathNodeEntry>                   sDBCTaxiPathNode(TaxiPathNodefmt, "dbc_taxipathnode");
SQLStorage<TransportAnimationEntry>             sDBCTransportAnimation(TransportAnimationfmt, "dbc_transportanimation");
SQLStorage<TotemCategoryEntry>                  sDBCTotemCategory(TotemCategoryfmt, "dbc_totemcategory");
SQLStorage<WorldMapAreaEntry>                   sDBCWorldMapArea(WorldMapAreafmt, "dbc_worldmaparea");
SQLStorage<WMOAreaTableEntry>                   sDBCWMOAreaTable(WMOAreaTablefmt, "dbc_wmoareatable");

AreaFlagByAreaID sAreaFlagByAreaID;
AreaFlagByMapID  sAreaFlagByMapID;                   // for instances without generated *.map files

WMOAreaInfoByTripple sWMOAreaInfoByTripple;

SpellCategoryStore sSpellCategoryStore;
ItemSpellCategoryStore sItemSpellCategoryStore;
PetFamilySpellsStore sPetFamilySpellsStore;

// store absolute bit position for first rank for talent inspect
TalentInspectMap sTalentPosInInspect;
TalentInspectMap sTalentTabSizeInInspect;
uint32 sTalentTabPages[12/*MAX_CLASSES*/][3];
TalentSpellPosMap sTalentSpellPosMap;

TaxiMask sTaxiNodesMask;
TaxiPathSetBySource sTaxiPathSetBySource;
TaxiPathNodesByPath sTaxiPathNodesByPath;// DBC store data but sTaxiPathNodesByPath used for fast access to entries (it's not owner pointed data).

void InitializeDBC()
{
    // must be after sAreaStore loading
    for (auto areaEntry : sDBCAreaTable)    // areaflag numbered from 0
    {
            // fill AreaId->DBC records
            sAreaFlagByAreaID.insert(AreaFlagByAreaID::value_type(uint16(areaEntry->ID), areaEntry->exploreFlag));

            // fill MapId->DBC records ( skip sub zones and continents )
            if (areaEntry->zone == 0 && areaEntry->mapid != 0 && areaEntry->mapid != 1 && areaEntry->mapid != 530)
                sAreaFlagByMapID.insert(AreaFlagByMapID::value_type(areaEntry->mapid, areaEntry->exploreFlag));
    }

    for (auto skillLine : sDBCSkillLineAbility)
    {
        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry(skillLine->spellId);
        if (spellInfo && (spellInfo->Attributes & (SPELL_ATTR_ABILITY | SPELL_ATTR_PASSIVE | SPELL_ATTR_HIDDEN_CLIENTSIDE | SPELL_ATTR_HIDE_IN_COMBAT_LOG)) == (SPELL_ATTR_ABILITY | SPELL_ATTR_PASSIVE | SPELL_ATTR_HIDDEN_CLIENTSIDE | SPELL_ATTR_HIDE_IN_COMBAT_LOG))
        {
            for (auto cFamily : sDBCCreatureFamily)
            {
                if (skillLine->skillId != cFamily->skillLine[0] && skillLine->skillId != cFamily->skillLine[1])
                    continue;

                sPetFamilySpellsStore[cFamily->ID].insert(spellInfo->Id);
            }
        }
    }

    // create talent spells set
    for (auto talentInfo : sDBCTalent)
    {
        for (int j = 0; j < 5; ++j)
            if (talentInfo->RankID[j])
                sTalentSpellPosMap[talentInfo->RankID[j]] = TalentSpellPos(talentInfo->TalentID, j);
    }

    // prepare fast data access to bit pos of talent ranks for use at inspecting
    {
        // fill table by amount of talent ranks and fill sTalentTabBitSizeInInspect
        // store in with (row,col,talent)->size key for correct sorting by (row,col)
        typedef std::map<uint32, uint32> TalentBitSize;
        TalentBitSize sTalentBitSize;
        for (auto talentInfo : sDBCTalent)
        {
            TalentTabEntry const* talentTabInfo = sDBCTalentTab.LookupEntry(talentInfo->TalentTab);
            if (!talentTabInfo)
                continue;

            // find talent rank
            uint32 curtalent_maxrank = 0;
            for (uint32 k = 5; k > 0; --k)
            {
                if (talentInfo->RankID[k - 1])
                {
                    curtalent_maxrank = k;
                    break;
                }
            }

            sTalentBitSize[(talentInfo->Row << 24) + (talentInfo->Col << 16) + talentInfo->TalentID] = curtalent_maxrank;
            sTalentTabSizeInInspect[talentInfo->TalentTab] += curtalent_maxrank;
        }

        // now have all max ranks (and then bit amount used for store talent ranks in inspect)
        for (auto talentTabInfo : sDBCTalentTab)
        {
            // prevent memory corruption; otherwise cls will become 12 below
            if ((talentTabInfo->ClassMask & CLASSMASK_ALL_PLAYABLE) == 0)
                continue;

            // store class talent tab pages
            uint32 cls = 1;
            for (uint32 m = 1; !(m & talentTabInfo->ClassMask) && cls < MAX_CLASSES; m <<= 1, ++cls) {}

            sTalentTabPages[cls][talentTabInfo->tabpage] = talentTabInfo->TalentTabID;

            // add total amount bits for first rank starting from talent tab first talent rank pos.
            uint32 pos = 0;
            for (TalentBitSize::iterator itr = sTalentBitSize.begin(); itr != sTalentBitSize.end(); ++itr)
            {
                uint32 talentId = itr->first & 0xFFFF;
                TalentEntry const* talentInfo = sDBCTalent.LookupEntry(talentId);
                if (!talentInfo)
                    continue;

                if (talentInfo->TalentTab != talentTabInfo->TalentTabID)
                    continue;

                sTalentPosInInspect[talentId] = pos;
                pos += itr->second;
            }
        }
    }

    for (auto entry : sDBCTaxiPath)
        sTaxiPathSetBySource[entry->from][entry->to] = TaxiPathBySourceAndDestination(entry->ID, entry->price);
    uint32 pathCount = sDBCTaxiPath.GetMaxEntry();

    std::vector<uint32> pathLength;
    pathLength.resize(pathCount);                           // 0 and some other indexes not used
    for (auto entry : sDBCTaxiPathNode)
    {
        if (pathLength[entry->path] < entry->index + 1)
            pathLength[entry->path] = entry->index + 1;
    }
    // Set path length
    sTaxiPathNodesByPath.resize(pathCount);                 // 0 and some other indexes not used
    for (uint32 i = 1; i < sTaxiPathNodesByPath.size(); ++i)
        sTaxiPathNodesByPath[i].resize(pathLength[i]);
    // fill data (pointers to sTaxiPathNodeStore elements
    for (auto entry : sDBCTaxiPathNode)
        sTaxiPathNodesByPath[entry->path].set(entry->index, entry);

    // Initialize global taxinodes mask
    // include existing nodes that have at least single not spell base (scripted) path
    {
        std::set<uint32> spellPaths;
        for (auto sInfo : sSpellTemplate)
            for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
                if (sInfo->Effect[j] == 123 /*SPELL_EFFECT_SEND_TAXI*/)
                    spellPaths.insert(sInfo->EffectMiscValue[j]);

        memset(sTaxiNodesMask, 0, sizeof(sTaxiNodesMask));
        for (auto node : sDBCTaxiNodes)
        {
            TaxiPathSetBySource::const_iterator src_i = sTaxiPathSetBySource.find(node->ID);
            if (src_i != sTaxiPathSetBySource.end() && !src_i->second.empty())
            {
                bool ok = false;
                for (const auto& dest_i : src_i->second)
                {
                    // not spell path
                    if (spellPaths.find(dest_i.second.ID) == spellPaths.end())
                    {
                        ok = true;
                        break;
                    }
                }

                if (!ok)
                    continue;
            }

            // valid taxi network node
            uint8  field = (uint8)((node->ID - 1) / 32);
            uint32 submask = 1 << ((node->ID - 1) % 32);
            sTaxiNodesMask[field] |= submask;
        }
    }

    for (auto entry : sDBCWMOAreaTable)
    {
        sWMOAreaInfoByTripple[WMOAreaTableTripple(entry->rootId, entry->adtId, entry->groupId)].push_back(entry);
    }

    // Check loaded DBC files proper version
    if (!sDBCSkillLineAbility.LookupEntry(17514) ||
        !sDBCMap.LookupEntry(598) ||
        !sDBCGemProperties.LookupEntry(1127) ||
        !sDBCItemExtendedCost.LookupEntry(2425) ||
        !sDBCCharTitles.LookupEntry(71) ||
        !sDBCAreaTable.LookupEntry(1768))
    {
        sLog.outError("\nYou have _outdated_ DBC files. Please re-extract DBC files for one from client build: %s", World::AcceptableClientBuildsListStr().c_str());
        Log::WaitBeforeContinueIfNeed();
        exit(1);
    }
}

void LoadDBCTables()
{
    sDBCAreaTable.Load();
    sDBCAreaTrigger.Load();
    sDBCAuctionHouse.Load();
    sDBCBankBagSlotPrices.Load();
    sDBCBattlemasterList.Load();
    sDBCCharStartOutfit.Load();
    sDBCCharTitles.Load();
    sDBCChatChannels.Load();
    sDBCChrClasses.Load();
    sDBCChrRaces.Load();
    sDBCCinematicCamera.Load();
    sDBCCinematicSequences.Load();
    sDBCCreatureDisplayInfo.Load();
    sDBCCreatureDisplayInfoExtra.Load();
    sDBCCreatureFamily.Load();
    sDBCCreatureModelData.Load();
    sDBCCreatureSpellData.Load();
    sDBCCreatureType.Load();
    sDBCDurabilityQuality.Load();
    sDBCDurabilityCosts.Load();
    sDBCEmotes.Load();
    sDBCEmotesText.Load();
    sDBCFactionTemplate.Load();
    sDBCGameObjectDisplayInfo.Load();
    sDBCGemProperties.Load();
    sDBCGMSurveyCurrentSurvey.Load();
    sDBCGMSurveyQuestions.Load();
    sDBCGMSurveySurveys.Load();
    sDBCGMTicketCategory.Load();
    sDBCgtCombatRatings.Load();
    sDBCgtChanceToMeleeCritBase.Load();
    sDBCgtChanceToMeleeCrit.Load();
    sDBCgtChanceToSpellCritBase.Load();
    sDBCgtChanceToSpellCrit.Load();
    sDBCgtOCTRegenHP.Load();
    sDBCgtNPCManaCostScaler.Load();
    sDBCgtRegenHPPerSpt.Load();
    sDBCgtRegenMPPerSpt.Load();
    sDBCItem.Load();
    sDBCItemBagFamily.Load();
    sDBCItemClass.Load();
    sDBCItemExtendedCost.Load();
    sDBCItemRandomProperties.Load();
    sDBCItemRandomSuffix.Load();
    sDBCItemSet.Load();
    sDBCLiquidType.Load();
    sDBCLock.Load();
    sDBCMailTemplate.Load();
    sDBCMap.Load();
    sDBCQuestSort.Load();
    sDBCRandPropPoints.Load();
    sDBCSkillLine.Load();
    sDBCSkillLineAbility.Load();
    sDBCSkillRaceClassInfo.Load();
    sDBCSkillTiers.Load();
    sDBCSoundEntries.Load();
    sDBCSpellCastTimes.Load();
    sDBCSpellDuration.Load();
    sDBCSpellFocusObject.Load();
    sDBCSpellItemEnchantment.Load();
    sDBCSpellItemEnchantmentCondition.Load();
    sDBCSpellRadius.Load();
    sDBCSpellRange.Load();
    sDBCSpellShapeshiftForm.Load();
    sDBCSpellVisual.Load();
    sDBCStableSlotPrices.Load();
    sDBCSummonProperties.Load();
    sDBCTalent.Load();
    sDBCTalentTab.Load();
    sDBCTaxiNodes.Load();
    sDBCTaxiPath.Load();
    sDBCTaxiPathNode.Load();
    sDBCTransportAnimation.Load();
    sDBCTotemCategory.Load();
    sDBCWorldMapArea.Load();
    sDBCWMOAreaTable.Load();

    InitializeDBC();

    sLog.outString(">> DBC loaded.");
    sLog.outString();
}


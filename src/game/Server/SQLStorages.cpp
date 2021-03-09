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

const char CreatureInfosrcfmt[] = "nsssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiss";
const char CreatureInfodstfmt[] = "nsssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiisi";
const char CreatureDataAddonInfofmt[] = "niibbiis";
const char CreatureConditionalSpawnSrcFmt[] = "niix";
const char CreatureConditionalSpawnDstFmt[] = "nii";
const char CreatureModelfmt[] = "nffffbii";
const char CreatureInfoAddonInfofmt[] = "niibbiis";
const char EquipmentInfofmt[] = "niii";
const char EquipmentInfoRawfmt[] = "niiiiiiiii";
const char GameObjectInfosrcfmt[] = "niisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiis";
const char GameObjectInfodstfmt[] = "niisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char ItemPrototypesrcfmt[] = "niiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifsiiiiii";
const char ItemPrototypedstfmt[] = "niiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiii";
const char PageTextfmt[] = "nsi";
const char InstanceTemplatesrcfmt[] = "niiiiisl";
const char InstanceTemplatedstfmt[] = "niiiiiil";
const char WorldTemplatesrcfmt[] = "ns";
const char WorldTemplatedstfmt[] = "ni";
const char ConditionsFmt[] = "niiiiiix";
const char SpellScriptTargetFmt[] = "niii";
const char SpellEntryfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiifffiiiissssssssssssssssssssssssssssssssiiiiiLiiiifffiiiiiiiii";
const char SpellConefmt[] = "ni";
const char DungeonEncounterFmt[] = "niiiissssssssssssssssii";
const char FactionEntryfmt[] = "niiiiiiiiiiiiiiiiiiffiissssssssssssssss";
const char WorldSafeLocsFmt[] = "niffffs";

SQLStorage<CreatureInfo>             sCreatureStorage(CreatureInfosrcfmt, CreatureInfodstfmt, "", "creature_template");
SQLStorage<CreatureDataAddon>        sCreatureDataAddonStorage(CreatureDataAddonInfofmt, "creature_addon");
SQLStorage<CreatureDataAddon>        sCreatureInfoAddonStorage(CreatureInfoAddonInfofmt, "creature_template_addon");
SQLStorage<CreatureModelInfo>        sCreatureModelStorage(CreatureModelfmt, "creature_model_info");
SQLStorage<EquipmentInfo>            sEquipmentStorage(EquipmentInfofmt, "creature_equip_template");
SQLStorage<EquipmentInfoRaw>         sEquipmentStorageRaw(EquipmentInfoRawfmt, "creature_equip_template_raw");
SQLStorage<PageText>                 sPageTextStore(PageTextfmt, "page_text");
SQLStorage<ItemPrototype>            sItemStorage(ItemPrototypesrcfmt, ItemPrototypedstfmt, "", "item_template");
SQLStorage<InstanceTemplate>         sInstanceTemplate(InstanceTemplatesrcfmt, InstanceTemplatedstfmt, "", "instance_template");
SQLStorage<WorldTemplate>            sWorldTemplate(WorldTemplatesrcfmt, WorldTemplatedstfmt, "", "world_template");
SQLStorage<ConditionEntry>           sConditionStorage(ConditionsFmt, "conditions");
SQLStorage<SpellEntry>               sSpellTemplate(SpellEntryfmt, "spell_template");
SQLStorage<SpellCone>                sSpellCones(SpellConefmt, "spell_cone");
SQLStorage<DungeonEncounterEntry>    sDungeonEncounterStore(DungeonEncounterFmt, "instance_dungeon_encounters");
SQLStorage<FactionEntry>             sFactionStore(FactionEntryfmt, "faction_store");
SQLStorage<CreatureConditionalSpawn> sCreatureConditionalSpawnStore(CreatureConditionalSpawnSrcFmt, CreatureConditionalSpawnDstFmt, "", "creature_conditional_spawn");
SQLStorage<WorldSafeLocsEntry>       sWorldSafeLocsStore(WorldSafeLocsFmt, "world_safe_locs");

SQLHashStorage<GameObjectInfo> sGOStorage(GameObjectInfosrcfmt, GameObjectInfodstfmt, "entry", "gameobject_template");

SQLMultiStorage<SpellTargetEntry> sSpellScriptTargetStorage(SpellScriptTargetFmt, "entry", "spell_script_target");

SQLStorage<SpellEntry> const* GetSpellStore() { return &sSpellTemplate; }


// DBC store in database
const char AreaTablefmt[]                     = "iiinixxxxxissssssssssssssssxiiiiixx";
const char AreaTriggerfmt[]                   = "niffffffff";
const char AuctionHousefmt[]                  = "niiixxxxxxxxxxxxxxxxx";
const char BankBagSlotPricesfmt[]             = "ni";
const char BattlemasterListfmt[]              = "niiiiiiiiiiiixxssssssssssssssssxx";
const char CharStartOutfitsrcfmt[]            = "dbbbbiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxx"; const char CharStartOutfitdstfmt[] = "diiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesfmt[]                    = "nxssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char ChatChannelsfmt[]                  = "nixssssssssssssssssxxxxxxxxxxxxxxxxxx";
const char ChrClassesfmt[]                    = "nxixssssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix";
const char ChrRacesfmt[]                      = "nxixiixxixxxxissssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxi";
const char CinematicCamerafmt[]               = "nsiffff";
const char CinematicSequencesfmt[]            = "nxixxxxxxx";
const char CreatureDisplayInfofmt[]           = "nixifxxxxxxxxx";
const char CreatureDisplayInfoExtrafmt[]      = "nixxxxxxxxxxxxxxxxxxx";
const char CreatureFamilyfmt[]                = "nfifiiiissssssssssssssssxx";
const char CreatureModelDatafmt[]             = "nixxfxxxxxxxxxxffxxxxxxx";
const char CreatureSpellDatafmt[]             = "niiiixxxx";
const char CreatureTypefmt[]                  = "nxxxxxxxxxxxxxxxxxx";
const char DurabilityCostsfmt[]               = "niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[]             = "nf";
const char Emotesfmt[]                        = "nxxiiix";
const char EmotesTextfmt[]                    = "nxixxxxxxxxxxxxxxxx";
const char FactionTemplatefmt[]               = "niiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[]         = "nsxxxxxxxxxxffffff";
const char GemPropertiesfmt[]                 = "nixxi";
const char GMSurveyCurrentSurveyfmt[]         = "ni";
const char GMSurveyQuestionsfmt[]             = "nssssssssssssssssx";
const char GMSurveySurveysfmt[]               = "niiiiiiiiii";
const char GMTicketCategoryfmt[]              = "nssssssssssssssssx";
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
const char ItemBagFamilyfmt[]                 = "nxxxxxxxxxxxxxxxxx";
const char ItemClassfmt[]                     = "nxxssssssssssssssssx";
const char ItemExtendedCostfmt[]              = "niiiiiiiiiiiii";
const char ItemRandomPropertiesfmt[]          = "nxiiixxssssssssssssssssx";
const char ItemRandomSuffixfmt[]              = "nssssssssssssssssxxiiiiii";
const char ItemSetfmt[]                       = "dssssssssssssssssxxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiii";
const char LiquidTypefmt[]                    = "niii";
const char Lockfmt[]                          = "niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char MailTemplatefmt[]                  = "nxxxxxxxxxxxxxxxxxssssssssssssssssx";
const char Mapfmt[]                           = "nxixssssssssssssssssxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiffiixxi";
const char QuestSortfmt[]                     = "nxxxxxxxxxxxxxxxxx";
const char RandPropPointsfmt[]                = "niiiiiiiiiiiiiii";
const char SkillLinefmt[]                     = "nixssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char SkillLineAbilityfmt[]              = "niiiixxiiiiixxi";
const char SkillRaceClassInfofmt[]            = "xiiiiiix";
const char SkillTiersfmt[]                    = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char SoundEntriesfmt[]                  = "nxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellCastTimesfmt[]                = "niii";
const char SpellDurationfmt[]                 = "niii";
const char SpellFocusObjectfmt[]              = "nxxxxxxxxxxxxxxxxx";
const char SpellItemEnchantmentfmt[]          = "niiiiiixxxiiissssssssssssssssxiiii";
const char SpellItemEnchantmentConditionfmt[] = "nbbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[]                   = "nfxx";
const char SpellRangefmt[]                    = "nffixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellShapeshiftFormfmt[]           = "nxxxxxxxxxxxxxxxxxxiixiixxxiiiiiiii";
const char SpellVisualfmt[]                   = "nxxxxxiixxxxxxxxxxxxxxxxx";
const char StableSlotPricesfmt[]              = "ni";
const char SummonPropertiesfmt[]              = "niiiii";
const char Talentfmt[]                        = "niiiiiiiixxxxixxixxxi";
const char TalentTabfmt[]                     = "nxxxxxxxxxxxxxxxxxxxiix";
const char TaxiNodesfmt[]                     = "nifffssssssssssssssssxii";
const char TaxiPathfmt[]                      = "niii";
const char TaxiPathNodefmt[]                  = "niiifffiiii";
const char TransportAnimationfmt[]            = "niifffx";
const char TotemCategoryfmt[]                 = "nxxxxxxxxxxxxxxxxxii";
const char WorldMapAreafmt[]                  = "diixffffi";
const char WMOAreaTablefmt[]                  = "niiixxxxxiixxxxxxxxxxxxxxxxx";

SQLStorage<AreaTableEntry>                      sDBCAreaTable(AreaTablefmt, "dbc_areatable");
SQLStorage<AreaTriggerEntry>                    sDBCAreaTrigger(AreaTriggerfmt, "dbc_areatrigger");
SQLStorage<AuctionHouseEntry>                   sDBCAuctionHouse(AuctionHousefmt, "dbc_auctionhouse");
SQLStorage<BankBagSlotPricesEntry>              sDBCBankBagSlotPrices(BankBagSlotPricesfmt, "dbc_bankbagslotprices");
SQLStorage<BattlemasterListEntry>               sDBCBattlemasterList(BattlemasterListfmt, "dbc_battlemasterlist");
SQLStorage<CharStartOutfitEntry>                sDBCCharStartOutfit(CharStartOutfitsrcfmt, CharStartOutfitdstfmt, "", "dbc_charstartoutfit");
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
    sDBCDurabilityCosts.Load();
    sDBCDurabilityQuality.Load();
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

int32 GetAreaFlagByAreaID(uint32 area_id)
{
    AreaFlagByAreaID::iterator i = sAreaFlagByAreaID.find(area_id);
    if (i == sAreaFlagByAreaID.end())
        return -1;

    return i->second;
}

uint32 GetAreaIdByLocalizedName(const std::string& name)
{
    for (auto areaEntry : sDBCAreaTable)
    {
        for (uint32 i = 0; i < MAX_LOCALE; ++i)
        {
            std::string area_name(areaEntry->area_name[i]);
            if (area_name.size() > 0 && name.find(" - " + area_name) != std::string::npos)
            {
                return areaEntry->ID;
            }
        }
    }
    return 0;
}

std::vector<WMOAreaTableEntry const*>& GetWMOAreaTableEntriesByTripple(int32 rootid, int32 adtid, int32 groupid)
{
    return sWMOAreaInfoByTripple[WMOAreaTableTripple(rootid, adtid, groupid)];
}

AreaTableEntry const* GetAreaEntryByAreaID(uint32 area_id)
{
    int32 areaflag = GetAreaFlagByAreaID(area_id);
    if (areaflag < 0)
        return nullptr;

    return sDBCAreaTable.LookupEntry(areaflag);
}

AreaTableEntry const* GetAreaEntryByAreaFlagAndMap(uint32 area_flag, uint32 map_id)
{
    if (area_flag)
        return sDBCAreaTable.LookupEntry(area_flag);

    if (MapEntry const* mapEntry = sMapStore.LookupEntry(map_id))
        return GetAreaEntryByAreaID(mapEntry->linked_zone);

    return nullptr;
}

uint32 GetAreaFlagByMapId(uint32 mapid)
{
    AreaFlagByMapID::iterator i = sAreaFlagByMapID.find(mapid);
    if (i == sAreaFlagByMapID.end())
        return 0;
    return i->second;
}

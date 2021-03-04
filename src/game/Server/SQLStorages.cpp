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

const char CreatureInfosrcfmt[] = "isssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiss";
const char CreatureInfodstfmt[] = "isssiiiiiiiifiiiiliiiiiffiiiiiiiiffffffiiiiffffiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiisi";
const char CreatureDataAddonInfofmt[] = "iiibbiis";
const char CreatureConditionalSpawnSrcFmt[] = "iiix";
const char CreatureConditionalSpawnDstFmt[] = "iii";
const char CreatureModelfmt[] = "iffffbii";
const char CreatureInfoAddonInfofmt[] = "iiibbiis";
const char EquipmentInfofmt[] = "iiii";
const char EquipmentInfoRawfmt[] = "iiiiiiiiii";
const char GameObjectInfosrcfmt[] = "iiisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiis";
const char GameObjectInfodstfmt[] = "iiisssiiifiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char ItemPrototypesrcfmt[] = "iiiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifsiiiiii";
const char ItemPrototypedstfmt[] = "iiiisiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffiffiffiffiffiiiiiiiiiifiiifiiiiiifiiiiiifiiiiiifiiiiiifiiiisiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiii";
const char PageTextfmt[] = "isi";
const char InstanceTemplatesrcfmt[] = "iiiiiisl";
const char InstanceTemplatedstfmt[] = "iiiiiiil";
const char WorldTemplatesrcfmt[] = "is";
const char WorldTemplatedstfmt[] = "ii";
const char ConditionsFmt[] = "iiiiiiix";
const char SpellScriptTargetFmt[] = "iiii";
const char SpellEntryfmt[] = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiifiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiffffffiiiiiiiiiiiiiiiiiiiiifffiiiiiiiiiiiiiiifffiiiissssssssssssssssssssssssssssssssiiiiiLiiiifffiiiiiiiii";
const char SpellConefmt[] = "ii";
const char DungeonEncounterFmt[] = "iiiiissssssssssssssssii";
const char FactionEntryfmt[] = "iiiiiiiiiiiiiiiiiiiffiissssssssssssssss";
const char WorldSafeLocsFmt[] = "iiffffs";

SQLStorage<CreatureInfo>             sCreatureStorage(CreatureInfosrcfmt, CreatureInfodstfmt, "Entry", "creature_template");
SQLStorage<CreatureDataAddon>        sCreatureDataAddonStorage(CreatureDataAddonInfofmt, "guid", "creature_addon");
SQLStorage<CreatureDataAddon>        sCreatureInfoAddonStorage(CreatureInfoAddonInfofmt, "entry", "creature_template_addon");
SQLStorage<CreatureModelInfo>        sCreatureModelStorage(CreatureModelfmt, "modelid", "creature_model_info");
SQLStorage<EquipmentInfo>            sEquipmentStorage(EquipmentInfofmt, "entry", "creature_equip_template");
SQLStorage<EquipmentInfoRaw>         sEquipmentStorageRaw(EquipmentInfoRawfmt, "entry", "creature_equip_template_raw");
SQLStorage<PageText>                 sPageTextStore(PageTextfmt, "entry", "page_text");
SQLStorage<ItemPrototype>            sItemStorage(ItemPrototypesrcfmt, ItemPrototypedstfmt, "entry", "item_template");
SQLStorage<InstanceTemplate>         sInstanceTemplate(InstanceTemplatesrcfmt, InstanceTemplatedstfmt, "map", "instance_template");
SQLStorage<WorldTemplate>            sWorldTemplate(WorldTemplatesrcfmt, WorldTemplatedstfmt, "map", "world_template");
SQLStorage<ConditionEntry>           sConditionStorage(ConditionsFmt, "condition_entry", "conditions");
SQLStorage<SpellEntry>               sSpellTemplate(SpellEntryfmt, "id", "spell_template");
SQLStorage<SpellCone>                sSpellCones(SpellConefmt, "id", "spell_cone");
SQLStorage<DungeonEncounterEntry>    sDungeonEncounterStore(DungeonEncounterFmt, "id", "instance_dungeon_encounters");
SQLStorage<FactionEntry>             sFactionStore(FactionEntryfmt, "entry", "faction_store");
SQLStorage<CreatureConditionalSpawn> sCreatureConditionalSpawnStore(CreatureConditionalSpawnSrcFmt, CreatureConditionalSpawnDstFmt, "guid", "creature_conditional_spawn");
SQLStorage<WorldSafeLocsEntry>       sWorldSafeLocsStore(WorldSafeLocsFmt, "id", "world_safe_locs");

SQLHashStorage sGOStorage(GameObjectInfosrcfmt, GameObjectInfodstfmt, "entry", "gameobject_template");

SQLMultiStorage sSpellScriptTargetStorage(SpellScriptTargetFmt, "entry", "spell_script_target");

SQLStorage<SpellEntry> const* GetSpellStore() { return &sSpellTemplate; }


// DBC store in database                         0123456789012345678901234567890123456789
const char AreaTablefmt[]                     = "iiiiixxxxxissssssssssssssssxiiiiixx";
const char AreaTriggerfmt[]                   = "iiffffffff";
const char AuctionHousefmt[]                  = "iiiixxxxxxxxxxxxxxxxx";
const char BankBagSlotPricesfmt[]             = "ii";
const char BattlemasterListfmt[]              = "iiiiiiiiiiiiixxssssssssssssssssxx";
const char CharStartOutfitsrcfmt[]            = "dbbbbiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxx"; const char CharStartOutfitdstfmt[] = "diiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesfmt[]                    = "ixssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char ChatChannelsfmt[]                  = "iixssssssssssssssssxxxxxxxxxxxxxxxxxx";
const char ChrClassesfmt[]                    = "ixixssssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix";
const char ChrRacesfmt[]                      = "ixixiixxixxxxissssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxi";
const char CinematicCamerafmt[]               = "isiffff";
const char CinematicSequencesfmt[]            = "ixixxxxxxx";
const char CreatureDisplayInfofmt[]           = "iixifxxxxxxxxx";
const char CreatureDisplayInfoExtrafmt[]      = "iixxxxxxxxxxxxxxxxxxx";
const char CreatureFamilyfmt[]                = "ififiiiissssssssssssssssxx";
const char CreatureModelDatafmt[]             = "iixxfxxxxxxxxxxffxxxxxxx";
const char CreatureSpellDatafmt[]             = "iiiiixxxx";
const char CreatureTypefmt[]                  = "ixxxxxxxxxxxxxxxxxx";
const char DurabilityCostsfmt[]               = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[]             = "if";
const char Emotesfmt[]                        = "ixxiiix";
const char EmotesTextfmt[]                    = "ixixxxxxxxxxxxxxxxx";
const char FactionTemplatefmt[]               = "iiiiiiiiiiiiii";
const char GameObjectDisplayInfofmt[]         = "isxxxxxxxxxxffffff";
const char GemPropertiesfmt[]                 = "iixxi";
const char GMSurveyCurrentSurveyfmt[]         = "ii";
const char GMSurveyQuestionsfmt[]             = "issssssssssssssssx";
const char GMSurveySurveysfmt[]               = "iiiiiiiiiii";
const char GMTicketCategoryfmt[]              = "issssssssssssssssx";
const char gtCombatRatingsfmt[]               = "f";
const char gtChanceToMeleeCritBasefmt[]       = "f";
const char gtChanceToMeleeCritfmt[]           = "f";
const char gtChanceToSpellCritBasefmt[]       = "f";
const char gtChanceToSpellCritfmt[]           = "f";
const char gtOCTRegenHPfmt[]                  = "f";
const char gtNPCManaCostScalerfmt[]           = "f";
const char gtRegenHPPerSptfmt[]               = "f";
const char gtRegenMPPerSptfmt[]               = "f";
const char Itemfmt[]                          = "iiii";
const char ItemBagFamilyfmt[]                 = "ixxxxxxxxxxxxxxxxx";
const char ItemClassfmt[]                     = "ixxssssssssssssssssx";
const char ItemExtendedCostfmt[]              = "iiiiiiiiiiiiii";
const char ItemRandomPropertiesfmt[]          = "ixiiixxssssssssssssssssx";
const char ItemRandomSuffixfmt[]              = "issssssssssssssssxxiiiiii";
const char ItemSetfmt[]                       = "xssssssssssssssssxxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiii";
const char LiquidTypefmt[]                    = "iiii";
const char Lockfmt[]                          = "iiiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char MailTemplatefmt[]                  = "ixxxxxxxxxxxxxxxxxssssssssssssssssx";
const char Mapfmt[]                           = "ixixssssssssssssssssxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiffiixxi";
const char QuestSortfmt[]                     = "ixxxxxxxxxxxxxxxxx";
const char RandPropPointsfmt[]                = "iiiiiiiiiiiiiiii";
const char SkillLinefmt[]                     = "iixssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char SkillLineAbilityfmt[]              = "iiiiixxiiiiixxi";
const char SkillRaceClassInfofmt[]            = "xiiiiiix";
const char SkillTiersfmt[]                    = "iiiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char SoundEntriesfmt[]                  = "ixxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellCastTimesfmt[]                = "iiii";
const char SpellDurationfmt[]                 = "iiii";
const char SpellFocusObjectfmt[]              = "ixxxxxxxxxxxxxxxxx";
const char SpellItemEnchantmentfmt[]          = "iiiiiiixxxiiissssssssssssssssxiiii";
const char SpellItemEnchantmentConditionfmt[] = "ibbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[]                   = "ifxx";
const char SpellRangefmt[]                    = "iffixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellShapeshiftFormfmt[]           = "ixxxxxxxxxxxxxxxxxxiixiixxxiiiiiiii";
const char SpellVisualfmt[]                   = "ixxxxxiixxxxxxxxxxxxxxxxx";
const char StableSlotPricesfmt[]              = "ii";
const char SummonPropertiesfmt[]              = "iiiiii";
const char Talentfmt[]                        = "iiiiiiiiixxxxixxixxxi";
const char TalentTabfmt[]                     = "ixxxxxxxxxxxxxxxxxxxiix";
const char TaxiNodesfmt[]                     = "iifffssssssssssssssssxii";
const char TaxiPathfmt[]                      = "iiii";
const char TaxiPathNodefmt[]                  = "xiiifffiiii";
const char TransportAnimationfmt[]            = "xiifffx";
const char TotemCategoryfmt[]                 = "ixxxxxxxxxxxxxxxxxii";
const char WorldMapAreafmt[]                  = "xiixffffi";
const char WMOAreaTablefmt[]                  = "iiiixxxxxiixxxxxxxxxxxxxxxxx";

SQLStorage<AreaTableEntry>                      sDBCAreaTable(AreaTablefmt, "ID", "dbc_areatable");
SQLStorage<AreaTriggerEntry>                    sDBCAreaTrigger(AreaTriggerfmt, "ID", "dbc_areatrigger");
SQLStorage<AuctionHouseEntry>                   sDBCAuctionHouse(AuctionHousefmt, "ID", "dbc_auctionhouse");
SQLStorage<BankBagSlotPricesEntry>              sDBCBankBagSlotPrices(BankBagSlotPricesfmt, "ID", "dbc_bankbagslotprices");
SQLStorage<BattlemasterListEntry>               sDBCBattlemasterList(BattlemasterListfmt, "ID", "dbc_battlemasterlist");
SQLStorage<CharStartOutfitEntry>                sDBCCharStartOutfit(CharStartOutfitsrcfmt, CharStartOutfitdstfmt, "ID", "dbc_charstartoutfit");
SQLStorage<CharTitlesEntry>                     sDBCCharTitles(CharTitlesfmt, "ID", "dbc_chartitles");
SQLStorage<ChatChannelsEntry>                   sDBCChatChannels(ChatChannelsfmt, "ID", "dbc_chatchannels");
SQLStorage<ChrClassesEntry>                     sDBCChrClasses(ChrClassesfmt, "ID", "dbc_chrclasses");
SQLStorage<ChrRacesEntry>                       sDBCChrRaces(ChrRacesfmt, "ID", "dbc_chrraces");
SQLStorage<CinematicCameraEntry>                sDBCCinematicCamera(CinematicCamerafmt, "ID", "dbc_cinematiccamera");
SQLStorage<CinematicSequencesEntry>             sDBCCinematicSequences(CinematicSequencesfmt, "ID", "dbc_cinematicsequences");
SQLStorage<CreatureDisplayInfoEntry>            sDBCCreatureDisplayInfo(CreatureDisplayInfofmt, "ID", "dbc_creaturedisplayinfo");
SQLStorage<CreatureDisplayInfoExtraEntry>       sDBCCreatureDisplayInfoExtra(CreatureDisplayInfoExtrafmt, "ID", "dbc_creaturedisplayinfoextra");
SQLStorage<CreatureFamilyEntry>                 sDBCCreatureFamily(CreatureFamilyfmt, "ID", "dbc_creaturefamily");
SQLStorage<CreatureModelDataEntry>              sDBCCreatureModelData(CreatureModelDatafmt, "ID", "dbc_creaturemodeldata");
SQLStorage<CreatureSpellDataEntry>              sDBCCreatureSpellData(CreatureSpellDatafmt, "ID", "dbc_creaturespelldata");
SQLStorage<CreatureTypeEntry>                   sDBCCreatureType(CreatureTypefmt, "ID", "dbc_creaturetype");
SQLStorage<DurabilityCostsEntry>                sDBCDurabilityCosts(DurabilityCostsfmt, "ID", "dbc_durabilitycosts");
SQLStorage<DurabilityQualityEntry>              sDBCDurabilityQuality(DurabilityQualityfmt, "ID", "dbc_durabilityquality");
SQLStorage<EmotesEntry>                         sDBCEmotes(Emotesfmt, "ID", "dbc_emotes");
SQLStorage<EmotesTextEntry>                     sDBCEmotesText(EmotesTextfmt, "ID", "dbc_emotestext");
SQLStorage<FactionTemplateEntry>                sDBCFactionTemplate(FactionTemplatefmt, "ID", "dbc_factiontemplate");
SQLStorage<GameObjectDisplayInfoEntry>          sDBCGameObjectDisplayInfo(GameObjectDisplayInfofmt, "ID", "dbc_gameobjectdisplayinfo");
SQLStorage<GemPropertiesEntry>                  sDBCGemProperties(GemPropertiesfmt, "ID", "dbc_gemproperties");
SQLStorage<GMSurveyCurrentSurveyEntry>          sDBCGMSurveyCurrentSurvey(GMSurveyCurrentSurveyfmt, "LANGID", "dbc_gmsurveycurrentsurvey");
SQLStorage<GMSurveyQuestionsEntry>              sDBCGMSurveyQuestions(GMSurveyQuestionsfmt, "ID", "dbc_gmsurveyquestions");
SQLStorage<GMSurveyEntry>                       sDBCGMSurveySurveys(GMSurveySurveysfmt, "ID", "dbc_gmsurveysurveys");
SQLStorage<GMTicketCategoryEntry>               sDBCGMTicketCategory(GMTicketCategoryfmt, "ID", "dbc_gmticketcategory");
SQLStorage<GtCombatRatingsEntry>                sDBCgtCombatRatings(gtCombatRatingsfmt, "Data", "dbc_gtcombatratings");
SQLStorage<GtChanceToMeleeCritBaseEntry>        sDBCgtChanceToMeleeCritBase(gtChanceToMeleeCritBasefmt, "Data", "dbc_gtchancetomeleecritbase");
SQLStorage<GtChanceToMeleeCritEntry>            sDBCgtChanceToMeleeCrit(gtChanceToMeleeCritfmt, "Data", "dbc_gtchancetomeleecrit");
SQLStorage<GtChanceToSpellCritBaseEntry>        sDBCgtChanceToSpellCritBase(gtChanceToSpellCritBasefmt, "Data", "dbc_gtchancetospellcritbase");
SQLStorage<GtChanceToSpellCritEntry>            sDBCgtChanceToSpellCrit(gtChanceToSpellCritfmt, "Data", "dbc_gtchancetospellcrit");
SQLStorage<GtOCTRegenHPEntry>                   sDBCgtOCTRegenHP(gtOCTRegenHPfmt, "Data", "dbc_gtoctregenhp");
SQLStorage<GtNPCManaCostScalerEntry>            sDBCgtNPCManaCostScaler(gtNPCManaCostScalerfmt, "Data", "dbc_gtnpcmanacostscaler");
SQLStorage<GtRegenHPPerSptEntry>                sDBCgtRegenHPPerSpt(gtRegenHPPerSptfmt, "Data", "dbc_gtregenhpperspt");
SQLStorage<GtRegenMPPerSptEntry>                sDBCgtRegenMPPerSpt(gtRegenMPPerSptfmt, "Data", "dbc_gtregenmpperspt");
SQLStorage<ItemEntry>                           sDBCItem(Itemfmt, "ID", "dbc_item");
SQLStorage<ItemBagFamilyEntry>                  sDBCItemBagFamily(ItemBagFamilyfmt, "ID", "dbc_itembagfamily");
SQLStorage<ItemClassEntry>                      sDBCItemClass(ItemClassfmt, "ClassID", "dbc_itemclass");
SQLStorage<ItemExtendedCostEntry>               sDBCItemExtendedCost(ItemExtendedCostfmt, "ID", "dbc_itemextendedcost");
SQLStorage<ItemRandomPropertiesEntry>           sDBCItemRandomProperties(ItemRandomPropertiesfmt, "ID", "dbc_itemrandomproperties");
SQLStorage<ItemRandomSuffixEntry>               sDBCItemRandomSuffix(ItemRandomSuffixfmt, "ID", "dbc_itemrandomsuffix");
SQLStorage<ItemSetEntry>                        sDBCItemSet(ItemSetfmt, "ID", "dbc_itemset");
SQLStorage<LiquidTypeEntry>                     sDBCLiquidType(LiquidTypefmt, "ID", "dbc_liquidtype");
SQLStorage<LockEntry>                           sDBCLock(Lockfmt, "ID", "dbc_lock");
SQLStorage<MailTemplateEntry>                   sDBCMailTemplate(MailTemplatefmt, "ID", "dbc_mailtemplate");
SQLStorage<MapEntry>                            sDBCMap(Mapfmt, "ID", "dbc_map");
SQLStorage<QuestSortEntry>                      sDBCQuestSort(QuestSortfmt, "ID", "dbc_questsort");
SQLStorage<RandomPropertiesPointsEntry>         sDBCRandPropPoints(RandPropPointsfmt, "ID", "dbc_randproppoints");
SQLStorage<SkillLineEntry>                      sDBCSkillLine(SkillLinefmt, "ID", "dbc_skillline");
SQLStorage<SkillLineAbilityEntry>               sDBCSkillLineAbility(SkillLineAbilityfmt, "ID", "dbc_skilllineability");
SQLStorage<SkillRaceClassInfoEntry>             sDBCSkillRaceClassInfo(SkillRaceClassInfofmt, "ID", "dbc_skillraceclassinfo");
SQLStorage<SkillTiersEntry>                     sDBCSkillTiers(SkillTiersfmt, "ID", "dbc_skilltiers");
SQLStorage<SoundEntriesEntry>                   sDBCSoundEntries(SoundEntriesfmt, "ID", "dbc_soundentries");
SQLStorage<SpellCastTimesEntry>                 sDBCSpellCastTimes(SpellCastTimesfmt, "ID", "dbc_spellcasttimes");
SQLStorage<SpellDurationEntry>                  sDBCSpellDuration(SpellDurationfmt, "ID", "dbc_spellduration");
SQLStorage<SpellFocusObjectEntry>               sDBCSpellFocusObject(SpellFocusObjectfmt, "ID", "dbc_spellfocusobject");
SQLStorage<SpellItemEnchantmentEntry>           sDBCSpellItemEnchantment(SpellItemEnchantmentfmt, "ID", "dbc_spellitemenchantment");
SQLStorage<SpellItemEnchantmentConditionEntry>  sDBCSpellItemEnchantmentCondition(SpellItemEnchantmentConditionfmt, "ID", "dbc_spellitemenchantmentcondition");
SQLStorage<SpellRadiusEntry>                    sDBCSpellRadius(SpellRadiusfmt, "ID", "dbc_spellradius");
SQLStorage<SpellRangeEntry>                     sDBCSpellRange(SpellRangefmt, "ID", "dbc_spellrange");
SQLStorage<SpellShapeshiftFormEntry>            sDBCSpellShapeshiftForm(SpellShapeshiftFormfmt, "ID", "dbc_spellshapeshiftform");
SQLStorage<SpellVisualEntry>                    sDBCSpellVisual(SpellVisualfmt, "ID", "dbc_spellvisual");
SQLStorage<StableSlotPricesEntry>               sDBCStableSlotPrices(StableSlotPricesfmt, "ID", "dbc_stableslotprices");
SQLStorage<SummonPropertiesEntry>               sDBCSummonProperties(SummonPropertiesfmt, "ID", "dbc_summonproperties");
SQLStorage<TalentEntry>                         sDBCTalent(Talentfmt, "ID", "dbc_talent");
SQLStorage<TalentTabEntry>                      sDBCTalentTab(TalentTabfmt, "ID", "dbc_talenttab");
SQLStorage<TaxiNodesEntry>                      sDBCTaxiNodes(TaxiNodesfmt, "ID", "dbc_taxinodes");
SQLStorage<TaxiPathEntry>                       sDBCTaxiPath(TaxiPathfmt, "ID", "dbc_taxipath");
SQLStorage<TaxiPathNodeEntry>                   sDBCTaxiPathNode(TaxiPathNodefmt, "ID", "dbc_taxipathnode");
SQLStorage<TransportAnimationEntry>             sDBCTransportAnimation(TransportAnimationfmt, "ID", "dbc_transportanimation");
SQLStorage<TotemCategoryEntry>                  sDBCTotemCategory(TotemCategoryfmt, "ID", "dbc_totemcategory");
SQLStorage<WorldMapAreaEntry>                   sDBCWorldMapArea(WorldMapAreafmt, "ID", "dbc_worldmaparea");
SQLStorage<WMOAreaTableEntry>                   sDBCWMOAreaTable(WMOAreaTablefmt, "ID", "dbc_wmoareatable");

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

    sLog.outString(">> DBC loaded.");
    sLog.outString();
}

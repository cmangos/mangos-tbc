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

SQLStorage<AreaTableEntry>                      sAreaTableStore(AreaTablefmt, "areatable_store");
SQLStorage<AreaTriggerEntry>                    sAreaTriggerStore(AreaTriggerfmt, "areatrigger_store");
SQLStorage<AuctionHouseEntry>                   sAuctionHouseStore(AuctionHousefmt, "auctionhouse_store");
SQLStorage<BankBagSlotPricesEntry>              sBankBagSlotPricesStore(BankBagSlotPricesfmt, "bankbagslotprices_store");
SQLStorage<BattlemasterListEntry>               sBattlemasterListStore(BattlemasterListfmt, "battlemasterlist_store");
SQLStorage<CharStartOutfitEntry>                sCharStartOutfitStore(CharStartOutfitfmt, "charstartoutfit_store");
SQLStorage<CharTitlesEntry>                     sCharTitlesStore(CharTitlesfmt, "chartitles_store");
SQLStorage<ChatChannelsEntry>                   sChatChannelsStore(ChatChannelsfmt, "chatchannels_store");
SQLStorage<ChrClassesEntry>                     sChrClassesStore(ChrClassesfmt, "chrclasses_store");
SQLStorage<ChrRacesEntry>                       sChrRacesStore(ChrRacesfmt, "chrraces_store");
SQLStorage<CinematicCameraEntry>                sCinematicCameraStore(CinematicCamerafmt, "cinematiccamera_store");
SQLStorage<CinematicSequencesEntry>             sCinematicSequencesStore(CinematicSequencesfmt, "cinematicsequences_store");
SQLStorage<CreatureDisplayInfoEntry>            sCreatureDisplayInfoStore(CreatureDisplayInfofmt, "creaturedisplayinfo_store");
SQLStorage<CreatureDisplayInfoExtraEntry>       sCreatureDisplayInfoExtraStore(CreatureDisplayInfoExtrafmt, "creaturedisplayinfoextra_store");
SQLStorage<CreatureFamilyEntry>                 sCreatureFamilyStore(CreatureFamilyfmt, "creaturefamily_store");
SQLStorage<CreatureModelDataEntry>              sCreatureModelDataStore(CreatureModelDatafmt, "creaturemodeldata_store");
SQLStorage<CreatureSpellDataEntry>              sCreatureSpellDataStore(CreatureSpellDatafmt, "creaturespelldata_store");
SQLStorage<CreatureTypeEntry>                   sCreatureTypeStore(CreatureTypefmt, "creaturetype_store");
SQLStorage<DurabilityCostsEntry>                sDurabilityCostsStore(DurabilityCostsfmt, "durabilitycosts_store");
SQLStorage<DurabilityQualityEntry>              sDurabilityQualityStore(DurabilityQualityfmt, "durabilityquality_store");
SQLStorage<EmotesEntry>                         sEmotesStore(Emotesfmt, "emotes_store");
SQLStorage<EmotesTextEntry>                     sEmotesTextStore(EmotesTextfmt, "emotestext_store");
SQLStorage<FactionTemplateEntry>                sFactionTemplateStore(FactionTemplatefmt, "factiontemplate_store");
SQLStorage<GameObjectDisplayInfoEntry>          sGameObjectDisplayInfoStore(GameObjectDisplayInfofmt, "gameobjectdisplayinfo_store");
SQLStorage<GemPropertiesEntry>                  sGemPropertiesStore(GemPropertiesfmt, "gemproperties_store");
SQLStorage<GMSurveyCurrentSurveyEntry>          sGMSurveyCurrentSurveyStore(GMSurveyCurrentSurveyfmt, "gmsurveycurrentsurvey_store");
SQLStorage<GMSurveyQuestionsEntry>              sGMSurveyQuestionsStore(GMSurveyQuestionsfmt, "gmsurveyquestions_store");
SQLStorage<GMSurveyEntry>                       sGMSurveySurveysStore(GMSurveySurveysfmt, "gmsurveysurveys_store");
SQLStorage<GMTicketCategoryEntry>               sGMTicketCategoryStore(GMTicketCategoryfmt, "gmticketcategory_store");
SQLStorage<GtCombatRatingsEntry>                sgtCombatRatingsStore(gtCombatRatingsfmt, "gtcombatratings_store");
SQLStorage<GtChanceToMeleeCritBaseEntry>        sgtChanceToMeleeCritBaseStore(gtChanceToMeleeCritBasefmt, "gtchancetomeleecritbase_store");
SQLStorage<GtChanceToMeleeCritEntry>            sgtChanceToMeleeCritStore(gtChanceToMeleeCritfmt, "gtchancetomeleecrit_store");
SQLStorage<GtChanceToSpellCritBaseEntry>        sgtChanceToSpellCritBaseStore(gtChanceToSpellCritBasefmt, "gtchancetospellcritbase_store");
SQLStorage<GtChanceToSpellCritEntry>            sgtChanceToSpellCritStore(gtChanceToSpellCritfmt, "gtchancetospellcrit_store");
SQLStorage<GtOCTRegenHPEntry>                   sgtOCTRegenHPStore(gtOCTRegenHPfmt, "gtoctregenhp_store");
SQLStorage<GtNPCManaCostScalerEntry>            sgtNPCManaCostScalerStore(gtNPCManaCostScalerfmt, "gtnpcmanacostscaler_store");
SQLStorage<GtRegenHPPerSptEntry>                sgtRegenHPPerSptStore(gtRegenHPPerSptfmt, "gtregenhpperspt_store");
SQLStorage<GtRegenMPPerSptEntry>                sgtRegenMPPerSptStore(gtRegenMPPerSptfmt, "gtregenmpperspt_store");
SQLStorage<ItemEntry>                           sItemStore(Itemfmt, "item_store");
SQLStorage<ItemBagFamilyEntry>                  sItemBagFamilyStore(ItemBagFamilyfmt, "itembagfamily_store");
SQLStorage<ItemClassEntry>                      sItemClassStore(ItemClassfmt, "itemclass_store");
SQLStorage<ItemExtendedCostEntry>               sItemExtendedCostStore(ItemExtendedCostfmt, "itemextendedcost_store");
SQLStorage<ItemRandomPropertiesEntry>           sItemRandomPropertiesStore(ItemRandomPropertiesfmt, "itemrandomproperties_store");
SQLStorage<ItemRandomSuffixEntry>               sItemRandomSuffixStore(ItemRandomSuffixfmt, "itemrandomsuffix_store");
SQLStorage<ItemSetEntry>                        sItemSetStore(ItemSetfmt, "itemset_store");
SQLStorage<LiquidTypeEntry>                     sLiquidTypeStore(LiquidTypefmt, "liquidtype_store");
SQLStorage<LockEntry>                           sLockStore(Lockfmt, "lock_store");
SQLStorage<MailTemplateEntry>                   sMailTemplateStore(MailTemplatefmt, "mailtemplate_store");
SQLStorage<MapEntry>                            sMapStore(Mapfmt, "map_store");
SQLStorage<QuestSortEntry>                      sQuestSortStore(QuestSortfmt, "questsort_store");
SQLStorage<RandomPropertiesPointsEntry>         sRandPropPointsStore(RandPropPointsfmt, "randproppoints_store");
SQLStorage<SkillLineEntry>                      sSkillLineStore(SkillLinefmt, "skillline_store");
SQLStorage<SkillLineAbilityEntry>               sSkillLineAbilityStore(SkillLineAbilityfmt, "skilllineability_store");
SQLStorage<SkillRaceClassInfoEntry>             sSkillRaceClassInfoStore(SkillRaceClassInfofmt, "skillraceclassinfo_store");
SQLStorage<SkillTiersEntry>                     sSkillTiersStore(SkillTiersfmt, "skilltiers_store");
SQLStorage<SoundEntriesEntry>                   sSoundEntriesStore(SoundEntriesfmt, "soundentries_store");
SQLStorage<SpellCastTimesEntry>                 sSpellCastTimesStore(SpellCastTimesfmt, "spellcasttimes_store");
SQLStorage<SpellDurationEntry>                  sSpellDurationStore(SpellDurationfmt, "spellduration_store");
SQLStorage<SpellFocusObjectEntry>               sSpellFocusObjectStore(SpellFocusObjectfmt, "spellfocusobject_store");
SQLStorage<SpellItemEnchantmentEntry>           sSpellItemEnchantmentStore(SpellItemEnchantmentfmt, "spellitemenchantment_store");
SQLStorage<SpellItemEnchantmentConditionEntry>  sSpellItemEnchantmentConditionStore(SpellItemEnchantmentConditionfmt, "spellitemenchantmentcondition_store");
SQLStorage<SpellRadiusEntry>                    sSpellRadiusStore(SpellRadiusfmt, "spellradius_store");
SQLStorage<SpellRangeEntry>                     sSpellRangeStore(SpellRangefmt, "spellrange_store");
SQLStorage<SpellShapeshiftFormEntry>            sSpellShapeshiftFormStore(SpellShapeshiftFormfmt, "spellshapeshiftform_store");
SQLStorage<SpellVisualEntry>                    sSpellVisualStore(SpellVisualfmt, "spellvisual_store");
SQLStorage<StableSlotPricesEntry>               sStableSlotPricesStore(StableSlotPricesfmt, "stableslotprices_store");
SQLStorage<SummonPropertiesEntry>               sSummonPropertiesStore(SummonPropertiesfmt, "summonproperties_store");
SQLStorage<TalentEntry>                         sTalentStore(Talentfmt, "talent_store");
SQLStorage<TalentTabEntry>                      sTalentTabStore(TalentTabfmt, "talenttab_store");
SQLStorage<TaxiNodesEntry>                      sTaxiNodesStore(TaxiNodesfmt, "taxinodes_store");
SQLStorage<TaxiPathEntry>                       sTaxiPathStore(TaxiPathfmt, "taxipath_store");
SQLStorage<TaxiPathNodeEntry>                   sTaxiPathNodeStore(TaxiPathNodefmt, "taxipathnode_store");
SQLStorage<TransportAnimationEntry>             sTransportAnimationStore(TransportAnimationfmt, "transportanimation_store");
SQLStorage<TotemCategoryEntry>                  sTotemCategoryStore(TotemCategoryfmt, "totemcategory_store");
SQLStorage<WorldMapAreaEntry>                   sWorldMapAreaStore(WorldMapAreafmt, "worldmaparea_store");
SQLStorage<WMOAreaTableEntry>                   sWMOAreaTableStore(WMOAreaTablefmt, "wmoareatable_store");

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
    for (auto areaEntry : sAreaTableStore)    // areaflag numbered from 0
    {
            // fill AreaId->DBC records
            sAreaFlagByAreaID.insert(AreaFlagByAreaID::value_type(uint16(areaEntry->ID), areaEntry->exploreFlag));

            // fill MapId->DBC records ( skip sub zones and continents )
            if (areaEntry->zone == 0 && areaEntry->mapid != 0 && areaEntry->mapid != 1 && areaEntry->mapid != 530)
                sAreaFlagByMapID.insert(AreaFlagByMapID::value_type(areaEntry->mapid, areaEntry->exploreFlag));
    }

    for (auto skillLine : sSkillLineAbilityStore)
    {
        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry(skillLine->spellId);
        if (spellInfo && (spellInfo->Attributes & (SPELL_ATTR_ABILITY | SPELL_ATTR_PASSIVE | SPELL_ATTR_HIDDEN_CLIENTSIDE | SPELL_ATTR_HIDE_IN_COMBAT_LOG)) == (SPELL_ATTR_ABILITY | SPELL_ATTR_PASSIVE | SPELL_ATTR_HIDDEN_CLIENTSIDE | SPELL_ATTR_HIDE_IN_COMBAT_LOG))
        {
            for (auto cFamily : sCreatureFamilyStore)
            {
                if (skillLine->skillId != cFamily->skillLine[0] && skillLine->skillId != cFamily->skillLine[1])
                    continue;

                sPetFamilySpellsStore[cFamily->ID].insert(spellInfo->Id);
            }
        }
    }

    // create talent spells set
    for (auto talentInfo : sTalentStore)
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
        for (auto talentInfo : sTalentStore)
        {
            TalentTabEntry const* talentTabInfo = sTalentTabStore.LookupEntry(talentInfo->TalentTab);
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
        for (auto talentTabInfo : sTalentTabStore)
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
                TalentEntry const* talentInfo = sTalentStore.LookupEntry(talentId);
                if (!talentInfo)
                    continue;

                if (talentInfo->TalentTab != talentTabInfo->TalentTabID)
                    continue;

                sTalentPosInInspect[talentId] = pos;
                pos += itr->second;
            }
        }
    }

    for (auto entry : sTaxiPathStore)
        sTaxiPathSetBySource[entry->from][entry->to] = TaxiPathBySourceAndDestination(entry->ID, entry->price);
    uint32 pathCount = sTaxiPathStore.GetMaxEntry();

    std::vector<uint32> pathLength;
    pathLength.resize(pathCount);                           // 0 and some other indexes not used
    for (auto entry : sTaxiPathNodeStore)
    {
        if (pathLength[entry->path] < entry->index + 1)
            pathLength[entry->path] = entry->index + 1;
    }
    // Set path length
    sTaxiPathNodesByPath.resize(pathCount);                 // 0 and some other indexes not used
    for (uint32 i = 1; i < sTaxiPathNodesByPath.size(); ++i)
        sTaxiPathNodesByPath[i].resize(pathLength[i]);
    // fill data (pointers to sTaxiPathNodeStore elements
    for (auto entry : sTaxiPathNodeStore)
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
        for (auto node : sTaxiNodesStore)
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

    for (auto entry : sWMOAreaTableStore)
    {
        sWMOAreaInfoByTripple[WMOAreaTableTripple(entry->rootId, entry->adtId, entry->groupId)].push_back(entry);
    }

    // Check loaded DBC files proper version
    if (!sSkillLineAbilityStore.LookupEntry(17514) ||
        !sMapStore.LookupEntry(598) ||
        !sGemPropertiesStore.LookupEntry(1127) ||
        !sItemExtendedCostStore.LookupEntry(2425) ||
        !sCharTitlesStore.LookupEntry(71) ||
        !sAreaTableStore.LookupEntry(1768))
    {
        sLog.outError("\nYou have _outdated_ DBC files. Please re-extract DBC files for one from client build: %s", World::AcceptableClientBuildsListStr().c_str());
        Log::WaitBeforeContinueIfNeed();
        exit(1);
    }
}

void LoadDBCTables()
{
    sAreaTableStore.Load();
    sAreaTriggerStore.Load();
    sAuctionHouseStore.Load();
    sBankBagSlotPricesStore.Load();
    sBattlemasterListStore.Load();
    sCharStartOutfitStore.Load();
    sCharTitlesStore.Load();
    sChatChannelsStore.Load();
    sChrClassesStore.Load();
    sChrRacesStore.Load();
    sCinematicCameraStore.Load();
    sCinematicSequencesStore.Load();
    sCreatureDisplayInfoStore.Load();
    sCreatureDisplayInfoExtraStore.Load();
    sCreatureFamilyStore.Load();
    sCreatureModelDataStore.Load();
    sCreatureSpellDataStore.Load();
    sCreatureTypeStore.Load();
    sDurabilityQualityStore.Load();
    sDurabilityCostsStore.Load();
    sEmotesStore.Load();
    sEmotesTextStore.Load();
    sFactionTemplateStore.Load();
    sGameObjectDisplayInfoStore.Load();
    sGemPropertiesStore.Load();
    sGMSurveyCurrentSurveyStore.Load();
    sGMSurveyQuestionsStore.Load();
    sGMSurveySurveysStore.Load();
    sGMTicketCategoryStore.Load();
    sgtCombatRatingsStore.Load();
    sgtChanceToMeleeCritBaseStore.Load();
    sgtChanceToMeleeCritStore.Load();
    sgtChanceToSpellCritBaseStore.Load();
    sgtChanceToSpellCritStore.Load();
    sgtOCTRegenHPStore.Load();
    sgtNPCManaCostScalerStore.Load();
    sgtRegenHPPerSptStore.Load();
    sgtRegenMPPerSptStore.Load();
    sItemStore.Load();
    sItemBagFamilyStore.Load();
    sItemClassStore.Load();
    sItemExtendedCostStore.Load();
    sItemRandomPropertiesStore.Load();
    sItemRandomSuffixStore.Load();
    sItemSetStore.Load();
    sLiquidTypeStore.Load();
    sLockStore.Load();
    sMailTemplateStore.Load();
    sMapStore.Load();
    sQuestSortStore.Load();
    sRandPropPointsStore.Load();
    sSkillLineStore.Load();
    sSkillLineAbilityStore.Load();
    sSkillRaceClassInfoStore.Load();
    sSkillTiersStore.Load();
    sSoundEntriesStore.Load();
    sSpellCastTimesStore.Load();
    sSpellDurationStore.Load();
    sSpellFocusObjectStore.Load();
    sSpellItemEnchantmentStore.Load();
    sSpellItemEnchantmentConditionStore.Load();
    sSpellRadiusStore.Load();
    sSpellRangeStore.Load();
    sSpellShapeshiftFormStore.Load();
    sSpellVisualStore.Load();
    sStableSlotPricesStore.Load();
    sSummonPropertiesStore.Load();
    sTalentStore.Load();
    sTalentTabStore.Load();
    sTaxiNodesStore.Load();
    sTaxiPathStore.Load();
    sTaxiPathNodeStore.Load();
    sTransportAnimationStore.Load();
    sTotemCategoryStore.Load();
    sWorldMapAreaStore.Load();
    sWMOAreaTableStore.Load();

    InitializeDBC();

    sLog.outString(">> DBC loaded.");
    sLog.outString();
}


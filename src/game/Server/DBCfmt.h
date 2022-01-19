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

#ifndef MANGOS_DBCSFRM_H
#define MANGOS_DBCSFRM_H

const char AreaTableEntryfmt[] = "iiinixxxxxissssssssssssssssxiiiiixx";
const char AreaTriggerEntryfmt[] = "niffffffff";
const char AuctionHouseEntryfmt[] = "niiixxxxxxxxxxxxxxxxx";
const char BankBagSlotPricesEntryfmt[] = "ni";
const char BattlemasterListEntryfmt[] = "niiiiiiiiiiiixxssssssssssssssssxx";
char const CharSectionsEntryfmt[] = "diiiiixxxi";
char const CharacterFacialHairStylesfmt[] = "iiixxxxxxxx";
const char CharStartOutfitEntryfmt[] = "diiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxxxx";
// 3*12 new item fields in 3.0.x
// const char CharStartOutfitEntryfmt[]="diiiiiiiiiiiiiiiiiiiiiiiiixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char CharTitlesEntryfmt[] = "nxssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char ChatChannelsEntryfmt[] = "iixssssssssssssssssxxxxxxxxxxxxxxxxxx";
// ChatChannelsEntryfmt, index not used (more compact store)
const char ChrClassesEntryfmt[] = "nxixssssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxix";
const char ChrRacesEntryfmt[] = "nxixiixxixxxxissssssssssssssssxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxi";
const char CinematicCameraEntryfmt[] = "nsiffff";
const char CinematicSequencesEntryfmt[] = "nxixxxxxxx";
const char CreatureDisplayInfofmt[] = "nixifxxxxxxxxx";
const char CreatureDisplayInfoExtrafmt[] = "nixxxxxxxxxxxxxxxxxxx";
const char CreatureFamilyfmt[] = "nfifiiiissssssssssssssssxx";
const char CreatureModelDatafmt[] = "nixxfxxxxxxxxxfffxxxxxxx";
const char CreatureSpellDatafmt[] = "niiiixxxx";
const char CreatureTypefmt[] = "nxxxxxxxxxxxxxxxxxx";
const char DurabilityCostsfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char DurabilityQualityfmt[] = "nf";
const char EmotesEntryfmt[] = "nxxiiix";
const char EmotesTextEntryfmt[] = "nxixxxxxxxxxxxxxxxx";
#ifdef ENABLE_PLAYERBOTS
char const EmotesTextSoundEntryfmt[] = "niiii";
#endif
// const char FactionEntryfmt[] = "niiiiiiiiiiiiiiiiiissssssssssssssssxxxxxxxxxxxxxxxxxx";
const char FactionTemplateEntryfmt[] = "niiiiiiiiiiiii";
const char GameObjectArtKitfmt[] = "nxxxxxxx";
const char GameObjectDisplayInfofmt[] = "nsxxxxxxxxxxffffff";
const char GMSurveyCurrentSurveyfmt[] = "ni";
const char GMSurveySurveysfmt[] = "niiiiiiiiii";
const char GMSurveyQuestionsfmt[] = "nssssssssssssssssx";
const char GMTicketCategoryfmt[] = "nssssssssssssssssx";
const char GemPropertiesEntryfmt[] = "nixxi";
const char GtCombatRatingsfmt[] = "f";
const char GtChanceToMeleeCritBasefmt[] = "f";
const char GtChanceToMeleeCritfmt[] = "f";
const char GtChanceToSpellCritBasefmt[] = "f";
const char GtChanceToSpellCritfmt[] = "f";
const char GtOCTRegenHPfmt[] = "f";
const char GtNPCManaCostScalerfmt[] = "f";
// const char GtOCTRegenMPfmt[]="f";
const char GtRegenHPPerSptfmt[] = "f";
const char GtRegenMPPerSptfmt[] = "f";
const char Itemfmt[] = "niii";
const char ItemBagFamilyfmt[] = "nxxxxxxxxxxxxxxxxx";
const char ItemClassfmt[] = "nxxssssssssssssssssx";
// const char ItemDisplayTemplateEntryfmt[]="nxxxxxxxxxxixxxxxxxxxxx";
// const char ItemCondExtCostsEntryfmt[]="xiii";
const char ItemExtendedCostEntryfmt[] = "niiiiiiiiiiiii";
const char ItemRandomPropertiesfmt[] = "nxiiixxssssssssssssssssx";
const char ItemRandomSuffixfmt[] = "nssssssssssssssssxxiiiiii";
const char ItemSetEntryfmt[] = "dssssssssssssssssxxxxxxxxxxxxxxxxxxiiiiiiiiiiiiiiiiii";
const char LFGDungeonEntryfmt[] = "nssssssssssssssssxiiiixx";
const char LiquidTypefmt[] = "niii";
const char LightEntryfmt[] = "nifffxxxxxxx";
const char LockEntryfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiixxxxxxxx";
const char MailTemplateEntryfmt[] = "nxxxxxxxxxxxxxxxxxssssssssssssssssx";
const char MapEntryfmt[] = "nxixssssssssssssssssxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxiffiixxi";
const char QuestSortEntryfmt[] = "nxxxxxxxxxxxxxxxxx";
const char RandomPropertiesPointsfmt[] = "niiiiiiiiiiiiiii";
const char SkillLinefmt[] = "nixssssssssssssssssxxxxxxxxxxxxxxxxxxi";
const char SkillLineAbilityfmt[] = "niiiixxiiiiixxi";
const char SkillRaceClassInfofmt[] = "diiiiiix";
const char SkillTiersfmt[] = "niiiiiiiiiiiiiiiiiiiiiiiiiiiiiiii";
const char SoundEntriesfmt[] = "nxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellCastTimefmt[] = "niii";
const char SpellDurationfmt[] = "niii";
const char SpellFocusObjectfmt[] = "nxxxxxxxxxxxxxxxxx";
const char SpellItemEnchantmentfmt[] = "niiiiiixxxiiissssssssssssssssxiiii";
const char SpellItemEnchantmentConditionfmt[] = "nbbbbbxxxxxbbbbbbbbbbiiiiiXXXXX";
const char SpellRadiusfmt[] = "nfxx";
const char SpellRangefmt[] = "nffixxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx";
const char SpellShapeshiftfmt[] = "nxxxxxxxxxxxxxxxxxxiixiixxxiiiiiiii";
const char SpellVisualfmt[] = "nxxxxxiixxxxxxxxxxxxxxxxx"; // wotlk - "nxxxxxxiixxxxxxxxxxxxxxxxxxxxxxx"
const char StableSlotPricesfmt[] = "ni";
const char SummonPropertiesfmt[] = "niiiii";
const char TalentEntryfmt[] = "niiiiiiiixxxxixxixxxi";
const char TalentTabEntryfmt[] = "nxxxxxxxxxxxxxxxxxxxiix";
const char TaxiNodesEntryfmt[] = "nifffssssssssssssssssxii";
const char TaxiPathEntryfmt[] = "niii";
const char TaxiPathNodeEntryfmt[] = "diiifffiiii";
const char TransportAnimationfmt[] = "diifffx";
const char TotemCategoryEntryfmt[] = "nxxxxxxxxxxxxxxxxxii";
const char WMOAreaTableEntryfmt[] = "niiixxxxxiissssssssssssssssx";
const char WorldMapAreaEntryfmt[] = "xinxffffi";
// const char WorldMapOverlayEntryfmt[]="nxiiiixxxxxxxxxxx";
const char WorldSafeLocsEntryfmt[] = "nifffxxxxxxxxxxxxxxxxx";

#endif

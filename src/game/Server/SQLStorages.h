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

extern SQLStorage sCreatureStorage;
extern SQLStorage sCreatureDataAddonStorage;
extern SQLStorage sCreatureInfoAddonStorage;
extern SQLStorage sCreatureModelStorage;
extern SQLStorage sEquipmentStorage;
extern SQLStorage sEquipmentStorageRaw;
extern SQLStorage sPageTextStore;
extern SQLStorage sItemStorage;
extern SQLStorage sInstanceTemplate;
extern SQLStorage sWorldTemplate;
extern SQLStorage sConditionStorage;
extern SQLStorage sSpellTemplate;
extern SQLStorage sSpellCones;
extern SQLStorage sDungeonEncounterStore;
extern SQLStorage sFactionStore;
extern SQLStorage sCreatureConditionalSpawnStore;
extern SQLStorage sWorldSafeLocsStore;


extern SQLHashStorage sGOStorage;

extern SQLMultiStorage sSpellScriptTargetStorage;


// DBC stores in db
extern SQLStorage sDBCAreaTable;
extern SQLStorage sDBCAreaTrigger;
extern SQLStorage sDBCAuctionHouse;
extern SQLStorage sDBCBankBagSlotPrices;
extern SQLStorage sDBCBattlemasterList;
extern SQLStorage sDBCCharStartOutfit;
extern SQLStorage sDBCCharTitles;
extern SQLStorage sDBCChatChannels;
extern SQLStorage sDBCChrClasses;
extern SQLStorage sDBCChrRaces;
extern SQLStorage sDBCCinematicCamera;
extern SQLStorage sDBCCinematicSequences;
extern SQLStorage sDBCCreatureDisplayInfo;
extern SQLStorage sDBCCreatureDisplayInfoExtra;
extern SQLStorage sDBCCreatureFamily;
extern SQLStorage sDBCCreatureModelData;
extern SQLStorage sDBCCreatureSpellData;
extern SQLStorage sDBCCreatureType;
extern SQLStorage sDBCDurabilityCosts;
extern SQLStorage sDBCDurabilityQuality;
extern SQLStorage sDBCEmotes;
extern SQLStorage sDBCEmotesText;
extern SQLStorage sDBCFactionTemplate;
extern SQLStorage sDBCGameObjectDisplayInfo;
extern SQLStorage sDBCGemProperties;
extern SQLStorage sDBCGMSurveyCurrentSurvey;
extern SQLStorage sDBCGMSurveyQuestions;
extern SQLStorage sDBCGMSurveySurveys;
extern SQLStorage sDBCGMTicketCategory;
extern SQLStorage sDBCgtCombatRatings;
extern SQLStorage sDBCgtChanceToMeleeCritBase;
extern SQLStorage sDBCgtChanceToMeleeCrit;
extern SQLStorage sDBCgtChanceToSpellCritBase;
extern SQLStorage sDBCgtChanceToSpellCrit;
extern SQLStorage sDBCgtOCTRegenHP;
extern SQLStorage sDBCgtNPCManaCostScaler;
extern SQLStorage sDBCgtRegenHPPerSpt;
extern SQLStorage sDBCgtRegenMPPerSpt;
extern SQLStorage sDBCItem;
extern SQLStorage sDBCItemBagFamily;
extern SQLStorage sDBCItemClass;
extern SQLStorage sDBCItemExtendedCost;
extern SQLStorage sDBCItemRandomProperties;
extern SQLStorage sDBCItemRandomSuffix;
extern SQLStorage sDBCItemSet;
extern SQLStorage sDBCLiquidType;
extern SQLStorage sDBCLock;
extern SQLStorage sDBCMailTemplate;
extern SQLStorage sDBCMap;
extern SQLStorage sDBCQuestSort;
extern SQLStorage sDBCRandPropPoints;
extern SQLStorage sDBCSkillLine;
extern SQLStorage sDBCSkillLineAbility;
extern SQLStorage sDBCSkillRaceClassInfo;
extern SQLStorage sDBCSkillTiers;
extern SQLStorage sDBCSoundEntries;
extern SQLStorage sDBCSpellCastTimes;
extern SQLStorage sDBCSpellDuration;
extern SQLStorage sDBCSpellFocusObject;
extern SQLStorage sDBCSpellItemEnchantment;
extern SQLStorage sDBCSpellItemEnchantmentCondition;
extern SQLStorage sDBCSpellRadius;
extern SQLStorage sDBCSpellRange;
extern SQLStorage sDBCSpellShapeshiftForm;
extern SQLStorage sDBCSpellVisual;
extern SQLStorage sDBCStableSlotPrices;
extern SQLStorage sDBCSummonProperties;
extern SQLStorage sDBCTalent;
extern SQLStorage sDBCTalentTab;
extern SQLStorage sDBCTaxiNodes;
extern SQLStorage sDBCTaxiPath;
extern SQLStorage sDBCTaxiPathNode;
extern SQLStorage sDBCTransportAnimation;
extern SQLStorage sDBCTotemCategory;
extern SQLStorage sDBCWorldMapArea;
extern SQLStorage sDBCWMOAreaTable;

void LoadDBCTables();



SQLStorage                 const* GetSpellStore();

#endif

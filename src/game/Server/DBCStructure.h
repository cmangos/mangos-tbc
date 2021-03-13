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

#ifndef MANGOS_DBCSTRUCTURE_H
#define MANGOS_DBCSTRUCTURE_H

#include "Server/DBCEnums.h"
#include "MotionGenerators/Path.h"
#include "Platform/Define.h"
#include "Globals/SharedDefines.h"
#include "Entities/ObjectVisibilityDefines.h"
#include "Globals/Conditions.h"

#include <map>
#include <set>
#include <vector>
#include "Util.h"
#include "Entities/ObjectGuid.h"
#include "Entities/ItemPrototype.h"

// Structures using to access raw DBC data and required packing to portability

// GCC have alternative #pragma pack(N) syntax and old gcc version not support pack(push,N), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack(1)
#else
#pragma pack(push,1)
#endif

struct AreaTableEntry
{
    uint32  ID;                                             // 0        m_ID
    uint32  mapid;                                          // 1        m_ContinentID
    uint32  zone;                                           // 2        m_ParentAreaID
    uint32  exploreFlag;                                    // 3        m_AreaBit
    uint32  flags;                                          // 4        m_flags
    // 5        m_SoundProviderPref
    // 6        m_SoundProviderPrefUnderwater
    // 7        m_AmbienceID
    // 8        m_ZoneMusic
    // 9        m_IntroSound
    int32   area_level;                                     // 10       m_ExplorationLevel
    char*   area_name[16];                                  // 11-26    m_AreaName_lang
    // 27 string flags
    uint32  team;                                           // 28       m_factionGroupMask
    uint32  LiquidTypeOverride[4];                          // 29-32    m_liquidTypeID[4]
    // 33       m_minElevation
    // 34       m_ambient_multiplier
};

struct AreaTriggerEntry
{
    uint32    id;                                           // 0
    uint32    mapid;                                        // 1
    float     x;                                            // 2
    float     y;                                            // 3
    float     z;                                            // 4
    float     radius;                                       // 5
    float     box_x;                                        // 6 extent x edge
    float     box_y;                                        // 7 extent y edge
    float     box_z;                                        // 8 extent z edge
    float     box_orientation;                              // 9 extent rotation by about z axis
};

struct AuctionHouseEntry
{
    uint32    houseId;                                      // 0        m_ID
    uint32    faction;                                      // 1        m_factionID
    uint32    depositPercent;                               // 2        m_depositRate
    uint32    cutPercent;                                   // 3        m_consignmentRate
    // char*     name[16];                                  // 4-19     m_name_lang
    // 20 string flags
};

struct BankBagSlotPricesEntry
{
    uint32  ID;                                             // 0        m_ID
    uint32  price;                                          // 1        m_Cost
};

struct BattlemasterListEntry
{
    uint32  id;                                             // 0        m_ID
    int32   mapid[8];                                       // 1-8      m_mapID[8]
    uint32  type;                                           // 9        m_instanceType
    uint32  minLevel;                                       // 10       m_minlevel
    uint32  maxLevel;                                       // 11       m_maxlevel
    uint32  maxplayersperteam;                              // 12
    // 13-14 unused
    char*       name[16];                                   // 15-30    m_name_lang
    // 31 string flags
    // 32 unused
};

/*struct Cfg_CategoriesEntry
{
    uint32 Index;                                           //          m_ID categoryId (sent in RealmList packet)
    uint32 Unk1;                                            //          m_localeMask
    uint32 Unk2;                                            //          m_charsetMask
    uint32 IsTournamentRealm;                               //          m_flags
    char *categoryName[16];                                 //          m_name_lang
    uint32 categoryNameFlags;
}*/

/*struct Cfg_ConfigsEntry
{
    uint32 Id;                                              //          m_ID
    uint32 Type;                                            //          m_realmType (sent in RealmList packet)
    uint32 IsPvp;                                           //          m_playerKillingAllowed
    uint32 IsRp;                                            //          m_roleplaying
};*/

#define MAX_OUTFIT_ITEMS 12
// #define MAX_OUTFIT_ITEMS 24                              // 12->24 in 3.0.x

struct CharStartOutfitEntry
{
    // uint32 Id;                                           // 0        m_ID
    uint32 RaceClassGender;                                 // 1        m_raceID m_classID m_sexID m_outfitID (UNIT_FIELD_BYTES_0 & 0x00FFFFFF) comparable (0 byte = race, 1 byte = class, 2 byte = gender)
    int32 ItemId[MAX_OUTFIT_ITEMS];                         // 2-13     m_ItemID
    // int32 ItemDisplayId[MAX_OUTFIT_ITEMS];               // 14-25    m_DisplayItemID not required at server side
    // int32 ItemInventorySlot[MAX_OUTFIT_ITEMS];           // 26-37    m_InventoryType not required at server side
    // uint32 Unknown1;                                     // 38, unique values (index-like with gaps ordered in other way as ids)
    // uint32 Unknown2;                                     // 39
    // uint32 Unknown3;                                     // 40
};

struct CharTitlesEntry
{
    uint32  ID;                                             // 0,       m_ID
    // uint32      unk1;                                    // 1        m_Condition_ID
    char*   name[16];                                       // 2-17     m_name_lang
    // 18 string flags
    // char*       name2[16];                               // 19-34    m_name1_lang
    // 35 string flags
    uint32  bit_index;                                      // 36       m_mask_ID used in PLAYER_CHOSEN_TITLE and 1<<index in PLAYER__FIELD_KNOWN_TITLES
};

struct ChatChannelsEntry
{
    uint32  ChannelID;                                      // 0        m_ID
    uint32  flags;                                          // 1        m_flags
    // 2        m_factionGroup
    char*   pattern[16];                                    // 3-18     m_name_lang
    // 19 string flags
    // char*       name[16];                                // 20-35    m_shortcut_lang
    // 36 string flags
};

struct ChrClassesEntry
{
    uint32  ClassID;                                        // 0        m_ID
    // uint32 flags;                                        // 1 unknown
    uint32  powerType;                                      // 2        m_DisplayPower
    // 3        m_petNameToken
    char const* name[16];                                   // 4-19     m_name_lang
    // 20 string flags
    // char*       nameFemale[16];                          // 21-36    m_name_female_lang
    // 37 string flags
    // char*       nameNeutralGender[16];                   // 38-53    m_name_male_lang
    // 54 string flags
    // 55       m_filename
    uint32  spellfamily;                                    // 56       m_spellClassSet
    // uint32 flags2;                                       // 57       m_flags (0x08 HasRelicSlot)
};

struct ChrRacesEntry
{
    uint32      RaceID;                                     // 0        m_ID
    // 1        m_flags
    uint32      FactionID;                                  // 2        m_factionID
    // 3        m_ExplorationSoundID
    uint32      model_m;                                    // 4        m_MaleDisplayId
    uint32      model_f;                                    // 5        m_FemaleDisplayId
    // 6        m_ClientPrefix
    // 7        unused
    uint32      TeamID;                                     // 8        m_BaseLanguage (7-Alliance 1-Horde)
    // 9        m_creatureType
    // 10       m_ResSicknessSpellID
    // 11       m_SplashSoundID
    // 12       m_clientFileString
    uint32      CinematicSequence;                          // 13       m_cinematicSequenceID
    char*       name[16];                                   // 14-29    m_name_lang used for DBC language detection/selection
    // 30 string flags
    // char*       nameFemale[16];                          // 31-46    m_name_female_lang
    // 47 string flags
    // char*       nameNeutralGender[16];                   // 48-63    m_name_male_lang
    // 64 string flags
    // 65-66    m_facialHairCustomization[2]
    // 67       m_hairCustomization
    uint32      expansion;                                  // 68       m_required_expansion
};

struct CinematicCameraEntry
{
    uint32 ID;                                               // 0
    char const* Model;                                       // 1    Model filename (translate .mdx to .m2)
    uint32 SoundID;                                          // 2    Sound ID       (voiceover for cinematic)
    DBCPosition3D Origin;                                    // 3-5  Position in map used for basis for M2 co-ordinates
    float OriginFacing;                                      // 4    Orientation in map used for basis for M2 co-ordinates
};

struct CinematicSequencesEntry
{
    uint32      Id;                                         // 0        m_ID
    // uint32      unk1;                                    // 1        m_soundID
    uint32      cinematicCamera;                            // 2        m_camera[8]
};

struct CreatureDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
    uint32      ModelId;                                    // 1
    // 2        m_soundID
    uint32      ExtendedDisplayInfoID;                      // 3        m_extendedDisplayInfoID -> CreatureDisplayInfoExtraEntry::DisplayExtraId
    float       scale;                                      // 4        m_creatureModelScale
    // 5        m_creatureModelAlpha
    // 6-8      m_textureVariation[3]
    // 9        m_portraitTextureName
    // 10       m_sizeClass
    // 11       m_bloodID
    // 12       m_NPCSoundID
    // 13       m_particleColorID
};

struct CreatureDisplayInfoExtraEntry
{
    uint32      DisplayExtraId;                             // 0        m_ID CreatureDisplayInfoEntry::m_extendedDisplayInfoID
    uint32      Race;                                       // 1        m_DisplayRaceID
    // uint32    Gender;                                    // 2        m_DisplaySexID
    // uint32    SkinColor;                                 // 3        m_SkinID
    // uint32    FaceType;                                  // 4        m_FaceID
    // uint32    HairType;                                  // 5        m_HairStyleID
    // uint32    HairStyle;                                 // 6        m_HairColorID
    // uint32    BeardStyle;                                // 7        m_FacialHairID
    // uint32    Equipment[11];                             // 8-18     m_NPCItemDisplay equipped static items EQUIPMENT_SLOT_HEAD..EQUIPMENT_SLOT_HANDS, client show its by self
    // uint32    CanEquip;                                  // 19       m_flags 0..1 Can equip additional things when used for players
    // char*                                                // 20       m_BakeName CreatureDisplayExtra-*.blp
};

struct CreatureFamilyEntry
{
    uint32    ID;                                           // 0
    float     minScale;                                     // 1
    uint32    minScaleLevel;                                // 2 0/1
    float     maxScale;                                     // 3
    uint32    maxScaleLevel;                                // 4 0/60
    uint32    skillLine[2];                                 // 5-6
    uint32    petFoodMask;                                  // 7
    char*     Name[16];                                     // 8-23
    // 24 string flags, unused
    // 25 icon, unused
};

struct CreatureModelDataEntry
{
    uint32 Id;
    uint32 Flags;
    //char* ModelPath;
    //uint32 Unk1;
    float Scale;                                             // Used in calculation of unit collision data
    //int32 Unk2
    //int32 Unk3
    //uint32 Unk4
    //uint32 Unk5
    //float Unk6
    //uint32 Unk7
    //float Unk8
    //uint32 Unk9
    //uint32 Unk10
    //float CollisionWidth;
    float CollisionHeight;
    float MountHeight;                                       // Used in calculation of unit collision data when mounted
    //float Unks[7] wotlk has 11
};

#define MAX_CREATURE_SPELL_DATA_SLOT 4

struct CreatureSpellDataEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    spellId[MAX_CREATURE_SPELL_DATA_SLOT];        // 1-4      m_spells[4]
    // uint32    availability[MAX_CREATURE_SPELL_DATA_SLOT];// 4-7      m_availability[4]
};

struct CreatureTypeEntry
{
    uint32    ID;                                           // 0        m_ID
    // char*   Name[16];                                    // 1-16     m_name_lang
    // 17 string flags
    // uint32    no_expirience;                             // 18       m_flags
};

struct DungeonEncounterEntry
{
    uint32 Id;                                              // 0        m_ID
    uint32 mapId;                                           // 1        m_mapID
    uint32 Difficulty;                                      // 2        m_difficulty
    uint32 encounterData;                                   // 3        m_orderIndex
    uint32 encounterIndex;                                  // 4        m_Bit
    char*  encounterName[16];                               // 5-20     m_name_lang
    uint32 nameLangFlags;                                   // 21       m_name_lang_flags
    uint32 spellIconID;                                     // 22       m_spellIconID
};

struct DurabilityCostsEntry
{
    uint32    Itemlvl;                                      // 0        m_ID
    uint32    multiplier[29];                               // 1-29     m_weaponSubClassCost m_armorSubClassCost
};

struct DurabilityQualityEntry
{
    uint32    Id;                                           // 0        m_ID
    float     quality_mod;                                  // 1        m_data
};

struct EmotesEntry
{
    uint32  Id;                                             // 0        m_ID
    // char*   Name;                                        // 1        m_EmoteSlashCommand
    // uint32  AnimationId;                                 // 2        m_AnimID
    uint32  Flags;                                          // 3        m_EmoteFlags
    uint32  EmoteType;                                      // 4        m_EmoteSpecProc (determine how emote are shown)
    uint32  UnitStandState;                                 // 5        m_EmoteSpecProcParam
    // uint32  SoundId;                                     // 6        m_EventSoundID
};

struct EmotesTextEntry
{
    uint32  Id;                                             //          m_ID
    //          m_name
    uint32  textid;                                         //          m_emoteID
    //          m_emoteText
};

struct FactionEntry
{
    uint32      ID;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    float       spilloverRateIn;                            // 19       m_parentFactionMod[2] Faction gains incoming rep * spilloverRateIn
    float       spilloverRateOut;                           // 20       Faction outputs rep * spilloverRateOut as spillover reputation
    uint32      spilloverMaxRankIn;                         // 21       m_parentFactionCap[2] The highest rank the faction will profit from incoming spillover
    uint32      spilloverRank_unk;                          // 22       It does not seem to be the max standing at which a faction outputs spillover ...so no idea
    char*       name[16];                                   // 23-38    m_name_lang
    // 39 string flags
    // char*     description[16];                           // 40-55    m_description_lang
    // 56 string flags

    // helpers

    int GetIndexFitTo(uint32 raceMask, uint32 classMask) const
    {
        for (int i = 0; i < 4; ++i)
        {
            if ((BaseRepRaceMask[i] == 0 || (BaseRepRaceMask[i] & raceMask)) &&
                    (BaseRepClassMask[i] == 0 || (BaseRepClassMask[i] & classMask)))
                return i;
        }

        return -1;
    }
    bool HasReputation() const { return reputationListID >= 0; }
};

/*
// NOTE: FactionGroup.dbc - currently unused, please refer to related hardcoded enum FactionGroupMask
struct FactionGroupEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      maskID;                                     // 1        m_maskID       index of the bit to check for in the faction group mask
    char*       internalName;                               // 2        m_internalName
    // char*       name[16];                                // 3-18     m_name_lang    localized display name in the UI
    // 19 string flags
};
*/

struct FactionTemplateEntry
{
    uint32      ID;                                         // 0
    uint32      faction;                                    // 1
    uint32      factionFlags;                               // 2 specific flags for that faction
    uint32      factionGroupMask;                           // 3 if mask set (see FactionGroupMask) then faction included in masked group
    uint32      friendGroupMask;                            // 4 if mask set (see FactionGroupMask) then faction friendly to masked group
    uint32      enemyGroupMask;                             // 5 if mask set (see FactionGroupMask) then faction hostile to masked group
    uint32      enemyFaction[4];                            // 6-9
    uint32      friendFaction[4];                           // 10-13
    //-------------------------------------------------------  end structure

    // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if (entry.faction)
        {
            for (unsigned int i : enemyFaction)
                if (i == entry.faction)
                    return false;
            for (unsigned int i : friendFaction)
                if (i == entry.faction)
                    return true;
        }
        return (friendGroupMask & entry.factionGroupMask) || (factionGroupMask & entry.friendGroupMask);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if (entry.faction)
        {
            for (unsigned int i : enemyFaction)
                if (i == entry.faction)
                    return true;
            for (unsigned int i : friendFaction)
                if (i == entry.faction)
                    return false;
        }
        return (enemyGroupMask & entry.factionGroupMask) != 0;
    }
    bool IsHostileToPlayers() const { return (enemyGroupMask & FACTION_GROUP_MASK_PLAYER) != 0; }
    bool IsNeutralToAll() const
    {
        for (unsigned int i : enemyFaction)
            if (i != 0)
                return false;
        return enemyGroupMask == 0 && friendGroupMask == 0;
    }
    bool IsContestedGuardFaction() const { return (factionFlags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD) != 0; }
};

struct GameObjectDisplayInfoEntry
{
    uint32 Displayid;                                       // 0 m_ID
    char* filename;                                         // 1 m_modelName
    // uint32 unknown2[10];                                 // 2-11 m_Sound
    float minX;                                             // 12 m_geoBoxMinX
    float minY;                                             // 13 m_geoBoxMinY
    float minZ;                                             // 14 m_geoBoxMinZ
    float maxX;                                             // 15 m_geoBoxMaxX
    float maxY;                                             // 16 m_geoBoxMaxY
    float maxZ;                                             // 17 m_geoBoxMaxZ
};

struct GemPropertiesEntry
{
    uint32      ID;                                         //          m_id
    uint32      spellitemenchantement;                      //          m_enchant_id
    //          m_maxcount_inv
    //          m_maxcount_item
    uint32      color;                                      //          m_type
};

struct GMSurveyCurrentSurveyEntry
{
    uint32    localeID;                                     // 0    m_LANGID
    uint32    surveyID;                                     // 1    m_GMSURVEY_ID
};

#define MAX_GMSURVEY_QUESTIONS 10                           // Hardcoded in all versions of the game, max amount of questions in gm survey

struct GMSurveyEntry
{
    uint32    ID;                                           // 0    m_ID
    uint32    questionID[MAX_GMSURVEY_QUESTIONS];           // 1-11 m_Q[10]
};

struct GMSurveyQuestionsEntry
{
    uint32    ID;                                           // 0    m_ID
    char*     question[16];                                 // 1-17 m_Question_lang;
    // 18 string flags, unused
};

struct GMTicketCategoryEntry
{
    uint32    ID;                                           // 0    m_ID
    char*     name[16];                                     // 1-17 m_category_lang
    // 18 string flags, unused
};

// All Gt* DBC store data for 100 levels, some by 100 per class/race
#define GT_MAX_LEVEL    100

struct GtCombatRatingsEntry
{
    float    ratio;
};

struct GtChanceToMeleeCritBaseEntry
{
    float    base;
};

struct GtChanceToMeleeCritEntry
{
    float    ratio;
};

struct GtChanceToSpellCritBaseEntry
{
    float    base;
};

struct GtChanceToSpellCritEntry
{
    float    ratio;
};

struct GtOCTRegenHPEntry
{
    float    ratio;
};

struct GtNPCManaCostScalerEntry
{
    float    ratio;
};

// struct GtOCTRegenMPEntry
//{
//    float    ratio;
//};

struct GtRegenHPPerSptEntry
{
    float    ratio;
};

struct GtRegenMPPerSptEntry
{
    float    ratio;
};

struct ItemEntry
{
    uint32  ID;                                             // 0        m_ID
    uint32  DisplayId;                                      // 1        m_displayInfoID
    uint32  InventoryType;                                  // 2        m_inventoryType
    uint32  Sheath;                                         // 3        m_sheatheType
};

struct ItemBagFamilyEntry
{
    uint32   ID;                                            // 0        m_ID
    // char*     name[16]                                   // 1-16     m_name_lang
    //                                                      // 17       name flags
};

struct ItemClassEntry
{
    uint32   ID;                                            // 0        m_ID
    // uint32   unk1;                                       // 1
    // uint32   unk2;                                       // 2        only weapon have 1 in field, other 0
    char*    name[16];                                      // 3-19     m_name_lang
    //                                                      // 20       name flags
};

struct ItemDisplayInfoEntry
{
    uint32      ID;
    uint32      randomPropertyChance;
};

// struct ItemCondExtCostsEntry
//{
//    uint32      ID;
//    uint32      condExtendedCost;                         // ItemPrototype::CondExtendedCost
//    uint32      itemextendedcostentry;                    // ItemPrototype::ExtendedCost
//    uint32      arenaseason;                              // arena season number(1-4)
//};

#define MAX_EXTENDED_COST_ITEMS 5

struct ItemExtendedCostEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      reqhonorpoints;                             // 1        m_honorPoints
    uint32      reqarenapoints;                             // 2        m_arenaPoints
    uint32      reqitem[MAX_EXTENDED_COST_ITEMS];           // 3-7      m_itemID
    uint32      reqitemcount[MAX_EXTENDED_COST_ITEMS];      // 8-12     m_itemCount
    uint32      reqpersonalarenarating;                     // 13       m_requiredArenaRating
};

struct ItemRandomPropertiesEntry
{
    uint32    ID;                                           // 0        m_ID
    // char*     internalName                               // 1        m_Name
    uint32    enchant_id[3];                                // 2-4      m_Enchantment
    // 5-6 unused, 0 only values, reserved for additional enchantments
    char*     nameSuffix[16];                               // 7-22     m_name_lang
    // 23 string flags
};

struct ItemRandomSuffixEntry
{
    uint32    ID;                                           // 0        m_ID
    char*     nameSuffix[16];                               // 1-16     m_name_lang
    // 17 string flags
    // 18       m_internalName
    uint32    enchant_id[3];                                // 19-21    m_enchantment
    uint32    prefix[3];                                    // 22-24    m_allocationPct
};

struct ItemSetEntry
{
    uint32    id;                                           // 0        m_ID
    char*     name[16];                                     // 1-16     m_name_lang
    // 17 string flags
    // uint32    itemId[17];                                // 18-34    m_itemID
    uint32    spells[8];                                    // 35-42    m_setSpellID
    uint32    items_to_triggerspell[8];                     // 43-50    m_setThreshold
    uint32    required_skill_id;                            // 51       m_requiredSkill
    uint32    required_skill_value;                         // 52       m_requiredSkillRank
};

struct LiquidTypeEntry
{
    uint32 Id;                                              // 0
    uint32 LiquidId;                                        // 1        1: Coilfang Raid - Water; 23: Water; 29: Ocean; 35: Magma; 41: Slime; 47: Naxxramas - Slime; 65: Hyjal Past - Water.
    uint32 Type;                                            // 2        0: Magma; 2: Slime; 3: Water.
    uint32 SpellId;                                         // 3        Reference to Spell.dbc
};

#define MAX_LOCK_CASE 8

struct LockEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      Type[MAX_LOCK_CASE];                        // 1-5      m_Type
    uint32      Index[MAX_LOCK_CASE];                       // 9-16     m_Index
    uint32      Skill[MAX_LOCK_CASE];                       // 17-24    m_Skill
    // uint32      Action[MAX_LOCK_CASE];                   // 25-32    m_Action
};

struct MailTemplateEntry
{
    uint32      ID;                                         // 0        m_ID
    // char*       subject[16];                             // 1-16     m_subject_lang
    // 17 string flags
    char*       content[16];                                // 18-33    m_body_lang
};

struct MapEntry
{
    uint32  MapID;                                          // 0        m_ID
    // char*       internalname;                            // 1        m_Directory
    uint32  map_type;                                       // 2        m_InstanceType
    // uint32 isPvP;                                        // 3        m_PVP 0 or 1 for battlegrounds (not arenas)
    char*   name[16];                                       // 4-19     m_MapName_lang
    // 20 string flags
    // 21-23 unused (something PvPZone related - levels?)
    // 24-26
    uint32  linked_zone;                                    // 27       m_areaTableID
    // char*     hordeIntro[16];                            // 28-43    m_MapDescription0_lang
    // 44 string flags
    // char*     allianceIntro[16];                         // 45-60    m_MapDescription1_lang
    // 61 string flags
    uint32  multimap_id;                                    // 62       m_LoadingScreenID (LoadingScreens.dbc)
    // 63-64 not used
    // float   BattlefieldMapIconScale;                     // 65       m_minimapIconScale
    // chat*     unknownText1                               // 66-81 unknown empty text fields, possible normal Intro text.
    // 82 text flags
    // chat*     heroicIntroText                            // 83-98 heroic mode requirement text
    // 99 text flags
    // chat*     unknownText2                               // 100-115 unknown empty text fields
    // 116 text flags
    int32   ghost_entrance_map;                             // 117      m_corpseMapID map_id of entrance map in ghost mode (continent always and in most cases = normal entrance)
    float   ghost_entrance_x;                               // 118      m_corpseX entrance x coordinate in ghost mode  (in most cases = normal entrance)
    float   ghost_entrance_y;                               // 119      m_corpseY entrance y coordinate in ghost mode  (in most cases = normal entrance)
    uint32 resetTimeRaid;                                   // 120
    uint32 resetTimeHeroic;                                 // 121
    // 122      all 0
    // uint32  timeOfDayOverride;                           // 123      m_timeOfDayOverride
    uint32  addon;                                          // 124      m_expansionID

    // Helpers
    uint32 Expansion() const { return addon; }

    bool IsDungeon() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID; }
    bool IsNonRaidDungeon() const { return map_type == MAP_INSTANCE; }
    bool Instanceable() const { return map_type == MAP_INSTANCE || map_type == MAP_RAID || map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }
    bool IsRaid() const { return map_type == MAP_RAID; }
    bool IsBattleGround() const { return map_type == MAP_BATTLEGROUND; }
    bool IsBattleArena() const { return map_type == MAP_ARENA; }
    bool IsBattleGroundOrArena() const { return map_type == MAP_BATTLEGROUND || map_type == MAP_ARENA; }
    bool SupportsHeroicMode() const { return resetTimeHeroic && !resetTimeRaid; }
    bool HasResetTime() const { return resetTimeHeroic || resetTimeRaid; }

    bool IsContinent() const
    {
        return MapID == 0 || MapID == 1 || MapID == 530;
    }
};

struct QuestSortEntry
{
    uint32      id;                                         // 0        m_ID
    // char*       name[16];                                // 1-16     m_SortName_lang
    // 17 string flags
};

struct RandomPropertiesPointsEntry
{
    // uint32  Id;                                          // 0        m_ID
    uint32    itemLevel;                                    // 1        m_ItemLevel
    uint32    EpicPropertiesPoints[5];                      // 2-6      m_Epic
    uint32    RarePropertiesPoints[5];                      // 7-11     m_Superior
    uint32    UncommonPropertiesPoints[5];                  // 12-16    m_Good
};

/*struct SkillLineCategoryEntry
{
    uint32    id;                                           // 0        m_ID
    char*     name[16];                                     // 1-17     m_name_lang
                                                            // 18 string flags
    uint32    displayOrder;                                 // 19       m_sortIndex
};*/

struct SkillRaceClassInfoEntry
{
    // uint32    id;                                        // 0        m_ID
    uint32    skillId;                                      // 1        m_skillID
    uint32    raceMask;                                     // 2        m_raceMask
    uint32    classMask;                                    // 3        m_classMask
    uint32    flags;                                        // 4        m_flags
    uint32    reqLevel;                                     // 5        m_minLevel
    uint32    skillTierId;                                  // 6        m_skillTierID
    // uint32    skillCostID;                               // 7        m_skillCostIndex
};

#define MAX_SKILL_STEP 16

struct SkillTiersEntry
{
    uint32    id;                                           // 0        m_ID
    uint32    skillValue[MAX_SKILL_STEP];                   // 1-17     m_cost
    uint32    maxSkillValue[MAX_SKILL_STEP];                // 18-33    m_valueMax
};

struct SkillLineEntry
{
    uint32    id;                                           // 0        m_ID
    int32     categoryId;                                   // 1        m_categoryID
    // uint32    skillCostID;                               // 2        m_skillCostsID
    char*     name[16];                                     // 3-18     m_displayName_lang
    // 19 string flags
    // char*     description[16];                           // 20-35    m_description_lang
    // 36 string flags
    uint32    spellIcon;                                    // 37       m_spellIconID
};

struct SkillLineAbilityEntry
{
    uint32    id;                                           // 0, INDEX
    uint32    skillId;                                      // 1
    uint32    spellId;                                      // 2
    uint32    racemask;                                     // 3
    uint32    classmask;                                    // 4
    // uint32    racemaskNot;                               // 5 always 0 in 2.4.2
    // uint32    classmaskNot;                              // 6 always 0 in 2.4.2
    uint32    req_skill_value;                              // 7 for trade skill.not for training.
    uint32    forward_spellid;                              // 8
    uint32    learnOnGetSkill;                              // 9 can be 1 or 2 for spells learned on get skill
    uint32    max_value;                                    // 10
    uint32    min_value;                                    // 11
    // 12-13, unknown, always 0
    uint32    reqtrainpoints;                               // 14
};

struct SoundEntriesEntry
{
    uint32    Id;                                           // 0        m_ID
    // uint32    Type;                                      // 1        m_soundType
    // char*     InternalName;                              // 2        m_name
    // char*     FileName[10];                              // 3-12     m_File[10]
    // uint32    Unk13[10];                                 // 13-22    m_Freq[10]
    // char*     Path;                                      // 23       m_DirectoryBase
    // 24       m_volumeFloat
    // 25       m_flags
    // 26       m_minDistance
    // 27       m_distanceCutoff
    // 28       m_EAXDef
};

struct ClassFamilyMask
{
    uint64 Flags;

    ClassFamilyMask() : Flags(0) {}
    explicit ClassFamilyMask(uint64 familyFlags) : Flags(familyFlags) {}

    bool Empty() const { return Flags == 0; }
    bool operator!() const { return Empty(); }
    operator void const* () const { return Empty() ? nullptr : this; } // for allow normal use in if(mask)
    bool operator== (const ClassFamilyMask& another) const { return (Flags == another.Flags); }

    bool IsFitToFamilyMask(uint64 familyFlags) const { return !!(Flags & familyFlags); }
    bool IsFitToFamilyMask(ClassFamilyMask const& mask) const { return !!(Flags & mask.Flags); }

    // possible will removed at finish convertion code use IsFitToFamilyMask
    uint64 operator& (uint64 mask) const { return !!(Flags & mask); }

    ClassFamilyMask& operator|= (ClassFamilyMask const& mask)
    {
        Flags |= mask.Flags;
        return *this;
    }
};

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2
#define MAX_SPELL_TOTEM_CATEGORIES 2

struct SpellEntry
{
        uint32    Id;                                       // 0        m_ID
        uint32    Category;                                 // 1        m_category
        uint32    CastUI;                                   // 2        not used
        uint32    Dispel;                                   // 3        m_dispelType
        uint32    Mechanic;                                 // 4        m_mechanic
        uint32    Attributes;                               // 5        m_attributes
        uint32    AttributesEx;                             // 6        m_attributesEx
        uint32    AttributesEx2;                            // 7        m_attributesExB
        uint32    AttributesEx3;                            // 8        m_attributesExC
        uint32    AttributesEx4;                            // 9        m_attributesExD
        uint32    AttributesEx5;                            // 10       m_attributesExE
        uint32    AttributesEx6;                            // 11       m_attributesExF
        uint32    Stances;                                  // 12       m_shapeshiftMask
        uint32    StancesNot;                               // 13       m_shapeshiftExclude
        uint32    Targets;                                  // 14       m_targets
        uint32    TargetCreatureType;                       // 15       m_targetCreatureType
        uint32    RequiresSpellFocus;                       // 16       m_requiresSpellFocus
        uint32    FacingCasterFlags;                        // 17       m_facingCasterFlags
        uint32    CasterAuraState;                          // 18       m_casterAuraState
        uint32    TargetAuraState;                          // 19       m_targetAuraState
        uint32    CasterAuraStateNot;                       // 20       m_excludeCasterAuraState
        uint32    TargetAuraStateNot;                       // 21       m_excludeTargetAuraState
        uint32    CastingTimeIndex;                         // 22       m_castingTimeIndex
        uint32    RecoveryTime;                             // 23       m_recoveryTime
        uint32    CategoryRecoveryTime;                     // 24       m_categoryRecoveryTime
        uint32    InterruptFlags;                           // 25       m_interruptFlags
        uint32    AuraInterruptFlags;                       // 26       m_auraInterruptFlags
        uint32    ChannelInterruptFlags;                    // 27       m_channelInterruptFlags
        uint32    procFlags;                                // 28       m_procTypeMask
        uint32    procChance;                               // 29       m_procChance
        uint32    procCharges;                              // 30       m_procCharges
        uint32    maxLevel;                                 // 31       m_maxLevel
        uint32    baseLevel;                                // 32       m_baseLevel
        uint32    spellLevel;                               // 33       m_spellLevel
        uint32    DurationIndex;                            // 34       m_durationIndex
        uint32    powerType;                                // 35       m_powerType
        uint32    manaCost;                                 // 36       m_manaCost
        uint32    manaCostPerlevel;                         // 37       m_manaCostPerLevel
        uint32    manaPerSecond;                            // 38       m_manaPerSecond
        uint32    manaPerSecondPerLevel;                    // 39       m_manaPerSecondPerLevel
        uint32    rangeIndex;                               // 40       m_rangeIndex
        float     speed;                                    // 41       m_speed
        uint32    modalNextSpell;                           // 42       m_modalNextSpell not used
        uint32    StackAmount;                              // 43       m_cumulativeAura
        uint32    Totem[MAX_SPELL_TOTEMS];                  // 44-45    m_totem
        int32     Reagent[MAX_SPELL_REAGENTS];              // 46-53    m_reagent
        uint32    ReagentCount[MAX_SPELL_REAGENTS];         // 54-61    m_reagentCount
        int32     EquippedItemClass;                        // 62       m_equippedItemClass (value)
        int32     EquippedItemSubClassMask;                 // 63       m_equippedItemSubclass (mask)
        int32     EquippedItemInventoryTypeMask;            // 64       m_equippedItemInvTypes (mask)
        uint32    Effect[MAX_EFFECT_INDEX];                 // 65-67    m_effect
        int32     EffectDieSides[MAX_EFFECT_INDEX];         // 68-70    m_effectDieSides
        uint32    EffectBaseDice[MAX_EFFECT_INDEX];         // 71-73
        float     EffectDicePerLevel[MAX_EFFECT_INDEX];     // 74-76
        float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 77-79    m_effectRealPointsPerLevel
        int32     EffectBasePoints[MAX_EFFECT_INDEX];       // 80-82    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
        uint32    EffectMechanic[MAX_EFFECT_INDEX];         // 83-85    m_effectMechanic
        uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];  // 86-88    m_implicitTargetA
        uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];  // 89-91    m_implicitTargetB
        uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];      // 92-94    m_effectRadiusIndex - spellradius.dbc
        uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];    // 95-97    m_effectAura
        uint32    EffectAmplitude[MAX_EFFECT_INDEX];        // 98-100   m_effectAuraPeriod
        float     EffectMultipleValue[MAX_EFFECT_INDEX];    // 101-103  m_effectAmplitude
        uint32    EffectChainTarget[MAX_EFFECT_INDEX];      // 104-106  m_effectChainTargets
        uint32    EffectItemType[MAX_EFFECT_INDEX];         // 107-109  m_effectItemType
        int32     EffectMiscValue[MAX_EFFECT_INDEX];        // 110-112  m_effectMiscValue
        int32     EffectMiscValueB[MAX_EFFECT_INDEX];       // 113-115  m_effectMiscValueB
        uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];     // 116-118  m_effectTriggerSpell
        float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 119-121  m_effectPointsPerCombo
        uint32    SpellVisual;                              // 122      m_spellVisualID
        // uint32    SpellVisual2;                          // 123 not used
        uint32    SpellIconID;                              // 124      m_spellIconID
        uint32    activeIconID;                             // 125      m_activeIconID
        uint32    spellPriority;                            // 126      m_spellPriority not used
        char*     SpellName[16];                            // 127-142  m_name_lang
        // uint32    SpellNameFlag;                         // 143      m_name_flag not used
        char*     Rank[16];                                 // 144-159  m_nameSubtext_lang
        // uint32    RankFlags;                             // 160      m_nameSubtext_flag not used
        // char*     Description[16];                       // 161-176  m_description_lang not used
        // uint32    DescriptionFlags;                      // 177      m_description_flag not used
        // char*     ToolTip[16];                           // 178-193  m_auraDescription_lang not used
        // uint32    ToolTipFlags;                          // 194      m_auraDescription_flag not used
        uint32    ManaCostPercentage;                       // 195      m_manaCostPct
        uint32    StartRecoveryCategory;                    // 196      m_startRecoveryCategory
        uint32    StartRecoveryTime;                        // 197      m_startRecoveryTime
        uint32    MaxTargetLevel;                           // 198      m_maxTargetLevel
        uint32    SpellFamilyName;                          // 199      m_spellClassSet
        ClassFamilyMask SpellFamilyFlags;                   // 200-201  m_spellClassMask
        uint32    MaxAffectedTargets;                       // 202      m_maxTargets
        uint32    DmgClass;                                 // 203      m_defenseType
        uint32    PreventionType;                           // 204      m_preventionType
        int32    StanceBarOrder;                            // 205      m_stanceBarOrder not used
        float     DmgMultiplier[MAX_EFFECT_INDEX];          // 206-208  m_effectChainAmplitude
        uint32    MinFactionId;                             // 209      m_minFactionID not used
        uint32    MinReputation;                            // 210      m_minReputation not used
        uint32    RequiredAuraVision;                       // 211      m_requiredAuraVision not used
        uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];// 212-213  m_requiredTotemCategoryID
        uint32    AreaId;                                   // 214
        uint32    SchoolMask;                               // 215      m_schoolMask

        // custom
        uint32    IsServerSide;                             // 216
        uint32    AttributesServerside;                     // 217

        // helpers
        int32 CalculateSimpleValue(SpellEffectIndex eff) const { return EffectBasePoints[eff] + int32(EffectBaseDice[eff]); }

        bool IsFitToFamilyMask(uint64 familyFlags) const
        {
            return SpellFamilyFlags.IsFitToFamilyMask(familyFlags);
        }

        bool IsFitToFamily(SpellFamily family, uint64 familyFlags) const
        {
            return SpellFamily(SpellFamilyName) == family && IsFitToFamilyMask(familyFlags);
        }

        bool IsFitToFamilyMask(ClassFamilyMask const& mask) const
        {
            return SpellFamilyFlags.IsFitToFamilyMask(mask);
        }

        bool IsFitToFamily(SpellFamily family, ClassFamilyMask const& mask) const
        {
            return SpellFamily(SpellFamilyName) == family && IsFitToFamilyMask(mask);
        }

        inline bool HasAttribute(SpellAttributes attribute) const { return (Attributes & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx attribute) const { return (AttributesEx & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx2 attribute) const { return (AttributesEx2 & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx3 attribute) const { return (AttributesEx3 & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx4 attribute) const { return (AttributesEx4 & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx5 attribute) const { return (AttributesEx5 & attribute) != 0; }
        inline bool HasAttribute(SpellAttributesEx6 attribute) const { return (AttributesEx6 & attribute) != 0; }

        // custom
        bool HasAttribute(SpellAttributesServerside attribute) const { return (AttributesServerside & attribute) != 0; }

    private:
        // prevent creating custom entries (copy data from original in fact)
        SpellEntry(SpellEntry const&);                      // DON'T must have implementation
};

// A few fields which are required for automated convertion
// NOTE that these fields are count by _skipping_ the fields that are unused!
#define LOADED_SPELLDBC_FIELD_POS_EQUIPPED_ITEM_CLASS  60   // Must be converted to -1
#define LOADED_SPELLDBC_FIELD_POS_SPELLNAME_0          123  // Links to "MaNGOS server-side spell"

struct SpellCastTimesEntry
{
    uint32    ID;                                           // 0        m_ID
    int32     CastTime;                                     // 1        m_base
    int32     CastTimePerLevel;                             // 2        m_perLevel
    int32     MinCastTime;                                  // 3        m_minimum
};

struct SpellFocusObjectEntry
{
    uint32    ID;                                           // 0        m_ID
    // char*     Name[16];                                  // 1-15     m_name_lang
    // 16 string flags
};

struct SpellRadiusEntry
{
    uint32    ID;                                           //          m_ID
    float     Radius;                                       //          m_radius
    //          m_radiusPerLevel
    // float     RadiusMax;                                 //          m_radiusMax
};

struct SpellRangeEntry
{
    uint32    ID;                                           // 0        m_ID
    float     minRange;                                     // 1        m_rangeMin
    float     maxRange;                                     // 2        m_rangeMax
    uint32  Flags;                                          // 3        m_flags
    // char*   Name[16];                                    // 4-19     m_displayName_lang
    // uint32  NameFlags;                                   // 20 string flags
    // char*   ShortName[16];                               // 21-36    m_displayNameShort_lang
    // uint32  NameFlags;                                   // 37 string flags
};

struct SpellShapeshiftFormEntry
{
    uint32 ID;                                              // 0        m_ID
    // uint32 buttonPosition;                               // 1        m_bonusActionBar
    // char*  Name[16];                                     // 2-17     m_name_lang
    // uint32 NameFlags;                                    // 18 string flags
    uint32 flags1;                                          // 19       m_flags
    int32  creatureType;                                    // 20       m_creatureType <=0 humanoid, other normal creature types
    // uint32 unk1;                                         // 21       m_attackIconID
    uint32 attackSpeed;                                     // 22       m_combatRoundTime
    uint32 modelID_A;                                       // 23       m_creatureDisplayID[4]
    // uint32 modelID_H;                                    // 24 horde modelid (but all 0)
    // uint32 unk3;                                         // 25 unused always 0
    // uint32 unk4;                                         // 26 unused always 0
    uint32 spellId[8];                                      // 27-34    m_presetSpellID[8]
};

struct SpellDurationEntry
{
    uint32    ID;                                           //          m_ID
    int32     Duration[3];                                  //          m_duration, m_durationPerLevel, m_maxDuration
};

struct SpellItemEnchantmentEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      type[3];                                    // 1-3      m_effect[3]
    uint32      amount[3];                                  // 4-6      m_effectPointsMin[3]
    // uint32      amount2[3]                               // 7-9      m_effectPointsMax[3]
    uint32      spellid[3];                                 // 10-12    m_effectArg[3]
    char*       description[16];                            // 13-28    m_name_lang[16]
    // uint32      descriptionFlags;                        // 29 string flags
    uint32      aura_id;                                    // 30       m_itemVisual
    uint32      slot;                                       // 31       m_flags
    uint32      GemID;                                      // 32       m_src_itemID
    uint32      EnchantmentCondition;                       // 33       m_condition_id
};

struct SpellItemEnchantmentConditionEntry
{
    uint32  ID;
    uint8   Color[5];
    uint8   Comparator[5];
    uint8   CompareColor[5];
    uint32  Value[5];
};

struct SpellVisualEntry
{
    uint32 Id;
    //uint32 PrecastKit;
    //uint32 CastingKit;
    //uint32 ImpactKit;
    //uint32 StateKit;
    //uint32 StateDoneKit; - from wotlk, not in tbc
    //uint32 ChannelKit;
    uint32 HasMissile;
    int32 MissileModel;
    //uint32 MissilePathType;
    //uint32 MissileDestinationAttachment;
    //uint32 MissileSound;
    //uint32 AnimEventSoundID;
    //uint32 Flags;
    //uint32 CasterImpactKit;
    //uint32 TargetImpactKit;
    //int32 MissileAttachment;
    //uint32 MissileFollowGroundHeight;
    //uint32 MissileFollowGroundDropSpeed;
    //uint32 MissileFollowGroundApprach;
    //uint32 MissileFollowGroundFlags;
    //uint32 MissileMotionId;
    //uint32 MissileTargetingKit;
    //uint32 InstantAreaKit;
    //uint32 ImpactAreaKit;
    //uint32 PersistentAreaKit;
    //DBCPosition3D MissileCastOffset; - from wotlk, not in tbc
    //DBCPosition3D MissileImpactOffset; - from wotlk, not in tbc
};

struct StableSlotPricesEntry
{
    uint32 Slot;                                            //          m_ID
    uint32 Price;                                           //          m_cost
};

struct SummonPropertiesEntry
{
    uint32  Id;                                             // 0        m_id
    uint32  Group;                                          // 1        m_control (enum SummonPropGroup)
    uint32  FactionId;                                      // 2        m_faction
    uint32  Title;                                          // 3        m_title (enum UnitNameSummonTitle)
    uint32  Slot;                                           // 4,       m_slot if title = UNITNAME_SUMMON_TITLE_TOTEM, its actual slot (0-6).
    //    Slot may have other uses, selection of pet type in some cases?
    uint32  Flags;                                          // 5        m_flags (enum SummonPropFlags)
};

#define MAX_TALENT_RANK 5

struct TalentEntry
{
    uint32    TalentID;                                     // 0        m_ID
    uint32    TalentTab;                                    // 1        m_tabID (TalentTab.dbc)
    uint32    Row;                                          // 2        m_tierID
    uint32    Col;                                          // 3        m_columnIndex
    uint32    RankID[MAX_TALENT_RANK];                      // 4-8      m_spellRank
    // 9-12 part of prev field
    uint32    DependsOn;                                    // 13       m_prereqTalent (Talent.dbc)
    // 14-15 part of prev field
    uint32    DependsOnRank;                                // 16       m_prereqRank
    // 17-18 part of prev field
    // uint32  needAddInSpellBook;                          // 19       m_flags also need disable higest ranks on reset talent tree
    uint32    DependsOnSpell;                               // 20       m_requiredSpellID req.spell
};

struct TalentTabEntry
{
    uint32  TalentTabID;                                    // 0        m_ID
    // char* name[16];                                      // 1-16     m_name_lang
    // uint32  nameFlags;                                   // 17 string flags
    // unit32  spellicon;                                   // 18       m_spellIconID
    // 19       m_raceMask
    uint32  ClassMask;                                      // 20       m_classMask
    uint32  tabpage;                                        // 21       m_orderIndex
    // char* internalname;                                  // 22       m_backgroundFile
};

struct TaxiNodesEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    map_id;                                       // 1        m_ContinentID
    float     x;                                            // 2        m_x
    float     y;                                            // 3        m_y
    float     z;                                            // 4        m_z
    char*     name[16];                                     // 5-21     m_Name_lang
    // 22 string flags
    uint32    MountCreatureID[2];                           // 23-24    m_MountCreatureID[2]
};

struct TaxiPathEntry
{
    uint32    ID;
    uint32    from;
    uint32    to;
    uint32    price;
};

struct TaxiPathNodeEntry
{
    // 0        m_ID
    uint32    path;                                         // 1        m_PathID
    uint32    index;                                        // 2        m_NodeIndex
    uint32    mapid;                                        // 3        m_ContinentID
    float     x;                                            // 4        m_LocX
    float     y;                                            // 5        m_LocY
    float     z;                                            // 6        m_LocZ
    uint32    actionFlag;                                   // 7        m_flags
    uint32    delay;                                        // 8        m_delay
    uint32    arrivalEventID;                               // 9        m_arrivalEventID
    uint32    departureEventID;                             // 10       m_departureEventID
};

struct TotemCategoryEntry
{
    uint32    ID;                                           // 0        m_ID
    // char*   name[16];                                    // 1-16     m_name_lang
    // 17 string flags
    uint32    categoryType;                                 // 18       m_totemCategoryType (one for specialization)
    uint32    categoryMask;                                 // 19       m_totemCategoryMask (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

struct TransportAnimationEntry
{
    //uint32  Id;
    uint32  TransportEntry;
    uint32  TimeSeg;
    float   X;
    float   Y;
    float   Z;
    //uint32  MovementId;
};

struct WMOAreaTableEntry
{
    uint32 Id;                                              // 0        m_ID index
    int32 rootId;                                           // 1        m_WMOID used in root WMO
    int32 adtId;                                            // 2        m_NameSetID used in adt file
    int32 groupId;                                          // 3        m_WMOGroupID used in group WMO
    // uint32 field4;                                       // 4        m_SoundProviderPref
    // uint32 field5;                                       // 5        m_SoundProviderPrefUnderwater
    // uint32 field6;                                       // 6        m_AmbienceID
    // uint32 field7;                                       // 7        m_ZoneMusic
    // uint32 field8;                                       // 8        m_IntroSound
    uint32 Flags;                                           // 9        m_flags (used for indoor/outdoor determination)
    uint32 areaId;                                          // 10       m_AreaTableID (AreaTable.dbc)
    // char *Name[16];                                      //          m_AreaName_lang
    // uint32 nameFlags;
};

struct WorldMapAreaEntry
{
    // uint32  ID;                                          // 0        m_ID
    uint32  map_id;                                         // 1        m_mapID
    uint32  area_id;                                        // 2        m_areaID index (continent 0 areas ignored)
    // char* internal_name                                  // 3        m_areaName
    float   y1;                                             // 4        m_locLeft
    float   y2;                                             // 5        m_locRight
    float   x1;                                             // 6        m_locTop
    float   x2;                                             // 7        m_locBottom
    int32   virtual_map_id;                                 // 8        m_displayMapID -1 (map_id have correct map) other: virtual map where zone show (map_id - where zone in fact internally)
};

/* not used in 2.4.3 code
#define MAX_WORLD_MAP_OVERLAY_AREA_IDX 4

struct WorldMapOverlayEntry
{
    uint32    ID;                                           // 0        m_ID
    // uint32    worldMapAreaId;                            // 1        m_mapAreaID (WorldMapArea.dbc)
    uint32    areatableID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];  // 2-5      m_areaID
                                                            // 6        m_mapPointX
                                                            // 7        m_mapPointY
    // char* internal_name                                  // 8        m_textureName
                                                            // 9        m_textureWidth
                                                            // 10       m_textureHeight
                                                            // 11       m_offsetX
                                                            // 12       m_offsetY
                                                            // 13       m_hitRectTop
                                                            // 14       m_hitRectLeft
                                                            // 15       m_hitRectBottom
                                                            // 16       m_hitRectRight
};
*/

/* Structure WorldSafeLocsEntry is no longer loaded from DBC but from DB instead
struct WorldSafeLocsEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    map_id;                                       // 1        m_continent
    float     x;                                            // 2        m_locX
    float     y;                                            // 3        m_locY
    float     z;                                            // 4        m_locZ
    // char*   name[16]                                     // 5-20     m_AreaName_lang
    // 21 string flags
};
*/

struct ItemCategorySpellPair
{
    uint32 spellId;
    uint32 itemId;
    ItemCategorySpellPair(uint32 _spellId, uint32 _itemId) : spellId(_spellId), itemId(_itemId) {}
    bool operator <(ItemCategorySpellPair const& pair) const { return spellId == pair.spellId ? itemId < pair.itemId : spellId < pair.spellId; }
};

typedef std::set<ItemCategorySpellPair> ItemSpellCategorySet;
typedef std::map<uint32, ItemSpellCategorySet > ItemSpellCategoryStore;
typedef std::set<uint32> SpellCategorySet;
typedef std::map<uint32, SpellCategorySet> SpellCategoryStore;
typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32, PetFamilySpellsSet > PetFamilySpellsStore;

// Structures not used for casting to loaded DBC data and not required then packing
struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) {}
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) {}

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32, TalentSpellPos> TalentSpellPosMap;

struct TaxiPathBySourceAndDestination
{
    TaxiPathBySourceAndDestination() : ID(0), price(0) {}
    TaxiPathBySourceAndDestination(uint32 _id, uint32 _price) : ID(_id), price(_price) {}

    uint32    ID;
    uint32    price;
};
typedef std::map<uint32, TaxiPathBySourceAndDestination> TaxiPathSetForSource;
typedef std::map<uint32, TaxiPathSetForSource> TaxiPathSetBySource;

typedef Path<TaxiPathNodeEntry const*> TaxiPathNodeList;
typedef std::vector<TaxiPathNodeList> TaxiPathNodesByPath;

#define TaxiMaskSize 16
typedef uint32 TaxiMask[TaxiMaskSize];

#define CREATURE_MAX_SPELLS 10
#define MAX_KILL_CREDIT 2
#define MAX_CREATURE_MODEL 4
#define USE_DEFAULT_DATABASE_LEVEL  0                   // just used to show we don't want to force the new creature level and use the level stored in db
#define MINIMUM_LOOTING_TIME (2 * MINUTE * IN_MILLISECONDS) // give player enough time to pick loot

// from `creature_addon` and `creature_template_addon`tables
struct CreatureDataAddon
{
    uint32 guidOrEntry;
    uint32 mount;
    uint32 bytes1;
    uint8  sheath_state;                                    // SheathState
    uint8  flags;                                           // UnitBytes2_Flags
    uint32 emote;
    uint32 move_flags;
    uint32 const* auras;                                    // loaded as char* "spell1 spell2 ... "
};

// Bases values for given Level and UnitClass
struct CreatureClassLvlStats
{
    uint32  BaseHealth;
    uint32  BaseMana;
    float   BaseDamage;
    float   BaseMeleeAttackPower;
    float   BaseRangedAttackPower;
    uint32  BaseArmor;
};

struct CreatureModelInfo
{
    uint32 modelid;
    float bounding_radius;
    float combat_reach;
    float SpeedWalk;
    float SpeedRun;
    uint8 gender;
    uint32 modelid_other_gender;                            // The oposite gender for this modelid (male/female)
    uint32 modelid_alternative;                             // An alternative model. Generally same gender(2)
};

struct CreatureModelRace
{
    uint32 modelid;                                         // Native model/base model the selection is for
    uint32 racemask;                                        // Races it applies to (and then a player source must exist for selection)
    uint32 creature_entry;                                  // Modelid from creature_template.entry will be selected
    uint32 modelid_racial;                                  // Explicit modelid. Used if creature_template entry is not defined
};

struct CreatureConditionalSpawn
{
    uint32 Guid;
    uint32 EntryAlliance;
    uint32 EntryHorde;
    // Note: future condition flags to be added
};

// from `creature_template` table
struct CreatureInfo
{
    uint32  Entry;
    char* Name;
    char* SubName;
    char* IconName;
    uint32  MinLevel;
    uint32  MaxLevel;
    uint32  HeroicEntry;
    uint32  ModelId[MAX_CREATURE_MODEL];
    uint32  Faction;
    float   Scale;
    uint32  Family;                                        // enum CreatureFamily values (optional)
    uint32  CreatureType;                                  // enum CreatureType values
    uint32  InhabitType;
    uint32  RegenerateStats;
    bool    RacialLeader;
    uint32  NpcFlags;
    uint32  UnitFlags;                                     // enum UnitFlags mask values
    uint32  DynamicFlags;
    uint32  ExtraFlags;
    uint32  CreatureTypeFlags;                             // enum CreatureTypeFlags mask values
    float   SpeedWalk;
    float   SpeedRun;
    uint32  Detection;                                     // Detection Range for Line of Sight aggro
    uint32  CallForHelp;
    uint32  Pursuit;
    uint32  Leash;
    uint32  Timeout;
    uint32  UnitClass;                                     // enum Classes. Note only 4 classes are known for creatures.
    uint32  Rank;
    int32   Expansion;                                     // creature expansion, important for stats, CAN BE -1 as marker for some invalid cases.
    float   HealthMultiplier;
    float   PowerMultiplier;
    float   DamageMultiplier;
    float   DamageVariance;
    float   ArmorMultiplier;
    float   ExperienceMultiplier;
    uint32  MinLevelHealth;
    uint32  MaxLevelHealth;
    uint32  MinLevelMana;
    uint32  MaxLevelMana;
    float   MinMeleeDmg;
    float   MaxMeleeDmg;
    float   MinRangedDmg;
    float   MaxRangedDmg;
    uint32  Armor;
    uint32  MeleeAttackPower;
    uint32  RangedAttackPower;
    uint32  MeleeBaseAttackTime;
    uint32  RangedBaseAttackTime;
    uint32  DamageSchool;
    uint32  MinLootGold;
    uint32  MaxLootGold;
    uint32  LootId;
    uint32  PickpocketLootId;
    uint32  SkinningLootId;
    uint32  KillCredit[MAX_KILL_CREDIT];
    uint32  MechanicImmuneMask;
    uint32  SchoolImmuneMask;
    int32   ResistanceHoly;
    int32   ResistanceFire;
    int32   ResistanceNature;
    int32   ResistanceFrost;
    int32   ResistanceShadow;
    int32   ResistanceArcane;
    uint32  PetSpellDataId;
    uint32  MovementType;
    uint32  TrainerType;
    uint32  TrainerSpell;
    uint32  TrainerClass;
    uint32  TrainerRace;
    uint32  TrainerTemplateId;
    uint32  VendorTemplateId;
    uint32  EquipmentTemplateId;
    uint32  GossipMenuId;
    VisibilityDistanceType visibilityDistanceType;
    char const* AIName;
    uint32  ScriptID;

    // helpers
    static HighGuid GetHighGuid()
    {
        return HIGHGUID_UNIT;                               // in pre-3.x always HIGHGUID_UNIT
    }

    ObjectGuid GetObjectGuid(uint32 lowguid) const { return ObjectGuid(GetHighGuid(), Entry, lowguid); }

    SkillType GetRequiredLootSkill() const
    {
        if (CreatureTypeFlags & CREATURE_TYPEFLAGS_HERBLOOT)
            return SKILL_HERBALISM;
        if (CreatureTypeFlags & CREATURE_TYPEFLAGS_MININGLOOT)
            return SKILL_MINING;

        return SKILL_SKINNING;                          // normal case
    }

    bool isTameable() const
    {
        return CreatureType == CREATURE_TYPE_BEAST && Family != 0 && (CreatureTypeFlags & CREATURE_TYPEFLAGS_TAMEABLE);
    }
};

struct CreatureTemplateSpells
{
    uint32 entry;
    uint32 setId;
    uint32 spells[CREATURE_MAX_SPELLS];
};

struct CreatureCooldowns
{
    uint32 entry;
    uint32 spellId;
    uint32 cooldownMin;
    uint32 cooldownMax;
};

struct EquipmentInfo
{
    uint32 entry;
    uint32 equipentry[3];
};

// depricated old way
struct EquipmentInfoRaw
{
    uint32  entry;
    uint32  equipmodel[3];
    uint32  equipinfo[3];
    uint32  equipslot[3];
};

struct CreatureSpawnTemplate
{
    uint32 entry;
    int64 unitFlags;
    uint32 faction;
    uint32 modelId;
    int32 equipmentId;
    uint32 curHealth;
    uint32 curMana;
    uint32 spawnFlags;

    bool IsRunning() const { return (spawnFlags & SPAWN_FLAG_RUN_ON_SPAWN) != 0; }
    bool IsHovering() const { return (spawnFlags & SPAWN_FLAG_HOVER) != 0; }
};

// from `creature` table
struct CreatureData
{
    uint32 id;                                              // entry in creature_template
    uint16 mapid;
    uint32 modelid_override;                                // overrides any model defined in creature_template
    int32 equipmentId;
    float posX;
    float posY;
    float posZ;
    float orientation;
    uint32 spawntimesecsmin;
    uint32 spawntimesecsmax;
    float spawndist;
    uint32 currentwaypoint;
    uint32 curhealth;
    uint32 curmana;
    bool  is_dead;
    uint8 movementType;
    uint8 spawnMask;
    int16 gameEvent;
    uint16 GuidPoolId;
    uint16 EntryPoolId;
    uint16 OriginalZoneId;
    CreatureSpawnTemplate const* spawnTemplate;

    // helper function
    ObjectGuid GetObjectGuid(uint32 lowguid) const { return ObjectGuid(CreatureInfo::GetHighGuid(), id, lowguid); }
    uint32 GetRandomRespawnTime() const { return urand(spawntimesecsmin, spawntimesecsmax); }

    // return false if it should be handled by GameEventMgr or PoolMgr
    bool IsNotPartOfPoolOrEvent() const { return (!gameEvent && !GuidPoolId && !EntryPoolId); }
};

struct PageText
{
    uint32 Page_ID;
    char* Text;

    uint32 Next_Page;
};

struct InstanceTemplate
{
    uint32 map;                                             // instance map
    uint32 parent;                                          // non-continent parent instance (for instance with entrance in another instances)
    // or 0 (not related to continent 0 map id)
    uint32 levelMin;
    uint32 levelMax;
    uint32 maxPlayers;
    uint32 reset_delay;                                     // in days
    uint32 script_id;
    bool   mountAllowed;
};

struct WorldTemplate
{
    uint32 map;                                             // non-instance map
    uint32 script_id;
};

struct SpellCone
{
    uint32 spellId;
    int32 coneAngle;
};

struct WorldSafeLocsEntry
{
    uint32    ID;
    uint32    map_id;
    float     x;
    float     y;
    float     z;
    float     o;
    char* name;
};

// from `gameobject_template`
struct GameObjectInfo
{
    uint32  id;
    uint32  type;
    uint32  displayId;
    char* name;
    char* IconName;
    char* castBarCaption;
    uint32  faction;
    uint32  flags;
    uint32  ExtraFlags;
    float   size;
    union                                                   // different GO types have different data field
    {
        //0 GAMEOBJECT_TYPE_DOOR
        struct
        {
            uint32 startOpen;                               //0 used client side to determine GO_ACTIVATED means open/closed
            uint32 lockId;                                  //1 -> Lock.dbc
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
            uint32 noDamageImmune;                          //3 break opening whenever you recieve damage?
            uint32 openTextID;                              //4 can be used to replace castBarCaption?
            uint32 closeTextID;                             //5
        } door;
        //1 GAMEOBJECT_TYPE_BUTTON
        struct
        {
            uint32 startOpen;                               //0
            uint32 lockId;                                  //1 -> Lock.dbc
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
            uint32 linkedTrapId;                            //3
            uint32 noDamageImmune;                          //4 isBattlegroundObject
            uint32 large;                                   //5
            uint32 openTextID;                              //6 can be used to replace castBarCaption?
            uint32 closeTextID;                             //7
            uint32 losOK;                                   //8
        } button;
        //2 GAMEOBJECT_TYPE_QUESTGIVER
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 questList;                               //1
            uint32 pageMaterial;                            //2
            uint32 gossipID;                                //3
            uint32 customAnim;                              //4
            uint32 noDamageImmune;                          //5
            int32 openTextID;                               //6 can be used to replace castBarCaption?
            uint32 losOK;                                   //7
            uint32 allowMounted;                            //8
            uint32 large;                                   //9
        } questgiver;
        //3 GAMEOBJECT_TYPE_CHEST
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 lootId;                                  //1
            uint32 chestRestockTime;                        //2
            uint32 consumable;                              //3
            uint32 minSuccessOpens;                         //4
            uint32 maxSuccessOpens;                         //5
            int32 eventId;                                  //6 lootedEvent
            uint32 linkedTrapId;                            //7
            uint32 questId;                                 //8 not used currently but store quest required for GO activation for player
            uint32 level;                                   //9
            uint32 losOK;                                   //10
            uint32 leaveLoot;                               //11
            uint32 notInCombat;                             //12
            uint32 logLoot;                                 //13
            uint32 openTextID;                              //14 can be used to replace castBarCaption?
            uint32 groupLootRules;                          //15
        } chest;
        //4 GAMEOBJECT_TYPE_BINDER - empty
        //5 GAMEOBJECT_TYPE_GENERIC
        struct
        {
            uint32 floatingTooltip;                         //0
            uint32 highlight;                               //1
            uint32 serverOnly;                              //2
            uint32 large;                                   //3
            uint32 floatOnWater;                            //4
            uint32 questID;                                 //5
        } _generic;
        //6 GAMEOBJECT_TYPE_TRAP
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 level;                                   //1
            uint32 diameter;                                //2 radius for trap activation
            uint32 spellId;                                 //3
            uint32 charges;                                 //4 need respawn (if > 0)
            uint32 cooldown;                                //5 time in secs
            int32 autoCloseTime;                            //6
            uint32 startDelay;                              //7
            uint32 serverOnly;                              //8
            uint32 stealthed;                               //9
            uint32 large;                                   //10
            uint32 invisible;                               //11
            uint32 openTextID;                              //12 can be used to replace castBarCaption?
            uint32 closeTextID;                             //13
        } trap;
        //7 GAMEOBJECT_TYPE_CHAIR
        struct
        {
            uint32 slots;                                   //0
            uint32 height;                                  //1
            uint32 onlyCreatorUse;                          //2
        } chair;
        //8 GAMEOBJECT_TYPE_SPELL_FOCUS
        struct
        {
            uint32 focusId;                                 //0
            uint32 dist;                                    //1
            uint32 linkedTrapId;                            //2
            uint32 serverOnly;                              //3
            uint32 questID;                                 //4
            uint32 large;                                   //5
        } spellFocus;
        //9 GAMEOBJECT_TYPE_TEXT
        struct
        {
            uint32 pageID;                                  //0
            uint32 language;                                //1
            uint32 pageMaterial;                            //2
            uint32 allowMounted;                            //3
        } text;
        //10 GAMEOBJECT_TYPE_GOOBER
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            int32 questId;                                  //1
            uint32 eventId;                                 //2
            uint32 autoCloseTime;                           //3
            uint32 customAnim;                              //4
            uint32 consumable;                              //5
            int32 cooldown;                                 //6
            uint32 pageId;                                  //7
            uint32 language;                                //8
            uint32 pageMaterial;                            //9
            uint32 spellId;                                 //10
            uint32 noDamageImmune;                          //11
            uint32 linkedTrapId;                            //12
            uint32 large;                                   //13
            uint32 openTextID;                              //14 can be used to replace castBarCaption?
            uint32 closeTextID;                             //15
            uint32 isPvPObject;                             //16 flags used only in battlegrounds
            uint32 allowMounted;                            //17
            uint32 floatingTooltip;                         //18
            uint32 gossipID;                                //19
        } goober;
        //11 GAMEOBJECT_TYPE_TRANSPORT
        struct
        {
            uint32 pause;                                   //0
            uint32 startOpen;                               //1
            uint32 autoCloseTime;                           //2 secs till autoclose = autoCloseTime / 0x10000
        } transport;
        //12 GAMEOBJECT_TYPE_AREADAMAGE
        struct
        {
            uint32 lockId;                                  //0
            uint32 radius;                                  //1
            uint32 damageMin;                               //2
            uint32 damageMax;                               //3
            uint32 damageSchool;                            //4
            uint32 autoCloseTime;                           //5 secs till autoclose = autoCloseTime / 0x10000
            uint32 openTextID;                              //6
            uint32 closeTextID;                             //7
        } areadamage;
        //13 GAMEOBJECT_TYPE_CAMERA
        struct
        {
            uint32 lockId;                                  //0 -> Lock.dbc
            uint32 cinematicId;                             //1
            uint32 eventID;                                 //2
            uint32 openTextID;                              //3 can be used to replace castBarCaption?
        } camera;
        //14 GAMEOBJECT_TYPE_MAPOBJECT - empty
        //15 GAMEOBJECT_TYPE_MO_TRANSPORT
        struct
        {
            uint32 taxiPathId;                              //0
            uint32 moveSpeed;                               //1
            uint32 accelRate;                               //2
            uint32 startEventID;                            //3
            uint32 stopEventID;                             //4
            uint32 transportPhysics;                        //5
            uint32 mapID;                                   //6
        } moTransport;
        //16 GAMEOBJECT_TYPE_DUELFLAG - empty
        //17 GAMEOBJECT_TYPE_FISHINGNODE
        struct
        {
            uint32 _data0;                                  //0
            uint32 lootId;                                  //1
        } fishnode;
        //18 GAMEOBJECT_TYPE_SUMMONING_RITUAL
        struct
        {
            uint32 reqParticipants;                         //0
            uint32 spellId;                                 //1
            uint32 animSpell;                               //2
            uint32 ritualPersistent;                        //3
            uint32 casterTargetSpell;                       //4
            uint32 casterTargetSpellTargets;                //5
            uint32 castersGrouped;                          //6
            uint32 ritualNoTargetCheck;                     //7
        } summoningRitual;
        //19 GAMEOBJECT_TYPE_MAILBOX - empty
        //20 GAMEOBJECT_TYPE_AUCTIONHOUSE
        struct
        {
            uint32 actionHouseID;                           //0
        } auctionhouse;
        //21 GAMEOBJECT_TYPE_GUARDPOST
        struct
        {
            uint32 creatureID;                              //0
            uint32 charges;                                 //1
        } guardpost;
        //22 GAMEOBJECT_TYPE_SPELLCASTER
        struct
        {
            uint32 spellId;                                 //0
            int32 charges;                                  //1
            uint32 partyOnly;                               //2
            uint32 allowMounted;                            //3 Is usable while on mount/vehicle. (0/1)
            uint32 large;                                   //4
            uint32 conditionID1;                            //5
        } spellcaster;
        //23 GAMEOBJECT_TYPE_MEETINGSTONE
        struct
        {
            uint32 minLevel;                                //0
            uint32 maxLevel;                                //1
            uint32 areaID;                                  //2
        } meetingstone;
        //24 GAMEOBJECT_TYPE_FLAGSTAND
        struct
        {
            uint32 lockId;                                  //0
            uint32 pickupSpell;                             //1
            uint32 radius;                                  //2
            uint32 returnAura;                              //3
            uint32 returnSpell;                             //4
            uint32 noDamageImmune;                          //5
            uint32 openTextID;                              //6
            uint32 losOK;                                   //7
        } flagstand;
        //25 GAMEOBJECT_TYPE_FISHINGHOLE
        struct
        {
            uint32 radius;                                  //0 how close bobber must land for sending loot
            uint32 lootId;                                  //1
            uint32 minSuccessOpens;                         //2
            uint32 maxSuccessOpens;                         //3
            uint32 lockId;                                  //4 -> Lock.dbc; possibly 1628 for all?
        } fishinghole;
        //26 GAMEOBJECT_TYPE_FLAGDROP
        struct
        {
            uint32 lockId;                                  //0
            uint32 eventID;                                 //1
            uint32 pickupSpell;                             //2
            uint32 noDamageImmune;                          //3
            uint32 openTextID;                              //4
        } flagdrop;
        //27 GAMEOBJECT_TYPE_MINI_GAME
        struct
        {
            uint32 gameType;                                //0
        } miniGame;
        //29 GAMEOBJECT_TYPE_CAPTURE_POINT
        struct
        {
            uint32 radius;                                  //0
            uint32 spell;                                   //1
            uint32 worldState1;                             //2
            uint32 worldState2;                             //3
            uint32 winEventID1;                             //4
            uint32 winEventID2;                             //5
            uint32 contestedEventID1;                       //6
            uint32 contestedEventID2;                       //7
            uint32 progressEventID1;                        //8
            uint32 progressEventID2;                        //9
            uint32 neutralEventID1;                         //10
            uint32 neutralEventID2;                         //11
            uint32 neutralPercent;                          //12
            uint32 worldState3;                             //13
            uint32 minSuperiority;                          //14
            uint32 maxSuperiority;                          //15
            uint32 minTime;                                 //16
            uint32 maxTime;                                 //17
            uint32 large;                                   //18
            uint32 highlight;                               //19
        } capturePoint;
        //30 GAMEOBJECT_TYPE_AURA_GENERATOR
        struct
        {
            uint32 startOpen;                               //0
            uint32 radius;                                  //1
            uint32 auraID1;                                 //2
            uint32 conditionID1;                            //3
            uint32 auraID2;                                 //4
            uint32 conditionID2;                            //5
            int32 serverOnly;                               //6
        } auraGenerator;
        //31 GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY
        struct
        {
            uint32 mapID;                                   //0
            uint32 difficulty;                              //1
        } dungeonDifficulty;
        //32 GAMEOBJECT_TYPE_DO_NOT_USE_YET
        struct
        {
            uint32 mapID;                                   //0
            uint32 difficulty;                              //1
        } doNotUseYet;
        //33 GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING
        struct
        {
            uint32 dmgPctState1;                            //0
            uint32 dmgPctState2;                            //1
            uint32 state1Name;                              //2
            uint32 state2Name;                              //3
        } destructibleBuilding;
        //34 GAMEOBJECT_TYPE_GUILDBANK - empty

        // not use for specific field access (only for output with loop by all filed), also this determinate max union size
        struct
        {
            uint32 data[24];
        } raw;
    };

    union
    {
        //6 GAMEOBJECT_TYPE_TRAP
        struct
        {
            uint32 triggerOn;
        } trapCustom;

        //18 GAMEOBJECT_TYPE_SUMMONING_RITUAL
        struct
        {
            uint32 delay;
        } summoningRitualCustom;

        struct
        {
            uint32 data[1];
        } rawCustom;
    };

    uint32 MinMoneyLoot;
    uint32 MaxMoneyLoot;
    uint32 ScriptId;

    // helpers
    bool IsDespawnAtAction() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:  return chest.consumable != 0;
            case GAMEOBJECT_TYPE_GOOBER: return goober.consumable != 0;
            default: return false;
        }
    }

    bool IsUsableMounted() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_MAILBOX: return true;
            case GAMEOBJECT_TYPE_BARBER_CHAIR: return false;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.allowMounted != 0;
            case GAMEOBJECT_TYPE_TEXT: return text.allowMounted != 0;
            case GAMEOBJECT_TYPE_GOOBER: return goober.allowMounted != 0;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spellcaster.allowMounted != 0;
            default: return false;
        }
    }

    uint32 GetLockId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.lockId;
            case GAMEOBJECT_TYPE_BUTTON:     return button.lockId;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.lockId;
            case GAMEOBJECT_TYPE_CHEST:      return chest.lockId;
            case GAMEOBJECT_TYPE_TRAP:       return trap.lockId;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.lockId;
            case GAMEOBJECT_TYPE_AREADAMAGE: return areadamage.lockId;
            case GAMEOBJECT_TYPE_CAMERA:     return camera.lockId;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.lockId;
            case GAMEOBJECT_TYPE_FISHINGHOLE: return fishinghole.lockId;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.lockId;
            default: return 0;
        }
    }

    bool GetDespawnPossibility() const                      // despawn at targeting of cast?
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_BUTTON:     return button.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_GOOBER:     return goober.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.noDamageImmune != 0;
            default: return true;
        }
    }

    bool CannotBeUsedUnderImmunity() const // Cannot be used/activated/looted by players under immunity effects (example: Divine Shield)
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:       return door.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_BUTTON:     return button.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_QUESTGIVER: return questgiver.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_CHEST:      return true;                           // All chests cannot be opened while immune on 3.3.5a
            case GAMEOBJECT_TYPE_GOOBER:     return goober.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGSTAND:  return flagstand.noDamageImmune != 0;
            case GAMEOBJECT_TYPE_FLAGDROP:   return flagdrop.noDamageImmune != 0;
            default: return false;
        }
    }

    uint32 GetCharges() const                               // despawn at uses amount
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_TRAP:        return trap.charges;
            case GAMEOBJECT_TYPE_GUARDPOST:   return guardpost.charges;
            case GAMEOBJECT_TYPE_SPELLCASTER: return spellcaster.charges;
            default: return 0;
        }
    }

    uint32 GetCooldown() const                              // not triggering at detection target or use until coolodwn expire
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_TRAP:        return trap.cooldown;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.cooldown;
            default: return 0;
        }
    }

    uint32 GetLinkedGameObjectEntry() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_BUTTON:      return button.linkedTrapId;
            case GAMEOBJECT_TYPE_CHEST:       return chest.linkedTrapId;
            case GAMEOBJECT_TYPE_SPELL_FOCUS: return spellFocus.linkedTrapId;
            case GAMEOBJECT_TYPE_GOOBER:      return goober.linkedTrapId;
            default: return 0;
        }
    }

    uint32 GetAutoCloseTime() const
    {
        uint32 autoCloseTime = 0;
        switch (type)
        {
            case GAMEOBJECT_TYPE_DOOR:          autoCloseTime = door.autoCloseTime; break;
            case GAMEOBJECT_TYPE_BUTTON:        autoCloseTime = button.autoCloseTime; break;
            case GAMEOBJECT_TYPE_TRAP:          autoCloseTime = trap.autoCloseTime; break;
            case GAMEOBJECT_TYPE_GOOBER:        autoCloseTime = goober.autoCloseTime; break;
            case GAMEOBJECT_TYPE_TRANSPORT:     autoCloseTime = transport.autoCloseTime; break;
            case GAMEOBJECT_TYPE_AREADAMAGE:    autoCloseTime = areadamage.autoCloseTime; break;
            default: break;
        }
        return autoCloseTime / 0x10000;
    }

    uint32 GetLootId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_CHEST:       return chest.lootId;
            case GAMEOBJECT_TYPE_FISHINGHOLE: return fishinghole.lootId;
            default: return 0;
        }
    }

    uint32 GetGossipMenuId() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_QUESTGIVER:    return questgiver.gossipID;
            case GAMEOBJECT_TYPE_GOOBER:        return goober.gossipID;
            default: return 0;
        }
    }

    bool IsLargeGameObject() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_BUTTON:            return button.large != 0;
            case GAMEOBJECT_TYPE_QUESTGIVER:        return questgiver.large != 0;
            case GAMEOBJECT_TYPE_GENERIC:           return _generic.large != 0;
            case GAMEOBJECT_TYPE_TRAP:              return trap.large != 0;
            case GAMEOBJECT_TYPE_SPELL_FOCUS:       return spellFocus.large != 0;
            case GAMEOBJECT_TYPE_GOOBER:            return goober.large != 0;
            case GAMEOBJECT_TYPE_TRANSPORT:         return true;
            case GAMEOBJECT_TYPE_SPELLCASTER:       return spellcaster.large != 0;
            case GAMEOBJECT_TYPE_CAPTURE_POINT:     return capturePoint.large != 0;
            default: return false;
        }
    }

    bool IsServerOnly() const
    {
        switch (type)
        {
            case GAMEOBJECT_TYPE_GENERIC: return _generic.serverOnly;
            case GAMEOBJECT_TYPE_TRAP: return trap.serverOnly;
            case GAMEOBJECT_TYPE_SPELL_FOCUS: return spellFocus.serverOnly;
            case GAMEOBJECT_TYPE_AURA_GENERATOR: return auraGenerator.serverOnly;
            default: return false;
        }
    }
};

// pre-defined targeting for spells
struct SpellTargetEntry
{
    uint32 spellId;
    uint32 type;
    uint32 targetEntry;
    uint32 inverseEffectMask;

    bool CanNotHitWithSpellEffect(SpellEffectIndex effect) const { return (inverseEffectMask & (1 << effect)) != 0; }
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

#endif

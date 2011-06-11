/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
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

#include "Common.h"
#include "DBCEnums.h"
#include "Path.h"
#include "Platform/Define.h"

#include <map>
#include <set>
#include <vector>

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
                                                            // 29-32    m_liquidTypeID[4]
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
    //char*     name[16];                                   // 4-19     m_name_lang
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
    //uint32 Id;                                            // 0        m_ID
    uint32 RaceClassGender;                                 // 1        m_raceID m_classID m_sexID m_outfitID (UNIT_FIELD_BYTES_0 & 0x00FFFFFF) comparable (0 byte = race, 1 byte = class, 2 byte = gender)
    int32 ItemId[MAX_OUTFIT_ITEMS];                         // 2-13     m_ItemID
    //int32 ItemDisplayId[MAX_OUTFIT_ITEMS];                // 14-25    m_DisplayItemID not required at server side
    //int32 ItemInventorySlot[MAX_OUTFIT_ITEMS];            // 26-37    m_InventoryType not required at server side
    //uint32 Unknown1;                                      // 38, unique values (index-like with gaps ordered in other way as ids)
    //uint32 Unknown2;                                      // 39
    //uint32 Unknown3;                                      // 40
};

struct CharTitlesEntry
{
    uint32  ID;                                             // 0,       m_ID
    //uint32      unk1;                                     // 1        m_Condition_ID
    char*   name[16];                                       // 2-17     m_name_lang
                                                            // 18 string flags
    //char*       name2[16];                                // 19-34    m_name1_lang
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
    //char*       name[16];                                 // 20-35    m_shortcut_lang
                                                            // 36 string flags
};

struct ChrClassesEntry
{
    uint32  ClassID;                                        // 0        m_ID
    //uint32 flags;                                         // 1 unknown
    uint32  powerType;                                      // 2        m_DisplayPower
                                                            // 3        m_petNameToken
    char const* name[16];                                   // 4-19     m_name_lang
                                                            // 20 string flags
    //char*       nameFemale[16];                           // 21-36    m_name_female_lang
                                                            // 37 string flags
    //char*       nameNeutralGender[16];                    // 38-53    m_name_male_lang
                                                            // 54 string flags
                                                            // 55       m_filename
    uint32  spellfamily;                                    // 56       m_spellClassSet
    //uint32 flags2;                                        // 57       m_flags (0x08 HasRelicSlot)
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
    //char*       nameFemale[16];                           // 31-46    m_name_female_lang
                                                            // 47 string flags
    //char*       nameNeutralGender[16];                    // 48-63    m_name_male_lang
                                                            // 64 string flags
                                                            // 65-66    m_facialHairCustomization[2]
                                                            // 67       m_hairCustomization
    uint32      expansion;                                  // 68       m_required_expansion
};

/*struct CinematicCameraEntry
{
    uint32      id;                                         // 0        m_ID
    char*       filename;                                   // 1        m_model
    uint32      soundid;                                    // 2        m_soundID
    float       start_x;                                    // 3        m_originX
    float       start_y;                                    // 4        m_originY
    float       start_z;                                    // 5        m_originZ
    float       unk6;                                       // 6        m_originFacing
};*/

struct CinematicSequencesEntry
{
    uint32      Id;                                         // 0        m_ID
    //uint32      unk1;                                     // 1        m_soundID
    //uint32      cinematicCamera;                          // 2        m_camera[8]
};

struct CreatureDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
                                                            // 1        m_modelID
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
    //uint32    Gender;                                     // 2        m_DisplaySexID
    //uint32    SkinColor;                                  // 3        m_SkinID
    //uint32    FaceType;                                   // 4        m_FaceID
    //uint32    HairType;                                   // 5        m_HairStyleID
    //uint32    HairStyle;                                  // 6        m_HairColorID
    //uint32    BeardStyle;                                 // 7        m_FacialHairID
    //uint32    Equipment[11];                              // 8-18     m_NPCItemDisplay equipped static items EQUIPMENT_SLOT_HEAD..EQUIPMENT_SLOT_HANDS, client show its by self
    //uint32    CanEquip;                                   // 19       m_flags 0..1 Can equip additional things when used for players
    //char*                                                 // 20       m_BakeName CreatureDisplayExtra-*.blp
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

#define MAX_CREATURE_SPELL_DATA_SLOT 4

struct CreatureSpellDataEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    spellId[MAX_CREATURE_SPELL_DATA_SLOT];        // 1-4      m_spells[4]
    //uint32    availability[MAX_CREATURE_SPELL_DATA_SLOT]; // 4-7      m_availability[4]
};

struct CreatureTypeEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*   Name[16];                                     // 1-16     m_name_lang
                                                            // 17 string flags
    //uint32    no_expirience;                              // 18       m_flags
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
    //char*   Name;                                         // 1        m_EmoteSlashCommand
    //uint32  AnimationId;                                  // 2        m_AnimID
    uint32  Flags;                                          // 3        m_EmoteFlags
    uint32  EmoteType;                                      // 4        m_EmoteSpecProc (determine how emote are shown)
    uint32  UnitStandState;                                 // 5        m_EmoteSpecProcParam
    //uint32  SoundId;                                      // 6        m_EventSoundID
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
    char*       name[16];                                   // 19-34    m_name_lang
                                                            // 35 string flags
    //char*     description[16];                            // 36-51    m_description_lang
                                                            // 52 string flags

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
};

struct FactionTemplateEntry
{
    uint32      ID;                                         // 0
    uint32      faction;                                    // 1
    uint32      factionFlags;                               // 2 specific flags for that faction
    uint32      ourMask;                                    // 3 if mask set (see FactionMasks) then faction included in masked team
    uint32      friendlyMask;                               // 4 if mask set (see FactionMasks) then faction friendly to masked team
    uint32      hostileMask;                                // 5 if mask set (see FactionMasks) then faction hostile to masked team
    uint32      enemyFaction[4];                            // 6-9
    uint32      friendFaction[4];                           // 10-13
    //-------------------------------------------------------  end structure

    // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return false;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return true;
        }
        return (friendlyMask & entry.ourMask) || (ourMask & entry.friendlyMask);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if(entry.faction)
        {
            for(int i = 0; i < 4; ++i)
                if (enemyFaction[i]  == entry.faction)
                    return true;
            for(int i = 0; i < 4; ++i)
                if (friendFaction[i] == entry.faction)
                    return false;
        }
        return (hostileMask & entry.ourMask) != 0;
    }
    bool IsHostileToPlayers() const { return (hostileMask & FACTION_MASK_PLAYER) !=0; }
    bool IsNeutralToAll() const
    {
        for(int i = 0; i < 4; ++i)
            if (enemyFaction[i] != 0)
                return false;
        return hostileMask == 0 && friendlyMask == 0;
    }
    bool IsContestedGuardFaction() const { return (factionFlags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD)!=0; }
};

struct GameObjectDisplayInfoEntry
{
    uint32      Displayid;                                  // 0        m_ID
    // char* filename;                                      // 1        m_modelName
                                                            // 2-11     m_Sound
    float  unknown12;                                       // 12       m_geoBoxMinX (use first value as interact dist, mostly in hacks way)
                                                            // 13       m_geoBoxMinY
                                                            // 14       m_geoBoxMinZ
                                                            // 15       m_geoBoxMaxX
                                                            // 16       m_geoBoxMaxY
                                                            // 17       m_geoBoxMaxZ
};

struct GemPropertiesEntry
{
    uint32      ID;                                         //          m_id
    uint32      spellitemenchantement;                      //          m_enchant_id
                                                            //          m_maxcount_inv
                                                            //          m_maxcount_item
    uint32      color;                                      //          m_type
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

//struct GtOCTRegenMPEntry
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
    //char*     name[16]                                    // 1-16     m_name_lang
    //                                                      // 17       name flags
};

struct ItemDisplayInfoEntry
{
    uint32      ID;
    uint32      randomPropertyChance;
};

//struct ItemCondExtCostsEntry
//{
//    uint32      ID;
//    uint32      condExtendedCost;                           // ItemPrototype::CondExtendedCost
//    uint32      itemextendedcostentry;                      // ItemPrototype::ExtendedCost
//    uint32      arenaseason;                                // arena season number(1-4)
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
    //char*     internalName                                // 1        m_Name
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
    //uint32    id                                          // 0        m_ID
    char*     name[16];                                     // 1-16     m_name_lang
                                                            // 17 string flags
    //uint32    itemId[17];                                 // 18-34    m_itemID
    uint32    spells[8];                                    // 35-42    m_setSpellID
    uint32    items_to_triggerspell[8];                     // 43-50    m_setThreshold
    uint32    required_skill_id;                            // 51       m_requiredSkill
    uint32    required_skill_value;                         // 52       m_requiredSkillRank
};

#define MAX_LOCK_CASE 8

struct LockEntry
{
    uint32      ID;                                         // 0        m_ID
    uint32      Type[MAX_LOCK_CASE];                        // 1-5      m_Type
    uint32      Index[MAX_LOCK_CASE];                       // 9-16     m_Index
    uint32      Skill[MAX_LOCK_CASE];                       // 17-24    m_Skill
    //uint32      Action[MAX_LOCK_CASE];                    // 25-32    m_Action
};

struct MailTemplateEntry
{
    uint32      ID;                                         // 0        m_ID
    //char*       subject[16];                              // 1-16     m_subject_lang
                                                            // 17 string flags
    char*       content[16];                                // 18-33    m_body_lang
};

struct MapEntry
{
    uint32  MapID;                                          // 0        m_ID
    //char*       internalname;                             // 1        m_Directory
    uint32  map_type;                                       // 2        m_InstanceType
    //uint32 isPvP;                                         // 3        m_PVP 0 or 1 for battlegrounds (not arenas)
    char*   name[16];                                       // 4-19     m_MapName_lang
                                                            // 20 string flags
                                                            // 21-23 unused (something PvPZone related - levels?)
                                                            // 24-26
    uint32  linked_zone;                                    // 27       m_areaTableID
    //char*     hordeIntro[16];                             // 28-43    m_MapDescription0_lang
                                                            // 44 string flags
    //char*     allianceIntro[16];                          // 45-60    m_MapDescription1_lang
                                                            // 61 string flags
    uint32  multimap_id;                                    // 62       m_LoadingScreenID (LoadingScreens.dbc)
                                                            // 63-64 not used
    //float   BattlefieldMapIconScale;                      // 65       m_minimapIconScale
    //chat*     unknownText1                                // 66-81 unknown empty text fields, possible normal Intro text.
                                                            // 82 text flags
    //chat*     heroicIntroText                             // 83-98 heroic mode requirement text
                                                            // 99 text flags
    //chat*     unknownText2                                // 100-115 unknown empty text fields
                                                            // 116 text flags
    int32   ghost_entrance_map;                             // 117      m_corpseMapID map_id of entrance map in ghost mode (continent always and in most cases = normal entrance)
    float   ghost_entrance_x;                               // 118      m_corpseX entrance x coordinate in ghost mode  (in most cases = normal entrance)
    float   ghost_entrance_y;                               // 119      m_corpseY entrance y coordinate in ghost mode  (in most cases = normal entrance)
    uint32 resetTimeRaid;                                   // 120
    uint32 resetTimeHeroic;                                 // 121
                                                            // 122      all 0
    //uint32  timeOfDayOverride;                            // 123      m_timeOfDayOverride
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

    bool IsMountAllowed() const
    {
        return !IsDungeon() ||
            MapID==209 || MapID==269 || MapID==309 ||       // TanarisInstance, CavernsOfTime, Zul'gurub
            MapID==509 || MapID==534 || MapID==560 ||       // AhnQiraj, HyjalPast, HillsbradPast
            MapID==568 || MapID==580;                       // ZulAman, Sunwell Plateau
    }

    bool IsContinent() const
    {
        return MapID == 0 || MapID == 1 || MapID == 530;
    }
};

struct QuestSortEntry
{
    uint32      id;                                         // 0        m_ID
    //char*       name[16];                                 // 1-16     m_SortName_lang
                                                            // 17 string flags
};

struct RandomPropertiesPointsEntry
{
    //uint32  Id;                                           // 0        m_ID
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
    //uint32    id;                                         // 0        m_ID
    uint32    skillId;                                      // 1        m_skillID
    uint32    raceMask;                                     // 2        m_raceMask
    uint32    classMask;                                    // 3        m_classMask
    uint32    flags;                                        // 4        m_flags
    uint32    reqLevel;                                     // 5        m_minLevel
    //uint32    skillTierId;                                // 6        m_skillTierID
    //uint32    skillCostID;                                // 7        m_skillCostIndex
};

/*struct SkillTiersEntry{
    uint32    id;                                           // 0        m_ID
    uint32    skillValue[16];                               // 1-17     m_cost
    uint32    maxSkillValue[16];                            // 18-3     m_valueMax
};*/

struct SkillLineEntry
{
    uint32    id;                                           // 0        m_ID
    int32     categoryId;                                   // 1        m_categoryID
    //uint32    skillCostID;                                // 2        m_skillCostsID
    char*     name[16];                                     // 3-18     m_displayName_lang
                                                            // 19 string flags
    //char*     description[16];                            // 20-35    m_description_lang
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
    //uint32    racemaskNot;                                // 5 always 0 in 2.4.2
    //uint32    classmaskNot;                               // 6 always 0 in 2.4.2
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
    //uint32    Type;                                       // 1        m_soundType
    //char*     InternalName;                               // 2        m_name
    //char*     FileName[10];                               // 3-12     m_File[10]
    //uint32    Unk13[10];                                  // 13-22    m_Freq[10]
    //char*     Path;                                       // 23       m_DirectoryBase
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
    bool operator! () const { return Empty(); }
    operator void const* () const { return Empty() ? NULL : this; }// for allow normal use in if(mask)

    bool IsFitToFamilyMask(uint64 familyFlags) const
    {
        return Flags & familyFlags;
    }

    bool IsFitToFamilyMask(ClassFamilyMask const& mask) const
    {
        return Flags & mask.Flags;
    }

    uint64 operator& (uint64 mask) const                     // possible will removed at finish convertion code use IsFitToFamilyMask
    {
        return Flags & mask;
    }

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
    uint32    Id;                                           // 0        m_ID
    uint32    Category;                                     // 1        m_category
    //uint32     castUI                                     // 2 not used
    uint32    Dispel;                                       // 3        m_dispelType
    uint32    Mechanic;                                     // 4        m_mechanic
    uint32    Attributes;                                   // 5        m_attributes
    uint32    AttributesEx;                                 // 6        m_attributesEx
    uint32    AttributesEx2;                                // 7        m_attributesExB
    uint32    AttributesEx3;                                // 8        m_attributesExC
    uint32    AttributesEx4;                                // 9        m_attributesExD
    uint32    AttributesEx5;                                // 10       m_attributesExE
    uint32    AttributesEx6;                                // 11       m_attributesExF
    uint32    Stances;                                      // 12       m_shapeshiftMask
    uint32    StancesNot;                                   // 13       m_shapeshiftExclude
    uint32    Targets;                                      // 14       m_targets
    uint32    TargetCreatureType;                           // 15       m_targetCreatureType
    uint32    RequiresSpellFocus;                           // 16       m_requiresSpellFocus
    uint32    FacingCasterFlags;                            // 17       m_facingCasterFlags
    uint32    CasterAuraState;                              // 18       m_casterAuraState
    uint32    TargetAuraState;                              // 19       m_targetAuraState
    uint32    CasterAuraStateNot;                           // 20       m_excludeCasterAuraState
    uint32    TargetAuraStateNot;                           // 21       m_excludeTargetAuraState
    uint32    CastingTimeIndex;                             // 22       m_castingTimeIndex
    uint32    RecoveryTime;                                 // 23       m_recoveryTime
    uint32    CategoryRecoveryTime;                         // 24       m_categoryRecoveryTime
    uint32    InterruptFlags;                               // 25       m_interruptFlags
    uint32    AuraInterruptFlags;                           // 26       m_auraInterruptFlags
    uint32    ChannelInterruptFlags;                        // 27       m_channelInterruptFlags
    uint32    procFlags;                                    // 28       m_procTypeMask
    uint32    procChance;                                   // 29       m_procChance
    uint32    procCharges;                                  // 30       m_procCharges
    uint32    maxLevel;                                     // 31       m_maxLevel
    uint32    baseLevel;                                    // 32       m_baseLevel
    uint32    spellLevel;                                   // 33       m_spellLevel
    uint32    DurationIndex;                                // 34       m_durationIndex
    uint32    powerType;                                    // 35       m_powerType
    uint32    manaCost;                                     // 36       m_manaCost
    uint32    manaCostPerlevel;                             // 37       m_manaCostPerLevel
    uint32    manaPerSecond;                                // 38       m_manaPerSecond
    uint32    manaPerSecondPerLevel;                        // 39       m_manaPerSecondPerLevel
    uint32    rangeIndex;                                   // 40       m_rangeIndex
    float     speed;                                        // 41       m_speed
    //uint32    modalNextSpell;                             // 42       m_modalNextSpell not used
    uint32    StackAmount;                                  // 43       m_cumulativeAura
    uint32    Totem[MAX_SPELL_TOTEMS];                      // 44-45    m_totem
    int32     Reagent[MAX_SPELL_REAGENTS];                  // 46-53    m_reagent
    uint32    ReagentCount[MAX_SPELL_REAGENTS];             // 54-61    m_reagentCount
    int32     EquippedItemClass;                            // 62       m_equippedItemClass (value)
    int32     EquippedItemSubClassMask;                     // 63       m_equippedItemSubclass (mask)
    int32     EquippedItemInventoryTypeMask;                // 64       m_equippedItemInvTypes (mask)
    uint32    Effect[MAX_EFFECT_INDEX];                     // 65-67    m_effect
    int32     EffectDieSides[MAX_EFFECT_INDEX];             // 68-70    m_effectDieSides
    uint32    EffectBaseDice[MAX_EFFECT_INDEX];             // 71-73
    float     EffectDicePerLevel[MAX_EFFECT_INDEX];         // 74-76
    float     EffectRealPointsPerLevel[MAX_EFFECT_INDEX];   // 77-79    m_effectRealPointsPerLevel
    int32     EffectBasePoints[MAX_EFFECT_INDEX];           // 80-82    m_effectBasePoints (don't must be used in spell/auras explicitly, must be used cached Spell::m_currentBasePoints)
    uint32    EffectMechanic[MAX_EFFECT_INDEX];             // 83-85    m_effectMechanic
    uint32    EffectImplicitTargetA[MAX_EFFECT_INDEX];      // 86-88    m_implicitTargetA
    uint32    EffectImplicitTargetB[MAX_EFFECT_INDEX];      // 89-91    m_implicitTargetB
    uint32    EffectRadiusIndex[MAX_EFFECT_INDEX];          // 92-94    m_effectRadiusIndex - spellradius.dbc
    uint32    EffectApplyAuraName[MAX_EFFECT_INDEX];        // 95-97    m_effectAura
    uint32    EffectAmplitude[MAX_EFFECT_INDEX];            // 98-100   m_effectAuraPeriod
    float     EffectMultipleValue[MAX_EFFECT_INDEX];        // 101-103  m_effectAmplitude
    uint32    EffectChainTarget[MAX_EFFECT_INDEX];          // 104-106  m_effectChainTargets
    uint32    EffectItemType[MAX_EFFECT_INDEX];             // 107-109  m_effectItemType
    int32     EffectMiscValue[MAX_EFFECT_INDEX];            // 110-112  m_effectMiscValue
    int32     EffectMiscValueB[MAX_EFFECT_INDEX];           // 113-115  m_effectMiscValueB
    uint32    EffectTriggerSpell[MAX_EFFECT_INDEX];         // 116-118  m_effectTriggerSpell
    float     EffectPointsPerComboPoint[MAX_EFFECT_INDEX];  // 119-121  m_effectPointsPerCombo
    uint32    SpellVisual;                                  // 122      m_spellVisualID
    //uint32    SpellVisual2;                               // 123 not used
    uint32    SpellIconID;                                  // 124      m_spellIconID
    uint32    activeIconID;                                 // 125      m_activeIconID
    //uint32    spellPriority;                              // 126      m_spellPriority not used
    char*     SpellName[16];                                // 127-142  m_name_lang
    //uint32    SpellNameFlag;                              // 143      m_name_flag not used
    char*     Rank[16];                                     // 144-159  m_nameSubtext_lang
    //uint32    RankFlags;                                  // 160      m_nameSubtext_flag not used
    //char*     Description[16];                            // 161-176  m_description_lang not used
    //uint32    DescriptionFlags;                           // 177      m_description_flag not used
    //char*     ToolTip[16];                                // 178-193  m_auraDescription_lang not used
    //uint32    ToolTipFlags;                               // 194      m_auraDescription_flag not used
    uint32    ManaCostPercentage;                           // 195      m_manaCostPct
    uint32    StartRecoveryCategory;                        // 196      m_startRecoveryCategory
    uint32    StartRecoveryTime;                            // 197      m_startRecoveryTime
    uint32    MaxTargetLevel;                               // 198      m_maxTargetLevel
    uint32    SpellFamilyName;                              // 199      m_spellClassSet
    ClassFamilyMask SpellFamilyFlags;                       // 200-201  m_spellClassMask
    uint32    MaxAffectedTargets;                           // 202      m_maxTargets
    uint32    DmgClass;                                     // 203      m_defenseType
    uint32    PreventionType;                               // 204      m_preventionType
    //uint32    StanceBarOrder;                             // 205      m_stanceBarOrder not used
    float     DmgMultiplier[MAX_EFFECT_INDEX];              // 206-208  m_effectChainAmplitude
    //uint32    MinFactionId;                               // 209      m_minFactionID not used
    //uint32    MinReputation;                              // 210      m_minReputation not used
    //uint32    RequiredAuraVision;                         // 211      m_requiredAuraVision not used
    uint32    TotemCategory[MAX_SPELL_TOTEM_CATEGORIES];    // 212-213  m_requiredTotemCategoryID
    uint32    AreaId;                                       // 214
    uint32    SchoolMask;                                   // 215      m_schoolMask

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

    private:
        // prevent creating custom entries (copy data from original in fact)
        SpellEntry(SpellEntry const&);                      // DON'T must have implementation
};

struct SpellCastTimesEntry
{
    uint32    ID;                                           // 0        m_ID
    int32     CastTime;                                     // 1        m_base
    //float     CastTimePerLevel;                           // 2        m_perLevel
    //int32     MinCastTime;                                // 3        m_minimum
};

struct SpellFocusObjectEntry
{
    uint32    ID;                                           // 0        m_ID
    //char*     Name[16];                                   // 1-15     m_name_lang
                                                            // 16 string flags
};

struct SpellRadiusEntry
{
    uint32    ID;                                           //          m_ID
    float     Radius;                                       //          m_radius
                                                            //          m_radiusPerLevel
    //float     RadiusMax;                                  //          m_radiusMax
};

struct SpellRangeEntry
{
    uint32    ID;                                           // 0        m_ID
    float     minRange;                                     // 1        m_rangeMin
    float     maxRange;                                     // 2        m_rangeMax
    //uint32  Flags;                                        // 3        m_flags
    //char*   Name[16];                                     // 4-19     m_displayName_lang
    //uint32  NameFlags;                                    // 20 string flags
    //char*   ShortName[16];                                // 21-36    m_displayNameShort_lang
    //uint32  NameFlags;                                    // 37 string flags
};

struct SpellShapeshiftFormEntry
{
    uint32 ID;                                              // 0        m_ID
    //uint32 buttonPosition;                                // 1        m_bonusActionBar
    //char*  Name[16];                                      // 2-17     m_name_lang
    //uint32 NameFlags;                                     // 18 string flags
    uint32 flags1;                                          // 19       m_flags
    int32  creatureType;                                    // 20       m_creatureType <=0 humanoid, other normal creature types
    //uint32 unk1;                                          // 21       m_attackIconID
    uint32 attackSpeed;                                     // 22       m_combatRoundTime
    uint32 modelID_A;                                       // 23       m_creatureDisplayID[4]
    //uint32 modelID_H;                                     // 24 horde modelid (but all 0)
    //uint32 unk3;                                          // 25 unused always 0
    //uint32 unk4;                                          // 26 unused always 0
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
    //uint32      amount2[3]                                // 7-9      m_effectPointsMax[3]
    uint32      spellid[3];                                 // 10-12    m_effectArg[3]
    char*       description[16];                            // 13-28    m_name_lang[16]
    //uint32      descriptionFlags;                         // 29 string flags
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
    //uint32  needAddInSpellBook;                           // 19       m_flags also need disable higest ranks on reset talent tree
    uint32    DependsOnSpell;                               // 20       m_requiredSpellID req.spell
};

struct TalentTabEntry
{
    uint32  TalentTabID;                                    // 0        m_ID
    //char* name[16];                                       // 1-16     m_name_lang
    //uint32  nameFlags;                                    // 17 string flags
    //unit32  spellicon;                                    // 18       m_spellIconID
                                                            // 19       m_raceMask
    uint32  ClassMask;                                      // 20       m_classMask
    uint32  tabpage;                                        // 21       m_orderIndex
    //char* internalname;                                   // 22       m_backgroundFile
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
    //char*   name[16];                                     // 1-16     m_name_lang
                                                            // 17 string flags
    uint32    categoryType;                                 // 18       m_totemCategoryType (one for specialization)
    uint32    categoryMask;                                 // 19       m_totemCategoryMask (compatibility mask for same type: different for totems, compatible from high to low for rods)
};

struct WMOAreaTableEntry
{
    uint32 Id;                                              // 0        m_ID index
    int32 rootId;                                           // 1        m_WMOID used in root WMO
    int32 adtId;                                            // 2        m_NameSetID used in adt file
    int32 groupId;                                          // 3        m_WMOGroupID used in group WMO
    //uint32 field4;                                        // 4        m_SoundProviderPref
    //uint32 field5;                                        // 5        m_SoundProviderPrefUnderwater
    //uint32 field6;                                        // 6        m_AmbienceID
    //uint32 field7;                                        // 7        m_ZoneMusic
    //uint32 field8;                                        // 8        m_IntroSound
    uint32 Flags;                                           // 9        m_flags (used for indoor/outdoor determination)
    uint32 areaId;                                          // 10       m_AreaTableID (AreaTable.dbc)
    //char *Name[16];                                       //          m_AreaName_lang
    //uint32 nameFlags;
};

struct WorldMapAreaEntry
{
    //uint32  ID;                                           // 0        m_ID
    uint32  map_id;                                         // 1        m_mapID
    uint32  area_id;                                        // 2        m_areaID index (continent 0 areas ignored)
    //char* internal_name                                   // 3        m_areaName
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
    //uint32    worldMapAreaId;                             // 1        m_mapAreaID (WorldMapArea.dbc)
    uint32    areatableID[MAX_WORLD_MAP_OVERLAY_AREA_IDX];  // 2-5      m_areaID
                                                            // 6        m_mapPointX
                                                            // 7        m_mapPointY
    //char* internal_name                                   // 8        m_textureName
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

struct WorldSafeLocsEntry
{
    uint32    ID;                                           // 0        m_ID
    uint32    map_id;                                       // 1        m_continent
    float     x;                                            // 2        m_locX
    float     y;                                            // 3        m_locY
    float     z;                                            // 4        m_locZ
    //char*   name[16]                                      // 5-20     m_AreaName_lang
                                                            // 21 string flags
};

// GCC have alternative #pragma pack() syntax and old gcc version not support pack(pop), also any gcc version not support it at some platform
#if defined( __GNUC__ )
#pragma pack()
#else
#pragma pack(pop)
#endif

typedef std::set<uint32> SpellCategorySet;
typedef std::map<uint32,SpellCategorySet > SpellCategoryStore;
typedef std::set<uint32> PetFamilySpellsSet;
typedef std::map<uint32,PetFamilySpellsSet > PetFamilySpellsStore;

// Structures not used for casting to loaded DBC data and not required then packing
struct TalentSpellPos
{
    TalentSpellPos() : talent_id(0), rank(0) {}
    TalentSpellPos(uint16 _talent_id, uint8 _rank) : talent_id(_talent_id), rank(_rank) {}

    uint16 talent_id;
    uint8  rank;
};

typedef std::map<uint32,TalentSpellPos> TalentSpellPosMap;

struct TaxiPathBySourceAndDestination
{
    TaxiPathBySourceAndDestination() : ID(0),price(0) {}
    TaxiPathBySourceAndDestination(uint32 _id,uint32 _price) : ID(_id),price(_price) {}

    uint32    ID;
    uint32    price;
};
typedef std::map<uint32,TaxiPathBySourceAndDestination> TaxiPathSetForSource;
typedef std::map<uint32,TaxiPathSetForSource> TaxiPathSetBySource;

struct TaxiPathNodePtr
{
    TaxiPathNodePtr() : i_ptr(NULL) {}
    TaxiPathNodePtr(TaxiPathNodeEntry const* ptr) : i_ptr(ptr) {}

    TaxiPathNodeEntry const* i_ptr;

    operator TaxiPathNodeEntry const& () const { return *i_ptr; }
};

typedef Path<TaxiPathNodePtr,TaxiPathNodeEntry const> TaxiPathNodeList;
typedef std::vector<TaxiPathNodeList> TaxiPathNodesByPath;

#define TaxiMaskSize 16
typedef uint32 TaxiMask[TaxiMaskSize];
#endif

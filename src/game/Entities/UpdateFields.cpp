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

#include "UpdateFields.h"
#include "Log/Log.h"
#include "ObjectGuid.h"
#include <array>
#include <vector>

// Auto generated file
// Patch: 2.4.3
// Build: 8606

static std::array<UpdateFieldData, 399> const g_updateFieldsData =
{{
        // enum EObjectFields
    { TYPEMASK_OBJECT       , "OBJECT_FIELD_GUID"                               , 0x0  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT       , "OBJECT_FIELD_TYPE"                               , 0x2  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT       , "OBJECT_FIELD_ENTRY"                              , 0x3  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT       , "OBJECT_FIELD_SCALE_X"                            , 0x4  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_OBJECT       , "OBJECT_FIELD_PADDING"                            , 0x5  , 1  , UF_TYPE_INT      , UF_FLAG_NONE },
    { TYPEMASK_OBJECT       , "OBJECT_END"                                      , 0x6  , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // EContainerFields
    { TYPEMASK_CONTAINER    , "CONTAINER_FIELD_NUM_SLOTS"                       , 0x3C , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_CONTAINER    , "CONTAINER_ALIGN_PAD"                             , 0x3D , 1  , UF_TYPE_BYTES    , UF_FLAG_NONE },
    { TYPEMASK_CONTAINER    , "CONTAINER_FIELD_SLOT_1"                          , 0x3E , 72 , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_CONTAINER    , "CONTAINER_END"                                   , 0x86 , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum EItemFields
    { TYPEMASK_ITEM         , "ITEM_FIELD_OWNER"                                , 0x6  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_CONTAINED"                            , 0x8  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_CREATOR"                              , 0xA  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_GIFTCREATOR"                          , 0xC  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_STACK_COUNT"                          , 0xE  , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM         , "ITEM_FIELD_DURATION"                             , 0xF  , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM         , "ITEM_FIELD_SPELL_CHARGES"                        , 0x10 , 5  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM         , "ITEM_FIELD_FLAGS"                                , 0x15 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_ENCHANTMENT"                          , 0x16 , 33 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_PROPERTY_SEED"                        , 0x37 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_RANDOM_PROPERTIES_ID"                 , 0x38 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_ITEM         , "ITEM_FIELD_ITEM_TEXT_ID"                         , 0x39 , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY },
    { TYPEMASK_ITEM         , "ITEM_FIELD_DURABILITY"                           , 0x3A , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM         , "ITEM_FIELD_MAXDURABILITY"                        , 0x3B , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY + UF_FLAG_UNK2 },
    { TYPEMASK_ITEM         , "ITEM_END"                                        , 0x3C , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum EUnitFields
    { TYPEMASK_UNIT         , "UNIT_FIELD_CHARM"                                , 0x6  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_SUMMON"                               , 0x8  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_CHARMEDBY"                            , 0xA  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_SUMMONEDBY"                           , 0xC  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_CREATEDBY"                            , 0xE  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_TARGET"                               , 0x10 , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PERSUADED"                            , 0x12 , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_CHANNEL_OBJECT"                       , 0x14 , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_HEALTH"                               , 0x16 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER1"                               , 0x17 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER2"                               , 0x18 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER3"                               , 0x19 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER4"                               , 0x1A , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER5"                               , 0x1B , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXHEALTH"                            , 0x1C , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXPOWER1"                            , 0x1D , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXPOWER2"                            , 0x1E , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXPOWER3"                            , 0x1F , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXPOWER4"                            , 0x20 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXPOWER5"                            , 0x21 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_LEVEL"                                , 0x22 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_FACTIONTEMPLATE"                      , 0x23 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BYTES_0"                              , 0x24 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_VIRTUAL_ITEM_SLOT_DISPLAY"                  , 0x25 , 3  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_VIRTUAL_ITEM_INFO"                          , 0x28 , 6  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_FLAGS"                                , 0x2E , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_FLAGS_2"                              , 0x2F , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_AURA"                                 , 0x30 , 56 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_AURAFLAGS"                            , 0x68 , 14 , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_AURALEVELS"                           , 0x76 , 14 , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_AURAAPPLICATIONS"                     , 0x84 , 14 , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_AURASTATE"                            , 0x92 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BASEATTACKTIME"                       , 0x93 , 2  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RANGEDATTACKTIME"                     , 0x95 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BOUNDINGRADIUS"                       , 0x96 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_COMBATREACH"                          , 0x97 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_DISPLAYID"                            , 0x98 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NATIVEDISPLAYID"                      , 0x99 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MOUNTDISPLAYID"                       , 0x9A , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MINDAMAGE"                            , 0x9B , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXDAMAGE"                            , 0x9C , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MINOFFHANDDAMAGE"                     , 0x9D , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXOFFHANDDAMAGE"                     , 0x9E , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BYTES_1"                              , 0x9F , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PETNUMBER"                            , 0xA0 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PET_NAME_TIMESTAMP"                   , 0xA1 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PETEXPERIENCE"                        , 0xA2 , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PETNEXTLEVELEXP"                      , 0xA3 , 1  , UF_TYPE_INT      , UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_DYNAMIC_FLAGS"                              , 0xA4 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT         , "UNIT_CHANNEL_SPELL"                              , 0xA5 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_MOD_CAST_SPEED"                             , 0xA6 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_CREATED_BY_SPELL"                           , 0xA7 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_NPC_FLAGS"                                  , 0xA8 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_UNIT         , "UNIT_NPC_EMOTESTATE"                             , 0xA9 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_TRAINING_POINTS"                            , 0xAA , 1  , UF_TYPE_TWO_SHORT, UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_STAT0"                                , 0xAB , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_STAT1"                                , 0xAC , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_STAT2"                                , 0xAD , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_STAT3"                                , 0xAE , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_STAT4"                                , 0xAF , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POSSTAT0"                             , 0xB0 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POSSTAT1"                             , 0xB1 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POSSTAT2"                             , 0xB2 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POSSTAT3"                             , 0xB3 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POSSTAT4"                             , 0xB4 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NEGSTAT0"                             , 0xB5 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NEGSTAT1"                             , 0xB6 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NEGSTAT2"                             , 0xB7 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NEGSTAT3"                             , 0xB8 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_NEGSTAT4"                             , 0xB9 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RESISTANCES"                          , 0xBA , 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY + UF_FLAG_SPECIAL_INFO },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RESISTANCEBUFFMODSPOSITIVE"           , 0xC1 , 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RESISTANCEBUFFMODSNEGATIVE"           , 0xC8 , 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BASE_MANA"                            , 0xCF , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BASE_HEALTH"                          , 0xD0 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_BYTES_2"                              , 0xD1 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_UNIT         , "UNIT_FIELD_ATTACK_POWER"                         , 0xD2 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_ATTACK_POWER_MODS"                    , 0xD3 , 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_ATTACK_POWER_MULTIPLIER"              , 0xD4 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RANGED_ATTACK_POWER"                  , 0xD5 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RANGED_ATTACK_POWER_MODS"             , 0xD6 , 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER"       , 0xD7 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MINRANGEDDAMAGE"                      , 0xD8 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXRANGEDDAMAGE"                      , 0xD9 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER_COST_MODIFIER"                  , 0xDA , 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_POWER_COST_MULTIPLIER"                , 0xE1 , 7  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_MAXHEALTHMODIFIER"                    , 0xE8 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE + UF_FLAG_OWNER_ONLY },
    { TYPEMASK_UNIT         , "UNIT_FIELD_PADDING"                              , 0xE9 , 1  , UF_TYPE_INT      , UF_FLAG_NONE },
    { TYPEMASK_UNIT         , "UNIT_END"                                        , 0xEA , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum EPlayerFields
    { TYPEMASK_PLAYER       , "PLAYER_DUEL_ARBITER"                             , 0xEA , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_FLAGS"                                    , 0xEC , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_GUILDID"                                  , 0xED , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_GUILDRANK"                                , 0xEE , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_BYTES"                                    , 0xEF , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_BYTES_2"                                  , 0xF0 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_BYTES_3"                                  , 0xF1 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_DUEL_TEAM"                                , 0xF2 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_GUILD_TIMESTAMP"                          , 0xF3 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_1_1"                            , 0xF4 , 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_1_2"                            , 0xF5 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_1_3"                            , 0xF6 , 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_1_4"                            , 0xF7 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_2_1"                            , 0xF8 , 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_2_2"                            , 0xF9 , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_2_3"                            , 0xFA , 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_2_4"                            , 0xFB , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_3_1"                            , 0xFC , 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_3_2"                            , 0xFD , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_3_3"                            , 0xFE , 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_3_4"                            , 0xFF , 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_4_1"                            , 0x100, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_4_2"                            , 0x101, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_4_3"                            , 0x102, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_4_4"                            , 0x103, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_5_1"                            , 0x104, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_5_2"                            , 0x105, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_5_3"                            , 0x106, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_5_4"                            , 0x107, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_6_1"                            , 0x108, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_6_2"                            , 0x109, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_6_3"                            , 0x10A, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_6_4"                            , 0x10B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_7_1"                            , 0x10C, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_7_2"                            , 0x10D, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_7_3"                            , 0x10E, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_7_4"                            , 0x10F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_8_1"                            , 0x110, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_8_2"                            , 0x111, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_8_3"                            , 0x112, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_8_4"                            , 0x113, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_9_1"                            , 0x114, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_9_2"                            , 0x115, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_9_3"                            , 0x116, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_9_4"                            , 0x117, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_10_1"                           , 0x118, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_10_2"                           , 0x119, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_10_3"                           , 0x11A, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_10_4"                           , 0x11B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_11_1"                           , 0x11C, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_11_2"                           , 0x11D, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_11_3"                           , 0x11E, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_11_4"                           , 0x11F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_12_1"                           , 0x120, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_12_2"                           , 0x121, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_12_3"                           , 0x122, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_12_4"                           , 0x123, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_13_1"                           , 0x124, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_13_2"                           , 0x125, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_13_3"                           , 0x126, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_13_4"                           , 0x127, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_14_1"                           , 0x128, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_14_2"                           , 0x129, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_14_3"                           , 0x12A, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_14_4"                           , 0x12B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_15_1"                           , 0x12C, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_15_2"                           , 0x12D, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_15_3"                           , 0x12E, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_15_4"                           , 0x12F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_16_1"                           , 0x130, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_16_2"                           , 0x131, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_16_3"                           , 0x132, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_16_4"                           , 0x133, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_17_1"                           , 0x134, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_17_2"                           , 0x135, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_17_3"                           , 0x136, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_17_4"                           , 0x137, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_18_1"                           , 0x138, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_18_2"                           , 0x139, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_18_3"                           , 0x13A, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_18_4"                           , 0x13B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_19_1"                           , 0x13C, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_19_2"                           , 0x13D, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_19_3"                           , 0x13E, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_19_4"                           , 0x13F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_20_1"                           , 0x140, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_20_2"                           , 0x141, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_20_3"                           , 0x142, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_20_4"                           , 0x143, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_21_1"                           , 0x144, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_21_2"                           , 0x145, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_21_3"                           , 0x146, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_21_4"                           , 0x147, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_22_1"                           , 0x148, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_22_2"                           , 0x149, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_22_3"                           , 0x14A, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_22_4"                           , 0x14B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_23_1"                           , 0x14C, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_23_2"                           , 0x14D, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_23_3"                           , 0x14E, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_23_4"                           , 0x14F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_24_1"                           , 0x150, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_24_2"                           , 0x151, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_24_3"                           , 0x152, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_24_4"                           , 0x153, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_25_1"                           , 0x154, 1  , UF_TYPE_INT      , UF_FLAG_GROUP_ONLY },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_25_2"                           , 0x155, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_25_3"                           , 0x156, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_QUEST_LOG_25_4"                           , 0x157, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_1_CREATOR"                   , 0x158, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_1_0"                         , 0x15A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_1_PROPERTIES"                , 0x166, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_1_PAD"                       , 0x167, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_2_CREATOR"                   , 0x168, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_2_0"                         , 0x16A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_2_PROPERTIES"                , 0x176, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_2_PAD"                       , 0x177, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_3_CREATOR"                   , 0x178, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_3_0"                         , 0x17A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_3_PROPERTIES"                , 0x186, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_3_PAD"                       , 0x187, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_4_CREATOR"                   , 0x188, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_4_0"                         , 0x18A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_4_PROPERTIES"                , 0x196, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_4_PAD"                       , 0x197, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_5_CREATOR"                   , 0x198, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_5_0"                         , 0x19A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_5_PROPERTIES"                , 0x1A6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_5_PAD"                       , 0x1A7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_6_CREATOR"                   , 0x1A8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_6_0"                         , 0x1AA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_6_PROPERTIES"                , 0x1B6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_6_PAD"                       , 0x1B7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_7_CREATOR"                   , 0x1B8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_7_0"                         , 0x1BA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_7_PROPERTIES"                , 0x1C6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_7_PAD"                       , 0x1C7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_8_CREATOR"                   , 0x1C8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_8_0"                         , 0x1CA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_8_PROPERTIES"                , 0x1D6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_8_PAD"                       , 0x1D7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_9_CREATOR"                   , 0x1D8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_9_0"                         , 0x1DA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_9_PROPERTIES"                , 0x1E6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_9_PAD"                       , 0x1E7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_10_CREATOR"                  , 0x1E8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_10_0"                        , 0x1EA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_10_PROPERTIES"               , 0x1F6, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_10_PAD"                      , 0x1F7, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_11_CREATOR"                  , 0x1F8, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_11_0"                        , 0x1FA, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_11_PROPERTIES"               , 0x206, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_11_PAD"                      , 0x207, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_12_CREATOR"                  , 0x208, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_12_0"                        , 0x20A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_12_PROPERTIES"               , 0x216, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_12_PAD"                      , 0x217, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_13_CREATOR"                  , 0x218, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_13_0"                        , 0x21A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_13_PROPERTIES"               , 0x226, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_13_PAD"                      , 0x227, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_14_CREATOR"                  , 0x228, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_14_0"                        , 0x22A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_14_PROPERTIES"               , 0x236, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_14_PAD"                      , 0x237, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_15_CREATOR"                  , 0x238, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_15_0"                        , 0x23A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_15_PROPERTIES"               , 0x246, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_15_PAD"                      , 0x247, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_16_CREATOR"                  , 0x248, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_16_0"                        , 0x24A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_16_PROPERTIES"               , 0x256, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_16_PAD"                      , 0x257, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_17_CREATOR"                  , 0x258, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_17_0"                        , 0x25A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_17_PROPERTIES"               , 0x266, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_17_PAD"                      , 0x267, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_18_CREATOR"                  , 0x268, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_18_0"                        , 0x26A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_18_PROPERTIES"               , 0x276, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_18_PAD"                      , 0x277, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_19_CREATOR"                  , 0x278, 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_19_0"                        , 0x27A, 12 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_19_PROPERTIES"               , 0x286, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_VISIBLE_ITEM_19_PAD"                      , 0x287, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_CHOSEN_TITLE"                             , 0x288, 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_PAD_0"                              , 0x289, 1  , UF_TYPE_INT      , UF_FLAG_NONE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_INV_SLOT_HEAD"                      , 0x28A, 46 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_PACK_SLOT_1"                        , 0x2B8, 32 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BANK_SLOT_1"                        , 0x2D8, 56 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BANKBAG_SLOT_1"                     , 0x310, 14 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_VENDORBUYBACK_SLOT_1"               , 0x31E, 24 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_KEYRING_SLOT_1"                     , 0x336, 64 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_VANITYPET_SLOT_1"                   , 0x376, 36 , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FARSIGHT"                                 , 0x39A, 2  , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER__FIELD_KNOWN_TITLES"                      , 0x39C, 2  , UF_TYPE_GUID     , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_XP"                                       , 0x39E, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_NEXT_LEVEL_XP"                            , 0x39F, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_SKILL_INFO_1_1"                           , 0x3A0, 384, UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_CHARACTER_POINTS1"                        , 0x520, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_CHARACTER_POINTS2"                        , 0x521, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_TRACK_CREATURES"                          , 0x522, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_TRACK_RESOURCES"                          , 0x523, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_BLOCK_PERCENTAGE"                         , 0x524, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_DODGE_PERCENTAGE"                         , 0x525, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_PARRY_PERCENTAGE"                         , 0x526, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_EXPERTISE"                                , 0x527, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_OFFHAND_EXPERTISE"                        , 0x528, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_CRIT_PERCENTAGE"                          , 0x529, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_RANGED_CRIT_PERCENTAGE"                   , 0x52A, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_OFFHAND_CRIT_PERCENTAGE"                  , 0x52B, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_SPELL_CRIT_PERCENTAGE1"                   , 0x52C, 7  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_SHIELD_BLOCK"                             , 0x533, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_EXPLORED_ZONES_1"                         , 0x534, 128, UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_REST_STATE_EXPERIENCE"                    , 0x5B4, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_COINAGE"                            , 0x5B5, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_DAMAGE_DONE_POS"                , 0x5B6, 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_DAMAGE_DONE_NEG"                , 0x5BD, 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_DAMAGE_DONE_PCT"                , 0x5C4, 7  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_HEALING_DONE_POS"               , 0x5CB, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_TARGET_RESISTANCE"              , 0x5CC, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_TARGET_PHYSICAL_RESISTANCE"     , 0x5CD, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BYTES"                              , 0x5CE, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_AMMO_ID"                                  , 0x5CF, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_SELF_RES_SPELL"                           , 0x5D0, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_PVP_MEDALS"                         , 0x5D1, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BUYBACK_PRICE_1"                    , 0x5D2, 12 , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BUYBACK_TIMESTAMP_1"                , 0x5DE, 12 , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_KILLS"                              , 0x5EA, 1  , UF_TYPE_TWO_SHORT, UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_TODAY_CONTRIBUTION"                 , 0x5EB, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_YESTERDAY_CONTRIBUTION"             , 0x5EC, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_LIFETIME_HONORABLE_KILLS"           , 0x5ED, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_BYTES2"                             , 0x5EE, 1  , UF_TYPE_BYTES    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_WATCHED_FACTION_INDEX"              , 0x5EF, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_COMBAT_RATING_1"                    , 0x5F0, 24 , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_ARENA_TEAM_INFO_1_1"                , 0x608, 18 , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_HONOR_CURRENCY"                     , 0x61A, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_ARENA_CURRENCY"                     , 0x61B, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_MANA_REGEN"                     , 0x61C, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MOD_MANA_REGEN_INTERRUPT"           , 0x61D, 1  , UF_TYPE_FLOAT    , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_MAX_LEVEL"                          , 0x61E, 1  , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_FIELD_DAILY_QUESTS_1"                     , 0x61F, 25 , UF_TYPE_INT      , UF_FLAG_PRIVATE },
    { TYPEMASK_PLAYER       , "PLAYER_END"                                      , 0x638, 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum EGameObjectFields
    { TYPEMASK_GAMEOBJECT   , "OBJECT_FIELD_CREATED_BY"                         , 0x6  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_DISPLAYID"                            , 0x8  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_FLAGS"                                , 0x9  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_ROTATION"                             , 0xA  , 4  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_STATE"                                , 0xE  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_POS_X"                                , 0xF  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_POS_Y"                                , 0x10 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_POS_Z"                                , 0x11 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_FACING"                               , 0x12 , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_DYN_FLAGS"                            , 0x13 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_FACTION"                              , 0x14 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_TYPE_ID"                              , 0x15 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_LEVEL"                                , 0x16 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_ARTKIT"                               , 0x17 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_ANIMPROGRESS"                         , 0x18 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_PADDING"                              , 0x19 , 1  , UF_TYPE_INT      , UF_FLAG_NONE },
    { TYPEMASK_GAMEOBJECT   , "GAMEOBJECT_END"                                  , 0x1A , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum EDynamicObjectFields
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_CASTER"                            , 0x6  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_BYTES"                             , 0x8  , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_SPELLID"                           , 0x9  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_RADIUS"                            , 0xA  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_X"                             , 0xB  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_Y"                             , 0xC  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_POS_Z"                             , 0xD  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_FACING"                            , 0xE  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_CASTTIME"                          , 0xF  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_DYNAMICOBJECT, "DYNAMICOBJECT_END"                               , 0x10 , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
    // enum ECorpseFields
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_OWNER"                              , 0x6  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_PARTY"                              , 0x8  , 2  , UF_TYPE_GUID     , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_FACING"                             , 0xA  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_POS_X"                              , 0xB  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_POS_Y"                              , 0xC  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_POS_Z"                              , 0xD  , 1  , UF_TYPE_FLOAT    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_DISPLAY_ID"                         , 0xE  , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_ITEM"                               , 0xF  , 19 , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_BYTES_1"                            , 0x22 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_BYTES_2"                            , 0x23 , 1  , UF_TYPE_BYTES    , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_GUILD"                              , 0x24 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_FLAGS"                              , 0x25 , 1  , UF_TYPE_INT      , UF_FLAG_PUBLIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_DYNAMIC_FLAGS"                      , 0x26 , 1  , UF_TYPE_INT      , UF_FLAG_DYNAMIC },
    { TYPEMASK_CORPSE       , "CORPSE_FIELD_PAD"                                , 0x27 , 1  , UF_TYPE_INT      , UF_FLAG_NONE },
    { TYPEMASK_CORPSE       , "CORPSE_END"                                      , 0x28 , 0  , UF_TYPE_NONE     , UF_FLAG_NONE },
}};

template<std::size_t SIZE>
static std::array<uint16, SIZE> SetupUpdateFieldFlagsArray(uint8 objectTypeMask)
{
    std::array<uint16, SIZE> flagsArray;
    for (auto const& itr : g_updateFieldsData)
    {
        if ((itr.objectTypeMask & objectTypeMask) == 0)
            continue;

        for (uint16 i = itr.offset; i < itr.offset + itr.size; i++)
        {
            flagsArray.at(i) = itr.flags;
        }
    }
    return flagsArray;
}

static std::array<uint16, CONTAINER_END> const g_containerUpdateFieldFlags = SetupUpdateFieldFlagsArray<CONTAINER_END>(TYPEMASK_OBJECT | TYPEMASK_ITEM | TYPEMASK_CONTAINER);
static std::array<uint16, PLAYER_END> const g_playerUpdateFieldFlags = SetupUpdateFieldFlagsArray<PLAYER_END>(TYPEMASK_OBJECT | TYPEMASK_UNIT | TYPEMASK_PLAYER);
static std::array<uint16, GAMEOBJECT_END> const g_gameObjectUpdateFieldFlags = SetupUpdateFieldFlagsArray<GAMEOBJECT_END>(TYPEMASK_OBJECT | TYPEMASK_GAMEOBJECT);
static std::array<uint16, DYNAMICOBJECT_END> const g_dynamicObjectUpdateFieldFlags = SetupUpdateFieldFlagsArray<DYNAMICOBJECT_END>(TYPEMASK_OBJECT | TYPEMASK_DYNAMICOBJECT);
static std::array<uint16, CORPSE_END> const g_corpseUpdateFieldFlags = SetupUpdateFieldFlagsArray<CORPSE_END>(TYPEMASK_OBJECT | TYPEMASK_CORPSE);

uint16 const* UpdateFields::GetUpdateFieldFlagsArray(uint8 objectTypeId)
{
    switch (objectTypeId)
    {
        case TYPEID_ITEM:
        case TYPEID_CONTAINER:
        {
            return g_containerUpdateFieldFlags.data();
        }
        case TYPEID_UNIT:
        case TYPEID_PLAYER:
        {
            return g_playerUpdateFieldFlags.data();
        }
        case TYPEID_GAMEOBJECT:
        {
            return g_gameObjectUpdateFieldFlags.data();
        }
        case TYPEID_DYNAMICOBJECT:
        {
            return g_dynamicObjectUpdateFieldFlags.data();
        }
        case TYPEID_CORPSE:
        {
            return g_corpseUpdateFieldFlags.data();
        }
    }
    sLog.outError("Unhandled object type id (%hhu) in GetUpdateFieldFlagsArray!", objectTypeId);
    return 0;
}

UpdateFieldData const* UpdateFields::GetUpdateFieldDataByName(char const* name)
{
    for (const auto& itr : g_updateFieldsData)
    {
        if (strcmp(itr.name, name) == 0)
            return &itr;
    }
    return nullptr;
}

UpdateFieldData const* UpdateFields::GetUpdateFieldDataByTypeMaskAndOffset(uint8 objectTypeMask, uint16 offset)
{
    for (auto const& itr : g_updateFieldsData)
    {
        if ((itr.objectTypeMask & objectTypeMask) == 0)
            continue;

        if (offset == itr.offset || (offset > itr.offset && offset < (itr.offset + itr.size)))
            return &itr;
    }
    return nullptr;
}

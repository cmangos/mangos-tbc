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

#ifndef MANGOS_SPELLEFFECTDEFINES_H
#define MANGOS_SPELLEFFECTDEFINES_H

#include "Spells/SpellTargetDefines.h"

enum SpellEffects
{
    SPELL_EFFECT_NONE                      = 0,
    SPELL_EFFECT_INSTAKILL                 = 1,
    SPELL_EFFECT_SCHOOL_DAMAGE             = 2,
    SPELL_EFFECT_DUMMY                     = 3,
    SPELL_EFFECT_PORTAL_TELEPORT           = 4,
    SPELL_EFFECT_TELEPORT_UNITS            = 5,
    SPELL_EFFECT_APPLY_AURA                = 6,
    SPELL_EFFECT_ENVIRONMENTAL_DAMAGE      = 7,
    SPELL_EFFECT_POWER_DRAIN               = 8,
    SPELL_EFFECT_HEALTH_LEECH              = 9,
    SPELL_EFFECT_HEAL                      = 10,
    SPELL_EFFECT_BIND                      = 11,
    SPELL_EFFECT_PORTAL                    = 12,
    SPELL_EFFECT_RITUAL_BASE               = 13,
    SPELL_EFFECT_RITUAL_SPECIALIZE         = 14,
    SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL    = 15,
    SPELL_EFFECT_QUEST_COMPLETE            = 16,
    SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL    = 17,
    SPELL_EFFECT_RESURRECT                 = 18,
    SPELL_EFFECT_ADD_EXTRA_ATTACKS         = 19,
    SPELL_EFFECT_DODGE                     = 20,
    SPELL_EFFECT_EVADE                     = 21,
    SPELL_EFFECT_PARRY                     = 22,
    SPELL_EFFECT_BLOCK                     = 23,
    SPELL_EFFECT_CREATE_ITEM               = 24,
    SPELL_EFFECT_WEAPON                    = 25,
    SPELL_EFFECT_DEFENSE                   = 26,
    SPELL_EFFECT_PERSISTENT_AREA_AURA      = 27,
    SPELL_EFFECT_SUMMON                    = 28,
    SPELL_EFFECT_LEAP                      = 29,
    SPELL_EFFECT_ENERGIZE                  = 30,
    SPELL_EFFECT_WEAPON_PERCENT_DAMAGE     = 31,
    SPELL_EFFECT_TRIGGER_MISSILE           = 32,
    SPELL_EFFECT_OPEN_LOCK                 = 33,
    SPELL_EFFECT_SUMMON_CHANGE_ITEM        = 34,
    SPELL_EFFECT_APPLY_AREA_AURA_PARTY     = 35,
    SPELL_EFFECT_LEARN_SPELL               = 36,
    SPELL_EFFECT_SPELL_DEFENSE             = 37,
    SPELL_EFFECT_DISPEL                    = 38,
    SPELL_EFFECT_LANGUAGE                  = 39,
    SPELL_EFFECT_DUAL_WIELD                = 40,
    SPELL_EFFECT_41                        = 41,            // old SPELL_EFFECT_SUMMON_WILD
    SPELL_EFFECT_42                        = 42,            // old SPELL_EFFECT_SUMMON_GUARDIAN
    SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER = 43,
    SPELL_EFFECT_SKILL_STEP                = 44,
    SPELL_EFFECT_ADD_HONOR                 = 45,
    SPELL_EFFECT_SPAWN                     = 46,
    SPELL_EFFECT_TRADE_SKILL               = 47,
    SPELL_EFFECT_STEALTH                   = 48,
    SPELL_EFFECT_DETECT                    = 49,
    SPELL_EFFECT_TRANS_DOOR                = 50,
    SPELL_EFFECT_FORCE_CRITICAL_HIT        = 51,
    SPELL_EFFECT_GUARANTEE_HIT             = 52,
    SPELL_EFFECT_ENCHANT_ITEM              = 53,
    SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY    = 54,
    SPELL_EFFECT_TAMECREATURE              = 55,
    SPELL_EFFECT_SUMMON_PET                = 56,
    SPELL_EFFECT_LEARN_PET_SPELL           = 57,
    SPELL_EFFECT_WEAPON_DAMAGE             = 58,
    SPELL_EFFECT_OPEN_LOCK_ITEM            = 59,
    SPELL_EFFECT_PROFICIENCY               = 60,
    SPELL_EFFECT_SEND_EVENT                = 61,
    SPELL_EFFECT_POWER_BURN                = 62,
    SPELL_EFFECT_THREAT                    = 63,
    SPELL_EFFECT_TRIGGER_SPELL             = 64,
    SPELL_EFFECT_HEALTH_FUNNEL             = 65,
    SPELL_EFFECT_POWER_FUNNEL              = 66,
    SPELL_EFFECT_HEAL_MAX_HEALTH           = 67,
    SPELL_EFFECT_INTERRUPT_CAST            = 68,
    SPELL_EFFECT_DISTRACT                  = 69,
    SPELL_EFFECT_PULL                      = 70,
    SPELL_EFFECT_PICKPOCKET                = 71,
    SPELL_EFFECT_ADD_FARSIGHT              = 72,
    SPELL_EFFECT_73                        = 73,            // old SPELL_EFFECT_SUMMON_POSSESSED
    SPELL_EFFECT_74                        = 74,            // old SPELL_EFFECT_SUMMON_TOTEM
    SPELL_EFFECT_HEAL_MECHANICAL           = 75,
    SPELL_EFFECT_SUMMON_OBJECT_WILD        = 76,
    SPELL_EFFECT_SCRIPT_EFFECT             = 77,
    SPELL_EFFECT_ATTACK                    = 78,
    SPELL_EFFECT_SANCTUARY                 = 79,
    SPELL_EFFECT_ADD_COMBO_POINTS          = 80,
    SPELL_EFFECT_CREATE_HOUSE              = 81,
    SPELL_EFFECT_BIND_SIGHT                = 82,
    SPELL_EFFECT_DUEL                      = 83,
    SPELL_EFFECT_STUCK                     = 84,
    SPELL_EFFECT_SUMMON_PLAYER             = 85,
    SPELL_EFFECT_ACTIVATE_OBJECT           = 86,
    SPELL_EFFECT_87                        = 87,            // old SPELL_EFFECT_SUMMON_TOTEM_SLOT1
    SPELL_EFFECT_88                        = 88,            // old SPELL_EFFECT_SUMMON_TOTEM_SLOT2
    SPELL_EFFECT_89                        = 89,            // old SPELL_EFFECT_SUMMON_TOTEM_SLOT3
    SPELL_EFFECT_90                        = 90,            // old SPELL_EFFECT_SUMMON_TOTEM_SLOT4
    SPELL_EFFECT_THREAT_ALL                = 91,
    SPELL_EFFECT_ENCHANT_HELD_ITEM         = 92,
    SPELL_EFFECT_93                        = 93,            // old SPELL_EFFECT_SUMMON_PHANTASM
    SPELL_EFFECT_SELF_RESURRECT            = 94,
    SPELL_EFFECT_SKINNING                  = 95,
    SPELL_EFFECT_CHARGE                    = 96,
    SPELL_EFFECT_97                        = 97,            // old SPELL_EFFECT_SUMMON_CRITTER
    SPELL_EFFECT_KNOCK_BACK                = 98,
    SPELL_EFFECT_DISENCHANT                = 99,
    SPELL_EFFECT_INEBRIATE                 = 100,
    SPELL_EFFECT_FEED_PET                  = 101,
    SPELL_EFFECT_DISMISS_PET               = 102,
    SPELL_EFFECT_REPUTATION                = 103,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT1       = 104,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT2       = 105,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT3       = 106,
    SPELL_EFFECT_SUMMON_OBJECT_SLOT4       = 107,
    SPELL_EFFECT_DISPEL_MECHANIC           = 108,
    SPELL_EFFECT_SUMMON_DEAD_PET           = 109,
    SPELL_EFFECT_DESTROY_ALL_TOTEMS        = 110,
    SPELL_EFFECT_DURABILITY_DAMAGE         = 111,
    SPELL_EFFECT_112                       = 112,           // old SPELL_EFFECT_SUMMON_DEMON
    SPELL_EFFECT_RESURRECT_NEW             = 113,
    SPELL_EFFECT_ATTACK_ME                 = 114,
    SPELL_EFFECT_DURABILITY_DAMAGE_PCT     = 115,
    SPELL_EFFECT_SKIN_PLAYER_CORPSE        = 116,
    SPELL_EFFECT_SPIRIT_HEAL               = 117,
    SPELL_EFFECT_SKILL                     = 118,
    SPELL_EFFECT_APPLY_AREA_AURA_PET       = 119,
    SPELL_EFFECT_TELEPORT_GRAVEYARD        = 120,
    SPELL_EFFECT_NORMALIZED_WEAPON_DMG     = 121,
    SPELL_EFFECT_122                       = 122,
    SPELL_EFFECT_SEND_TAXI                 = 123,
    SPELL_EFFECT_PULL_TOWARDS              = 124,
    SPELL_EFFECT_MODIFY_THREAT_PERCENT     = 125,
    SPELL_EFFECT_STEAL_BENEFICIAL_BUFF     = 126,
    SPELL_EFFECT_PROSPECTING               = 127,
    SPELL_EFFECT_APPLY_AREA_AURA_FRIEND    = 128,
    SPELL_EFFECT_APPLY_AREA_AURA_ENEMY     = 129,
    SPELL_EFFECT_REDIRECT_THREAT           = 130,
    SPELL_EFFECT_PLAY_SOUND                = 131,
    SPELL_EFFECT_PLAY_MUSIC                = 132,
    SPELL_EFFECT_UNLEARN_SPECIALIZATION    = 133,
    SPELL_EFFECT_KILL_CREDIT_GROUP         = 134,
    SPELL_EFFECT_CALL_PET                  = 135,
    SPELL_EFFECT_HEAL_PCT                  = 136,
    SPELL_EFFECT_ENERGIZE_PCT              = 137,
    SPELL_EFFECT_LEAP_BACK                 = 138,
    SPELL_EFFECT_CLEAR_QUEST               = 139,
    SPELL_EFFECT_FORCE_CAST                = 140,
    SPELL_EFFECT_FORCE_CAST_WITH_VALUE     = 141,
    SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE  = 142,
    SPELL_EFFECT_APPLY_AREA_AURA_OWNER     = 143,
    SPELL_EFFECT_KNOCKBACK_FROM_POSITION   = 144,
    SPELL_EFFECT_PULL_TOWARDS_DEST         = 145,
    SPELL_EFFECT_146                       = 146,
    SPELL_EFFECT_QUEST_FAIL                = 147,
    SPELL_EFFECT_148                       = 148,
    SPELL_EFFECT_CHARGE_DEST               = 149,
    SPELL_EFFECT_150                       = 150,
    SPELL_EFFECT_TRIGGER_SPELL_2           = 151,
    SPELL_EFFECT_SUMMON_RAF_FRIEND         = 152, // TODO: Implement
    SPELL_EFFECT_CREATE_PET                = 153, // TODO: Implement
    MAX_SPELL_EFFECTS                      = 154
};

struct SpellEffectInfo
{
    char const* name;
    SpellTargetImplicitType requiredTarget;                 // Needs to correspond to what handler can handle
    SpellTarget defaultTarget;                              // [TARGET_NONE,TARGET_NONE] case
};

extern SpellEffectInfo SpellEffectInfoTable[MAX_SPELL_EFFECTS];

#endif
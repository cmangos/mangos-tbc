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

#ifndef __SPELL_DEFINES_H
#define __SPELL_DEFINES_H

#include "Common.h"

// ***********************************
// Spell Attributes definitions
// ***********************************

enum SpellAttributes
{
    SPELL_ATTR_PROC_FAILURE_BURNS_CHARGE       = 0x00000001,// 0
    SPELL_ATTR_USES_RANGED_SLOT                = 0x00000002,// 1 All ranged abilites have this flag
    SPELL_ATTR_ON_NEXT_SWING_NO_DAMAGE         = 0x00000004,// 2 on next swing
    SPELL_ATTR_DO_NOT_LOG_IMMUNE_MISSES        = 0x00000008,// 3 not set in 3.0.3
    SPELL_ATTR_IS_ABILITY                      = 0x00000010,// 4 Displays ability instead of spell clientside
    SPELL_ATTR_IS_TRADESKILL                   = 0x00000020,// 5 trade spells, will be added by client to a sublist of profession spell
    SPELL_ATTR_PASSIVE                         = 0x00000040,// 6 Passive spell
    SPELL_ATTR_DO_NOT_DISPLAY                  = 0x00000080,// 7 Hidden in Spellbook, Aura Icon, Combat Log
    SPELL_ATTR_DO_NOT_LOG                      = 0x00000100,// 8
    SPELL_ATTR_HELD_ITEM_ONLY                  = 0x00000200,// 9 Client automatically selects item from mainhand slot as a cast target
    SPELL_ATTR_ON_NEXT_SWING                   = 0x00000400,// 10 on next swing 2
    SPELL_ATTR_WEARER_CASTS_PROC_TRIGGER       = 0x00000800,// 11
    SPELL_ATTR_DAYTIME_ONLY                    = 0x00001000,// 12 only useable at daytime, not set in 2.4.2
    SPELL_ATTR_NIGHT_ONLY                      = 0x00002000,// 13 only useable at night, not set in 2.4.2
    SPELL_ATTR_ONLY_INDOORS                    = 0x00004000,// 14 only useable indoors, not set in 2.4.2
    SPELL_ATTR_ONLY_OUTDOORS                   = 0x00008000,// 15 Only useable outdoors.
    SPELL_ATTR_NOT_SHAPESHIFT                  = 0x00010000,// 16 Not while shapeshifted
    SPELL_ATTR_ONLY_STEALTHED                  = 0x00020000,// 17 Must be in stealth
    SPELL_ATTR_DO_NOT_SHEATH                   = 0x00040000,// 18 client won't hide unit weapons in sheath on cast/channel TODO: Implement
    SPELL_ATTR_SCALES_WITH_CREATURE_LEVEL      = 0x00080000,// 19 spelldamage depends on caster level
    SPELL_ATTR_CANCELS_AUTO_ATTACK_COMBAT      = 0x00100000,// 20 Stop attack after use this spell (and not begin attack if use)
    SPELL_ATTR_NO_ACTIVE_DEFENSE               = 0x00200000,// 21 Cannot be dodged/parried/blocked
    SPELL_ATTR_TRACK_TARGET_IN_CAST_PLAYER_ONLY= 0x00400000,// 22 SetTrackingTarget
    SPELL_ATTR_ALLOW_CAST_WHILE_DEAD           = 0x00800000,// 23 castable while dead
    SPELL_ATTR_ALLOW_WHILE_MOUNTED             = 0x01000000,// 24 castable while mounted
    SPELL_ATTR_COOLDOWN_ON_EVENT               = 0x02000000,// 25 Activate and start cooldown after aura fade or remove summoned creature or go
    SPELL_ATTR_AURA_IS_DEBUFF                  = 0x04000000,// 26
    SPELL_ATTR_ALLOW_WHILE_SITTING             = 0x08000000,// 27 castable while sitting
    SPELL_ATTR_NOT_IN_COMBAT_ONLY_PEACEFUL     = 0x10000000,// 28 Cannot be used in combat
    SPELL_ATTR_NO_IMMUNITIES                   = 0x20000000,// 29 unaffected by invulnerability
    SPELL_ATTR_HEARTBEAT_RESIST                = 0x40000000,// 30 Chance for spell effects to break early (heartbeat resist)
    SPELL_ATTR_NO_AURA_CANCEL                  = 0x80000000,// 31 positive aura can't be canceled
};

enum SpellAttributesEx
{
    SPELL_ATTR_EX_DISMISS_PET_FIRST            = 0x00000001,// 0
    SPELL_ATTR_EX_USE_ALL_MANA                 = 0x00000002,// 1
    SPELL_ATTR_EX_IS_CHANNELED                 = 0x00000004,// 2
    SPELL_ATTR_EX_NO_REDIRECTION               = 0x00000008,// 3
    SPELL_ATTR_EX_NO_SKILL_INCREASE            = 0x00000010,// 4
    SPELL_ATTR_EX_ALLOW_WHILE_STEALTHED        = 0x00000020,// 5
    SPELL_ATTR_EX_IS_SELF_CHANNELED            = 0x00000040,// 6
    SPELL_ATTR_EX_NO_REFLECTION                = 0x00000080,// 7
    SPELL_ATTR_EX_ONLY_PEACEFUL_TARGETS        = 0x00000100,// 8 Target must not be in combat
    SPELL_ATTR_EX_INITIATES_COMBAT_ENABLES_AUTO_ATTACK = 0x00000200,// 9
    SPELL_ATTR_EX_NO_THREAT                    = 0x00000400,// 10
    SPELL_ATTR_EX_AURA_UNIQUE                  = 0x00000800,// 11
    SPELL_ATTR_EX_FAILURE_BREAKS_STEALTH       = 0x00001000,// 12
    SPELL_ATTR_EX_TOGGLE_FARSIGHT              = 0x00002000,// 13
    SPELL_ATTR_EX_TRACK_TARGET_IN_CHANNEL      = 0x00004000,// 14
    SPELL_ATTR_EX_IMMUNITY_PURGES_EFFECT       = 0x00008000,// 15 auras which give immunity also punch through and purge the given effect
    SPELL_ATTR_EX_IMMUNITY_TO_HOSTILE_AND_FRIENDLY_EFFECTS = 0x00010000,// 16 TODO: Investigate use
    SPELL_ATTR_EX_NO_AUTOCAST_AI               = 0x00020000,// 17
    SPELL_ATTR_EX_PREVENTS_ANIM                = 0x00040000,// 18
    SPELL_ATTR_EX_EXCLUDE_CASTER               = 0x00080000,// 19 spells with area effect or friendly targets that exclude the caster
    SPELL_ATTR_EX_FINISHING_MOVE_DAMAGE        = 0x00100000,// 20 Uses combo points
    SPELL_ATTR_EX_THREAT_ONLY_ON_MISS          = 0x00200000,// 21
    SPELL_ATTR_EX_FINISHING_MOVE_DURATION      = 0x00400000,// 22 Uses combo points
    SPELL_ATTR_EX_IGNORE_OWNERS_DEATH          = 0x00800000,// 23
    SPELL_ATTR_EX_SPECIAL_SKILLUP              = 0x01000000,// 24
    SPELL_ATTR_EX_AURA_STAYS_AFTER_COMBAT      = 0x02000000,// 25
    SPELL_ATTR_EX_REQUIRE_ALL_TARGETS          = 0x04000000,// 26
    SPELL_ATTR_EX_DISCOUNT_POWER_ON_MISS       = 0x08000000,// 27
    SPELL_ATTR_EX_NO_AURA_ICON                 = 0x10000000,// 28
    SPELL_ATTR_EX_NAME_IN_CHANNEL_BAR          = 0x20000000,// 29
    SPELL_ATTR_EX_COMBO_ON_BLOCK               = 0x40000000,// 30 NYI
    SPELL_ATTR_EX_CAST_WHEN_LEARNED            = 0x80000000,// 31
};

enum SpellAttributesEx2
{
    SPELL_ATTR_EX2_ALLOW_DEAD_TARGET           = 0x00000001,// 0 can target dead unit or corpse
    SPELL_ATTR_EX2_NO_SHAPESHIFT_UI            = 0x00000002,// 1 
    SPELL_ATTR_EX2_IGNORE_LINE_OF_SIGHT        = 0x00000004,// 2
    SPELL_ATTR_EX2_ALLOW_LOW_LEVEL_BUFF        = 0x00000008,// 3
    SPELL_ATTR_EX2_USE_SHAPESHIFT_BAR          = 0x00000010,// 4 client displays icon in stance bar when learned, even if not shapeshift
    SPELL_ATTR_EX2_AUTO_REPEAT                 = 0x00000020,// 5
    SPELL_ATTR_EX2_CANNOT_CAST_ON_TAPPED       = 0x00000040,// 6 only usable on tapped by yourself
    SPELL_ATTR_EX2_DO_NOT_REPORT_SPELL_FAILURE = 0x00000080,// 7
    SPELL_ATTR_EX2_INCLUDE_IN_ADVANCED_COMBAT_LOG = 0x00000100,// 8 not used anywhere - likely also had different meaning
    SPELL_ATTR_EX2_ALWAYS_CAST_AS_UNIT         = 0x00000200,// 9 no idea
    SPELL_ATTR_EX2_SPECIAL_TAMING_FLAG         = 0x00000400,// 10 no idea
    SPELL_ATTR_EX2_NO_TARGET_PER_SECOND_COSTS  = 0x00000800,// 11
    SPELL_ATTR_EX2_CHAIN_FROM_CASTER           = 0x00001000,// 12
    SPELL_ATTR_EX2_ENCHANT_OWN_ITEM_ONLY       = 0x00002000,// 13
    SPELL_ATTR_EX2_ALLOW_WHILE_INVISIBLE       = 0x00004000,// 14
    SPELL_ATTR_EX2_UNK15                       = 0x00008000,// 15
    SPELL_ATTR_EX2_NO_ACTIVE_PETS              = 0x00010000,// 16
    SPELL_ATTR_EX2_DO_NOT_RESET_COMBAT_TIMERS  = 0x00020000,// 17 suspend weapon timer instead of resetting it, (?Hunters Shot and Stings only have this flag?)
    SPELL_ATTR_EX2_REQ_DEAD_PET                = 0x00040000,// 18 unconfirmed
    SPELL_ATTR_EX2_ALLOW_WHILE_NOT_SHAPESHIFTED= 0x00080000,// 19
    SPELL_ATTR_EX2_INITIATE_COMBAT_POST_CAST   = 0x00100000,// 20 NYI
    SPELL_ATTR_EX2_FAIL_ON_ALL_TARGETS_IMMUNE  = 0x00200000,// 21
    SPELL_ATTR_EX2_NO_INITIAL_THREAT           = 0x00400000,// 22
    SPELL_ATTR_EX2_PROC_COOLDOWN_ON_FAILURE    = 0x00800000,// 23
    SPELL_ATTR_EX2_ITEM_CAST_WITH_OWNER_SKILL  = 0x01000000,// 24 NYI
    SPELL_ATTR_EX2_DONT_BLOCK_MANA_REGEN       = 0x02000000,// 25 maybe different meaning - doesnt hurt anything however
    SPELL_ATTR_EX2_NO_SCHOOL_IMMUNITIES        = 0x04000000,// 26
    SPELL_ATTR_EX2_IGNORE_WEAPONSKILL          = 0x08000000,// 27 NYI
    SPELL_ATTR_EX2_NOT_AN_ACTION               = 0x10000000,// 28
    SPELL_ATTR_EX2_CANT_CRIT                   = 0x20000000,// 29 Spell can't crit
    SPELL_ATTR_EX2_ACTIVE_THREAT               = 0x40000000,// 30 NYI - has some sort of active threat component like fire nova totem
    SPELL_ATTR_EX2_RETAIN_ITEM_CAST            = 0x80000000,// 31 Possibly could have stacking implications in aura triggered spells because item guid is retained
};

enum SpellAttributesEx3
{
    SPELL_ATTR_EX3_PVP_ENABLING                = 0x00000001,// 0 Spell landed counts as hostile action against enemy even if it doesn't trigger combat state, propagates PvP flags
    SPELL_ATTR_EX3_NO_PROC_EQUIP_REQUIREMENT   = 0x00000002,// 1
    SPELL_ATTR_EX3_NO_CASTING_BAR_TEXT         = 0x00000004,// 2
    SPELL_ATTR_EX3_COMPLETELY_BLOCKED          = 0x00000008,// 3
    SPELL_ATTR_EX3_NO_RES_TIMER                = 0x00000010,// 4
    SPELL_ATTR_EX3_NO_DURABILITY_LOSS          = 0x00000020,// 5
    SPELL_ATTR_EX3_NO_AVOIDANCE                = 0x00000040,// 6
    SPELL_ATTR_EX3_DOT_STACKING_RULE           = 0x00000080,// 7 create a separate (de)buff stack for each caster
    SPELL_ATTR_EX3_ONLY_ON_PLAYER              = 0x00000100,// 8 Can target only player
    SPELL_ATTR_EX3_NOT_A_PROC                  = 0x00000200,// 9 aura periodic trigger is not evaluated as triggered (official meaning of proc)
    SPELL_ATTR_EX3_REQUIRES_MAIN_HAND_WEAPON   = 0x00000400,// 10
    SPELL_ATTR_EX3_ONLY_BATTLEGROUNDS          = 0x00000800,// 11 Can casted only on battleground
    SPELL_ATTR_EX3_ONLY_ON_GHOSTS              = 0x00001000,// 12
    SPELL_ATTR_EX3_HIDE_CHANNEL_BAR            = 0x00002000,// 13
    SPELL_ATTR_EX3_HIDE_IN_RAID_FILTER         = 0x00004000,// 14 "Honorless Target" only these spells have this flag
    SPELL_ATTR_EX3_NORMAL_RANGED_ATTACK        = 0x00008000,// 15 Spells with this attribute are processed as ranged attacks in client
    SPELL_ATTR_EX3_SUPPRESS_CASTER_PROCS       = 0x00010000,// 16
    SPELL_ATTR_EX3_SUPPRESS_TARGET_PROCS       = 0x00020000,// 17
    SPELL_ATTR_EX3_ALWAYS_HIT                  = 0x00040000,// 18 Spell should always hit its target 
    SPELL_ATTR_EX3_INSTANT_TARGET_PROCS        = 0x00080000,// 19 Related to spell batching - not an issue for us
    SPELL_ATTR_EX3_ALLOW_AURA_WHILE_DEAD       = 0x00100000,// 20 Death persistent spells
    SPELL_ATTR_EX3_ONLY_PROC_OUTDOORS          = 0x00200000,// 21
    SPELL_ATTR_EX3_CASTING_CANCELS_AUTOREPEAT  = 0x00400000,// 22
    SPELL_ATTR_EX3_NO_DAMAGE_HISTORY           = 0x00800000,// 23
    SPELL_ATTR_EX3_REQUIRES_OFFHAND_WEAPON     = 0x01000000,// 24 Req offhand weapon
    SPELL_ATTR_EX3_TREAT_AS_PERIODIC           = 0x02000000,// 25 Treated as periodic spell
    SPELL_ATTR_EX3_CAN_PROC_FROM_PROCS         = 0x04000000,// 26 Auras with this attribute can proc off procced spells (periodic triggers etc)
    SPELL_ATTR_EX3_ONLY_PROC_ON_CASTER         = 0x08000000,// 27
    SPELL_ATTR_EX3_IGNORE_CASTER_AND_TARGET_RESTRICTIONS = 0x10000000,// 28
    SPELL_ATTR_EX3_IGNORE_CASTER_MODIFIERS     = 0x20000000,// 29 Resistances should still affect damage
    SPELL_ATTR_EX3_DO_NOT_DISPLAY_RANGE        = 0x40000000,// 30
    SPELL_ATTR_EX3_NOT_ON_AOE_IMMUNE           = 0x80000000,// 31
};

enum SpellAttributesEx4
{
    SPELL_ATTR_EX4_NO_CAST_LOG                 = 0x00000001,// 0
    SPELL_ATTR_EX4_CLASS_TRIGGER_ONLY_ON_TARGET= 0x00000002,// 1
    SPELL_ATTR_EX4_AURA_EXPIRES_OFFLINE        = 0x00000004,// 2
    SPELL_ATTR_EX4_NO_HELPFUL_THREAT           = 0x00000008,// 3
    SPELL_ATTR_EX4_NO_HARMFUL_THREAT           = 0x00000010,// 4
    SPELL_ATTR_EX4_ALLOW_CLIENT_TARGETING      = 0x00000020,// 5
    SPELL_ATTR_EX4_CANNOT_BE_STOLEN            = 0x00000040,// 6 although such auras might be dispellable, they cannot be stolen
    SPELL_ATTR_EX4_ALLOW_CAST_WHILE_CASTING    = 0x00000080,// 7 Can use this spell while another is channeled/cast/autocast
    SPELL_ATTR_EX4_IGNORE_DAMAGE_TAKEN_MODIFIERS = 0x00000100,// 8
    SPELL_ATTR_EX4_COMBAT_FEEDBACK_WHEN_USABLE = 0x00000200,// 9 initially disabled / trigger activate from event (Execute, Riposte, Deep Freeze end other)
    SPELL_ATTR_EX4_WEAPON_SPEED_COST_SCALING   = 0x00000400,// 10
    SPELL_ATTR_EX4_NO_PARTIAL_IMMUNITY         = 0x00000800,// 11 Curse of Tongues - 1.12.0
    SPELL_ATTR_EX4_AURA_IS_BUFF                = 0x00001000,// 12
    SPELL_ATTR_EX4_DO_NOT_LOG_CASTER           = 0x00002000,// 13
    SPELL_ATTR_EX4_REACTIVE_DAMAGE_PROC        = 0x00004000,// 14
    SPELL_ATTR_EX4_NOT_IN_SPELLBOOK            = 0x00008000,// 15
    SPELL_ATTR_EX4_NOT_IN_ARENA                = 0x00010000,// 16
    SPELL_ATTR_EX4_IGNORE_DEFAULT_ARENA_RESTRICTIONS = 0x00020000,// 17
    SPELL_ATTR_EX4_BOUNCY_CHAIN_MISSILES       = 0x00040000,// 18
    SPELL_ATTR_EX4_ALLOW_PROC_WHILE_SITTING    = 0x00080000,// 19
    SPELL_ATTR_EX4_AURA_NEVER_BOUNCES          = 0x00100000,// 20 do not give "more powerful spell" error message
    SPELL_ATTR_EX4_ALLOW_ENTERING_ARENA        = 0x00200000,// 21
    SPELL_ATTR_EX4_PROC_SUPPRESS_SWING_ANIM    = 0x00400000,// 22
    SPELL_ATTR_EX4_SUPPRESS_WEAPON_PROCS       = 0x00800000,// 23
    SPELL_ATTR_EX4_AUTO_RANGED_COMBAT          = 0x01000000,// 24
    SPELL_ATTR_EX4_OWNER_POWER_SCALING         = 0x02000000,// 25 pet scaling auras
    SPELL_ATTR_EX4_ONLY_FLYING_AREAS           = 0x04000000,// 26
    SPELL_ATTR_EX4_FORCE_DISPLAY_CASTBAR       = 0x08000000,// 27
    SPELL_ATTR_EX4_IGNORE_COMBAT_TIMER         = 0x10000000,// 28 NYI
    SPELL_ATTR_EX4_UNK29                       = 0x20000000,// 29 different - impact on dispel of effect 0 of something
    SPELL_ATTR_EX4_UNK30                       = 0x40000000,// 30 different - impact on dispel of effect 1 of something
    SPELL_ATTR_EX4_UNK31                       = 0x80000000,// 31 different - impact on dispel of effect 2 of something
};

enum SpellAttributesEx5
{
    SPELL_ATTR_EX5_ALLOW_ACTIONS_DURING_CHANNEL= 0x00000001,// 0 don't interrupt channeling spells when moving/melee attacking/casting
    SPELL_ATTR_EX5_NO_REAGENT_COST_WITH_AURA   = 0x00000002,// 1 not need reagents if UNIT_FLAG_PREPARATION
    SPELL_ATTR_EX5_REMOVE_ENTERING_ARENA       = 0x00000004,// 2 removed at enter arena (e.g. 31850 since 3.3.3)
    SPELL_ATTR_EX5_ALLOW_WHILE_STUNNED         = 0x00000008,// 3
    SPELL_ATTR_EX5_TRIGGERS_CHANNELING         = 0x00000010,// 4
    SPELL_ATTR_EX5_LIMIT_N                     = 0x00000020,// 5 Only N targets can be apply at a time - dont of spells that have N>1 in tbc/wotlk
    SPELL_ATTR_EX5_IGNORE_AREA_EFFECT_PVP_CHECK= 0x00000040,// 6
    SPELL_ATTR_EX5_NOT_ON_PLAYER               = 0x00000080,// 7
    SPELL_ATTR_EX5_NOT_ON_PLAYER_CONTROLLED_NPC= 0x00000100,// 8
    SPELL_ATTR_EX5_EXTRA_INITIAL_PERIOD        = 0x00000200,// 9 begin periodic tick at aura apply
    SPELL_ATTR_EX5_DO_NOT_DISPLAY_DURATION     = 0x00000400,// 10
    SPELL_ATTR_EX5_IMPLIED_TARGETING           = 0x00000800,// 11 targets target of current hostile target if current hostile target is not eligible
    SPELL_ATTR_EX5_MELEE_CHAIN_TARGETING       = 0x00001000,// 12 Cleave Generic chain damage front targets
    SPELL_ATTR_EX5_SPELL_HASTE_AFFECTS_PERIODIC= 0x00002000,// 13 haste affects duration
    SPELL_ATTR_EX5_NOT_AVAILABLE_WHILE_CHARMED = 0x00004000,// 14
    SPELL_ATTR_EX5_TREAT_AS_AREA_EFFECT        = 0x00008000,// 15
    SPELL_ATTR_EX5_AURA_AFFECTS_NOT_JUST_REQ_EQUIPPED_ITEM  = 0x00010000,// 16 (only affects protpally One-Handed Weapon Spec)
    SPELL_ATTR_EX5_ALLOW_WHILE_FLEEING         = 0x00020000,// 17
    SPELL_ATTR_EX5_ALLOW_WHILE_CONFUSED        = 0x00040000,// 18
    SPELL_ATTR_EX5_AI_DOESNT_FACE_TARGET       = 0x00080000,// 19
    SPELL_ATTR_EX5_DO_NOT_ATTEMPT_A_PET_RESUMMON_WHEN_DISMOUNTING = 0x00100000,// 20 NYI - I think we do it innately for festive auras already
    SPELL_ATTR_EX5_IGNORE_TARGET_REQUIREMENTS  = 0x00200000,// 21
    SPELL_ATTR_EX5_NOT_ON_TRIVIAL              = 0x00400000,// 22
    SPELL_ATTR_EX5_NO_PARTIAL_RESISTS          = 0x00800000,// 23
    SPELL_ATTR_EX5_IGNORE_CASTER_REQUIREMENTS  = 0x01000000,// 24
    SPELL_ATTR_EX5_ALWAYS_LINE_OF_SIGHT        = 0x02000000,// 25
    SPELL_ATTR_EX5_ALWAYS_AOE_LINE_OF_SIGHT    = 0x04000000,// 26
    SPELL_ATTR_EX5_NO_CASTER_AURA_ICON         = 0x08000000,// 27
    SPELL_ATTR_EX5_NO_TARGET_AURA_ICON         = 0x10000000,// 28
    SPELL_ATTR_EX5_AURA_UNIQUE_PER_CASTER      = 0x20000000,// 29
    SPELL_ATTR_EX5_ALWAYS_SHOW_GROUND_TEXTURE  = 0x40000000,// 30
    SPELL_ATTR_EX5_ADD_MELEE_HIT_RATING        = 0x80000000,// 31 Introduced in patch 2.3: Taunt, Growl, etc spells use ability miss calculation (see implementation for details)
};

enum SpellAttributesEx6
{
    SPELL_ATTR_EX6_NO_COOLDOWN_ON_TOOLTIP      = 0x00000001,// 0
    SPELL_ATTR_EX6_DO_NOT_RESET_COOLDOWN_IN_ARENA = 0x00000002, // 1 Unused in tbc
    SPELL_ATTR_EX6_NOT_AN_ATTACK               = 0x00000004,// 2 Likely has more meaning than just ignore caster auras
    SPELL_ATTR_EX6_CAN_ASSIST_IMMUNE_PC        = 0x00000008,// 3
    SPELL_ATTR_EX6_IGNORE_FOR_MOD_TIME_RATE    = 0x00000010,// 4 Unused in tbc
    SPELL_ATTR_EX6_DO_NOT_CONSUME_RESOURCES    = 0x00000020,// 5 Requires resources but doesnt consume them - ritual of summoning child spell consumes
    SPELL_ATTR_EX6_FLOATING_COMBAT_TEXT_ON_CAST= 0x00000040,// 6 Auras with this attribute trigger SPELL_CAST combat log event instead of SPELL_AURA_START (clientside attribute)
    SPELL_ATTR_EX6_AURA_IS_WEAPON_PROC         = 0x00000080,// 7
    SPELL_ATTR_EX6_DO_NOT_CHAIN_TO_CROWD_CONTROLLED_TARGETS = 0x00000100,// 8 ignores target with cc effects
    SPELL_ATTR_EX6_ALLOW_ON_CHARMED_TARGETS    = 0x00000200,// 9 Unused in tbc
    SPELL_ATTR_EX6_NO_AURA_LOG                 = 0x00000400,// 10 Seems different in wotlk
    SPELL_ATTR_EX6_NOT_IN_RAID_INSTANCES       = 0x00000800,// 11
    SPELL_ATTR_EX6_ALLOW_WHILE_RIDING_VEHICLE  = 0x00001000,// 12 Unused in tbc
    SPELL_ATTR_EX6_IGNORE_PHASE_SHIFT          = 0x00002000,// 13 Can target in different phase
    SPELL_ATTR_EX6_AI_PRIMARY_RANGED_ATTACK    = 0x00004000,// 14 NYI - Likely global flag alternative to flagging spells as main in creature spell list
    SPELL_ATTR_EX6_NO_PUSHBACK                 = 0x00008000,// 15 Unused in tbc
    SPELL_ATTR_EX6_NO_JUMP_PATHING             = 0x00010000,// 16 Unused in tbc
    SPELL_ATTR_EX6_ALLOW_EQUIP_WHILE_CASTING   = 0x00020000,// 17
};

enum SpellAttributesServerside
{
    SPELL_ATTR_SS_PREVENT_INVIS                = 0x00000001,
    SPELL_ATTR_SS_AOE_CAP                      = 0x00000002,
    SPELL_ATTR_SS_IGNORE_EVADE                 = 0x00000004,
    SPELL_ATTR_SS_FACING_BACK                  = 0x00000008,
};

enum SpellCastResult : uint32
{
    SPELL_FAILED_AFFECTING_COMBAT               = 0x00,
    SPELL_FAILED_ALREADY_AT_FULL_HEALTH         = 0x01,
    SPELL_FAILED_ALREADY_AT_FULL_MANA           = 0x02,
    SPELL_FAILED_ALREADY_AT_FULL_POWER          = 0x03,
    SPELL_FAILED_ALREADY_BEING_TAMED            = 0x04,
    SPELL_FAILED_ALREADY_HAVE_CHARM             = 0x05,
    SPELL_FAILED_ALREADY_HAVE_SUMMON            = 0x06,
    SPELL_FAILED_ALREADY_OPEN                   = 0x07,
    SPELL_FAILED_AURA_BOUNCED                   = 0x08,
    SPELL_FAILED_AUTOTRACK_INTERRUPTED          = 0x09,
    SPELL_FAILED_BAD_IMPLICIT_TARGETS           = 0x0A,
    SPELL_FAILED_BAD_TARGETS                    = 0x0B,
    SPELL_FAILED_CANT_BE_CHARMED                = 0x0C,
    SPELL_FAILED_CANT_BE_DISENCHANTED           = 0x0D,
    SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL     = 0x0E,
    SPELL_FAILED_CANT_BE_PROSPECTED             = 0x0F,
    SPELL_FAILED_CANT_CAST_ON_TAPPED            = 0x10,
    SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE      = 0x11,
    SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED      = 0x12,
    SPELL_FAILED_CANT_STEALTH                   = 0x13,
    SPELL_FAILED_CASTER_AURASTATE               = 0x14,
    SPELL_FAILED_CASTER_DEAD                    = 0x15,
    SPELL_FAILED_CHARMED                        = 0x16,
    SPELL_FAILED_CHEST_IN_USE                   = 0x17,
    SPELL_FAILED_CONFUSED                       = 0x18,
    SPELL_FAILED_DONT_REPORT                    = 0x19,
    SPELL_FAILED_EQUIPPED_ITEM                  = 0x1A,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS            = 0x1B,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND   = 0x1C,
    SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND    = 0x1D,
    SPELL_FAILED_ERROR                          = 0x1E,
    SPELL_FAILED_FIZZLE                         = 0x1F,
    SPELL_FAILED_FLEEING                        = 0x20,
    SPELL_FAILED_FOOD_LOWLEVEL                  = 0x21,
    SPELL_FAILED_HIGHLEVEL                      = 0x22,
    SPELL_FAILED_HUNGER_SATIATED                = 0x23,
    SPELL_FAILED_IMMUNE                         = 0x24,
    SPELL_FAILED_INTERRUPTED                    = 0x25,
    SPELL_FAILED_INTERRUPTED_COMBAT             = 0x26,
    SPELL_FAILED_ITEM_ALREADY_ENCHANTED         = 0x27,
    SPELL_FAILED_ITEM_GONE                      = 0x28,
    SPELL_FAILED_ITEM_NOT_FOUND                 = 0x29,
    SPELL_FAILED_ITEM_NOT_READY                 = 0x2A,
    SPELL_FAILED_LEVEL_REQUIREMENT              = 0x2B,
    SPELL_FAILED_LINE_OF_SIGHT                  = 0x2C,
    SPELL_FAILED_LOWLEVEL                       = 0x2D,
    SPELL_FAILED_LOW_CASTLEVEL                  = 0x2E,
    SPELL_FAILED_MAINHAND_EMPTY                 = 0x2F,
    SPELL_FAILED_MOVING                         = 0x30,
    SPELL_FAILED_NEED_AMMO                      = 0x31,
    SPELL_FAILED_NEED_AMMO_POUCH                = 0x32,
    SPELL_FAILED_NEED_EXOTIC_AMMO               = 0x33,
    SPELL_FAILED_NOPATH                         = 0x34,
    SPELL_FAILED_NOT_BEHIND                     = 0x35,
    SPELL_FAILED_NOT_FISHABLE                   = 0x36,
    SPELL_FAILED_NOT_FLYING                     = 0x37,
    SPELL_FAILED_NOT_HERE                       = 0x38,
    SPELL_FAILED_NOT_INFRONT                    = 0x39,
    SPELL_FAILED_NOT_IN_CONTROL                 = 0x3A,
    SPELL_FAILED_NOT_KNOWN                      = 0x3B,
    SPELL_FAILED_NOT_MOUNTED                    = 0x3C,
    SPELL_FAILED_NOT_ON_TAXI                    = 0x3D,
    SPELL_FAILED_NOT_ON_TRANSPORT               = 0x3E,
    SPELL_FAILED_NOT_READY                      = 0x3F,
    SPELL_FAILED_NOT_SHAPESHIFT                 = 0x40,
    SPELL_FAILED_NOT_STANDING                   = 0x41,
    SPELL_FAILED_NOT_TRADEABLE                  = 0x42,
    SPELL_FAILED_NOT_TRADING                    = 0x43,
    SPELL_FAILED_NOT_UNSHEATHED                 = 0x44,
    SPELL_FAILED_NOT_WHILE_GHOST                = 0x45,
    SPELL_FAILED_NO_AMMO                        = 0x46,
    SPELL_FAILED_NO_CHARGES_REMAIN              = 0x47,
    SPELL_FAILED_NO_CHAMPION                    = 0x48,
    SPELL_FAILED_NO_COMBO_POINTS                = 0x49,
    SPELL_FAILED_NO_DUELING                     = 0x4A,
    SPELL_FAILED_NO_ENDURANCE                   = 0x4B,
    SPELL_FAILED_NO_FISH                        = 0x4C,
    SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED    = 0x4D,
    SPELL_FAILED_NO_MOUNTS_ALLOWED              = 0x4E,
    SPELL_FAILED_NO_PET                         = 0x4F,
    SPELL_FAILED_NO_POWER                       = 0x50,
    SPELL_FAILED_NOTHING_TO_DISPEL              = 0x51,
    SPELL_FAILED_NOTHING_TO_STEAL               = 0x52,
    SPELL_FAILED_ONLY_ABOVEWATER                = 0x53,
    SPELL_FAILED_ONLY_DAYTIME                   = 0x54,
    SPELL_FAILED_ONLY_INDOORS                   = 0x55,
    SPELL_FAILED_ONLY_MOUNTED                   = 0x56,
    SPELL_FAILED_ONLY_NIGHTTIME                 = 0x57,
    SPELL_FAILED_ONLY_OUTDOORS                  = 0x58,
    SPELL_FAILED_ONLY_SHAPESHIFT                = 0x59,
    SPELL_FAILED_ONLY_STEALTHED                 = 0x5A,
    SPELL_FAILED_ONLY_UNDERWATER                = 0x5B,
    SPELL_FAILED_OUT_OF_RANGE                   = 0x5C,
    SPELL_FAILED_PACIFIED                       = 0x5D,
    SPELL_FAILED_POSSESSED                      = 0x5E,
    SPELL_FAILED_REAGENTS                       = 0x5F,
    SPELL_FAILED_REQUIRES_AREA                  = 0x60,
    SPELL_FAILED_REQUIRES_SPELL_FOCUS           = 0x61,
    SPELL_FAILED_ROOTED                         = 0x62,
    SPELL_FAILED_SILENCED                       = 0x63,
    SPELL_FAILED_SPELL_IN_PROGRESS              = 0x64,
    SPELL_FAILED_SPELL_LEARNED                  = 0x65,
    SPELL_FAILED_SPELL_UNAVAILABLE              = 0x66,
    SPELL_FAILED_STUNNED                        = 0x67,
    SPELL_FAILED_TARGETS_DEAD                   = 0x68,
    SPELL_FAILED_TARGET_AFFECTING_COMBAT        = 0x69,
    SPELL_FAILED_TARGET_AURASTATE               = 0x6A,
    SPELL_FAILED_TARGET_DUELING                 = 0x6B,
    SPELL_FAILED_TARGET_ENEMY                   = 0x6C,
    SPELL_FAILED_TARGET_ENRAGED                 = 0x6D,
    SPELL_FAILED_TARGET_FRIENDLY                = 0x6E,
    SPELL_FAILED_TARGET_IN_COMBAT               = 0x6F,
    SPELL_FAILED_TARGET_IS_PLAYER               = 0x70,
    SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED    = 0x71,
    SPELL_FAILED_TARGET_NOT_DEAD                = 0x72,
    SPELL_FAILED_TARGET_NOT_IN_PARTY            = 0x73,
    SPELL_FAILED_TARGET_NOT_LOOTED              = 0x74,
    SPELL_FAILED_TARGET_NOT_PLAYER              = 0x75,
    SPELL_FAILED_TARGET_NO_POCKETS              = 0x76,
    SPELL_FAILED_TARGET_NO_WEAPONS              = 0x77,
    SPELL_FAILED_TARGET_UNSKINNABLE             = 0x78,
    SPELL_FAILED_THIRST_SATIATED                = 0x79,
    SPELL_FAILED_TOO_CLOSE                      = 0x7A,
    SPELL_FAILED_TOO_MANY_OF_ITEM               = 0x7B,
    SPELL_FAILED_TOTEM_CATEGORY                 = 0x7C,
    SPELL_FAILED_TOTEMS                         = 0x7D,
    SPELL_FAILED_TRAINING_POINTS                = 0x7E,
    SPELL_FAILED_TRY_AGAIN                      = 0x7F,
    SPELL_FAILED_UNIT_NOT_BEHIND                = 0x80,
    SPELL_FAILED_UNIT_NOT_INFRONT               = 0x81,
    SPELL_FAILED_WRONG_PET_FOOD                 = 0x82,
    SPELL_FAILED_NOT_WHILE_FATIGUED             = 0x83,
    SPELL_FAILED_TARGET_NOT_IN_INSTANCE         = 0x84,
    SPELL_FAILED_NOT_WHILE_TRADING              = 0x85,
    SPELL_FAILED_TARGET_NOT_IN_RAID             = 0x86,
    SPELL_FAILED_DISENCHANT_WHILE_LOOTING       = 0x87, // TODO: add
    SPELL_FAILED_PROSPECT_WHILE_LOOTING         = 0x88, // TODO: add
    SPELL_FAILED_NEED_MORE_ITEMS                = 0x89,
    SPELL_FAILED_TARGET_FREEFORALL              = 0x8A,
    SPELL_FAILED_NO_EDIBLE_CORPSES              = 0x8B,
    SPELL_FAILED_ONLY_BATTLEGROUNDS             = 0x8C,
    SPELL_FAILED_TARGET_NOT_GHOST               = 0x8D,
    SPELL_FAILED_TOO_MANY_SKILLS                = 0x8E,
    SPELL_FAILED_TRANSFORM_UNUSABLE             = 0x8F,
    SPELL_FAILED_WRONG_WEATHER                  = 0x90,
    SPELL_FAILED_DAMAGE_IMMUNE                  = 0x91,
    SPELL_FAILED_PREVENTED_BY_MECHANIC          = 0x92,
    SPELL_FAILED_PLAY_TIME                      = 0x93,
    SPELL_FAILED_REPUTATION                     = 0x94,
    SPELL_FAILED_MIN_SKILL                      = 0x95,
    SPELL_FAILED_NOT_IN_ARENA                   = 0x96,
    SPELL_FAILED_NOT_ON_SHAPESHIFT              = 0x97,
    SPELL_FAILED_NOT_ON_STEALTHED               = 0x98,
    SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE           = 0x99,
    SPELL_FAILED_NOT_ON_MOUNTED                 = 0x9A,
    SPELL_FAILED_TOO_SHALLOW                    = 0x9B,
    SPELL_FAILED_TARGET_NOT_IN_SANCTUARY        = 0x9C,
    SPELL_FAILED_TARGET_IS_TRIVIAL              = 0x9D,
    SPELL_FAILED_BM_OR_INVISGOD                 = 0x9E,
    SPELL_FAILED_EXPERT_RIDING_REQUIREMENT      = 0x9F,
    SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT     = 0xA0,
    SPELL_FAILED_NOT_IDLE                       = 0xA1,
    SPELL_FAILED_NOT_INACTIVE                   = 0xA2,
    SPELL_FAILED_PARTIAL_PLAYTIME               = 0xA3,
    SPELL_FAILED_NO_PLAYTIME                    = 0xA4,
    SPELL_FAILED_NOT_IN_BATTLEGROUND            = 0xA5,
    SPELL_FAILED_ONLY_IN_ARENA                  = 0xA6,
    SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 0xA7,
    SPELL_FAILED_UNKNOWN                        = 0xA8,

    SPELL_FAILED_CLIENT_MAX                     = 0xA9,

    SPELL_RESULT_DONT_SEND_TO_CLIENT            = 0xFD,     // Always has to be first - TODO: is this still needed? not in public
    SPELL_FAILED_PVP_CHECK                      = 0xFD,     // custom value for serverside check
    SPELL_NOT_FOUND                             = 0xFE,
    SPELL_CAST_OK                               = 0xFF      // custom value, don't must be send to client
};

enum SpellInterruptFlags
{
    SPELL_INTERRUPT_FLAG_MOVEMENT           = 0x01,
    SPELL_INTERRUPT_FLAG_DAMAGE_PUSHBACK    = 0x02, // Player only
    SPELL_INTERRUPT_FLAG_STUN               = 0x04, // not implemented until more research - many creature spells miss it
    SPELL_INTERRUPT_FLAG_COMBAT             = 0x08,
    SPELL_INTERRUPT_FLAG_DAMAGE_CANCELS     = 0x10, // Player only
};

enum SpellAuraInterruptFlags // also used for ChannelInterruptFlags
{
    AURA_INTERRUPT_FLAG_HOSTILE_ACTION              = 0x00000001,   // 0    removed when getting hit by a negative spell
    AURA_INTERRUPT_FLAG_DAMAGE                      = 0x00000002,   // 1    removed by any damage
    AURA_INTERRUPT_FLAG_ACTION                      = 0x00000004,   // 2    removed by any cast
    AURA_INTERRUPT_FLAG_MOVING                      = 0x00000008,   // 3    removed by any movement
    AURA_INTERRUPT_FLAG_TURNING                     = 0x00000010,   // 4    removed by any turning
    AURA_INTERRUPT_FLAG_ANIM_CANCELS                = 0x00000020,   // 5    removed by anim
    AURA_INTERRUPT_FLAG_DISMOUNT                    = 0x00000040,   // 6    removed by unmounting
    AURA_INTERRUPT_FLAG_UNDERWATER_CANCELS          = 0x00000080,   // 7    removed by entering water
    AURA_INTERRUPT_FLAG_ABOVEWATER_CANCELS          = 0x00000100,   // 8    removed by leaving water
    AURA_INTERRUPT_FLAG_SHEATHING_CANCELS           = 0x00000200,   // 9    removed by unsheathing
    AURA_INTERRUPT_FLAG_INTERACTING                 = 0x00000400,   // 10   talk to npc / loot? action on creature
    AURA_INTERRUPT_FLAG_LOOTING                     = 0x00000800,   // 11   mine/use/open action on gameobject
    AURA_INTERRUPT_FLAG_ATTACKING                   = 0x00001000,   // 12   removed by attack
    AURA_INTERRUPT_FLAG_ITEM_USE                    = 0x00002000,   // 13
    AURA_INTERRUPT_FLAG_DAMAGE_CHANNEL_DURATION     = 0x00004000,   // 14
    AURA_INTERRUPT_FLAG_SHAPESHIFTING               = 0x00008000,   // 15
    AURA_INTERRUPT_FLAG_ACTION_LATE                 = 0x00010000,   // 16
    AURA_INTERRUPT_FLAG_MOUNTING                    = 0x00020000,   // 17   removed by mounting
    AURA_INTERRUPT_FLAG_STANDING_CANCELS            = 0x00040000,   // 18   removed by standing up (used by food and drink mostly and sleep/Fake Death like)
    AURA_INTERRUPT_FLAG_LEAVE_WORLD                 = 0x00080000,   // 19   leaving map/getting teleported
    AURA_INTERRUPT_FLAG_STEALTH_INVIS_CANCELS       = 0x00100000,   // 20
    AURA_INTERRUPT_FLAG_INVULNERABILITY_BUFF_CANCELS= 0x00200000,   // 21
    AURA_INTERRUPT_FLAG_ENTER_WORLD                 = 0x00400000,   // 22
    AURA_INTERRUPT_FLAG_PVP_ACTIVE_CANCELS          = 0x00800000,   // 23   removed by entering pvp combat
    AURA_INTERRUPT_FLAG_NON_PERIODIC_DAMAGE         = 0x01000000    // 24   removed by any direct damage
};

enum SpellFacingFlags
{
    SPELL_FACING_FLAG_INFRONT = 0x0001
};

enum SpellModOp
{
    SPELLMOD_DAMAGE                     = 0,
    SPELLMOD_DURATION                   = 1,
    SPELLMOD_THREAT                     = 2,
    SPELLMOD_EFFECT1                    = 3,
    SPELLMOD_CHARGES                    = 4,
    SPELLMOD_RANGE                      = 5,
    SPELLMOD_RADIUS                     = 6,
    SPELLMOD_CRITICAL_CHANCE            = 7,
    SPELLMOD_ALL_EFFECTS                = 8,
    SPELLMOD_NOT_LOSE_CASTING_TIME      = 9,
    SPELLMOD_CASTING_TIME               = 10,
    SPELLMOD_COOLDOWN                   = 11,
    SPELLMOD_EFFECT2                    = 12,
    SPELLMOD_UNK1                       = 13, // unused
    SPELLMOD_COST                       = 14,
    SPELLMOD_CRIT_DAMAGE_BONUS          = 15,
    SPELLMOD_RESIST_MISS_CHANCE         = 16,
    SPELLMOD_JUMP_TARGETS               = 17,
    SPELLMOD_CHANCE_OF_SUCCESS          = 18, // Only used with SPELL_AURA_ADD_FLAT_MODIFIER and affects proc spells
    SPELLMOD_ACTIVATION_TIME            = 19,
    SPELLMOD_EFFECT_PAST_FIRST          = 20,
    SPELLMOD_GLOBAL_COOLDOWN            = 21,
    SPELLMOD_DOT                        = 22,
    SPELLMOD_EFFECT3                    = 23,
    SPELLMOD_SPELL_BONUS_DAMAGE         = 24,
    SPELLMOD_UNK2                       = 25, // unused
    // SPELLMOD_FREQUENCY_OF_SUCCESS    = 26,                // not used in 2.4.3
    SPELLMOD_MULTIPLE_VALUE             = 27,
    SPELLMOD_RESIST_DISPEL_CHANCE       = 28,
    MAX_SPELLMOD                        = 32,
};

// Spell triggering settings for CastSpell that enable us to skip some checks so that we can investigate spell specific settings
enum TriggerCastFlags : uint32
{
    TRIGGERED_NONE                              = 0x00000000,   // Not Triggered
    TRIGGERED_OLD_TRIGGERED                     = 0x00000001,   // Legacy bool support TODO: Restrict usage as much as possible.
    TRIGGERED_IGNORE_HIT_CALCULATION            = 0x00000002,   // Will ignore calculating hit in SpellHitResult
    TRIGGERED_IGNORE_UNSELECTABLE_FLAG          = 0x00000004,   // Ignores UNIT_FLAG_UNINTERACTIBLE in CheckTarget
    TRIGGERED_INSTANT_CAST                      = 0x00000008,   // Will ignore any cast time set in spell entry
    TRIGGERED_AUTOREPEAT                        = 0x00000010,   // Will signal spell system that this is internal autorepeat call
    TRIGGERED_IGNORE_UNATTACKABLE_FLAG          = 0x00000020,   // Ignores UNIT_FLAG_NOT_ATTACKABLE in CheckTarget
    TRIGGERED_DO_NOT_PROC                       = 0x00000040,   // Spells from scripts should not proc - DBScripts for example
    TRIGGERED_PET_CAST                          = 0x00000080,   // Spell that should report error through pet opcode
    TRIGGERED_NORMAL_COMBAT_CAST                = 0x00000100,   // AI needs to be notified about change of target TODO: change into TRIGGERED_NONE
    TRIGGERED_IGNORE_GCD                        = 0x00000200,   // Ignores GCD - to be used in spell scripts
    TRIGGERED_IGNORE_COSTS                      = 0x00000400,   // Ignores spell costs
    TRIGGERED_IGNORE_COOLDOWNS                  = 0x00000800,   // Ignores cooldowns
    TRIGGERED_IGNORE_CURRENT_CASTED_SPELL       = 0x00001000,   // Ignores concurrent casts and is not set as currently executed
    TRIGGERED_HIDE_CAST_IN_COMBAT_LOG           = 0x00002000,   // Sends cast flag for ignoring combat log display - used for many procs - default behaviour for triggered by aura
    TRIGGERED_DO_NOT_RESET_LEASH                = 0x00004000,   // Does not reset leash on cast
    TRIGGERED_CHANNEL_ONLY                      = 0x00008000,   // Only starts channel and no effects - used for summoning portal GO anims
    TRIGGERED_IGNORE_CASTER_AURA_STATE          = 0x00010000,   // Ignores the Aurastate of the caster
    TRIGGERED_FORCE_COSTS                       = 0x00020000,   // Forces costs for triggered spells
    TRIGGERED_FULL_MASK                         = 0xFFFFFFFF
};

// high byte (3 from 0..3) of UNIT_FIELD_BYTES_2
enum ShapeshiftForm
{
    FORM_NONE               = 0x00,
    FORM_CAT                = 0x01,
    FORM_TREE               = 0x02,
    FORM_TRAVEL             = 0x03,
    FORM_AQUA               = 0x04,
    FORM_BEAR               = 0x05,
    FORM_AMBIENT            = 0x06,
    FORM_GHOUL              = 0x07,
    FORM_DIREBEAR           = 0x08,
    FORM_CREATUREBEAR       = 0x0E,
    FORM_CREATURECAT        = 0x0F,
    FORM_GHOSTWOLF          = 0x10,
    FORM_BATTLESTANCE       = 0x11,
    FORM_DEFENSIVESTANCE    = 0x12,
    FORM_BERSERKERSTANCE    = 0x13,
    FORM_TEST               = 0x14,
    FORM_ZOMBIE             = 0x15,
    FORM_FLIGHT_EPIC        = 0x1B,
    FORM_SHADOW             = 0x1C,
    FORM_FLIGHT             = 0x1D,
    FORM_STEALTH            = 0x1E,
    FORM_MOONKIN            = 0x1F,
    FORM_SPIRITOFREDEMPTION = 0x20
};

const char* GetSpellCastResultString(SpellCastResult result);

#endif

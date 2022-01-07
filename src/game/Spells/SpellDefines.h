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
    SPELL_ATTR_UNK0                            = 0x00000001,// 0
    SPELL_ATTR_RANGED                          = 0x00000002,// 1 All ranged abilites have this flag
    SPELL_ATTR_ON_NEXT_SWING_NO_DAMAGE         = 0x00000004,// 2 on next swing
    SPELL_ATTR_UNK3                            = 0x00000008,// 3 not set in 3.0.3
    SPELL_ATTR_ABILITY                         = 0x00000010,// 4 Displays ability instead of spell clientside
    SPELL_ATTR_TRADESPELL                      = 0x00000020,// 5 trade spells, will be added by client to a sublist of profession spell
    SPELL_ATTR_PASSIVE                         = 0x00000040,// 6 Passive spell
    SPELL_ATTR_DO_NOT_DISPLAY                  = 0x00000080,// 7 Hidden in Spellbook, Aura Icon, Combat Log
    SPELL_ATTR_HIDE_IN_COMBAT_LOG              = 0x00000100,// 8 Do Not Log - our name is better understandable
    SPELL_ATTR_TARGET_MAINHAND_ITEM            = 0x00000200,// 9 Client automatically selects item from mainhand slot as a cast target TODO: Implement
    SPELL_ATTR_ON_NEXT_SWING                   = 0x00000400,// 10 on next swing 2
    SPELL_ATTR_WEARER_CASTS_PROC_TRIGGER       = 0x00000800,// 11
    SPELL_ATTR_DAYTIME_ONLY                    = 0x00001000,// 12 only useable at daytime, not set in 2.4.2
    SPELL_ATTR_NIGHT_ONLY                      = 0x00002000,// 13 only useable at night, not set in 2.4.2
    SPELL_ATTR_INDOORS_ONLY                    = 0x00004000,// 14 only useable indoors, not set in 2.4.2
    SPELL_ATTR_OUTDOORS_ONLY                   = 0x00008000,// 15 Only useable outdoors.
    SPELL_ATTR_NOT_SHAPESHIFT                  = 0x00010000,// 16 Not while shapeshifted
    SPELL_ATTR_ONLY_STEALTHED                  = 0x00020000,// 17 Must be in stealth
    SPELL_ATTR_DONT_AFFECT_SHEATH_STATE        = 0x00040000,// 18 client won't hide unit weapons in sheath on cast/channel TODO: Implement
    SPELL_ATTR_LEVEL_DAMAGE_CALCULATION        = 0x00080000,// 19 spelldamage depends on caster level
    SPELL_ATTR_STOP_ATTACK_TARGET              = 0x00100000,// 20 Stop attack after use this spell (and not begin attack if use)
    SPELL_ATTR_IMPOSSIBLE_DODGE_PARRY_BLOCK    = 0x00200000,// 21 Cannot be dodged/parried/blocked
    SPELL_ATTR_SET_TRACKING_TARGET             = 0x00400000,// 22 SetTrackingTarget
    SPELL_ATTR_CASTABLE_WHILE_DEAD             = 0x00800000,// 23 castable while dead
    SPELL_ATTR_CASTABLE_WHILE_MOUNTED          = 0x01000000,// 24 castable while mounted
    SPELL_ATTR_DISABLED_WHILE_ACTIVE           = 0x02000000,// 25 Activate and start cooldown after aura fade or remove summoned creature or go
    SPELL_ATTR_AURA_IS_DEBUFF                  = 0x04000000,// 26
    SPELL_ATTR_CASTABLE_WHILE_SITTING          = 0x08000000,// 27 castable while sitting
    SPELL_ATTR_CANT_USED_IN_COMBAT             = 0x10000000,// 28 Cannot be used in combat
    SPELL_ATTR_NO_IMMUNITIES                   = 0x20000000,// 29 unaffected by invulnerability
    SPELL_ATTR_HEARTBEAT_RESIST_CHECK          = 0x40000000,// 30 Chance for spell effects to break early (heartbeat resist)
    SPELL_ATTR_CANT_CANCEL                     = 0x80000000,// 31 positive aura can't be canceled
};

enum SpellAttributesEx
{
    SPELL_ATTR_EX_DISMISS_PET                  = 0x00000001,// 0
    SPELL_ATTR_EX_DRAIN_ALL_POWER              = 0x00000002,// 1 use all power (Only paladin Lay of Hands and Bunyanize)
    SPELL_ATTR_EX_CHANNELED_1                  = 0x00000004,// 2 channeled 1
    SPELL_ATTR_EX_CANT_BE_REDIRECTED           = 0x00000008,// 3
    SPELL_ATTR_EX_UNK4                         = 0x00000010,// 4
    SPELL_ATTR_EX_NOT_BREAK_STEALTH            = 0x00000020,// 5 Not break stealth
    SPELL_ATTR_EX_CHANNELED_2                  = 0x00000040,// 6 channeled 2
    SPELL_ATTR_EX_CANT_BE_REFLECTED            = 0x00000080,// 7
    SPELL_ATTR_EX_NOT_IN_COMBAT_TARGET         = 0x00000100,// 8 Spell req target not to be in combat state
    SPELL_ATTR_EX_FACING_TARGET                = 0x00000200,// 9 TODO: CONFIRM!
    SPELL_ATTR_EX_NO_THREAT                    = 0x00000400,// 10 no generates threat on cast 100%
    SPELL_ATTR_EX_DONT_REFRESH_DURATION_ON_RECAST = 0x00000800,// 11 Aura will not refresh its duration when recast
    SPELL_ATTR_EX_FAILURE_BREAKS_STEALTH       = 0x00001000,// 12
    SPELL_ATTR_EX_TOGGLE_FARSIGHT              = 0x00002000,// 13
    SPELL_ATTR_EX_CHANNEL_TRACK_TARGET         = 0x00004000,// 14
    SPELL_ATTR_EX_DISPEL_AURAS_ON_IMMUNITY     = 0x00008000,// 15 remove auras on immunity
    SPELL_ATTR_EX_UNAFFECTED_BY_SCHOOL_IMMUNE  = 0x00010000,// 16 unaffected by school immunity
    SPELL_ATTR_EX_UNAUTOCASTABLE_BY_CHARMED    = 0x00020000,// 17 TODO: Investigate more Chero version: SPELL_ATTR_EX_PLAYER_CANT_CAST_CHARMED, likely related to MC
    SPELL_ATTR_EX_PREVENTS_ANIM                = 0x00040000,// 18
    SPELL_ATTR_EX_CANT_TARGET_SELF             = 0x00080000,// 19 spells with area effect or friendly targets that exclude the caster
    SPELL_ATTR_EX_REQ_TARGET_COMBO_POINTS      = 0x00100000,// 20 Req combo points on target
    SPELL_ATTR_EX_THREAT_ONLY_ON_MISS          = 0x00200000,// 21
    SPELL_ATTR_EX_REQ_COMBO_POINTS             = 0x00400000,// 22 Use combo points (in 4.x not required combo point target selected)
    SPELL_ATTR_EX_UNK23                        = 0x00800000,// 23
    SPELL_ATTR_EX_UNK24                        = 0x01000000,// 24 Req fishing pole?? SPELL_ATTR_EX_FISHING
    SPELL_ATTR_EX_UNK25                        = 0x02000000,// 25 not set in 2.4.2
    SPELL_ATTR_EX_REQUIRE_ALL_TARGETS          = 0x04000000,// 26
    SPELL_ATTR_EX_REFUND_POWER                 = 0x08000000,// 27 All these spells refund power on parry or deflect
    SPELL_ATTR_EX_DONT_DISPLAY_IN_AURA_BAR     = 0x10000000,// 28
    SPELL_ATTR_EX_CHANNEL_DISPLAY_SPELL_NAME   = 0x20000000,// 29
    SPELL_ATTR_EX_ENABLE_AT_DODGE              = 0x40000000,// 30 overpower
    SPELL_ATTR_EX_UNK31                        = 0x80000000,// 31
};

enum SpellAttributesEx2
{
    SPELL_ATTR_EX2_CAN_TARGET_DEAD             = 0x00000001,// 0 can target dead unit or corpse
    SPELL_ATTR_EX2_UNK1                        = 0x00000002,// 1 
    SPELL_ATTR_EX2_IGNORE_LOS                  = 0x00000004,// 2 do not need LOS (e.g. 18220 since 3.3.3)
    SPELL_ATTR_EX2_UNK3                        = 0x00000008,// 3 auto targeting? (e.g. fishing skill enhancement items since 3.3.3)
    SPELL_ATTR_EX2_DISPLAY_IN_STANCE_BAR       = 0x00000010,// 4 client displays icon in stance bar when learned, even if not shapeshift
    SPELL_ATTR_EX2_AUTOREPEAT_FLAG             = 0x00000020,// 5
    SPELL_ATTR_EX2_CANT_TARGET_TAPPED          = 0x00000040,// 6 only usable on tabbed by yourself
    SPELL_ATTR_EX2_UNK7                        = 0x00000080,// 7
    SPELL_ATTR_EX2_UNK8                        = 0x00000100,// 8 not set in 2.4.2
    SPELL_ATTR_EX2_UNK9                        = 0x00000200,// 9
    SPELL_ATTR_EX2_UNK10                       = 0x00000400,// 10 SPELL_ATTR_EX2_TAME_SPELLS
    SPELL_ATTR_EX2_HEALTH_FUNNEL               = 0x00000800,// 11
    SPELL_ATTR_EX2_UNK12                       = 0x00001000,// 12 SPELL_ATTR_EX2_CLASS_CLEAVE
    SPELL_ATTR_EX2_UNK13                       = 0x00002000,// 13 TODO: Implement from TC SPELL_ATTR_EX2_CASTABLE_ON_ITEMS
    SPELL_ATTR_EX2_UNK14                       = 0x00004000,// 14
    SPELL_ATTR_EX2_UNK15                       = 0x00008000,// 15 not set in 2.4.2
    SPELL_ATTR_EX2_TAME_BEAST                  = 0x00010000,// 16
    SPELL_ATTR_EX2_NOT_RESET_AUTO_ACTIONS      = 0x00020000,// 17 suspend weapon timer instead of resetting it, (?Hunters Shot and Stings only have this flag?)
    SPELL_ATTR_EX2_REQ_DEAD_PET                = 0x00040000,// 18 Only Revive pet - possible req dead pet
    SPELL_ATTR_EX2_NOT_NEED_SHAPESHIFT         = 0x00080000,// 19 does not necessary need shapeshift (pre-3.x not have passive spells with this attribute)
    SPELL_ATTR_EX2_FACING_TARGETS_BACK         = 0x00100000,// 20 TODO: CONFIRM!
    SPELL_ATTR_EX2_DAMAGE_REDUCED_SHIELD       = 0x00200000,// 21 for ice blocks, pala immunity buffs, priest absorb shields, but used also for other spells -> not sure!
    SPELL_ATTR_EX2_NO_INITIAL_THREAT           = 0x00400000,// 22
    SPELL_ATTR_EX2_IS_ARCANE_CONCENTRATION     = 0x00800000,// 23 Only mage Arcane Concentration have this flag
    SPELL_ATTR_EX2_UNK24                       = 0x01000000,// 24
    SPELL_ATTR_EX2_UNK25                       = 0x02000000,// 25
    SPELL_ATTR_EX2_UNAFFECTED_BY_AURA_SCHOOL_IMMUNE = 0x04000000,// 26
    SPELL_ATTR_EX2_UNK27                       = 0x08000000,// 27
    SPELL_ATTR_EX2_UNK28                       = 0x10000000,// 28 no breaks stealth if it fails??
    SPELL_ATTR_EX2_CANT_CRIT                   = 0x20000000,// 29 Spell can't crit
    SPELL_ATTR_EX2_TRIGGERED_CAN_TRIGGER_PROC  = 0x40000000,// 30 Chero hint: SPELL_ATTR_EX2_CAN_TRIGGER_VICTIM
    SPELL_ATTR_EX2_FOOD_BUFF                   = 0x80000000,// 31 Food or Drink Buff (like Well Fed)
};

enum SpellAttributesEx3
{
    SPELL_ATTR_EX3_OUT_OF_COMBAT_ATTACK        = 0x00000001,// 0 Spell landed counts as hostile action against enemy even if it doesn't trigger combat state, propagates PvP flags
    SPELL_ATTR_EX3_UNK1                        = 0x00000002,// 1
    SPELL_ATTR_EX3_UNK2                        = 0x00000004,// 2
    SPELL_ATTR_EX3_BLOCKABLE_SPELL             = 0x00000008,// 3 TODO: Investigate more
    SPELL_ATTR_EX3_IGNORE_RESURRECTION_TIMER   = 0x00000010,// 4 Druid Rebirth only this spell have this flag
    SPELL_ATTR_EX3_UNK5                        = 0x00000020,// 5
    SPELL_ATTR_EX3_UNK6                        = 0x00000040,// 6
    SPELL_ATTR_EX3_STACK_FOR_DIFF_CASTERS      = 0x00000080,// 7 create a separate (de)buff stack for each caster
    SPELL_ATTR_EX3_TARGET_ONLY_PLAYER          = 0x00000100,// 8 Can target only player
    SPELL_ATTR_EX3_TRIGGERED_CAN_TRIGGER_SPECIAL = 0x00000200,// 9 Can only proc auras
    SPELL_ATTR_EX3_MAIN_HAND                   = 0x00000400,// 10 Main hand weapon required
    SPELL_ATTR_EX3_BATTLEGROUND                = 0x00000800,// 11 Can casted only on battleground
    SPELL_ATTR_EX3_CAST_ON_DEAD                = 0x00001000,// 12 target is a dead player (not every spell has this flag)
    SPELL_ATTR_EX3_DONT_DISPLAY_CHANNEL_BAR    = 0x00002000,// 13
    SPELL_ATTR_EX3_IS_HONORLESS_TARGET         = 0x00004000,// 14 "Honorless Target" only this spells have this flag
    SPELL_ATTR_EX3_RANGED_ATTACK               = 0x00008000,// 15 Spells with this attribute are processed as ranged attacks in client
    SPELL_ATTR_EX3_SUPPRESS_CASTER_PROCS       = 0x00010000,// 16
    SPELL_ATTR_EX3_SUPPRESS_TARGET_PROCS       = 0x00020000,// 17
    SPELL_ATTR_EX3_ALWAYS_HIT                  = 0x00040000,// 18 Spell should always hit its target 
    SPELL_ATTR_EX3_UNK19                       = 0x00080000,// 19 TODO: Implement from TC
    SPELL_ATTR_EX3_DEATH_PERSISTENT            = 0x00100000,// 20 Death persistent spells
    SPELL_ATTR_EX3_UNK21                       = 0x00200000,// 21
    SPELL_ATTR_EX3_REQ_WAND                    = 0x00400000,// 22 Req wand
    SPELL_ATTR_EX3_UNK23                       = 0x00800000,// 23
    SPELL_ATTR_EX3_REQ_OFFHAND                 = 0x01000000,// 24 Req offhand weapon
    SPELL_ATTR_EX3_TREAT_AS_PERIODIC           = 0x02000000,// 25 Treated as periodic spell
    SPELL_ATTR_EX3_CAN_PROC_FROM_TRIGGERED     = 0x04000000,// 26 Auras with this attribute can proc off SPELL_ATTR_EX3_TRIGGERED_CAN_TRIGGER_SPECIAL
    SPELL_ATTR_EX3_UNK27                       = 0x08000000,// 27
    SPELL_ATTR_EX3_UNK28                       = 0x10000000,// 28 always cast ok ? (requires more research)
    SPELL_ATTR_EX3_IGNORE_CASTER_MODIFIERS     = 0x20000000,// 29 Resistances should still affect damage
    SPELL_ATTR_EX3_DONT_DISPLAY_RANGE          = 0x40000000,// 30
    SPELL_ATTR_EX3_UNK31                       = 0x80000000,// 31
};

enum SpellAttributesEx4
{
    SPELL_ATTR_EX4_IGNORE_RESISTANCES          = 0x00000001,// 0
    SPELL_ATTR_EX4_PROC_ONLY_ON_CASTER         = 0x00000002,// 1 Only proc on self-cast
    SPELL_ATTR_EX4_AURA_EXPIRES_OFFLINE        = 0x00000004,// 2
    SPELL_ATTR_EX4_UNK3                        = 0x00000008,// 3
    SPELL_ATTR_EX4_UNK4                        = 0x00000010,// 4 This will no longer cause guards to attack on use??
    SPELL_ATTR_EX4_UNK5                        = 0x00000020,// 5
    SPELL_ATTR_EX4_NOT_STEALABLE               = 0x00000040,// 6 although such auras might be dispellable, they cannot be stolen
    SPELL_ATTR_EX4_CAN_CAST_WHILE_CASTING      = 0x00000080,// 7 In theory, can use this spell while another is channeled/cast/autocast
    SPELL_ATTR_EX4_IGNORE_DAMAGE_TAKEN_MODIFIERS = 0x00000100,// 8
    SPELL_ATTR_EX4_TRIGGER_ACTIVATE            = 0x00000200,// 9 initially disabled / trigger activate from event (Execute, Riposte, Deep Freeze end other)
    SPELL_ATTR_EX4_SPELL_VS_EXTEND_COST        = 0x00000400,// 10 Rogue Shiv have this flag
    SPELL_ATTR_EX4_UNK11                       = 0x00000800,// 11
    SPELL_ATTR_EX4_UNK12                       = 0x00001000,// 12
    SPELL_ATTR_EX4_UNK13                       = 0x00002000,// 13
    SPELL_ATTR_EX4_DAMAGE_DOESNT_BREAK_AURAS   = 0x00004000,// 14
    SPELL_ATTR_EX4_UNK15                       = 0x00008000,// 15 Dont add to spellbook
    SPELL_ATTR_EX4_NOT_USABLE_IN_ARENA         = 0x00010000,// 16 not usable in arena
    SPELL_ATTR_EX4_USABLE_IN_ARENA             = 0x00020000,// 17 usable in arena
    SPELL_ATTR_EX4_UNK18                       = 0x00040000,// 18 TODO: Investigate from TC
    SPELL_ATTR_EX4_UNK19                       = 0x00080000,// 19
    SPELL_ATTR_EX4_NOT_CHECK_SELFCAST_POWER    = 0x00100000,// 20 do not give "more powerful spell" error message
    SPELL_ATTR_EX4_UNK21                       = 0x00200000,// 21
    SPELL_ATTR_EX4_UNK22                       = 0x00400000,// 22
    SPELL_ATTR_EX4_UNK23                       = 0x00800000,// 23
    SPELL_ATTR_EX4_AUTO_RANGED_COMBAT_SPELL    = 0x01000000,// 24
    SPELL_ATTR_EX4_IS_PET_SCALING              = 0x02000000,// 25 pet scaling auras
    SPELL_ATTR_EX4_CAST_ONLY_IN_OUTLAND        = 0x04000000,// 26 Can only be used in Outland.
    SPELL_ATTR_EX4_UNK27                       = 0x08000000,// 27 Always shown in combat log
    SPELL_ATTR_EX4_UNK28                       = 0x10000000,// 28
    SPELL_ATTR_EX4_UNK29                       = 0x20000000,// 29 Related to client check about dispel, CC seems to have them - dispel effect 0
    SPELL_ATTR_EX4_UNK30                       = 0x40000000,// 30 - dispel effect 1
    SPELL_ATTR_EX4_UNK31                       = 0x80000000,// 31 - dispel effect 2
};

enum SpellAttributesEx5
{
    SPELL_ATTR_EX5_CAN_CHANNEL_WHEN_MOVING     = 0x00000001,// 0 don't interrupt channeling spells when moving
    SPELL_ATTR_EX5_NO_REAGENT_WHILE_PREP       = 0x00000002,// 1 not need reagents if UNIT_FLAG_PREPARATION
    SPELL_ATTR_EX5_REMOVE_ON_ARENA_ENTER       = 0x00000004,// 2 removed at enter arena (e.g. 31850 since 3.3.3)
    SPELL_ATTR_EX5_USABLE_WHILE_STUNNED        = 0x00000008,// 3 usable while stunned
    SPELL_ATTR_EX5_UNK4                        = 0x00000010,// 4
    SPELL_ATTR_EX5_SINGLE_TARGET_SPELL         = 0x00000020,// 5 Only one target can be apply at a time
    SPELL_ATTR_EX5_UNK6                        = 0x00000040,// 6
    SPELL_ATTR_EX5_UNK7                        = 0x00000080,// 7
    SPELL_ATTR_EX5_UNK8                        = 0x00000100,// 8
    SPELL_ATTR_EX5_START_PERIODIC_AT_APPLY     = 0x00000200,// 9  begin periodic tick at aura apply
    SPELL_ATTR_EX5_HIDE_DURATION               = 0x00000400,// 10
    SPELL_ATTR_EX5_ALLOW_TARGET_OF_TARGET_AS_TARGET = 0x00000800,// 11
    SPELL_ATTR_EX5_CLEAVE_FRONT_TARGET         = 0x00001000,// 12 Cleave Generic chain damage front targets
    SPELL_ATTR_EX5_HASTE_AFFECT_DURATION       = 0x00002000,// 13 haste affects duration
    SPELL_ATTR_EX5_UNK14                       = 0x00004000,// 14
    SPELL_ATTR_EX5_UNK15                       = 0x00008000,// 15
    SPELL_ATTR_EX5_MOD_ALL_DAMAGE              = 0x00010000,// 16 (only affects protpally One-Handed Weapon Spec)
    SPELL_ATTR_EX5_USABLE_WHILE_FEARED         = 0x00020000,// 17 usable while feared
    SPELL_ATTR_EX5_USABLE_WHILE_CONFUSED       = 0x00040000,// 18 usable while confused
    SPELL_ATTR_EX5_AI_DOESNT_FACE_TARGET       = 0x00080000,// 19
    SPELL_ATTR_EX5_UNK20                       = 0x00100000,// 20
    SPELL_ATTR_EX5_UNK21                       = 0x00200000,// 21
    SPELL_ATTR_EX5_NOT_ON_TRIVIAL              = 0x00400000,// 22
    SPELL_ATTR_EX5_UNK23                       = 0x00800000,// 23
    SPELL_ATTR_EX5_UNK24                       = 0x01000000,// 24
    SPELL_ATTR_EX5_UNK25                       = 0x02000000,// 25
    SPELL_ATTR_EX5_UNK26                       = 0x04000000,// 26
    SPELL_ATTR_EX5_DONT_SHOW_AURA_IF_SELF_CAST = 0x08000000,// 27 Auras with this attribute are not visible on units that are the caster
    SPELL_ATTR_EX5_DONT_SHOW_AURA_IF_NOT_SELF_CAST = 0x10000000,// 28 Auras with this attribute are not visible on units that are not the caster
    SPELL_ATTR_EX5_UNK29                       = 0x20000000,// 29
    SPELL_ATTR_EX5_UNK30                       = 0x40000000,// 30
    SPELL_ATTR_EX5_USE_PHYSICAL_HIT_CHANCE     = 0x80000000,// 31 Introduced in patch 2.3: Taunt, Growl, etc spells use ability miss calculation (see implementation for details)
};

enum SpellAttributesEx6
{
    SPELL_ATTR_EX6_DONT_DISPLAY_COOLDOWN       = 0x00000001,// 0 Only Move spell have this flag
    SPELL_ATTR_EX6_ONLY_IN_ARENA               = 0x00000002,// 1 only usable in arena, not used in 3.2.0a and early
    SPELL_ATTR_EX6_IGNORE_CASTER_AURAS         = 0x00000004,// 2
    SPELL_ATTR_EX6_ASSIST_IGNORE_IMMUNE_FLAG   = 0x00000008,// 3
    SPELL_ATTR_EX6_UNK4                        = 0x00000010,// 4
    SPELL_ATTR_EX6_UNK5                        = 0x00000020,// 5
    SPELL_ATTR_EX6_USE_SPELL_CAST_EVENT        = 0x00000040,// 6 Auras with this attribute trigger SPELL_CAST combat log event instead of SPELL_AURA_START (clientside attribute)
    SPELL_ATTR_EX6_UNK7                        = 0x00000080,// 7
    SPELL_ATTR_EX6_IGNORE_CC_TARGETS           = 0x00000100,// 8 ignores target with cc effects
    SPELL_ATTR_EX6_UNK9                        = 0x00000200,// 9
    SPELL_ATTR_EX6_UNK10                       = 0x00000400,// 10 TODO: Investigate from TC
    SPELL_ATTR_EX6_NOT_IN_RAID_INSTANCE        = 0x00000800,// 11 not usable in raid instance
    SPELL_ATTR_EX6_UNK12                       = 0x00001000,// 12 for auras SPELL_AURA_TRACK_CREATURES, SPELL_AURA_TRACK_RESOURCES and SPELL_AURA_TRACK_STEALTHED select non-stacking tracking spells
    SPELL_ATTR_EX6_IGNORE_PHASE_SHIFT          = 0x00002000,// 13 Can target in different phase
    SPELL_ATTR_EX6_UNK14                       = 0x00004000,// 14
    SPELL_ATTR_EX6_UNK15                       = 0x00008000,// 15 not set in 3.0.3
    SPELL_ATTR_EX6_UNK16                       = 0x00010000,// 16
    SPELL_ATTR_EX6_UNK17                       = 0x00020000,// 17
    SPELL_ATTR_EX6_UNK18                       = 0x00040000,// 18
    SPELL_ATTR_EX6_UNK19                       = 0x00080000,// 19
    SPELL_ATTR_EX6_UNK20                       = 0x00100000,// 20
    SPELL_ATTR_EX6_UNK21                       = 0x00200000,// 21
    SPELL_ATTR_EX6_UNK22                       = 0x00400000,// 22
    SPELL_ATTR_EX6_UNK23                       = 0x00800000,// 23 not set in 3.0.3
    SPELL_ATTR_EX6_UNK24                       = 0x01000000,// 24 not set in 3.0.3
    SPELL_ATTR_EX6_UNK25                       = 0x02000000,// 25 not set in 3.0.3
    SPELL_ATTR_EX6_UNK26                       = 0x04000000,// 26 not set in 3.0.3
    SPELL_ATTR_EX6_UNK27                       = 0x08000000,// 27 not set in 3.0.3
    SPELL_ATTR_EX6_UNK28                       = 0x10000000,// 28 not set in 3.0.3
    SPELL_ATTR_EX6_NO_DMG_PERCENT_MODS         = 0x20000000,// 29 do not apply damage mods (usually in cases where it has already been applied)
    SPELL_ATTR_EX6_UNK30                       = 0x40000000,// 30 not set in 3.0.3
    SPELL_ATTR_EX6_UNK31                       = 0x80000000,// 31 not set in 3.0.3
};

enum SpellAttributesServerside
{
    SPELL_ATTR_SS_PREVENT_INVIS                = 0x00000001,
    SPELL_ATTR_SS_AOE_CAP                      = 0x00000002,
    SPELL_ATTR_SS_IGNORE_EVADE                 = 0x00000004,
};

enum SpellCastResult
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
    SPELL_FAILED_PROSPECT_NEED_MORE             = 0x89,
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
    TRIGGERED_IGNORE_UNSELECTABLE_FLAG          = 0x00000004,   // Ignores UNIT_FLAG_NOT_SELECTABLE in CheckTarget
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
    TRIGGERED_FULL_MASK                         = 0xFFFFFFFF
};

#endif

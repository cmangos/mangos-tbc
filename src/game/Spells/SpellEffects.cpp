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

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "WorldPacket.h"
#include "Server/Opcodes.h"
#include "Log.h"
#include "World/World.h"
#include "Globals/ObjectMgr.h"
#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "Entities/Player.h"
#include "Skills/SkillExtraItems.h"
#include "Entities/Unit.h"
#include "Spells/Spell.h"
#include "Entities/DynamicObject.h"
#include "Spells/SpellAuras.h"
#include "Entities/UpdateData.h"
#include "Globals/SharedDefines.h"
#include "Entities/Pet.h"
#include "Entities/GameObject.h"
#include "Entities/GossipDef.h"
#include "Entities/Creature.h"
#include "Entities/Totem.h"
#include "AI/BaseAI/CreatureAI.h"
#include "BattleGround/BattleGroundMgr.h"
#include "BattleGround/BattleGround.h"
#include "Tools/Language.h"
#include "Social/SocialMgr.h"
#include "Util.h"
#include "Entities/TemporarySpawn.h"
#include "DBScripts/ScriptMgr.h"
#include "Skills/SkillDiscovery.h"
#include "Tools/Formulas.h"
#include "Grids/GridNotifiers.h"
#include "Grids/GridNotifiersImpl.h"
#include "Grids/CellImpl.h"
#include "G3D/Vector3.h"
#include "Loot/LootMgr.h"
#include "Movement/MoveSpline.h"
#include "AI/ScriptDevAI/include/sc_grid_searchers.h"
#include "Maps/InstanceData.h"
#include "Entities/Transports.h"

pEffect SpellEffects[MAX_SPELL_EFFECTS] =
{
    &Spell::EffectNULL,                                     //  0
    &Spell::EffectInstaKill,                                //  1 SPELL_EFFECT_INSTAKILL
    &Spell::EffectSchoolDMG,                                //  2 SPELL_EFFECT_SCHOOL_DAMAGE
    &Spell::EffectDummy,                                    //  3 SPELL_EFFECT_DUMMY
    &Spell::EffectUnused,                                   //  4 SPELL_EFFECT_PORTAL_TELEPORT          unused from pre-1.2.1
    &Spell::EffectTeleportUnits,                            //  5 SPELL_EFFECT_TELEPORT_UNITS
    &Spell::EffectApplyAura,                                //  6 SPELL_EFFECT_APPLY_AURA
    &Spell::EffectEnvironmentalDMG,                         //  7 SPELL_EFFECT_ENVIRONMENTAL_DAMAGE
    &Spell::EffectPowerDrain,                               //  8 SPELL_EFFECT_POWER_DRAIN
    &Spell::EffectHealthLeech,                              //  9 SPELL_EFFECT_HEALTH_LEECH
    &Spell::EffectHeal,                                     // 10 SPELL_EFFECT_HEAL
    &Spell::EffectBind,                                     // 11 SPELL_EFFECT_BIND
    &Spell::EffectUnused,                                   // 12 SPELL_EFFECT_PORTAL                   unused from pre-1.2.1, exist 2 spell, but not exist any data about its real usage
    &Spell::EffectUnused,                                   // 13 SPELL_EFFECT_RITUAL_BASE              unused from pre-1.2.1
    &Spell::EffectUnused,                                   // 14 SPELL_EFFECT_RITUAL_SPECIALIZE        unused from pre-1.2.1
    &Spell::EffectUnused,                                   // 15 SPELL_EFFECT_RITUAL_ACTIVATE_PORTAL   unused from pre-1.2.1
    &Spell::EffectQuestComplete,                            // 16 SPELL_EFFECT_QUEST_COMPLETE
    &Spell::EffectWeaponDmg,                                // 17 SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL
    &Spell::EffectResurrect,                                // 18 SPELL_EFFECT_RESURRECT
    &Spell::EffectAddExtraAttacks,                          // 19 SPELL_EFFECT_ADD_EXTRA_ATTACKS
    &Spell::EffectEmpty,                                    // 20 SPELL_EFFECT_DODGE                    one spell: Dodge
    &Spell::EffectEmpty,                                    // 21 SPELL_EFFECT_EVADE                    one spell: Evade (DND)
    &Spell::EffectParry,                                    // 22 SPELL_EFFECT_PARRY
    &Spell::EffectBlock,                                    // 23 SPELL_EFFECT_BLOCK                    one spell: Block
    &Spell::EffectCreateItem,                               // 24 SPELL_EFFECT_CREATE_ITEM
    &Spell::EffectEmpty,                                    // 25 SPELL_EFFECT_WEAPON                   spell per weapon type, in ItemSubclassmask store mask that can be used for usability check at equip, but current way using skill also work.
    &Spell::EffectEmpty,                                    // 26 SPELL_EFFECT_DEFENSE                  one spell: Defense
    &Spell::EffectPersistentAA,                             // 27 SPELL_EFFECT_PERSISTENT_AREA_AURA
    &Spell::EffectSummonType,                               // 28 SPELL_EFFECT_SUMMON
    &Spell::EffectLeapForward,                              // 29 SPELL_EFFECT_LEAP
    &Spell::EffectEnergize,                                 // 30 SPELL_EFFECT_ENERGIZE
    &Spell::EffectWeaponDmg,                                // 31 SPELL_EFFECT_WEAPON_PERCENT_DAMAGE
    &Spell::EffectTriggerMissileSpell,                      // 32 SPELL_EFFECT_TRIGGER_MISSILE
    &Spell::EffectOpenLock,                                 // 33 SPELL_EFFECT_OPEN_LOCK
    &Spell::EffectSummonChangeItem,                         // 34 SPELL_EFFECT_SUMMON_CHANGE_ITEM
    &Spell::EffectApplyAreaAura,                            // 35 SPELL_EFFECT_APPLY_AREA_AURA_PARTY
    &Spell::EffectLearnSpell,                               // 36 SPELL_EFFECT_LEARN_SPELL
    &Spell::EffectEmpty,                                    // 37 SPELL_EFFECT_SPELL_DEFENSE            one spell: SPELLDEFENSE (DND)
    &Spell::EffectDispel,                                   // 38 SPELL_EFFECT_DISPEL
    &Spell::EffectEmpty,                                    // 39 SPELL_EFFECT_LANGUAGE                 misc store lang id
    &Spell::EffectDualWield,                                // 40 SPELL_EFFECT_DUAL_WIELD
    &Spell::EffectUnused,                                   // 41 SPELL_EFFECT_41 (old SPELL_EFFECT_SUMMON_WILD)
    &Spell::EffectUnused,                                   // 42 SPELL_EFFECT_42 (old SPELL_EFFECT_SUMMON_GUARDIAN)
    &Spell::EffectTeleUnitsFaceCaster,                      // 43 SPELL_EFFECT_TELEPORT_UNITS_FACE_CASTER
    &Spell::EffectLearnSkill,                               // 44 SPELL_EFFECT_SKILL_STEP
    &Spell::EffectAddHonor,                                 // 45 SPELL_EFFECT_ADD_HONOR                honor/pvp related
    &Spell::EffectSpawn,                                    // 46 SPELL_EFFECT_SPAWN                    spawn/login animation, expected by spawn unit cast, also base points store some dynflags
    &Spell::EffectTradeSkill,                               // 47 SPELL_EFFECT_TRADE_SKILL
    &Spell::EffectUnused,                                   // 48 SPELL_EFFECT_STEALTH                  one spell: Base Stealth
    &Spell::EffectUnused,                                   // 49 SPELL_EFFECT_DETECT                   one spell: Detect
    &Spell::EffectTransmitted,                              // 50 SPELL_EFFECT_TRANS_DOOR
    &Spell::EffectUnused,                                   // 51 SPELL_EFFECT_FORCE_CRITICAL_HIT       unused from pre-1.2.1
    &Spell::EffectUnused,                                   // 52 SPELL_EFFECT_GUARANTEE_HIT            unused from pre-1.2.1
    &Spell::EffectEnchantItemPerm,                          // 53 SPELL_EFFECT_ENCHANT_ITEM
    &Spell::EffectEnchantItemTmp,                           // 54 SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY
    &Spell::EffectTameCreature,                             // 55 SPELL_EFFECT_TAMECREATURE
    &Spell::EffectSummonPet,                                // 56 SPELL_EFFECT_SUMMON_PET
    &Spell::EffectLearnPetSpell,                            // 57 SPELL_EFFECT_LEARN_PET_SPELL
    &Spell::EffectWeaponDmg,                                // 58 SPELL_EFFECT_WEAPON_DAMAGE
    &Spell::EffectOpenLock,                                 // 59 SPELL_EFFECT_OPEN_LOCK_ITEM
    &Spell::EffectProficiency,                              // 60 SPELL_EFFECT_PROFICIENCY
    &Spell::EffectSendEvent,                                // 61 SPELL_EFFECT_SEND_EVENT
    &Spell::EffectPowerBurn,                                // 62 SPELL_EFFECT_POWER_BURN
    &Spell::EffectThreat,                                   // 63 SPELL_EFFECT_THREAT
    &Spell::EffectTriggerSpell,                             // 64 SPELL_EFFECT_TRIGGER_SPELL
    &Spell::EffectUnused,                                   // 65 SPELL_EFFECT_HEALTH_FUNNEL            unused
    &Spell::EffectUnused,                                   // 66 SPELL_EFFECT_POWER_FUNNEL             unused from pre-1.2.1
    &Spell::EffectHealMaxHealth,                            // 67 SPELL_EFFECT_HEAL_MAX_HEALTH
    &Spell::EffectInterruptCast,                            // 68 SPELL_EFFECT_INTERRUPT_CAST
    &Spell::EffectDistract,                                 // 69 SPELL_EFFECT_DISTRACT
    &Spell::EffectPull,                                     // 70 SPELL_EFFECT_PULL                     one spell: Distract Move
    &Spell::EffectPickPocket,                               // 71 SPELL_EFFECT_PICKPOCKET
    &Spell::EffectAddFarsight,                              // 72 SPELL_EFFECT_ADD_FARSIGHT
    &Spell::EffectUnused,                                   // 73 SPELL_EFFECT_73 (old SPELL_EFFECT_SUMMON_POSSESSED
    &Spell::EffectUnused,                                   // 74 SPELL_EFFECT_74 (old SPELL_EFFECT_SUMMON_TOTEM)
    &Spell::EffectHealMechanical,                           // 75 SPELL_EFFECT_HEAL_MECHANICAL          one spell: Mechanical Patch Kit
    &Spell::EffectSummonObjectWild,                         // 76 SPELL_EFFECT_SUMMON_OBJECT_WILD
    &Spell::EffectScriptEffect,                             // 77 SPELL_EFFECT_SCRIPT_EFFECT
    &Spell::EffectUnused,                                   // 78 SPELL_EFFECT_ATTACK
    &Spell::EffectSanctuary,                                // 79 SPELL_EFFECT_SANCTUARY
    &Spell::EffectAddComboPoints,                           // 80 SPELL_EFFECT_ADD_COMBO_POINTS
    &Spell::EffectUnused,                                   // 81 SPELL_EFFECT_CREATE_HOUSE             one spell: Create House (TEST)
    &Spell::EffectNULL,                                     // 82 SPELL_EFFECT_BIND_SIGHT
    &Spell::EffectDuel,                                     // 83 SPELL_EFFECT_DUEL
    &Spell::EffectStuck,                                    // 84 SPELL_EFFECT_STUCK
    &Spell::EffectSummonPlayer,                             // 85 SPELL_EFFECT_SUMMON_PLAYER
    &Spell::EffectActivateObject,                           // 86 SPELL_EFFECT_ACTIVATE_OBJECT
    &Spell::EffectUnused,                                   // 87 SPELL_EFFECT_87 (old SPELL_EFFECT_SUMMON_TOTEM_SLOT1)
    &Spell::EffectUnused,                                   // 88 SPELL_EFFECT_88 (old SPELL_EFFECT_SUMMON_TOTEM_SLOT2)
    &Spell::EffectUnused,                                   // 89 SPELL_EFFECT_89 (old SPELL_EFFECT_SUMMON_TOTEM_SLOT3)
    &Spell::EffectUnused,                                   // 90 SPELL_EFFECT_90 (old SPELL_EFFECT_SUMMON_TOTEM_SLOT4)
    &Spell::EffectUnused,                                   // 91 SPELL_EFFECT_THREAT_ALL               one spell: zzOLDBrainwash
    &Spell::EffectEnchantHeldItem,                          // 92 SPELL_EFFECT_ENCHANT_HELD_ITEM
    &Spell::EffectUnused,                                   // 93 SPELL_EFFECT_93 (old SPELL_EFFECT_SUMMON_PHANTASM)
    &Spell::EffectSelfResurrect,                            // 94 SPELL_EFFECT_SELF_RESURRECT
    &Spell::EffectSkinning,                                 // 95 SPELL_EFFECT_SKINNING
    &Spell::EffectCharge,                                   // 96 SPELL_EFFECT_CHARGE
    &Spell::EffectUnused,                                   // 97 SPELL_EFFECT_97 (old SPELL_EFFECT_SUMMON_CRITTER)
    &Spell::EffectKnockBack,                                // 98 SPELL_EFFECT_KNOCK_BACK
    &Spell::EffectDisEnchant,                               // 99 SPELL_EFFECT_DISENCHANT
    &Spell::EffectInebriate,                                //100 SPELL_EFFECT_INEBRIATE
    &Spell::EffectFeedPet,                                  //101 SPELL_EFFECT_FEED_PET
    &Spell::EffectDismissPet,                               //102 SPELL_EFFECT_DISMISS_PET
    &Spell::EffectReputation,                               //103 SPELL_EFFECT_REPUTATION
    &Spell::EffectSummonObject,                             //104 SPELL_EFFECT_SUMMON_OBJECT_SLOT1
    &Spell::EffectSummonObject,                             //105 SPELL_EFFECT_SUMMON_OBJECT_SLOT2
    &Spell::EffectSummonObject,                             //106 SPELL_EFFECT_SUMMON_OBJECT_SLOT3
    &Spell::EffectSummonObject,                             //107 SPELL_EFFECT_SUMMON_OBJECT_SLOT4
    &Spell::EffectDispelMechanic,                           //108 SPELL_EFFECT_DISPEL_MECHANIC
    &Spell::EffectSummonDeadPet,                            //109 SPELL_EFFECT_SUMMON_DEAD_PET
    &Spell::EffectDestroyAllTotems,                         //110 SPELL_EFFECT_DESTROY_ALL_TOTEMS
    &Spell::EffectDurabilityDamage,                         //111 SPELL_EFFECT_DURABILITY_DAMAGE
    &Spell::EffectUnused,                                   //112 SPELL_EFFECT_112 (old SPELL_EFFECT_SUMMON_DEMON)
    &Spell::EffectResurrect,                                //113 SPELL_EFFECT_RESURRECT_NEW
    &Spell::EffectTaunt,                                    //114 SPELL_EFFECT_ATTACK_ME
    &Spell::EffectDurabilityDamagePCT,                      //115 SPELL_EFFECT_DURABILITY_DAMAGE_PCT
    &Spell::EffectSkinPlayerCorpse,                         //116 SPELL_EFFECT_SKIN_PLAYER_CORPSE       one spell: Remove Insignia, bg usage, required special corpse flags...
    &Spell::EffectSpiritHeal,                               //117 SPELL_EFFECT_SPIRIT_HEAL              one spell: Spirit Heal
    &Spell::EffectSkill,                                    //118 SPELL_EFFECT_SKILL                    professions and more
    &Spell::EffectApplyAreaAura,                            //119 SPELL_EFFECT_APPLY_AREA_AURA_PET
    &Spell::EffectTeleportGraveyard,                        //120 SPELL_EFFECT_TELEPORT_GRAVEYARD       one spell: Graveyard Teleport Test
    &Spell::EffectWeaponDmg,                                //121 SPELL_EFFECT_NORMALIZED_WEAPON_DMG
    &Spell::EffectUnused,                                   //122 SPELL_EFFECT_122                      unused
    &Spell::EffectSendTaxi,                                 //123 SPELL_EFFECT_SEND_TAXI                taxi/flight related (misc value is taxi path id)
    &Spell::EffectPullTowards,                              //124 SPELL_EFFECT_PULL_TOWARDS
    &Spell::EffectModifyThreatPercent,                      //125 SPELL_EFFECT_MODIFY_THREAT_PERCENT
    &Spell::EffectStealBeneficialBuff,                      //126 SPELL_EFFECT_STEAL_BENEFICIAL_BUFF    spell steal effect?
    &Spell::EffectProspecting,                              //127 SPELL_EFFECT_PROSPECTING              Prospecting spell
    &Spell::EffectApplyAreaAura,                            //128 SPELL_EFFECT_APPLY_AREA_AURA_FRIEND
    &Spell::EffectApplyAreaAura,                            //129 SPELL_EFFECT_APPLY_AREA_AURA_ENEMY
    &Spell::EffectRedirectThreat,                           //130 SPELL_EFFECT_REDIRECT_THREAT
    &Spell::EffectPlaySound,                                //131 SPELL_EFFECT_PLAY_SOUND               sound id in misc value (SoundEntries.dbc)
    &Spell::EffectPlayMusic,                                //132 SPELL_EFFECT_PLAY_MUSIC               sound id in misc value (SoundEntries.dbc)
    &Spell::EffectUnlearnSpecialization,                    //133 SPELL_EFFECT_UNLEARN_SPECIALIZATION   unlearn profession specialization
    &Spell::EffectKillCreditGroup,                          //134 SPELL_EFFECT_KILL_CREDIT_GROUP        misc value is creature entry
    &Spell::EffectNULL,                                     //135 SPELL_EFFECT_CALL_PET
    &Spell::EffectHealPct,                                  //136 SPELL_EFFECT_HEAL_PCT
    &Spell::EffectEnergisePct,                              //137 SPELL_EFFECT_ENERGIZE_PCT
    &Spell::EffectLeapBack,                                 //138 SPELL_EFFECT_LEAP_BACK                Leap back
    &Spell::EffectUnused,                                   //139 SPELL_EFFECT_CLEAR_QUEST              (misc - is quest ID), unused
    &Spell::EffectForceCast,                                //140 SPELL_EFFECT_FORCE_CAST
    &Spell::EffectForceCast,                                //141 SPELL_EFFECT_FORCE_CAST_WITH_VALUE
    &Spell::EffectTriggerSpellWithValue,                    //142 SPELL_EFFECT_TRIGGER_SPELL_WITH_VALUE
    &Spell::EffectApplyAreaAura,                            //143 SPELL_EFFECT_APPLY_AREA_AURA_OWNER
    &Spell::EffectKnockBackFromPosition,                    //144 SPELL_EFFECT_KNOCKBACK_FROM_POSITION
    &Spell::EffectPullTowards,                              //145 SPELL_EFFECT_PULL_TOWARDS_DEST
    &Spell::EffectUnused,                                   //146 SPELL_EFFECT_146                      unused
    &Spell::EffectQuestFail,                                //147 SPELL_EFFECT_QUEST_FAIL               quest fail
    &Spell::EffectUnused,                                   //148 SPELL_EFFECT_148                      unused
    &Spell::EffectChargeDest,                               //149 SPELL_EFFECT_CHARGE_DEST                  swoop
    &Spell::EffectUnused,                                   //150 SPELL_EFFECT_150                      unused
    &Spell::EffectTriggerRitualOfSummoning,                 //151 SPELL_EFFECT_TRIGGER_SPELL_2
    &Spell::EffectNULL,                                     //152 SPELL_EFFECT_SUMMON_RAF_FRIEND                      summon Refer-a-Friend
    &Spell::EffectCreateTamedPet,                           //153 SPELL_EFFECT_CREATE_PET               misc value is creature entry
};

void Spell::EffectEmpty(SpellEffectIndex /*eff_idx*/)
{
    // NOT NEED ANY IMPLEMENTATION CODE, EFFECT POSISBLE USED AS MARKER OR CLIENT INFORM
}

void Spell::EffectNULL(SpellEffectIndex /*eff_idx*/)
{
    DEBUG_LOG("WORLD: Spell Effect DUMMY");
}

void Spell::EffectUnused(SpellEffectIndex /*eff_idx*/)
{
    // NOT USED BY ANY SPELL OR USELESS OR IMPLEMENTED IN DIFFERENT WAY IN MANGOS
}

void Spell::EffectInstaKill(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || !unitTarget->IsAlive())
        return;

    // Demonic Sacrifice
    if (m_spellInfo->Id == 18788 && unitTarget->GetTypeId() == TYPEID_UNIT)
    {
        uint32 entry = unitTarget->GetEntry();
        uint32 spellID;
        switch (entry)
        {
            case   416: spellID = 18789; break;             // imp
            case   417: spellID = 18792; break;             // fellhunter
            case  1860: spellID = 18790; break;             // void
            case  1863: spellID = 18791; break;             // succubus
            case 17252: spellID = 35701; break;             // fellguard
            default:
                sLog.outError("EffectInstaKill: Unhandled creature entry (%u) case.", entry);
                return;
        }

        m_caster->CastSpell(m_caster, spellID, TRIGGERED_OLD_TRIGGERED);
    }

    if (m_caster == unitTarget)                             // prevent interrupt message
        finish();

    WorldObject* caster = GetCastingObject();               // we need the original casting object

    WorldPacket data(SMSG_SPELLINSTAKILLLOG, (8 + 8 + 4));
    data << (caster && caster->GetTypeId() != TYPEID_GAMEOBJECT ? m_caster->GetObjectGuid() : ObjectGuid()); // Caster GUID
    data << unitTarget->GetObjectGuid();                    // Victim GUID
    data << uint32(m_spellInfo->Id);
    m_caster->SendMessageToSet(data, true);

    Unit::DealDamage(m_caster, unitTarget, unitTarget->GetHealth(), nullptr, INSTAKILL, SPELL_SCHOOL_MASK_NORMAL, m_spellInfo, false);
}

void Spell::EffectEnvironmentalDMG(SpellEffectIndex eff_idx)
{
    uint32 absorb = 0;
    int32 resist = 0;

    // Note: this hack with damage replace required until GO casting not implemented
    // environment damage spells already have around enemies targeting but this not help in case nonexistent GO casting support
    // currently each enemy selected explicitly and self cast damage, we prevent apply self casted spell bonuses/etc
    damage = m_spellInfo->CalculateSimpleValue(eff_idx);

    m_caster->CalculateDamageAbsorbAndResist(m_caster, GetSpellSchoolMask(m_spellInfo), SPELL_DIRECT_DAMAGE, damage, &absorb, &resist);

    m_caster->SendSpellNonMeleeDamageLog(m_caster, m_spellInfo->Id, damage, GetSpellSchoolMask(m_spellInfo), absorb, resist, false, 0, false);
    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        ((Player*)m_caster)->EnvironmentalDamage(DAMAGE_FIRE, damage);
}

void Spell::EffectSchoolDMG(SpellEffectIndex eff_idx)
{
    if (unitTarget && unitTarget->IsAlive())
    {
        switch (m_spellInfo->SpellFamilyName)
        {
            case SPELLFAMILY_GENERIC:
            {
                // Gore
                if (m_spellInfo->SpellIconID == 2269)
                {
                    damage += urand() % 2 ? damage : 0;
                }

                switch (m_spellInfo->Id)                    // better way to check unknown
                {
                    // Meteor like spells (divided damage to targets)
                    case 24340: case 26558: case 28884:     // Meteor
                    case 36837: case 38903: case 41276:     // Meteor
                    case 26789:                             // Shard of the Fallen Star
                    case 40810: case 43267: case 43268:     // Saber Lash
                    case 42384:                             // Brutal Swipe
                    case 45150:                             // Meteor Slash
                    {
                        uint32 count = 0;
                        for (TargetList::const_iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
                            if (ihit->effectHitMask & (1 << eff_idx))
                                ++count;

                        damage /= count;                    // divide to all targets
                        break;
                    }
                    // percent from health with min
                    case 25599:                             // Thundercrash
                    {
                        damage = unitTarget->GetHealth() / 2;
                        if (damage < 200)
                            damage = 200;
                        break;
                    }
                    case 33666:                             // Sonic Boom - Normal
                    case 38795:                             // Sonic Boom - Heroic
                    {
                        damage = (unitTarget->GetMaxHealth() * (m_spellInfo->Id == 33666 ? 90 : 95)) / 100;
                        break;
                    }
                    case 33671:                             // Shatter - Gruul
                    {
                        float x, y, z;
                        unitTarget->GetPosition(x, y, z);
                        damage = (20 - m_caster->GetDistance(x, y, z, DIST_CALC_COMBAT_REACH))*(damage / 20);
                        break;
                    }
                    // Lightning Strike
                    case 37841:
                        if (unitTarget->GetTypeId() == TYPEID_PLAYER && unitTarget->HasAura(37830)) // Repolarized Magneto Sphere
                            ((Player*)unitTarget)->KilledMonsterCredit(21910);
                        break;
                    // Cataclysmic Bolt
                    case 38441:
                        damage = unitTarget->GetMaxHealth() / 2;
                        break;
                    case 38977:                             // Spore Quake Effect
                        if (roll_chance_i(33))
                            m_caster->CastSpell(unitTarget, 39002, TRIGGERED_OLD_TRIGGERED); // Spore Quake Knockdown
                        break;
                    case 39384:
                    {
                        if (eff_idx == 0)
                        {
                            if (unitTarget->getFaction() == 1690)
                                damage = 10000;
                            else
                                damage = 0;
                        }
                        else
                        {
                            if (unitTarget->getFaction() == 1689)
                                damage = 10000;
                            else
                                damage = 0;
                        }
                        break;
                    }
                    case 40065: // Apexis Reprisal
                    {
                        damage = unitTarget->GetMaxHealth() / 3;
                        break;
                    }
                    case 43657: // Electrical Storm - Akil'zon
                    {
                        if (Aura* aura = m_caster->GetAura(43648, EFFECT_INDEX_1))
                            damage *= std::min(aura->GetAuraTicks(), uint32(3));
                        break;
                    }
                }
                break;
            }

            case SPELLFAMILY_MAGE:
            {
                // Arcane Blast
                if (m_spellInfo->SpellFamilyFlags & uint64(0x20000000))
                    m_caster->CastSpell(m_caster, 36032, TRIGGERED_INSTANT_CAST);
                break;
            }
            case SPELLFAMILY_WARRIOR:
            {
                // Bloodthirst
                if (m_spellInfo->SpellFamilyFlags & uint64(0x40000000000))
                {
                    damage = uint32(damage * (m_caster->GetTotalAttackPowerValue(BASE_ATTACK)) / 100);
                }
                // Shield Slam
                else if (m_spellInfo->SpellFamilyFlags & uint64(0x100000000))
                    damage += int32(m_caster->GetShieldBlockValue());
                break;
            }
            case SPELLFAMILY_WARLOCK:
            {
                // Incinerate Rank 1 & 2
                if ((m_spellInfo->SpellFamilyFlags & uint64(0x00004000000000)) && m_spellInfo->SpellIconID == 2128)
                {
                    // Incinerate does more dmg (dmg*0.25) if the target is Immolated.
                    if (unitTarget->HasAuraState(AURA_STATE_CONFLAGRATE))
                        damage += int32(damage * 0.25);
                }
                // Conflagrate - consumes Immolate
                else if (m_spellInfo->TargetAuraState == AURA_STATE_CONFLAGRATE)
                {
                    // for caster applied auras only
                    Unit::AuraList const& mPeriodic = unitTarget->GetAurasByType(SPELL_AURA_PERIODIC_DAMAGE);
                    for (auto i : mPeriodic)
                    {
                        if (i->GetCasterGuid() == m_caster->GetObjectGuid() &&
                                // Immolate
                                i->GetSpellProto()->IsFitToFamily(SPELLFAMILY_WARLOCK, uint64(0x0000000000000004)))
                        {
                            unitTarget->RemoveAurasByCasterSpell(i->GetId(), m_caster->GetObjectGuid());
                            break;
                        }
                    }
                }
                break;
            }
            case SPELLFAMILY_PRIEST:
            {
                break;
            }
            case SPELLFAMILY_DRUID:
            {
                // Ferocious Bite
                if ((m_spellInfo->SpellFamilyFlags & uint64(0x000800000)) && m_spellInfo->SpellVisual == 6587)
                {
                    // converts each extra point of energy into additional damage
                    damage += int32(m_caster->GetPower(POWER_ENERGY) * m_spellInfo->DmgMultiplier[eff_idx]);
                    m_caster->SetPower(POWER_ENERGY, 0);
                    // scaled AP bonus
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        damage += int32(m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * 0.03f * m_caster->GetComboPoints());
                    break;
                }
                // L5 Arcane Charge - Promenade Sentinal 23394
                if (m_spellInfo->Id == 41360)
                {
                    damage = unitTarget->GetMaxHealth();
                    break;
                }
                break;
            }
            case SPELLFAMILY_ROGUE:
            {
                // Envenom
                if (m_caster->GetTypeId() == TYPEID_PLAYER && (m_spellInfo->SpellFamilyFlags & uint64(0x800000000)))
                {
                    // consume from stack dozes not more that have combo-points
                    if (uint32 combo = m_caster->GetComboPoints())
                    {
                        Aura* poison = nullptr;
                        // Lookup for Deadly poison (only attacker applied)
                        Unit::AuraList const& auras = unitTarget->GetAurasByType(SPELL_AURA_PERIODIC_DAMAGE);
                        for (auto aura : auras)
                        {
                            if (aura->GetSpellProto()->SpellFamilyName == SPELLFAMILY_ROGUE &&
                                    aura->GetSpellProto()->SpellFamilyFlags & uint64(0x10000) &&
                                    aura->GetSpellProto()->SpellVisual == 5100 &&
                                    aura->GetCasterGuid() == m_caster->GetObjectGuid())
                            {
                                poison = aura;
                                break;
                            }
                        }
                        // count consumed deadly poison doses at target
                        if (poison)
                        {
                            uint32 spellId = poison->GetId();
                            uint32 doses = poison->GetStackAmount();
                            if (doses > combo)
                                doses = combo;

                            unitTarget->RemoveAuraHolderFromStack(spellId, doses, m_caster->GetObjectGuid());

                            damage *= doses;
                            damage += int32(((Player*)m_caster)->GetTotalAttackPowerValue(BASE_ATTACK) * 0.03f * doses);
                        }
                        // Eviscerate and Envenom Bonus Damage (item set effect)
                        if (m_caster->GetDummyAura(37169))
                            damage += m_caster->GetComboPoints() * 40;
                    }
                }
                // Eviscerate
                else if ((m_spellInfo->SpellFamilyFlags & uint64(0x00020000)) && m_caster->GetTypeId() == TYPEID_PLAYER)
                {
                    if (uint32 combo = m_caster->GetComboPoints())
                    {
                        damage += int32(m_caster->GetTotalAttackPowerValue(BASE_ATTACK) * combo * 0.03f);

                        // Eviscerate and Envenom Bonus Damage (item set effect)
                        if (m_caster->GetDummyAura(37169))
                            damage += combo * 40;
                    }
                }
                break;
            }
            case SPELLFAMILY_HUNTER:
            {
                // Steady Shot
                if (m_spellInfo->SpellFamilyFlags & uint64(0x100000000))
                {
                    bool found = false;

                    // check dazed affect
                    Unit::AuraList const& decSpeedList = unitTarget->GetAurasByType(SPELL_AURA_MOD_DECREASE_SPEED);
                    for (Unit::AuraList::const_iterator iter = decSpeedList.begin(); iter != decSpeedList.end(); ++iter)
                    {
                        if ((*iter)->GetSpellProto()->SpellIconID == 15 && (*iter)->GetSpellProto()->Dispel == 0)
                        {
                            found = true;
                            break;
                        }
                    }

                    if (found)
                        damage += CalculateSpellEffectValue(eff_idx, unitTarget);

                    int32 base = irand((int32)m_caster->GetBaseWeaponDamage(RANGED_ATTACK, MINDAMAGE), (int32)m_caster->GetBaseWeaponDamage(RANGED_ATTACK, MAXDAMAGE));
                    damage += int32(float(base) / m_caster->GetAttackTime(RANGED_ATTACK) * 2800);
                }
                break;
            }
            case SPELLFAMILY_PALADIN:
            {
                // Judgement of Vengeance
                if ((m_spellInfo->SpellFamilyFlags & uint64(0x800000000)) && m_spellInfo->SpellIconID == 2292)
                {
                    // Get stack of Holy Vengeance on the target added by caster
                    uint32 stacks = 0;
                    Unit::AuraList const& auras = unitTarget->GetAurasByType(SPELL_AURA_PERIODIC_DAMAGE);
                    for (auto aura : auras)
                    {
                        if ((aura->GetId() == 31803) && aura->GetCasterGuid() == m_caster->GetObjectGuid())
                        {
                            stacks = aura->GetStackAmount();
                            break;
                        }
                    }
                    if (!stacks)
                        // No damage if the target isn't affected by this
                        damage = -1;
                    else
                        damage *= stacks;
                }
                switch (m_spellInfo->Id)
                {
                    case 20467: // Judgement of Command
                    case 20963:
                    case 20964:
                    case 20965:
                    case 20966:
                    case 27171:
                        if (!unitTarget->IsStunned())
                            damage /= 2;
                        break;
                }
                break;
            }
        }

        if (damage >= 0)
            m_damagePerEffect[eff_idx] = CalculateSpellEffectDamage(unitTarget, damage);
    }
}

void Spell::EffectDummy(SpellEffectIndex eff_idx)
{
    // selection by spell family
    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            switch (m_spellInfo->Id)
            {
                case 2400:                                  // Transfer Powers
                {
                    if (unitTarget)
                        m_caster->CastSpell(unitTarget, 26565, TRIGGERED_OLD_TRIGGERED);   // Heal Brethren

                    return;
                }
                case 3360:                                  // Curse of the Eye
                {
                    if (unitTarget)
                        m_caster->CastSpell(unitTarget, ((unitTarget->getGender() == GENDER_MALE) ? 10651 : 10653), TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 4131:                                  // Banish Cresting Exile
                {
                    if (!unitTarget)
                        return;

                    DoScriptText(-1010004, unitTarget, m_caster);
                    unitTarget->CastSpell(nullptr, 3617, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 7671:                                  // Transformation (human<->worgen)
                {
                    if (unitTarget) // Transform Visual
                        unitTarget->CastSpell(unitTarget, 24085, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 8063:                                  // Deviate Fish
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // 8064 = Sleepy | 8065 = Invigorate | 8066 = Shrink | 8067 = Party Time! | 8068 = Healthy Spirit
                        const uint32 spell_list[5] = {8064, 8065, 8066, 8067, 8068};
                        m_caster->CastSpell(m_caster, spell_list[urand(0, 4)], TRIGGERED_OLD_TRIGGERED, nullptr);
                    }

                    return;
                }
                case 8213:                                  // Savory Deviate Delight
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(m_caster, (urand(0, 1)
                                                       ? (m_caster->getGender() == GENDER_MALE ? 8219 : 8220)                      // Flip Out - ninja
                                                       : (m_caster->getGender() == GENDER_MALE ? 8221 : 8222)), TRIGGERED_OLD_TRIGGERED, nullptr);    // Yaaarrrr - pirate

                    return;
                }
                case 8344:                                  // Gnomish Universal Remote (ItemID: 7506)
                {
                    if (m_CastItem && unitTarget)
                    {
                        // 8345 - Control the machine | 8346 = Malfunction the machine (root) | 8347 = Taunt/enrage the machine
                        const uint32 spell_list[3] = { 8345, 8346, 8347 };
                        m_caster->CastSpell(unitTarget, spell_list[urand(0, 2)], TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    }

                    return;
                }
                case 8606:                                  // Summon Cyclonian
                {
                    if (!(m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION))
                        return;

                    float x, y, z;
                    m_targets.getDestination(x, y, z); // database loaded coordinates due to target type
                    m_caster->SummonCreature(6239, x, y, z, 0.0f, TEMPSPAWN_TIMED_OOC_DESPAWN, 30 * IN_MILLISECONDS);

                    return;
                }
                case 9012:                                  // Attract Rift Spawn
                {
                    if (!unitTarget || !unitTarget->HasAura(9032))
                        return;

                    unitTarget->CastSpell(unitTarget, 9010, TRIGGERED_NONE);
                    return;
                }
                case 9204:                                  // Hate to Zero
                case 20538:
                case 26569:
                case 26637:
                {
                    m_caster->getThreatManager().modifyThreatPercent(unitTarget, -100);
                    return;
                }
                case 9976:                                  // Polly Eats the E.C.A.C.
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                    {
                        // Summon Polly Jr.
                        unitTarget->CastSpell(unitTarget, 9998, TRIGGERED_OLD_TRIGGERED);
                        ((Creature*)unitTarget)->ForcedDespawn(100);
                    }

                    return;
                }
                case 10254:                                 // Stone Dwarf Awaken Visual
                {
                    if (m_caster->GetTypeId() == TYPEID_UNIT) // see spell 10255 (aura dummy)
                    {
                        m_caster->clearUnitState(UNIT_STAT_ROOT);
                        m_caster->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER | UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_NOT_SELECTABLE);
                    }

                    return;
                }
                case 12975:                                 // Last Stand
                {
                    int32 healthModSpellBasePoints0 = int32(m_caster->GetMaxHealth() * 0.3);
                    m_caster->CastCustomSpell(m_caster, 12976, &healthModSpellBasePoints0, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, nullptr);

                    return;
                }
                case 13006:                                 // Gnomish Shrink Ray (ItemID: 10716)
                {
                    if (unitTarget && m_CastItem)
                    {
                        uint32 roll = urand(0, 99);
                        // These rates are hella random; someone feel free to correct them
                        if (roll < 3)                                         // Whole party will grow
                            m_caster->CastSpell(m_caster, 13004, TRIGGERED_OLD_TRIGGERED);
                        else if (roll < 6)                                    // Whole party will shrink
                            m_caster->CastSpell(m_caster, 13010, TRIGGERED_OLD_TRIGGERED);
                        else if (roll < 9)                                    // Whole enemy 'team' will grow
                            m_caster->CastSpell(unitTarget, 13004, TRIGGERED_OLD_TRIGGERED);
                        else if (roll < 12)                                    // Whole enemy 'team' will shrink
                            m_caster->CastSpell(unitTarget, 13010, TRIGGERED_OLD_TRIGGERED);
                        else if (roll < 24)                                   // Caster will shrink
                            m_caster->CastSpell(m_caster, 13003, TRIGGERED_OLD_TRIGGERED);
                        else                                                  // Enemy target will shrink
                            m_caster->CastSpell(unitTarget, 13003, TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 13120:                                 // Net-O-Matic
                {
                    if (unitTarget && m_CastItem)
                    {
                        uint32 roll = urand(0, 99);
                        if (roll < 2)                           // 2% for 30 sec self root (off-like chance unknown)
                            m_caster->CastSpell(unitTarget, 16566, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 4)                      // 2% for 20 sec root, charge to target (off-like chance unknown)
                            m_caster->CastSpell(unitTarget, 13119, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else                                    // normal root
                            m_caster->CastSpell(unitTarget, 13099, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    }

                    return;
                }
                case 13180:                                 // Gnomish Mind Control Cap (ItemID: 10726)
                {
                    if (unitTarget && m_CastItem)
                    {
                        uint32 roll = urand(0, 9);
                        if (roll == 1 && unitTarget->GetTypeId() == TYPEID_PLAYER)
                            unitTarget->CastSpell(m_caster, 13181, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll)
                            m_caster->CastSpell(unitTarget, 13181, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    }

                    return;
                }
                case 13489:
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 14744, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 13567:                                 // Dummy Trigger
                {
                    // can be used for different aura triggering, so select by aura
                    if (m_triggeredByAuraSpell && unitTarget)
                    {
                        switch (m_triggeredByAuraSpell->Id)
                        {
                            case 26467:                         // Persistent Shield
                                m_caster->CastCustomSpell(unitTarget, 26470, &damage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                                break;
                            default:
                                sLog.outError("EffectDummy: Non-handled case for spell 13567 for triggered aura %u", m_triggeredByAuraSpell->Id);
                                break;
                        }
                    }

                    return;
                }
                case 14537:                                 // Six Demon Bag
                {
                    if (unitTarget)
                    {
                        uint32 roll = urand(0, 99);
                        if (roll < 25)                          // Fireball (25% chance)
                            m_caster->CastSpell(unitTarget, 15662, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 50)                     // Frostbolt (25% chance)
                            m_caster->CastSpell(unitTarget, 11538, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 70)                     // Chain Lighting (20% chance)
                            m_caster->CastSpell(unitTarget, 21179, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 85)                     // Enveloping Winds (15% chance)
                            m_caster->CastSpell(unitTarget, 25189, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 90)                     // Summon Felhund minion (5% chance)
                            m_caster->CastSpell(m_caster, 14642, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else if (roll < 97)                     // Polymorph (7% to target, 10% chance total)
                            m_caster->CastSpell(unitTarget, 14621, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                        else                                    // Polymorph (3% to self, backfire, 10% chance total)
                            m_caster->CastSpell(m_caster, 14621, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    }

                    return;
                }
                case 15998:                                 // Capture Worg Pup
                case 29435:                                 // Capture Female Kaliri Hatchling
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                        ((Creature*)unitTarget)->ForcedDespawn();

                    return;
                }
                case 16049:                                 // Emberseer Growing
                {
                    if (UnitAI* ai = m_caster->AI())
                        ai->SendAIEvent(AI_EVENT_CUSTOM_A, m_caster, m_caster);
                    return;
                }
                case 16378:                                 // Temperature Reading
                {
                    if (!unitTarget || !m_caster->IsPlayer())
                        return;

                    switch (unitTarget->GetGUIDLow()) // sadly each spawn does different texts - meant to be db guids
                    {
                        case 23712: // Z: -241.0724
                        {
                            static std::vector<int32> textIds = {-1010012, -1010013, -1010014};
                            DoScriptText(textIds[urand(0, textIds.size() - 1)], unitTarget, m_caster);
                            break;
                        }
                        case 23713: // Z: -265.2025
                        {
                            static std::vector<int32> textIds = {-1010009, -1010010, -1010011};
                            DoScriptText(textIds[urand(0, textIds.size() - 1)], unitTarget, m_caster);
                            break;
                        }
                        case 23714: // Z: -240.8598
                        {
                            static std::vector<int32> textIds = {-1010015, -1010016, -1010017};
                            DoScriptText(textIds[urand(0, textIds.size() - 1)], unitTarget, m_caster);
                            break;
                        }
                        case 23715: // Z: -246.8467
                        {
                            static std::vector<int32> textIds = {-1010015, -1010016, -1010017};
                            DoScriptText(textIds[urand(0, textIds.size() - 1)], unitTarget, m_caster);
                            break;
                        }
                        case 23716: // Z: -186.0754 quest completion one
                        {
                            static std::vector<int32> textIds = {-1010018, -1010019, -1010020, -1010021};
                            DoScriptText(textIds[urand(0, textIds.size() - 1)], unitTarget, m_caster);
                            Player* player = static_cast<Player*>(m_caster);
                            player->RewardPlayerAndGroupAtEventCredit(unitTarget->GetEntry(), unitTarget);
                            break;
                        }
                        default:
                        {
                            sLog.outErrorDb("Database has wrong data for q.974 - guids do not correspond.");
                            break;
                        }
                    }

                    return;
                }
                case 16589:                                 // Noggenfogger Elixir
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        const uint32 spell_list[3] = {16595, 16593, 16591};
                        m_caster->CastSpell(m_caster, spell_list[urand(0, 2)], TRIGGERED_OLD_TRIGGERED, nullptr);
                    }

                    return;
                }
                case 17009:                                 // Voodoo
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        // 16707 = Hex | 16708 = Hex | 16709 = Hex | 16711 = Grow | 16712 = Special Brew | 16713 = Ghostly | 16716 = Launch
                        const uint32 spell_list[7] = {16707, 16708, 16709, 16711, 16712, 16713, 16716};
                        m_caster->CastSpell(unitTarget, spell_list[urand(0, 6)], TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_originalCasterGUID, m_spellInfo);
                    }

                    return;
                }
                case 17251:                                 // Spirit Healer Res
                {
                    if (unitTarget)
                    {
                        Unit* caster = GetAffectiveCaster();
                        if (caster && caster->GetTypeId() == TYPEID_PLAYER)
                        {
                            WorldPacket data(SMSG_SPIRIT_HEALER_CONFIRM, 8);
                            data << unitTarget->GetObjectGuid();
                            ((Player*)caster)->GetSession()->SendPacket(data);
                        }
                    }

                    return;
                }
                case 17271:                                 // Test Fetid Skull
                {
                    // 17269 = Create Resonating Skull | 17270 = Create Bone Dust
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(m_caster, (urand(0, 1) ? 17269 : 17270), TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 17678:                                 // Despawn Spectral Combatants (sic)
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                    {
                        Creature* creatureTarget = (Creature*)unitTarget;
                        if (creatureTarget)
                            creatureTarget->ForcedDespawn(3000);
                    }

                    return;
                }
                case 17770:                                 // Wolfshead Helm Energy
                {
                    m_caster->CastSpell(m_caster, 29940, TRIGGERED_OLD_TRIGGERED, nullptr);

                    return;
                }
                case 17950:                                 // Shadow Portal
                {
                    if (unitTarget)
                    {
                        const uint32 spell_list[6] = {17863, 17939, 17943, 17944, 17946, 17948};
                        m_caster->CastSpell(unitTarget, spell_list[urand(0, 5)], TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 18350:                                 // Dummy Trigger
                {
                    if (m_triggeredByAuraSpell && unitTarget)
                    {
                        switch (m_triggeredByAuraSpell->Id)
                        {
                            case 13810: // Frost Trap Aura
                            {
                                // Need to check casting of entrapment on every pulse
                                // Chose this route so that whole proc system doesnt have to run
                                // IDs are in reverse order because its more likely someone will have max rank
                                float chance = 0.f;
                                uint32 entrapmentIDs[] = { 19388 , 19387, 19184 };
                                for (uint32 spellId : entrapmentIDs)
                                    if (SpellAuraHolder* holder = m_caster->GetSpellAuraHolder(spellId))
                                    {
                                        chance = holder->GetSpellProto()->procChance;
                                        break;
                                    }

                                if (roll_chance_f(chance))
                                    m_caster->CastSpell(unitTarget, 19185, TRIGGERED_OLD_TRIGGERED);
                                break;
                            }
                            case 28821: // Lightning Shield
                            {
                                // Need remove self if Lightning Shield not active
                                Unit::SpellAuraHolderMap const& auras = unitTarget->GetSpellAuraHolderMap();
                                for (const auto& aura : auras)
                                {
                                    SpellEntry const* spell = aura.second->GetSpellProto();
                                    if (spell->SpellFamilyName == SPELLFAMILY_SHAMAN
                                        && spell->SpellFamilyFlags & uint64(0x0000000000000400))
                                        return;
                                }

                                unitTarget->RemoveAurasDueToSpell(28820);
                                break;
                            }
                            case 28820:                             // Lightning Shield (The Earthshatterer set trigger after cast Lighting Shield)
                            {
                                // Need remove self if Lightning Shield not active
                                Unit::SpellAuraHolderMap const& auras = unitTarget->GetSpellAuraHolderMap();
                                for (const auto& aura : auras)
                                {
                                    SpellEntry const* spell = aura.second->GetSpellProto();
                                    if (spell->SpellFamilyName == SPELLFAMILY_SHAMAN &&
                                        (spell->SpellFamilyFlags & uint64(0x0000000000000400)))
                                        return;
                                }
                                unitTarget->RemoveAurasDueToSpell(28820);
                                return;
                            }
                            case 38443:                             // Totemic Mastery (Skyshatter Regalia (Shaman Tier 6) - bonus)
                            {
                                if (unitTarget->IsAllTotemSlotsUsed())
                                    unitTarget->CastSpell(nullptr, 38437, TRIGGERED_OLD_TRIGGERED, nullptr);
                                else
                                    unitTarget->RemoveAurasDueToSpell(38437);
                                return;
                            }
                            case 37594: // Greater Heal Refund
                            {
                                // If your Greater Heal brings the target to full health, you gain $37595s1 mana.
                                if (unitTarget->GetHealth() == unitTarget->GetMaxHealth())
                                    m_caster->CastSpell(nullptr, 37595, TRIGGERED_OLD_TRIGGERED);
                                break;
                            }
                            case 37705: // Healing Discount
                            {
                                uint32 spellId = 0;
                                switch (m_caster->getClass())
                                {
                                    case CLASS_PALADIN:
                                        spellId = 37723;
                                        break;
                                    case CLASS_PRIEST:
                                        spellId = 37706;
                                        break;
                                    case CLASS_SHAMAN:
                                        spellId = 37722;
                                        break;
                                    case CLASS_DRUID:
                                        spellId = 37721;
                                        break;
                                }
                                m_caster->CastSpell(nullptr, spellId, TRIGGERED_OLD_TRIGGERED);
                                break;
                            }
                        }
                    }
                    return;
                }
                case 18947:                                 // Baron Geddon - Inferno
                {
                    Aura* aura = m_caster->GetAura(m_triggeredByAuraSpell->Id, EFFECT_INDEX_0);
                    if (!aura)
                        return;
                    int32 damageForTick[8] = { 500, 500, 1000, 1000, 2000, 2000, 3000, 5000 };
                    m_caster->CastCustomSpell(nullptr, 19698, &damageForTick[aura->GetAuraTicks() - 1], nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 19395:                                 // Gordunni Trap
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->CastSpell(unitTarget, urand(0, 1) ? 19394 : 11756, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 19411:                                 // Lava Bomb
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 20494, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 19484:
                {
                    if (unitTarget)
                    {
                        unitTarget->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                        unitTarget->CastSpell(nullptr, 19527, TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
                case 20474:                                 // Lava Bomb
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 20495, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 19869:                                 // Dragon Orb
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER && !unitTarget->HasAura(23958))
                        unitTarget->CastSpell(nullptr, 19832, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 20037:                                 // Explode Orb Effect
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 20038, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 20577:                                 // Cannibalize
                {
                    m_caster->CastSpell(nullptr, 20578, TRIGGERED_NONE);
                    return;
                }
                case 21108:                                 // Summon Sons of Flame
                {
                    // Trigger the eight summoning spells for the adds in Ragnaros encounter
                    for (const uint32 spell : {21110, 21111, 21112, 21113, 21114, 21115, 21116, 21117})
                    m_caster->CastSpell(m_caster, spell, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 21147:                                 // Arcane Vacuum
                {
                    if (unitTarget)
                    {
                        // Spell used by Azuregos to teleport all the players to him
                        // This also resets the target threat
                        if (m_caster->getThreatManager().getThreat(unitTarget))
                            m_caster->getThreatManager().modifyThreatPercent(unitTarget, -100);

                        // cast summon player
                        m_caster->CastSpell(unitTarget, 21150, TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 21908:                                 // Lava Burst Randomizer
                {
                    // randomly cast one of the nine Lava Burst spell A to I in Ragnaros encounter
                    const uint32 spell_list[9] = {21886, 21900, 21901, 21902, 21903, 21904, 21905, 21906, 21907};
                    m_caster->CastSpell(m_caster, spell_list[urand(0, 8)], TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 22276:                                 // Elemental Shield
                {
                    const uint32 elemshields[] = { 22277, 22278, 22279, 22280, 22281 };

                    for (uint32 spell : elemshields)
                        if (m_caster->HasAura(spell))
                            m_caster->RemoveAurasDueToSpell(spell);
                    m_caster->CastSpell(m_caster, elemshields[urand(0, 4)], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 22282:                                 // Brood Power
                {
                    uint32 broodpowers[] = { 22283, 22285, 22286, 22287, 22288 };

                    for (uint32 spell : broodpowers)
                        if (m_caster->HasAura(spell))
                            m_caster->RemoveAurasDueToSpell(spell);
                    m_caster->CastSpell(m_caster, broodpowers[urand(0, 4)], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 22659:                                 // Spawn Drakonid
                {
                    // Spawn drakonids depending on caster color (spawner type)
                    uint32 spellSummonDrakonid = 0;
                    switch (m_caster->GetEntry())
                    {
                        case 14312: spellSummonDrakonid = 22658; break; // Blue
                        case 14310: spellSummonDrakonid = 22656; break; // Green
                        case 14311: spellSummonDrakonid = 22657; break; // Bronze
                        case 14309: spellSummonDrakonid = 22655; break; // Red
                        case 14307: spellSummonDrakonid = 22654; break; // Black
                        default: return;
                    }
                    m_caster->CastSpell(m_caster, spellSummonDrakonid, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 22664:                                 // Shadowblink
                {
                    if (eff_idx == EFFECT_INDEX_1)
                    {
                        // randomly cast one of the nine Shadowblink spell in Nefarian encounter (phase 1)
                        const uint32 spell_list[9] = {22668, 22669, 22670, 22671, 22672, 22673, 22674, 22675, 22676};
                        m_caster->CastSpell(nullptr, spell_list[urand(0, 8)], TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
                case 23019:                                 // Crystal Prison Dummy DND
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->IsAlive())
                    {
                        Creature* creatureTarget = (Creature*)unitTarget;
                        if (!creatureTarget->IsPet())
                        {
                            creatureTarget->CastSpell(creatureTarget, 23022, TRIGGERED_OLD_TRIGGERED);
                            creatureTarget->ForcedDespawn();
                        }
                    }

                    return;
                }
                case 23074:                                 // Arcanite Dragonling
                {
                    if (m_CastItem)
                        m_caster->CastSpell(m_caster, 19804, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 23075:                                 // Mithril Mechanical Dragonling
                {
                    if (m_CastItem)
                        m_caster->CastSpell(m_caster, 12749, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 23076:                                 // Mechanical Dragonling
                {
                    if (m_CastItem)
                        m_caster->CastSpell(m_caster, 4073, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 23133:                                 // Gnomish Battle Chicken
                {
                    if (m_CastItem)
                        m_caster->CastSpell(m_caster, 13166, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 23134:                                 // Goblin Bomb Dispenser
                {
                    if (m_CastItem)
                        m_caster->CastSpell(m_caster, 13258, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 23138:                                 // Gate of Shazzrah
                {
                    if (!unitTarget || m_scriptValue > 0)
                        return;
                    m_scriptValue = 1; // mark as executed

                    std::vector<Unit*> possibleTargets;
                    possibleTargets.reserve(m_UniqueTargetInfo.size());
                    for (TargetList::const_iterator itr = m_UniqueTargetInfo.begin(); itr != m_UniqueTargetInfo.end(); ++itr)
                    {
                        // Skip Non-Players
                        if (!itr->targetGUID.IsPlayer())
                            continue;

                        if (Unit* target = m_caster->GetMap()->GetPlayer(itr->targetGUID))
                            possibleTargets.push_back(target);
                    }

                    // Cast Siphon Soul channeling spell
                    if (!possibleTargets.empty())
                        possibleTargets[urand(0, possibleTargets.size() - 1)]->CastSpell(m_caster, 23139, TRIGGERED_NONE);

                    if (m_caster->AI())
                        m_caster->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, m_caster, m_caster);

                    return;
                }
                case 23173:                                 // Brood Affliction - TODO: Rework to use proper targeting
                {
                    // This spell selects one brood affliction amongst five and apply it onto 15 targets
                    // If there are less than 15 targets, then the spell loops over the targets again
                    // until there are 15 appliance of the chosen brood affliction

                    // Brood Affliction selection
                    uint32 afflictions[] = { 23153, 23154, 23155, 23170, 23169 };   // Blue / Black / Red / Bronze / Green
                    uint32 spellAfflict = afflictions[urand(0, 4)];

                    // Get the fifteen (potentially duplicate) targets from threat list
                    GuidVector vGuids;
                    ((Creature*)m_caster)->FillGuidsListFromThreatList(vGuids);

                    std::vector<Unit*> fifteenTargets;
                    uint8 targetsCount = 0;
                    while (targetsCount < 15)
                    {
                        for (GuidVector::const_iterator i = vGuids.begin(); i != vGuids.end(); ++i)
                        {
                            Unit* unit = m_caster->GetMap()->GetUnit(*i);
                            if (unit && targetsCount < 15 && unit->GetTypeId() == TYPEID_PLAYER && unit->IsAlive())
                            {
                                fifteenTargets.push_back(unit);
                                targetsCount++;
                            }
                            else break;
                        }
                        // Prevent infinite loop: if fifteenTargets is still empty after first iteration: return
                        if (targetsCount == 0)
                        {
                            return;
                        }
                    }

                    for (auto unit : fifteenTargets)
                    {
                        // Cast Brood Affliction if not mutated
                        if (!(unit->HasAura(23174, EFFECT_INDEX_0)))
                            m_caster->CastSpell(unit, spellAfflict, TRIGGERED_OLD_TRIGGERED);

                        // Cast Chromatic Mutation (23174) if target is now affected by all five brood afflictions
                        if (unit->HasAura(23153, EFFECT_INDEX_0)
                                && unit->HasAura(23154, EFFECT_INDEX_0)
                                && unit->HasAura(23155, EFFECT_INDEX_0)
                                && unit->HasAura(23170, EFFECT_INDEX_0)
                                && unit->HasAura(23169, EFFECT_INDEX_0))
                        {
                            unit->RemoveAllAuras();
                            m_caster->CastSpell(unit, 23174, TRIGGERED_OLD_TRIGGERED);
                            unit->CastSpell(unit, 23175, TRIGGERED_OLD_TRIGGERED);
                            unit->CastSpell(unit, 23177, TRIGGERED_OLD_TRIGGERED);
                        }
                    }
                    return;
                }
                case 23195:                                 // Dragondog Breath Selection
                {
                    // This spell selects two breaths for Chromaggus amongst five and send them to BWL instance script through events

                    // Breaths selection
                    // 5 possiblities for the first breath, 4 for the second: 20 total possiblites
                    uint8 rightBreath = urand(0, 4);
                    uint8 leftBreath = (rightBreath + urand(1, 4)) % 5;

                    // Sending left breath to instance script
                    uint32 leftBreaths[] = { 23317, 23318, 23319, 23320, 23321 };
                    m_caster->CastSpell(m_caster, leftBreaths[leftBreath], TRIGGERED_OLD_TRIGGERED);

                    // Sending right breath to instance script
                    uint32 rightBreaths[] = { 23322, 23323, 23324, 23325, 23326 };
                    m_caster->CastSpell(m_caster, rightBreaths[rightBreath], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 23343:                                 // Nefarian Tunnel Selection
                {
                    // This spell selects two kinds of drakonids amongst five and send them to BWL instance script through events

                    // Drakonids selection
                    // 5 possiblities for the first kind, 4 for the second: 20 total possiblites
                    uint8 rightDrakonid = urand(0, 4);
                    uint8 leftDrakonid = (rightDrakonid + urand(1, 4)) % 5;

                    // Sending left tunnel selection to instance script
                    uint32 leftDrakonids[] = { 23344, 23345, 23346, 23347, 23348 };
                    m_caster->CastSpell(m_caster, leftDrakonids[leftDrakonid], TRIGGERED_OLD_TRIGGERED);

                    // Sending right tunnel selection to instance script
                    uint32 rightDrakonids[] = { 23349, 23350, 23351, 23352, 23353 };
                    m_caster->CastSpell(m_caster, rightDrakonids[rightDrakonid], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 23450:                                 // Transporter Arrival - (Gadgetzan + Everlook)
                {
                    uint32 rand = urand(0, 5);              // Roll for minor malfunctions:
                    if (!rand)                              // (1/6) - Polymorph (23456 & 23457 are both carbon copies of this one)
                        m_caster->CastSpell(m_caster, 23444, TRIGGERED_OLD_TRIGGERED);
                    else if (rand <= 2)                     // (2/6) - Evil Twin
                        m_caster->CastSpell(m_caster, 23445, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 23453:                                 // Gnomish Transporter - Ultrasafe Transporter: Gadgetzan
                {
                    // Roll chance for major malfunction (1/6); 23441 = success | 23446 = malfunction (missed destination)
                    m_caster->CastSpell(m_caster, (urand(0, 5) ? 23441 : 23446), TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 23645:                                 // Hourglass Sand
                {
                    m_caster->RemoveAurasDueToSpell(23170); // Brood Affliction: Bronze

                    return;
                }
                case 23725:                                 // Gift of Life (warrior bwl trinket)
                {
                    m_caster->CastSpell(nullptr, 23782, TRIGGERED_OLD_TRIGGERED);
                    // m_caster->CastSpell(nullptr, 23783, TRIGGERED_OLD_TRIGGERED); // Patch 2.1 no longer heals
                    return;
                }
                case 23484:                                 // Dispel Drakonids
                {
                    // Despawn all drakonids from Nefarian phase 1
                    if (unitTarget->GetTypeId() == TYPEID_UNIT)
                    {
                        switch (unitTarget->GetEntry())
                        {
                            case 14261:
                            case 14262:
                            case 14263:
                            case 14264:
                            case 14265:
                            case 14302:
                                ((Creature*)unitTarget)->ForcedDespawn();
                        }
                    }
                    return;
                }
                case 24019:                                 // Gurubashi Axe Thrower; Axe Flurry.
                {
                    if (unitTarget && m_caster->IsWithinLOSInMap(unitTarget, true))
                        m_caster->CastSpell(unitTarget, 24020, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 24150:                                 // Stinger Charge Primer
                {
                    if (unitTarget->HasAura(25187))
                        m_caster->CastSpell(unitTarget, 25191, TRIGGERED_OLD_TRIGGERED);
                    else
                        m_caster->CastSpell(unitTarget, 25190, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 24796:                                 // Summon Demented Druid Spirit
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(unitTarget, 24795, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 25145:                                 // Merithra's Wake
                {
                    unitTarget->CastSpell(unitTarget, 25172, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25149:                                 // Arygos's Vengeance
                {
                    unitTarget->CastSpell(unitTarget, 25168, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25150:                                 // Molten Rain
                {
                    unitTarget->CastSpell(unitTarget, 25169, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 25170, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25158:                                 // Time Stop
                {
                    unitTarget->SetImmuneToNPC(true);
                    unitTarget->RemoveAllAuras();
                    unitTarget->CastSpell(unitTarget, 25171, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25792:                                 // Despawn Brood
                {
                    // Despawn all Yauj Brood
                    if (unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->GetEntry() == 15621)
                        ((Creature*)unitTarget)->ForcedDespawn();
                    return;
                }
                case 26080:                                 // Stinger Charge Primer
                {
                    if (unitTarget->HasAura(26078))
                        m_caster->CastSpell(unitTarget, 26082, TRIGGERED_OLD_TRIGGERED);
                    else
                        m_caster->CastSpell(unitTarget, 26081, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 24721:                                 // Buru Transform
                {
                    // remaining Buru Eggs summon Hive'Zara Hatchlings and despawn
                    if (unitTarget->GetEntry() == 15514)
                    {
                        unitTarget->CastSpell(unitTarget, 1881, TRIGGERED_OLD_TRIGGERED);
                        ((Creature*)unitTarget)->ForcedDespawn();
                    }

                    return;
                }
                case 24781:                                 // Dream Fog
                {
                    // Let the current target be and move to the new one
                    if (m_caster->GetVictim())
                    {
                        m_caster->DeleteThreatList();
                        m_caster->AttackStop(true, false, false);
                    }
                    if (unitTarget && m_caster->AI())
                        m_caster->AI()->AttackStart(unitTarget);

                    return;
                }
                case 24886:                                 // Despawn Taerar Shades
                {
                    if (unitTarget && unitTarget->GetEntry() == 15302)
                    {
                        ((Creature*)unitTarget)->ForcedDespawn();
                        ((Creature*)unitTarget)->RemoveFromWorld();
                    }

                    return;
                }
                case 24930:                                 // Hallow's End Treat
                {
                    // 24924 = Larger and Orange | 24925 = Skeleton | 24926 = Pirate | 24927 = Ghost
                    const uint32 spell_list[4] = {24924, 24925, 24926, 24927};
                    m_caster->CastSpell(m_caster, spell_list[urand(0, 3)], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 25860:                                 // Reindeer Transformation
                {
                    if (!m_caster->HasAuraType(SPELL_AURA_MOUNTED))
                        return;

                    float flyspeed = m_caster->GetSpeedRate(MOVE_FLIGHT);
                    float speed = m_caster->GetSpeedRate(MOVE_RUN);

                    m_caster->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

                    // 5 different spells used depending on mounted speed and if mount can fly or not
                    if (flyspeed >= 4.1f)
                        // Flying Reindeer
                        m_caster->CastSpell(m_caster, 44827, TRIGGERED_OLD_TRIGGERED); // 310% flying Reindeer
                    else if (flyspeed >= 3.8f)
                        // Flying Reindeer
                        m_caster->CastSpell(m_caster, 44825, TRIGGERED_OLD_TRIGGERED); // 280% flying Reindeer
                    else if (flyspeed >= 1.6f)
                        // Flying Reindeer
                        m_caster->CastSpell(m_caster, 44824, TRIGGERED_OLD_TRIGGERED); // 60% flying Reindeer
                    else if (speed >= 2.0f)
                        // Reindeer
                        m_caster->CastSpell(m_caster, 25859, TRIGGERED_OLD_TRIGGERED); // 100% ground Reindeer
                    else
                        // Reindeer
                        m_caster->CastSpell(m_caster, 25858, TRIGGERED_OLD_TRIGGERED); // 60% ground Reindeer

                    return;
                }
                case 26074:                                 // Holiday Cheer
                {
                    // implemented at client side
                    return;
                }
                case 26374:                                 // Elune's Candle
                {
                    if (unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->GetEntry() == 15467)  // Omen
                    {
                        uint32 eluneCandle[5] = { 26622, 26623, 26624, 26625, 26649 };
                        m_caster->CastSpell(unitTarget, eluneCandle[urand(0, 4)], TRIGGERED_OLD_TRIGGERED); // Damage (random visual)
                        return;
                    }
                    // Default harmless spell
                    m_caster->CastSpell(unitTarget, 26636, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 26399:                                 // Despawn Tentacles
                {
                    if (unitTarget->GetTypeId() == TYPEID_UNIT)
                        ((Creature*)unitTarget)->ForcedDespawn();
                    return;
                }
                case 26626:                                 // Mana Burn Area
                {
                    if (unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->GetPowerType() == POWER_MANA)
                        m_caster->CastSpell(unitTarget, 25779, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 26899:                                 // Give Friendship Bracers
                {
                    if ((unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT) || !unitTarget->HasAura(26898)) // Target is not a player or is not heartbroken
                        return;

                    unitTarget->RemoveAurasDueToSpell(26898);                               // Remove Heartbroken
                    unitTarget->CastSpell(unitTarget, 26921, TRIGGERED_OLD_TRIGGERED);      // cast Cancel Heartbroken, Create Bracelet
                    return;
                }
                case 28000:                                 // Land Mine Trigger
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(nullptr, 25099, TRIGGERED_OLD_TRIGGERED);       // Detonation
                    m_caster->RemoveAurasDueToSpell(27999);                             // Land Mine Periodic
                    static_cast<Creature*>(m_caster)->ForcedDespawn(2000);
                    return;
                }
                case 28006:                                 // Arcane Cloaking
                {
                    // Naxxramas Entry Flag Effect DND
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                        m_caster->CastSpell(unitTarget, 29296, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 28089:                                 // Polarity Shift
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(28059);
                    unitTarget->RemoveAurasDueToSpell(28084);

                    // 28059 28084
                    switch (m_scriptValue)
                    {
                        case 0: // first target random
                            m_scriptValue = urand(0, 1) ? 28059 : 28084;
                            unitTarget->CastSpell(unitTarget, m_scriptValue, TRIGGERED_OLD_TRIGGERED);
                            break;
                        case 28059: // second target the other
                            m_scriptValue = 1;
                            unitTarget->CastSpell(unitTarget, 28084, TRIGGERED_OLD_TRIGGERED);
                            break;
                        case 28084:
                            m_scriptValue = 1;
                            unitTarget->CastSpell(unitTarget, 28059, TRIGGERED_OLD_TRIGGERED);
                            break;
                        default: // third and later random
                            unitTarget->CastSpell(unitTarget, urand(0, 1) ? 28059 : 28084, TRIGGERED_OLD_TRIGGERED);
                            break;
                    }
                    return;
                }
                case 28098:                                 // Stalagg Tesla Effect
                case 28110:                                 // Feugen Tesla Effect
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->IsAlive())
                    {
                        if (!m_caster->hasUnitState(UNIT_STAT_ROOT))    // This state is found in sniffs and is probably caused by another aura like 23973
                            m_caster->addUnitState(UNIT_STAT_ROOT);     // but as we are not sure (the aura does not show up in sniffs), we handle the state here

                        // Cast chain (Stalagg Chain or Feugen Chain)
                        uint32 chainSpellId = m_spellInfo->Id == 28098 ? 28096 : 28111;
                        // Only cast if not already present and in range
                        if (!unitTarget->HasAura(chainSpellId) && m_caster->IsWithinDistInMap(unitTarget, 60.0f))
                        {
                            if (!m_caster->IsImmuneToPlayer())
                                m_caster->SetImmuneToPlayer(true);
                            m_caster->CastSpell(unitTarget, chainSpellId, TRIGGERED_OLD_TRIGGERED);
                        }
                        // Not in range and fight in progress: remove aura and cast Shock onto players
                        else if (!m_caster->IsWithinDistInMap(unitTarget, 60.0f) && m_caster)
                        {
                            unitTarget->RemoveAurasDueToSpell(chainSpellId);
                            m_caster->SetImmuneToPlayer(false);

                            if (Unit* target = ((Creature*)m_caster)->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                                m_caster->CastSpell(target, 28099, TRIGGERED_NONE);
                        }
                        // else: in range and already have aura: do nothing
                    }
                    return;
                }
                case 28238:                                 // Zombie Chow Search
                {
                    m_caster->SetHealth(m_caster->GetHealth() + m_caster->GetMaxHealth() * 0.05f); // Gain 5% heal
                    return;
                }
                case 28307:                                 // Hateful Strike Primer
                {
                    // Target is filtered in Spell::FilterTargetMap
                    m_caster->CastSpell(unitTarget, 28308, TRIGGERED_NONE); // Hateful Strike
                    return;
                }
                case 28359:                                 // Trigger Teslas
                {
                    if (unitTarget)
                    {
                        DoScriptText(-1533150, unitTarget, unitTarget);
                        unitTarget->RemoveAllAuras();
                        unitTarget->CastSpell(unitTarget, 28159, TRIGGERED_NONE);   // Shock
                    }
                    return;
                }
                case 28414:                                 // Call of the Ashbringer
                {
                    if (!m_caster || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;
                    static constexpr uint32 AshbringerSounds[12] = { 8906,8907,8908,8920,8921,8922,8923,8924,8925,8926,8927,8928 };
                    m_caster->PlayDirectSound(AshbringerSounds[urand(0, 11)], PlayPacketParameters(PLAY_TARGET, (Player*)m_caster));
                    return;
                }
                case 28697:                                 // Forgiveness
                {
                    unitTarget->CastSpell(nullptr, 3617, TRIGGERED_OLD_TRIGGERED); // guessed suicide spell
                    return;
                }
                case 28730:                                 // Arcane Torrent (Mana)
                {
                    Aura* dummy = m_caster->GetDummyAura(28734);
                    if (dummy)
                    {
                        int32 bp = damage * dummy->GetStackAmount();
                        m_caster->CastCustomSpell(m_caster, 28733, &bp, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                        m_caster->RemoveAurasDueToSpell(28734);
                    }

                    return;
                }
                case 28961:                                 // Summon Corpse Scarabs (10)
                 {
                    if (unitTarget->IsAlive())
                        return;

                    unitTarget->CastSpell(unitTarget, 28864, TRIGGERED_OLD_TRIGGERED);  // Actual summoning spell
                    ((Creature*)unitTarget)->ForcedDespawn(2000);

                    return;
                }
                case 29200:                                 // Purify Helboar Meat
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spell_id = roll_chance_i(50)
                                      ? 29277               // Summon Purified Helboar Meat
                                      : 29278;              // Summon Toxic Helboar Meat

                    m_caster->CastSpell(m_caster, spell_id, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 29682:                                 // Call All Zombie Chow
                {
                    if (unitTarget->IsAlive())
                     {
                        float radius = GetSpellRadius(sSpellRadiusStore.LookupEntry(m_spellInfo->EffectRadiusIndex[eff_idx]));
                        unitTarget->GetMotionMaster()->MoveFollow(m_caster, radius, 0);
                    }
                    return;
                }
                case 29767:                                 // Overload
                {
                    m_caster->CastCustomSpell(m_caster, 29766, &damage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 29858:                                 // Soulshatter
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT && unitTarget->CanAttack(m_caster))
                        m_caster->CastSpell(unitTarget, 32835, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 30023:                                 // Periodic Trigger Dummy - triggered by many spells
                {
                    switch (m_triggeredByAuraSpell->Id)
                    {
                        case 29946: break; // Flame Wreath
                        case 29947: // Flame Wreath
                        {
                            // Cast explosion debuff
                            unitTarget->CastSpell(unitTarget, 29949, TRIGGERED_NONE);
                            return;
                        }
                        case 37589: // Shriveling gaze
                        {
                            unitTarget->RemoveAuraStack(m_triggeredByAuraSpell->Id);
                            return;
                        }
                        case 40250: // Improved Duration - Anzu spirits
                        {
                            auto periodicAuraList = unitTarget->GetAurasByType(SPELL_AURA_PERIODIC_HEAL);
                            uint32 duration = 0;
                            for (auto itr = periodicAuraList.rbegin(); itr != periodicAuraList.rend(); ++itr)
                            {
                                if ((*itr)->GetHolder()->GetSpellProto()->IsFitToFamily(SPELLFAMILY_DRUID, 0x0000001000000050)) // only Rejuvenation, Regrowth and Lifebloom
                                {
                                    Aura* lastPeriodic = *itr; // get last applied druid HOT
                                    duration = lastPeriodic->GetHolder()->GetAuraDuration();
                                    duration = duration * 2 > 60000 ? 60000 : duration * 2;
                                    lastPeriodic->GetHolder()->SetAuraDuration(duration); // double duration up to 60 seconds
                                    lastPeriodic->GetHolder()->SetAuraMaxDuration(duration);
                                    lastPeriodic->GetHolder()->UpdateAuraDuration();
                                }
                            }
                            unitTarget->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, unitTarget, unitTarget, duration);
                            return;
                        }
                        default:
                            break;
                    }
                    return;
                }
                case 30458:                                 // Nigh Invulnerability
                {
                    if (!m_CastItem)
                        return;

                    if (roll_chance_i(86))                  // Nigh-Invulnerability   - success
                        m_caster->CastSpell(m_caster, 30456, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    else                                    // Complete Vulnerability - backfire in 14% casts
                        m_caster->CastSpell(m_caster, 30457, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 30507:                                 // Poultryizer
                {
                    if (!m_CastItem)
                        return;

                    if (roll_chance_i(80))                  // Poultryized! - success
                        m_caster->CastSpell(unitTarget, 30501, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    else                                    // Poultryized! - backfire 20%
                        m_caster->CastSpell(unitTarget, 30504, TRIGGERED_OLD_TRIGGERED, m_CastItem);

                    return;
                }
                case 31617:                                 // Raise Dead
                case 31624:
                case 31625:
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    static_cast<Creature*>(unitTarget)->ForcedDespawn();

                    break;
                }
                case 32027:                                 // Expedition Flare
                {
                    // 32029 = Expedition Preserver | 32030 = Expedition Scout
                    m_caster->CastSpell(m_caster, (urand(0, 1) ? 32029 : 32030), TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 32146:                                 // Liquid Fire
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    ((Player*)m_caster)->KilledMonsterCredit(unitTarget->GetEntry(), unitTarget->GetObjectGuid());
                    ((Creature*)unitTarget)->ForcedDespawn();
                    return;
                }
                case 32300:                                 // Focus Fire
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, unitTarget->GetMap()->IsRegularDifficulty() ? 32302 : 38382, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 32312:                                 // Move 1 (Chess event AI short distance move)
                case 37388:                                 // Move 2 (Chess event AI long distance move)
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    // cast generic move spell
                    m_caster->CastSpell(unitTarget, 30012, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 32343:                                 // Revive Self
                {
                    if (!unitTarget)
                        return;

                    unitTarget->SetHealth(unitTarget->GetMaxHealth());
                    return;
                }
                case 32589:                                 // Crystal Shatter
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    unitTarget->CastSpell(nullptr, 32614, TRIGGERED_OLD_TRIGGERED);
                    ((Creature*)unitTarget)->ForcedDespawn(1000);
                    return;
                }
                case 33060:                                 // Make a Wish
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spell_id = 0;

                    switch (urand(1, 5))
                    {
                        case 1: spell_id = 33053; break;    // Mr Pinchy's Blessing
                        case 2: spell_id = 33057; break;    // Summon Mighty Mr. Pinchy
                        case 3: spell_id = 33059; break;    // Summon Furious Mr. Pinchy
                        case 4: spell_id = 33062; break;    // Tiny Magical Crawdad
                        case 5: spell_id = 33064; break;    // Mr. Pinchy's Gift
                    }

                    m_caster->CastSpell(m_caster, spell_id, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 33812:                                 // Gruul the Dragonkiller - Hateful Primer
                {
                    if (!unitTarget || m_UniqueTargetInfo.rbegin()->targetGUID != unitTarget->GetObjectGuid())
                        return;

                    Unit* target = unitTarget;
                    for (TargetList::const_iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ihit)
                    {
                        if (m_caster->GetMap()->GetPlayer(ihit->targetGUID) == m_caster->GetVictim())
                            continue;

                        if (m_caster->getThreatManager().getThreat(m_caster->GetMap()->GetPlayer(ihit->targetGUID)) > m_caster->getThreatManager().getThreat(target) || target == m_caster->GetVictim())
                            target = m_caster->GetMap()->GetPlayer(ihit->targetGUID);
                    }

                    m_caster->CastSpell(target, 33813, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 34063:                                 // Soul Mirror - Kill creature on spell and spawn mob
                {
                    unitTarget->CastSpell(nullptr, 34064, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(nullptr, 3617, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 34094:                                 // Power of Arrazius
                {
                    if (!unitTarget)
                        return;

                    uint32 triggered_spell_id = 0;
                    AIEventType triggered_event = AI_EVENT_CUSTOM_A;

                    // Feeble Weapons: Warrior, Rogue, Hunter
                    // Doubting Mind: Paladin, Shaman, Druid
                    // Chilling Words: Mage, Warlock, Priest
                    switch (unitTarget->getClass())
                    {
                        case CLASS_WARRIOR:
                        case CLASS_ROGUE:
                        case CLASS_HUNTER:
                            triggered_spell_id = 34088;
                            triggered_event = AI_EVENT_CUSTOM_EVENTAI_A;
                            break;
                        case CLASS_PALADIN:
                        case CLASS_SHAMAN:
                        case CLASS_DRUID:
                            triggered_spell_id = 34089;
                            triggered_event = AI_EVENT_CUSTOM_EVENTAI_B;
                            break;
                        case CLASS_MAGE:
                        case CLASS_WARLOCK:
                        case CLASS_PRIEST:
                            triggered_spell_id = 34087;
                            triggered_event = AI_EVENT_CUSTOM_EVENTAI_C;
                            break;
                        default:
                            return;
                    }

                    // This spell has lower range than the main spell,
                    // and the spell might fail because of that; this is working as
                    // intended
                    m_caster->CastSpell(unitTarget, triggered_spell_id, TRIGGERED_OLD_TRIGGERED);
                    if (m_caster->IsCreature())
                        m_caster->AI()->SendAIEvent(triggered_event, unitTarget, m_caster);

                    return;
                }
                case 34803:                                 // Summon Reinforcements
                {
                    m_caster->CastSpell(m_caster, 34810, TRIGGERED_OLD_TRIGGERED); // Summon 20083 behind of the caster
                    m_caster->CastSpell(m_caster, 34817, TRIGGERED_OLD_TRIGGERED); // Summon 20078 right of the caster
                    m_caster->CastSpell(m_caster, 34818, TRIGGERED_OLD_TRIGGERED); // Summon 20078 left of the caster
                    m_caster->CastSpell(m_caster, 34819, TRIGGERED_OLD_TRIGGERED); // Summon 20078 front of the caster
                    return;
                }
                case 35517:                                 // Teleport
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                        ((Creature*)unitTarget)->ForcedDespawn(1000);

                    return;
                }
                case 35598:                                 // Wrath of Socrethar (pretend to kill Ishanah)
                {
                    unitTarget->CastSpell(unitTarget, 29266, TRIGGERED_IGNORE_CURRENT_CASTED_SPELL); // Permanent Feign Death
                    return;
                }
                case 35600:                                 // Wrath of Socrethar (Kill Kaylaan)
                {
                    unitTarget->CastSpell(unitTarget, 29266, TRIGGERED_IGNORE_CURRENT_CASTED_SPELL); // Permanent Feign Death
                    return;
                }
                case 35683:                                 // Placing Protectorate Disruptor
                {
                    unitTarget->InterruptSpell(CURRENT_CHANNELED_SPELL, false);
                    return;
                }
                case 36196:                                 // Pure Nether Beam
                case 36197:
                case 36198:
                {
                    if (!unitTarget)
                        return;

                    unitTarget->PlaySpellVisual(7234);
                    unitTarget->PlaySpellVisual(7235);
                    return;
                }
                case 36677:                                 // Chaos Breath
                {
                    if (!unitTarget)
                        return;

                    uint32 possibleSpells[] = {36693, 36694, 36695, 36696, 36697, 36698, 36699, 36700} ;
                    std::vector<uint32> spellPool(possibleSpells, possibleSpells + countof(possibleSpells));
                    std::shuffle(spellPool.begin(), spellPool.end(), *GetRandomGenerator());

                    for (uint8 i = 0; i < (m_caster->GetMap()->IsRegularDifficulty() ? 2 : 4); ++i)
                        m_caster->CastSpell(m_caster, spellPool[i], TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 33923:                                 // Sonic Boom
                case 38796:                                 // Sonic Boom (heroic)
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, m_spellInfo->Id == 33923 ? 33666 : 38795, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 35745:                                 // Socrethar's Stone
                {
                    uint32 spell_id;
                    switch (m_caster->GetAreaId())
                    {
                        case 3900: spell_id = 35743; break; // Socrethar Portal
                        case 3742: spell_id = 35744; break; // Socrethar Portal
                        default: return;
                    }

                    m_caster->CastSpell(m_caster, spell_id, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 36327:                                 // Shoot Arcane Explosion Arrow
                {
                    m_caster->SummonCreature(21290, unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), unitTarget->GetOrientation(), TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 5000);
                    return;
                }
                case 37674:                                 // Chaos Blast
                {
                    if (!unitTarget)
                        return;

                    int32 basepoints0 = 100;
                    m_caster->CastCustomSpell(unitTarget, 37675, &basepoints0, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 37867:                                 // Arcano-Scorp Control
                case 37892:
                case 37894:
                {
                    if (!unitTarget)
                        return;

                    uint32 spellId;
                    switch (m_spellInfo->Id)
                    {
                        case 37867: spellId = 37868; break;
                        case 37892: spellId = 37893; break;
                        case 37894: spellId = 37895; break;
                        default:
                            return;
                    }

                    unitTarget->CastSpell(nullptr, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 38002:                                 // Fel Reaver Controller
                case 38120:
                case 38122:
                case 38125:
                case 38127:
                case 38129:
                {
                    if (!unitTarget)
                        return;

                    uint32 spellId = 0;
                    switch (m_spellInfo->Id)
                    {
                        case 38002: spellId = 38003; break;
                        case 38120: spellId = 38121; break;
                        case 38122: spellId = 38123; break;
                        case 38125: spellId = 38126; break;
                        case 38127: spellId = 38128; break;
                        case 38129: spellId = 38130; break;
                    }

                    unitTarget->CastSpell(nullptr, spellId, TRIGGERED_NONE);
                    return;
                }
                case 38020:                             // Fel Reaver Controller Tag
                {
                    unitTarget->CastSpell(unitTarget, 38022, TRIGGERED_NONE); // FRS Quest Credit
                    return;
                }
                case 38173:                             // Summon Spirit
                {
                    if (eff_idx == 0)
                    {
                        if (unitTarget->GetObjectGuid().GetEntry() == 22160)
                        {
                            bool checkTaskmaster = false;
                            bool checkSoothsayer = false;
                            for (auto& target : m_UniqueTargetInfo)
                            {
                                if (target.targetGUID.GetEntry() == 22160)
                                    checkTaskmaster = true;
                                else if (target.targetGUID.GetEntry() == 22384)
                                    checkSoothsayer = true;
                            }
                            if (checkSoothsayer && checkTaskmaster)
                                m_caster->CastSpell(nullptr, 39074, TRIGGERED_OLD_TRIGGERED);
                        }
                    }
                    return;
                }
                case 39096:                                 // Polarity Shift
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(39088);
                    unitTarget->RemoveAurasDueToSpell(39091);

                    // 39088 39091
                    switch (m_scriptValue)
                    {
                        case 0: // first target random
                            m_scriptValue = urand(0, 1) ? 39088 : 39091;
                            unitTarget->CastSpell(unitTarget, m_scriptValue, TRIGGERED_OLD_TRIGGERED);
                            break;
                        case 39088: // second target the other
                            m_scriptValue = 1;
                            unitTarget->CastSpell(unitTarget, 39091, TRIGGERED_OLD_TRIGGERED);
                            break;
                        case 39091:
                            m_scriptValue = 1;
                            unitTarget->CastSpell(unitTarget, 39088, TRIGGERED_OLD_TRIGGERED);
                            break;
                        default: // third and later random
                            unitTarget->CastSpell(unitTarget, urand(0, 1) ? 39088 : 39091, TRIGGERED_OLD_TRIGGERED);
                            break;
                    }
                    return;
                }
                case 39142:                                 // Drain World Tree Dummy
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 39141, TRIGGERED_NONE);
                    return;
                }
                case 39189:                                 // Sha'tari Torch
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Flames
                    if (unitTarget->HasAura(39199))
                        return;

                    unitTarget->CastSpell(unitTarget, 39199, TRIGGERED_OLD_TRIGGERED);
                    ((Player*)m_caster)->KilledMonsterCredit(unitTarget->GetEntry(), unitTarget->GetObjectGuid());
                    ((Creature*)unitTarget)->ForcedDespawn(10000);
                    return;
                }
                case 39238:                                 // Fumping
                {
                    // Summon Mature Bone Sifter as default
                    uint32 spellId;

                    // 50/50 chance to summon Mature Bone Sifter instead of Sand Gnome
                    switch (urand(0, 1))
                    {
                        case 0: spellId = 39241; break; // Summon Mature Bone Sifter
                        default:
                        case 1: spellId = 39240; break; // Summon Sand Gnome
                    }

                    m_caster->CastSpell(m_caster, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 39246:
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || eff_idx != EFFECT_INDEX_2)
                        return;

                    uint32 spellId;
                    switch (urand(0, 2))
                    {
                        case 0: spellId = 39248; break; // Summon Hai'Shulud
                        case 1: spellId = 39245; break; // Summon Mature Bone Sifter 2x
                        default:
                        case 2: spellId = 39247; break; // Summon Sand Gnome 2x
                    }
                    m_caster->CastSpell(unitTarget, spellId, TRIGGERED_OLD_TRIGGERED);

                    ((Creature*)unitTarget)->ForcedDespawn();
                    return;
                }
                case 39255:                                 // Black Dragon Form
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    ((Creature*)m_caster)->UpdateEntry(22496);
                    return;
                }
                case 39371:                                 // Prayer Beads
                {
                    if (!unitTarget)
                        return;

                    switch (unitTarget->GetEntry())
                    {
                        case 22431:
                            m_caster->CastSpell(unitTarget, 39322, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                            break;
                        case 22507:
                        case 22506:
                            m_caster->CastSpell(unitTarget, 39323, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                            break;
                    }
                    return;
                }
                case 39487:                                 // Crypt Scarab Hate
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    if (Unit* spawner = unitTarget->GetSpawner())
                    {
                        if (Unit* spawnerTarget = spawner->GetVictim()) // Force attacking the same target as its spawner
                        {
                            if (unitTarget->CanAttackOnSight(spawnerTarget)) // Need to make sure target is attackable currently
                            {
                                unitTarget->AI()->AttackStart(spawnerTarget);
                                unitTarget->AddThreat(spawnerTarget, 50000000);
                            }
                        }
                    }
                    return;
                }
                case 39635:                                 // Throw Glaive (first)
                case 39849:                                 // Throw Glaive (second)
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 41466, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 39992:                                 // Needle Spine Targeting - Najentus
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 39835, TRIGGERED_NONE);
                    return;
                }
                case 39995:                                 // Four Dragons: Dummy to Dragon
                {
                    if (!unitTarget || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->PlayDirectSound(3520);
                    unitTarget->CastSpell(m_caster, 40032, TRIGGERED_NONE);
                    return;
                }
                case 40032:                                 // Fiery Breath (Patch 2.4.2 (2008-05-13): Dragons in Blade's Edge Mountains will no longer instantly knock you off your flying mount.)
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 39998, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40160:                                 // Throw Bomb
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    static_cast<Player*>(m_caster)->RewardPlayerAndGroupAtEventCredit(unitTarget->GetEntry(), unitTarget);

                    Creature* creature = GetClosestCreatureWithEntry(unitTarget, 23119, 5.f);
                    GameObject* go = GetClosestGameObjectWithEntry(unitTarget, 185861, 5.f);
                    if (creature)
                    {
                        creature->CastSpell(nullptr, 40162, TRIGGERED_OLD_TRIGGERED);
                        creature->ForcedDespawn(4000);
                    }
                    if (go)
                    {
                        go->SetRespawnTime(1);
                        go->SetLootState(GO_JUST_DEACTIVATED);
                    }
                    static_cast<Creature*>(unitTarget)->ForcedDespawn();
                    return;
                }
                case 40200:                                 // Bombing Run: Remove See Invisibility
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(40195);
                    return;
                }
                case 40758:                                 // Ethereal Ring: The Bolt
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 40799, TRIGGERED_NONE);
                    return;
                }
                case 40802:                                 // Mingo's Fortune Generator (Mingo's Fortune Giblets)
                {
                    // selecting one from Bloodstained Fortune item
                    uint32 newitemid;
                    switch (urand(1, 20))
                    {
                        case 1:  newitemid = 32688; break;
                        case 2:  newitemid = 32689; break;
                        case 3:  newitemid = 32690; break;
                        case 4:  newitemid = 32691; break;
                        case 5:  newitemid = 32692; break;
                        case 6:  newitemid = 32693; break;
                        case 7:  newitemid = 32700; break;
                        case 8:  newitemid = 32701; break;
                        case 9:  newitemid = 32702; break;
                        case 10: newitemid = 32703; break;
                        case 11: newitemid = 32704; break;
                        case 12: newitemid = 32705; break;
                        case 13: newitemid = 32706; break;
                        case 14: newitemid = 32707; break;
                        case 15: newitemid = 32708; break;
                        case 16: newitemid = 32709; break;
                        case 17: newitemid = 32710; break;
                        case 18: newitemid = 32711; break;
                        case 19: newitemid = 32712; break;
                        case 20: newitemid = 32713; break;
                        default:
                            return;
                    }

                    DoCreateItem(eff_idx, newitemid);
                    return;
                }
                case 40834:                                 // Agonizing Flames
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(unitTarget, 40932, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40869:                                 // Fatal Attraction - Mother Shahraz
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(unitTarget, 41001, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40870:                                 // Fatal Attraction - tick - Mother Shahraz
                {
                    if (!unitTarget || m_scriptValue != 0) // only execute once
                        return;
                    m_scriptValue = 1;
                    Aura* aura = m_caster->GetAura(41001, EFFECT_INDEX_1);
                    if (!aura)
                        return;
                    int32 dmgValue = std::min(aura->GetAuraTicks(), 4u) * 750;
                    m_caster->CastCustomSpell(nullptr, 40871, &dmgValue, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40962:                                 // Blade's Edge Terrace Demon Boss Summon Branch
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spell_id = 0;
                    switch (urand(1, 4))
                    {
                        case 1: spell_id = 40957; break;    // Blade's Edge Terrace Demon Boss Summon 1
                        case 2: spell_id = 40959; break;    // Blade's Edge Terrace Demon Boss Summon 2
                        case 3: spell_id = 40960; break;    // Blade's Edge Terrace Demon Boss Summon 3
                        case 4: spell_id = 40961; break;    // Blade's Edge Terrace Demon Boss Summon 4
                    }
                    unitTarget->CastSpell(unitTarget, spell_id, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 41283:                                 // Abyssal Toss
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 41284, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 41333:                                 // Empyreal Equivalency
                {
                    if (!unitTarget)
                        return;

                    // Equilize the health of all targets based on the corresponding health percent
                    unitTarget->SetHealth(m_caster->GetHealth() / 4);
                    return;
                }
                case 41499:                                 // Empyreal Balance
                {
                    unitTarget->SetMaxHealth(m_caster->GetMaxHealth() / 4);
                    return;
                }
                case 42287:                                 // Salvage Wreckage
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (roll_chance_i(66))
                        m_caster->CastSpell(m_caster, 42289, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                    else
                        m_caster->CastSpell(m_caster, 42288, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 42489:                                 // Cast Ooze Zap When Energized
                {
                    if (!unitTarget || !m_caster->HasAura(42490))
                        return;

                    m_caster->CastSpell(unitTarget, 42483, TRIGGERED_NONE);

                    return;
                }
                case 42628:                                 // Fire Bomb (throw)
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 42629, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 42631:                                 // Fire Bomb (explode)
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    unitTarget->RemoveAurasDueToSpell(42629);
                    unitTarget->CastSpell(unitTarget, 42630, TRIGGERED_OLD_TRIGGERED);

                    // despawn the bomb after exploding
                    ((Creature*)unitTarget)->ForcedDespawn(3000);
                    return;
                }
                case 43096:                                 // Summon All Players
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(unitTarget, 43097, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 43144:                                 // Hatch All Eggs
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 42493, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 43152:                                 // Lynx Rush - Zul'Jin
                {
                    if (!unitTarget || m_scriptValue)
                        return;

                    m_scriptValue = 1;
                    GuidVector targets;
                    for (TargetList::const_iterator ihit = m_UniqueTargetInfo.begin(); ihit != m_UniqueTargetInfo.end(); ++ ihit)
                        if (ihit->effectMask & (1 << eff_idx) && ihit->missCondition == SPELL_MISS_NONE)
                            targets.push_back(ihit->targetGUID);

                    ObjectGuid guid = targets[urand(0, targets.size() - 1)];
                    if (Unit* target = m_caster->GetMap()->GetUnit(guid))
                        m_caster->CastSpell(target, 43153, TRIGGERED_NONE);
                    return;
                }
                case 43498:                                 // Siphon Soul
                {
                    // This spell should cast the next spell only for one (player)target, however it should hit multiple targets, hence this kind of implementation
                    if (!unitTarget || m_UniqueTargetInfo.rbegin()->targetGUID != unitTarget->GetObjectGuid())
                        return;

                    std::vector<Unit*> possibleTargets;
                    possibleTargets.reserve(m_UniqueTargetInfo.size());
                    for (TargetList::const_iterator itr = m_UniqueTargetInfo.begin(); itr != m_UniqueTargetInfo.end(); ++itr)
                    {
                        // Skip Non-Players
                        if (!itr->targetGUID.IsPlayer())
                            continue;

                        if (Unit* target = m_caster->GetMap()->GetPlayer(itr->targetGUID))
                            possibleTargets.push_back(target);
                    }

                    // Cast Siphon Soul channeling spell
                    if (!possibleTargets.empty())
                        m_caster->CastSpell(possibleTargets[urand(0, possibleTargets.size() - 1)], 43501, TRIGGERED_NONE);

                    return;
                }
                case 43647:                                 // Cosmetic - Spear Throw
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    unitTarget->SetFlag(UNIT_FIELD_FLAGS, 33587456);
                    unitTarget->SetDisplayId(22347);
                    unitTarget->CastSpell(unitTarget, 23973, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->SetStandState(UNIT_STAND_STATE_DEAD);
                    return;
                }
                // Demon Broiled Surprise
                case 43723:
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    ((Player*)m_caster)->CastSpell(unitTarget, 43753, TRIGGERED_OLD_TRIGGERED, m_CastItem, nullptr, m_originalCasterGUID, m_spellInfo);
                    return;
                }
                case 44869:                                 // Spectral Blast
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // If target has spectral exhaustion or spectral realm aura return
                    if (unitTarget->HasAura(44867) || unitTarget->HasAura(46021))
                        return;

                    // Cast the spectral realm effect spell, visual spell and spectral blast rift summoning
                    unitTarget->CastSpell(unitTarget, 44866, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    unitTarget->CastSpell(unitTarget, 46648, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    unitTarget->CastSpell(unitTarget, 44811, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 44875:                                 // Complete Raptor Capture
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    Creature* creatureTarget = (Creature*)unitTarget;

                    creatureTarget->ForcedDespawn();

                    // cast spell Raptor Capture Credit
                    m_caster->CastSpell(m_caster, 42337, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 44997:                                 // Converting Sentry
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    Creature* creatureTarget = (Creature*)unitTarget;

                    creatureTarget->ForcedDespawn();

                    // Converted Sentry Credit
                    m_caster->CastSpell(m_caster, 45009, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45030:                                 // Impale Emissary
                {
                    // Emissary of Hate Credit
                    m_caster->CastSpell(m_caster, 45088, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45235:                                 // Blaze
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 45236, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 45260:                                 // Karazhan - Chess - Force Player to Kill Bunny
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(unitTarget, 45259, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45714:                                 // Fog of Corruption (caster inform)
                {
                    if (!unitTarget || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45717:                                 // Fog of Corruption (player buff)
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(unitTarget, 45726, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45785:                                 // Sinister Reflection Clone
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45833:                                 // Power of the Blue Flight
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 45836, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45892:                                 // Sinister Reflection
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Summon 4 clones of the same player
                    for (uint8 i = 0; i < 4; ++i)
                        unitTarget->CastSpell(unitTarget, 45891, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 45976:                                 // Open Portal
                case 46177:                                 // Open All Portals
                {
                    if (!unitTarget)
                        return;

                    // portal visual
                    unitTarget->CastSpell(unitTarget, 45977, TRIGGERED_OLD_TRIGGERED);

                    // break in case additional procressing in scripting library required
                    break;
                }
                case 45989:                                 // Summon Void Sentinel Summoner Visual
                {
                    if (!unitTarget)
                        return;

                    // summon void sentinel
                    unitTarget->CastSpell(unitTarget, 45988, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 46292:                                 // Cataclysm Breath
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spellId = 0;

                    switch (urand(0, 7))
                    {
                        case 0: spellId = 46293; break;     // Corrosive Poison
                        case 1: spellId = 46294; break;     // Fevered Fatigue
                        case 2: spellId = 46295; break;     // Hex
                        case 3: spellId = 46296; break;     // Necrotic Poison
                        case 4: spellId = 46297; break;     // Piercing Shadow
                        case 5: spellId = 46298; break;     // Shrink
                        case 6: spellId = 46299; break;     // Wavering Will
                        case 7: spellId = 46300; break;     // Withered Touch
                    }

                    m_caster->CastSpell(unitTarget, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 46372:                                 // Ice Spear Target Picker
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(unitTarget, 46359, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 46289:                                 // Negative Energy
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 46285, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 46430:                                 // Synch Health
                {
                    if (!unitTarget)
                        return;

                    unitTarget->SetHealth(m_caster->GetHealth());
                    return;
                }
                case 49357:                                 // Brewfest Mount Transformation
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (!m_caster->HasAuraType(SPELL_AURA_MOUNTED))
                        return;

                    m_caster->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

                    // Ram for Alliance, Kodo for Horde
                    if (((Player*)m_caster)->GetTeam() == ALLIANCE)
                    {
                        if (m_caster->GetSpeedRate(MOVE_RUN) >= 2.0f)
                            // 100% Ram
                            m_caster->CastSpell(m_caster, 43900, TRIGGERED_OLD_TRIGGERED);
                        else
                            // 60% Ram
                            m_caster->CastSpell(m_caster, 43899, TRIGGERED_OLD_TRIGGERED);
                    }
                    else
                    {
                        if (((Player*)m_caster)->GetSpeedRate(MOVE_RUN) >= 2.0f)
                            // 100% Kodo
                            m_caster->CastSpell(m_caster, 49379, TRIGGERED_OLD_TRIGGERED);
                        else
                            // 60% Kodo
                            m_caster->CastSpell(m_caster, 49378, TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
                case 50243:                                 // Teach Language
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // spell has a 1/3 chance to trigger one of the below
                    if (roll_chance_i(66))
                        return;

                    if (((Player*)m_caster)->GetTeam() == ALLIANCE)
                    {
                        // 1000001 - gnomish binary
                        m_caster->CastSpell(m_caster, 50242, TRIGGERED_OLD_TRIGGERED);
                    }
                    else
                    {
                        // 01001000 - goblin binary
                        m_caster->CastSpell(m_caster, 50246, TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 51582:                                 // Rocket Boots Engaged (Rocket Boots Xtreme and Rocket Boots Xtreme Lite)
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (BattleGround* bg = ((Player*)m_caster)->GetBattleGround())
                        bg->HandlePlayerDroppedFlag((Player*)m_caster);

                    m_caster->CastSpell(m_caster, 30452, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 52845:                                 // Brewfest Mount Transformation (Faction Swap)
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (!m_caster->HasAuraType(SPELL_AURA_MOUNTED))
                        return;

                    m_caster->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

                    // Ram for Horde, Kodo for Alliance
                    if (((Player*)m_caster)->GetTeam() == HORDE)
                    {
                        if (m_caster->GetSpeedRate(MOVE_RUN) >= 2.0f)
                            // Swift Brewfest Ram, 100% Ram
                            m_caster->CastSpell(m_caster, 43900, TRIGGERED_OLD_TRIGGERED);
                        else
                            // Brewfest Ram, 60% Ram
                            m_caster->CastSpell(m_caster, 43899, TRIGGERED_OLD_TRIGGERED);
                    }
                    else
                    {
                        if (((Player*)m_caster)->GetSpeedRate(MOVE_RUN) >= 2.0f)
                            // Great Brewfest Kodo, 100% Kodo
                            m_caster->CastSpell(m_caster, 49379, TRIGGERED_OLD_TRIGGERED);
                        else
                            // Brewfest Riding Kodo, 60% Kodo
                            m_caster->CastSpell(m_caster, 49378, TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
            }

            // All IconID Check in there
            switch (m_spellInfo->SpellIconID)
            {
                // Berserking (troll racial traits)
                case 1661:
                {
                    uint32 healthPerc = uint32((float(m_caster->GetHealth()) / m_caster->GetMaxHealth()) * 100);
                    int32 haste_mod = 10;
                    if (healthPerc <= 40)
                        haste_mod = 30;
                    if (healthPerc < 100 && healthPerc > 40)
                        haste_mod = 10 + (100 - healthPerc) / 3;

                    // haste_mod is the same for all effects
                    int32 hasteModBasePoints0 = haste_mod;  // Haste Melee
                    int32 hasteModBasePoints1 = haste_mod;  // Haste Range
                    int32 hasteModBasePoints2 = haste_mod;  // Haste Cast

                    // FIXME: custom spell required this aura state by some unknown reason, we not need remove it anyway
                    m_caster->ModifyAuraState(AURA_STATE_BERSERKING, true);
                    m_caster->CastCustomSpell(m_caster, 26635, &hasteModBasePoints0, &hasteModBasePoints1, &hasteModBasePoints2, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_MAGE:
        {
            switch (m_spellInfo->Id)
            {
                case 11958:                                 // Cold Snap
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // immediately finishes the cooldown on Frost spells
                    auto cdCheck = [](SpellEntry const & spellEntry) -> bool
                    {
                        if (spellEntry.Id == 11958 || spellEntry.SpellFamilyName != SPELLFAMILY_MAGE)
                            return false;
                        if ((GetSpellSchoolMask(&spellEntry) & SPELL_SCHOOL_MASK_FROST) && GetSpellRecoveryTime(&spellEntry) > 0)
                            return true;
                        return false;
                    };
                    static_cast<Player*>(m_caster)->RemoveSomeCooldown(cdCheck);
                    return;
                }
                case 30610:                                 // Wrath of the Titans Stacker
                {
                    uint32 count = m_caster->GetAuraCount(30554);
                    for (uint32 i = count; i < 5; ++i)
                        m_caster->CastSpell(nullptr, 30554, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 38194:                                 // Blink
                {
                    // Blink
                    if (unitTarget)
                        m_caster->CastSpell(unitTarget, 38203, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 38642:                                 // Blink
                {
                    // Blink
                    if (unitTarget)
                        unitTarget->CastSpell(m_caster, 38643, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 41060:                                 // Return
                {
                    if (!unitTarget || m_caster->GetTypeId() != TYPEID_UNIT)
                        return;

                    ((Creature*)m_caster)->ForcedDespawn(2500);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_WARRIOR:
        {
            // Charge
            if ((m_spellInfo->SpellFamilyFlags & uint64(0x1)) && m_spellInfo->SpellVisual == 867)
            {
                int32 chargeBasePoints0 = damage;
                m_caster->CastCustomSpell(m_caster, 34846, &chargeBasePoints0, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                return;
            }

            switch (m_spellInfo->Id)
            {
                // Warrior's Wrath
                case 21977:
                {
                    if (!unitTarget)
                        return;
                    m_caster->CastSpell(unitTarget, 21887, TRIGGERED_OLD_TRIGGERED); // spell mod
                    return;
                }
                case 30012:                                 // Move
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, 30253, TRIGGERED_OLD_TRIGGERED);
                }
                case 30284:                                 // Change Facing
                {
                    if (!unitTarget || eff_idx != EFFECT_INDEX_0)
                        return;

                    unitTarget->CastSpell(m_caster, 30270, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 37144:                                 // Move (Chess event player knight move)
                case 37146:                                 // Move (Chess event player pawn move)
                case 37148:                                 // Move (Chess event player queen move)
                case 37151:                                 // Move (Chess event player rook move)
                case 37152:                                 // Move (Chess event player bishop move)
                case 37153:                                 // Move (Chess event player king move)
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    // cast generic move spell
                    m_caster->CastSpell(unitTarget, 30012, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            switch (m_spellInfo->Id)
            {
                case 39977:                                 // Remove Impaling Spine
                {
                    if (!unitTarget)
                        return;

                    if (unitTarget->HasAura(39837))
                        unitTarget->RemoveAurasDueToSpell(39837);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_PRIEST:
        {
            switch (m_spellInfo->Id)
            {
                case 28598:                                 // Touch of Weakness triggered spell
                {
                    if (!unitTarget || !m_triggeredByAuraSpell)
                        return;

                    uint32 spellid = 0;

                    switch (m_triggeredByAuraSpell->Id)
                    {
                        case 2652:  spellid =  2943; break; // Rank 1
                        case 19261: spellid = 19249; break; // Rank 2
                        case 19262: spellid = 19251; break; // Rank 3
                        case 19264: spellid = 19252; break; // Rank 4
                        case 19265: spellid = 19253; break; // Rank 5
                        case 19266: spellid = 19254; break; // Rank 6
                        case 25461: spellid = 25460; break; // Rank 7
                        default:
                            sLog.outError("Spell::EffectDummy: Spell 28598 triggered by unhandeled spell %u", m_triggeredByAuraSpell->Id);
                            return;
                    }
                    m_caster->CastSpell(unitTarget, spellid, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 36448:                                 // Focused Bursts
                case 36475:
                case 38986:
                case 38987:
                {
                    if (!unitTarget || eff_idx != EFFECT_INDEX_0)
                        return;

                    uint32 spellid = m_spellInfo->EffectBasePoints[urand(0, MAX_EFFECT_INDEX - 1)] + 1;
                    m_caster->CastSpell(unitTarget, spellid, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
            }

            break;
        }
        case SPELLFAMILY_DRUID:
        {
            switch (m_spellInfo->Id)
            {
                case 5229:                                  // Enrage
                {
                    int32 reductionMod = -27;
                    if (m_caster->HasAura(9634)) // If in Dire Bear form only 16%
                        reductionMod = -16;
                    m_caster->CastCustomSpell(nullptr, 25503, &reductionMod, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 5420:                                  // Tree of Life passive
                {
                    // Tree of Life area effect
                    int32 health_mod = int32(m_caster->GetStat(STAT_SPIRIT) / 4);
                    if (Aura* aura = m_caster->GetAura(39926, EFFECT_INDEX_0)) // Improved party auras
                        health_mod += aura->GetAmount();
                    m_caster->CastCustomSpell(m_caster, 34123, &health_mod, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 29201:                                 // Loatheb Corrupted Mind triggered sub spells
                {
                    uint32 spellid = 0;
                    switch (unitTarget->getClass())
                    {
                        case CLASS_PALADIN: spellid = 29196; break;
                        case CLASS_PRIEST: spellid = 29185; break;
                        case CLASS_SHAMAN: spellid = 29198; break;
                        case CLASS_DRUID: spellid = 29194; break;
                        default: break;
                    }
                    if (spellid != 0)
                        m_caster->CastSpell(unitTarget, spellid, TRIGGERED_OLD_TRIGGERED, nullptr);
                }
                case 29284:                                 // Brittle Armor - dummy exists so that max stacks are added
                {
                    m_caster->CastSpell(unitTarget, 24575, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 29286:                                 // Mercurial Shield - dummy exists so that max stacks are added
                {
                    m_caster->CastSpell(unitTarget, 26464, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
            }

            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            switch (m_spellInfo->Id)
            {
                case 5938:                                  // Shiv
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Player* pCaster = static_cast<Player*>(m_caster);

                    Item* item = pCaster->GetWeaponForAttack(OFF_ATTACK);
                    if (!item)
                        return;

                    // all poison enchantments is temporary
                    if (uint32 enchant_id = item->GetEnchantmentId(TEMP_ENCHANTMENT_SLOT))
                    {
                        SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
                        if (!pEnchant)
                            return;

                        for (int s = 0; s < 3; ++s)
                        {
                            if (pEnchant->type[s] != ITEM_ENCHANTMENT_TYPE_COMBAT_SPELL)
                                continue;

                            SpellEntry const* combatEntry = sSpellTemplate.LookupEntry<SpellEntry>(pEnchant->spellid[s]);
                            if (!combatEntry || combatEntry->Dispel != DISPEL_POISON)
                                continue;

                            m_caster->CastSpell(unitTarget, combatEntry, TRIGGERED_OLD_TRIGGERED, item);
                        }
                    }

                    m_caster->CastSpell(unitTarget, 5940, TRIGGERED_OLD_TRIGGERED);
                    return;
                }

                case 31231:                                 // Cheat Death
                {
                    // Cheating Death
                    m_caster->CastSpell(m_caster, 45182, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_HUNTER:
        {
            // Kill command
            if (m_spellInfo->SpellFamilyFlags & uint64(0x00080000000000))
            {
                if (m_caster->getClass() != CLASS_HUNTER)
                    return;

                // clear hunter crit aura state
                m_caster->ModifyAuraState(AURA_STATE_HUNTER_CRIT_STRIKE, false);

                // additional damage from pet to pet target
                Pet* pet = m_caster->GetPet();
                if (!pet || !pet->GetVictim())
                    return;

                uint32 spell_id = 0;
                switch (m_spellInfo->Id)
                {
                    case 34026: spell_id = 34027; break;    // rank 1
                    default:
                        sLog.outError("Spell::EffectDummy: Spell %u not handled in KC", m_spellInfo->Id);
                        return;
                }

                pet->CastSpell(pet->GetVictim(), spell_id, TRIGGERED_OLD_TRIGGERED);
                return;
            }

            switch (m_spellInfo->Id)
            {
                case 23989:                                 // Readiness talent
                {
                    if (m_caster->GetTypeId() == TYPEID_PLAYER)
                    {
                        // immediately finishes the cooldown for hunter abilities
                        auto cdCheck = [](SpellEntry const & spellEntry) -> bool { return (spellEntry.SpellFamilyName == SPELLFAMILY_HUNTER && spellEntry.Id != 23989 && GetSpellRecoveryTime(&spellEntry) > 0); };
                        static_cast<Player*>(m_caster)->RemoveSomeCooldown(cdCheck);
                    }
                    return;
                }
            }

            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            switch (m_spellInfo->SpellIconID)
            {
                case 156:                                   // Holy Shock
                {
                    if (!unitTarget)
                        return;

                    int hurt;
                    int heal;
                    switch (m_spellInfo->Id)
                    {
                        case 20473: hurt = 25912; heal = 25914; break;
                        case 20929: hurt = 25911; heal = 25913; break;
                        case 20930: hurt = 25902; heal = 25903; break;
                        case 27174: hurt = 27176; heal = 27175; break;
                        case 33072: hurt = 33073; heal = 33074; break;
                        default:
                            sLog.outError("Spell::EffectDummy: Spell %u not handled in HS", m_spellInfo->Id);
                            return;
                    }

                    if (m_caster->CanAssistSpell(unitTarget, m_spellInfo))
                        m_caster->CastSpell(unitTarget, heal, TRIGGERED_OLD_TRIGGERED);
                    else
                        m_caster->CastSpell(unitTarget, hurt, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 561:                                   // Judgement of command
                {
                    if (unitTarget)
                        if (SpellEntry const* spell_proto = sSpellTemplate.LookupEntry<SpellEntry>(m_currentBasePoints[eff_idx]))
                            m_caster->CastSpell(unitTarget, spell_proto, TRIGGERED_OLD_TRIGGERED, nullptr);

                    return;
                }
            }
            switch (m_spellInfo->Id)
            {
                case 37877:                                 // Blessing of Faith
                {
                    if (!unitTarget)
                        return;

                    uint32 spell_id;
                    switch (unitTarget->getClass())
                    {
                        case CLASS_DRUID:   spell_id = 37878; break;
                        case CLASS_PALADIN: spell_id = 37879; break;
                        case CLASS_PRIEST:  spell_id = 37880; break;
                        case CLASS_SHAMAN:  spell_id = 37881; break;
                        default: return;                    // ignore for not healing classes
                    }

                    m_caster->CastSpell(m_caster, spell_id, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 51640:                                 // Taunt Flag Targeting
                {
                    if (!unitTarget || !unitTarget->IsPlayer())
                        return;

                    float x, y, z;
                    if (Corpse* corpse = static_cast<Player*>(unitTarget)->GetCorpse())
                        corpse->GetPosition(x, y, z);
                    else
                        unitTarget->GetPosition(x, y, z);

                    DoScriptText(-1015072, m_caster, unitTarget);
                    m_caster->CastSpell(x, y, z, 52605, TRIGGERED_OLD_TRIGGERED); // should also send start
                    return;
                }
            }

            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            // Rockbiter Weapon
            if (m_spellInfo->SpellFamilyFlags & uint64(0x400000))
            {
                uint32 spell_id = 0;
                switch (m_spellInfo->Id)
                {
                    case  8017: spell_id = 36494; break;    // Rank 1
                    case  8018: spell_id = 36750; break;    // Rank 2
                    case  8019: spell_id = 36755; break;    // Rank 3
                    case 10399: spell_id = 36759; break;    // Rank 4
                    case 16314: spell_id = 36763; break;    // Rank 5
                    case 16315: spell_id = 36766; break;    // Rank 6
                    case 16316: spell_id = 36771; break;    // Rank 7
                    case 25479: spell_id = 36775; break;    // Rank 8
                    case 25485: spell_id = 36499; break;    // Rank 9
                    default:
                        sLog.outError("Spell::EffectDummy: Spell %u not handled in RW", m_spellInfo->Id);
                        return;
                }

                SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spell_id);

                if (!spellInfo)
                {
                    sLog.outError("WORLD: unknown spell id %i", spell_id);
                    return;
                }

                if (m_caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                for (int j = BASE_ATTACK; j <= OFF_ATTACK; ++j)
                {
                    if (Item* item = ((Player*)m_caster)->GetWeaponForAttack(WeaponAttackType(j)))
                    {
                        if (item->IsFitToSpellRequirements(m_spellInfo))
                        {
                            Spell* spell = new Spell(m_caster, spellInfo, TRIGGERED_OLD_TRIGGERED);

                            // enchanting spell selected by calculated damage-per-sec in enchanting effect
                            // at calculation applied affect from Elemental Weapons talent
                            // real enchantment damage
                            spell->m_currentBasePoints[1] = damage;

                            SpellCastTargets targets;
                            targets.setItemTarget(item);
                            spell->SpellStart(&targets);
                        }
                    }
                }
                return;
            }
            if (m_spellInfo->SpellFamilyFlags & uint64(0x0000000000200000)) // Flametongue Weapon Proc, Ranks
            {
                if (m_CastItem)
                {
                    // found spelldamage coefficients of 0.381% per 0.1 speed and 15.244 per 4.0 speed
                    // but own calculation say 0.385 gives at most one point difference to published values
                    int32 bonusDamage = m_caster->SpellBaseDamageBonusDone(GetSpellSchoolMask(m_spellInfo))
                                        + unitTarget->SpellBaseDamageBonusTaken(GetSpellSchoolMask(m_spellInfo));
                    // Does Amplify Magic/Dampen Magic influence flametongue? If not, the above addition must be removed.
                    float weaponSpeed = float(m_CastItem->GetProto()->Delay) / IN_MILLISECONDS;
                    bonusDamage = m_caster->SpellBonusWithCoeffs(m_spellInfo, 0, bonusDamage, 0, SPELL_DIRECT_DAMAGE, false); // apply spell coeff
                    int32 totalDamage = (damage * 0.01 * weaponSpeed) + bonusDamage;

                    m_caster->CastCustomSpell(unitTarget, 10444, &totalDamage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                }
                else
                    sLog.outError("Spell::EffectDummy: spell %i requires cast Item", m_spellInfo->Id);

                return;
            }
            if (m_spellInfo->SpellFamilyFlags & uint64(0x0000000400000000)) // Flametongue Totem Proc, Ranks
            {
                if (m_CastItem) // Does not scale with gear
                {
                    float weaponSpeed = float(m_CastItem->GetProto()->Delay) / IN_MILLISECONDS;
                    int32 totalDamage = (damage * 0.01f * weaponSpeed * (m_CastItem->GetEnchantmentModifier() + 100.f) / 100.f);
                    m_caster->CastCustomSpell(unitTarget, 16368, &totalDamage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                }
                else
                    sLog.outError("Spell::EffectDummy: spell %i requires cast Item", m_spellInfo->Id);

                return;
            }
            if (m_spellInfo->Id == 39610)                   // Mana Tide Totem effect
            {
                if (!unitTarget || unitTarget->GetPowerType() != POWER_MANA)
                    return;

                // Regenerate 6% of Total Mana Every 3 secs
                int32 EffectBasePoints0 = unitTarget->GetMaxPower(POWER_MANA)  * damage / 100;
                m_caster->CastCustomSpell(unitTarget, 39609, &EffectBasePoints0, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_originalCasterGUID);
                return;
            }

            break;
        }
    }

    // pet auras
    if (PetAura const* petSpell = sSpellMgr.GetPetAura(m_spellInfo->Id))
    {
        m_caster->AddPetAura(petSpell);
        return;
    }

    // Script based implementation. Must be used only for not good for implementation in core spell effects
    // So called only for not processed cases
    bool libraryResult = false;
    if (gameObjTarget)
        libraryResult = sScriptDevAIMgr.OnEffectDummy(m_caster, m_spellInfo->Id, eff_idx, gameObjTarget, m_originalCasterGUID);
    else if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
        libraryResult = sScriptDevAIMgr.OnEffectDummy(m_caster, m_spellInfo->Id, eff_idx, (Creature*)unitTarget, m_originalCasterGUID);
    else if (itemTarget)
        libraryResult = sScriptDevAIMgr.OnEffectDummy(m_caster, m_spellInfo->Id, eff_idx, itemTarget, m_originalCasterGUID);

    if (unitTarget && !libraryResult)
    {
        // Previous effect might have started script
        if (ScriptMgr::CanSpellEffectStartDBScript(m_spellInfo, eff_idx))
        {
            DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell ScriptStart spellid %u in EffectDummy", m_spellInfo->Id);
            m_caster->GetMap()->ScriptsStart(sSpellScripts, m_spellInfo->Id, m_caster, unitTarget);
        }
    }
}

void Spell::EffectTriggerSpellWithValue(SpellEffectIndex eff_idx)
{
    uint32 triggered_spell_id = m_spellInfo->EffectTriggerSpell[eff_idx];

    // normal case
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(triggered_spell_id);

    if (!spellInfo)
    {
        // No previous Effect might have started a script
        bool startDBScript = unitTarget && ScriptMgr::CanSpellEffectStartDBScript(m_spellInfo, eff_idx);
        if (startDBScript)
        {
            DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell ScriptStart spellid %u in EffectTriggerSpell", m_spellInfo->Id);
            startDBScript = m_caster->GetMap()->ScriptsStart(sSpellScripts, m_spellInfo->Id, m_caster, unitTarget);
        }

        if (!startDBScript)
            sLog.outError("EffectTriggerSpell of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    int32 bp = damage;
    m_caster->CastCustomSpell(unitTarget, triggered_spell_id, &bp, &bp, &bp, TRIGGERED_OLD_TRIGGERED, m_CastItem, nullptr, m_originalCasterGUID, m_spellInfo);
}

void Spell::EffectTriggerRitualOfSummoning(SpellEffectIndex eff_idx)
{
    uint32 triggered_spell_id = m_spellInfo->EffectTriggerSpell[eff_idx];
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(triggered_spell_id);

    if (!spellInfo)
    {
        sLog.outError("EffectTriggerRitualOfSummoning of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    finish();

    m_caster->CastSpell(unitTarget, spellInfo, TRIGGERED_NONE);
}

void Spell::EffectForceCast(SpellEffectIndex effIndex)
{
    if (!unitTarget)
        return;

    uint32 triggered_spell_id = m_spellInfo->EffectTriggerSpell[effIndex];

    // normal case
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(triggered_spell_id);

    if (!spellInfo)
    {
        sLog.outError("EffectForceCast of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    int32 basePoints = damage;

    SpellCastTargets targets;

    switch (m_spellInfo->EffectImplicitTargetA[effIndex])
    {
        case TARGET_LOCATION_UNIT_MINION_POSITION: break; // confirmed by 31348 nothing is forwarded
        default:
            if (IsSpellRequireTarget(spellInfo))
                targets.setUnitTarget(unitTarget);
            break;
    }

    if (spellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
    {
        if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        {
            float x, y, z;
            m_targets.getDestination(x, y, z);
            targets.setDestination(x, y, z);
        }
        else if (unitTarget)
        {
            float x, y, z;
            unitTarget->GetPosition(x, y, z);
            targets.setDestination(x, y, z);
        }
    }

    // spell effect 141 needs to be cast as custom with basePoints
    if (m_spellInfo->Effect[effIndex] == SPELL_EFFECT_FORCE_CAST_WITH_VALUE)
        unitTarget->CastCustomSpell(targets, spellInfo, &basePoints, &basePoints, &basePoints, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, ObjectGuid(), m_spellInfo);
    else
        unitTarget->CastSpell(targets, spellInfo, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, ObjectGuid(), m_spellInfo);
}

void Spell::EffectTriggerSpell(SpellEffectIndex effIndex)
{
    uint32 triggered_spell_id = m_spellInfo->EffectTriggerSpell[effIndex];

    // special cases
    switch (triggered_spell_id)
    {
        case 23209: // Terrordale Haunting Spirit 
            if (urand(1, 100) > 55)
                return;
            break;
        case 23253: // Terrordale Haunting Spirit 
            if (urand(1, 100) > 35)
                return;
            break;
        // Flame Wreath: Explosion
        case 29950:
            m_caster->RemoveAurasDueToSpellByCancel(29947);
            return;
        // Priest Shadowfiend (34433) need apply mana gain trigger aura on pet
        case 41967:
        {
            if (Unit* pet = unitTarget->GetPet())
            {
                pet->CastSpell(pet, 28305, TRIGGERED_OLD_TRIGGERED);
                pet->AI()->AttackStart(m_caster->GetTarget());
            }
            return;
        }
        case 44949:
            // triggered spell have same category
            if (m_caster->GetTypeId() == TYPEID_PLAYER)
                m_caster->RemoveSpellCooldown(triggered_spell_id);
            break;
        case 47531: // Dismiss pet - suppress error
            return;
    }

    // normal case
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(triggered_spell_id);
    if (!spellInfo)
    {
        sLog.outError("EffectTriggerSpell of spell %u: triggering unknown spell id %i", m_spellInfo->Id, triggered_spell_id);
        return;
    }

    // select formal caster for triggered spell
    Unit* caster = m_caster;

    // some triggered spells require specific equipment
    if (spellInfo->EquippedItemClass >= 0 && m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        // main hand weapon required
        if (spellInfo->AttributesEx3 & SPELL_ATTR_EX3_MAIN_HAND)
        {
            Item* item = ((Player*)m_caster)->GetWeaponForAttack(BASE_ATTACK, true, false);

            // skip spell if no weapon in slot or broken
            if (!item)
                return;

            // skip spell if weapon not fit to triggered spell
            if (!item->IsFitToSpellRequirements(spellInfo))
                return;
        }

        // offhand hand weapon required
        if (spellInfo->AttributesEx3 & SPELL_ATTR_EX3_REQ_OFFHAND)
        {
            Item* item = ((Player*)m_caster)->GetWeaponForAttack(OFF_ATTACK, true, false);

            // skip spell if no weapon in slot or broken
            if (!item)
                return;

            // skip spell if weapon not fit to triggered spell
            if (!item->IsFitToSpellRequirements(spellInfo))
                return;
        }
    }

    SpellCastTargets targets;

    switch (m_spellInfo->EffectImplicitTargetA[effIndex])
    {
        case TARGET_LOCATION_UNIT_MINION_POSITION: break; // confirmed by 31348 nothing is forwarded
        default: targets.setUnitTarget(unitTarget);
    }

    if (spellInfo->Targets & TARGET_FLAG_DEST_LOCATION)
    {
        if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        {
            float x, y, z;
            m_targets.getDestination(x, y, z);
            targets.setDestination(x, y, z);
        }
        else if (unitTarget)
        {
            float x, y, z;
            unitTarget->GetPosition(x, y, z);
            targets.setDestination(x, y, z);
        }
    }

    caster->CastSpell(targets, spellInfo, TRIGGERED_OLD_TRIGGERED, m_CastItem, nullptr, m_originalCasterGUID, m_spellInfo);
}

void Spell::EffectTriggerMissileSpell(SpellEffectIndex effect_idx)
{
    uint32 triggered_spell_id = m_spellInfo->EffectTriggerSpell[effect_idx];

    // normal case
    SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(triggered_spell_id);

    if (!spellInfo)
    {
        if (unitTarget)
        {
            DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell ScriptStart spellid %u in EffectTriggerMissileSpell", m_spellInfo->Id);
            m_caster->GetMap()->ScriptsStart(sSpellScripts, m_spellInfo->Id, m_caster, unitTarget);
        }
        else
            sLog.outError("EffectTriggerMissileSpell of spell %u (eff: %u): triggering unknown spell id %u",
                          m_spellInfo->Id, effect_idx, triggered_spell_id);
        return;
    }

    if (m_CastItem)
        DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "WORLD: cast Item spellId - %i", spellInfo->Id);

    SpellCastTargets targets;
    if (unitTarget)
        m_targets.setUnitTarget(unitTarget);
    else if (gameObjTarget)
        m_targets.setGOTarget(gameObjTarget);
    else
        m_targets.setDestination(m_targets.m_destPos.x, m_targets.m_destPos.y, m_targets.m_destPos.z);
    m_caster->CastSpell(m_targets, spellInfo, TRIGGERED_OLD_TRIGGERED, m_CastItem, nullptr, m_originalCasterGUID, m_spellInfo);
}

void Spell::EffectTeleportUnits(SpellEffectIndex eff_idx)   // TODO - Use target settings for this effect!
{
    if (!unitTarget || unitTarget->IsTaxiFlying())
        return;

    // Target dependend on TargetB, if there is none provided, decide dependend on A
    uint32 targetType = m_spellInfo->EffectImplicitTargetB[eff_idx];
    if (!targetType)
        targetType = m_spellInfo->EffectImplicitTargetA[eff_idx];

    // If not exist data for dest location - return
    if (!(m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION))
    {
        sLog.outError("Spell::EffectTeleportUnits - unknown EffectImplicitTargetB[%u] = %u for spell ID %u", eff_idx, m_spellInfo->EffectImplicitTargetB[eff_idx], m_spellInfo->Id);
        return;
    }
    // Init dest coordinates
    Position position = m_targets.getDestination();
    float orientation = m_targets.m_destPos.o;
    if (orientation == 0.f) // not filled in spell targeting
    {
        if (m_caster != unitTarget)
            orientation = position.GetAngle(m_caster->GetPositionX(), m_caster->GetPositionY());
        else
            orientation = unitTarget->GetOrientation();
    }
    
    // Teleport
    if (m_targets.m_mapId == UINT32_MAX || m_targets.m_mapId == unitTarget->GetMapId())
    {
        if (unitTarget->IsPlayer() && unitTarget->IsMoving())
            position.z += 0.5f;
        unitTarget->NearTeleportTo(position.x, position.y, position.z, orientation, unitTarget == m_caster,
            m_spellInfo->EffectImplicitTargetA[eff_idx] == TARGET_LOCATION_DATABASE ||
            m_spellInfo->EffectImplicitTargetB[eff_idx] == TARGET_LOCATION_DATABASE);
    }
    else if (unitTarget->GetTypeId() == TYPEID_PLAYER)
    {
        Player* player = static_cast<Player*>(unitTarget);
        MapEntry const* targetMapEntry = sMapStore.LookupEntry(m_targets.m_mapId);
        if (!targetMapEntry)
            return;
        if (!player->IsAlive() && targetMapEntry->IsDungeon())
        {
            auto data = player->CheckAndRevivePlayerOnDungeonEnter(targetMapEntry, m_targets.m_mapId);
            if (!data.first)
                return;
        }
        player->TeleportTo(m_targets.m_mapId, position.x, position.y, position.z, orientation, unitTarget == m_caster ? TELE_TO_SPELL : 0);
    }

    // post effects for TARGET_LOCATION_DATABASE
    switch (m_spellInfo->Id)
    {
        case 23441:                                 // Ultrasafe Transporter: Gadgetzan
        {
            // Wrong destination already rolled for, only handle minor malfunction on sucess
            m_caster->CastSpell(m_caster, 23450, TRIGGERED_OLD_TRIGGERED); // Transporter Arrival

            return;
        }
        case 23442:                                 // Dimensional Ripper - Everlook
        {
            // Roll for major malfunction (1/6); 23450 = success | 23449 = malfunction (being set afire)
            m_caster->CastSpell(m_caster, (urand(0, 5) ? 23450 : 23449), TRIGGERED_OLD_TRIGGERED);

            return;
        }
        // Ultrasafe Transporter: Toshley's Station
        case 36941:
        {
            if (roll_chance_i(50))                          // 50% success
            {
                int32 rand_eff = urand(1, 7);
                switch (rand_eff)
                {
                    case 1:
                        // soul split - evil
                        m_caster->CastSpell(m_caster, 36900, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 2:
                        // soul split - good
                        m_caster->CastSpell(m_caster, 36901, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 3:
                        // Increase the size
                        m_caster->CastSpell(m_caster, 36895, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 4:
                        // Decrease the size
                        m_caster->CastSpell(m_caster, 36893, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 5:
                        // Transform
                    {
                        if (((Player*)m_caster)->GetTeam() == ALLIANCE)
                            m_caster->CastSpell(m_caster, 36897, TRIGGERED_OLD_TRIGGERED);
                        else
                            m_caster->CastSpell(m_caster, 36899, TRIGGERED_OLD_TRIGGERED);
                        break;
                    }
                    case 6:
                        // chicken
                        m_caster->CastSpell(m_caster, 36940, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 7:
                        // evil twin
                        m_caster->CastSpell(m_caster, 23445, TRIGGERED_OLD_TRIGGERED);
                        break;
                }
            }
            return;
        }
        // Dimensional Ripper - Area 52
        case 36890:
        {
            if (roll_chance_i(50))                          // 50% success
            {
                int32 rand_eff = urand(1, 4);
                switch (rand_eff)
                {
                    case 1:
                        // soul split - evil
                        m_caster->CastSpell(m_caster, 36900, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 2:
                        // soul split - good
                        m_caster->CastSpell(m_caster, 36901, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 3:
                        // Increase the size
                        m_caster->CastSpell(m_caster, 36895, TRIGGERED_OLD_TRIGGERED);
                        break;
                    case 4:
                        // Transform
                    {
                        if (((Player*)m_caster)->GetTeam() == ALLIANCE)
                            m_caster->CastSpell(m_caster, 36897, TRIGGERED_OLD_TRIGGERED);
                        else
                            m_caster->CastSpell(m_caster, 36899, TRIGGERED_OLD_TRIGGERED);
                        break;
                    }
                }
            }
            return;
        }
    }
}

void Spell::EffectApplyAura(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    // ghost spell check, allow apply any auras at player loading in ghost mode (will be cleanup after load)
    if ((!unitTarget->IsAlive() && !(IsDeathOnlySpell(m_spellInfo) || IsDeathPersistentSpell(m_spellInfo))) &&
        (unitTarget->GetTypeId() != TYPEID_PLAYER || !((Player*)unitTarget)->GetSession()->PlayerLoading()))
        return;

    Unit* caster = GetAffectiveCaster();
    if (!caster)
    {
        // FIXME: currently we can't have auras applied explicitly by gameobjects
        // so for auras from wild gameobjects (no owner) target used
        if (m_originalCasterGUID.IsGameObject())
            caster = unitTarget;
        else
            return;
    }

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell: Aura is: %u", m_spellInfo->EffectApplyAuraName[eff_idx]);

    Aura* aur = CreateAura(m_spellInfo, eff_idx, &damage, &m_currentBasePoints[eff_idx], m_spellAuraHolder, unitTarget, caster, m_CastItem);
    m_spellAuraHolder->AddAura(aur, eff_idx);
}

void Spell::EffectUnlearnSpecialization(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* _player = (Player*)unitTarget;
    uint32 spellToUnlearn = m_spellInfo->EffectTriggerSpell[eff_idx];

    _player->removeSpell(spellToUnlearn);

    if (WorldObject const* caster = GetCastingObject())
        DEBUG_LOG("Spell: %s has unlearned spell %u at %s", _player->GetGuidStr().c_str(), spellToUnlearn, caster->GetGuidStr().c_str());
}

void Spell::EffectPowerDrain(SpellEffectIndex eff_idx)
{
    if (m_spellInfo->EffectMiscValue[eff_idx] < 0 || m_spellInfo->EffectMiscValue[eff_idx] >= MAX_POWERS)
        return;

    Powers powerType = Powers(m_spellInfo->EffectMiscValue[eff_idx]);

    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;
    if (unitTarget->GetPowerType() != powerType)
        return;
    if (damage < 0)
        return;

    uint32 curPower = unitTarget->GetPower(powerType);

    // add spell damage bonus
    damage = m_caster->SpellDamageBonusDone(unitTarget, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);
    damage = unitTarget->SpellDamageBonusTaken(m_caster, m_spellInfo, uint32(damage), SPELL_DIRECT_DAMAGE);

    uint32 power = damage;

    power -= unitTarget->GetResilienceRatingDamageReduction(power, SpellDmgClass(m_spellInfo->DmgClass), false, powerType);

    int32 new_damage;
    if (curPower < power)
        new_damage = curPower;
    else
        new_damage = power;

    unitTarget->ModifyPower(powerType, -new_damage);

    float gainMultiplier = 1.0f;

    // Do not gain power from self drain or when power types don't match
    if (m_caster->GetPowerType() == powerType && m_caster != unitTarget)
    {
        gainMultiplier = m_spellInfo->EffectMultipleValue[eff_idx];

        if (Player* modOwner = m_caster->GetSpellModOwner())
            modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_MULTIPLE_VALUE, gainMultiplier);
    }

    m_spellLog.AddLog(uint32(SPELL_EFFECT_POWER_DRAIN), unitTarget->GetPackGUID(), new_damage, uint32(powerType), gainMultiplier);

    if (int32 gain = int32(new_damage * gainMultiplier))
        m_caster->EnergizeBySpell(m_caster, m_spellInfo, gain, powerType);
}

void Spell::EffectSendEvent(SpellEffectIndex effectIndex)
{
    /*
    we do not handle a flag dropping or clicking on flag in battleground by sendevent system
    TODO: Actually, why not...
    */
    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell ScriptStart %u for spellid %u in EffectSendEvent ", m_spellInfo->EffectMiscValue[effectIndex], m_spellInfo->Id);

    StartEvents_Event(m_caster->GetMap(), m_spellInfo->EffectMiscValue[effectIndex], m_caster, focusObject, true, m_caster);
}

void Spell::EffectPowerBurn(SpellEffectIndex eff_idx)
{
    if (m_spellInfo->EffectMiscValue[eff_idx] < 0 || m_spellInfo->EffectMiscValue[eff_idx] >= MAX_POWERS)
        return;

    Powers powertype = Powers(m_spellInfo->EffectMiscValue[eff_idx]);

    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;
    if (unitTarget->GetPowerType() != powertype)
        return;
    if (damage < 0)
        return;

    int32 curPower = int32(unitTarget->GetPower(powertype));

    int32 power = damage;

    power -= unitTarget->GetResilienceRatingDamageReduction(uint32(power), SpellDmgClass(m_spellInfo->DmgClass), false, powertype);

    int32 new_damage = (curPower < power) ? curPower : power;

    unitTarget->ModifyPower(powertype, -new_damage);
    float multiplier = m_spellInfo->EffectMultipleValue[eff_idx];

    if (Player* modOwner = m_caster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_MULTIPLE_VALUE, multiplier);

    new_damage = int32(new_damage * multiplier);

    m_damagePerEffect[eff_idx] = CalculateSpellEffectDamage(unitTarget, new_damage);

    // should use here effect POWER_DRAIN because POWER_BURN is not implemented on client
    m_spellLog.AddLog(uint32(SPELL_EFFECT_POWER_DRAIN), unitTarget->GetPackGUID(), new_damage, uint32(powertype), multiplier);
}

void Spell::EffectHeal(SpellEffectIndex eff_idx)
{
    if (unitTarget && unitTarget->IsAlive() && damage >= 0)
    {
        // Try to get original caster
        Unit* caster = GetAffectiveCaster();
        if (!caster)
            return;

        int32 addhealth = damage;

        // Vessel of the Naaru (Vial of the Sunwell trinket)
        if (m_spellInfo->Id == 45064)
        {
            // Amount of heal - depends from stacked Holy Energy
            int damageAmount = 0;
            Unit::AuraList const& mDummyAuras = m_caster->GetAurasByType(SPELL_AURA_DUMMY);
            for (Unit::AuraList::const_iterator i = mDummyAuras.begin(); i != mDummyAuras.end(); ++i)
                if ((*i)->GetId() == 45062)
                    damageAmount += (*i)->GetModifier()->m_amount;
            if (damageAmount)
                m_caster->RemoveAurasDueToSpell(45062);

            addhealth += damageAmount;
        }
        // Swiftmend - consumes Regrowth or Rejuvenation
        else if (m_spellInfo->TargetAuraState == AURA_STATE_SWIFTMEND && unitTarget->HasAuraState(AURA_STATE_SWIFTMEND))
        {
            Unit::AuraList const& RejorRegr = unitTarget->GetAurasByType(SPELL_AURA_PERIODIC_HEAL);
            // find most short by duration
            Aura* targetAura = nullptr;
            for (Unit::AuraList::const_iterator i = RejorRegr.begin(); i != RejorRegr.end(); ++i)
            {
                if ((*i)->GetSpellProto()->SpellFamilyName == SPELLFAMILY_DRUID &&
                        // Regrowth or Rejuvenation 0x40 | 0x10
                        ((*i)->GetSpellProto()->SpellFamilyFlags & uint64(0x0000000000000050)))
                {
                    if (!targetAura || (*i)->GetAuraDuration() < targetAura->GetAuraDuration())
                        targetAura = *i;
                }
            }

            if (!targetAura)
            {
                sLog.outError("Target (GUID: %u TypeId: %u) has aurastate AURA_STATE_SWIFTMEND but no matching aura.", unitTarget->GetGUIDLow(), unitTarget->GetTypeId());
                return;
            }
            int idx = 0;
            while (idx < 3)
            {
                if (targetAura->GetSpellProto()->EffectApplyAuraName[idx] == SPELL_AURA_PERIODIC_HEAL)
                    break;
                idx++;
            }

            int32 tickheal = targetAura->GetModifier()->m_amount;
            int32 tickcount = GetSpellDuration(targetAura->GetSpellProto()) / targetAura->GetSpellProto()->EffectAmplitude[idx];

            unitTarget->RemoveAurasByCasterSpell(targetAura->GetId(), targetAura->GetCasterGuid());

            addhealth += tickheal * tickcount;
        }
        else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_POTION)
        {
            if (m_caster->HasAura(17619)) // Alchemists stone
                addhealth *= 1.4f; // increase healing by 40%
        }
        else
        {
            switch (m_spellInfo->Id)
            {
                // Crusader Enchant: Holy Strength amount decrease by 4% each level after 60
                case 20007:
                {
                    if (GetCaster()->GetTypeId() == TYPEID_PLAYER && GetCaster()->getLevel() > 60)
                        addhealth = int32(addhealth * (1 - (((float(GetCaster()->getLevel()) - 60) * 4) / 100)));
                    break;
                }
                // Vessel of the Naaru (Vial of the Sunwell trinket)
                case  45064:
                {
                    // Amount of heal - depends from stacked Holy Energy
                    int damageAmount = 0;
                    Unit::AuraList const& mDummyAuras = m_caster->GetAurasByType(SPELL_AURA_DUMMY);
                    for (Unit::AuraList::const_iterator i = mDummyAuras.begin(); i != mDummyAuras.end(); ++i)
                        if ((*i)->GetId() == 45062)
                            damageAmount += (*i)->GetModifier()->m_amount;
                    if (damageAmount)
                        m_caster->RemoveAurasDueToSpell(45062);

                    addhealth += damageAmount;
                    break;

                }
            }
        }

        addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, addhealth, HEAL);
        addhealth = unitTarget->SpellHealingBonusTaken(caster, m_spellInfo, addhealth, HEAL);

        m_healingPerEffect[eff_idx] = addhealth;
    }
}

void Spell::EffectHealPct(SpellEffectIndex eff_idx)
{
    if (unitTarget && unitTarget->IsAlive() && damage >= 0)
    {
        // Try to get original caster
        Unit* caster = GetAffectiveCaster();
        if (!caster)
            return;

        uint32 addhealth = unitTarget->GetMaxHealth() * damage / 100;

        addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, addhealth, HEAL);
        addhealth = unitTarget->SpellHealingBonusTaken(caster, m_spellInfo, addhealth, HEAL);

        m_healingPerEffect[eff_idx] = addhealth;
    }
}

void Spell::EffectHealMechanical(SpellEffectIndex eff_idx)
{
    // Mechanic creature type should be correctly checked by targetCreatureType field
    if (unitTarget && unitTarget->IsAlive() && damage >= 0)
    {
        // Try to get original caster
        Unit* caster = GetAffectiveCaster();
        if (!caster)
            return;

        uint32 addhealth = caster->SpellHealingBonusDone(unitTarget, m_spellInfo, damage, HEAL);
        addhealth = unitTarget->SpellHealingBonusTaken(caster, m_spellInfo, addhealth, HEAL);

        m_healingPerEffect[eff_idx] = addhealth;
    }
}

void Spell::EffectHealthLeech(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    if (damage < 0)
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "HealthLeech :%i", damage);

    uint32 curHealth = unitTarget->GetHealth();
    damage = m_caster->SpellNonMeleeDamageLog(unitTarget, m_spellInfo->Id, damage);
    if ((int32)curHealth < damage)
        damage = curHealth;

    float multiplier = m_spellInfo->EffectMultipleValue[eff_idx];

    if (Player* modOwner = m_caster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_MULTIPLE_VALUE, multiplier);

    uint32 heal = uint32(damage * multiplier);
    if (m_caster->IsAlive())
    {
        heal = m_caster->SpellHealingBonusTaken(m_caster, m_spellInfo, heal, HEAL);

        m_caster->DealHeal(m_caster, heal, m_spellInfo);
    }
}

bool Spell::DoCreateItem(SpellEffectIndex /*eff_idx*/, uint32 itemtype, bool reportError)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return false;

    Player* player = (Player*)unitTarget;

    uint32 newitemid = itemtype;
    ItemPrototype const* pProto = ObjectMgr::GetItemPrototype(newitemid);
    if (!pProto)
    {
        if (reportError)
            player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, nullptr, nullptr);
        return false;
    }

    // bg reward have some special in code work
    uint32 bgType = 0;
    switch (m_spellInfo->Id)
    {
        case SPELL_AV_MARK_WINNER:
        case SPELL_AV_MARK_LOSER:
            bgType = BATTLEGROUND_AV;
            break;
        case SPELL_WS_MARK_WINNER:
        case SPELL_WS_MARK_LOSER:
            bgType = BATTLEGROUND_WS;
            break;
        case SPELL_AB_MARK_WINNER:
        case SPELL_AB_MARK_LOSER:
            bgType = BATTLEGROUND_AB;
            break;
        default:
            break;
    }

    uint32 num_to_add = damage;

    if (num_to_add < 1)
        num_to_add = 1;
    if (num_to_add > pProto->Stackable)
        num_to_add = pProto->Stackable;

    // init items_count to 1, since 1 item will be created regardless of specialization
    int items_count = 1;
    // the chance to create additional items
    float additionalCreateChance = 0.0f;
    // the maximum number of created additional items
    uint8 additionalMaxNum = 0;
    // get the chance and maximum number for creating extra items
    if (canCreateExtraItems(player, m_spellInfo->Id, additionalCreateChance, additionalMaxNum))
    {
        // roll with this chance till we roll not to create or we create the max num
        while (roll_chance_f(additionalCreateChance) && items_count <= additionalMaxNum)
            ++items_count;
    }

    // really will be created more items
    num_to_add *= items_count;

    // can the player store the new item?
    ItemPosCountVec dest;
    uint32 no_space = 0;
    InventoryResult msg = player->CanStoreNewItem(NULL_BAG, NULL_SLOT, dest, newitemid, num_to_add, &no_space);
    if (msg != EQUIP_ERR_OK)
    {
        // convert to possible store amount
        if (msg == EQUIP_ERR_INVENTORY_FULL || msg == EQUIP_ERR_CANT_CARRY_MORE_OF_THIS)
            num_to_add -= no_space;

        // for battleground marks send by mail if not add all expected
        if (no_space > 0 && bgType)
        {
            if (BattleGround * bg = sBattleGroundMgr.GetBattleGroundTemplate(BattleGroundTypeId(bgType)))
            {
                bg->SendRewardMarkByMail(player, newitemid, no_space);
                return true;
            }
        }

        // if not created by another reason from full inventory or unique items amount limitation
        if (reportError)
            player->SendEquipError(msg, nullptr, nullptr, newitemid);
        return false;
    }

    if (num_to_add)
    {
        // create the new item and store it
        Item* pItem = player->StoreNewItem(dest, newitemid, true, Item::GenerateItemRandomPropertyId(newitemid));

        // was it successful? return error if not
        if (!pItem)
        {
            if (reportError)
                player->SendEquipError(EQUIP_ERR_ITEM_NOT_FOUND, nullptr, nullptr);
            return false;
        }

        // set the "Crafted by ..." property of the item
        if (pItem->GetProto()->Class != ITEM_CLASS_CONSUMABLE && pItem->GetProto()->Class != ITEM_CLASS_QUEST)
            pItem->SetGuidValue(ITEM_FIELD_CREATOR, player->GetObjectGuid());

        // send info to the client
        player->SendNewItem(pItem, num_to_add, true, !bgType);

        // we succeeded in creating at least one item, so a levelup is possible
        if (!bgType)
            player->UpdateCraftSkill(m_spellInfo->Id);
    }
    return true;
}

void Spell::EffectCreateItem(SpellEffectIndex eff_idx)
{
    if (DoCreateItem(eff_idx, m_spellInfo->EffectItemType[eff_idx], !m_spellInfo->HasAttribute(SPELL_ATTR_HIDE_IN_COMBAT_LOG)))
        m_spellLog.AddLog(uint32(SPELL_EFFECT_CREATE_ITEM), m_spellInfo->EffectItemType[eff_idx]);
}

void Spell::EffectPersistentAA(SpellEffectIndex eff_idx)
{
    Unit* caster = GetAffectiveCaster();
    // FIXME: in case wild GO will used wrong affective caster (target in fact) as dynobject owner
    if (!caster)
        caster = m_caster;

    float radius = GetSpellRadius(sSpellRadiusStore.LookupEntry(m_spellInfo->EffectRadiusIndex[eff_idx]));

    if (Player* modOwner = caster->GetSpellModOwner())
        modOwner->ApplySpellMod(m_spellInfo->Id, SPELLMOD_RADIUS, radius, this);

    SpellTarget target = SpellTarget(m_spellInfo->EffectImplicitTargetB[eff_idx] ? m_spellInfo->EffectImplicitTargetB[eff_idx] : m_spellInfo->EffectImplicitTargetA[eff_idx]);

    DynamicObject* dynObj = new DynamicObject;
    if (!dynObj->Create(caster->GetMap()->GenerateLocalLowGuid(HIGHGUID_DYNAMICOBJECT), caster, m_spellInfo->Id,
        eff_idx, m_targets.m_destPos.x, m_targets.m_destPos.y, m_targets.m_destPos.z, m_duration, radius, DYNAMIC_OBJECT_AREA_SPELL, target, damage, m_currentBasePoints[eff_idx]))
    {
        delete dynObj;
        return;
    }

    caster->AddDynObject(dynObj);
    caster->GetMap()->Add(dynObj);

    // Potential Hack - at the time of channel start Dynamic Object is not created yet, so have to do it here
    // Sent in next Object Update so for client its the same
    if (eff_idx == EFFECT_INDEX_0 && IsChanneledSpell(m_spellInfo))
    {
        m_caster->SetChannelObject(dynObj);
        m_caster->SendForcedObjectUpdate();
    }
}

void Spell::EffectEnergize(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    if (m_spellInfo->EffectMiscValue[eff_idx] < 0 || m_spellInfo->EffectMiscValue[eff_idx] >= MAX_POWERS)
        return;

    Powers power = Powers(m_spellInfo->EffectMiscValue[eff_idx]);

    // Some level depends spells
    int level_multiplier = 0;
    int level_diff = 0;
    switch (m_spellInfo->Id)
    {
        case 5530:
            if (m_caster->getClass() == CLASS_ROGUE) // Warrior and rogue use same spell, on rogue not supposed to give resource, WTF game devs?!
                return;
            break;
        case 9512:                                          // Restore Energy
            level_diff = m_caster->getLevel() - 40;
            level_multiplier = 2;
            break;
        case 24571:                                         // Blood Fury
            level_diff = m_caster->getLevel() - 60;
            level_multiplier = 10;
            break;
        case 24532:                                         // Burst of Energy
            level_diff = m_caster->getLevel() - 60;
            level_multiplier = 4;
            break;
        default:
            break;
    }

    if (m_spellInfo->SpellFamilyName == SPELLFAMILY_POTION)
    {
        if (m_caster->HasAura(17619)) // Alchemists stone
            damage *= 1.4f; // increase healing by 40%
    }

    if (level_diff > 0)
        damage -= level_multiplier * level_diff;

    if (damage < 0)
        return;

    if (unitTarget->GetMaxPower(power) == 0)
        return;

    m_caster->EnergizeBySpell(unitTarget, m_spellInfo, damage, power);

    // Mad Alchemist's Potion
    if (m_spellInfo->Id == 45051)
    {
        // find elixirs on target
        uint32 elixir_mask = 0;
        Unit::SpellAuraHolderMap& Auras = unitTarget->GetSpellAuraHolderMap();
        for (Unit::SpellAuraHolderMap::iterator itr = Auras.begin(); itr != Auras.end(); ++itr)
        {
            uint32 spell_id = itr->second->GetId();
            if (uint32 mask = sSpellMgr.GetSpellElixirMask(spell_id))
                elixir_mask |= mask;
        }

        // get available elixir mask any not active type from battle/guardian (and flask if no any)
        elixir_mask = (elixir_mask & ELIXIR_FLASK_MASK) ^ ELIXIR_FLASK_MASK;

        // get all available elixirs by mask and spell level
        std::vector<uint32> elixirs;
        SpellElixirMap const& m_spellElixirs = sSpellMgr.GetSpellElixirMap();
        for (SpellElixirMap::const_iterator itr = m_spellElixirs.begin(); itr != m_spellElixirs.end(); ++itr)
        {
            if (itr->second & elixir_mask)
            {
                if (itr->second & (ELIXIR_UNSTABLE_MASK | ELIXIR_SHATTRATH_MASK))
                    continue;

                SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(itr->first);
                if (spellInfo && (spellInfo->spellLevel < m_spellInfo->spellLevel || spellInfo->spellLevel > unitTarget->getLevel()))
                    continue;

                elixirs.push_back(itr->first);
            }
        }

        if (!elixirs.empty())
        {
            // cast random elixir on target
            uint32 rand_spell = urand(0, elixirs.size() - 1);
            m_caster->CastSpell(unitTarget, elixirs[rand_spell], TRIGGERED_OLD_TRIGGERED, m_CastItem);
        }
    }
}

void Spell::EffectEnergisePct(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    if (m_spellInfo->EffectMiscValue[eff_idx] < 0 || m_spellInfo->EffectMiscValue[eff_idx] >= MAX_POWERS)
        return;

    Powers power = Powers(m_spellInfo->EffectMiscValue[eff_idx]);

    uint32 maxPower = unitTarget->GetMaxPower(power);
    if (maxPower == 0)
        return;

    uint32 gain = damage * maxPower / 100;
    m_caster->EnergizeBySpell(unitTarget, m_spellInfo, gain, power);
}

void Spell::SendLoot(ObjectGuid guid, LootType loottype, LockType lockType)
{
    switch (guid.GetHigh())
    {
        case HIGHGUID_GAMEOBJECT:
        {
            if (gameObjTarget)
            {
                switch (gameObjTarget->GetGoType())
                {
                    case GAMEOBJECT_TYPE_DOOR:
                    case GAMEOBJECT_TYPE_BUTTON:
                    case GAMEOBJECT_TYPE_QUESTGIVER:
                    case GAMEOBJECT_TYPE_SPELL_FOCUS:
                    case GAMEOBJECT_TYPE_GOOBER:
                    case GAMEOBJECT_TYPE_FLAGSTAND:
                        gameObjTarget->Use(m_caster);
                        return;

                    case GAMEOBJECT_TYPE_CHEST:
                        gameObjTarget->Use(m_caster);
                        // Don't return, let loots been taken
                        break;

                    case GAMEOBJECT_TYPE_TRAP:
                        switch (lockType)
                        {
                            case LOCKTYPE_NONE:
                            case LOCKTYPE_DISARM_TRAP:
                            case LOCKTYPE_OPEN_ATTACKING:
                                gameObjTarget->SetLootState(GO_ACTIVATED);
                                return;
                            default:
                                sLog.outError("Spell::SendLoot unhandled locktype %u for GameObject trap (entry %u) for spell %u.", lockType, gameObjTarget->GetEntry(), m_spellInfo->Id);
                                return;
                        }
                    default:
                        sLog.outError("Spell::SendLoot unhandled GameObject type %u (entry %u) for spell %u.", gameObjTarget->GetGoType(), gameObjTarget->GetEntry(), m_spellInfo->Id);
                        return;
                }

                if (m_caster->GetTypeId() != TYPEID_PLAYER)
                    return;

                Loot*& loot = gameObjTarget->m_loot;
                if (!loot)
                {
                    loot = new Loot((Player*)m_caster, gameObjTarget, loottype);
                    TakeCastItem();
                }
                loot->ShowContentTo((Player*)m_caster);
                return;
            }
            break;
        }

        case HIGHGUID_ITEM:
        {
            if (itemTarget)
            {
                Loot*& loot = itemTarget->m_loot;
                if (!loot)
                {
                    loot = new Loot((Player*)m_caster, itemTarget, loottype);
                    TakeCastItem();
                }
                loot->ShowContentTo((Player*)m_caster);
                return;
            }

            break;
        }
        default:
            sLog.outError("Spell::SendLoot unhandled Object type %s for spell %u.", guid.GetString().c_str(), m_spellInfo->Id);
            break;
    }
}

void Spell::EffectOpenLock(SpellEffectIndex eff_idx)
{
    if (!m_caster || m_caster->GetTypeId() != TYPEID_PLAYER)
    {
        DEBUG_LOG("WORLD: Open Lock - No Player Caster!");
        return;
    }

    Player* player = (Player*)m_caster;

    uint32 lockId;

    // Get lockId
    if (gameObjTarget)
    {
        lockId = gameObjTarget->GetGOInfo()->GetLockId();
    }
    else if (itemTarget)
    {
        lockId = itemTarget->GetProto()->LockID;
    }
    else
    {
        DEBUG_LOG("WORLD: Open Lock - No GameObject/Item Target!");
        return;
    }

    // not allow use skill grow at item base open
    if (m_effectSkillInfo[eff_idx].skillId != SKILL_NONE)
    {
        // update skill if really known
        if (uint32 pureSkillValue = player->GetSkillValuePure(m_effectSkillInfo[eff_idx].skillId))
        {
            if (gameObjTarget && !gameObjTarget->m_loot)
            {
                // Allow one skill-up until respawned
                if (!gameObjTarget->IsInSkillupList(player) &&
                        player->UpdateGatherSkill(m_effectSkillInfo[eff_idx].skillId, pureSkillValue, m_effectSkillInfo[eff_idx].reqSkillValue))
                    gameObjTarget->AddToSkillupList(player);
            }
            else if (itemTarget && !itemTarget->m_loot)
            {
                // Do one skill-up
                player->UpdateGatherSkill(m_effectSkillInfo[eff_idx].skillId, pureSkillValue, m_effectSkillInfo[eff_idx].reqSkillValue);
            }
        }
    }

    // mark item as unlocked
    if (itemTarget)
    {
        itemTarget->SetFlag(ITEM_FIELD_FLAGS, ITEM_DYNFLAG_UNLOCKED);

        // only send loot if owner is player, else client sends release anyway
        if (itemTarget->GetOwnerGuid() == m_caster->GetObjectGuid())
        {
            SendLoot(itemTarget->GetObjectGuid(), LOOT_SKINNING, LockType(m_spellInfo->EffectMiscValue[eff_idx]));
            m_spellLog.AddLog(uint32(SPELL_EFFECT_OPEN_LOCK), itemTarget->GetPackGUID());
        }
    }
    else
    {
        SendLoot(gameObjTarget->GetObjectGuid(), LOOT_SKINNING, LockType(m_spellInfo->EffectMiscValue[eff_idx]));
        m_spellLog.AddLog(uint32(SPELL_EFFECT_OPEN_LOCK), gameObjTarget->GetPackGUID());
    }
}

void Spell::EffectSummonChangeItem(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = (Player*)m_caster;

    // applied only to using item
    if (!m_CastItem)
        return;

    // ... only to item in own inventory/bank/equip_slot
    if (m_CastItem->GetOwnerGuid() != player->GetObjectGuid())
        return;

    uint32 newitemid = m_spellInfo->EffectItemType[eff_idx];
    if (!newitemid)
        return;

    Item* oldItem = m_CastItem;

    if (m_CastItem)
        m_CastItem->SetUsedInSpell(false);
    // prevent crash at access and unexpected charges counting with item update queue corrupt
    ClearCastItem();

    uint32 curItemCount = player->GetItemCount(newitemid, true);

    if (Item* newItem = player->ConvertItem(oldItem, newitemid))
    {
        player->ItemAddedQuestCheck(newItem->GetEntry(), newItem->GetCount());

        // Push packet to client so it knows we've created an item and quest can show objective update
        player->SendNewItem(newItem, newItem->GetCount() - curItemCount, true, false);
    }
}

void Spell::EffectProficiency(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* player = static_cast<Player*>(m_caster);

    uint32 subClassMask = m_spellInfo->EquippedItemSubClassMask;
    if (m_spellInfo->EquippedItemClass == ITEM_CLASS_WEAPON && !(player->GetWeaponProficiency() & subClassMask))
    {
        player->AddWeaponProficiency(subClassMask);
        player->SendProficiency(ITEM_CLASS_WEAPON, player->GetWeaponProficiency());
    }
    if (m_spellInfo->EquippedItemClass == ITEM_CLASS_ARMOR && !(player->GetArmorProficiency() & subClassMask))
    {
        player->AddArmorProficiency(subClassMask);
        player->SendProficiency(ITEM_CLASS_ARMOR, player->GetArmorProficiency());
    }
}

void Spell::EffectApplyAreaAura(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    AreaAura* Aur = new AreaAura(m_spellInfo, eff_idx, &damage, &m_currentBasePoints[eff_idx], m_spellAuraHolder, unitTarget, m_caster, m_CastItem);
    m_spellAuraHolder->AddAura(Aur, eff_idx);
}

void Spell::EffectSummonType(SpellEffectIndex eff_idx)
{
    // TODO add script for 35679 and 34877

    uint32 prop_id = m_spellInfo->EffectMiscValueB[eff_idx];
    SummonPropertiesEntry const* summon_prop = sSummonPropertiesStore.LookupEntry(prop_id);
    if (!summon_prop)
    {
        sLog.outError("EffectSummonType: Unhandled summon type %u", prop_id);
        return;
    }

    // Pet's are atm handled differently - TODO: Unify with rest
    if (summon_prop->Group == SUMMON_PROP_GROUP_PETS && prop_id != 1562)
    {
        DoSummonPet(eff_idx);
        return;
    }

    // Get casting object
    WorldObject* realCaster = GetCastingObject();
    if (!realCaster)
    {
        sLog.outError("EffectSummonType: No Casting Object found for spell %u, (caster = %s)", m_spellInfo->Id, m_caster->GetGuidStr().c_str());
        return;
    }

    Unit* responsibleCaster = m_originalCaster;
    if (realCaster->GetTypeId() == TYPEID_GAMEOBJECT)
        responsibleCaster = ((GameObject*)realCaster)->GetOwner();

    // Expected Amount: TODO - there are quite some exceptions (like totems, engineering dragonlings..)
    uint32 amount = 1;
    uint32 health = 0; // totems have HP in base points
    uint32 unk = 0; // no idea what it means, but 4000-25000 cant be right for summon count
    if (prop_id == 121 || summon_prop->Title == UNITNAME_SUMMON_TITLE_TOTEM)
    {
        health = damage;
    }
    else
    {
        switch (summon_prop->Group)
        {
            case SUMMON_PROP_GROUP_CONTROLLABLE:
                unk = damage;
                break;
            default:
                amount = damage > 0 ? damage : 1; // old code
                break;
        }
    }

    // Expected Level
    Unit* petInvoker = responsibleCaster ? responsibleCaster : m_caster;
    uint32 level;
    // Everything considered as guardian or critter pets uses its creature template level by default (may change depending on SpellEffect params)
    if (summon_prop->Title == UNITNAME_SUMMON_TITLE_COMPANION)
    {
        if (CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(m_spellInfo->EffectMiscValue[eff_idx]))
            level = urand(cInfo->MinLevel, cInfo->MaxLevel);
        else
        {
            sLog.outError("Spell Effect EFFECT_SUMMON (%u) - no creature template found for summoned NPC %u (spell id %u, effIndex %u)", m_spellInfo->Effect[eff_idx], m_spellInfo->EffectMiscValue[eff_idx], m_spellInfo->Id, eff_idx);
            return;
        }
    }
    else    // Use invoker level in all other cases (to be confirmed)
    {
        if (CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(m_spellInfo->EffectMiscValue[eff_idx]))
            level = std::max(std::min(petInvoker->getLevel(), cInfo->MaxLevel), cInfo->MinLevel);
        else
        {
            sLog.outError("Spell Effect EFFECT_SUMMON (%u) - no creature template found for summoned NPC %u (spell id %u, effIndex %u)", m_spellInfo->Effect[eff_idx], m_spellInfo->EffectMiscValue[eff_idx], m_spellInfo->Id, eff_idx);
            return;
        }
    }
    if (petInvoker->GetTypeId() != TYPEID_PLAYER)
    {
        // If EffectMultipleValue <= 0, pets have their calculated level modified by EffectMultipleValue
        if (m_spellInfo->EffectMultipleValue[eff_idx] <= 0)
        {
            uint32 resultLevel = std::max(petInvoker->getLevel() + m_spellInfo->EffectMultipleValue[eff_idx], 0.0f);

            // Result level should be a valid level for creatures
            if (resultLevel > 0 && resultLevel <= DEFAULT_MAX_CREATURE_LEVEL)
                level = resultLevel;
        }
    }
    // level of creature summoned using engineering item based at engineering skill level
    else if (m_CastItem)
    {
        ItemPrototype const* proto = m_CastItem->GetProto();
        if (proto && proto->RequiredSkill == SKILL_ENGINEERING && proto->InventoryType == INVTYPE_TRINKET)
        {
            if (uint16 engineeringSkill = ((Player*)m_caster)->GetSkillValue(SKILL_ENGINEERING))
            {
                level = engineeringSkill / 5;
                amount = 1;                                 // TODO HACK (needs a neat way of doing)
            }
        }
        // other cases are covered above by using level from template
    }

    CreatureSummonPositions summonPositions;
    summonPositions.resize(amount, CreaturePosition());

    // Set middle position
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(summonPositions[0].x, summonPositions[0].y, summonPositions[0].z);
    else
    {
        realCaster->GetPosition(summonPositions[0].x, summonPositions[0].y, summonPositions[0].z);
        // TODO - Is this really an error?
        sLog.outDebug("Spell Effect EFFECT_SUMMON (%u) - summon without destination (spell id %u, effIndex %u)", m_spellInfo->Effect[eff_idx], m_spellInfo->Id, eff_idx);
    }

    // Set summon positions
    float radius = GetSpellRadius(sSpellRadiusStore.LookupEntry(m_spellInfo->EffectRadiusIndex[eff_idx]));
    CreatureSummonPositions::iterator itr = summonPositions.begin();
    for (++itr; itr != summonPositions.end(); ++itr)        // In case of multiple summons around position for not-fist positions
    {
        if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION || radius > 1.0f)
        {
            realCaster->GetRandomPoint(summonPositions[0].x, summonPositions[0].y, summonPositions[0].z, radius, itr->x, itr->y, itr->z);
            if (realCaster->GetMap()->GetHitPosition(summonPositions[0].x, summonPositions[0].y, summonPositions[0].z, itr->x, itr->y, itr->z, -0.5f))
                realCaster->UpdateAllowedPositionZ(itr->x, itr->y, itr->z);
        }
        else                                                // Get a point near the caster
        {
            realCaster->GetClosePoint(itr->x, itr->y, itr->z, 0.0f, radius, frand(0.0f, 2 * M_PI_F));
            if (realCaster->GetMap()->GetHitPosition(summonPositions[0].x, summonPositions[0].y, summonPositions[0].z, itr->x, itr->y, itr->z, -0.5f))
                realCaster->UpdateAllowedPositionZ(itr->x, itr->y, itr->z);
        }
    }

    bool summonResult = false;
    switch (summon_prop->Group)
    {
        // faction handled later on, or loaded from template
        case SUMMON_PROP_GROUP_WILD:
        case SUMMON_PROP_GROUP_FRIENDLY:
        {
            switch (summon_prop->Title)                     // better from known way sorting summons by AI types
            {
                case UNITNAME_SUMMON_TITLE_NONE:
                {
                    // those are classical totems - effectbasepoints is their hp and not summon ammount!
                    // 121: 23035, battlestands
                    // 647: 52893, Anti-Magic Zone (npc used)
                    if (prop_id == 121 || prop_id == 647)
                        summonResult = DoSummonTotem(summonPositions, eff_idx);
                    else
                    {
                        switch (m_spellInfo->Id) // unable to distinguish based on prop_id, therefore spell by spell override
                        {
                            case 38544: // summon marmot, gives control of marmot pet
                                summonResult = DoSummonPossessed(summonPositions, summon_prop, eff_idx, level);
                                break;
                            default:
                                summonResult = DoSummonWild(summonPositions, summon_prop, eff_idx, level);
                                break;
                        }
                    }
                    break;
                }
                case UNITNAME_SUMMON_TITLE_PET:
                    summonResult = DoSummonGuardian(summonPositions, summon_prop, eff_idx, level);
                    break;
                case UNITNAME_SUMMON_TITLE_GUARDIAN:
                {
                    if (prop_id == 61)
                    {
                        // Totem cases
                        if (CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(m_spellInfo->EffectMiscValue[eff_idx]))
                        {
                            if (cInfo->CreatureType == CREATURE_TYPE_TOTEM)
                            {
                                summonResult = DoSummonTotem(summonPositions, eff_idx);
                                break;
                            }
                        }
                        else
                            return;
                    }

                    summonResult = DoSummonGuardian(summonPositions, summon_prop, eff_idx, level);
                    break;
                }
                case UNITNAME_SUMMON_TITLE_TOTEM:
                    summonResult = DoSummonTotem(summonPositions, eff_idx, summon_prop->Slot);
                    break;
                case UNITNAME_SUMMON_TITLE_COMPANION:
                    // slot 6 set for critters that can help to player in fighting
                    if (summon_prop->Slot == 6)
                        summonResult = DoSummonGuardian(summonPositions, summon_prop, eff_idx, level);
                    else
                        summonResult = DoSummonCritter(summonPositions, summon_prop, eff_idx, level);
                    break;
                default:
                    sLog.outError("EffectSummonType: Unhandled summon title %u", summon_prop->Title);
                    break;
            }
            break;
        }
        case SUMMON_PROP_GROUP_PETS:
        {
            // FIXME : multiple summons -  not yet supported as pet
            // 1562 - force of nature  - sid 33831
            // 1161 - feral spirit - sid 51533
            if (prop_id == 1562)                            // 3 uncontrolable instead of one controllable :/
                summonResult = DoSummonGuardian(summonPositions, summon_prop, eff_idx, level);
            break;
        }
        case SUMMON_PROP_GROUP_CONTROLLABLE:
        {
            summonResult = DoSummonPossessed(summonPositions, summon_prop, eff_idx, level);
            break;
        }
        default:
            sLog.outError("EffectSummonType: Unhandled summon group type %u", summon_prop->Group);
            break;
    }

    if (!summonResult)
        return;                                             // No further handling required

    Creature* caster = nullptr;
    if (m_originalCaster)
    {
        if (m_originalCaster->GetTypeId() == TYPEID_UNIT)
            caster = static_cast<Creature*>(m_originalCaster);
    }
    else if (m_caster && m_caster->GetTypeId() == TYPEID_UNIT)
        caster = static_cast<Creature*>(m_caster);

    for (itr = summonPositions.begin(); itr != summonPositions.end(); ++itr)
    {
        MANGOS_ASSERT(itr->creature || itr != summonPositions.begin());
        if (!itr->creature)
        {
            sLog.outError("EffectSummonType: Expected to have %u NPCs summoned, but some failed (Spell id %u)", amount, m_spellInfo->Id);
            continue;
        }

        if (summon_prop->FactionId)
            itr->creature->setFaction(summon_prop->FactionId);
        // Else set faction to summoner's faction for pet-like summoned
        else if ((summon_prop->Flags & SUMMON_PROP_FLAG_INHERIT_FACTION) || !itr->creature->IsTemporarySummon())
            itr->creature->setFaction(petInvoker->getFaction());

        if (!itr->creature->IsTemporarySummon())
        {
            m_caster->GetMap()->Add(itr->creature);

            itr->creature->AIM_Initialize();

            // Notify original caster if not done already
            if (caster && caster->AI())
                caster->AI()->JustSummoned(itr->creature);
        }
        else if (m_originalCaster && m_originalCaster != m_caster && m_originalCaster->AI())
        {
            // original caster is provided by script so we have to notify it as its not done in Object::SummonCreature
            m_originalCaster->AI()->JustSummoned(itr->creature);
        }

        OnSummon(itr->creature);

        m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON), itr->creature->GetPackGUID());
    }
}

bool Spell::DoSummonPet(SpellEffectIndex eff_idx)
{
    if (m_caster->GetPetGuid())
        return false;

    uint32 pet_entry = m_spellInfo->EffectMiscValue[eff_idx];
    if (!pet_entry)
        return false;

    Pet* spawnCreature = new Pet();

    Player* _player = nullptr;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        _player = static_cast<Player*>(m_caster);

        // Load pet from db; if any to load
        if (m_caster->getClass() != CLASS_PRIEST
                && spawnCreature->LoadPetFromDB(_player, pet_entry))
        {
            spawnCreature->SetHealth(spawnCreature->GetMaxHealth());
            spawnCreature->SetPower(POWER_MANA, spawnCreature->GetMaxPower(POWER_MANA));

            // set timer for unsummon
            if (m_duration > 0)
                spawnCreature->SetDuration(m_duration);

            spawnCreature->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
            OnSummon(spawnCreature);
            m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON), spawnCreature->GetPackGUID());
            return true;
        }

        spawnCreature->setPetType(SUMMON_PET);
    }
    else
        spawnCreature->setPetType(GUARDIAN_PET);

    CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(pet_entry);
    if (!cInfo)
    {
        sLog.outErrorDb("Spell::DoSummon: creature entry %u not found for spell %u.", pet_entry, m_spellInfo->Id);
        delete spawnCreature;
        return false;
    }

    // Summon in dest location
    CreatureCreatePos pos(m_caster->GetMap(), m_targets.m_destPos.x, m_targets.m_destPos.y, m_targets.m_destPos.z, -m_caster->GetOrientation());

    if (!(m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION))
    {
        float px, py, pz;
        m_caster->GetClosePoint(px, py, pz, 2.0f);
        pos = CreatureCreatePos(m_caster->GetMap(), px, py, pz, -m_caster->GetOrientation());
    }

    Map* map = m_caster->GetMap();
    uint32 pet_number = sObjectMgr.GeneratePetNumber();
    if (!spawnCreature->Create(map->GenerateLocalLowGuid(HIGHGUID_PET), pos, cInfo, pet_number))
    {
        sLog.outErrorDb("Spell::EffectSummon: can't create creature with entry %u for spell %u", cInfo->Entry, m_spellInfo->Id);
        delete spawnCreature;
        return false;
    }

    spawnCreature->SetLoading(true);

    // Level of pet summoned
    uint32 level = std::max(m_caster->getLevel() + m_spellInfo->EffectMultipleValue[eff_idx], 1.0f);

    spawnCreature->SetRespawnCoord(pos);

    // set timer for unsummon
    if (m_duration > 0)
        spawnCreature->SetDuration(m_duration);

    spawnCreature->SetOwnerGuid(m_caster->GetObjectGuid());
    spawnCreature->SetUInt32Value(UNIT_FIELD_FLAGS, cInfo->UnitFlags);
    spawnCreature->SetUInt32Value(UNIT_NPC_FLAGS, cInfo->NpcFlags);
    spawnCreature->setFaction(m_caster->getFaction());
    spawnCreature->SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, 0);
    spawnCreature->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    spawnCreature->SetCanModifyStats(true);
    spawnCreature->InitStatsForLevel(level);

    if (CharmInfo* charmInfo = spawnCreature->GetCharmInfo())
        charmInfo->SetPetNumber(pet_number, (m_caster->GetTypeId() == TYPEID_PLAYER && spawnCreature->isControlled()));

    // spawnCreature->SetName("");                          // generated by client

    if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        spawnCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        spawnCreature->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
    }
    else
        spawnCreature->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

    if (spawnCreature->getPetType() == GUARDIAN_PET)
        m_caster->AddGuardian(spawnCreature);
    else
        m_caster->SetPet(spawnCreature);

    if (m_caster->IsImmuneToNPC())
        spawnCreature->SetImmuneToNPC(true);

    if (m_caster->IsImmuneToPlayer())
        spawnCreature->SetImmuneToPlayer(true);

    if (m_caster->IsPvP())
        spawnCreature->SetPvP(true);

    map->Add((Creature*)spawnCreature);
    spawnCreature->AIM_Initialize();
    spawnCreature->AI()->SetReactState(REACT_DEFENSIVE);
    spawnCreature->InitPetCreateSpells();

    if (_player)
    {
        _player->PetSpellInitialize();
        if (m_caster->getClass() != CLASS_PRIEST)
            spawnCreature->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
    }
    spawnCreature->SetLoading(false);

    // Notify original caster if not done already
    if (m_caster->AI())
        m_caster->AI()->JustSummoned(spawnCreature);

    OnSummon(spawnCreature);

    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON), spawnCreature->GetPackGUID());
    return true;
}

void Spell::EffectLearnSpell(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
    {
        if (m_caster->GetTypeId() == TYPEID_PLAYER)
            EffectLearnPetSpell(eff_idx);

        return;
    }

    Player* player = (Player*)unitTarget;

    uint32 spellToLearn = (m_spellInfo->Id == SPELL_ID_GENERIC_LEARN) ? damage : m_spellInfo->EffectTriggerSpell[eff_idx];
    player->learnSpell(spellToLearn, false);

    if (WorldObject const* caster = GetCastingObject())
        DEBUG_LOG("Spell: %s has learned spell %u from %s", player->GetGuidStr().c_str(), spellToLearn, caster->GetGuidStr().c_str());
}

void Spell::EffectDispel(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    // Fill possible dispel list
    std::list <std::pair<SpellAuraHolder*, uint32> > dispelList;

    // Create dispel mask by dispel type
    uint32 dispelMask  = GetDispellMask(DispelType(m_spellInfo->EffectMiscValue[eff_idx]));
    Unit::SpellAuraHolderMap const& auras = unitTarget->GetSpellAuraHolderMap();
    for (Unit::SpellAuraHolderMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
    {
        SpellAuraHolder* holder = itr->second;
        if ((1 << holder->GetSpellProto()->Dispel) & dispelMask)
        {
            if (holder->GetSpellProto()->Dispel == DISPEL_MAGIC)
            {
                // do not remove positive auras if friendly target
                //               negative auras if non-friendly target
                if (holder->IsPositive() == m_caster->CanAssistSpell(unitTarget, m_spellInfo))
                    continue;
            }
            dispelList.push_back(std::pair<SpellAuraHolder*, uint32>(holder, holder->GetStackAmount()));
        }
    }
    std::list<std::pair<SpellAuraHolder*, uint32> > successList;
    std::list <uint32> failList;
    ProcessDispelList(dispelList, successList, failList);
    EvaluateResultLists(successList, failList);
}

void Spell::EffectDispelMechanic(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    uint32 mechanic = m_spellInfo->EffectMiscValue[eff_idx];

    // Fill possible dispel list
    std::list <std::pair<SpellAuraHolder*, uint32> > dispelList;

    Unit::SpellAuraHolderMap& Auras = unitTarget->GetSpellAuraHolderMap();
    for (Unit::SpellAuraHolderMap::iterator iter = Auras.begin(); iter != Auras.end(); ++iter)
    {
        SpellEntry const* spell = iter->second->GetSpellProto();
        if (iter->second->HasMechanic(mechanic))
            dispelList.push_back(std::pair<SpellAuraHolder*, uint32>(iter->second, iter->second->GetStackAmount()));
    }
    std::list<std::pair<SpellAuraHolder*, uint32> > successList;
    std::list <uint32> failList;
    ProcessDispelList(dispelList, successList, failList);
    EvaluateResultLists(successList, failList);
}

void Spell::ProcessDispelList(std::list <std::pair<SpellAuraHolder*, uint32> >& dispelList, std::list<std::pair<SpellAuraHolder*, uint32> >& successList, std::list <uint32>& failList)
{
    // Ok if exist some buffs for dispel try dispel it
    if (!dispelList.empty())
    {
        // some spells have effect value = 0 and all from its by meaning expect 1
        if (!damage)
            damage = 1;

        // Dispel N = damage buffs (or while exist buffs for dispel)
        for (int32 count = 0; count < damage && !dispelList.empty(); ++count)
        {
            // Random select buff for dispel
            std::list<std::pair<SpellAuraHolder*, uint32> >::iterator dispel_itr = dispelList.begin();
            std::advance(dispel_itr, urand(0, dispelList.size() - 1));

            SpellAuraHolder* holder = dispel_itr->first;

            dispel_itr->second -= 1;

            // remove entry from dispel_list if nothing left in stack
            if (dispel_itr->second == 0)
                dispelList.erase(dispel_itr);

            SpellEntry const* spellInfo = holder->GetSpellProto();
            // Base dispel chance
            // TODO: possible chance depend from spell level??
            int32 miss_chance = 0;
            // Apply dispel mod from aura caster
            if (Unit* caster = holder->GetCaster())
            {
                if (Player* modOwner = caster->GetSpellModOwner())
                    modOwner->ApplySpellMod(spellInfo->Id, SPELLMOD_RESIST_DISPEL_CHANCE, miss_chance, this);
                miss_chance += caster->GetTotalAuraModifier(SPELL_AURA_MOD_DISPEL_RESIST);
            }
            // Try dispel
            if (roll_chance_i(miss_chance))
                failList.push_back(spellInfo->Id);
            else
            {
                bool foundDispelled = false;
                for (std::list<std::pair<SpellAuraHolder*, uint32> >::iterator success_iter = successList.begin(); success_iter != successList.end(); ++success_iter)
                {
                    if (success_iter->first->GetId() == holder->GetId() && success_iter->first->GetCasterGuid() == holder->GetCasterGuid())
                    {
                        success_iter->second += 1;
                        foundDispelled = true;
                        break;
                    }
                }
                if (!foundDispelled)
                    successList.push_back(std::pair<SpellAuraHolder*, uint32>(holder, 1));
            }
        }
    }
}

void Spell::EvaluateResultLists(std::list<std::pair<SpellAuraHolder*, uint32> >& successList, std::list <uint32>& failList)
{
    // Send success log and really remove auras
    if (!successList.empty())
    {
        int32 count = successList.size();
        WorldPacket data(SMSG_SPELLDISPELLOG, 8 + 8 + 4 + 1 + 4 + count * 5);
        data << unitTarget->GetPackGUID();              // Victim GUID
        data << m_caster->GetPackGUID();                // Caster GUID
        data << uint32(m_spellInfo->Id);                // Dispel spell id
        data << uint8(0);                               // not used
        data << uint32(count);                          // count
        for (std::list<std::pair<SpellAuraHolder*, uint32> >::iterator j = successList.begin(); j != successList.end(); ++j)
        {
            SpellAuraHolder* dispelledHolder = j->first;
            data << uint32(dispelledHolder->GetId());   // Spell Id
            data << uint8(0);                           // 0 - dispelled !=0 cleansed
            unitTarget->RemoveAuraHolderDueToSpellByDispel(dispelledHolder->GetId(), m_spellInfo->Id, j->second, dispelledHolder->GetCasterGuid(), m_caster);
        }
        m_caster->SendMessageToSet(data, true);

        // On success dispel
        // Devour Magic
        if (m_spellInfo->SpellFamilyName == SPELLFAMILY_WARLOCK && m_spellInfo->Category == SPELLCATEGORY_DEVOUR_MAGIC)
        {
            uint32 heal_spell = 0;
            switch (m_spellInfo->Id)
            {
                case 19505: heal_spell = 19658; break;
                case 19731: heal_spell = 19732; break;
                case 19734: heal_spell = 19733; break;
                case 19736: heal_spell = 19735; break;
                case 27276: heal_spell = 27278; break;
                case 27277: heal_spell = 27279; break;
                default:
                    DEBUG_LOG("Spell for Devour Magic %d not handled in Spell::EffectDispel", m_spellInfo->Id);
                    break;
            }
            if (heal_spell)
                m_caster->CastSpell(m_caster, heal_spell, TRIGGERED_OLD_TRIGGERED);
        }
    }
    // Send fail log to client
    if (!failList.empty())
    {
        // Failed to dispel
        WorldPacket data(SMSG_DISPEL_FAILED, 8 + 8 + 4 + 4 * failList.size());
        data << m_caster->GetObjectGuid();              // Caster GUID
        data << unitTarget->GetObjectGuid();            // Victim GUID
        data << uint32(m_spellInfo->Id);                // Dispel spell id
        for (std::list< uint32 >::iterator j = failList.begin(); j != failList.end(); ++j)
            data << uint32(*j);                         // Spell Id
        m_caster->SendMessageToSet(data, true);
    }
}

void Spell::EffectDualWield(SpellEffectIndex /*eff_idx*/)
{
    if (unitTarget)
        unitTarget->SetCanDualWield(true);
}

void Spell::EffectPull(SpellEffectIndex /*eff_idx*/)
{
    // TODO: create a proper pull towards distract spell center for distract
    DEBUG_LOG("WORLD: Spell Effect DUMMY");
}

void Spell::EffectDistract(SpellEffectIndex /*eff_idx*/)
{
    // Check for possible target
    if (!unitTarget || unitTarget->IsInCombat())
        return;

    // target must be OK to do this
    if (unitTarget->hasUnitState(UNIT_STAT_CAN_NOT_REACT))
        return;

    unitTarget->clearUnitState(UNIT_STAT_MOVING);

    if (unitTarget->GetTypeId() == TYPEID_UNIT)
        unitTarget->GetMotionMaster()->MoveDistract(damage * IN_MILLISECONDS);

    float orientation = unitTarget->GetAngle(m_targets.m_destPos.x, m_targets.m_destPos.y);
    unitTarget->SetFacingTo(orientation);
    // This is needed to change the facing server side as well (and it must be after the MoveDistract call)
    unitTarget->SetOrientation(orientation);
}

void Spell::EffectPickPocket(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    // victim must be creature and attackable
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || !m_caster->CanAttackNow(unitTarget))
        return;

    Creature* creatureTarget = static_cast<Creature*>(unitTarget);
    Player* playerCaster = static_cast<Player*>(m_caster);

    int chance = 5; //base failure chance is 5%

    //TODO investigate if font pickpocketing has higher failure chance then from behind
    //if (m_caster->IsFacingTargetsFront(unitTarget))
    //    chance *= 4; //base chance is 20% from the front

    int casterLevel = int32(m_caster->getLevel());
    int targetLevel = int32(unitTarget->getLevel());

    //we need to increase the base chance for failure if target is higher level then caster
    //incremental chance to fail based on level. maximum is 97% chance if level difference is dramatic (give it 3% chance to succeed?).
    if (targetLevel > casterLevel)
        chance = int32(std::min(int32(std::floor(((targetLevel - casterLevel) * 2.0) + 0.5) * chance), 97));

    int result = urand() % 100;

    if (result >= chance)
    {
        // Stealing successful
        //BASIC_LOG("Successfull pickpocket result %i for chance %i", result, chance);

        Loot*& loot = unitTarget->m_loot;
        if (!loot)
            loot = new Loot(playerCaster, creatureTarget, LOOT_PICKPOCKETING);
        else
        {
            if (loot->GetLootType() == LOOT_PICKPOCKETING)
            {
                if (creatureTarget->GetLootStatus() == CREATURE_LOOT_STATUS_PICKPOCKETED)
                {
                    if (creatureTarget->CanRestockPickpocketLoot())
                    {
                        // refill pickpocket
                        delete loot;
                        loot = new Loot(playerCaster, creatureTarget, LOOT_PICKPOCKETING);
                        creatureTarget->SetLootStatus(CREATURE_LOOT_STATUS_NONE, true);
                    }
                    else
                    {
                        playerCaster->SendLootError(unitTarget->GetObjectGuid(), LOOT_ERROR_ALREADY_PICKPOCKETED);
                        return;
                    }
                } // else not fully taken
            }
            else
            {
                delete loot;
                loot = new Loot(playerCaster, creatureTarget, LOOT_PICKPOCKETING);
            }
        }
        loot->ShowContentTo(playerCaster);
    }
    else
    {
        //BASIC_LOG("Failed pickpocket result %i for chance %i", result, chance);

        // Reveal action + get attack
        m_caster->RemoveAurasWithInterruptFlags(AURA_INTERRUPT_FLAG_TALK);
        unitTarget->AttackedBy(m_caster);
    }
}

void Spell::EffectAddFarsight(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    DynamicObject* dynObj = new DynamicObject;

    // set radius to 0: spell not expected to work as persistent aura
    if (!dynObj->Create(m_caster->GetMap()->GenerateLocalLowGuid(HIGHGUID_DYNAMICOBJECT), m_caster,
                        m_spellInfo->Id, eff_idx, m_targets.m_destPos.x, m_targets.m_destPos.y, m_targets.m_destPos.z, m_duration, 0, DYNAMIC_OBJECT_FARSIGHT_FOCUS, TARGET_NONE, damage, m_currentBasePoints[eff_idx]))
    {
        delete dynObj;
        return;
    }

    m_caster->AddDynObject(dynObj);
    m_caster->GetMap()->Add(dynObj);

    ((Player*)m_caster)->GetCamera().SetView(dynObj);
}

bool Spell::DoSummonWild(CreatureSummonPositions& list, SummonPropertiesEntry const* /*prop*/, SpellEffectIndex effIdx, uint32 level)
{
    uint32 creature_entry = m_spellInfo->EffectMiscValue[effIdx];
    CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature_entry);
    if (!cInfo)
    {
        sLog.outErrorDb("Spell::DoSummonWild: creature entry %u not found for spell %u.", creature_entry, m_spellInfo->Id);
        return false;
    }

    TempSpawnType summonType = (m_duration == 0) ? TEMPSPAWN_DEAD_DESPAWN : TEMPSPAWN_TIMED_OR_DEAD_DESPAWN;

    for (CreatureSummonPositions::iterator itr = list.begin(); itr != list.end(); ++itr)
        if (Creature* summon = WorldObject::SummonCreature(TempSpawnSettings(m_caster, creature_entry, itr->x, itr->y, itr->z, m_caster->GetOrientation(), summonType, m_duration, false,
                IsSpellSetRun(m_spellInfo), 0, 0, false, false, m_spellInfo->Id), m_caster->GetMap()))
        {
            itr->creature = summon;

            switch(m_spellInfo->Id)
            {
                case 1122: // Warlock Infernal - requires custom code - generalized in WOTLK
                {
                    summon->SelectLevel(level); // needs to have casters level
                    // Enslave demon effect, without mana cost and cooldown
                    summon->CastSpell(nullptr, 22707, TRIGGERED_OLD_TRIGGERED);  // short root spell on infernal from sniffs
                    m_caster->CastSpell(summon, 20882, TRIGGERED_OLD_TRIGGERED);
                    summon->CastSpell(nullptr, 22699, TRIGGERED_NONE);  // Inferno effect
                    summon->CastSpell(itr->x, itr->y, itr->z, 20310, TRIGGERED_NONE);  // Stun
                    summon->AI()->DoCastSpellIfCan(nullptr, 19483, CAST_TRIGGERED | CAST_AURA_NOT_PRESENT);
                    break;
                }
            }
        }
        else
            return false;

    return true;
}

bool Spell::DoSummonGuardian(CreatureSummonPositions& list, SummonPropertiesEntry const* prop, SpellEffectIndex effIdx, uint32 level)
{
    MANGOS_ASSERT(!list.empty() && prop);

    uint32 pet_entry = m_spellInfo->EffectMiscValue[effIdx];
    CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(pet_entry);
    if (!cInfo)
    {
        sLog.outErrorDb("Spell::DoSummonGuardian: creature entry %u not found for spell %u.", pet_entry, m_spellInfo->Id);
        return false;
    }

    PetType petType = GUARDIAN_PET;

    // second direct cast unsummon guardian(s) (guardians without like functionality have cooldown > spawn time)
    if (!m_IsTriggeredSpell && m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        bool found = false;
        // including protector
        while (Pet* old_summon = m_caster->FindGuardianWithEntry(pet_entry))
        {
            old_summon->Unsummon(PET_SAVE_AS_DELETED, m_caster);
            found = true;
        }

        if (found && !(m_spellInfo->DurationIndex && m_spellInfo->Category))
            return false;
    }

    // in another case summon new
    for (CreatureSummonPositions::iterator itr = list.begin(); itr != list.end(); ++itr)
    {
        Pet* spawnCreature = new Pet(petType);

        CreatureCreatePos pos(m_caster->GetMap(), itr->x, itr->y, itr->z, -m_caster->GetOrientation());

        uint32 pet_number = sObjectMgr.GeneratePetNumber();
        if (!spawnCreature->Create(m_caster->GetMap()->GenerateLocalLowGuid(HIGHGUID_PET), pos, cInfo, pet_number))
        {
            sLog.outError("Spell::DoSummonGuardian: can't create creature entry %u for spell %u.", pet_entry, m_spellInfo->Id);
            delete spawnCreature;
            return false;
        }

        spawnCreature->SetLoading(true);

        itr->creature = spawnCreature;

        spawnCreature->SetRespawnCoord(pos);

        if (m_duration > 0)
            spawnCreature->SetDuration(m_duration);

        CreatureInfo const* cInfo = spawnCreature->GetCreatureInfo();

        // spawnCreature->SetName("");                      // generated by client
        spawnCreature->SetOwnerGuid(m_caster->GetObjectGuid());
        spawnCreature->SetUInt32Value(UNIT_FIELD_FLAGS, cInfo->UnitFlags);
        spawnCreature->SetUInt32Value(UNIT_NPC_FLAGS, cInfo->NpcFlags);
        spawnCreature->setFaction(m_caster->getFaction());
        spawnCreature->SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, 0);
        spawnCreature->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

        spawnCreature->SetCanModifyStats(true);
        spawnCreature->InitStatsForLevel(level);

        if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
        {
            spawnCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
            spawnCreature->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
        }
        else
            spawnCreature->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

        if (m_caster->IsImmuneToNPC())
            spawnCreature->SetImmuneToNPC(true);

        if (m_caster->IsImmuneToPlayer())
            spawnCreature->SetImmuneToPlayer(true);

        if (m_caster->IsPvP())
            spawnCreature->SetPvP(true);

        if (CharmInfo* charmInfo = spawnCreature->GetCharmInfo())
            charmInfo->SetPetNumber(pet_number, false);

        spawnCreature->SetLoading(false);
        m_caster->AddGuardian(spawnCreature);
    }

    return true;
}


void Spell::EffectTeleUnitsFaceCaster(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    if (unitTarget->IsTaxiFlying())
        return;

    float x, y, z;
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(x, y, z);
    else
        return;

    unitTarget->NearTeleportTo(x, y, z, -m_caster->GetOrientation(), unitTarget == m_caster);
}

void Spell::EffectLearnSkill(SpellEffectIndex eff_idx)
{
    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    if (damage < 0)
        return;

    Player* target = static_cast<Player*>(unitTarget);

    uint16 skillid =  uint16(m_spellInfo->EffectMiscValue[eff_idx]);
    uint16 step = uint16(damage);
    target->SetSkillStep(skillid, step);

    if (WorldObject const* caster = GetCastingObject())
        DEBUG_LOG("Spell: %s teaches %s skill %u (to step %u)", caster->GetGuidStr().c_str(), target->GetGuidStr().c_str(), skillid, step);
}

void Spell::EffectAddHonor(SpellEffectIndex /*eff_idx*/)
{
    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    // 2.4.3 honor-spells don't scale with level and won't be casted by an item
    // also we must use damage+1 (spelldescription says +25 honor but damage is only 24)
    ((Player*)unitTarget)->RewardHonor(nullptr, 1, float(damage + 1));
    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "SpellEffect::AddHonor (spell_id %u) rewards %u honor points (non scale) for player: %u", m_spellInfo->Id, damage, ((Player*)unitTarget)->GetGUIDLow());
}

void Spell::EffectSpawn(SpellEffectIndex /*eff_idx*/)
{
    switch (m_spellInfo->Id)
    {
        case 15750: // Rookery Whelp Spawn-in Spell
        case 26262: // Birth
        case 34115:
            m_caster->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            break;
    }
}

void Spell::EffectTradeSkill(SpellEffectIndex /*eff_idx*/)
{
    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    // uint32 skillid =  m_spellInfo->EffectMiscValue[i];
    // uint16 skillmax = ((Player*)unitTarget)->(skillid);
    // ((Player*)unitTarget)->SetSkill(skillid,skillval?skillval:1,skillmax+75);
}

void Spell::EffectEnchantItemPerm(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!itemTarget)
        return;

    Player* p_caster = (Player*)m_caster;

    // not grow at item use at item case
    p_caster->UpdateCraftSkill(m_spellInfo->Id);

    uint32 enchant_id = m_spellInfo->EffectMiscValue[eff_idx];
    if (!enchant_id)
        return;

    SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
    if (!pEnchant)
        return;

    // item can be in trade slot and have owner diff. from caster
    Player* item_owner = itemTarget->GetOwner();
    if (!item_owner)
        return;

    if (item_owner != p_caster && p_caster->GetSession()->GetSecurity() > SEC_PLAYER && sWorld.getConfig(CONFIG_BOOL_GM_LOG_TRADE))
    {
        sLog.outCommand(p_caster->GetSession()->GetAccountId(), "GM %s (Account: %u) enchanting(perm): %s (Entry: %d) for player: %s (Account: %u)",
                        p_caster->GetName(), p_caster->GetSession()->GetAccountId(),
                        itemTarget->GetProto()->Name1, itemTarget->GetEntry(),
                        item_owner->GetName(), item_owner->GetSession()->GetAccountId());
    }

    // remove old enchanting before applying new if equipped
    item_owner->ApplyEnchantment(itemTarget, PERM_ENCHANTMENT_SLOT, false);

    itemTarget->SetEnchantment(PERM_ENCHANTMENT_SLOT, enchant_id, 0, 0, m_caster->GetObjectGuid());

    // add new enchanting if equipped
    item_owner->ApplyEnchantment(itemTarget, PERM_ENCHANTMENT_SLOT, true);
}

void Spell::EffectEnchantItemTmp(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!itemTarget)
        return;

    Player* p_caster = (Player*)m_caster;

    uint32 enchant_id = m_spellInfo->EffectMiscValue[eff_idx];

    // Shaman Rockbiter Weapon
    if (eff_idx == EFFECT_INDEX_0 && m_spellInfo->Effect[EFFECT_INDEX_1] == SPELL_EFFECT_DUMMY)
    {
        int32 enchanting_damage = m_currentBasePoints[EFFECT_INDEX_1];

        // enchanting id selected by calculated damage-per-sec stored in Effect[1] base value
        // with already applied percent bonus from Elemental Weapons talent
        // Note: damage calculated (correctly) with rounding int32(float(v)) but
        // RW enchantments applied damage int32(float(v)+0.5), this create  0..1 difference sometime
        switch (enchanting_damage)
        {
            // Rank 1
            case  2: enchant_id =   29; break;              //  0% [ 7% ==  2, 14% == 2, 20% == 2]
            // Rank 2
            case  4: enchant_id =    6; break;              //  0% [ 7% ==  4, 14% == 4]
            case  5: enchant_id = 3025; break;              // 20%
            // Rank 3
            case  6: enchant_id =    1; break;              //  0% [ 7% ==  6, 14% == 6]
            case  7: enchant_id = 3027; break;              // 20%
            // Rank 4
            case  9: enchant_id = 3032; break;              //  0% [ 7% ==  6]
            case 10: enchant_id =  503; break;              // 14%
            case 11: enchant_id = 3031; break;              // 20%
            // Rank 5
            case 15: enchant_id = 3035; break;              // 0%
            case 16: enchant_id = 1663; break;              // 7%
            case 17: enchant_id = 3033; break;              // 14%
            case 18: enchant_id = 3034; break;              // 20%
            // Rank 6
            case 28: enchant_id = 3038; break;              // 0%
            case 29: enchant_id =  683; break;              // 7%
            case 31: enchant_id = 3036; break;              // 14%
            case 33: enchant_id = 3037; break;              // 20%
            // Rank 7
            case 40: enchant_id = 3041; break;              // 0%
            case 42: enchant_id = 1664; break;              // 7%
            case 45: enchant_id = 3039; break;              // 14%
            case 48: enchant_id = 3040; break;              // 20%
            // Rank 8
            case 49: enchant_id = 3044; break;              // 0%
            case 52: enchant_id = 2632; break;              // 7%
            case 55: enchant_id = 3042; break;              // 14%
            case 58: enchant_id = 3043; break;              // 20%
            // Rank 9
            case 62: enchant_id = 2633; break;              // 0%
            case 66: enchant_id = 3018; break;              // 7%
            case 70: enchant_id = 3019; break;              // 14%
            case 74: enchant_id = 3020; break;              // 20%
            default:
                sLog.outError("Spell::EffectEnchantItemTmp: Damage %u not handled in S'RW", enchanting_damage);
                return;
        }
    }

    if (!enchant_id)
    {
        sLog.outError("Spell %u Effect %u (SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY) have 0 as enchanting id", m_spellInfo->Id, eff_idx);
        return;
    }

    SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
    if (!pEnchant)
    {
        sLog.outError("Spell %u Effect %u (SPELL_EFFECT_ENCHANT_ITEM_TEMPORARY) have nonexistent enchanting id %u ", m_spellInfo->Id, eff_idx, enchant_id);
        return;
    }

    // select enchantment duration
    uint32 duration;

    // rogue family enchantments exception by duration
    if (m_spellInfo->Id == 38615)
        duration = 1800;                                    // 30 mins
    // other rogue family enchantments always 1 hour (some have spell damage=0, but some have wrong data in EffBasePoints)
    else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_ROGUE)
        duration = 3600;                                    // 1 hour
    // shaman family enchantments
    else if (m_spellInfo->SpellFamilyName == SPELLFAMILY_SHAMAN)
        duration = 1800;                                    // 30 mins
    // other cases with this SpellVisual already selected
    else if (m_spellInfo->SpellVisual == 215)
        duration = 1800;                                    // 30 mins
    // some fishing pole bonuses
    else if (m_spellInfo->SpellVisual == 563)
        duration = 600;                                     // 10 mins
    // shaman rockbiter enchantments
    else if (m_spellInfo->SpellVisual == 0)
        duration = 1800;                                    // 30 mins
    else if (m_spellInfo->Id == 29702)
        duration = 300;                                     // 5 mins
    else if (m_spellInfo->Id == 37360)
        duration = 300;                                     // 5 mins
    // default case
    else
        duration = 3600;                                    // 1 hour

    // item can be in trade slot and have owner diff. from caster
    Player* item_owner = itemTarget->GetOwner();
    if (!item_owner)
        return;

    if (item_owner != p_caster && p_caster->GetSession()->GetSecurity() > SEC_PLAYER && sWorld.getConfig(CONFIG_BOOL_GM_LOG_TRADE))
    {
        sLog.outCommand(p_caster->GetSession()->GetAccountId(), "GM %s (Account: %u) enchanting(temp): %s (Entry: %d) for player: %s (Account: %u)",
                        p_caster->GetName(), p_caster->GetSession()->GetAccountId(),
                        itemTarget->GetProto()->Name1, itemTarget->GetEntry(),
                        item_owner->GetName(), item_owner->GetSession()->GetAccountId());
    }

    // remove old enchanting before applying new if equipped
    item_owner->ApplyEnchantment(itemTarget, TEMP_ENCHANTMENT_SLOT, false);

    itemTarget->SetEnchantment(TEMP_ENCHANTMENT_SLOT, enchant_id, duration * 1000, 0, m_caster->GetObjectGuid());

    // add new enchanting if equipped
    item_owner->ApplyEnchantment(itemTarget, TEMP_ENCHANTMENT_SLOT, true);
}

void Spell::EffectTameCreature(SpellEffectIndex /*eff_idx*/)
{
    // Caster must be player, checked in Spell::CheckCast
    // Spell can be triggered, we need to check original caster prior to caster
    Player* plr = static_cast<Player*>(GetAffectiveCaster());

    Creature* creatureTarget = static_cast<Creature*>(unitTarget);

    // cast finish successfully
    // SendChannelUpdate(0);
    finish();

    Pet* pet = new Pet(HUNTER_PET);

    if (!pet->CreateBaseAtCreature(creatureTarget))
    {
        delete pet;
        return;
    }

    pet->SetLoading(true);
    pet->SetOwnerGuid(plr->GetObjectGuid());
    pet->setFaction(plr->getFaction());
    pet->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    if (plr->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        pet->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        pet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
    }
    else
        pet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

    if (plr->IsImmuneToNPC())
        pet->SetImmuneToNPC(true);

    if (plr->IsImmuneToPlayer())
        pet->SetImmuneToPlayer(true);

    if (plr->IsPvP())
        pet->SetPvP(true);

    pet->GetCharmInfo()->SetPetNumber(sObjectMgr.GeneratePetNumber(), true);

    uint32 level = creatureTarget->getLevel();
    pet->SetCanModifyStats(true);
    pet->InitStatsForLevel(level);

    pet->SetHealthPercent(creatureTarget->GetHealthPercent());

    // destroy creature object
    creatureTarget->ForcedDespawn();

    // prepare visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, level - 1);

    // add pet object to the world
    pet->GetMap()->Add((Creature*)pet);
    pet->AIM_Initialize();

    pet->AI()->SetReactState(REACT_DEFENSIVE);

    // visual effect for levelup
    pet->SetUInt32Value(UNIT_FIELD_LEVEL, level);

    // enable rename and abandon prompt
    pet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
    pet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_ABANDONED);

    // this enables pet details window (Shift+P)
    pet->InitPetCreateSpells();

    pet->LearnPetPassives();
    pet->CastPetAuras(true);
    pet->CastOwnerTalentAuras();
    pet->UpdateAllStats();

    pet->SetRequiredXpForNextLoyaltyLevel();

    // caster have pet now
    plr->SetPet(pet);

    plr->PetSpellInitialize();
    pet->SetLoading(false);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT, plr);
}

void Spell::EffectSummonPet(SpellEffectIndex eff_idx)
{
    uint32 petentry = m_spellInfo->EffectMiscValue[eff_idx];

    Pet* NewSummon = new Pet;

    Player* _player = nullptr;

    if (m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        _player = static_cast<Player*>(m_caster);

        switch (m_caster->getClass())
        {
            case CLASS_HUNTER:
            {
                if (NewSummon->LoadPetFromDB(_player))
                {
                    OnSummon(NewSummon);
                    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON_PET), NewSummon->GetPackGUID());
                }
                else
                    delete NewSummon;
                return;
            }
            case CLASS_WARLOCK:
            {
                // Remove Demonic Sacrifice auras (known pet)
                if (Aura* aura = m_caster->GetOverrideScript(2228))
                    m_caster->RemoveAurasDueToSpell(aura->GetId());
            }
            default:
            {
                if (Pet* OldSummon = m_caster->GetPet())
                    OldSummon->Unsummon(PET_SAVE_NOT_IN_SLOT, m_caster);

                // Load pet from db; if any to load
                if (NewSummon->LoadPetFromDB((Player*)m_caster, petentry))
                {
                    NewSummon->SetHealth(NewSummon->GetMaxHealth());
                    NewSummon->SetPower(POWER_MANA, NewSummon->GetMaxPower(POWER_MANA));
                    OnSummon(NewSummon);
                    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON_PET), NewSummon->GetPackGUID());
                    return;
                }

                NewSummon->setPetType(SUMMON_PET);
            }
        }
    }
    else
        NewSummon->setPetType(GUARDIAN_PET);

    CreatureInfo const* cInfo = petentry ? ObjectMgr::GetCreatureTemplate(petentry) : nullptr;
    if (!cInfo)
    {
        sLog.outErrorDb("EffectSummonPet: creature entry %u not found for spell %u.", petentry, m_spellInfo->Id);
        delete NewSummon;
        return;
    }

    float px, py, pz;
    m_caster->GetClosePoint(px, py, pz, 2.0f);
    CreatureCreatePos pos(m_caster->GetMap(), px, py, pz, -m_caster->GetOrientation());

    Map* map = m_caster->GetMap();
    uint32 pet_number = sObjectMgr.GeneratePetNumber();
    if (!NewSummon->Create(map->GenerateLocalLowGuid(HIGHGUID_PET), pos, cInfo, pet_number))
    {
        delete NewSummon;
        return;
    }

    NewSummon->SetRespawnCoord(pos);

    // Level of pet summoned
    uint32 level = std::max(m_caster->getLevel() + m_spellInfo->EffectMultipleValue[eff_idx], 1.0f);

    NewSummon->SetOwnerGuid(m_caster->GetObjectGuid());
    NewSummon->setFaction(m_caster->getFaction());
    NewSummon->SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, uint32(time(nullptr)));
    NewSummon->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    NewSummon->SetCanModifyStats(true);
    NewSummon->InitStatsForLevel(level);
    NewSummon->InitPetCreateSpells();

    if (NewSummon->getPetType() == GUARDIAN_PET)
        m_caster->AddGuardian(NewSummon);
    else
        m_caster->SetPet(NewSummon);

    if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        NewSummon->SetUInt32Value(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        NewSummon->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
        NewSummon->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
    }
    else
    {
        NewSummon->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);
        NewSummon->SetFlag(UNIT_FIELD_FLAGS, cInfo->UnitFlags);
        NewSummon->SetUInt32Value(UNIT_NPC_FLAGS, cInfo->NpcFlags);
    }

    if (m_caster->IsImmuneToNPC())
        NewSummon->SetImmuneToNPC(true);

    if (m_caster->IsImmuneToPlayer())
        NewSummon->SetImmuneToPlayer(true);

    if (m_caster->IsPvP())
        NewSummon->SetPvP(true);

    map->Add((Creature*)NewSummon);
    NewSummon->AIM_Initialize();
    NewSummon->AI()->SetReactState(REACT_DEFENSIVE);

    if (_player)
    {
        NewSummon->GetCharmInfo()->SetPetNumber(pet_number, true);

        // generate new name for summon pet
        NewSummon->SetName(sObjectMgr.GeneratePetName(petentry));

        NewSummon->LearnPetPassives();
        NewSummon->CastPetAuras(true);
        NewSummon->CastOwnerTalentAuras();
        NewSummon->UpdateAllStats();

        NewSummon->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
        _player->PetSpellInitialize();
        NewSummon->SetLoading(false);
    }
    else
    {
        NewSummon->SetLoading(false);
        // Notify Summoner
        if (m_originalCaster && (m_originalCaster != m_caster) && (m_originalCaster->AI()))
            m_originalCaster->AI()->JustSummoned(NewSummon);
        else if (m_caster->AI())
            m_caster->AI()->JustSummoned(NewSummon);
    }

    if (GenericTransport* transport = m_caster->GetTransport())
        transport->AddPetToTransport(m_caster, NewSummon);

    OnSummon(NewSummon);

    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON_PET), NewSummon->GetPackGUID());
}

void Spell::EffectLearnPetSpell(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* _player = static_cast<Player*>(m_caster);

    Pet* pet = _player->GetPet();
    if (!pet)
        return;
    if (!pet->IsAlive())
        return;

    SpellEntry const* learn_spellproto = sSpellTemplate.LookupEntry<SpellEntry>(m_spellInfo->EffectTriggerSpell[eff_idx]);
    if (!learn_spellproto)
        return;

    pet->SetTP(pet->m_TrainingPoints - pet->GetTPForSpell(learn_spellproto->Id));
    pet->learnSpell(learn_spellproto->Id);

    pet->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
    _player->PetSpellInitialize();

    if (WorldObject const* caster = GetCastingObject())
        DEBUG_LOG("Spell: %s has learned spell %u from %s", pet->GetGuidStr().c_str(), learn_spellproto->Id, caster->GetGuidStr().c_str());
}

void Spell::EffectTaunt(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    // this effect use before aura Taunt apply for prevent taunt already attacking target
    // for spell as marked "non effective at already attacking target"
    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
    {
        if (unitTarget->GetVictim() == m_caster)
        {
            SendCastResult(SPELL_FAILED_DONT_REPORT);
            return;
        }
    }

    // Also use this effect to set the taunter's threat to the taunted creature's highest value
    if (unitTarget->CanHaveThreatList())
    {
        float addedThreat = unitTarget->getThreatManager().GetHighestThreat() - unitTarget->getThreatManager().getThreat(m_caster);
        unitTarget->getThreatManager().addThreatDirectly(m_caster, addedThreat);
        unitTarget->getThreatManager().setCurrentVictimByTarget(m_caster); // force changes the target to caster of taunt
    }
    // Units without threat lists but with AI are susceptible to attack target interference by taunt effect:
    else if (!unitTarget->CanHaveThreatList() && !unitTarget->hasUnitState(UNIT_STAT_CAN_NOT_REACT_OR_LOST_CONTROL))
    {
        if (UnitAI* ai = unitTarget->AI())
        {
            // 2.4.3+: "Passive pets will no longer attack due to AoE taunt spells."
            if (ai->HasReactState(REACT_PASSIVE) && !unitTarget->GetVictim())
            {
                if (SpellTargetInfoTable[m_spellInfo->EffectImplicitTargetA[eff_idx]].enumerator != TARGET_ENUMERATOR_SINGLE)
                    return;

                if (SpellTargetInfoTable[m_spellInfo->EffectImplicitTargetB[eff_idx]].enumerator != TARGET_ENUMERATOR_SINGLE)
                    return;
            }

            ai->AttackStart(m_caster);
        }
    }
}

void Spell::EffectWeaponDmg(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    // multiple weapon dmg effect workaround
    // execute only the last weapon damage
    // and handle all effects at once
    for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
    {
        switch (m_spellInfo->Effect[j])
        {
            case SPELL_EFFECT_WEAPON_DAMAGE:
            case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
            case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
            case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
                if (j < int(eff_idx))                       // we must calculate only at last weapon effect
                    return;
                break;
        }
    }

    // some spell specific modifiers
    bool customBonusDamagePercentMod = false;
    float bonusDamagePercentMod  = 1.0f;                    // applied to fixed effect damage bonus if set customBonusDamagePercentMod
    float weaponDamagePercentMod = 1.0f;                    // applied to weapon damage (and to fixed effect damage bonus if customBonusDamagePercentMod not set
    float totalDamagePercentMod  = 1.0f;                    // applied to final bonus+weapon damage
    bool normalized = false;

    int32 fixed_bonus = 0;
    int32 spell_bonus = 0;                                  // bonus specific for spell

    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_WARRIOR:
        {
            // Devastate
            if (m_spellInfo->SpellVisual == 671 && m_spellInfo->SpellIconID == 1508)
            {
                // Sunder Armor
                Aura* sunder = unitTarget->GetAura(SPELL_AURA_MOD_RESISTANCE, SPELLFAMILY_WARRIOR, uint64(0x0000000000004000), m_caster->GetObjectGuid());

                // 44452 unknown use
                // apply sunder armor first
                if (!sunder || sunder->GetStackAmount() < sunder->GetSpellProto()->StackAmount)
                {
                    // get highest rank of the sunder armor spell
                    const PlayerSpellMap& sp_list = ((Player*)m_caster)->GetSpellMap();
                    for (PlayerSpellMap::const_iterator itr = sp_list.begin(); itr != sp_list.end(); ++itr)
                    {
                        // only highest rank is shown in spell book, so simply check if shown in spell book
                        if (!itr->second.active || itr->second.disabled || itr->second.state == PLAYERSPELL_REMOVED)
                            continue;

                        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(itr->first);
                        if (!spellInfo)
                            continue;

                        if (spellInfo->IsFitToFamily(SPELLFAMILY_WARRIOR, uint64(0x0000000000004000)) && spellInfo->SpellIconID == 565)
                        {
                            // child sunder cant miss
                            m_caster->CastSpell(unitTarget, spellInfo, TRIGGERED_IGNORE_HIT_CALCULATION | TRIGGERED_IGNORE_GCD | TRIGGERED_IGNORE_COSTS);
                            break;
                        }
                    }

                    // Rescan sunder armor to apply all bonus effects if aura was not present.
                    if (!sunder)
                        sunder = unitTarget->GetAura(SPELL_AURA_MOD_RESISTANCE, SPELLFAMILY_WARRIOR, uint64(0x0000000000004000), m_caster->GetObjectGuid());
                }

                // Devastate bonus and sunder armor refresh, additional threat
                if (sunder)
                {
                    if (sunder->GetStackAmount() == sunder->GetSpellProto()->StackAmount)
                        sunder->GetHolder()->RefreshHolder();

                    for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
                    {
                        if (m_spellInfo->Effect[j] == SPELL_EFFECT_NORMALIZED_WEAPON_DMG)
                        {
                            fixed_bonus += (sunder->GetStackAmount() - 1) * CalculateSpellEffectValue(SpellEffectIndex(j), unitTarget);
                            break;
                        }
                    }

                    // 14 * stack
                    unitTarget->AddThreat(m_caster, 14.0f * sunder->GetStackAmount(), false, GetSpellSchoolMask(m_spellInfo), m_spellInfo);
                }
            }
            break;
        }
        case SPELLFAMILY_ROGUE:
        {
            // Ambush
            if (m_spellInfo->SpellFamilyFlags & uint64(0x00000200))
            {
                customBonusDamagePercentMod = true;
                bonusDamagePercentMod = 2.5f;               // 250%
            }
            // Mutilate (for each hand)
            else if (m_spellInfo->SpellFamilyFlags & uint64(0x600000000))
            {
                bool found = false;
                // fast check
                if (unitTarget->HasAuraState(AURA_STATE_DEADLY_POISON))
                    found = true;
                // full aura scan
                else
                {
                    Unit::SpellAuraHolderMap const& auras = unitTarget->GetSpellAuraHolderMap();
                    for (Unit::SpellAuraHolderMap::const_iterator itr = auras.begin(); itr != auras.end(); ++itr)
                    {
                        if (itr->second->GetSpellProto()->Dispel == DISPEL_POISON)
                        {
                            found = true;
                            break;
                        }
                    }
                }

                if (found)
                    totalDamagePercentMod *= 1.5f;          // 150% if poisoned
            }
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            break;
        }
        case SPELLFAMILY_SHAMAN:
        {
            // Skyshatter Harness item set bonus
            // Stormstrike
            if (m_spellInfo->SpellFamilyFlags & uint64(0x001000000000))
                if (Aura* aura = m_caster->GetOverrideScript(5634))
                    m_caster->CastSpell(nullptr, 38430, TRIGGERED_OLD_TRIGGERED, nullptr, aura);
            break;
        }
    }

    for (int j = 0; j < MAX_EFFECT_INDEX; ++j)
    {
        switch (m_spellInfo->Effect[j])
        {
            case SPELL_EFFECT_WEAPON_DAMAGE:
            case SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL:
                fixed_bonus += CalculateSpellEffectValue(SpellEffectIndex(j), unitTarget);
                break;
            case SPELL_EFFECT_NORMALIZED_WEAPON_DMG:
                fixed_bonus += CalculateSpellEffectValue(SpellEffectIndex(j), unitTarget);
                normalized = true;
                break;
            case SPELL_EFFECT_WEAPON_PERCENT_DAMAGE:
                weaponDamagePercentMod *= float(CalculateSpellEffectValue(SpellEffectIndex(j), unitTarget)) / 100.0f;

                // applied only to prev.effects fixed damage
                if (customBonusDamagePercentMod)
                    fixed_bonus = int32(fixed_bonus * bonusDamagePercentMod);
                else
                    fixed_bonus = int32(fixed_bonus * weaponDamagePercentMod);
                break;
            default:
                break;                                      // not weapon damage effect, just skip
        }
    }

    // non-weapon damage
    int32 bonus = spell_bonus + fixed_bonus;

    bool addDamage = false; // hack in place until effect handler is split up
    switch (m_spellInfo->DmgClass)
    {
        case SPELL_DAMAGE_CLASS_MELEE:
        case SPELL_DAMAGE_CLASS_RANGED: addDamage = true; break;
        case SPELL_DAMAGE_CLASS_MAGIC: break; // TODO: Add behaviour for spell behaviour
        case SPELL_DAMAGE_CLASS_NONE: break; // do nothing
    }

    if (m_spellInfo->Effect[eff_idx] == SPELL_EFFECT_WEAPON_DAMAGE_NOSCHOOL)
        addDamage = true;

    if (addDamage)
    {
        // apply to non-weapon bonus weapon total pct effect, weapon total flat effect included in weapon damage
        if (bonus)
        {
            UnitMods unitMod;
            switch (m_attackType)
            {
                default:
                case BASE_ATTACK:   unitMod = UNIT_MOD_DAMAGE_MAINHAND; break;
                case OFF_ATTACK:    unitMod = UNIT_MOD_DAMAGE_OFFHAND;  break;
                case RANGED_ATTACK: unitMod = UNIT_MOD_DAMAGE_RANGED;   break;
            }

            float weapon_total_pct = m_caster->GetModifierValue(unitMod, TOTAL_PCT);
            bonus = int32(bonus * weapon_total_pct);
        }

        // + weapon damage with applied weapon% dmg to base weapon damage in call
        bonus += int32(m_caster->CalculateDamage(m_attackType, normalized) * weaponDamagePercentMod);
    }

    // total damage
    bonus = int32(bonus * totalDamagePercentMod);

    // prevent negative damage
    m_damagePerEffect[eff_idx] = CalculateSpellEffectDamage(unitTarget, bonus);

    // Hemorrhage
    if (m_spellInfo->IsFitToFamily(SPELLFAMILY_ROGUE, uint64(0x0000000002000000)))
    {
        if (m_caster->GetTypeId() == TYPEID_PLAYER)
            m_caster->AddComboPoints(unitTarget, 1);
    }
    // Mangle (Cat): CP
    else if (m_spellInfo->IsFitToFamily(SPELLFAMILY_DRUID, uint64(0x0000040000000000)))
    {
        if (m_caster->GetTypeId() == TYPEID_PLAYER)
            m_caster->AddComboPoints(unitTarget, 1);
    }
}

void Spell::EffectThreat(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || !unitTarget->IsAlive() || !m_caster->IsAlive())
        return;

    if (!unitTarget->CanHaveThreatList())
        return;

    if (!m_caster->IsInCombat() || !unitTarget->IsInCombat())
    {
        if (unitTarget->AI())
            unitTarget->AI()->AttackStart(m_caster);
        else
            unitTarget->EngageInCombatWith(m_caster);
    }

    unitTarget->AddThreat(m_caster, float(damage), false, GetSpellSchoolMask(m_spellInfo), m_spellInfo);
}

void Spell::EffectHealMaxHealth(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    uint32 heal = m_caster->GetMaxHealth();

    m_healing += heal;
}

void Spell::EffectInterruptCast(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;
    if (!unitTarget->IsAlive())
        return;

    uint32 interruptedSpellId = 0;
    // TODO: not all spells that used this effect apply cooldown at school spells
    // also exist case: apply cooldown to interrupted cast only and to all spells
    for (uint32 i = CURRENT_FIRST_NON_MELEE_SPELL; i < CURRENT_MAX_SPELL; ++i)
    {
        if (Spell* spell = unitTarget->GetCurrentSpell(CurrentSpellTypes(i)))
        {
            SpellEntry const* curSpellInfo = spell->m_spellInfo;
            // check if we can interrupt spell
            if ((curSpellInfo->InterruptFlags & SPELL_INTERRUPT_FLAG_INTERRUPT) && curSpellInfo->PreventionType == SPELL_PREVENTION_TYPE_SILENCE)
            {
                unitTarget->LockOutSpells(GetSpellSchoolMask(curSpellInfo), GetSpellDuration(m_spellInfo));
                unitTarget->InterruptSpell(CurrentSpellTypes(i), false);
                interruptedSpellId = curSpellInfo->Id;
            }
        }
    }

    if (interruptedSpellId)
        m_spellLog.AddLog(uint32(SPELL_EFFECT_INTERRUPT_CAST), unitTarget->GetPackGUID(), interruptedSpellId);
}

void Spell::EffectSummonObjectWild(SpellEffectIndex eff_idx)
{
    uint32 gameobject_id = m_spellInfo->EffectMiscValue[eff_idx];

    GameObject* pGameObj = new GameObject;

    WorldObject* target = focusObject;
    if (!target)
        target = m_caster;

    float x, y, z;
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(x, y, z);
    else
        m_caster->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE);

    Map* map = target->GetMap();

    if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), gameobject_id, map,
                          x, y, z, target->GetOrientation()))
    {
        delete pGameObj;
        return;
    }

    pGameObj->SetRespawnTime(m_duration > 0 ? m_duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);

    // Wild object not have owner and check clickable by players
    map->Add(pGameObj);
    pGameObj->AIM_Initialize();

    // Notify Summoner
    if (m_originalCaster && (m_originalCaster != m_caster) && (m_originalCaster->AI()))
        m_originalCaster->AI()->JustSummoned(pGameObj);
    else if (m_caster->AI())
        m_caster->AI()->JustSummoned(pGameObj);

    OnSummon(pGameObj);

    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON_OBJECT_WILD), pGameObj->GetPackGUID());

    if (GameObject* linkedGO = pGameObj->GetLinkedTrap())
    {
        OnSummon(linkedGO);
        m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON_OBJECT_WILD), linkedGO->GetPackGUID());
    }
}

void Spell::EffectScriptEffect(SpellEffectIndex eff_idx)
{
    // TODO: we must implement hunter pet summon at login there (spell 6962)

    switch (m_spellInfo->SpellFamilyName)
    {
        case SPELLFAMILY_GENERIC:
        {
            switch (m_spellInfo->Id)
            {
                case 5249:                                  // Ice Lock
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 22856, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 8856:                                  // Bending Shinbone
                {
                    if (!itemTarget && m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spell_id;
                    switch (urand(1, 5))
                    {
                        case 1:  spell_id = 8854; break;
                        default: spell_id = 8855; break;
                    }

                    m_caster->CastSpell(m_caster, spell_id, TRIGGERED_OLD_TRIGGERED, nullptr);
                    return;
                }
                case 10101:                                 // Knock Away variants
                case 18670:
                case 18813:
                case 18945:
                case 19633:
                case 20686:
                case 23382:
                case 25778:
                case 30121:                                 // Forceful Howl - Plagued Deathhound
                case 31389:                                 // Knock Away
                case 32077:                                 // Boglord Bash
                case 32959:                                 // Knock Away
                case 37597:                                 // Meat Slap
                case 40486:                                 // Eject - Bloodboil
                {
                    // Knock Away variants and derrivatives with scripted threat reduction component
                    if (!unitTarget)
                        return;
                    // Default (most of the time) reduction is 50%. TODO: Verify when possible per spell
                    int32 pct = -50;
                    // A subset of spells has different values
                    switch (m_spellInfo->Id)
                    {
                        case 19633:
                        case 25778:
                        case 31389:
                        case 37102:                                 // Knock Away - Crystalcore Devastator 20040
                        case 40486:
                            pct = -25;
                            break;
                        case 30013:                                 // Disarm - Ethereal Thief 16544
                            pct = -99;
                            break;
                    }
                    m_caster->getThreatManager().modifyThreatPercent(unitTarget, pct);
                    return;
                }
                case 17512:                                 // Piccolo of the Flaming Fire
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->HandleEmoteCommand(EMOTE_STATE_DANCE);

                    return;
                }
                case 22539:                                 // Shadow Flame (All script effects, not just end ones to
                case 22972:                                 // prevent player from dodging the last triggered spell)
                case 22975:
                case 22976:
                case 22977:
                case 22978:
                case 22979:
                case 22980:
                case 22981:
                case 22982:
                case 22983:
                case 22984:
                case 22985:
                {
                    if (!unitTarget || !unitTarget->IsAlive())
                        return;

                    // Onyxia Scale Cloak
                    if (unitTarget->GetDummyAura(22683))
                        return;

                    // Shadow Flame
                    m_caster->CastSpell(unitTarget, 22682, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 23853:
                {
                    unitTarget->CastSpell(nullptr, 23852, TRIGGERED_NONE);
                    return;
                }
                case 24194:                                 // Uther's Tribute
                case 24195:                                 // Grom's Tribute
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint8 race = m_caster->getRace();
                    uint32 spellId = 0;

                    switch (m_spellInfo->Id)
                    {
                        case 24194:
                            switch (race)
                            {
                                case RACE_HUMAN:            spellId = 24105; break;
                                case RACE_DWARF:            spellId = 24107; break;
                                case RACE_NIGHTELF:         spellId = 24108; break;
                                case RACE_GNOME:            spellId = 24106; break;
                                // next case not exist in 2.x officially (quest has been broken for race until 3.x time)
                                case RACE_DRAENEI:          spellId = 24108; break;
                            }
                            break;
                        case 24195:
                            switch (race)
                            {
                                case RACE_ORC:              spellId = 24104; break;
                                case RACE_UNDEAD:           spellId = 24103; break;
                                case RACE_TAUREN:           spellId = 24102; break;
                                case RACE_TROLL:            spellId = 24101; break;
                                // next case not exist in 2.x officially (quest has been broken for race until 3.x time)
                                case RACE_BLOODELF:         spellId = 24101; break;
                            }
                            break;
                    }

                    if (spellId)
                        m_caster->CastSpell(m_caster, spellId, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 24320:                                 // Poisonous Blood
                {
                    unitTarget->CastSpell(unitTarget, 24321, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 24324:                                 // Blood Siphon
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(m_caster, unitTarget->HasAura(24321) ? 24323 : 24322, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24590:                                 // Brittle Armor - need remove one 24575 Brittle Armor aura
                    unitTarget->RemoveAuraHolderFromStack(24575);
                    return;
                case 24714:                                 // Trick
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (roll_chance_i(14))                  // Trick (can be different critter models). 14% since below can have 1 of 6
                        m_caster->CastSpell(m_caster, 24753, TRIGGERED_OLD_TRIGGERED);
                    else                                    // Random Costume, 6 different (plus add. for gender)
                        m_caster->CastSpell(m_caster, 24720, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 24717:                                 // Pirate Costume
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Pirate Costume (male or female)
                    m_caster->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 24708 : 24709, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24718:                                 // Ninja Costume
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Ninja Costume (male or female)
                    m_caster->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 24711 : 24710, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24719:                                 // Leper Gnome Costume
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Leper Gnome Costume (male or female)
                    m_caster->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 24712 : 24713, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24720:                                 // Random Costume
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spellId = 0;

                    switch (urand(0, 6))
                    {
                        case 0:
                            spellId = unitTarget->getGender() == GENDER_MALE ? 24708 : 24709;
                            break;
                        case 1:
                            spellId = unitTarget->getGender() == GENDER_MALE ? 24711 : 24710;
                            break;
                        case 2:
                            spellId = unitTarget->getGender() == GENDER_MALE ? 24712 : 24713;
                            break;
                        case 3:
                            spellId = 24723;
                            break;
                        case 4:
                            spellId = 24732;
                            break;
                        case 5:
                            spellId = unitTarget->getGender() == GENDER_MALE ? 24735 : 24736;
                            break;
                        case 6:
                            spellId = 24740;
                            break;
                    }

                    m_caster->CastSpell(unitTarget, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24731:                                 // Cannon Fire
                case 42868:                                 // Fire Cannon
                {
                    if (!unitTarget || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(m_caster, m_spellInfo->Id == 24731 ? 24742 : 42867, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24737:                                 // Ghost Costume
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Ghost Costume (male or female)
                    m_caster->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 24735 : 24736, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24742:                                 // Magic Wings
                case 42867:                                 // Magic Wings (Terrokar Forest)
                {
                    if(!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(24754);   // Darkmoon Faire Cannon root aura
                    return;
                }
                case 24751:                                 // Trick or Treat
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Tricked or Treated
                    unitTarget->CastSpell(unitTarget, 24755, TRIGGERED_OLD_TRIGGERED);

                    // Treat / Trick
                    unitTarget->CastSpell(unitTarget, roll_chance_i(50) ? 24714 : 24715, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 24935:                                 // Summon RC Tank
                {
                    if (m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->CastSpell(unitTarget, 24934, TRIGGERED_OLD_TRIGGERED); // Summon RC Tank
                    return;
                }
                case 25140:                                 // Orb teleport spells
                case 25143:
                case 25650:
                case 25652:
                case 29128:
                case 29129:
                case 34448:
                case 34452:
                case 35376:
                case 35727:
                case 45367:
                case 45370:
                {
                    if (!unitTarget)
                        return;

                    uint32 spellid;
                    Unit* spellTarget = nullptr;
                    switch (m_spellInfo->Id)
                    {
                        case 25140: spellid =  32568; break;
                        case 25143: spellid =  32572; break;
                        case 25650: spellid =  30140; break;
                        case 25652: spellid =  30141; break;
                        case 29128: spellid =  32571; break;
                        case 29129: spellid =  32569; break;
                        case 34448: spellid =  26566; break;
                        case 34452: spellid =  26572; spellTarget = unitTarget; break;
                        case 35376: spellid =  25649; break;
                        case 35727: spellid =  35730; break;
                        case 45367: spellid =  45368; break;
                        case 45370: spellid =  45371; break;
                        default:
                            return;
                    }

                    unitTarget->CastSpell(spellTarget, spellid, TRIGGERED_NONE);
                    return;
                }
                case 25671:                                 // Drain Mana
                case 25755:
                {
                    unitTarget->CastSpell(m_caster, 26639, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25676: // Moam                         // Drain Mana
                case 26559: // Obsidian Nullifier
                {
                    m_caster->CastSpell(unitTarget, 25671, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 25754: // Obsidian Destroyer           // Drain Mana
                case 26457: // Obsidian Eradicator
                {
                    m_caster->CastSpell(unitTarget, 25755, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 26004:                                 // Mistletoe
                {
                    if (!unitTarget)
                        return;

                    unitTarget->HandleEmote(EMOTE_ONESHOT_CHEER);
                    return;
                }
                case 26218:                                 // Mistletoe
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spells[3] = {26206, 26207, 45036};

                    m_caster->CastSpell(unitTarget, spells[urand(0, 2)], TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 26275:                                 // PX-238 Winter Wondervolt TRAP
                {
                    uint32 spells[4] = {26272, 26157, 26273, 26274};

                    // check presence
                    for (int j = 0; j < 4; ++j)
                        if (unitTarget->HasAura(spells[j], EFFECT_INDEX_0))
                            return;

                    // cast
                    unitTarget->CastSpell(unitTarget, spells[urand(0, 3)], TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 26465:                                 // Mercurial Shield - need remove one 26464 Mercurial Shield aura
                    unitTarget->RemoveAuraHolderFromStack(26464);
                    return;
                case 26524:                                 // Sand Trap (AQ20 - Kurinnaxx, parent spell selecting one target)
                {
                    if (unitTarget)
                        unitTarget->CastSpell(unitTarget, 25648, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 26528:                                 // Summon Reindeer - trigger actual summoning
                {
                    if (unitTarget)
                        unitTarget->CastSpell(nullptr, 26529, TRIGGERED_NONE);
                    return;
                }
                case 26656:                                 // Summon Black Qiraji Battle Tank
                {
                    if (!unitTarget)
                        return;

                    if (unitTarget->HasAura(25863) || unitTarget->HasAura(26655))
                        return; // protection against visual glitch

                    // Prevent stacking of mounts
                    unitTarget->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);

                    // Two separate mounts depending on area id (allows use both in and out of specific instance)
                    if (unitTarget->GetAreaId() == 3428)
                        unitTarget->CastSpell(unitTarget, 25863, TRIGGERED_NONE);
                    else
                        unitTarget->CastSpell(unitTarget, 26655, TRIGGERED_NONE);

                    return;
                }
                case 26663:                                 // Valentine - Orgrimmar Grunt
                case 26923:                                 // Valentine - Thunderbluff Watcher
                case 26924:                                 // Valentine - Undercity Guardian
                case 27541:                                 // Valentine - Darnassus Sentinel
                case 27547:                                 // Valentine - Ironforge Guard
                case 27548:                                 // Valentine - Stormwind City Guard
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 PledgeGiftOrHeartbroken;
                    // Guard spellIds map [Pledge of Friendship , Pledge of Adoration]
                    std::map<uint32, std::vector<uint32>> loveAirSpellsMapForFaction = {
                            {11, {27242, 27510}},   // Stormwind
                            {85, {27247, 27507}},   // Orgrimmar
                            {57, {27244, 27506}},   // Ironforge
                            {68, {27246, 27515}},   // Undercity Guardian
                            {71, {27246, 27515}},   // Undercity Seeker
                            {79, {27245, 27504}},   // Darnassus
                            {105, {27248, 27513}}   // Thunderbluff
                        };

                    if (loveAirSpellsMapForFaction.count(m_caster->getFaction()))
                    {
                        if (!urand(0, 5))                       // Sets 1 in 6 chance to cast Heartbroken
                            PledgeGiftOrHeartbroken = 26898;    // Heartbroken
                        else if (!unitTarget->HasAura(26680))
                        {
                            PledgeGiftOrHeartbroken = loveAirSpellsMapForFaction[m_caster->getFaction()][1];    // Pledge of Adoration for related faction
                            unitTarget->CastSpell(unitTarget, 26680, TRIGGERED_OLD_TRIGGERED);  // Cast Adored
                        }
                        else
                            PledgeGiftOrHeartbroken = loveAirSpellsMapForFaction[m_caster->getFaction()][0];    // Pledge of Friendship for related faction

                        unitTarget->CastSpell(unitTarget, PledgeGiftOrHeartbroken, TRIGGERED_OLD_TRIGGERED);
                        m_caster->RemoveAurasDueToSpell(27741);                             // Remove Love is in the Air from guard
                        ((Player*)unitTarget)->DestroyItemCount(21815, 1, true, false);     // Remove 1 love token on cast from inventory
                    }
                    return;
                }
                case 26678:                                 // Create Heart Candy
                {
                    uint32 spellId = 0;

                    switch (urand(0, 7))
                    {
                        case 0: spellId = 26668; break;
                        case 1: spellId = 26670; break;
                        case 2: spellId = 26671; break;
                        case 3: spellId = 26672; break;
                        case 4: spellId = 26673; break;
                        case 5: spellId = 26674; break;
                        case 6: spellId = 26675; break;
                        case 7: spellId = 26676; break;
                    }

                    m_caster->CastSpell(m_caster, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 27549:                                 // Valentine - Horde Civilian
                case 27550:                                 // Valentine - Alliance Civilian
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 PledgeGiftOrHeartbroken;
                    // Civilian spellIds map [Gift of Friendship , Gift of Adoration]
                    std::map<uint32, std::vector<uint32>> loveAirSpellsMapForFaction = {
                            {12, {27525, 27509}},   // Stormwind
                            {29, {27523, 27505}},   // Orgrimmar orcs
                            {55, {27520, 27503}},   // Ironforge dwarves
                            {68, {27529, 27512}},   // Undercity
                            {80, {27519, 26901}},   // Darnassus
                            {104, {27524, 27511}},  // Thunderbluff
                            {126, {27523, 27505}},  // Orgrimmar trolls
                            {875, {27520, 27503}}   // Ironforge gnomes
                        };

                    if (loveAirSpellsMapForFaction.count(m_caster->getFaction()))
                    {
                        if (!urand(0, 5))                       // Sets 1 in 6 chance to cast Heartbroken
                            PledgeGiftOrHeartbroken = 26898;    // Heartbroken
                        else if (!unitTarget->HasAura(26680))
                        {
                            PledgeGiftOrHeartbroken = loveAirSpellsMapForFaction[m_caster->getFaction()][1];    // Gift of Adoration for related faction
                            unitTarget->CastSpell(unitTarget, 26680, TRIGGERED_OLD_TRIGGERED);                  // Cast Adored
                        }
                        else
                            PledgeGiftOrHeartbroken = loveAirSpellsMapForFaction[m_caster->getFaction()][0];    // Gift of Friendship for related faction

                        unitTarget->CastSpell(unitTarget, PledgeGiftOrHeartbroken, TRIGGERED_OLD_TRIGGERED);
                        m_caster->RemoveAurasDueToSpell(27741);                             // Remove Love is in the Air from civilian
                        ((Player*)unitTarget)->DestroyItemCount(21815, 1, true, false);     // remove 1 love token on cast from inventory
                    }
                    return;
                }
                case 27654:                                 // Love is in the Air Test
                {
                    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
                    {
                        unitTarget->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);          // Add gossip flag for NPC missing it
                        if (!unitTarget->HasFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_INNKEEPER))  // Cast Amorous if caster is not an innkeeper
                            unitTarget->CastSpell(m_caster, 26869, TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
                case 27687:                                 // Summon Bone Minions
                {
                    if (!unitTarget)
                        return;

                    // Spells 27690, 27691, 27692, 27693 are missing from DBC
                    // So we need to summon creature 16119 manually
                    float x, y, z;
                    float angle = unitTarget->GetOrientation();
                    for (uint8 i = 0; i < 4; ++i)
                    {
                        unitTarget->GetNearPoint(unitTarget, x, y, z, unitTarget->GetObjectBoundingRadius(), INTERACTION_DISTANCE, angle + i * M_PI_F / 2);
                        unitTarget->SummonCreature(16119, x, y, z, angle, TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 10 * MINUTE * IN_MILLISECONDS);
                    }
                    return;
                }
                case 27695:                                 // Summon Bone Mages
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 27696, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 27697, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 27698, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 27699, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 27749:                                 // Initialize Tank
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 24936, TRIGGERED_OLD_TRIGGERED);  // RC Tank Control
                    unitTarget->CastSpell(nullptr, 27747, TRIGGERED_OLD_TRIGGERED);  // Steam Tank Passive
                    return;
                }
                case 28236:                                 // Zombie Chow Search
                {
                    if (!unitTarget->IsAlive())
                        return;

                    m_caster->SetTarget(nullptr);
                    m_caster->SetFacingToObject(unitTarget);
                    if (m_caster->CastSpell(unitTarget, 28239, TRIGGERED_NONE) == SPELL_CAST_OK)    // Zombie Chow Search - Insta kill, single target
                        DoScriptText(-1533119, m_caster, unitTarget);
                    return;
                }
                case 28338:                                 // Magnetic Pull
                case 28339:                                 // Magnetic Pull
                {
                    if (unitTarget && m_caster->GetVictim())
                        unitTarget->CastSpell(m_caster->GetVictim(), 28337, TRIGGERED_OLD_TRIGGERED);   // target cast actual Magnetic Pull on caster's victim
                        // ToDo research if target should also get the threat of the caster for caster's victim.
                        // This is the case in WotLK version but we have no proof of this in Classic/TBC
                        // and it was common at these times to let players manage threat and tank transitions by themselves
                    return;
                }

                case 28352:                                 // Breath of Sargeras
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(unitTarget, 28342, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 28374:                                 // Decimate (Naxxramas: Gluth)
                {
                    if (!unitTarget)
                        return;

                    // Return if not player, pet nor Zombie Chow NPC
                    if (unitTarget->GetTypeId() == TYPEID_UNIT && !unitTarget->IsControlledByPlayer() && unitTarget->GetEntry() != 16360)
                        return;

                    int32 damage = unitTarget->GetHealth() - unitTarget->GetMaxHealth() * 0.05f;
                    if (damage > 0)
                        m_caster->CastCustomSpell(unitTarget, 28375, &damage, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 28617:                                 // Web Wrap (Maexxna: pull spell initialiser)
                {
                    if (!m_originalCaster)
                        return;

                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT || m_caster->GetTypeId() != TYPEID_PLAYER)
                        return;

                    float dist = m_caster->GetDistance(unitTarget, false);
                    // Switch the pull target spell based on the distance from the web wrap position
                    uint32 pullSpellId = 28621;
                    if (dist < 25.0f)
                        pullSpellId = 28618;
                    else if (dist < 50.0f)
                        pullSpellId = 28619;
                    else if (dist < 75.0f)
                        pullSpellId = 28620;

                    unitTarget->CastSpell(m_caster, pullSpellId, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_originalCaster->GetObjectGuid());
                    return;
                }
                case 28628:                                 // Clear Web Wrap (Maexxna: clear effects on player)
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        unitTarget->RemoveAurasDueToSpell(28627); // Web Wrap polymorph
                        unitTarget->RemoveAurasDueToSpell(28622); // Web Wrap stun and DoT
                    }
                    return;
                }
                case 28629:                                 // Clear Web Wrap (Maexxna: kill Web Wrap NPC)
                {
                    if (unitTarget && unitTarget->GetTypeId() == TYPEID_UNIT)
                        unitTarget->CastSpell(nullptr, 29108, TRIGGERED_OLD_TRIGGERED);  // Kill Web Wrap
                    return;
                }
                case 28732:                                 // Widow Embrace
                {
                    m_caster->CastSpell(nullptr, 28748, TRIGGERED_OLD_TRIGGERED);       // Self suicide
                    return;
                }
                case 29336:                                 // Despawn Buffet
                case 29379:                                 // Despawn Crypt Guards
                case 30134:                                 // Despawn Boss Adds
                case 30228:                                 // Despawn Summons
                {
                    if (unitTarget)
                        ((Creature*)unitTarget)->ForcedDespawn();
                    return;
                }
                case 29395:                                 // Break Kaliri Egg
                {
                    uint32 creature_id;
                    uint32 rand = urand(0, 99);

                    if (rand < 10)
                        creature_id = 17034;
                    else if (rand < 60)
                        creature_id = 17035;
                    else
                        creature_id = 17039;

                    if (WorldObject* pSource = GetAffectiveCasterObject())
                        pSource->SummonCreature(creature_id, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 120 * IN_MILLISECONDS);
                    return;
                }
                case 29830:                                 // Mirren's Drinking Hat
                {
                    uint32 item = 0;
                    switch (urand(1, 6))
                    {
                        case 1:
                        case 2:
                        case 3:
                            item = 23584; break;            // Loch Modan Lager
                        case 4:
                        case 5:
                            item = 23585; break;            // Stouthammer Lite
                        case 6:
                            item = 23586; break;            // Aerie Peak Pale Ale
                    }

                    if (item)
                        DoCreateItem(eff_idx, item);

                    break;
                }
                case 30541:                                 // Blaze
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 30542, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 30572:                                 // Quake - Magtheridon
                {
                    unitTarget->RemoveAurasDueToSpell(30657);   // Remove quake from all triggers
                    return;
                }
                case 30629:                                 // Debris - Magtheridon
                {
                    unitTarget->CastSpell(nullptr, 30630, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 30769:                                 // Pick Red Riding Hood
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // cast Little Red Riding Hood
                    m_caster->CastSpell(unitTarget, 30768, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 30834:                                 // Infernal Relay
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 30835, TRIGGERED_NONE);
                    break;
                }
                case 30835:                                 // Infernal Relay
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 30836, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    break;
                }
                case 30918:                                 // Improved Sprint
                {
                    if (!unitTarget)
                        return;

                    // Removes snares and roots.
                    unitTarget->RemoveAurasAtMechanicImmunity(IMMUNE_TO_ROOT_AND_SNARE_MASK, 30918, true);
                    break;
                }
                case 30952:                                 // Shoot Flame Arrow (Shattered Halls)
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 30953, TRIGGERED_NONE); // cast explosion
                    break;
                }
                case 37142:                                 // Karazhan - Chess NPC Action: Melee Attack: Conjured Water Elemental
                case 37143:                                 // Karazhan - Chess NPC Action: Melee Attack: Charger
                case 37147:                                 // Karazhan - Chess NPC Action: Melee Attack: Human Cleric
                case 37149:                                 // Karazhan - Chess NPC Action: Melee Attack: Human Conjurer
                case 37150:                                 // Karazhan - Chess NPC Action: Melee Attack: King Llane
                case 37220:                                 // Karazhan - Chess NPC Action: Melee Attack: Summoned Daemon
                case 32227:                                 // Karazhan - Chess NPC Action: Melee Attack: Footman
                case 32228:                                 // Karazhan - Chess NPC Action: Melee Attack: Grunt
                case 37337:                                 // Karazhan - Chess NPC Action: Melee Attack: Orc Necrolyte
                case 37339:                                 // Karazhan - Chess NPC Action: Melee Attack: Orc Wolf
                case 37345:                                 // Karazhan - Chess NPC Action: Melee Attack: Orc Warlock
                case 37348:                                 // Karazhan - Chess NPC Action: Melee Attack: Warchief Blackhand
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 32247, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 32301:                                 // Ping Shirrak
                {
                    if (!unitTarget)
                        return;

                    // Cast Focus fire on caster
                    unitTarget->CastSpell(m_caster, 32300, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 33525:                                 // Ground Slam - Gruul
                {
                    if (unitTarget->GetTypeId() == TYPEID_PLAYER)
                    {
                        float angle = frand(0,M_PI_F*2);
                        ((Player*)unitTarget)->GetSession()->SendKnockBack(unitTarget, angle, 15.f, urand(15, 24));
                    }
                    return;
                }
                case 33654:                                 // Shatter - Gruul
                {
                    if (unitTarget->HasAura(33652) && unitTarget->GetTypeId() == TYPEID_PLAYER)
                        unitTarget->CastSpell(nullptr, 33671, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->RemoveAurasDueToSpell(33572);
                    unitTarget->RemoveAurasDueToSpell(33652);
                    return;
                }
                case 34098:                                 // ClearAllDebuffs
                {
                    auto holderMap = m_caster->GetSpellAuraHolderMap();
                    for (auto holderPair : holderMap)
                    {
                        if (!holderPair.second->IsPositive() && !holderPair.second->IsPassive())
                        {
                            m_caster->RemoveAurasDueToSpell(holderPair.second->GetId());
                        }
                    }
                    return;
                }
                case 34789:                                 // Shared Bonds
                {
                    Creature* creature = GetClosestCreatureWithEntry(m_caster, m_caster->GetEntry(), 30.f, true, false, true);
                    if (creature)
                    {
                        if (m_caster->HasAura(34788) || creature->HasAura(34788))
                            return;

                        m_caster->CastSpell(creature, 34788, TRIGGERED_OLD_TRIGGERED);
                        creature->CastSpell(m_caster, 34788, TRIGGERED_OLD_TRIGGERED);
                    }
                    return;
                }
                case 35597:                                 // Cancel Power of the Legion
                {
                    unitTarget->RemoveAurasDueToSpell(35596); // remove aura Power of the Legion
                    return;
                }
                case 35869:                                 // Nether Beam
                {
                    if (m_caster->GetTypeId() != TYPEID_UNIT)
                        return;

                    ThreatList const& threatlist = m_caster->getThreatManager().getThreatList();
                    if (threatlist.empty())
                        return;

                    std::vector<Unit*> suitableUnits;
                    suitableUnits.reserve(threatlist.size());

                    for (ThreatList::const_iterator itr = threatlist.begin(); itr != threatlist.end(); ++itr)
                        if (Unit* pTarget = m_caster->GetMap()->GetUnit((*itr)->getUnitGuid()))
                            if (pTarget->GetTypeId() == TYPEID_PLAYER)
                                suitableUnits.push_back(pTarget);

                    if (!suitableUnits.empty())
                    {
                        while (suitableUnits.size() > 5)
                            suitableUnits.erase(suitableUnits.begin() + urand(0, suitableUnits.size() - 1));

                        for (Unit* beamTarget : suitableUnits)
                            m_caster->CastSpell(beamTarget, 35873, TRIGGERED_NONE);
                    }

                    return;
                }
                case 36092:                                 // Kael Explodes
                {
                    m_caster->CastSpell(nullptr, 36185, TRIGGERED_NONE);
                    m_caster->CastSpell(nullptr, 36550, TRIGGERED_NONE);
                    m_caster->PlayDirectSound(3320);
                    m_caster->PlayDirectSound(10845);
                    m_caster->PlayDirectSound(6539);
                    return;
                }
                case 36201:                                 // Pure Nether Beam
                case 36290:
                case 36291:
                {
                    if (!unitTarget)
                        return;

                    uint32 spellId;
                    switch (urand(0, 2))
                    {
                        case 0: spellId = 36196; break;
                        case 1: spellId = 36197; break;
                        case 2: spellId = 36198; break;
                    }

                    m_caster->PlayDirectSound(6477);
                    m_caster->PlayDirectSound(44);

                    unitTarget->CastSpell(nullptr, spellId, TRIGGERED_NONE); // also triggered in sniff, only SMSG_SPELL_GO
                    return;
                }
                case 36208:                                 // Steal Weapon
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_NONE);
                    return;
                }
                case 36251:                                 // Hammer Slam
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_NONE);
                    return;
                }
                case 37013:                                 // Despawn Kaliri Totem
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    if (unitTarget->GetEntry() == 21468)
                        ((Creature*)unitTarget)->ForcedDespawn(0);
                    return;
                }
                case 37028:                                 // Dispelling Analysis
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(36904);
                    unitTarget->CastSpell(nullptr, 37013, TRIGGERED_NONE);
                    return;
                }
                case 37641:                                 // Whirlwind
                {
                    UnitAI* ai = m_caster->AI();
                    if (!ai || m_caster->GetTypeId() != TYPEID_UNIT)
                        return;

                    if (urand(0, 2) == 0 && m_caster->HasAura(37640))
                    {
                        ai->DoResetThreat();
                        if (Unit* target = static_cast<Creature*>(m_caster)->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                            m_caster->AddThreat(target, 100000.f);
                    }
                    return;
                }
                case 37751:                                 // Submerged
                case 37752:                                 // Stand
                {
                    if (!unitTarget)
                        return;

                    unitTarget->SetStandState(m_spellInfo->Id == 37751 ? UNIT_STAND_STATE_CUSTOM : UNIT_STAND_STATE_STAND);
                    return;
                }
                case 37775:                                 // Karazhan - Chess NPC Action - Poison Cloud
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 37469, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 37824:                                 // Karazhan - Chess NPC Action - Shadow Mend
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 37456, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 38055:                                 // Destroy Deathforged Infernal
                {
                    if (!unitTarget)
                        return;

                    for (uint32 i = 0; i < 10; ++i)
                        m_caster->CastSpell(nullptr, 38054, TRIGGERED_OLD_TRIGGERED);

                    return;
                }
                case 38650:                                 // Rancid Mushroom Primer
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 38651, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 38629:                                 // Poison Keg
                {
                    if (!unitTarget)
                        return;

                    Unit* master = m_caster->GetMaster();
                    if (master->GetTypeId() != TYPEID_PLAYER)
                        return;

                    uint32 spellId;

                    switch (unitTarget->GetEntry())
                    {
                        case 22356: spellId = 38996; break; // [DND]Green Spot Grog Keg Credit
                        case 22367: spellId = 38997; break; // [DND]Ripe Moonshine Keg Credit
                        case 22368: spellId = 38998; break; // [DND]Fermented Seed Beer Keg Credit
                    }

                    Player* possessor = static_cast<Player*>(master);

                    possessor->CastSpell(possessor, spellId, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 38794:                                 // Murmur's Touch - Heroic
                {
                    UnitList objectList;
                    MaNGOS::AnyFriendlyUnitInObjectRangeCheck check(unitTarget, nullptr, 100.f);
                    MaNGOS::UnitListSearcher<MaNGOS::AnyFriendlyUnitInObjectRangeCheck> searcher(objectList, check);
                    Cell::VisitAllObjects(unitTarget, searcher, 100.0f);
                    objectList.remove(unitTarget); // remove target

                    for (Unit* pullTarget : objectList)
                        unitTarget->CastSpell(pullTarget, 28337, TRIGGERED_OLD_TRIGGERED); // this is guesswork based on sniff

                    return;
                }
                case 38920:                                 // Detonate Teleporter
                {
                    if (Player* pPlayer = m_caster->GetBeneficiaryPlayer())
                        pPlayer->RewardPlayerAndGroupAtEventCredit(unitTarget->GetEntry(), unitTarget);

                    return;
                }
                case 39190:                                 // Send Vengeance
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget->GetSpawner(), 39202, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 39202:
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 39206, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 39338:                                 // Karazhan - Chess, Medivh CHEAT: Hand of Medivh, Target Horde
                case 39342:                                 // Karazhan - Chess, Medivh CHEAT: Hand of Medivh, Target Alliance
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, 39339, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 39341:                                 // Karazhan - Chess, Medivh CHEAT: Fury of Medivh, Target Horde
                case 39344:                                 // Karazhan - Chess, Medivh CHEAT: Fury of Medivh, Target Alliance
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 39495:                                 // Remove Tainted Cores
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(unitTarget, 39496, TRIGGERED_NONE);
                    return;
                }
                case 39835:                                 // Needle Spine - Najentus
                {
                    unitTarget->CastSpell(nullptr, 39968, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40022:                                 // Four Dragons: Aggro Check
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    unitTarget->CastSpell(m_caster, damage, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40742:                                 // Booterang
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, damage, TRIGGERED_NONE);
                    return;
                }
                case 40761:                                 // Cage Trap - Illidan
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 40760, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 40762:                                 // Clear Peon All
                {
                    m_caster->CombatStop(true);
                    m_caster->RemoveAurasDueToSpell(40735); // Defiant and Enraged
                    m_caster->RemoveAurasDueToSpell(40732); // Lazy and Good for Nothing
                    return;
                }
                case 40828:                                 // Banish the Demons: Cast Kill Credit on Master
                {
                    if (!unitTarget)
                        return;

                    // Serverside 40829 does not exist
                    if (Unit* spawner = unitTarget->GetSpawner())
                        if (spawner->GetTypeId() == TYPEID_PLAYER)
                            ((Player*)spawner)->RewardPlayerAndGroupAtEventCredit(unitTarget->GetEntry(), unitTarget);

                    return;
                }
                case 40904:                                 // Draw Soul - Illidan
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, 40903, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 41055:                                 // Copy Weapon
                {
                    if (m_caster->GetTypeId() != TYPEID_UNIT || !unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Item* pItem = ((Player*)unitTarget)->GetWeaponForAttack(BASE_ATTACK))
                    {
                        ((Creature*)m_caster)->SetVirtualItem(VIRTUAL_ITEM_SLOT_0, pItem->GetEntry());

                        // Unclear what this spell should do
                        unitTarget->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 41072:                                 // Bloodbolt
                {
                    if (!unitTarget)
                        return;

                    m_caster->CastSpell(unitTarget, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 41126:                                 // Flame Crash
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 41131, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 41195:                                 // Whirlwind
                {
                    if (m_caster->GetTypeId() != TYPEID_UNIT)
                        return;

                    Unit* target = ((Creature *)m_caster)->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, uint32(0), SELECT_FLAG_PLAYER);
                    if (target)
                    {
                        ThreatList const& threatList = m_caster->getThreatManager().getThreatList();
                        for (auto i : threatList)
                            if (Unit* Temp = m_caster->GetMap()->GetUnit(i->getUnitGuid()))
                                m_caster->getThreatManager().modifyThreatPercent(Temp, -100);

                        m_caster->AddThreat(target, 100000.f);
                    }

                    return;
                }
                case 41914:                                 // Parasitic Shadowfiend
                {
                    if (!unitTarget || !m_caster->AI())
                        return;
                    m_caster->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, unitTarget, m_caster);
                    return;
                }
                case 42179:                                 // Summon Amani'shi Sentries
                {
                    if (!unitTarget)
                        return;

                    uint32 spells[4] = { 42180, 42181, 42182, 42183 };
                    unitTarget->CastSpell(unitTarget, spells[urand(0, 3)], TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 42281:                                 // Sprouting
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(42280);
                    unitTarget->RemoveAurasDueToSpell(42294);
                    unitTarget->CastSpell(unitTarget, 42285, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 42291, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 42399:                                 // Headless Horseman Climax - Send Head
                {
                    if (unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    Creature* creatureTarget = static_cast<Creature*>(unitTarget);

                    if (creatureTarget->GetEntry() == 23775)
                        creatureTarget->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, m_caster, creatureTarget);

                    return;
                }
                case 43101:                                 // Headless Horseman Climax - Command, Head Requests Body
                {
                    if (unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    Creature* creatureTarget = static_cast<Creature*>(unitTarget);

                    if (creatureTarget->GetEntry() == 23682)
                        creatureTarget->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, m_caster, creatureTarget);

                    return;
                }
                case 42492:                                 // Cast Energized
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Player* pPlayer = unitTarget->GetBeneficiaryPlayer())
                        if (pPlayer->GetQuestStatus(11174) != QUEST_STATUS_INCOMPLETE)
                            return;

                    m_caster->CastSpell(unitTarget, 42490, TRIGGERED_NONE);

                    return;
                }
                case 42578:                                 // Cannon Blast
                {
                    if (!unitTarget)
                        return;

                    int32 basePoints = m_spellInfo->CalculateSimpleValue(eff_idx);
                    unitTarget->CastCustomSpell(unitTarget, 42576, &basePoints, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 42577:                                 // Zap
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, 43137, TRIGGERED_NONE);
                    return;
                }
                case 43783:                                 // Spawn Guard
                {
                    float pointX = 0;
                    float pointY = 0;
                    float pointZ = 0;

                    uint32 guardEntry = 0;
                    uint32 counter = 0;

                    bool foundPosition = false;

                    switch (m_caster->GetAreaId())
                    {
                        case 9:
                        case 24: guardEntry = 1642;     break;      // Northshire
                        case 42: guardEntry = 10038;    break;      // Darkshire
                        case 69: guardEntry = 10037;    break;      // Lakeshire
                        case 87: guardEntry = 1423;     break;      // Goldshire
                        case 108: guardEntry = 8096;    break;      // Sentinel Hill
                        case 131: guardEntry = 727;     break;      // Kharanos
                        case 132: guardEntry = 853;     break;      // Coldridge Valley
                        case 144: guardEntry = 8055;    break;      // Thelsamar
                        case 152:                                   // The Bulwark
                        case 154:                                   // Deathknell
                        case 159: guardEntry = 7980;    break;      // Brill
                        case 188: guardEntry = 4844;    break;      // Shadowglen
                        case 186: guardEntry = 3571;    break;      // Dolanaar
                        case 221:                                   // Camp Narache
                        case 222:                                   // Bloodhoof Village
                        {
                            switch (rand() % 4)
                            {
                                case 0: guardEntry = 3210; break;
                                case 1: guardEntry = 3211; break;
                                case 2: guardEntry = 3213; break;
                                case 3: guardEntry = 3214; break;
                            }
                            break;
                        }
                        case 228: guardEntry = 7489;    break;      // Sulpcher
                        case 271: guardEntry = 2386;    break;      // Southshore
                        case 272: guardEntry = 2405;    break;      // Tarren Mill
                        case 320: guardEntry = 10696;   break;      // Refuge Pointe
                        case 321: guardEntry = 2621;    break;      // Hammerfall
                        case 340: guardEntry = 8155;    break;      // Kargath
                        case 362: guardEntry = 5953;    break;      // Razor Hill
                        case 363: guardEntry = 5952;    break;      // Valley of Trials
                        case 380: guardEntry = 3501;    break;      // Crossroads
                        case 415: guardEntry = 6087;    break;      // Astranaar
                        case 431: guardEntry = 12903;   break;      // Splintertree Post
                        case 442: guardEntry = 6086;    break;      // Auberdine
                        case 460: guardEntry = 7730;    break;      // Sun Rock Retreat
                        case 484: guardEntry = 9525;    break;      // Freewind Post
                        case 513: guardEntry = 4979;    break;      // Threamore
                        case 597: guardEntry = 8154;    break;      // Ghost Walker Post
                        case 608: guardEntry = 8151;    break;      // Nijel's Point
                        case 1099: guardEntry = 8147;   break;      // Camp Mojache
                        case 1116: guardEntry = 7939;   break;      // Feathermoon Stronghold
                        case 1497: guardEntry = 5624;   break;      // Undercity
                        case 1519: guardEntry = 68;     break;      // Stormwind City
                        case 1537: guardEntry = 5595;   break;      // Ironforge
                        case 1637: guardEntry = 3296;   break;      // Orgrimmar
                        case 1638: guardEntry = 3084;   break;      // Thunder Bluff
                        case 1657: guardEntry = 4262;   break;      // Darnassus
                        case 2408: guardEntry = 12338;  break;      // Shadowprey Village
                        case 2897: guardEntry = 12903;  break;      // Zoram'gar Outpost
                        case 3462:                                  // Fairbreeze Village
                        case 3487:                                  // Silvermoon City
                        case 3488: guardEntry = 16222;  break;      // Tranquillien
                        case 3527: guardEntry = 16921;  break;      // Crash Site
                        case 3557: guardEntry = 16733;  break;      // Exodar
                        case 3576: guardEntry = 18038;  break;      // Azure Watch
                        case 3584: guardEntry = 17549;  break;      // Blood Watch
                        case 3665: guardEntry = 16222;  break;      // Falconwing Square
                    }


                    if (!unitTarget)
                        return;

                    m_caster->GetRandomPoint(m_caster->GetPositionX(), m_caster->GetPositionY(), m_caster->GetPositionZ(), 30.0f, pointX, pointY, pointZ, 20.0f);


                    while (counter < 100)
                    {
                        foundPosition = m_caster->GetMap()->GetReachableRandomPosition(m_caster, pointX, pointY, pointZ, 20.0f);

                        if (foundPosition)
                            break;

                        counter++;
                    }

                    // Spawn Guards only if we have random position.
                    if (foundPosition && guardEntry != 0)
                    {
                        Creature* pGuard = m_caster->SummonCreature(guardEntry, pointX, pointY, pointZ, m_caster->GetOrientation(), TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 30 * IN_MILLISECONDS);

                        if (pGuard)
                            pGuard->AI()->AttackStart(m_caster->getAttackerForHelper());
                    }

                    return;
                }
                case 43648:                                 // Akilzon - Electrical Storm
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 44007, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 43658:                                 // Akilzon - Electrical Overload Graphic Pulse
                {
                    m_caster->CastSpell(nullptr, 43653, TRIGGERED_OLD_TRIGGERED);
                    m_caster->CastSpell(nullptr, 43654, TRIGGERED_OLD_TRIGGERED);
                    m_caster->CastSpell(nullptr, 43655, TRIGGERED_OLD_TRIGGERED);
                    m_caster->CastSpell(nullptr, 43656, TRIGGERED_OLD_TRIGGERED);
                    m_caster->CastSpell(nullptr, 43659, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 44008:                                 // Akilzon - Static Disruption
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(nullptr, 45265, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 44224:                                 // Gravity Lapse
                {
                    if (!unitTarget)
                        return;

                    static const uint32 aGravityLapseSpells[] = { 44219, 44220, 44221, 44222, 44223 };
                    m_caster->CastSpell(unitTarget, aGravityLapseSpells[m_scriptValue], TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(nullptr, 44227, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(nullptr, 44226, TRIGGERED_OLD_TRIGGERED);
                    ++m_scriptValue;
                    return;
                }
                case 44232:                                 // Clear Flight
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasDueToSpell(44227);
                    unitTarget->RemoveAurasDueToSpell(44226);
                    return;
                }
                case 44876:                                 // Force Cast - Portal Effect: Sunwell Isle
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 44870, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 44811:                                 // Spectral Realm
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // If the player can't be teleported, send him a notification
                    if (unitTarget->HasAura(44867))
                    {
                        ((Player*)unitTarget)->GetSession()->SendNotification(LANG_FAIL_ENTER_SPECTRAL_REALM);
                        return;
                    }

                    // Teleport target to the spectral realm, add debuff and force faction
                    unitTarget->CastSpell(unitTarget, 46019, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 46021, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 44845, TRIGGERED_OLD_TRIGGERED);
                    unitTarget->CastSpell(unitTarget, 44852, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45071:                                 // Quest - Sunwell Daily - Dead Scar Bombing Run
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    m_caster->PlayMusic(12318, PlayPacketParameters(PLAY_TARGET, static_cast<Player*>(unitTarget)));
                    return;
                }
                case 45141:                                 // Burn
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 46394, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_caster->GetObjectGuid());
                    return;
                }
                case 45151:                                 // Burn
                {
                    if (!unitTarget || unitTarget->HasAura(46394))
                        return;

                    // Make the burn effect jump to another friendly target
                    unitTarget->CastSpell(unitTarget, 46394, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45185:                                 // Stomp
                {
                    if (!unitTarget)
                        return;

                    // Remove the burn effect
                    unitTarget->RemoveAurasDueToSpell(46394);
                    return;
                }
                case 45204:                                 // Clone Me!
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 45206:                                 // Copy Off-hand Weapon
                {
                    if (m_caster->GetTypeId() != TYPEID_UNIT || !unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    if (Item* pItem = ((Player*)unitTarget)->GetWeaponForAttack(OFF_ATTACK))
                    {
                        ((Creature*)m_caster)->SetVirtualItem(VIRTUAL_ITEM_SLOT_1, pItem->GetEntry());

                        // Unclear what this spell should do
                        unitTarget->CastSpell(m_caster, m_spellInfo->CalculateSimpleValue(eff_idx), TRIGGERED_OLD_TRIGGERED);
                    }

                    return;
                }
                case 45313:                                 // Anchor Here
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_UNIT)
                        return;

                    ((Creature*)unitTarget)->SetRespawnCoord(unitTarget->GetPositionX(), unitTarget->GetPositionY(), unitTarget->GetPositionZ(), unitTarget->GetOrientation());
                    return;
                }
                case 45918:                                 // Soul Sever
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER || !unitTarget->HasAura(45717))
                        return;

                    // kill all charmed targets
                    unitTarget->CastSpell(unitTarget, 45917, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 46203:                                 // Goblin Weather Machine
                {
                    if (!unitTarget)
                        return;

                    uint32 spellId = 0;
                    switch (rand() % 4)
                    {
                        case 0: spellId = 46740; break;
                        case 1: spellId = 46739; break;
                        case 2: spellId = 46738; break;
                        case 3: spellId = 46736; break;
                    }
                    unitTarget->CastSpell(unitTarget, spellId, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 46642:                                 //5,000 Gold
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    ((Player*)unitTarget)->ModifyMoney(50000000);
                    break;
                }
                case 47108:                                 // Clear Energy Feedback
                {
                    if (unitTarget)
                        unitTarget->RemoveAurasDueToSpell(44335);
                    return;
                }
                case 47977:                                 // Use Broom
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Spell::SelectMountByAreaAndSkill(unitTarget, m_spellInfo, 42680, 42683, 42667, 42668, 0);
                    return;
                }
                case 48025:                             // Headless Horseman's Mount
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    Spell::SelectMountByAreaAndSkill(unitTarget, m_spellInfo, 51621, 48024, 51617, 48023, 0);
                    return;
                }
                case 48917:                                 // Who Are They: Cast from Questgiver
                {
                    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
                        return;

                    // Male Shadowy Disguise / Female Shadowy Disguise
                    unitTarget->CastSpell(unitTarget, unitTarget->getGender() == GENDER_MALE ? 38080 : 38081, TRIGGERED_OLD_TRIGGERED);
                    // Shadowy Disguise
                    unitTarget->CastSpell(unitTarget, 32756, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
                case 50499:                                 // Listening to Music (Parent)
                {
                    unitTarget->CastSpell(unitTarget, 50493, TRIGGERED_OLD_TRIGGERED);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_WARLOCK:
        {
            switch (m_spellInfo->Id)
            {
                case  6201:                                 // Healthstone creating spells
                case  6202:
                case  5699:
                case 11729:
                case 11730:
                case 27230:
                {
                    if (!unitTarget)
                        return;

                    uint32 itemType = GetUsableHealthStoneItemType(unitTarget);
                    if (itemType)
                        DoCreateItem(eff_idx, itemType);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_PRIEST:
        {
            switch (m_spellInfo->Id)
            {
                case 39649:                                 // Summon Shadowfiends
                {
                    for (uint8 i = 0; i < 10; ++i)
                        m_caster->CastSpell(m_caster, 41159, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 40081:                                 // Free Friend
                {
                    if (!unitTarget)
                        return;

                    unitTarget->RemoveAurasAtMechanicImmunity(IMMUNE_TO_INCAPACITATE_MASK, m_spellInfo->Id);
                    return;
                }
            }
            break;
        }
        case SPELLFAMILY_PALADIN:
        {
            if (m_spellInfo->SpellFamilyFlags & uint64(0x0000000000800000))
            {
                if (!unitTarget || !unitTarget->IsAlive())
                    return;

                uint32 spellId2 = 0;

                // all seals have aura dummy
                Unit::AuraList const& m_dummyAuras = m_caster->GetAurasByType(SPELL_AURA_DUMMY);
                for (auto m_dummyAura : m_dummyAuras)
                {
                    SpellEntry const* spellInfo = m_dummyAura->GetSpellProto();

                    // search seal (all seals have judgement's aura dummy spell id in 2 effect
                    if (!spellInfo || !IsSealSpell(m_dummyAura->GetSpellProto()) || m_dummyAura->GetEffIndex() != 2)
                        continue;

                    // must be calculated base at raw base points in spell proto, GetModifier()->m_value for S.Righteousness modified by SPELLMOD_DAMAGE
                    spellId2 = m_dummyAura->GetSpellProto()->CalculateSimpleValue(EFFECT_INDEX_2);

                    if (spellId2 <= 1)
                        continue;

                    // found, remove seal
                    m_caster->RemoveAurasDueToSpell(m_dummyAura->GetId());

                    // Sanctified Judgement
                    Unit::AuraList const& m_auras = m_caster->GetAurasByType(SPELL_AURA_DUMMY);
                    for (Unit::AuraList::const_iterator i = m_auras.begin(); i != m_auras.end(); ++i)
                    {
                        if ((*i)->GetSpellProto()->SpellIconID == 205 && (*i)->GetSpellProto()->Attributes == uint64(0x01D0))
                        {
                            int32 chance = (*i)->GetModifier()->m_amount;
                            if (roll_chance_i(chance))
                            {
                                int32 mana = spellInfo->manaCost;
                                if (Player* modOwner = m_caster->GetSpellModOwner())
                                    modOwner->ApplySpellMod(spellInfo->Id, SPELLMOD_COST, mana);
                                mana = int32(mana * 0.8f);
                                m_caster->CastCustomSpell(m_caster, 31930, &mana, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED, nullptr, *i);
                            }
                            break;
                        }
                    }

                    break;
                }
                m_caster->CastSpell(unitTarget, spellId2, TRIGGERED_OLD_TRIGGERED);
                if (m_caster->HasAura(37188)) // improved judgement
                    m_caster->CastSpell(nullptr, 43838, TRIGGERED_OLD_TRIGGERED);
                return;
            }
            break;
        }
        case SPELLFAMILY_POTION:
        {
            switch (m_spellInfo->Id)
            {
                case 28698:                                 // Dreaming Glory
                {
                    if (!unitTarget)
                        return;

                    unitTarget->CastSpell(unitTarget, 28694, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 28702:                                 // Netherbloom
                {
                    if (!unitTarget)
                        return;

                    // 25% chance of casting a random buff
                    if (roll_chance_i(75))
                        return;

                    // triggered spells are 28703 to 28707
                    // Note: some sources say, that there was the possibility of
                    //       receiving a debuff. However, this seems to be removed by a patch.
                    const uint32 spellid = 28703;

                    // don't overwrite an existing aura
                    for (uint8 i = 0; i < 5; ++i)
                        if (unitTarget->HasAura(spellid + i, EFFECT_INDEX_0))
                            return;

                    unitTarget->CastSpell(unitTarget, spellid + urand(0, 4), TRIGGERED_OLD_TRIGGERED);
                    break;
                }
                case 28720:                                 // Nightmare Vine
                {
                    if (!unitTarget)
                        return;

                    // 25% chance of casting Nightmare Pollen
                    if (roll_chance_i(75))
                        return;

                    unitTarget->CastSpell(unitTarget, 28721, TRIGGERED_OLD_TRIGGERED);
                    break;
                }
            }
            break;
        }
    }

    // normal DB scripted effect
    if (!unitTarget)
        return;

    // Script based implementation. Must be used only for not good for implementation in core spell effects
    // So called only for not processed cases
    if (unitTarget->GetTypeId() == TYPEID_UNIT)
    {
        if (sScriptDevAIMgr.OnEffectScriptEffect(m_caster, m_spellInfo->Id, eff_idx, (Creature*)unitTarget, m_originalCasterGUID))
            return;
    }

    // Previous effect might have started script
    if (!ScriptMgr::CanSpellEffectStartDBScript(m_spellInfo, eff_idx))
        return;

    DEBUG_FILTER_LOG(LOG_FILTER_SPELL_CAST, "Spell ScriptStart spellid %u in EffectScriptEffect", m_spellInfo->Id);
    m_caster->GetMap()->ScriptsStart(sSpellScripts, m_spellInfo->Id, m_caster, unitTarget);
}

void Spell::EffectSanctuary(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    unitTarget->InterruptSpellsCastedOnMe(true);
    InstanceData* instance = unitTarget->GetInstanceData();
    if (instance && sWorld.getConfig(CONFIG_BOOL_INSTANCE_STRICT_COMBAT_LOCKDOWN) && instance->IsEncounterInProgress())
    {
        unitTarget->AttackStop(true, false, false);
        unitTarget->getHostileRefManager().addThreatPercent(-100);
    }
    else
        unitTarget->CombatStop(false, false);

    // Vanish allows to remove all threat and cast regular stealth so other spells can be used
    if (m_spellInfo->IsFitToFamily(SPELLFAMILY_ROGUE, uint64(0x0000000000000800)))
        ((Player*)unitTarget)->RemoveSpellsCausingAura(SPELL_AURA_MOD_ROOT);
}

void Spell::EffectAddComboPoints(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    if (damage <= 0)
        return;

    m_caster->AddComboPoints(unitTarget, damage);
}

void Spell::EffectDuel(SpellEffectIndex eff_idx)
{
    if (!m_caster || !unitTarget || m_caster->GetTypeId() != TYPEID_PLAYER || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* caster = (Player*)m_caster;
    Player* target = (Player*)unitTarget;

    // caster or target already have requested duel
    if (caster->duel || target->duel || !target->GetSocial() || target->GetSocial()->HasIgnore(caster->GetObjectGuid()))
        return;

    // Players can only fight a duel with each other outside (=not inside dungeons and not in capital cities)
    AreaTableEntry const* casterAreaEntry = GetAreaEntryByAreaID(caster->GetAreaId());
    if (casterAreaEntry && !(casterAreaEntry->flags & AREA_FLAG_DUEL))
    {
        SendCastResult(SPELL_FAILED_NO_DUELING);            // Dueling isn't allowed here
        return;
    }

    AreaTableEntry const* targetAreaEntry = GetAreaEntryByAreaID(target->GetAreaId());
    if (targetAreaEntry && !(targetAreaEntry->flags & AREA_FLAG_DUEL))
    {
        SendCastResult(SPELL_FAILED_NO_DUELING);            // Dueling isn't allowed here
        return;
    }

    // CREATE DUEL FLAG OBJECT
    GameObject* pGameObj = new GameObject;

    uint32 gameobject_id = m_spellInfo->EffectMiscValue[eff_idx];

    Map* map = m_caster->GetMap();
    float x = (m_caster->GetPositionX() + unitTarget->GetPositionX()) * 0.5f;
    float y = (m_caster->GetPositionY() + unitTarget->GetPositionY()) * 0.5f;
    float z = m_caster->GetPositionZ();
    m_caster->UpdateAllowedPositionZ(x, y, z);
    if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), gameobject_id, map, x, y, z, m_caster->GetOrientation()))
    {
        delete pGameObj;
        return;
    }

    pGameObj->SetUInt32Value(GAMEOBJECT_FACTION, m_caster->getFaction());
    pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel() + 1);

    pGameObj->SetRespawnTime(m_duration > 0 ? m_duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);

    m_caster->AddGameObject(pGameObj);
    map->Add(pGameObj);
    pGameObj->AIM_Initialize();

    // END

    // Send request
    WorldPacket data(SMSG_DUEL_REQUESTED, 8 + 8);
    data << pGameObj->GetObjectGuid();
    data << caster->GetObjectGuid();
    caster->GetSession()->SendPacket(data);
    target->GetSession()->SendPacket(data);

    // create duel-info
    DuelInfo* duel   = new DuelInfo;
    duel->initiator  = caster;
    duel->opponent   = target;
    duel->startTime  = 0;
    duel->startTimer = 0;
    caster->duel     = duel;

    DuelInfo* duel2   = new DuelInfo;
    duel2->initiator  = caster;
    duel2->opponent   = caster;
    duel2->startTime  = 0;
    duel2->startTimer = 0;
    target->duel      = duel2;

    caster->SetGuidValue(PLAYER_DUEL_ARBITER, pGameObj->GetObjectGuid());
    target->SetGuidValue(PLAYER_DUEL_ARBITER, pGameObj->GetObjectGuid());

    m_spellLog.AddLog(uint32(SPELL_EFFECT_DUEL), target->GetPackGUID());
}

void Spell::EffectStuck(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!sWorld.getConfig(CONFIG_BOOL_CAST_UNSTUCK))
        return;

    Player* player = (Player*)m_caster;

    DEBUG_LOG("Spell Effect: Stuck");
    DETAIL_LOG("Player %s (guid %u) used auto-unstuck feature at map %u (%f, %f, %f)", player->GetName(), player->GetGUIDLow(), player->GetMapId(), player->GetPositionX(), player->GetPositionY(), player->GetPositionZ());

    if (player->IsTaxiFlying())
        return;

    // If the player is dead, it will return them to the graveyard closest to their corpse.
    if (player->HasFlag(PLAYER_FLAGS, PLAYER_FLAGS_GHOST))
    {
        player->RepopAtGraveyard();
        return;
    }

    // If the player is alive, and their hearthstone is in their inventory, and their hearthstone
    // is cooled down, it will activate their hearthstone. The 30 minute hearthstone cooldown is activated as usual.
    if (player->IsSpellReady(8690) && player->HasItemCount(6948, 1, false))
    {
        player->TeleportToHomebind(TELE_TO_SPELL);
        // Trigger cooldown
        SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(8690);
        if (!spellInfo)
            return;
        Spell spell(player, spellInfo, TRIGGERED_OLD_TRIGGERED);
        spell.SendSpellCooldown();
    }
    else
    {
        // If the player is alive, but their hearthstone is either not in their inventory (e.g. in the bank) or
        // their hearthstone is on cooldown, then the game will try to "nudge" the player in a seemingly random direction.
        // @todo This check could possibly more accurately find a safe position to port to, has the potential for porting underground.
        float x, y, z;
        player->GetNearPoint(player, x, y, z, DEFAULT_WORLD_OBJECT_SIZE, 10.0f, player->GetOrientation());
        player->NearTeleportTo(x, y, z, player->GetOrientation());
    }
}

void Spell::EffectSummonPlayer(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    // Evil Twin (ignore player summon, but hide this for summoner)
    if (unitTarget->GetDummyAura(23445))
        return;

    float x, y, z;
    m_caster->GetPosition(x, y, z);

    ((Player*)unitTarget)->SetSummonPoint(m_caster->GetMapId(), x, y, z);

    WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
    data << m_caster->GetObjectGuid();                      // summoner guid
    data << uint32(m_caster->GetZoneId());                  // summoner zone
    data << uint32(MAX_PLAYER_SUMMON_DELAY * IN_MILLISECONDS); // auto decline after msecs
    ((Player*)unitTarget)->GetSession()->SendPacket(data);
}

static ScriptInfo generateActivateCommand()
{
    ScriptInfo si;
    si.command = SCRIPT_COMMAND_ACTIVATE_OBJECT;
    si.id = 0;
    si.buddyEntry = 0;
    si.searchRadiusOrGuid = 0;
    si.data_flags = 0x00;
    return si;
}

void Spell::EffectActivateObject(SpellEffectIndex eff_idx)
{
    if (!gameObjTarget)
        return;

    uint32 misc_value = m_spellInfo->EffectMiscValue[eff_idx];

    switch (misc_value)
    {
        case 3:                     // GO custom anim - found mostly in Lunar Fireworks spells
            gameObjTarget->SendGameObjectCustomAnim(gameObjTarget->GetObjectGuid());
            // no break: the GO is then used;
        case 1:                     // GO simple use
        case 2:                     // unk - 2 spells
        case 4:                     // unk - 1 spell
        case 5:                     // GO trap usage
        case 8:                     // GO usage with TargetB = none or random
        case 19:                    // unk - 1 spell
        case 20:                    // unk - 2 spells
        {
            // Specific case for Darkmoon Faire Cannon (this is probably a hint that our logic about GO use / activation is not accurate)
            switch (m_spellInfo->Id)
            {
                case 17731:         // Onyxia - Eruption
                case 24731:
                case 40964:         // Fel Crystalforge: Create 1 Flask
                case 40965:         // Fel Crystalforge: Create 5 Flasks
                case 40968:         // Bash'ir Crystalforge: Create 1 Flask
                case 40970:         // Bash'ir Crystalforge: Create 5 Flasks
                case 42868:
                    gameObjTarget->SendGameObjectCustomAnim(gameObjTarget->GetObjectGuid());
                    break;
                case 36546:         // no delay meant to happen - activate trap immediately
                case 38054:
                case 39844:
                    gameObjTarget->Use(m_caster, m_spellInfo);
                    break;
                default:
                {
                    static ScriptInfo activateCommand = generateActivateCommand();

                    int32 delay_secs = m_spellInfo->CalculateSimpleValue(eff_idx);

                    gameObjTarget->GetMap()->ScriptCommandStart(activateCommand, delay_secs * IN_MILLISECONDS, m_caster, gameObjTarget);
                    break;
                }
            }
            break;
        }
        case 7:                     // unk - 2 spells
        {
            gameObjTarget->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
            break;
        }
        case 10:                    // unk - 2 spells
        {
            gameObjTarget->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_LOCKED);
            gameObjTarget->ResetDoorOrButton();
            break;
        }
        case 12:                    // GO state active alternative - found mostly in Simon Game spells
            gameObjTarget->UseDoorOrButton(0, true);
            break;
        case 13:                    // GO state ready - found only in Simon Game spells
            gameObjTarget->ResetDoorOrButton();
            break;
        case 15:                    // GO destroy
            gameObjTarget->SetLootState(GO_JUST_DEACTIVATED);
            break;
        case 16:                    // GO custom use - found mostly in Wind Stones spells, Simon Game spells and other GO target summoning spells
        {
            switch (m_spellInfo->Id)
            {
                case 24734:         // Summon Templar Random
                case 24744:         // Summon Templar (fire)
                case 24756:         // Summon Templar (air)
                case 24758:         // Summon Templar (earth)
                case 24760:         // Summon Templar (water)
                case 24763:         // Summon Duke Random
                case 24765:         // Summon Duke (fire)
                case 24768:         // Summon Duke (air)
                case 24770:         // Summon Duke (earth)
                case 24772:         // Summon Duke (water)
                case 24784:         // Summon Royal Random
                case 24786:         // Summon Royal (fire)
                case 24788:         // Summon Royal (air)
                case 24789:         // Summon Royal (earth)
                case 24790:         // Summon Royal (water)
                {
                    uint32 npcEntry = 0;
                    uint32 templars[] = {15209, 15211, 15212, 15307};
                    uint32 dukes[] = {15206, 15207, 15208, 15220};
                    uint32 royals[] = {15203, 15204, 15205, 15305};

                    switch (m_spellInfo->Id)
                    {
                        case 24734: npcEntry = templars[urand(0, 3)]; break;
                        case 24763: npcEntry = dukes[urand(0, 3)];    break;
                        case 24784: npcEntry = royals[urand(0, 3)];   break;
                        case 24744: npcEntry = 15209;                 break;
                        case 24756: npcEntry = 15212;                 break;
                        case 24758: npcEntry = 15307;                 break;
                        case 24760: npcEntry = 15211;                 break;
                        case 24765: npcEntry = 15206;                 break;
                        case 24768: npcEntry = 15220;                 break;
                        case 24770: npcEntry = 15208;                 break;
                        case 24772: npcEntry = 15207;                 break;
                        case 24786: npcEntry = 15203;                 break;
                        case 24788: npcEntry = 15204;                 break;
                        case 24789: npcEntry = 15205;                 break;
                        case 24790: npcEntry = 15305;                 break;
                    }

                    gameObjTarget->SummonCreature(npcEntry, gameObjTarget->GetPositionX(), gameObjTarget->GetPositionY(), gameObjTarget->GetPositionZ(), gameObjTarget->GetAngle(m_caster), TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, MINUTE * IN_MILLISECONDS);
                    gameObjTarget->SetLootState(GO_JUST_DEACTIVATED);
                    break;
                }
                case 40176:         // Simon Game pre-game Begin, blue
                case 40177:         // Simon Game pre-game Begin, green
                case 40178:         // Simon Game pre-game Begin, red
                case 40179:         // Simon Game pre-game Begin, yellow
                case 40283:         // Simon Game END, blue
                case 40284:         // Simon Game END, green
                case 40285:         // Simon Game END, red
                case 40286:         // Simon Game END, yellow
                case 40494:         // Simon Game, switched ON
                case 40495:         // Simon Game, switched OFF
                case 40512:         // Simon Game, switch...disable Off switch
                    gameObjTarget->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
                    break;
                case 40632:         // Summon Gezzarak the Huntress
                case 40640:         // Summon Karrog
                case 40642:         // Summon Darkscreecher Akkarai
                case 40644:         // Summon Vakkiz the Windrager
                case 41004:         // Summon Terokk
                    gameObjTarget->SetLootState(GO_JUST_DEACTIVATED);
                    break;
                case 46592:         // Summon Ahune Lieutenant
                {
                    uint32 npcEntry = 0;

                    switch (gameObjTarget->GetEntry())
                    {
                        case 188049: npcEntry = 26116; break;       // Frostwave Lieutenant (Ashenvale)
                        case 188137: npcEntry = 26178; break;       // Hailstone Lieutenant (Desolace)
                        case 188138: npcEntry = 26204; break;       // Chillwind Lieutenant (Stranglethorn)
                        case 188148: npcEntry = 26214; break;       // Frigid Lieutenant (Searing Gorge)
                        case 188149: npcEntry = 26215; break;       // Glacial Lieutenant (Silithus)
                        case 188150: npcEntry = 26216; break;       // Glacial Templar (Hellfire Peninsula)
                    }

                    gameObjTarget->SummonCreature(npcEntry, gameObjTarget->GetPositionX(), gameObjTarget->GetPositionY(), gameObjTarget->GetPositionZ(), gameObjTarget->GetAngle(m_caster), TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, MINUTE * IN_MILLISECONDS);
                    gameObjTarget->SetLootState(GO_JUST_DEACTIVATED);
                    break;
                }
            }
            break;
        }
        case 17:                    // GO unlock - found mostly in Simon Game spells
            gameObjTarget->RemoveFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);
            break;
        default:
            sLog.outError("Spell::EffectActivateObject called with unknown misc value. Spell Id %u", m_spellInfo->Id);
            break;
    }
}

bool Spell::DoSummonTotem(CreatureSummonPositions& list, SpellEffectIndex eff_idx, uint8 slot_dbc)
{
    // DBC store slots starting from 1, with no slot 0 value)
    int slot = slot_dbc ? slot_dbc - 1 : TOTEM_SLOT_NONE;

    // unsummon old totem
    if (slot < MAX_TOTEM_SLOT)
        if (Totem* OldTotem = m_caster->GetTotem(TotemSlot(slot)))
            OldTotem->UnSummon();

    // FIXME: Setup near to finish point because GetObjectBoundingRadius set in Create but some Create calls can be dependent from proper position
    // if totem have creature_template_addon.auras with persistent point for example or script call

    CreatureCreatePos pos(m_caster->GetMap(), list[0].x, list[0].y, list[0].z, m_caster->GetOrientation());

    CreatureInfo const* cinfo = ObjectMgr::GetCreatureTemplate(m_spellInfo->EffectMiscValue[eff_idx]);
    if (!cinfo)
    {
        sLog.outErrorDb("Creature entry %u does not exist but used in spell %u totem summon.", m_spellInfo->Id, m_spellInfo->EffectMiscValue[eff_idx]);
        return false;
    }

    Totem* pTotem = new Totem;
    list[0].creature = pTotem;

    if (!pTotem->Create(m_caster->GetMap()->GenerateLocalLowGuid(HIGHGUID_UNIT), pos, cinfo, m_caster))
    {
        delete pTotem;
        return false;
    }

    pTotem->SetRespawnCoord(pos);

    if (slot < MAX_TOTEM_SLOT)
        m_caster->_AddTotem(TotemSlot(slot), pTotem);

    // pTotem->SetName("");                                 // generated by client
    pTotem->SetOwnerGuid(m_caster->GetObjectGuid());
    pTotem->setFaction(m_caster->getFaction());
    pTotem->SetLevel(m_caster->getLevel());
    pTotem->SetTypeBySummonSpell(m_spellInfo);              // must be after Create call where m_spells initialized

    pTotem->SetDuration(m_duration);

    if (damage)                                             // if not spell info, DB values used
    {
        pTotem->SetMaxHealth(damage);
        pTotem->SetHealth(damage);
    }

    pTotem->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
        pTotem->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);

    if (m_caster->IsImmuneToNPC())
        pTotem->SetImmuneToNPC(true);

    if (m_caster->IsImmuneToPlayer())
        pTotem->SetImmuneToPlayer(true);

    if (m_caster->IsPvP())
        pTotem->SetPvP(true);

    // sending SMSG_TOTEM_CREATED before add to map (done in Summon)
    if (slot < MAX_TOTEM_SLOT && m_caster->GetTypeId() == TYPEID_PLAYER)
    {
        WorldPacket data(SMSG_TOTEM_CREATED, 1 + 8 + 4 + 4);
        data << uint8(slot);
        data << pTotem->GetObjectGuid();
        data << uint32(m_duration);
        data << uint32(m_spellInfo->Id);
        ((Player*)m_caster)->SendDirectMessage(data);
    }

    pTotem->Summon(m_caster);

    OnSummon(pTotem);

    m_spellLog.AddLog(uint32(SPELL_EFFECT_SUMMON), pTotem->GetPackGUID());

    // everything is handled now
    // should return false to skip further handling
    return false;
}

bool Spell::DoSummonPossessed(CreatureSummonPositions& list, SummonPropertiesEntry const* prop, SpellEffectIndex effIdx, uint32 /*level*/)
{
    MANGOS_ASSERT(!list.empty() && prop);

    int32 const& creatureEntry = m_spellInfo->EffectMiscValue[effIdx];

    Unit* newUnit = m_caster->TakePossessOf(m_spellInfo, prop, effIdx, list[0].x, list[0].y, list[0].z, m_caster->GetOrientation());
    if (!newUnit)
    {
        sLog.outError("Spell::DoSummonPossessed: creature entry %d for spell %u could not be summoned.", creatureEntry, m_spellInfo->Id);
        return false;
    }

    list[0].creature = static_cast<Creature*>(newUnit);
    return true;
}

void Spell::EffectEnchantHeldItem(SpellEffectIndex eff_idx)
{
    // this is only item spell effect applied to main-hand weapon of target player (players in area)
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* item_owner = (Player*)unitTarget;
    Item* item = item_owner->GetItemByPos(INVENTORY_SLOT_BAG_0, EQUIPMENT_SLOT_MAINHAND);

    if (!item)
        return;

    // must be equipped
    if (!item ->IsEquipped())
        return;

    if (m_spellInfo->EffectMiscValue[eff_idx])
    {
        uint32 enchant_id = m_spellInfo->EffectMiscValue[eff_idx];
        int32 duration = m_duration;                        // Try duration index first...
        if (!duration)
            duration = m_currentBasePoints[eff_idx];        // Base points after...
        if (!duration)
            duration = 10;                                  // 10 seconds for enchants which don't have listed duration

        SpellItemEnchantmentEntry const* pEnchant = sSpellItemEnchantmentStore.LookupEntry(enchant_id);
        if (!pEnchant)
            return;

        // Always go to temp enchantment slot
        EnchantmentSlot slot = TEMP_ENCHANTMENT_SLOT;

        // Enchantment will not be applied if a different one already exists
        if (item->GetEnchantmentId(slot) && item->GetEnchantmentId(slot) != enchant_id)
            return;

        // Apply the temporary enchantment
        item->SetEnchantment(slot, enchant_id, duration * IN_MILLISECONDS, 0, m_caster->GetObjectGuid());

        // Improved Weapon Totems
        if (m_spellInfo->IsFitToFamilyMask(0x0000000004000000))
        {
            SpellAuraHolder* holder = m_caster->GetOwner()->GetSpellAuraHolder(29192);
            if (!holder)
                holder = m_caster->GetOwner()->GetSpellAuraHolder(29193);
            SpellEffectIndex dummyAuraIndex = m_spellInfo->SpellIconID == 1397 ? EFFECT_INDEX_0 : EFFECT_INDEX_1; // 0 - Windfury 1 - Flametongue
            if (holder && holder->m_auras[dummyAuraIndex] && holder->GetSpellProto())
                item->SetEnchantmentModifier(holder->m_auras[dummyAuraIndex]->GetModifier()->m_amount);
        }
        item_owner->ApplyEnchantment(item, slot, true);
    }
}

void Spell::EffectDisEnchant(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* p_caster = (Player*)m_caster;
    if (!itemTarget || !itemTarget->GetProto()->DisenchantID)
        return;

    p_caster->UpdateCraftSkill(m_spellInfo->Id);

    Loot*& loot = itemTarget->m_loot;
    if (!loot)
        loot = new Loot(p_caster, itemTarget, LOOT_DISENCHANTING);
    else
    {
        if (loot->GetLootType() != LOOT_DISENCHANTING)
        {
            delete loot;
            loot = new Loot(p_caster, itemTarget, LOOT_DISENCHANTING);
        }
    }

    loot->ShowContentTo(p_caster);

    // item will be removed at disenchanting end
}

void Spell::EffectInebriate(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = (Player*)unitTarget;
    uint16 currentDrunk = player->GetDrunkValue();
    uint16 drunkMod = damage * 256;
    if (currentDrunk + drunkMod > 0xFFFF)
        currentDrunk = 0xFFFF;
    else
        currentDrunk += drunkMod;
    player->SetDrunkValue(currentDrunk, m_CastItem ? m_CastItem->GetEntry() : 0);
}

void Spell::EffectFeedPet(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* _player = (Player*)m_caster;

    Item* foodItem = itemTarget;
    if (!foodItem)
        return;

    Pet* pet = _player->GetPet();
    if (!pet)
        return;

    if (!pet->IsAlive())
        return;

    int32 benefit = pet->GetCurrentFoodBenefitLevel(foodItem->GetProto()->ItemLevel);
    if (benefit <= 0)
        return;

    m_spellLog.AddLog(uint32(SPELL_EFFECT_FEED_PET), foodItem->GetEntry());
    // send log now before remove it from player inventory
    m_spellLog.SendToSet();

    uint32 count = 1;
    _player->DestroyItemCount(foodItem, count, true);
    // TODO: fix crash when a spell has two effects, both pointed at the same item target

    m_caster->CastCustomSpell(nullptr, m_spellInfo->EffectTriggerSpell[eff_idx], &benefit, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
}

void Spell::EffectDismissPet(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Pet* pet = m_caster->GetPet();

    // not let dismiss dead pet
    if (!pet || !pet->IsAlive())
        return;

    m_spellLog.AddLog(uint32(SPELL_EFFECT_DISMISS_PET), pet->GetPackGUID());
    // send log now before remove it from map to avoid "unknown" name
    m_spellLog.SendToSet();

    pet->Unsummon(PET_SAVE_NOT_IN_SLOT, m_caster);
}

void Spell::EffectSummonObject(SpellEffectIndex eff_idx)
{
    uint32 go_id = m_spellInfo->EffectMiscValue[eff_idx];

    uint8 slot;
    switch (m_spellInfo->Effect[eff_idx])
    {
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT1: slot = 0; break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT2: slot = 1; break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT3: slot = 2; break;
        case SPELL_EFFECT_SUMMON_OBJECT_SLOT4: slot = 3; break;
        default: return;
    }

    if (ObjectGuid guid = m_caster->m_ObjectSlotGuid[slot])
    {
        if (GameObject* obj = m_caster ? m_caster->GetMap()->GetGameObject(guid) : nullptr)
            obj->SetLootState(GO_JUST_DEACTIVATED);
        m_caster->m_ObjectSlotGuid[slot].Clear();
    }

    GameObject* pGameObj = new GameObject;

    float x, y, z;
    // If dest location if present
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(x, y, z);
    // Summon in random point all other units if location present
    else
        m_caster->GetClosePoint(x, y, z, DEFAULT_WORLD_OBJECT_SIZE);

    Map* map = m_caster->GetMap();
    if (!pGameObj->Create(map->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), go_id, map,
                          x, y, z, m_caster->GetOrientation(), 0.0f, 0.0f, 0.0f, 0.0f, GO_ANIMPROGRESS_DEFAULT, GO_STATE_READY))
    {
        delete pGameObj;
        return;
    }

    pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel());
    pGameObj->SetRespawnTime(m_duration > 0 ? m_duration / IN_MILLISECONDS : 0);
    pGameObj->SetSpellId(m_spellInfo->Id);
    m_caster->AddGameObject(pGameObj);

    map->Add(pGameObj);
    pGameObj->AIM_Initialize();

    WorldPacket data(SMSG_GAMEOBJECT_SPAWN_ANIM_OBSOLETE, 8);
    data << ObjectGuid(pGameObj->GetObjectGuid());
    m_caster->SendMessageToSet(data, true);

    m_caster->m_ObjectSlotGuid[slot] = pGameObj->GetObjectGuid();

    // Notify Summoner
    if (m_originalCaster && (m_originalCaster != m_caster) && (m_originalCaster->AI()))
        m_originalCaster->AI()->JustSummoned(pGameObj);
    else if (m_caster->AI())
        m_caster->AI()->JustSummoned(pGameObj);

    m_spellLog.AddLog(m_spellInfo->Effect[eff_idx], pGameObj->GetPackGUID());

    if (GameObject* linkedGO = pGameObj->GetLinkedTrap())
        m_spellLog.AddLog(m_spellInfo->Effect[eff_idx], linkedGO->GetPackGUID());
}

void Spell::EffectResurrect(SpellEffectIndex eff_idx)
{
    if (!unitTarget && !corpseTarget)
        return;

    switch (m_spellInfo->Id)
    {
        case 8342:                                          // Defibrillate (Goblin Jumper Cables) has 33% chance on success
        case 22999:                                         // Defibrillate (Goblin Jumper Cables XL) has 50% chance on success
        {
            uint32 failChance = 0;
            uint32 failSpellId = 0;
            switch (m_spellInfo->Id)
            {
                case 8342:  failChance = 67; failSpellId = 8338;  break;
                case 22999: failChance = 50; failSpellId = 23055; break;
            }

            if (roll_chance_i(failChance))
            {
                if (failSpellId)
                    m_caster->CastSpell(m_caster, failSpellId, TRIGGERED_OLD_TRIGGERED, m_CastItem);
                return;
            }
            break;
        }
        default: break;
    }

    uint32 effectId = m_spellInfo->Effect[eff_idx];
    Player* player = nullptr;

    if (unitTarget) // thread safe version
    {
        if (unitTarget->IsAlive() || unitTarget->GetTypeId() != TYPEID_PLAYER || !unitTarget->IsInWorld())
            return;

        player = static_cast<Player*>(unitTarget);
    }

    auto const computator = [](Player* player, uint32& health, uint32& mana, uint32 effectId, int32 damage, int32 miscValue)
    {
        if (effectId == SPELL_EFFECT_RESURRECT_NEW)
        {
            health = damage;
            mana = miscValue;
        }
        else
        {
            health = player->GetMaxHealth() * damage / 100;
            mana = player->GetMaxPower(POWER_MANA) * damage / 100;
        }
    };

    if (corpseTarget)
    {
        if (!corpseTarget->IsInWorld())
            return;

        player = m_caster->GetMap()->GetPlayer(corpseTarget->GetOwnerGuid());
        if (!player) // thread unsafe version - corpse and player in different maps
        {
            std::string sentName = m_caster->GetTypeId() == TYPEID_PLAYER ? "" : m_caster->GetName();
            sWorld.GetMessager().AddMessage([playerGuid = corpseTarget->GetOwnerGuid(), position = m_caster->GetPosition(), casterGuid = m_caster->GetObjectGuid(),
                effectId, damage = damage, spellInfo = m_spellInfo, eff_idx = eff_idx, mapId = m_caster->GetMapId(), isSpiritHealer = m_caster->isSpiritHealer(), sentName, computator](World* world)
            {
                if (Player* player = ObjectAccessor::FindPlayer(playerGuid))
                {
                    if (player->isRessurectRequested()) // already have one active request
                        return;
                    uint32 health;
                    uint32 mana;
                    computator(player, health, mana, spellInfo->Effect[eff_idx], damage, spellInfo->EffectMiscValue[eff_idx]);
                    char const* name = sentName.data();
                    if (!casterGuid.IsPlayer())
                        sObjectMgr.GetCreatureLocaleStrings(casterGuid.GetEntry(), player->GetSession()->GetSessionDbLocaleIndex(), &name);
                    player->AddResurrectRequest(casterGuid, spellInfo, position, mapId, health, mana, isSpiritHealer, name);
                }
            });
        }
    }

    if (player)
    {
        if (player->isRessurectRequested()) // already have one active request
            return;

        uint32 health, mana;
        computator(player, health, mana, m_spellInfo->Effect[eff_idx], damage, m_spellInfo->EffectMiscValue[eff_idx]);

        player->AddResurrectRequest(m_caster->GetObjectGuid(), m_spellInfo, m_caster->GetPosition(), m_caster->GetMapId(), health, mana, m_caster->isSpiritHealer(),
            m_caster->GetTypeId() == TYPEID_PLAYER ? "" : m_caster->GetNameForLocaleIdx(player->GetSession()->GetSessionDbLocaleIndex()));
    }
}

void Spell::EffectAddExtraAttacks(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || !unitTarget->IsAlive())
        return;

    if (unitTarget->m_extraAttacks)
        return;

    unitTarget->m_extraAttacks = damage;
    m_spellLog.AddLog(uint32(SPELL_EFFECT_ADD_EXTRA_ATTACKS), unitTarget->GetPackGUID(), damage);
}

void Spell::EffectParry(SpellEffectIndex /*eff_idx*/)
{
    m_caster->SetCanParry(true);
}

void Spell::EffectBlock(SpellEffectIndex /*eff_idx*/)
{
    m_caster->SetCanBlock(true);
}

void Spell::EffectLeapForward(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    float x, y, z;
    m_targets.getDestination(x, y, z);

    float orientation = unitTarget->GetOrientation();

    unitTarget->NearTeleportTo(x, y, z, orientation, unitTarget == m_caster);
}

void Spell::EffectLeapBack(SpellEffectIndex eff_idx)
{
    if (unitTarget->IsTaxiFlying())
        return;

    m_caster->KnockBackFrom(unitTarget, float(m_spellInfo->EffectMiscValue[eff_idx]) / 10, float(damage) / 10);
}

void Spell::EffectReputation(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* _player = (Player*)unitTarget;

    int32  rep_change = m_currentBasePoints[eff_idx];
    uint32 faction_id = m_spellInfo->EffectMiscValue[eff_idx];

    FactionEntry const* factionEntry = sFactionStore.LookupEntry<FactionEntry>(faction_id);

    if (!factionEntry)
        return;

    rep_change = _player->CalculateReputationGain(REPUTATION_SOURCE_SPELL, rep_change, 0, faction_id);

    _player->GetReputationMgr().ModifyReputation(factionEntry, rep_change);
}

void Spell::EffectQuestComplete(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    uint32 quest_id = m_spellInfo->EffectMiscValue[eff_idx];
    ((Player*)unitTarget)->AreaExploredOrEventHappens(quest_id);
}

void Spell::EffectSelfResurrect(SpellEffectIndex eff_idx)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;
    Player* player = static_cast<Player*>(m_caster);

    uint32 health;
    uint32 mana = 0;

    // flat case
    if (damage < 0)
    {
        health = uint32(-damage);
        mana = m_spellInfo->EffectMiscValue[eff_idx];
    }
    // percent case
    else
    {
        health = uint32(damage / 100.0f * player->GetMaxHealth());
        if (player->GetMaxPower(POWER_MANA) > 0)
            mana = uint32(damage / 100.0f * player->GetMaxPower(POWER_MANA));
    }

    player->ResurrectPlayer(0.0f);

    player->SetHealth(health);
    player->SetPower(POWER_MANA, mana);
    player->SetPower(POWER_RAGE, 0);
    player->SetPower(POWER_ENERGY, player->GetMaxPower(POWER_ENERGY));

    player->SpawnCorpseBones();
}

void Spell::EffectSkinning(SpellEffectIndex /*eff_idx*/)
{
    if (unitTarget->GetTypeId() != TYPEID_UNIT)
        return;
    if (!m_caster || m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Creature* creature = (Creature*) unitTarget;
    int32 targetLevel = creature->getLevel();

    uint32 skill = creature->GetCreatureInfo()->GetRequiredLootSkill();

    Loot*& loot = unitTarget->m_loot;

    if (loot)
    {
        if (loot->GetLootType() != LOOT_SKINNING)
        {
            delete loot;
            loot = nullptr;
        }
    }

    if (!loot)
    {
        loot = new Loot((Player*)m_caster, creature, LOOT_SKINNING);

        int32 reqValue = targetLevel < 10 ? 0 : targetLevel < 20 ? (targetLevel - 10) * 10 : targetLevel * 5;

        int32 skillValue = ((Player*)m_caster)->GetSkillValuePure(skill);

        // Double chances for elites
        ((Player*)m_caster)->UpdateGatherSkill(skill, skillValue, reqValue, creature->IsElite() ? 2 : 1);
    }

    loot->ShowContentTo((Player*)m_caster);
    creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
}

void Spell::EffectCharge(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || !m_caster)
        return;

    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        ((Creature*)unitTarget)->StopMoving();

    // charge changes fall time
    if (m_caster->GetTypeId() == TYPEID_PLAYER)
        static_cast<Player*>(m_caster)->SetFallInformation(0, m_caster->GetPositionZ());

    const float speed = (m_spellInfo->speed != 0.f ? m_spellInfo->speed : BASE_CHARGE_SPEED);

    m_caster->GetMotionMaster()->MoveCharge(*unitTarget, speed, m_spellInfo->Id);

    // Players: charge against hostiles initiates auto-attack
    // TODO: This is executed after spell effects. Verify if this should be executed before spell effects
    if (m_caster->IsClientControlled() && m_caster->CanAttackNow(unitTarget) && m_caster->CanAttackSpell(unitTarget, m_spellInfo))
        m_caster->Attack(unitTarget, !m_spellInfo->HasAttribute(SPELL_ATTR_RANGED));
}

void Spell::EffectChargeDest(SpellEffectIndex /*eff_idx*/)
{
    if ((m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION) == 0)
        return;

    float x, y, z;
    m_targets.getDestination(x, y, z);
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        ((Creature*)m_caster)->StopMoving();

    float speed = m_spellInfo->speed ? m_spellInfo->speed : BASE_CHARGE_SPEED;

    m_caster->GetMotionMaster()->MoveCharge(x, y, z, speed, m_spellInfo->Id);
}


bool Spell::DoSummonCritter(CreatureSummonPositions& list, SummonPropertiesEntry const* prop, SpellEffectIndex effIdx, uint32 /*level*/)
{
    MANGOS_ASSERT(!list.empty() && prop);

    // ATM only first position is supported for summoning
    uint32 pet_entry = m_spellInfo->EffectMiscValue[effIdx];
    CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(pet_entry);
    if (!cInfo)
    {
        sLog.outErrorDb("Spell::DoSummonCritter: creature entry %u not found for spell %u.", pet_entry, m_spellInfo->Id);
        return false;
    }

    Pet* old_critter = m_caster->GetMiniPet();

    // for same pet just despawn (player unsummon command)
    if (m_caster->GetTypeId() == TYPEID_PLAYER && old_critter && old_critter->GetEntry() == pet_entry)
    {
        m_caster->RemoveMiniPet();
        return false;
    }

    // despawn old pet before summon new
    if (old_critter)
        m_caster->RemoveMiniPet();

    // for (CreatureSummonPositions::iterator itr = list.begin(); itr != list.end(); ++itr)
    CreatureCreatePos pos(m_caster->GetMap(), list[0].x, list[0].y, list[0].z, m_caster->GetOrientation());

    // summon new pet
    Pet* critter = new Pet(MINI_PET);

    uint32 pet_number = sObjectMgr.GeneratePetNumber();
    if (!critter->Create(m_caster->GetMap()->GenerateLocalLowGuid(HIGHGUID_PET), pos, cInfo, pet_number))
    {
        sLog.outError("Spell::EffectSummonCritter, spellid %u: no such creature entry %u", m_spellInfo->Id, pet_entry);
        delete critter;
        return false;
    }

    critter->SetLoading(true);

    // itr!
    list[0].creature = critter;

    critter->SetRespawnCoord(pos);

    // critter->SetName("");                                // generated by client
    critter->SetOwnerGuid(m_caster->GetObjectGuid());
    critter->setFaction(m_caster->getFaction());
    critter->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);
    critter->SelectLevel();                                 // some summoned critters have different from 1 DB data for level/hp
    const CreatureInfo* info = critter->GetCreatureInfo();
    // Some companions have additional UNIT_FLAG_NON_ATTACKABLE (0x2), perphaps coming from template, so add template flags
    critter->SetUInt32Value(UNIT_FIELD_FLAGS, info->UnitFlags);
    critter->SetUInt32Value(UNIT_NPC_FLAGS, info->NpcFlags);// some companions may have quests, so they need npc flags
    critter->InitPetCreateSpells();                         // some companions may have spells (e.g. disgusting oozeling)
    if (m_duration > 0)                                     // set timer for unsummon
        critter->SetDuration(m_duration);

    m_caster->SetMiniPet(critter);

    if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        critter->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        critter->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
    }
    else
        critter->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

    // NOTE: All companions should have these (creatureinfo needs to be tuned accordingly before we can remove these two lines):
    critter->SetImmuneToNPC(true);
    critter->SetImmuneToPlayer(true);
    critter->SetLoading(false);

    // NOTE: Do not set PvP flags (confirmed) for companions.

    return true;
}

void Spell::EffectKnockBack(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    switch (m_spellInfo->Id)
    {
        case 36812:                                     // Soaring - Test Flight quests
        case 37910:
        case 37962:
        case 37968:
            unitTarget->RemoveAurasDueToSpell(36801); // Remove Cannon Channel to prevent root affecting knockback
            break;
        case 37852:                                     // Watery Grave Explosion
            if (m_triggeredByAuraSpell)
                unitTarget->RemoveAurasDueToSpell(m_triggeredByAuraSpell->Id); // Remove Watery Grave to prevent root affecting knockback
            break;
    }

    unitTarget->KnockBackFrom(m_caster, float(m_spellInfo->EffectMiscValue[eff_idx]) / 10, float(damage) / 10);
}

void Spell::EffectSendTaxi(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    ((Player*)unitTarget)->ActivateTaxiPathTo(m_spellInfo->EffectMiscValue[eff_idx], m_spellInfo->Id);
}

void Spell::EffectPullTowards(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    float x, y, z, dist;

    if (m_spellInfo->Effect[eff_idx] == SPELL_EFFECT_PULL_TOWARDS)
    {
        z = m_caster->GetPositionZ();
        dist = unitTarget->GetDistance(m_caster, false);
    }
    else // SPELL_EFFECT_PULL_TOWARDS_DEST
    {
        m_targets.getDestination(x, y, z);
        dist = sqrt(unitTarget->GetDistance2d(x, y, DIST_CALC_NONE));
    }

    if (damage && dist > damage)
        dist = float(damage);

    if (dist < 0.1f)
        return;

    // Projectile motion
    float speedXY = float(m_spellInfo->EffectMiscValue[eff_idx]) * 0.1f;
    float time = dist / speedXY;
    float speedZ = ((z - unitTarget->GetPositionZ()) + 0.5f * time * time * Movement::gravity) / time;

    unitTarget->KnockBackFrom(m_caster, -speedXY, speedZ);
}

void Spell::EffectSummonDeadPet(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* _player = static_cast<Player*>(m_caster);
    Pet* pet = _player->GetPet();
    if (!pet)
    {
        pet = new Pet();
        if (!pet->LoadPetFromDB(_player, 0, 0, false, damage))
            delete pet;
        // if above successfully loaded the pet all is done
        return;
    }
    if (pet->IsAlive())
        return;

    if (_player->GetDistance(pet) >= 2.0f)
    {
        pet->ResetCorpseRespawn(); // need to absolutely make sure pet is visible - despawned corpse - invisible - assert
        float x, y, z; // this effect is destination targeted
        m_targets.getDestination(x, y, z);
        pet->NearTeleportTo(x, y, z, -m_caster->GetOrientation());
    }

    pet->SetUInt32Value(UNIT_DYNAMIC_FLAGS, UNIT_DYNFLAG_NONE);
    pet->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_SKINNABLE);
    pet->SetDeathState(ALIVE);
    pet->clearUnitState(static_cast<uint32>(UNIT_STAT_ALL_STATE));
    pet->SetHealth(uint32(pet->GetMaxHealth() * (float(damage) / 100)));

    // _player->PetSpellInitialize(); // action bar not removed at death and not required send at revive
    pet->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
}

void Spell::EffectDestroyAllTotems(SpellEffectIndex /*eff_idx*/)
{
    int32 mana = 0;
    for (int slot = 0;  slot < MAX_TOTEM_SLOT; ++slot)
    {
        if (Totem* totem = m_caster->GetTotem(TotemSlot(slot)))
        {
            if (damage)
            {
                uint32 spell_id = totem->GetUInt32Value(UNIT_CREATED_BY_SPELL);
                if (SpellEntry const* spellInfo = sSpellTemplate.LookupEntry<SpellEntry>(spell_id))
                {
                    uint32 manacost = spellInfo->manaCost + m_caster->GetCreateMana() * spellInfo->ManaCostPercentage / 100;
                    mana += manacost * damage / 100;
                }
            }
            totem->UnSummon();
        }
    }

    if (mana)
        m_caster->CastCustomSpell(m_caster, 39104, &mana, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
}

void Spell::EffectDurabilityDamage(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = m_spellInfo->EffectMiscValue[eff_idx];

    // FIXME: some spells effects have value -1/-2
    // Possibly its mean -1 all player equipped items and -2 all items
    if (slot < 0)
    {
        ((Player*)unitTarget)->DurabilityPointsLossAll(damage, (slot < -1));
        return;
    }

    // invalid slot value
    if (slot >= INVENTORY_SLOT_BAG_END)
        return;

    if (Item* item = ((Player*)unitTarget)->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        ((Player*)unitTarget)->DurabilityPointsLoss(item, damage);
}

void Spell::EffectDurabilityDamagePCT(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    int32 slot = m_spellInfo->EffectMiscValue[eff_idx];

    // FIXME: some spells effects have value -1/-2
    // Possibly its mean -1 all player equipped items and -2 all items
    if (slot < 0)
    {
        ((Player*)unitTarget)->DurabilityLossAll(double(damage) / 100.0f, (slot < -1));
        return;
    }

    // invalid slot value
    if (slot >= INVENTORY_SLOT_BAG_END)
        return;

    if (damage <= 0)
        return;

    if (Item* item = ((Player*)unitTarget)->GetItemByPos(INVENTORY_SLOT_BAG_0, slot))
        ((Player*)unitTarget)->DurabilityLoss(item, double(damage) / 100.0f);
}

void Spell::EffectModifyThreatPercent(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    unitTarget->getThreatManager().modifyThreatPercent(m_caster, damage);
}

void Spell::EffectTransmitted(SpellEffectIndex eff_idx)
{
    uint32 name_id = m_spellInfo->EffectMiscValue[eff_idx];

    switch (m_spellInfo->Id)
    {
        case 29886: // Create Soulwell
            if (m_caster->HasAura(18692))
                name_id = 183510;
            else if (m_caster->HasAura(18693))
                name_id = 183511;
            break;
        default:
            break;
    }

    GameObjectInfo const* goinfo = ObjectMgr::GetGameObjectInfo(name_id);

    if (!goinfo)
    {
        sLog.outErrorDb("Gameobject (Entry: %u) not exist and not created at spell (ID: %u) cast", name_id, m_spellInfo->Id);
        return;
    }

    float fx, fy, fz;

    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(fx, fy, fz);
    // FIXME: this can be better check for most objects but still hack
    else if (m_spellInfo->EffectRadiusIndex[eff_idx] && m_spellInfo->speed == 0)
    {
        float dis = GetSpellRadius(sSpellRadiusStore.LookupEntry(m_spellInfo->EffectRadiusIndex[eff_idx]));
        m_caster->GetClosePoint(fx, fy, fz, DEFAULT_WORLD_OBJECT_SIZE, dis);
    }
    else
    {
        float min_dis = GetSpellMinRange(sSpellRangeStore.LookupEntry(m_spellInfo->rangeIndex));
        float max_dis = GetSpellMaxRange(sSpellRangeStore.LookupEntry(m_spellInfo->rangeIndex));
        float dis = rand_norm_f() * (max_dis - min_dis) + min_dis;

        // special code for fishing bobber (TARGET_LOCATION_CASTER_FISHING_SPOT), should not try to avoid objects
        // nor try to find ground level, but randomly vary in angle
        if (goinfo->type == GAMEOBJECT_TYPE_FISHINGNODE)
        {
            // calculate angle variation for roughly equal dimensions of target area
            float max_angle = (max_dis - min_dis) / (max_dis + m_caster->GetObjectBoundingRadius());
            float angle_offset = max_angle * (rand_norm_f() - 0.5f);
            m_caster->GetNearPoint2d(fx, fy, dis + m_caster->GetObjectBoundingRadius(), m_caster->GetOrientation() + angle_offset);

            GridMapLiquidData liqData;
            if (!m_caster->GetTerrain()->IsInWater(fx, fy, m_caster->GetPositionZ() + 1.f, &liqData))
            {
                SendCastResult(SPELL_FAILED_NOT_FISHABLE);
                SendChannelUpdate(0);
                return;
            }

            fz = liqData.level;
            // finally, check LoS
            if (!m_caster->IsWithinLOS(fx, fy, fz))
            {
                SendCastResult(SPELL_FAILED_LINE_OF_SIGHT);
                SendChannelUpdate(0);
                return;
            }
        }
        else
            m_caster->GetClosePoint(fx, fy, fz, DEFAULT_WORLD_OBJECT_SIZE, dis);
    }

    Map* cMap = m_caster->GetMap();


    // if gameobject is summoning object, it should be spawned right on caster's position
    if (goinfo->type == GAMEOBJECT_TYPE_SUMMONING_RITUAL)
    {
        m_caster->GetPosition(fx, fy, fz);
    }

    GameObject* pGameObj = new GameObject;

    if (!pGameObj->Create(cMap->GenerateLocalLowGuid(HIGHGUID_GAMEOBJECT), name_id, cMap,
                          fx, fy, fz, m_caster->GetOrientation()))
    {
        delete pGameObj;
        return;
    }

    int32 duration = m_duration;

    switch (goinfo->type)
    {
        case GAMEOBJECT_TYPE_FISHINGNODE:
        {
            m_caster->SetChannelObject(pGameObj);
            m_caster->AddGameObject(pGameObj);              // will removed at spell cancel

            // end time of range when possible catch fish (FISHING_BOBBER_READY_TIME..GetDuration(m_spellInfo))
            // start time == fish-FISHING_BOBBER_READY_TIME (0..GetDuration(m_spellInfo)-FISHING_BOBBER_READY_TIME)
            int32 lastSec = 0;
            switch (urand(0, 3))
            {
                case 0: lastSec =  3; break;
                case 1: lastSec =  7; break;
                case 2: lastSec = 13; break;
                case 3: lastSec = 17; break;
            }

            duration = duration - lastSec * IN_MILLISECONDS + FISHING_BOBBER_READY_TIME * IN_MILLISECONDS;
            break;
        }
        case GAMEOBJECT_TYPE_SUMMONING_RITUAL:
        {
            if (m_caster->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = (Player*)m_caster;
                pGameObj->AddUniqueUse(player);
                pGameObj->SetActionTarget(player->GetSelectionGuid());
                m_caster->AddGameObject(pGameObj);          // will removed at spell cancel
            }
            break;
        }
        case GAMEOBJECT_TYPE_SPELLCASTER:
        {
            m_caster->AddGameObject(pGameObj);
            break;
        }
        // Other GO types have startOpen attribute but only GAMEOBJECT_TYPE_BUTTON is used by spells
        case GAMEOBJECT_TYPE_BUTTON:
        {
            // Change GO state if it is supposed to be already activated at summoning
            pGameObj->SetGoState((goinfo->button.startOpen ? GO_STATE_ACTIVE : GO_STATE_READY));
            break;
        }
        case GAMEOBJECT_TYPE_FISHINGHOLE:
        case GAMEOBJECT_TYPE_CHEST:
        default:
            break;
    }

    pGameObj->SetRespawnTime(duration > 0 ? duration / IN_MILLISECONDS : 0);

    pGameObj->SetOwnerGuid(m_caster->GetObjectGuid());

    pGameObj->SetUInt32Value(GAMEOBJECT_LEVEL, m_caster->getLevel());
    pGameObj->SetSpellId(m_spellInfo->Id);

    DEBUG_LOG("AddObject at SpellEfects.cpp EffectTransmitted");
    // m_caster->AddGameObject(pGameObj);
    // m_ObjToDel.push_back(pGameObj);

    cMap->Add(pGameObj);

    // Notify Summoner
    if (m_originalCaster && (m_originalCaster != m_caster) && (m_originalCaster->AI()))
        m_originalCaster->AI()->JustSummoned(pGameObj);
    else if (m_caster->AI())
        m_caster->AI()->JustSummoned(pGameObj);

    OnSummon(pGameObj);

    m_spellLog.AddLog(uint32(SPELL_EFFECT_TRANS_DOOR), pGameObj->GetPackGUID());

    if (GameObject* linkedGO = pGameObj->GetLinkedTrap())
    {
        OnSummon(linkedGO);
        m_spellLog.AddLog(uint32(SPELL_EFFECT_TRANS_DOOR), linkedGO->GetPackGUID());
    }
}

void Spell::EffectProspecting(SpellEffectIndex /*eff_idx*/)
{
    if (m_caster->GetTypeId() != TYPEID_PLAYER || !itemTarget)
        return;

    Player* p_caster = (Player*)m_caster;

    if (sWorld.getConfig(CONFIG_BOOL_SKILL_PROSPECTING))
    {
        uint32 SkillValue = p_caster->GetSkillValuePure(SKILL_JEWELCRAFTING);
        uint32 reqSkillValue = itemTarget->GetProto()->RequiredSkillRank;
        p_caster->UpdateGatherSkill(SKILL_JEWELCRAFTING, SkillValue, reqSkillValue);
    }

    Loot*& loot = itemTarget->m_loot;
    delete loot;

    loot = new Loot(p_caster, itemTarget, LOOT_PROSPECTING);

    loot->ShowContentTo(p_caster);
}

void Spell::EffectSkill(SpellEffectIndex /*eff_idx*/)
{
    DEBUG_LOG("WORLD: SkillEFFECT");
}

void Spell::EffectSpiritHeal(SpellEffectIndex /*eff_idx*/)
{
    // TODO player can't see the heal-animation - he should respawn some ticks later
    if (!unitTarget || unitTarget->IsAlive())
        return;
    if (unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;
    if (!unitTarget->IsInWorld())
        return;
    if (m_spellInfo->Id == 22012 && !unitTarget->HasAura(2584))
        return;

    ((Player*)unitTarget)->ResurrectPlayer(1.0f);
    ((Player*)unitTarget)->SpawnCorpseBones();
}

// remove insignia spell effect
void Spell::EffectSkinPlayerCorpse(SpellEffectIndex /*eff_idx*/)
{
    DEBUG_LOG("Effect: SkinPlayerCorpse");
    if (m_caster->GetTypeId() != TYPEID_PLAYER)
        return;

    if (!unitTarget && !corpseTarget)
        return;

    if (unitTarget)
        static_cast<Player*>(unitTarget)->RemovedInsignia(static_cast<Player*>(m_caster));
    if (corpseTarget) // thread safe because all must be in same battleground map
        if (Player* player = m_caster->GetMap()->GetPlayer(corpseTarget->GetOwnerGuid()))
            player->RemovedInsignia(static_cast<Player*>(m_caster));
}

void Spell::EffectStealBeneficialBuff(SpellEffectIndex eff_idx)
{
    DEBUG_LOG("Effect: StealBeneficialBuff");

    if (!unitTarget || unitTarget == m_caster)              // can't steal from self
        return;

    std::list <std::pair<SpellAuraHolder*, uint32> > dispelList;
    // Create dispel mask by dispel type
    uint32 dispelMask  = GetDispellMask(DispelType(m_spellInfo->EffectMiscValue[eff_idx]));
    Unit::SpellAuraHolderMap const& auras = unitTarget->GetSpellAuraHolderMap();
    for (const auto& aura : auras)
    {
        SpellAuraHolder* holder = aura.second;
        if (holder && (1 << holder->GetSpellProto()->Dispel) & dispelMask)
        {
            // Need check for passive? this
            if (holder->IsPositive() && !holder->IsPassive() && !holder->GetSpellProto()->HasAttribute(SPELL_ATTR_EX4_NOT_STEALABLE))
                dispelList.emplace_back(holder, holder->GetStackAmount());
        }
    }
    std::list<std::pair<SpellAuraHolder*, uint32> > successList;
    std::list <uint32> failList;
    ProcessDispelList(dispelList, successList, failList);
    // Ok if exist some buffs for dispel try dispel it
    // Really try steal and send log
    if (!successList.empty())
    {
        int32 count = successList.size();
        WorldPacket data(SMSG_SPELLSTEALLOG, 8 + 8 + 4 + 1 + 4 + count * 5);
        data << unitTarget->GetPackGUID();       // Victim GUID
        data << m_caster->GetPackGUID();         // Caster GUID
        data << uint32(m_spellInfo->Id);         // Dispell spell id
        data << uint8(0);                        // not used
        data << uint32(count);                   // count
        for (auto& spellstealSpell : successList)
        {
            SpellEntry const* spellInfo = spellstealSpell.first->GetSpellProto();
            data << uint32(spellInfo->Id);       // Spell Id
            data << uint8(0);                    // 0 - steals !=0 transfers
            unitTarget->RemoveAurasDueToSpellBySteal(spellstealSpell.first, m_caster);
        }
        m_caster->SendMessageToSet(data, true);
    }
    // Send fail log to client
    if (!failList.empty())
    {
        // Failed to dispel
        WorldPacket data(SMSG_DISPEL_FAILED, 8 + 8 + 4 + 4 * failList.size());
        data << m_caster->GetObjectGuid();              // Caster GUID
        data << unitTarget->GetObjectGuid();            // Victim GUID
        data << uint32(m_spellInfo->Id);                // Dispel spell id
        for (std::list< uint32 >::iterator j = failList.begin(); j != failList.end(); ++j)
            data << uint32(*j);                         // Spell Id
        m_caster->SendMessageToSet(data, true);
    }
}

void Spell::EffectKillCreditGroup(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    ((Player*)unitTarget)->RewardPlayerAndGroupAtEventCredit(m_spellInfo->EffectMiscValue[eff_idx], unitTarget);
}

void Spell::EffectQuestFail(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    ((Player*)unitTarget)->FailQuest(m_spellInfo->EffectMiscValue[eff_idx]);
}

void Spell::EffectPlaySound(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    uint32 soundId = m_spellInfo->EffectMiscValue[eff_idx];
    if (!sSoundEntriesStore.LookupEntry(soundId))
    {
        sLog.outError("EffectPlaySound: Sound (Id: %u) in spell %u does not exist.", soundId, m_spellInfo->Id);
        return;
    }

    unitTarget->PlayDirectSound(soundId, PlayPacketParameters(PLAY_TARGET, (Player*)unitTarget));
}

void Spell::EffectPlayMusic(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    uint32 soundId = m_spellInfo->EffectMiscValue[eff_idx];
    if (!sSoundEntriesStore.LookupEntry(soundId))
    {
        sLog.outError("EffectPlayMusic: Sound (Id: %u) in spell %u does not exist.", soundId, m_spellInfo->Id);
        return;
    }

    m_caster->PlayMusic(soundId, PlayPacketParameters(PLAY_TARGET, (Player*)unitTarget));
}

void Spell::EffectBind(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || unitTarget->GetTypeId() != TYPEID_PLAYER)
        return;

    Player* player = (Player*)unitTarget;

    uint32 area_id;
    WorldLocation loc;
    player->GetPosition(loc);
    area_id = player->GetAreaId();

    player->SetHomebindToLocation(loc, area_id);

    // binding
    WorldPacket data(SMSG_BINDPOINTUPDATE, (4 + 4 + 4 + 4 + 4));
    data << float(loc.coord_x);
    data << float(loc.coord_y);
    data << float(loc.coord_z);
    data << uint32(loc.mapid);
    data << uint32(area_id);
    player->SendDirectMessage(data);

    DEBUG_LOG("New Home Position X is %f", loc.coord_x);
    DEBUG_LOG("New Home Position Y is %f", loc.coord_y);
    DEBUG_LOG("New Home Position Z is %f", loc.coord_z);
    DEBUG_LOG("New Home MapId is %u", loc.mapid);
    DEBUG_LOG("New Home AreaId is %u", area_id);

    // zone update
    data.Initialize(SMSG_PLAYERBOUND, 8 + 4);
    data << m_caster->GetObjectGuid();
    data << uint32(area_id);
    player->SendDirectMessage(data);
}

void Spell::EffectRedirectThreat(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget)
        return;

    m_caster->getHostileRefManager().SetThreatRedirection(unitTarget->GetObjectGuid());
}

void Spell::EffectKnockBackFromPosition(SpellEffectIndex eff_idx)
{
    if (!unitTarget)
        return;

    float x, y, z;
    if (m_targets.m_targetMask & TARGET_FLAG_DEST_LOCATION)
        m_targets.getDestination(x, y, z);
    else
        m_caster->GetPosition(x, y, z);

    float angle = unitTarget->GetAngle(x, y) + M_PI_F;
    float horizontalSpeed = m_spellInfo->EffectMiscValue[eff_idx] * 0.1f;
    float verticalSpeed = damage * 0.1f;
    unitTarget->KnockBackWithAngle(angle, horizontalSpeed, verticalSpeed);
}

void Spell::EffectCreateTamedPet(SpellEffectIndex eff_idx)
{
    if (!unitTarget || unitTarget->getClass() != CLASS_HUNTER)
        return;

    uint32 creatureEntry = m_spellInfo->EffectMiscValue[eff_idx];

    CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creatureEntry);
    if (creatureEntry && !cInfo)
    {
        sLog.outErrorDb("EffectCreateTamedPet: Creature entry %u not found for spell %u.", creatureEntry, m_spellInfo->Id);
        return;
    }

    Pet* newTamedPet = new Pet(HUNTER_PET);
    CreatureCreatePos pos(unitTarget, unitTarget->GetOrientation());

    Map* map = unitTarget->GetMap();
    uint32 petNumber = sObjectMgr.GeneratePetNumber();
    if (!newTamedPet->Create(map->GenerateLocalLowGuid(HIGHGUID_PET), pos, cInfo, petNumber))
    {
        delete newTamedPet;
        return;
    }

    newTamedPet->SetLoading(true);

    newTamedPet->SetRespawnCoord(pos);

    newTamedPet->SetOwnerGuid(unitTarget->GetObjectGuid());
    newTamedPet->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);
    newTamedPet->setFaction(unitTarget->getFaction());
    newTamedPet->SetUInt32Value(UNIT_FIELD_PET_NAME_TIMESTAMP, uint32(time(nullptr)));
    newTamedPet->SetUInt32Value(UNIT_CREATED_BY_SPELL, m_spellInfo->Id);

    newTamedPet->GetCharmInfo()->SetPetNumber(petNumber, true);

    if (unitTarget->IsPvP())
        newTamedPet->SetPvP(true);

    if (unitTarget->IsPvPFreeForAll())
        newTamedPet->SetPvPFreeForAll(true);

    if (unitTarget->IsPvPSanctuary())
        newTamedPet->SetPvPSanctuary(true);

    newTamedPet->SetCanModifyStats(true);

    map->Add((Creature*)newTamedPet);

    newTamedPet->InitStatsForLevel(unitTarget->getLevel());
    newTamedPet->InitPetCreateSpells();

    newTamedPet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_RENAMED);
    newTamedPet->SetByteFlag(UNIT_FIELD_BYTES_2, 2, UNIT_CAN_BE_ABANDONED);

    if (m_caster->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED))
    {
        newTamedPet->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED);
        newTamedPet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_PLAYER_CONTROLLED_DEBUFF_LIMIT);
    }
    else
        newTamedPet->SetByteValue(UNIT_FIELD_BYTES_2, 1, UNIT_BYTE2_CREATURE_DEBUFF_LIMIT);

    newTamedPet->AIM_Initialize();

    float x, y, z;
    unitTarget->GetClosePoint(x, y, z, newTamedPet->GetObjectBoundingRadius());
    newTamedPet->Relocate(x, y, z, unitTarget->GetOrientation());

    m_caster->SetPet(newTamedPet);

    newTamedPet->SetLoading(false);

    Player* _player = static_cast<Player*>(unitTarget);
    if (_player)
    {
        newTamedPet->SavePetToDB(PET_SAVE_AS_CURRENT, _player);
        _player->PetSpellInitialize();
    }
}

void Spell::EffectTeleportGraveyard(SpellEffectIndex /*eff_idx*/)
{
    if (!unitTarget || !unitTarget->IsPlayer() || !unitTarget->GetMap()->IsBattleGround())
        return;

    Player* player = static_cast<Player*>(unitTarget);
    player->RepopAtGraveyard();
}

uint32 Spell::GetUsableHealthStoneItemType(Unit* target)
{
    if (!target || target->GetTypeId() != TYPEID_PLAYER)
        return 0;

    uint32 itemtype = 0;
    uint32 rank = 0;
    Unit::AuraList const& mDummyAuras = target->GetAurasByType(SPELL_AURA_DUMMY);
    for (auto mDummyAura : mDummyAuras)
    {
        if (mDummyAura->GetId() == 18692)
        {
            rank = 1;
            break;
        }
        if (mDummyAura->GetId() == 18693)
        {
            rank = 2;
            break;
        }
    }

    static uint32 const itypes[6][3] =
    {
        { 5512, 19004, 19005},              // Minor Healthstone
        { 5511, 19006, 19007},              // Lesser Healthstone
        { 5509, 19008, 19009},              // Healthstone
        { 5510, 19010, 19011},              // Greater Healthstone
        { 9421, 19012, 19013},              // Major Healthstone
        {22103, 22104, 22105}               // Master Healthstone
    };

    switch (m_spellInfo->Id)
    {
    case  6201:
        itemtype = itypes[0][rank]; break; // Minor Healthstone
    case  6202:
        itemtype = itypes[1][rank]; break; // Lesser Healthstone
    case  5699:
        itemtype = itypes[2][rank]; break; // Healthstone
    case 11729:
        itemtype = itypes[3][rank]; break; // Greater Healthstone
    case 11730:
        itemtype = itypes[4][rank]; break; // Major Healthstone
    case 27230:
        itemtype = itypes[5][rank]; break; // Master Healthstone
    }
    return itemtype;
}

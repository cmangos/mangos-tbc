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
#ifndef MANGOS_SPELLAURAS_H
#define MANGOS_SPELLAURAS_H

#include "Spells/SpellAuraDefines.h"
#include "Server/DBCEnums.h"
#include "Entities/ObjectGuid.h"
#include "Spells/Scripts/SpellScript.h"
#include "Util/UniqueTrackablePtr.h"

/**
 * Used to modify what an Aura does to a player/npc.
 * Accessible through Aura::m_modifier.
 * \see CreateAura
 * \see Aura
 * \see AreaAura
 * \see AuraType
 */
struct Modifier
{
    /**
     * Decides what the aura does, ie, it may have the
     * value AuraType::SPELL_AURA_MOD_BASE_RESISTANCE_PCT which
     * would change the base armor of a player.
     */
    AuraType m_auraname;
    /**
     * By how much the aura should change the affected
     * value. Ie, -27 would make the value decided by Modifier::m_miscvalue
     * be reduced by 27% if the earlier mentioned AuraType
     * would have been used. And 27 would increase the value by 27%
     */
    int32 m_amount;
    /**
     * A miscvalue that is dependent on what the aura will do, this
     * is usually decided by the AuraType, ie:
     * with AuraType::SPELL_AURA_MOD_BASE_RESISTANCE_PCT this value
     * could be SpellSchoolMask::SPELL_SCHOOL_MASK_NORMAL which would
     * tell the aura that it should change armor.
     * If Modifier::m_auraname would have been AuraType::SPELL_AURA_MOUNTED
     * then m_miscvalue would have decided which model the mount should have
     */
    int32 m_miscvalue;
    /**
     * Decides how often the aura should be applied, if it is
     * set to 0 it's only applied once and then removed when
     * the Aura is removed
     */
    uint32 periodictime;
    /**
    * Tells how much amount increased during recent stacks change
    */
    int32 m_recentAmount;
    /**
    * Set at the beginning so that stack increases dont need to calculate spell values
    */
    int32 m_baseAmount;
};

class Unit;
struct SpellEntry;
struct SpellModifier;
struct ProcTriggerSpell;

class Aura;

// internal helper
struct ReapplyAffectedPassiveAurasHelper;

enum SpellAuraHolderState
{
    SPELLAURAHOLDER_STATE_CREATED       = 0,                // just created, initialization steps
    SPELLAURAHOLDER_STATE_READY         = 1,                // all initialization steps are done
    SPELLAURAHOLDER_STATE_REMOVING      = 2,                // removing steps
    SPELLAURAHOLDER_STATE_DB_LOAD       = 3                 // during db load some events must not be executed
};

class SpellAuraHolder
{
    public:
        SpellAuraHolder(SpellEntry const* spellproto, Unit* target, WorldObject* caster, Item* castItem, SpellEntry const* triggeredBy);
        ~SpellAuraHolder();
        Aura* m_auras[MAX_EFFECT_INDEX];

        void AddAura(Aura* aura, SpellEffectIndex index);
        void RemoveAura(SpellEffectIndex index);
        void ApplyAuraModifiers(bool apply, bool real = false);
        void _AddSpellAuraHolder();
        void _RemoveSpellAuraHolder();
        void HandleSpellSpecificBoosts(bool apply);
        void CleanupTriggeredSpells();

        void setDiminishGroup(DiminishingGroup group) { m_AuraDRGroup = group; }
        DiminishingGroup getDiminishGroup() const { return m_AuraDRGroup; }

        uint32 GetStackAmount() const { return m_stackAmount; }
        void SetStackAmount(uint32 stackAmount, Unit* newCaster);
        bool ModStackAmount(int32 num, Unit* newCaster); // return true if last charge dropped

        Aura* GetAuraByEffectIndex(SpellEffectIndex index) const { return m_auras[index]; }
        SpellEntry const* GetTriggeredBy() const { return m_triggeredBy; }

        uint32 GetId() const { return m_spellProto->Id; }
        SpellEntry const* GetSpellProto() const { return m_spellProto; }
        SpellAuraHolderState GetState() const { return m_spellAuraHolderState; }
        void SetState(SpellAuraHolderState state) { m_spellAuraHolderState = state; }

        ObjectGuid const& GetCasterGuid() const { return m_casterGuid; }
        void SetCasterGuid(ObjectGuid guid) { m_casterGuid = guid; }
        ObjectGuid const& GetCastItemGuid() const { return m_castItemGuid; }
        Unit* GetCaster() const;
        Unit* GetTarget() const { return m_target; }
        void SetTarget(Unit* target) { m_target = target; }

        bool IsPermanent() const { return m_permanent; }
        void SetPermanent(bool permanent) { m_permanent = permanent; }
        bool IsPassive() const { return m_isPassive; }
        bool IsDeathPersistent() const { return m_isDeathPersist; }
        bool IsPersistent() const;
        bool IsPositive() const;
        bool IsAreaAura() const;                            // if one from auras of holder applied as area aura
        bool IsWeaponBuffCoexistableWith(SpellAuraHolder const* ref) const;
        bool IsNeedVisibleSlot(Unit const* caster) const;
        bool IsRemovedOnShapeLost() const { return m_isRemovedOnShapeLost; }
        bool IsDeleted() const { return m_deleted;}
        bool IsEmptyHolder() const;
        bool IsSaveToDbHolder() const;
        bool IsCharm() const;

        void SetDeleted() { m_deleted = true; m_spellAuraHolderState = SPELLAURAHOLDER_STATE_REMOVING; }

        void UpdateHolder(uint32 diff) { Update(diff); }
        void Update(uint32 diff);
        void RefreshHolder();

        TrackedAuraType GetTrackedAuraType() const { return m_trackedAuraType; }
        void SetTrackedAuraType(TrackedAuraType val) { m_trackedAuraType = val; }
        void UnregisterAndCleanupTrackedAuras();

        int32 GetAuraMaxDuration() const { return m_maxDuration; }
        void SetAuraMaxDuration(int32 duration);
        int32 GetAuraDuration() const { return m_duration; }
        void SetAuraDuration(int32 duration) { m_duration = duration; }

        void SetHeartbeatResist(uint32 chance, int32 originalDuration, uint32 drLevel);

        uint8 GetAuraSlot() const { return m_auraSlot; }
        void SetAuraSlot(uint8 slot) { m_auraSlot = slot; }
        uint8 GetAuraLevel() const { return m_auraLevel; }
        void SetAuraLevel(uint8 level) { m_auraLevel = level; }
        uint32 GetAuraCharges() const { return m_procCharges; }
        void SetAuraCharges(uint32 charges, bool update = true);

        // SpellMods
        bool DropAuraCharge();                               // return true if last charge dropped
        void ResetSpellModCharges();
        bool HasModifier(const uint64& modId) const;

        uint32 GetAuraApplyTime() const { return m_applyTime; }
        uint32 GetAuraApplyMSTime() const { return m_applyMSTime; } // milliseconds time

        void SetRemoveMode(AuraRemoveMode mode) { m_removeMode = mode; }
        void SetLoadedState(ObjectGuid const& casterGUID, ObjectGuid const& itemGUID, uint32 stackAmount, uint32 charges, int32 maxduration, int32 duration)
        {
            m_casterGuid   = casterGUID;
            m_castItemGuid = itemGUID;
            m_procCharges  = charges;
            m_stackAmount  = stackAmount;
            SetAuraMaxDuration(maxduration);
            SetAuraDuration(duration);
        }

        bool HasMechanic(uint32 mechanic) const;
        bool HasMechanicMask(uint32 mechanicMask) const;
        bool IsDispellableByMask(uint32 dispelMask, Unit const* caster, SpellEntry const* spellInfo) const;

        void UpdateAuraDuration();
        void LoginAuraDuration();
        void ForceUpdateAuraDuration();
        void SendAuraDuration();
        void SendAuraDurationToCaster(Player* caster, uint32 slot = MAX_AURAS);
        void SendAuraDurationToCasterNeedUpdate(Player* caster);

        void SetAura(uint32 slot, bool remove) { m_target->SetUInt32Value(UNIT_FIELD_AURA + slot, remove ? 0 : GetId()); }
        void SetAuraFlag(uint32 slot, bool add);
        void SetAuraLevel(uint32 slot, uint32 level);

        void SetCreationDelayFlag();

        bool HasAuraType(AuraType type);

        bool IsProcReady(TimePoint const& now) const;
        void SetProcCooldown(std::chrono::milliseconds cooldown, TimePoint const& now);

        bool IsReducedProcChancePast60() { return m_reducedProcChancePast60; }
        void SetReducedProcChancePast60() { m_reducedProcChancePast60 = true; }

        // Scripting system
        AuraScript* GetAuraScript() const { return m_auraScript; }
        // hooks
        void OnHolderInit(WorldObject* caster);
        void OnDispel(Unit* dispeller, uint32 dispellingSpellId, uint32 originalStacks);
        // helpers
        void PresetAuraStacks(uint32 stacks) { m_stackAmount = stacks; } // use only in OnHolderInit
    private:
        void UpdateAuraApplication();                       // called at charges or stack changes
        void ClearExtraAuraInfo(Unit* caster);
        void UpdateHeartbeatResist(uint32 diff);

        SpellEntry const* m_spellProto;

        Unit* m_target;
        ObjectGuid m_casterGuid;
        ObjectGuid m_castItemGuid;                          // it is NOT safe to keep a pointer to the item because it may get deleted
        time_t m_applyTime;
        uint32 m_applyMSTime;
        SpellEntry const* m_triggeredBy;                    // Spell responsible for this holder
        SpellAuraHolderState m_spellAuraHolderState;        // State used to be sure init part is finished (ex there is still some aura to add or effect to process)

        uint8 m_auraSlot;                                   // Aura slot on unit (for show in client)
        uint8 m_auraLevel;                                  // Aura level (store caster level for correct show level dep amount)
        uint32 m_procCharges;                               // Aura charges (0 for infinite)
        uint32 m_stackAmount;                               // Aura stack amount
        int32 m_maxDuration;                                // Max aura duration
        int32 m_duration;                                   // Current time
        int32 m_timeCla;                                    // Timer for power per sec calculation

        float m_heartbeatResistChance;                      // Chance to break this spell due to heartbeat resistance
        int32 m_heartbeatResistInterval;                    // Heartbeat resistance periodic interval
        int32 m_heartbeatResistTimer;                       // Timer for heartbeat resistance

        AuraRemoveMode m_removeMode: 8;                     // Store info for know remove aura reason
        DiminishingGroup m_AuraDRGroup: 8;                  // Diminishing
        TrackedAuraType m_trackedAuraType: 8;               // store if the caster tracks the aura - can change at spell steal for example

        bool m_permanent: 1;
        bool m_isPassive: 1;
        bool m_isDeathPersist: 1;
        bool m_isRemovedOnShapeLost: 1;
        bool m_deleted: 1;
        bool m_skipUpdate: 1;

        TimePoint m_procCooldown;

        bool m_reducedProcChancePast60;

        // Scripting System
        AuraScript* m_auraScript;
};

typedef void(Aura::*pAuraHandler)(bool Apply, bool Real);
// Real == true at aura add/remove
// Real == false at aura mod unapply/reapply; when adding/removing dependent aura/item/stat mods
//
// Code in aura handler can be guarded by if(Real) check if it should execution only at real add/remove of aura
//
// MAIN RULE: Code MUST NOT be guarded by if(Real) check if it modifies any stats
//      (percent auras, stats mods, etc)
// Second rule: Code must be guarded by if(Real) check if it modifies object state (start/stop attack, send packets to client, etc)
//
// Other case choice: each code line moved under if(Real) check is mangos speedup,
//      each setting object update field code line moved under if(Real) check is significant mangos speedup, and less server->client data sends
//      each packet sending code moved under if(Real) check is _large_ mangos speedup, and lot less server->client data sends

class Aura
{
        friend struct ReapplyAffectedPassiveAurasHelper;
        friend Aura* CreateAura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, Unit* caster, Item* castItem, uint64 scriptValue);

    public:
        // aura handlers
        void HandleNULL(bool, bool)
        {
            // NOT IMPLEMENTED
        }
        void HandleUnused(bool, bool)
        {
            // NOT USED BY ANY SPELL OR USELESS
        }
        void HandleNoImmediateEffect(bool, bool)
        {
            // aura not have immediate effect at add/remove and handled by ID in other code place
        }
        void HandleBindSight(bool apply, bool Real);
        void HandleModPossess(bool apply, bool Real);
        void HandlePeriodicDamage(bool apply, bool Real);
        void HandleAuraDummy(bool apply, bool Real);
        void HandleAuraPeriodicDummy(bool apply, bool Real);
        void HandleModConfuse(bool apply, bool Real);
        void HandleModCharm(bool apply, bool Real);
        void HandleModFear(bool apply, bool Real);
        void HandlePeriodicHeal(bool apply, bool Real);
        void HandleModAttackSpeed(bool apply, bool Real);
        void HandleModMeleeRangedSpeedPct(bool apply, bool Real);
        void HandleModCombatSpeedPct(bool apply, bool Real);
        void HandleModThreat(bool apply, bool Real);
        void HandleModTaunt(bool Apply, bool Real);
        void HandleFeignDeath(bool apply, bool Real);
        void HandleAuraModDisarm(bool apply, bool Real);
        void HandleAuraModStalked(bool apply, bool Real);
        void HandleAuraWaterWalk(bool apply, bool Real);
        void HandleAuraFeatherFall(bool apply, bool Real);
        void HandleAuraHover(bool apply, bool Real);
        void HandleAddModifier(bool apply, bool Real);
        void HandleAuraModStun(bool apply, bool Real);
        void HandleModDamageDone(bool apply, bool Real);
        void HandleAuraUntrackable(bool apply, bool Real);
        void HandleAuraEmpathy(bool apply, bool Real);
        void HandleModOffhandDamagePercent(bool apply, bool Real);
        void HandleAuraModRangedAttackPower(bool apply, bool Real);
        void HandleAuraModIncreaseEnergyPercent(bool apply, bool Real);
        void HandleAuraModIncreaseHealthPercent(bool apply, bool Real);
        void HandleAuraModRegenInterrupt(bool apply, bool Real);
        void HandleModMeleeSpeedPct(bool apply, bool Real);
        void HandlePeriodicTriggerSpell(bool apply, bool Real);
        void HandlePeriodicTriggerSpellWithValue(bool apply, bool Real);
        void HandlePeriodicEnergize(bool apply, bool Real);
        void HandleAuraModResistanceExclusive(bool apply, bool Real);
        void HandleAuraSafeFall(bool Apply, bool Real);
        void HandleModStealth(bool apply, bool Real);
        void HandleModStealthDetect(bool apply, bool real);
        void HandleInvisibility(bool apply, bool Real);
        void HandleInvisibilityDetect(bool apply, bool Real);
        void HandleAuraModTotalHealthPercentRegen(bool apply, bool Real);
        void HandleAuraModTotalManaPercentRegen(bool apply, bool Real);
        void HandleAuraModResistance(bool apply, bool Real);
        void HandleAuraModRoot(bool apply, bool Real);
        void HandleAuraModSilence(bool apply, bool Real);
        void HandleAuraModStat(bool apply, bool Real);
        void HandleDetectAmore(bool apply, bool Real);
        void HandleAuraModIncreaseSpeed(bool Apply, bool Real);
        void HandleAuraModIncreaseMountedSpeed(bool apply, bool Real);
        void HandleAuraModIncreaseFlightSpeed(bool apply, bool Real);
        void HandleAuraModDecreaseSpeed(bool apply, bool Real);
        void HandleAuraModUseNormalSpeed(bool Apply, bool Real);
        void HandleAuraModIncreaseHealth(bool apply, bool Real);
        void HandleAuraModIncreaseEnergy(bool apply, bool Real);
        void HandleAuraModShapeshift(bool apply, bool Real);
        void HandleAuraModEffectImmunity(bool apply, bool Real);
        void HandleAuraModStateImmunity(bool apply, bool Real);
        void HandleAuraModSchoolImmunity(bool apply, bool Real);
        void HandleAuraModDmgImmunity(bool apply, bool Real);
        void HandleAuraModDispelImmunity(bool apply, bool Real);
        void HandleAuraProcTriggerSpell(bool apply, bool Real);
        void HandleAuraTrackCreatures(bool apply, bool Real);
        void HandleAuraTrackResources(bool apply, bool Real);
        void HandleAuraModParryPercent(bool apply, bool Real);
        void HandleAuraModDodgePercent(bool apply, bool Real);
        void HandleAuraModBlockPercent(bool apply, bool Real);
        void HandleAuraModCritPercent(bool apply, bool Real);
        void HandlePeriodicLeech(bool apply, bool Real);
        void HandleModHitChance(bool apply, bool Real);
        void HandleModSpellHitChance(bool apply, bool Real);
        void HandleAuraModScale(bool apply, bool Real);
        void HandlePeriodicManaLeech(bool apply, bool Real);
        void HandlePeriodicHealthFunnel(bool apply, bool Real);
        void HandleModCastingSpeed(bool apply, bool Real);
        void HandleAuraMounted(bool apply, bool Real);
        void HandleWaterBreathing(bool apply, bool real);
        void HandleModStealthLevel(bool apply, bool real);
        void HandleModWaterBreathing(bool apply, bool Real);
        void HandleModBaseResistance(bool apply, bool Real);
        void HandleModRegen(bool apply, bool Real);
        void HandleModPowerRegen(bool apply, bool Real);
        void HandleModPowerRegenPCT(bool Apply, bool Real);
        void HandleModHealingPCT(bool apply, bool real);
        void HandleChannelDeathItem(bool apply, bool Real);
        void HandlePeriodicDamagePCT(bool apply, bool Real);
        void HandleAuraModAttackPower(bool apply, bool Real);
        void HandleAuraTransform(bool apply, bool Real);
        void HandleModSpellCritChance(bool apply, bool Real);
        void HandleAuraModIncreaseSwimSpeed(bool Apply, bool Real);
        void HandleModPowerCostPCT(bool apply, bool Real);
        void HandleModPowerCost(bool apply, bool Real);
        void HandleFarSight(bool apply, bool Real);
        void HandleModPossessPet(bool apply, bool Real);
        void HandleModMechanicImmunity(bool apply, bool Real);
        void HandleModMechanicImmunityMask(bool apply, bool Real);
        void HandleAuraModSkill(bool apply, bool Real);
        void HandleModDamagePercentDone(bool apply, bool Real);
        void HandleModPercentStat(bool apply, bool Real);
        void HandleModResistancePercent(bool apply, bool Real);
        void HandleAuraModBaseResistancePercent(bool apply, bool Real);
        void HandleAuraTrackStealthed(bool apply, bool Real);
        void HandleForceReaction(bool apply, bool Real);
        void HandleAuraModRangedHaste(bool apply, bool Real);
        void HandleRangedAmmoHaste(bool apply, bool Real);
        void HandleModHealingDone(bool Apply, bool Real);
        void HandleModTotalPercentStat(bool apply, bool Real);
        void HandleAuraModTotalThreat(bool apply, bool Real);
        void HandleModUnattackable(bool Apply, bool Real);
        void HandleAuraModPacify(bool apply, bool Real);
        void HandleAuraGhost(bool apply, bool Real);
        void HandleAuraAllowFlight(bool apply, bool Real);
        void HandleModRating(bool apply, bool Real);
        void HandleModTargetResistance(bool apply, bool Real);
        void HandleAuraModAttackPowerPercent(bool apply, bool Real);
        void HandleAuraModRangedAttackPowerPercent(bool apply, bool Real);
        void HandleAuraModRangedAttackPowerOfStatPercent(bool apply, bool Real);
        void HandleSpiritOfRedemption(bool apply, bool Real);
        void HandleAoECharm(bool apply, bool Real);
        void HandleModManaRegen(bool apply, bool Real);
        void HandleComprehendLanguage(bool apply, bool Real);
        void HandleShieldBlockValue(bool apply, bool Real);
        void HandleModSpellCritChanceShool(bool apply, bool Real);
        void HandleAuraRetainComboPoints(bool apply, bool Real);
        void HandleModSpellDamagePercentFromStat(bool apply, bool Real);
        void HandleModSpellHealingPercentFromStat(bool apply, bool Real);
        void HandleAuraModDispelResist(bool apply, bool Real);
        void HandleModSpellDamagePercentFromAttackPower(bool apply, bool Real);
        void HandleModSpellHealingPercentFromAttackPower(bool apply, bool Real);
        void HandleAuraModPacifyAndSilence(bool apply, bool Real);
        void HandleAuraModIncreaseMaxHealth(bool apply, bool Real);
        void HandleAuraModExpertise(bool apply, bool Real);
        void HandleForceMoveForward(bool apply, bool Real);
        void HandleAuraModResistenceOfStatPercent(bool apply, bool Real);
        void HandleAuraPowerBurn(bool apply, bool Real);
        void HandleSchoolAbsorb(bool apply, bool Real);
        void HandlePreventFleeing(bool apply, bool Real);
        void HandleManaShield(bool apply, bool Real);
        void HandleArenaPreparation(bool apply, bool Real);
        void HandleAuraMirrorImage(bool apply, bool Real);
        void HandleFactionOverride(bool apply, bool Real);
        void HandlePrayerOfMending(bool apply, bool Real);
        void HandleAuraDetaunt(bool Apply, bool Real);
        void HandleOverrideClassScript(bool apply, bool real);
        void HandleAuraPhase(bool apply, bool real);

        virtual ~Aura();

        void SetModifier(AuraType type, int32 amount, uint32 periodicTime, int32 miscValue);
        Modifier*       GetModifier()       { return &m_modifier; }
        Modifier const* GetModifier() const { return &m_modifier; }
        int32 GetMiscValue() const { return m_spellAuraHolder->GetSpellProto()->EffectMiscValue[m_effIndex]; }
        int32 GetMiscBValue() const { return m_spellAuraHolder->GetSpellProto()->EffectMiscValueB[m_effIndex]; }

        SpellEntry const* GetSpellProto() const { return GetHolder()->GetSpellProto(); }
        uint32 GetId() const { return GetHolder()->GetSpellProto()->Id; }
        ObjectGuid const& GetCastItemGuid() const { return GetHolder()->GetCastItemGuid(); }
        ObjectGuid const& GetCasterGuid() const { return GetHolder()->GetCasterGuid(); }
        Unit* GetCaster() const { return GetHolder()->GetCaster(); }
        Unit* GetTarget() const { return GetHolder()->GetTarget(); }

        SpellEffectIndex GetEffIndex() const { return m_effIndex; }
        int32 GetBasePoints() const { return m_currentBasePoints; }
        int32 GetAmount() const { return m_modifier.m_amount; }
        void SetAmount(int32 amount) { m_modifier.m_amount = amount; }

        int32 GetAuraMaxDuration() const { return GetHolder()->GetAuraMaxDuration(); }
        int32 GetAuraDuration() const { return GetHolder()->GetAuraDuration(); }
        time_t GetAuraApplyTime() const { return m_applyTime; }
        uint32 GetAuraTicks() const { return m_periodicTick; }
        uint32 GetAuraMaxTicks() const
        {
            int32 maxDuration = GetAuraMaxDuration();
            return maxDuration > 0 && m_modifier.periodictime > 0 ? maxDuration / m_modifier.periodictime : 0;
        }
        uint32 GetStackAmount() const { return GetHolder()->GetStackAmount(); }

        void SetLoadedState(int32 damage, uint32 periodicTime)
        {
            m_modifier.m_amount = damage;
            m_modifier.periodictime = periodicTime;

            if (uint32 maxticks = GetAuraMaxTicks())
                m_periodicTick = maxticks - GetAuraDuration() / m_modifier.periodictime;
        }

        bool IsPositive() const { return m_positive; }
        bool IsPersistent() const { return m_isPersistent; }
        bool IsAreaAura() const { return m_isAreaAura; }
        bool IsPeriodic() const { return m_isPeriodic; }
        bool IsSaveToDbAura() const;

        void ApplyModifier(bool apply, bool Real = false);
        void UpdateAuraScaling();

        void UpdateAura(uint32 diff) { Update(diff); }

        void SetRemoveMode(AuraRemoveMode mode) { m_removeMode = mode; }
        AuraRemoveMode GetRemoveMode() { return m_removeMode; }

        virtual Unit* GetTriggerTarget() const { return m_spellAuraHolder->GetTarget(); }

        // add/remove SPELL_AURA_MOD_SHAPESHIFT (36) linked auras
        void HandleShapeshiftBoosts(bool apply);

        void TriggerSpell();
        void TriggerSpellWithValue();

        // more limited that used in future versions (spell_affect table based only), so need be careful with backporting uses
        ClassFamilyMask GetAuraSpellClassMask() const;
        bool isAffectedOnSpell(SpellEntry const* spell) const;
        bool CanProcFrom(SpellEntry const* spell, uint32 EventProcEx, uint32 procEx, bool damaging, bool absorbing, bool useClassMask) const;

        SpellAuraHolder* GetHolder() { return m_spellAuraHolder; }
        SpellAuraHolder const* GetHolder() const { return m_spellAuraHolder; }

        bool IsLastAuraOnHolder();

        bool HasMechanic(uint32 mechanic) const;

        SpellModifier* GetSpellModifier() { return m_spellmod; }

        void UseMagnet() { m_magnetUsed = true; }
        bool IsMagnetUsed() const { return m_magnetUsed; }

        static uint32 CalculateAuraEffectValue(Unit* caster, Unit* target, SpellEntry const* spellProto, SpellEffectIndex effIdx, uint32 value);

        // Scripting system
        AuraScript* GetAuraScript() const { return GetHolder()->GetAuraScript(); }
        // Variable storage
        void SetScriptValue(uint64 value) { m_scriptValue = value; }
        uint64 GetScriptValue() { return m_scriptValue; }
        void SetScriptStorage(ScriptStorage* storage) { m_storage = storage; } // do not set more than once
        ScriptStorage* GetScriptStorage() { return m_storage; }
        // hooks
        void OnAuraInit();
        int32 OnAuraValueCalculate(Unit* caster, int32 currentValue, Item* castItem);
        void OnDamageCalculate(Unit* victim, Unit* attacker, int32& advertisedBenefit, float& totalMod);
        void OnCritChanceCalculate(Unit const* victim, float& chance, SpellEntry const* spellInfo);
        void OnApply(bool apply);
        void OnAfterApply(bool apply);
        bool OnCheckProc(ProcExecutionData& data);
        SpellAuraProcResult OnProc(ProcExecutionData& data);
        void OnAbsorb(int32& currentAbsorb, int32& remainingDamage, uint32& reflectedSpellId, int32& reflectDamage, bool& preventedDeath, bool& dropCharge, DamageEffectType damageType);
        void OnManaAbsorb(int32& currentAbsorb);
        void OnAuraDeathPrevention(int32& remainingDamage);
        void OnPeriodicTrigger(PeriodicTriggerData& data);
        void OnPeriodicDummy();
        void OnPeriodicTickEnd();
        void OnPeriodicCalculateAmount(uint32& amount);
        void OnHeartbeat();
        bool OnAffectCheck(SpellEntry const* spellInfo) const;
        uint32 GetAuraScriptCustomizationValue();
        // Hook Requirements
        void ForcePeriodicity(uint32 periodicTime);
        void SetAffectOverriden() { m_affectOverriden = true; } // spell script must implement condition

        MaNGOS::unique_weak_ptr<Aura> GetWeakPtr() const { return m_scriptRef; }
        void InvalidateScriptRef() { m_scriptRef = nullptr; }

    protected:
        Aura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, Unit* caster = nullptr, Item* castItem = nullptr);

        // must be called only from Aura::UpdateAura
        virtual void Update(uint32 diff);

        // must be called only from Aura*::Update
        void PeriodicTick();
        void PeriodicDummyTick();

        void ReapplyAffectedPassiveAuras();

        void PickTargetsForSpellTrigger(Unit *& triggerCaster, Unit *& triggerTarget, WorldObject *& triggerTargetObject, SpellEntry const* spellInfo);
        void CastTriggeredSpell(PeriodicTriggerData& data);

        Modifier m_modifier;
        SpellModifier* m_spellmod;

        time_t m_applyTime;

        int32 m_currentBasePoints;                          // cache SpellEntry::CalculateSimpleValue and use for set custom base points
        int32 m_periodicTimer;                              // Timer for periodic auras
        uint32 m_periodicTick;                              // Tick count pass (including current if use in tick code) from aura apply, used for some tick count dependent aura effects

        AuraRemoveMode m_removeMode: 8;                     // Store info for know remove aura reason

        SpellEffectIndex m_effIndex : 8;                    // Aura effect index in spell

        bool m_positive: 1;
        bool m_isPeriodic: 1;
        bool m_isAreaAura: 1;
        bool m_isPersistent: 1;
        bool m_magnetUsed: 1;

        SpellAuraHolder* const m_spellAuraHolder;

        // Scripting system
        uint64 m_scriptValue; // persistent value for spell script state
        ScriptStorage* m_storage;
        bool m_affectOverriden;

        struct NoopAuraDeleter { void operator()(Aura*) const { /*noop - not managed*/ } };
        MaNGOS::unique_trackable_ptr<Aura> m_scriptRef;
    private:
        void ReapplyAffectedPassiveAuras(Unit* target, bool owner_mode);
};

class AreaAura : public Aura
{
    public:
        AreaAura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, Unit* caster = nullptr, Item* castItem = nullptr, uint32 originalRankSpellId = 0);
        virtual ~AreaAura();

        bool OnAreaAuraCheckTarget(Unit* target) const;
    protected:
        void Update(uint32 diff) override;
    private:
        float m_radius;
        AreaAuraType m_areaAuraType;
        uint32       m_originalRankSpellId;
};

class PersistentAreaAura : public Aura
{
    public:
        PersistentAreaAura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, Unit* caster = nullptr, Item* castItem = nullptr);
        virtual ~PersistentAreaAura();
    protected:
        void Update(uint32 diff) override;
};

// Used for GO Area Auras
class GameObjectAura : public Aura
{
    public:
        GameObjectAura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, GameObject* caster);
        virtual ~GameObjectAura();

    protected:
        void Update(uint32 diff) override;
};

Aura* CreateAura(SpellEntry const* spellproto, SpellEffectIndex eff, int32 const* currentDamage, int32 const* currentBasePoints, SpellAuraHolder* holder, Unit* target, Unit* caster = nullptr, Item* castItem = nullptr, uint64 scriptValue = 0);
SpellAuraHolder* CreateSpellAuraHolder(SpellEntry const* spellproto, Unit* target, WorldObject* caster, Item* castItem = nullptr, SpellEntry const* triggeredBy = nullptr);
#endif

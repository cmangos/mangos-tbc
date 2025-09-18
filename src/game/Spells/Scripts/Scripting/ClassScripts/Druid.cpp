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

#include "Spells/Scripts/SpellScript.h"
#include "Spells/SpellAuras.h"
#include "Spells/SpellMgr.h"

enum
{
    SPELL_BLESSING_OF_THE_CLAW = 28750,
};

// 8936 - Regrowth
struct Regrowth : public AuraScript
{
    void OnPeriodicTickEnd(Aura* aura) const override
    {
        if (Unit* caster = aura->GetCaster())
            if (caster->HasOverrideScript(4537))
                caster->CastSpell(aura->GetTarget(), SPELL_BLESSING_OF_THE_CLAW, TRIGGERED_OLD_TRIGGERED);
    }
};

// 1178 - Bear Form, 3025 - Cat Form, 9635 - Dire Bear Form, 24905 - Moonkin Form
struct FormScalingAttackPowerAuras : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& data, int32 value) const override
    {
        if (data.spellProto->EffectApplyAuraName[data.effIdx] == SPELL_AURA_MOD_ATTACK_POWER)
        {
            // Predatory Strikes
            Aura* predatoryStrikes = nullptr;
            if (Aura* aura = data.target->GetAura(16975, EFFECT_INDEX_0)) // rank 3
                predatoryStrikes = aura;
            else if (Aura* aura = data.target->GetAura(16974, EFFECT_INDEX_0)) // rank 2
                predatoryStrikes = aura;
            else if (Aura* aura = data.target->GetAura(16972, EFFECT_INDEX_0)) // rank 1
                predatoryStrikes = aura;
            if (predatoryStrikes)
                value += data.target->GetLevel() * predatoryStrikes->GetAmount() / 100;
        }
        return value;
    }
};

// 33831 - Force of Nature
struct ForceOfNatureSummon : public SpellScript, public AuraScript
{
    void OnSummon(Spell* /*spell*/, Creature* summon) const override
    {
        summon->CastSpell(nullptr, 37846, TRIGGERED_NONE);
    }

    void OnHolderInit(SpellAuraHolder* holder, WorldObject* /*caster*/) const override
    {
        holder->SetAuraDuration(2000);
    }

    void OnPeriodicDummy(Aura* aura) const override
    {
        Unit* target = aura->GetTarget();
        target->CastSpell(nullptr, 41929, TRIGGERED_OLD_TRIGGERED);
    }
};

// 41929 - Guardian Aggro Spell
struct GuardianAggroSpell : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_0)
            return;

        Unit* target = spell->GetUnitTarget();
        Unit* caster = spell->GetCaster();
        if (target->GetEntry() == 1964) // Force of Nature treant
        {
            if (target->CanAttack(caster))
            {
                if (target->IsVisibleForOrDetect(caster, caster, true))
                    target->AI()->AttackStart(caster);
            }
        }
    }
};

// 33876, 33878 - Mangle
struct MangleDruidTBC : public SpellScript, public AuraScript
{
    void OnAuraInit(Aura* aura) const override
    {
        aura->SetAffectOverriden();
    }

    void OnApply(Aura* aura, bool apply) const override
    {
        aura->GetTarget()->RegisterScriptedLocationAura(aura, SCRIPT_LOCATION_MELEE_DAMAGE_TAKEN, apply);
        aura->GetTarget()->RegisterScriptedLocationAura(aura, SCRIPT_LOCATION_SPELL_DAMAGE_TAKEN, apply);
    }

    bool OnAffectCheck(Aura const* /*aura*/, SpellEntry const* spellInfo) const override
    {
        if (spellInfo == nullptr)
            return false;

        if (GetAllSpellMechanicMask(spellInfo) & (1 << (MECHANIC_BLEED - 1)))
            return true;
        
        switch (spellInfo->Id)
        {
            case 5221: // Shred
            case 6800:
            case 8992:
            case 9829:
            case 9830:
            case 27001:
            case 27002:
                return true;
            default: return false;
        }
    }

    void OnDamageCalculate(Aura* aura, Unit* /*attacker*/, Unit* /*victim*/, int32& /*advertisedBenefit*/, float& totalMod) const override
    {
        totalMod *= (100.0f + aura->GetModifier()->m_amount) / 100.0f;
    }

    void OnAfterHit(Spell* spell) const override
    {
        if (spell->m_spellInfo->CanBeUsedInForm(FORM_CAT))
            spell->GetCaster()->CastSpell(spell->GetUnitTarget(), 34071, TRIGGERED_OLD_TRIGGERED);
    }
};

// 37327 - Starfire Bonus
struct StarfireBonus : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const override
    {
        aura->GetTarget()->RegisterScriptedLocationAura(aura, SCRIPT_LOCATION_SPELL_DAMAGE_DONE, apply);
    }

    void OnDamageCalculate(Aura* aura, Unit* /*attacker*/, Unit* victim, int32& /*advertisedBenefit*/, float& totalMod) const override
    {
        if (victim->GetAura(SPELL_AURA_PERIODIC_DAMAGE, SPELLFAMILY_DRUID, uint64(0x0000000000200002)))
            totalMod *= (aura->GetModifier()->m_amount + 100.0f) / 100.0f;
    }
};

void LoadDruidScripts()
{
    RegisterSpellScript<Regrowth>("spell_regrowth");
    RegisterSpellScript<FormScalingAttackPowerAuras>("spell_druid_form_scaling_ap_auras");
    RegisterSpellScript<ForceOfNatureSummon>("spell_force_of_nature_summon");
    RegisterSpellScript<GuardianAggroSpell>("spell_guardian_aggro_spell");
    RegisterSpellScript<MangleDruidTBC>("spell_mangle_druid_tbc");
    RegisterSpellScript<StarfireBonus>("spell_starfire_bonus");
}
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

// 1130 - Hunter's Mark
struct HuntersMark : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& data, int32 value) const override
    {
        if (data.effIdx == EFFECT_INDEX_2)
        {
            int32 auraValue = 0;
            if (data.aura)
            {
                if (Aura* otherAura = data.aura->GetHolder()->m_auras[EFFECT_INDEX_1])
                    auraValue = otherAura->GetAmount(); // fetch ranged aura AP
            }
            else if (data.caster) // or newly calculate it
                auraValue = data.caster->CalculateSpellEffectValue(data.target, data.spellProto, EFFECT_INDEX_1, nullptr, true, false);

            if (Unit* caster = data.caster)
            {
                Unit::AuraList const& classScriptAuras = caster->GetAurasByType(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
                for (auto& aura : classScriptAuras)
                {
                    switch (aura->GetModifier()->m_miscvalue)
                    {
                        case 5236:
                        case 5237:
                        case 5238:
                        case 5239:
                        case 5240:
                            value = aura->GetModifier()->m_amount * auraValue / 100;
                            break;
                    }
                }
            }
        }
        return value;
    }

    SpellAuraProcResult OnProc(Aura* aura, ProcExecutionData& /*procData*/) const override
    {
        if (aura->GetEffIndex() != EFFECT_INDEX_0) // increases debuff strength on every hit up to 4th
        {
            int32 basevalue = aura->GetBasePoints();
            aura->GetModifier()->m_amount += basevalue / 10;
            if (aura->GetModifier()->m_amount > basevalue * 4)
                aura->GetModifier()->m_amount = basevalue * 4;
        }
        return SPELL_AURA_PROC_OK;
    }
};

// 34026 - Kill Command
struct KillCommand : public SpellScript
{
    void OnHit(Spell* spell, SpellMissInfo /*missInfo*/) const override
    {
        if (spell->GetCaster()->HasAura(37483)) // Improved Kill Command - Item set bonus
            spell->GetCaster()->CastSpell(nullptr, 37482, TRIGGERED_OLD_TRIGGERED);// Exploited Weakness
    }

    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_1 || !spell->GetUnitTarget() || spell->GetCaster()->getClass() != CLASS_HUNTER)
            return;

        // clear hunter crit aura state
        spell->GetCaster()->ModifyAuraState(AURA_STATE_HUNTER_CRIT_STRIKE, false);

        // additional damage from pet to pet target
        Pet* pet = static_cast<Pet*>(spell->GetUnitTarget()); // guaranteed by spell targeting
        if (!pet->GetVictim())
            return;

        uint32 spell_id = 0;
        switch (spell->m_spellInfo->Id)
        {
            case 34026: spell_id = 34027; break;    // rank 1
            default: sLog.outError("KillCommand: Spell %u not handled", spell->m_spellInfo->Id); return;
        }

        pet->CastSpell(pet->GetVictim(), spell_id, TRIGGERED_OLD_TRIGGERED);
        return;
    }
};

// 34477 - Misdirection
struct Misdirection : public SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool/* strict*/) const override
    {
        // Patch 2.3.0 (2007-11-13):
        // Misdirection: If a Hunter attempts to use this ability on a target which already has an active Misdirection, the spell will fail to apply due to a more powerful spell already being in effect.
        if (Unit* target = spell->m_targets.getUnitTarget())
        {
            if (target->HasAura(35079))
                return SPELL_FAILED_AURA_BOUNCED;
            if (target->IsMounted())
                return SPELL_FAILED_NOT_ON_MOUNTED;
        }

        return SPELL_CAST_OK;
    }
};

// 34501 - Expose Weakness
struct ExposeWeakness : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& data, int32 value) const override
    {
        if (data.caster)
            value = (data.caster->GetStat(STAT_AGILITY) * value) / 100;

        return value;
    }
};

// 34701 - Random Aggro
struct RandomAggroSnakeTrap : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_0)
            return;

        Unit* target = spell->GetUnitTarget();
        Unit* caster = spell->GetCaster();
        if (caster->CanAttack(target))
        {
            if (caster->IsVisibleForOrDetect(target, target, true))
                caster->AI()->AttackStart(caster);
        }
    }
};

// TODO: some evidence tbc pet growl scales with hunter AP

void LoadHunterScripts()
{
    RegisterSpellScript<HuntersMark>("spell_hunters_mark");
    RegisterSpellScript<KillCommand>("spell_kill_command");
    RegisterSpellScript<Misdirection>("spell_misdirection");
    RegisterSpellScript<ExposeWeakness>("spell_expose_weakness");
    RegisterSpellScript<RandomAggroSnakeTrap>("spell_random_aggro_snake_trap");
}

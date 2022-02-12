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

struct WarriorExecute : public SpellScript
{
    void OnCast(Spell* spell) const override // confirmed main spell can not hit and child still hits
    {
        int32 basePoints0 = spell->GetCaster()->CalculateSpellEffectValue(spell->m_targets.getUnitTarget(), spell->m_spellInfo, SpellEffectIndex(0))
            + int32((spell->GetCaster()->GetPower(POWER_RAGE)) * spell->m_spellInfo->DmgMultiplier[0]);
        SpellCastResult result = spell->GetCaster()->CastCustomSpell(spell->m_targets.getUnitTarget(), 20647, &basePoints0, nullptr, nullptr, TRIGGERED_IGNORE_CURRENT_CASTED_SPELL);
    }
};

struct WarriorExecuteDamage : public SpellScript
{
    void OnHit(Spell* spell, SpellMissInfo missInfo) const override
    {
        if (missInfo == SPELL_MISS_NONE)
            spell->GetCaster()->SetPower(POWER_RAGE, 0);
    }
};

struct VictoryRush : public SpellScript
{
    void OnCast(Spell* spell) const override
    {
        spell->GetCaster()->ModifyAuraState(AURA_STATE_WARRIOR_VICTORY_RUSH, false);
    }

    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        spell->SetDamage(uint32(spell->GetDamage() * spell->GetCaster()->GetTotalAttackPowerValue(BASE_ATTACK) / 100));
    }
};

struct Devastate : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_2)
            return;

        Unit* unitTarget = spell->GetUnitTarget();
        Unit* caster = spell->GetCaster();
        // Sunder Armor
        Aura* sunder = unitTarget->GetAura(SPELL_AURA_MOD_RESISTANCE, SPELLFAMILY_WARRIOR, uint64(0x0000000000004000), caster->GetObjectGuid());

        // 44452 unknown use
        // apply sunder armor first
        if (!sunder || sunder->GetStackAmount() < sunder->GetSpellProto()->StackAmount)
        {
            uint32 sunderId = static_cast<Player*>(caster)->LookupHighestLearnedRank(7386);
            if (sunderId)
                caster->CastSpell(unitTarget, sunderId, TRIGGERED_IGNORE_HIT_CALCULATION | TRIGGERED_IGNORE_GCD | TRIGGERED_IGNORE_COSTS);
        }

        // Devastate bonus and sunder armor refresh, additional threat
        if (sunder)
        {
            if (sunder->GetStackAmount() == sunder->GetSpellProto()->StackAmount)
                sunder->GetHolder()->RefreshHolder();

            spell->SetDamage(spell->GetDamage() * sunder->GetStackAmount());

            // 14 * stack
            unitTarget->AddThreat(caster, 14.0f * sunder->GetStackAmount(), false, GetSpellSchoolMask(spell->m_spellInfo), spell->m_spellInfo);
        }
    }
};

void LoadWarriorScripts()
{
    RegisterSpellScript<WarriorExecute>("spell_warrior_execute");
    RegisterSpellScript<WarriorExecuteDamage>("spell_warrior_execute_damage");
    RegisterSpellScript<VictoryRush>("spell_warrior_victory_rush");
    RegisterSpellScript<Devastate>("spell_devastate");
}
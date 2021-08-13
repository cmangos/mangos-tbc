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

struct SealOfTheCrusader : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const
    {
        if (aura->GetEffIndex() != EFFECT_INDEX_1)
            return;

        // Seal of the Crusader damage reduction
        // SotC increases attack speed but reduces damage to maintain the same DPS
        float reduction = (-100.0f * aura->GetModifier()->m_amount) / (aura->GetModifier()->m_amount + 100.0f);
        aura->GetTarget()->HandleStatModifier(UNIT_MOD_DAMAGE_MAINHAND, TOTAL_PCT, reduction, apply);
    }
};

struct IncreasedHolyLightHealing : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const
    {
        aura->GetTarget()->RegisterScriptedLocationAura(aura, SCRIPT_LOCATION_SPELL_HEALING_DONE, apply);
    }

    void OnDamageCalculate(Aura* aura, int32& advertisedBenefit, float& /*totalMod*/) const override
    {
        advertisedBenefit += aura->GetModifier()->m_amount;
    }
};

struct RighteousDefense : public SpellScript
{
    bool OnCheckTarget(const Spell* spell, Unit* target, SpellEffectIndex /*eff*/) const override
    {
        if (target->HasFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_PLAYER_CONTROLLED) || spell->GetCaster()->CanAssistSpell(target, spell->m_spellInfo))
            return true;

        return false;
    }

    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_0)
            return;

        Unit* unitTarget = spell->GetUnitTarget();
        if (!unitTarget)
            return;
        Unit* caster = spell->GetCaster();

        // non-standard cast requirement check
        if (unitTarget->getAttackers().empty())
        {
            caster->RemoveSpellCooldown(*spell->m_spellInfo, true);
            spell->SendCastResult(SPELL_FAILED_TARGET_AFFECTING_COMBAT);
            return;
        }

        // not empty (checked), copy
        Unit::AttackerSet attackers = unitTarget->getAttackers();

        // selected from list 3
        size_t size = std::min(size_t(3), attackers.size());
        for (uint32 i = 0; i < size; ++i)
        {
            Unit::AttackerSet::iterator aItr = attackers.begin();
            std::advance(aItr, urand() % attackers.size());
            caster->CastSpell((*aItr), 31790, TRIGGERED_NONE); // step 2
            attackers.erase(aItr);
        }
    }
};

enum
{
    SPELL_SEAL_OF_BLOOD_DAMAGE              = 31893,
    SPELL_JUDGEMENT_OF_BLOOD_SELF_DAMAGE    = 32220,
    SPELL_SEAL_OF_BLOOD_SELF_DAMAGE         = 32221
};

struct SealOfBloodSelfDamage : public SpellScript
{
    void OnAfterHit(Spell* spell) const override
    {
        int32 damagePoint = spell->GetTotalTargetDamage() * 33 / 100;
        spell->GetCaster()->CastCustomSpell(nullptr, (spell->m_spellInfo->Id == SPELL_SEAL_OF_BLOOD_DAMAGE ? SPELL_SEAL_OF_BLOOD_SELF_DAMAGE : SPELL_JUDGEMENT_OF_BLOOD_SELF_DAMAGE), &damagePoint, nullptr, nullptr, TRIGGERED_OLD_TRIGGERED);
    }
};

void LoadPaladinScripts()
{
    RegisterAuraScript<IncreasedHolyLightHealing>("spell_increased_holy_light_healing");
    RegisterSpellScript<RighteousDefense>("spell_righteous_defense");
    RegisterAuraScript<SealOfTheCrusader>("spell_seal_of_the_crusader");
    RegisterSpellScript<SealOfBloodSelfDamage>("spell_seal_of_blood_self_damage");
}
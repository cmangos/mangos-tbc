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
#include "Spells/SpellMgr.h"

// 11213 - Arcane Concentration
struct ArcaneConcentration : public AuraScript
{
    bool OnCheckProc(Aura* aura, ProcExecutionData& procData) const override
    {
        if (Spell* spell = procData.spell)
        {
            if (IsChanneledSpell(spell->m_spellInfo))
                return false; // these never proc
            if (SpellEntry const* spellInfo = spell->GetTriggeredByAuraSpellInfo())
            {
                if (IsChanneledSpell(spellInfo))
                {
                    if (Spell* channeledSpell = spell->GetCaster()->GetCurrentSpell(CURRENT_CHANNELED_SPELL))
                    {
                        if (channeledSpell->IsAuraProcced(aura))
                            return false;

                        channeledSpell->RegisterAuraProc(aura);
                    }
                }
            }
            spell->RegisterAuraProc(aura);
        }
        return true;
    }
};

// 11170 - Shatter
struct ShatterMage : public AuraScript
{
    void OnApply(Aura* aura, bool apply) const override
    {
        aura->GetTarget()->RegisterScriptedLocationAura(aura, SCRIPT_LOCATION_CRIT_CHANCE, apply);
    }

    void OnCritChanceCalculate(Aura* aura, Unit const* target, float& chance, SpellEntry const* /*spellInfo*/) const override
    {
        switch (aura->GetModifier()->m_miscvalue)
        {
            // Shatter
            case 849: if (target->isFrozen()) chance += 10.0f; break;
            case 910: if (target->isFrozen()) chance += 20.0f; break;
            case 911: if (target->isFrozen()) chance += 30.0f; break;
            case 912: if (target->isFrozen()) chance += 40.0f; break;
            case 913: if (target->isFrozen()) chance += 50.0f; break;
            default:
                break;
        }
    }
};

// 543 - Fire Ward
struct FireWardMage : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& data, int32 value) const override
    {
        if (data.caster)
        {
            if (data.caster->HasSpell(13043)) // Molten Shields
                value += data.caster->CalculateSpellEffectValue(data.target, sSpellTemplate.LookupEntry<SpellEntry>(13043), EFFECT_INDEX_0);
            else if (data.caster->HasSpell(11094)) // Molten Shields
                value += data.caster->CalculateSpellEffectValue(data.target, sSpellTemplate.LookupEntry<SpellEntry>(11094), EFFECT_INDEX_0);
            
        }
        return value;
    }
};

// 6143 - Frost Ward
struct FrostWardMage : public AuraScript
{
    int32 OnAuraValueCalculate(AuraCalcData& data, int32 value) const override
    {
        if (data.caster)
        {
            if (data.caster->HasAura(11189)) // Frost Warding
                value += data.caster->CalculateSpellEffectValue(data.target, sSpellTemplate.LookupEntry<SpellEntry>(11189), EFFECT_INDEX_1);
            else if (data.caster->HasAura(28332)) // Frost Warding
                value += data.caster->CalculateSpellEffectValue(data.target, sSpellTemplate.LookupEntry<SpellEntry>(28332), EFFECT_INDEX_1);

        }
        return value;
    }
};

// 42208 - Blizzard
struct Blizzard : public SpellScript
{
    void OnCast(Spell* spell) const override
    {
        if (spell->GetCaster()->HasOverrideScript(836)) // Improved Blizzard (Rank 1)
            spell->AddPrecastSpell(12484);
        if (spell->GetCaster()->HasOverrideScript(988)) // Improved Blizzard (Rank 2)
            spell->AddPrecastSpell(12485);
        if (spell->GetCaster()->HasOverrideScript(989)) // Improved Blizzard (Rank 3)
            spell->AddPrecastSpell(12486);
    }
};

// 31679 - Molten Fury
struct MoltenFury : public AuraScript
{
    void OnDamageCalculate(Aura* aura, Unit* /*attacker*/, Unit* victim, int32& /*advertisedBenefit*/, float& totalMod) const override
    {
        if (victim->HasAuraState(AURA_STATE_HEALTHLESS_20_PERCENT))
            totalMod *= (100.0f + aura->GetModifier()->m_amount) / 100.0f;
    }
};

// 30455 - Ice Lance
struct IceLance : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_0)
            return;

        Unit* target = spell->GetUnitTarget();
        if (target->isFrozen()) // does not affect damage taken modifiers per research
            spell->SetDamageDoneModifier(3.f, EFFECT_INDEX_0);
    }
};

void LoadMageScripts()
{
    RegisterSpellScript<ArcaneConcentration>("spell_arcane_concentration");
    RegisterSpellScript<ShatterMage>("spell_shatter_mage");
    RegisterSpellScript<FireWardMage>("spell_fire_ward_mage");
    RegisterSpellScript<FrostWardMage>("spell_frost_ward_mage");
    RegisterSpellScript<Blizzard>("spell_blizzard");
    RegisterSpellScript<MoltenFury>("spell_molten_fury");
    RegisterSpellScript<IceLance>("spell_ice_lance");
}
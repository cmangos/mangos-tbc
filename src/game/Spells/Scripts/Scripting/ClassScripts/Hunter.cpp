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

struct HuntersMark : public AuraScript
{
    int32 OnAuraValueCalculate(Aura* aura, Unit* caster, int32 damage) const override
    {
        if (aura->GetEffIndex() == EFFECT_INDEX_2)
        {
            int32 auraValue = 0;
            if (Aura* otherAura = aura->GetHolder()->m_auras[EFFECT_INDEX_1])
                auraValue = otherAura->GetAmount(); // fetch ranged aura AP

            if (Unit* caster = aura->GetCaster())
            {
                Unit::AuraList const& mclassScritAuras = caster->GetAurasByType(SPELL_AURA_OVERRIDE_CLASS_SCRIPTS);
                for (Unit::AuraList::const_iterator j = mclassScritAuras.begin(); j != mclassScritAuras.end(); ++j)
                {
                    switch ((*j)->GetModifier()->m_miscvalue)
                    {
                        case 5236:
                        case 5237:
                        case 5238:
                        case 5239:
                        case 5240:
                            damage = std::min((*j)->GetModifier()->m_amount, auraValue); // use lower, so that talent doesnt make low lvls OP
                            break;
                    }
                }
            }
        }
        return damage;
    }

    SpellAuraProcResult OnProc(Aura* aura, ProcExecutionData& procData) const override
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

struct KillCommand : public SpellScript
{
    void OnHit(Spell* spell) const override
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
        if (!pet->getVictim())
            return;

        uint32 spell_id = 0;
        switch (spell->m_spellInfo->Id)
        {
            case 34026: spell_id = 34027; break;    // rank 1
            default: sLog.outError("KillCommand: Spell %u not handled", spell->m_spellInfo->Id); return;
        }

        pet->CastSpell(pet->getVictim(), spell_id, TRIGGERED_OLD_TRIGGERED);
        return;
    }
};

void LoadHunterScripts()
{
    RegisterAuraScript<HuntersMark>("spell_hunters_mark");
    RegisterSpellScript<KillCommand>("spell_kill_command");
}
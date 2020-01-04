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
    int32 OnDamageCalculate(Aura* aura, Unit* caster, int32 damage) const override
    {
        if (aura->GetEffIndex() == EFFECT_INDEX_2)
        {
            int32 auraValue = 0;
            if (Aura* aura = aura->GetHolder()->m_auras[EFFECT_INDEX_1])
                auraValue = aura->GetAmount(); // fetch ranged aura AP

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

void LoadHunterScripts()
{
    RegisterAuraScript<HuntersMark>("spell_hunters_mark");
}
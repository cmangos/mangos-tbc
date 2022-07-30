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

void LoadMageScripts()
{
    RegisterSpellScript<ArcaneConcentration>("spell_arcane_concentration");
    RegisterSpellScript<Blizzard>("spell_blizzard");
}
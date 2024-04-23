/* This file is part of the ScriptDev2 Project. See AUTHORS file for Copyright information
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

#include "AI/ScriptDevAI/include/sc_common.h"
#include "botanica.h"

enum BotanicaActions
{
    BOTANICA_ACTION_MAX,
};

instance_botanica::instance_botanica(Map* map) : ScriptedInstance(map)
{
    /*
    auto posCheck = [](Unit const* unit) -> bool { return unit->GetPositionY() > 124.5f; };
    auto successEvent = [&]()
    {
        // Trigger Legionnaire group 04 and 05
        instance->GetVariableManager().SetVariable(WORLD_STATE_LEGIONNAIRE_003, 1);
    };
    AddInstanceEvent(SHH_TRIGGER_LEGIONNAIRE, posCheck, successEvent);
    */
}

void instance_botanica::AddInstanceEvent(uint32 id, std::function<bool(Unit const*)> check, std::function<void()> successEvent)
{
    AddCustomAction(id, false, [instance = this->instance, check = check, successEvent = successEvent, id, this]()
    {
        for (const auto& data : instance->GetPlayers())
        {
            if (data.getSource()->IsGameMaster())
                continue;

            if (check(data.getSource()))
            {
                successEvent();
                return;
            }
        }
        ResetTimer(id, 1000);
    });
}

void instance_botanica::Update(const uint32 diff)
{
    UpdateTimers(diff);
}
// 34799 ArcaneDevastation
enum Spells
{
    SPELL_ARCANE_RESONANCE = 34794,
};

struct ArcaneDevastation : public SpellScript
{
    void OnAfterHit(Spell* spell) const override
    {
        Unit* target = spell->m_targets.getUnitTarget();
        target->RemoveAurasDueToSpell(SPELL_ARCANE_RESONANCE);
        return;
    }
};

void AddSC_instance_botanica()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_botanica";
    pNewScript->GetInstanceData = &GetNewInstanceScript<instance_botanica>;
    pNewScript->RegisterSelf();

    RegisterSpellScript<ArcaneDevastation>("spell_arcane_devastation");
}

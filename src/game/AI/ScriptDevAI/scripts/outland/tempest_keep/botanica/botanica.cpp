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
    BOTANICA_TRIGGER_BLOODWARDER_PROTECTOR_01,
    BOTANICA_ACTION_MAX,
};

instance_botanica::instance_botanica(Map* map) : ScriptedInstance(map)
{
    // trigger 1 -1.2472258, Y:87.49708, Z:-5.6631246 
    auto posCheckTrigger01 = [](Unit const* unit) -> bool { return unit->GetPositionY() > 87.147f; };
    // trigger 2 -0.8657537, 143.51009, -5.539602
    auto posCheckTrigger02 = [](Unit const* unit) -> bool { return unit->GetPositionY() > 143.51f; };
    // trigger 3 -0.3957295, 219.5542, -5.54034
    auto posCheckTrigger03 = [](Unit const* unit) -> bool { return unit->GetPositionY() > 219.551f; };
    // trigger 4 -7.0142794, 288.0116, 0.46252948
    auto posCheckTrigger04 = [](Unit const* unit) -> bool { return unit->GetPositionX() < -7.0142794f && unit->GetPositionY() > 219.551f; };

    auto successEvent01 = [&]()
    {
        auto m_bloodwarderGroup = instance->GetCreatures(THIRD_BLOODWARDER_STRING);
        if (m_bloodwarderGroup != nullptr)
        {
            for (Creature* creature : *m_bloodwarderGroup)
            {
                if (!creature->IsAlive())
                    return;

                creature->GetMotionMaster()->MoveWaypoint();
            }
        }
    };
    AddInstanceEvent(BOTANICA_TRIGGER_BLOODWARDER_PROTECTOR_01, posCheckTrigger01, successEvent01);
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

void AddSC_instance_botanica()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_botanica";
    pNewScript->GetInstanceData = &GetNewInstanceScript<instance_botanica>;
    pNewScript->RegisterSelf();
}

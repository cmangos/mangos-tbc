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

/* ScriptData
SDName: world_map_scripts
SD%Complete: 100
SDComment: Quest support: 1126, 4740, 8868, 11538
SDCategory: World Map Scripts
EndScriptData */

#include "AI/ScriptDevAI/include/precompiled.h"
#include "world_map_scripts.h"
#include "World/WorldState.h"
#include "World/WorldStateDefines.h"
#include "Entities/TemporarySpawn.h"
#include <array>
#include <ctime>

enum
{
    EVENT_UC_FROM_GROMGOL_ARRIVAL = 15312,
    EVENT_GROMGOL_FROM_UC_ARRIVAL = 15314,
    EVENT_OG_FROM_UC_ARRIVAL = 15318,
    EVENT_UC_FROM_OG_ARRIVAL = 15320,
    EVENT_OG_FROM_GROMGOL_ARRIVAL = 15322,
    EVENT_GROMGOL_FROM_OG_ARRIVAL = 15324,

    SOUND_ZEPPELIN_HORN = 11804,
};

bool ProcessEventTransports(uint32 uiEventId, Object* pSource, Object* /*pTarget*/, bool /*bIsStart*/)
{
    sWorldState.HandleConditionStateChange(pSource->GetEntry(), uiEventId);

    WorldObject* transport = (WorldObject*)pSource;
    uint32 entry = 0;
    switch (uiEventId)
    {
        case EVENT_UC_FROM_GROMGOL_ARRIVAL: // UC arrival from gromgol
            entry = NPC_HINDENBURG;
            break;
        case EVENT_GROMGOL_FROM_UC_ARRIVAL: // gromgol arrival from UC
            entry = NPC_SQUIBBY_OVERSPECK;
            break;
        case EVENT_OG_FROM_UC_ARRIVAL:      // OG arrival from UC
            entry = NPC_FREZZA;
            break;
        case EVENT_UC_FROM_OG_ARRIVAL:      // UC arrival from OG
            entry = NPC_ZAPETTA;
            break;
        case EVENT_OG_FROM_GROMGOL_ARRIVAL: // OG arrival from gromgol
            entry = NPC_SNURK_BUCKSQUICK;
            break;
        case EVENT_GROMGOL_FROM_OG_ARRIVAL: // gromgol arrival from OG
            entry = NPC_NEZRAZ;
            break;
    }
    if (entry)
        if (Creature* zeppelinMaster = ((ScriptedInstance*)transport->GetMap()->GetInstanceData())->GetSingleCreatureFromStorage(entry))
            zeppelinMaster->PlayDistanceSound(SOUND_ZEPPELIN_HORN);

    return true;
}

void AddSC_world_map_scripts()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "event_transports";
    pNewScript->pProcessEventId = &ProcessEventTransports;
    pNewScript->RegisterSelf();
}

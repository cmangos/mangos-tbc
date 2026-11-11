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
SDName: Instance_Uldaman
SD%Complete: 60
SDComment:
SDCategory: Uldaman
EndScriptData
*/

#include "AI/ScriptDevAI/include/sc_common.h"
#include "uldaman.h"

instance_uldaman::instance_uldaman(Map* pMap) : ScriptedInstance(pMap),
    m_uiKeeperCooldown(0)
{
    Initialize();
}

void instance_uldaman::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    instance->GetVariableManager().SetVariable(WORLD_STATE_CUSTOM_SPAWN_ANNORA, 0);
}

void instance_uldaman::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_TEMPLE_DOOR_UPPER:
        case GO_TEMPLE_DOOR_LOWER:
            if (GetData(TYPE_ALTAR_EVENT) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ANCIENT_VAULT:
            if (GetData(TYPE_ARCHAEDAS) == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ANCIENT_TREASURE:
            break;
        default:
            return;
    }
    m_goEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_uldaman::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_HALLSHAPER:
        case NPC_CUSTODIAN:
            m_sWardens.insert(pCreature->GetObjectGuid());
            break;
        case NPC_STONE_KEEPER:
            m_sKeepers.insert(pCreature->GetObjectGuid());
            break;
        case NPC_ARCHAEDAS:
            m_npcEntryGuidStore[NPC_ARCHAEDAS] = pCreature->GetObjectGuid();
            break;
        default:
            break;
    }
}

// Prototype, hardcoded
void instance_uldaman::OnCreatureGroupDespawn(CreatureGroup* pGroup, Creature* /*pCreature*/)
{
    if (pGroup->GetGroupId() == 7000000)    
        instance->GetVariableManager().SetVariable(WORLD_STATE_CUSTOM_SPAWN_ANNORA, 1);
}

void instance_uldaman::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_ALTAR_EVENT:
            if (uiData == DONE)
            {
                debug_log("SD2: Uldaman: altar event DONE, opening temple doors");
                DoUseOpenableObject(GO_TEMPLE_DOOR_UPPER, true);
                DoUseOpenableObject(GO_TEMPLE_DOOR_LOWER, true);
            }
            else if (uiData == IN_PROGRESS)
            {
                if (m_sKeepers.empty())
                {
                    script_error_log("Instance Uldaman: cannot start altar event, no Stone Keepers registered");
                    return;
                }

                // Also do a reset before starting the event - this will respawn dead Keepers
                DoResetKeeperEvent();
                m_uiKeeperCooldown = 5000;
            }
            else if (uiData == NOT_STARTED)
            {
                DoResetKeeperEvent();
            }
            m_auiEncounter[0] = uiData;
            break;

        case TYPE_ARCHAEDAS:
            if (uiData == DONE)
            {
                DoUseDoorOrButton(GO_ANCIENT_VAULT);
                DoRespawnGameObject(GO_ANCIENT_TREASURE, HOUR);
            }
            m_auiEncounter[1] = uiData;
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1];

        m_strInstData = saveStream.str();
        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_uldaman::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1];

    for (uint32& i : m_auiEncounter)
    {
        if (i == IN_PROGRESS)
            i = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

void instance_uldaman::SetData64(uint32 uiData, uint64 uiGuid)
{
    switch (uiData)
    {
        // ToDo: check if this one is used in ACID. Otherwise it can be dropped
        case DATA_EVENT_STARTER:
            m_playerGuid = ObjectGuid(uiGuid);
            break;
    }
}

uint32 instance_uldaman::GetData(uint32 uiType) const
{
    switch (uiType)
    {
        case TYPE_ALTAR_EVENT:
            return m_auiEncounter[0];
        case TYPE_ARCHAEDAS:
            return m_auiEncounter[1];
    }
    return 0;
}

uint64 instance_uldaman::GetData64(uint32 uiData) const
{
    switch (uiData)
    {
        case DATA_EVENT_STARTER:
            return m_playerGuid.GetRawValue();
    }
    return 0;
}

void instance_uldaman::StartEvent(uint32 uiEventId, Player* pPlayer)
{
    m_playerGuid = pPlayer->GetObjectGuid();

    if (uiEventId == EVENT_ID_ALTAR_KEEPER)
    {
        if (GetData(TYPE_ALTAR_EVENT) == NOT_STARTED)
            SetData(TYPE_ALTAR_EVENT, IN_PROGRESS);
    }
    else if (uiEventId == EVENT_ID_ALTAR_ARCHAEDAS)
    {
        if (GetData(TYPE_ARCHAEDAS) == NOT_STARTED || GetData(TYPE_ARCHAEDAS) == FAIL)
            SetData(TYPE_ARCHAEDAS, SPECIAL);
    }
}

void instance_uldaman::DoResetKeeperEvent()
{
    // Start every attempt from a clean slate, even if a previous attempt left
    // dead keepers behind.
    m_sDeadKeepers.clear();

    if (m_sKeepers.empty())
    {
        script_error_log("Instance Uldaman: ERROR creature %u couldn't be found or something really bad happened.", NPC_STONE_KEEPER);
        return;
    }

    // Force reset all keepers to the original state
    for (ObjectGuid const& guid : m_sKeepers)
    {
        if (Creature* pKeeper = instance->GetCreature(guid))
        {
            if (!pKeeper->IsAlive())
                pKeeper->Respawn();
        }
    }
}

Creature* instance_uldaman::GetClosestDwarfNotInCombat(Creature* pSearcher)
{
    CreatureList lTemp;

    for (ObjectGuid const& guid : m_sWardens)
    {
        Creature* pTemp = instance->GetCreature(guid);

        if (pTemp && pTemp->IsAlive() && !pTemp->GetVictim())
            lTemp.push_back(pTemp);
    }

    if (lTemp.empty())
        return nullptr;

    lTemp.sort(ObjectDistanceOrder(pSearcher));
    return lTemp.front();
}

void instance_uldaman::OnCreatureEvade(Creature* pCreature)
{
    // Reset the altar event only while it is still running. Once it is DONE,
    // a late keeper evade must not undo the door state.
    if (pCreature->GetEntry() == NPC_STONE_KEEPER && GetData(TYPE_ALTAR_EVENT) == IN_PROGRESS)
        SetData(TYPE_ALTAR_EVENT, NOT_STARTED);
}

void instance_uldaman::OnCreatureDeath(Creature* pCreature)
{
    if (pCreature->GetEntry() != NPC_STONE_KEEPER)
        return;

    if (GetData(TYPE_ALTAR_EVENT) != IN_PROGRESS)
        return;

    if (m_sKeepers.empty())
    {
        script_error_log("Instance Uldaman: Stone Keeper died but no keepers are registered");
        return;
    }

    m_sDeadKeepers.insert(pCreature->GetObjectGuid());

    // If a keeper respawned mid-event, it is alive again and must not remain
    // counted as dead.
    for (GuidSet::iterator itr = m_sDeadKeepers.begin(); itr != m_sDeadKeepers.end();)
    {
        Creature* pKeeper = instance->GetCreature(*itr);
        if (pKeeper && pKeeper->IsAlive())
            itr = m_sDeadKeepers.erase(itr);
        else
            ++itr;
    }

    uint32 deadCount = 0;
    for (ObjectGuid const& guid : m_sKeepers)
        if (m_sDeadKeepers.find(guid) != m_sDeadKeepers.end())
            ++deadCount;

    debug_log("SD2: Uldaman: keeper died, %u/%u dead", deadCount, uint32(m_sKeepers.size()));

    if (deadCount == m_sKeepers.size())
        SetData(TYPE_ALTAR_EVENT, DONE);
    else
        m_uiKeeperCooldown = 5000;
}

void instance_uldaman::Update(uint32 uiDiff)
{
    if (GetData(TYPE_ALTAR_EVENT) != IN_PROGRESS)
        return;

    if (!m_uiKeeperCooldown)
        return;

    if (m_uiKeeperCooldown <= uiDiff)
    {
        for (ObjectGuid const& guid : m_sKeepers)
        {
            // Get Keeper which is alive and out of combat
            Creature* pKeeper = instance->GetCreature(guid);
            if (!pKeeper || !pKeeper->IsAlive() || pKeeper->GetVictim())
                continue;

            // Get starter player for attack
            Player* pPlayer = pKeeper->GetMap()->GetPlayer(m_playerGuid);
            if (!pPlayer || !pPlayer->IsAlive())
            {
                // If he's not available, then get a random player, within a reasonamble distance in map
                pPlayer = GetPlayerInMap(true, false);
                if (!pPlayer || !pPlayer->IsWithinDistInMap(pKeeper, 50.0f))
                {
                    SetData(TYPE_ALTAR_EVENT, NOT_STARTED);
                    return;
                }
            }

            // Attack the player
            pKeeper->RemoveAurasDueToSpell(SPELL_STONED);
            pKeeper->AI()->AttackStart(pPlayer);
            break;
        }

        m_uiKeeperCooldown = 0;
    }
    else
        m_uiKeeperCooldown -= uiDiff;
}

InstanceData* GetInstanceData_instance_uldaman(Map* pMap)
{
    return new instance_uldaman(pMap);
}

bool ProcessEventId_event_spell_altar_boss_aggro(uint32 uiEventId, Object* pSource, Object* /*pTarget*/, bool bIsStart)
{
    if (bIsStart && pSource->GetTypeId() == TYPEID_PLAYER)
    {
        if (instance_uldaman* pInstance = (instance_uldaman*)((Player*)pSource)->GetInstanceData())
        {
            pInstance->StartEvent(uiEventId, (Player*)pSource);
            return true;
        }
    }
    return false;
}

void AddSC_instance_uldaman()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_uldaman";
    pNewScript->GetInstanceData = &GetInstanceData_instance_uldaman;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "event_spell_altar_boss_aggro";
    pNewScript->pProcessEventId = &ProcessEventId_event_spell_altar_boss_aggro;
    pNewScript->RegisterSelf();
}

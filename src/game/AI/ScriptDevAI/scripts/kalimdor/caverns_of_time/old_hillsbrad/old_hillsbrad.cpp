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
SDName: Instance_Old_Hillsbrad
SD%Complete: 75
SDComment: Thrall reset on server restart is not supported, because of core limitation.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "old_hillsbrad.h"

instance_old_hillsbrad::instance_old_hillsbrad(Map* pMap) : ScriptedInstance(pMap),
    m_uiBarrelCount(0),
    m_uiThrallEventCount(0),
    m_uiDrakeStep(0)
{
    Initialize();
}


enum OHFActions
{
    OHF_BARREL_RP,
    OHF_THRALL_RESET,
    OHF_EPOCH_WAVES,
};

void instance_old_hillsbrad::Initialize()
{
    // On soft reset - Those trash respawns again
    // Trash in the Huts that cant respawn when Lieutnant Drake is alive
    instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_DRAKE_TRASH_RESPAWN, 0);
    // Trash on the Bridges that get despawned when player starts Thrall escort
    instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_THRALL_TRASH_RESPAWN, 0);
    // Trash and friendly npcs around tarren mill that get despawned during Epoch Hunter Event
    instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_TARREN_MILL_DESPAWN, 0);

    // If Escort got finished we keep Barrels and all Escort related NPCs despawned
    if (GetData(TYPE_THRALL_EVENT) == DONE)
        instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_THRALL_ESCORT, 1);
    else
    {
        instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_THRALL_ESCORT, 0);
        // For safety reason (crash)
        HandleThrallRelocation();        
    }

    AddCustomAction(OHF_BARREL_RP, true, [&]() { DoBarrelRP(); });
    AddCustomAction(OHF_THRALL_RESET, true, [&]() { HandleThrallRelocation(); });
    AddCustomAction(OHF_EPOCH_WAVES, true, [&]() { SpawnWave(); });
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_old_hillsbrad::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_THRALL:
        case NPC_TARETHA:
        case NPC_ARMORER:
        case NPC_EROZION:
        case NPC_DRAKE:
        case NPC_SKARLOC:
        case NPC_EPOCH:
        case NPC_BARTOLO:
        case NPC_COMMANDER_MOGRAINE:
        case NPC_COT_DESPAWN_TRIGGER:
        case NPC_SKARLOCS_MOUNT:
            m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
    }
}

void instance_old_hillsbrad::OnCreatureRespawn(Creature* creature)
{
    switch (creature->GetEntry())
    {
        case NPC_SKARLOC:
            // Confirmed from TBC Anni that on soft reset Thrall respawns at Prison and players can do the Escort again
            // Guessed: To prevent getting double boss loot (confirmed on mop classic) 
            if (GetData(TYPE_SKARLOC) == DONE)
            {
                creature->SetNoXP(true);
                creature->SetNoLoot(true);
                creature->SetNoReputation(true);
            }
        break;
        case NPC_IMAGE_EROZION: 
        {            
            // on try 19 there is another Text - no text after 20 trys
            if (m_uiThrallEventCount == 19)
                DoBroadcastText(SAY_ERONZION_RESET_LAST, creature);
            else if (m_uiThrallEventCount <= MAX_WIPE_COUNTER)
                DoBroadcastText(SAY_ERONZION_RESET_THRALL, creature);
        }
        case NPC_EROZION:
            if (creature->HasStringId("OHF_EROZION_TARRENMILL"))
                UpdateEscortQuestCredit();
    }
}
void instance_old_hillsbrad::OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_DRAKE:   SetData(TYPE_DRAKE, DONE);   break;
        case NPC_SKARLOC: SetData(TYPE_SKARLOC, DONE); break;
        case NPC_EPOCH:   SetData(TYPE_EPOCH, DONE);   break;
    }
}

void instance_old_hillsbrad::OnCreatureEnterCombat(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_DRAKE: SetData(TYPE_DRAKE, IN_PROGRESS); break;
        case NPC_SKARLOC: SetData(TYPE_SKARLOC, IN_PROGRESS); break;
        case NPC_EPOCH:   SetData(TYPE_EPOCH, IN_PROGRESS);   break;
    }
}

void instance_old_hillsbrad::OnCreatureEvade(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_DRAKE:   SetData(TYPE_DRAKE, FAIL);   break;
        case NPC_SKARLOC: SetData(TYPE_SKARLOC, FAIL); break;
        case NPC_EPOCH:   SetData(TYPE_EPOCH, FAIL);   break;
    }
}

void instance_old_hillsbrad::OnCreatureDespawn(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_SKARLOC:
            if (GetData(TYPE_SKARLOC) == IN_PROGRESS) 
                SetData(TYPE_SKARLOC, FAIL); 
            break;
    }
}

void instance_old_hillsbrad::OnObjectCreate(GameObject* pGo)
{
    if (pGo->GetEntry() == GO_PRISON_DOOR)
        m_goEntryGuidStore[GO_PRISON_DOOR] = pGo->GetObjectGuid();
}

void instance_old_hillsbrad::OnCreatureGroupDespawn(CreatureGroup* creatureGroup, Creature* /*pCreature*/)
{
    if (creatureGroup->HasStringId("OHF_BARN_GROUP"))
        if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL))
            if (thrall->IsAlive())
                thrall->GetMotionMaster()->UnpauseWaypoints();

    // Spawn next Wave if group died before timer but only if next wave isnt spawned yet
    if (creatureGroup->HasStringId("OHF_EPOCH_WAVE_01"))
        if (m_uiWave == 2)
            SpawnWave();

    if (creatureGroup->HasStringId("OHF_EPOCH_WAVE_02"))
        if (m_uiWave == 3)
            SpawnWave();

    if (creatureGroup->HasStringId("OHF_EPOCH_WAVE_03"))
        if (m_uiWave == 4)
            SpawnWave();
}

void instance_old_hillsbrad::OnPlayerEnter(Player* pPlayer)
{
}

void instance_old_hillsbrad::HandleThrallRelocation()
{
    if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
    {
        debug_log("SD2: Instance Old Hillsbrad: Thrall relocation");

        // Thrall already got spawned
        if (thrall->IsAlive())
            return;

        // Despawn Corpse
        thrall->ForcedDespawn();
    }

    if (GetData(TYPE_ESCORT_INN) == DONE)
    {
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);

        // respawn thrall
        if (SpawnGroup* thrallGroup = instance->GetSpawnManager().GetSpawnGroup("OHF_THRALL_INN"))
            thrallGroup->Spawn(true, true);

        // readd Gossip Flag for Taretha and remove standstate
        if (Creature* taretha = GetSingleCreatureFromStorage(NPC_TARETHA, true))
        {
            taretha->RemoveAurasDueToSpell(SPELL_SHADOW_SPIKE);
            taretha->SetStandState(UNIT_STAND_STATE_STAND);
            taretha->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
        else 
        {
        // Something went wrong, respawn
            if (SpawnGroup* taretha = instance->GetSpawnManager().GetSpawnGroup("OHF_TARETHA"))
                taretha->Spawn(true, true);
        }
    }
    else if (GetData(TYPE_ESCORT_BARN) == DONE)
    {
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
        // respawn thrall
        if (SpawnGroup* thrallGroup = instance->GetSpawnManager().GetSpawnGroup("OHF_THRALL_BARN"))
            thrallGroup->Spawn(true, true);
    }
    // Skarloc Dead - Respawn at that Position
    else if (GetData(TYPE_ESCORT_SKARLOC) == DONE)
    {
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
        // respawn thrall
        if (SpawnGroup* thrallGroup = instance->GetSpawnManager().GetSpawnGroup("OHF_THRALL_SKARLOC"))
            thrallGroup->Spawn(true, true);

        // Also respawn Horse
        if (SpawnGroup* horseGroup = instance->GetSpawnManager().GetSpawnGroup("OHF_SKARLOC_MOUNT"))
            horseGroup->Spawn(true, true);
    }
    // Died before Skarloc - respawn at Prison and Close Door
    else
    {
        SetData(TYPE_THRALL_EVENT, NOT_STARTED);
        // respawn thrall
        if (SpawnGroup* thrallGroup = instance->GetSpawnManager().GetSpawnGroup("OHF_THRALL_PRISON"))
            thrallGroup->Spawn(true, true);

        DoUseDoorOrButton(GO_PRISON_DOOR);
    }
}

void instance_old_hillsbrad::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_BARREL_DIVERSION:
            m_auiEncounter[uiType] = uiData;
            if (uiData == SPECIAL)
            {
                if (m_uiBarrelCount >= MAX_BARRELS)
                    return;

                // Update barrels used and world state
                ++m_uiBarrelCount;
                DoUpdateWorldState(WORLD_STATE_OLD_HILLSBRAD_BARREL_COUNT, m_uiBarrelCount);

                debug_log("SD2: Instance Old Hillsbrad: go_barrel_old_hillsbrad count %u", m_uiBarrelCount);
                
                // 5 Barrels used - Worldstate still gets shown ingame                
                if (m_uiBarrelCount == MAX_BARRELS)
                {
                    ResetTimer(OHF_BARREL_RP, 3000);
                    m_uiDrakeStep = 1;
                }
                // Change to IN_PROGRESS for gossip condition handling
                SetData(TYPE_BARREL_DIVERSION, IN_PROGRESS);
            }
            break;
        case TYPE_THRALL_EVENT:
            // nothing to do if already done and thrall respawn
            if (GetData(TYPE_THRALL_EVENT) == DONE)
                return;
            m_auiEncounter[uiType] = uiData;
            if (uiData == FAIL)
            {                
                // CoT Hillsbrad Despawn Trigger - spell cast depending on "phase"
                if (GetData(TYPE_ESCORT_INN) == DONE)
                {
                    if (Creature* despawnTrigger = GetSingleCreatureFromStorage(NPC_COT_DESPAWN_TRIGGER))
                        despawnTrigger->AI()->DoCastSpellIfCan(nullptr, SPELL_STUN_PHASE_5);
                }
                else if (GetData(TYPE_ESCORT_BARN) == DONE)
                {
                    if (Creature* despawnTrigger = GetSingleCreatureFromStorage(NPC_COT_DESPAWN_TRIGGER))
                        despawnTrigger->AI()->DoCastSpellIfCan(nullptr, SPELL_STUN_PHASE_4);
                } 
                else if (GetData(TYPE_ESCORT_SKARLOC) == DONE)
                {
                    if (Creature* despawnTrigger = GetSingleCreatureFromStorage(NPC_COT_DESPAWN_TRIGGER))
                        despawnTrigger->AI()->DoCastSpellIfCan(nullptr, SPELL_STUN_PHASE_3);
                }
                else
                {
                    if (Creature* despawnTrigger = GetSingleCreatureFromStorage(NPC_COT_DESPAWN_TRIGGER))
                        despawnTrigger->AI()->DoCastSpellIfCan(nullptr, SPELL_STUN_PHASE_2);
                }

                if (Creature* armorer = GetSingleCreatureFromStorage(NPC_ARMORER))
                    armorer->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_B, armorer, armorer);
                    
                if (GetData(TYPE_EPOCH_WAVE) == IN_PROGRESS)
                {
                    SetData(TYPE_EPOCH_WAVE, NOT_STARTED);
                    DisableTimer(OHF_EPOCH_WAVES);
                }
                if (m_uiThrallEventCount <= MAX_WIPE_COUNTER)
                {
                    ++m_uiThrallEventCount;
                    debug_log("SD2: Instance Old Hillsbrad: Thrall event failed %u times.", m_uiThrallEventCount);

                    // reset Thrall on timer
                    ResetTimer(OHF_THRALL_RESET, 30000);
                }
                // If we already respawned Thrall too many times, the event is failed for good
                else if (m_uiThrallEventCount > MAX_WIPE_COUNTER)
                    debug_log("SD2: Instance Old Hillsbrad: Thrall event failed %u times. Reset instance required.", m_uiThrallEventCount);
            }
            break;
        case TYPE_DRAKE:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)           
                instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_DRAKE_TRASH_RESPAWN, 0);
                break;
        case TYPE_SKARLOC:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {                
                if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
                    thrall->GetMotionMaster()->UnpauseWaypoints();

                SetData(TYPE_ESCORT_SKARLOC, DONE);
            }
            break;
        case TYPE_EPOCH_WAVE: 
            m_auiEncounter[uiType] = uiData;
            if (uiData == IN_PROGRESS)
            {
                m_uiWave = 1;
                ResetTimer(OHF_EPOCH_WAVES, 5000);
            }
            break;
        case TYPE_EPOCH:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                // Safety
                if (GetData(TYPE_EPOCH_WAVE) == IN_PROGRESS)
                {
                    SetData(TYPE_EPOCH_WAVE, DONE);
                    DisableTimer(OHF_EPOCH_WAVES);
                }
                // Start end RP
                if (Creature* taretha = GetSingleCreatureFromStorage(NPC_TARETHA))
                {
                    if (taretha->IsAlive())
                    {
                        taretha->RemoveAllAuras();
                        taretha->SetStandState(UNIT_STAND_STATE_STAND);
                        taretha->SetWalk(false);
                        taretha->GetMotionMaster()->MovePath();
                    }
                }
            }
            break;
        case TYPE_ESCORT_BARN:
        case TYPE_ESCORT_INN:
        case TYPE_ESCORT_SKARLOC:
            m_auiEncounter[uiType] = uiData;
            debug_log("SD2: Instance Old Hillsbrad: Thrall event type %u adjusted to data %u.", uiType, uiData);
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                   << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5] << " "
                   << m_auiEncounter[6];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

uint32 instance_old_hillsbrad::GetData(uint32 uiType) const
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

void instance_old_hillsbrad::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
               >> m_auiEncounter[4] >> m_auiEncounter[5] >> m_auiEncounter[6];

    for (uint32& i : m_auiEncounter)
    {
        if (i == IN_PROGRESS)
            i = NOT_STARTED;
    }

    // custom reload
    // If Epoch event is not done, we have to redo barrel and full escort
    if (m_auiEncounter[7] != DONE)
    {
        m_auiEncounter[0] = NOT_STARTED;    // Barrel
        m_auiEncounter[3] = NOT_STARTED;    // Thrall respawning at Skarloc
        m_auiEncounter[4] = NOT_STARTED;    // Thrall respawning at Barn
        m_auiEncounter[5] = NOT_STARTED;    // Thrall respawning at Inn
        m_auiEncounter[6] = NOT_STARTED;    // Epoch Hunter Waves
        m_auiEncounter[8] = NOT_STARTED;    // Escort
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

void instance_old_hillsbrad::ShowChatCommands(ChatHandler* handler)
{
    handler->SendSysMessage("This instance supports the following commands:\n barrel, prison, skarloc, barn, epoch");
}

void instance_old_hillsbrad::ExecuteChatCommand(ChatHandler* handler, char* args)
{
    char* result = handler->ExtractLiteralArg(&args);
    if (!result)
        return;
    std::string val = result;
    if (val == "barrel")
    {        
        m_uiBarrelCount = MAX_BARRELS;

        ResetTimer(OHF_BARREL_RP, 3000);
        m_uiDrakeStep = 1;
 
        // Change to IN_PROGRESS for gossip condition handling
        SetData(TYPE_BARREL_DIVERSION, IN_PROGRESS);
    }
    else if (val == "prison")
    {
        // Nothing started yet
        SetData(TYPE_SKARLOC, NOT_STARTED);
        SetData(TYPE_ESCORT_SKARLOC, NOT_STARTED);
        SetData(TYPE_ESCORT_BARN, NOT_STARTED);
        SetData(TYPE_ESCORT_INN, NOT_STARTED);
        SetData(TYPE_EPOCH, NOT_STARTED);
        SetData(TYPE_THRALL_EVENT, NOT_STARTED);
        if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
            thrall->ForcedDespawn();
        HandleThrallRelocation();
    }
    else if (val == "skarloc")
    {
        SetData(TYPE_SKARLOC, DONE);
        SetData(TYPE_ESCORT_SKARLOC, DONE);
        SetData(TYPE_ESCORT_BARN, NOT_STARTED);
        SetData(TYPE_ESCORT_INN, NOT_STARTED);
        SetData(TYPE_EPOCH, NOT_STARTED);
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
        if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
            thrall->ForcedDespawn();
        HandleThrallRelocation();
    }
    else if (val == "barn")
    {
        SetData(TYPE_SKARLOC, DONE);
        SetData(TYPE_ESCORT_SKARLOC, DONE);
        SetData(TYPE_ESCORT_BARN, DONE);
        SetData(TYPE_ESCORT_INN, NOT_STARTED);
        SetData(TYPE_EPOCH, NOT_STARTED);
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
        if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
            thrall->ForcedDespawn();
        HandleThrallRelocation();
    }
    else if (val == "epoch")
    {
        SetData(TYPE_SKARLOC, DONE);
        SetData(TYPE_ESCORT_SKARLOC, DONE);
        SetData(TYPE_ESCORT_BARN, DONE);
        SetData(TYPE_ESCORT_INN, DONE);
        SetData(TYPE_EPOCH, NOT_STARTED);
        SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
        if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL, true))
            thrall->ForcedDespawn();
        HandleThrallRelocation();
    }
}

bool instance_old_hillsbrad::CheckConditionCriteriaMeet(Player const* player, uint32 instanceConditionId, WorldObject const* conditionSource, uint32 conditionSourceType) const
{
    switch (instanceConditionId)
    {
        case INSTANCE_CONDITION_ID_THRALL_STARTABLE:
            return (GetData(TYPE_BARREL_DIVERSION) == IN_PROGRESS);
    }

    script_error_log("instance_old_hillsbrad::CheckConditionCriteriaMeet called with unsupported Id %u. Called with param plr %s, src %s, condition source type %u",
        instanceConditionId,
        player ? player->GetGuidStr().c_str() : "nullptr",
        conditionSource ? conditionSource->GetGuidStr().c_str() : "nullptr",
        conditionSourceType);
    return false;
}

void instance_old_hillsbrad::UpdateLodgeQuestCredit()
{
    Map::PlayerList const& players = instance->GetPlayers();

    if (!players.isEmpty())
    {
        for (const auto& player : players)
        {
            if (Player* pPlayer = player.getSource())
                pPlayer->KilledMonsterCredit(NPC_LODGE_QUEST_TRIGGER);
        }
    }
}

void instance_old_hillsbrad::UpdateEscortQuestCredit()
{
    Map::PlayerList const& players = instance->GetPlayers();

    if (!players.isEmpty())
    {
        for (const auto& player : players)
        {
            if (Player* pPlayer = player.getSource())
                pPlayer->KilledMonsterCredit(NPC_ESCORT_QUEST_TRIGGER);
        }
    }
}

void instance_old_hillsbrad::DoBarrelRP()
{
    switch (m_uiDrakeStep)
    {
        case 1: 
        {
            // First spawn  all Roaring Flames - despawning on soft reset
            if (SpawnGroup* roaringFlames = instance->GetSpawnManager().GetSpawnGroup("OHF_ROARING_FLAMES"))
                roaringFlames->Spawn(true, true);
            ResetTimer(OHF_BARREL_RP, 2000);
            m_uiDrakeStep = 2;
            break;
        }
        case 2: 
        {
            // Spawn Lieutnant Drake only if not already done and prevent enemy npc respawning
            if (GetData(TYPE_DRAKE) != DONE)
            {
                if (SpawnGroup* lieutnantDrake = instance->GetSpawnManager().GetSpawnGroup("OHF_LIEUTENANTDRAKE"))
                    lieutnantDrake->Spawn(true, true);

                instance->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_DRAKE_TRASH_RESPAWN, 1);
            }

            // Orc Prisoners and all alive enemy NPC groups around the orc Huts will have differen RP elements after Lieutenant Drake spawned
            // Everything gets handled via EAI activated with AI_EVENT_CUSTOM_EVENTAI_A
            if (std::vector<Creature*> const* drakerpSpecial = instance->GetCreatures("OHF_DRAKE_RP_SPECIAL"))
            {
                for (Creature* creature : *drakerpSpecial)
                    creature->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_A, creature, creature);
            }
            ResetTimer(OHF_BARREL_RP, 7000);
            m_uiDrakeStep = 3;
            break;
        }
        case 3: 
        {
            // Remove Barrel Worldstate and update quests
            UpdateLodgeQuestCredit();
            DoUpdateWorldState(WORLD_STATE_OLD_HILLSBRAD_BARREL_COUNT, 0);
            break;
        }
    }
}

void instance_old_hillsbrad::SpawnWave()
{
    switch (m_uiWave)
    {
        case 1: 
        {
            if (SpawnGroup* wave01 = instance->GetSpawnManager().GetSpawnGroup("OHF_EPOCH_WAVE_01"))
                wave01->Spawn(true, true);
            m_uiWave = 2;            
            ResetTimer(OHF_EPOCH_WAVES, 95000);
            break;
        }
        case 2: 
        {
            if (SpawnGroup* wave02 = instance->GetSpawnManager().GetSpawnGroup("OHF_EPOCH_WAVE_02"))
                wave02->Spawn(true, true);

            if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL))
                if (thrall->IsAlive())
                    thrall->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, thrall, thrall);
            m_uiWave = 3;
            ResetTimer(OHF_EPOCH_WAVES, 95000);
            break;
        }
        case 3: 
        {
            if (SpawnGroup* wave03 = instance->GetSpawnManager().GetSpawnGroup("OHF_EPOCH_WAVE_03"))
                wave03->Spawn(true, true);

            if (Creature* thrall = GetSingleCreatureFromStorage(NPC_THRALL))
                if (thrall->IsAlive())
                    thrall->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, thrall, thrall);
            
            m_uiWave = 4;
            ResetTimer(OHF_EPOCH_WAVES, 120000);
            break;
        }
        case 4: 
        {
            SetData(TYPE_EPOCH_WAVE, DONE);
            if (Creature* epoch = GetSingleCreatureFromStorage(NPC_EPOCH))
                if (epoch->IsAlive())
                    epoch->GetMotionMaster()->MoveWaypoint();
            break;
        }
    }
}


void instance_old_hillsbrad::Update(uint32 uiDiff)
{
    UpdateTimers(uiDiff);
}

InstanceData* GetInstanceData_instance_old_hillsbrad(Map* pMap)
{
    return new instance_old_hillsbrad(pMap);
}

bool ProcessEventId_event_go_barrel_old_hillsbrad(uint32 /*uiEventId*/, Object* pSource, Object* pTarget, bool bIsStart)
{
    if (bIsStart && pSource->GetTypeId() == TYPEID_PLAYER)
    {
        if (instance_old_hillsbrad* pInstance = (instance_old_hillsbrad*)((Player*)pSource)->GetInstanceData())
        {
            if (static_cast<GameObject*>(pTarget)->HasFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT))
                return true;

            pInstance->SetData(TYPE_BARREL_DIVERSION, SPECIAL);

            // Don't allow players to use same object twice
            if (pTarget->GetTypeId() == TYPEID_GAMEOBJECT)
                ((GameObject*)pTarget)->SetFlag(GAMEOBJECT_FLAGS, GO_FLAG_NO_INTERACT);

            return true;
        }
    }
    return false;
}

void AddSC_instance_old_hillsbrad()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_old_hillsbrad";
    pNewScript->GetInstanceData = &GetInstanceData_instance_old_hillsbrad;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "event_go_barrel_old_hillsbrad";
    pNewScript->pProcessEventId = &ProcessEventId_event_go_barrel_old_hillsbrad;
    pNewScript->RegisterSelf();
}

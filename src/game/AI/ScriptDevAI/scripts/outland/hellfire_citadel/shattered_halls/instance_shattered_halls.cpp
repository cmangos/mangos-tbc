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
SDName: Instance_Shattered_Halls
SD%Complete: 50
SDComment: currently missing info about door. instance not complete
SDCategory: Hellfire Citadel, Shattered Halls
EndScriptData */

#include "AI/ScriptDevAI/include/precompiled.h"
#include "shattered_halls.h"

instance_shattered_halls::instance_shattered_halls(Map* pMap) : ScriptedInstance(pMap),
    m_uiExecutionTimer(55 * MINUTE * IN_MILLISECONDS),
    m_uiTeam(0),
    m_uiExecutionStage(0),
    m_uiPrisonersLeft(3)
{
    Initialize();
}

void instance_shattered_halls::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
}

void instance_shattered_halls::OnPlayerEnter(Player* pPlayer)
{
    // Only on heroic
    if (instance->IsRegularDifficulty() || m_uiTeam)
        return;

    m_uiTeam = pPlayer->GetTeam();

    if (m_uiTeam == ALLIANCE)
        pPlayer->SummonCreature(aSoldiersLocs[1].m_uiAllianceEntry, aSoldiersLocs[1].m_fX, aSoldiersLocs[1].m_fY, aSoldiersLocs[1].m_fZ, aSoldiersLocs[1].m_fO, TEMPSPAWN_DEAD_DESPAWN, 0);
    else
        pPlayer->SummonCreature(aSoldiersLocs[0].m_uiHordeEntry, aSoldiersLocs[0].m_fX, aSoldiersLocs[0].m_fY, aSoldiersLocs[0].m_fZ, aSoldiersLocs[0].m_fO, TEMPSPAWN_DEAD_DESPAWN, 0);
}

void instance_shattered_halls::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_NETHEKURSE_DOOR:
            if (m_auiEncounter[TYPE_NETHEKURSE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_NETHEKURSE_ENTER_DOOR:
            if (m_auiEncounter[TYPE_NETHEKURSE] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_BLAZE:
            m_vBlazeTimers.push_back({ pGo->GetObjectGuid(), 0 });
            break;
        default:
            return;
    }

    m_goEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_shattered_halls::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_NETHEKURSE:
        case NPC_KARGATH_BLADEFIST:
        case NPC_EXECUTIONER:
        case NPC_SOLDIER_ALLIANCE_2:
        case NPC_SOLDIER_ALLIANCE_3:
        case NPC_OFFICER_ALLIANCE:
        case NPC_SOLDIER_HORDE_2:
        case NPC_SOLDIER_HORDE_3:
        case NPC_OFFICER_HORDE:
            m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        case NPC_ZEALOT:
        case NPC_SCOUT:
            if (pCreature->IsTemporarySummon())
                m_vGauntletTemporaryGuids.push_back(pCreature->GetObjectGuid());
            else
                m_vGauntletPermanentGuids.push_back(pCreature->GetObjectGuid());
            break;
        case NPC_BLOOD_GUARD:
        case NPC_PORUNG:
        case NPC_ARCHER:
            m_vGauntletBossGuids.push_back(pCreature->GetObjectGuid());
            break;
        case NPC_GAUNTLET_OF_FIRE:
            m_guidGauntletNPC = pCreature->GetObjectGuid();
            break;
    }
}

void instance_shattered_halls::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_NETHEKURSE:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                DoUseDoorOrButton(GO_NETHEKURSE_DOOR);
                DoUseDoorOrButton(GO_NETHEKURSE_ENTER_DOOR);
            }
            break;
        case TYPE_OMROGG:
            m_auiEncounter[uiType] = uiData;
            break;
        case TYPE_BLADEFIST:
            m_auiEncounter[uiType] = uiData;
            if (uiData == DONE)
            {
                // Make executioner attackable only after the final boss is dead
                if (Creature* pExecutioner = GetSingleCreatureFromStorage(NPC_EXECUTIONER, true))
                    pExecutioner->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);
            }
            break;
        case TYPE_EXECUTION:
            m_auiEncounter[uiType] = uiData;
            if (uiData == IN_PROGRESS && !GetSingleCreatureFromStorage(NPC_EXECUTIONER, true))
            {
                if (Player* pPlayer = GetPlayerInMap())
                {
                    // summon the 3 npcs for execution
                    for (uint8 i = 2; i < 5; ++i)
                        pPlayer->SummonCreature(m_uiTeam == ALLIANCE ? aSoldiersLocs[i].m_uiAllianceEntry : aSoldiersLocs[i].m_uiHordeEntry, aSoldiersLocs[i].m_fX, aSoldiersLocs[i].m_fY, aSoldiersLocs[i].m_fZ, aSoldiersLocs[i].m_fO, TEMPSPAWN_DEAD_DESPAWN, 0);

                    // Summon the executioner; Note: according to wowhead he shouldn't be targetable until Kargath encounter is finished
                    if (Creature* pExecutioner = pPlayer->SummonCreature(NPC_EXECUTIONER, afExecutionerLoc[0], afExecutionerLoc[1], afExecutionerLoc[2], afExecutionerLoc[3], TEMPSPAWN_DEAD_DESPAWN, 0, true))
                        pExecutioner->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_NON_ATTACKABLE);

                    // cast the execution spell
                    DoCastGroupDebuff(SPELL_KARGATH_EXECUTIONER_1);
                }
            }
            if (uiData == DONE)
            {
                // If the officer is already killed, then skip the quest completion
                if (m_uiExecutionStage)
                    break;

                // Complete quest 9524 or 9525
                if (Creature* pOfficer = GetSingleCreatureFromStorage(m_uiTeam == ALLIANCE ? NPC_OFFICER_ALLIANCE : NPC_OFFICER_HORDE))
                {
                    Map::PlayerList const& lPlayers = instance->GetPlayers();

                    for (const auto& lPlayer : lPlayers)
                    {
                        if (Player* pPlayer = lPlayer.getSource())
                            pPlayer->KilledMonsterCredit(pOfficer->GetEntry(), pOfficer->GetObjectGuid());
                    }
                }
            }
            break;
        case TYPE_GAUNTLET:
            switch (uiData)
            {
                case FAIL: // Called on wipe/players left/Boss Evade
                    FailGauntlet(instance->GetCreature(m_guidGauntletNPC));
                    break;
                case DONE:  // Called on boss kill
                    EndGauntlet(instance->GetCreature(m_guidGauntletNPC));
                    break;
                case SPECIAL: // Called on Boss Aggro
                    StopGauntlet(instance->GetCreature(m_guidGauntletNPC));
                    break;
                default:
                    break;
            }

            m_auiEncounter[uiType] = uiData;
            break;

    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;

        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3];
        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

void instance_shattered_halls::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3];

    for (uint32& i : m_auiEncounter)
    {
        if (i == IN_PROGRESS)
            i = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

uint32 instance_shattered_halls::GetData(uint32 uiType) const
{
    if (uiType < MAX_ENCOUNTER)
        return m_auiEncounter[uiType];

    return 0;
}

void instance_shattered_halls::OnCreatureDeath(Creature* pCreature)
{
    if (pCreature->GetEntry() == NPC_EXECUTIONER)
        SetData(TYPE_EXECUTION, DONE);
}

void instance_shattered_halls::OnCreatureEnterCombat(Creature* pCreature)
{
    // Set data to special in order to pause the event timer
    // This is according to the blizz comments which say that it is possible to complete the event if you engage the npc while you have only a few seconds left
    if (pCreature->GetEntry() == NPC_EXECUTIONER)
        SetData(TYPE_EXECUTION, SPECIAL);
}

void instance_shattered_halls::OnCreatureEvade(Creature* pCreature)
{
    // If npc evades continue the counting
    if (pCreature->GetEntry() == NPC_EXECUTIONER)
        SetData(TYPE_EXECUTION, IN_PROGRESS);
}

bool instance_shattered_halls::CheckConditionCriteriaMeet(Player const* pPlayer, uint32 uiInstanceConditionId, WorldObject const* pConditionSource, uint32 conditionSourceType) const
{
    switch (uiInstanceConditionId)
    {
        case INSTANCE_CONDITION_ID_NORMAL_MODE:             // No soldier alive
        case INSTANCE_CONDITION_ID_HARD_MODE:               // One soldier alive
        case INSTANCE_CONDITION_ID_HARD_MODE_2:             // Two soldier alive
        case INSTANCE_CONDITION_ID_HARD_MODE_3:             // Three soldier alive
            return uiInstanceConditionId == uint32(m_uiPrisonersLeft);
    }

    script_error_log("instance_shattered_halls::CheckConditionCriteriaMeet called with unsupported Id %u. Called with param plr %s, src %s, condition source type %u",
                     uiInstanceConditionId, pPlayer ? pPlayer->GetGuidStr().c_str() : "nullptr", pConditionSource ? pConditionSource->GetGuidStr().c_str() : "nullptr", conditionSourceType);
    return false;
}

void instance_shattered_halls::Update(uint32 uiDiff)
{
    if (m_auiEncounter[TYPE_GAUNTLET] == IN_PROGRESS)
    {
        Creature* gauntlet = instance->GetCreature(m_guidGauntletNPC);
        if (!gauntlet || !GetPlayerInMap(true))
        {
            SetData(TYPE_GAUNTLET, FAIL);
        }
        else
        {
            for (auto& blaze : m_vBlazeTimers)
            {
                if (blaze.second <= uiDiff)
                {
                    blaze.second = 2000;
                    if (GameObject* blazeGo = instance->GetGameObject(blaze.first))
                        gauntlet->CastSpell(nullptr, SPELL_FLAMES, TRIGGERED_NONE, nullptr, nullptr, blazeGo->GetObjectGuid());
                }
                else
                    blaze.second -= uiDiff;
            }
        }
    }

    if (m_auiEncounter[TYPE_EXECUTION] != IN_PROGRESS)
        return;

    if (m_uiExecutionTimer < uiDiff)
    {
        switch (m_uiExecutionStage)
        {
            case 0:
                // Kill the officer
                if (Creature* pSoldier = GetSingleCreatureFromStorage(m_uiTeam == ALLIANCE ? NPC_OFFICER_ALLIANCE : NPC_OFFICER_HORDE))
                    pSoldier->DealDamage(pSoldier, pSoldier->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                // Make Kargath yell
                DoOrSimulateScriptTextForThisInstance(m_uiTeam == ALLIANCE ? SAY_KARGATH_EXECUTE_ALLY : SAY_KARGATH_EXECUTE_HORDE, NPC_KARGATH_BLADEFIST);

                // Set timer for the next execution
                DoCastGroupDebuff(SPELL_KARGATH_EXECUTIONER_2);
                m_uiExecutionTimer = 10 * MINUTE * IN_MILLISECONDS;
                break;
            case 1:
                if (Creature* pSoldier = GetSingleCreatureFromStorage(m_uiTeam == ALLIANCE ? NPC_SOLDIER_ALLIANCE_2 : NPC_SOLDIER_HORDE_2))
                    pSoldier->DealDamage(pSoldier, pSoldier->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                DoCastGroupDebuff(SPELL_KARGATH_EXECUTIONER_3);
                m_uiExecutionTimer = 15 * MINUTE * IN_MILLISECONDS;
                break;
            case 2:
                if (Creature* pSoldier = GetSingleCreatureFromStorage(m_uiTeam == ALLIANCE ? NPC_SOLDIER_ALLIANCE_3 : NPC_SOLDIER_HORDE_3))
                    pSoldier->DealDamage(pSoldier, pSoldier->GetHealth(), nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);

                SetData(TYPE_EXECUTION, FAIL);
                m_uiExecutionTimer = 0;
                break;
        }
        --m_uiPrisonersLeft;
        ++m_uiExecutionStage;
    }
    else
        m_uiExecutionTimer -= uiDiff;
}

void instance_shattered_halls::FailGauntlet(Creature* gauntlet)
{
    // If success despawn all, else respawn permanents
    for (ObjectGuid& guid : m_vGauntletPermanentGuids)
        if (Creature* creature = instance->GetCreature(guid))
            creature->Respawn();

    for (ObjectGuid& guid : m_vGauntletTemporaryGuids)
        if (Creature* creature = instance->GetCreature(guid))
            creature->ForcedDespawn();

    for (ObjectGuid& guid : m_vGauntletBossGuids)
        if (Creature* boss = instance->GetCreature(guid))
            boss->Respawn();

    for (auto& blaze : m_vBlazeTimers) // despawn blaze GOs from flame arrows
        if (GameObject* go = instance->GetGameObject(blaze.first))
            go->AddObjectToRemoveList();

    EndGauntlet(gauntlet);
}

void instance_shattered_halls::StopGauntlet(Creature* gauntlet)
{
    if (gauntlet)
        gauntlet->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, gauntlet, gauntlet);
}

void instance_shattered_halls::EndGauntlet(Creature* gauntlet)
{
    if (gauntlet)
        gauntlet->ForcedDespawn();

    m_vGauntletTemporaryGuids.clear();
}

// Add debuff to all players in the instance
void instance_shattered_halls::DoCastGroupDebuff(uint32 uiSpellId)
{
    Map::PlayerList const& lPlayers = instance->GetPlayers();

    for (const auto& lPlayer : lPlayers)
    {
        Player* pPlayer = lPlayer.getSource();
        if (pPlayer && !pPlayer->HasAura(uiSpellId))
            pPlayer->CastSpell(pPlayer, uiSpellId, TRIGGERED_OLD_TRIGGERED);
    }
}

InstanceData* GetInstanceData_instance_shattered_halls(Map* pMap)
{
    return new instance_shattered_halls(pMap);
}

enum {
    NPC_SHATTERED_HAND_SCOUT  = 17693,
    NPC_SHATTERED_HAND_ZEALOT = 17462,
    NPC_SHATTERED_HAND_ARCHER = 17427,
    NPC_SHATTERED_HAND_BG	  = 17461, // Porung is the heroic entry for this npc
//	NPC_ARCHER_TARGET		  = 29097, // Might not need? 
    NPC_GUARD_PORUNG		  = 20923, // not needed

    SCOUT_AGRO_YELL		   = -1540051,
    PORUNG_FORM_RANKS_YELL = -1540052,
    PORUNG_READY_YELL	   = -1540053,
    PORUNG_AIM_YELL		   = -1540054,
    PORUNG_FIRE_YELL	   = -1540055,

    DELAY_350_MILLI		= 350,
    PORUNG_YELL_DELAY_1 = 4000,
    PORUNG_YELL_DELAY_2 = 1200,
    WAVE_TIMER			= 20000,
    ARCHER_SHOOT_DELAY  = 15000,

    SHOOT_FLAME_ARROW	= 30952
};

static float gauntletSpawnCoords[1][3] = 
{
    {409.848f, 315.385f, 1.921f}
};

static float scoutCoords[1][3] =
{
    {494.015f, 316.213f, 1.945f}
};

static float zealotSpawnCoords[3][3] =
{
    {519.107f, 273.546f, 1.916f}, // (waves)
    {504.649f, 302.811f, 1.940f}, // L (first 8 zealots)
    {506.683f, 329.961f, 2.069f}  // R (first 8 zealots)
};

static float zealotWaypoints[4][3] =
{
    {518.681f, 291.375f, 1.923f}, // 1
    {504.559f, 315.952f, 1.942f}, // 2
    {482.445f, 315.779f, 1.939f}, // 3
    {352.104f, 315.725f, 3.139f}, // 4
};

static float firstWaveWaypoints[2][3] =
{
    {495.646f, 313.251f, 1.945f},
    {497.516f, 319.176f, 1.945f}
};

static float zealotDestinations[8][3] =
{
    // First Row:
    {362.577f, 311.449f, 1.918f}, // L
    {362.592f, 320.969f, 1.918f}, // R
    // Second Row:		  	 
    {384.897f, 311.348f, 1.946f}, // L
    {384.212f, 321.826f, 1.946f}, // R
    // Third Row:		  	 
    {422.212f, 310.864f, 1.946f}, // L
    {419.034f, 319.279f, 1.940f}, // R
    // Fourth Row:		  	 
    {463.375f, 310.195f, 1.935f}, // L
    {458.814f, 321.833f, 1.946f}  // R
};

/*
Scout will run to the end of the hall and summon the gauntlet npc. 
That npc will spawn have the scripting for the event. I Initially thought to just put 
everything on the scout and have the scout go invisible after he runs down but that 
puts the player in combat permanently and they should be able to get out of combat during 
breaks.
*/

// Gauntlet of Fire scripting
struct npc_Gauntlet_of_Fire : public ScriptedAI
{
    npc_Gauntlet_of_Fire(Creature* pCreature) : ScriptedAI(pCreature)	
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_gauntletStopped = false;
        SetReactState(REACT_PASSIVE);
        Reset(); 
    }

    bool m_bInitialWavesSpawned; // done spawning waves?
    bool m_bPorungDoneYelling;	 // done yelling?
    bool m_bZealotOneOrTwo;		 // delay is different whether spawning first or second zealot in wave
    bool m_gauntletStopped;

    Creature* m_porung;				   // normal or heroic this is him
    std::list<Creature*> m_lSHArchers; // the two archers
    ScriptedInstance* m_pInstance;	   // to set gauntlet in progress/not

    uint8 m_uiNumInitialWaves;			 // counter for initial waves spawning
    uint8 m_uiPorungYellNumber;			 // keeps track of porung as he yells
    uint32 m_uiInitialWaves_Delay;		 // time between initial waves spawn
    uint32 m_uiWaveTimer;				 // timer for periodic wave spawns
    uint32 m_uiPorungYellDelay;			 // delay between READY, AIM, FIRE
    uint32 m_uiShootFlamingArrowTimer_1; // timer for fire arrow ability (left archer)
    uint32 m_uiShootFlamingArrowTimer_2; // (right archer)
    
    void Reset() override
    {
        m_uiNumInitialWaves    = 0;
        m_uiPorungYellNumber   = 0;
        m_uiInitialWaves_Delay = 0;
        m_uiWaveTimer          = WAVE_TIMER / 2; // let the first wave spawn faster than concurrent ones
        m_uiPorungYellDelay    = 0;
        m_uiShootFlamingArrowTimer_1 = ARCHER_SHOOT_DELAY;
        m_uiShootFlamingArrowTimer_2 = ARCHER_SHOOT_DELAY;
        m_bInitialWavesSpawned = false;
        m_bPorungDoneYelling   = false;
        m_bZealotOneOrTwo      = false;
        m_porung               = nullptr;
        m_lSHArchers.clear();
    }

    void DoInitialGets()
    {
        m_porung = GetClosestCreatureWithEntry(m_creature, m_creature->GetMap()->IsRegularDifficulty() ? NPC_SHATTERED_HAND_BG : NPC_GUARD_PORUNG, 150.0f);
        GetCreatureListWithEntryInGrid(m_lSHArchers, m_creature, NPC_SHATTERED_HAND_ARCHER, 150.0f);
    }

    void DoSummonInitialWave()
    {
        if (Creature* pAdd = m_creature->SummonCreature(NPC_SHATTERED_HAND_ZEALOT, zealotSpawnCoords[1][0], zealotSpawnCoords[1][1], zealotSpawnCoords[1][2], 0.0f, TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 150000, true, true))
        {
            pAdd->GetMotionMaster()->MovePoint(100 + m_uiNumInitialWaves, firstWaveWaypoints[0][0], firstWaveWaypoints[0][1], firstWaveWaypoints[0][2]);
        }
        if (Creature* pAdd = m_creature->SummonCreature(NPC_SHATTERED_HAND_ZEALOT, zealotSpawnCoords[2][0], zealotSpawnCoords[2][1], zealotSpawnCoords[2][2], 0.0f, TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 150000, true, true))
        {
            pAdd->GetMotionMaster()->MovePoint(200 + m_uiNumInitialWaves, firstWaveWaypoints[1][0], firstWaveWaypoints[1][1], firstWaveWaypoints[1][2]);
        }
    }

    void DoSummonSHZealot()
    {
        if (Creature* pAdd = m_creature->SummonCreature(NPC_SHATTERED_HAND_ZEALOT, zealotSpawnCoords[0][0], zealotSpawnCoords[0][1], zealotSpawnCoords[0][2], 0.0f, TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 150000, true, true))
        {
            pAdd->GetMotionMaster()->MovePoint(0, zealotWaypoints[0][0], zealotWaypoints[0][1], zealotWaypoints[0][2]);
        }
    }

    void DoBeginArcherAttack(bool leftOrRight)
    {
        // Arrow boundaries:
        //				 x		 y		z
        // Top Left:  481.519 323.895 1.945
        // Top Right: 480.630 308.647 1.942
        // Bot Left:  362.607 323.948 1.918
        // Bot Right: 360.884 308.777 1.918
        // This should probably also try to only shoot arrows that will land within
        // some range of the players (videos from back when seem to show that behavior)
        // but I'm not sure how best to implement that and this works fine for now

        std::list<Creature*>::iterator itr;
        if (leftOrRight) // left one shoot
            itr = m_lSHArchers.begin();
        else // right one shoot
        {
            itr = m_lSHArchers.begin();
            itr++;
        }

        if ((*itr))
        {
            float xCoord = frand(361.7455f, 481.0745f);
            float yCoord = frand(308.7120f, 323.9215f);
            float zCoord = 1.93075f;

            //Creature* pAdd = nullptr;
            //if (pAdd = m_creature->SummonCreature(NPC_ARCHER_TARGET, xCoord, yCoord, zCoord, 0.0f, TEMPSUMMON_TIMED_OOC_OR_DEAD_DESPAWN, 20000))
            //{
                //(*itr)->CastSpell(pAdd, SHOOT_FLAME_ARROW, true);
            (*itr)->CastSpell(xCoord, yCoord, zCoord, SHOOT_FLAME_ARROW, TRIGGERED_NONE);
            //}
        }
    }

    void JustSummoned(Creature* pSummoned) override
    {
        if (pSummoned->GetEntry() == NPC_SHATTERED_HAND_ZEALOT)
        {
            pSummoned->HandleEmoteState(EMOTE_STATE_READY1H);
        }
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiData) override
    {
        if (pSummoned->GetEntry() == NPC_SHATTERED_HAND_ZEALOT && uiMotionType == POINT_MOTION_TYPE) // sanity check
        {
            switch (uiData)
            {
                // Below are for the waves
                case 0: 
                    pSummoned->GetMotionMaster()->MovePoint(1, zealotWaypoints[1][0], zealotWaypoints[1][1], zealotWaypoints[1][2]);
                    break;
                case 1:
                    pSummoned->GetMotionMaster()->MovePoint(2, zealotWaypoints[2][0], zealotWaypoints[2][1], zealotWaypoints[2][2]);
                    break;
                case 2:
                    pSummoned->GetMotionMaster()->MovePoint(3, zealotWaypoints[3][0], zealotWaypoints[3][1], zealotWaypoints[3][2]);
                    break;
                // Rest are the initial spawns
                // Left
                case 100:
                    pSummoned->GetMotionMaster()->MovePoint(98, zealotDestinations[0][0], zealotDestinations[0][1], zealotDestinations[0][2]);
                    break;
                case 101:
                    pSummoned->GetMotionMaster()->MovePoint(98, zealotDestinations[2][0], zealotDestinations[2][1], zealotDestinations[2][2]);
                    break;
                case 102:
                    pSummoned->GetMotionMaster()->MovePoint(98, zealotDestinations[4][0], zealotDestinations[4][1], zealotDestinations[4][2]);
                    break;
                case 103:
                    pSummoned->GetMotionMaster()->MovePoint(98, zealotDestinations[6][0], zealotDestinations[6][1], zealotDestinations[6][2]);
                    break;
                // Right
                case 200:
                    pSummoned->GetMotionMaster()->MovePoint(99, zealotDestinations[1][0], zealotDestinations[1][1], zealotDestinations[1][2]);
                    break;
                case 201:
                    pSummoned->GetMotionMaster()->MovePoint(99, zealotDestinations[3][0], zealotDestinations[3][1], zealotDestinations[3][2]);
                    break;
                case 202:
                    pSummoned->GetMotionMaster()->MovePoint(99, zealotDestinations[5][0], zealotDestinations[5][1], zealotDestinations[5][2]);
                    break;
                case 203:
                    pSummoned->GetMotionMaster()->MovePoint(99, zealotDestinations[7][0], zealotDestinations[7][1], zealotDestinations[7][2]);
                    break;
                case 98: // turn so not facing at an awkward angle
                    pSummoned->SetFacingTo(2.8f);
                    pSummoned->GetMotionMaster()->MoveIdle();
                    break;
                case 99:
                    pSummoned->SetFacingTo(-2.8f);
                    pSummoned->GetMotionMaster()->MoveIdle();
                    break;
                default:
                    pSummoned->GetMotionMaster()->MoveIdle();
                    break;
            }
        }        
    }

    void ReceiveAIEvent(AIEventType eventType, Unit* /*pSender*/, Unit* /*pInvoker*/, uint32 /*uiMiscValue*/) override
    {
        if (eventType == AI_EVENT_CUSTOM_A)
            m_gauntletStopped = true;
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_gauntletStopped)
            return;

        if (m_bInitialWavesSpawned)
        {
            if (m_bPorungDoneYelling)
            {
                if (m_uiWaveTimer < uiDiff) // Periodic waves
                {
                    if (m_bZealotOneOrTwo) // second zealot, long delay
                    {
                        DoSummonSHZealot();
                        m_uiWaveTimer = WAVE_TIMER;
                        m_bZealotOneOrTwo = false;
                    }
                    else // first zealot, short delay
                    {
                        DoSummonSHZealot();
                        m_uiWaveTimer = DELAY_350_MILLI;
                        m_bZealotOneOrTwo = true;
                    }
                }
                else
                    m_uiWaveTimer -= uiDiff;

                if (m_uiShootFlamingArrowTimer_1 < uiDiff) // Left Archer
                {
                    DoBeginArcherAttack(true);
                    m_uiShootFlamingArrowTimer_1 = ARCHER_SHOOT_DELAY + urand(0, 2000);
                }
                else
                    m_uiShootFlamingArrowTimer_1 -= uiDiff;

                if (m_uiShootFlamingArrowTimer_2 < uiDiff) // Right Archer
                {
                    DoBeginArcherAttack(false);
                    m_uiShootFlamingArrowTimer_2 = ARCHER_SHOOT_DELAY + urand(0, 2000);
                }
                else
                    m_uiShootFlamingArrowTimer_2 -= uiDiff;
            }
            else // Not done yelling
            {
                if (m_uiPorungYellDelay < uiDiff)
                {
                    switch (m_uiPorungYellNumber)
                    {
                        case 0:
                            DoScriptText(PORUNG_FORM_RANKS_YELL, m_porung);
                            m_uiPorungYellDelay = PORUNG_YELL_DELAY_1;
                            m_uiPorungYellNumber += 1;
                            break;
                        case 1:
                            DoScriptText(PORUNG_READY_YELL, m_porung);
                            DoBeginArcherAttack(true);
                            DoBeginArcherAttack(false);
                            m_uiPorungYellDelay = PORUNG_YELL_DELAY_2;
                            m_uiPorungYellNumber += 1;
                            break;
                        case 2:
                            DoScriptText(PORUNG_AIM_YELL, m_porung);
                            m_uiPorungYellDelay = PORUNG_YELL_DELAY_2;
                            m_uiPorungYellNumber += 1;
                            break;
                        case 3:
                            DoScriptText(PORUNG_FIRE_YELL, m_porung);
                            m_bPorungDoneYelling = true;
                            break;
                    }
                }
                else
                    m_uiPorungYellDelay -= uiDiff;
            }
        }
        else // not done spawning first waves
        {
            if (m_uiInitialWaves_Delay < uiDiff)
            {
                switch (m_uiNumInitialWaves)
                {
                    case 0:
                    case 1:
                    case 2:
                        DoSummonInitialWave();
                        m_uiNumInitialWaves++;
                        m_uiInitialWaves_Delay = DELAY_350_MILLI;
                        break;
                    case 3:
                        DoSummonInitialWave();
                        m_bInitialWavesSpawned = true;
                        break;
                }
            }
            else
                m_uiInitialWaves_Delay -= uiDiff;
        }
    }
};

UnitAI* GetAI_npc_Gauntlet_of_Fire(Creature* pCreature)
{
    return new npc_Gauntlet_of_Fire(pCreature);
}

// Scout scripting
struct npc_Shattered_Hand_Scout : public ScriptedAI
{
    npc_Shattered_Hand_Scout(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    bool m_bRunning;

    void Reset() override
    {
        m_bRunning = false;
    }

    void Aggro(Unit* pWho) override {}

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (pWho->GetTypeId() == TYPEID_PLAYER && pWho->GetDistance(m_creature) <= 40.f)
            if (!m_bRunning)
                DoStartRunning();
    }

    void DoStartRunning()
    {
        m_bRunning = true;
        m_creature->SetWalk(false);
        m_creature->AI()->SetCombatMovement(false);
        m_creature->GetMotionMaster()->MovePoint(0, scoutCoords[0][0], scoutCoords[0][1], scoutCoords[0][2]);
        DoScriptText(SCOUT_AGRO_YELL, m_creature);
    }

    void DoZealotsEmoteReady()
    {
        std::list<Creature*> zealots;
        GetCreatureListWithEntryInGrid(zealots, m_creature, NPC_SHATTERED_HAND_ZEALOT, 20.0f);

        for (std::list<Creature*>::iterator itr = zealots.begin(); itr != zealots.end(); ++itr)
        {
            (*itr)->HandleEmoteState(EMOTE_STATE_READY1H);
        }
    }

    void MovementInform(uint32 uiMovementType, uint32 uiData) override
    {
        if (uiMovementType == POINT_MOTION_TYPE && m_creature->isAlive())
        {
            switch (uiData)
            {
                case 0:
                    DoZealotsEmoteReady();

                    if (Creature* gauntlet = m_creature->SummonCreature(NPC_GAUNTLET_OF_FIRE, gauntletSpawnCoords[0][0], gauntletSpawnCoords[0][1], gauntletSpawnCoords[0][2], 0.0f, TEMPSPAWN_TIMED_OOC_OR_CORPSE_DESPAWN, 600000))
                    {
                        if (npc_Gauntlet_of_Fire* pGauntletAI = dynamic_cast<npc_Gauntlet_of_Fire*>(gauntlet->AI()))
                        {
                            pGauntletAI->DoInitialGets();
                            m_creature->GetMap()->GetInstanceData()->SetData(TYPE_GAUNTLET, IN_PROGRESS);
                        }
                    }

                    m_creature->ForcedDespawn();
                    break;
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        return;
    }
};

UnitAI* GetAI_npc_Shattered_Hand_Scout(Creature* pCreature)
{
    return new npc_Shattered_Hand_Scout(pCreature);
}


bool AreaTrigger_at_shattered_halls(Player* pPlayer, AreaTriggerEntry const* /*pAt*/)
{
    if (pPlayer->isGameMaster() || !pPlayer->isAlive())
        return false;

    instance_shattered_halls* pInstance = (instance_shattered_halls*)pPlayer->GetInstanceData();

    if (!pInstance)
        return false;

    // Only on heroic
    if (pInstance->instance->IsRegularDifficulty())
        return false;

    // Don't allow players to cheat
    if (pInstance->GetData(TYPE_BLADEFIST) == DONE || pInstance->GetData(TYPE_OMROGG) == DONE)
        return false;

    if (pInstance->GetData(TYPE_EXECUTION) == NOT_STARTED)
        pInstance->SetData(TYPE_EXECUTION, IN_PROGRESS);

    return true;
}

void AddSC_instance_shattered_halls()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_shattered_halls";
    pNewScript->GetInstanceData = &GetInstanceData_instance_shattered_halls;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_shattered_halls";
    pNewScript->pAreaTrigger = &AreaTrigger_at_shattered_halls;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_gauntlet_of_fire";
    pNewScript->GetAI = &GetAI_npc_Gauntlet_of_Fire;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_shattered_hand_scout";
    pNewScript->GetAI = &GetAI_npc_Shattered_Hand_Scout;
    pNewScript->RegisterSelf();

}

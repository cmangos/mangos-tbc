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
SDName: Instance_Shadowfang_Keep
SD%Complete: 100
SDComment:
SDCategory: Shadowfang Keep
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "AI/ScriptDevAI/include/sc_instance.h"
#include "Entities/Creature.h"
#include "Entities/Unit.h"
#include "Globals/ObjectMgr.h"
#include "Globals/SharedDefines.h"
#include "shadowfang_keep.h"

static const DialogueEntry aArugalDialogue[] =
{
    {NPC_VINCENT,                      0,   2000},
    {VINCENT_DEATH,          NPC_VINCENT,   8000},
    {ARUGAL_VISIBLE,          NPC_ARUGAL,    500},
    {ARUGAL_TELEPORT_IN,      NPC_ARUGAL,   2000},
    {SAY_ARUGAL_INTRO_1,      NPC_ARUGAL,   1750},
    {ARUGAL_EMOTE_POINT,      NPC_ARUGAL,   1750},
    {SAY_ARUGAL_INTRO_2,      NPC_ARUGAL,   1750},
    {ARUGAL_EMOTE_EXCLAMATION,NPC_ARUGAL,   1750},
    {SAY_ARUGAL_INTRO_3,      NPC_ARUGAL,   1750},
    {ARUGAL_EMOTE_LAUGH,      NPC_ARUGAL,   1750},
    {SAY_ARUGAL_INTRO_4,      NPC_ARUGAL,   2000},
    {ARUGAL_TELEPORT_OUT,     NPC_ARUGAL,    500},
    {ARUGAL_INTRO_DONE,       NPC_ARUGAL,      0},
    {NPC_ARCHMAGE_ARUGAL,              0,    100},
    {YELL_FENRUS,    NPC_ARCHMAGE_ARUGAL,   2000},
    {ARCHMAGE_FIRE,  NPC_ARCHMAGE_ARUGAL,   5000},
    {ARCHMAGE_LIGHTNING, NPC_ARCHMAGE_ARUGAL, 5000},
    {ARCHMAGE_INVIS, NPC_ARCHMAGE_ARUGAL,    500},
    {ARCHMAGE_VOIDWALKERS, NPC_ARCHMAGE_ARUGAL, 0},
    {0, 0, 0},
};

instance_shadowfang_keep::instance_shadowfang_keep(Map* pMap) : ScriptedInstance(pMap), DialogueHelper(aArugalDialogue)
{
    Initialize();
}

void instance_shadowfang_keep::Initialize()
{
    memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
    InitializeDialogueHelper(this);
}

void instance_shadowfang_keep::OnCreatureCreate(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_ASH:
        case NPC_ADA:
        case NPC_FENRUS:
        case NPC_MASTER_NANDOS:
            break;
        case NPC_VINCENT:
            // If Arugal has done the intro, make Vincent dead!
            if (m_auiEncounter[4] == DONE)
                pCreature->SetStandState(UNIT_STAND_STATE_DEAD);
            else
                StartNextDialogueText(NPC_VINCENT);
            break;
        case NPC_LUPINE_HORROR:
        case NPC_WOLFGUARD_WORG:
        case NPC_BLEAK_WORG:
        case NPC_SLAVERING_WORG:
            // Only store the wolves/worgs that are static spawn on the top level of the instance
            if (pCreature->GetPositionZ() > nandosMovement.fZ && !pCreature->IsTemporarySummon())
                m_lNandosWolvesGuids.push_back(pCreature->GetObjectGuid());
            break;
        case NPC_ARUGAL:
            pCreature->SetVisibility(VISIBILITY_OFF);
            break;
        case NPC_ARCHMAGE_ARUGAL:
            m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
            break;
        default:
            return;
    }
    m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
}

void instance_shadowfang_keep::OnCreatureDeath(Creature* pCreature)
{
    switch (pCreature->GetEntry())
    {
        case NPC_LUPINE_HORROR:
        case NPC_WOLFGUARD_WORG:
        case NPC_BLEAK_WORG:
        case NPC_SLAVERING_WORG:
            if (m_lNandosWolvesGuids.empty())
                return;

            m_lNandosWolvesGuids.remove(pCreature->GetObjectGuid());
            // If all wolves are dead, make Wolf Master Nandos engage in combat
            if (m_lNandosWolvesGuids.empty())
            {
                if (Creature* nandos = GetSingleCreatureFromStorage(NPC_MASTER_NANDOS))
                {
                    if (nandos->IsInCombat())   // Wolf Master Nandos already joined the fight: no need to go further
                        return;
                    DoScriptText(YELL_PACK_DEAD, nandos);
                    nandos->SetWalk(false);
                    nandos->GetMotionMaster()->MovePoint(0, nandosMovement.fX, nandosMovement.fY, nandosMovement.fZ);
                }
            }
            break;
        default:
            return;
    }
}

void instance_shadowfang_keep::OnObjectCreate(GameObject* pGo)
{
    switch (pGo->GetEntry())
    {
        case GO_COURTYARD_DOOR:
            if (m_auiEncounter[0] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        // For this we ignore voidwalkers, because if the server restarts
        // They won't be there, but Fenrus is dead so the door can't be opened!
        case GO_SORCERER_DOOR:
            if (m_auiEncounter[2] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ARUGAL_DOOR:
            if (m_auiEncounter[3] == DONE)
                pGo->SetGoState(GO_STATE_ACTIVE);
            break;
        case GO_ARUGAL_FOCUS:
            break;

        default:
            return;
    }
    m_goEntryGuidStore[pGo->GetEntry()] = pGo->GetObjectGuid();
}

void instance_shadowfang_keep::DoSpeech()
{
    Creature* pAda = GetSingleCreatureFromStorage(NPC_ADA);
    Creature* pAsh = GetSingleCreatureFromStorage(NPC_ASH);

    if (pAda && pAda->IsAlive() && pAsh && pAsh->IsAlive())
    {
        DoScriptText(SAY_BOSS_DIE_AD, pAda);
        DoScriptText(SAY_BOSS_DIE_AS, pAsh);
    }
}

void instance_shadowfang_keep::SetData(uint32 uiType, uint32 uiData)
{
    switch (uiType)
    {
        case TYPE_FREE_NPC:
            if (uiData == DONE)
                DoUseDoorOrButton(GO_COURTYARD_DOOR);
            m_auiEncounter[0] = uiData;
            break;
        case TYPE_RETHILGORE:
            if (uiData == DONE)
                DoSpeech();
            m_auiEncounter[1] = uiData;
            break;
        case TYPE_FENRUS:
            if (uiData == DONE)
            {
                if (Creature* pFenrus = GetSingleCreatureFromStorage(NPC_FENRUS))
                    pFenrus->SummonCreature(NPC_ARCHMAGE_ARUGAL, -136.89f, 2169.17f, 136.58f, 2.794f, TEMPSPAWN_TIMED_DESPAWN, 30000);
                StartNextDialogueText(NPC_ARCHMAGE_ARUGAL);
            }
            m_auiEncounter[2] = uiData;
            break;
        case TYPE_NANDOS:
            if (uiData == DONE)
                DoUseDoorOrButton(GO_ARUGAL_DOOR);
            m_auiEncounter[3] = uiData;
            break;
        case TYPE_INTRO:
            m_auiEncounter[4] = uiData;
            break;
        case TYPE_VOIDWALKER:
            if (uiData == DONE)
            {
                m_auiEncounter[5]++;
                if (m_auiEncounter[5] > 3)
                    DoUseDoorOrButton(GO_SORCERER_DOOR);
            }
            break;
    }

    if (uiData == DONE)
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " " << m_auiEncounter[3]
                   << " " << m_auiEncounter[4] << " " << m_auiEncounter[5];

        m_strInstData = saveStream.str();

        SaveToDB();
        OUT_SAVE_INST_DATA_COMPLETE;
    }
}

uint32 instance_shadowfang_keep::GetData(uint32 uiType) const
{
    switch (uiType)
    {
        case TYPE_FREE_NPC:   return m_auiEncounter[0];
        case TYPE_RETHILGORE: return m_auiEncounter[1];
        case TYPE_FENRUS:     return m_auiEncounter[2];
        case TYPE_NANDOS:     return m_auiEncounter[3];
        case TYPE_INTRO:      return m_auiEncounter[4];

        default:
            return 0;
    }
}

void instance_shadowfang_keep::Load(const char* chrIn)
{
    if (!chrIn)
    {
        OUT_LOAD_INST_DATA_FAIL;
        return;
    }

    OUT_LOAD_INST_DATA(chrIn);

    std::istringstream loadStream(chrIn);
    loadStream >> m_auiEncounter[0] >> m_auiEncounter[1] >> m_auiEncounter[2] >> m_auiEncounter[3]
               >> m_auiEncounter[4] >> m_auiEncounter[5];

    for (uint32& i : m_auiEncounter)
    {
        if (i == IN_PROGRESS)
            i = NOT_STARTED;
    }

    OUT_LOAD_INST_DATA_COMPLETE;
}

void instance_shadowfang_keep::JustDidDialogueStep(int32 iEntry)
{
    switch(iEntry)
    {
        case VINCENT_DEATH:
            if (Creature* pVincent = GetSingleCreatureFromStorage(NPC_VINCENT))
                pVincent->SetStandState(UNIT_STAND_STATE_DEAD);
            break;
        case ARUGAL_VISIBLE:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->SetVisibility(VISIBILITY_ON);
        }
            break;
        case ARUGAL_TELEPORT_IN:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->AI()->DoCastSpellIfCan(pCreature, SPELL_SPAWN);
        }
            break;
        case ARUGAL_EMOTE_POINT:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->HandleEmote(EMOTE_ONESHOT_POINT);
        }
            break;
        case ARUGAL_EMOTE_EXCLAMATION:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->HandleEmote(EMOTE_ONESHOT_EXCLAMATION);
        }
            break;
        case ARUGAL_EMOTE_LAUGH:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->HandleEmote(EMOTE_ONESHOT_LAUGH);
        }
            break;
        case ARUGAL_TELEPORT_OUT:
        if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
        {
            pCreature->AI()->DoCastSpellIfCan(pCreature, SPELL_SPAWN);
        }
            break;
        case ARUGAL_INTRO_DONE:
            SetData(TYPE_INTRO, DONE);
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARUGAL))
            {
                pCreature->SetVisibility(VISIBILITY_OFF);
                pCreature->ForcedDespawn();
            }
            break;
        case YELL_FENRUS:
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARCHMAGE_ARUGAL))
            {
                pCreature->SetVisibility(VISIBILITY_ON);
            }
            break;
        case ARCHMAGE_FIRE:
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARCHMAGE_ARUGAL))
            {
                pCreature->AI()->DoCastSpellIfCan(pCreature, SPELL_FIRE);
            }
            break;
        case ARCHMAGE_LIGHTNING:
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARCHMAGE_ARUGAL))
            {
                if (GameObject* pLighting = GetSingleGameObjectFromStorage(GO_ARUGAL_FOCUS))
                {
                    pLighting->Use(pCreature);
                }
            }
            break;
        case ARCHMAGE_INVIS:
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARCHMAGE_ARUGAL))
            {
                pCreature->SetVisibility(VISIBILITY_OFF);
            }
            break;
        case ARCHMAGE_VOIDWALKERS:
            if (Creature* pCreature = GetSingleCreatureFromStorage(NPC_ARCHMAGE_ARUGAL))
            {
                ObjectGuid leaderGuid;

                for (uint8 i = 0; i < 4; ++i)
                {
                    // No suitable spell was found for this in DBC files, so summoning the hard way
                    if (Creature* voidwalker = pCreature->SummonCreature(NPC_VOIDWALKER, VWSpawns[i].fX, VWSpawns[i].fY, VWSpawns[i].fZ, VWSpawns[i].fO, TEMPSPAWN_DEAD_DESPAWN, 1))
                    {
                        // Set Voidwalker's home to the middle of the room to avoid evade in an unreachable place
                        voidwalker->SetRespawnCoord(voidwalkerHome.fX, voidwalkerHome.fY, voidwalkerHome.fZ, voidwalker->GetOrientation());

                        if (!i)
                        {
                            leaderGuid = voidwalker->GetObjectGuid();
                            if (mob_arugal_voidwalker_baseAI* voidwalkerAI = dynamic_cast<mob_arugal_voidwalker_baseAI*>(voidwalker->AI()))
                                voidwalkerAI->SetLeader();
                        }
                        else
                        {
                            if (mob_arugal_voidwalker_baseAI* voidwalkerAI = dynamic_cast<mob_arugal_voidwalker_baseAI*>(voidwalker->AI()))
                                voidwalkerAI->SetFollower(leaderGuid, i);
                        }
                    }
                }
            }
            break;
    }
}

void instance_shadowfang_keep::Update(uint32 uiDiff){
    DialogueUpdate(uiDiff);
}

InstanceData* GetInstanceData_instance_shadowfang_keep(Map* pMap)
{
    return new instance_shadowfang_keep(pMap);
}

void AddSC_instance_shadowfang_keep()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "instance_shadowfang_keep";
    pNewScript->GetInstanceData = &GetInstanceData_instance_shadowfang_keep;
    pNewScript->RegisterSelf();
}

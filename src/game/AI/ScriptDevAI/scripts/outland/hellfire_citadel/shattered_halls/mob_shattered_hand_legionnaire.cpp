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
#include "shattered_halls.h"

 /*######
 ## mob_shattered_hand_legionnair
 ######*/

enum
{
    SPELL_AURA_OF_DISCIPLIN = 30472,
    SPELL_PUMMEL = 15615,
    SPELL_ENRAGE = 30485,

    EMOTE_ENRAGE = -1540066,

    MOB_FEL_ORC = 17083
};

static float FelOrcSpawnCoords[][4] =    // Coords needed for spawns and waypoints
{
    { 0.0f, 0.0f, 0.0f, 0.0f,}, // first group no spawn
    { 81.417f, 113.488f, -13.223f, 3.127f }, // spawn 1
    { 86.376f, 187.03f, -13.236f, 3.127f}, // spawn 2
};

static float FelOrcMoveCoords[][4] =    // Coords needed for spawns and waypoints
{
    { 0.0f, 0.0f, 0.0f, 0.0f,}, // no spawn
    { 69.774910f, 46.661671f, -13.211f, 3.127f}, // Waypoint 1
    { 69.908f, 98.118f, -13.22f,  3.127f}, // waypoint 2
};

enum LegionnaireGUIDS
{
    FIRST_LEGIONNAIRE_GUID = 5400077,
    SECOND_LEGIONNAIRE_GUID = 5400075,
};

static const int32 aRandomReinf[] = { -1540056, -1540057, -1540058, -1540059, -1540060, -1540061, -1540062, 1540063, 1540064, 1540065 };

struct mob_shattered_hand_legionnaireAI : public ScriptedAI
{
    mob_shattered_hand_legionnaireAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = pCreature->GetMap()->IsRegularDifficulty();
        Reset();

        uint32 guid = m_creature->GetGUIDLow();

        if (guid == FIRST_LEGIONNAIRE_GUID)
            legionnaireGuid = 1;
        else if (guid == SECOND_LEGIONNAIRE_GUID)
            legionnaireGuid = 2;
        else
            legionnaireGuid = 0;
    }

    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;

    uint32 m_uiPummelTimmer;
    uint32 m_uiAuraTimer;
    uint32 m_uiMinionSpawnTimmer;
    uint32 legionnaireGuid;
    bool nearbyFriendDied;

    void Reset() override
    {
        m_uiPummelTimmer = urand(10000, 15000);
        m_uiAuraTimer = 15000;

        nearbyFriendDied = false;
        m_uiMinionSpawnTimmer = 0;
    }

    void ReceiveAIEvent(AIEventType eventType, Unit* pSender, Unit* pInvoker, uint32 /*miscValue*/) override
    {
        // Nearby creatue died
        if (eventType == AI_EVENT_CUSTOM_EVENTAI_B)
            nearbyFriendDied = true;
    }

    void SummonedMovementInform(Creature* pSummoned, uint32 uiMotionType, uint32 uiPointId) override
    {
        // When last waypoint reached, search for players.
        if (pSummoned->GetEntry() == MOB_FEL_ORC && uiPointId == 100)
        {
            m_creature->CastSpell(m_creature, SPELL_ENRAGE, TRIGGERED_NONE);
            pSummoned->GetMotionMaster()->MoveIdle();
            pSummoned->StopMoving();
            pSummoned->GetMotionMaster()->Clear(false, true);
            pSummoned->SetInCombatWithZone();
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0))
                pSummoned->AI()->AttackStart(pTarget);
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (nearbyFriendDied)
        {
            if (!m_creature->HasAura(SPELL_ENRAGE))
            {
                m_creature->CastSpell(m_creature, SPELL_ENRAGE, TRIGGERED_NONE);
                DoScriptText(EMOTE_ENRAGE, m_creature);
            }

            // Have to reasearch the cooldown for FelOrc spawn
            if (m_uiMinionSpawnTimmer < uiDiff)
            {                

                if (Creature* felorc = m_creature->SummonCreature(MOB_FEL_ORC, FelOrcSpawnCoords[legionnaireGuid][0], FelOrcSpawnCoords[legionnaireGuid][1], FelOrcSpawnCoords[legionnaireGuid][2], FelOrcSpawnCoords[legionnaireGuid][3], TEMPSPAWN_TIMED_OOC_OR_DEAD_DESPAWN, 100000, true, true))
                {
                    felorc->GetMotionMaster()->MovePoint(100, FelOrcMoveCoords[legionnaireGuid][0], FelOrcMoveCoords[legionnaireGuid][1], FelOrcMoveCoords[legionnaireGuid][2]);
                    felorc->SetRespawnCoord(FelOrcMoveCoords[legionnaireGuid][0], FelOrcMoveCoords[legionnaireGuid][1], FelOrcMoveCoords[legionnaireGuid][2], FelOrcMoveCoords[legionnaireGuid][3]);
                }
                DoScriptText(aRandomReinf[urand(0, 10)], m_creature);
                nearbyFriendDied = false;
                m_uiMinionSpawnTimmer = 5000;
            }
            else
                m_uiMinionSpawnTimmer -= uiDiff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if (m_uiPummelTimmer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, SPELL_PUMMEL, SELECT_FLAG_PLAYER_CASTING))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_PUMMEL) == CAST_OK)
                    m_uiPummelTimmer = urand(10000, 15000);
            }
        }
        else
            m_uiPummelTimmer -= uiDiff;

        if (m_uiAuraTimer < uiDiff)
        {
            m_creature->CastSpell(m_creature, SPELL_AURA_OF_DISCIPLIN, TRIGGERED_NONE);
            m_uiAuraTimer = 15000;
        }
        else
            m_uiAuraTimer -= uiDiff;

        if (m_creature->GetHealthPercent() <= 30.0f)
            m_creature->CastSpell(m_creature, SPELL_ENRAGE, TRIGGERED_NONE);

        DoMeleeAttackIfReady();
    }
};

UnitAI* GetAI_mob_shattered_hand_legionnaire(Creature* pCreature)
{
    return new mob_shattered_hand_legionnaireAI(pCreature);
}

void AddSC_mob_shattered_hand_legionnaire()
{
    Script* pNewScript = new Script;
    pNewScript = new Script;
    pNewScript->Name = "mob_shattered_hand_legionnaire";
    pNewScript->GetAI = &GetAI_mob_shattered_hand_legionnaire;
    pNewScript->RegisterSelf();
}
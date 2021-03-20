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
SDName: Shadowfang_Keep
SD%Complete: 75
SDComment: npc_shadowfang_prisoner using escortAI for movement to door.
SDCategory: Shadowfang Keep
EndScriptData */

/* ContentData
npc_shadowfang_prisoner
mob_arugal_voidwalker
npc_arugal
boss_arugal
npc_deathstalker_vincent
EndContentData */


#include "AI/ScriptDevAI/base/CombatAI.h"
#include "AI/ScriptDevAI/base/escort_ai.h"
#include "AI/ScriptDevAI/include/sc_common.h"
#include "AI/ScriptDevAI/include/sc_instance.h"
#include "shadowfang_keep.h"
#include "Spells/Scripts/SpellScript.h"

/*######
## npc_shadowfang_prisoner
######*/

enum
{
    SAY_FREE_AS             = -1033000,
    SAY_OPEN_DOOR_AS        = -1033001,
    SAY_POST_DOOR_AS        = -1033002,
    EMOTE_VANISH_AS         = -1033014,
    SAY_FREE_AD             = -1033003,
    SAY_OPEN_DOOR_AD        = -1033004,
    SAY_POST1_DOOR_AD       = -1033005,
    SAY_POST2_DOOR_AD       = -1033006,
    EMOTE_UNLOCK_DOOR_AD    = -1033015,

    SPELL_UNLOCK            = 6421,

    GOSSIP_ITEM_DOOR        = -3033000
};

struct npc_shadowfang_prisonerAI : public npc_escortAI
{
    npc_shadowfang_prisonerAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_uiNpcEntry = pCreature->GetEntry();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    uint32 m_uiNpcEntry;

    void WaypointReached(uint32 uiPoint) override
    {
        switch (uiPoint)
        {
            case 1:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_FREE_AS, m_creature);
                else
                    DoScriptText(SAY_FREE_AD, m_creature);
                break;
            case 11:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_OPEN_DOOR_AS, m_creature);
                else
                    DoScriptText(SAY_OPEN_DOOR_AD, m_creature);
                break;
            case 12:
                if (m_uiNpcEntry == NPC_ASH)
                    DoCastSpellIfCan(m_creature, SPELL_UNLOCK);
                else
                    DoScriptText(EMOTE_UNLOCK_DOOR_AD, m_creature);
                break;
//            case 12:
//                if (m_uiNpcEntry != NPC_ASH)
//                    m_creature->HandleEmote(EMOTE_ONESHOT_USESTANDING);
//                break;
            case 14:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(SAY_POST_DOOR_AS, m_creature);
                else
                    DoScriptText(SAY_POST1_DOOR_AD, m_creature);

                if (m_pInstance)
                    m_pInstance->SetData(TYPE_FREE_NPC, DONE);
                break;
            case 15:
                if (m_uiNpcEntry == NPC_ASH)
                    DoCastSpellIfCan(m_creature, SPELL_FIRE);
                else
                {
                    DoScriptText(SAY_POST2_DOOR_AD, m_creature);
                    SetRun();
                }
                break;
            case 16:
                if (m_uiNpcEntry == NPC_ASH)
                    DoScriptText(EMOTE_VANISH_AS, m_creature);
                break;
        }
    }

    void Reset() override {}

    // Let's prevent Adamant from charging into Ashcrombe's cell
    // And beating the crap out of him and vice versa XD
    void AttackStart(Unit* pWho) override
    {
        if (pWho)
        {
            if (pWho->GetEntry() == NPC_ASH || pWho->GetEntry() == NPC_ADA)
                return;
            ScriptedAI::AttackStart(pWho);
        }
    }
};

UnitAI* GetAI_npc_shadowfang_prisoner(Creature* pCreature)
{
    return new npc_shadowfang_prisonerAI(pCreature);
}

bool GossipHello_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_FREE_NPC) != DONE && pInstance->GetData(TYPE_RETHILGORE) == DONE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_DOOR, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_shadowfang_prisoner(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (npc_shadowfang_prisonerAI* pEscortAI = dynamic_cast<npc_shadowfang_prisonerAI*>(pCreature->AI()))
            pEscortAI->Start();
    }
    return true;
}

/*######
## mob_arugal_voidwalker
######*/

enum
{
    SPELL_DARK_OFFERING = 7154,
    MAX_VOID_WALKERS    = 4,
};

enum ArugalVoidWalker
{
    VOIDWALKER_DARKOFFERING,
    VOIDWALKER_CHECK_GROUP,
    VOIDWALKER_ACTIONS_MAX
};


struct mob_arugal_voidwalkerAI : public mob_arugal_voidwalker_baseAI
{
    mob_arugal_voidwalkerAI(Creature* creature) : CombatAI(creature, VOIDWALKER_ACTIONS_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        AddCombatAction(VOIDWALKER_DARKOFFERING, 4400, 12500);
        AddCustomAction(VOIDWALKER_CHECK_GROUP, 1000u, [&]() { CheckGroupStatus(); });
        m_position = -1;
        m_leaderGuid = ObjectGuid();
    }

    ScriptedInstance* m_instance;
    
    void GetAIInformation(ChatHandler& reader) override
    {
        if (!m_leaderGuid)
            reader.PSendSysMessage("Arugal's Voidwalker - no group leader found");
        if (IsLeader())
            reader.PSendSysMessage("Arugal's Voidwalker - is group leader");
        else
        {
            if (m_position)
                reader.PSendSysMessage("Arugal's Voidwalker - is follower with position %u", m_position);
            else
                reader.PSendSysMessage("Arugal's Voidwalker - is neither leader nor follower");
        }
    }

    bool IsLeader()
    {
        return m_position == 0;
    }

    void CheckGroupStatus()
    {
        ResetTimer(VOIDWALKER_CHECK_GROUP, 1 * IN_MILLISECONDS);

        // Do not care about group while fighting
        if (m_creature->IsInCombat())
            return;

        // If a group leader already exists and is alive, do nothing
        if (m_leaderGuid && !IsLeader())
        {
            if (Creature* leader = m_creature->GetMap()->GetCreature(m_leaderGuid))
            {
                // Leader is alive and we are following it, do nothing
                if (leader->IsAlive() && m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == FOLLOW_MOTION_TYPE)
                    return;
            }
        }

        // If we are leader and already following path, do nothing
        if (IsLeader())
        {
            if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == WAYPOINT_MOTION_TYPE)
                return;
        }

        // For whatever other reason, re-initialise the group
        InitVoidWalkersGroup();
    }

    void InitVoidWalkersGroup()
    {
        SetLeader();

        // Inform other Voidwalkers
        CreatureList walkersList;
        GetCreatureListWithEntryInGrid(walkersList, m_creature, m_creature->GetEntry(), 50.0f);

        uint8 position = 0;
        for (auto& walker : walkersList)
        {
            if (walker->IsAlive() && walker->GetObjectGuid() != m_leaderGuid)
            {
                mob_arugal_voidwalkerAI* walkerAI = dynamic_cast<mob_arugal_voidwalkerAI*>(walker->AI());
                walkerAI->SetFollower(m_creature->GetObjectGuid(), ++position);
            }
        }

        if (position + 1 > MAX_VOID_WALKERS)
            script_error_log("mob_arugal_voidwalker for %s: has more buddies than expected (%u expected, found: %u).", m_creature->GetGuidStr().c_str(), MAX_VOID_WALKERS, position);
    }

    void ExecuteAction(uint32 action) override
    {
        if (action == VOIDWALKER_DARKOFFERING)
        {
            if (Unit* dearestFriend = DoSelectLowestHpFriendly(10.0f, 290))
            {
                if (DoCastSpellIfCan(dearestFriend, SPELL_DARK_OFFERING) == CAST_OK)
                    ResetCombatAction(action, urand(4, 12) * IN_MILLISECONDS);
            }
        }
    }

    void JustDied(Unit* /*killer*/) override
    {
        if (m_instance)
            m_instance->SetData(TYPE_VOIDWALKER, DONE);
    }
};

/*######
## boss_arugal
######*/

enum
{
    SPELL_VOID_BOLT                 = 7588,
    SPELL_SHADOW_PORT_UPPER_LEDGE   = 7587,
    SPELL_SHADOW_PORT_SPAWN_LEDGE   = 7586,
    SPELL_SHADOW_PORT_STAIRS        = 7136,
    SPELL_ARUGALS_CURSE             = 7621,
    SPELL_THUNDERSHOCK              = 7803,
};

enum ArugalPosition
{
    POSITION_SPAWN_LEDGE = 0,
    POSITION_UPPER_LEDGE = 1,
    POSITION_STAIRS      = 2
};

// Roughly the height of Fenrus' room,
// Used to tell how he should behave
const float HEIGHT_FENRUS_ROOM      = 140.0f;

struct boss_arugalAI : public ScriptedAI
{
    boss_arugalAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

        if (pCreature->GetPositionZ() < HEIGHT_FENRUS_ROOM)
        {
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->SetVisibility(VISIBILITY_OFF);
            m_bEventMode = true;
        }
        else
            m_bEventMode = false;

        Reset();
    }

    ScriptedInstance* m_pInstance;
    ArugalPosition m_posPosition;
    uint32 m_uiTeleportTimer, m_uiCurseTimer, m_uiVoidboltTimer, m_uiThundershockTimer, m_uiYellTimer;
    bool m_bAttacking, m_bEventMode;

    void Reset() override
    {
        m_uiTeleportTimer = urand(22000, 26000);
        m_uiCurseTimer = urand(20000, 30000);
        m_uiVoidboltTimer = m_uiThundershockTimer = 0;
        m_uiYellTimer = urand(32000, 46000);
        m_bAttacking = true;
        m_posPosition = POSITION_SPAWN_LEDGE;
    }

    void Aggro(Unit* pWho) override
    {
        DoScriptText(YELL_AGGRO, m_creature);
        DoCastSpellIfCan(pWho, SPELL_VOID_BOLT);
    }

    void KilledUnit(Unit* pVictim) override
    {
        if (pVictim->GetTypeId() == TYPEID_PLAYER)
            DoScriptText(YELL_KILLED_PLAYER, m_creature);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_bEventMode)
            return;

        // Check if we have a current target
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if (GetManaPercent() < 6.0f && !m_bAttacking)
        {
            if (m_posPosition != POSITION_UPPER_LEDGE)
                StartAttacking();
            else if (m_uiTeleportTimer > 2000)
                m_uiTeleportTimer = 2000;

            m_bAttacking = true;
        }
        else if (GetManaPercent() > 12.0f && m_bAttacking)
        {
            StopAttacking();
            m_bAttacking = false;
        }

        if (m_uiYellTimer < uiDiff)
        {
            DoScriptText(YELL_COMBAT, m_creature);
            m_uiYellTimer = urand(34000, 68000);
        }
        else
            m_uiYellTimer -= uiDiff;

        if (m_uiCurseTimer < uiDiff)
        {
            if (Unit* pTarget = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 1))
                DoCastSpellIfCan(pTarget, SPELL_ARUGALS_CURSE);

            m_uiCurseTimer = urand(20000, 35000);
        }
        else
            m_uiCurseTimer -= uiDiff;

        if (m_uiThundershockTimer < uiDiff)
        {
            if (GetVictimDistance() < 5.0f)
            {
                DoCastSpellIfCan(m_creature->GetVictim(), SPELL_THUNDERSHOCK);
                m_uiThundershockTimer = urand(30200, 38500);
            }
        }
        else
            m_uiThundershockTimer -= uiDiff;

        if (m_uiVoidboltTimer < uiDiff)
        {
            if (!m_bAttacking)
            {
                DoCastSpellIfCan(m_creature->GetVictim(), SPELL_VOID_BOLT);
                m_uiVoidboltTimer = urand(2900, 4800);
            }
        }
        else
            m_uiVoidboltTimer -= uiDiff;

        if (m_uiTeleportTimer < uiDiff)
        {
            ArugalPosition posNewPosition;

            if (m_posPosition == POSITION_SPAWN_LEDGE)
                posNewPosition = (ArugalPosition)urand(1, 2);
            else
            {
                posNewPosition = (ArugalPosition)urand(0, 1);

                if (m_posPosition == posNewPosition)
                    posNewPosition = POSITION_STAIRS;
            }

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            switch (posNewPosition)
            {
                case POSITION_SPAWN_LEDGE:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_SPAWN_LEDGE, true);
                    break;
                case POSITION_UPPER_LEDGE:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_UPPER_LEDGE, true);
                    break;
                case POSITION_STAIRS:
                    DoCastSpellIfCan(m_creature, SPELL_SHADOW_PORT_STAIRS, true);
                    break;
            }

            if (GetManaPercent() < 6.0f)
            {
                if (posNewPosition == POSITION_UPPER_LEDGE)
                {
                    StopAttacking();
                    m_uiTeleportTimer = urand(2000, 2200);
                }
                else
                {
                    StartAttacking();
                    m_uiTeleportTimer = urand(48000, 55000);
                }
            }
            else
                m_uiTeleportTimer = urand(48000, 55000);

            m_posPosition = posNewPosition;
        }
        else
            m_uiTeleportTimer -= uiDiff;

        if (m_bAttacking)
            DoMeleeAttackIfReady();
    }

    void AttackStart(Unit* pWho) override
    {
        if (!m_bEventMode)
            ScriptedAI::AttackStart(pWho);
    }

    // Make the code nice and pleasing to the eye
    inline float GetManaPercent() const
    {
        return (((float)m_creature->GetPower(POWER_MANA) / (float)m_creature->GetMaxPower(POWER_MANA)) * 100);
    }

    inline float GetVictimDistance() const
    {
        return (m_creature->GetVictim() ? m_creature->GetDistance(m_creature->GetVictim(), false) : 999.9f);
    }

    void StopAttacking()
    {
        if (Unit* victim = m_creature->GetVictim())
            m_creature->SendMeleeAttackStop(victim);

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == CHASE_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear(false);
            m_creature->GetMotionMaster()->MoveIdle();
            m_creature->StopMoving();
        }
    }

    void StartAttacking()
    {
        if (Unit* victim = m_creature->GetVictim())
            m_creature->SendMeleeAttackStart(victim);

        if (m_creature->GetMotionMaster()->GetCurrentMovementGeneratorType() == IDLE_MOTION_TYPE)
        {
            m_creature->GetMotionMaster()->Clear(false);
            m_creature->GetMotionMaster()->MoveChase(m_creature->GetVictim(), 0.0f, 0.0f);
        }
    }
};

UnitAI* GetAI_boss_arugal(Creature* pCreature)
{
    return new boss_arugalAI(pCreature);
}

/*######
## npc_deathstalker_vincent
######*/

enum
{
    SAY_VINCENT_DIE     = -1033016,

    FACTION_FRIENDLY    = 35
};

struct npc_deathstalker_vincentAI : public ScriptedAI
{
    npc_deathstalker_vincentAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset() override
    {
        if (m_pInstance && m_pInstance->GetData(TYPE_INTRO) == DONE && !m_creature->GetByteValue(UNIT_FIELD_BYTES_1, 0))
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
        if (m_pInstance && (m_pInstance->GetData(TYPE_INTRO) == NOT_STARTED || m_pInstance->GetData(TYPE_INTRO) == IN_PROGRESS))
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
    }

    void DamageTaken(Unit* /*dealer*/, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (m_creature->getStandState())
            m_creature->SetStandState(UNIT_STAND_STATE_STAND);

        if (damage >= m_creature->GetHealth())
        {
            damage = std::min(damage, m_creature->GetHealth() - 1);
            m_creature->SetFactionTemporary(FACTION_FRIENDLY, TEMPFACTION_NONE);
            EnterEvadeMode();
            DoScriptText(SAY_VINCENT_DIE, m_creature);
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (m_creature->IsInCombat() && m_creature->getFaction() == FACTION_FRIENDLY)
            EnterEvadeMode();

        ScriptedAI::UpdateAI(uiDiff);
    }
};

UnitAI* GetAI_npc_deathstalker_vincent(Creature* pCreature)
{
    return new npc_deathstalker_vincentAI(pCreature);
}

struct ForsakenSkill : public AuraScript
{
    void OnPeriodicDummy(Aura* aura) const override
    {
        // Possibly need cast one of them (but
        // 7038 Forsaken Skill: Swords
        // 7039 Forsaken Skill: Axes
        // 7040 Forsaken Skill: Daggers
        // 7041 Forsaken Skill: Maces
        // 7042 Forsaken Skill: Staves
        // 7043 Forsaken Skill: Bows
        // 7044 Forsaken Skill: Guns
        // 7045 Forsaken Skill: 2H Axes
        // 7046 Forsaken Skill: 2H Maces
        // 7047 Forsaken Skill: 2H Swords
        // 7048 Forsaken Skill: Defense
        // 7049 Forsaken Skill: Fire
        // 7050 Forsaken Skill: Frost
        // 7051 Forsaken Skill: Holy
        // 7053 Forsaken Skill: Shadow
        static uint32 forsakenSpells[] = { 7038,7039,7040,7041,7042,7043,7044,7045,7046,7047,7048,7049,7050,7051,7053 };
        if (urand(0, 99) == 0)
            aura->GetTarget()->CastSpell(nullptr, forsakenSpells[urand(0, 14)], TRIGGERED_OLD_TRIGGERED);
    }
};

void AddSC_shadowfang_keep()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_shadowfang_prisoner";
    pNewScript->pGossipHello =  &GossipHello_npc_shadowfang_prisoner;
    pNewScript->pGossipSelect = &GossipSelect_npc_shadowfang_prisoner;
    pNewScript->GetAI = &GetAI_npc_shadowfang_prisoner;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "mob_arugal_voidwalker";
    pNewScript->GetAI = &GetNewAIInstance<mob_arugal_voidwalkerAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_arugal";
    pNewScript->GetAI = &GetAI_boss_arugal;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_deathstalker_vincent";
    pNewScript->GetAI = &GetAI_npc_deathstalker_vincent;
    pNewScript->RegisterSelf();

    RegisterAuraScript<ForsakenSkill>("spell_forsaken_skill");
}

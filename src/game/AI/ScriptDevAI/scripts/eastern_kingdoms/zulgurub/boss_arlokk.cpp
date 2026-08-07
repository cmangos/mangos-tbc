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
SDName: Boss_Arlokk
SD%Complete: 80
SDComment: Vanish spell is replaced by workaround; Timers
SDCategory: Zul'Gurub
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "zulgurub.h"
#include "AI/ScriptDevAI/base/CombatAI.h"

/* ContentData
boss_arlokk
npc_zulian_prowler
go_gong_of_bethekk
EndContentData */

enum
{
    SAY_AGGRO                   = -1309011,
    SAY_FEAST_PANTHER           = -1309012,
    SAY_DEATH                   = -1309013,

    SPELL_SHADOW_WORD_PAIN      = 24212,
    SPELL_GOUGE                 = 12540,
    SPELL_MARK_ARLOKK           = 24210,
    SPELL_RAVAGE                = 24213,
    SPELL_TRASH                 = 3391,
    SPELL_WHIRLWIND             = 24236,
    SPELL_PANTHER_TRANSFORM     = 24190,
    SPELL_HATE_TO_ZERO          = 20538,

    // 1.12 used spells 24247 (periodic trigger aura) and 24246 (summon) which do
    // not exist in TBC data, so the summoning is now implemented directly.
    NPC_ZULIAN_PROWLER          = 15101,

    SPELL_VANISH_TELEPORT       = 24228,
    SPELL_VANISH                = 24223,
    SPELL_SUPER_INVIS           = 24235,

    SPELL_TRANSFORM_VISUAL      = 24085,

    SPELL_SNEAK                 = 22766,

    SPELL_LIST_PHASE_1 = 1451501,
    SPELL_LIST_PHASE_2 = 1451502,
};

enum ArlokkActions
{
    ARLOKK_PHASE_TRANSITION,
    ARLOKK_SUMMON_PROWLERS,
    ARLOKK_ACTION_MAX,
    ARLOKK_INVIS_SELECT,
    ARLOKK_INVIS_TIMER,
};

struct boss_arlokkAI : public CombatAI
{
    boss_arlokkAI(Creature* creature) : CombatAI(creature, ARLOKK_ACTION_MAX), m_instance(static_cast<instance_zulgurub*>(creature->GetInstanceData()))
    {
        AddCombatAction(ARLOKK_PHASE_TRANSITION, 30000u);
        AddCombatAction(ARLOKK_SUMMON_PROWLERS, 5000u);
        AddCustomAction(ARLOKK_INVIS_SELECT, true, [&]()
        {
            if (Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                AttackStart(target);
            SetCombatMovement(false, true);
        });
        AddCustomAction(ARLOKK_INVIS_TIMER, true, [&]()
        {
            m_creature->RemoveAurasDueToSpell(SPELL_SUPER_INVIS);
            SetCombatScriptStatus(false);
            SetCombatMovement(true, true);
            SetMeleeEnabled(true);
        });
    }

    instance_zulgurub* m_instance;

    ObjectGuid m_trigger1Guid;
    ObjectGuid m_trigger2Guid;

    GuidList m_lProwlerGUIDList;

    bool m_bIsPhaseTwo;

    void Reset() override
    {
        CombatAI::Reset();

        m_bIsPhaseTwo = false;

        m_trigger1Guid.Clear();
        m_trigger2Guid.Clear();
        m_lProwlerGUIDList.clear();

        SetCombatScriptStatus(false);
        SetCombatMovement(true);
        SetMeleeEnabled(true);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_AGGRO, m_creature);

        m_lProwlerGUIDList.clear();

        if (Creature* pTrigger = m_instance->SelectRandomPantherTrigger(true))
            m_trigger1Guid = pTrigger->GetObjectGuid();

        if (Creature* pTrigger = m_instance->SelectRandomPantherTrigger(false))
            m_trigger2Guid = pTrigger->GetObjectGuid();
    }

    // The boss returns to the pull position on evade and may despawn before
    // reaching its real home, so JustReachedHome is not a reliable cleanup
    // point. Stop the summons and despawn the prowlers as soon as evade starts.
    void EnterEvadeMode() override
    {
        DoStopZulianProwlers();
        CombatAI::EnterEvadeMode();
    }

    // Replicates the 1.12 mechanic: each of the two panther triggers summons a
    // Zulian Prowler every 5 seconds for as long as the encounter is running.
    void SummonZulianProwlers()
    {
        ObjectGuid aTriggerGuids[2] = { m_trigger1Guid, m_trigger2Guid };

        for (uint8 i = 0; i < 2; ++i)
        {
            if (Creature* pTrigger = m_creature->GetMap()->GetCreature(aTriggerGuids[i]))
            {
                if (!pTrigger->IsAlive())
                    continue;

                if (Creature* pProwler = m_creature->SummonCreature(NPC_ZULIAN_PROWLER,
                        pTrigger->GetPositionX(), pTrigger->GetPositionY(), pTrigger->GetPositionZ(), pTrigger->GetOrientation(),
                        TEMPSPAWN_DEAD_DESPAWN, 0))
                {
                    m_lProwlerGUIDList.push_back(pProwler->GetObjectGuid());
                }
            }
        }
    }

    void JustReachedHome() override
    {
        DoStopZulianProwlers();

        if (m_instance)
            m_instance->SetData(TYPE_ARLOKK, FAIL);

        // we should be summoned, so despawn
        m_creature->ForcedDespawn();

        m_creature->SetSpellList(SPELL_LIST_PHASE_1);
    }

    void JustDied(Unit* /*pKiller*/) override
    {
        DoScriptText(SAY_DEATH, m_creature);
        // Restore visibility in case of killed by dots
        if (m_creature->GetVisibility() != VISIBILITY_ON)
            m_creature->SetVisibility(VISIBILITY_ON);

        DoStopZulianProwlers();

        if (m_instance)
            m_instance->SetData(TYPE_ARLOKK, DONE);
    }

    // Wrapper to stop the summoning and despawn the zulian panthers on evade / death.
    // Re-resolve objects by GUID so a despawned object is never dereferenced.
    void DoStopZulianProwlers()
    {
        m_trigger1Guid.Clear();
        m_trigger2Guid.Clear();

        for (GuidList::const_iterator itr = m_lProwlerGUIDList.begin(); itr != m_lProwlerGUIDList.end(); ++itr)
        {
            if (Creature* pProwler = m_creature->GetMap()->GetCreature(*itr))
                pProwler->ForcedDespawn();
        }

        m_lProwlerGUIDList.clear();
    }

    void ReceiveAIEvent(AIEventType eventType, Unit* /*sender*/, Unit* /*invoker*/, uint32 /*miscValue*/) override
    {
        if (eventType == AI_EVENT_CUSTOM_A)
        {
            DoResetThreat();
            SetCombatScriptStatus(true);
            SetMeleeEnabled(false);
            ResetTimer(ARLOKK_INVIS_SELECT, 10000);
            ResetTimer(ARLOKK_INVIS_TIMER, 50000);
        }
    }

    void ExecuteAction(uint32 action) override
    {
        switch (action)
        {
            case ARLOKK_SUMMON_PROWLERS:
                SummonZulianProwlers();
                ResetCombatAction(action, 5000);
                break;

            case ARLOKK_PHASE_TRANSITION:
                if (m_bIsPhaseTwo)
                {
                    if (DoCastSpellIfCan(nullptr, SPELL_TRANSFORM_VISUAL) == CAST_OK)
                    {
                        m_creature->RemoveAurasDueToSpell(SPELL_PANTHER_TRANSFORM);
                        ResetCombatAction(action, 30000);
                        m_bIsPhaseTwo = false;
                        m_creature->SetSpellList(SPELL_LIST_PHASE_1);
                    }
                }
                else
                {
                    if (DoCastSpellIfCan(nullptr, SPELL_PANTHER_TRANSFORM) == CAST_OK)
                    {
                        m_creature->CastSpell(nullptr, SPELL_HATE_TO_ZERO, TRIGGERED_NONE);
                        ResetCombatAction(action, 120000);
                        m_bIsPhaseTwo = true;
                        m_creature->SetSpellList(SPELL_LIST_PHASE_2);
                    }
                }
                break;
        }
    }

    void OnSpellCast(SpellEntry const* spellInfo, Unit* target) override
    {
        if (spellInfo->Id == SPELL_MARK_ARLOKK)
            DoScriptText(SAY_FEAST_PANTHER, m_creature, target);
    }
};

struct npc_zulian_prowlerAI : public ScriptedAI
{
    npc_zulian_prowlerAI(Creature* creature) : ScriptedAI(creature), m_bMoveToAid(creature->IsTemporarySummon())
    {
        Reset();
    }

    GuidList m_lProwlerGUIDList;

    bool m_bMoveToAid;

    void Reset() override {}

    void JustRespawned() override
    {
        ScriptedAI::JustRespawned();
        DoCastSpellIfCan(nullptr, SPELL_SNEAK);

        // Do only once, and only for those summoned by Arlokk
        if (m_bMoveToAid)
        {
            // Add to GUID list to despawn later
            m_lProwlerGUIDList.push_back(m_creature->GetObjectGuid());

            // Count the number of prowlers alive
            uint32 count = 0;
            for (GuidList::const_iterator itr = m_lProwlerGUIDList.begin(); itr != m_lProwlerGUIDList.end(); ++itr)
            {
                if (Unit* pProwler = m_creature->GetMap()->GetUnit(*itr))
                    if (pProwler->IsAlive())
                        count++;
            }

            // Check if more than 40 are alive, if so, despawn
            if (count > 40)
            {
                m_creature->ForcedDespawn();
                return;
            }

            m_creature->GetMotionMaster()->Clear();
            m_creature->GetMotionMaster()->MovePoint(1, aArlokkWallShieldPos[0], aArlokkWallShieldPos[1], aArlokkWallShieldPos[2]);

            m_bMoveToAid = false;
        }
    }
};

bool GOUse_go_gong_of_bethekk(Player* /*pPlayer*/, GameObject* pGo)
{
    if (ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData())
    {
        if (pInstance->GetData(TYPE_ARLOKK) == DONE || pInstance->GetData(TYPE_ARLOKK) == IN_PROGRESS)
            return true;

        pInstance->SetData(TYPE_ARLOKK, IN_PROGRESS);
    }

    return false;
}

struct ArlokkVanish : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_1)
            return;

        Unit* caster = spell->GetCaster();
        caster->CastSpell(nullptr, SPELL_VANISH_TELEPORT, TRIGGERED_OLD_TRIGGERED);
        caster->CastSpell(nullptr, SPELL_SUPER_INVIS, TRIGGERED_OLD_TRIGGERED);

        if (caster->AI())
            caster->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, caster, caster);
    }
};

void AddSC_boss_arlokk()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "boss_arlokk";
    pNewScript->GetAI = &GetNewAIInstance<boss_arlokkAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_zulian_prowler";
    pNewScript->GetAI = &GetNewAIInstance<npc_zulian_prowlerAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_gong_of_bethekk";
    pNewScript->pGOUse = &GOUse_go_gong_of_bethekk;
    pNewScript->RegisterSelf();

    RegisterSpellScript<ArlokkVanish>("spell_arlokk_vanish");
}

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
SDName: Boss_Mograine_And_Whitemane
SD%Complete: 95
SDComment:
SDCategory: Scarlet Monastery
EndScriptData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "scarlet_monastery.h"
#include "AI/ScriptDevAI/base/CombatAI.h"

enum
{
    // Mograine says
    SAY_MO_AGGRO                 = -1189005,
    SAY_MO_KILL                  = -1189006,
    SAY_MO_RESSURECTED           = -1189007,

    // Whitemane says
    SAY_WH_INTRO                 = -1189008,
    SAY_WH_KILL                  = -1189009,
    SAY_WH_RESSURECT             = -1189010,

    // Mograine Spells
    SPELL_CRUSADERSTRIKE         = 14518,
    SPELL_HAMMEROFJUSTICE        = 5589,
    SPELL_LAYONHANDS             = 9257,
    SPELL_RETRIBUTIONAURA        = 8990,
    SPELL_DIVINESHIELD           = 642,

    // Whitemanes Spells
    SPELL_DEEPSLEEP              = 9256,
    SPELL_SCARLETRESURRECTION    = 9232,
    SPELL_DOMINATEMIND           = 14515,
    SPELL_HOLYSMITE              = 9481,
    SPELL_HEAL                   = 12039,
    SPELL_POWERWORDSHIELD        = 22187,

    ASHBRINGER_RELAY_SCRIPT_ID   = 9001,
    ITEM_CORRUPTED_ASHBRINGER    = 22691,

    SOUND_MOGRAINE_FAKE_DEATH    = 1326,
};

enum MograineActions
{
    MOGRAINE_ACTION_CRUSADER_STRIKE,
    MOGRAINE_ACTION_HAMMER_OF_JUSTICE,
    MOGRAINE_ACTION_LAY_ON_HANDS,
    MOGRAINE_ACTION_DIVINE_SHIELD,
    MOGRAINE_ACTION_MAX,
};

enum WhitemaneActions
{
    WHITEMANE_ACTION_DEEP_SLEEP,
    WHITEMANE_ACTION_SCARLET_RESURRECTION,
    WHITEMANE_ACTION_DOMINATE_MIND,
    WHITEMANE_ACTION_HOLY_SMITE,
    WHITEMANE_ACTION_HEAL,
    WHITEMANE_ACTION_POWERWORD_SHIELD,
    WHITEMANE_ACTION_SCARLET_RESURRECTION_ENTER_COMBAT,
    WHITEMANE_ACTION_SCARLET_RESURRECTION_TIMER,
    WHITEMANE_ACTION_MAX,
};

struct boss_scarlet_commander_mograineAI : public CombatAI
{
    boss_scarlet_commander_mograineAI(Creature* creature) : CombatAI(creature, MOGRAINE_ACTION_MAX), m_instance(static_cast<instance_scarlet_monastery*>(creature->GetInstanceData()))
    {
        AddCombatAction(MOGRAINE_ACTION_CRUSADER_STRIKE, 8400u);
        AddCombatAction(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, 9600u);
        AddCombatAction(MOGRAINE_ACTION_DIVINE_SHIELD, 40000u);
        AddTimerlessCombatAction(MOGRAINE_ACTION_LAY_ON_HANDS, true);
        Reset();
    }

    instance_scarlet_monastery* m_instance;

    // uint32 m_uiCrusaderStrike_Timer;
    // uint32 m_uiHammerOfJustice_Timer;
    // uint32 m_uiDivineShield_Timer;

    bool m_bHasDied;
    bool m_bHeal;
    bool m_bFakeDeath;
    bool m_bDivineShield;

    void Reset() override
    {
        CombatAI::Reset();
        m_bHasDied                = false;
        m_bHeal                   = false;
        m_bFakeDeath              = false;
        m_bDivineShield           = false;

        // Incase wipe during phase that mograine fake death
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        SetDeathPrevention(true);
    }

    uint32 GetSubsequentActionTimer(uint32 id)
    {
        switch (id)
        {
            case MOGRAINE_ACTION_CRUSADER_STRIKE: return urand(6000, 15000);
            case MOGRAINE_ACTION_HAMMER_OF_JUSTICE: return urand(7000, 18500);
            default: return 0; // never occurs but for compiler
        }
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (!m_instance)
            return;

        if (m_instance->GetData(TYPE_ASHBRINGER_EVENT) == IN_PROGRESS)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = static_cast<Player*>(pWho);
                if (player->HasItemOrGemWithIdEquipped(ITEM_CORRUPTED_ASHBRINGER, 1) && m_creature->IsWithinDist(player, 20.0f))
                {
                    player->GetMap()->ScriptsStart(sRelayScripts, ASHBRINGER_RELAY_SCRIPT_ID, m_creature, player);
                    m_instance->SetData(TYPE_ASHBRINGER_EVENT, DONE);
                }
            }
        }
        ScriptedAI::MoveInLineOfSight(pWho);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_MO_AGGRO, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_RETRIBUTIONAURA);

        m_creature->CallForHelp(VISIBLE_RANGE);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoScriptText(SAY_MO_KILL, m_creature);
    }

    void JustReachedHome() override
    {
        if (!m_instance)
            return;

        Creature* pWhitemane = m_instance->GetSingleCreatureFromStorage(NPC_WHITEMANE);
        if (pWhitemane && !pWhitemane->IsAlive()){
            if (!(m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED) || !(m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
                m_instance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, FAIL);
            pWhitemane->Respawn();
        }            
    }

    void JustPreventedDeath(Unit* /*attacker*/) override
    {
        if (!m_instance)
            return;

        if (Creature* pWhitemane = m_instance->GetSingleCreatureFromStorage(NPC_WHITEMANE))
        {
            m_instance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, IN_PROGRESS);

            pWhitemane->GetMotionMaster()->MovePoint(1, 1163.113370f, 1398.856812f, 32.527786f);
            pWhitemane->AI()->AttackStart(m_creature->GetVictim());

            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->GetMotionMaster()->MoveIdle();

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            m_creature->ClearComboPointHolders();
            m_creature->RemoveAllAurasOnDeath();
            m_creature->ClearAllReactives();

            SetActionReadyStatus(MOGRAINE_ACTION_CRUSADER_STRIKE, false);
            SetActionReadyStatus(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, false);
            SetActionReadyStatus(MOGRAINE_ACTION_DIVINE_SHIELD, false);

            DisableCombatAction(MOGRAINE_ACTION_CRUSADER_STRIKE);
            DisableCombatAction(MOGRAINE_ACTION_HAMMER_OF_JUSTICE);
            DisableCombatAction(MOGRAINE_ACTION_DIVINE_SHIELD);

            m_creature->PlayDistanceSound(SOUND_MOGRAINE_FAKE_DEATH);

            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            m_creature->SetStandState(UNIT_STAND_STATE_DEAD);

            m_bHasDied = true;
            m_bFakeDeath = true;
        }
    }

    void SpellHit(Unit* /*pWho*/, const SpellEntry* pSpell) override
    {
        // When hit with ressurection say text
        if (pSpell->Id == SPELL_SCARLETRESURRECTION)
        {
            DoScriptText(SAY_MO_RESSURECTED, m_creature);
            m_bFakeDeath = false;

            if (m_instance)
                m_instance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, SPECIAL);
        }
    }

    void ExecuteAction(uint32 action) override
    {
        switch (action)
        {
    // MOGRAINE_ACTION_CRUSADER_STRIKE,
    // MOGRAINE_ACTION_HAMMER_OF_JUSTICE,
    // MOGRAINE_ACTION_LAY_ON_HANDS,
    // MOGRAINE_ACTION_DIVINE_SHIELD,
    // MOGRAINE_ACTION_MAX,
            case MOGRAINE_ACTION_CRUSADER_STRIKE:
            {
                if(DoCastSpellIfCan(m_creature->GetVictim(), SPELL_CRUSADERSTRIKE) == CAST_OK)
                    ResetCombatAction(action, GetSubsequentActionTimer(action));
                return;
            }
            case MOGRAINE_ACTION_HAMMER_OF_JUSTICE:
            {
                if(DoCastSpellIfCan(m_creature->GetVictim(), SPELL_HAMMEROFJUSTICE) == CAST_OK)
                    ResetCombatAction(action, GetSubsequentActionTimer(action));
                return;
            }
            case MOGRAINE_ACTION_LAY_ON_HANDS:
            {
                if (m_bHasDied && !m_bHeal && m_instance && m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == SPECIAL)
                    {
                        if (Creature* pWhitemane = m_instance->GetSingleCreatureFromStorage(NPC_WHITEMANE))
                        {
                            // On ressurection, stop fake death and heal whitemane and resume fight
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
                            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                            m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                            SetDeathPrevention(false);
                            // spell has script target on Whitemane but sometimes wouldn't work
                            if(DoCastSpellIfCan(pWhitemane, SPELL_LAYONHANDS) != CAST_OK)
                            {
                                pWhitemane->SetHealth(std::min(pWhitemane->GetMaxHealth(), m_creature->GetMaxHealth()));
                            }
                            SetActionReadyStatus(MOGRAINE_ACTION_CRUSADER_STRIKE, true);
                            SetActionReadyStatus(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, true);
                            SetActionReadyStatus(MOGRAINE_ACTION_DIVINE_SHIELD, true);
                            ResetIfNotStarted(MOGRAINE_ACTION_CRUSADER_STRIKE, GetSubsequentActionTimer(MOGRAINE_ACTION_CRUSADER_STRIKE));
                            ResetCombatAction(MOGRAINE_ACTION_CRUSADER_STRIKE, GetSubsequentActionTimer(MOGRAINE_ACTION_CRUSADER_STRIKE));
                            ResetIfNotStarted(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, GetSubsequentActionTimer(MOGRAINE_ACTION_HAMMER_OF_JUSTICE));
                            ResetCombatAction(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, GetSubsequentActionTimer(MOGRAINE_ACTION_HAMMER_OF_JUSTICE));

                            if (m_creature->GetVictim())
                                m_creature->GetMotionMaster()->MoveChase(m_creature->GetVictim());

                            m_bHeal = true;
                        }
                    }

                return;
            }
            case MOGRAINE_ACTION_DIVINE_SHIELD:
            {
                if(!m_bDivineShield && m_creature->GetHealthPercent() <= 50.f)
                    if(DoCastSpellIfCan(m_creature, SPELL_DIVINESHIELD) == CAST_OK)
                    {
                        m_bDivineShield = true;
                        DisableCombatAction(action); // once per fight
                    }
                return;
            }
        }
    }
};
/*
  boss_scarlet_commander_mograineAI(Creature* creature) : CombatAI(creature, MOGRAINE_ACTION_MAX), m_instance(static_cast<instance_scarlet_monastery*>(creature->GetInstanceData()))
    {
        AddCombatAction(MOGRAINE_ACTION_CRUSADER_STRIKE, 8400u);
        AddCombatAction(MOGRAINE_ACTION_HAMMER_OF_JUSTICE, 9600u);
        AddCombatAction(MOGRAINE_ACTION_DIVINE_SHIELD, 40000u);
        AddTimerlessCombatAction(MOGRAINE_ACTION_LAY_ON_HANDS, true);
        Reset();
    }

    WHITEMANE_ACTION_DEEP_SLEEP,
    WHITEMANE_ACTION_SCARLET_RESURRECTION,
    WHITEMANE_ACTION_DOMINATE_MIND,
    WHITEMANE_ACTION_HOLY_SMITE,
    WHITEMANE_ACTION_HEAL,
    WHITEMANE_ACTION_POWERWORD_SHIELD,
    WHITEMANE_ACTION_MAX,
    WHITEMANE_ACTION_SCARLET_RESURRECTION_ENTER_COMBAT,
    WHITEMANE_ACTION_SCARLET_RESURRECTION_TIMER,

*/
struct boss_high_inquisitor_whitemaneAI : public CombatAI
{
    boss_high_inquisitor_whitemaneAI(Creature* creature) : CombatAI(creature, WHITEMANE_ACTION_MAX), m_instance(static_cast<instance_scarlet_monastery*>(creature->GetInstanceData()))
    {
        AddCombatAction(WHITEMANE_ACTION_HEAL, 10000u);
        AddCombatAction(WHITEMANE_ACTION_POWERWORD_SHIELD, 15000u);
        AddCombatAction(WHITEMANE_ACTION_HOLY_SMITE, 4000u);
        AddCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION, true);
        AddCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION_TIMER, false);
        AddCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION_ENTER_COMBAT, false);
        AddTimerlessCombatAction(WHITEMANE_ACTION_DEEP_SLEEP, true);
        AddTimerlessCombatAction(WHITEMANE_ACTION_DOMINATE_MIND, true);

        Reset();
    }

    uint32 GetSubsequentActionTimer(uint32 id)
    {
        switch (id)
        {
            case WHITEMANE_ACTION_HEAL: return 13000u;
            case WHITEMANE_ACTION_POWERWORD_SHIELD: return urand(22000, 45000);
            case WHITEMANE_ACTION_HOLY_SMITE: return urand(3500, 5000);
            default: return 0; // never occurs but for compiler
        }
    }

    instance_scarlet_monastery* m_instance;

    bool m_bCanResurrectCheck;
    bool m_bCanResurrect;
    bool m_bDidResurrect;

    void Reset() override
    {
        CombatAI::Reset();

        m_bCanResurrectCheck      = false;
        m_bCanResurrect           = false;
        m_bDidResurrect           = false;

        SetCombatScriptStatus(false);

        if (!m_instance)
            return;

        if (Creature* pMograine = m_instance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
        {
            if (m_creature->IsAlive() && !pMograine->IsAlive())
                pMograine->Respawn();
        }
    }

    void JustReachedHome() override
    {
        if (m_instance)
        {
            if (!(m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED) || !(m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
                m_instance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, FAIL);
        }
    }

    void MoveInLineOfSight(Unit* /*pWho*/) override
    {
        // This needs to be empty because Whitemane should NOT aggro while fighting Mograine. Mograine will give us a target.
    }

    void AttackStart(Unit* pWho) override
    {
        if (m_instance && (m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED || m_instance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId) override
    {
        if (uiMotionType == POINT_MOTION_TYPE && uiPointId == 2)
            if(m_instance)
                if (Creature* pMograine = m_instance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
                    m_creature->SetFacingToObject(pMograine);
        if(uiMotionType == POINT_MOTION_TYPE && uiPointId == 1)
            SetCombatScriptStatus(true);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_WH_INTRO, m_creature);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoScriptText(SAY_WH_KILL, m_creature);
    }

    void ExecuteAction(uint32 action) override
    {
        switch (action)
        {
    // WHITEMANE_ACTION_DEEP_SLEEP,
    // WHITEMANE_ACTION_SCARLET_RESURRECTION,
    // WHITEMANE_ACTION_DOMINATE_MIND,
    // WHITEMANE_ACTION_HOLY_SMITE,
    // WHITEMANE_ACTION_HEAL,
    // WHITEMANE_ACTION_POWERWORD_SHIELD,
    // WHITEMANE_ACTION_MAX,
            case WHITEMANE_ACTION_HEAL:
            {
                sLog.outError("Heal");
                if (Unit* pTarget = DoSelectLowestHpFriendly(50.0f))
                {
                    if (DoCastSpellIfCan(pTarget, SPELL_HEAL) == CAST_OK)
                        ResetCombatAction(action, GetSubsequentActionTimer(action));
                }
                return;
            }
            case WHITEMANE_ACTION_HOLY_SMITE:
            {
                sLog.outError("Smite");
                if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_HOLYSMITE) == CAST_OK)                    
                    ResetCombatAction(action, GetSubsequentActionTimer(action));
                return;
            }
            case WHITEMANE_ACTION_POWERWORD_SHIELD:
            {
                sLog.outError("Shield");
                if (DoCastSpellIfCan(m_creature, SPELL_POWERWORDSHIELD) == CAST_OK)
                    ResetCombatAction(action, GetSubsequentActionTimer(action));
                return;
            }
            case WHITEMANE_ACTION_DEEP_SLEEP:
            {
                if (!m_bCanResurrectCheck && m_creature->GetHealthPercent() <= 50.0f)
                {
                    DoCastSpellIfCan(m_creature, SPELL_DEEPSLEEP, CAST_INTERRUPT_PREVIOUS);
                    m_bCanResurrectCheck = true;
                    m_bCanResurrect = true;
                    if (Creature* pMograine = m_instance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
                    {
                        SetCombatMovement(false);
                        m_creature->AttackStop(true);
                        float fX, fY, fZ;
                        pMograine->GetContactPoint(m_creature, fX, fY, fZ, INTERACTION_DISTANCE/2.f);
                        m_creature->GetMotionMaster()->Clear();
                        m_creature->GetMotionMaster()->MovePoint(2, fX, fY, fZ, FORCED_MOVEMENT_RUN);
                    }
                    DisableCombatAction(action);
                }
                return;
            }
            case WHITEMANE_ACTION_DOMINATE_MIND:
            {
                if(urand(1, 1000) == 1){
                    Unit* target = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0);
                    if(target)
                        DoCastSpellIfCan(target, SPELL_DOMINATEMIND);
                }
                return;
            }
            case WHITEMANE_ACTION_SCARLET_RESURRECTION_TIMER:
            {
                if (m_bCanResurrect)
                {
                    m_creature->AttackStop(true);
                    ResetCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION, 7000u);
                    DisableCombatAction(WHITEMANE_ACTION_DOMINATE_MIND);
                    DisableCombatAction(WHITEMANE_ACTION_HEAL);
                    DisableCombatAction(WHITEMANE_ACTION_HOLY_SMITE);
                    DisableCombatAction(action);
                }
                return;
            }
            case WHITEMANE_ACTION_SCARLET_RESURRECTION:
            {
                DisableCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION);
                if (Creature* pMograine = m_instance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
                {
                    m_creature->SetFacingToObject(pMograine);
                }
                // spell has script target on Mograine
                DoCastSpellIfCan(m_creature, SPELL_SCARLETRESURRECTION);
                DoScriptText(SAY_WH_RESSURECT, m_creature);
                m_bCanResurrect = false;
                m_bDidResurrect = true;
                m_creature->GetMotionMaster()->Clear();
                SetCombatMovement(true);
                ResetCombatAction(WHITEMANE_ACTION_SCARLET_RESURRECTION_ENTER_COMBAT, 2200u);
                m_creature->AttackStop(true);
                return;
            }
            case WHITEMANE_ACTION_SCARLET_RESURRECTION_ENTER_COMBAT:
            {
                m_creature->GetMotionMaster()->MoveChase(m_creature->GetVictim());
                m_bDidResurrect = false;
                ResetTimer(WHITEMANE_ACTION_HEAL, 13000u);
                ResetTimer(WHITEMANE_ACTION_POWERWORD_SHIELD, urand(22000, 45000));
                ResetTimer(WHITEMANE_ACTION_HOLY_SMITE, urand(3500, 5000));
                DisableCombatAction(action);
                return;
            }
        }
    }

/*     void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if(m_bDidResurrect)
        {
            if(m_uiResurrectWait_Timer < uiDiff)
            {
                m_creature->GetMotionMaster()->MoveChase(m_creature->GetVictim());
                m_bDidResurrect = false;
            }
            else
            {
                m_uiResurrectWait_Timer -= uiDiff;
            }
        }

        // Cast Deep sleep when health is less than 50%


        // while in "resurrect-mode", don't do anything
        if (m_bCanResurrect)
            return;

        // If we are <75% hp cast healing spells at self or Mograine
        

        // m_uiPowerWordShield_Timer


        // m_uiHolySmite_Timer




        //DoMeleeAttackIfReady();
    } */
};

void AddSC_boss_mograine_and_whitemane()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "boss_scarlet_commander_mograine";
    pNewScript->GetAI = &GetNewAIInstance<boss_scarlet_commander_mograineAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "boss_high_inquisitor_whitemane";
    pNewScript->GetAI = &GetNewAIInstance<boss_high_inquisitor_whitemaneAI>;
    pNewScript->RegisterSelf();
}

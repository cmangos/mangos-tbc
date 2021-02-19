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

struct boss_scarlet_commander_mograineAI : public ScriptedAI
{
    boss_scarlet_commander_mograineAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiCrusaderStrike_Timer;
    uint32 m_uiHammerOfJustice_Timer;

    bool m_bHasDied;
    bool m_bHeal;
    bool m_bFakeDeath;

    void Reset() override
    {
        m_uiCrusaderStrike_Timer  = 8400;
        m_uiHammerOfJustice_Timer = 9600;

        m_bHasDied                = false;
        m_bHeal                   = false;
        m_bFakeDeath              = false;

        // Incase wipe during phase that mograine fake death
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        SetDeathPrevention(true);
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (!m_pInstance)
            return;

        if (m_pInstance->GetData(TYPE_ASHBRINGER_EVENT) == IN_PROGRESS)
        {
            if (pWho->GetTypeId() == TYPEID_PLAYER)
            {
                Player* player = static_cast<Player*>(pWho);
                if (player->HasItemOrGemWithIdEquipped(ITEM_CORRUPTED_ASHBRINGER, 1) && m_creature->IsWithinDist(player, 20.0f))
                {
                    player->GetMap()->ScriptsStart(sRelayScripts, ASHBRINGER_RELAY_SCRIPT_ID, m_creature, player);
                    m_pInstance->SetData(TYPE_ASHBRINGER_EVENT, DONE);
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
        if (!m_pInstance)
            return;

        Creature* pWhitemane = m_pInstance->GetSingleCreatureFromStorage(NPC_WHITEMANE);
        if (pWhitemane && !pWhitemane->IsAlive()){
            if (!(m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED) || !(m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
                m_pInstance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, FAIL);
            pWhitemane->Respawn();
        }            
    }

    void JustPreventedDeath(Unit* /*attacker*/) override
    {
        if (!m_pInstance)
            return;

        if (Creature* pWhitemane = m_pInstance->GetSingleCreatureFromStorage(NPC_WHITEMANE))
        {
            m_pInstance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, IN_PROGRESS);

            pWhitemane->GetMotionMaster()->MovePoint(1, 1163.113370f, 1398.856812f, 32.527786f);
            pWhitemane->AI()->AttackStart(m_creature->GetVictim());

            m_creature->GetMotionMaster()->MovementExpired();
            m_creature->GetMotionMaster()->MoveIdle();

            if (m_creature->IsNonMeleeSpellCasted(false))
                m_creature->InterruptNonMeleeSpells(false);

            m_creature->ClearComboPointHolders();
            m_creature->RemoveAllAurasOnDeath();
            m_creature->ClearAllReactives();

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

            if (m_pInstance)
                m_pInstance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, SPECIAL);
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if (m_bHasDied && !m_bHeal && m_pInstance && m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == SPECIAL)
        {
            if (Creature* pWhitemane = m_pInstance->GetSingleCreatureFromStorage(NPC_WHITEMANE))
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
                    m_creature->SetPower(POWER_MANA, 0);
                }
                m_uiCrusaderStrike_Timer = 8400;
                m_uiHammerOfJustice_Timer = 9600;

                if (m_creature->GetVictim())
                    m_creature->GetMotionMaster()->MoveChase(m_creature->GetVictim());

                m_bHeal = true;
            }
        }

        // This if-check to make sure mograine does not attack while fake death
        if (m_bFakeDeath)
            return;

        if (m_bHasDied)
        {
            if(m_creature->GetHealthPercent()<33.3f)
            {
                DoCastSpellIfCan(m_creature, SPELL_DIVINESHIELD);
            }
        }

        // m_uiCrusaderStrike_Timer
        if (m_uiCrusaderStrike_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_CRUSADERSTRIKE) == CAST_OK)
                m_uiCrusaderStrike_Timer = urand(6000, 15000);
        }
        else
            m_uiCrusaderStrike_Timer -= uiDiff;

        // m_uiHammerOfJustice_Timer
        if (m_uiHammerOfJustice_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_HAMMEROFJUSTICE) == CAST_OK)
                m_uiHammerOfJustice_Timer = urand(7000, 18500);
        }
        else
            m_uiHammerOfJustice_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

struct boss_high_inquisitor_whitemaneAI : public ScriptedAI
{
    boss_high_inquisitor_whitemaneAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 m_uiHeal_Timer;
    uint32 m_uiPowerWordShield_Timer;
    uint32 m_uiHolySmite_Timer;
    uint32 m_uiWait_Timer;
    uint32 m_uiResurrectWait_Timer;

    bool m_bCanResurrectCheck;
    bool m_bCanResurrect;
    bool m_bDidResurrect;

    void Reset() override
    {
        m_uiWait_Timer            = 7000;
        m_uiHeal_Timer            = 10000;
        m_uiPowerWordShield_Timer = 15000;
        m_uiHolySmite_Timer       = 4000;
        m_uiResurrectWait_Timer   = 2200;

        m_bCanResurrectCheck      = false;
        m_bCanResurrect           = false;
        m_bDidResurrect           = false;

        if (!m_pInstance)
            return;

        if (Creature* pMograine = m_pInstance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
        {
            if (m_creature->IsAlive() && !pMograine->IsAlive())
                pMograine->Respawn();
        }

        SetDeathPrevention(true);
    }

    void JustReachedHome() override
    {
        if (m_pInstance)
        {
            if (!(m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED) || !(m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
                m_pInstance->SetData(TYPE_MOGRAINE_AND_WHITE_EVENT, FAIL);
        }
    }

    void MoveInLineOfSight(Unit* /*pWho*/) override
    {
        // This needs to be empty because Whitemane should NOT aggro while fighting Mograine. Mograine will give us a target.
    }

    void AttackStart(Unit* pWho) override
    {
        if (m_pInstance && (m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == NOT_STARTED || m_pInstance->GetData(TYPE_MOGRAINE_AND_WHITE_EVENT) == FAIL))
            return;

        ScriptedAI::AttackStart(pWho);
    }

    void MovementInform(uint32 uiMotionType, uint32 uiPointId) override
    {
        if (uiMotionType == POINT_MOTION_TYPE && uiPointId == 2)
            if(m_pInstance)
                if (Creature* pMograine = m_pInstance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
                    m_creature->SetFacingToObject(pMograine);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        DoScriptText(SAY_WH_INTRO, m_creature);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        DoScriptText(SAY_WH_KILL, m_creature);
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if (m_bCanResurrect)
        {
            // When casting resuruction make sure to delay so on rez when reinstate battle deepsleep runs out
            m_creature->AttackStop(true);
            if (m_uiWait_Timer < uiDiff)
            {
                if (Creature* pMograine = m_pInstance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
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
                SetDeathPrevention(false);
            }
            else
            {
                m_uiWait_Timer -= uiDiff;
            }
        }

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
        if (!m_bCanResurrectCheck && m_creature->GetHealthPercent() <= 50.0f)
        {
            DoCastSpellIfCan(m_creature, SPELL_DEEPSLEEP, CAST_INTERRUPT_PREVIOUS);
            m_bCanResurrectCheck = true;
            m_bCanResurrect = true;
            if (Creature* pMograine = m_pInstance->GetSingleCreatureFromStorage(NPC_MOGRAINE))
            {
                SetCombatMovement(false);
                m_creature->AttackStop(true);
                float fX, fY, fZ;
                pMograine->GetContactPoint(m_creature, fX, fY, fZ, INTERACTION_DISTANCE);
                m_creature->GetMotionMaster()->Clear();
                m_creature->GetMotionMaster()->MovePoint(2, fX, fY, fZ, FORCED_MOVEMENT_RUN);
            }
            return;
        }

        // while in "resurrect-mode", don't do anything
        if (m_bCanResurrect)
            return;

        // If we are <75% hp cast healing spells at self or Mograine
        if (m_uiHeal_Timer < uiDiff)
        {
            if (Unit* pTarget = DoSelectLowestHpFriendly(50.0f))
            {
                if (DoCastSpellIfCan(pTarget, SPELL_HEAL) == CAST_OK)
                    m_uiHeal_Timer = 13000;
            }
        }
        else
            m_uiHeal_Timer -= uiDiff;

        // m_uiPowerWordShield_Timer
        if (m_uiPowerWordShield_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature, SPELL_POWERWORDSHIELD) == CAST_OK)
                m_uiPowerWordShield_Timer = urand(22000, 45000);
        }
        else
            m_uiPowerWordShield_Timer -= uiDiff;

        // m_uiHolySmite_Timer
        if (m_uiHolySmite_Timer < uiDiff)
        {
            if (DoCastSpellIfCan(m_creature->GetVictim(), SPELL_HOLYSMITE) == CAST_OK)
                m_uiHolySmite_Timer = urand(3500, 5000);
        }
        else
            m_uiHolySmite_Timer -= uiDiff;

        DoMeleeAttackIfReady();
    }
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

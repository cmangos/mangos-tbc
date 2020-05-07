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
    SPELL_PUMMEL            = 15615,
    SPELL_ENRAGE            = 30485,

    MOB_FEL_ORC             = 17083
};

struct mob_shattered_hand_legionnairAI : public ScriptedAI
{
    mob_shattered_hand_legionnairAI(Creature* pCreature) : ScriptedAI(pCreature) 
    {
        Reset();
    }

    uint32 m_uiPummelTimmer;
    uint32 m_uiAuraTimer;

    void Reset() override
    {
        // m_creature->CastSpell(m_creature, SPELL_AURA_OF_DISCIPLIN, TRIGGERED_NONE);
        m_uiPummelTimmer = 15000;
        m_uiAuraTimer = 15000;
    }

    void ReceiveAIEvent(AIEventType eventType, Unit* pSender, Unit* pInvoker, uint32 /*miscValue*/) override
    {
        // Nearby creatue died
        if (eventType == AI_EVENT_CUSTOM_EVENTAI_B)         
            m_creature->CastSpell(m_creature, SPELL_ENRAGE, TRIGGERED_NONE);           
    }   

    void UpdateAI(const uint32 uiDiff) override
    {
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
            m_creature->CastSpell(m_creature, SPELL_ENRAGE, TRIGGERED_NONE);
            m_uiAuraTimer = 15000;
        }
        else
            m_uiAuraTimer -= uiDiff;

        if (m_creature->GetHealthPercent() <= 30.0f)
            m_creature->CastSpell(m_creature, SPELL_AURA_OF_DISCIPLIN, TRIGGERED_NONE);

        DoMeleeAttackIfReady();
    }
};

UnitAI* GetAI_mob_shattered_hand_legionnair(Creature* pCreature)
{
    return new mob_shattered_hand_legionnairAI(pCreature);
}

void AddSC_shattered_halls()
{
    Script* pNewScript = new Script;
    pNewScript = new Script;
    pNewScript->Name = "mob_shattered_hand_legionnair";
    pNewScript->GetAI = &GetAI_mob_shattered_hand_legionnair;
    pNewScript->RegisterSelf();
}
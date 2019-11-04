#include "AI/ScriptDevAI/include/precompiled.h"

enum
{
    // List of text id's. The text is stored in database, also in a localized version
    // (if translation not exist for the textId, default english text will be used)
    TEXT_P1 = -1080001,
    TEXT_P2 = -1080002,
    TEXT_P3 = -1080003,

    // List of used spells
    SPELL_ONE_P1     = 17274,
    SPELL_ONE_P1_ALT = 17145,
    SPELL_TWO_P1     = 29964,
    SPELL_THREE_P1   = 16390,
    SPELL_ONE_P2     = 11,
    SPELL_ONE_P2_ALT = 22643,
    SPELL_TWO_P2     = 20681,
    SPELL_THREE_P2   = 11426,
    SPELL_ONE_P3     = 15735,
    SPELL_ONE_P3_ALT = 11975,
    SPELL_TWO_P3     = 228,
    SPELL_THREE_P3   = 29960,
};

struct boss_pomelomageAI : public ScriptedAI
{
    // *** HANDLED FUNCTION ***
    // This is the constructor, called only once when the creature is first created
    boss_pomelomageAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    // *** CUSTOM VARIABLES ****
    // These variables are for use only by this individual script.
    // Nothing else will ever call them but us.

    uint32 m_uiSpellOneTimer;                               // Timer for spell 1 when in combat
    uint32 m_uiSpellTwoTimer;                               // Timer for spell 1 when in combat
    uint32 m_uiSpellThreeTimer;                             // Timer for spell 1 when in combat
    uint32 m_uiPhase;                                       // The current battle phase we are in

    // *** HANDLED FUNCTION ***
    // This is called whenever the core decides we need to evade
    void Reset() override
    {
        m_uiPhase = 1;                                      // Start in phase 1
        m_uiSpellOneTimer = 8000;                           
        m_uiSpellTwoTimer = 37000;                          
        m_uiSpellThreeTimer = 19000;                        
    }

    // *** HANDLED FUNCTION ***
    // Aggro is called when we enter combat, against an enemy, and haven't been in combat before
    void Aggro(Unit* pWho) override
    {
        // Say some stuff
        DoScriptText(TEXT_P1, m_creature);
    }

    // *** HANDLED FUNCTION ***
    // Update AI is called Every single map update (roughly once every 100ms if a player is within the grid)
    void UpdateAI(const uint32 uiDiff) override
    {        
        // Return since we have no target
        if (!m_creature->SelectHostileTarget() || !m_creature->getVictim())
            return;

        if (m_creature->GetHealthPercent() > 60.0f)
        {
            m_uiPhase = 1;
        }
        else if (m_creature->GetHealthPercent() > 30.0f)
        {
            if (m_uiPhase != 2)
                DoScriptText(TEXT_P2, m_creature);
            m_uiPhase = 2;
        }
        else
        {
            if (m_uiPhase != 3)
                DoScriptText(TEXT_P3, m_creature);
            m_uiPhase = 3;
        }

        if (m_uiPhase == 1)
        {
            // Spell Three timer
            if (m_uiSpellThreeTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_THREE_P1) == CAST_OK)
                    m_uiSpellThreeTimer = 37 * IN_MILLISECONDS;   // Only Update Timer, if we could start casting
            }
            else
                m_uiSpellThreeTimer -= uiDiff;

            // Spell Two timer
            if (m_uiSpellTwoTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_TWO_P1) == CAST_OK)
                    m_uiSpellTwoTimer = 19 * IN_MILLISECONDS;   // Only Update Timer, if we could start casting
            }
            else
                m_uiSpellTwoTimer -= uiDiff;

            // Spell One timer
            if (m_uiSpellOneTimer < uiDiff)
            {
                if (Unit * pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(pUnit, SPELL_ONE_P1);
                else
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ONE_P1_ALT);

                m_uiSpellOneTimer = 8000;
            }
            else
                m_uiSpellOneTimer -= uiDiff;
        }
        else if (m_uiPhase == 2)
        {
            // Spell Three timer
            if (m_uiSpellThreeTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_THREE_P2) == CAST_OK)
                    m_uiSpellThreeTimer = 37 * IN_MILLISECONDS;   // Only Update Timer, if we could start casting
            }
            else
                m_uiSpellThreeTimer -= uiDiff;

            // Spell Two timer
            if (m_uiSpellTwoTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature->getVictim(), SPELL_TWO_P2) == CAST_OK)
                    m_uiSpellTwoTimer = 19 * IN_MILLISECONDS;   // Only Update Timer, if we could start casting
            }
            else
                m_uiSpellTwoTimer -= uiDiff;

            // Spell One timer
            if (m_uiSpellOneTimer < uiDiff)
            {
                // Cast spell one on our current target.
                if (Unit * pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(pUnit, SPELL_ONE_P2);
                else
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ONE_P2_ALT);

                m_uiSpellOneTimer = 2500;
            }
            else
                m_uiSpellOneTimer -= uiDiff;
        }
        else
        {
            // Spell Three timer
            if (m_uiSpellThreeTimer < uiDiff)
            {
                if (DoCastSpellIfCan(m_creature, SPELL_THREE_P3) == CAST_OK)
                    m_uiSpellThreeTimer = 37 * IN_MILLISECONDS;   // Only Update Timer, if we could start casting
            }
            else
                m_uiSpellThreeTimer -= uiDiff;

            // Spell Two timer
            if (m_uiSpellTwoTimer < uiDiff)
            {
                DoCastSpellIfCan(m_creature->getVictim(), SPELL_TWO_P3);
                if (Unit * pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(pUnit, SPELL_TWO_P3);
                if (Unit * pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(pUnit, SPELL_TWO_P3);
                m_uiSpellTwoTimer = 19 * IN_MILLISECONDS;
            }
            else
                m_uiSpellTwoTimer -= uiDiff;

            // Spell One timer
            if (m_uiSpellOneTimer < uiDiff)
            {
                // Cast spell one on our current target.
                if (Unit* pUnit = m_creature->SelectAttackingTarget(ATTACKING_TARGET_RANDOM, 0, nullptr, SELECT_FLAG_PLAYER))
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ONE_P3);
                else
                    DoCastSpellIfCan(m_creature->getVictim(), SPELL_ONE_P3_ALT);

                m_uiSpellOneTimer = 6000;
            }
            else
                m_uiSpellOneTimer -= uiDiff;

        }

        DoMeleeAttackIfReady();
    }
};

UnitAI* GetAI_boss_pomelomage(Creature* pCreature)
{
    return new boss_pomelomageAI(pCreature);
}

void AddSC_boss_pomelomage()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "boss_pomelomage";
    pNewScript->GetAI = &GetAI_boss_pomelomage;
    pNewScript->RegisterSelf(false);
}

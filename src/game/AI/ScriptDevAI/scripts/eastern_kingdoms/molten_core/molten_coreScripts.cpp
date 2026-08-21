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
SDName: Molten_Core
SD%Complete:
SDComment:
SDCategory: Molten Core
EndScriptData */

/* ContentData
EndContentData */

#include "AI/EventAI/CreatureEventAI.h"
#include "AI/ScriptDevAI/include/sc_common.h"
#include "molten_core.h"

/*######
## go_molten_core_rune
######*/

bool GOUse_go_molten_core_rune(Player* /*pPlayer*/, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return true;

    for (uint8 i = 0; i < MAX_MOLTEN_RUNES; ++i)
    {
        if (pGo->GetEntry() == m_aMoltenCoreRunes[i].m_uiRuneEntry)
        {
            // check if boss is already dead - if not return true
            if (pInstance->GetData(m_aMoltenCoreRunes[i].m_uiType) != DONE)
                return true;

            pInstance->SetData(m_aMoltenCoreRunes[i].m_uiType, SPECIAL);
            return false;
        }
    }

    return true;
}

struct npc_core_hound : public CreatureEventAI
{
    enum CoreHoundMoltenCore
    {
        REIGNITE_TIMER          = 0,

        SPELL_FULL_HEAL         = 17683,
        SPELL_FIRE_NOVA_VISUAL  = 19823,
        SPELL_PACIFY_SELF       = 19951,

        NPC_CORE_HOUND = 11671,

        EMOTE_SMOLDER   = 7866,
        EMOTE_REIGNITE  = 7867,
    };

    npc_core_hound(Creature* creature) : CreatureEventAI(creature)
    {
        SetDeathPrevention(true);
        AddCustomAction(REIGNITE_TIMER, true, [this] { HandleReigniteTimer(); });
    }

    void Reset() override
    {
        CreatureEventAI::Reset();
        SetDeathPrevention(true);
    }

    // Reignite, exiting a fake death.
    void Reignite()
    {
        m_creature->SetStandState(UNIT_STAND_STATE_STAND);
        m_creature->RemoveAurasDueToSpell(SPELL_PACIFY_SELF);
        DoCastSpellIfCan(nullptr, SPELL_FULL_HEAL, CAST_TRIGGERED);
        DoResetThreat();
        SetCombatMovement(true);

        SetDeathPrevention(true);

        DoBroadcastText(EMOTE_REIGNITE, m_creature); // %s reignites from the heat of another Core Hound!
    }

    // Collapse, entering a fake death.
    // Notes:
    // * You can still target a collapsed Core Hound.
    // * You can still damage a collapsed Core Hound.
    // * They keep debuffs (Curse of the Elements, Sunders, etc).
    // To do:
    // * Confirm they keep combo points.
    void Collapse()
    {
        DoBroadcastText(EMOTE_SMOLDER, m_creature); // %s collapses and begins to smolder.

        ResetTimer(REIGNITE_TIMER, 10000);

        DoCastSpellIfCan(nullptr, SPELL_PACIFY_SELF, CAST_TRIGGERED);

        m_creature->SetTarget(nullptr);
        SetCombatMovement(false);
        m_creature->SetStandState(UNIT_STAND_STATE_DEAD);
    }

    void JustPreventedDeath(Unit* /*attacker*/) override
    {
        Collapse();
    }

    void HandleReigniteTimer()
    {
        // Reignite if there are still other core hounds alive 10 seconds after the collapse.
        std::list<Creature*> coreHounds;
        GetCreatureListWithEntryInGrid(coreHounds, m_creature, NPC_CORE_HOUND, 40.0f);
        for (Creature* coreHound : coreHounds)
        {
            // Ignore alive core hounds in groups not in combat with us.
            if (coreHound && coreHound->IsInCombat() && coreHound->GetHealth() > 1)
            {
                Reignite();
                DoCastSpellIfCan(nullptr, SPELL_FIRE_NOVA_VISUAL, CAST_TRIGGERED);
                return;
            }
        }

        // No other core hounds alive: really die (and despawn the corpse).
        m_creature->Suicide();
        m_creature->ForcedDespawn();
    }
};

void AddSC_molten_core()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "go_molten_core_rune";
    pNewScript->pGOUse = &GOUse_go_molten_core_rune;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_core_hound";
    pNewScript->GetAI = &GetNewAIInstance<npc_core_hound>;
    pNewScript->RegisterSelf();
}

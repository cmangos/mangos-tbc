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
SDName: Teldrassil
SD%Complete: 100
SDComment: Quest support: 938
SDCategory: Teldrassil
EndScriptData */

/* ContentData
npc_mist
EndContentData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "AI/ScriptDevAI/base/follower_ai.h"

/*####
# npc_mist
####*/

enum
{
    QUEST_MIST              = 938,
    NPC_ARYNIA              = 3519,
    FACTION_DARNASSUS       = 10
};

enum MistsActions
{
    MIST_FINISH,
    MIST_ACTION_MAX,
};

struct npc_mistAI : public FollowerAI
{
    npc_mistAI(Creature* creature) : FollowerAI(creature, MIST_ACTION_MAX) 
    { 
        Reset(); 
        AddCustomAction(MIST_FINISH, true, [&]() { DoCompleteQuestEvent(); });
    }

    void Reset() override { }

    void MoveInLineOfSight(Unit* who) override
    {
        FollowerAI::MoveInLineOfSight(who);

        if (!HasFollowState(STATE_FOLLOW_COMPLETE) && who->GetEntry() == NPC_ARYNIA)
        {
            if (m_creature->IsWithinDistInMap(who, 10.0f))
            {
                // Stop Movement
                SetFollowComplete(true);                
                // Start RP inside DB
                m_creature->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_A, m_creature, who);
                // 2 Seconds Delay before Quest gets completed
                ResetTimer(MIST_FINISH, 2000);
            }
        }
    }

    void DoCompleteQuestEvent()
    {
        if (Player* player = GetLeaderForFollower())
        {
            if (player->GetQuestStatus(QUEST_MIST) == QUEST_STATUS_INCOMPLETE)
                player->RewardPlayerAndGroupAtEventExplored(QUEST_MIST, m_creature);
        }
    }

    void UpdateFollowerAI(const uint32 uiDiff) override 
    {
       // UpdateTimers(uiDiff, m_creature->IsInCombat());

        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

bool QuestAccept_npc_mist(Player* player, Creature* creature, const Quest* quest)
{
    if (quest->GetQuestId() == QUEST_MIST)
    {
        creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC | UNIT_FLAG_IMMUNE_TO_PLAYER);

        if (npc_mistAI* pMistAI = dynamic_cast<npc_mistAI*>(creature->AI()))
            pMistAI->StartFollow(player, FACTION_DARNASSUS, quest);
    }

    return true;
}

void AddSC_teldrassil()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_mist";
    pNewScript->GetAI = &GetNewAIInstance<npc_mistAI>;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_mist;
    pNewScript->RegisterSelf();
}

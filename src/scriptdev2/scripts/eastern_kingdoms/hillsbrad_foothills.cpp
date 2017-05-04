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
SDName: Hillsbrad Foothills
SD%Complete: 100
SDComment: Quest support: 1713
SDCategory: Hillsbrad Foothills
EndScriptData */

/* ContentData
npc_bathrah_the_windwatcher
EndContentData */

#include "precompiled.h"
#include "escort_ai.h"

/*######
## npc_bathrah_the_windwatcher:6176
######*/

enum
{
    SAY_PROGRESS_1 = -1800002,
    SAY_PROGRESS_2 = -1800003,
    SPELL_SUMMON_CYCLONIAN = 8606,
    QUEST_THE_SUMMONING = 1713
};

struct npc_bathrah_the_windwatcherAI : public npc_escortAI
{
    npc_bathrah_the_windwatcherAI(Creature* pCreature) : npc_escortAI(pCreature) { Reset(); }

    void Reset() override { }

    void WaypointReached(uint32 uiPointId) override
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch (uiPointId)
        {
            case 0:
                pPlayer->GroupEventHappens(QUEST_THE_SUMMONING, m_creature);
                SetRun();
                break;
            case 5:
                SetRun(false);
                break;
            case 6:
                m_creature->SetFacingTo(5.85258532f);
                break;
            case 7:
                DoScriptText(SAY_PROGRESS_2, m_creature, pPlayer);
                m_creature->CastSpell(m_creature, SPELL_SUMMON_CYCLONIAN, TRIGGERED_NONE);
                break;
            case 13:
                SetRun(false);
                break;
        }
    }

    void WaypointStart(uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 8:
                SetRun();
            break;
        }
    }
 
    void JustSummoned(Creature* pSummoned) override
    {
        if (Player* pPlayer = GetPlayerForEscort())
            pSummoned->AI()->AttackStart(pPlayer);
    }
};

bool QuestAccept_npc_bathrah_the_windwatcher(Player* pPlayer, Creature* pCreature, const Quest* pQuest)
{
    if (pQuest->GetQuestId() == QUEST_THE_SUMMONING)
    {
        DoScriptText(SAY_PROGRESS_1, pCreature, pPlayer);

        if (npc_bathrah_the_windwatcherAI* pEscortAI = dynamic_cast<npc_bathrah_the_windwatcherAI*>(pCreature->AI()))
            pEscortAI->Start(false, pPlayer, pQuest, true);
    }
    return true;
}

CreatureAI* GetAI_npc_bathrah_the_windwatcher(Creature* pCreature)
{
    return new npc_bathrah_the_windwatcherAI(pCreature);
}

void AddSC_hillsbrad_foothills()
{
    Script* pNewScript;

    pNewScript = new Script;
    pNewScript->Name = "npc_bathrah_the_windwatcher";
    pNewScript->GetAI = &GetAI_npc_bathrah_the_windwatcher;
    pNewScript->pQuestAcceptNPC = &QuestAccept_npc_bathrah_the_windwatcher;
    pNewScript->RegisterSelf();
}

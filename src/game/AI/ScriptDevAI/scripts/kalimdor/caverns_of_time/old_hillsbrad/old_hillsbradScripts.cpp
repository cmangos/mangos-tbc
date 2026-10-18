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
SDName: Old_Hillsbrad
SD%Complete: 90
SDComment: Quest support: 10283, 10284. All friendly NPC's. Thrall escort event is complete, possible a few details are still missing.
SDCategory: Caverns of Time, Old Hillsbrad Foothills
EndScriptData */

/* ContentData
npc_erozion
npc_thrall_old_hillsbrad
npc_taretha
EndContentData */

#include "AI/ScriptDevAI/include/sc_common.h"
#include "old_hillsbrad.h"
#include "AI/ScriptDevAI/base/escort_ai.h"
#include "AI/EventAI/CreatureEventAI.h"

/*######
## npc_erozion
######*/

enum
{
    GOSSIP_ITEM_NEED_BOMBS          = -3560001,
    TEXT_ID_DEFAULT                 = 9778,
    TEXT_ID_GOT_ITEM                = 9515,

    ITEM_ENTRY_BOMBS                = 25853,
};

bool GossipHello_npc_erozion(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    ScriptedInstance* pInstance = (ScriptedInstance*)pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_BARREL_DIVERSION) != DONE && !pPlayer->HasItemCount(ITEM_ENTRY_BOMBS, 1))
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_NEED_BOMBS, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    // Need info, should have option to teleport or not
    if (pInstance && pInstance->GetData(TYPE_EPOCH) == DONE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, "Take me back to my time.", GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->SEND_GOSSIP_MENU(TEXT_ID_DEFAULT, pCreature->GetObjectGuid());

    return true;
}

bool GossipSelect_npc_erozion(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        if (Item* pItem = pPlayer->StoreNewItemInInventorySlot(ITEM_ENTRY_BOMBS, 1))
            pPlayer->SendNewItem(pItem, 1, true, false);

        pPlayer->SEND_GOSSIP_MENU(TEXT_ID_GOT_ITEM, pCreature->GetObjectGuid());
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
        pPlayer->CLOSE_GOSSIP_MENU();

    return true;
}

/*######
## npc_thrall_old_hillsbrad
######*/

enum
{
    // Thrall texts - misc
    SAY_TH_RANDOM_LOW_HP1           = 17610,
    SAY_TH_RANDOM_LOW_HP2           = 17611,

    SAY_TH_RANDOM_DIE1              = 17612,
    SAY_TH_RANDOM_DIE2              = 17613,

    SAY_TH_RANDOM_AGGRO1            = 17600,
    SAY_TH_RANDOM_AGGRO2            = 17601,
    SAY_TH_RANDOM_AGGRO3            = 17602,
    SAY_TH_RANDOM_AGGRO4            = 17603,

    SAY_TH_RANDOM_KILL1             = 17604,
    SAY_TH_RANDOM_KILL2             = 17605,
    SAY_TH_RANDOM_KILL3             = 17606,

    SAY_TH_LEAVE_COMBAT1            = 17607,
    SAY_TH_LEAVE_COMBAT2            = 17608,
    SAY_TH_LEAVE_COMBAT3            = 17609,

    // reset texts
    SAY_ERONZION_RESET_THRALL       = 16729,
    SAY_ERONZION_RESET_LAST         = 16731,

    GOSSIP_START = 7499,
};

enum ThrallActions
{
    THRALL_ACTION_MAX,
    THRALL_LOW_HEALTH
};


struct npc_thrall_old_hillsbradAI : public npc_escortAI
{
    npc_thrall_old_hillsbradAI(Creature* pCreature) : npc_escortAI(pCreature)
    {
        m_pInstance = (instance_old_hillsbrad*)pCreature->GetInstanceData();
        Reset();
        AddTimerlessCombatAction(THRALL_LOW_HEALTH, true);
    }

    instance_old_hillsbrad* m_pInstance;


    void Reset() override
    {      
            
    }

    void EnterCombat(Unit* enemy) override
    {
        npc_escortAI::EnterCombat(enemy);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        switch (urand(0, 3))
        {
            case 0: DoBroadcastText(SAY_TH_RANDOM_AGGRO1, m_creature); break;
            case 1: DoBroadcastText(SAY_TH_RANDOM_AGGRO2, m_creature); break;
            case 2: DoBroadcastText(SAY_TH_RANDOM_AGGRO3, m_creature); break;
            case 3: DoBroadcastText(SAY_TH_RANDOM_AGGRO4, m_creature); break;
        }
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        switch (urand(0, 2))
        {
            case 0: DoBroadcastText(SAY_TH_RANDOM_KILL1, m_creature); break;
            case 1: DoBroadcastText(SAY_TH_RANDOM_KILL2, m_creature); break;
            case 2: DoBroadcastText(SAY_TH_RANDOM_KILL3, m_creature); break;
        }
    }

    void JustDied(Unit* /*pKiller*/) override
    {        
    }

    void CorpseRemoved(uint32& uiRespawnDelay) override
    {
    }

    void JustRespawned() override
    {
        npc_escortAI::JustRespawned();        
    }

    void JustReachedHome() override 
    {       
        npc_escortAI::JustReachedHome();
    }

    void EnterEvadeMode() override
    {
        npc_escortAI::EnterEvadeMode();
    }

    void WaypointReached(uint32 uiPoint) override
    {
        if (!m_pInstance)
            return;
    }

    void UpdateAI(const uint32 uiDiff) override
    {        
    }

    void UpdateEscortAI(const uint32 uiDiff) override
    {  
        DoMeleeAttackIfReady();
    }

    void ExecuteAction(uint32 action) override
    {
        switch (action)
        {
            case THRALL_LOW_HEALTH: {
                if (m_creature->GetHealthPercent() < 20.0f)
                {
                    DoBroadcastText(urand(0, 1) ? SAY_TH_RANDOM_LOW_HP1 : SAY_TH_RANDOM_LOW_HP2, m_creature);
                    SetActionReadyStatus(action, false);
                }
                break;
            }
        }
    }
};

UnitAI* GetAI_npc_thrall_old_hillsbrad(Creature* pCreature)
{
    return new npc_thrall_old_hillsbradAI(pCreature);
}

bool GossipHello_npc_thrall_old_hillsbrad(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
    {
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());
        pPlayer->SendPreparedQuest(pCreature->GetObjectGuid());
    }

    return true;
}

bool GossipSelect_npc_thrall_old_hillsbrad(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    instance_old_hillsbrad* pInstance = (instance_old_hillsbrad*)pCreature->GetInstanceData();

    switch (uiAction)
    {
    }
    return true;
}

/*######
## npc_taretha
######*/

enum
{
    // end event texts and spells
    SAY_TA_FREE                     = 16082,
    SAY_TR_GLAD_SAFE                = 16083,
    SAY_TA_NEVER_MET                = 16085,
    SAY_TR_THEN_WHO                 = 16084,
    SAY_PRE_WIPE                    = 16086,
    SAY_WIPE_MEMORY                 = 16087,
    SAY_ABOUT_TARETHA               = 16088,
    SAY_TH_EVENT_COMPLETE           = 16089,
    SAY_TA_FAREWELL                 = 16090,

    GOSSIP_ITEM_EPOCH_1             = -3560005,             // "Strange wizard?"
    TEXT_ID_EPOCH_1                 = 9610,                 // Thank you for helping Thrall escape, friends. Now I only hope

    GOSSIP_ITEM_EPOCH_2             = -3560006,             // "We'll get you out. Taretha. Don't worry. I doubt the wizard would wander too far away."
    TEXT_ID_EPOCH_2                 = 9613,                 // Yes, friends. This man was no wizard of

    SPELL_TELEPORT                  = 7791,
    SPELL_MEMORY_WIPE               = 33336,                // hits Taretha and Thrall
    SPELL_MEMORY_WP_RESUME          = 33337,
    SPELL_SHADOW_PRISON             = 33071,                // in creature_template_addon - remove from Taretha on event complete
};

static const DialogueEntry aTarethaDialogue[] =
{
    {SAY_TA_FREE,           NPC_TARETHA,    4000, DIALOGUE_STEP_TEXT},
    {SAY_TR_GLAD_SAFE,      NPC_THRALL,     9000, DIALOGUE_STEP_TEXT},
    {SAY_TA_NEVER_MET,      NPC_TARETHA,    3000, DIALOGUE_STEP_TEXT},
    {SAY_TR_THEN_WHO,       NPC_THRALL,     6000, DIALOGUE_STEP_TEXT},
    {SPELL_MEMORY_WIPE,     0,              3000},
    {SAY_WIPE_MEMORY,       NPC_EROZION,    12000, DIALOGUE_STEP_TEXT},
    {SAY_ABOUT_TARETHA,     NPC_EROZION,    6000, DIALOGUE_STEP_TEXT},
    {SAY_TH_EVENT_COMPLETE, NPC_THRALL,     3000, DIALOGUE_STEP_TEXT},
    {NPC_THRALL,            0,              2000},
    {SAY_TA_FAREWELL,       NPC_TARETHA,    3000, DIALOGUE_STEP_TEXT},
    {NPC_TARETHA,           0,              0},
    {0, 0, 0},
};

struct npc_tarethaAI : public npc_escortAI, private DialogueHelper
{
    npc_tarethaAI(Creature* pCreature) : npc_escortAI(pCreature),
        DialogueHelper(aTarethaDialogue)
    {
        m_pInstance = (instance_old_hillsbrad*)pCreature->GetInstanceData();
        InitializeDialogueHelper(m_pInstance);
        Reset();
    }

    instance_old_hillsbrad* m_pInstance;

    bool m_bHasStartedEpilogue;

    void Reset() override
    {
        m_bHasStartedEpilogue = false;
    }

    void JustSummoned(Creature* pSummoned) override
    {
        // Remove flags from the npc - the quest will be handled by the entrance version
        if (pSummoned->GetEntry() == NPC_EROZION)
        {
            DoBroadcastText(SAY_PRE_WIPE, pSummoned);
            pSummoned->CastSpell(pSummoned, SPELL_TELEPORT, TRIGGERED_NONE);
            pSummoned->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP | UNIT_NPC_FLAG_QUESTGIVER);
        }
    }

    Creature* GetSpeakerByEntry(uint32 uiEntry) override
    {
        switch (uiEntry)
        {
            case NPC_TARETHA:                   return m_creature;
            case NPC_THRALL:                    return m_pInstance->GetSingleCreatureFromStorage(NPC_THRALL);
            case NPC_EROZION:                   return m_pInstance->GetSingleCreatureFromStorage(NPC_EROZION);
            default:                            return nullptr;
        }
    }

    void WaypointReached(uint32 uiPoint) override
    {
        if (uiPoint == 8)
        {
            StartNextDialogueText(SAY_TA_FREE);

            if (m_pInstance)
            {
                if (Creature* pThrall = m_pInstance->GetSingleCreatureFromStorage(NPC_THRALL))
                    pThrall->SetFacingToObject(m_creature);
            }

            m_creature->HandleEmote(EMOTE_ONESHOT_CHEER);
            SetEscortPaused(true);
            SetRun(false);
        }
    }

    void JustDidDialogueStep(int32 iEntry) override
    {
        if (!m_pInstance)
            return;

        switch (iEntry)
        {
            case SAY_TR_THEN_WHO:
                m_creature->SummonCreature(NPC_EROZION, 2646.47f, 680.416f, 55.38f, 4.16f, TEMPSPAWN_TIMED_DESPAWN, 5 * MINUTE * IN_MILLISECONDS);
                break;
            case SPELL_MEMORY_WIPE:
                if (Creature* pErozion = m_pInstance->GetSingleCreatureFromStorage(NPC_EROZION))
                    pErozion->CastSpell(pErozion, SPELL_MEMORY_WIPE, TRIGGERED_NONE);
                break;
            case SAY_TH_EVENT_COMPLETE:
                if (Creature* pErozion = m_pInstance->GetSingleCreatureFromStorage(NPC_EROZION))
                    pErozion->CastSpell(pErozion, SPELL_MEMORY_WP_RESUME, TRIGGERED_NONE);
                if (Creature* pThrall = m_pInstance->GetSingleCreatureFromStorage(NPC_THRALL))
                    pThrall->RemoveAurasDueToSpell(SPELL_MEMORY_WIPE);
                m_creature->RemoveAurasDueToSpell(SPELL_MEMORY_WIPE);
                break;
            case NPC_THRALL:
                if (Creature* pThrall = m_pInstance->GetSingleCreatureFromStorage(NPC_THRALL))
                {
                    if (npc_thrall_old_hillsbradAI* pThrallAI = dynamic_cast<npc_thrall_old_hillsbradAI*>(pThrall->AI()))
                        pThrallAI->SetEscortPaused(false);
                }
                break;
            case SAY_TA_FAREWELL:
                if (Creature* pThrall = m_pInstance->GetSingleCreatureFromStorage(NPC_THRALL))
                    m_creature->SetFacingToObject(pThrall);
                m_creature->HandleEmote(EMOTE_ONESHOT_WAVE);
                break;
            case NPC_TARETHA:
                if (Creature* pErozion = m_pInstance->GetSingleCreatureFromStorage(NPC_EROZION))
                    pErozion->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
                m_pInstance->SetData(TYPE_THRALL_EVENT, DONE);
                SetEscortPaused(false);
                break;
        }
    }

    void UpdateEscortAI(const uint32 uiDiff) override
    {
        DialogueUpdate(uiDiff);

        if (!m_bHasStartedEpilogue && m_pInstance)
        {
            // Start epilogue
            if (m_pInstance->GetData(TYPE_EPOCH) == DONE && m_pInstance->GetData(TYPE_THRALL_EVENT) != DONE)
            {
                m_creature->RemoveAurasDueToSpell(SPELL_SHADOW_PRISON);
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_UNINTERACTIBLE);
                m_creature->SetStandState(UNIT_STAND_STATE_STAND);

                Start(true);
                m_bHasStartedEpilogue = true;
            }
        }
    }
};

UnitAI* GetAI_npc_taretha(Creature* pCreature)
{
    return new npc_tarethaAI(pCreature);
}

bool GossipHello_npc_taretha(Player* pPlayer, Creature* pCreature)
{
    instance_old_hillsbrad* pInstance = (instance_old_hillsbrad*)pCreature->GetInstanceData();

    if (pInstance && pInstance->GetData(TYPE_ESCORT_INN) == DONE && pInstance->GetData(TYPE_EPOCH) != DONE)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH_1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);
        pPlayer->SEND_GOSSIP_MENU(TEXT_ID_EPOCH_1, pCreature->GetObjectGuid());
    }

    return true;
}

bool GossipSelect_npc_taretha(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    instance_old_hillsbrad* pInstance = (instance_old_hillsbrad*)pCreature->GetInstanceData();

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_EPOCH_2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 2);
        pPlayer->SEND_GOSSIP_MENU(TEXT_ID_EPOCH_2, pCreature->GetObjectGuid());
    }

    if (uiAction == GOSSIP_ACTION_INFO_DEF + 2)
    {
        pPlayer->CLOSE_GOSSIP_MENU();

        if (pInstance && pInstance->GetData(TYPE_THRALL_EVENT) == IN_PROGRESS)
        {
            pCreature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);

        }
    }

    return true;
}

enum
{
    BARTOLO_SAY_1 = 18137,
    BARTOLO_SAY_2 = 18138,
};

struct npc_bartolo_ginsetti : public ScriptedAI
{
    npc_bartolo_ginsetti(Creature* creature) : ScriptedAI(creature) { Reset(); }

    bool m_bCanStartScript;
    uint32 m_uiScriptCooldownTimer;
    uint32 m_uiSayTwoTimer;
    uint32 m_uiFlexTwoTimer;

    void Reset() override
    {
        m_uiScriptCooldownTimer = 0;
        m_uiSayTwoTimer         = 0;
        m_uiFlexTwoTimer        = 0;
        m_bCanStartScript       = true;
    }

    void StartScript(Player* player)
    {
        m_bCanStartScript = false;
        m_uiScriptCooldownTimer = 60000;
        m_uiFlexTwoTimer = 5000;
        m_uiSayTwoTimer = 8000;
        m_creature->HandleEmote(EMOTE_ONESHOT_POINT);
        DoBroadcastText(BARTOLO_SAY_1, m_creature, player);
    }

    void UpdateAI(const uint32 diff) override
    {
        if (m_uiScriptCooldownTimer)
        {
            if (m_uiScriptCooldownTimer < diff)
            {
                m_uiScriptCooldownTimer = 0;
                m_bCanStartScript = true;
            }
            else
                m_uiScriptCooldownTimer -= diff;
        }

        if (m_uiFlexTwoTimer)
        {
            if (m_uiFlexTwoTimer < diff)
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_FLEX);
                m_uiFlexTwoTimer = 0;
            }
            else
                m_uiFlexTwoTimer -= diff;
        }

        if (m_uiSayTwoTimer)
        {
            if (m_uiSayTwoTimer < diff)
            {
                m_creature->HandleEmote(EMOTE_ONESHOT_FLEX);
                DoBroadcastText(BARTOLO_SAY_2, m_creature);
                m_uiSayTwoTimer = 0;
            }
            else
                m_uiSayTwoTimer -= diff;
        }
    }
};

bool AreaTrigger_at_bartolo_ginsetti(Player* player, AreaTriggerEntry const* /*pAt*/)
{
    if (player->IsGameMaster() || !player->IsAlive())
        return false;

    instance_old_hillsbrad* instance = (instance_old_hillsbrad*)player->GetInstanceData();

    if (!instance)
        return false;

    if (Creature* bartolo = instance->GetSingleCreatureFromStorage(NPC_BARTOLO))
    {
        if (npc_bartolo_ginsetti* bartoloAI = dynamic_cast<npc_bartolo_ginsetti*>(bartolo->AI()))
        {
            if (bartoloAI->m_bCanStartScript)
            {
                bartolo->SetFacingToObject(player);
                bartoloAI->StartScript(player);
            }
        }
    }

    return true;
}

std::vector<uint32> beggarTexts = { 18148, 18149, 18150, 18151, 18152, 18153, 18154 };

bool AreaTrigger_at_beggar(Player* player, AreaTriggerEntry const* /*pAt*/)
{
    if (player->IsGameMaster() || !player->IsAlive())
        return false;

    instance_old_hillsbrad* instance = (instance_old_hillsbrad*)player->GetInstanceData();

    if (!instance)
        return false;

    TimePoint currentTime = player->GetMap()->GetCurrentClockTime();

    if (currentTime > instance->m_beggarScriptTime + std::chrono::seconds(5))
    {
        if (Creature* beggar = GetClosestCreatureWithEntry(player, NPC_BEGGAR, 25.f))
        {
            instance->m_beggarScriptTime = currentTime;
            beggar->HandleEmote(EMOTE_ONESHOT_BEG);
            DoBroadcastText(beggarTexts[urand(0, beggarTexts.size() - 1)], beggar, player);
        }
    }

    return true;
}

bool AreaTrigger_at_southshore_inn(Player* player, AreaTriggerEntry const* /*pAt*/)
{
    instance_old_hillsbrad* instance = (instance_old_hillsbrad*)player->GetInstanceData();
    if (Creature* mograine = instance->GetSingleCreatureFromStorage(NPC_COMMANDER_MOGRAINE))
        mograine->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_A, player, mograine);
    return true;
}

// 33133 - Transform
struct InfiniteTransform : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        Unit* unitTarget = spell->GetCaster();
        if (!unitTarget || !unitTarget->IsCreature())
            return;
        Creature* oldCreature = (Creature*)unitTarget;
        uint32 transformEntry = 0;
        // update entry based on current entry
        switch (oldCreature->GetEntry())
        {
            case 18092:
                transformEntry = 18170;
                break;
            case 18093:
                transformEntry = 18172;
                break;
            case 18094:
                transformEntry = 18171;
                break;
            default:
                return;
                break;
        }
        oldCreature->UpdateEntry(transformEntry);
        // init new EventAI
        if (oldCreature->GetAIName() == "EventAI")
        {
            CreatureEventAI* eventAI = static_cast<CreatureEventAI*>(oldCreature->AI());
            if (eventAI)
                eventAI->InitAI();
        }
    }
};

void AddSC_old_hillsbrad()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_erozion";
    pNewScript->pGossipHello = &GossipHello_npc_erozion;
    pNewScript->pGossipSelect = &GossipSelect_npc_erozion;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_thrall_old_hillsbrad";
    pNewScript->GetAI = &GetAI_npc_thrall_old_hillsbrad;
    pNewScript->pGossipHello = &GossipHello_npc_thrall_old_hillsbrad;
    pNewScript->pGossipSelect = &GossipSelect_npc_thrall_old_hillsbrad;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_taretha";
    pNewScript->GetAI = &GetAI_npc_taretha;
    pNewScript->pGossipHello = &GossipHello_npc_taretha;
    pNewScript->pGossipSelect = &GossipSelect_npc_taretha;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_bartolo_ginsetti";
    pNewScript->GetAI = &GetNewAIInstance<npc_bartolo_ginsetti>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_bartolo_ginsetti";
    pNewScript->pAreaTrigger = &AreaTrigger_at_bartolo_ginsetti;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_beggar";
    pNewScript->pAreaTrigger = &AreaTrigger_at_beggar;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "at_southshore_inn";
    pNewScript->pAreaTrigger = &AreaTrigger_at_southshore_inn;
    pNewScript->RegisterSelf();

    RegisterSpellScript<InfiniteTransform>("spell_infinite_transform");
}

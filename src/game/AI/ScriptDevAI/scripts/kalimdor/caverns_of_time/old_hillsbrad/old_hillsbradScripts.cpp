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
    GOSSIP_ENTRANCE = 7769,
    GOSSIP_FINISHED = 8391,
};

bool GossipHello_npc_erozion(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
        player->PrepareQuestMenu(creature->GetObjectGuid());

    if (creature->HasStringId("OHF_EROZION_ENTRANCE"))
    {
        player->PrepareGossipMenu(creature, GOSSIP_ENTRANCE, true);
        player->SendPreparedGossip(creature);
    }
    else if (creature->HasStringId("OHF_EROZION_TARRENMILL"))
    {
        player->PrepareGossipMenu(creature, GOSSIP_FINISHED);
        player->SendPreparedGossip(creature);
    }
    return true;
}

/*######
## npc_thrall_old_hillsbrad
######*/

enum
{
    // Thrall texts
    SAY_TH_RANDOM_LOW_HP1           = 17610,
    SAY_TH_RANDOM_LOW_HP2           = 17611,

    SAY_TH_RANDOM_DIE1              = 17612,
    SAY_TH_RANDOM_DIE2              = 17613,

    SAY_TH_RANDOM_KILL1             = 17604,
    SAY_TH_RANDOM_KILL2             = 17605,

    SPELL_SUMMON_EROZION_IMAGE      = 33954, // if thrall dies during escort

    GOSSIP_START = 7499,
    GOSSIP_SKARLOC_01 = 7830,
    GOSSIP_SKARLOC_02 = 7829,
    GOSSIP_SKARLOC_03 = 7831,
    GOSSIP_BARN = 7840,
    GOSSIP_INN = 7853,
    MODEL_SKARLOC_MOUNT = 8469,
};

static const int32 aRandomAggro[] = {17600, 17601, 17602, 17603};
static const int32 aRandomEvade[] = {17606, 17607, 17608, 17609};

enum ThrallActions
{
    THRALL_LOW_HEALTH,
    THRALL_ACTION_MAX,
};


struct npc_thrall_old_hillsbradAI : public npc_escortAI
{
    npc_thrall_old_hillsbradAI(Creature* creature) : npc_escortAI(creature, THRALL_ACTION_MAX), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {      
        AddTimerlessCombatAction(THRALL_LOW_HEALTH, true);
        m_Mounted = false;
        m_Wave = false;
        creature->SetActiveObjectState(true);
        Reset();
    }

    ScriptedInstance* m_instance;

    bool m_Mounted;
    bool m_Wave;

    void Reset() override
    {      
        if (m_Mounted)
        {
            m_creature->Mount(MODEL_SKARLOC_MOUNT);
            m_Mounted = false;
        }            
    }
    void ReceiveAIEvent(AIEventType eventType, Unit* /*sender*/, Unit* /*invoker*/, uint32 /*miscValue*/) override
    {
        // Next Wave spawned
        if (eventType == AI_EVENT_CUSTOM_A)
        {
            // We are in combat - new spawned wave should aggro us instantly
            if (m_creature->IsInCombat())
                m_creature->AI()->SendAIEventAround(AI_EVENT_CUSTOM_EVENTAI_F, m_creature, 0, 5000);
            // We are not in combat and not on evade let wave aggro 
            else if (!m_creature->IsInCombat() && !m_creature->GetCombatManager().IsInEvadeMode())
                m_creature->AI()->SendAIEventAround(AI_EVENT_CUSTOM_EVENTAI_F, m_creature, 1500, 50);
        }
    }

    void EnterCombat(Unit* enemy) override
    {
        if (m_creature->GetMountID())
        {
            m_creature->Unmount();
            m_Mounted = true;
        }
        npc_escortAI::EnterCombat(enemy);
    }

    void Aggro(Unit* /*pWho*/) override
    {
        if (urand(0, 4) == 0)
            DoBroadcastText(aRandomAggro[urand(0, 3)], m_creature);
    }

    void JustDied(Unit* /*killer*/) override
    {
        // fail, and relocation handled in instance script
        if (m_instance)
            m_instance->SetData(TYPE_THRALL_EVENT, FAIL);

        DoBroadcastText(urand(0, 1) ? SAY_TH_RANDOM_DIE1 : SAY_TH_RANDOM_DIE2, m_creature);
        DoCastSpellIfCan(m_creature, SPELL_SUMMON_EROZION_IMAGE, CAST_TRIGGERED);
    }

    void KilledUnit(Unit* /*pVictim*/) override
    {
        if (urand(0, 4) == 0)
            DoBroadcastText(urand(0, 1) ? SAY_TH_RANDOM_KILL1 : SAY_TH_RANDOM_KILL2, m_creature);
    }

    void JustReachedHome() override
    {
        // During Escort, everytime Thrall leaves combat he has a 20% chance to say some text before going to next waypoint
        if (HasEscortState(STATE_ESCORT_ESCORTING))
        {
            if (urand(0, 4) == 0)
                DoBroadcastText(aRandomEvade[urand(0, 3)], m_creature);

            if (m_Wave)
                m_creature->AI()->SendAIEventAround(AI_EVENT_CUSTOM_EVENTAI_F, m_creature, 1500, 50);            
        }
        npc_escortAI::JustReachedHome();
    }

    void JustRespawned() override
    {
        npc_escortAI::JustRespawned();

        if (!m_instance)
            return;

        // We died during Escort and respawned from instance 
        if (m_instance->GetData(TYPE_THRALL_EVENT) == IN_PROGRESS)
        {
            Start(true, nullptr, nullptr, false, false, THRALL_PATH_ID);
            SetEscortPaused(true);

            // check current states before fail and set current waypoint, everything else handled via DB
            if (m_instance->GetData(TYPE_ESCORT_INN) == DONE)
                SetCurrentWaypoint(81);
            else if (m_instance->GetData(TYPE_ESCORT_BARN) == DONE)
                SetCurrentWaypoint(48);
            else if (m_instance->GetData(TYPE_ESCORT_SKARLOC) == DONE)
                SetCurrentWaypoint(22);

            m_creature->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
    }

    // Wrapper to restart escort
    void DoRestartEscortMovement()
    {
        m_creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_NPC);
        SetEscortPaused(false);
    }

    void WaypointReached(uint32 uiPoint) override
    {
        if (!m_instance)
            return;

        switch (uiPoint)
        {
            // We reached Barn - everything else handled via DB
            case 48: 
                m_instance->SetData(TYPE_ESCORT_BARN, DONE);
                break;
            // We reached Taretha
            case 80:
                m_instance->SetData(TYPE_ESCORT_INN, DONE);
                break;
            // We are standing before Epoch Hunter - start waves
            case 86:
                m_Wave = true;
                m_instance->SetData(TYPE_EPOCH_WAVE, IN_PROGRESS);
                break;
            // Last Waypoint
            case 87:
                m_instance->SetData(TYPE_THRALL_EVENT, DONE);
                End();
                break;
        }
    }

    void ExecuteAction(uint32 action) override
    {
        switch (action)
        {
            case THRALL_LOW_HEALTH: 
            {
                if (m_creature->GetHealthPercent() < 35.0f)
                {
                    DoBroadcastText(urand(0, 1) ? SAY_TH_RANDOM_LOW_HP1 : SAY_TH_RANDOM_LOW_HP2, m_creature);
                    SetActionReadyStatus(action, false);
                }
                break;
            }
        }
    }
};

bool GossipHello_npc_thrall_old_hillsbrad(Player* player, Creature* creature)
{
    if (creature->isQuestGiver())
    {
        player->PrepareQuestMenu(creature->GetObjectGuid());
        player->SendPreparedQuest(creature->GetObjectGuid());
    }

    if (instance_old_hillsbrad* instance = (instance_old_hillsbrad*)creature->GetInstanceData())
    {
        // Inn Reached
        if (instance->GetData(TYPE_ESCORT_INN) == DONE)
        {
            player->PrepareGossipMenu(creature, GOSSIP_INN);
            player->SendPreparedGossip(creature);
        }
        // Barn Reached
        else if (instance->GetData(TYPE_ESCORT_BARN) == DONE)
        {
            player->PrepareGossipMenu(creature, GOSSIP_BARN);
            player->SendPreparedGossip(creature);
        }
        else if (instance->GetData(TYPE_ESCORT_SKARLOC) == DONE)
        {
            player->PrepareGossipMenu(creature, GOSSIP_SKARLOC_01);
            player->SendPreparedGossip(creature);
        }
        // Text gets always shown, GossipAction handled via condition
        else
        {
            player->PrepareGossipMenu(creature, GOSSIP_START, true);
            player->SendPreparedGossip(creature);
        }
    }
    return true;
}

bool GossipSelect_npc_thrall_old_hillsbrad(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
{
    instance_old_hillsbrad* instance = (instance_old_hillsbrad*)creature->GetInstanceData();

    switch (action)
    {
        case 100:
        {
            // Start Event and open Prison Door
            if (instance)
            {
                instance->SetData(TYPE_THRALL_EVENT, IN_PROGRESS);
                instance->DoUseDoorOrButton(GO_PRISON_DOOR);
            }
            if (npc_thrall_old_hillsbradAI* thrallAI = dynamic_cast<npc_thrall_old_hillsbradAI*>(creature->AI()))
                thrallAI->Start(true, player, nullptr, false, false, THRALL_PATH_ID);

            // Despawn 2 groups on the Bridge via EAI so they dont despawn if InCombat            
            if (std::vector<Creature*> const* bridgeSpecial = creature->GetMap()->GetCreatures("OHF_THRALL_BRIDGETRASH_DESPAWN"))
            {
                for (Creature* creature : *bridgeSpecial)
                    creature->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_A, creature, creature);
            }

            // Also set Worldstate condition to false so they dont respawn
            creature->GetMap()->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_THRALL_TRASH_RESPAWN, 1);

            return true;
        }
        case 101:
        {
            player->PrepareGossipMenu(creature, GOSSIP_SKARLOC_02);
            player->SendPreparedGossip(creature);
            return true;
        }
        case 102: 
        {
            player->PrepareGossipMenu(creature, GOSSIP_SKARLOC_03);
            player->SendPreparedGossip(creature);
            return true;
        }
        case 103: 
        {            
            if (instance)            
                instance->SetData(TYPE_ESCORT_BARN, IN_PROGRESS);            
            
            if (npc_thrall_old_hillsbradAI* thrallAI = dynamic_cast<npc_thrall_old_hillsbradAI*>(creature->AI()))
                thrallAI->DoRestartEscortMovement();

            return true;
        }
        case 104: 
        {
            if (instance)
                instance->SetData(TYPE_ESCORT_INN, IN_PROGRESS);

            if (npc_thrall_old_hillsbradAI* thrallAI = dynamic_cast<npc_thrall_old_hillsbradAI*>(creature->AI()))
                thrallAI->DoRestartEscortMovement();
            return true;
        }
    }
    return false;
}

/*######
## npc_taretha
######*/

enum
{
    GOSSIP_ITEM_EPOCH_1 = 7849,
    GOSSIP_ITEM_EPOCH_2 = 7852
};


struct npc_tarethaAI : public ScriptedAI
{
    npc_tarethaAI(Creature* creature) : ScriptedAI(creature), m_instance(static_cast<ScriptedInstance*>(creature->GetInstanceData()))
    {
        Reset();
    }

    ScriptedInstance* m_instance;


    void Reset() override
    {
    }
};

bool GossipSelect_npc_taretha(Player* player, Creature* creature, uint32 /*sender*/, uint32 action)
{
    instance_old_hillsbrad* instance = (instance_old_hillsbrad*)creature->GetInstanceData();

    switch (action)
    {
        case 100:      
        {
            player->PrepareGossipMenu(creature, GOSSIP_ITEM_EPOCH_2);
            player->SendPreparedGossip(creature);
            return true;
        }
        case 101:        
        {
            if (instance && instance->GetData(TYPE_THRALL_EVENT) == IN_PROGRESS)
            {
                creature->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
                creature->SetActiveObjectState(true);

                if (Creature* thrall = instance->GetSingleCreatureFromStorage(NPC_THRALL))
                {
                    if (npc_thrall_old_hillsbradAI* thrallAI = dynamic_cast<npc_thrall_old_hillsbradAI*>(thrall->AI()))
                        thrallAI->DoRestartEscortMovement();
                }

                // Despawn all enemy groups around this area
                if (std::vector<Creature*> const* epochSpecial = creature->GetMap()->GetCreatures("OHF_EPOCH_EVENT_DESPAWN"))
                {
                    for (Creature* creature : *epochSpecial)
                        creature->AI()->SendAIEvent(AI_EVENT_CUSTOM_EVENTAI_A, creature, creature);
                }
                // Also set Worldstate to prevent respawn
                creature->GetMap()->GetVariableManager().SetVariable(WORLD_STATE_OLD_HILLSBRAD_CUSTOM_TARREN_MILL_DESPAWN, 1);
            }
            return true;
        }
    }
    return false;
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
// 33937, 34016, 34023, 34024 - Stun Phase 2, 3, 4, 5 Units
struct StunPhaseUnits : public SpellScript
{
    void OnEffectExecute(Spell* spell, SpellEffectIndex /*effIdx*/) const override
    {
        Unit* caster = spell->GetCaster();
        Unit* target = spell->GetUnitTarget();
        if (!caster || !target || target == caster || !target->IsCreature())
            return;

        static_cast<Creature*>(target)->ForcedDespawn(3000);
        static_cast<Creature*>(target)->AI()->SetAIImmobilizedState(true);
    }

};

void AddSC_old_hillsbrad()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_erozion";
    pNewScript->pGossipHello = &GossipHello_npc_erozion;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_thrall_old_hillsbrad";
    pNewScript->GetAI = &GetNewAIInstance<npc_thrall_old_hillsbradAI>;
    pNewScript->pGossipHello = &GossipHello_npc_thrall_old_hillsbrad;
    pNewScript->pGossipSelect = &GossipSelect_npc_thrall_old_hillsbrad;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_taretha";
    pNewScript->GetAI = &GetNewAIInstance<npc_tarethaAI>;
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
    RegisterSpellScript<StunPhaseUnits>("spell_stun_phase_unit");
}

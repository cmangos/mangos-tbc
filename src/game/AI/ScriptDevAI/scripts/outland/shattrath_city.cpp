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
SDName: Shattrath_City
SD%Complete: 100
SDComment: Quest support: 10004, 10231.
SDCategory: Shattrath City
EndScriptData */

/* ContentData
npc_dirty_larry
npc_ishanah
npc_khadgars_servant
npc_salsalabim
EndContentData */

#include "AI/BaseAI/AIDefines.h"
#include "AI/ScriptDevAI/ScriptDevAIMgr.h"
#include "AI/ScriptDevAI/include/sc_common.h"
#include "AI/ScriptDevAI/base/escort_ai.h"
#include "AI/ScriptDevAI/include/sc_creature.h"
#include "Entities/Creature.h"
#include "Entities/Object.h"
#include "Entities/Unit.h"
#include "World/WorldState.h"
#include "AI/ScriptDevAI/base/TimerAI.h"
#include "Spells/Scripts/SpellScript.h"

enum
{
    SAY_START               = -1000274,
    EMOTE_KNUCKLES          = -1001242,
    SAY_COUNT               = -1000275,
    SAY_COUNT_1             = -1000276,
    SAY_COUNT_2             = -1000277,
    SAY_ATTACK              = -1000278,
    SAY_GIVEUP              = -1000279,
    QUEST_WHAT_BOOK         = 10231,
    ENTRY_CREEPJACK         = 19726,
    ENTRY_MALONE            = 19725,
    GOSSIP_ITEM_BOOK        = -3000105,
};

struct npc_dirty_larryAI : public ScriptedAI
{
    npc_dirty_larryAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_uiNpcFlags = pCreature->GetUInt32Value(UNIT_NPC_FLAGS);
        Reset();
    }

    uint32 m_uiNpcFlags;

    ObjectGuid m_creepjackGuid;
    ObjectGuid m_maloneGuid;
    ObjectGuid m_playerGuid;

    bool bEvent;
    bool bActiveAttack;

    uint32 m_uiSayTimer;
    uint32 m_uiStep;

    void Reset() override
    {
        m_creature->SetUInt32Value(UNIT_NPC_FLAGS, m_uiNpcFlags);

        m_playerGuid.Clear();
        m_creepjackGuid.Clear();
        m_maloneGuid.Clear();

        bEvent = false;
        bActiveAttack = false;

        m_uiSayTimer = 1000;
        m_uiStep = 0;

        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
    }

    void StartEvent(Player* pPlayer)
    {
        m_playerGuid = pPlayer->GetObjectGuid();

        m_creature->SetUInt32Value(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_NONE);

        m_creature->SetFacingToObject(pPlayer);

        if (Creature* pCreepjack = GetClosestCreatureWithEntry(m_creature, ENTRY_CREEPJACK, 20.0f))
        {
            m_creepjackGuid = pCreepjack->GetObjectGuid();
            pCreepjack->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        }

        if (Creature* pMalone = GetClosestCreatureWithEntry(m_creature, ENTRY_MALONE, 20.0f))
        {
            m_maloneGuid = pMalone->GetObjectGuid();
            pMalone->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
        }

        bEvent = true;
    }

    uint32 NextStep(uint32 uiStep)
    {
        Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid);

        if (!pPlayer)
        {
            if (Creature* pCreepjack = m_creature->GetMap()->GetCreature(m_creepjackGuid))
            {
                if (!pCreepjack->GetCombatManager().IsInEvadeMode() && pCreepjack->IsAlive())
                    pCreepjack->AI()->EnterEvadeMode();

                pCreepjack->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
            }

            if (Creature* pMalone = m_creature->GetMap()->GetCreature(m_maloneGuid))
            {
                if (!pMalone->GetCombatManager().IsInEvadeMode() && pMalone->IsAlive())
                    pMalone->AI()->EnterEvadeMode();

                pMalone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
            }

            EnterEvadeMode();
            return 0;
        }

        switch (uiStep)
        {
            case 1:
                if (Creature* pCreepjack = m_creature->GetMap()->GetCreature(m_creepjackGuid))
                    pCreepjack->SetStandState(UNIT_STAND_STATE_STAND);

                if (Creature* pMalone = m_creature->GetMap()->GetCreature(m_maloneGuid))
                    pMalone->SetStandState(UNIT_STAND_STATE_STAND);

                DoScriptText(SAY_START, m_creature, pPlayer);
                return 2000;
            case 2:
                if (Creature* pMalone = m_creature->GetMap()->GetCreature(m_maloneGuid))
                {
                    pMalone->SetFacingToObject(pPlayer);
                    DoScriptText(EMOTE_KNUCKLES, pMalone, pPlayer);
                }
                if (Creature* pCreepjack = m_creature->GetMap()->GetCreature(m_creepjackGuid))
                {
                    pCreepjack->SetFacingToObject(pPlayer);
                    DoScriptText(EMOTE_KNUCKLES, pCreepjack, pPlayer);
                }
                return 2000;
            case 3: DoScriptText(SAY_COUNT, m_creature, pPlayer);   return 5000;
            case 4: DoScriptText(SAY_COUNT_1, m_creature, pPlayer); return 2000;
            case 5: DoScriptText(SAY_COUNT_2, m_creature, pPlayer); return 2000;
            case 6: DoScriptText(SAY_ATTACK, m_creature, pPlayer);  return 2000;
            case 7:
                m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
                SetReactState(REACT_AGGRESSIVE);

                if (pPlayer->IsAlive())
                {
                    if (!m_creature->IsInCombat())
                        AttackStart(pPlayer);

                    if (Creature* pMalone = m_creature->GetMap()->GetCreature(m_maloneGuid))
                    {
                        pMalone->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
                        if (!pMalone->IsInCombat())
                            pMalone->AI()->AttackStart(pPlayer);
                    }

                    if (Creature* pCreepjack = m_creature->GetMap()->GetCreature(m_creepjackGuid))
                    {
                        pCreepjack->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
                        if (!pCreepjack->IsInCombat())
                            pCreepjack->AI()->AttackStart(pPlayer);
                    }
                }

                bActiveAttack = true;
                return 500;
            case 8:
                DoScriptText(SAY_GIVEUP, m_creature, pPlayer);
                return 4000;
            case 9:
                m_creature->GetMotionMaster()->MoveTargetedHome();
                EnterEvadeMode();
                return 0;
            default:
                return 0;
        }
    }

    void AttackedBy(Unit* pAttacker) override
    {
        if (m_creature->GetVictim())
            return;

        if (!bActiveAttack)
            return;

        AttackStart(pAttacker);
    }

    void DamageTaken(Unit* /*dealer*/, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (damage < m_creature->GetHealth())
            return;

        damage = std::min(damage, m_creature->GetHealth() - 1);

        // damage will kill, this is pretty much the same as 1%HP left
        if (bEvent)
        {
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
            SetReactState(REACT_PASSIVE);
            m_creature->CombatStop();

            if (Player* pPlayer = m_creature->GetMap()->GetPlayer(m_playerGuid))
                pPlayer->RewardPlayerAndGroupAtEventExplored(QUEST_WHAT_BOOK, m_creature);

            if (Creature* pCreepjack = m_creature->GetMap()->GetCreature(m_creepjackGuid))
            {
                if (!pCreepjack->GetCombatManager().IsInEvadeMode() && pCreepjack->IsAlive())
                    pCreepjack->AI()->EnterEvadeMode();

                pCreepjack->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
            }
            if (Creature* pMalone = m_creature->GetMap()->GetCreature(m_maloneGuid))
            {
                if (!pMalone->GetCombatManager().IsInEvadeMode() && pMalone->IsAlive())
                    pMalone->AI()->EnterEvadeMode();

                pMalone->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_IMMUNE_TO_PLAYER);
            }

            bActiveAttack = false;
        }
    }

    void UpdateAI(const uint32 diff) override
    {
        if (bEvent && !bActiveAttack)
        {
            if (m_uiSayTimer < diff)
                m_uiSayTimer = NextStep(++m_uiStep);
            else
                m_uiSayTimer -= diff;
        }

        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

bool GossipHello_npc_dirty_larry(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetObjectGuid());

    if (pPlayer->GetQuestStatus(QUEST_WHAT_BOOK) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM_ID(GOSSIP_ICON_CHAT, GOSSIP_ITEM_BOOK, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF + 1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetObjectGuid());
    return true;
}

bool GossipSelect_npc_dirty_larry(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF + 1)
    {
        if (npc_dirty_larryAI* pLarryAI = dynamic_cast<npc_dirty_larryAI*>(pCreature->AI()))
            pLarryAI->StartEvent(pPlayer);

        pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

UnitAI* GetAI_npc_dirty_larry(Creature* pCreature)
{
    return new npc_dirty_larryAI(pCreature);
}

/*######
## npc_khadgars_servant
######*/

enum
{
    SAY_KHAD_START          = -1000489,
    SAY_KHAD_SERV_0         = -1000234,

    SAY_KHAD_SERV_1         = -1000235,
    SAY_KHAD_SERV_2         = -1000236,
    SAY_KHAD_SERV_3         = -1000237,
    SAY_KHAD_SERV_4         = -1000238,

    SAY_KHAD_SERV_5         = -1000239,
    SAY_KHAD_SERV_6         = -1000240,
    SAY_KHAD_SERV_7         = -1000241,

    SAY_KHAD_SERV_8         = -1000242,
    SAY_KHAD_SERV_9         = -1000243,
    SAY_KHAD_SERV_10        = -1000244,
    SAY_KHAD_SERV_11        = -1000245,

    SAY_KHAD_SERV_12        = -1000246,
    SAY_KHAD_SERV_13        = -1000247,

    SAY_KHAD_SERV_14        = -1000248,
    SAY_KHAD_SERV_15        = -1000249,
    SAY_KHAD_SERV_16        = -1000250,
    SAY_KHAD_SERV_17        = -1000251,

    SAY_KHAD_SERV_18        = -1000252,
    SAY_KHAD_SERV_19        = -1000253,
    SAY_KHAD_SERV_20        = -1000254,
    SAY_KHAD_SERV_21        = -1000255,

    SAY_KHAD_INJURED        = -1000490,
    SAY_KHAD_MIND_YOU       = -1000491,
    SAY_KHAD_MIND_ALWAYS    = -1000492,
    SAY_KHAD_ALDOR_GREET    = -1000493,
    SAY_KHAD_SCRYER_GREET   = -1000494,
    SAY_KHAD_HAGGARD        = -1000495,

    NPC_KHADGAR             = 18166,
    NPC_SHANIR              = 18597,
    NPC_IZZARD              = 18622,
    NPC_ADYRIA              = 18596,
    NPC_ANCHORITE           = 19142,
    NPC_ARCANIST            = 18547,
    NPC_HAGGARD             = 19684,

    QUEST_CITY_LIGHT        = 10211
};

struct npc_khadgars_servantAI : public npc_escortAI
{
    npc_khadgars_servantAI(Creature* creature) : npc_escortAI(creature), m_startPhase(0)
    {
        AddCustomAction(0, 2000u, [=]() { HandleStart(); });
        SetReactState(REACT_PASSIVE);
        Reset();
    }

    uint32 m_uiPointId;
    uint32 m_uiTalkTimer;
    uint32 m_uiTalkCount;
    uint32 m_uiRandomTalkCooldown;

    uint32 m_startPhase;

    void Reset() override
    {
        m_uiTalkTimer = 2500;
        m_uiTalkCount = 0;
        m_uiPointId = 0;
        m_uiRandomTalkCooldown = 0;
    }

    void MoveInLineOfSight(Unit* pWho) override
    {
        if (!m_uiRandomTalkCooldown && pWho->GetTypeId() == TYPEID_UNIT && m_creature->IsWithinDistInMap(pWho, 10.0f))
        {
            switch (pWho->GetEntry())
            {
                case NPC_HAGGARD:
                    if (Player* pPlayer = GetPlayerForEscort())
                        DoScriptText(SAY_KHAD_HAGGARD, pWho, pPlayer);
                    m_uiRandomTalkCooldown = 7500;
                    break;
                case NPC_ANCHORITE:
                    if (Player* pPlayer = GetPlayerForEscort())
                        DoScriptText(SAY_KHAD_ALDOR_GREET, pWho, pPlayer);
                    m_uiRandomTalkCooldown = 7500;
                    break;
                case NPC_ARCANIST:
                    if (Player* pPlayer = GetPlayerForEscort())
                        DoScriptText(SAY_KHAD_SCRYER_GREET, pWho, pPlayer);
                    m_uiRandomTalkCooldown = 7500;
                    break;
            }
        }
    }

    void HandleStart()
    {
        uint32 timer = 0;
        switch (m_startPhase)
        {
            case 0: // khadgar talks
                if (Creature* pKhadgar = GetClosestCreatureWithEntry(m_creature, NPC_KHADGAR, 10.0f))
                    DoScriptText(SAY_KHAD_START, pKhadgar);
                timer = 3000;
                break;
            case 1: // servant talks
                DoScriptText(SAY_KHAD_SERV_0, m_creature);
                timer = 4000;
                break;
            case 2: // wps start
                if (m_creature->GetOwner() && m_creature->GetOwner()->GetTypeId() == TYPEID_PLAYER)
                    Start(false, static_cast<Player*>(m_creature->GetOwner()));
                else
                    script_error_log("npc_khadgars_servant can not obtain owner or owner is not a player.");
                break;
        }
        ++m_startPhase;
        if (timer)
            ResetTimer(0, timer);
    }

    void WaypointReached(uint32 uiPointId) override
    {
        m_uiPointId = uiPointId;

        switch (uiPointId)
        {
            case 1:
                break;
            case 7:
            case 26:
            case 52:
            case 65:
            case 76:
            case 77:
                SetEscortPaused(true);
                break;
            case 36:
                if (Creature* pIzzard = GetClosestCreatureWithEntry(m_creature, NPC_IZZARD, 10.0f))
                    DoScriptText(SAY_KHAD_MIND_YOU, pIzzard);
                break;
            case 37:
                if (Creature* pAdyria = GetClosestCreatureWithEntry(m_creature, NPC_ADYRIA, 10.0f))
                    DoScriptText(SAY_KHAD_MIND_ALWAYS, pAdyria);
                break;
        }
    }

    void UpdateEscortAI(const uint32 diff) override
    {
        UpdateTimers(diff, m_creature->IsInCombat());

        if (m_uiRandomTalkCooldown)
        {
            if (m_uiRandomTalkCooldown <= diff)
                m_uiRandomTalkCooldown = 0;
            else
                m_uiRandomTalkCooldown -= diff;
        }

        if (HasEscortState(STATE_ESCORT_PAUSED))
        {
            if (m_uiTalkTimer <= diff)
            {
                ++m_uiTalkCount;
                m_uiTalkTimer = 7500;

                Player* pPlayer = GetPlayerForEscort();

                if (!pPlayer)
                    return;

                switch (m_uiPointId)
                {
                    case 7:                                 // to lower city
                    {
                        switch (m_uiTalkCount)
                        {
                            case 1:
                                DoScriptText(SAY_KHAD_SERV_1, m_creature, pPlayer);
                                break;
                            case 2:
                                DoScriptText(SAY_KHAD_SERV_2, m_creature, pPlayer);
                                break;
                            case 3:
                                DoScriptText(SAY_KHAD_SERV_3, m_creature, pPlayer);
                                break;
                            case 4:
                                DoScriptText(SAY_KHAD_SERV_4, m_creature, pPlayer);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                    case 26:                                // in lower city
                    {
                        switch (m_uiTalkCount)
                        {
                            case 5:
                                if (Creature* pShanir = GetClosestCreatureWithEntry(m_creature, NPC_SHANIR, 15.0f))
                                    DoScriptText(SAY_KHAD_INJURED, pShanir, pPlayer);

                                DoScriptText(SAY_KHAD_SERV_5, m_creature, pPlayer);
                                break;
                            case 6:
                                DoScriptText(SAY_KHAD_SERV_6, m_creature, pPlayer);
                                break;
                            case 7:
                                DoScriptText(SAY_KHAD_SERV_7, m_creature, pPlayer);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                    case 52:                                // outside
                    {
                        switch (m_uiTalkCount)
                        {
                            case 8:
                                DoScriptText(SAY_KHAD_SERV_8, m_creature, pPlayer);
                                break;
                            case 9:
                                DoScriptText(SAY_KHAD_SERV_9, m_creature, pPlayer);
                                break;
                            case 10:
                                DoScriptText(SAY_KHAD_SERV_10, m_creature, pPlayer);
                                break;
                            case 11:
                                DoScriptText(SAY_KHAD_SERV_11, m_creature, pPlayer);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                    case 65:                                // scryer
                    {
                        switch (m_uiTalkCount)
                        {
                            case 12:
                                DoScriptText(SAY_KHAD_SERV_12, m_creature, pPlayer);
                                break;
                            case 13:
                                DoScriptText(SAY_KHAD_SERV_13, m_creature, pPlayer);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                    case 76:                                // aldor
                    {
                        switch (m_uiTalkCount)
                        {
                            case 14:
                                DoScriptText(SAY_KHAD_SERV_14, m_creature, pPlayer);
                                break;
                            case 15:
                                DoScriptText(SAY_KHAD_SERV_15, m_creature, pPlayer);
                                break;
                            case 16:
                                DoScriptText(SAY_KHAD_SERV_16, m_creature, pPlayer);
                                break;
                            case 17:
                                DoScriptText(SAY_KHAD_SERV_17, m_creature, pPlayer);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                    case 77:                                // a'dal
                    {
                        switch (m_uiTalkCount)
                        {
                            case 18:
                                DoScriptText(SAY_KHAD_SERV_18, m_creature, pPlayer);
                                break;
                            case 19:
                                DoScriptText(SAY_KHAD_SERV_19, m_creature, pPlayer);
                                break;
                            case 20:
                                DoScriptText(SAY_KHAD_SERV_20, m_creature, pPlayer);
                                break;
                            case 21:
                                DoScriptText(SAY_KHAD_SERV_21, m_creature, pPlayer);
                                pPlayer->AreaExploredOrEventHappens(QUEST_CITY_LIGHT);
                                SetEscortPaused(false);
                                break;
                        }
                        break;
                    }
                }
            }
            else
                m_uiTalkTimer -= diff;
        }
    }
};

/*######
# npc_salsalabim
######*/

enum
{
    FACTION_HOSTILE_SA              = 90,
    QUEST_10004                     = 10004,

    SPELL_MAGNETIC_PULL             = 31705,

    SAY_SAL_AGGRO                   = -1015104
};

struct npc_salsalabimAI : public ScriptedAI
{
    npc_salsalabimAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    uint32 m_uiMagneticPullTimer;

    void Reset() override
    {
        m_uiMagneticPullTimer = 15000;
    }

    void DamageTaken(Unit* pDoneBy, uint32& damage, DamageEffectType /*damagetype*/, SpellEntry const* /*spellInfo*/) override
    {
        if (pDoneBy && pDoneBy->GetTypeId() == TYPEID_PLAYER)
        {
            if (m_creature->GetHealthPercent() < 20.0f)
            {
                ((Player*)pDoneBy)->RewardPlayerAndGroupAtEventExplored(QUEST_10004, m_creature);
                damage = std::min(damage, m_creature->GetHealth() - 1);
                EnterEvadeMode();
            }
        }
    }

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_creature->SelectHostileTarget() || !m_creature->GetVictim())
            return;

        if (m_uiMagneticPullTimer < uiDiff)
        {
            DoCastSpellIfCan(m_creature->GetVictim(), SPELL_MAGNETIC_PULL);
            m_uiMagneticPullTimer = 15000;
        }
        else
            m_uiMagneticPullTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

UnitAI* GetAI_npc_salsalabim(Creature* pCreature)
{
    return new npc_salsalabimAI(pCreature);
}

bool GossipSelect_npc_salsalabim(Player* pPlayer, Creature* pCreature, uint32 /*uiSender*/, uint32 uiAction)
{
    if (uiAction == 1)
    {
       pCreature->SetFactionTemporary(FACTION_HOSTILE_SA, TEMPFACTION_RESTORE_REACH_HOME);
       pCreature->AI()->AttackStart(pPlayer);
       DoScriptText(SAY_SAL_AGGRO, pCreature, pPlayer);
       pPlayer->CLOSE_GOSSIP_MENU();
    }

    return true;
}

enum
{
    QUEST_KAELTHAS_AND_THE_VERDANT_SPHERE   = 11007,
    QUEST_TRIAL_OF_THE_NAARU_MAGTHERIDON    = 10888,
    QUEST_CUDGEL_OF_KARDESH                 = 10901,
    TITLE_CHAMPION_OF_THE_NAARU             = 53,

    SCRIPT_RELAY_ID = 10061,
};

bool QuestRewarded_npc_adal(Player* player, Creature* creature, Quest const* quest)
{
    switch (quest->GetQuestId())
    {
        case QUEST_TRIAL_OF_THE_NAARU_MAGTHERIDON:
            if (player->GetQuestStatus(QUEST_CUDGEL_OF_KARDESH) == QUEST_STATUS_COMPLETE)
                player->SetTitle(TITLE_CHAMPION_OF_THE_NAARU);
            break;
        case QUEST_KAELTHAS_AND_THE_VERDANT_SPHERE:
            sWorldState.HandleExternalEvent(CUSTOM_EVENT_ADALS_SONG_OF_BATTLE, 0);
            player->GetMap()->ScriptsStart(sRelayScripts, SCRIPT_RELAY_ID, creature, player, Map::SCRIPT_EXEC_PARAM_UNIQUE_BY_SOURCE); // only once active per adal
            return true; // handled
    }

    return false; // unhandled
}

enum recruitEventIds
{
    NPC_GRAND_ANCHORITE_ALMONEN = 19216,
    NPC_COMMANDER_STEELE = 25141,
    NPC_F_DRAENEI_TRAINEE = 25137,
    NPC_M_DRAENEI_TRAINEE = 25136,
    NPC_F_BLOODELF_TRAINEE = 25135,
    NPC_M_BLOODELF_TRAINEE = 25134,
    NPC_BLOODELF_VETERAN = 25143,
};

struct npc_shattered_sun_traineeAI : public ScriptedAI
{
    npc_shattered_sun_traineeAI(Creature* pCreature) : ScriptedAI(pCreature) {
        AddCustomAction(0, true, [&]()
        {
            m_creature->HandleEmote(urand(0,4) ? 21 : 4);
            ResetTimer(0, 1500u);
        });
        Reset();
    }

    const float radian = M_PI_F/2;
    const float forward = 5.497790;

    void ReceiveAIEvent(AIEventType type, Unit* sender, Unit* invoker, uint32 miscValue) override
    {
        if (!sender || (sender->GetEntry() != NPC_COMMANDER_STEELE && sender->GetEntry() != NPC_GRAND_ANCHORITE_ALMONEN))
            return;

        switch (type)
        {
            case AI_EVENT_CUSTOM_EVENTAI_A:
                if (miscValue == 26)
                    m_creature->SetStandState(UNIT_STAND_STATE_STAND);
                else if (miscValue == 68)
                    m_creature->SetStandState(UNIT_STAND_STATE_KNEEL);
                else if (miscValue == 253)
                    ResetTimer(0, 2000u);
                else
                    m_creature->HandleEmote(miscValue);

            break;
            case AI_EVENT_CUSTOM_EVENTAI_B:
            {
                SetRootSelf(true);
                switch (miscValue)
                {
                    case 0:
                        m_creature->SetOrientation(forward);
                        break;
                    case 1:
                        m_creature->SetOrientation(forward - radian);
                        break;
                    case 2:
                        m_creature->SetOrientation(forward - 2 * radian);
                        break;
                    case 3: 
                        m_creature->SetOrientation(forward + radian);
                        break;
                }
                m_creature->SendHeartBeat();
            }
                break;
            case AI_EVENT_CUSTOM_EVENTAI_C:
                DisableTimer(0);
                break;
            default:
                break;
        }
    }

    void MovementInform(uint32 motionType, uint32 uiPointId) override
    {
        switch (uiPointId)
        {
            case 2: m_creature->GetMotionMaster()->Clear(); m_creature->GetMotionMaster()->MoveIdle(); m_creature->SetFacingTo(forward); break;
            case 3: m_creature->ForcedDespawn();
        }
    }
};

struct npc_commander_steeleAI: public ScriptedAI
{
    npc_commander_steeleAI(Creature* pCreature) : ScriptedAI(pCreature) { Reset(); }

    ObjectGuid recruitMatrix[4][4];
    ObjectGuid veteran;
    const Position veteranEntryPosition = {-1803.735, 5294.502, -12.38359, 1.62};
    const Position veteranEventPosition = {-1780.713, 5332.765, -12.43613, 5.497787};
    const Position veteranExitPosition = {-1798.737, 5308.549, -14.55699, 1.62};
    const Position recruitEntryPositions[4][4] =
    {
        {
            {-1810.735, 5292.215, -12.3448, 5.5},
            {-1797.464, 5308.929, -14.69543, 5.5},
            {-1801.254, 5313.176, -12.43915, 5.5},
            {-1816.387, 5357.304, -12.43532, 5.5},
        },
        {
            {-1823.218, 5329.122, -12.3977, 5.5},
            {-1841.915, 5347.13, -12.34478, 5.5},
            {-1824.706, 5307.167, -12.3448, 5.5},
            {-1790.77, 5300.418, -20.52535, 5.5},
        },
        {
            {-1795.66, 5306.961, -16.11753, 5.5},
            {-1835.797, 5375.394, -12.3448, 5.5},
            {-1823.988, 5360.059, -12.43532, 5.5},
            {-1809.875, 5325.414, -12.40578, 5.5},
        },
        {
            {-1811.616, 5333.609, -12.43531, 5.5},
            {-1818.436, 5351.488, -12.43532, 5.5},
            {-1828.191, 5364.457, -12.34482, 5.5},
            {-1818.281, 5301.583, -12.3448, 5.5},
        },
    };

    const Position recruitEventPositions[4][4] =
    {
        {
            {-1783.63, 5333.444, -12.43531, 5.497787},
            {-1779.016, 5337.96, -12.43531, 5.497787},
            {-1783.164, 5337.674, -12.43531, 5.497787},
            {-1787.639, 5341.807, -12.43532, 5.497787},
        },
        {
            {-1787.731, 5337.603, -12.43532, 5.497787},
            {-1792.356, 5337.139, -12.43532, 5.497787},
            {-1785.664, 5335.256, -12.43532, 5.497787},
            {-1780.876, 5339.828, -12.43531, 5.497787},
        },
        {
            {-1781.292, 5335.792, -12.43531, 5.497787},
            {-1782.86, 5342.133, -12.43531, 5.497787},
            {-1789.791, 5339.68, -12.43532, 5.497787},
            {-1785.902, 5331.252, -12.43613, 5.497787},
        },
        {
            {-1787.792, 5333.102, -12.43613, 5.497787},
            {-1785.457, 5339.807, -12.43532, 5.497787},
            {-1785.311, 5344.088, -12.43532, 5.497787},
            {-1790.151, 5335.142, -12.43532, 5.497787},
        },
    };

    const Position recruitExitPositions[4][4] =
    {
        {
            {-1796.377, 5299.302, -19.65246, 100},
            {-1744.358, 5380.27, -12.43531, 100},
            {-1796.183, 5304.772, -17.0572, 100},
            {-1798.558, 5309.034, -14.36996, 100},
        },
        {
            {-1796.379, 5299.602, -19.50641, 100},
            {-1796.706, 5308.721, -15.00909, 100},
            {-1799.474, 5307.094, -15.06679, 100},
            {-1730.106, 5363.373, -9.859305, 100},
        },
        {
            {-1728.108, 5366.323, -9.279177, 100},
            {-1764.693, 5385.993, -5.32568, 100},
            {-1798.901, 5305.465, -16.00611, 100},
            {-1794.535, 5303.782, -17.97032, 100},
        },
        {
            {-1794.568, 5309.374, -15.2566, 100},
            {-1763.738, 5383.413, -7.619812, 100},
            {-1741.796, 5385.382, -12.43531, 100},
            {-1792.979, 5307.494, -16.58447, 100},
        },
    };

    void ReceiveAIEvent(AIEventType type, Unit*, Unit*, uint32 miscValue) override
    {
        if (type == AI_EVENT_CUSTOM_EVENTAI_D)
        {
            HandleRecruitSpawn(!miscValue);
            m_creature->SetActiveObjectState(miscValue);
        }
    }

    void HandleRecruitSpawn(bool despawn)
    {
        if (despawn)
        {
            for (int x=0; x<4; x++)
            {
                for (int y=0; y<4; y++)
                {
                    if (recruitMatrix[x][y])
                    {
                        Unit* crRecruit = m_creature->GetMap()->GetUnit(recruitMatrix[x][y]);
                        if (crRecruit && crRecruit->IsAlive() && crRecruit->AI())
                        {
                            crRecruit->AI()->SetRootSelf(false);
                            crRecruit->AI()->ReceiveAIEvent(AI_EVENT_CUSTOM_EVENTAI_C, m_creature, m_creature, 0);
                            crRecruit->GetMotionMaster()->MovePoint(3, recruitExitPositions[x][y], FORCED_MOVEMENT_RUN);
                        }
                    }
                }
            }
            Unit* crVeteran = m_creature->GetMap()->GetUnit(veteran);
            if (crVeteran && crVeteran->IsAlive() && crVeteran->AI())
            {
                crVeteran->AI()->SetRootSelf(false);
                crVeteran->GetMotionMaster()->MovePoint(3, veteranExitPosition, FORCED_MOVEMENT_RUN);
            }
        }
        else
        {
            static const std::vector<uint32> entries = {NPC_F_BLOODELF_TRAINEE, NPC_F_DRAENEI_TRAINEE, NPC_M_BLOODELF_TRAINEE, NPC_M_DRAENEI_TRAINEE};
            TempSpawnSettings spawnSettings;
            for (int x=0; x<4; x++)
            {
                for (int y=0; y<4; y++)
                {
                    spawnSettings.x = recruitEntryPositions[x][y].x;
                    spawnSettings.y = recruitEntryPositions[x][y].y;
                    spawnSettings.z = recruitEntryPositions[x][y].z;
                    spawnSettings.ori = recruitEntryPositions[x][y].o;
                    spawnSettings.spawnType = TEMPSPAWN_CORPSE_DESPAWN;
                    spawnSettings.entry = entries[urand(0,3)];
                    spawnSettings.activeObject = true;
                    spawnSettings.spawner = m_creature;
                    if (Creature* summoned = m_creature->SummonCreature(spawnSettings, m_creature->GetMap()))
                    {
                        recruitMatrix[x][y] = summoned->GetObjectGuid();
                        summoned->GetMotionMaster()->MovePoint(2, recruitEventPositions[x][y], FORCED_MOVEMENT_RUN);
                    }
                }
            }
            spawnSettings.x = veteranEntryPosition.x;
            spawnSettings.y = veteranEntryPosition.y;
            spawnSettings.z = veteranEntryPosition.z;
            spawnSettings.ori = veteranEntryPosition.o;
            spawnSettings.spawnType = TEMPSPAWN_CORPSE_DESPAWN;
            spawnSettings.entry = NPC_BLOODELF_VETERAN;
            spawnSettings.activeObject = true;
            spawnSettings.spawner = m_creature;
            if (Creature* summoned = m_creature->SummonCreature(spawnSettings, m_creature->GetMap()))
            {
                veteran = summoned->GetObjectGuid();
                summoned->GetMotionMaster()->MovePoint(2, veteranEventPosition, FORCED_MOVEMENT_RUN);
            }
        }
    }
};

enum
{
    SPELL_DEMON_BROILED_SURPRISE    = 43753,
};

struct DemonBroiledSurprise : public SpellScript
{
    SpellCastResult OnCheckCast(Spell* spell, bool strict) const
    {
        if (strict)
        {
            float radius = GetSpellMaxRange(sSpellRangeStore.LookupEntry(spell->m_spellInfo->rangeIndex));
            UnitList tempUnitList;
            GameObjectList tempGOList;
            return spell->CheckScriptTargeting(EFFECT_INDEX_1, 1, radius, TARGET_ENUM_UNITS_SCRIPT_AOE_AT_SRC_LOC, tempUnitList, tempGOList);
        }
        return SPELL_CAST_OK;
    }

    void OnEffectExecute(Spell* spell, SpellEffectIndex effIdx) const override
    {
        if (effIdx != EFFECT_INDEX_0)
            return;

        spell->GetCaster()->CastSpell(nullptr, SPELL_DEMON_BROILED_SURPRISE, TRIGGERED_NONE);
    }
};

void AddSC_shattrath_city()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "npc_dirty_larry";
    pNewScript->GetAI = &GetAI_npc_dirty_larry;
    pNewScript->pGossipHello = &GossipHello_npc_dirty_larry;
    pNewScript->pGossipSelect = &GossipSelect_npc_dirty_larry;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_khadgars_servant";
    pNewScript->GetAI = &GetNewAIInstance<npc_khadgars_servantAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_salsalabim";
    pNewScript->GetAI = &GetAI_npc_salsalabim;
    pNewScript->pGossipSelect = &GossipSelect_npc_salsalabim;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_shattered_sun_trainee";
    pNewScript->GetAI = &GetNewAIInstance<npc_shattered_sun_traineeAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_commander_steele";
    pNewScript->GetAI = &GetNewAIInstance<npc_commander_steeleAI>;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_adal";
    pNewScript->pQuestRewardedNPC = &QuestRewarded_npc_adal;
    pNewScript->RegisterSelf();

    RegisterSpellScript<DemonBroiledSurprise>("spell_demon_broiled_surprise");
}

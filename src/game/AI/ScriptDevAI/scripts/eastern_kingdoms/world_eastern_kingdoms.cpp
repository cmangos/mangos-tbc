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

#include "world_eastern_kingdoms.h"
#include "AI/ScriptDevAI/include/sc_common.h"
#include "AI/ScriptDevAI/scripts/world/world_map_scripts.h"
#include "AI/ScriptDevAI/base/TimerAI.h"
#include "World/WorldState.h"
#include "World/WorldStateDefines.h"

/* *********************************************************
 *                  EASTERN KINGDOMS
 */
struct world_map_eastern_kingdoms : public ScriptedMap, public TimerManager
{
    world_map_eastern_kingdoms(Map* pMap) : ScriptedMap(pMap), m_shadeData({ AREAID_GOLDSHIRE, AREAID_KHARANOS, AREAID_BRILL })
    {
        AddCustomAction(EVENT_SPAWN, true, [&]
        {
            if (_spawn.size() < 16)
            {
                switch (urand(0, 4))
                {
                    case 0: DoSpawn(NPC_INVADING_FELGUARD); break;
                    case 1: DoSpawn(NPC_INVADING_VOIDWALKER); break;
                    case 2: DoSpawn(NPC_INVADING_INFERNAL); break;
                    case 3: DoSpawn(NPC_INVADING_FEL_STALKER); break;
                    case 4: DoSpawn(NPC_INVADING_ANGUISHER); break;
                }
            }
            ResetTimer(EVENT_SPAWN, urand(1000, 5000));
        });
        AddCustomAction(EVENT_SPAWN_BOSS, true, [&]
        {
            if (_spawnBoss.size() < 1)
            {
                urand(0, 1) ? ResetTimer(EVENT_SPAWN_DREADKNIGHT, urand(5000, 10000)) : ResetTimer(EVENT_SPAWN_FELGUARD_LIEUTENANT, urand(5000, 10000));
            }
            ResetTimer(EVENT_SPAWN_BOSS, urand(20000, 30000));
        });
        AddCustomAction(EVENT_SPAWN_DREADKNIGHT, true, [&]
        {
            DoSpawn(NPC_DREADKNIGHT);
            DoSpawn(NPC_INVADING_INFERNAL);
            DoSpawn(NPC_INVADING_INFERNAL);
        });
        AddCustomAction(EVENT_SPAWN_FELGUARD_LIEUTENANT, true, [&]
        {
            DoSpawn(NPC_FELGUARD_LIEUTENANT);
            DoSpawn(NPC_INVADING_FEL_STALKER);
            DoSpawn(NPC_INVADING_ANGUISHER);
        });
        AddCustomAction(EVENT_REINFORCEMENTS_NEEDED, true, [&]
        {
            if (_spawnSupport.size() < 1)
            {
                if (_spawnProtector.size() < 4 || _spawnGuardian.size() < 4)
                {
                    ResetTimer(EVENT_SPAWN_REINFORCEMENTS, 1000);
                    ResetTimer(EVENT_REINFORCEMENTS_LEADER_SPEAK, urand(45000, 90000));
                    ResetTimer(EVENT_REINFORCEMENTS_LEADER_FLEE, 4 * MINUTE * IN_MILLISECONDS);
                }
            }
            if (_spawnProtector.size() < 8 || _spawnGuardian.size() < 8)
            {
                ResetTimer(EVENT_SPAWN_SMALL_REINFORCEMENTS, 1000);
            }
            ResetTimer(EVENT_REINFORCEMENTS_NEEDED, urand(5000, 15000));
        });
        AddCustomAction(EVENT_SPAWN_SMALL_REINFORCEMENTS, true, [&]
        {
            if (_spawnProtector.size() < 10)
            {
                switch (urand(0, 1))
                {
                case 0: DoSpawn(NPC_ARGENT_GUARDIAN); break;
                case 1: DoSpawn(NPC_ARGENT_BOWMAN); break;
                }
            }
            if (_spawnGuardian.size() < 10)
            {
                switch (urand(0, 1))
                {
                case 0: DoSpawn(NPC_ARGENT_PROTECTOR); break;
                case 1: DoSpawn(NPC_ARGENT_HUNTER); break;
                }
            }
        });
        AddCustomAction(EVENT_SPAWN_REINFORCEMENTS, true, [&]
        {
            switch (urand(0, 2))
            {
                case 0: DoSpawn(NPC_LORD_MARSHAL_RAYNOR); break;
                case 1: DoSpawn(NPC_JUSTINIUS_THE_HARBINGER); break;
                case 2: DoSpawn(NPC_MELGROMM_HIGHMOUNTAIN); break;
            }
        });
        AddCustomAction(EVENT_REINFORCEMENTS_LEADER_FLEE, true, [&]
        {
            if (_spawnSupport.size() > 0)
            {
                uint32 randomScriptTextId = 0;

                for (std::set<ObjectGuid>::iterator it = _spawnSupport.begin(); it != _spawnSupport.end(); ++it)
                {
                    if (Creature* lead = instance->GetCreature(*it))
                    {
                        Position fleePos;
                        uint32 despawnScriptTextId = 0;

                        switch (lead->GetEntry())
                        {
                        case NPC_LORD_MARSHAL_RAYNOR:
                            despawnScriptTextId = LMR_DESPAWN;
                            fleePos = spawnAllyReinforcementPos;
                        case NPC_JUSTINIUS_THE_HARBINGER:
                            despawnScriptTextId = JTH_DESPAWN;
                            fleePos = spawnAllyReinforcementPos;
                            break;
                        case NPC_MELGROMM_HIGHMOUNTAIN:
                            despawnScriptTextId = MH_DESPAWN;
                            fleePos = spawnHordeReinforcementPos;
                            break;
                        }
                        DoScriptText(despawnScriptTextId, lead);
                        lead->CombatStop();
                        lead->RemoveAllAurasOnEvade();
                        lead->SetFactionTemporary(35, TEMPFACTION_RESTORE_RESPAWN);
                        lead->GetMotionMaster()->MovePoint(0, fleePos.x, fleePos.y, fleePos.z, FORCED_MOVEMENT_RUN, true);
                    }
                }
            }
        });
        AddCustomAction(EVENT_REINFORCEMENTS_LEADER_SPEAK, true, [&]
        {
            if (_spawnSupport.size() > 0)
            {
                uint32 randomScriptTextId = 0;

                for (std::set<ObjectGuid>::iterator it = _spawnSupport.begin(); it != _spawnSupport.end(); ++it)
                {
                    if (Creature* add = instance->GetCreature(*it))
                    {
                        switch (add->GetEntry())
                        {
                            case NPC_LORD_MARSHAL_RAYNOR:
                                switch (urand(0, 4))
                                {
                                    case 0: randomScriptTextId = LMR_RANDOM_TEXT_1; break;
                                    case 1: randomScriptTextId = LMR_RANDOM_TEXT_2; break;
                                    case 2: randomScriptTextId = LMR_RANDOM_TEXT_3; break;
                                    case 3: randomScriptTextId = LMR_RANDOM_TEXT_4; break;
                                    case 4: randomScriptTextId = LMR_RANDOM_TEXT_5; break;
                                }
                                break;
                            case NPC_JUSTINIUS_THE_HARBINGER:
                                switch (urand(0, 3))
                                {
                                    case 0: randomScriptTextId = JTH_RANDOM_TEXT_1; break;
                                    case 1: randomScriptTextId = JTH_RANDOM_TEXT_2; break;
                                    case 2: randomScriptTextId = JTH_RANDOM_TEXT_3; break;
                                }
                                break;
                            case NPC_MELGROMM_HIGHMOUNTAIN:
                                switch (urand(0, 5))
                                {
                                    case 0: randomScriptTextId = MH_RANDOM_TEXT_1; break;
                                    case 1: randomScriptTextId = MH_RANDOM_TEXT_2; break;
                                    case 2: randomScriptTextId = MH_RANDOM_TEXT_3; break;
                                    case 3: randomScriptTextId = MH_RANDOM_TEXT_4; break;
                                    case 4: randomScriptTextId = MH_RANDOM_TEXT_5; break;
                                    case 5: randomScriptTextId = MH_RANDOM_TEXT_6; break;
                                }
                                break;
                        }
                        DoScriptText(randomScriptTextId, add);
                    }
                }
            }
            ResetTimer(EVENT_REINFORCEMENTS_LEADER_SPEAK, urand(60000, 90000));
        });
        Initialize();
    }

    std::set<ObjectGuid> _spawn;
    std::set<ObjectGuid> _spawnBoss;
    std::set<ObjectGuid> _spawnSupport;
    std::set<ObjectGuid> _spawnProtector;
    std::set<ObjectGuid> _spawnGuardian;

    Position const spawnPortalPos = { -11900.3f, -3207.62f, -14.7534f, 0.146405f };
    Position const spawnPortalPos1 = { -11901.25f, -3202.272f, -14.7534f, 0.146405f };
    Position const spawnBossPortalPos = { -11891.500f, -3207.010f, -14.798f, 0.146405f };
    Position const centerBattlePos = { -11815.1f, -3190.39f, -30.7338f, 3.32447f };
    Position const spawnAllyReinforcementPos = { -11772.43f, -3272.84f, -17.9f, 2.0f };
    Position const spawnHordeReinforcementPos = { -11741.70f, -3130.3f, -11.7936f, 3.8f };
    Position const spawnSmallAllyReinforcementPos = { -11794.278f, -3224.424f, -29.99856f, 2.5f };
    Position const spawnSmallAllyReinforcementPos2 = { -11818.512f, -3234.08f, -30.017094f, 1.6f };
    Position const spawnSmallHordeReinforcementPos = { -11774.95f, -3183.269f, -28.9086f, 3.0f };
    Position const allyGuardPos = { -11838.594f, -3212.88f, -30.049786f, 2.74f };
    Position const allyGuardPos2 = { -11836.145f, -3204.032f, -30.24958f, 2.74f };
    Position const hordeGuardPos = { -11834.107f,  -3194.97f, -30.048494f, 3.5f };
    Position const hordeGuardPos2 = { -11837.795f, -3188.976f, -29.704037f, 3.5f };

    // Shade of the Horseman village attack event
    ShadeOfTheHorsemanData m_shadeData;

    void Initialize() override
    {
        m_shadeData.Reset();
    }

    bool CheckConditionCriteriaMeet(Player const* player, uint32 instanceConditionId, WorldObject const* conditionSource, uint32 conditionSourceType) const override
    {
        if (instanceConditionId >= INSTANCE_CONDITION_ID_FIRE_BRIGADE_PRACTICE_GOLDSHIRE && instanceConditionId <= INSTANCE_CONDITION_ID_LET_THE_FIRES_COME_HORDE)
            return m_shadeData.IsConditionFulfilled(instanceConditionId, player->GetAreaId());

        script_error_log("world_map_eastern_kingdoms::CheckConditionCriteriaMeet called with unsupported Id %u. Called with param plr %s, src %s, condition source type %u",
            instanceConditionId, player ? player->GetGuidStr().c_str() : "nullptr", conditionSource ? conditionSource->GetGuidStr().c_str() : "nullptr", conditionSourceType);
        return false;
    }

    void FillInitialWorldStates(ByteBuffer& data, uint32& count, uint32 /*zoneId*/, uint32 areaId) override
    {
        switch (areaId)
        {
            case AREAID_GOLDSHIRE:
            case AREAID_KHARANOS:
            case AREAID_BRILL:
            {
                FillInitialWorldStateData(data, count, WORLD_STATE_SHADE_OF_THE_HORSEMAN_TIMER, m_shadeData.CalculateWorldstateTimerValue());
                break;
            }
            default: break;
        }
    }

    void OnCreatureCreate(Creature* pCreature) override
    {
        switch (pCreature->GetEntry())
        {
            case NPC_NEZRAZ:
            case NPC_HINDENBURG:
            case NPC_ZAPETTA:
            case NPC_SQUIBBY_OVERSPECK:
            case NPC_JONATHAN:
            case NPC_WRYNN:
            case NPC_BOLVAR:
            case NPC_PRESTOR:
            case NPC_WINDSOR:
            case NPC_HIGHLORD_KRUUL:
            case NPC_AGENT_PROUDWELL:
            case NPC_FALSTAD_WILDHAMMER:
                m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
                break;
            case NPC_DREADKNIGHT:
            case NPC_FELGUARD_LIEUTENANT:
                _spawnBoss.insert(pCreature->GetObjectGuid());
                break;
            case NPC_LORD_MARSHAL_RAYNOR:
            case NPC_JUSTINIUS_THE_HARBINGER:
            case NPC_MELGROMM_HIGHMOUNTAIN:
                _spawnSupport.insert(pCreature->GetObjectGuid());
                break;
            case NPC_INVADING_INFERNAL:
            case NPC_INVADING_FELGUARD:
            case NPC_INVADING_FEL_STALKER:
            case NPC_INVADING_VOIDWALKER:
            case NPC_INVADING_ANGUISHER:
                _spawn.insert(pCreature->GetObjectGuid());
                break;
            case NPC_ARGENT_GUARDIAN:
            case NPC_ARGENT_HUNTER:
                _spawnGuardian.insert(pCreature->GetObjectGuid());
                break;
            case NPC_ARGENT_PROTECTOR:
            case NPC_ARGENT_BOWMAN:
                _spawnProtector.insert(pCreature->GetObjectGuid());
                break;
            case NPC_MASKED_ORPHAN_MATRON:
                m_npcEntryGuidStore[pCreature->GetEntry()] = pCreature->GetObjectGuid();
                break;
            case NPC_COSTUMED_ORPHAN_MATRON:
                m_npcEntryGuidCollection[pCreature->GetEntry()].push_back(pCreature->GetObjectGuid());
                break;
        }
    }

    void OnCreatureDeath(Creature* pCreature) override
    {
        switch (pCreature->GetEntry())
        {
            case NPC_DREADKNIGHT:
            case NPC_FELGUARD_LIEUTENANT:
                _spawnBoss.erase(pCreature->GetObjectGuid());
                break;
            case NPC_LORD_MARSHAL_RAYNOR:
            case NPC_JUSTINIUS_THE_HARBINGER:
            case NPC_MELGROMM_HIGHMOUNTAIN:
                _spawnSupport.erase(pCreature->GetObjectGuid());
                break;
            case NPC_ARGENT_GUARDIAN:
            case NPC_ARGENT_HUNTER:
                _spawnGuardian.erase(pCreature->GetObjectGuid());
                break;
            case NPC_ARGENT_PROTECTOR:
            case NPC_ARGENT_BOWMAN:
                _spawnProtector.erase(pCreature->GetObjectGuid());
                break;
            default:
                _spawn.erase(pCreature->GetObjectGuid());
                break;
        }
    }

    void OnCreatureEvade(Creature* pCreature) override
    {
        float x, y, z;
        float ori = 3.6f;
        switch (pCreature->GetEntry())
        {
        case NPC_DREADKNIGHT:
        case NPC_FELGUARD_LIEUTENANT:
        case NPC_INVADING_FELGUARD:
        case NPC_INVADING_VOIDWALKER:
        case NPC_INVADING_INFERNAL:
        case NPC_PORTAL_HOUND:
        case NPC_INVADING_FEL_STALKER:
        case NPC_INVADING_ANGUISHER:
            pCreature->GetRandomPoint(centerBattlePos.x, centerBattlePos.y, centerBattlePos.z, 20.0f, x, y, z);
            pCreature->SetRespawnCoord(x, y, z, 1.0f);
            pCreature->GetMotionMaster()->MovePoint(0, x, y, z, FORCED_MOVEMENT_RUN, true);
            break;
        case NPC_LORD_MARSHAL_RAYNOR:
        case NPC_JUSTINIUS_THE_HARBINGER:
        case NPC_MELGROMM_HIGHMOUNTAIN:
            if (urand(0, 1))
            {
                pCreature->GetRandomPoint(allyGuardPos.x, allyGuardPos.y, allyGuardPos.z, 2.0f, x, y, z);
                ori = 2.7f;
            }
            else
                pCreature->GetRandomPoint(hordeGuardPos.x, hordeGuardPos.y, hordeGuardPos.z, 2.0f, x, y, z);
            pCreature->SetRespawnCoord(x, y, z, ori);
            pCreature->GetMotionMaster()->MovePoint(0, x, y, z, FORCED_MOVEMENT_RUN, true);
            break;
        case NPC_ARGENT_GUARDIAN:
        case NPC_ARGENT_HUNTER:
        case NPC_ARGENT_PROTECTOR:
        case NPC_ARGENT_BOWMAN:
            if (urand(0, 1))
            {
                pCreature->GetRandomPoint(allyGuardPos.x, allyGuardPos.y, allyGuardPos.z, 2.0f, x, y, z);
                ori = 2.7f;
            }
            else
                pCreature->GetRandomPoint(hordeGuardPos.x, hordeGuardPos.y, hordeGuardPos.z, 2.0f, x, y, z);
            pCreature->SetRespawnCoord(x, y, z, ori);
            pCreature->GetMotionMaster()->MovePoint(0, x, y, z, FORCED_MOVEMENT_RUN, true);
            break;
        }
    }

    void DespawnAdds()
    {
        for (std::set<ObjectGuid>::iterator it = _spawn.begin(); it != _spawn.end(); ++it)
            if (Creature* add = instance->GetCreature(*it))
                add->AddObjectToRemoveList();
        _spawn.clear();

        for (std::set<ObjectGuid>::iterator it = _spawnSupport.begin(); it != _spawnSupport.end(); ++it)
            if (Creature* add = instance->GetCreature(*it))
                add->AddObjectToRemoveList();
        _spawnSupport.clear();

        for (std::set<ObjectGuid>::iterator it = _spawnBoss.begin(); it != _spawnBoss.end(); ++it)
            if (Creature* add = instance->GetCreature(*it))
                add->AddObjectToRemoveList();
        _spawnBoss.clear();
    }

    void DoSpawn(uint32 spawnId)
    {
        Position spawnPos;
        uint32 spawnScriptTextId = 0;
        uint32 formationCreatureEntry = 0;
        uint32 despawnTimer = 0;
        bool isEnemy = false;
        bool isBoss = false;
        bool isSoldier = false;
        TempSpawnType spawnType = TEMPSPAWN_DEAD_DESPAWN;

        switch (spawnId)
        {
            case NPC_DREADKNIGHT:
            case NPC_FELGUARD_LIEUTENANT:
                spawnPos = spawnBossPortalPos;
                isBoss = true;
                isEnemy = true;
                break;
            case NPC_LORD_MARSHAL_RAYNOR:
                spawnPos = spawnAllyReinforcementPos;
                despawnTimer = 4.3 * MINUTE * IN_MILLISECONDS;
                spawnType = TEMPSPAWN_TIMED_OR_DEAD_DESPAWN;
                formationCreatureEntry = NPC_STORMWIND_MARSHAL;
                spawnScriptTextId = LMR_SPAWN;
                break;
            case NPC_JUSTINIUS_THE_HARBINGER:
                spawnPos = spawnAllyReinforcementPos;
                despawnTimer = 4.2 * MINUTE * IN_MILLISECONDS;
                spawnType = TEMPSPAWN_TIMED_OR_DEAD_DESPAWN;
                formationCreatureEntry = NPC_AZUREMYST_VINDICATOR;
                spawnScriptTextId = JTH_SPAWN;
                break;
            case NPC_MELGROMM_HIGHMOUNTAIN:
                spawnPos = spawnHordeReinforcementPos;
                despawnTimer = 4.2 * MINUTE * IN_MILLISECONDS;
                spawnType = TEMPSPAWN_TIMED_OR_DEAD_DESPAWN;
                formationCreatureEntry = NPC_THUNDER_BLUFF_HUNTSMAN;
                spawnScriptTextId = MH_SPAWN;
                break;
            case NPC_ARGENT_GUARDIAN:
            case NPC_ARGENT_HUNTER:
                spawnPos = spawnSmallHordeReinforcementPos;
                isSoldier = true;
                break;
            case NPC_ARGENT_PROTECTOR:
            case NPC_ARGENT_BOWMAN:
                spawnPos = urand(0, 1) ? spawnSmallAllyReinforcementPos : spawnSmallAllyReinforcementPos2;
                isSoldier = true;
                break;
            default:
                spawnPos = urand(0, 1) ? spawnPortalPos : spawnPortalPos1;
                isEnemy = true;
                break;
        }

        if (Creature* pProudwell = GetSingleCreatureFromStorage(NPC_AGENT_PROUDWELL, true))
        {
            if (Creature* summon = pProudwell->SummonCreature(spawnId, spawnPos.x, spawnPos.y, spawnPos.z, spawnPos.o, spawnType, despawnTimer))
            {
                if (spawnScriptTextId)
                    DoScriptText(spawnScriptTextId, summon);

                if (formationCreatureEntry)
                {
                    if (Creature* add = summon->SummonCreature(formationCreatureEntry, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), 0.0f, spawnType, despawnTimer))
                        add->GetMotionMaster()->MoveFollow(summon, 5.f, 220.f * float(M_PI) / 180.0f, true);

                    if (Creature* add = summon->SummonCreature(formationCreatureEntry, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), 0.0f, spawnType, despawnTimer))
                        add->GetMotionMaster()->MoveFollow(summon, 5.f, 140.f * float(M_PI) / 180.0f, true);

                    if (Creature* add = summon->SummonCreature(formationCreatureEntry, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), 0.0f, spawnType, despawnTimer))
                        add->GetMotionMaster()->MoveFollow(summon, 5.f, 180.f * float(M_PI) / 180.0f, true);

                    if (Creature* add = summon->SummonCreature(formationCreatureEntry, summon->GetPositionX(), summon->GetPositionY(), summon->GetPositionZ(), 0.0f, spawnType, despawnTimer))
                        add->GetMotionMaster()->MoveFollow(summon, 5.f, 100.f * float(M_PI) / 180.0f, true);

                    float x, y, z;
                    float ori = 3.6f;
                    if (urand(0, 1))
                    {
                        summon->GetRandomPoint(allyGuardPos.x, allyGuardPos.y, allyGuardPos.z, 2.0f, x, y, z);
                        ori = 2.7f;
                    }
                    else
                        summon->GetRandomPoint(hordeGuardPos.x, hordeGuardPos.y, hordeGuardPos.z, 2.0f, x, y, z);
                    summon->SetRespawnCoord(x, y, z, ori);
                    summon->GetMotionMaster()->MovePoint(0, x, y, z, FORCED_MOVEMENT_RUN, true);
                }

                if (isEnemy)
                {
                    float x, y, z;
                    summon->GetRandomPoint(centerBattlePos.x, centerBattlePos.y, centerBattlePos.z, 20.0f, x, y, z);
                    summon->SetRespawnCoord(x, y, z, 1.0f);
                    summon->GetMotionMaster()->MovePoint(0, x, y, z, isBoss ? FORCED_MOVEMENT_WALK : FORCED_MOVEMENT_RUN, true);
                }

                if (isSoldier)
                {
                    bool isAlly = true;
                    switch (spawnId)
                    {
                    case NPC_ARGENT_GUARDIAN:
                    case NPC_ARGENT_HUNTER:
                        isAlly = false;
                        break;
                    }
                    float x, y, z;
                    if (isAlly)
                    {
                        if (urand(0, 1))
                            summon->GetRandomPoint(allyGuardPos.x, allyGuardPos.y, allyGuardPos.z, 5.0f, x, y, z);
                        else
                            summon->GetRandomPoint(allyGuardPos2.x, allyGuardPos2.y, allyGuardPos2.z, 5.0f, x, y, z);
                    }
                    else
                    {
                        if (urand(0, 1))
                            summon->GetRandomPoint(hordeGuardPos.x, hordeGuardPos.y, hordeGuardPos.z, 5.0f, x, y, z);
                        else
                            summon->GetRandomPoint(hordeGuardPos2.x, hordeGuardPos2.y, hordeGuardPos2.z, 5.0f, x, y, z);
                    }
                    summon->SetRespawnCoord(x, y, z, isAlly ? 2.7f : 3.6f);
                    summon->GetMotionMaster()->MovePoint(0, x, y, z, FORCED_MOVEMENT_RUN, true);
                }
            }
        }
    }

    void OnEventHappened(uint16 event_id, bool activate, bool resume) override
    {
        if (event_id != GAME_EVENT_BEFORE_THE_STORM)
            return;

        DespawnAdds();

        if (activate && !resume)
        {
            ResetTimer(EVENT_SPAWN, 60000);
            ResetTimer(EVENT_SPAWN_BOSS, 90000);
            ResetTimer(EVENT_REINFORCEMENTS_NEEDED, 30000);
            ResetTimer(EVENT_SPAWN_SMALL_REINFORCEMENTS, 1000);
        }
        else
        {
            ResetAllTimers();
        }
    }

    void Update(uint32 diff) override
    {
        UpdateTimers(diff);

        if (m_shadeData.Update(diff))
        {
            // Brill
            if (Creature* matron = instance->GetCreature(m_npcEntryGuidStore[NPC_MASKED_ORPHAN_MATRON]))
                matron->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, matron, matron);
            // Goldshire & Kharanos
            for (ObjectGuid guid : m_npcEntryGuidCollection[NPC_COSTUMED_ORPHAN_MATRON])
                if (Creature* matron = instance->GetCreature(guid))
                    matron->AI()->SendAIEvent(AI_EVENT_CUSTOM_A, matron, matron);
        }
    }

    uint32 GetData(uint32 type) const override
    {
        if (type >= TYPE_SHADE_OF_THE_HORSEMAN_ATTACK_PHASE && type <= TYPE_SHADE_OF_THE_HORSEMAN_MAX)
            return m_shadeData.HandleGetData(type);
        return 0;
    }

    void SetData(uint32 type, uint32 data) override
    {
        if (type >= TYPE_SHADE_OF_THE_HORSEMAN_ATTACK_PHASE && type <= TYPE_SHADE_OF_THE_HORSEMAN_MAX)
            return m_shadeData.HandleSetData(type, data);
    }
};

struct go_infernaling_summoner_portal_hound : public GameObjectAI
{
    go_infernaling_summoner_portal_hound(GameObject* go) : GameObjectAI(go)
    {
        m_uiSummonTimer = 15000;
    }

    uint32 m_uiSummonTimer;

    void UpdateAI(const uint32 uiDiff) override
    {
        if (!m_go->IsSpawned())
            return;

        if (m_uiSummonTimer <= uiDiff)
        {
            if (Creature* pProudwell = ((ScriptedInstance*)m_go->GetMap()->GetInstanceData())->GetSingleCreatureFromStorage(NPC_AGENT_PROUDWELL))
            {
                pProudwell->CastSpell(pProudwell, SPELL_SUMMON_INFERNALING_PORTAL_HOUND, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, m_go->GetObjectGuid());
            }
            m_uiSummonTimer = urand(60000, 120000);
        }
        else
            m_uiSummonTimer -= uiDiff;
    }
};

GameObjectAI* GetAI_go_infernaling_summoner_portal_hound(GameObject* go)
{
    return new go_infernaling_summoner_portal_hound(go);
}

// does not work currently - need to handle spell 33710 somehow when it hits/activates either object 183358 or 183357?
bool GOUse_go_infernaling_summoner_portal_hound(Player* /*pPlayer*/, GameObject* pGo)
{
    ScriptedInstance* pInstance = (ScriptedInstance*)pGo->GetInstanceData();

    if (!pInstance)
        return false;

    if (Creature* pProudwell = pInstance->GetSingleCreatureFromStorage(NPC_AGENT_PROUDWELL))
    {
        pProudwell->CastSpell(pProudwell, SPELL_SUMMON_INFERNALING_PORTAL_HOUND, TRIGGERED_OLD_TRIGGERED, nullptr, nullptr, pGo->GetObjectGuid());
    }

    return false;
}

struct npc_agent_proudwell : public ScriptedAI
{
    npc_agent_proudwell(Creature* pCreature) : ScriptedAI(pCreature) { }

    void Reset() override {}

    void SummonedCreatureDespawn(Creature* pSummoned) override
    {
        uint32 despawnScriptTextId = 0;
        switch (pSummoned->GetEntry())
        {
            case NPC_LORD_MARSHAL_RAYNOR: despawnScriptTextId = LMR_DESPAWN; break;
            case NPC_JUSTINIUS_THE_HARBINGER: despawnScriptTextId = JTH_DESPAWN; break;
            case NPC_MELGROMM_HIGHMOUNTAIN: despawnScriptTextId = MH_DESPAWN; break;
        }

        world_map_eastern_kingdoms* pInstance = (world_map_eastern_kingdoms*)pSummoned->GetInstanceData();

        if (pInstance)
            pInstance->_spawnSupport.erase(pSummoned->GetObjectGuid());

        //if (despawnScriptTextId && pSummoned->IsAlive())
        //    DoScriptText(despawnScriptTextId, pSummoned);
    }
};

UnitAI* GetAI_npc_agent_proudwell(Creature* pCreature)
{
    return new npc_agent_proudwell(pCreature);
}

InstanceData* GetInstanceData_world_map_eastern_kingdoms(Map* pMap)
{
    return new world_map_eastern_kingdoms(pMap);
}

void AddSC_world_eastern_kingdoms()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "world_map_eastern_kingdoms";
    pNewScript->GetInstanceData = &GetInstanceData_world_map_eastern_kingdoms;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "go_infernaling_summoner_portal_hound";
    pNewScript->GetGameObjectAI = &GetAI_go_infernaling_summoner_portal_hound;
    pNewScript->pGOUse = &GOUse_go_infernaling_summoner_portal_hound;
    pNewScript->RegisterSelf();

    pNewScript = new Script;
    pNewScript->Name = "npc_agent_proudwell";
    pNewScript->GetAI = &GetAI_npc_agent_proudwell;
    pNewScript->RegisterSelf();
}

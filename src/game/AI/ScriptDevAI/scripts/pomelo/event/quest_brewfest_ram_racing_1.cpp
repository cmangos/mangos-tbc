/**
 *
 * @File : quest_brewfest_ram_racing_1.h
 * @Authors : yukozh
 * @Date : 09/26/2019
 *
 **/

#include "AI/ScriptDevAI/include/precompiled.h"
#include "Globals/ObjectMgr.h"

enum RamSpeed : uint8
{
    SPEED_LOW,
    SPEED_MEDIUM,
    SPEED_HIGH
};

uint8 speed_objid_map[3] = { 1, 0 ,2 };
float speed_rates[3] = { 0.2f, 1.2f, 2.0f };

struct RamStatusData 
{
    uint8        speed;
    uint32       keepSpeedLeftMs;
    uint32       keepSpeedPastMs;
    const Quest* quest;
    Creature*    creature;
};

std::unordered_map<ObjectGuid, RamStatusData> map;

bool OnItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
    const auto pData = &map[pPlayer->GetObjectGuid()];
    if (pData)
    {
        pPlayer->CastSpell(nullptr, 42924, TRIGGERED_OLD_TRIGGERED);
        pData->keepSpeedLeftMs += 5000;
        if (pData->keepSpeedLeftMs >= 10000)
        {
            if (pData->speed < SPEED_HIGH)
            {
                pData->speed += 1;
                pData->keepSpeedLeftMs = 5000;
                pData->keepSpeedPastMs = 0;
                pPlayer->SetSpeedRate(MOVE_RUN, speed_rates[pData->speed], true);
            }
            else
            {
                pData->keepSpeedLeftMs = 10000;
            }
        }
    }
    return true;
}

bool OnAcceptQuest(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    RamStatusData data;
    data.speed = SPEED_LOW;
    data.keepSpeedLeftMs = 0;
    data.keepSpeedPastMs = 0;
    data.quest = pQuest;
    data.creature = pCreature;
    pCreature->CastSpell(pPlayer, 42149, TRIGGERED_OLD_TRIGGERED);
    map[pPlayer->GetObjectGuid()] = data;
    return true;
}

void OnQuestEnd(const Quest* pQuest, Player* pPlayer)
{
    auto move_auras = pPlayer->GetAurasByType(AuraType::SPELL_AURA_FORCE_MOVE_FORWARD);
    for (auto itr : move_auras)
    {
        pPlayer->RemoveAura(itr);
    }

    auto speed_auras = pPlayer->GetAurasByType(AuraType::SPELL_AURA_MOD_DECREASE_SPEED);
    for (auto itr : speed_auras)
    {
        pPlayer->RemoveAura(itr);
    }

    pPlayer->SetSpeedRate(MOVE_RUN, 1.0f);
    auto pData = &map[pPlayer->GetObjectGuid()];
    auto pCreature = pData->creature;
    pCreature->CastSpell(pPlayer, 44358, TRIGGERED_OLD_TRIGGERED);
}

bool OnRewardedQuest(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
{
    OnQuestEnd(pQuest, pPlayer);
    map.erase(pPlayer->GetObjectGuid());
    return true;
}

void SetFinished(const Quest* pQuest, Player* pPlayer, uint8 i)
{
    int32 creature = pQuest->ReqCreatureOrGOId[i];
    uint32 creaturecount = pQuest->ReqCreatureOrGOCount[i];

    if (uint32 spell_id = pQuest->ReqSpell[i])
    {
        for (uint16 z = 0; z < creaturecount; ++z)
            pPlayer->CastedCreatureOrGO(creature, ObjectGuid(), spell_id);
    }
    else if (creature > 0)
    {
        if (CreatureInfo const* cInfo = ObjectMgr::GetCreatureTemplate(creature))
            for (uint16 z = 0; z < creaturecount; ++z)
                pPlayer->KilledMonster(cInfo, ObjectGuid());
    }
    else if (creature < 0)
    {
        for (uint16 z = 0; z < creaturecount; ++z)
            pPlayer->CastedCreatureOrGO(-creature, ObjectGuid(), 0);
    }

    if (pPlayer->CanCompleteQuest(pQuest->GetQuestId()))
    {
        pPlayer->CompleteQuest(pQuest->GetQuestId());
        OnQuestEnd(pQuest, pPlayer);
    }
    else
    {
        pPlayer->UpdateForQuestWorldObjects();
    }
}

struct quest_brewfest_ram_racing_1 : public ScriptedAI
{
    quest_brewfest_ram_racing_1(Creature* creature) : ScriptedAI(creature)
    {
        Reset();
    }

    void Reset() override
    {
        map.clear();
    }

    void UpdateAI(const uint32 diff) override
    {
        for (auto itr = map.begin(); itr != map.end(); ++itr)
        {
            Player* pPlayer = sObjectMgr.GetPlayer(itr->first);
            if (pPlayer)
            {
                const auto pData = &itr->second;

                auto debug = pPlayer->GetAura(43883, SpellEffectIndex::EFFECT_INDEX_0);
                if (pData->keepSpeedPastMs > 0 && !debug)
                {
                    OnQuestEnd(pData->quest, pPlayer);
                    continue;
                }

                pData->keepSpeedPastMs += diff;
                if (pData->keepSpeedPastMs >= 8000)
                {
                    SetFinished(pData->quest, pPlayer, speed_objid_map[pData->speed]);
                }
                if (pData->speed > SPEED_LOW)
                {
                    if (pData->keepSpeedLeftMs < diff)
                    {
                        pData->keepSpeedLeftMs = 5000;
                        pData->keepSpeedPastMs = 0;
                        --pData->speed;
                        pPlayer->SetSpeedRate(MOVE_RUN, speed_rates[pData->speed], true);
                    }
                    else
                    {
                        pData->keepSpeedLeftMs -= diff;
                    }
                }
            }
        }
        ScriptedAI::UpdateAI(diff);
    }
};

UnitAI* GetAI_quest_brewfest_ram_racing_1(Creature* pCreature)
{
    return new quest_brewfest_ram_racing_1(pCreature);
}

void AddSC_quest_brewfest_ram_racing_1()
{
    Script* pNewScript = new Script;
    pNewScript->Name = "quest_brewfest_ram_racing_1";
    pNewScript->GetAI = &GetAI_quest_brewfest_ram_racing_1;
    pNewScript->pQuestAcceptNPC = &OnAcceptQuest;
    pNewScript->pQuestRewardedNPC = &OnRewardedQuest;
    pNewScript->RegisterSelf();

    Script* pNewScript2 = new Script;
    pNewScript2->Name = "item_brewfest_ram_racing_1";
    pNewScript2->pItemUse = &OnItemUse;
    pNewScript2->RegisterSelf();
}
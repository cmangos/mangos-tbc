/**
 *
 * @File : item_multi_talent.h
 * @Authors : yukozh
 * @Date : 09/19/2019
 *
 **/

#ifndef SC_ITEM_MULTI_TALENT_H
#define SC_ITEM_MULTI_TALENT_H

#include "AI/ScriptDevAI/include/sc_item_teleport.h"

enum MultiTalentCostType
{
    MULTI_TALENT_COST_FREE             = 0,
    MULTI_TALENT_COST_MONEY            = 1,
    MULTI_TALENT_COST_CUSTOM_CURRENCY  = 2
};

#define CONFIG_MULTI_TALENT_COST_TYPE       "multitalent.cost.type"
#define CONFIG_MULTI_TALENT_COST_CURRENCY   "multitalent.cost.currency"
#define CONFIG_MULTI_TALENT_COST_VALUE      "multitalent.cost.value"
#define CONFIG_MULTI_TALENT_PERMISSION      "multitalent.permission"
#define CONFIG_MULTI_TALENT_MAX             "multitalent.template.max"
 
void GenerateMultiTalentGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandleMultiTalentGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
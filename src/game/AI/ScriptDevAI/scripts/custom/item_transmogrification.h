/**
 *
 * @File : item_transmogrification.h
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#ifndef SC_ITEM_TRANSMOGRIFICATION_H
#define SC_ITEM_TRANSMOGRIFICATION_H

#include "AI/ScriptDevAI/include/sc_item_teleport.h"

enum TransmogCostType
{
    TRANSMOG_COST_FREE             = 0,
    TRANSMOG_COST_MONEY            = 1,
    TRANSMOG_COST_CUSTOM_CURRENCY  = 2
};

#define CONFIG_TRANSMOG_COST_TYPE       "transmog.cost.type"
#define CONFIG_TRANSMOG_COST_CURRENCY   "transmog.cost.currency"
#define CONFIG_TRANSMOG_COST_VALUE      "transmog.cost.value"
#define CONFIG_TRANSMOG_PERMISSION      "transmog.permission"

void GenerateTransmogrificationGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandleTransmogrificationGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
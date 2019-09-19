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

void GenerateTransmogrificationGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandleTransmogrificationGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
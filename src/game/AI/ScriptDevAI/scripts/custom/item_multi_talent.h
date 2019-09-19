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

void GenerateMultiTalentGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandleMultiTalentGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
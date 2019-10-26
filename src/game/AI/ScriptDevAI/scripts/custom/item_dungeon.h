/**
 *
 * @File : item_dungeon.h
 * @Authors : yukozh
 * @Date : 10/06/2019
 *
 **/

#ifndef SC_ITEM_DUNGEON_H
#define SC_ITEM_DUNGEON_H

#include "AI/ScriptDevAI/include/sc_item_teleport.h"
 
void GenerateDungeonGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandleDungeonGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
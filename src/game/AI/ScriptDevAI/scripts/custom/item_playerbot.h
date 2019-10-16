/**
 *
 * @File : item_playerbot.h
 * @Authors : yukozh
 * @Date : 10/13/2019
 *
 **/
#ifdef BUILD_PLAYERBOT
#ifndef SC_ITEM_PLAYERBOT_H
#define SC_ITEM_PLAYERBOT_H

#include "AI/ScriptDevAI/include/sc_item_teleport.h"
#include "PlayerBot/Base/PlayerbotClassAI.h"

struct AccountCharacter
{
    uint32       guid;
    std::string  name;
    bool         hired;
    JOB_TYPE     job;
    uint8        race;
};

void RemovePlayerBotCachedCharacters(Player* pPlayer);
void LoadAndCachePlayerBotCharacters(Player* pPlayer);
void GeneratePlayerBotGossipMenu(Player* pPlayer, ObjectGuid guid);
bool HandlePlayerBotGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action);

#endif
#endif
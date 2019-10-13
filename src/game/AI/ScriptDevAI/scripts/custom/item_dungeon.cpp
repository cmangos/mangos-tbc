/**
 *
 * @File : item_dungeon.cpp
 * @Authors : yukozh
 * @Date : 10/06/2019
 *
 **/

#include "item_dungeon.h"
#include "Pomelo/DBConfigMgr.h"
#include "Pomelo/CustomCurrencyMgr.h"
#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "Tools/Language.h"

#define ADVANCED_DIFFICULTY_COUNT 2

void GenerateDungeonGossipMenu(Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

    for (uint8 i = 0; i < ADVANCED_DIFFICULTY_COUNT; ++i)
    {
        auto str = std::string(pPlayer->GetSession()->GetMangosString(LANG_POMELO_DIFFICULTY_NORMAL + i));
        if (pPlayer->GetAdvancedDifficulty() == AdvancedDifficulty(i))
        {
            str.append(pPlayer->GetSession()->GetMangosString(LANG_MULTI_TALENT_TEMPLATE_CURRENT));
        }
	    pPlayer->ADD_GOSSIP_ITEM(0, str.c_str(), 80008, i);
    }
	pPlayer->SEND_GOSSIP_MENU(100000 - 1013, guid);
}

bool HandleDungeonGossipMenuSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	if (sender != 80008) return false;

    if (action >= MAX_ADVANCED_DIFFICULTY)
        return true;

    if (pPlayer->GetMap()->IsDungeon() || pPlayer->GetMap()->IsRaid())
    {
        pPlayer->GetSession()->SendNotification(LANG_DIFFICULTY_WRONG_MAP);
        pPlayer->PlayerTalkClass->CloseGossip();
        return true;
    }

    Group* pGroup = pPlayer->GetGroup();
    if (pGroup)
    {
        if (!pGroup->IsLeader(pPlayer->GetObjectGuid()))
        {
		    pPlayer->GetSession()->SendNotification(LANG_POMELO_DIFFICULTY_NEED_GLEADER);
		    pPlayer->PlayerTalkClass->CloseGossip();
            return true;
        }
        pGroup->SetAdvancedDifficulty(AdvancedDifficulty(action));
    }
    else
    {
        pPlayer->SetAdvancedDifficulty(AdvancedDifficulty(action));
        pPlayer->SendDungeonDifficulty(true);
        ChatHandler(pPlayer).PSendSysMessage(
            LANG_POMELO_DIFFICULTY_CHANGED,
            pPlayer->GetSession()->GetMangosString(LANG_POMELO_DIFFICULTY_NORMAL + action));
    }

	pPlayer->PlayerTalkClass->CloseGossip();
    return true;
}
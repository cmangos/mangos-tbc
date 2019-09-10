/**
 *
 * @File : item_teleport.cpp
 * @Authors : yukozh
 * @Date : 09/09/2019
 *
 **/

#include "AI/ScriptDevAI/include/sc_gossip.h"
#include "AI/ScriptDevAI/include/precompiled.h"
#include "AI/ScriptDevAI/include/sc_item_teleport.h"

#define SPELL_VISUAL_TELEPORT   35517

using namespace Teleport;

void AddFilteredGossipMenuForPlayer(uint32 menu_id, Player* pPlayer, ObjectGuid guid, TELE_ORDER order)
{
	size_t length = map_count[menu_id];
	for (size_t i = 0; i < length; ++i)
	{
		auto item = map_item[menu_id][i];
		if (order != item.camp_order) continue;
		pPlayer->ADD_GOSSIP_ITEM(item.icon, item.text, menu_id, item.action_id);
	}
}

bool IsAlliance(uint8 race)
{
	return race == 1 || race == 3 || race == 4 || race == 7 || race == 11;
}

void GenerateGossipMenu(uint32 menu_id, Player* pPlayer, ObjectGuid guid)
{
	// Clear menu
	pPlayer->PlayerTalkClass->ClearMenus();

	if (map_order[menu_id])
	{
		if (IsAlliance(pPlayer->getRace()))
		{
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::ALLIANCE);
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::HORDE);
		}
		else
		{
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::HORDE);
			AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::ALLIANCE);
		}
	}
	AddFilteredGossipMenuForPlayer(menu_id, pPlayer, guid, TELE_ORDER::NONE);
	pPlayer->SEND_GOSSIP_MENU(100000 - menu_id, guid);
}

void TeleportTo(Player* const player, const uint16& map,
	const float& X, const float& Y, const float& Z, const float& orient)
{
	// Play the teleport spell before teleport player
	player->Unmount();
	player->RemoveSpellsCausingAura(SPELL_AURA_MOUNTED);
	player->CastSpell(player, SPELL_VISUAL_TELEPORT, TRIGGERED_OLD_TRIGGERED);
	player->TeleportTo(map, X, Y, Z, orient);
}

bool GossipSelect(Player* pPlayer, Object* pObj, uint32 sender, uint32 action)
{
	auto item = map_item[sender][action];
	// TODO: Support more functions
	switch (item.function)
	{
	case TELE_FUNC::SHOW_SUB_MENU:
		GenerateGossipMenu(item.trigger_menu, pPlayer, pObj->GetObjectGuid());
		break;
	case TELE_FUNC::TELEPORT:
		TeleportTo(pPlayer, item.teleport_map, item.teleport_x, item.teleport_y, item.teleport_z, 0);
		pPlayer->PlayerTalkClass->CloseGossip();
		break;
	default:
		return false;
		break;
	}

	return true;
}

bool GossipHello(Player* pPlayer, Creature* pCreature)
{
	GenerateGossipMenu(0, pPlayer, pCreature->GetObjectGuid());
	return true;
}

bool GossipItemUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
{
	GenerateGossipMenu(0, pPlayer, pItem->GetObjectGuid());
	return true;
}

bool GossipSelectCreature(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
{
	return GossipSelect(pPlayer, pCreature, sender, action);
}

bool GossipSelectItem(Player* pPlayer, Item* pItem, uint32 sender, uint32 action)
{
	return GossipSelect(pPlayer, pItem, sender, action);
}

void AddSC_item_teleport()
{
	BuildTeleportMenuMap();
    Script *newscript;

    newscript = new Script;
    newscript->Name="item_teleport";
	newscript->pItemUse = &GossipItemUse;
	newscript->pGossipHello = &GossipHello;
	newscript->pGossipSelect = &GossipSelectCreature;
	newscript->pGossipSelectItem = &GossipSelectItem;
    newscript->RegisterSelf();
}

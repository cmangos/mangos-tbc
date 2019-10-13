/**
 *
 * @File : sc_item_teleport.h
 * @Authors : yukozh
 * @Date : 09/09/2019
 *
 **/


#ifndef SC_ITEM_TELEPORT_H
#define SC_ITEM_TELEPORT_H

#define TELE_ITEM  Teleport::TeleportMenuItem
#define TELE_FUNC  Teleport::TeleportMenuItemFunction
#define TELE_ORDER Teleport::TeleportMenuItemFactionOrder
#define TELE_COST  Teleport::CostType

namespace Teleport
{
	enum TeleportMenuItemFunction
	{
		SHOW_SUB_MENU         = 0,
		TELEPORT              = 1,
		STORE                 = 2,
		BANK                  = 3,
		ACTIVATE_FLIGHT       = 4,
		QUERY_CURRENCY        = 5,
		TRANSMOGRIFY_MENU     = 6,
		MULTI_TALENT_MENU     = 7,
        TRAIN                 = 8,
		TRAIN_CLASS           = 9,
		DAILY_REWARD          = 10,
		INCREASE_WEAPON_SKILL = 11,
        BUY_TIER_THREE        = 12,
        DUNGEON_SETTINGS      = 13,
        PLAYERBOT             = 14
	};

	enum TeleportMenuItemFactionOrder
	{
		NONE     = 0,
		ALLIANCE = 1,
		HORDE    = 2
	};

	enum CostType
	{
		COST_FREE             = 0,
		COST_MONEY            = 1,
		COST_CUSTOM_CURRENCY  = 2
	};

	struct TeleportMenuItem
	{
		uint32                       menu_id;
		uint32                       action_id;
		uint32                       icon;
		std::string                  text;
		TeleportMenuItemFunction     function;
		uint32                       teleport_map;
		float                        teleport_x;
		float                        teleport_y;
		float                        teleport_z;
		uint32                       cost_amount;
		CostType                     cost_type;
		uint32                       cost_currency_id;
		uint32                       level_required;
		uint32                       permission_required;
		TeleportMenuItemFactionOrder faction_order;
		uint32                       trigger_menu;
	};

	void BuildTeleportMenuMap();
	extern std::unordered_map<uint32, std::vector<TELE_ITEM>> map_item;
	extern std::unordered_map<uint32, bool> map_order;
}

#endif


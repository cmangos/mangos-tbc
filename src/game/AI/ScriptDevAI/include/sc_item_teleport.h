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
#define TELE_ORDER Teleport::TeleportMenuItemCampOrder

namespace Teleport
{
	enum TeleportMenuItemFunction
	{
		SHOW_SUB_MENU        = 0,
		TELEPORT             = 1,
		STORE                = 2,
		BANK                 = 3,
		ACTIVATE_FLIGHT      = 4,
		QUERY_CURRENCY       = 5,
		TRANSMOGRIFY_MENU    = 6,
	};

	enum TeleportMenuItemCampOrder
	{
		NONE     = 0,
		ALLIANCE = 1,
		HORDE    = 2
	};

	struct TeleportMenuItem
	{
		uint32                    menu_id;
		uint32                    action_id;
		uint32                    icon;
		std::string               text;
		TeleportMenuItemFunction  function;
		uint32                    teleport_map;
		float                     teleport_x;
		float                     teleport_y;
		float                     teleport_z;
		uint32                    cost_money;
		uint32                    level_required;
		uint32                    permission_required;
		TeleportMenuItemCampOrder camp_order;
		uint32                    trigger_menu;
	};

	void BuildTeleportMenuMap();
	extern std::unordered_map<uint32, std::vector<TELE_ITEM>> map_item;
	extern std::unordered_map<uint32, bool> map_order;
}

#endif


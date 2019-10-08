/**
 *
 * @File : sc_item_teleport.cpp
 * @Authors : yukozh
 * @Date : 09/09/2019
 *
 **/


#include "precompiled.h"
#include "sc_item_teleport.h"
#include "ProgressBar.h"

// Initializing maps
std::unordered_map<uint32, std::vector<TELE_ITEM>> Teleport::map_item;
std::unordered_map<uint32, bool> Teleport::map_order;

std::vector<TELE_ITEM> LoadTeleportTemplate()
{
	// Load teleport menu items from database
	QueryResult* qr = WorldDatabase.PQuery(
	" SELECT `menu_id`, `action_id`, `icon`, `menu_item_text`, `function`, "
	" `teleport_map`, `teleport_x`, `teleport_y`, `teleport_z`, `cost_amount`, "
	" `cost_type`, `cost_custom_currency_id`, `level_required`, "
    "`permission_required`, `trigger_menu`, `faction_order` "
	" FROM `pomelo_teleport_template` ORDER BY `menu_id`, `action_id` "
	);
	std::vector<TELE_ITEM> ret;
	if (qr)
	{
		outstring_log("SD2: %u teleport menu items loaded...", qr->GetRowCount());
		do
		{
			Field* field = qr->Fetch();
			TELE_ITEM item;
			item.menu_id = field[0].GetUInt32();
			item.action_id = field[1].GetUInt32();
			item.icon = field[2].GetUInt32();
			item.text = field[3].GetCppString();
			item.function = (TELE_FUNC)field[4].GetUInt32();
			item.teleport_map = field[5].GetUInt32();
			item.teleport_x = field[6].GetFloat();
			item.teleport_y = field[7].GetFloat();
			item.teleport_z = field[8].GetFloat();
			item.cost_amount = field[9].GetUInt32();
            item.cost_type = (TELE_COST)field[10].GetUInt32();
            item.cost_currency_id = field[11].GetUInt32();
			item.level_required = field[12].GetUInt32();
			item.permission_required = field[13].GetUInt32();
			item.trigger_menu = field[14].GetUInt32();
			item.faction_order = (TELE_ORDER)field[15].GetUInt32();
			ret.push_back(item);
		} while (qr->NextRow());

		delete qr;
	}

	return ret;
}

void Teleport::BuildTeleportMenuMap()
{
    map_item.clear();
    map_order.clear();
	auto result = LoadTeleportTemplate();

	// Grouping the menu items
	for (size_t i = 0; i < result.size(); ++i)
	{
		map_item[result[i].menu_id].push_back(result[i]);
		if (result[i].faction_order > TELE_ORDER::NONE)
		{
			map_order[result[i].menu_id] = true;
		}
	}
}
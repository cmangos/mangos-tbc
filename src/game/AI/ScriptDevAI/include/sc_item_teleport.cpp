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
std::map<uint32, TELE_ITEM[20]> Teleport::map_item = std::map<uint32, TELE_ITEM[20]>();
std::map<uint32, size_t> Teleport::map_count = std::map<uint32, size_t>();
std::map<uint32, bool> Teleport::map_order = std::map<uint32, bool>();

TELE_ITEM* LoadTeleportTemplate(size_t& length)
{
	// Load teleport menu items from database
	auto qr = WorldDatabase.PQuery(
	" SELECT `menu_id`, `action_id`, `icon`, `menu_item_text`, `function`, "
	" `teleport_map`, `teleport_x`, `teleport_y`, `teleport_z`, `cost_money`, "
	" `level_required`, `permission_required`, `trigger_menu`, `camp_order` "
	" FROM `pomelo_teleport_template` order by `menu_id`, `action_id` "
	);

	if (qr)
	{
		length = qr->GetRowCount();
		outstring_log("SD2: %u teleport menu items loaded...", length);
		auto result = new TELE_ITEM[length];
		auto i = 0;
		do
		{
			Field* field = qr->Fetch();
			result[i] = TELE_ITEM();
			result[i].menu_id = field[0].GetUInt32();
			result[i].action_id = field[1].GetUInt32();
			result[i].icon = field[2].GetUInt32();
			result[i].text = field[3].GetCppString();
			result[i].function = (TELE_FUNC)field[4].GetUInt32();
			result[i].teleport_map = field[5].GetUInt32();
			result[i].teleport_x = field[6].GetFloat();
			result[i].teleport_y = field[7].GetFloat();
			result[i].teleport_z = field[8].GetFloat();
			result[i].cost_money = field[9].GetUInt32();
			result[i].level_required = field[10].GetUInt32();
			result[i].permission_required = field[11].GetUInt32();
			result[i].trigger_menu = field[12].GetUInt32();
			result[i].camp_order = (TELE_ORDER)field[13].GetUInt32();
			++i;
		} while (qr->NextRow());

		delete qr;
		return result;
	}
	else
	{
		length = 0;
		return nullptr;
	}
}

void Teleport::BuildTeleportMenuMap()
{
	size_t length;
	auto result = LoadTeleportTemplate(length);

	// Grouping the menu items
	for (size_t i = 0; i < length; ++i)
	{
		map_item[result[i].menu_id][map_count[result[i].menu_id]++] = result[i];
		if (result[i].camp_order > TELE_ORDER::NONE)
		{
			map_order[result[i].menu_id] = true;
		}
	}
}
/**
 *
 * @File : TransmogrificationMgr.cpp
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#include "TransmogrificationMgr.h"
#include "Entities/Item.h"
#include "Globals/ObjectMgr.h"

std::unordered_map<uint32, uint32> itemguid_character_map;
std::unordered_map<uint32, std::map<uint32, TransmogrificationData>> character_itemguid_transmogdata_map; // map[user][item-id] = transmog-data
std::unordered_map<uint32, uint32> transmogid_item_map;
std::unordered_map<uint32, TransmogrificationData> transmogid_transmogdata_map;
std::unordered_map<uint32, std::map<EquipmentSlots, TransmogrificationTempStore>> character_slot_display_map;

void TransmogrificationMgr::ApplyTransmogrification(Player* pPlayer, Item* pItem)
{
	uint32 character_id = pPlayer->GetGUIDLow();
	if (pItem)
	{
		if (itemguid_character_map.find(pItem->GetGUIDLow()) == itemguid_character_map.end())
		{
			pPlayer->SetUInt64Value(PLAYER_VISIBLE_ITEM_1_0 + (pItem->GetSlot() * MAX_VISIBLE_ITEM_OFFSET), pItem->GetEntry());
			return;
		}

		auto fakeEntry = ToItemEntry(character_itemguid_transmogdata_map[character_id][pItem->GetGUIDLow()].entry);
		pPlayer->SetUInt64Value(PLAYER_VISIBLE_ITEM_1_0 + (pItem->GetSlot() * MAX_VISIBLE_ITEM_OFFSET), fakeEntry);
	}
}

void TransmogrificationMgr::ApplyTransmogrification(Player* pPlayer, EquipmentSlots slot)
{
	uint32 character_id = pPlayer->GetGUIDLow();
	Item* pItem = pPlayer->GetItemByPos(INVENTORY_SLOT_BAG_0, slot);
	ApplyTransmogrification(pPlayer, pItem);
}

void TransmogrificationMgr::ApplyTransmogrification(Player* pPlayer)
{
	// If there is no transmog data then return.
	uint32 character_id = pPlayer->GetGUIDLow();
	if (itemguid_character_map.find(character_id) == itemguid_character_map.end())
	{
		return;
	}

	for (uint32 i = EQUIPMENT_SLOT_START; i < EQUIPMENT_SLOT_END; ++i)
	{
		ApplyTransmogrification(pPlayer, (EquipmentSlots)i);
	}
}

void TransmogrificationMgr::OnLogin(uint32 characterId)
{
	QueryResult* result = CharacterDatabase.PQuery(
		"SELECT `entry`, `item_instance_guid`, `model`, `owner_guid`, "
        "`item_template_id`, `sheath`, `material` "
		"FROM `pomelo_transmogrification` "
		"WHERE `owner_guid` = %u", characterId);

	if (result)
	{
		do
		{
			Field* field = result->Fetch();
			TransmogrificationData data;
			data.entry = field[0].GetUInt32();
			data.item_instance_guid = field[1].GetUInt32();
			data.model = field[2].GetUInt32();
			data.owner_guid = field[3].GetUInt32();
			data.item_template_id = field[4].GetUInt32();
            data.sheath = field[5].GetUInt32();
            data.material = field[6].GetUInt32();

			itemguid_character_map[data.item_instance_guid] = data.owner_guid;
			character_itemguid_transmogdata_map[data.owner_guid][data.item_instance_guid] = data;
			transmogid_item_map[data.entry] = data.item_template_id;
			transmogid_transmogdata_map[data.entry] = data;
		} while (result->NextRow());
	}

    delete result;
}

void TransmogrificationMgr::OnLogout(uint32 characterId)
{
	for (auto i = character_itemguid_transmogdata_map[characterId].begin(); i != character_itemguid_transmogdata_map[characterId].end(); ++i)
	{
		transmogid_item_map.erase(i->second.entry);
		transmogid_transmogdata_map.erase(i->second.entry);
	}
	character_itemguid_transmogdata_map.erase(characterId);
	character_slot_display_map.erase(characterId);
}

uint32 TransmogrificationMgr::ToItemEntry(uint32 fakeEntry)
{
	return fakeEntry + TRANSMOGRIFICATION_ENTRY_OFFSET;
}

uint32 TransmogrificationMgr::ToFakeEntry(uint32 itemEntry)
{
	return itemEntry - TRANSMOGRIFICATION_ENTRY_OFFSET;
}

bool TransmogrificationMgr::IsFakeEntry(uint32 entry)
{
	return entry > TRANSMOGRIFICATION_ENTRY_OFFSET;
}

uint32 TransmogrificationMgr::GetModelId(uint32 fakeId)
{
	return transmogid_transmogdata_map[ToFakeEntry(fakeId)].model;
}

uint32 TransmogrificationMgr::GetMaterial(uint32 fakeId)
{
    return transmogid_transmogdata_map[ToFakeEntry(fakeId)].material;
}

uint32 TransmogrificationMgr::GetSheath(uint32 fakeId)
{
    return transmogid_transmogdata_map[ToFakeEntry(fakeId)].sheath;
}

const ItemPrototype* TransmogrificationMgr::GetOriginItemProto(uint32 fakeId)
{
	auto fakeEntry = transmogid_item_map[ToFakeEntry(fakeId)];
	return sObjectMgr.GetItemPrototype(fakeEntry);
}

uint32 TransmogrificationMgr::GetModelIdByItemInstanceId(uint32 itemGuid)
{
	uint32 owner_id = itemguid_character_map[itemGuid];
	return character_itemguid_transmogdata_map[owner_id][itemGuid].model;
}

bool TransmogrificationMgr::IsTransmogrified(uint32 itemGuid)
{
	return itemguid_character_map.find(itemGuid) != itemguid_character_map.end();
}

uint32 TransmogrificationMgr::GetCharacterIdByTransmogrificationId(uint32 transmogId)
{
	QueryResult* result = CharacterDatabase.PQuery(
		"SELECT `owner_guid` "
		"FROM `pomelo_transmogrification` "
		"WHERE `entry` = %u", transmogId);
	if (!result)
	{
		return 0;
	}

	Field* field = result->Fetch();

	return field[0].GetUInt32();
}

void TransmogrificationMgr::StoreDisplay(Player* pPlayer, Item* pItem)
{
	if (pItem)
	{
		TransmogrificationTempStore info;
		auto pProto = pItem->GetProto();
		info.name = std::string(pProto->Name1);
		info.display = pProto->DisplayInfoID;
		info.quality = pProto->Quality;
		info.item_template_id = pItem->GetEntry();
		info.slot = (EquipmentSlots)pItem->GetSlot();
        info.material = pProto->Material;
        info.sheath = pProto->Sheath;
		character_slot_display_map[pPlayer->GetGUIDLow()][(EquipmentSlots)pItem->GetSlot()] = info;
	}
}

std::vector<TransmogrificationTempStore> TransmogrificationMgr::GetStoredDisplays(Player* pPlayer)
{
	std::vector<TransmogrificationTempStore> ret;
	auto map = character_slot_display_map[pPlayer->GetGUIDLow()];
	for (auto i = map.begin(); i != map.end(); ++i) 
	{
		ret.push_back(i->second);
	}
	return ret;
}

void TransmogrificationMgr::ClearStoredDisplays(Player* pPlayer)
{
	character_slot_display_map.erase(pPlayer->GetGUIDLow());
}

void TransmogrificationMgr::TransmogrifyItemFromTempStore(Item* pItem, EquipmentSlots slot)
{
	Player* pPlayer = pItem->GetOwner();
	auto store = character_slot_display_map[pPlayer->GetGUIDLow()][slot];
	if (store.display)
	{
		TransmogrifyItem(pItem, store.display, store.material, store.sheath);
	}
}

void TransmogrificationMgr::TransmogrifyItem(Item* pItem, uint32 display, uint32 material, uint32 sheath)
{
	if (pItem)
	{
		CharacterDatabase.DirectPExecute(
			"INSERT INTO `pomelo_transmogrification` "
			"(`item_instance_guid`, `model`, `owner_guid`, `item_template_id`, `material`, `sheath`) "
			"VALUES (%u, %u, %u, %u, %u, %u);",
			pItem->GetGUIDLow(), display, pItem->GetOwner()->GetGUIDLow(), pItem->GetEntry(), material, sheath);
		
		// TODO: How to get inserted id in this MySQL client?
		QueryResult* result = CharacterDatabase.PQuery(
			"SELECT `entry` FROM `pomelo_transmogrification` "
			"WHERE `item_instance_guid` = %u "
			"AND `model` = %u "
			"AND `owner_guid` = %u "
			"AND `item_template_id` = %u", pItem->GetGUIDLow(), display, pItem->GetOwner()->GetGUIDLow(), pItem->GetEntry());
		if (result)
		{
			Field* field = result->Fetch();
			TransmogrificationData data;
			data.entry = field[0].GetUInt32();
			data.item_instance_guid = pItem->GetGUIDLow();
			data.model = display;
			data.owner_guid = pItem->GetOwner()->GetGUIDLow();
			data.item_template_id = pItem->GetEntry();
            data.material = material;
            data.sheath = sheath;

			itemguid_character_map[data.item_instance_guid] = data.owner_guid;
			character_itemguid_transmogdata_map[data.owner_guid][data.item_instance_guid] = data;
			transmogid_item_map[data.entry] = data.item_template_id;
			transmogid_transmogdata_map[data.entry] = data;

			ApplyTransmogrification(pItem->GetOwner(), pItem);
		}
	}
}

std::vector<TransmogrificationTempStore> TransmogrificationMgr::GetTransmogrifiedItems(Player* pPlayer)
{
	std::vector<TransmogrificationTempStore> ret;
	auto map = character_itemguid_transmogdata_map[pPlayer->GetGUIDLow()];
	for (auto i = map.begin(); i != map.end(); ++i)
	{
		TransmogrificationTempStore data;
		auto pProto = sObjectMgr.GetItemPrototype(i->second.item_template_id);
		data.name = pProto->Name1;
		data.quality = pProto->Quality;
		data.item_template_id = i->second.item_instance_guid;
        data.material = i->second.material;
        data.sheath = i->second.sheath;
		ret.push_back(data);
	}
	return ret;
}

bool TransmogrificationMgr::IsItemTransmogrified(uint32 itemguid)
{
	return transmogid_item_map.find(itemguid) != transmogid_item_map.end();
}

void TransmogrificationMgr::RestoreTransmogrification(Player* pPlayer, uint32 itemguid)
{
	CharacterDatabase.PExecute(
		"DELETE FROM `pomelo_transmogrification` "
		"WHERE `item_instance_guid` = %u AND `owner_guid` = %u;",
		itemguid, pPlayer->GetGUIDLow());

	auto transmogId = character_itemguid_transmogdata_map[pPlayer->GetGUIDLow()][itemguid].entry;
	itemguid_character_map.erase(itemguid);
	character_itemguid_transmogdata_map[pPlayer->GetGUIDLow()].erase(itemguid);
	transmogid_item_map.erase(transmogId);
	transmogid_transmogdata_map.erase(transmogId);
	ApplyTransmogrification(pPlayer, pPlayer->GetItemByGuid(ObjectGuid(HIGHGUID_ITEM, itemguid)));
}
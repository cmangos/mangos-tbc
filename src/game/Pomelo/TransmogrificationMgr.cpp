#include "TransmogrificationMgr.h"
#include "Entities/Item.h"
#include "Globals/ObjectMgr.h"

std::unordered_map<uint32, uint32> transmog_user_map;
std::unordered_map<uint32, std::map<uint32, TransmogrificationData>> user_transmog_map; // map[user][item-id] = transmog-data
std::unordered_map<uint32, uint32> fake_item_map;
std::unordered_map<uint32, TransmogrificationData> fake_transmog_map;

void TransmogrificationMgr::ApplyTransmogrification(Player* pPlayer, Item* pItem)
{
	uint32 character_id = pPlayer->GetGUIDLow();
	if (pItem)
	{
		if (transmog_user_map.find(pItem->GetGUIDLow()) == transmog_user_map.end())
		{
			pPlayer->SetUInt64Value(PLAYER_VISIBLE_ITEM_1_0 + (pItem->GetSlot() * MAX_VISIBLE_ITEM_OFFSET), pItem->GetEntry());
			return;
		}

		auto fakeEntry = ToItemEntry(user_transmog_map[character_id][pItem->GetGUIDLow()].entry);
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
	if (transmog_user_map.find(character_id) == transmog_user_map.end())
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
	"SELECT `entry`, `item_instance_guid`, `model`, `owner_guid`, `item_template_id` "
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

			transmog_user_map[data.item_instance_guid] = data.owner_guid;
			user_transmog_map[data.owner_guid][data.item_instance_guid] = data;
			fake_item_map[data.entry] = data.item_template_id;
			fake_transmog_map[data.entry] = data;
		} while (result->NextRow());
	}
}

void TransmogrificationMgr::OnLogout(uint32 characterId) 
{
	for (auto i = user_transmog_map[characterId].begin(); i != user_transmog_map[characterId].end(); ++i)
	{
		fake_item_map.erase(i->second.entry);
		fake_transmog_map.erase(i->second.entry);
	}
	user_transmog_map.erase(characterId);
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
	return fake_transmog_map[ToFakeEntry(fakeId)].model;
}

const ItemPrototype* TransmogrificationMgr::GetOriginItemProto(uint32 fakeId)
{
	auto fakeEntry = fake_item_map[ToFakeEntry(fakeId)];
	return sObjectMgr.GetItemPrototype(fakeEntry);
}

uint32 TransmogrificationMgr::GetModelIdByItemInstanceId(uint32 itemGuid)
{
	uint32 owner_id = transmog_user_map[itemGuid];
	return user_transmog_map[owner_id][itemGuid].model;
}

bool TransmogrificationMgr::IsTransmogrified(uint32 itemGuid)
{
	return transmog_user_map.find(itemGuid) != transmog_user_map.end();
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
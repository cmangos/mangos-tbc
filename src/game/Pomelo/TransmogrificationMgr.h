/**
 *
 * @File : TransmogrificationMgr.h
 * @Authors : yukozh
 * @Date : 09/18/2019
 *
 **/

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"
#include "Entities/Player.h"

#ifndef MANGOS_TRANSMOGRIFICATION_MGR_H
#define MANGOS_TRANSMOGRIFICATION_MGR_H

#define TRANSMOGRIFICATION_ENTRY_OFFSET 1000000

struct TransmogrificationData
{
	uint32 entry;
	uint32 item_instance_guid;
	uint32 model;
	uint32 owner_guid;
	uint32 item_template_id;
    uint32 material;
    uint32 sheath;
};

struct TransmogrificationTempStore
{
	uint32 display;
	std::string name;
	uint32 item_template_id;
	uint32 quality;
	EquipmentSlots slot;
    uint32 material;
    uint32 sheath;
};

class TransmogrificationMgr
{
public:
	void OnLogin(uint32 characterId);
	void OnLogout(uint32 characterId);
	bool IsFakeEntry(uint32 itemEntry);
	uint32 ToFakeEntry(uint32 fakeEntry);
	uint32 ToItemEntry(uint32 fakeEntry);
    uint32 GetModelId(uint32 fakeEntry);
    uint32 GetMaterial(uint32 fakeEntry);
    uint32 GetSheath(uint32 fakeEntry);
	uint32 GetModelIdByItemInstanceId(uint32 itemGuid);
	uint32 GetCharacterIdByTransmogrificationId(uint32 transmogId);
	const ItemPrototype* GetOriginItemProto(uint32 fakeEntry);
	void ApplyTransmogrification(Player* pPlayer, Item* pItem);
	void ApplyTransmogrification(Player* pPlayer, EquipmentSlots slot);
	void ApplyTransmogrification(Player* pPlayer);
	bool IsTransmogrified(uint32 itemGuid);
	void TransmogrifyItem(Item* pItem, uint32 display, uint32 material, uint32 sheath);
	void StoreDisplay(Player* pPlayer, Item* pItem);
	std::vector<TransmogrificationTempStore> GetStoredDisplays(Player* pPlayer);
	void ClearStoredDisplays(Player* pPlayer);
	void TransmogrifyItemFromTempStore(Item* pItem, EquipmentSlots slot);
	std::vector<TransmogrificationTempStore> GetTransmogrifiedItems(Player* pPlayer);
	bool IsItemTransmogrified(uint32 itemguid);
	void RestoreTransmogrification(Player* pPlayer, uint32 itemguid);
};

#define sTransmogrificationMgr MaNGOS::Singleton<TransmogrificationMgr>::Instance()

#endif
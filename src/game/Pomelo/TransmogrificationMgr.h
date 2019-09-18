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
	uint32 GetModelIdByItemInstanceId(uint32 itemGuid);
	uint32 GetCharacterIdByTransmogrificationId(uint32 transmogId);
	const ItemPrototype* GetOriginItemProto(uint32 fakeEntry);
	void ApplyTransmogrification(Player* pPlayer, Item* pItem);
	void ApplyTransmogrification(Player* pPlayer, EquipmentSlots slot);
	void ApplyTransmogrification(Player* pPlayer);
	bool IsTransmogrified(uint32 itemGuid);
};

#define sTransmogrificationMgr MaNGOS::Singleton<TransmogrificationMgr>::Instance()

#endif
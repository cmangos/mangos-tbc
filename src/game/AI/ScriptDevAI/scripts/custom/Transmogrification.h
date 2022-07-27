#ifndef DEF_TRANSMOGRIFICATION_H
#define DEF_TRANSMOGRIFICATION_H

#include "World.h"

#include <unordered_map>

#define PRESETS // comment this line to disable preset feature totally
#define MAX_OPTIONS 25 // do not alter

class Item;
class Player;
class WorldSession;
struct ItemPrototype;

enum TransmogAcoreStrings // Language.h might have same entries, appears when executing SQL, change if needed
{
	LANG_ERR_TRANSMOG_OK = 11100, // change this
	LANG_ERR_TRANSMOG_INVALID_SLOT,
	LANG_ERR_TRANSMOG_INVALID_SRC_ENTRY,
	LANG_ERR_TRANSMOG_MISSING_SRC_ITEM,
	LANG_ERR_TRANSMOG_MISSING_DEST_ITEM,
	LANG_ERR_TRANSMOG_INVALID_ITEMS,
	LANG_ERR_TRANSMOG_NOT_ENOUGH_MONEY,
	LANG_ERR_TRANSMOG_NOT_ENOUGH_TOKENS,
	LANG_ERR_TRANSMOG_SAME_DISPLAYID,

	LANG_ERR_UNTRANSMOG_OK,
	LANG_ERR_UNTRANSMOG_SINGLE_OK,
	LANG_ERR_UNTRANSMOG_NO_TRANSMOGS,
	LANG_ERR_UNTRANSMOG_SINGLE_NO_TRANSMOGS,


#ifdef PRESETS
	LANG_PRESET_ERR_INVALID_NAME,
#endif
	LANG_CMD_TRANSMOG_SHOW,
	LANG_CMD_TRANSMOG_HIDE,
	LANG_CMD_TRANSMOG_ADD_UNSUITABLE,
	LANG_CMD_TRANSMOG_ADD_FORBIDDEN,
	LANG_MENU_NO_SUITABLE_ITEMS,
	LANG_MENU_REMOVE,
	LANG_MENU_BACK,
	LANG_MENU_MAIN_MENU,
	LANG_MENU_BEFORE,
	LANG_MENU_AFTER,
	LANG_MENU_COST_IS,
	LANG_MENU_CONFIRM,
	LANG_MENU_YOUR_ITEM,
	LANG_MENU_TRANSMOG,
	LANG_MENU_POSSIBLE_LOOK,
	LANG_MENU_OPTIONS,
};

class Transmogrification
{
public:
	static Transmogrification* instance();

	typedef std::unordered_map<ObjectGuid, uint32> transmog2Data;
	typedef std::unordered_map<ObjectGuid, transmog2Data> transmogMap;
	transmogMap entryMap; // entryMap[pGUID][iGUID] = entry

	typedef std::unordered_map<ObjectGuid, ObjectGuid> transmogData;
	transmogData dataMap; // dataMap[iGUID] = pGUID

#ifdef PRESETS
	bool EnableSetInfo;
	uint32 SetNpcText;

	typedef std::map<uint8, uint32> slotMap;
	typedef std::map<uint8, slotMap> presetData;
	typedef std::unordered_map<ObjectGuid, presetData> presetDataMap;
	presetDataMap presetById; // presetById[pGUID][presetID][slot] = entry
	typedef std::map<uint8, std::string> presetIdMap;
	typedef std::unordered_map<ObjectGuid, presetIdMap> presetNameMap;
	presetNameMap presetByName; // presetByName[pGUID][presetID] = presetName

	void PresetTransmog(Player* player, Item* itemTransmogrified, uint32 fakeEntry, uint8 slot);

	bool EnableSets;
	uint8 MaxSets;
	float SetCostModifier;
	int32 SetCopperCost;

	bool GetEnableSets() const;
	uint8 GetMaxSets() const;
	float GetSetCostModifier() const;
	int32 GetSetCopperCost() const;

	void LoadPlayerSets(ObjectGuid pGUID);
	void UnloadPlayerSets(ObjectGuid pGUID);
#endif

	bool EnableTransmogInfo;
	uint32 TransmogNpcText;
	uint32 TransmogNpcSelectLookText;
	uint32 TransmogNpcConfirmText;
	uint32 TransmogNpcAlreadyText;
	uint32 TransmogNpcAlreadyAltText;

	// Use IsAllowed() and IsNotAllowed()
	// these are thread unsafe, but assumed to be static data so it should be safe
	std::set<uint32> Allowed;
	std::set<uint32> NotAllowed;

	float ScaledCostModifier;
	int32 CopperCost;

	bool RequireToken;
	uint32 TokenEntry;
	uint32 TokenAmount;

	bool AllowPoor;
	bool AllowCommon;
	bool AllowUncommon;
	bool AllowRare;
	bool AllowEpic;
	bool AllowLegendary;
	bool AllowArtifact;
	bool AllowHeirloom;

	bool AllowMixedArmorTypes;
	bool AllowMixedWeaponTypes;
	bool AllowFishingPoles;

	bool IgnoreReqRace;
	bool IgnoreReqClass;
	bool IgnoreReqSkill;
	bool IgnoreReqSpell;
	bool IgnoreReqLevel;
	bool IgnoreReqEvent;
	bool IgnoreReqStats;

	bool IsAllowed(uint32 entry) const;
	bool IsNotAllowed(uint32 entry) const;
	bool IsAllowedQuality(uint32 quality) const;
	bool IsRangedWeapon(uint32 Class, uint32 SubClass) const;

	void LoadConfig(bool reload); // thread unsafe

	std::string GetItemIcon(uint32 entry, uint32 width, uint32 height, int x, int y) const;
	std::string GetSlotIcon(uint8 slot, uint32 width, uint32 height, int x, int y) const;
	const char* GetSlotName(uint8 slot, WorldSession* session) const;
	std::string GetItemLink(Item* item, WorldSession* session) const;
	std::string GetItemLink(uint32 entry, WorldSession* session) const;
	uint32 GetFakeEntry(ObjectGuid itemGUID) const;
	void UpdateItem(Player* player, Item* item) const;
	void DeleteFakeEntry(Player* player, uint8 slot, Item* itemTransmogrified);
	void SetFakeEntry(Player* player, uint32 newEntry, Item* itemTransmogrified);

	TransmogAcoreStrings Transmogrify(Player* player, ObjectGuid itemTransmogrifier, uint8 slot, /*uint32 newEntry, */bool no_cost = false);
	bool CanTransmogrifyItemWithItem(Player* player, ItemPrototype const* target, ItemPrototype const* source) const;
	static bool SuitableForTransmogrification(Player* player, ItemPrototype const* proto);
	// bool CanBeTransmogrified(Item const* item);
	// bool CanTransmogrify(Item const* item);
	uint32 GetSpecialPrice(ItemPrototype const* proto) const;
	std::string FormatPrice(uint32 copper) const;

	void DeleteFakeFromDB(ObjectGuid itemLowGuid);
	static void CleanUp(Player* pPlayer);
	void BuildTransmogMap(Player* pPlayer);
	bool Refresh(Player* pPlayer, Item* pEquippedItem);
	static bool RevertAll(Player* pPlayer);
	bool ApplyAll(Player* pPlayer);
	void OnLogout(Player* player);
	float GetScaledCostModifier() const;
	int32 GetCopperCost() const;

	bool GetRequireToken() const;
	uint32 GetTokenEntry() const;
	uint32 GetTokenAmount() const;

	bool GetAllowMixedArmorTypes() const;
	bool GetAllowMixedWeaponTypes() const;

	// Config
	bool GetEnableTransmogInfo() const;
	uint32 GetTransmogNpcText() const;
	bool GetEnableSetInfo() const;
	uint32 GetSetNpcText() const;
	uint32 GetNpcSelectLookText() const;
	uint32 GetSetNpcConfirmText() const;
	uint32 GetSetNpcAlreadyText() const;
	uint32 GetSetNpcAlreadyAltText() const;
};
#define sTransmogrification Transmogrification::instance()

#endif

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "Platform/Define.h"

#ifndef MANGOS_CUSTOM_CURRENCY_MGR_H
#define MANGOS_CUSTOM_CURRENCY_MGR_H

struct CustomCurrencyInfo
{
	uint32       entry;
	std::string  name;
};

struct CustomCurrencyOwnedPair
{
	uint32       curid;
	uint32       amount;
};

class CustomCurrencyMgr
{
public:
	CustomCurrencyMgr();
	void LoadFromDB();
	uint32 GetAccountCurrency(uint32 accid, uint32 curid);
	bool ModifyAccountCurrency(uint32 accid, uint32 curid, int32 amount);
	CustomCurrencyInfo* GetCurrencyInfo(uint32 curid);
	std::vector<CustomCurrencyOwnedPair> GetOwnedCurrencies(uint32 accid);
};

#define sCustomCurrencyMgr MaNGOS::Singleton<CustomCurrencyMgr>::Instance()

#endif
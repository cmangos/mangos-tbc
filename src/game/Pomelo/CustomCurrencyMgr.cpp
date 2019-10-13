#include "CustomCurrencyMgr.h"

std::unordered_map<uint32, CustomCurrencyInfo> m_currency;

CustomCurrencyMgr::CustomCurrencyMgr()
{
	LoadFromDB();
}

void CustomCurrencyMgr::LoadFromDB()
{
	sLog.outString("Loading custom currencies...");

	QueryResult* result = LoginDatabase.PQuery(
	" SELECT `entry`, `name` "
	" FROM `pomelo_currency` ");

	if (result)
	{
		do
		{
			Field* field = result->Fetch();
			uint32 entry = field[0].GetUInt32();
			m_currency[entry] = CustomCurrencyInfo();
			m_currency[entry].entry = entry;
			m_currency[entry].name = field[1].GetCppString();
		} while (result->NextRow());
	}

	delete result;

	sLog.outString(">> Loaded %u custom currencies", result->GetRowCount());
}

uint32 CustomCurrencyMgr::GetAccountCurrency(uint32 accid, uint32 curid)
{
	QueryResult* result = LoginDatabase.PQuery(
		" SELECT `amount` "
		" FROM `pomelo_currency_owned`"
		" WHERE `accid` = %u AND `currency` = %u",
		accid, curid);

	if (!result || result->GetRowCount() != 1) return 0;

	Field* field = result->Fetch();
	uint32 ret = field[0].GetUInt32();
	delete result;
	return ret;
}

bool CustomCurrencyMgr::ModifyAccountCurrency(uint32 accid, uint32 curid, int32 amount)
{
	QueryResult* result = LoginDatabase.PQuery(
		" INSERT INTO `pomelo_currency_owned` "
		" (`accid`, `currency`, `amount`) "
		" VALUES (%u, %u, %d) "
		" ON DUPLICATE KEY UPDATE "
		" `amount` = `amount` + (%d);",
		accid, curid, amount, amount);
	bool ret = true;
	if (!result || result->GetRowCount() == 0) ret = false;
	delete result;
	return ret;
}

CustomCurrencyInfo* CustomCurrencyMgr::GetCurrencyInfo(uint32 curid)
{
	return &m_currency[curid];
}


std::vector<CustomCurrencyOwnedPair> CustomCurrencyMgr::GetOwnedCurrencies(uint32 accid)
{
	std::vector<CustomCurrencyOwnedPair> ret;

	QueryResult* result = LoginDatabase.PQuery(
		" SELECT `currency`, `amount` "
		" FROM `pomelo_currency_owned` "
		" WHERE `accid` = %u ", accid);

	if (result)
	{
		do
		{
			Field* field = result->Fetch();
			CustomCurrencyOwnedPair item;
			item.curid = field[0].GetUInt32();
			item.amount = field[1].GetUInt32();
			ret.push_back(item);
		} while (result->NextRow());
	}

    delete result;

	return ret;
}
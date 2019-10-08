/**
 *
 * @File : DailySignInReward.cpp
 * @Authors : yukozh
 * @Date : 09/23/2019
 *
 **/

#include "DailySignInRewardMgr.h"
#include "CustomCurrencyMgr.h"
#include "DBConfigMgr.h"

bool IsSameDay(tm* tm1, tm* tm2)
{
    if (tm1->tm_year != tm2->tm_year)
    {
        return false;
    }

    if (tm1->tm_mon != tm2->tm_mon)
    {
        return false;
    }

    if (tm1->tm_mday != tm2->tm_mday)
    {
        return false;
    }

    return true;
}

bool DailySignInRewardMgr::ClaimReward(Player* pPlayer)
{
    uint32 accountId = pPlayer->GetSession()->GetAccountId();
    QueryResult* result = LoginDatabase.PQuery(
    "SELECT `LastClaimSignInReward` "
    "FROM `pomelo_account` "
    "WHERE `Id` = %u;", accountId);

    if (!result)
    {
        return false;
    }

	Field* field = result->Fetch();
    time_t now = time(0);
    time_t last = time_t(field[0].GetInt64());
    tm* now_tm_t = localtime(&now);
    // copy the now_tm in to new space
    tm now_tm;
    now_tm.tm_year = now_tm_t->tm_year;
    now_tm.tm_mon = now_tm_t->tm_mon;
    now_tm.tm_mday = now_tm_t->tm_mday;

    tm* last_tm = localtime(&last);

    delete result;

    if (IsSameDay(&now_tm, last_tm))
    {
        return false;
    }

    uint32 amount = sDBConfigMgr.GetUInt32("reward.daily.amount");
    uint32 currencyId = sDBConfigMgr.GetUInt32("reward.daily.currency");
    LoginDatabase.PExecute(
    "UPDATE `pomelo_account` "
    "SET `LastClaimSignInReward` = %lld "
    "WHERE `Id` = %u", now, accountId);
    sCustomCurrencyMgr.ModifyAccountCurrency(accountId, currencyId, amount);
    return true;
}
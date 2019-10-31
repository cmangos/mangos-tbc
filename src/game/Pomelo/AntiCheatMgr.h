/**
 *
 * @File : AntiCheatMgr.h
 * @Authors : yukozh
 * @Date : 10/28/2019
 *
 **/

#ifndef MANGOS_ANTICHEAT_MGR_H
#define MANGOS_ANTICHEAT_MGR_H

#include "Common.h"
#include "Globals/SharedDefines.h"
#include "DBConfigMgr.h"
#include "Platform/Define.h"
#include <string>

enum AntiCheatAction
{
    ANTI_CHEAT_ACTION_NOACTION,
    ANTI_CHEAT_ACTION_KICK,
    ANTI_CHEAT_ACTION_DIE
};

enum CheatType
{
    CHEAT_TYPE_OVERSPEED
};

class AntiCheatMgr
{
public:
    void LogToDB(Player* pPlayer, CheatType type, const char* detail);
    void TakeActionForCheater(Player* pPlayer, AntiCheatAction action);
    bool PlayerIsFalling(Player* pPlayer);
    bool CheckSight() { return sDBConfigMgr.GetUInt32("anticheat.sight"); }
    bool CheckSpeed() { return sDBConfigMgr.GetUInt32("anticheat.speed"); }
    bool IsSpeedCheat(Player* pPlayer, MovementInfo* movement);
private:
    void ResetSpeedCounters(Player* pPlayer);
};

#define sAntiCheatMgr MaNGOS::Singleton<AntiCheatMgr>::Instance()

#endif
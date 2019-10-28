/**
 *
 * @File : AntiCheatMgr.cpp
 * @Authors : yukozh
 * @Date : 10/28/2019
 *
 **/

#include "AntiCheatMgr.h"
#include "World/World.h"
#include "Tools/Language.h"

void AntiCheatMgr::LogToDB(Player* pPlayer, CheatType type, const char* detail)
{
    CharacterDatabase.DirectPExecute(
        "INSERT INTO `pomelo_cheat_log` "
        "(`guid`, `type`, `detail`) "
        "VALUES (%u, %u, '%s');",
        pPlayer->GetGUIDLow(), type, detail);
}

void AntiCheatMgr::TakeActionForCheater(Player* pPlayer, AntiCheatAction action)
{
    switch (action)
    {
    case ANTI_CHEAT_ACTION_KICK:
    {
        const char* format = pPlayer->GetSession()->GetMangosString(LANG_CHEATER_KICKED);
        char str[2048];
        snprintf(str, 2048, format, pPlayer->GetName());
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, str);
        pPlayer->GetSession()->KickPlayer();
        break; 
    }
    case ANTI_CHEAT_ACTION_DIE:
    {
        const char* format = pPlayer->GetSession()->GetMangosString(LANG_CHEATER_DIED);
        char str[2048];
        snprintf(str, 2048, format, pPlayer->GetName());
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, str);
        pPlayer->KillPlayer();
        break; 
    }
    case ANTI_CHEAT_ACTION_NOACTION:
    default:
    {
        const char* format = pPlayer->GetSession()->GetMangosString(LANG_CHEATER_NO_ACTION);
        char str[2048];
        snprintf(str, 2048, format, pPlayer->GetName());
        sWorld.SendServerMessage(SERVER_MSG_CUSTOM, str);
        break;
    }
    }
}

void AntiCheatMgr::ResetSpeedCounters(Player* pPlayer)
{
    pPlayer->m_anticheatSpeedTimer = 0;
    pPlayer->m_anticheatSpeedMovedLength = 0;
}

bool AntiCheatMgr::IsSpeedCheat(Player* pPlayer, MovementInfo* pMovement)
{
    if (!CheckSpeed())
        return false;

    if (!pPlayer || !pMovement)
        return false;

    uint32 diff = pPlayer->m_anticheatSpeedTimer;

    if (!pPlayer->IsInWorld() 
        || pPlayer->IsBeingTeleported() 
        || pPlayer->m_anticheatTeleported)
    {
        ResetSpeedCounters(pPlayer);

        if (pPlayer->m_anticheatTeleported)
            pPlayer->m_anticheatTeleported = false;

        return false;
    }

    const Position* pos = pMovement->GetPos();
    float dis = pPlayer->GetDistance(pos->x, pos->y, pos->z);
    
    if (diff < 3000)
    {
        pPlayer->m_anticheatSpeedMovedLength += dis;
        return false;
    }
    else
    {
        dis += pPlayer->m_anticheatSpeedMovedLength;
        ResetSpeedCounters(pPlayer);
    }
    
    float speedRate = pPlayer->GetSpeed(pPlayer->m_movementInfo.GetSpeedType());

    if (dis / diff * 1000.f > speedRate * 1.05) // Leave 5% buffer for network latency
    {
        const char* format = "%s is making speed cheat: length=%f, capacity=%f, interval=%u ms";
        char detail[2048];
        snprintf(detail, 2048, format, pPlayer->GetGuidStr().c_str(), dis / diff * 1000.f, speedRate, diff);
        sLog.outString("[Anti-Cheat] %s", detail);
        LogToDB(pPlayer, CHEAT_TYPE_OVERSPEED, detail);

        AntiCheatAction action = AntiCheatAction(sDBConfigMgr.GetUInt32("anticheat.speed.action"));
        TakeActionForCheater(pPlayer, action);

        return true;
    }

    return false;
}
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

        if (pPlayer->isAlive())
        {
            DamageEffectType damageType = DIRECT_DAMAGE;
            uint32 absorb = 0;
            uint32 damage = pPlayer->GetHealth();
            pPlayer->DealDamageMods(pPlayer, damage, &absorb, damageType);
            pPlayer->DealDamage(pPlayer, damage, nullptr, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, nullptr, false);
        }

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
    pPlayer->m_anticheatSpeedResetTimer = 0;
    pPlayer->m_anticheatSpeedMovedLength = 0;
    pPlayer->m_anticheatSpeedMaxLength = 0;
}

bool AntiCheatMgr::PlayerIsFalling(Player* pPlayer)
{
    return pPlayer->HasMovementFlag(MovementFlags::MOVEFLAG_FALLING)
        || pPlayer->HasMovementFlag(MovementFlags::MOVEFLAG_FALLINGFAR);
}

bool AntiCheatMgr::IsSpeedCheat(Player* pPlayer, MovementInfo* pMovement)
{
    if (!CheckSpeed())
        return false;

    if (!pPlayer || !pMovement)
        return false;

    uint32 now = WorldTimer::getMSTime();
    if (pPlayer->m_anticheatBaseTimer == 0)
    {
        pPlayer->m_anticheatBaseTimer = now;
        return false;
    }

    uint32 diff = now - pPlayer->m_anticheatBaseTimer;
    pPlayer->m_anticheatBaseTimer = now;
    
    if (!pPlayer->IsInWorld() 
        || pPlayer->IsBeingTeleported() 
        || pPlayer->m_anticheatTeleported
        || !pPlayer->GetMover()->IsPlayer()
        || PlayerIsFalling(pPlayer)
        || diff > 15000)
    {
        ResetSpeedCounters(pPlayer);

        if (pPlayer->m_anticheatTeleported)
        {
            pPlayer->m_anticheatTeleported = false;
        }

        return false;
    }

    pPlayer->m_anticheatSpeedResetTimer += diff;
    const Position* pos = pMovement->GetPos();
    float dis = pPlayer->GetDistance(pos->x, pos->y, pos->z);
    float maxdis = 0;

    float speedRate = pPlayer->GetSpeed(pMovement->GetSpeedType());
    if (speedRate < 7.f)
        speedRate = 7.f;
    pPlayer->m_anticheatSpeedMovedLength += dis;
    pPlayer->m_anticheatSpeedMaxLength += speedRate * diff / 1000.f;

    uint32 timer = pPlayer->m_anticheatSpeedResetTimer;
    if (timer >= 3000)
    {
        maxdis = pPlayer->m_anticheatSpeedMaxLength;
        dis += pPlayer->m_anticheatSpeedMovedLength;
        ResetSpeedCounters(pPlayer);

        if (dis > maxdis * sDBConfigMgr.GetFloat("anticheat.speed.buffer")) // Leave buffer for network latency
        {
            const char* format = "%s is making speed cheat: length=%f, capacity=%f, interval=%u ms";
            char detail[2048];
            snprintf(detail, 2048, format, pPlayer->GetGuidStr().c_str(), dis, maxdis, timer);
            sLog.outString("[Anti-Cheat] %s", detail);
            LogToDB(pPlayer, CHEAT_TYPE_OVERSPEED, detail);

            AntiCheatAction action = AntiCheatAction(sDBConfigMgr.GetUInt32("anticheat.speed.action"));
            TakeActionForCheater(pPlayer, action);

            return true;
        }
    }

    return false;
}
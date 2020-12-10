#include <numeric>

#include "AntiCheat_time.h"
#include "Entities/Unit.h"
#include "World/World.h"
#include "Custom/CPlayer.h"
#include "Entities/Transports.h"

AntiCheat_time::AntiCheat_time(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_TIME;
    calculatedServerTime = 0;
}

bool AntiCheat_time::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
    {
        calculatedServerTime = MoveInfo->ctime;
        return SetOldMoveInfo(false);
    }

    if (GetDiff() < 500)
        return false;

    int diff = MoveInfo->ctime - calculatedServerTime;

    if (std::abs(diff) > 1000 + m_Player->GetSession()->GetLatency())
    {
        m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "TIMECHEAT" << "\n";
            m_Player->BoxChat << "ClientTime: " << MoveInfo->ctime << "\n";
            m_Player->BoxChat << "ServerTime: " << WorldTimer::getMSTime() << "\n";
            m_Player->BoxChat << "Offset: " << diff << "\n";
        }

        // Reset time offset when cheat is detected
        calculatedServerTime = MoveInfo->ctime;
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_time::HandleUpdate(uint32 updatediffms)
{
    calculatedServerTime += updatediffms;
}

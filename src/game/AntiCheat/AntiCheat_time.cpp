#include <numeric>

#include "AntiCheat_time.h"
#include "World/World.h"
#include "Entities/CPlayer.h"
#include "Entities/Transports.h"

AntiCheat_time::AntiCheat_time(CPlayer* player) : AntiCheat(player)
{
    m_RelativeServerTime = 0;
}

bool AntiCheat_time::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        m_RelativeServerTime += MoveInfo.GetTime();
        return SetOldMoveInfo(false);
    }

    if (GetDiff() < 50)
        return false;

    if (GetDistance() < 0.1f)
        return false;

    uint32 diff = std::abs(int64(MoveInfo.GetTime()) - m_RelativeServerTime);

    if (diff > 1000 + m_Player->GetSession()->GetLatency())
    {
        m_Player->TeleportToPos(oldMapID, oldMoveInfo.GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "ClientTime: " << MoveInfo.GetTime() << "\n";
            m_Player->BoxChat << "ServerTime: " << m_RelativeServerTime << "\n";
            m_Player->BoxChat << "ClientTime - ServerTime: " << int64(MoveInfo.GetTime()) - m_RelativeServerTime << "\n";
        }

        m_RelativeServerTime = MoveInfo.GetTime() - 900 + m_Player->GetSession()->GetLatency();
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_time::HandleUpdate(uint32 update_diff, uint32 p_time)
{
    m_RelativeServerTime += update_diff;
}
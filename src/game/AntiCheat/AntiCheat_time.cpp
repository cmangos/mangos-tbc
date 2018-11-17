#include <numeric>

#include "AntiCheat_time.h"
#include "World/World.h"
#include "Entities/CPlayer.h"
#include "Entities/Transports.h"

AntiCheat_time::AntiCheat_time(CPlayer* player) : AntiCheat(player)
{
    ClientServerTimeOffset = 0;
}

bool AntiCheat_time::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        ClientServerTimeOffset = MoveInfo->GetTime() - WorldTimer::getMSTime();
        return SetOldMoveInfo(false);
    }

    if (GetDiff() < 500)
        return false;

    if (GetTimeDiff() > 1000 + m_Player->GetSession()->GetLatency())
    {
        m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "TIMECHEAT" << "\n";
            m_Player->BoxChat << "ClientTime: " << MoveInfo->GetTime() << "\n";
            m_Player->BoxChat << "ServerTime: " << WorldTimer::getMSTime() << "\n";
            m_Player->BoxChat << "Offfset: " << ClientServerTimeOffset << "\n";
            m_Player->BoxChat << "Diff: " << GetTimeDiff() << "\n";
        }

        // Reset time offset when cheat is detected
        ClientServerTimeOffset = MoveInfo->GetTime() - WorldTimer::getMSTime();
    }

    return SetOldMoveInfo(false);
}

uint32 AntiCheat_time::GetTimeDiff()
{
    return std::abs(WorldTimer::getMSTime() + ClientServerTimeOffset - newmoveInfo->GetTime());
}

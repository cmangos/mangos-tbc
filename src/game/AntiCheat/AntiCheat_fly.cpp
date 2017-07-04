#include "AntiCheat_fly.h"
#include "Entities/CPlayer.h"

AntiCheat_fly::AntiCheat_fly(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_fly::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    if (!Initialized())
    {
        m_LastCanFlyTime = MoveInfo.GetTime();
        return false;
    }

    if (CanFly())
        m_LastCanFlyTime = MoveInfo.GetTime();

    if (isFlying(MoveInfo) && !CanFly() && m_LastCanFlyTime + 500 < MoveInfo.GetTime())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "FLY CHEAT" << "\n";

        m_Player->SetCanFly(false);

        return true;
    }

    return false;
}

#include "AntiCheat_fly.h"
#include "CPlayer.h"

AntiCheat_fly::AntiCheat_fly(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_fly::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        m_LastCanFlyTime = newMoveInfo.GetTime();
        return SetOldMoveInfo(false);
    }

    if (CanFly())
        m_LastCanFlyTime = newMoveInfo.GetTime();

    if (isFlying(newMoveInfo) && !CanFly() && m_LastCanFlyTime + 500 < newMoveInfo.GetTime())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "FLY CHEAT" << "\n";

        m_Player->SetCanFly(false);

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

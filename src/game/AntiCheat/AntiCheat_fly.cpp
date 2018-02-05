#include "AntiCheat_fly.h"
#include "Entities/CPlayer.h"

AntiCheat_fly::AntiCheat_fly(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_fly::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    if (isFlying(MoveInfo) && !CanFly())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "FLY CHEAT" << "\n";

        m_Player->SetCanFly(false);

        return true;
    }

    return false;
}

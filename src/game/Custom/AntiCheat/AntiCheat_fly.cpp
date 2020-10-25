#include "AntiCheat_fly.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"

AntiCheat_fly::AntiCheat_fly(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_FLY;
}

bool AntiCheat_fly::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

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

#include "AntiCheat_nofall.h"
#include "Custom/CPlayer.h"
#include "World/World.h"

AntiCheat_nofall::AntiCheat_nofall(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_NOFALL;
}

bool AntiCheat_nofall::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
        return false;

    if (newmoveInfo->HasMovementFlag(MOVEFLAG_LEVITATING) && !CanFly())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "NOFALL CHEAT" << "\n";

		m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        return true;
    }

    return SetOldMoveInfo(false);
}

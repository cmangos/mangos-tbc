#include "AntiCheat_nofall.h"
#include "Entities/CPlayer.h"
#include "World/World.h"

AntiCheat_nofall::AntiCheat_nofall(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_nofall::HandleMovement(const MovementInfoPtr& moveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(moveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    if (newmoveInfo->HasMovementFlag(MOVEFLAG_LEVITATING) && !CanFly())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "NOFALL CHEAT" << "\n";

		m_Player->TeleportToPos(oldMapID, oldmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        return true;
    }

    return SetoldmoveInfo(false);
}

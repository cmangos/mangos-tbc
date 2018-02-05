#include "AntiCheat_jump.h"
#include "Entities/CPlayer.h"

AntiCheat_jump::AntiCheat_jump(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_jump::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    if (!cheat && opcode == MSG_MOVE_JUMP && isFalling(oldmoveInfo))
    {
		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Jump hack" << "\n";

        return SetoldmoveInfo(true);
    }

    if (opcode == MSG_MOVE_JUMP)
        SetstoredmoveInfo(false);

    return SetoldmoveInfo(false);
}

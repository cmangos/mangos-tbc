#include "AntiCheat_jump.h"
#include "CPlayer.h"

AntiCheat_jump::AntiCheat_jump(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_jump::HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[2] = m_MoveInfo[0];
        return SetOldMoveInfo(false);
    }

    if (!cheat && opcode == MSG_MOVE_JUMP && isFalling(m_MoveInfo[1]))
    {
        const Position* pos = m_MoveInfo[2].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->BoxChat << "Jump hack" << "\n";

        return SetOldMoveInfo(true);
    }

    if (opcode == MSG_MOVE_JUMP)
        m_MoveInfo[2] = m_MoveInfo[0];

    return SetOldMoveInfo(false);
}

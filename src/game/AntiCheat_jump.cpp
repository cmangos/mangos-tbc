#include "AntiCheat_jump.h"
#include "CPlayer.h"

AntiCheat_jump::AntiCheat_jump(Player* player) : AntiCheat(player)
{
    jumping = false;
}

bool AntiCheat_jump::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (isSwimming())
        jumping = false;

    if (opcode == MSG_MOVE_JUMP && jumping)
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->ToCPlayer()->BoxChat << "Jump hack" << "\n";

        return true;
    }
    else if (opcode == MSG_MOVE_JUMP)
    {
        jumping = true;
        m_MoveInfo[1] = m_MoveInfo[0];
    }
    else if (opcode == MSG_MOVE_FALL_LAND)
        jumping = false;

    return false;
}

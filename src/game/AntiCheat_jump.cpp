#include "AntiCheat_jump.h"
#include "CPlayer.h"

AntiCheat_jump::AntiCheat_jump(Player* player) : AntiCheat(player)
{
    jumping = false;
}

bool AntiCheat_jump::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    if (!Initialized())
        return false;

    if (opcode == MSG_MOVE_JUMP && jumping)
        m_Player->ToCPlayer()->BoxChat << "Jump hack" << "\n";
    else if (opcode == MSG_MOVE_JUMP)
        jumping = true;
    else if (opcode == MSG_MOVE_FALL_LAND)
        jumping = false;

    return false;
}

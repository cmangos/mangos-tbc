#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    m_StartJumpZ = 0;
    jumping = false;
}

bool AntiCheat_gravity::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
        return false;
    }

    std::stringstream& ss = m_Player->BoxChat;

    if (jumping && ((isSwimming() && m_MoveInfo[0].GetPos()->z - m_StartJumpZ > JUMPHEIGHT_WATER) || (!isSwimming() && m_MoveInfo[0].GetPos()->z - m_StartJumpZ > JUMPHEIGHT_LAND)))
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        ss << "Gravity hacking" << "\n";

        return true;
    }

    if (opcode == MSG_MOVE_JUMP)
        jumping = true;
    else if (opcode == MSG_MOVE_FALL_LAND)
        jumping = false;

    if (opcode == MSG_MOVE_JUMP)
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_StartJumpZ = m_MoveInfo[0].GetPos()->z;
    }
    return false;
}

void AntiCheat_gravity::HandleTeleport()
{
    m_Initialized = false;
}

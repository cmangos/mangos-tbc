#include "AntiCheat_gravity.h"
#include "CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(Player* player) : AntiCheat(player)
{
}

bool AntiCheat_gravity::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    std::stringstream& ss = m_Player->ToCPlayer()->BoxChat;

    if (opcode == MSG_MOVE_JUMP || opcode == MSG_MOVE_HEARTBEAT)
    {
        ss << "cosAngle: " << m_MoveInfo[0].GetJumpInfo().cosAngle << "\n";
        ss << "sinAngle: " << m_MoveInfo[0].GetJumpInfo().sinAngle << "\n";
        ss << "velocity: " << m_MoveInfo[0].GetJumpInfo().velocity << "\n";
        ss << "xyspeed: " << m_MoveInfo[0].GetJumpInfo().xyspeed << "\n";
    }

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}


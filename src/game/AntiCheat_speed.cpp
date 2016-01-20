#include "AntiCheat_speed.h"

AntiCheat_speed::AntiCheat_speed(Player* player) : AntiCheat(player)
{

}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    if (!Initialized())
    {
        m_MoveInfo = moveInfo;
        return false;
    }

    float distance = GetDistance(moveInfo, m_MoveInfo);
    float speed = GetSpeed(moveInfo, m_MoveInfo);

    
}
#include "AntiCheat_test.h"
#include "CPlayer.h"
#include "Transports.h"

AntiCheat_test::AntiCheat_test(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_test::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}


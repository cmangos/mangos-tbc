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

    m_Player->BoxChat << "cposx: " << m_MoveInfo[0].GetPos()->x << "\n";
    m_Player->BoxChat << "cposy: " << m_MoveInfo[0].GetPos()->y << "\n";
    m_Player->BoxChat << "cposz: " << m_MoveInfo[0].GetPos()->z << "\n";
    m_Player->BoxChat << "oposx: " << m_MoveInfo[1].GetPos()->x << "\n";
    m_Player->BoxChat << "oposy: " << m_MoveInfo[1].GetPos()->y << "\n";
    m_Player->BoxChat << "oposz: " << m_MoveInfo[1].GetPos()->z << "\n";

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_test::HandleRelocate(float x, float y, float z, float o)
{
    m_MoveInfo[1].ChangePosition(x, y, z, o);
}
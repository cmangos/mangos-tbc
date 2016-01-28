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

    m_Player->BoxChat << "PX: " << m_MoveInfo[0].GetPos()->x << "\n";
    m_Player->BoxChat << "PY: " << m_MoveInfo[0].GetPos()->y << "\n";
    m_Player->BoxChat << "PZ: " << m_MoveInfo[0].GetPos()->z << "\n";
    m_Player->BoxChat << "TX: " << m_MoveInfo[0].GetTransportPos()->x << "\n";
    m_Player->BoxChat << "TY: " << m_MoveInfo[0].GetTransportPos()->y << "\n";
    m_Player->BoxChat << "TZ: " << m_MoveInfo[0].GetTransportPos()->z << "\n";
    m_Player->BoxChat << "Transport: " << (isTransport() ? "true" : "false") << "\n";


    float x, y, z;
    //m_Player->GetTransport()->GetPosition(x, y, z);

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_test::HandleTeleport()
{
    m_Initialized = false;
}

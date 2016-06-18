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

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    m_Player->BoxChat << "cosAngle: " << m_MoveInfo[0].GetJumpInfo().cosAngle << "\n";
    m_Player->BoxChat << "sinAngle: " << m_MoveInfo[0].GetJumpInfo().sinAngle << "\n";
    m_Player->BoxChat << "velocity: " << m_MoveInfo[0].GetJumpInfo().velocity << "\n";
    m_Player->BoxChat << "xyspeed: " << m_MoveInfo[0].GetJumpInfo().xyspeed << "\n";
    m_Player->BoxChat << "cposx: " << m_MoveInfo[0].GetPos()->x << "\n";
    m_Player->BoxChat << "cposy: " << m_MoveInfo[0].GetPos()->y << "\n";
    m_Player->BoxChat << "cposz: " << m_MoveInfo[0].GetPos()->z << "\n";
    m_Player->BoxChat << "angle: " << angle << "\n";
    m_Player->BoxChat << "moving: " << (IsMoving(m_MoveInfo[0]) ? "true" : "false") << "\n";
    m_Player->BoxChat << "falling: " << (isFalling(m_MoveInfo[0]) ? "true" : "false") << "\n";
    m_Player->BoxChat << "flying: " << (isFlying(m_MoveInfo[0]) ? "true" : "false") << "\n";
    m_Player->BoxChat << "transport: " << (isTransport(m_MoveInfo[0]) ? "true" : "false") << "\n";
    m_Player->BoxChat << "slowfall: " << (m_MoveInfo[0].HasMovementFlag(MOVEFLAG_SAFE_FALL) ? "true" : "false") << "\n";

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_test::HandleRelocate(float x, float y, float z, float o)
{
}

void AntiCheat_test::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
}
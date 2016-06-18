#include "AntiCheat_slowfall.h"
#include "CPlayer.h"
#include "Transports.h"

AntiCheat_slowfall::AntiCheat_slowfall(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_slowfall::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    float allowedangle = -90.f;

    m_Player->BoxChat << "angle: " << angle << "\n";
    m_Player->BoxChat << "slowfall: " << (moveInfo.HasMovementFlag(MOVEFLAG_SAFE_FALL) ? "true" : "false") << "\n";

    bool cheat = true;

    if (opcode == MSG_MOVE_JUMP)
        cheat = false;

    if (opcode == MSG_MOVE_FALL_LAND)
        cheat = false;

    if (!isFalling())
        cheat = false;

    if (GetDistanceZ() > 0.f)
        cheat = false;


    if (cheat && angle > -44.99f) // Just some value i got from printing angle when falling.
    {
        m_Player->BoxChat << "SLOWFALL CHEAT" << "\n";
    }

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_slowfall::HandleRelocate(float x, float y, float z, float o)
{
}

void AntiCheat_slowfall::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
}
#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"
#include "MapManager.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    float speedrounding = 100.f;

    bool skipcheat = false;

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_MoveInfo[2] = m_MoveInfo[0];

        fallspeed = 0.f;
        knockback = false;

        return false;
    }

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(m_MoveInfo[0]))
        knockback = false;

    if (GetDiff() < 50 || GetDistance3D() < 0.5f)
        return false;

    bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

    float allowedspeed = GetSpeed();

    if (!isFalling(m_MoveInfo[1]) && isFalling(m_MoveInfo[0]))
        fallspeed = allowedspeed;

    if (isFalling(m_MoveInfo[0]))
        allowedspeed = fallspeed;
    else
        fallspeed = 0.f;

    bool threed = isFlying() || isSwimming();

    float travelspeed = floor(((onTransport ? GetTransportDist(threed) : GetDistance(threed)) / GetVirtualDiffInSec()) * speedrounding) / speedrounding;

    bool cheating = false;

    if (travelspeed > allowedspeed)
        cheating = true;

    if (isTransport(m_MoveInfo[0]) && !verifyTransportCoords(m_MoveInfo[0]))
        cheating = false;

    if (m_MoveInfo[0].GetJumpInfo().xyspeed > allowedspeed)
        cheating = true;

    if (knockback)
        cheating = false;

    if (false)
    {
        m_Player->BoxChat << "----------------------------" << "\n";
        m_Player->BoxChat << "MOVEFLAG_FALLING: " << m_MoveInfo[0].HasMovementFlag(MOVEFLAG_FALLING) << "\n";
        m_Player->BoxChat << "MOVEFLAG_FALLINGFAR: " << m_MoveInfo[0].HasMovementFlag(MOVEFLAG_FALLINGFAR) << "\n";
        m_Player->BoxChat << "MOVEFLAG_SAFE_FALL: " << m_MoveInfo[0].HasMovementFlag(MOVEFLAG_SAFE_FALL) << "\n";
        m_Player->BoxChat << "xyspeed: " << m_MoveInfo[0].GetJumpInfo().xyspeed << "\n";
        m_Player->BoxChat << "velocity: " << m_MoveInfo[0].GetJumpInfo().velocity << "\n";
        m_Player->BoxChat << "allowedspeed: " << allowedspeed << "\n";
        m_Player->BoxChat << "travelspeed: " << travelspeed << "\n";
    }

    if (cheating)
    {
        const Position* p = m_MoveInfo[2].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        m_Player->BoxChat << "SPEEDCHEAT" << "\n";
    }
    else
        m_MoveInfo[2] = m_MoveInfo[0];

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_speed::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    knockback = true;
}

void AntiCheat_speed::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        AntiCheat::HandleRelocate(x, y, z, o);
}

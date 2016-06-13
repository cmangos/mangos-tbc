#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"
#include "MapManager.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    bool skipcheat = false;

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        m_MoveInfo[2] = m_MoveInfo[0];

        knockback = false;

        return false;
    }

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(m_MoveInfo[0]))
        knockback = false;

	if (GetDiff() < 50)
		return false;

    bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

    float allowedspeed = GetSpeed();

    float d2speed = (onTransport ? GetTransportDist2D() : GetDistance2D()) / GetVirtualDiffInSec();
    float d3speed = (onTransport ? GetTransportDist3D() : GetDistance3D()) / GetVirtualDiffInSec();
    float travelspeed = floor((isFlying() || isSwimming() ? d3speed : d2speed) * 100.f) / 100.f;

	bool cheating = false;

	if (travelspeed > allowedspeed && ((isFalling() && GetDistanceZ() > 0.f) || !isFalling()))
		cheating = true;

	if (m_MoveInfo[0].GetJumpInfo().xyspeed > allowedspeed)
		cheating = true;

    if (isTransport(m_MoveInfo[0]) && !verifyTransportCoords(m_MoveInfo[0]))
        cheating = false;

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

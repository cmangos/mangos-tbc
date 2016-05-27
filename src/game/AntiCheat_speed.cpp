#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"
#include "MapManager.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
    m_LastCheat = false;
}

float AntiCheat_speed::rfloor100(float& value)
{
    value = floor(value * 100) / 100;
    return value;
}

float AntiCheat_speed::rceil100(float& value)
{
    value = ceil(value * 100) / 100;
    return value;
}

float AntiCheat_speed::floor100(float value)
{
    value = floor(value * 100) / 100;
    return value;
}

float AntiCheat_speed::ceil100(float value)
{
    value = ceil(value * 100) / 100;
    return value;
}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

	bool skipcheat = false;

	if (!Initialized())
		skipcheat = true;

	if (isTransport(m_MoveInfo[0]) && !verifyTransportCoords(m_MoveInfo[0]))
		skipcheat = true;

    if (skipcheat)
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (GetDiff() < 50 || GetDistance3D() < 0.25f)
        return false;

    bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

    float allowedspeed = GetSpeed();

    float d2YPS = (onTransport ? GetTransportDist2D() : GetDistance2D()) / GetDiffInSec();
    float d3YPS = (onTransport ? GetTransportDist3D() : GetDistance3D()) / GetDiffInSec();
    float travelspeed = floor((isFlying() || isSwimming() ? d3YPS : d2YPS) * 100.f) / 100.f;

	bool cheating = false;

	if (travelspeed > allowedspeed)
		cheating = true;

	if (m_MoveInfo[0].GetJumpInfo().xyspeed > allowedspeed)
		cheating = true;

	if (cheating)
	{
		m_MoveInfo[0] = m_MoveInfo[1];
		const Position* p = m_MoveInfo[0].GetPos();

		m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_TRANSPORT);
	}	

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_speed::HandleTeleport(float x, float y, float z)
{
    m_MoveInfo[1].ChangePosition(x, y, z, m_Player->GetOrientation());
}

void AntiCheat_speed::HandleFlightpathFinish()
{
    float x, y, z;
    m_Player->GetPosition(x, y, z);
    m_MoveInfo[1].ChangePosition(x, y, z, m_Player->GetOrientation());
}

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

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (GetDiff() < 50 || GetDistance3D() < 0.25f)
        return false;

    bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

    float allowedYPS = GetSpeed();

    float d2YPS = (onTransport ? GetTransportDist2D() : GetDistance2D()) / GetDiffInSec();
    float d3YPS = (onTransport ? GetTransportDist3D() : GetDistance3D()) / GetDiffInSec();
    float traveledYPS = 0.f;

    if (isTransport(m_MoveInfo[0]) != isTransport(m_MoveInfo[1]))
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (isFlying())
        traveledYPS = isFlying() ? d3YPS : d2YPS;


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

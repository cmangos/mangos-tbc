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

    float speed = GetSpeed();

    float d2dps = (onTransport ? GetTransportDist2D() : GetDistance2D()) / GetDiffInSec();
    float d3dps = (onTransport ? GetTransportDist3D() : GetDistance3D()) / GetDiffInSec();
    float dzps = onTransport ? GetTransportDistZ() : GetDistanceZ() / GetDiffInSec();
    float angle = MapManager::NormalizeOrientation(atan2(dzps, d2dps));
    float allowed2dps = speed;

    if (isFalling())
        allowed2dps = dzps / tan(angle);

    float allowed3dps = allowed2dps / cos(angle);

    rfloor100(d2dps);
    rceil100(allowed2dps);
    rfloor100(d3dps);
    rceil100(allowed3dps);

    if (d2dps > allowed2dps && d3dps > allowed3dps)
    {
        if (m_LastCheat)
        {
            const Position* p = m_MoveInfo[1].GetPos();
            m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);

            m_Player->BoxChat << "-----------------------------------------" << "\n";
            m_Player->BoxChat << "d2dps: " << d2dps << "\n";
            m_Player->BoxChat << "allowed2dps: " << allowed2dps << "\n";
            m_Player->BoxChat << "cheat: " << (d2dps > allowed2dps ? "true" : "false") << "\n";
            m_Player->BoxChat << "d3dps: " << d3dps << "\n";
            m_Player->BoxChat << "allowed3dps: " << allowed3dps << "\n";
            m_Player->BoxChat << "cheat: " << (d3dps > allowed3dps ? "true" : "false") << "\n";
        }

        m_LastCheat = true;
    }
    else
        m_LastCheat = false;

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

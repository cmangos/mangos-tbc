#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
    m_LastFallCheck = 0;
    fallingFromTransportSpeed = 0.f;
}

float AntiCheat_speed::floor100(float& value)
{
    value = floor(value * 100) / 100;
    return value;
}

float AntiCheat_speed::ceil100(float& value)
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

    if (GetDiff() < 50)
        return false;

    float d2dps = GetDistance2D() / GetDiffInSec();
    float d3dps = GetDistance3D() / GetDiffInSec();
    float dzps = abs(GetDistanceZ()) / GetDiffInSec();
    float speed = GetSpeed();
    float allowed2dps = speed;
    float allowed3dps = speed;
    float angle = atan2(dzps, d2dps);


    if (isFalling() && GetDistanceZ() < 0.f && angle > 0.f)
        allowed2dps = dzps / tan(angle);

    allowed3dps = allowed2dps / cos(angle);

    floor100(d2dps);
    floor100(d3dps);
    ceil100(allowed2dps);
    ceil100(allowed3dps);

    if (d2dps > allowed2dps || d3dps > allowed3dps)
    {
        if (m_Player->isGameMaster())
        {
            m_Player->BoxChat << "d2d: " << d2dps << "\n";
            m_Player->BoxChat << "allowed2d: " << allowed2dps << "\n";
            m_Player->BoxChat << "cheat: " << (d2dps > allowed2dps ? "true" : "false") << "\n";
            m_Player->BoxChat << "d3d: " << d3dps << "\n";
            m_Player->BoxChat << "allowed3d: " << allowed3dps << "\n";
            m_Player->BoxChat << "cheat: " << (d3dps > allowed3dps ? "true" : "false") << "\n";
        }
        else
        {
            const Position* pos = m_MoveInfo[1].GetPos();
            m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        }
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

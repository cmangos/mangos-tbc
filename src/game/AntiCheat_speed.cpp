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

        m_Knockback = false;
        m_FlySpeed = 0.f;

        return false;
    }

    {
        bool hasflightmodaura = false;

        bool back = m_MoveInfo[0].HasMovementFlag(MOVEFLAG_BACKWARD) && m_MoveInfo[1].HasMovementFlag(MOVEFLAG_BACKWARD);

        for (uint8 i = SPELL_AURA_MOD_FLIGHT_SPEED; i <= SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_NOT_STACKING; ++i)
            if (m_Player->HasAuraType(AuraType(i)))
                hasflightmodaura = true;

        if (hasflightmodaura && isFlying())
            m_FlySpeed = m_Player->GetSpeed(back ? MOVE_FLIGHT_BACK : MOVE_FLIGHT);
        else if (!isFlying())
            m_FlySpeed = 0.f;
    }

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(m_MoveInfo[0]))
        m_Knockback = false;

    if (GetDiff() < 50 || GetDistance3D() < 0.5f)
        return false;

    bool onTransport = isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1]);

    float allowedspeed = GetSpeed();
    allowedspeed = m_Knockback ? std::max(allowedspeed, m_KnockbackSpeed) : allowedspeed;
    allowedspeed = isFlying() ? std::max(allowedspeed, m_FlySpeed) : allowedspeed;

    bool threed = isFlying() || isSwimming();

    float travelspeed = floor(((onTransport ? GetTransportDist(threed) : GetDistance(threed)) / GetVirtualDiffInSec()) * speedrounding) / speedrounding;

    bool cheating = false;

    if (isFalling())
    {
        if (m_MoveInfo[0].GetJumpInfo().xyspeed > allowedspeed)
            cheating = true;
    }
    else
    {
        if (travelspeed > allowedspeed)
            cheating = true;
    }

    if (isTransport(m_MoveInfo[0]) && !verifyTransportCoords(m_MoveInfo[0]))
        cheating = false;

    if (cheating)
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "----------------------------" << "\n";
            m_Player->BoxChat << "xyspeed: " << m_MoveInfo[0].GetJumpInfo().xyspeed << "\n";
            m_Player->BoxChat << "velocity: " << m_MoveInfo[0].GetJumpInfo().velocity << "\n";
            m_Player->BoxChat << "allowedspeed: " << allowedspeed << "\n";
            m_Player->BoxChat << "travelspeed: " << travelspeed << "\n";
            m_Player->BoxChat << "SPEEDCHEAT" << "\n";
        }

        const Position* p = m_MoveInfo[2].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

    }
    else
        m_MoveInfo[2] = m_MoveInfo[0];

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_speed::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_Knockback = true;
    m_KnockbackSpeed = horizontalSpeed;
}

void AntiCheat_speed::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        AntiCheat::HandleRelocate(x, y, z, o);
}

#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"
#include "MapManager.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_speed::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    float speedrounding = 100.f;

    bool skipcheat = false;

    if (!Initialized())
    {
        oldMoveInfo = newMoveInfo;
        storedMoveInfo = newMoveInfo;

        m_Knockback = false;
        m_FlySpeed = 0.f;

        return false;
    }

    UpdateFlySpeed();

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(newMoveInfo))
        m_Knockback = false;

    if (GetDiff() < 250)
        return false;

    if (GetDistance3D() < 2.5f)
        return false;

    if (!isSwimming(oldMoveInfo) && isSwimming(newMoveInfo))
        return false;

    bool onTransport = isTransport(newMoveInfo) && isTransport(oldMoveInfo);

    float allowedspeed = GetAllowedSpeed();

    bool threed = isFlying() || isSwimming();

    float travelspeed = floor(((onTransport ? GetTransportDist(threed) : GetDistance(threed)) / GetVirtualDiffInSec()) * speedrounding) / speedrounding;

    bool cheating = false;

    if (isFalling())
    {
        if (newMoveInfo.GetJumpInfo().xyspeed > allowedspeed)
            cheating = true;
    }
    else
    {
        if (travelspeed > allowedspeed)
            cheating = true;
    }

    if (isTransport(newMoveInfo) && !verifyTransportCoords(newMoveInfo))
        cheating = false;

    if (!cheat && cheating)
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "----------------------------" << "\n";
            m_Player->BoxChat << "xyspeed: " << newMoveInfo.GetJumpInfo().xyspeed << "\n";
            m_Player->BoxChat << "velocity: " << newMoveInfo.GetJumpInfo().velocity << "\n";
            m_Player->BoxChat << "allowedspeed: " << allowedspeed << "\n";
            m_Player->BoxChat << "travelspeed: " << travelspeed << "\n";
            m_Player->BoxChat << "SPEEDCHEAT" << "\n";
        }

        const Position* p = storedMoveInfo.GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        return SetOldMoveInfo(true);
    }
    else
        storedMoveInfo = newMoveInfo;

    return SetOldMoveInfo(false);
}

void AntiCheat_speed::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_Knockback = true;
    m_KnockbackSpeed = horizontalSpeed;
}

void AntiCheat_speed::UpdateFlySpeed()
{
    bool hasFlightAuras = false;

    bool back = newMoveInfo.HasMovementFlag(MOVEFLAG_BACKWARD) && oldMoveInfo.HasMovementFlag(MOVEFLAG_BACKWARD);

    for (uint8 i = SPELL_AURA_MOD_FLIGHT_SPEED; i <= SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED_NOT_STACKING; ++i)
        if (m_Player->HasAuraType(AuraType(i)))
            hasFlightAuras = true;

    hasFlightAuras = hasFlightAuras || m_Player->HasAuraType(SPELL_AURA_FLY);

    if (hasFlightAuras && isFlying())
        m_FlySpeed = m_Player->GetSpeed(back ? MOVE_FLIGHT_BACK : MOVE_FLIGHT);
    else if (!isFlying())
        m_FlySpeed = 0.f;
}

float AntiCheat_speed::GetAllowedSpeed()
{
    float allowedspeed = GetSpeed();
    allowedspeed = m_Knockback ? std::max(allowedspeed, GetKnockBackSpeed()) : allowedspeed;
    allowedspeed = isFlying() ? std::max(allowedspeed, GetFlySpeed()) : allowedspeed;

    return allowedspeed;
}

#include "AntiCheat_speed.h"
#include "Entities/CPlayer.h"
#include "World/World.h"
#include "Maps/Map.h"
#include "Maps/MapManager.h"

#include <iomanip>

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_speed::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        m_Knockback = false;
        m_KnockbackSpeed = 0.f;
        return false;
    }

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(newmoveInfo))
        m_Knockback = false;

    if (GetDiff() < 250)
        return false;

    if (GetDistance3D() < 2.5f)
        return false;

    if (!isSwimming(oldmoveInfo) && isSwimming(newmoveInfo))
        return false;

    bool onTransport = isTransport(newmoveInfo) && isTransport(oldmoveInfo);

    float allowedspeed = RoundFloat(GetAllowedSpeed(), 100, true);

    bool threed = isFlying() || isSwimming();

    float travelspeed = RoundFloat(GetSpeedDistance() / GetVirtualDiffInSec(), 100, false);

    bool cheating = false;

    if (isFalling())
    {
        if (newmoveInfo->GetJumpInfo().xyspeed > allowedspeed)
            cheating = true;
    }
    else if (travelspeed > allowedspeed)
		cheating = true;

    if (isTransport(newmoveInfo) && !verifyTransportCoords(newmoveInfo))
        cheating = false; // When we're just walking onto a transport every coordinate is a mess

    if (!cheat && cheating)
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "----------------------------" << "\n";
            m_Player->BoxChat << "xyspeed: " << newmoveInfo->GetJumpInfo().xyspeed << "\n";
            m_Player->BoxChat << "velocity: " << newmoveInfo->GetJumpInfo().velocity << "\n";
            m_Player->BoxChat << std::setprecision(10) << "allowedspeed: " << allowedspeed << "\n";
            m_Player->BoxChat << std::setprecision(10) << "travelspeed: " << travelspeed << "\n";
            m_Player->BoxChat << std::setprecision(10) << "diff: " << travelspeed - allowedspeed << "\n";
            m_Player->BoxChat << "SPEEDCHEAT" << "\n";
        }

		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        return SetOldMoveInfo(true);
    }
    else
        SetStoredMoveInfo(false);

    return SetOldMoveInfo(false);
}

void AntiCheat_speed::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_Knockback = true;
    m_KnockbackSpeed = horizontalSpeed;
}

float AntiCheat_speed::GetAllowedSpeed()
{
    float allowedspeed = GetServerSpeed();
    allowedspeed = IsKnockedback() ? std::max(allowedspeed, GetKnockBackSpeed()) : allowedspeed;

    return allowedspeed;
}

#include "AntiCheat_speed.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"
#include "World/World.h"
#include "Maps/Map.h"
#include "Maps/MapManager.h"

#include <iomanip>

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_SPEED;
}

bool AntiCheat_speed::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
        return false;

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
        if (newmoveInfo->jump.xyspeed > allowedspeed)
            cheating = true;
    }
    else if (travelspeed > allowedspeed)
		cheating = true;

    if (isTransport(newmoveInfo) && !verifyTransportCoords(newmoveInfo))
        cheating = false; // When we're just walking onto a transport every coordinate is a mess.

    if (triggeredcheats.none() && cheating)
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "----------------------------" << "\n";
            m_Player->BoxChat << "xyspeed: " << newmoveInfo->jump.xyspeed << "\n";
            m_Player->BoxChat << "velocity: " << newmoveInfo->jump.velocity << "\n";
            m_Player->BoxChat << std::setprecision(10) << "allowedspeed: " << allowedspeed << "\n";
            m_Player->BoxChat << std::setprecision(10) << "travelspeed: " << travelspeed << "\n";
            m_Player->BoxChat << std::setprecision(10) << "diff: " << travelspeed - allowedspeed << "\n";
            m_Player->BoxChat << "SPEEDCHEAT" << "\n";
        }

		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        return SetOldMoveInfo(true);
    }
    else if (!isFalling())
        SetStoredMoveInfo(false);

    return SetOldMoveInfo(false);
}

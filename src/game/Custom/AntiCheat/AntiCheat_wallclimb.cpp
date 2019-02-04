#include "AntiCheat_wallclimb.h"
#include "Custom/CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_wallclimb::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (isTransport())
        return SetOldMoveInfo(false);

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (angle <= 50.f)
        SetStoredMoveInfo(false);

    if (!Initialized())
        return false;

    if (GetDistanceZ() <= 0.f)
        return SetOldMoveInfo(false);

    if (GetDistanceZ() < JUMPHEIGHT_WATER)
        return false;

    if (isFalling())
        return false;

    if (isFlying() || isSwimming())
        return false;

    if (opcode == MSG_MOVE_FALL_LAND)
        return false;

    if (!cheat && angle > 50.f)
    {
		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Wallclimbing angle: " << angle << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

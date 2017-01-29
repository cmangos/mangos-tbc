#include "AntiCheat_wallclimb.h"
#include "CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_wallclimb::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (angle <= 50.f)
        storedMoveInfo = newMoveInfo;

    if (!Initialized())
        return SetOldMoveInfo(false);

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
        const Position* p = storedMoveInfo.GetPos();
        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Wallclimbing angle: " << angle << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

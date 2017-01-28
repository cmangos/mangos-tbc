#include "AntiCheat_wallclimb.h"
#include "CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_wallclimb::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return SetOldMoveInfo(false);

    if (GetDistanceZ() <= 0.f)
        return SetOldMoveInfo(false);

    if (GetDistanceZ() < WALKABLE_CLIMB)
        return false;

    if (isFalling(newMoveInfo))
        return false;

    if (isFlying() || isSwimming())
        return false;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (!cheat && angle > 50.f)
    {
        const Position* p = oldMoveInfo.GetPos();
        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Wallclimbing angle: " << angle << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_wallclimb::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        AntiCheat::HandleRelocate(x, y, z, o);
}

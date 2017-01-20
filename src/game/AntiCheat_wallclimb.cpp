#include "AntiCheat_wallclimb.h"
#include "CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_wallclimb::HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
        return SetOldMoveInfo(false);

    if ((GetDistanceZ() < WALKABLE_CLIMB && GetDistanceZ() > 0.f) && !isFalling(m_MoveInfo[0]))
        return false;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (!cheat && !isFlying() && !isSwimming() && angle > 50.f && !isFalling(m_MoveInfo[1]))
    {
        const Position* p = m_MoveInfo[1].GetPos();
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

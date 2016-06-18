#include "AntiCheat_wallclimb.h"
#include "CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_wallclimb::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if ((GetDistanceZ() < WALKABLE_CLIMB && GetDistanceZ() > 0.f) && !isFalling(m_MoveInfo[0]))
        return false;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (!isFlying() && !isSwimming() && angle > 50.f && !isFalling(m_MoveInfo[1]))
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->BoxChat << "Wallclimbing angle: " << angle << "\n";

        return true;
    }

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}


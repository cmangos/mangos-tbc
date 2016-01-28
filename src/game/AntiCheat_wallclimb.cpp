#include "AntiCheat_wallclimb.h"
#include "CPlayer.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
    jumping = false;
}

bool AntiCheat_wallclimb::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    std::stringstream& ss = m_Player->BoxChat;

    if (opcode == MSG_MOVE_JUMP)
        jumping = true;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (!isFlying() && !isSwimming() && angle > 50.f && !jumping)
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        ss << "Wallclimbing angle: " << angle << "\n";

        return true;
    }

    if (opcode == MSG_MOVE_FALL_LAND)
        jumping = false;

    if (abs(GetDistanceZ() > JUMPHEIGHT_WATER)) // If distanceZ is too small we won't update the old movement info
        m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_wallclimb::HandleTeleport()
{
    m_Initialized = false;
}

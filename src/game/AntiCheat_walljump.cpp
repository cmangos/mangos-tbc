#include "AntiCheat_walljump.h"
#include "CPlayer.h"
#include "PathFinder.h"

AntiCheat_walljump::AntiCheat_walljump(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_walljump::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        AboveAngleCount = 0;
        return false;
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (angle > 50.f)
        {
            if (AboveAngleCount)
            {
                const Position* pos = m_MoveInfo[2].GetPos();

                m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_COMBAT);
                m_Player->BoxChat << "Jumpclimbing angle: " << angle << "\n";
            }

            ++AboveAngleCount;
        }
        else
        {
            --AboveAngleCount;
            m_MoveInfo[2] = m_MoveInfo[0];
        }
    }
    else if (!isFalling(m_MoveInfo[0]) && GetDistanceZ() < 0.f)
        --AboveAngleCount;

    if (AboveAngleCount <= 0)
        AboveAngleCount = 0;

    if (opcode == MSG_MOVE_JUMP)
        m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

void AntiCheat_walljump::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        AntiCheat::HandleRelocate(x, y, z, o);
}

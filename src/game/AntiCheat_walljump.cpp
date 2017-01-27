#include "AntiCheat_walljump.h"
#include "CPlayer.h"
#include <algorithm>

AntiCheat_walljump::AntiCheat_walljump(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_walljump::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        AboveAngleCount = 0;
        return SetOldMoveInfo(false);
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (angle > 50.f)
        {
            if (!cheat && !isFlying() && !isSwimming() && AboveAngleCount)
            {
                const Position* pos = storedMoveInfo.GetPos();
                m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_COMBAT);

                if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                    m_Player->BoxChat << "Jumpclimbing angle: " << angle << "\n";

                cheat = true;
            }

            ++AboveAngleCount;
        }
        else
        {
            --AboveAngleCount;
            storedMoveInfo = newMoveInfo;
        }
    }
    else if (!isFalling(newMoveInfo) && GetDistanceZ() < 0.f)
        AboveAngleCount = std::max(AboveAngleCount, int8(0));

    if (opcode == MSG_MOVE_JUMP)
        return SetOldMoveInfo(cheat);

    return cheat;
}

void AntiCheat_walljump::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        AntiCheat::HandleRelocate(x, y, z, o);
}

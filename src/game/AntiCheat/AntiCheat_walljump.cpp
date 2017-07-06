#include "AntiCheat_walljump.h"
#include "Entities/CPlayer.h"
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
        return false;
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (angle > 50.f)
        {
            if (!cheat && !isFlying() && !isSwimming() && AboveAngleCount)
            {
				m_Player->TeleportToPos(storedMapID, storedMoveInfo.GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

                if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                    m_Player->BoxChat << "Jumpclimbing angle: " << angle << "\n";

                cheat = true;
            }

            ++AboveAngleCount;
        }
        else
        {
            --AboveAngleCount;
            SetStoredMoveInfo(false);
        }
    }

    AboveAngleCount = std::max(AboveAngleCount, int8(0));

    if (opcode == MSG_MOVE_JUMP)
    {
        if (!AboveAngleCount)
            SetStoredMoveInfo(false);

        return SetOldMoveInfo(cheat);
    }

    if (storedMoveInfo.GetPos()->z > newMoveInfo.GetPos()->z)
        AboveAngleCount = 0;

    return cheat;
}

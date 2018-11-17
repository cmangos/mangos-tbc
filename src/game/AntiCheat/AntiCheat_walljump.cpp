#include "AntiCheat_walljump.h"
#include "Entities/CPlayer.h"
#include <algorithm>

AntiCheat_walljump::AntiCheat_walljump(CPlayer* player) : AntiCheat(player)
{
    AboveAngleCount = 0;
}

bool AntiCheat_walljump::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        return SetOldMoveInfo(false);
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (angle > 50.f)
        {
            if (!cheat && !isFlying() && !isSwimming() && AboveAngleCount)
            {
				m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

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

    if (storedmoveInfo->GetPos()->z > newmoveInfo->GetPos()->z)
        AboveAngleCount = 0;

    return cheat;
}

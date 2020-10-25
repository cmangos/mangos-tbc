#include "AntiCheat_walljump.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"
#include <algorithm>

AntiCheat_walljump::AntiCheat_walljump(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_WALLJUMP;
    AboveAngleCount = 0;
}

bool AntiCheat_walljump::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized())
    {
        return SetOldMoveInfo(false);
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        if (angle > 50.f)
        {
            if (triggeredcheats.none() && !isFlying() && !isSwimming() && AboveAngleCount)
            {
				m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

                if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                    m_Player->BoxChat << "Jumpclimbing angle: " << angle << "\n";

                triggeredcheats.set(AntiCheatFieldOffsets::CHEAT_WALLJUMP);
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

        return SetOldMoveInfo(triggeredcheats.any());
    }

    if (storedmoveInfo->GetPos()->z > newmoveInfo->GetPos()->z)
        AboveAngleCount = 0;

    return triggeredcheats.any();
}

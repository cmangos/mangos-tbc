#include "AntiCheat_wallclimb.h"
#include "Custom/AntiCheat/AntiCheat.h"
#include "Custom/CPlayer.h"
#include "Server/Opcodes.h"

AntiCheat_wallclimb::AntiCheat_wallclimb(CPlayer* player) : AntiCheat(player)
{
    antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_WALLCLIMB;
}

bool AntiCheat_wallclimb::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, triggeredcheats);

    if (!Initialized() ||
        isTransport() ||
        GetDistanceZ() < 0.f ||
        CanFly())
        {
        return SetOldMoveInfo(false);
        }
    else if (isFlying() ||
        isSwimming() ||
        isFalling() ||
        (GetDistanceZ() > 0.f && GetDistanceZ() < JUMPHEIGHT_WATER) ||
        opcode == MSG_MOVE_FALL_LAND)
        return false;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;
    m_Player->BoxChat << "angle: " << angle << "\n";
    m_Player->BoxChat << "distance3d: " << GetDistance3D() << "\n";
    m_Player->BoxChat << "distancez: " << GetDistanceZ() << "\n";

    if (triggeredcheats.none() && angle > 50.f)
    {
		m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "Wallclimbing angle: " << angle << "\n";

        return SetOldMoveInfo(true);
    }
    else if (angle <= 50.f)
        SetStoredMoveInfo(false);

    return false;
}

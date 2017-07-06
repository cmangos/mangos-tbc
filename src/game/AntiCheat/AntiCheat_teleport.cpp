#include "AntiCheat_teleport.h"
#include "Entities/CPlayer.h"

AntiCheat_teleport::AntiCheat_teleport(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_teleport::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        knockBack = false;
        teleporting = false;
        return SetOldMoveInfo(false);
    }

    if (!cheat && !knockBack && !teleporting)
    {
        if (!IsMoving(oldMoveInfo) && GetDistOrTransportDist(true) > 0.1f && (!isFalling() || opcode == MSG_MOVE_JUMP))
        {
            const Position* p = oldMoveInfo.GetPos();
            m_Player->TeleportTo(oldMapID, p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

            if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                m_Player->BoxChat << "TELE CHEAT" << "\n";

            return SetOldMoveInfo(true);
        }
    }

    if (opcode == MSG_MOVE_FALL_LAND)
    {
        knockBack = false;
        teleporting = false;
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_teleport::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    knockBack = true;
}

void AntiCheat_teleport::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    AntiCheat::HandleTeleport(map, x, y, z, o);
    teleporting = true;
}


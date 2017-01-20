#include "AntiCheat_teleport.h"
#include "CPlayer.h"

AntiCheat_teleport::AntiCheat_teleport(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_teleport::HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        knockBack = false;
        return false;
    }

    if (opcode == MSG_MOVE_FALL_LAND)
        knockBack = false;

    if (!cheat && !IsMoving(m_MoveInfo[1]) && GetDistOrTransportDist() > 0.f && !knockBack)
    {
        const Position* p = m_MoveInfo[1].GetPos();
        m_Player->TeleportTo(m_Player->GetMapId(), p->x, p->y, p->z, p->o, TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
            m_Player->BoxChat << "TELE CHEAT" << "\n";

        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

void AntiCheat_teleport::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    knockBack = true;
}


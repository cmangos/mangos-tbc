#include "AntiCheat_teleport.h"
#include "CPlayer.h"

AntiCheat_teleport::AntiCheat_teleport(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_teleport::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (!IsMoving(m_MoveInfo[1]) && IsMoving(m_MoveInfo[0]) && GetDistOrTransportDist() > 0.f)
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);

        m_Player->BoxChat << "TELE CHEAT" << "\n";
    }

    m_MoveInfo[1] = m_MoveInfo[0];

    return false;
}

bool AntiCheat_teleport::IsMoving(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FORWARD) ||
        moveInfo.HasMovementFlag(MOVEFLAG_BACKWARD) ||
        moveInfo.HasMovementFlag(MOVEFLAG_STRAFE_LEFT) ||
        moveInfo.HasMovementFlag(MOVEFLAG_STRAFE_RIGHT) ||
        moveInfo.HasMovementFlag(MOVEFLAG_FALLING) ||
        moveInfo.HasMovementFlag(MOVEFLAG_FALLINGFAR) ||
        moveInfo.HasMovementFlag(MOVEFLAG_ASCENDING) ||
        moveInfo.HasMovementFlag(MOVEFLAG_SAFE_FALL);
}

void AntiCheat_teleport::HandleTeleport(float x, float y, float z)
{
    m_MoveInfo[1].ChangePosition(x, y, z, m_Player->GetOrientation());
}

void AntiCheat_teleport::HandleFlightpathFinish()
{
    float x, y, z;
    m_Player->GetPosition(x, y, z);
    m_MoveInfo[1].ChangePosition(x, y, z, m_Player->GetOrientation());
}

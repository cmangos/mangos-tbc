#include "AntiCheat_teleport.h"
#include "CPlayer.h"

AntiCheat_teleport::AntiCheat_teleport(Player* player) : AntiCheat(player)
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

    bool startMove = false;
    bool stopMove = false;

    switch (opcode) // Determine if they're going forwards or backwards
    {
    case MSG_MOVE_START_FORWARD:
    case MSG_MOVE_START_BACKWARD:
    case MSG_MOVE_START_STRAFE_LEFT:
    case MSG_MOVE_START_STRAFE_RIGHT:
    case MSG_MOVE_START_SWIM:
    case MSG_MOVE_START_ASCEND:
    case MSG_MOVE_START_DESCEND:
    case MSG_MOVE_JUMP:
        startMove = true;
        break;

    case MSG_MOVE_STOP:   
    case MSG_MOVE_STOP_STRAFE:
    case MSG_MOVE_STOP_TURN:
    case MSG_MOVE_STOP_SWIM:   
    case MSG_MOVE_STOP_ASCEND:
    case MSG_MOVE_FALL_LAND:
        stopMove = true;
        break;
    default:
        break;
    }

    if (!startMove && !stopMove)
        return false;

    MoveType moveType = NONE;

    switch (opcode) // Determine which type of movement they're doing
    {
    case MSG_MOVE_START_FORWARD:
    case MSG_MOVE_START_BACKWARD:
    case MSG_MOVE_STOP:
        moveType = MOVEY;
        break;
    case MSG_MOVE_START_STRAFE_LEFT:
    case MSG_MOVE_START_STRAFE_RIGHT:
    case MSG_MOVE_STOP_STRAFE:
        moveType = MOVEX;
        break;
    case MSG_MOVE_START_SWIM:
    case MSG_MOVE_STOP_SWIM:
        moveType = SWIM;
        break;
    case MSG_MOVE_START_ASCEND:
    case MSG_MOVE_START_DESCEND:
    case MSG_MOVE_STOP_ASCEND:
        moveType = MOVEZ;
        break;
    case MSG_MOVE_JUMP:
    case MSG_MOVE_FALL_LAND:
        moveType = JUMP;
        break;
    default:
        break;
    }

    if (moveType == NONE) // Shouldn't happen, but we don't want this in the container.
        return false;

    bool moving = false;

    for (auto& i : m_MoveMap) // Check if we're moving in any direction (before this packet was recieved)
        if (i.second)
            moving = true;

    if (startMove && !moving && GetDistance3D() > 0.f) // We started moving, wasn't moving before & distance is more then 0, damn cheaters.
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->ToCPlayer()->BoxChat << "TELE CHEAT!" << "\n";

        return true;
    }

    if (startMove) // Update data if we're moving or not.
        m_MoveMap[moveType] = true;
    else if (stopMove)
        m_MoveMap[moveType] = false;

    if (stopMove) // Only update old movementinfo if we're stopping
        m_MoveInfo[1] = m_MoveInfo[0];


    return false;
}

void AntiCheat_teleport::HandleUpdate(uint32 update_diff, uint32 p_time)
{
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
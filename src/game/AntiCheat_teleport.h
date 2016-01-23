#pragma once

#include "AntiCheat.h"

enum MoveType
{
    NONE,
    MOVEY,  // MSG_MOVE_START_FORWARD, MSG_MOVE_START_BACKWARD, MSG_MOVE_STOP
    MOVEX,  // MSG_MOVE_START_STRAFE_LEFT, MSG_MOVE_START_STRAFE_RIGHT, MSG_MOVE_STOP_STRAFE
    SWIM,   // MSG_MOVE_START_SWIM, MSG_MOVE_STOP_SWIM
    MOVEZ,  // MSG_MOVE_START_ASCEND, MSG_MOVE_START_DESCEND, MSG_MOVE_STOP_ASCEND
    JUMP,   // MSG_MOVE_JUMP, MSG_MOVE_FALL_LAND
};

/*
MSG_MOVE_START_FORWARD
MSG_MOVE_START_BACKWARD
MSG_MOVE_START_STRAFE_LEFT
MSG_MOVE_START_STRAFE_RIGHT
MSG_MOVE_START_SWIM
MSG_MOVE_START_ASCEND
MSG_MOVE_START_DESCEND
MSG_MOVE_JUMP

MSG_MOVE_STOP              
MSG_MOVE_STOP_STRAFE       
MSG_MOVE_STOP_TURN              
MSG_MOVE_STOP_SWIM         
MSG_MOVE_STOP_ASCEND       
*/

class AntiCheat_teleport : public AntiCheat
{
public:
    typedef std::unordered_map<MoveType, bool> MoveMap;
    AntiCheat_teleport(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleUpdate(uint32 update_diff, uint32 p_time);
    bool IsMoving(MovementInfo& moveInfo);
private:
    MoveMap m_MoveMap;
};

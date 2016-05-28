#pragma once

#include "AntiCheat.h"

class AntiCheat_teleport : public AntiCheat
{
public:
    AntiCheat_teleport(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
};

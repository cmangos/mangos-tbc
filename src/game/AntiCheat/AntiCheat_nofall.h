#pragma once

#include "AntiCheat.h"

class AntiCheat_nofall : public AntiCheat
{
public:
    AntiCheat_nofall(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat);
};

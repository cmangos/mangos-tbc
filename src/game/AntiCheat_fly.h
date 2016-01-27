#pragma once

#include "AntiCheat.h"

class AntiCheat_fly : public AntiCheat
{
public:
    AntiCheat_fly(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    bool CanFly();
};

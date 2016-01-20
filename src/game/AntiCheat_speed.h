#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
};
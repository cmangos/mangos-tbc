#pragma once

#include "AntiCheat.h"


class AntiCheat_waterwalking : public AntiCheat
{
public:
    AntiCheat_waterwalking(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
};

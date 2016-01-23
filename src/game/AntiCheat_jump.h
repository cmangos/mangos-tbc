#pragma once

#include "AntiCheat.h"


class AntiCheat_jump : public AntiCheat
{
public:
    AntiCheat_jump(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);

private:
    bool jumping;
};

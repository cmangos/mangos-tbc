#pragma once

#include "AntiCheat.h"

class AntiCheat_test : public AntiCheat
{
public:
    AntiCheat_test(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleRelocate(float x, float y, float z, float o);
};

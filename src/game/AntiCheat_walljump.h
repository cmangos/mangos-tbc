#pragma once

#include "AntiCheat.h"

class AntiCheat_walljump : public AntiCheat
{
public:
    AntiCheat_walljump(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleRelocate(float x, float y, float z, float o);
private:
    int8 AboveAngleCount;
};

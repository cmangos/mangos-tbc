#pragma once

#include "AntiCheat.h"

class AntiCheat_walljump : public AntiCheat
{
public:
    AntiCheat_walljump(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat) override;
    void HandleRelocate(float x, float y, float z, float o) override;
private:
    int8 AboveAngleCount;
};

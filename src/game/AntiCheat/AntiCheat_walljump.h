#pragma once

#include "AntiCheat.h"

class AntiCheat_walljump : public AntiCheat
{
public:
    AntiCheat_walljump(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
private:
    int8 AboveAngleCount;
};

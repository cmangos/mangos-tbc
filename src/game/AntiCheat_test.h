#pragma once

#include "AntiCheat.h"

class AntiCheat_test : public AntiCheat
{
public:
    AntiCheat_test(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
};

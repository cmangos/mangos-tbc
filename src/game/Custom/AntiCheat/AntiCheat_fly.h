#pragma once

#include "AntiCheat.h"

class AntiCheat_fly : public AntiCheat
{
public:
    AntiCheat_fly(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;
};

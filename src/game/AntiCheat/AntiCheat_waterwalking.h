#pragma once

#include "AntiCheat.h"

class AntiCheat_waterwalking : public AntiCheat
{
public:
    AntiCheat_waterwalking(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;
};

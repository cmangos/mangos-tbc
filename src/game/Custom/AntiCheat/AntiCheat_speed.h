#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;

    float RoundFloat(float value, float rounding, bool up)
    {
        if (up)
            return ceil(value * rounding) / rounding;

        return floor(value * rounding) / rounding;
    }
};

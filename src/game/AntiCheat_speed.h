#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);
    void HandleRelocate(float x, float y, float z, float o);
private:
    float fallspeed;
    bool knockback;
};

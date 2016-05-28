#pragma once

#include "AntiCheat.h"

class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleRelocate(float x, float y, float z, float o);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);
private:
    bool knockBack;
    float m_StartJumpZ;
    bool m_StartJumpWater;
};

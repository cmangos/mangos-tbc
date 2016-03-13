#pragma once

#include "AntiCheat.h"

class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleTeleport(float x, float y, float z);
private:
    float m_StartJumpZ;
    bool m_StartJumpWater;
};

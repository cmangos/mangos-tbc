#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);
private:
    bool m_LastCheat;

    float knockback_angle;
    float knockback_horizontalSpeed;
    float knockback_verticalSpeed;
};

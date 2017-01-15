#pragma once

#include "AntiCheat.h"

class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleTeleport(uint32 map, float x, float y, float z, float o);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);

    float computeFallElevation(float t_passed, bool isSafeFall, float start_velocity);

private:
    float m_StartFallZ;
    float m_StartVelocity;
    bool m_Falling;
    bool m_SlowFall;

    double gravity;

    /// Velocity bounds that makes fall speed limited
    float terminalVelocity;
    float terminalSavefallVelocity;

    float terminal_length;
    float terminal_savefall_length;
    float terminalFallTime;
};

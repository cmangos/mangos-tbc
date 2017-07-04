#pragma once

#include "AntiCheat.h"

class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
    void HandleTeleport(uint32 map, float x, float y, float z, float o) override;
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed) override;

    float ComputeFallElevation(float t_passed, bool isSafeFall, float start_velocity);

private:
    float m_StartFallZ;
    float m_StartVelocity;
    float m_InitialDiff;
    bool m_Falling;
    bool m_Jumping;
    bool m_SlowFall;
};

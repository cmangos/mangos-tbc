#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed) override;
    float GetAllowedSpeed();
    float IsKnockedback() { return m_Knockback; }
    float GetKnockBackSpeed() { return m_KnockbackSpeed; }

private:
    bool m_Knockback;
    float m_KnockbackSpeed;
};

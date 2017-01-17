#pragma once

#include "AntiCheat.h"

class AntiCheat_teleport : public AntiCheat
{
public:
    AntiCheat_teleport(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);
private:
    bool knockBack;
};

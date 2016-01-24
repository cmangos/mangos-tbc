#pragma once

#include "AntiCheat.h"


class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(Player* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
private:
    float m_StartJumpZ;
    bool jumping;
};

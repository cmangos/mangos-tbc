#pragma once

#include "AntiCheat.h"

class AntiCheat_wallclimb : public AntiCheat
{
public:
    AntiCheat_wallclimb(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleRelocate(float x, float y, float z, float o);
private:
    bool jumping;
};

#pragma once

#include "AntiCheat.h"

class AntiCheat_wallclimb : public AntiCheat
{
public:
    AntiCheat_wallclimb(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
    void HandleRelocate(float x, float y, float z, float o) override;
private:
};

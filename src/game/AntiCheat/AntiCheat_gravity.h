#pragma once

#include "AntiCheat.h"

class AntiCheat_gravity : public AntiCheat
{
public:
    AntiCheat_gravity(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;

private:
    uint32 GetCorrectedFallTime();
    int32 timeCorrection;
    float startZ;
};

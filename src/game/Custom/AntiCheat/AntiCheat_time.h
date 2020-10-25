#pragma once

#include "AntiCheat.h"

class AntiCheat_time : public AntiCheat
{
public:
    AntiCheat_time(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats) override;
    void HandleUpdate(uint32 updatediffms) override;

private:
    int64 calculatedServerTime;
};

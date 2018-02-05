#pragma once

#include "AntiCheat.h"

class AntiCheat_time : public AntiCheat
{
public:
    AntiCheat_time(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;
    uint32 GetTimeDiff();

private:
    int64 ClientServerTimeOffset;
};

#pragma once

#include "AntiCheat.h"

class AntiCheat_time : public AntiCheat
{
public:
    AntiCheat_time(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
    void HandleUpdate(uint32 update_diff, uint32 p_time) override;

private:
    int64 m_RelativeServerTime;
};

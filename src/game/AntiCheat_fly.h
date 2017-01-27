#pragma once

#include "AntiCheat.h"

class AntiCheat_fly : public AntiCheat
{
public:
    AntiCheat_fly(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;

private:
    uint32 m_LastCanFlyTime;
};

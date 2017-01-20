#pragma once

#include "AntiCheat.h"

class AntiCheat_fly : public AntiCheat
{
public:
    AntiCheat_fly(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode, bool cheat) override;
    bool CanFly();

private:
    uint32 m_LastFlyTime;
};

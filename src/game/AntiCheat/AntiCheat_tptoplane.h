#pragma once

#include "AntiCheat.h"

class AntiCheat_tptoplane : public AntiCheat
{
public:
    AntiCheat_tptoplane(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
};

#pragma once

#include "AntiCheat.h"

class AntiCheat_wallclimb : public AntiCheat
{
public:
    AntiCheat_wallclimb(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat) override;
private:
};

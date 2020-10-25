#pragma once

#include "AntiCheat.h"

class AntiCheat_teleport : public AntiCheat
{
public:
    AntiCheat_teleport(CPlayer* player);

    bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats) override;
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed) override;
    void HandleTeleport(uint32 map, float x, float y, float z, float o) override;
private:
    bool serverInitiatedMove;
};

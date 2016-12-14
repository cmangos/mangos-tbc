#pragma once

#include "AntiCheat.h"

class AntiCheat_slowfall : public AntiCheat
{
public:
    AntiCheat_slowfall(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleRelocate(float x, float y, float z, float o);
    void HandleTeleport(uint32 map, float x, float y, float z, float o);

private:
	float m_OldSpeed;
};

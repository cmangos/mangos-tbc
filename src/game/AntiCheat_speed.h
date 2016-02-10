#pragma once

#include "AntiCheat.h"

class AntiCheat_speed : public AntiCheat
{
public:
    AntiCheat_speed(CPlayer* player);

    bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode);
    void HandleTeleport(float x, float y, float z);
    void HandleFlightpathFinish();
    float floor100(float& value);
    float ceil100(float& value);
private:
    uint32 m_LastFallCheck;
    float fallingFromTransportSpeed;
};

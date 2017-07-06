#pragma once

#include "AntiCheat.h"

class AntiCheat_time : public AntiCheat
{
public:
    AntiCheat_time(CPlayer* player);

    bool HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat) override;
    uint32 GetServerDiff();

private:
    time_t m_LastGameTime;

    std::deque<uint32> m_ServerDiffs;
    std::deque<uint32> m_ClientDiffs;
};

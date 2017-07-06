#include <numeric>

#include "AntiCheat_time.h"
#include "World/World.h"
#include "Entities/CPlayer.h"
#include "Entities/Transports.h"

AntiCheat_time::AntiCheat_time(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_time::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        m_LastGameTime = sWorld.GetGameTime();
        return SetOldMoveInfo(false);
    }

    if (GetDiff() < 500)
        return false;

    m_ServerDiffs.push_back(GetServerDiff());
    m_ClientDiffs.push_back(GetDiff());

    // Only store last 20 
    while (m_ServerDiffs.size() > 20)
    {
        m_ServerDiffs.pop_front();
        m_ClientDiffs.pop_front();
    }

    bool supercheat = GetDiff() > GetServerDiff() * 2; // Faster detection if they cheat bigtime

    if (m_ServerDiffs.size() > 10 || supercheat)
    {
        uint32 TotalServerDiff = std::accumulate(m_ServerDiffs.begin(), m_ServerDiffs.end(), 0) + m_Player->GetSession()->GetLatency() + 50; // 50 is how long we spend between updates
        uint32 TotalClientDiff = std::accumulate(m_ClientDiffs.begin(), m_ClientDiffs.end(), 0);

        if (TotalClientDiff > TotalServerDiff || supercheat)
        {
            if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
                m_Player->BoxChat << "TIME CHEAT" << "\n";

            // Punish player in some way here
        }
    }

    m_LastGameTime = sWorld.GetGameTime();
    return SetOldMoveInfo(false);
}

uint32 AntiCheat_time::GetServerDiff()
{
    return std::abs(sWorld.GetGameTime() - m_LastGameTime);
}
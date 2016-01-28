#include "AntiCheat_speed.h"
#include "CPlayer.h"
#include "World.h"
#include "Map.h"

AntiCheat_speed::AntiCheat_speed(CPlayer* player) : AntiCheat(player)
{
    m_LastFallCheck = 0;
    fallingFromTransportSpeed = 0.f;
}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    if (isTransport(m_MoveInfo[0]) && isTransport(m_MoveInfo[1])) // If player is on transport we store his speed, it'll be 
        fallingFromTransportSpeed = GetDiffInSec() * GetDistance3D();

    float distance = GetDistOrTransportDist();
    distance = floor(distance * 1000.0f) / 1000.0f; // Dirty float rounding (only want to calculate with the last 3 digits)
    float alloweddistance = fallingFromTransportSpeed > 0.f ? fallingFromTransportSpeed : GetAllowedDistance();

    if (distance < GetSpeed(false))
        return false;

    bool sliding = false;
    if (isFalling() && sWorld.GetGameTime() - m_LastFallCheck > 100)
    {
        if (Map* pMap = m_Player->GetMap())
        {
            auto pos = m_MoveInfo[0].GetPos();
            auto groundZ = pMap->GetHeight(pos->x, pos->y, pos->z);

            if (abs(groundZ - pos->z) < 1)
                sliding = true;
        }

        m_LastFallCheck = sWorld.GetGameTime();
    }

    if (sliding)
        alloweddistance *= 3;

    if (distance > alloweddistance)
    {
        const Position* pos = m_MoveInfo[1].GetPos();

        m_Player->TeleportTo(m_Player->GetMapId(), pos->x, pos->y, pos->z, pos->o, TELE_TO_NOT_LEAVE_TRANSPORT & TELE_TO_NOT_LEAVE_COMBAT);
        m_Player->BoxChat << "Distance: " << distance << " alloweddistance: " << alloweddistance << " toofast: " << (distance > alloweddistance ? "true" : "false") << "\n";

        return true;
    }

    if (!isFalling())
        fallingFromTransportSpeed = 0.f;

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}

void AntiCheat_speed::HandleTeleport()
{
    m_Initialized = false;
}

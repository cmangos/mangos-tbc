#include "AntiCheat_speed.h"
#include "CPlayer.h"

AntiCheat_speed::AntiCheat_speed(Player* player) : AntiCheat(player)
{

}

bool AntiCheat_speed::HandleMovement(MovementInfo& moveInfo, Opcodes opcode)
{
    m_MoveInfo[0] = moveInfo; // moveInfo shouldn't be used anymore then assigning it in the beginning.

    if (!Initialized())
    {
        m_MoveInfo[1] = m_MoveInfo[0];
        return false;
    }

    float distance = GetDistance();
    distance = floor(distance * 1000.0f) / 1000.0f; // Dirty float rounding (only want to calculate with the last 3 digits)
    float alloweddistance = GetAllowedDistance();

    if (distance < GetSpeed() && GetDiffInSec() < 1)
        return false;

    m_Player->ToCPlayer()->BoxChat << "Distance: " << distance << " alloweddistance: " << alloweddistance <<  " toofast: " << (distance > alloweddistance ? "true" : "false") << "\n";

    m_MoveInfo[1] = m_MoveInfo[0];
    return false;
}

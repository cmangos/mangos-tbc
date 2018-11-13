#include "AntiCheat_gravity.h"
#include "Entities/CPlayer.h"

#include <iomanip>

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_gravity::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    if (CanFly())
        return SetOldMoveInfo();

    auto diff = newmoveInfo->GetPos()->z - GetExpectedZ(newmoveInfo->GetFallTime());

    if (!isFalling())
        SetStoredMoveInfo();

    if (!cheat && isFalling() && diff > GetFallDistance() * 0.01f && diff > 0.01f)
    {
        m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);

        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "Gravity hack" << "\n";
            m_Player->BoxChat << std::fixed << "diff:" << diff << std::endl;
            m_Player->BoxChat << "currentz: " << newmoveInfo->GetPos()->z << std::endl;
            m_Player->BoxChat << "expectedz: " << GetExpectedZ(newmoveInfo->GetFallTime()) << std::endl;
            m_Player->BoxChat << "velocityZ: " << GetDistanceZ() / GetDiffInSec() << std::endl;
            m_Player->BoxChat << "falltime: " << newmoveInfo->GetFallTime() << std::endl;
            m_Player->BoxChat << "falldistance: " << GetFallDistance() << std::endl;
        }
    }

    return SetOldMoveInfo(false);
}

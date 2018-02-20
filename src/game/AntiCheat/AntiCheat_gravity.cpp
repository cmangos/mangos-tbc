#include "AntiCheat_gravity.h"
#include "Entities/CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_gravity::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    float falldiff = newmoveInfo->GetPos()->z -  GetExpectedZ();

    if (!cheat && isFalling() && falldiff > 0.1f && !CanFly()) // Make acceptable diff configureable
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "currentz: " << newmoveInfo->GetPos()->z << std::endl;
            m_Player->BoxChat << "expectedz: " << GetExpectedZ() << std::endl;
            m_Player->BoxChat << "velocityZ: " << GetDistanceZ() / GetDiffInSec() << std::endl;
            m_Player->BoxChat << "diff: " << falldiff << std::endl;
            m_Player->BoxChat << "Gravity hack" << std::endl;
        }
    
        m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);
    
        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

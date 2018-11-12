#include "AntiCheat_gravity.h"
#include "Entities/CPlayer.h"

AntiCheat_gravity::AntiCheat_gravity(CPlayer* player) : AntiCheat(player)
{
    timeCorrection = 0;
    startZ = 0.f;
}

bool AntiCheat_gravity::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    if ((timeCorrection == 0 && newmoveInfo->GetFallTime()) > 0 || newmoveInfo->GetFallTime() < timeCorrection)
        timeCorrection = newmoveInfo->GetFallTime();

    float falldiff = newmoveInfo->GetPos()->z - GetExpectedZ(GetCorrectedFallTime());
    float magicnumber = (GetFallDistance() + falldiff) / GetFallDistance();

    if (!cheat && isFalling() && magicnumber > 1.05f && GetCorrectedFallTime() > 500 && !CanFly())
    {
        if (m_Player->GetSession()->GetSecurity() > SEC_PLAYER)
        {
            m_Player->BoxChat << "currentz: " << newmoveInfo->GetPos()->z << std::endl;
            m_Player->BoxChat << "expectedz: " << GetExpectedZ(GetCorrectedFallTime()) << std::endl;
            m_Player->BoxChat << "velocityZ: " << GetDistanceZ() / GetDiffInSec() << std::endl;
            m_Player->BoxChat << "diff: " << falldiff << std::endl;
            m_Player->BoxChat << "falltime: " << newmoveInfo->GetFallTime() << std::endl;
            m_Player->BoxChat << "falldistance: " << GetFallDistance() << std::endl;
            m_Player->BoxChat << "magicnumber: " << magicnumber << std::endl;
            m_Player->BoxChat << "Gravity hack" << std::endl;
        }
    
        m_Player->TeleportToPos(storedMapID, storedmoveInfo->GetPos(), TELE_TO_NOT_LEAVE_COMBAT);
    
        return SetOldMoveInfo(true);
    }

    return SetOldMoveInfo(false);
}

uint32 AntiCheat_gravity::GetCorrectedFallTime()
{
    return newmoveInfo->GetFallTime() - timeCorrection;
}

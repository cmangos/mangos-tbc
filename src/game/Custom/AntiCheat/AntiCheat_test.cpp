#include "AntiCheat_test.h"
#include "Custom/CPlayer.h"
#include "Entities/Transports.h"

AntiCheat_test::AntiCheat_test(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_test::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
        return false;

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    m_Player->BoxChat << "cosAngle: " << newmoveInfo->GetJumpInfo().cosAngle << "\n";
    m_Player->BoxChat << "sinAngle: " << newmoveInfo->GetJumpInfo().sinAngle << "\n";
    m_Player->BoxChat << "velocity: " << newmoveInfo->GetJumpInfo().velocity << "\n";
    m_Player->BoxChat << "xyspeed: " << newmoveInfo->GetJumpInfo().xyspeed << "\n";
    m_Player->BoxChat << "cposx: " << newmoveInfo->GetPos()->x << "\n";
    m_Player->BoxChat << "cposy: " << newmoveInfo->GetPos()->y << "\n";
    m_Player->BoxChat << "cposz: " << newmoveInfo->GetPos()->z << "\n";
    m_Player->BoxChat << "angle: " << angle << "\n";
    m_Player->BoxChat << "moving: " << (IsMoving(newmoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "falling: " << (isFalling(newmoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "flying: " << (isFlying(newmoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "transport: " << (isTransport(newmoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "slowfall: " << (newmoveInfo->HasMovementFlag(MOVEFLAG_SAFE_FALL) ? "true" : "false") << "\n";

    return SetOldMoveInfo(false);
}

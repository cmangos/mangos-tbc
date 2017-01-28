#include "AntiCheat_test.h"
#include "CPlayer.h"
#include "Transports.h"

AntiCheat_test::AntiCheat_test(CPlayer* player) : AntiCheat(player)
{
}

bool AntiCheat_test::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    AntiCheat::HandleMovement(MoveInfo, opcode, cheat);

    if (!Initialized())
    {
        oldMoveInfo = newMoveInfo;
        return false;
    }

    float angle = std::atan2(GetDistanceZ(), GetDistance2D()) * 180.f / M_PI_F;

    m_Player->BoxChat << "cosAngle: " << newMoveInfo.GetJumpInfo().cosAngle << "\n";
    m_Player->BoxChat << "sinAngle: " << newMoveInfo.GetJumpInfo().sinAngle << "\n";
    m_Player->BoxChat << "velocity: " << newMoveInfo.GetJumpInfo().velocity << "\n";
    m_Player->BoxChat << "xyspeed: " << newMoveInfo.GetJumpInfo().xyspeed << "\n";
    m_Player->BoxChat << "cposx: " << newMoveInfo.GetPos()->x << "\n";
    m_Player->BoxChat << "cposy: " << newMoveInfo.GetPos()->y << "\n";
    m_Player->BoxChat << "cposz: " << newMoveInfo.GetPos()->z << "\n";
    m_Player->BoxChat << "angle: " << angle << "\n";
    m_Player->BoxChat << "moving: " << (IsMoving(newMoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "falling: " << (isFalling(newMoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "flying: " << (isFlying(newMoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "transport: " << (isTransport(newMoveInfo) ? "true" : "false") << "\n";
    m_Player->BoxChat << "slowfall: " << (newMoveInfo.HasMovementFlag(MOVEFLAG_SAFE_FALL) ? "true" : "false") << "\n";

    oldMoveInfo = newMoveInfo;

    return false;
}

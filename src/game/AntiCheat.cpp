#include "AntiCheat.h"
#include "CPlayer.h"

AntiCheat::AntiCheat(CPlayer* player)
{
    m_Player = player;

    oldMoveInfo = MovementInfo();
    storedMoveInfo = MovementInfo();

    m_Initialized = false;

    player->AddAntiCheatModule(this);
}

bool AntiCheat::HandleMovement(MovementInfo& MoveInfo, Opcodes opcode, bool cheat)
{
    newMoveInfo = MoveInfo;

    return false;
}

void AntiCheat::HandleRelocate(float x, float y, float z, float o)
{
    oldMoveInfo.ChangePosition(x, y, z, o);
}

void AntiCheat::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    oldMoveInfo.ChangePosition(x, y, z, o);
}

bool AntiCheat::Initialized()
{
    if (!m_Initialized)
    {
        m_Initialized = true;
        return false;
    }

    return true;
}

bool AntiCheat::CanFly()
{
    return m_Player->HasAuraType(SPELL_AURA_FLY) || m_Player->GetGMFly();
}

bool AntiCheat::IsMoving(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FORWARD) ||
        moveInfo.HasMovementFlag(MOVEFLAG_BACKWARD) ||
        moveInfo.HasMovementFlag(MOVEFLAG_STRAFE_LEFT) ||
        moveInfo.HasMovementFlag(MOVEFLAG_STRAFE_RIGHT) ||
        moveInfo.HasMovementFlag(MOVEFLAG_FALLING) ||
        moveInfo.HasMovementFlag(MOVEFLAG_FALLINGFAR) ||
        moveInfo.HasMovementFlag(MOVEFLAG_ASCENDING) ||
        moveInfo.HasMovementFlag(MOVEFLAG_SAFE_FALL);
}

bool AntiCheat::IsMoving()
{
    return IsMoving(newMoveInfo) || IsMoving(oldMoveInfo);
}

bool AntiCheat::isFlying(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FLYING) || moveInfo.HasMovementFlag(MOVEFLAG_FLYING2);
}

bool AntiCheat::isFlying()
{
    return isFlying(newMoveInfo) || isFlying(oldMoveInfo);
}

bool AntiCheat::isWalking(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_WALK_MODE);
}

bool AntiCheat::isWalking()
{
    return isWalking(newMoveInfo) || isWalking(oldMoveInfo);
}

bool AntiCheat::isFalling(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FALLING) || moveInfo.HasMovementFlag(MOVEFLAG_FALLINGFAR);
}

bool AntiCheat::isFalling()
{
    return isFalling(newMoveInfo) || isFalling(oldMoveInfo);
}

bool AntiCheat::isTransport(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_ONTRANSPORT);
}

bool AntiCheat::isTransport()
{
    return isTransport(newMoveInfo) || isTransport(oldMoveInfo);
}

bool AntiCheat::isSwimming(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_SWIMMING);
}

bool AntiCheat::isSwimming()
{
    return isSwimming(newMoveInfo) || isSwimming(oldMoveInfo) || m_Player->IsInWater();
}

bool AntiCheat::verifyTransportCoords(MovementInfo& moveInfo)
{
    return !(std::abs(newMoveInfo.GetTransportPos()->x) > 100 || std::abs(newMoveInfo.GetTransportPos()->y) > 100 || std::abs(newMoveInfo.GetTransportPos()->z) > 100);
}

bool AntiCheat::verifyTransportCoords()
{
    return verifyTransportCoords(newMoveInfo) || verifyTransportCoords(oldMoveInfo);
}

float AntiCheat::GetDistOrTransportDist()
{
    return GetDistOrTransportDist(isFlying());
}

float AntiCheat::GetDistOrTransportDist(bool threed)
{
    return isTransport(newMoveInfo) && isTransport(oldMoveInfo) ? GetTransportDist(threed) : GetDistance(threed);
}

float AntiCheat::GetDistanceZ()
{
    return newMoveInfo.GetPos()->z - oldMoveInfo.GetPos()->z;
}

float AntiCheat::GetDistance()
{
    return GetDistance(isFlying());
}

float AntiCheat::GetDistance(bool threed)
{
    return threed ? GetDistance3D() : GetDistance2D();
}

float AntiCheat::GetDistance2D()
{
    return
        sqrt(pow(newMoveInfo.GetPos()->x - oldMoveInfo.GetPos()->x, 2) +
            pow(newMoveInfo.GetPos()->y - oldMoveInfo.GetPos()->y, 2));
}

float AntiCheat::GetDistance3D()
{
    return
        sqrt(pow(newMoveInfo.GetPos()->x - oldMoveInfo.GetPos()->x, 2) +
            pow(newMoveInfo.GetPos()->y - oldMoveInfo.GetPos()->y, 2) +
            pow(newMoveInfo.GetPos()->z - oldMoveInfo.GetPos()->z, 2));
}

float AntiCheat::GetTransportDist()
{
    return GetTransportDist(isFlying());
}

float AntiCheat::GetTransportDist(bool threed)
{
    return threed ? GetTransportDist3D() : GetTransportDist2D();
}

float AntiCheat::GetTransportDist2D()
{
    return
        sqrt(pow(newMoveInfo.GetTransportPos()->x - oldMoveInfo.GetTransportPos()->x, 2) +
            pow(newMoveInfo.GetTransportPos()->y - oldMoveInfo.GetTransportPos()->y, 2));
}

float AntiCheat::GetTransportDist3D()
{
    return
        sqrt(pow(newMoveInfo.GetTransportPos()->x - oldMoveInfo.GetTransportPos()->x, 2) +
            pow(newMoveInfo.GetTransportPos()->y - oldMoveInfo.GetTransportPos()->y, 2) +
            pow(newMoveInfo.GetTransportPos()->z - oldMoveInfo.GetTransportPos()->z, 2));
}

float AntiCheat::GetTransportDistZ()
{
    return newMoveInfo.GetTransportPos()->z - oldMoveInfo.GetTransportPos()->z;
}

float AntiCheat::GetSpeed()
{
    // Positive speed modifiers are applied if they're active in current or previous, negative if they're active in previous and current.
    bool back = newMoveInfo.HasMovementFlag(MOVEFLAG_BACKWARD) && oldMoveInfo.HasMovementFlag(MOVEFLAG_BACKWARD);

    float speed = m_Player->GetSpeed(back ? MOVE_RUN_BACK : MOVE_RUN);

    if (isFlying(newMoveInfo) || isFlying(oldMoveInfo))
        speed = m_Player->GetSpeed(back ? MOVE_FLIGHT_BACK : MOVE_FLIGHT);
    else if (isWalking(newMoveInfo) && isWalking(oldMoveInfo))
        speed = m_Player->GetSpeed(MOVE_WALK);
    else if (isSwimming(newMoveInfo) && isSwimming(oldMoveInfo))
        speed = m_Player->GetSpeed(back ? MOVE_SWIM_BACK : MOVE_SWIM);

    return speed;
}

float AntiCheat::GetAllowedDistance()
{
    return GetDiffInSec() * GetSpeed();
}

uint32 AntiCheat::GetDiff()
{
    uint32 t1 = newMoveInfo.GetTime();
    uint32 t2 = oldMoveInfo.GetTime();

    return std::max(uint32(1), std::max(t1, t2) - std::min(t1, t2));
}

float AntiCheat::GetDiffInSec()
{
    return GetDiff() / 1000.f;
}

float AntiCheat::GetVirtualDiffInSec()
{
    if (IsMoving(newMoveInfo) && !IsMoving(oldMoveInfo))
        return 1.f;

    return GetDiffInSec();
}

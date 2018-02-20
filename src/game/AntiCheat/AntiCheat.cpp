#include "AntiCheat.h"
#include "Entities/CPlayer.h"

AntiCheat::AntiCheat(CPlayer* player)
{
    m_Player = player;

    newmoveInfo = MovementInfoPtr(new MovementInfo());
    oldmoveInfo = MovementInfoPtr(new MovementInfo());
    storedmoveInfo = MovementInfoPtr(new MovementInfo());

    m_Initialized = false;
    m_CanFly = false;
    m_CanWaterwalk = false;

    m_StartFallZ = 0;
    m_Falling = false;

    m_Knockback = false;
    m_KnockbackSpeed = 0.f;

    player->AddAntiCheatModule(this);
}

bool AntiCheat::HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat)
{
    newmoveInfo = MoveInfo;
    newMapID = m_Player->GetMapId();

    if (m_Player->HasAuraType(SPELL_AURA_FLY) || m_Player->HasAuraType(SPELL_AURA_MOD_FLIGHT_SPEED_MOUNTED) || m_Player->GetGMFly())
        m_CanFly = true;
    else if (opcode == CMSG_MOVE_SET_CAN_FLY_ACK) // Trust that client will send ack when he's told not to fly anymore
        m_CanFly = false;

    if (m_Player->HasAuraType(SPELL_AURA_WATER_WALK) || m_Player->HasAuraType(SPELL_AURA_GHOST))
        m_CanWaterwalk = true;
    else if (opcode == CMSG_MOVE_WATER_WALK_ACK)
        m_CanWaterwalk = false;

    if (opcode == MSG_MOVE_FALL_LAND || !isFalling(newmoveInfo))
        m_Knockback = false;

    UpdateGravityInfo(opcode);
    UpdateSpeedInfo(opcode);

    return false;
}

void AntiCheat::HandleRelocate(float x, float y, float z, float o)
{
    if (m_Player->IsTaxiFlying())
        oldmoveInfo->ChangePosition(x, y, z, o);
}

void AntiCheat::HandleTeleport(uint32 map, float x, float y, float z, float o)
{
    oldmoveInfo->ChangePosition(x, y, z, o);
    oldMapID = map;

    m_Falling = true;
    m_Jumping = false;
    m_StartFallZ = z;
    m_StartVelocity = 0.f;
}

void AntiCheat::HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed)
{
    m_Falling = true;
    m_Jumping = false;
    m_StartFallZ = newmoveInfo->GetPos()->z;
    m_StartVelocity = -verticalSpeed;
    m_InitialDiff = -1.f;

    m_Knockback = true;
    m_KnockbackSpeed = horizontalSpeed;
}

bool AntiCheat::Initialized()
{
    if (!m_Initialized || m_Player->GetMapId() != oldMapID)
    {
        m_Initialized = true;
        SetOldMoveInfo(false);
        SetStoredMoveInfo(false);

        for (uint8 i = 0; i < MAX_MOVE_TYPE; ++i)
            AllowedSpeed[i] = m_Player->GetSpeed(UnitMoveType(i));

        m_Falling = false;
        m_Jumping = false;
        m_SlowFall = false;
        m_StartFallZ = 0.f;
        m_StartVelocity = 0.f;
        m_InitialDiff = -1.f;

        return false;
    }

    return true;
}

bool AntiCheat::SetOldMoveInfo(bool value)
{
    oldmoveInfo = newmoveInfo;
    oldMapID = m_Player->GetMapId();

    OldServerSpeed = GetServerSpeed(false);

    return value;
}

bool AntiCheat::SetStoredMoveInfo(bool value)
{
    storedmoveInfo = newmoveInfo;
    storedMapID = m_Player->GetMapId();
    return value;
}

bool AntiCheat::IsMoving(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_FORWARD) ||
        moveInfo->HasMovementFlag(MOVEFLAG_BACKWARD) ||
        moveInfo->HasMovementFlag(MOVEFLAG_STRAFE_LEFT) ||
        moveInfo->HasMovementFlag(MOVEFLAG_STRAFE_RIGHT) ||
        moveInfo->HasMovementFlag(MOVEFLAG_FALLING) ||
        moveInfo->HasMovementFlag(MOVEFLAG_FALLINGFAR) ||
        moveInfo->HasMovementFlag(MOVEFLAG_ASCENDING) ||
        moveInfo->HasMovementFlag(MOVEFLAG_SAFE_FALL);
}

bool AntiCheat::IsMoving()
{
    return IsMoving(newmoveInfo) || IsMoving(oldmoveInfo);
}

bool AntiCheat::isFlying(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_FLYING) || moveInfo->HasMovementFlag(MOVEFLAG_FLYING2);
}

bool AntiCheat::isFlying()
{
    return isFlying(newmoveInfo) || isFlying(oldmoveInfo);
}

bool AntiCheat::isWalking(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_WALK_MODE);
}

bool AntiCheat::isWalking()
{
    return isWalking(newmoveInfo) || isWalking(oldmoveInfo);
}

bool AntiCheat::isFalling(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_FALLING) || moveInfo->HasMovementFlag(MOVEFLAG_FALLINGFAR);
}

bool AntiCheat::isFalling()
{
    return m_Falling;
}

bool AntiCheat::isFallingMoveInfo()
{
    return isFalling(newmoveInfo) || isFalling(oldmoveInfo);
}

bool AntiCheat::isTransport(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_ONTRANSPORT);
}

bool AntiCheat::isTransport()
{
    return isTransport(newmoveInfo) || isTransport(oldmoveInfo);
}

bool AntiCheat::isSwimming(const MovementInfoPtr& moveInfo)
{
    return moveInfo->HasMovementFlag(MOVEFLAG_SWIMMING);
}

bool AntiCheat::isSwimming()
{
    return isSwimming(newmoveInfo) || isSwimming(oldmoveInfo) || m_Player->IsInWater();
}

bool AntiCheat::verifyTransportCoords(const MovementInfoPtr& moveInfo)
{
    return !(std::abs(moveInfo->GetTransportPos()->x) > 100 || std::abs(moveInfo->GetTransportPos()->y) > 100 || std::abs(moveInfo->GetTransportPos()->z) > 100);
}

bool AntiCheat::verifyTransportCoords()
{
    return verifyTransportCoords(newmoveInfo) || verifyTransportCoords(oldmoveInfo);
}

float AntiCheat::GetDistOrTransportDist()
{
    return GetDistOrTransportDist(isFlying());
}

float AntiCheat::GetDistOrTransportDist(bool threed)
{
    return isTransport(newmoveInfo) && isTransport(oldmoveInfo) ? GetTransportDist(threed) : GetDistance(threed);
}

float AntiCheat::GetDistanceZ()
{
    return newmoveInfo->GetPos()->z - oldmoveInfo->GetPos()->z;
}

float AntiCheat::GetDistance()
{
    return GetDistance(isFlying());
}

float AntiCheat::GetSpeedDistance()
{
    return isTransport(newmoveInfo) && isTransport(oldmoveInfo) ?
        GetTransportDist(isFlying() || isSwimming()) :
        GetDistance(isFlying() || isSwimming());
}

float AntiCheat::GetDistance(bool threed)
{
    return threed ? GetDistance3D() : GetDistance2D();
}

float AntiCheat::GetDistance2D()
{
    return
        sqrt(pow(newmoveInfo->GetPos()->x - oldmoveInfo->GetPos()->x, 2) +
            pow(newmoveInfo->GetPos()->y - oldmoveInfo->GetPos()->y, 2));
}

float AntiCheat::GetDistance3D()
{
    return
        sqrt(pow(newmoveInfo->GetPos()->x - oldmoveInfo->GetPos()->x, 2) +
            pow(newmoveInfo->GetPos()->y - oldmoveInfo->GetPos()->y, 2) +
            pow(newmoveInfo->GetPos()->z - oldmoveInfo->GetPos()->z, 2));
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
        sqrt(pow(newmoveInfo->GetTransportPos()->x - oldmoveInfo->GetTransportPos()->x, 2) +
            pow(newmoveInfo->GetTransportPos()->y - oldmoveInfo->GetTransportPos()->y, 2));
}

float AntiCheat::GetTransportDist3D()
{
    return
        sqrt(pow(newmoveInfo->GetTransportPos()->x - oldmoveInfo->GetTransportPos()->x, 2) +
            pow(newmoveInfo->GetTransportPos()->y - oldmoveInfo->GetTransportPos()->y, 2) +
            pow(newmoveInfo->GetTransportPos()->z - oldmoveInfo->GetTransportPos()->z, 2));
}

float AntiCheat::GetTransportDistZ()
{
    return newmoveInfo->GetTransportPos()->z - oldmoveInfo->GetTransportPos()->z;
}

float AntiCheat::GetServerSpeed(bool includeold)
{
    bool back = newmoveInfo->HasMovementFlag(MOVEFLAG_BACKWARD);
    float speed = AllowedSpeed[back ? MOVE_RUN_BACK : MOVE_RUN];

    if (isFlying(newmoveInfo))
        speed = AllowedSpeed[back ? MOVE_FLIGHT_BACK : MOVE_FLIGHT];
    else if (isSwimming(newmoveInfo))
        speed = AllowedSpeed[back ? MOVE_SWIM_BACK : MOVE_SWIM];
    else if (isWalking(newmoveInfo))
        speed = AllowedSpeed[MOVE_WALK];

    return includeold ? std::max(OldServerSpeed, speed) : speed;
}

float AntiCheat::GetAllowedSpeed()
{
    float allowedspeed = GetServerSpeed();
    allowedspeed = IsKnockedback() ? std::max(allowedspeed, GetKnockBackSpeed()) : allowedspeed;

    return allowedspeed;
}

float AntiCheat::GetExpectedZ()
{
    if (!m_Falling)
        return newmoveInfo->GetPos()->z;

    return m_StartFallZ - ComputeFallElevation(newmoveInfo->GetFallTime() / 1000.f, m_SlowFall, m_StartVelocity);
}

float AntiCheat::GetAllowedDistance()
{
    return GetDiffInSec() * GetServerSpeed();
}

uint32 AntiCheat::GetDiff()
{
    uint32 t1 = newmoveInfo->GetACTime();
    uint32 t2 = oldmoveInfo->GetACTime();

    return std::max(uint32(1), std::max(t1, t2) - std::min(t1, t2));
}

float AntiCheat::GetDiffInSec()
{
    return GetDiff() / 1000.f;
}

float AntiCheat::GetVirtualDiffInSec()
{
    if (IsMoving(newmoveInfo) && !IsMoving(oldmoveInfo))
        return 1.f;

    return GetDiffInSec();
}

float AntiCheat::ComputeFallElevation(float t_passed, bool isSafeFall, float start_velocity)
{
    double gravity = 19.29110527038574;
    /// Velocity bounds that makes fall speed limited
    float terminalVelocity = isSafeFall ? 7.f : 60.148003f;

    float terminal_length = float(terminalVelocity * terminalVelocity) / (2.f* gravity);
    float terminalFallTime = float(terminalVelocity / gravity); // the time that needed to reach terminalVelocity

    float result = 0.f;

    if (start_velocity > terminalVelocity)
        start_velocity = terminalVelocity;

    float terminal_time = terminalFallTime - start_velocity / gravity; // the time that needed to reach terminalVelocity

    if (t_passed > terminal_time)
    {
        result = terminalVelocity * (t_passed - terminal_time) +
            start_velocity * terminal_time + gravity * terminal_time * terminal_time * 0.5f;
    }
    else
        result = t_passed * (start_velocity + t_passed * gravity * 0.5f);

    return result;
}

void AntiCheat::UpdateGravityInfo(Opcodes opcode)
{
    float alloweddiff = 0.05f;

    bool startfalling = !isFalling(oldmoveInfo) && isFalling(newmoveInfo);
    bool stopfalling = !isFalling(newmoveInfo) && isFalling(oldmoveInfo);

    if (!m_Falling)
        m_StartFallZ = newmoveInfo->GetPos()->z;

    uint32 falltime = m_Falling ? newmoveInfo->GetFallTime() : 0;

    if (!m_Falling && (startfalling || opcode == MSG_MOVE_JUMP))
    {
        m_Falling = true;
        m_StartVelocity = (opcode == MSG_MOVE_JUMP ? newmoveInfo->GetJumpInfo().velocity : 0.f);
        storedmoveInfo = opcode == MSG_MOVE_JUMP ? newmoveInfo : oldmoveInfo;
        storedMapID = opcode == MSG_MOVE_JUMP ? newMapID : oldMapID;

        // Revisit this again, we wanna keep this enabled.
        //if (opcode == MSG_MOVE_JUMP)
        //    m_Jumping = true;
    }

    bool oldslowfall = m_SlowFall;

    if ((m_Falling || isFalling() || opcode == MSG_MOVE_JUMP) && m_Player->HasAuraType(SPELL_AURA_FEATHER_FALL))
        m_SlowFall = true;

    if (!oldslowfall && m_SlowFall)
        m_InitialDiff = -1.f;

    float expectedfalldist = ComputeFallElevation(falltime / 1000.f, m_SlowFall, m_StartVelocity);
    float expectedz = m_StartFallZ - expectedfalldist;

    float diff = newmoveInfo->GetPos()->z - expectedz;

    if (m_InitialDiff <= 0.f && diff > alloweddiff)
        m_InitialDiff = diff;

    if (!m_Jumping && m_InitialDiff >= 0.f)
        diff -= m_InitialDiff;

    if (stopfalling || opcode == MSG_MOVE_FALL_LAND || opcode == MSG_MOVE_START_SWIM)
    {
        m_Falling = false;
        m_Jumping = false;
        m_SlowFall = false;
        m_InitialDiff = -1.f;
    }
}

void AntiCheat::UpdateSpeedInfo(Opcodes opcode)
{
    switch (opcode)
    {
    case CMSG_FORCE_WALK_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_WALK] = m_Player->GetSpeed(MOVE_WALK);
        break;
    case CMSG_FORCE_RUN_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_RUN] = m_Player->GetSpeed(MOVE_RUN);
        break;
    case CMSG_FORCE_RUN_BACK_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_RUN_BACK] = m_Player->GetSpeed(MOVE_RUN_BACK);
        break;
    case CMSG_FORCE_SWIM_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_SWIM] = m_Player->GetSpeed(MOVE_SWIM);
        break;
    case CMSG_FORCE_SWIM_BACK_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_SWIM_BACK] = m_Player->GetSpeed(MOVE_SWIM_BACK);
        break;
    case CMSG_FORCE_TURN_RATE_CHANGE_ACK:
        AllowedSpeed[MOVE_TURN_RATE] = m_Player->GetSpeed(MOVE_TURN_RATE);
        break;
    case CMSG_FORCE_FLIGHT_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_FLIGHT] = m_Player->GetSpeed(MOVE_FLIGHT);
        break;
    case CMSG_FORCE_FLIGHT_BACK_SPEED_CHANGE_ACK:
        AllowedSpeed[MOVE_FLIGHT_BACK] = m_Player->GetSpeed(MOVE_FLIGHT_BACK);
        break;
    default: break;
    }

    for (uint8 i = 0; i < MAX_MOVE_TYPE; ++i)
        if (m_Player->GetSpeed(UnitMoveType(i)) > AllowedSpeed[UnitMoveType(i)])
            AllowedSpeed[UnitMoveType(i)] = m_Player->GetSpeed(UnitMoveType(i));
}
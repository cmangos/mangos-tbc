#include "AntiCheat.h"
#include "CPlayer.h"

AntiCheat::AntiCheat(Player* player)
{
    m_Player = player;

    for (uint8 i = 0; i < 2; ++i)
        m_MoveInfo[i] = MovementInfo();

    m_Initialized = false;

    player->ToCPlayer()->AddAntiCheatModule(this);
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

bool AntiCheat::isFlying(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FLYING) || moveInfo.HasMovementFlag(MOVEFLAG_FLYING2);
}

bool AntiCheat::isFlying()
{
    return isFlying(m_MoveInfo[0]) || isFlying(m_MoveInfo[1]);
}

bool AntiCheat::isWalking(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_WALK_MODE);
}

bool AntiCheat::isWalking()
{
    return isWalking(m_MoveInfo[0]) || isWalking(m_MoveInfo[1]);
}

bool AntiCheat::isFalling(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_FALLING) || moveInfo.HasMovementFlag(MOVEFLAG_FALLINGFAR) || moveInfo.HasMovementFlag(MOVEFLAG_SAFE_FALL);
}

bool AntiCheat::isFalling()
{
    return isFalling(m_MoveInfo[0]) || isFalling(m_MoveInfo[1]);
}

bool AntiCheat::isTransport(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_ONTRANSPORT);
}

bool AntiCheat::isTransport()
{
    return isTransport(m_MoveInfo[0]) || isTransport(m_MoveInfo[1]);
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
        sqrt(pow(m_MoveInfo[0].GetPos()->x - m_MoveInfo[1].GetPos()->x, 2) +
            pow(m_MoveInfo[0].GetPos()->y - m_MoveInfo[1].GetPos()->y, 2));
}

float AntiCheat::GetDistance3D()
{
    return
        sqrt(pow(m_MoveInfo[0].GetPos()->x - m_MoveInfo[1].GetPos()->x, 2) +
            pow(m_MoveInfo[0].GetPos()->y - m_MoveInfo[1].GetPos()->y, 2) +
            pow(m_MoveInfo[0].GetPos()->z - m_MoveInfo[1].GetPos()->z, 2));
}

float AntiCheat::GetSpeed(MovementInfo& moveInfo)
{
    float speed = 0;

    bool back = moveInfo.HasMovementFlag(MOVEFLAG_BACKWARD);

    if (moveInfo.HasMovementFlag(MOVEFLAG_WALK_MODE))
        speed = m_Player->GetSpeed(MOVE_WALK);
    else if (moveInfo.HasMovementFlag(MOVEFLAG_SWIMMING))
        speed = m_Player->GetSpeed(back ? MOVE_SWIM_BACK : MOVE_SWIM);
    else if (moveInfo.HasMovementFlag(MOVEFLAG_FLYING))
        speed = m_Player->GetSpeed(back ? MOVE_FLIGHT_BACK : MOVE_FLIGHT);
    else
        speed = m_Player->GetSpeed(back ? MOVE_RUN_BACK : MOVE_RUN);

    return speed;
}

float AntiCheat::GetSpeed(bool high)
{
    float speed[2];
    for (uint8 i = 0; i < 2; ++i)
        speed[i] = GetSpeed(m_MoveInfo[i]);

    if (high)
        return speed[0] > speed[1] ? speed[0] : speed[1];

    return speed[0] < speed[1] ? speed[0] : speed[1];
}

float AntiCheat::GetAllowedDistance(bool high)
{
    return GetDiffInSec() * GetSpeed(high);
}

uint32 AntiCheat::GetDiff()
{
    auto t1 = m_MoveInfo[0].GetTime();
    auto t2 = m_MoveInfo[1].GetTime();

    uint32 diff = t1 > t2 ? t1 - t2 : t2 - t1;

    return diff;
}

float AntiCheat::GetDiffInSec()
{
    float diff = GetDiff();
    return diff / 1000.f;
}

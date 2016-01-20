#include "AntiCheat.h"

AntiCheat::AntiCheat(Player* player)
{
    m_Player = player;
    m_MoveInfo = MovementInfo();
    m_Initialized = false;
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

bool AntiCheat::isFlying(MovementInfo& moveInfo1, MovementInfo& moveInfo2)
{
    return isFlying(moveInfo1) || isFlying(moveInfo2);
}

bool AntiCheat::isWalking(MovementInfo& moveInfo)
{
    return moveInfo.HasMovementFlag(MOVEFLAG_WALK_MODE);
}

bool AntiCheat::isWalking(MovementInfo& moveInfo1, MovementInfo& moveInfo2)
{
    return isWalking(moveInfo1) || isWalking(moveInfo2);
}

float AntiCheat::GetDistance(MovementInfo& moveInfo1, MovementInfo& moveInfo2)
{
    return GetDistance(moveInfo1, moveInfo2, isFlying(moveInfo1, moveInfo2));
}

float AntiCheat::GetDistance(MovementInfo& moveInfo1, MovementInfo& moveInfo2, bool threed)
{
    return threed ? GetDistance3D(moveInfo1, moveInfo2) : GetDistance2D(moveInfo1, moveInfo2);
}

float AntiCheat::GetDistance2D(MovementInfo& moveInfo1, MovementInfo& moveInfo2)
{
    return
        sqrt(pow(moveInfo1.GetPos()->x - moveInfo2.GetPos()->x, 2) +
            pow(moveInfo1.GetPos()->y - moveInfo2.GetPos()->y, 2));
}

float AntiCheat::GetDistance3D(MovementInfo& moveInfo1, MovementInfo& moveInfo2)
{
    return
        sqrt(pow(moveInfo1.GetPos()->x - moveInfo2.GetPos()->x, 2) +
            pow(moveInfo1.GetPos()->y - moveInfo2.GetPos()->y, 2) +
            pow(moveInfo1.GetPos()->z - moveInfo2.GetPos()->z, 2));
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

float AntiCheat::GetSpeed(MovementInfo& moveInfo1, MovementInfo& moveInfo2, bool high)
{
    float speed1 = GetSpeed(moveInfo1);
    float speed2 = GetSpeed(moveInfo2);

    if (high)
        return speed1 > speed2 ? speed1 : speed2;

    return speed1 < speed2 ? speed1 : speed2;
}
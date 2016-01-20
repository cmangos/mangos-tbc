#pragma once

class AntiCheat
{
public:
    AntiCheat(Player* player);

    virtual bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode) = 0;

protected:
    bool Initialized();

    bool isFlying(MovementInfo& moveInfo);
    bool isFlying(MovementInfo& moveInfo1, MovementInfo& moveInfo2);
    bool AntiCheat::isWalking(MovementInfo& moveInfo);
    bool isWalking(MovementInfo& moveInfo1, MovementInfo& moveInfo2);
    float GetDistance(MovementInfo& moveInfo1, MovementInfo& moveInfo2);
    float GetDistance(MovementInfo& moveInfo1, MovementInfo& moveInfo2, bool threed);
    float GetDistance2D(MovementInfo& moveInfo1, MovementInfo& moveInfo2);
    float GetDistance3D(MovementInfo& moveInfo1, MovementInfo& moveInfo2);

    float GetSpeed(MovementInfo& moveInfo);
    float GetSpeed(MovementInfo& moveInfo1, MovementInfo& moveInfo2, bool high = false);

    Player* m_Player;
    MovementInfo m_MoveInfo;

private:
    bool m_Initialized;
};

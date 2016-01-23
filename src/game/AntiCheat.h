#pragma once

class AntiCheat
{
public:
    AntiCheat(Player* player);
    ~AntiCheat() {}

    virtual bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode) = 0;
    virtual void HandleUpdate(uint32 update_diff, uint32 p_time) { };

protected:
    bool Initialized();

    bool isFlying(MovementInfo& moveInfo);
    bool isFlying();
    bool isWalking(MovementInfo& moveInfo);
    bool isWalking();
    bool isFalling(MovementInfo& moveInfo);
    bool isFalling();
    float GetDistance();
    float GetDistance(bool threed);
    float GetDistance2D();
    float GetDistance3D();

    float GetSpeed(MovementInfo& moveInfo);
    float GetSpeed(bool high = true);
    float GetAllowedDistance(bool high = true);

    uint32 GetDiff();
    float GetDiffInSec();

    Player* m_Player;
    MovementInfo m_MoveInfo[2];

private:
    bool m_Initialized;
};

#pragma once

class AntiCheat
{
public:
    AntiCheat(Player* player);
    ~AntiCheat() {}

    virtual bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode) = 0;
    virtual void HandleUpdate(uint32 update_diff, uint32 p_time) { };
    virtual void HandleTeleport() { };

protected:
    bool Initialized();

    bool isFlying(MovementInfo& moveInfo);
    bool isFlying();
    bool isWalking(MovementInfo& moveInfo);
    bool isWalking();
    bool isFalling(MovementInfo& moveInfo);
    bool isFalling();
    bool isTransport(MovementInfo& moveInfo);
    bool isTransport();
    bool isSwimming(MovementInfo& moveInfo);
    bool isSwimming();
    float GetDistance();
    float GetDistance(bool threed);
    float GetDistanceZ();
    float GetDistance2D();
    float GetDistance3D();
    float GetTransportDist(bool threed);
    float GetTransportDist2D();
    float GetTransportDist3D();

    float GetSpeed(MovementInfo& moveInfo);
    float GetSpeed(bool high = true);
    float GetAllowedDistance(bool high = true);

    uint32 GetDiff();
    float GetDiffInSec();

    Player* m_Player;
    MovementInfo m_MoveInfo[2];
    bool m_Initialized;

private:
    
};

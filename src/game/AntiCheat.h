#pragma once

#define JUMPHEIGHT_LAND 1.65f
#define JUMPHEIGHT_WATER 2.15f
#define WALKABLE_CLIMB 1.f // https://goo.gl/oxvse6

class AntiCheat
{
public:
    AntiCheat(CPlayer* player);
    ~AntiCheat() {}

    virtual bool HandleMovement(MovementInfo& moveInfo, Opcodes opcode) = 0;
    virtual void HandleUpdate(uint32 update_diff, uint32 p_time) { };
    virtual void HandleTeleport(float x, float y, float z) { };
    virtual void HandleFlightpathFinish() { };

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
    float GetDistOrTransportDist();
    float GetDistOrTransportDist(bool threed);
    float GetDistanceZ();
    float GetDistance();
    float GetDistance(bool threed);
    float GetDistance2D();
    float GetDistance3D();
    float GetTransportDist();
    float GetTransportDist(bool threed);
    float GetTransportDist2D();
    float GetTransportDist3D();
    float GetTransportDistZ();

    float GetSpeed(MovementInfo& moveInfo);
    float GetSpeed(bool high = true);
    float GetAllowedDistance(bool high = true);

    uint32 GetDiff();
    float GetDiffInSec();

    CPlayer* m_Player;
    MovementInfo m_MoveInfo[2];
    bool m_Initialized;

private:
};

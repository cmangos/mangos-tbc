#pragma once

#include "Server/Opcodes.h"
#include "Entities/Unit.h"

#define JUMPHEIGHT_LAND 1.65f
#define JUMPHEIGHT_WATER 2.15f
#define WALKABLE_CLIMB 1.f // https://goo.gl/oxvse6

class CPlayer;

class AntiCheat
{
public:
    AntiCheat(CPlayer* player);
    virtual ~AntiCheat() {}

    virtual bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, bool cheat);
    virtual void HandleUpdate(uint32 update_diff, uint32 p_time) { };
    virtual void HandleRelocate(float x, float y, float z, float o);
    virtual void HandleTeleport(uint32 map, float x, float y, float z, float o);
    virtual void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed) { };

protected:
    bool Initialized();
    bool SetOldMoveInfo(bool value);
    bool SetStoredMoveInfo(bool value);

    bool CanFly() { return m_CanFly; }
    bool CanWaterwalk() { return m_CanWaterwalk; }
    bool IsMoving(const MovementInfoPtr& moveInfo);
    bool IsMoving();
    bool isFlying(const MovementInfoPtr& moveInfo);
    bool isFlying();
    bool isWalking(const MovementInfoPtr& moveInfo);
    bool isWalking();
    bool isFalling(const MovementInfoPtr& moveInfo);
    bool isFalling();
    bool isTransport(const MovementInfoPtr& moveInfo);
    bool isTransport();
    bool isSwimming(const MovementInfoPtr& moveInfo);
    bool isSwimming();
    bool verifyTransportCoords(const MovementInfoPtr& moveInfo);
    bool verifyTransportCoords();
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

    float GetServerSpeed(bool includeold = true);
    float GetAllowedDistance();

    uint32 GetDiff();
    float GetDiffInSec();
    float GetVirtualDiffInSec();

protected:
    CPlayer* m_Player;
    MovementInfoPtr newmoveInfo;
    MovementInfoPtr oldmoveInfo;
    MovementInfoPtr storedmoveInfo;
    uint32 newMapID;
    uint32 oldMapID;
    uint32 storedMapID;
    bool m_Initialized;

private:
    bool m_CanFly;
    bool m_CanWaterwalk;

    float AllowedSpeed[MAX_MOVE_TYPE];
    float OldServerSpeed;
};

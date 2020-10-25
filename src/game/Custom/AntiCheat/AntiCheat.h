#pragma once

#include "Entities/Unit.h"
#include "Server/Opcodes.h"

#include <type_traits>
#include <bitset>

#define JUMPHEIGHT_LAND 1.65f
#define JUMPHEIGHT_WATER 2.15f
#define WALKABLE_CLIMB 1.f // https://goo.gl/oxvse6

enum AntiCheatFieldOffsets : std::size_t {
  CHEAT_NONE,
  CHEAT_FLY,
  CHEAT_GRAVITY,
  CHEAT_JUMP,
  CHEAT_NOFALL,
  CHEAT_SPEED,
  CHEAT_TELEPORT,
  CHEAT_TIME,
  CHEAT_TPTOPLANE,
  CHEAT_WALLCLIMB,
  CHEAT_WALLJUMP,
  CHEAT_WATERWALK,
  CHEAT_TEST,
  CHEAT_MAX,
};

class CPlayer;

typedef std::bitset<AntiCheatFieldOffsets::CHEAT_MAX> AntiCheatFields;

class AntiCheat
{
public:
    AntiCheat(CPlayer* player);
    virtual ~AntiCheat() {}

    virtual bool HandleMovement(const MovementInfoPtr& MoveInfo, Opcodes opcode, AntiCheatFields& triggeredcheats);
    virtual void HandleUpdate(uint32 /*update_diff*/) { }
    virtual void HandleRelocate(float x, float y, float z, float o);
    virtual void HandleTeleport(uint32 map, float x, float y, float z, float o);
    virtual void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);

protected:
    bool Initialized();
    bool SetOldMoveInfo(bool cheat = false);
    bool SetStoredMoveInfo(bool cheat = false);

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
    bool isFallingMoveInfo();
    bool isJumping();
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
    float GetSpeedDistance();
    float GetDistance(bool threed);
    float GetDistance2D();
    float GetDistance3D();
    float GetTransportDist();
    float GetTransportDist(bool threed);
    float GetTransportDist2D();
    float GetTransportDist3D();
    float GetTransportDistZ();

    float GetAllowedSpeed();
    float GetServerSpeed(bool includeold = true);
    float GetAllowedDistance();
    float GetExpectedZ();
    float GetExpectedZ(uint32 falltime);

    uint32 GetDiff();
    float GetDiffInSec();
    float GetVirtualDiffInSec();

    float ComputeFallElevation(float t_passed, bool isSafeFall, float start_velocity);

    void UpdateGravityInfo(Opcodes opcode);
    void UpdateSpeedInfo(Opcodes opcode);

    bool IsKnockedback() { return m_Knockback; }
    float GetKnockBackSpeed() { return m_KnockbackSpeed; }
    float GetFallDistance() { return m_StartFallZ - newmoveInfo->GetPos()->z; }

protected:
    CPlayer* m_Player;
    MovementInfoPtr newmoveInfo;
    MovementInfoPtr oldmoveInfo;
    MovementInfoPtr storedmoveInfo;
    uint32 newMapID;
    uint32 oldMapID;
    uint32 storedMapID;
    bool m_Initialized;
    AntiCheatFieldOffsets antiCheatFieldOffset = AntiCheatFieldOffsets::CHEAT_NONE;

  private:
    bool m_CanFly;
    bool m_CanWaterwalk;

    std::array<float, MAX_MOVE_TYPE> AllowedSpeed;
    float OldServerSpeed;

    float m_StartFallZ;
    float m_StartVelocity;
    float m_InitialFallDiff;
    bool m_Falling;
    bool m_Jumping;
    bool m_SlowFall;

    bool m_Knockback;
    float m_KnockbackSpeed;
};

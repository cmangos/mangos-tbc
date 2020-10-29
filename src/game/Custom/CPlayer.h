#pragma once

#include "Entities/Player.h"

#include <sstream>

class AntiCheat;
struct Position;
enum MessageType : uint8;

typedef std::map<ObjectGuid, float> DMGHEALMap;
typedef std::vector<std::string> RewardMap;

class CPlayer : public Player
{
public:
    typedef std::unique_ptr<AntiCheat> AntiCheatPtr;
    typedef std::vector<AntiCheatPtr> AntiCheatStorage;

public:
    explicit CPlayer(WorldSession* session);
    ~CPlayer();

public:
    Player* ToPlayer() { return static_cast<Player*>(this); }

    // PvP Kill reward system
public:
    void HandlePvPKill();
    void AddDamage(ObjectGuid guid, uint32 amount);
    void AddHealing(ObjectGuid guid, uint32 amount);
    DMGHEALMap& GetDamagers() { return m_Damagers; }
    DMGHEALMap& GetHealers() { return m_Healers; }
    void AddReward(std::string name, float amount);
    std::string GetRewardNames(bool duplicates = true);
    static std::string GetGoldString(uint32 copper);
private:
    DMGHEALMap m_Damagers;
    DMGHEALMap m_Healers;
    RewardMap m_rewards;
    float m_PendingReward;

    // AntiCheat
public:
    bool HandleAntiCheat(const MovementInfoPtr& moveInfo, Opcodes opcode);
    void HandleKnockBack(float angle, float horizontalSpeed, float verticalSpeed);
    void HandleRelocate(float x, float y, float z, float o);
    void HandleTeleport(uint32 map, float x, float y, float z, float o);
    void SetGMFly(bool value) { m_GMFly = value; }
    bool GetGMFly() { return m_GMFly; }

private:
    AntiCheatStorage antiCheatStorage;
    bool m_GMFly;

    // Chat messages
public:
    void SendStreamMessages(MessageType type, std::stringstream &ss);

    std::stringstream BoxChat;
    std::stringstream WideChat;
    std::stringstream BothChat;

    // Virtualised Player functions
public:
    void Update(uint32 update_diff) override;

    // Misc
public:
    bool AddAura(uint32 spellid);
    bool TeleportToPos(uint32 mapid, const Position* pos, uint32 options = 0, AreaTrigger const* at = nullptr);
    void AutoLearnSpells();
    void OnLogin();
    std::string GetNameLink(bool applycolors = false);

    // CFBG
public:
    Team GetTeam() const
    {
        if (GetBattleGround() && GetBattleGround()->IsBattleGround())
            return m_bgData.bgTeam ? m_bgData.bgTeam : GetOTeam();

        return GetOTeam();
    }

    bool NativeTeam() const { return GetTeam() == GetOTeam(); }
    uint8 getFRace() const { return m_fRace; }
    uint8 getORace() const { return m_oRace; }
    uint32 getOFaction() const { return m_oFaction; }
    uint32 getFFaction() const { return m_fFaction; }

    void CFJoinBattleGround();

    void CFLeaveBattleGround();

    void FakeDisplayID();
    void ReplaceRacials(bool native);

    void SetFakeValues();

private:
    uint8 m_fRace;
    uint8 m_oRace;
    uint32 m_fFaction;
    uint32 m_oFaction;
};

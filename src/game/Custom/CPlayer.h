#pragma once

#include "Entities/Player.h"

#include <sstream>

// Move those please.
static const std::string MSG_COLOR_LIGHTRED = "|cffff6060";
static const std::string MSG_COLOR_LIGHTBLUE = "|cff00ccff";
static const std::string MSG_COLOR_ANN_GREEN = "|c1f40af20";
static const std::string MSG_COLOR_RED = "|cffff0000";
static const std::string MSG_COLOR_GOLD = "|cffffcc00";
static const std::string MSG_COLOR_SUBWHITE = "|cffbbbbbb";
static const std::string MSG_COLOR_MAGENTA = "|cffff00ff";
static const std::string MSG_COLOR_YELLOW = "|cffffff00";
static const std::string MSG_COLOR_CYAN = "|cff00ffff";
static const std::string MSG_COLOR_DARKBLUE = "|cff0000ff";

static const std::string MSG_COLOR_GREY = "|cff9d9d9d";
static const std::string MSG_COLOR_WHITE = "|cffffffff";
static const std::string MSG_COLOR_GREEN = "|cff1eff00";
static const std::string MSG_COLOR_BLUE = "|cff0080ff";
static const std::string MSG_COLOR_PURPLE = "|cffb048f8";
static const std::string MSG_COLOR_ORANGE = "|cffff8000";

static const std::string MSG_COLOR_DRUID = "|cffff7d0a";
static const std::string MSG_COLOR_HUNTER = "|cffabd473";
static const std::string MSG_COLOR_MAGE = "|cff69ccf0";
static const std::string MSG_COLOR_PALADIN = "|cfff58cba";
static const std::string MSG_COLOR_PRIEST = "|cffffffff";
static const std::string MSG_COLOR_ROGUE = "|cfffff569";
static const std::string MSG_COLOR_SHAMAN = "|cff0070de";
static const std::string MSG_COLOR_WARLOCK = "|cff9482c9";
static const std::string MSG_COLOR_WARRIOR = "|cffc79c6e";

class AntiCheat;
struct Position;
enum MessageType : uint8;

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

    // CFBG
public:
    Team GetTeam() const
    {
        if (GetBattleGround() && GetBattleGround()->isBattleGround())
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

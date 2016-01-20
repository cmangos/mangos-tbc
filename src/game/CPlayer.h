#pragma once

#include "Player.h"

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

enum MessageTypes
{
    CHAT_BOX = 0x1,
    CHAT_WIDE = 0x2
};

class AntiCheat;

class CPlayer : public Player
{
    // Typedefs
public:
    typedef std::vector<AntiCheat*> AntiCheatStorage;

    // Constructor / destructor
public:
    explicit CPlayer(WorldSession* session);
    ~CPlayer();

    // Cast helper
public:
    Player* ToPlayer() { return static_cast<Player*>(this); }

    // AntiCheat
public:
    void HandleAntiCheat(MovementInfo& moveInfo);
private:
    AntiCheatStorage m_AntiCheatStorage;

    // Chat messages
public:
    void SendSteamMessages(MessageTypes type, std::stringstream &ss);

    std::stringstream BoxChat;
    std::stringstream WideChat;
    std::stringstream BothChat;

    // Hooked Player functions
public:
    void CUpdate(uint32 update_diff, uint32 p_time);

};

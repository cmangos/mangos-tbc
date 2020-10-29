#pragma once

class Custom_Constants
{
private:
    Custom_Constants() {}
public:
    static const std::string* GetClassColor(uint8 classid) { return &classColors[classid]; }

    static const std::string MSG_COLOR_LIGHTRED;
    static const std::string MSG_COLOR_LIGHTBLUE;
    static const std::string MSG_COLOR_ANN_GREEN;
    static const std::string MSG_COLOR_RED;
    static const std::string MSG_COLOR_GOLD;
    static const std::string MSG_COLOR_SUBWHITE;
    static const std::string MSG_COLOR_MAGENTA;
    static const std::string MSG_COLOR_YELLOW;
    static const std::string MSG_COLOR_CYAN;
    static const std::string MSG_COLOR_DARKBLUE;

    static const std::string MSG_COLOR_GREY;
    static const std::string MSG_COLOR_WHITE;
    static const std::string MSG_COLOR_GREEN;
    static const std::string MSG_COLOR_BLUE;
    static const std::string MSG_COLOR_PURPLE;
    static const std::string MSG_COLOR_ORANGE;

    static const std::string MSG_COLOR_DRUID;
    static const std::string MSG_COLOR_HUNTER;
    static const std::string MSG_COLOR_MAGE;
    static const std::string MSG_COLOR_PALADIN;
    static const std::string MSG_COLOR_PRIEST;
    static const std::string MSG_COLOR_ROGUE;
    static const std::string MSG_COLOR_SHAMAN;
    static const std::string MSG_COLOR_WARLOCK;
    static const std::string MSG_COLOR_WARRIOR;

    static const std::string classColors[];
};

enum class PvPRewardType : uint32
{
    NONE,
    GOLD,
    HONOR,
    ARENAPOINTS,
};
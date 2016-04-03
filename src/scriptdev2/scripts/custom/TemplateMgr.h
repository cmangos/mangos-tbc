#ifndef _TEMPLATE_MGR
#define _TEMPLATE_MGR

#include "precompiled.h"

enum TemplateItemEntry {
};

enum TemplateSpellEntry {
    // Warrior
    DEFAULT_WARRIOR = 1,
    PVP_WARRIOR_ARMS_SWEEPING_STRIKES,
    PVP_WARRIOR_ARMS_ENDLESS_RAGE,
    PVP_WARRIOR_ARMS_FLURRY,

    // Paladin
    DEFAULT_PALADIN,
    PVP_PALADIN_HOLY,
    PVP_PALADIN_RETRIBUTION,

    // Hunter
    DEFAULT_HUNTER,
    PVP_HUNTER_MARKSMANSHIP,
    PVP_HUNTER_BEAST_MASTERY,
    PVP_HUNTER_SURVIVAL,

    // Rogue
    DEFAULT_ROGUE,
    PVP_ROGUE_MUTILATE,
    PVP_ROGUE_COMBAT_FULL,
    PVP_ROGUE_COMBAT_WITH_HEMORRHAGE,
    PVP_ROGUE_SHADOWSTEP,

    // Priest
    DEFAULT_PRIEST,
    PVP_PRIEST_DISCIPLINE_DEFENSIVE,
    PVP_PRIEST_DISCIPLINE_OFFENSIVE,
    PVP_PRIEST_SHADOW,

    // Shaman
    DEFAULT_SHAMAN,
    PVP_SHAMAN_ELEMENTAL,
    PVP_SHAMAN_ENHANCEMENT,
    PVP_SHAMAN_RESTORATION_MANA_TIDE_TOTEM,
    PVP_SHAMAN_RESTORATION_IMP_HEALING_WAVE,

    // Mage
    DEFAULT_MAGE,
    PVP_MAGE_FROST,
    PVP_MAGE_FIRE_IMP_COUNTERSPELL,
    PVP_MAGE_FIRE_ICY_VEINS,

    // Warlock
    DEFAULT_WARLOCK,
    PVP_WARLOCK_AFFLICTION,
    PVP_WARLOCK_SIPHON_LIFE_SOUL_LINK,
    PVP_WARLOCK_DESTRUCTION,

    // Druid
    DEFAULT_DRUID,
    PVP_DRUID_BALANCE_NATURES_SWIFTNESS,
    PVP_DRUID_BALANCE_TREANTS,
    PVP_DRUID_FERAL_COMBAT,
    PVP_DRUID_RESTORATION_FULL,
    PVP_DRUID_RESTORATION_DREAMSTATE
};

enum TemplateReputationEntry {
};

struct TemplateItem
{
    uint32 itemEntry;
    uint32 itemAmount;
    uint32 enchantEntry;
    uint32 gemEnchantEntry[MAX_GEM_SOCKETS];
};

struct TemplateReputation
{
    uint32 factionEntry;
    uint32 factionStanding;
};

typedef std::unordered_map<uint32, std::vector<TemplateItem>> TemplateItems;
typedef std::unordered_map<uint32, std::vector<uint32> /*spellEntry*/> TemplateSpells;
typedef std::unordered_map<uint32, std::vector<TemplateReputation>> TemplateReputations;

class TemplateMgr
{
public:
    TemplateMgr()
    {
        LoadItems();
        LoadSpells();
        LoadReputations();
    }

    void AddItems(Player* player, TemplateItemEntry te);
    void AddSpells(Player* player, TemplateSpellEntry te);
    void AddReputations(Player* player, TemplateReputationEntry te);

private:
    void LoadItems();
    void LoadSpells();
    void LoadReputations();

    TemplateItems templateItems;
    TemplateSpells templateSpells;
    TemplateReputations templateReputations;
};

#define sTemplateMgr MaNGOS::Singleton<TemplateMgr>::Instance()

#endif

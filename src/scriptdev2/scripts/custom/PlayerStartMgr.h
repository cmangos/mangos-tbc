#ifndef _NPC_WELCOME_STOCKAGE_HEADER
#define _NPC_WELCOME_STOCKAGE_HEADER

#include "Mail.h"
//#include "Nostalrius.h"
#include "precompiled.h"
#include "ProgressBar.h"
#include "Policies/Singleton.h"
#include "Database/DatabaseEnv.h"

#define BAG_ADD_ID 21876

#define MOUNT_SPELL 33392
#define SPELL_SLEEP 9159
#define SPELL_ELECVISUAL 28136

struct PlayerStartSpell
{
    uint32 spellId;
    uint32 playerClass;
    uint32 playerRace;
    uint32 reqLevel;
};

struct PlayerStartEquip
{
    uint32 entry;
    uint8 playerClass;
    uint32 itemId;
    uint32 itemAmount;
    uint8 equipmentSlot;
};

class PlayerStartMgr
{
    public:
        PlayerStartMgr();
        ~PlayerStartMgr();

        void load();

        std::map<uint32,PlayerStartSpell*> const& GetSpells() { return spells;}
        std::map<uint32, PlayerStartEquip*> const& GetEquipment() const { return equip; }

        void AddItems(Player* player);
        void AddSpells(Player* player);

    private:
        std::map<uint32,PlayerStartSpell*> spells;
        std::map<uint32,PlayerStartEquip*> equip; 
};

#define sPlayerStartMgr MaNGOS::Singleton<PlayerStartMgr>::Instance()

#endif

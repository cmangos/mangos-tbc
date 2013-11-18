/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
 * Copyright (C) 2010 - 2013 Eluna Lua Engine <http://emudevs.com/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "ScriptMgr.h"

#ifndef LUAHOOKS_H
#define LUAHOOKS_H

// void Eluna_AddScriptHooks();

class HookScript;
class HookMgr
{
public:
    typedef std::set<HookScript*> HookPointerSet;
    HookPointerSet hookPointers;

    HookMgr() { }

    // misc
    /*void OnLootItem(Player* player, Item* item, uint32 count, uint64 guid);
    void OnFirstLogin(Player* player);
    void OnEquip(Player* player, Item* item, uint8 bag, uint8 slot);
    void OnRepop(Player* player);
    void OnResurrect(Player* player);
    InventoryResult OnCanUseItem(const Player* player, uint32 itemEntry);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel);
    // item
    bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, Item* target);
    bool OnQuestAccept(Player* player, Item* item, Quest const* quest);
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets);
    bool OnExpire(Player* player, ItemPrototype const* proto);*/
    void OnEngineRestart();
    void HandleGossipSelectOption(Player* player, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId);
    // creature
    bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, Creature* target);
    bool OnGossipHello(Player* player, Creature* creature);
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt);
    uint32 GetDialogStatus(Player* player, Creature* creature);
    // gameobject
    /*bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, GameObject* target);
    bool OnGossipHello(Player* player, GameObject* go);
    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest);
    bool OnQuestReward(Player* player, GameObject* go, Quest const* quest, uint32 opt);
    uint32 GetDialogStatus(Player* player, GameObject* go);
    void OnDestroyed(GameObject* go, Player* player);
    void OnDamaged(GameObject* go, Player* player);
    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit);
    void OnGameObjectStateChanged(GameObject* go, uint32 state);
    // areatrigger
    bool OnTrigger(Player* player, AreaTriggerEntry const* trigger);
    // weather
    void OnChange(Weather* weather, WeatherState state, float grade);
    // condition
    //bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo);
    // transport
    void OnAddPassenger(Transport* transport, Player* player);
    void OnAddCreaturePassenger(Transport* transport, Creature* creature);
    void OnRemovePassenger(Transport* transport, Player* player);
    void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z);*/
};
#define sHookMgr MaNGOS::Singleton<HookMgr>::Instance()

class HookScript
{
public:
    HookScript()
    {
        sHookMgr.hookPointers.insert(this);
    }
    ~HookScript()
    {
        sHookMgr.hookPointers.erase(this);
    }
    // misc
    /*virtual void OnLootItem(Player* player, Item* item, uint32 count, uint64 guid) { }
    virtual void OnFirstLogin(Player* player) { }
    virtual void OnEquip(Player* player, Item* item, uint8 bag, uint8 slot) { }
    virtual void OnRepop(Player* player) { }
    virtual void OnResurrect(Player* player) { }
    virtual InventoryResult OnCanUseItem(Player* player, uint32 itemEntry) { return EQUIP_ERR_OK; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel) { return true; }
    // item
    virtual bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, Item* target) { return false; }
    virtual bool OnQuestAccept(Player* player, Item* item, Quest const* quest) { return false; }
    virtual bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) { return false; }
    virtual bool OnExpire(Player* player, ItemPrototype const* proto) { return false; }*/
    virtual void OnEngineRestart() { }
    virtual void HandleGossipSelectOption(Player* player, uint64 guid, uint32 sender, uint32 action, std::string code, uint32 menuId) { }
    // creature
    virtual bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, Creature* target) { return false; }
    virtual bool OnGossipHello(Player* player, Creature* creature) { return false; }
    virtual bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) { return false; }
    virtual bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) { return false; }
    virtual bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestReward(Player* player, Creature* creature, Quest const* quest, uint32 opt) { return false; }
    virtual uint32 GetDialogStatus(Player* player, Creature* creature) { return 100; }
    // gameobject
    /*virtual bool OnDummyEffect(Unit* caster, uint32 spellId, SpellEffectIndex effIndex, GameObject* target) { return false; }
    virtual bool OnGossipHello(Player* player, GameObject* go) { return false; }
    virtual bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) { return false; }
    virtual bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code) { return false; }
    virtual bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest) { return false; }
    virtual bool OnQuestReward(Player* player, GameObject* go, Quest const* quest, uint32 opt) { return false; }
    virtual uint32 GetDialogStatus(Player* player, GameObject* go) { return 100; }
    virtual void OnDestroyed(GameObject* go, Player* player) { }
    virtual void OnDamaged(GameObject* go, Player* player) { }
    virtual void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit) { }
    virtual void OnGameObjectStateChanged(GameObject* go, uint32 state) { }
    // areatrigger
    virtual bool OnTrigger(Player* player, AreaTriggerEntry const* trigger) { return false; }
    // weather
    virtual void OnChange(Weather* weather, WeatherState state, float grade) { }
    // condition
    //virtual bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo) { return true; }
    // transport
    virtual void OnAddPassenger(Transport* transport, Player* player) { }
    virtual void OnAddCreaturePassenger(Transport* transport, Creature* creature) { }
    virtual void OnRemovePassenger(Transport* transport, Player* player) { }
    virtual void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z) { }*/
};
#endif

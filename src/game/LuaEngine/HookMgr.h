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
    void OnLootItem(Player* player, Item* item, uint32 count, uint64 guid);
    void OnFirstLogin(Player* player);
    void OnEquip(Player* player, Item* item, uint8 bag, uint8 slot);
    void OnRepop(Player* player);
    void OnResurrect(Player* player);
    InventoryResult OnCanUseItem(const Player* player, uint32 itemEntry);
    // item
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget);
    bool OnQuestAccept(Player* player, Item* item, Quest const* quest);
    bool OnUse(Player* player, Item* item, SpellCastTargets const& targets);
    bool OnExpire(Player* player, ItemPrototype const* proto);
    void OnEngineRestart();
    void HandleGossipSelectOption(Player* player, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId);
    // creature
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget);
    bool OnGossipHello(Player* player, Creature* creature);
    bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest);
    bool OnQuestReward(Player* player, Creature* creature, Quest const* quest);
    uint32 GetDialogStatus(Player* player, Creature* creature);
    // gameobject
    bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget);
    bool OnGossipHello(Player* player, GameObject* go);
    bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action);
    bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code);
    bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest);
    bool OnQuestReward(Player* player, GameObject* go, Quest const* quest);
    bool OnGameObjectUse(Player* pPlayer, GameObject* pGameObject);
    uint32 GetDialogStatus(Player* player, GameObject* go);
    void OnDestroyed(GameObject* go, Player* player);
    void OnDamaged(GameObject* go, Player* player);
    void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit);
    void OnGameObjectStateChanged(GameObject* go, uint32 state);
    // Player
    void OnPlayerEnterCombat(Player* player, Unit* enemy);
    void OnPlayerLeaveCombat(Player* player);
    void OnPVPKill(Player* killer, Player* killed);
    void OnCreatureKill(Player* killer, Creature* killed);
    void OnPlayerKilledByCreature(Creature* killer, Player* killed);
    void OnLevelChanged(Player* player, uint8 oldLevel);
    void OnFreeTalentPointsChanged(Player* player, uint32 newPoints);
    void OnTalentsReset(Player* player, bool noCost);
    void OnMoneyChanged(Player* player, int32& amount);
    void OnGiveXP(Player* player, uint32& amount, Unit* victim);
    void OnReputationChange(Player* player, uint32 factionID, int32& standing, bool incremental);
    void OnDuelRequest(Player* target, Player* challenger);
    void OnDuelStart(Player* player1, Player* player2);
    void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type);
    void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild);
    bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel);
    void OnEmote(Player* player, uint32 emote);
    void OnTextEmote(Player* player, uint32 textEmote, uint32 emoteNum, uint64 guid);
    void OnSpellCast(Player* player, Spell* spell, bool skipCheck);
    void OnLogin(Player* player);
    void OnLogout(Player* player);
    void OnCreate(Player* player);
    void OnDelete(uint32 guid);
    void OnSave(Player* player);
    void OnBindToInstance(Player* player, Difficulty difficulty, uint32 mapid, bool permanent);
    void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea);
    void OnMapChanged(Player* player);
    // areatrigger
    bool OnAreaTrigger(Player* player, AreaTriggerEntry const* trigger);
    // weather
    /*void OnChange(Weather* weather, WeatherState state, float grade);
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
    virtual void OnLootItem(Player* player, Item* item, uint32 count, uint64 guid) { }
    virtual void OnFirstLogin(Player* player) { }
    virtual void OnEquip(Player* player, Item* item, uint8 bag, uint8 slot) { }
    virtual void OnRepop(Player* player) { }
    virtual void OnResurrect(Player* player) { }
    virtual InventoryResult OnCanUseItem(Player* player, uint32 itemEntry) { return EQUIP_ERR_OK; }
    // item*/
    virtual bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget) { return false; }
    virtual bool OnQuestAccept(Player* player, Item* item, Quest const* quest) { return false; }
    virtual bool OnUse(Player* player, Item* item, SpellCastTargets const& targets) { return false; }
    virtual bool OnExpire(Player* player, ItemPrototype const* proto) { return false; }
    virtual void OnEngineRestart() { }
    virtual void HandleGossipSelectOption(Player* player, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId) { }
    // creature
    virtual bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget) { return false; }
    virtual bool OnGossipHello(Player* player, Creature* creature) { return false; }
    virtual bool OnGossipSelect(Player* player, Creature* creature, uint32 sender, uint32 action) { return false; }
    virtual bool OnGossipSelectCode(Player* player, Creature* creature, uint32 sender, uint32 action, const char* code) { return false; }
    virtual bool OnQuestAccept(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestSelect(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestComplete(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual bool OnQuestReward(Player* player, Creature* creature, Quest const* quest) { return false; }
    virtual uint32 GetDialogStatus(Player* player, Creature* creature) { return 100; }
    // gameobject
    virtual bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget) { return false; }
    virtual bool OnGossipHello(Player* player, GameObject* go) { return false; }
    virtual bool OnGossipSelect(Player* player, GameObject* go, uint32 sender, uint32 action) { return false; }
    virtual bool OnGossipSelectCode(Player* player, GameObject* go, uint32 sender, uint32 action, const char* code) { return false; }
    virtual bool OnQuestAccept(Player* player, GameObject* go, Quest const* quest) { return false; }
    virtual bool OnQuestReward(Player* player, GameObject* go, Quest const* quest) { return false; }
    virtual bool OnGameObjectUse(Player* pPlayer, GameObject* pGameObject) { return false; }
    virtual uint32 GetDialogStatus(Player* player, GameObject* go) { return 100; }
    virtual void OnDestroyed(GameObject* go, Player* player) { }
    virtual void OnDamaged(GameObject* go, Player* player) { }
    virtual void OnLootStateChanged(GameObject* go, uint32 state, Unit* unit) { }
    virtual void OnGameObjectStateChanged(GameObject* go, uint32 state) { }
    // Player
    virtual void OnPlayerEnterCombat(Player* player, Unit* enemy) { }
    virtual void OnPlayerLeaveCombat(Player* player) { }
    virtual void OnPVPKill(Player* killer, Player* killed) { }
    virtual void OnCreatureKill(Player* killer, Creature* killed) { }
    virtual void OnPlayerKilledByCreature(Creature* killer, Player* killed) { }
    virtual void OnLevelChanged(Player* player, uint8 oldLevel) { }
    virtual void OnFreeTalentPointsChanged(Player* player, uint32 newPoints) { }
    virtual void OnTalentsReset(Player* player, bool noCost) { }
    virtual void OnMoneyChanged(Player* player, int32& amount) { }
    virtual void OnGiveXP(Player* player, uint32& amount, Unit* victim) { }
    virtual void OnReputationChange(Player* player, uint32 factionID, int32& standing, bool incremental) { }
    virtual void OnDuelRequest(Player* target, Player* challenger) { }
    virtual void OnDuelStart(Player* player1, Player* player2) { }
    virtual void OnDuelEnd(Player* winner, Player* loser, DuelCompleteType type) { }
    virtual void OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Player* receiver) { }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Group* group) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Guild* guild) { return true; }
    virtual bool OnChat(Player* player, uint32 type, uint32 lang, std::string& msg, Channel* channel) { return true; }
    virtual void OnEmote(Player* player, uint32 emote) { }
    virtual void OnTextEmote(Player* player, uint32 textEmote, uint32 emoteNum, uint64 guid) { }
    virtual void OnSpellCast(Player* player, Spell* spell, bool skipCheck) { }
    virtual void OnLogin(Player* player) { }
    virtual void OnLogout(Player* player) { }
    virtual void OnCreate(Player* player) { }
    virtual void OnDelete(uint32 guid) { }
    virtual void OnSave(Player* player) { }
    virtual void OnBindToInstance(Player* player, Difficulty difficulty, uint32 mapid, bool permanent) { }
    virtual void OnUpdateZone(Player* player, uint32 newZone, uint32 newArea) { }
    virtual void OnMapChanged(Player* player) { }
    // areatrigger
    virtual bool OnAreaTrigger(Player* player, AreaTriggerEntry const* trigger) { return false; }
    // weather
    /*virtual void OnChange(Weather* weather, WeatherState state, float grade) { }
    // condition
    //virtual bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo) { return true; }
    // transport
    virtual void OnAddPassenger(Transport* transport, Player* player) { }
    virtual void OnAddCreaturePassenger(Transport* transport, Creature* creature) { }
    virtual void OnRemovePassenger(Transport* transport, Player* player) { }
    virtual void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z) { }*/
};
#endif

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

        /* Misc */
        void OnWorldUpdate(uint32 diff);
        void OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid);
        void OnFirstLogin(Player* pPlayer);
        void OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot);
        void OnRepop(Player* pPlayer);
        void OnResurrect(Player* pPlayer);
        InventoryResult OnCanUseItem(const Player* pPlayer, uint32 itemEntry);
        /* Item */
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget);
        bool OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest);
        bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets);
        bool OnExpire(Player* pPlayer, ItemPrototype const* pProto);
        void OnEngineRestart();
        void HandleGossipSelectOption(Player* pPlayer, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId);
        /* Creature */
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget);
        bool OnGossipHello(Player* pPlayer, Creature* pCreature);
        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action);
        bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code);
        bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
        bool OnQuestSelect(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
        bool OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
        bool OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest);
        uint32 GetDialogStatus(Player* pPlayer, Creature* pCreature);
        /* GameObject */
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget);
        bool OnGossipHello(Player* pPlayer, GameObject* pGameObject);
        bool OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action);
        bool OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code);
        bool OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
        bool OnQuestComplete(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
        bool OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest);
        bool OnGameObjectUse(Player* pPlayer, GameObject* pGameObject);
        uint32 GetDialogStatus(Player* pPlayer, GameObject* pGameObject);
        void OnDestroyed(GameObject* pGameObject, Player* pPlayer);
        void OnDamaged(GameObject* pGameObject, Player* pPlayer);
        void OnLootStateChanged(GameObject* pGameObject, uint32 state, Unit* pUnit);
        void OnGameObjectStateChanged(GameObject* pGameObject, uint32 state);
        /* Player */
        void OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy);
        void OnPlayerLeaveCombat(Player* pPlayer);
        void OnPVPKill(Player* pKiller, Player* pKilled);
        void OnCreatureKill(Player* pKiller, Creature* pKilled);
        void OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled);
        void OnLevelChanged(Player* pPlayer, uint8 oldLevel);
        void OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints);
        void OnTalentsReset(Player* pPlayer, bool noCost);
        void OnMoneyChanged(Player* pPlayer, int32& amount);
        void OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim);
        void OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental);
        void OnDuelRequest(Player* pTarget, Player* pChallenger);
        void OnDuelStart(Player* pStarter, Player* pChallenger);
        void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type);
        void OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver);
        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg);
        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup);
        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild);
        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel);
        void OnEmote(Player* pPlayer, uint32 emote);
        void OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid);
        void OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck);
        void OnLogin(Player* pPlayer);
        void OnLogout(Player* pPlayer);
        void OnCreate(Player* pPlayer);
        void OnDelete(uint32 guid);
        void OnSave(Player* pPlayer);
        void OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent);
        void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea);
        void OnMapChanged(Player* pPlayer);
        /* AreaTrigger */
        bool OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger);
        /* Weather */
        /*void OnChange(Weather* weather, WeatherState state, float grade);
        // condition
        // bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo);
        // transport
        void OnAddPassenger(Transport* transport, Player* player);
        void OnAddCreaturePassenger(Transport* transport, Creature* creature);
        void OnRemovePassenger(Transport* transport, Player* player);
        void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z);*/
        /* Guild */
        void OnAddMember(Guild* guild, Player* player, uint32 plRank);
        void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding/*, bool isKicked*/); // IsKicked not a part of Mangos, implement?
        void OnMOTDChanged(Guild* guild, const std::string& newMotd);
        void OnInfoChanged(Guild* guild, const std::string& newInfo);
        void OnCreate(Guild* guild, Player* leader, const std::string& name);
        void OnDisband(Guild* guild);
        void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount/*, bool isRepair*/);
        void OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount);
        void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId, bool isDestBank, uint8 destContainer, uint8 destSlotId); // TODO: Implement
        void OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank); // TODO: Implement
        void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId);
        /* Group */
        void OnAddMember(Group* group, uint64 guid);
        void OnInviteMember(Group* group, uint64 guid);
        void OnRemoveMember(Group* group, uint64 guid, uint8 method/*, uint64 kicker, const char* reason*/); // Kicker and Reason not a part of Mangos, implement?
        void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid);
        void OnDisband(Group* group);
        void OnCreate(Group* group, uint64 leaderGuid, GroupType groupType);
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
        /* Misc */
        virtual void OnWorldUpdate(uint32 /*diff*/) { }
        virtual void OnLootItem(Player* /*pPlayer*/, Item* /*pItem*/, uint32 /*count*/, uint64 /*guid*/) { }
        virtual void OnFirstLogin(Player* /*pPlayer*/) { }
        virtual void OnEquip(Player* /*pPlayer*/, Item* /*pItem*/, uint8 /*bag*/, uint8 /*slot*/) { }
        virtual void OnRepop(Player* /*pPlayer*/) { }
        virtual void OnResurrect(Player* /*pPlayer*/) { }
        virtual InventoryResult OnCanUseItem(Player* /*pPlayer*/, uint32 /*itemEntry*/) { return EQUIP_ERR_OK; }
        /* Item */
        virtual bool OnDummyEffect(Unit* /*pCaster*/, uint32 /*spellId*/, SpellEffectIndex /*effIndex*/, Item* /*pTarget*/) { return false; }
        virtual bool OnQuestAccept(Player* /*pPlayer*/, Item* /*pItem*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnUse(Player* /*pPlayer*/, Item* /*pItem*/, SpellCastTargets const& /*targets*/) { return false; }
        virtual bool OnExpire(Player* /*pPlayer*/, ItemPrototype const* /*pProto*/) { return false; }
        virtual void OnEngineRestart() { }
        virtual void HandleGossipSelectOption(Player* /*pPlayer*/, Item* /*item*/, uint32 /*sender*/, uint32 /*action*/, std::string /*code*/) { }
        virtual void HandleGossipSelectOption(Player* /*pPlayer*/, uint32 /*sender*/, uint32 /*action*/, std::string /*code*/, uint32 /*menuId*/) { }
        /* Creature */
        virtual bool OnDummyEffect(Unit* /*pCaster*/, uint32 /*spellId*/, SpellEffectIndex /*effIndex*/, Creature* /*pTarget*/) { return false; }
        virtual bool OnGossipHello(Player* /*pPlayer*/, Creature* /*pCreature*/) { return false; }
        virtual bool OnGossipSelect(Player* /*pPlayer*/, Creature* /*pCreature*/, uint32 /*sender*/, uint32 /*action*/) { return false; }
        virtual bool OnGossipSelectCode(Player* /*pPlayer*/, Creature* /*pCreature*/, uint32 /*sender*/, uint32 /*action*/, const char* /*code*/) { return false; }
        virtual bool OnQuestAccept(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnQuestSelect(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnQuestComplete(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnQuestReward(Player* /*pPlayer*/, Creature* /*pCreature*/, Quest const* /*pQuest*/) { return false; }
        virtual uint32 GetDialogStatus(Player* /*pPlayer*/, Creature* /*pCreature*/) { return 100; }
        /* GameObject */
        virtual bool OnDummyEffect(Unit* /*pCaster*/, uint32 /*spellId*/, SpellEffectIndex /*effIndex*/, GameObject* /*pTarget*/) { return false; }
        virtual bool OnGossipHello(Player* /*pPlayer*/, GameObject* /*pGameObject*/) { return false; }
        virtual bool OnGossipSelect(Player* /*pPlayer*/, GameObject* /*pGameObject*/, uint32 /*sender*/, uint32 /*action*/) { return false; }
        virtual bool OnGossipSelectCode(Player* /*pPlayer*/, GameObject* /*pGameObject*/, uint32 /*sender*/, uint32 /*action*/, const char* /*code*/) { return false; }
        virtual bool OnQuestAccept(Player* /*pPlayer*/, GameObject* /*pGameObject*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnQuestComplete(Player* /*pPlayer*/, GameObject* /*pGameObject*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnQuestReward(Player* /*pPlayer*/, GameObject* /*pGameObject*/, Quest const* /*pQuest*/) { return false; }
        virtual bool OnGameObjectUse(Player* /*pPlayer*/, GameObject* /*pGameObject*/) { return false; }
        virtual uint32 GetDialogStatus(Player* /*pPlayer*/, GameObject* /*pGameObject*/) { return 100; }
        virtual void OnDestroyed(GameObject* /*pGameObject*/, Player* /*pPlayer*/) { }
        virtual void OnDamaged(GameObject* /*pGameObject*/, Player* /*pPlayer*/) { }
        virtual void OnLootStateChanged(GameObject* /*pGameObject*/, uint32 /*state*/, Unit* /*pUnit*/) { }
        virtual void OnGameObjectStateChanged(GameObject* /*pGameObject*/, uint32 /*state*/) { }
        /* Player */
        virtual void OnPlayerEnterCombat(Player* /*pPlayer*/, Unit* /*pEnemy*/) { }
        virtual void OnPlayerLeaveCombat(Player* /*pPlayer*/) { }
        virtual void OnPVPKill(Player* /*pKiller*/, Player* /*pKilled*/) { }
        virtual void OnCreatureKill(Player* /*pKiller*/, Creature* /*pKilled*/) { }
        virtual void OnPlayerKilledByCreature(Creature* /*pKiller*/, Player* /*pKilled*/) { }
        virtual void OnLevelChanged(Player* /*pPlayer*/, uint8 /*oldLevel*/) { }
        virtual void OnFreeTalentPointsChanged(Player* /*pPlayer*/, uint32 /*newPoints*/) { }
        virtual void OnTalentsReset(Player* /*pPlayer*/, bool /*noCost*/) { }
        virtual void OnMoneyChanged(Player* /*pPlayer*/, int32& /*amount*/) { }
        virtual void OnGiveXP(Player* /*pPlayer*/, uint32& /*amount*/, Unit* /*pVictim*/) { }
        virtual void OnReputationChange(Player* /*pPlayer*/, uint32 /*factionID*/, int32& /*standing*/, bool /*incremental*/) { }
        virtual void OnDuelRequest(Player* /*pTarget*/, Player* /*pChallenger*/) { }
        virtual void OnDuelStart(Player* /*pStarter*/, Player* /*pChallenger*/) { }
        virtual void OnDuelEnd(Player* /*pWinner*/, Player* /*pLoser*/, DuelCompleteType /*type*/) { }
        virtual void OnChat(Player* /*pPlayer*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Player* /*pReceiver*/) { }
        virtual bool OnChat(Player* /*pPlayer*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/) { return true; }
        virtual bool OnChat(Player* /*pPlayer*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Group* /*pGroup*/) { return true; }
        virtual bool OnChat(Player* /*pPlayer*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Guild* /*pGuild*/) { return true; }
        virtual bool OnChat(Player* /*pPlayer*/, uint32 /*type*/, uint32 /*lang*/, std::string& /*msg*/, Channel* /*pChannel*/) { return true; }
        virtual void OnEmote(Player* /*pPlayer*/, uint32 /*emote*/) { }
        virtual void OnTextEmote(Player* /*pPlayer*/, uint32 /*textEmote*/, uint32 /*emoteNum*/, uint64 /*guid*/) { }
        virtual void OnSpellCast(Player* /*pPlayer*/, Spell* /*pSpell*/, bool /*skipCheck*/) { }
        virtual void OnLogin(Player* /*pPlayer*/) { }
        virtual void OnLogout(Player* /*pPlayer*/) { }
        virtual void OnCreate(Player* /*pPlayer*/) { }
        virtual void OnDelete(uint32 /*guid*/) { }
        virtual void OnSave(Player* /*pPlayer*/) { }
        virtual void OnBindToInstance(Player* /*pPlayer*/, Difficulty /*difficulty*/, uint32 /*mapid*/, bool /*permanent*/) { }
        virtual void OnUpdateZone(Player* /*pPlayer*/, uint32 /*newZone*/, uint32 /*newArea*/) { }
        virtual void OnMapChanged(Player* /*pPlayer*/) { }
        /* AreaTrigger */
        virtual bool OnAreaTrigger(Player* /*pPlayer*/, AreaTriggerEntry const* /*pTrigger*/) { return false; }
        /* Weather */
        // virtual void OnChange(Weather* weather, WeatherState state, float grade) { }
        /* Condition */
        // virtual bool OnConditionCheck(Condition* condition, ConditionSourceInfo& sourceInfo) { return true; }
        /* Transport */
        /*virtual void OnAddPassenger(Transport* transport, Player* player) { }
        virtual void OnAddCreaturePassenger(Transport* transport, Creature* creature) { }
        virtual void OnRemovePassenger(Transport* transport, Player* player) { }
        virtual void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z) { }*/
        /* Guild */
        virtual void OnAddMember(Guild* /*guild*/, Player* /*player*/, uint32 /*plRank*/) { }
        virtual void OnRemoveMember(Guild* /*guild*/, Player* /*player*/, bool /*isDisbanding, bool isKicked*/) { } // IsKicked not a part of Mangos, implement?
        virtual void OnMOTDChanged(Guild* /*guild*/, const std::string& /*newMotd*/) { }
        virtual void OnInfoChanged(Guild* /*guild*/, const std::string& /*newInfo*/) { }
        virtual void OnCreate(Guild* /*guild*/, Player* /*leader*/, const std::string& /*name*/) { }
        virtual void OnDisband(Guild* /*guild*/) { }
        virtual void OnMemberWitdrawMoney(Guild* /*guild*/, Player* /*player*/, uint32 /*&amount, bool isRepair*/) { }
        virtual void OnMemberDepositMoney(Guild* /*guild*/, Player* /*player*/, uint32 /*&amount*/) { }
        virtual void OnItemMove(Guild* /*guild*/, Player* /*player*/, Item* /*pItem*/, bool /*isSrcBank*/, uint8 /*srcContainer*/, uint8 /*srcSlotId*/, bool /*isDestBank*/, uint8 /*destContainer*/, uint8 /*destSlotId*/) { } // TODO: Implement
        virtual void OnEvent(Guild* /*guild*/, uint8 /*eventType*/, uint32 /*playerGuid1*/, uint32 /*playerGuid2*/, uint8 /*newRank*/) { } // TODO: Implement
        virtual void OnBankEvent(Guild* /*guild*/, uint8 /*eventType*/, uint8 /*tabId*/, uint32 /*playerGuid*/, uint32 /*itemOrMoney*/, uint16 /*itemStackCount*/, uint8 /*destTabId*/) { }
        /* Group */
        virtual void OnAddMember(Group* /*group*/, uint64 /*guid*/) { }
        virtual void OnInviteMember(Group* /*group*/, uint64 /*guid*/) { }
        virtual void OnRemoveMember(Group* /*group*/, uint64 /*guid*/, uint8 /*method, uint64 kicker, const char* reason*/) { } // Kicker and Reason not a part of Mangos, implement?
        virtual void OnChangeLeader(Group* /*group*/, uint64 /*newLeaderGuid*/, uint64 /*oldLeaderGuid*/) { }
        virtual void OnDisband(Group* /*group*/) { }
        virtual void OnCreate(Group* /*group*/, uint64 /*leaderGuid*/, GroupType /*groupType*/) { }
};
#endif

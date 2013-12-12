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

#include "HookMgr.h"
#include "LuaEngine.h"

class Eluna_HookScript : public HookScript
{
    public:
        Eluna_HookScript() : HookScript() { }
        // misc
        void OnLootItem(Player* pPlayer, Item* pItem, uint32 count, uint64 guid)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOOT_ITEM].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOOT_ITEM].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_LOOT_ITEM);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pItem);
                sEluna.Push(sEluna.L, count);
                sEluna.Push(sEluna.L, guid);
                sEluna.ExecuteCall(5, 0);
            }
        }

        void OnFirstLogin(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_FIRST_LOGIN].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_FIRST_LOGIN].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_FIRST_LOGIN);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnRepop(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPOP].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPOP].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_REPOP);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnResurrect(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_RESURRECT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_RESURRECT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_RESURRECT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_EQUIP].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_EQUIP].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_EQUIP);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pItem);
                sEluna.Push(sEluna.L, bag);
                sEluna.Push(sEluna.L, slot);
                sEluna.ExecuteCall(5, 0);
            }
        }

        InventoryResult OnCanUseItem(Player* pPlayer, uint32 itemEntry)
        {
            InventoryResult result = EQUIP_ERR_OK;
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CAN_USE_ITEM].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CAN_USE_ITEM].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_CAN_USE_ITEM);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, itemEntry);
                if (sEluna.ExecuteCall(3, 1))
                {
                    lua_State* L = sEluna.L;
                    if (!lua_isnoneornil(L, 1))
                        result = (InventoryResult)lua_tounsigned(L, 1);
                    sEluna.EndCall(1);
                }
            }
            return result;
        }

        void HandleGossipSelectOption(Player* pPlayer, ObjectGuid guid, uint32 sender, uint32 action, std::string code, uint32 menuId)
        {
            if (!pPlayer->isAlive() || pPlayer->GetCharmerGuid())
                return;

            if (pPlayer->hasUnitState(UNIT_STAT_DIED))
                pPlayer->RemoveAurasDueToSpell(SPELL_AURA_FEIGN_DEATH);
            pPlayer->PlayerTalkClass->ClearMenus();

            if (guid.IsItem())
            {
                Item* item = pPlayer->GetItemByGuid(guid);
                if (!item)
                    return;

                int bind = sEluna.ItemGossipBindings->GetBind(item->GetEntry(), GOSSIP_EVENT_ON_SELECT);
                if (bind)
                {
                    sEluna.BeginCall(bind);
                    sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
                    sEluna.Push(sEluna.L, pPlayer);
                    sEluna.Push(sEluna.L, item);
                    sEluna.Push(sEluna.L, sender);
                    sEluna.Push(sEluna.L, action);
                    if (code.empty())
                        lua_pushnil(sEluna.L);
                    else
                        sEluna.Push(sEluna.L, code);
                    sEluna.ExecuteCall(6, 0);
                }
            }
            else if (guid.IsPlayer())
            {
                if (pPlayer->GetGUIDLow() != guid)
                    return;

                int bind = sEluna.playerGossipBindings->GetBind(menuId, GOSSIP_EVENT_ON_SELECT);
                if (bind)
                {
                    sEluna.BeginCall(bind);
                    sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
                    sEluna.Push(sEluna.L, pPlayer); // receiver
                    sEluna.Push(sEluna.L, pPlayer); // sender, just not to mess up the amount of args.
                    sEluna.Push(sEluna.L, sender);
                    sEluna.Push(sEluna.L, action);
                    if (code.empty())
                        lua_pushnil(sEluna.L);
                    else
                        sEluna.Push(sEluna.L, code);
                    sEluna.Push(sEluna.L, menuId);
                    sEluna.ExecuteCall(7, 0);
                }
            }
        }

        void OnEngineRestart()
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[ELUNA_EVENT_ON_RESTART].begin();
                    itr != sEluna.ServerEventBindings[ELUNA_EVENT_ON_RESTART].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, ELUNA_EVENT_ON_RESTART);
                sEluna.ExecuteCall(1, 0);
            }
        }

        // item
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Item* pTarget)
        {
            int bind = sEluna.ItemEventBindings->GetBind(pTarget->GetEntry(), ITEM_EVENT_ON_DUMMY_EFFECT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, ITEM_EVENT_ON_DUMMY_EFFECT);
            sEluna.Push(sEluna.L, pCaster);
            sEluna.Push(sEluna.L, spellId);
            sEluna.Push(sEluna.L, effIndex);
            sEluna.Push(sEluna.L, pTarget);
            sEluna.ExecuteCall(5, 0);
            return true;
        }

        bool OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
        {
            int bind = sEluna.ItemEventBindings->GetBind(pItem->GetEntry(), ITEM_EVENT_ON_QUEST_ACCEPT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, ITEM_EVENT_ON_QUEST_ACCEPT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pItem);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        bool OnUse(Player* pPlayer, Item* pItem, SpellCastTargets const& targets)
        {
            int bind1 = sEluna.ItemGossipBindings->GetBind(pItem->GetEntry(), GOSSIP_EVENT_ON_HELLO);
            int bind2 = sEluna.ItemEventBindings->GetBind(pItem->GetEntry(), ITEM_EVENT_ON_USE);
            if (!bind1 && !bind2)
                return false;
            if (bind1)
            {
                pPlayer->PlayerTalkClass->ClearMenus();
                sEluna.BeginCall(bind1);
                sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_HELLO);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pItem);
                sEluna.ExecuteCall(3, 0);
            }
            if (bind2)
            {
                sEluna.BeginCall(bind2);
                sEluna.Push(sEluna.L, ITEM_EVENT_ON_USE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pItem);
                if (GameObject* target = targets.getGOTarget())
                    sEluna.Push(sEluna.L, target);
                else if (Item* target = targets.getItemTarget())
                    sEluna.Push(sEluna.L, target);
                else if (Unit* target = targets.getUnitTarget())
                    sEluna.Push(sEluna.L, target);
                else
                    lua_pushnil(sEluna.L);
                sEluna.ExecuteCall(4, 0);
            }
            pPlayer->SendEquipError((InventoryResult)83, pItem, NULL);
            return true;
        }

        bool OnExpire(Player* pPlayer, ItemPrototype const* pProto) // TODO: Implement
        {
            int bind = sEluna.ItemEventBindings->GetBind(pProto->ItemId, ITEM_EVENT_ON_EXPIRE);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, ITEM_EVENT_ON_EXPIRE);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pProto->ItemId);
            sEluna.ExecuteCall(3, 0);
            return true;
        }
        // creature
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, Creature* pTarget)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pTarget->GetEntry(), CREATURE_EVENT_ON_DUMMY_EFFECT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_DUMMY_EFFECT);
            sEluna.Push(sEluna.L, pCaster);
            sEluna.Push(sEluna.L, spellId);
            sEluna.Push(sEluna.L, effIndex);
            sEluna.Push(sEluna.L, pTarget);
            sEluna.ExecuteCall(5, 0);
            return true;
        }

        bool OnGossipHello(Player* pPlayer, Creature* pCreature)
        {
            int bind = sEluna.CreatureGossipBindings->GetBind(pCreature->GetEntry(), GOSSIP_EVENT_ON_HELLO);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_HELLO);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.ExecuteCall(3, 0);
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action)
        {
            int bind = sEluna.CreatureGossipBindings->GetBind(pCreature->GetEntry(), GOSSIP_EVENT_ON_SELECT);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, sender);
            sEluna.Push(sEluna.L, action);
            sEluna.ExecuteCall(5, 0);
            return true;
        }

        bool OnGossipSelectCode(Player* pPlayer, Creature* pCreature, uint32 sender, uint32 action, const char* code)
        {
            int bind = sEluna.CreatureGossipBindings->GetBind(pCreature->GetEntry(), GOSSIP_EVENT_ON_SELECT);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, sender);
            sEluna.Push(sEluna.L, action);
            sEluna.Push(sEluna.L, code);
            sEluna.ExecuteCall(6, 0);
            return true;
        }

        bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_ACCEPT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_QUEST_ACCEPT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        bool OnQuestSelect(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_SELECT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_QUEST_SELECT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        bool OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_COMPLETE);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_QUEST_COMPLETE);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        bool OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_REWARD);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_QUEST_REWARD);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        uint32 GetDialogStatus(Player* pPlayer, Creature* pCreature)
        {
            int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_DIALOG_STATUS);
            if (!bind)
                return 0;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, CREATURE_EVENT_ON_DIALOG_STATUS);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pCreature);
            sEluna.ExecuteCall(3, 0);
            return 100;
        }
        // gameobject
        bool OnDummyEffect(Unit* pCaster, uint32 spellId, SpellEffectIndex effIndex, GameObject* pTarget)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pTarget->GetEntry(), GAMEOBJECT_EVENT_ON_DUMMY_EFFECT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_DUMMY_EFFECT);
            sEluna.Push(sEluna.L, pCaster);
            sEluna.Push(sEluna.L, spellId);
            sEluna.Push(sEluna.L, effIndex);
            sEluna.Push(sEluna.L, pTarget);
            sEluna.ExecuteCall(5, 0);
            return true;
        }

        bool OnGossipHello(Player* pPlayer, GameObject* pGameObject)
        {
            int bind = sEluna.GameObjectGossipBindings->GetBind(pGameObject->GetEntry(), GOSSIP_EVENT_ON_HELLO);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_HELLO);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.ExecuteCall(3, 0);
            return true;
        }

        bool OnGossipSelect(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action)
        {
            int bind = sEluna.GameObjectGossipBindings->GetBind(pGameObject->GetEntry(), GOSSIP_EVENT_ON_SELECT);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, sender);
            sEluna.Push(sEluna.L, action);
            sEluna.ExecuteCall(5, 0);
            return true;
        }

        bool OnGossipSelectCode(Player* pPlayer, GameObject* pGameObject, uint32 sender, uint32 action, const char* code)
        {
            int bind = sEluna.GameObjectGossipBindings->GetBind(pGameObject->GetEntry(), GOSSIP_EVENT_ON_SELECT);
            if (!bind)
                return false;
            pPlayer->PlayerTalkClass->ClearMenus();
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GOSSIP_EVENT_ON_SELECT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, sender);
            sEluna.Push(sEluna.L, action);
            sEluna.Push(sEluna.L, code);
            sEluna.ExecuteCall(6, 0);
            return true;
        }

        bool OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_ACCEPT);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_QUEST_ACCEPT);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        bool OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_REWARD);
            if (!bind)
                return false;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_QUEST_REWARD);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, pQuest);
            sEluna.ExecuteCall(4, 0);
            return true;
        }

        uint32 GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DIALOG_STATUS);
            if (!bind)
                return 0;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_DIALOG_STATUS);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.ExecuteCall(3, 0);
            return 100;
        }

        void OnDestroyed(GameObject* pGameObject, Player* pPlayer)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DESTROYED);
            if (!bind)
                return;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_DESTROYED);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.ExecuteCall(3, 0);
        }

        void OnDamaged(GameObject* pGameObject, Player* pPlayer)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DAMAGED);
            if (!bind)
                return;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_DAMAGED);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, pPlayer);
            sEluna.ExecuteCall(3, 0);
        }

        void OnLootStateChanged(GameObject* pGameObject, uint32 state, Unit* pUnit)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE);
            if (!bind)
                return;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, state);
            sEluna.Push(sEluna.L, pUnit);
            sEluna.ExecuteCall(4, 0);
        }

        void OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
        {
            int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED);
            if (!bind)
                return;
            sEluna.BeginCall(bind);
            sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED);
            sEluna.Push(sEluna.L, pGameObject);
            sEluna.Push(sEluna.L, state);
            sEluna.ExecuteCall(3, 0);
        }
        // Player
        void OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_ENTER_COMBAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_ENTER_COMBAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_ENTER_COMBAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pEnemy);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnPlayerLeaveCombat(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEAVE_COMBAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEAVE_COMBAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_LEAVE_COMBAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnPVPKill(Player* pKiller, Player* pKilled)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_PLAYER].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_PLAYER].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_KILL_PLAYER);
                sEluna.Push(sEluna.L, pKiller);
                sEluna.Push(sEluna.L, pKilled);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnCreatureKill(Player* pKiller, Creature* pKilled)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_CREATURE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_CREATURE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_KILL_CREATURE);
                sEluna.Push(sEluna.L, pKiller);
                sEluna.Push(sEluna.L, pKilled);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILLED_BY_CREATURE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILLED_BY_CREATURE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_KILLED_BY_CREATURE);
                sEluna.Push(sEluna.L, pKiller);
                sEluna.Push(sEluna.L, pKilled);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnLevelChanged(Player* pPlayer, uint8 oldLevel)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEVEL_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEVEL_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_LEVEL_CHANGE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, oldLevel);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_TALENTS_CHANGE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, newPoints);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnTalentsReset(Player* pPlayer, bool noCost)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_RESET].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_RESET].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_TALENTS_RESET);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, noCost);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnMoneyChanged(Player* pPlayer, int32& amount)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_MONEY_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_MONEY_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_MONEY_CHANGE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, amount);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_GIVE_XP].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_GIVE_XP].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_GIVE_XP);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, amount);
                sEluna.Push(sEluna.L, pVictim);
                sEluna.ExecuteCall(4, 0);
            }
        }

        void OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPUTATION_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPUTATION_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_REPUTATION_CHANGE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, factionID);
                sEluna.Push(sEluna.L, standing);
                sEluna.Push(sEluna.L, incremental);
                sEluna.ExecuteCall(5, 0);
            }
        }

        void OnDuelRequest(Player* pTarget, Player* pChallenger)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_REQUEST].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_REQUEST].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_DUEL_REQUEST);
                sEluna.Push(sEluna.L, pTarget);
                sEluna.Push(sEluna.L, pChallenger);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnDuelStart(Player* pStarter, Player* pChallenger)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_START].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_START].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_DUEL_START);
                sEluna.Push(sEluna.L, pStarter);
                sEluna.Push(sEluna.L, pChallenger);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_END].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_END].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_DUEL_END);
                sEluna.Push(sEluna.L, pWinner);
                sEluna.Push(sEluna.L, pLoser);
                sEluna.Push(sEluna.L, type);
                sEluna.ExecuteCall(4, 0);
            }
        }

        void OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_WHISPER].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_WHISPER].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_WHISPER);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, msg);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, lang);
                sEluna.Push(sEluna.L, pReceiver);
                sEluna.ExecuteCall(6, 0);
            }
        }

        void OnEmote(Player* pPlayer, uint32 emote)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_EMOTE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_EMOTE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_EMOTE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, emote);
                sEluna.ExecuteCall(3, 0);
            }
        }

        void OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TEXT_EMOTE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TEXT_EMOTE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_TEXT_EMOTE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, textEmote);
                sEluna.Push(sEluna.L, emoteNum);
                sEluna.Push(sEluna.L, guid);
                sEluna.ExecuteCall(5, 0);
            }
        }

        void OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_SPELL_CAST].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_SPELL_CAST].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_SPELL_CAST);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pSpell);
                sEluna.Push(sEluna.L, skipCheck);
                sEluna.ExecuteCall(4, 0);
            }
        }

        void OnLogin(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGIN].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGIN].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_LOGIN);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnLogout(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGOUT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGOUT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_LOGOUT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnCreate(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_CREATE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_CREATE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_CHARACTER_CREATE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnDelete(uint32 guidlow)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_DELETE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_DELETE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_CHARACTER_DELETE);
                sEluna.Push(sEluna.L, guidlow);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnSave(Player* pPlayer)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_SAVE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_SAVE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_SAVE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.ExecuteCall(2, 0);
            }
        }

        void OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_BIND_TO_INSTANCE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_BIND_TO_INSTANCE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_BIND_TO_INSTANCE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, difficulty);
                sEluna.Push(sEluna.L, mapid);
                sEluna.Push(sEluna.L, permanent);
                sEluna.ExecuteCall(5, 0);
            }
        }

        void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_UPDATE_ZONE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_UPDATE_ZONE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_UPDATE_ZONE);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, newZone);
                sEluna.Push(sEluna.L, newArea);
                sEluna.ExecuteCall(4, 0);
            }
        }

        void OnMapChanged(Player* player)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_MAP_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_MAP_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_MAP_CHANGE);
                sEluna.Push(sEluna.L, player);
                sEluna.ExecuteCall(2, 0);
            }
        }

        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg)
        {
            bool Result = true;
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_CHAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, msg);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, lang);
                if (sEluna.ExecuteCall(5, 1))
                {
                    lua_State* L = sEluna.L;
                    if (!lua_isnoneornil(L, 1) && !lua_toboolean(L, 1))
                        Result = false;
                    sEluna.EndCall(1);
                }
            }
            return Result;
        }

        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Group* pGroup)
        {
            bool Result = true;
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_GROUP_CHAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_GROUP_CHAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_GROUP_CHAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, msg);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, lang);
                sEluna.Push(sEluna.L, pGroup);
                if (sEluna.ExecuteCall(6, 1))
                {
                    lua_State* L = sEluna.L;
                    if (!lua_isnoneornil(L, 1) && !lua_toboolean(L, 1))
                        Result = false;
                    sEluna.EndCall(1);
                }
            }
            return Result;
        }

        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Guild* pGuild)
        {
            bool Result = true;
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_GUILD_CHAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_GUILD_CHAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_GUILD_CHAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, msg);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, lang);
                sEluna.Push(sEluna.L, pGuild);
                if (sEluna.ExecuteCall(6, 1))
                {
                    lua_State* L = sEluna.L;
                    if (!lua_isnoneornil(L, 1) && !lua_toboolean(L, 1))
                        Result = false;
                    sEluna.EndCall(1);
                }
            }
            return Result;
        }

        bool OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Channel* pChannel)
        {
            bool Result = true;
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHANNEL_CHAT].begin();
                    itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHANNEL_CHAT].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, PLAYER_EVENT_ON_CHANNEL_CHAT);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, msg);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, lang);
                sEluna.Push(sEluna.L, pChannel->GetChannelId());
                if (sEluna.ExecuteCall(6, 1))
                {
                    lua_State* L = sEluna.L;
                    if (!lua_isnoneornil(L, 1) && !lua_toboolean(L, 1))
                        Result = false;
                    sEluna.EndCall(1);
                }
            }
            return Result;
        }
        // areatrigger
        bool OnAreaTrigger(Player* pPlayer, AreaTriggerEntry const* pTrigger)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[TRIGGER_EVENT_ON_TRIGGER].begin();
                    itr != sEluna.ServerEventBindings[TRIGGER_EVENT_ON_TRIGGER].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, TRIGGER_EVENT_ON_TRIGGER);
                sEluna.Push(sEluna.L, pPlayer);
                sEluna.Push(sEluna.L, pTrigger->id);
                sEluna.ExecuteCall(3, 0);
            }
            return false;
        }
        // weather
        void OnChange(Weather* weather, WeatherState state, float grade)
        {
            for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WEATHER_EVENT_ON_CHANGE].begin();
                    itr != sEluna.ServerEventBindings[WEATHER_EVENT_ON_CHANGE].end(); ++itr)
            {
                sEluna.BeginCall((*itr));
                sEluna.Push(sEluna.L, WEATHER_EVENT_ON_CHANGE);
                sEluna.Push(sEluna.L, (weather->GetZone()));
                sEluna.Push(sEluna.L, state);
                sEluna.Push(sEluna.L, grade);
                sEluna.ExecuteCall(4, 0);
            }
        }
        // transport
        void OnAddPassenger(Transport* transport, Player* player)
        {
        }
        void OnAddCreaturePassenger(Transport* transport, Creature* creature)
        {
        }
        void OnRemovePassenger(Transport* transport, Player* player)
        {
        }
        void OnRelocate(Transport* transport, uint32 waypointId, uint32 mapId, float x, float y, float z)
        {
        }
};

/*
class Eluna_GuildScript : public GuildScript
{
public:
    Eluna_GuildScript() : GuildScript("Eluna_GuildScript") { }

    void OnAddMember(Guild* guild, Player* player, uint8& plRank)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_ADD_MEMBER].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_ADD_MEMBER].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_ADD_MEMBER);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, player);
            sEluna.Push(sEluna.L, plRank);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding, bool isKicked)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_REMOVE_MEMBER].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_REMOVE_MEMBER].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_REMOVE_MEMBER);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, player);
            sEluna.Push(sEluna.L, isDisbanding);
            sEluna.Push(sEluna.L, isKicked);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnMOTDChanged(Guild* guild, const std::string& newMotd)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MOTD_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MOTD_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_MOTD_CHANGE);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, newMotd);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnInfoChanged(Guild* guild, const std::string& newInfo)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_INFO_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_INFO_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_INFO_CHANGE);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, newInfo);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnCreate(Guild* guild, Player* leader, const std::string& name)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_CREATE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_CREATE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_CREATE);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, leader);
            sEluna.Push(sEluna.L, name);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnDisband(Guild* guild)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_DISBAND].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_DISBAND].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_DISBAND);
            sEluna.Push(sEluna.L, guild);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount, bool isRepair)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_WITHDRAW].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_WITHDRAW].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_MONEY_WITHDRAW);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, player);
            sEluna.Push(sEluna.L, amount);
            sEluna.Push(sEluna.L, isRepair);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_DEPOSIT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_DEPOSIT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_MONEY_DEPOSIT);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, player);
            sEluna.Push(sEluna.L, amount);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnItemMove(Guild* guild, Player* player, Item* pItem, bool isSrcBank, uint8 srcContainer, uint8 srcSlotId,
        bool isDestBank, uint8 destContainer, uint8 destSlotId)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_ITEM_MOVE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_ITEM_MOVE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_ITEM_MOVE);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, player);
            sEluna.Push(sEluna.L, pItem);
            sEluna.Push(sEluna.L, isSrcBank);
            sEluna.Push(sEluna.L, srcContainer);
            sEluna.Push(sEluna.L, srcSlotId);
            sEluna.Push(sEluna.L, isDestBank);
            sEluna.Push(sEluna.L, destContainer);
            sEluna.Push(sEluna.L, destSlotId);
            sEluna.ExecuteCall(10, 0);
        }
    }

    void OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_EVENT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_EVENT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_EVENT);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, eventType);
            sEluna.Push(sEluna.L, playerGuid1);
            sEluna.Push(sEluna.L, playerGuid2);
            sEluna.Push(sEluna.L, newRank);
            sEluna.ExecuteCall(6, 0);
        }
    }

    void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_BANK_EVENT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_BANK_EVENT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GUILD_EVENT_ON_BANK_EVENT);
            sEluna.Push(sEluna.L, guild);
            sEluna.Push(sEluna.L, eventType);
            sEluna.Push(sEluna.L, tabId);
            sEluna.Push(sEluna.L, playerGuid);
            sEluna.Push(sEluna.L, itemOrMoney);
            sEluna.Push(sEluna.L, itemStackCount);
            sEluna.Push(sEluna.L, destTabId);
            sEluna.ExecuteCall(8, 0);
        }
    }
};
class Eluna_GroupScript : public GroupScript
{
public:
    Eluna_GroupScript() : GroupScript("Eluna_GroupScript") { }

    void OnAddMember(Group* group, uint64 guid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_ADD].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_ADD].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GROUP_EVENT_ON_MEMBER_ADD);
            sEluna.Push(sEluna.L, group);
            sEluna.Push(sEluna.L, guid);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnInviteMember(Group* group, uint64 guid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_INVITE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_INVITE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GROUP_EVENT_ON_MEMBER_INVITE);
            sEluna.Push(sEluna.L, group);
            sEluna.Push(sEluna.L, guid);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnRemoveMember(Group* group, uint64 guid, RemoveMethod method, uint64 kicker, const char* reason)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_REMOVE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_REMOVE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GROUP_EVENT_ON_MEMBER_REMOVE);
            sEluna.Push(sEluna.L, group);
            sEluna.Push(sEluna.L, guid);
            sEluna.Push(sEluna.L, method);
            sEluna.Push(sEluna.L, kicker);
            sEluna.Push(sEluna.L, reason);
            sEluna.ExecuteCall(6, 0);
        }
    }

    void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_LEADER_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_LEADER_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GROUP_EVENT_ON_LEADER_CHANGE);
            sEluna.Push(sEluna.L, group);
            sEluna.Push(sEluna.L, newLeaderGuid);
            sEluna.Push(sEluna.L, oldLeaderGuid);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnDisband(Group* group)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_DISBAND].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_DISBAND].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, GROUP_EVENT_ON_DISBAND);
            sEluna.Push(sEluna.L, group);
            sEluna.ExecuteCall(2, 0);
        }
    }
};*/



void Eluna::AddScriptHooks()
{
    // AI
    LuaCreatureAI = new Eluna_CreatureScript;
    LuaGameObjectAI = new Eluna_GameObjectScript;
    // Eluna Hooks
    new Eluna_HookScript;
}
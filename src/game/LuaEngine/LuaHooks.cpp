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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_LOOT_ITEM);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushItem(sEluna.LuaState, pItem);
            sEluna.PushUnsigned(sEluna.LuaState, count);
            sEluna.PushULong(sEluna.LuaState, guid);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnFirstLogin(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_FIRST_LOGIN].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_FIRST_LOGIN].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_FIRST_LOGIN);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnRepop(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPOP].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPOP].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_REPOP);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnResurrect(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_RESURRECT].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_RESURRECT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_RESURRECT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnEquip(Player* pPlayer, Item* pItem, uint8 bag, uint8 slot)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_EQUIP].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_EQUIP].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_EQUIP);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushItem(sEluna.LuaState, pItem);
            sEluna.PushUnsigned(sEluna.LuaState, bag);
            sEluna.PushUnsigned(sEluna.LuaState, slot);
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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_CAN_USE_ITEM);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, itemEntry);
            if (sEluna.ExecuteCall(3, 1))
            {
                lua_State* L = sEluna.LuaState;
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
                sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
                sEluna.PushUnit(sEluna.LuaState, pPlayer);
                sEluna.PushItem(sEluna.LuaState, item);
                sEluna.PushUnsigned(sEluna.LuaState, sender);
                sEluna.PushUnsigned(sEluna.LuaState, action);
                if (code.empty())
                    lua_pushnil(sEluna.LuaState);
                else
                    sEluna.PushString(sEluna.LuaState, code.c_str());
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
                sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
                sEluna.PushUnit(sEluna.LuaState, pPlayer); // receiver
                sEluna.PushUnit(sEluna.LuaState, pPlayer); // sender, just not to mess up the amount of args.
                sEluna.PushUnsigned(sEluna.LuaState, sender);
                sEluna.PushUnsigned(sEluna.LuaState, action);
                if (code.empty())
                    lua_pushnil(sEluna.LuaState);
                else
                    sEluna.PushString(sEluna.LuaState, code.c_str());
                sEluna.PushUnsigned(sEluna.LuaState, menuId);
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
            sEluna.PushUnsigned(sEluna.LuaState, ELUNA_EVENT_ON_RESTART);
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
        sEluna.PushUnsigned(sEluna.LuaState, ITEM_EVENT_ON_DUMMY_EFFECT);
        sEluna.PushUnit(sEluna.LuaState, pCaster);
        sEluna.PushUnsigned(sEluna.LuaState, spellId);
        sEluna.PushInteger(sEluna.LuaState, effIndex);
        sEluna.PushItem(sEluna.LuaState, pTarget);
        sEluna.ExecuteCall(5, 0);
        return true;
    }

    bool OnQuestAccept(Player* pPlayer, Item* pItem, Quest const* pQuest)
    {
        int bind = sEluna.ItemEventBindings->GetBind(pItem->GetEntry(), ITEM_EVENT_ON_QUEST_ACCEPT);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushUnsigned(sEluna.LuaState, ITEM_EVENT_ON_QUEST_ACCEPT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushItem(sEluna.LuaState, pItem);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
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
            sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_HELLO);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushItem(sEluna.LuaState, pItem);
            sEluna.ExecuteCall(3, 0);
        }
        if (bind2)
        {
            sEluna.BeginCall(bind2);
            sEluna.PushUnsigned(sEluna.LuaState, ITEM_EVENT_ON_USE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushItem(sEluna.LuaState, pItem);
            if (GameObject* target = targets.getGOTarget())
                sEluna.PushGO(sEluna.LuaState, target);
            else if (Item* target = targets.getItemTarget())
                sEluna.PushItem(sEluna.LuaState, target);
            else if (Unit* target = targets.getUnitTarget())
                sEluna.PushUnit(sEluna.LuaState, target);
            else
                lua_pushnil(sEluna.LuaState);
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
        sEluna.PushUnsigned(sEluna.LuaState, ITEM_EVENT_ON_EXPIRE);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnsigned(sEluna.LuaState, pProto->ItemId);
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
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_DUMMY_EFFECT);
        sEluna.PushUnit(sEluna.LuaState, pCaster);
        sEluna.PushUnsigned(sEluna.LuaState, spellId);
        sEluna.PushInteger(sEluna.LuaState, effIndex);
        sEluna.PushUnit(sEluna.LuaState, pTarget);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_HELLO);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushUnsigned(sEluna.LuaState, sender);
        sEluna.PushUnsigned(sEluna.LuaState, action);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushUnsigned(sEluna.LuaState, sender);
        sEluna.PushUnsigned(sEluna.LuaState, action);
        sEluna.PushString(sEluna.LuaState, code);
        sEluna.ExecuteCall(6, 0);
        return true;
    }

    bool OnQuestAccept(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
    {
        int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_ACCEPT);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_QUEST_ACCEPT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    bool OnQuestSelect(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
    {
        int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_SELECT);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_QUEST_SELECT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    bool OnQuestComplete(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
    {
        int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_COMPLETE);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_QUEST_COMPLETE);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    bool OnQuestReward(Player* pPlayer, Creature* pCreature, Quest const* pQuest)
    {
        int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_QUEST_REWARD);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_QUEST_REWARD);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    uint32 GetDialogStatus(Player* pPlayer, Creature* pCreature)
    {
        int bind = sEluna.CreatureEventBindings->GetBind(pCreature->GetEntry(), CREATURE_EVENT_ON_DIALOG_STATUS);
        if (!bind)
            return 0;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, CREATURE_EVENT_ON_DIALOG_STATUS);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushUnit(sEluna.LuaState, pCreature);
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
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_DUMMY_EFFECT);
        sEluna.PushUnit(sEluna.LuaState, pCaster);
        sEluna.PushUnsigned(sEluna.LuaState, spellId);
        sEluna.PushInteger(sEluna.LuaState, effIndex);
        sEluna.PushGO(sEluna.LuaState, pTarget);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_HELLO);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnsigned(sEluna.LuaState, sender);
        sEluna.PushUnsigned(sEluna.LuaState, action);
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
        sEluna.PushUnsigned(sEluna.LuaState, GOSSIP_EVENT_ON_SELECT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnsigned(sEluna.LuaState, sender);
        sEluna.PushUnsigned(sEluna.LuaState, action);
        sEluna.PushString(sEluna.LuaState, code);
        sEluna.ExecuteCall(6, 0);
        return true;
    }

    bool OnQuestAccept(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_ACCEPT);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_QUEST_ACCEPT);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    bool OnQuestReward(Player* pPlayer, GameObject* pGameObject, Quest const* pQuest)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_QUEST_REWARD);
        if (!bind)
            return false;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_QUEST_REWARD);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushQuest(sEluna.LuaState, pQuest);
        sEluna.ExecuteCall(4, 0);
        return true;
    }

    uint32 GetDialogStatus(Player* pPlayer, GameObject* pGameObject)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DIALOG_STATUS);
        if (!bind)
            return 0;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_DIALOG_STATUS);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.ExecuteCall(3, 0);
        return 100;
    }

    void OnDestroyed(GameObject* pGameObject, Player* pPlayer)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DESTROYED);
        if (!bind)
            return;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_DESTROYED);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.ExecuteCall(3, 0);
    }

    void OnDamaged(GameObject* pGameObject, Player* pPlayer)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_DAMAGED);
        if (!bind)
            return;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_DAMAGED);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnit(sEluna.LuaState, pPlayer);
        sEluna.ExecuteCall(3, 0);
    }

    void OnLootStateChanged(GameObject* pGameObject, uint32 state, Unit* pUnit)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE);
        if (!bind)
            return;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnsigned(sEluna.LuaState, state);
        sEluna.PushUnit(sEluna.LuaState, pUnit);
        sEluna.ExecuteCall(4, 0);
    }

    void OnGameObjectStateChanged(GameObject* pGameObject, uint32 state)
    {
        int bind = sEluna.GameObjectEventBindings->GetBind(pGameObject->GetEntry(), GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED);
        if (!bind)
            return;
        sEluna.BeginCall(bind);
        sEluna.PushInteger(sEluna.LuaState, GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED);
        sEluna.PushGO(sEluna.LuaState, pGameObject);
        sEluna.PushUnsigned(sEluna.LuaState, state);
        sEluna.ExecuteCall(3, 0);
    }
    // Player
    void OnPlayerEnterCombat(Player* pPlayer, Unit* pEnemy)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_ENTER_COMBAT].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_ENTER_COMBAT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_ENTER_COMBAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnit(sEluna.LuaState, pEnemy);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnPlayerLeaveCombat(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEAVE_COMBAT].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEAVE_COMBAT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_LEAVE_COMBAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnPVPKill(Player* pKiller, Player* pKilled)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_PLAYER].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_PLAYER].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_KILL_PLAYER);
            sEluna.PushUnit(sEluna.LuaState, pKiller);
            sEluna.PushUnit(sEluna.LuaState, pKilled);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnCreatureKill(Player* pKiller, Creature* pKilled)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_CREATURE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILL_CREATURE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_KILL_CREATURE);
            sEluna.PushUnit(sEluna.LuaState, pKiller);
            sEluna.PushUnit(sEluna.LuaState, pKilled);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnPlayerKilledByCreature(Creature* pKiller, Player* pKilled)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILLED_BY_CREATURE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_KILLED_BY_CREATURE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_KILLED_BY_CREATURE);
            sEluna.PushUnit(sEluna.LuaState, pKiller);
            sEluna.PushUnit(sEluna.LuaState, pKilled);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnLevelChanged(Player* pPlayer, uint8 oldLevel)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEVEL_CHANGE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LEVEL_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_LEVEL_CHANGE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, oldLevel);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnFreeTalentPointsChanged(Player* pPlayer, uint32 newPoints)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_CHANGE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_TALENTS_CHANGE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, newPoints);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnTalentsReset(Player* pPlayer, bool noCost)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_RESET].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TALENTS_RESET].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_TALENTS_RESET);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushBoolean(sEluna.LuaState, noCost);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnMoneyChanged(Player* pPlayer, int32& amount)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_MONEY_CHANGE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_MONEY_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_MONEY_CHANGE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushInteger(sEluna.LuaState, amount);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnGiveXP(Player* pPlayer, uint32& amount, Unit* pVictim)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_GIVE_XP].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_GIVE_XP].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_GIVE_XP);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, amount);
            sEluna.PushUnit(sEluna.LuaState, pVictim);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnReputationChange(Player* pPlayer, uint32 factionID, int32& standing, bool incremental)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPUTATION_CHANGE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_REPUTATION_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_REPUTATION_CHANGE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, factionID);
            sEluna.PushInteger(sEluna.LuaState, standing);
            sEluna.PushBoolean(sEluna.LuaState, incremental);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnDuelRequest(Player* pTarget, Player* pChallenger)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_REQUEST].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_REQUEST].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_DUEL_REQUEST);
            sEluna.PushUnit(sEluna.LuaState, pTarget);
            sEluna.PushUnit(sEluna.LuaState, pChallenger);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnDuelStart(Player* pStarter, Player* pChallenger)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_START].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_START].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_DUEL_START);
            sEluna.PushUnit(sEluna.LuaState, pStarter);
            sEluna.PushUnit(sEluna.LuaState, pChallenger);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnDuelEnd(Player* pWinner, Player* pLoser, DuelCompleteType type)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_END].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_DUEL_END].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_DUEL_END);
            sEluna.PushUnit(sEluna.LuaState, pWinner);
            sEluna.PushUnit(sEluna.LuaState, pLoser);
            sEluna.PushInteger(sEluna.LuaState, type);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnChat(Player* pPlayer, uint32 type, uint32 lang, std::string& msg, Player* pReceiver)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_WHISPER].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_WHISPER].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_WHISPER);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushString(sEluna.LuaState, msg.c_str());
            sEluna.PushUnsigned(sEluna.LuaState, type);
            sEluna.PushUnsigned(sEluna.LuaState, lang);
            sEluna.PushUnit(sEluna.LuaState, pReceiver);
            sEluna.ExecuteCall(6, 0);
        }
    }

    void OnEmote(Player* pPlayer, uint32 emote)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_EMOTE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_EMOTE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_EMOTE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, emote);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnTextEmote(Player* pPlayer, uint32 textEmote, uint32 emoteNum, uint64 guid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_TEXT_EMOTE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_TEXT_EMOTE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_TEXT_EMOTE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, textEmote);
            sEluna.PushUnsigned(sEluna.LuaState, emoteNum);
            sEluna.PushULong(sEluna.LuaState, guid);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnSpellCast(Player* pPlayer, Spell* pSpell, bool skipCheck)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_SPELL_CAST].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_SPELL_CAST].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_SPELL_CAST);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushSpell(sEluna.LuaState, pSpell);
            sEluna.PushBoolean(sEluna.LuaState, skipCheck);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnLogin(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGIN].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGIN].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_LOGIN);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnLogout(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGOUT].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_LOGOUT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_LOGOUT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnCreate(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_CREATE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_CREATE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_CHARACTER_CREATE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnDelete(uint32 guidlow)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_DELETE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_CHARACTER_DELETE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_CHARACTER_DELETE);
            sEluna.PushULong(sEluna.LuaState, guidlow);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnSave(Player* pPlayer)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_SAVE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_SAVE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_SAVE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnBindToInstance(Player* pPlayer, Difficulty difficulty, uint32 mapid, bool permanent)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_BIND_TO_INSTANCE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_BIND_TO_INSTANCE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_BIND_TO_INSTANCE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushInteger(sEluna.LuaState, difficulty);
            sEluna.PushUnsigned(sEluna.LuaState, mapid);
            sEluna.PushBoolean(sEluna.LuaState, permanent);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnUpdateZone(Player* pPlayer, uint32 newZone, uint32 newArea)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_UPDATE_ZONE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_UPDATE_ZONE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_UPDATE_ZONE);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, newZone);
            sEluna.PushUnsigned(sEluna.LuaState, newArea);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnMapChanged(Player* player)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[PLAYER_EVENT_ON_MAP_CHANGE].begin();
            itr != sEluna.ServerEventBindings[PLAYER_EVENT_ON_MAP_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_MAP_CHANGE);
            sEluna.PushUnit(sEluna.LuaState, player);
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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_CHAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushString(sEluna.LuaState, msg.c_str());
            sEluna.PushUnsigned(sEluna.LuaState, type);
            sEluna.PushUnsigned(sEluna.LuaState, lang);
            if (sEluna.ExecuteCall(5, 1))
            {
                lua_State* L = sEluna.LuaState;
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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_GROUP_CHAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushString(sEluna.LuaState, msg.c_str());
            sEluna.PushUnsigned(sEluna.LuaState, type);
            sEluna.PushUnsigned(sEluna.LuaState, lang);
            sEluna.PushGroup(sEluna.LuaState, pGroup);
            if (sEluna.ExecuteCall(6, 1))
            {
                lua_State* L = sEluna.LuaState;
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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_GUILD_CHAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushString(sEluna.LuaState, msg.c_str());
            sEluna.PushUnsigned(sEluna.LuaState, type);
            sEluna.PushUnsigned(sEluna.LuaState, lang);
            sEluna.PushGuild(sEluna.LuaState, pGuild);
            if (sEluna.ExecuteCall(6, 1))
            {
                lua_State* L = sEluna.LuaState;
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
            sEluna.PushUnsigned(sEluna.LuaState, PLAYER_EVENT_ON_CHANNEL_CHAT);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushString(sEluna.LuaState, msg.c_str());
            sEluna.PushUnsigned(sEluna.LuaState, type);
            sEluna.PushUnsigned(sEluna.LuaState, lang);
            sEluna.PushUnsigned(sEluna.LuaState, pChannel->GetChannelId());
            if (sEluna.ExecuteCall(6, 1))
            {
                lua_State* L = sEluna.LuaState;
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
            sEluna.PushUnsigned(sEluna.LuaState, TRIGGER_EVENT_ON_TRIGGER);
            sEluna.PushUnit(sEluna.LuaState, pPlayer);
            sEluna.PushUnsigned(sEluna.LuaState, pTrigger->id);
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
            sEluna.PushUnsigned(sEluna.LuaState, WEATHER_EVENT_ON_CHANGE);
            sEluna.PushUnsigned(sEluna.LuaState, (weather->GetZone()));
            sEluna.PushInteger(sEluna.LuaState, state);
            sEluna.PushFloat(sEluna.LuaState, grade);
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
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_ADD_MEMBER);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, player);
            sEluna.PushUnsigned(sEluna.LuaState, plRank);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnRemoveMember(Guild* guild, Player* player, bool isDisbanding, bool isKicked)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_REMOVE_MEMBER].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_REMOVE_MEMBER].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_REMOVE_MEMBER);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, player);
            sEluna.PushBoolean(sEluna.LuaState, isDisbanding);
            sEluna.PushBoolean(sEluna.LuaState, isKicked);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnMOTDChanged(Guild* guild, const std::string& newMotd)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MOTD_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MOTD_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_MOTD_CHANGE);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushString(sEluna.LuaState, newMotd.c_str());
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnInfoChanged(Guild* guild, const std::string& newInfo)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_INFO_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_INFO_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_INFO_CHANGE);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushString(sEluna.LuaState, newInfo.c_str());
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnCreate(Guild* guild, Player* leader, const std::string& name)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_CREATE].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_CREATE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_CREATE);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, leader);
            sEluna.PushString(sEluna.LuaState, name.c_str());
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnDisband(Guild* guild)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_DISBAND].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_DISBAND].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_DISBAND);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnMemberWitdrawMoney(Guild* guild, Player* player, uint32 &amount, bool isRepair)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_WITHDRAW].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_WITHDRAW].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_MONEY_WITHDRAW);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, player);
            sEluna.PushUnsigned(sEluna.LuaState, amount);
            sEluna.PushBoolean(sEluna.LuaState, isRepair);
            sEluna.ExecuteCall(5, 0);
        }
    }

    void OnMemberDepositMoney(Guild* guild, Player* player, uint32 &amount)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_DEPOSIT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_MONEY_DEPOSIT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_MONEY_DEPOSIT);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, player);
            sEluna.PushUnsigned(sEluna.LuaState, amount);
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
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_ITEM_MOVE);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnit(sEluna.LuaState, player);
            sEluna.PushItem(sEluna.LuaState, pItem);
            sEluna.PushBoolean(sEluna.LuaState, isSrcBank);
            sEluna.PushUnsigned(sEluna.LuaState, srcContainer);
            sEluna.PushUnsigned(sEluna.LuaState, srcSlotId);
            sEluna.PushBoolean(sEluna.LuaState, isDestBank);
            sEluna.PushUnsigned(sEluna.LuaState, destContainer);
            sEluna.PushUnsigned(sEluna.LuaState, destSlotId);
            sEluna.ExecuteCall(10, 0);
        }
    }

    void OnEvent(Guild* guild, uint8 eventType, uint32 playerGuid1, uint32 playerGuid2, uint8 newRank)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_EVENT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_EVENT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_EVENT);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnsigned(sEluna.LuaState, eventType);
            sEluna.PushUnsigned(sEluna.LuaState, playerGuid1);
            sEluna.PushUnsigned(sEluna.LuaState, playerGuid2);
            sEluna.PushUnsigned(sEluna.LuaState, newRank);
            sEluna.ExecuteCall(6, 0);
        }
    }

    void OnBankEvent(Guild* guild, uint8 eventType, uint8 tabId, uint32 playerGuid, uint32 itemOrMoney, uint16 itemStackCount, uint8 destTabId)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GUILD_EVENT_ON_BANK_EVENT].begin();
            itr != sEluna.ServerEventBindings[GUILD_EVENT_ON_BANK_EVENT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GUILD_EVENT_ON_BANK_EVENT);
            sEluna.PushGuild(sEluna.LuaState, guild);
            sEluna.PushUnsigned(sEluna.LuaState, eventType);
            sEluna.PushUnsigned(sEluna.LuaState, tabId);
            sEluna.PushUnsigned(sEluna.LuaState, playerGuid);
            sEluna.PushUnsigned(sEluna.LuaState, itemOrMoney);
            sEluna.PushUnsigned(sEluna.LuaState, itemStackCount);
            sEluna.PushUnsigned(sEluna.LuaState, destTabId);
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
            sEluna.PushUnsigned(sEluna.LuaState, GROUP_EVENT_ON_MEMBER_ADD);
            sEluna.PushGroup(sEluna.LuaState, group);
            sEluna.PushULong(sEluna.LuaState, guid);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnInviteMember(Group* group, uint64 guid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_INVITE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_INVITE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GROUP_EVENT_ON_MEMBER_INVITE);
            sEluna.PushGroup(sEluna.LuaState, group);
            sEluna.PushULong(sEluna.LuaState, guid);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnRemoveMember(Group* group, uint64 guid, RemoveMethod method, uint64 kicker, const char* reason)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_REMOVE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_MEMBER_REMOVE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GROUP_EVENT_ON_MEMBER_REMOVE);
            sEluna.PushGroup(sEluna.LuaState, group);
            sEluna.PushULong(sEluna.LuaState, guid);
            sEluna.PushInteger(sEluna.LuaState, method);
            sEluna.PushULong(sEluna.LuaState, kicker);
            sEluna.PushString(sEluna.LuaState, reason);
            sEluna.ExecuteCall(6, 0);
        }
    }

    void OnChangeLeader(Group* group, uint64 newLeaderGuid, uint64 oldLeaderGuid)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_LEADER_CHANGE].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_LEADER_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GROUP_EVENT_ON_LEADER_CHANGE);
            sEluna.PushGroup(sEluna.LuaState, group);
            sEluna.PushULong(sEluna.LuaState, newLeaderGuid);
            sEluna.PushULong(sEluna.LuaState, oldLeaderGuid);
            sEluna.ExecuteCall(4, 0);
        }
    }

    void OnDisband(Group* group)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[GROUP_EVENT_ON_DISBAND].begin();
            itr != sEluna.ServerEventBindings[GROUP_EVENT_ON_DISBAND].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.PushUnsigned(sEluna.LuaState, GROUP_EVENT_ON_DISBAND);
            sEluna.PushGroup(sEluna.LuaState, group);
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
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

#ifndef __ELUNA__H
#define __ELUNA__H

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
};

#include "Includes.h"

enum RegisterTypes
{
    REGTYPE_SERVER,
    REGTYPE_CREATURE,
    REGTYPE_CREATURE_GOSSIP,
    REGTYPE_GAMEOBJECT,
    REGTYPE_GAMEOBJECT_GOSSIP,
    REGTYPE_ITEM,
    REGTYPE_ITEM_GOSSIP,
    REGTYPE_PLAYER_GOSSIP,
    REGTYPE_COUNT
};

// RegisterServerHook(EventId, function)
enum ServerEvents
{
    // Player
    PLAYER_EVENT_ON_CHARACTER_CREATE        =     1,        // (event, player)
    PLAYER_EVENT_ON_CHARACTER_DELETE        =     2,        // (event, guid)
    PLAYER_EVENT_ON_LOGIN                   =     3,        // (event, player)
    PLAYER_EVENT_ON_LOGOUT                  =     4,        // (event, player)
    PLAYER_EVENT_ON_SPELL_CAST              =     5,        // (event, player, spell, skipCheck)
    PLAYER_EVENT_ON_KILL_PLAYER             =     6,        // (event, killer, killed)
    PLAYER_EVENT_ON_KILL_CREATURE           =     7,        // (event, killer, killed)
    PLAYER_EVENT_ON_KILLED_BY_CREATURE      =     8,        // (event, killer, killed)
    PLAYER_EVENT_ON_DUEL_REQUEST            =     9,        // (event, target, challenger)
    PLAYER_EVENT_ON_DUEL_START              =     10,       // (event, player1, player2)
    PLAYER_EVENT_ON_DUEL_END                =     11,       // (event, winner, loser, type)
    PLAYER_EVENT_ON_GIVE_XP                 =     12,       // (event, player, amount, victim)
    PLAYER_EVENT_ON_LEVEL_CHANGE            =     13,       // (event, player, oldLevel)
    PLAYER_EVENT_ON_MONEY_CHANGE            =     14,       // (event, player, amount)
    PLAYER_EVENT_ON_REPUTATION_CHANGE       =     15,       // (event, player, factionId, standing, incremental)
    PLAYER_EVENT_ON_TALENTS_CHANGE          =     16,       // (event, player, points)
    PLAYER_EVENT_ON_TALENTS_RESET           =     17,       // (event, player, noCost)
    PLAYER_EVENT_ON_CHAT                    =     18,       // (event, player, msg, Type, lang) - Can return false
    PLAYER_EVENT_ON_WHISPER                 =     19,       // (event, player, msg, Type, lang, receiver)
    PLAYER_EVENT_ON_GROUP_CHAT              =     20,       // (event, player, msg, Type, lang, group) - Can return false
    PLAYER_EVENT_ON_GUILD_CHAT              =     21,       // (event, player, msg, Type, lang, guild) - Can return false
    PLAYER_EVENT_ON_CHANNEL_CHAT            =     22,       // (event, player, msg, Type, lang, channel) - Can return false
    PLAYER_EVENT_ON_EMOTE                   =     23,       // (event, player, emote) - Not triggered on any known emote
    PLAYER_EVENT_ON_TEXT_EMOTE              =     24,       // (event, player, textEmote, emoteNum, guid)
    PLAYER_EVENT_ON_SAVE                    =     25,       // (event, player)
    PLAYER_EVENT_ON_BIND_TO_INSTANCE        =     26,       // (event, player, difficulty, mapid, permanent)
    PLAYER_EVENT_ON_UPDATE_ZONE             =     27,       // (event, player, newZone, newArea)
    PLAYER_EVENT_ON_MAP_CHANGE              =     28,       // (event, player)

    // Guild
    GUILD_EVENT_ON_ADD_MEMBER               =     29,       // (event, guild, player, rank)
    GUILD_EVENT_ON_REMOVE_MEMBER            =     30,       // (event, guild, isDisbanding, isKicked)
    GUILD_EVENT_ON_MOTD_CHANGE              =     31,       // (event, guild, newMotd)
    GUILD_EVENT_ON_INFO_CHANGE              =     32,       // (event, guild, newInfo)
    GUILD_EVENT_ON_CREATE                   =     33,       // (event, guild, leader, name)
    GUILD_EVENT_ON_DISBAND                  =     34,       // (event, guild)
    GUILD_EVENT_ON_MONEY_WITHDRAW           =     35,       // (event, guild, player, amount, isRepair)
    GUILD_EVENT_ON_MONEY_DEPOSIT            =     36,       // (event, guild, player, amount)
    GUILD_EVENT_ON_ITEM_MOVE                =     37,       // (event, guild, player, item, isSrcBank, srcContainer, srcSlotId, isDestBank, destContainer, destSlotId)
    GUILD_EVENT_ON_EVENT                    =     38,       // (event, guild, eventType, plrGUIDLow1, plrGUIDLow2, newRank)
    GUILD_EVENT_ON_BANK_EVENT               =     39,       // (event, guild, eventType, tabId, playerGUIDLow, itemOrMoney, itemStackCount, destTabId)

    // Server
    SERVER_EVENT_ON_NETWORK_START           =     40,       // Not Implemented
    SERVER_EVENT_ON_NETWORK_STOP            =     41,       // Not Implemented
    SERVER_EVENT_ON_SOCKET_OPEN             =     42,       // Not Implemented
    SERVER_EVENT_ON_SOCKET_CLOSE            =     43,       // Not Implemented
    SERVER_EVENT_ON_PACKET_RECEIVE          =     44,       // Not Implemented
    SERVER_EVENT_ON_PACKET_RECEIVE_UNKNOWN  =     45,       // Not Implemented
    SERVER_EVENT_ON_PACKET_SEND             =     46,       // Not Implemented

    // World
    WORLD_EVENT_ON_OPEN_STATE_CHANGE        =     47,       // (event, open)
    WORLD_EVENT_ON_CONFIG_LOAD              =     48,       // (event, reload)
    WORLD_EVENT_ON_MOTD_CHANGE              =     49,       // (event, newMOTD)
    WORLD_EVENT_ON_SHUTDOWN_INIT            =     50,       // (event, code, mask)
    WORLD_EVENT_ON_SHUTDOWN_CANCEL          =     51,       // (event)
    WORLD_EVENT_ON_UPDATE                   =     52,       // (event, diff)
    WORLD_EVENT_ON_STARTUP                  =     53,       // (event)
    WORLD_EVENT_ON_SHUTDOWN                 =     54,       // (event)

    // Eluna
    ELUNA_EVENT_ON_RESTART                  =     55,       // (event)

    // Map
    MAP_EVENT_ON_CREATE                     =     56,       // Not Implemented
    MAP_EVENT_ON_DESTROY                    =     57,       // Not Implemented
    MAP_EVENT_ON_LOAD                       =     58,       // Not Implemented
    MAP_EVENT_ON_UNLOAD                     =     59,       // Not Implemented
    MAP_EVENT_ON_PLAYER_ENTER               =     60,       // Not Implemented
    MAP_EVENT_ON_PLAYER_LEAVE               =     61,       // Not Implemented
    MAP_EVENT_ON_UPDATE                     =     62,       // Not Implemented

    // Area trigger
    TRIGGER_EVENT_ON_TRIGGER                =     63,       // (event, player, triggerId)

    // Weather
    WEATHER_EVENT_ON_CHANGE                 =     64,       // (event, weather, state, grade)

    // Auction house
    AUCTION_EVENT_ON_ADD                    =     65,       // Not Implemented
    AUCTION_EVENT_ON_REMOVE                 =     66,       // Not Implemented
    AUCTION_EVENT_ON_SUCCESFUL              =     67,       // Not Implemented
    AUCTION_EVENT_ON_EXPIRE                 =     68,       // Not Implemented

    // Group
    GROUP_EVENT_ON_MEMBER_ADD               =     69,       // (event, group, guid)
    GROUP_EVENT_ON_MEMBER_INVITE            =     70,       // (event, group, guid)
    GROUP_EVENT_ON_MEMBER_REMOVE            =     71,       // (event, group, guid, method, kicker, reason)
    GROUP_EVENT_ON_LEADER_CHANGE            =     72,       // (event, group, newLeaderGuid, oldLeaderGuid)
    GROUP_EVENT_ON_DISBAND                  =     73,       // (event, group)

    // Custom
    PLAYER_EVENT_ON_EQUIP                   =     74,       // (event, player, item, bag, slot)
    PLAYER_EVENT_ON_FIRST_LOGIN             =     75,       // (event, player)
    PLAYER_EVENT_ON_CAN_USE_ITEM            =     76,       // (event, player, itemEntry)
    PLAYER_EVENT_ON_LOOT_ITEM               =     77,       // (event, player, item, count)
    PLAYER_EVENT_ON_ENTER_COMBAT            =     78,       // (event, player, enemy)
    PLAYER_EVENT_ON_LEAVE_COMBAT            =     79,       // (event, player)
    PLAYER_EVENT_ON_REPOP                   =     80,       // (event, player)
    PLAYER_EVENT_ON_RESURRECT               =     81,       // (event, player)

    SERVER_EVENT_COUNT
};

// RegisterCreatureEvent(entry, EventId, function)
enum CreatureEvents
{
    CREATURE_EVENT_ON_ENTER_COMBAT                    = 1,  // (event, creature, target)
    CREATURE_EVENT_ON_LEAVE_COMBAT                    = 2,  // (event, creature)
    CREATURE_EVENT_ON_TARGET_DIED                     = 3,  // (event, creature, victim)
    CREATURE_EVENT_ON_DIED                            = 4,  // (event, creature, killer)
    CREATURE_EVENT_ON_SPAWN                           = 5,  // (event, creature)
    CREATURE_EVENT_ON_REACH_WP                        = 6,  // (event, creature, type, id)
    CREATURE_EVENT_ON_AIUPDATE                        = 7,  // (event, creature, diff)
    CREATURE_EVENT_ON_RECEIVE_EMOTE                   = 8,  // (event, creature, player, emoteid)
    CREATURE_EVENT_ON_DAMAGE_TAKEN                    = 9,  // (event, creature, attacker, damage)
    CREATURE_EVENT_ON_PRE_COMBAT                      = 10, // (event, creature, target)
    CREATURE_EVENT_ON_ATTACKED_AT                     = 11, // (event, creature, attacker)
    CREATURE_EVENT_ON_OWNER_ATTACKED                  = 12, // (event, creature, target)
    CREATURE_EVENT_ON_OWNER_ATTACKED_AT               = 13, // (event, creature, attacker)
    CREATURE_EVENT_ON_HIT_BY_SPELL                    = 14, // (event, creature, caster, spellid)
    CREATURE_EVENT_ON_SPELL_HIT_TARGET                = 15, // (event, creature, target, spellid)
    CREATURE_EVENT_ON_SPELL_CLICK                     = 16, // (event, creature, clicker)
    CREATURE_EVENT_ON_CHARMED                         = 17, // (event, creature, apply)
    CREATURE_EVENT_ON_POSSESS                         = 18, // (event, creature, apply)
    CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE          = 19, // (event, creature, summon)
    CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN       = 20, // (event, creature, summon)
    CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED          = 21, // (event, creature, summon, killer)
    CREATURE_EVENT_ON_SUMMONED                        = 22, // (event, creature, summoner)
    CREATURE_EVENT_ON_RESET                           = 23, // (event, creature)
    CREATURE_EVENT_ON_REACH_HOME                      = 24, // (event, creature)
    CREATURE_EVENT_ON_CAN_RESPAWN                     = 25, // (event, creature)
    CREATURE_EVENT_ON_CORPSE_REMOVED                  = 26, // (event, creature, respawndelay)
    CREATURE_EVENT_ON_MOVE_IN_LOS                     = 27, // (event, creature, unit)
    CREATURE_EVENT_ON_VISIBLE_MOVE_IN_LOS             = 28, // (event, creature, unit)
    CREATURE_EVENT_ON_PASSANGER_BOARDED               = 29, // (event, creature, passanger, seatid, apply)
    CREATURE_EVENT_ON_DUMMY_EFFECT                    = 30, // (event, caster, spellid, effindex, creature)
    CREATURE_EVENT_ON_QUEST_ACCEPT                    = 31, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_SELECT                    = 32, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_COMPLETE                  = 33, // (event, player, creature, quest)
    CREATURE_EVENT_ON_QUEST_REWARD                    = 34, // (event, player, creature, quest, opt)
    CREATURE_EVENT_ON_DIALOG_STATUS                   = 35, // (event, player, creature)
    CREATURE_EVENT_COUNT
};

// RegisterGameObjectEvent(entry, EventId, function)
enum GameObjectEvents
{
    GAMEOBJECT_EVENT_ON_AIUPDATE                    = 1,    // (event, go, diff)
    GAMEOBJECT_EVENT_ON_RESET                       = 2,    // (event, go)
    GAMEOBJECT_EVENT_ON_DUMMY_EFFECT                = 3,    // (event, caster, spellid, effindex, go)
    GAMEOBJECT_EVENT_ON_QUEST_ACCEPT                = 4,    // (event, player, go, quest)
    GAMEOBJECT_EVENT_ON_QUEST_REWARD                = 5,    // (event, player, go, quest, opt)
    GAMEOBJECT_EVENT_ON_DIALOG_STATUS               = 6,    // (event, player, go)
    GAMEOBJECT_EVENT_ON_DESTROYED                   = 7,    // (event, go, player)
    GAMEOBJECT_EVENT_ON_DAMAGED                     = 8,    // (event, go, player)
    GAMEOBJECT_EVENT_ON_LOOT_STATE_CHANGE           = 9,    // (event, go, state, unit)
    GAMEOBJECT_EVENT_ON_GO_STATE_CHANGED            = 10,   // (event, go, state)
    GAMEOBJECT_EVENT_COUNT
};

// RegisterItemEvent(entry, EventId, function)
enum ItemEvents
{
    ITEM_EVENT_ON_DUMMY_EFFECT                      = 1,    // (event, caster, spellid, effindex, item)
    ITEM_EVENT_ON_USE                               = 2,    // (event, player, item, target)
    ITEM_EVENT_ON_QUEST_ACCEPT                      = 3,    // (event, player, item, quest)
    ITEM_EVENT_ON_EXPIRE                            = 4,    // (event, player, itemid)
    ITEM_EVENT_COUNT
};

// RegisterCreatureGossipEvent(entry, EventId, function)
// RegisterGameObjectGossipEvent(entry, EventId, function)
// RegisterItemGossipEvent(entry, EventId, function)
// RegisterPlayerGossipEvent(menu_id, EventId, function)
enum GossipEvents
{
    GOSSIP_EVENT_ON_HELLO                           = 1,    // (event, player, object) - Object is the Creature/GameObject/Item
    GOSSIP_EVENT_ON_SELECT                          = 2,    // (event, player, object, sender, intid, code, menu_id) - Object is the Creature/GameObject/Item/Player, menu_id is only for player gossip
    GOSSIP_EVENT_COUNT
};

struct LoadedScripts
{
    std::set<std::string> luaFiles;
};

template<typename T> const char* GetTName();

template<class T>
struct ElunaRegister
{
    const char* name;
    int(*mfunc)(lua_State*, T*);
};

template<typename T>
void SetMethods(lua_State* L, ElunaRegister<T>* methodTable)
{
    if (!methodTable)
        return;
    if (!lua_istable(L, 1))
        return;
    lua_pushstring(L, "GetObjectType");
    lua_pushcclosure(L, ElunaTemplate<T>::type, 0);
    lua_settable(L, 1);
    for (; methodTable->name; ++methodTable)
    {
        lua_pushstring(L, methodTable->name);
        lua_pushlightuserdata(L, (void*)methodTable);
        lua_pushcclosure(L, ElunaTemplate<T>::thunk, 1);
        lua_settable(L, 1);
    }
}

template<typename T>
class ElunaTemplate
{
    public:
        static int type(lua_State* L)
        {
            lua_pushstring(L, GetTName<T>());
            return 1;
        }

        static void Register(lua_State* L)
        {
            lua_settop(L, 0); // clean stack

            lua_newtable(L);
            int methods = lua_gettop(L);

            luaL_newmetatable(L, GetTName<T>());
            int metatable = lua_gettop(L);

            // store method table in globals so that
            // scripts can add functions in Lua
            lua_pushvalue(L, methods);
            lua_setglobal(L, GetTName<T>());

            // hide metatable
            lua_pushvalue(L, methods);
            lua_setfield(L, metatable, "__metatable");

            lua_pushvalue(L, methods);
            lua_setfield(L, metatable, "__index");

            lua_pushcfunction(L, tostringT);
            lua_setfield(L, metatable, "__tostring");

            lua_pushcfunction(L, gcT);
            lua_setfield(L, metatable, "__gc");

            lua_newtable(L);
            lua_setmetatable(L, methods);
        }

        static int push(lua_State* L, T const* obj, bool gc = false)
        {
            if (!obj)
            {
                lua_pushnil(L);
                return lua_gettop(L);
            }
            luaL_getmetatable(L, GetTName<T>());
            if (lua_isnil(L, -1))
                luaL_error(L, "%s missing metatable", GetTName<T>());
            int idxMt = lua_gettop(L);
            T const** ptrHold = (T const**)lua_newuserdata(L, sizeof(T**));
            int ud = lua_gettop(L);
            if (ptrHold)
            {
                *ptrHold = obj;
                lua_pushvalue(L, idxMt);
                lua_setmetatable(L, -2);
                char name[32];
                tostring(name, obj);
                lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
                if (lua_isnil(L, -1))
                {
                    luaL_newmetatable(L, "DO NOT TRASH");
                    lua_pop(L, 1);
                }
                lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
                if (gc == false)
                {
                    lua_pushboolean(L, 1);
                    lua_setfield(L, -2, name);
                }
                lua_pop(L, 1);
            }
            lua_settop(L, ud);
            lua_replace(L, idxMt);
            lua_settop(L, idxMt);
            return idxMt;
        }

        static T* check(lua_State* L, int narg)
        {
            T** ptrHold = static_cast<T**>(lua_touserdata(L, narg));
            if (!ptrHold)
                return NULL;
            return *ptrHold;
        }

        static int thunk(lua_State* L)
        {
            T* obj = check(L, 1); // get self
            lua_remove(L, 1); // remove self
            ElunaRegister<T>* l = static_cast<ElunaRegister<T>*>(lua_touserdata(L, lua_upvalueindex(1)));
            if (!obj)
                return 0;
            return l->mfunc(L, obj);
        }

        static int gcT(lua_State* L)
        {
            T* obj = check(L, 1);
            if (!obj)
                return 0;
            lua_getfield(L, LUA_REGISTRYINDEX, "DO NOT TRASH");
            if (lua_istable(L, -1))
            {
                char name[32];
                tostring(name, obj);
                lua_getfield(L, -1, std::string(name).c_str());
                if (lua_isnil(L, -1))
                {
                    delete obj;
                    obj = NULL;
                }
            }
            return 1;
        }

        static int tostringT(lua_State* L)
        {
            char buff[32];
            T** ptrHold = (T**)lua_touserdata(L, 1);
            T* obj = *ptrHold;
            sprintf(buff, "%p", obj);
            lua_pushfstring(L, "%s (%s)", GetTName<T>(), buff);
            return 1;
        }

        inline static void tostring(char* buff, void const* obj)
        {
            sprintf(buff, "%p", obj);
        }

        static int index(lua_State* L)
        {
            lua_getglobal(L, GetTName<T>());
            const char* key = lua_tostring(L, 2);
            if (lua_istable(L, - 1))
            {
                lua_pushvalue(L, 2);
                lua_rawget(L, -2);
                if (lua_isnil(L, -1))
                {
                    lua_getmetatable(L, -2);
                    if (lua_istable(L, -1))
                    {
                        lua_getfield(L, -1, "__index");
                        if (lua_isfunction(L, -1))
                        {
                            lua_pushvalue(L, 1);
                            lua_pushvalue(L, 2);
                            lua_pcall(L, 2, 1, 0);
                        }
                        else if (lua_istable(L, -1))
                            lua_getfield(L, -1, key);
                        else
                            lua_pushnil(L);
                    }
                    else
                        lua_pushnil(L);
                }
                else if (lua_istable(L, -1))
                {
                    lua_pushvalue(L, 2);
                    lua_rawget(L, -2);
                }
            }
            else
                lua_pushnil(L);
            lua_insert(L, 1);
            lua_settop(L, 1);
            return 1;
        }
};

class Eluna
{
    public:
        friend class ScriptMgr;
        lua_State* L;

        class LuaEventMap;
        struct LuaEventData;
        class Eluna_CreatureScript;
        class Eluna_GameObjectScript;
        Eluna_CreatureScript* LuaCreatureAI;
        Eluna_GameObjectScript* LuaGameObjectAI;
        LuaEventMap* LuaWorldAI;

        typedef std::map<int, int> ElunaBindingMap;
        typedef UNORDERED_MAP<uint32, ElunaBindingMap> ElunaEntryMap;
        struct ElunaBind;
        std::map<int, std::vector<int> > ServerEventBindings;
        ElunaBind* CreatureEventBindings;
        ElunaBind* CreatureGossipBindings;
        ElunaBind* GameObjectEventBindings;
        ElunaBind* GameObjectGossipBindings;
        ElunaBind* ItemEventBindings;
        ElunaBind* ItemGossipBindings;
        ElunaBind* playerGossipBindings;

        void Initialize();
        void StartEluna(bool restart);
        void AddScriptHooks();
        static void report(lua_State*);
        void Register(uint8 reg, uint32 id, uint32 evt, int func);
        void BeginCall(int fReference);
        bool ExecuteCall(uint8 params, uint8 res);
        void EndCall(uint8 res);
        void LoadDirectory(char* directory, LoadedScripts* scr);
        // Pushes
        void Push(lua_State*); // nil
        void Push(lua_State*, uint64);
        void Push(lua_State*, int64);
        void Push(lua_State*, uint32);
        void Push(lua_State*, int32);
        void Push(lua_State*, bool);
        void Push(lua_State*, float);
        void Push(lua_State*, double);
        void Push(lua_State*, const char*);
        void Push(lua_State*, std::string);
        template<typename T> void Push(lua_State* L, T const* ptr)
        {
            ElunaTemplate<T>::push(L, ptr);
        }
        template<> void Eluna::Push<Unit>(lua_State* L, Unit const* unit)
        {
            switch (unit->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, unit->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, unit->ToPlayer());
                    break;
                default:
                    ElunaTemplate<Unit>::push(L, unit);
            }
        }
        template<> void Eluna::Push<WorldObject>(lua_State*, WorldObject const* obj)
        {
            switch (obj->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, obj->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, obj->ToPlayer());
                    break;
                case TYPEID_GAMEOBJECT:
                    Push(L, obj->ToGameObject());
                    break;
                case TYPEID_CORPSE:
                    Push(L, obj->ToCorpse());
                    break;
                default:
                    ElunaTemplate<WorldObject>::push(L, obj);
            }
        }
        template<> void Eluna::Push<Object>(lua_State* L, Object const* obj)
        {
            switch (obj->GetTypeId())
            {
                case TYPEID_UNIT:
                    Push(L, obj->ToCreature());
                    break;
                case TYPEID_PLAYER:
                    Push(L, obj->ToPlayer());
                    break;
                case TYPEID_GAMEOBJECT:
                    Push(L, obj->ToGameObject());
                    break;
                case TYPEID_CORPSE:
                    Push(L, obj->ToCorpse());
                    break;
                default:
                    ElunaTemplate<Object>::push(L, obj);
            }
        }

        // Checks
        WorldPacket* CHECK_PACKET(lua_State* L, int narg);
        Object* CHECK_OBJECT(lua_State* L, int narg);
        WorldObject* CHECK_WORLDOBJECT(lua_State* L, int narg);
        Unit* CHECK_UNIT(lua_State* L, int narg);
        Player* CHECK_PLAYER(lua_State* L, int narg);
        Creature* CHECK_CREATURE(lua_State* L, int narg);
        GameObject* CHECK_GAMEOBJECT(lua_State* L, int narg);
        Corpse* CHECK_CORPSE(lua_State* L, int narg);
        Quest* CHECK_QUEST(lua_State* L, int narg);
        Spell* CHECK_SPELL(lua_State* L, int narg);
        uint64 CHECK_ULONG(lua_State* L, int narg);
        int64 CHECK_LONG(lua_State* L, int narg);
        Item* CHECK_ITEM(lua_State* L, int narg);

        // Creates new binding stores
        Eluna()
        {
            L = NULL;
            LuaCreatureAI = NULL;
            LuaGameObjectAI = NULL;
            LuaWorldAI = NULL;

            for (int i = 0; i < SERVER_EVENT_COUNT; ++i)
            {
                std::vector<int> _vector;
                ServerEventBindings.insert(std::pair<int, std::vector<int> >(i, _vector));
            }
            CreatureEventBindings = new ElunaBind;
            CreatureGossipBindings = new ElunaBind;
            GameObjectEventBindings = new ElunaBind;
            GameObjectGossipBindings = new ElunaBind;
            ItemEventBindings = new ElunaBind;
            ItemGossipBindings = new ElunaBind;
            playerGossipBindings = new ElunaBind;
        }

        ~Eluna()
        {
            for (std::map<int, std::vector<int> >::iterator itr = ServerEventBindings.begin(); itr != ServerEventBindings.end(); ++itr)
            {
                for (std::vector<int>::iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }
            ServerEventBindings.clear();
            CreatureEventBindings->Clear();
            CreatureGossipBindings->Clear();
            GameObjectEventBindings->Clear();
            GameObjectGossipBindings->Clear();
            ItemEventBindings->Clear();
            ItemGossipBindings->Clear();
            playerGossipBindings->Clear();

            lua_close(L); // Closing
        }

        struct ElunaBind
        {
            void Clear(); // unregisters all registered functions and clears all registered events from the bind std::maps (reset)
            void Insert(uint32 entryId, uint32 eventId, int funcRef); // Inserts a new registered event

            // Gets the function ref of an entry for an event
            int GetBind(uint32 entryId, uint32 eventId)
            {
                ElunaEntryMap::iterator itr = Bindings.find(entryId);
                if (itr == Bindings.end())
                    return 0;

                return itr->second[eventId];
            }

            // Gets the binding std::map containing all registered events with the function refs for the entry
            ElunaBindingMap* GetBindMap(uint32 entryId)
            {
                ElunaEntryMap::iterator itr = Bindings.find(entryId);
                if (itr == Bindings.end())
                    return NULL;

                return &itr->second;
            }

            ElunaEntryMap Bindings; // Binding store Bindings[entryId][eventId] = funcRef;
        };

        struct ObjectGUIDCheck
        {
            ObjectGUIDCheck(ObjectGuid GUID) : _GUID(GUID) { }
            bool operator()(WorldObject* object)
            {
                return object->GetObjectGuid() == _GUID;
            }

            ObjectGuid _GUID;
        };

        // Binary predicate to sort WorldObjects based on the distance to a reference WorldObject
        struct ObjectDistanceOrderPred
        {
            ObjectDistanceOrderPred(WorldObject const* pRefObj, bool ascending = true) : m_refObj(pRefObj), m_ascending(ascending) { }
            bool operator()(WorldObject const* pLeft, WorldObject const* pRight) const
            {
                return m_ascending ? m_refObj->GetDistanceOrder(pLeft, pRight) : !m_refObj->GetDistanceOrder(pLeft, pRight);
            }

            WorldObject const* m_refObj;
            const bool m_ascending;
        };

        // Doesn't get self
        struct WorldObjectInRangeCheck
        {
            WorldObjectInRangeCheck(bool nearest, WorldObject const* obj, float range,
                                    TypeID typeId = TYPEID_OBJECT, uint32 entry = 0) : i_nearest(nearest),
                i_obj(obj), i_range(range), i_typeId(typeId), i_entry(entry) {}
            WorldObject const& GetFocusObject() const { return *i_obj; }
            bool operator()(WorldObject* u)
            {
                if (i_typeId && u->GetTypeId() != i_typeId)
                    return false;
                if (i_entry && u->GetEntry() != i_entry)
                    return false;
                if (i_obj->GetObjectGuid() == u->GetObjectGuid())
                    return false;
                if (!i_obj->IsWithinDistInMap(u, i_range))
                    return false;
                if (Unit* unit = u->ToUnit())
                    if (!unit->isAlive())
                        return false;
                if (i_nearest)
                    i_range = i_obj->GetDistance(u);
                return true;
            }

            WorldObject const* i_obj;
            float i_range;
            TypeID i_typeId;
            uint32 i_entry;
            bool i_nearest;

            WorldObjectInRangeCheck(WorldObjectInRangeCheck const&);
        };
};
#define sEluna MaNGOS::Singleton<Eluna>::Instance()

class Eluna::LuaEventMap
{
    public:
        LuaEventMap() { }
        ~LuaEventMap() { ScriptEventsReset(); }

        struct eventData
        {
            int funcRef; uint32 delay; uint32 calls;
            eventData(int _funcRef, uint32 _delay, uint32 _calls) :
                funcRef(_funcRef), delay(_delay), calls(_calls) {}
        };

        typedef std::multimap<uint32, eventData> EventStore;// Not to use multimap? Can same function ref ID be used multiple times?

        virtual void OnScriptEvent(int funcRef, uint32 delay, uint32 calls) { }

        static void ScriptEventsResetAll(); // Unregisters and stops all timed events
        void ScriptEventsReset();
        void ScriptEventCancel(int funcRef);
        void ScriptEventsExecute();

        // Gets the event map saved for a guid
        static LuaEventMap* GetEvents(WorldObject* obj)
        {
            if (!obj)
                return NULL;
            UNORDERED_MAP<uint64, LuaEventMap*>::const_iterator it = LuaEventMaps.find(obj->GetGUIDLow());
            if (it != LuaEventMaps.end())
                return it->second;
            return NULL;
        }

        void ScriptEventsUpdate(uint32 time)
        {
            _time += time;
        }

        bool ScriptEventsEmpty() const
        {
            return _eventMap.empty();
        }

        void ScriptEventCreate(int funcRef, uint32 delay, uint32 calls)
        {
            _eventMap.insert(EventStore::value_type(_time + delay, eventData(funcRef, delay, calls)));
        }

        static UNORDERED_MAP<uint64, LuaEventMap*> LuaEventMaps; // Creature and gameobject timed events

    private:
        EventStore _eventMap;
        uint32 _time;
};

/*class Eluna::Eluna_WorldScript : public WorldScript, public Eluna::LuaEventMap
{
public:
    Eluna_WorldScript() : WorldScript("SmartEluna_WorldScript"), LuaEventMap() { }
    ~Eluna_WorldScript() { }

    void OnOpenStateChange(bool open)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_OPEN_STATE_CHANGE].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_OPEN_STATE_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_OPEN_STATE_CHANGE);
            sEluna.Push(sEluna.L, open);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnConfigLoad(bool reload)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_CONFIG_LOAD].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_CONFIG_LOAD].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_CONFIG_LOAD);
            sEluna.Push(sEluna.L, reload);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnMotdChange(std::string& newMotd)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_MOTD_CHANGE].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_MOTD_CHANGE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_MOTD_CHANGE);
            sEluna.Push(sEluna.L, newMotd);
            sEluna.ExecuteCall(2, 0);
        }
    }

    void OnShutdownInitiate(ShutdownExitCode code, ShutdownMask mask)
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN_INIT].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN_INIT].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_SHUTDOWN_INIT);
            sEluna.Push(sEluna.L, code);
            sEluna.Push(sEluna.L, mask);
            sEluna.ExecuteCall(3, 0);
        }
    }

    void OnShutdownCancel()
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN_CANCEL].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN_CANCEL].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_SHUTDOWN_CANCEL);
            sEluna.ExecuteCall(1, 0);
        }
    }

    void OnUpdate(uint32 diff)
    {
        ScriptEventsUpdate(diff);
        ScriptEventsExecute();
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_UPDATE].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_UPDATE].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_UPDATE);
            sEluna.Push(sEluna.L, diff);
            sEluna.ExecuteCall(2, 0);
        }
    }
    // executed when a  timed event fires
    void OnScriptEvent(int funcRef, uint32 delay, uint32 calls)
    {
        sEluna.BeginCall(funcRef);
        sEluna.Push(sEluna.L, funcRef);
        sEluna.Push(sEluna.L, delay);
        sEluna.Push(sEluna.L, calls);
        sEluna.ExecuteCall(3, 0);
    }

    void OnStartup()
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_STARTUP].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_STARTUP].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_STARTUP);
            sEluna.ExecuteCall(1, 0);
        }
    }

    void OnShutdown()
    {
        for (std::vector<int>::const_iterator itr = sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN].begin();
            itr != sEluna.ServerEventBindings[WORLD_EVENT_ON_SHUTDOWN].end(); ++itr)
        {
            sEluna.BeginCall((*itr));
            sEluna.Push(sEluna.L, WORLD_EVENT_ON_SHUTDOWN);
            sEluna.ExecuteCall(1, 0);
        }
    }
};*/
class Eluna::Eluna_CreatureScript
{
    public:

        struct ScriptReactorAI : public ReactorAI
        {
            ScriptReactorAI(Creature* creature) : ReactorAI(creature) { }
            ~ScriptReactorAI() { }

            // Called at World update tick
            void UpdateAI(uint32 const diff)
            {
                ReactorAI::UpdateAI(diff);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_AIUPDATE);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_AIUPDATE);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, diff);
                sEluna.ExecuteCall(3, 0);
            }

            // Called for reaction at enter to combat if not in combat yet (enemy can be NULL)
            // Called at creature aggro either by MoveInLOS or Attack Start
            void EnterCombat(Unit* target)
            {
                ReactorAI::EnterCombat(target);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_ENTER_COMBAT);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_ENTER_COMBAT);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, target);
                sEluna.ExecuteCall(3, 0);
            }

            // Called at any Damage from any attacker (before damage apply)
            void DamageTaken(Unit* attacker, uint32& damage)
            {
                ReactorAI::DamageTaken(attacker, damage);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_DAMAGE_TAKEN);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_DAMAGE_TAKEN);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, attacker);
                sEluna.Push(sEluna.L, damage);
                sEluna.ExecuteCall(4, 0);
            }

            // Called at creature death
            void JustDied(Unit* killer)
            {
                ReactorAI::JustDied(killer);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_DIED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_DIED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, killer);
                sEluna.ExecuteCall(3, 0);
            }

            // Called at creature killing another unit
            void KilledUnit(Unit* victim)
            {
                ReactorAI::KilledUnit(victim);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_TARGET_DIED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_TARGET_DIED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, victim);
                sEluna.ExecuteCall(3, 0);
            }

            // Called when the creature summon successfully other creature
            void JustSummoned(Creature* summon)
            {
                ReactorAI::JustSummoned(summon);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_JUST_SUMMONED_CREATURE);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, summon);
                sEluna.ExecuteCall(3, 0);
            }

            // Called when a summoned creature is despawned
            void SummonedCreatureDespawn(Creature* summon)
            {
                ReactorAI::SummonedCreatureDespawn(summon);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SUMMONED_CREATURE_DESPAWN);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, summon);
                sEluna.ExecuteCall(3, 0);
            }

            // Called when hit by a spell
            void SpellHit(Unit* caster, SpellEntry const* spell)
            {
                ReactorAI::SpellHit(caster, spell);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_HIT_BY_SPELL);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_HIT_BY_SPELL);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, caster);
                sEluna.Push(sEluna.L, spell->Id);           // Pass spell object?
                sEluna.ExecuteCall(4, 0);
            }

            // Called when spell hits a target
            void SpellHitTarget(Unit* target, SpellEntry const* spell)
            {
                ReactorAI::SpellHitTarget(target, spell);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SPELL_HIT_TARGET);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SPELL_HIT_TARGET);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, target);
                sEluna.Push(sEluna.L, spell->Id);           // Pass spell object?
                sEluna.ExecuteCall(4, 0);
            }

            // Called at waypoint reached or PointMovement end
            void MovementInform(uint32 type, uint32 id)
            {
                ReactorAI::MovementInform(type, id);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_REACH_WP);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_REACH_WP);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, type);
                sEluna.Push(sEluna.L, id);
                sEluna.ExecuteCall(4, 0);
            }

            // Called when AI is temporarily replaced or put back when possess is applied or removed
            /*
            void OnPossess(bool apply)
            {
                ReactorAI::OnPossess(apply);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_POSSESS);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_POSSESS);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, apply);
                sEluna.ExecuteCall(3, 0);
            }*/

            // Called at creature reset either by death or evade
            /*void Reset()
            {
                ReactorAI::Reset();
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_RESET);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_RESET);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.ExecuteCall(2, 0);
            }*/

            // Called before EnterCombat even before the creature is in combat.
            void AttackStart(Unit* target)
            {
                ReactorAI::AttackStart(target);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_PRE_COMBAT);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_PRE_COMBAT);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, target);
                sEluna.ExecuteCall(3, 0);
            }

            // Called in Creature::Update when deathstate = DEAD. Inherited classes may maniuplate the ability to respawn based on scripted events.
            /*
            bool CanRespawn()
            {
                ReactorAI::CanRespawn();
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_CAN_RESPAWN);
                if (!bind)
                    return true;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_CAN_RESPAWN);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.ExecuteCall(2, 0);
                return true;
            }*/

            // Called for reaction at stopping attack at no attackers or targets
            void EnterEvadeMode()
            {
                ReactorAI::EnterEvadeMode();
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_LEAVE_COMBAT);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_LEAVE_COMBAT);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.ExecuteCall(2, 0);
            }

            // Called when the creature is summoned successfully by other creature
            /*void IsSummonedBy(Unit* summoner)
            {
                ReactorAI::IsSummonedBy(summoner);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SUMMONED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SUMMONED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, summoner);
                sEluna.ExecuteCall(3, 0);
            }*/

            /*void SummonedCreatureDies(Creature* summon, Unit* killer)
            {
                ReactorAI::SummonedCreatureDies(summon, killer);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SUMMONED_CREATURE_DIED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, summon);
                sEluna.Push(sEluna.L, killer);
                sEluna.ExecuteCall(4, 0);
            }*/

            // Called when the creature is target of hostile action: swing, hostile spell landed, fear/etc)
            void AttackedBy(Unit* attacker)
            {
                ReactorAI::AttackedBy(attacker);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_ATTACKED_AT);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_ATTACKED_AT);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, attacker);
                sEluna.ExecuteCall(3, 0);
            }

            // Called when creature is spawned or respawned (for reseting variables)
            void JustRespawned()
            {
                ReactorAI::JustRespawned();
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SPAWN);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SPAWN);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.ExecuteCall(2, 0);
            }

            /*void OnCharmed(bool apply)
            {
                ReactorAI::OnCharmed(apply);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_CHARMED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_CHARMED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, apply);
                sEluna.ExecuteCall(3, 0);
            }*/

            // Called at reaching home after evade
            void JustReachedHome()
            {
                ReactorAI::JustReachedHome();
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_REACH_HOME);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_REACH_HOME);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.ExecuteCall(2, 0);
            }

            // Called at text emote receive from player
            void ReceiveEmote(Player* player, uint32 emoteId)
            {
                ReactorAI::ReceiveEmote(player, emoteId);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_RECEIVE_EMOTE);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_RECEIVE_EMOTE);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, player);
                sEluna.Push(sEluna.L, emoteId);
                sEluna.ExecuteCall(4, 0);
            }

            // Called when owner takes damage
            /*void OwnerAttackedBy(Unit* attacker)
            {
                ReactorAI::OwnerAttackedBy(attacker);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_OWNER_ATTACKED_AT);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_OWNER_ATTACKED_AT);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, attacker);
                sEluna.ExecuteCall(3, 0);
            }*/

            // Called when owner attacks something
            /*void OwnerAttacked(Unit* target)
            {
                ReactorAI::OwnerAttacked(target);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_OWNER_ATTACKED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_OWNER_ATTACKED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, target);
                sEluna.ExecuteCall(3, 0);
            }*/

            // called when the corpse of this creature gets removed
            void CorpseRemoved(uint32& respawnDelay)
            {
                ReactorAI::CorpseRemoved(respawnDelay);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_CORPSE_REMOVED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_CORPSE_REMOVED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, respawnDelay);
                sEluna.ExecuteCall(3, 0);
            }

            /*void PassengerBoarded(Unit* passenger, int8 seatId, bool apply)
            {
                ReactorAI::PassengerBoarded(passenger, seatId, apply);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_PASSANGER_BOARDED);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_PASSANGER_BOARDED);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, passenger);
                sEluna.Push(sEluna.L, seatId);
                sEluna.Push(sEluna.L, apply);
                sEluna.ExecuteCall(5, 0);
            }*/

            /*void OnSpellClick(Unit* clicker, bool& result)
            {
                ReactorAI::OnSpellClick(clicker, result);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_SPELL_CLICK);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_SPELL_CLICK);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, clicker);
                sEluna.Push(sEluna.L, result);
                sEluna.ExecuteCall(4, 0);
            }*/

            void MoveInLineOfSight(Unit* who)
            {
                ReactorAI::MoveInLineOfSight(who);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_MOVE_IN_LOS);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_MOVE_IN_LOS);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, who);
                sEluna.ExecuteCall(3, 0);
            }

            // Called if IsVisible(Unit* who) is true at each who move, reaction at visibility zone enter
            /*void MoveInLineOfSight_Safe(Unit* who)
            {
                ReactorAI::MoveInLineOfSight_Safe(who);
                int bind = sEluna.CreatureEventBindings->GetBind(m_creature->GetEntry(), CREATURE_EVENT_ON_VISIBLE_MOVE_IN_LOS);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, CREATURE_EVENT_ON_VISIBLE_MOVE_IN_LOS);
                sEluna.Push(sEluna.L, m_creature);
                sEluna.Push(sEluna.L, who);
                sEluna.ExecuteCall(3, 0);
            }*/
        };

        ReactorAI* GetAI(Creature* creature)
        {
            if (!sEluna.CreatureEventBindings->GetBindMap(creature->GetEntry()))
                return NULL;

            ScriptReactorAI* luaReactorAI = new ScriptReactorAI(creature);
            return luaReactorAI;
        }
};

class Eluna::Eluna_GameObjectScript
{
    public:

        struct ScriptGameObjectAI : public GameObjectAI, public Eluna::LuaEventMap
        {
            ScriptGameObjectAI(GameObject* _go) : GameObjectAI(_go), LuaEventMap() { }
            ~ScriptGameObjectAI()
            {
                LuaEventMap::LuaEventMaps.erase(go->GetGUIDLow());
            }

            void UpdateAI(uint32 const diff)
            {
                ScriptEventsUpdate(diff);
                ScriptEventsExecute();
                int bind = sEluna.GameObjectEventBindings->GetBind(go->GetEntry(), GAMEOBJECT_EVENT_ON_AIUPDATE);
                if (!bind)
                    return;
                sEluna.BeginCall(bind);
                sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_AIUPDATE);
                sEluna.Push(sEluna.L, go);
                sEluna.Push(sEluna.L, diff);
                sEluna.ExecuteCall(3, 0);
            }

            // executed when a timed event fires
            void OnScriptEvent(int funcRef, uint32 delay, uint32 calls)
            {
                sEluna.BeginCall(funcRef);
                sEluna.Push(sEluna.L, funcRef);
                sEluna.Push(sEluna.L, delay);
                sEluna.Push(sEluna.L, calls);
                sEluna.Push(sEluna.L, go);
                sEluna.ExecuteCall(4, 0);
            }

            void Reset()
            {
                sEluna.BeginCall(sEluna.GameObjectEventBindings->GetBind(go->GetEntry(), GAMEOBJECT_EVENT_ON_RESET));
                sEluna.Push(sEluna.L, GAMEOBJECT_EVENT_ON_RESET);
                sEluna.Push(sEluna.L, go);
                sEluna.ExecuteCall(2, 0);
            }
        };

        GameObjectAI* GetAI(GameObject* gameObject) const
        {
            if (!sEluna.GameObjectEventBindings->GetBindMap(gameObject->GetEntry()))
                return NULL;

            ScriptGameObjectAI* luaGameObjectAI = new ScriptGameObjectAI(gameObject);
            LuaEventMap::LuaEventMaps[gameObject->GetGUIDLow()] = luaGameObjectAI;
            return luaGameObjectAI;
        }
};

struct Eluna::LuaEventData : public BasicEvent, public Eluna::LuaEventMap::eventData
{
    static UNORDERED_MAP<int, LuaEventData*> LuaEvents;
    static UNORDERED_MAP<uint64, std::set<int> > EventIDs;
    Unit* _unit;
    uint64 GUID;

    LuaEventData(int funcRef, uint32 delay, uint32 calls, Unit* unit) :
        _unit(unit), GUID(unit->GetGUIDLow()), Eluna::LuaEventMap::eventData(funcRef, delay, calls)
    {
        LuaEvents[funcRef] = this;
        EventIDs[unit->GetGUIDLow()].insert(funcRef);
    }

    ~LuaEventData()
    {
        luaL_unref(sEluna.L, LUA_REGISTRYINDEX, funcRef);
        LuaEvents.erase(funcRef);
        EventIDs[GUID].erase(funcRef);
    }

    static void RemoveAll()
    {
        for (UNORDERED_MAP<uint64, std::set<int> >::const_iterator it = EventIDs.begin(); it != EventIDs.end(); ++it)
        {
            if (it->second.empty())
                continue;
            for (std::set<int>::const_iterator itr = it->second.begin(); itr != it->second.end(); ++itr)
            {
                if (LuaEvents.find(*itr) == LuaEvents.end())
                    continue;
                if (LuaEvents[*itr]->_unit)
                {
                    LuaEvents[*itr]->_unit->m_Events.KillAllEvents(true);
                    break;
                }
            }
        }
        LuaEvents.clear();
        EventIDs.clear();
    }

    static void RemoveAll(Unit* unit)
    {
        if (!unit)
            return;
        unit->m_Events.KillAllEvents(true); // should delete the objects
        for (std::set<int>::const_iterator it = EventIDs[unit->GetGUIDLow()].begin(); it != EventIDs[unit->GetGUIDLow()].end(); ++it)
            LuaEvents.erase(*it); // deletes pointers
        EventIDs.erase(unit->GetGUIDLow());
    }

    static void Remove(uint32 guid, int eventID)
    {
        if (LuaEvents.find(eventID) != LuaEvents.end())
        {
            LuaEvents[eventID]->to_Abort = true; // delete on next cycle
            LuaEvents.erase(eventID);
        }
        EventIDs[guid].erase(eventID);
    }

    bool Execute(uint64 time, uint32 diff) // Should NEVER execute on dead events
    {
        sEluna.BeginCall(funcRef);
        sEluna.Push(sEluna.L, funcRef);
        sEluna.Push(sEluna.L, delay);
        sEluna.Push(sEluna.L, calls);
        sEluna.Push(sEluna.L, _unit);
        sEluna.ExecuteCall(4, 0);
        if (calls && !--calls) // dont repeat anymore
        {
            Remove(GUID, funcRef);
            return true; // destory event
        }
        _unit->m_Events.AddEvent(this, _unit->m_Events.CalculateTime(delay));
        return false; // dont destory event
    }
};

class LuaTaxiMgr
{
    private:
        static uint32 nodeId;
    public:
        static void StartTaxi(Player* player, uint32 pathid);
        static uint32 AddPath(std::list<TaxiPathNodeEntry> nodes, uint32 mountA, uint32 mountH, uint32 price = 0, uint32 pathId = 0);
};
#endif

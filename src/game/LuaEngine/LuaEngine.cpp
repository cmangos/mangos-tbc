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

#include "LuaEngine.h"
#include "HookMgr.h"

INSTANTIATE_SINGLETON_1(Eluna);

#if PLATFORM == PLATFORM_UNIX
#include <dirent.h>
#endif

template<typename T> const char* GetTName() { return NULL; }
template<> const char* GetTName<Object>() { return "Object"; }
template<> const char* GetTName<WorldObject>() { return "WorldObject"; }
template<> const char* GetTName<Unit>() { return "Unit"; }
template<> const char* GetTName<Player>() { return "Player"; }
template<> const char* GetTName<Creature>() { return "Creature"; }
template<> const char* GetTName<GameObject>() { return "GameObject"; }
template<> const char* GetTName<Group>() { return "Group"; }
template<> const char* GetTName<Guild>() { return "Guild"; }
template<> const char* GetTName<QueryResult>() { return "QueryResult"; }
template<> const char* GetTName<Aura>() { return "Aura"; }
template<> const char* GetTName<WorldPacket>() { return "WorldPacket"; }
template<> const char* GetTName<Item>() { return "Item"; }
template<> const char* GetTName<Spell>() { return "Spell"; }
template<> const char* GetTName<Quest>() { return "Quest"; }
template<> const char* GetTName<Map>() { return "Map"; }
template<> const char* GetTName<Corpse>() { return "Corpse"; }
template<> const char* GetTName<Weather>() { return "Weather"; }

extern void RegisterFunctions(lua_State* L);

void Eluna::Initialize()
{
    // Check config file for eluna is enabled or disabled
    if (sWorld.getConfig(CONFIG_BOOL_ELUNA_ENABLED))
        sEluna.StartEluna(false);
    else
        sLog.outError("[Eluna]: LuaEngine is Disabled. (If you want to use it please set config in 'mangosd.conf')");
}

void Eluna::StartEluna(bool restart)
{
    if (restart)
    {
        sHookMgr.OnEngineRestart();
        sLog.outString("[Eluna]: Restarting Lua Engine");

        if (L)
        {
            // Unregisters and stops all timed events
            LuaEventMap::ScriptEventsResetAll();
            LuaEventData::RemoveAll();

            // Remove bindings
            for (std::map<int, std::vector<int> >::iterator itr = ServerEventBindings.begin(); itr != ServerEventBindings.end(); ++itr)
            {
                for (std::vector<int>::const_iterator it = itr->second.begin(); it != itr->second.end(); ++it)
                    luaL_unref(L, LUA_REGISTRYINDEX, (*it));
                itr->second.clear();
            }
            CreatureEventBindings->Clear();
            CreatureGossipBindings->Clear();
            GameObjectEventBindings->Clear();
            GameObjectGossipBindings->Clear();
            ItemEventBindings->Clear();
            ItemGossipBindings->Clear();
            playerGossipBindings->Clear();

            lua_close(L);
        }
    }
    else
        AddScriptHooks();

    L = luaL_newstate();
    sLog.outString();
    sLog.outString("[Eluna]: Lua Engine loaded.");
    sLog.outString();

    LoadedScripts loadedScripts;
    LoadDirectory("lua_scripts", &loadedScripts);
    luaL_openlibs(L);
    // Register functions here
    RegisterFunctions(L);

    uint32 count = 0;
    char filename[200];
    for (std::set<std::string>::const_iterator itr = loadedScripts.luaFiles.begin(); itr !=  loadedScripts.luaFiles.end(); ++itr)
    {
        strcpy(filename, itr->c_str());
        if (luaL_loadfile(L, filename) != 0)
        {
            sLog.outErrorEluna("[Eluna]: Error loading file `%s`.", itr->c_str());
            report(L);
        }
        else
        {
            int err = lua_pcall(L, 0, 0, 0);
            if (err != 0 && err == LUA_ERRRUN)
            {
                sLog.outErrorEluna("[Eluna]: Error loading file `%s`.", itr->c_str());
                report(L);
            }
        }
        ++count;
    }

    /*
    if (restart)
    {
        //! Iterate over every supported source type (creature and gameobject)
        //! Not entirely sure how this will affect units in non-loaded grids.
        {
            HashMapHolder<Creature>::ReadGuard g(HashMapHolder<Creature>::GetLock());
            HashMapHolder<Creature>::MapType& m = HashMapHolder<Creature>::GetContainer();
            for (HashMapHolder<Creature>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            {
                if (itr->second->IsInWorld()) // must check?
                    // if(sEluna.CreatureEventBindings->GetBindMap(iter->second->GetEntry())) // update all AI or just Eluna?
                        itr->second->AIM_Initialize();
            }
        }

        {
            HashMapHolder<GameObject>::ReadGuard g(HashMapHolder<GameObject>::GetLock());
            HashMapHolder<GameObject>::MapType& m = HashMapHolder<GameObject>::GetContainer();
            for (HashMapHolder<GameObject>::MapType::const_iterator itr = m.begin(); itr != m.end(); ++itr)
            {
                if (itr->second->IsInWorld()) // must check?
                    // if(sEluna.GameObjectEventBindings->GetBindMap(iter->second->GetEntry())) // update all AI or just Eluna?
                        itr->second->AIM_Initialize();
            }
        }
    }
    */

    sLog.outString("[Eluna]: Loaded %u Lua scripts..", count);
    sLog.outString();
}

// Loads lua scripts from given directory
void Eluna::LoadDirectory(char* Dirname, LoadedScripts* lscr)
{
#ifdef WIN32
    HANDLE hFile;
    WIN32_FIND_DATA FindData;
    memset(&FindData, 0, sizeof(FindData));
    char SearchName[MAX_PATH];

    strcpy(SearchName, Dirname);
    strcat(SearchName, "\\*.*");

    hFile = FindFirstFile(SearchName, &FindData);
    if (hFile == INVALID_HANDLE_VALUE)
    {
        sLog.outErrorEluna("[Eluna]: Error No `lua_scripts` directory found! Creating a 'lua_scripts' directory and restarting Eluna.");
        CreateDirectory("lua_scripts", NULL);
        StartEluna(true);
        return;
    }

    FindNextFile(hFile, &FindData);
    while (FindNextFile(hFile, &FindData))
    {
        if (FindData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
        {
            strcpy(SearchName, Dirname);
            strcat(SearchName, "\\");
            strcat(SearchName, FindData.cFileName);
            LoadDirectory(SearchName, lscr);
        }
        else
        {
            std::string fname = Dirname;
            fname += "\\";
            fname += FindData.cFileName;
            size_t len = strlen(fname.c_str());
            int i = 0;
            char ext[MAX_PATH];
            while (len > 0)
            {
                ext[i++] = fname[--len];
                if (fname[len] == '.')
                    break;
            }
            ext[i++] = '\0';
            if (!_stricmp(ext, "aul."))
            {
                sLog.outDebug("[Eluna]: Load File: %s", fname.c_str());
                lscr->luaFiles.insert(fname);
            }
        }
    }
    FindClose(hFile);
#else
    char* dir = strrchr(Dirname, '/');
    if (strcmp(Dirname, "..") == 0 || strcmp(Dirname, ".") == 0)
        return;

    if (dir && (strcmp(dir, "/..") == 0 || strcmp(dir, "/.") == 0 || strcmp(dir, "/.svn") == 0))
        return;

    struct dirent** list;
    int fileCount = scandir(Dirname, &list, 0, 0);

    if (fileCount <= 0 || !list)
        return;

    struct stat attributes;
    bool error;
    while (fileCount--)
    {
        char _path[200];
        sprintf(_path, "%s/%s", Dirname, list[fileCount]->d_name);
        if (stat(_path, &attributes) == -1)
        {
            error = true;
            sLog.outErrorEluna("[Eluna]: Error opening `%s`", _path);
        }
        else
            error = false;

        if (!error && S_ISDIR(attributes.st_mode))
            LoadDirectory((char*)_path, lscr);
        else
        {
            char* ext = strrchr(list[fileCount]->d_name, '.');
            if (ext && !strcmp(ext, ".lua"))
                lscr->luaFiles.insert(_path);
        }
        free(list[fileCount]);
    }
    free(list);
#endif
}

void Eluna::report(lua_State* L)
{
    const char* msg = lua_tostring(L, -1);
    while (msg)
    {
        lua_pop(L, -1);
        sLog.outErrorEluna("\t%s\n", msg);
        msg = lua_tostring(L, -1);
    }
}

void Eluna::BeginCall(int fReference)
{
    lua_settop(L, 0); // stack should be empty
    lua_rawgeti(L, LUA_REGISTRYINDEX, (fReference));
}

bool Eluna::ExecuteCall(uint8 params, uint8 res)
{
    bool ret = true;
    int top = lua_gettop(L);

    if (lua_type(L, top - params) == LUA_TFUNCTION) // is function
    {
        if (lua_pcall(L, params, res, 0))
        {
            report(L);
            ret = false;
        }
    }
    else
    {
        ret = false;
        if (params > 0)
        {
            for (int i = top; i >= (top - params); i--)
            {
                if (!lua_isnone(L, i))
                    lua_remove(L, i);
            }
        }
    }
    return ret;
}

void Eluna::EndCall(uint8 res)
{
    for (int i = res; i > 0; i--)
    {
        if (!lua_isnone(L, res))
            lua_remove(L, res);
    }
}

/* Pushes */
void Eluna::Push(lua_State* L)
{
    lua_pushnil(L);
}
void Eluna::Push(lua_State* L, uint64 l)
{
    std::ostringstream ss;
    ss << "0x" << std::hex << l;
    sEluna.Push(L, ss.str());
}
void Eluna::Push(lua_State* L, int64 l)
{
    std::ostringstream ss;
    if (l < 0)
        ss << "-0x" << std::hex << -l;
    else
        ss << "0x" << std::hex << l;
    sEluna.Push(L, ss.str());
}
void Eluna::Push(lua_State* L, uint32 u)
{
    lua_pushunsigned(L, u);
}
void Eluna::Push(lua_State* L, int32 i)
{
    lua_pushinteger(L, i);
}
void Eluna::Push(lua_State* L, double d)
{
    lua_pushnumber(L, d);
}
void Eluna::Push(lua_State* L, float f)
{
    lua_pushnumber(L, f);
}
void Eluna::Push(lua_State* L, bool b)
{
    lua_pushboolean(L, b);
}
void Eluna::Push(lua_State* L, std::string str)
{
    lua_pushstring(L, str.c_str());
}
void Eluna::Push(lua_State* L, const char* str)
{
    lua_pushstring(L, str);
}

Object* Eluna::CHECK_OBJECT(lua_State* L, int narg)
{
    return ElunaTemplate<Object>::check(L, narg);
}

WorldObject* Eluna::CHECK_WORLDOBJECT(lua_State* L, int narg)
{
    return ElunaTemplate<WorldObject>::check(L, narg);
}

Unit* Eluna::CHECK_UNIT(lua_State* L, int narg)
{
    WorldObject* obj = CHECK_WORLDOBJECT(L, narg);
    if (!obj)
        return NULL;
    return obj->ToUnit();
}

Player* Eluna::CHECK_PLAYER(lua_State* L, int narg)
{
    WorldObject* obj = CHECK_WORLDOBJECT(L, narg);
    if (!obj)
        return NULL;
    return obj->ToPlayer();
}

Creature* Eluna::CHECK_CREATURE(lua_State* L, int narg)
{
    WorldObject* obj = CHECK_WORLDOBJECT(L, narg);
    if (!obj)
        return NULL;
    return obj->ToCreature();
}

GameObject* Eluna::CHECK_GAMEOBJECT(lua_State* L, int narg)
{
    WorldObject* obj = CHECK_WORLDOBJECT(L, narg);
    if (!obj)
        return NULL;
    return obj->ToGameObject();
}

Corpse* Eluna::CHECK_CORPSE(lua_State* L, int narg)
{
    WorldObject* obj = CHECK_WORLDOBJECT(L, narg);
    if (!obj)
        return NULL;
    return obj->ToCorpse();
}

WorldPacket* Eluna::CHECK_PACKET(lua_State* L, int narg)
{
    return ElunaTemplate<WorldPacket>::check(L, narg);
}

Quest* Eluna::CHECK_QUEST(lua_State* L, int narg)
{
    return ElunaTemplate<Quest>::check(L, narg);
}

Spell* Eluna::CHECK_SPELL(lua_State* L, int narg)
{
    return ElunaTemplate<Spell>::check(L, narg);
}

uint64 Eluna::CHECK_ULONG(lua_State* L, int narg)
{
    const char* c_str = luaL_optstring(L, narg, "0x0");
    return strtoul(c_str, NULL, 0);
}

int64 Eluna::CHECK_LONG(lua_State* L, int narg)
{
    const char* c_str = luaL_optstring(L, narg, "0x0");
    return strtol(c_str, NULL, 0);
}

Item* Eluna::CHECK_ITEM(lua_State* L, int narg)
{
    return ElunaTemplate<Item>::check(L, narg);
}

// Saves the function reference ID given to the register type's store for given entry under the given event
void Eluna::Register(uint8 regtype, uint32 id, uint32 evt, int functionRef)
{
    switch (regtype)
    {
        case REGTYPE_SERVER:
            if (evt < SERVER_EVENT_COUNT)
            {
                ServerEventBindings[evt].push_back(functionRef);
                return;
            }
            break;

        case REGTYPE_CREATURE:
            if (evt < CREATURE_EVENT_COUNT)
            {
                if (!sObjectMgr.GetCreatureTemplate(id))
                {
                    luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                    return;
                }

                sEluna.CreatureEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_CREATURE_GOSSIP:
            if (evt < GOSSIP_EVENT_COUNT)
            {
                if (!sObjectMgr.GetCreatureTemplate(id))
                {
                    luaL_error(L, "Couldn't find a creature with (ID: %d)!", id);
                    return;
                }

                sEluna.CreatureGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_GAMEOBJECT:
            if (evt < GAMEOBJECT_EVENT_COUNT)
            {
                if (!sObjectMgr.GetGameObjectInfo(id))
                {
                    luaL_error(L, "Couldn't find a gameobject with (ID: %d)!", id);
                    return;
                }

                sEluna.GameObjectEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_GAMEOBJECT_GOSSIP:
            if (evt < GOSSIP_EVENT_COUNT)
            {
                if (!sObjectMgr.GetGameObjectInfo(id))
                {
                    luaL_error(L, "Couldn't find a gameobject with (ID: %d)!", id);
                    return;
                }

                sEluna.GameObjectGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_ITEM:
            if (evt < ITEM_EVENT_COUNT)
            {
                if (!sObjectMgr.GetItemPrototype(id))
                {
                    luaL_error(L, "Couldn't find a item with (ID: %d)!", id);
                    return;
                }

                sEluna.ItemEventBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_ITEM_GOSSIP:
            if (evt < GOSSIP_EVENT_COUNT)
            {
                if (!sObjectMgr.GetItemPrototype(id))
                {
                    luaL_error(L, "Couldn't find a item with (ID: %d)!", id);
                    return;
                }

                sEluna.ItemGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        case REGTYPE_PLAYER_GOSSIP:
            if (evt < GOSSIP_EVENT_COUNT)
            {
                sEluna.playerGossipBindings->Insert(id, evt, functionRef);
                return;
            }
            break;

        default:
            luaL_error(L, "Unknown register type (regtype %d, id %d, event %d)", regtype, id, evt);
            return;
    }
    luaL_error(L, "Unknown event type (regtype %d, id %d, event %d)", regtype, id, evt);
}
void Eluna::ElunaBind::Clear()
{
    for (ElunaEntryMap::iterator itr = Bindings.begin(); itr != Bindings.end(); ++itr)
    {
        for (ElunaBindingMap::const_iterator it = itr->second.begin(); it != itr->second.end(); ++it)
            luaL_unref(sEluna.L, LUA_REGISTRYINDEX, it->second);
        itr->second.clear();
    }
    Bindings.clear();
}
void Eluna::ElunaBind::Insert(uint32 entryId, uint32 eventId, int funcRef)
{
    if (Bindings[entryId][eventId])
    {
        luaL_error(sEluna.L, "A function is already registered for entry (%d) event (%d)", entryId, eventId);
        luaL_unref(sEluna.L, LUA_REGISTRYINDEX, funcRef); // free the unused ref
    }
    else
        Bindings[entryId][eventId] = funcRef;
}

UNORDERED_MAP<uint64, Eluna::LuaEventMap*> Eluna::LuaEventMap::LuaEventMaps;
UNORDERED_MAP<int, Eluna::LuaEventData*> Eluna::LuaEventData::LuaEvents;
UNORDERED_MAP<uint64, std::set<int> > Eluna::LuaEventData::EventIDs;

void Eluna::LuaEventMap::ScriptEventsResetAll()
{
    // GameObject events reset
    if (!LuaEventMaps.empty())
        for (UNORDERED_MAP<uint64, LuaEventMap*>::const_iterator itr = LuaEventMaps.begin(); itr != LuaEventMaps.end(); ++itr)
            if (itr->second)
                itr->second->ScriptEventsReset();
    // Global events reset
    // sEluna.LuaWorldAI->ScriptEventsReset();
}
void Eluna::LuaEventMap::ScriptEventsReset()
{
    _time = 0;
    if (ScriptEventsEmpty())
        return;
    for (EventStore::const_iterator itr = _eventMap.begin(); itr != _eventMap.end();)
    {
        luaL_unref(sEluna.L, LUA_REGISTRYINDEX, itr->second.funcRef);
        ++itr;
    }
    _eventMap.clear();
}
void Eluna::LuaEventMap::ScriptEventCancel(int funcRef)
{
    if (ScriptEventsEmpty())
        return;

    for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
    {
        if (funcRef == itr->second.funcRef)
        {
            luaL_unref(sEluna.L, LUA_REGISTRYINDEX, itr->second.funcRef);
            _eventMap.erase(itr++);
        }
        else
            ++itr;
    }
}
void Eluna::LuaEventMap::ScriptEventsExecute()
{
    if (ScriptEventsEmpty())
        return;

    for (EventStore::iterator itr = _eventMap.begin(); itr != _eventMap.end();)
    {
        if (itr->first > _time)
        {
            ++itr;
            continue;
        }

        OnScriptEvent(itr->second.funcRef, itr->second.delay, itr->second.calls);

        if (itr->second.calls != 1)
        {
            if (itr->second.calls > 1)
                itr->second.calls = itr->second.calls - 1;
            _eventMap.insert(EventStore::value_type(_time + itr->second.delay, itr->second));
        }
        else
            luaL_unref(sEluna.L, LUA_REGISTRYINDEX, itr->second.funcRef);
        _eventMap.erase(itr++);
    }
}

// Lua taxi helper functions
uint32 LuaTaxiMgr::nodeId = 500;
void LuaTaxiMgr::StartTaxi(Player* player, uint32 pathid)
{
    if (pathid >= sTaxiPathNodesByPath.size())
        return;

    TaxiPathNodeList const& path = sTaxiPathNodesByPath[pathid];
    if (path.size() < 2)
        return;

    std::vector<uint32> nodes;
    nodes.resize(2);
    nodes[0] = path[0].index;
    nodes[1] = path[path.size() - 1].index;

    player->ActivateTaxiPathTo(nodes);
}
uint32 LuaTaxiMgr::AddPath(std::list<TaxiPathNodeEntry> nodes, uint32 mountA, uint32 mountH, uint32 price, uint32 pathId)
{
    if (nodes.size() < 2)
        return 0;
    if (!pathId)
        pathId = sTaxiPathNodesByPath.size();
    if (sTaxiPathNodesByPath.size() <= pathId)
        sTaxiPathNodesByPath.resize(pathId + 1);
    sTaxiPathNodesByPath[pathId].clear();
    sTaxiPathNodesByPath[pathId].resize(nodes.size());
    uint32 startNode = nodeId;
    uint32 index = 0;
    for (std::list<TaxiPathNodeEntry>::const_iterator it = nodes.begin(); it != nodes.end(); ++it)
    {
        TaxiPathNodeEntry entry = *it;
        entry.path = pathId;
        TaxiNodesEntry* nodeEntry = new TaxiNodesEntry();
        nodeEntry->ID = index;
        nodeEntry->map_id = entry.mapid;
        nodeEntry->MountCreatureID[0] = mountH;
        nodeEntry->MountCreatureID[1] = mountA;
        nodeEntry->x = entry.x;
        nodeEntry->y = entry.y;
        nodeEntry->z = entry.z;
        sTaxiNodesStore.SetEntry(nodeId, nodeEntry);
        entry.index = nodeId++;
        sTaxiPathNodesByPath[pathId].set(index++, TaxiPathNodePtr(new TaxiPathNodeEntry(entry)));
    }
    if (startNode >= nodeId)
        return 0;
    sTaxiPathSetBySource[startNode][nodeId - 1] = TaxiPathBySourceAndDestination(pathId, price);
    return pathId;
}
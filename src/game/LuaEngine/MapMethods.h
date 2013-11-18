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

#ifndef MAPMETHODS_H
#define MAPMETHODS_H

class LuaMap
{/*
public:
    // :GetName()
    static int GetName(lua_State* L, Map* map)
    {
        if(!map)
            return 0;

        sEluna->PushString(L, map->GetMapName());
        return 1;
    }

    // GetHeight(x, y[, phase])
    static int GetHeight(lua_State* L, Map* map)
    {
        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        uint32 phasemask = luaL_optunsigned(L, 3, 1);

        float z = map->GetHeight(phasemask, x, y, MAX_HEIGHT);
        if (z == INVALID_HEIGHT)
            return 0;
        sEluna->PushFloat(L, z);
        return 1;
    }

    // :GetDifficulty()
    static int GetDifficulty(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushUnsigned(L, map->GetDifficulty());
        return 1;
    }

    // :GetInstanceId()
    static int GetInstanceId(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushUnsigned(L, map->GetInstanceId());
        return 1;
    }

    // :GetPlayerCount()
    static int GetPlayerCount(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushUnsigned(L, map->GetPlayersCountExceptGMs());
        return 1;
    }

    // :GetMapId()
    static int GetMapId(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushUnsigned(L, map->GetId());
        return 1;
    }

    // :GetAreaId(x, y, z)
    static int GetAreaId(lua_State* L, Map* map)
    {
        if(!map)
            return 0;

        float x = luaL_checknumber(L, 1);
        float y = luaL_checknumber(L, 2);
        float z = luaL_checknumber(L, 3);

        sEluna->PushUnsigned(L, map->GetAreaId(x, y, z));
        return 1;
    }

    // :IsArena()
    static int IsArena(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushBoolean(L, map->IsBattleArena());
        return 1;
    }

    // :IsBattleground()
    static int IsBattleground(lua_State* L, Map* map)
    {
        if(!map)
            return 0;

        sEluna->PushBoolean(L, map->IsBattleground());
        return 1;
    }

    // :IsDungeon()
    static int IsDungeon(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushBoolean(L, map->IsDungeon());
        return 1;
    }

    // :IsEmpty()
    static int IsEmpty(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushBoolean(L, map->isEmpty());
        return 1;
    }

    // :IsHeroic()
    static int IsHeroic(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushBoolean(L, map->IsHeroic());
        return 1;
    }

    // :IsRaid()
    static int IsRaid(lua_State* L, Map* map)
    {
        if(!map)
            return 0;
        
        sEluna->PushBoolean(L, map->IsRaid());
        return 1;
    }*/
};
#endif
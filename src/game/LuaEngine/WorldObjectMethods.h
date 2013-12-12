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

#ifndef WORLDOBJECTMETHODS_H
#define WORLDOBJECTMETHODS_H

namespace LuaWorldObject
{
    int GetX(lua_State* L, WorldObject* obj)
    {
        sEluna.Push(L, obj->GetPositionX());
        return 1;
    }

    int GetY(lua_State* L, WorldObject* obj)
    {
        sEluna.Push(L, obj->GetPositionY());
        return 1;
    }

    int GetZ(lua_State* L, WorldObject* obj)
    {
        sEluna.Push(L, obj->GetPositionZ());
        return 1;
    }

    int GetO(lua_State* L, WorldObject* obj)
    {
        sEluna.Push(L, obj->GetOrientation());
        return 1;
    }

    int GetLocation(lua_State* L, WorldObject* obj)
    {
        sEluna.Push(L, obj->GetPositionX());
        sEluna.Push(L, obj->GetPositionY());
        sEluna.Push(L, obj->GetPositionZ());
        sEluna.Push(L, obj->GetOrientation());
        return 4;
    }
};
#endif

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

#ifndef OBJECTMETHODS_H
#define OBJECTMETHODS_H

namespace LuaObject
{
    static int GetGUID(lua_State* L, Object* obj)
    {
        sEluna.Push(L, obj->GetObjectGuid().GetRawValue());
        return 1;
    }
    static int GetGUIDLow(lua_State* L, Object* obj)
    {
        sEluna.Push(L, obj->GetGUIDLow());
        return 1;
    }
    static int IsInWorld(lua_State* L, Object* obj)
    {
        sEluna.Push(L, obj->IsInWorld());
        return 1;
    }
};
#endif

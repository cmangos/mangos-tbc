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

#ifndef AURAMETHODS_H
#define AURAMETHODS_H

namespace LuaAura
{
    int GetObjectType(lua_State*, Aura*);
    int GetCaster(lua_State*, Aura*);
    int GetCasterGUID(lua_State*, Aura*);
    int GetCasterLevel(lua_State*, Aura*);
    int GetDuration(lua_State*, Aura*);
    int GetCharges(lua_State*, Aura*);
    int GetAuraId(lua_State*, Aura*);
    int GetMaxDuration(lua_State*, Aura*);
    int GetStackAmount(lua_State*, Aura*);
    int SetDuration(lua_State*, Aura*);
    int SetMaxDuration(lua_State*, Aura*);
    int SetStackAmount(lua_State*, Aura*);
    int Remove(lua_State*, Aura*);
    int GetOwner(lua_State*, Aura*);
};
#endif

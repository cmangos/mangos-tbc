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
#include "AuraMethods.h"

int LuaAura::GetUnitType(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushString(L, "Aura");
    return 1;
}

int LuaAura::GetCaster(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushUnit(L, aura->GetCaster());
    return 1;
}

int LuaAura::GetCasterGUID(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushULong(L, aura->GetCasterGuid());
    return 1;
}

int LuaAura::GetCasterLevel(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushUnsigned(L, aura->GetCaster()->getLevel());
    return 1;
}

int LuaAura::GetDuration(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushInteger(L, aura->GetAuraDuration());
    return 1;
}

int LuaAura::GetCharges(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushUnsigned(L, aura->GetStackAmount());
    return 1;
}

int LuaAura::GetAuraId(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushUnsigned(L, aura->GetId());
    return 1;
}

int LuaAura::GetMaxDuration(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushInteger(L, aura->GetAuraMaxDuration());
    return 1;
}

int LuaAura::GetStackAmount(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    sEluna.PushUnsigned(L, aura->GetStackAmount());
    return 1;
}

int LuaAura::SetDuration(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    int duration = luaL_checkinteger(L, 1);
    aura->GetHolder()->SetAuraDuration(duration);
    return 0;
}

int LuaAura::SetMaxDuration(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    int duration = luaL_checkinteger(L, 1);
    aura->GetHolder()->SetAuraMaxDuration(duration);
    return 0;
}

int LuaAura::SetStackAmount(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;

    int amount = luaL_checkunsigned(L, 1);
    aura->GetHolder()->SetStackAmount(amount);
    return 0;
}

int LuaAura::Remove(lua_State* L, Aura* aura)
{
    if (!aura)
        return 0;
    aura->GetHolder()->RemoveAura(aura->GetEffIndex());
    return 0;
}

int LuaAura::GetOwner(lua_State* L, Aura* aura) // TODO: Implement
{
    /*if (!aura)
        return 0;

    if (aura->GetType() != UNIT_AURA_TYPE)
        return 0;

    sEluna.PushUnit(L, aura->GetUnitOwner());
    return 1;*/
    return 0; // Temp return to prevent errors
}

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
 
#ifndef WEATHERMETHODS_H
#define WEATHERMETHODS_H

class LuaWeather
{
public:

    static int GetScriptId(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        sEluna.PushUnsigned(L, weather->GetScriptId());
        return 1;
    }

    static int GetZoneId(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        sEluna.PushUnsigned(L, weather->GetZone());
        return 1;
    }

    static int SetWeather(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        uint32 weatherType = luaL_checkunsigned(L, 1);
        float grade = luaL_checknumber(L, 2);

        weather->SetWeather((WeatherType)weatherType, grade);
        return 0;
    }

    static int SendWeatherUpdateToPlayer(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        Player* player = sEluna.CHECK_PLAYER(L, 1);
        if (!player)
            return 0;

        weather->SendWeatherUpdateToPlayer(player);
        return 0;
    }

    static int Regenerate(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        sEluna.PushBoolean(L, weather->ReGenerate());
        return 1;
    }

    static int UpdateWeather(lua_State* L, Weather* weather)
    {
        if (!weather)
            return 0;

        sEluna.PushBoolean(L, weather->UpdateWeather());
        return 1;
    }
};

#endif
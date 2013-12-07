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

#ifndef GAMEOBJECTMETHODS_H
#define GAMEOBJECTMETHODS_H

namespace LuaGameObject
{
    int GetMap(lua_State*, GameObject*);
    int GetRelativePoint(lua_State*, GameObject*);
    int GetObjectType(lua_State*, GameObject*);
    int GetGUID(lua_State*, GameObject*);
    int CastSpell(lua_State*, GameObject*);
    int GetX(lua_State*, GameObject*);
    int GetY(lua_State*, GameObject*);
    int GetZ(lua_State*, GameObject*);
    int GetO(lua_State*, GameObject*);
    int GetLocation(lua_State*, GameObject*);
    int GetMapId(lua_State*, GameObject*);
    int GetZoneId(lua_State*, GameObject*);
    int GetAreaId(lua_State*, GameObject*);
    int GetName(lua_State*, GameObject*);
    int GetEntry(lua_State*, GameObject*);
    int SummonCreature(lua_State*, GameObject*);
    int SummonGameObject(lua_State*, GameObject*);
    int GetDisplayId(lua_State*, GameObject*);
    int GetScale(lua_State*, GameObject*);
    int IsInWorld(lua_State*, GameObject*);
    int HasQuest(lua_State*, GameObject*);
    int IsSpawned(lua_State*, GameObject*);
    int IsTransport(lua_State*, GameObject*);
    int IsDestructible(lua_State*, GameObject*);
    int IsActive(lua_State*, GameObject*);
    int Move(lua_State*, GameObject*);
    int SaveToDB(lua_State*, GameObject*);
    int SetScale(lua_State*, GameObject*);
    int RegisterEvent(lua_State*, GameObject*);
    int RemoveEventById(lua_State*, GameObject*);
    int RemoveEvents(lua_State*, GameObject*);
    int GetInt32Value(lua_State*, GameObject*);
    int GetUInt32Value(lua_State*, GameObject*);
    int GetFloatValue(lua_State*, GameObject*);
    int GetByteValue(lua_State*, GameObject*);
    int GetUInt16Value(lua_State*, GameObject*);
    int SetInt32Value(lua_State*, GameObject*);
    int SetUInt32Value(lua_State*, GameObject*);
    int UpdateUInt32Value(lua_State*, GameObject*);
    int SetFloatValue(lua_State*, GameObject*);
    int SetByteValue(lua_State*, GameObject*);
    int SetUInt16Value(lua_State*, GameObject*);
    int SetInt16Value(lua_State*, GameObject*);
    int GetGUIDLow(lua_State*, GameObject*);
    int GetNearestPlayer(lua_State*, GameObject*);
    int GetNearestGameObject(lua_State*, GameObject*);
    int GetNearestCreature(lua_State*, GameObject*);
    int UseDoorOrButton(lua_State*, GameObject*);
    int SetGoState(lua_State*, GameObject*);
    int GetGoState(lua_State*, GameObject*);
    int GetLootState(lua_State*, GameObject*);
    int SetLootState(lua_State*, GameObject*);
    int SetFlag(lua_State*, GameObject*);
    int RemoveFlag(lua_State*, GameObject*);
    int Despawn(lua_State*, GameObject*);
    int Respawn(lua_State*, GameObject*);
    int RemoveFromWorld(lua_State*, GameObject*);
};
#endif

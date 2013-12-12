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

#ifndef PLAYERMETHODS_H
#define PLAYERMETHODS_H

namespace LuaPlayer
{
    int HasSpell(lua_State* L, Player* player)
    {
        uint32 id = luaL_checkunsigned(L, 1);
        sEluna.Push(L, player->HasSpell(id));
        return 1;
    }


    int SummonPlayer(lua_State* L, Player* player)
    {
        Player* target = sEluna.CHECK_PLAYER(L, 1);
        uint32 map = luaL_checkunsigned(L, 2);
        float x = luaL_checknumber(L, 3);
        float y = luaL_checknumber(L, 4);
        float z = luaL_checknumber(L, 5);
        float zoneId = luaL_checkunsigned(L, 6);
        uint32 delay = luaL_optunsigned(L, 7, 0);
        if (!target || !MapManager::IsValidMapCoord(map, x, y, z))
            return 0;

        target->SetSummonPoint(map, x, y, z);
        WorldPacket data(SMSG_SUMMON_REQUEST, 8 + 4 + 4);
        data << uint64(player->GetGUIDLow());
        data << uint32(zoneId);
        data << uint32(delay ? delay* IN_MILLISECONDS : MAX_PLAYER_SUMMON_DELAY * IN_MILLISECONDS);
        target->GetSession()->SendPacket(&data);
        return 0;
    }

    int Mute(lua_State* L, Player* player)
    {
        uint32 muteseconds = luaL_checkunsigned(L, 1);
        const char* reason = luaL_checkstring(L, 2);

        /*PreparedStatement* stmt = LoginDatabase.GetPreparedStatement(LOGIN_UPD_MUTE_TIME);
        int64 muteTime = time(NULL) + muteseconds;
        player->GetSession()->m_muteTime = muteTime;
        stmt->setInt64(0, muteTime);
        stmt->setString(1, reason ? reason : "");
        stmt->setString(2, "Eluna");
        stmt->setUInt32(3, player->GetSession()->GetAccountId());
        LoginDatabase.Execute(stmt);*/
        return 0;
    }

};
#endif

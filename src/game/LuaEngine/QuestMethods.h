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

#ifndef QUESTMETHODS_H
#define QUESTMETHODS_H

class LuaQuest
{
    public:
        // :GetUnitType()
        static int GetUnitType(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            lua_pushstring(L, "Quest");
            return 1;
        }

        // :GetId()
        static int GetId(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushUnsigned(L, quest->GetQuestId());
            return 1;
        }

        // :GetLevel()
        static int GetLevel(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushInteger(L, quest->GetQuestLevel());
            return 1;
        }

        // :GetMaxLevel()
        static int GetMaxLevel(lua_State* L, Quest* quest) // TODO: Implementation core side
        {
            if (!quest)
                return 0;

            // sEluna.PushUnsigned(L, quest->GetMaxLevel());
            // return 1;
            return 0; // Temporary to prevent conflicts
        }

        // :GetMinLevel()
        static int GetMinLevel(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushUnsigned(L, quest->GetMinLevel());
            return 1;
        }

        // :GetNextQuestId()
        static int GetNextQuestId(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushInteger(L, quest->GetNextQuestId());
            return 1;
        }

        // :GetPrevQuestId()
        static int GetPrevQuestId(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushInteger(L, quest->GetPrevQuestId());
            return 1;
        }

        // :GetNextQuestInChain()
        static int GetNextQuestInChain(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushInteger(L, quest->GetNextQuestInChain());
            return 1;
        }

        // :GetFlags()
        static int GetFlags(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushUnsigned(L, quest->GetQuestFlags());
            return 1;
        }

        // :GetType()
        static int GetType(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushUnsigned(L, quest->GetType());
            return 1;
        }

        // :HasFlag(flag)
        static int HasFlag(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            uint32 flag = luaL_checkunsigned(L, 1);
            sEluna.PushBoolean(L, quest->HasQuestFlag((QuestFlags)flag));
            return 1;
        }

        // :IsDaily()
        static int IsDaily(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushBoolean(L, quest->IsDaily());
            return 1;
        }

        // :IsRepeatable()
        static int IsRepeatable(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            sEluna.PushBoolean(L, quest->IsRepeatable());
            return 1;
        }

        // :SetFlag(flag)
        static int SetFlag(lua_State* L, Quest* quest)
        {
            if (!quest)
                return 0;

            uint32 flag = luaL_checkunsigned(L, 1);
            quest->SetSpecialFlag((QuestSpecialFlags)flag);
            return 0;
        }
};
#endif
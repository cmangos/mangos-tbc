/*
 * This file is part of the CMaNGOS Project. See AUTHORS file for Copyright information
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

#ifndef MANGOS_SPELLTARGETS_H
#define MANGOS_SPELLTARGETS_H

#include "Spells/SpellTargetDefines.h"
#include "Spells/SpellEffectDefines.h"
#include "Server/DBCEnums.h"
#include "Platform/Define.h"

struct SpellTargetInfo
{
    char const* name;
    SpellTargetImplicitType type;
    SpellTargetFilter filter;
    SpellTargetEnumerator enumerator;

    SpellTargetInfo(char const* name = "", SpellTargetImplicitType type = TARGET_TYPE_UNKNOWN, SpellTargetFilter filter = TARGET_NEUTRAL, SpellTargetEnumerator enumerator = TARGET_ENUMERATOR_UNKNOWN);
};

extern SpellTargetInfo SpellTargetInfoTable[MAX_SPELL_TARGETS];

struct SpellTargetingData
{
    SpellTargetImplicitType implicitType[MAX_EFFECT_INDEX];
    SpellEffectIndex targetingIndex[MAX_EFFECT_INDEX];
};

class SpellTargetMgr
{
    public:
        static SpellTargetingData& GetSpellTargetingData(uint32 spellId);
        static void Initialize();
    private:
        static std::map<uint32, SpellTargetingData> spellTargetingData;
};

#endif
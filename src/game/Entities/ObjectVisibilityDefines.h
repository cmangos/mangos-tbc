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

#ifndef __OBJECT_VISIBILITY_DEFINES_H
#define __OBJECT_VISIBILITY_DEFINES_H

#include "Common.h"

enum class VisibilityDistanceType : uint32
{
    Normal = 0,
    Tiny = 1,
    Small = 2,
    Large = 3,
    Gigantic = 4,
    Infinite = 5,

    Max
};

enum StealthType : uint32
{
    STEALTH_UNIT = 0,
    STEALTH_TRAP = 1,
    STEALTH_TYPE_MAX,
};

enum InvisibilityType : uint32
{
    INVISIBILITY_TRAP = 3,
    INVISIBILITY_DRUNK = 6,
    INVISIBILITY_TYPE_MAX = 32,
};

#endif
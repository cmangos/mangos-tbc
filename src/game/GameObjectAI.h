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

#ifndef MANGOS_GAMEOBJECTAI_H
#define MANGOS_GAMEOBJECTAI_H

#include <list>
#include "Object.h"
#include "GameObject.h"
#include "CreatureAI.h"

class GameObjectAI
{
protected:
    GameObject * const go;
public:
    explicit GameObjectAI(GameObject *g) : go(g) {}
    virtual ~GameObjectAI() {}

    virtual void UpdateAI(const uint32 diff) {}

    virtual void InitializeAI() { Reset(); }

    virtual void Reset() {};

    static int Permissible(const GameObject* go);

    virtual bool GossipHello(Player* player) { return false; }
};

class NullGameObjectAI : public GameObjectAI
{
public:
    explicit NullGameObjectAI(GameObject *g);

    void UpdateAI(const uint32) {}

    // static int Permissible(const GameObject* go) { return (Permitions)PERMIT_BASE_IDLE; } // Thats give error with ScriptDev2 i have no idea to fix this, set for the moment to 1
    static int Permissible(const GameObject* go) { return 1; }
};
#endif

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

#include "VMapFactory.h"
#include "VMapManager2.h"
#include <atomic>
#include <mutex>

using namespace G3D;

namespace
{
    std::mutex gVMapMutex;
    std::atomic<VMAP::IVMapManager*> gVMapManager { nullptr };
}

namespace VMAP
{
    void VMapFactory::chompAndTrim(std::string& str)
    {
        while (str.length() > 0)
        {
            char lc = str[str.length() - 1];
            if (lc == '\r' || lc == '\n' || lc == ' ' || lc == '"' || lc == '\'')
            {
                str = str.substr(0, str.length() - 1);
            }
            else
            {
                break;
            }
        }
        while (str.length() > 0)
        {
            char lc = str[0];
            if (lc == ' ' || lc == '"' || lc == '\'')
            {
                str = str.substr(1, str.length() - 1);
            }
            else
            {
                break;
            }
        }
    }


    //===============================================
    // result false, if no more id are found

    bool VMapFactory::getNextId(const std::string& pString, unsigned int& pStartPos, unsigned int& pId)
    {
        bool result = false;
        unsigned int i;
        for (i = pStartPos; i < pString.size(); ++i)
        {
            if (pString[i] == ',')
            {
                break;
            }
        }
        if (i > pStartPos)
        {
            std::string idString = pString.substr(pStartPos, i - pStartPos);
            pStartPos = i + 1;
            chompAndTrim(idString);
            pId = atoi(idString.c_str());
            result = true;
        }
        return result;
    }

    /*
     * Return the instance.
     */
    IVMapManager& VMapFactory::GetVMapManager()
    {
        IVMapManager* instance = gVMapManager.load(std::memory_order_acquire);
        if (!instance)
        {
            std::lock_guard<std::mutex> lock(gVMapMutex);
            instance = gVMapManager.load(std::memory_order_relaxed);
            if (!instance)
            {
                instance = new VMapManager2();
                gVMapManager.store(instance, std::memory_order_release);
            }
        }
        return *instance;
    }

    /*
     * Delete all internal data structures.
     */
    void VMapFactory::clear()
    {
        // No lock required because no other thread should still be
        // accessing the VMapManager when we're deleting it!
        delete gVMapManager.load();
    }
}

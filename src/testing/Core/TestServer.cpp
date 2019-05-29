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
#include "TestServer.h"

#include "Common.h"
#include "Timer.h"

#ifdef _WIN32
#include "ServiceWin32.h"
char serviceName[] = "mangosd";
char serviceLongName[] = "MaNGOS world service";
char serviceDescription[] = "Massive Network Game Object Server";

int m_ServiceStatus = -1;
#else
#include "PosixDaemon.h"
#endif

DatabaseType WorldDatabase;       ///< Accessor to the world database
DatabaseType CharacterDatabase;   ///< Accessor to the character database
DatabaseType LoginDatabase;       ///< Accessor to the realm/login database

uint32 realmID;                   ///< Id of the realm

int TestServer::start()
{
    std::string auctionBotConfig;
    std::string configFile = _MANGOSD_CONFIG;
    std::string serviceParameter;

    boost::program_options::variables_map vm;

    if (!auctionBotConfig.empty())
        sAuctionBotConfig.SetConfigFileName(auctionBotConfig);

    if (!sConfig.SetSource(configFile))
    {
        sLog.outError("Could not find configuration file %s.", configFile.c_str());
        Log::WaitBeforeContinueIfNeed();
        return 1;
    }

    return sMaster.Run();
}

void TestServer::end(uint8 exitCode/* = SHUTDOWN_EXIT_CODE*/)
{
    World::StopNow(exitCode);
}

///////// ServerRunnable ///////////

void ServerRunnable::run()
{
    sTestServer.start();
}

#include "TestEngine.h"

#ifdef _WIN32
#include "ServiceWin32.h"
char serviceName[] = "mangosd";
char serviceLongName[] = "MaNGOS world service";
char serviceDescription[] = "Massive Network Game Object Server";
/*
 * -1 - not in service mode
 *  0 - stopped
 *  1 - running
 *  2 - paused
 */
int m_ServiceStatus = -1;
#else
#include "PosixDaemon.h"
#endif

DatabaseType WorldDatabase;                                 ///< Accessor to the world database
DatabaseType CharacterDatabase;                             ///< Accessor to the character database
DatabaseType LoginDatabase;                                 ///< Accessor to the realm/login database

uint32 realmID;                                             ///< Id of the realm

/*
TODO: We need to set up a test thread where we get access to all the world/master.
      Then when the test has ended we need to call World::StopNow(SHUTDOWN_EXIT_CODE)
*/
int TestEngine::start(int argc, char* argv[])
{
    std::string auctionBotConfig, configFile, serviceParameter;

    boost::program_options::options_description desc("Allowed options");
    desc.add_options()
        ("ahbot,a", boost::program_options::value<std::string>(&auctionBotConfig), "ahbot configuration file")
        ("config,c", boost::program_options::value<std::string>(&configFile)->default_value(_MANGOSD_CONFIG), "configuration file")
        ("help,h", "prints usage")
        ("version,v", "print version and exit");

    boost::program_options::variables_map vm;

    if (vm.count("ahbot"))
        sAuctionBotConfig.SetConfigFileName(auctionBotConfig);

    if (!sConfig.SetSource(configFile))
    {
        sLog.outError("Could not find configuration file %s.", configFile.c_str());
        Log::WaitBeforeContinueIfNeed();
        return 1;
    }

    return sMaster.Run();
}
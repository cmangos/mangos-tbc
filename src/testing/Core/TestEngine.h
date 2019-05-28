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

 /// \addtogroup mangosd Mangos Daemon
 /// @{
 /// \file
#ifndef _TEST_ENGINE_H
#define _TEST_ENGINE_H

#include "Common.h"
#include "Database/DatabaseEnv.h"
#include "Config/Config.h"
#include "ProgressBar.h"
#include "Log.h"
#include "Master.h"
#include "SystemConfig.h"
#include "AuctionHouseBot/AuctionHouseBot.h"

#include <openssl/opensslv.h>
#include <openssl/crypto.h>

#include <boost/program_options.hpp>
#include <boost/version.hpp>

#include <iostream>
#include <string>

/// Start the server
class TestEngine
{
public:
    TestEngine() {
        std::cout << "Creating" << std::endl;
    };

    int start(int argc, char* argv[]);
};

#define sMaster MaNGOS::Singleton<Master>::Instance()
#endif
/// @}

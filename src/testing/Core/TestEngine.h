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
#ifndef TEST_ENGINE_H
#define TEST_ENGINE_H

#include "TestServer.h"

class TestEngine {
public:
    TestEngine() {}
    ~TestEngine() {}

    void run() {
        if (serverThread == nullptr) {
            serverThread = new MaNGOS::Thread(new ServerRunnable);
        }
    }

    void kill() {
        // end the test server
        sTestServer.end();

        // destroy the server thread
        serverThread->destroy();
    }

    MaNGOS::Thread* getServerThread() {
        return serverThread;
    }

private:
    MaNGOS::Thread* serverThread;
};

#define sTestEngine MaNGOS::Singleton<TestEngine>::Instance()
#endif

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

#ifndef PLAYER_TEST_H
#define PLAYER_TEST_H

#include <boost/test/unit_test.hpp>

#include "GlobalTestFixture.h"
#include "TestEngine.h"

#include "Entities/Player.h"
#include "Server/WorldSession.h"

class PlayerTest {
public:
    static std::string default_suite() {
        return typeid(PlayerTest).name();
    }

    static void test_case1()
    {
        BOOST_TEST_MESSAGE("running test_case1");
        std::cout << ("running test_case1") << std::endl;
        BOOST_TEST(true);
    }

    static void test_case2()
    {
        BOOST_TEST_MESSAGE("running test_case2");
        std::cout << ("running test_case2") << std::endl;
        BOOST_TEST(false);
    }

    // TODO: Add more tests!
};

#endif
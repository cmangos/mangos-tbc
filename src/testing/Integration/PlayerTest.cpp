#define BOOST_TEST_MODULE PlayerIntegrationTests
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "Entities/Player.h"
#include "Server/WorldSession.h"
#include "TestEngine.h"

struct MyGlobalFixture {
    static MyGlobalFixture*& instance() {
        static MyGlobalFixture* s_inst = 0;
        return s_inst;
    }

    TestEngine* engine = new TestEngine();

    MyGlobalFixture() {
        std::cout << "global setup" << std::endl;
        engine->start(0, nullptr);
    }
    ~MyGlobalFixture() {
        std::cout << "global teardown" << std::endl;
        delete engine;
    }
};

BOOST_GLOBAL_FIXTURE(MyGlobalFixture);

struct F {
    F() : i(0) { BOOST_TEST_MESSAGE("setup fixture"); }
    ~F() { BOOST_TEST_MESSAGE("teardown fixture"); }

    int i;
};

BOOST_FIXTURE_TEST_SUITE(s, F)

BOOST_AUTO_TEST_CASE(PlayerTest)
{
    Player* player = new Player(nullptr);

    BOOST_CHECK(true);
}

BOOST_AUTO_TEST_SUITE_END()
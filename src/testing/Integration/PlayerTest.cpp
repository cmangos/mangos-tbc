#define BOOST_TEST_MODULE PlayerIntegrationTests
#include <boost/test/unit_test.hpp>
#include <iostream>

#include "Entities/Player.h"
#include "Server/WorldSession.h"
#include "TestEngine.h"

TestEngine* engine = new TestEngine();

struct MyGlobalFixture {
    MyGlobalFixture() {
        std::cout << "ctor fixture i=" << i << std::endl;
    }
    void setup() {
        std::cout << "setup fixture i=" << i << std::endl;
        i++;
    }
    void teardown() {
        std::cout << "teardown fixture i=" << i << std::endl;
        i += 2;
    }
    ~MyGlobalFixture() {
        std::cout << "dtor fixture i=" << i << std::endl;
    }
    static int i;
};
int MyGlobalFixture::i = 0;

BOOST_TEST_GLOBAL_FIXTURE(MyGlobalFixture);

BOOST_AUTO_TEST_SUITE(test_suite1)

BOOST_AUTO_TEST_CASE(test_case1)
{
    std::cout << ("running test_case1") << std::endl;
    BOOST_TEST(MyGlobalFixture::i == 1);
}

BOOST_AUTO_TEST_CASE(test_case2)
{
    std::cout << ("running test_case2") << std::endl;
    BOOST_TEST(MyGlobalFixture::i == 3);
}

BOOST_AUTO_TEST_SUITE_END()
#include "Time/Stardate.h"
#include "test/TestStardate.h"

using tsc::Time::Stardate;
using tsc::Time::ChristianDate;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestStardate);

void TestStardate::setUp()
{
}

void TestStardate::tearDown()
{
}

void TestStardate::testFromDate()
{
    Stardate d1_answer(2443259.9);
    Stardate d2_answer(2436116.31);
    Stardate d3_answer(1842713.0);
    Stardate d4_answer(1355671.4);
    Stardate d5_answer(0.0);

    Stardate d1 = Stardate::fromDate(ChristianDate(1977, 4, 26.4));
    Stardate d2 = Stardate::fromDate(ChristianDate(1957, 10, 4.81));
    Stardate d3 = Stardate::fromDate(ChristianDate(333, 1, 27, 12, 0, 0));
    Stardate d4 = Stardate::fromDate(ChristianDate(-1001, 8, 17.9));
    Stardate d5 = Stardate::fromDate(ChristianDate(-4712, 1, 1.5));

    CPPUNIT_ASSERT_EQUAL(d1_answer, d1);
    CPPUNIT_ASSERT_EQUAL(d2_answer, d2);
    CPPUNIT_ASSERT_EQUAL(d3_answer, d3);
    CPPUNIT_ASSERT_EQUAL(d4_answer, d4);
    CPPUNIT_ASSERT_EQUAL(d5_answer, d5);
}

void TestStardate::testComparisons()
{
    Stardate d1(2443259.9);
    Stardate d2(2436116.31);
    Stardate d3(1842713.0);
    Stardate d4(1355671.4);
    Stardate d5(0.0);
    Stardate d6(1355671.4);

    CPPUNIT_ASSERT(d1 > d2);
    CPPUNIT_ASSERT(d4 < d3);
    CPPUNIT_ASSERT(d5 >= d5);
    CPPUNIT_ASSERT(d3 <= d1);
    CPPUNIT_ASSERT(d2 != d4);
    CPPUNIT_ASSERT(d4 == d6);
    
}


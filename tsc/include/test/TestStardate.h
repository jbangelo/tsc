#ifndef TESTSTARDATE_H
#define TESTSTARDATE_H

#include <cppunit/extensions/HelperMacros.h>

class TestStardate : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestStardate);
    CPPUNIT_TEST(testFromDate);
    CPPUNIT_TEST(testComparisons);
    CPPUNIT_TEST_SUITE_END();

    public:
        void setUp();
        void tearDown();

        void testFromDate();
        void testComparisons();
};

#endif // TESTSTARDATE_H

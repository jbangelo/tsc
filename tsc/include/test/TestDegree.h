#ifndef TESTDEGREE_H
#define TESTDEGREE_H

#include <cppunit/extensions/HelperMacros.h>

class TestDegree : public CppUnit::TestFixture
{
CPPUNIT_TEST_SUITE(TestDegree);
        CPPUNIT_TEST(testComparisons);
    CPPUNIT_TEST_SUITE_END();

 public:
    void setUp();
    void tearDown();

    void testComparisons();
};

#endif // TESTDEGREE_H

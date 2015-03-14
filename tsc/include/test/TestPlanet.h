#ifndef TESTPLANET_H
#define TESTPLANET_H

#include <cppunit/extensions/HelperMacros.h>
#include <sqlite3.h>
#include "SkyObject/Planet.h"

using tsc::SkyObject::Planet;

class TestPlanet : public CppUnit::TestFixture
{
    CPPUNIT_TEST_SUITE(TestPlanet);
    CPPUNIT_TEST(testMercury);
    CPPUNIT_TEST(testVenus);
    CPPUNIT_TEST(testEarth);
    CPPUNIT_TEST(testMars);
    CPPUNIT_TEST(testJupiter);
    CPPUNIT_TEST(testSaturn);
    CPPUNIT_TEST(testUranus);
    CPPUNIT_TEST(testNeptune);
    CPPUNIT_TEST_SUITE_END();

    sqlite3* _db;
    Planet* _earth;

    public:
        void setUp();
        void tearDown();

        void testMercury();
        void testVenus();
        void testEarth();
        void testMars();
        void testJupiter();
        void testSaturn();
        void testUranus();
        void testNeptune();
};

#endif // TESTPLANET_H

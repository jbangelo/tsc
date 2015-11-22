#ifndef TESTPLANET_H
#define TESTPLANET_H

#include <cppunit/extensions/HelperMacros.h>
#include "SkyObject/PlanetFactory.h"
#include "Utils/SqliteStorage.h"


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

    tsc::Utils::SqliteStorage *_storage;
    tsc::SkyObject::PlanetFactory *_planetFactory;

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

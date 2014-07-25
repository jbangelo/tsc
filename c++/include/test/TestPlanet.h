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
	CPPUNIT_TEST_SUITE_END();

	sqlite3* _db;
	Planet* _earth;

	public:
		void setUp();
		void tearDown();

		void testMercury();
};

#endif // TESTPLANET_H

#ifndef TESTPLANET_H
#define TESTPLANET_H

#include <cppunit/extensions/HelperMacros.h>

class TestPlanet : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE(TestPlanet);
	CPPUNIT_TEST(testMercury);
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testMercury();
};

#endif // TESTPLANET_H

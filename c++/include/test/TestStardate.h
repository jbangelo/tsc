#ifndef TESTSTARDATE_H
#define TESTSTARDATE_H

#include <cppunit/extensions/HelperMacros.h>

class TestStardate : public CppUnit::TestFixture
{
	CPPUNIT_TEST_SUITE( TestStardate );
	CPPUNIT_TEST( testConstructor );
	CPPUNIT_TEST_SUITE_END();

	public:
		void setUp();
		void tearDown();

		void testConstructor();
};

#endif // TESTSTARDATE_H

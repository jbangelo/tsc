#include "Math/Degree.h"
#include "test/TestDegree.h"

using tsc::Math::Degree;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestDegree);

void TestDegree::setUp()
{
}

void TestDegree::tearDown()
{
}

void TestDegree::testComparisons()
{
	Degree d1(12.648);
	Degree d2(64.267);
	Degree d3(12.648);
	Degree d4(136.49);

	CPPUNIT_ASSERT(d2 > d1);
	CPPUNIT_ASSERT(d3 < d2);
	CPPUNIT_ASSERT(d4 >= d3);
	CPPUNIT_ASSERT(d1 <= d2);
	CPPUNIT_ASSERT(d2 != d4);
	CPPUNIT_ASSERT(d1 == d3);
	
}


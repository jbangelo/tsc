#include <iostream>
#include <iomanip>
#include "test/TestPlanet.h"
#include "Time/Stardate.h"
#include "Math/Units.h"

using tsc::Time::Stardate;
using tsc::Math::EclipticCoords;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlanet);

void TestPlanet::setUp()
{
	sqlite3_open_v2("../resources/tsc.db", &_db, SQLITE_OPEN_READONLY, NULL);
	_earth = new Planet(Planet::EARTH, _db, NULL);
}

void TestPlanet::tearDown()
{
	delete _earth;
	sqlite3_close(_db);
}

void TestPlanet::testMercury()
{
	Planet merc(Planet::MERCURY, _db, _earth);

	Stardate d1(2451545.0);
	EclipticCoords answer1(Degree::fromRad(4.4293481036), Degree::fromRad(-.0527573409), 0.4664714751);

	Stardate d2(2415020.0);
	EclipticCoords answer2(Degree::fromRad(3.4851161911), Degree::fromRad(0.0565906173), 0.4183426275);

	Stardate d3(2378495.0);
	EclipticCoords answer3(Degree::fromRad(2.0737894888), Degree::fromRad(0.1168184804), 0.3233909533);

	Stardate d4(2341970.0);
	EclipticCoords answer4(Degree::fromRad(0.1910149587), Degree::fromRad(-0.0682441256), 0.3381563139);

	Stardate d5(2305445.0);
	EclipticCoords answer5(Degree::fromRad(5.1836421820), Degree::fromRad(-0.1170914848), 0.4326517759);

	Stardate d6(2268920.0);
	EclipticCoords answer6(Degree::fromRad(4.2636517903), Degree::fromRad(-0.0457048516), 0.4661523936);

	Stardate d7(2232395.0);
	EclipticCoords answer7(Degree::fromRad(3.3115600862), Degree::fromRad(0.0639722347), 0.4152385205);

	Stardate d8(2195870.0);
	EclipticCoords answer8(Degree::fromRad(1.8738888759), Degree::fromRad(0.1126774697), 0.3209366232);

	Stardate d9(2159345.0);
	EclipticCoords answer9(Degree::fromRad(6.2819826060), Degree::fromRad(-0.0768697084), 0.3414354250);

	Stardate d10(2122820.0);
	EclipticCoords answer10(Degree::fromRad(5.0128397764), Degree::fromRad(-0.1143275808), 0.4352063237);

	EclipticCoords calcedAnswer;

	merc.calculatePosition(d1);
	calcedAnswer = merc.getGeocentricEclipticCoords();
	std::cout << std::setprecision(30) << std::endl;
	std::cout << answer1.lambda.rad() << std::endl << calcedAnswer.lambda.rad() << std::endl;
	CPPUNIT_ASSERT(answer1.lambda == calcedAnswer.lambda);
	CPPUNIT_ASSERT(answer1.beta == calcedAnswer.beta);
	CPPUNIT_ASSERT(answer1.delta == calcedAnswer.delta);
}


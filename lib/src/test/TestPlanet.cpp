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

    EclipticCoords calcedAnswer;

    merc.calculatePosition(d1);
    calcedAnswer = merc.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    merc.calculatePosition(d2);
    calcedAnswer = merc.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    merc.calculatePosition(d3);
    calcedAnswer = merc.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testVenus()
{
    Planet venus(Planet::VENUS, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(3.1870221833), Degree::fromRad(.0569782849), .7202129253);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(5.9749622238), Degree::fromRad(-.0591260014), .7274719359);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(2.5083656668), Degree::fromRad(.0552309407), .7185473298);

    EclipticCoords calcedAnswer;

    venus.calculatePosition(d1);
    calcedAnswer = venus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    venus.calculatePosition(d2);
    calcedAnswer = venus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    venus.calculatePosition(d3);
    calcedAnswer = venus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testEarth()
{
    Planet earth(Planet::EARTH, _db, NULL);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(1.7519238681), Degree::fromRad(-.0000039656), .9833276819);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(1.7391225563), Degree::fromRad(-.0000005679), .9832689778);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(1.7262638916), Degree::fromRad(.0000002083), .9832274321);

    EclipticCoords calcedAnswer;

    earth.calculatePosition(d1);
    calcedAnswer = earth.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    earth.calculatePosition(d2);
    calcedAnswer = earth.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    earth.calculatePosition(d3);
    calcedAnswer = earth.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testMars()
{
    Planet mars(Planet::MARS, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(6.2735389983), Degree::fromRad(-.0247779824), 1.3912076925);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.9942005211), Degree::fromRad(-.0271965869), 1.4218777705);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.8711855478), Degree::fromRad(.0034969939), 1.5615140011);

    EclipticCoords calcedAnswer;

    mars.calculatePosition(d1);
    calcedAnswer = mars.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    mars.calculatePosition(d2);
    calcedAnswer = mars.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    mars.calculatePosition(d3);
    calcedAnswer = mars.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testJupiter()
{
    Planet jupiter(Planet::JUPITER, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(.6334614186), Degree::fromRad(-.0205001039), 4.9653813154);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.0927527024), Degree::fromRad(.0161446618), 5.3850276671);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(1.5255696771), Degree::fromRad(-.0043606936), 5.1318457604);

    EclipticCoords calcedAnswer;

    jupiter.calculatePosition(d1);
    calcedAnswer = jupiter.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    jupiter.calculatePosition(d2);
    calcedAnswer = jupiter.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    jupiter.calculatePosition(d3);
    calcedAnswer = jupiter.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testSaturn()
{
    Planet saturn(Planet::SATURN, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(.7980038761), Degree::fromRad(-.0401984149), 9.1838483715);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.6512836347), Degree::fromRad(.0192701409), 10.0668531997);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(2.1956677359), Degree::fromRad(.0104156566), 9.1043068639);

    EclipticCoords calcedAnswer;

    saturn.calculatePosition(d1);
    calcedAnswer = saturn.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    saturn.calculatePosition(d2);
    calcedAnswer = saturn.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    saturn.calculatePosition(d3);
    calcedAnswer = saturn.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testUranus()
{
    Planet uranus(Planet::URANUS, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(5.5225485803), Degree::fromRad(-.0119527838), 19.9240482667);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.3397761173), Degree::fromRad(.0011570307), 18.9927163620);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.0388348558), Degree::fromRad(.0132392955), 18.2991154397);

    EclipticCoords calcedAnswer;

    uranus.calculatePosition(d1);
    calcedAnswer = uranus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    uranus.calculatePosition(d2);
    calcedAnswer = uranus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    uranus.calculatePosition(d3);
    calcedAnswer = uranus.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testNeptune()
{
    Planet neptune(Planet::NEPTUNE, _db, _earth);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(5.3045629252), Degree::fromRad(.0042236789), 30.1205328392);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(1.4956195225), Degree::fromRad(-.0219610030), 29.8710345051);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.9290537977), Degree::fromRad(.0310692112), 30.3209192288);

    EclipticCoords calcedAnswer;

    neptune.calculatePosition(d1);
    calcedAnswer = neptune.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    neptune.calculatePosition(d2);
    calcedAnswer = neptune.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    neptune.calculatePosition(d3);
    calcedAnswer = neptune.getGeocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}


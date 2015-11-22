#include <iostream>
#include <iomanip>
#include "TestPlanet.h"
#include "Time/Stardate.h"
#include "Math/Units.h"
#include "SkyObject/IPlanet.h"

using tsc::Time::Stardate;
using tsc::Math::EclipticCoords;
using tsc::SkyObject::IPlanet;
using tsc::Utils::SqliteStorage;
using tsc::SkyObject::PlanetFactory;

// Registers the fixture into the 'registry'
CPPUNIT_TEST_SUITE_REGISTRATION(TestPlanet);

void TestPlanet::setUp()
{
	_storage = new SqliteStorage("../../resources/tsc.db");
	_planetFactory = new PlanetFactory(*_storage);
}

void TestPlanet::tearDown()
{
    delete _planetFactory;
    delete _storage;
}

void TestPlanet::testMercury()
{
    IPlanet& merc = _planetFactory->getPlanet(PlanetFactory::MERCURY);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(4.4293481036),
                           Degree::fromRad(-.0527573409), 0.4664714751);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(3.4851161911),
                           Degree::fromRad(0.0565906173), 0.4183426275);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(2.0737894888),
                           Degree::fromRad(0.1168184804), 0.3233909533);

    EclipticCoords calcedAnswer;

    merc.calculatePosition(d1);
    calcedAnswer = merc.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    merc.calculatePosition(d2);
    calcedAnswer = merc.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    merc.calculatePosition(d3);
    calcedAnswer = merc.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testVenus()
{
    IPlanet& venus = _planetFactory->getPlanet(PlanetFactory::VENUS);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(3.1870221833),
                           Degree::fromRad(.0569782849), .7202129253);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(5.9749622238),
                           Degree::fromRad(-.0591260014), .7274719359);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(2.5083656668),
                           Degree::fromRad(.0552309407), .7185473298);

    EclipticCoords calcedAnswer;

    venus.calculatePosition(d1);
    calcedAnswer = venus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    venus.calculatePosition(d2);
    calcedAnswer = venus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    venus.calculatePosition(d3);
    calcedAnswer = venus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testEarth()
{
    IPlanet& earth = _planetFactory->getPlanet(PlanetFactory::EARTH);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(1.7519238681),
                           Degree::fromRad(-.0000039656), .9833276819);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(1.7391225563),
                           Degree::fromRad(-.0000005679), .9832689778);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(1.7262638916),
                           Degree::fromRad(.0000002083), .9832274321);

    EclipticCoords calcedAnswer;

    earth.calculatePosition(d1);
    calcedAnswer = earth.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    earth.calculatePosition(d2);
    calcedAnswer = earth.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    earth.calculatePosition(d3);
    calcedAnswer = earth.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testMars()
{
    IPlanet& mars = _planetFactory->getPlanet(PlanetFactory::MARS);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(6.2735389983),
                           Degree::fromRad(-.0247779824), 1.3912076925);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.9942005211),
                           Degree::fromRad(-.0271965869), 1.4218777705);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.8711855478),
                           Degree::fromRad(.0034969939), 1.5615140011);

    EclipticCoords calcedAnswer;

    mars.calculatePosition(d1);
    calcedAnswer = mars.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    mars.calculatePosition(d2);
    calcedAnswer = mars.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    mars.calculatePosition(d3);
    calcedAnswer = mars.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testJupiter()
{
    IPlanet& jupiter = _planetFactory->getPlanet(PlanetFactory::JUPITER);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(.6334614186),
                           Degree::fromRad(-.0205001039), 4.9653813154);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.0927527024),
                           Degree::fromRad(.0161446618), 5.3850276671);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(1.5255696771),
                           Degree::fromRad(-.0043606936), 5.1318457604);

    EclipticCoords calcedAnswer;

    jupiter.calculatePosition(d1);
    calcedAnswer = jupiter.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    jupiter.calculatePosition(d2);
    calcedAnswer = jupiter.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    jupiter.calculatePosition(d3);
    calcedAnswer = jupiter.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testSaturn()
{
    IPlanet& saturn = _planetFactory->getPlanet(PlanetFactory::SATURN);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(.7980038761),
                           Degree::fromRad(-.0401984149), 9.1838483715);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.6512836347),
                           Degree::fromRad(.0192701409), 10.0668531997);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(2.1956677359),
                           Degree::fromRad(.0104156566), 9.1043068639);

    EclipticCoords calcedAnswer;

    saturn.calculatePosition(d1);
    calcedAnswer = saturn.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    saturn.calculatePosition(d2);
    calcedAnswer = saturn.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    saturn.calculatePosition(d3);
    calcedAnswer = saturn.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testUranus()
{
    IPlanet& uranus = _planetFactory->getPlanet(PlanetFactory::URANUS);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(5.5225485803),
                           Degree::fromRad(-.0119527838), 19.9240482667);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(4.3397761173),
                           Degree::fromRad(.0011570307), 18.9927163620);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.0388348558),
                           Degree::fromRad(.0132392955), 18.2991154397);

    EclipticCoords calcedAnswer;

    uranus.calculatePosition(d1);
    calcedAnswer = uranus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    uranus.calculatePosition(d2);
    calcedAnswer = uranus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    uranus.calculatePosition(d3);
    calcedAnswer = uranus.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}

void TestPlanet::testNeptune()
{
    IPlanet& neptune = _planetFactory->getPlanet(PlanetFactory::NEPTUNE);

    Stardate d1(2451545.0);
    EclipticCoords answer1(Degree::fromRad(5.3045629252),
                           Degree::fromRad(.0042236789), 30.1205328392);

    Stardate d2(2415020.0);
    EclipticCoords answer2(Degree::fromRad(1.4956195225),
                           Degree::fromRad(-.0219610030), 29.8710345051);

    Stardate d3(2378495.0);
    EclipticCoords answer3(Degree::fromRad(3.9290537977),
                           Degree::fromRad(.0310692112), 30.3209192288);

    EclipticCoords calcedAnswer;

    neptune.calculatePosition(d1);
    calcedAnswer = neptune.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer1.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer1.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer1.delta - calcedAnswer.delta < 0.00000001);

    neptune.calculatePosition(d2);
    calcedAnswer = neptune.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer2.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer2.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer2.delta - calcedAnswer.delta < 0.00000001);

    neptune.calculatePosition(d3);
    calcedAnswer = neptune.getHeliocentricEclipticCoords();
    CPPUNIT_ASSERT(answer3.lambda - calcedAnswer.lambda < 0.00000001);
    CPPUNIT_ASSERT(answer3.beta - calcedAnswer.beta < 0.00000001);
    CPPUNIT_ASSERT(answer3.delta - calcedAnswer.delta < 0.00000001);
}


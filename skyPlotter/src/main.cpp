/*
 * main.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#include <iostream>
#include <unistd.h>
#include <sstream>
#include <stdio.h>
#include "Math/Degree.h"
#include "Time/Stardate.h"
#include "SkyObject/PlanetFactory.h"
#include "Utils/SqliteStorage.h"
#include "Math/Units.h"

using namespace std;
using tsc::Utils::SqliteStorage;
using tsc::SkyObject::Planet;
using tsc::SkyObject::PlanetFactory;
using tsc::Math::LatLng;
using tsc::Math::HorizontalCoords;

void printUsage(const char* progname);
bool parseDegree(const char* str, tsc::Math::Degree& deg);
bool parseDate(const char* str, tsc::Time::Stardate& date);

int main(int argc, char** argv)
{
	bool latParsed = false, lngParsed = false, dateParsed = false;
	tsc::Math::Degree lat, lng;
	tsc::Time::Stardate date(0);
	char *filename = NULL;
	int c;

	while ((c = getopt(argc, argv, "d:g:t:f:")) != -1)
	{
		switch (c)
		{
			case 'd':
				if (!parseDate(optarg, date))
				{
					cerr << "Invalid format for date." << endl;
					cerr << "Valid formats: YYYY/MM/DD HH:MM:SS" << endl;
					cerr << "               YYYY/MM/DD HH:MM     Seconds is assumed to be 0" << endl;
					cerr << "               YYYY/MM/DD           Time of day is assumed to be midnight" << endl;
					return 1;
				}
				dateParsed = true;
				break;
			case 'g':
				if (!parseDegree(optarg, lng))
				{
					cerr << "Invalid format for longitude." << endl;
					printUsage(argv[0]);
					return 1;
				}
				lngParsed = true;
				break;
			case 't':
				if (!parseDegree(optarg, lat))
				{
					cerr << "Invalid format for latitude." << endl;
					printUsage(argv[0]);
					return 1;
				}
				latParsed = true;
				break;
			case 'f':
				break;
			case '?':
				printUsage(argv[0]);
		        return 1;
			default:
				break;
		}
	}

	if (!latParsed || !lngParsed || !dateParsed)
	{
		cerr << "A date, latitude, and longitude must be provided!" << endl;
		printUsage(argv[0]);
		return 1;
	}

	cout << "Latitude = " << lat.degStr() << endl;
	cout << "Longitude = " << lng.degStr() << endl;
	cout << "Date = " << date.toGregorianDateStr() << endl;

	cout << "Loading planets" << endl;
	cout << flush;
	SqliteStorage storage("../../resources/tsc.db");
	PlanetFactory planetFactory(storage);

	Planet& mercury = planetFactory.getPlanet(PlanetFactory::MERCURY);
	Planet& venus = planetFactory.getPlanet(PlanetFactory::VENUS);
	Planet& mars = planetFactory.getPlanet(PlanetFactory::MARS);
	Planet& jupiter = planetFactory.getPlanet(PlanetFactory::JUPITER);
	Planet& saturn = planetFactory.getPlanet(PlanetFactory::SATURN);
	Planet& uranus = planetFactory.getPlanet(PlanetFactory::URANUS);
	Planet& neptune = planetFactory.getPlanet(PlanetFactory::NEPTUNE);

	cout << "Calculating positions" << endl;
	cout << flush;
	mercury.calculatePosition(date);
	venus.calculatePosition(date);
	mars.calculatePosition(date);
	jupiter.calculatePosition(date);
	saturn.calculatePosition(date);
	uranus.calculatePosition(date);
	neptune.calculatePosition(date);

	LatLng location(lat, lng);

	HorizontalCoords mercuryCoords = mercury.getHorizontalCoords(location, date);
	HorizontalCoords venusCoords = venus.getHorizontalCoords(location, date);
	HorizontalCoords marsCoords = mars.getHorizontalCoords(location, date);
	HorizontalCoords jupiterCoords = jupiter.getHorizontalCoords(location, date);
	HorizontalCoords saturnCoords = saturn.getHorizontalCoords(location, date);
	HorizontalCoords uranusCoords = uranus.getHorizontalCoords(location, date);
	HorizontalCoords neptuneCoords = neptune.getHorizontalCoords(location, date);
	return 0;
}

void printUsage(const char* progname)
{
	cerr << "Usage: " << progname << " -d date -g longitude -t latitude -f outputFile"	 << endl;
	cerr << "\t-d date: The date and time to calculate the map." << endl;
	cerr << "\t-g longitude: The longitude to calculate the map. Must be in degrees." << endl;
	cerr << "\t-t latitude: The latitude to calculate the map. Must be in degrees." << endl;
	cerr << "\t-f outputFile: The name of the output file." << endl;
}

bool parseDegree(const char* str, tsc::Math::Degree& deg)
{
	istringstream floatConversion(str);
	float f;

	floatConversion >> f;

	if (floatConversion.fail())
	{
		return false;
	}

	deg = tsc::Math::Degree(f);
	return true;
}

bool parseDate(const char* str, tsc::Time::Stardate& date)
{
	int year, month, day, hour, minute, second;

	if (sscanf(str, "%i/%i/%i %i:%i:%i", &year, &month, &day, &hour, &minute, &second) == 6)
	{
		date = tsc::Time::Stardate::fromDate(tsc::Time::ChristianDate(year, month, day, hour, minute, second));
	}
	else if (sscanf(str, "%i/%i/%i %i:%i", &year, &month, &day, &hour, &minute) == 5)
	{
		date = tsc::Time::Stardate::fromDate(tsc::Time::ChristianDate(year, month, day, hour, minute, 0));
	}
	else if (sscanf(str, "%i/%i/%i", &year, &month, &day) == 3)
	{
		date = tsc::Time::Stardate::fromDate(tsc::Time::ChristianDate(year, month, day, 0, 0, 0));
	}
	else
	{
		return false;
	}

	return true;
}

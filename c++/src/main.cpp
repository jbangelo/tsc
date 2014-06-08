/**
 * File: main.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: The entry point to the program
 *
 * The MIT License (MIT)
 *
 * Copyright (c) 2014 jbangelo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#include <iostream>
#include "sqlite3.h"
#include "Math/Degree.h"
#include "Time/Stardate.h"
#include "SkyObject/Planet.h"

using tsc::Math::Degree;
using tsc::Time::Stardate;
using tsc::Time::ChristianDate;
using tsc::SkyObject::Planet;
using namespace std;

int main(int argc, char** argv)
{
	Degree d1(90.0), d2(-90.0);

	cout.setf(ostream::fixed);

	cout << "d1 = " << d1.degStr() << endl;
	cout << "d2 = " << d2.hmsStr() << endl;
	cout << "d1 + d2 = " << (d1+d2).degStr() << endl;
	cout << "d1 - d2 = " << (d1-d2).degStr() << endl;
	cout << "d1 * d2 = " << (d1*d2).degStr() << endl;
	cout << "d1 / d2 = " << (d1/d2).degStr() << endl;

	Stardate sd1 = Stardate::fromDate(ChristianDate(2000, 1, 1, 12, 0, 0));
	Stardate sd2(2451179.5);
	Stardate sd3 = Stardate::fromDate(ChristianDate(1987, 1, 27));
	Stardate sd4(2446966.0);
	Stardate sd5 = Stardate::fromDate(ChristianDate(1988, 1, 27));
	Stardate sd6(2447332.0);
	Stardate sd7 = Stardate::fromDate(ChristianDate(1900, 1, 1));
	Stardate sd8(2305447.5);
	Stardate sd9 = Stardate::fromDate(ChristianDate(1600, 12, 31));
	Stardate sd10(2026871.8);
	Stardate sd11 = Stardate::fromDate(ChristianDate(-123, 12, 31));
	Stardate sd12(1676497.5);
	Stardate sd13 = Stardate::fromDate(ChristianDate(-1000, 7, 12, 12, 0, 0));
	Stardate sd14(1355866.5);
	Stardate sd15(1355671.4);
	Stardate sd16 = Stardate::fromDate(ChristianDate(-4712, 1, 1, 12, 0, 0));
	Stardate sd17(2436116.31);

	cout << "sd1 = " << sd1.toGregorianDateStr() << ", " << sd1.toJD() << endl;
	cout << "sd2 = " << sd2.toGregorianDateStr() << ", " << sd2.toJD() << endl;
	cout << "sd3 = " << sd3.toGregorianDateStr() << ", " << sd3.toJD() << endl;
	cout << "sd4 = " << sd4.toGregorianDateStr() << ", " << sd4.toJD() << endl;
	cout << "sd5 = " << sd5.toGregorianDateStr() << ", " << sd5.toJD() << endl;
	cout << "sd6 = " << sd6.toGregorianDateStr() << ", " << sd6.toJD() << endl;
	cout << "sd7 = " << sd7.toGregorianDateStr() << ", " << sd7.toJD() << endl;
	cout << "sd8 = " << sd8.toGregorianDateStr() << ", " << sd8.toJD() << endl;
	cout << "sd9 = " << sd9.toGregorianDateStr() << ", " << sd9.toJD() << endl;
	cout << "sd10 = " << sd10.toGregorianDateStr() << ", " << sd10.toJD() << endl;
	cout << "sd11 = " << sd11.toGregorianDateStr() << ", " << sd11.toJD() << endl;
	cout << "sd12 = " << sd12.toGregorianDateStr() << ", " << sd12.toJD() << endl;
	cout << "sd13 = " << sd13.toGregorianDateStr() << ", " << sd13.toJD() << endl;
	cout << "sd14 = " << sd14.toGregorianDateStr() << ", " << sd14.toJD() << endl;
	cout << "sd15 = " << sd15.toGregorianDateStr() << ", " << sd15.toJD() << endl;
	cout << "sd16 = " << sd16.toGregorianDateStr() << ", " << sd16.toJD() << endl;
	cout << "sd16 = " << sd17.toGregorianDateStr() << ", " << sd17.toJD() << endl;

	sqlite3* db;

	if (sqlite3_open("../resources/Planets/planet.db", &db) != SQLITE_OK)
	{
		cout << "Error opening up the database file!" << endl;
		return 1;
	}

	cout << "Mercury:" << endl;
	Planet mercury(Planet::MERCURY, db);
	cout << "Venus:" << endl;
	Planet venus(Planet::VENUS, db);
	cout << "Earth:" << endl;
	Planet earth(Planet::EARTH, db);
	cout << "Mars:" << endl;
	Planet mars(Planet::MARS, db);
	cout << "Jupiter:" << endl;
	Planet jupiter(Planet::JUPITER, db);
	cout << "Saturn:" << endl;
	Planet saturn(Planet::SATURN, db);
	cout << "Uranus:" << endl;
	Planet uranus(Planet::URANUS, db);
	cout << "Neptune:" << endl;
	Planet neptune(Planet::NEPTUNE, db);

	return 0;
}

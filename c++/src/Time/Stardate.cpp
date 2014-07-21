/**
 * File: Stardate.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines a class that keeps track of time that can be represented
 *		in several different caledars and time zones.
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
#include <iomanip>
#include <sstream>
#include "Time/Stardate.h"
#include "Time/NutationTerms.h"

using tsc::Time::Stardate;
using tsc::Time::NutationTerms;
using tsc::Time::ChristianDate;
using tsc::Math::AstroMath;

Stardate::Stardate(real JD) :
	_JD(JD)
{

}

Stardate::~Stardate()
{

}

Stardate Stardate::fromDate(ChristianDate date)
{
	if (date.year >= 1582)
	{
		return fromGregorianDate(date);
	}
	else
	{
		return fromJulianDate(date);
	}
}

Stardate Stardate::fromJulianDate(ChristianDate date)
{
	real D = date.day + (date.hour + (date.minute + (date.second/60.0))/60.0)/24.0;

	if (date.month <= 2)
	{
		date.year -= 1;
		date.month += 12;
	}
	
	return Stardate(int(365.25*(date.year+4716)) + int(30.6001*(date.month+1)) + D - 1524.5);
}

Stardate Stardate::fromGregorianDate(ChristianDate date)
{
	real D = date.day + (date.hour + (date.minute + (date.second/60.0))/60.0)/24.0;
	integer A = 0, B = 0;

	if (date.month <= 2)
	{
		date.year -= 1;
		date.month += 12;
	}
	
	A = int(date.year/100);
	B = 2 - A + int(A/4);
	
	return Stardate(int(365.25*(date.year+4716)) + int(30.6001*(date.month+1)) + D + B - 1524.5);
}

void Stardate::addDays(integer days)
{
	_JD += days;
}

real Stardate::toJD() const
{
	return _JD;
}

real Stardate::J2000() const
{
	return _JD-2451545.0L;
}

real Stardate::J2000c() const
{
	return this->J2000()/36525.0L;
}

real Stardate::J2000m() const
{
	return J2000m(0.0);
}

real Stardate::J2000m(real dt) const
{
	return (J2000() - dt)/365250.0L;
}

bool Stardate::isJulian() const
{
	return ((*this) < GREGORIAN_START);
}

bool Stardate::isGregorian() const
{
	return !this->isJulian();
}

Degree Stardate::meanSidereal()
{
	real T = this->J2000c();
	real meanSidereal = 280.46061838 + 360.98564736629*(this->_JD-2451545.0) + 0.000387933*T*T - (T*T*T)/38710000.0;

	while (meanSidereal < 0.0)
	{
		meanSidereal += 360.0;
	}

	while (meanSidereal > 360.0)
	{
		meanSidereal -= 360.0;
	}

	return Degree(meanSidereal);
}

void Stardate::nutation(Degree& Psi, Degree& E)
{
	this->nutation(Psi, E, true);
}

void Stardate::nutation(Degree& Psi, Degree& E, bool trueObliq)
{
	real T = this->J2000c();

	real Omega = 125.04452 - 1934.136261*T + 0.0020708*T*T + (T*T*T)/450000;
	real D = (297.85036 +445267.111480*T - 0.0019142*T*T + (T*T*T)/189474);
	real M = (357.52772 + 35999.050340*T - 0.0001603*T*T - (T*T*T)/300000);
	real Mp= (134.96298 + 477198.867398*T + 0.0086972*T*T + (T*T*T)/56250);
	real F = (93.27191 + 483202.017538*T - 0.0036825*T*T + (T*T*T)/327270);
	real dPsi = 0.0, dE = 0.0;

	for (int i = 0; i < tsc::Time::NutationTermCount; i++)
	{
		real *t = NutationTerms[i];
		Degree arg(D*t[0] + M*t[1] + Mp*t[2] + F*t[3] + Omega*t[4]);
		dPsi += (t[5]+(t[6]*T))*Degree::sin(arg);
		dE += (t[7]+(t[8]*T))*Degree::cos(arg);
	}

	if (trueObliq)
	{
		E = this->meanObliquity() + Degree::fromDMS(0,0,dE*0.0001);
	}
	else
	{
		E = Degree::fromDMS(0,0,dE*0.0001);
	}

	Psi = Degree::fromHMS(0,0,dPsi*0.0001);
}

Degree Stardate::meanObliquity()
{

	real T = this->J2000c();
	real U = T/100.0;

	Degree E0 = Degree::fromDMS(23,26,21.448)-Degree::fromDMS(0,0,4680.93)*U - 1.55*U*U + 1999.25*U*U*U - 51.38*AstroMath::power(U,4) - 249.67*AstroMath::power(U,5) - 39.05*AstroMath::power(U,6) + 7.12*AstroMath::power(U,7) + 27.87*AstroMath::power(U,8) + 5.79*AstroMath::power(U,9) + 2.45*AstroMath::power(U,10);

	return E0;
}

Degree Stardate::apparentSidereal()
{
	Degree Psi, E, nutation;

	this->nutation(Psi, E, true);

	nutation = (Psi/15.0)*Degree(Degree::cos(E));

	return this->meanSidereal() + nutation;
}

ChristianDate Stardate::toGregorianDate() const
{
	ChristianDate date(0,0,0,0,0,0);
	real jdMod = this->_JD + 0.5;
	integer Z = int(jdMod);
	real F = jdMod - Z;
	integer A = 0, B = 0, C = 0, D = 0, E = 0;
	real fullDay = 0.0, dayFraction = 0.0;

	if (Z < 2299161)
	{
		A = Z;
	}
	else
	{
		integer alpha = AstroMath::INT((Z - 1867216.25)/36524.25);
		A = Z + 1 + alpha - AstroMath::INT(alpha/4.0);
	}

	B = A + 1524;
	C = AstroMath::INT((B - 122.1)/365.25);
	D = AstroMath::INT(365.25*C);
	E = AstroMath::INT((B-D)/30.6001);

	fullDay = B - D - AstroMath::INT(30.6001*E) + F;

	if (E < 14)
	{
		date.month = E - 1;
	}
	else
	{
		date.month = E - 13;
	}

	if (date.month > 2)
	{
		date.year = C - 4716;
	}
	else
	{
		date.year = C - 4715;
	}

	date.day = AstroMath::INT(fullDay);
	dayFraction = fullDay - date.day;

	date.hour = AstroMath::INT(dayFraction*24.0);
	dayFraction = (dayFraction*24.0) - date.hour;
	date.minute = AstroMath::INT(dayFraction*60.0);
	dayFraction = (dayFraction*60.0) - date.minute;
	date.second = AstroMath::INT(dayFraction * 60.0);

	return date;
}

std::string Stardate::toGregorianDateStr() const
{
	std::string monthStr;
	std::ostringstream oss;

	ChristianDate date = this->toGregorianDate();

	switch (date.month)
	{
		case 1:
			monthStr = "January";
			break;
		case 2:
			monthStr = "February";
			break;
		case 3:
			monthStr = "March";
			break;
		case 4:
			monthStr = "April";
			break;
		case 5:
			monthStr = "May";
			break;
		case 6:
			monthStr = "June";
			break;
		case 7:
			monthStr = "July";
			break;
		case 8:
			monthStr = "August";
			break;
		case 9:
			monthStr = "September";
			break;
		case 10:
			monthStr = "October";
			break;
		case 11:
			monthStr = "November";
			break;
		case 12:
			monthStr = "December";
			break;
		default:
			monthStr = "Invalid Month Value";
			break;
	}

	oss << monthStr << " " << date.day << ", ";
	oss << AstroMath::absoluteValue(date.year);
	oss << (AstroMath::sign(date.year)==-1?" B.C.E. ":" C.E. ");
	oss << date.hour << ":" << date.minute << ":" << date.second;

	return oss.str();
}

bool Stardate::operator==(Stardate& param) const
{
	return ((this->_JD - param._JD) < 0.0001);
}

bool Stardate::operator!=(Stardate& param) const
{
	return ((this->_JD - param._JD) >= 0.0001);
}

bool Stardate::operator<(Stardate& param) const
{
	return (this->_JD < param._JD);
}

bool Stardate::operator>(Stardate& param) const
{
	return (this->_JD > param._JD);
}

bool Stardate::operator<=(Stardate& param) const
{
	return (this->_JD <= param._JD);
}

bool Stardate::operator>=(Stardate& param) const
{
	return (this->_JD >= param._JD);
}

bool Stardate::operator==(const Stardate& param) const
{
	return ((this->_JD - param._JD) < 0.0001);
}

bool Stardate::operator!=(const Stardate& param) const
{
	return ((this->_JD - param._JD) >= 0.0001);
}

bool Stardate::operator<(const Stardate& param) const
{
	return (this->_JD < param._JD);
}

bool Stardate::operator>(const Stardate& param) const
{
	return (this->_JD > param._JD);
}

bool Stardate::operator<=(const Stardate& param) const
{
	return (this->_JD <= param._JD);
}

bool Stardate::operator>=(const Stardate& param) const
{
	return (this->_JD >= param._JD);
}

std::ostream& tsc::Time::operator<<(std::ostream& stream, const Stardate& param)
{
        //stream << std::setprecision(30);
	stream << param.toJD() << "(" << param.toGregorianDateStr() << ")";
	return stream;
}

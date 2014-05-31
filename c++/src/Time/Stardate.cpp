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

#include <sstream>
#include "Time/Stardate.h"

using tsc::Time::Stardate;
using tsc::Math::AstroMath;

Stardate::Stardate(real JD) :
	_JD(JD)
{

}

Stardate::~Stardate()
{

}

Stardate Stardate::fromDate(integer year, integer month, integer day, integer hour, integer minute, integer second)
{
	if (year >= 1582)
	{
		return fromGregorianDate(year, month, day, hour, minute, second);
	}
	else
	{
		return fromJulianDate(year, month, day, hour, minute, second);
	}
}

Stardate Stardate::fromJulianDate(integer year, integer month, integer day, integer hour, integer minute, integer second)
{
	real D = day + (hour + (minute + (second/60.0))/60.0)/24.0;

	if (month <= 2)
	{
		year -= 1;
		month += 12;
	}
	
	return Stardate(int(365.25*(year+4716)) + int(30.6001*(month+1)) + D - 1524.5);
}

Stardate Stardate::fromGregorianDate(integer year, integer month, integer day, integer hour, integer minute, integer second)
{
	real D = day + (hour + (minute + (second/60.0))/60.0)/24.0;
	integer A = 0, B = 0;

	if (month <= 2)
	{
		year -= 1;
		month += 12;
	}
	
	A = int(year/100);
	B = 2 - A + int(A/4);
	
	return Stardate(int(365.25*(year+4716)) + int(30.6001*(month+1)) + D + B - 1524.5);
}

void Stardate::addDays(integer days)
{
	_JD += days;
}

real Stardate::toJD()
{
	return _JD;
}

real Stardate::J2000()
{
	return _JD-2451545.0L;
}

real Stardate::J2000c()
{
	return this->J2000()/36525.0L;
}

real Stardate::J2000m()
{
	return this->J2000()/365250.0L;
}

bool Stardate::isJulian()
{
	return ((*this) < GREGORIAN_START);
}

bool Stardate::isGregorian()
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

void Stardate::nutation(real& dPsi, real& dE)
{
/*
	real T = this->J2000c();

	real Omega = 125.04452 - 1934.136261*T + 0.0020708*T*T + (T*T*T)/450000;
	real D = (297.85036 +445267.111480*T - 0.0019142*T*T + (T*T*T)/189474);
	real M = (357.52772 + 35999.050340*T - 0.0001603*T*T - (T*T*T)/300000);
	real Mp= (134.96298 + 477198.867398*T + 0.0086972*T*T + (T*T*T)/56250);
	real F = (93.27191 + 483202.017538*T - 0.0036825*T*T + (T*T*T)/327270);

	real dPsi = 0.0;
	real dE = 0.0;

	for t in nutTerms:
		arg = Degree.new(D*t[0] + M*t[1] + Mp*t[2] + F*t[3] + Omega*t[4])
		dPsi += (t[5]+(t[6]*T))*astro.sin(arg)
		dE += (t[7]+(t[8]*T))*astro.cos(arg)

	if trueObliq:
		dE = self.meanObliquity() + Degree.new_DMS(0,0,dE*0.0001)
	else:
		dE = degree.new_DMS(0,0,dE*0.0001)

	dPsi = Degree.new_HMS(0,0,dPsi*0.0001)

	return (dPsi,dE)
*/
}

real Stardate::meanObliquity()
{
/*
	real T = this->J2000c();
	real U = T/100.0;

	real E0 = Degree.new_DMS(23,26,21.448)-Degree.new_DMS(0,0,4680.93)*U - 1.55*U*U + 1999.25*U*U*U - 51.38*pow(U,4) - 249.67*pow(U,5) - 39.05*pow(U,6) + 7.12*pow(U,7) + 27.87*pow(U,8) + 5.79*pow(U,9) + 2.45*pow(U,10);

	return E0
*/
	return 0.0;
}

real Stardate::apparentSidereal()
{
/*
	(dPsi, E) = self.nutation(True)

	nutation = (dPsi/15.0)*astro.cos(E)

	return self.meanSidereal() + nutation
*/
	return 0.0;
}

void Stardate::toGregorianDate(integer& year, integer& month, real& day)
{
	real jdMod = this->_JD + 0.5;
	integer Z = int(jdMod);
	real F = jdMod - Z;
	integer A = 0, B = 0, C = 0, D = 0, E = 0;

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

	day = B - D - AstroMath::INT(30.6001*E) + F;

	if (E < 14)
	{
		month = E - 1;
	}
	else
	{
		month = E - 13;
	}

	if (month > 2)
	{
		year = C - 4716;
	}
	else
	{
		year = C - 4715;
	}

}

void Stardate::toGregorianDate(integer& year, integer& month, integer& day,
	integer& hour, integer& minute, integer& second)
{
	real fullDay = 0.0, dayFraction = 0.0;
	this->toGregorianDate(year, month, fullDay);

	day = AstroMath::INT(fullDay);
	dayFraction = fullDay - day;

	hour = AstroMath::INT(dayFraction*24.0);
	dayFraction = (dayFraction*24.0) - hour;
	minute = AstroMath::INT(dayFraction*60.0);
	dayFraction = (dayFraction*60.0) - minute;
	second = AstroMath::INT(dayFraction * 60.0);
}

std::string Stardate::toGregorianDateStr()
{
	integer year, month, day, hour, minute, second;

	std::string monthStr;
	std::ostringstream oss;

	this->toGregorianDate(year, month, day, hour, minute, second);

	switch (month)
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

	oss << monthStr << " " << day << ", " << AstroMath::absoluteValue(year) << (AstroMath::sign(year)==-1?" B.C.E. ":" C.E. ") << hour << ":" << minute << ":" << second;

	return oss.str();
}

bool Stardate::operator==(Stardate& param)
{
	return (this->_JD == param._JD);
}

bool Stardate::operator!=(Stardate& param)
{
	return (this->_JD != param._JD);
}

bool Stardate::operator<(Stardate& param)
{
	return (this->_JD < param._JD);
}

bool Stardate::operator>(Stardate& param)
{
	return (this->_JD > param._JD);
}

bool Stardate::operator<=(Stardate& param)
{
	return (this->_JD <= param._JD);
}

bool Stardate::operator>=(Stardate& param)
{
	return (this->_JD >= param._JD);
}

bool Stardate::operator==(const Stardate& param)
{
	return (this->_JD == param._JD);
}

bool Stardate::operator!=(const Stardate& param)
{
	return (this->_JD != param._JD);
}

bool Stardate::operator<(const Stardate& param)
{
	return (this->_JD < param._JD);
}

bool Stardate::operator>(const Stardate& param)
{
	return (this->_JD > param._JD);
}

bool Stardate::operator<=(const Stardate& param)
{
	return (this->_JD <= param._JD);
}

bool Stardate::operator>=(const Stardate& param)
{
	return (this->_JD >= param._JD);
}


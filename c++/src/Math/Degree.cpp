/**
 * File: Degree.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines a class used to store and manipulate values in degrees
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
#include <sstream>
#include "Math/Degree.h"
#include "Math/AstroMath.h"

using tsc::Math::Degree;
using tsc::Math::AstroMath;

Degree::Degree(real value) : 
	_value(value)
{
	updateDMS();
	updateHMS();
}

Degree::Degree() :
	_value(0.0)
{
	updateHMS();
	updateDMS();
}

Degree::~Degree()
{

}

Degree Degree::fromRad(real value)
{
	return Degree(value*(180.0/AstroMath::pi));
}

Degree Degree::fromDMS(real deg, real arcminute, real arcsecond)
{
	return Degree(deg+(AstroMath::sign(deg)*arcminute/60.0)+(AstroMath::sign(deg)*arcsecond/3600.0));
}

Degree Degree::fromHMS(real hour, real minute, real second)
{
	return Degree((hour+(AstroMath::sign(hour)*minute/60.0)+(AstroMath::sign(hour)*second/3600.0))*15.0);
}

real Degree::deg()
{
	return _value;
}

real Degree::rad()
{
	return _value*(AstroMath::pi/180.0);
}

void Degree::abs()
{
	_value = AstroMath::absoluteValue(_value);
}

integer Degree::arcMinute()
{
	return _arcMinute;
}

real Degree::arcSecond()
{
	return _arcSecond;
}

integer Degree::hour()
{
	return _hour;
}

integer Degree::minute()
{
	return _minute;
}

real Degree::second()
{
	return _second;
}

std::string Degree::degStr()
{
	std::ostringstream oss;
	oss << _value << "°";
	return oss.str();
}

std::string Degree::dmStr()
{
	std::ostringstream oss;
	oss << _degree << "°" << _arcMinute+(_arcSecond/60.0) << "'";
	return oss.str();
}

std::string Degree::dmsStr()
{
	std::ostringstream oss;
	oss << _degree << "°" << _arcMinute << "'" << _arcSecond << "\"";
	return oss.str();
}

std::string Degree::hourStr()
{
	std::ostringstream oss;
	oss << _hour + (_minute + (_second/60.0)/60.0) << "h";
	return oss.str();
}

std::string Degree::hmStr()
{
	std::ostringstream oss;
	oss << _hour << "h" << _minute + (_second/60.0) << "m";
	return oss.str();
}

std::string Degree::hmsStr()
{
	std::ostringstream oss;
	oss << _hour << "h" << _minute << "m" << _second << "s";
	return oss.str();
}

void Degree::normalize()
{
	if (_value < 0.0L)
	{
		_value += (360.0L * (AstroMath::INT(_value/-360.0L)+1));
	}
	else if (_value >= 360.0L)
	{
		_value -= (360.0L * AstroMath::INT(_value/360.0));
	}
	updateHMS();
	updateDMS();
}

void Degree::normalizeLatitude()
{
	if (_value < -90.0L)
	{
		_value += (180.0L * (AstroMath::INT(_value/-180.0L)+1));
	}
	else if (_value > 90.0L)
	{
		_value -= (180.0L * AstroMath::INT(_value/180.0));
	}
	updateHMS();
	updateDMS();
}

real Degree::sin(Degree& param)
{
	return AstroMath::sine(param.rad());
}

real Degree::cos(Degree& param)
{
	return AstroMath::cosine(param.rad());
}

real Degree::tan(Degree& param)
{
	return AstroMath::tangent(param.rad());
}

Degree Degree::asin(real param)
{
	return Degree::fromRad(AstroMath::arcsine(param));
}

Degree Degree::acos(real param)
{
	return Degree::fromRad(AstroMath::arccosine(param));
}

Degree Degree::atan(real param)
{
	return Degree::fromRad(AstroMath::arctangent(param));
}

Degree Degree::atan2(real param1, real param2)
{
	return Degree::fromRad(AstroMath::arctangent2(param1, param2));
}

Degree Degree::operator+(const Degree& param) const
{
	return Degree(_value + param._value);
}

Degree Degree::operator-(const Degree& param) const
{
	return Degree(_value - param._value);
}

Degree Degree::operator*(const Degree& param) const
{
	return Degree(_value * param._value);
}

Degree Degree::operator/(const Degree& param) const
{
	return Degree(_value / param._value);
}

Degree Degree::operator+=(const Degree& param) const
{
	return Degree(_value + param._value);
}

Degree Degree::operator-=(const Degree& param) const
{
	return Degree(_value - param._value);
}

Degree Degree::operator*=(const Degree& param) const
{
	return Degree(_value * param._value);
}

Degree Degree::operator/=(const Degree& param) const
{
	return Degree(_value / param._value);
}

bool Degree::operator<=(const Degree& param) const
{
	return (_value <= param._value);
}

bool Degree::operator>=(const Degree& param) const
{
	return (_value >= param._value);
}

bool Degree::operator==(const Degree& param) const
{
	return (_value == param._value);
}

bool Degree::operator<(const Degree& param) const
{
	return (_value < param._value);
}

bool Degree::operator>(const Degree& param) const
{
	return (_value > param._value);
}

bool Degree::operator!=(const Degree& param) const
{
	return (_value != param._value);
}

void Degree::updateDMS()
{
	_degree = int(_value);
	_arcFraction = AstroMath::absoluteValue(_value - _degree);
	_arcMinute = int(_arcFraction*60.0);
	_arcSecond = (_arcFraction*60.0 - _arcMinute)*60.0;
}

void Degree::updateHMS()
{
	_hour = int(_value/15.0);
	_fraction = AstroMath::absoluteValue((_value/15.0) - _hour);
	_minute = int(_fraction*60.0);
	_second = (_fraction*60.0 - _minute)*60.0;
}

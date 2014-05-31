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
#include <sstream>
#include "Math/Degree.h"
#include "Math/AstroMath.h"

using tsc::Math::Degree;
using tsc::Math::AstroMath;

Degree::Degree(real value) : 
	_value(value)
{
	this->updateDMS();
	this->updateHMS();
}

Degree::~Degree()
{

}

Degree Degree::fromRad(real value)
{
	return Degree(value*(180.0/AstroMath::pi));
}

real Degree::deg()
{
	return this->_value;
}

real Degree::rad()
{
	return this->_value*(AstroMath::pi/180.0);
}

void Degree::abs()
{
	this->_value = AstroMath::absoluteValue(this->_value);
}

integer Degree::arcMinute()
{
	return this->_arcMinute;
}

real Degree::arcSecond()
{
	return this->_arcSecond;
}

integer Degree::hour()
{
	return this->_hour;
}

integer Degree::minute()
{
	return this->_minute;
}

real Degree::second()
{
	return this->_second;
}

std::string Degree::degStr()
{
	std::ostringstream oss;
	oss << this->_value << "°";
	return oss.str();
}

std::string Degree::dmStr()
{
	std::ostringstream oss;
	oss << this->_degree << "°" << this->_arcMinute+(this->_arcSecond/60.0) << "'";
	return oss.str();
}

std::string Degree::dmsStr()
{
	std::ostringstream oss;
	oss << this->_degree << "°" << this->_arcMinute << "'" << this->_arcSecond << "\"";
	return oss.str();
}

std::string Degree::hourStr()
{
	std::ostringstream oss;
	oss << this->_hour + (this->_minute + (this->_second/60.0)/60.0) << "h";
	return oss.str();
}

std::string Degree::hmStr()
{
	std::ostringstream oss;
	oss << this->_hour << "h" << this->_minute + (this->_second/60.0) << "m";
	return oss.str();
}

std::string Degree::hmsStr()
{
	std::ostringstream oss;
	oss << this->_hour << "h" << this->_minute << "m" << this->_second << "s";
	return oss.str();
}

void Degree::normalize()
{
	while (this->_value < 0.0)
	{
		this->_value += 360.0;
	}

	while (this->_value > 360.0)
	{
		this->_value -= 360.0;
	}
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

Degree Degree::operator+(const Degree& param)
{
	return Degree(this->_value + param._value);
}

Degree Degree::operator-(const Degree& param)
{
	return Degree(this->_value - param._value);
}

Degree Degree::operator*(const Degree& param)
{
	return Degree(this->_value * param._value);
}

Degree Degree::operator/(const Degree& param)
{
	return Degree(this->_value / param._value);
}

bool Degree::operator<=(const Degree& param)
{
	return (this->_value <= param._value);
}

bool Degree::operator>=(const Degree& param)
{
	return (this->_value >= param._value);
}

bool Degree::operator==(const Degree& param)
{
	return (this->_value == param._value);
}

void Degree::updateDMS()
{
	this->_degree = int(this->_value);
	this->_arcFraction = AstroMath::absoluteValue(this->_value - this->_degree);
	this->_arcMinute = int(this->_arcFraction*60.0);
	this->_arcSecond = (this->_arcFraction*60.0 - this->_arcMinute)*60.0;
}

void Degree::updateHMS()
{
	this->_hour = int(this->_value/15.0);
	this->_fraction = AstroMath::absoluteValue((this->_value/15.0) - this->_hour);
	this->_minute = int(this->_fraction*60.0);
	this->_second = (this->_fraction*60.0 - this->_minute)*60.0;
}

/**
 * File: Planet.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines an interface for all Planet objects to follow
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
#include "SkyObject/Planet.h"
#include "Math/AstroMath.h"

using tsc::SkyObject::Planet;
using tsc::Math::AstroMath;

Planet::Planet() : 
	SkyObject(),
	_heliocentricEcliptic(),
	_geocentricCartesian(),
	_geocentricEcliptic(),
	_i(0.0),
	_k(0.0),
	_dt(0.0),
	_heliocentricEclipticDelay(),
	_geocentricCartesianDelay(),
	_geocentricEclipticDelay(),
	_LTerms(),
	_BTerms(),
	_RTerms(),
	_lastUsedDate(0)
{

}

Planet::~Planet()
{

}

void Planet::calculatePosition(Stardate date)
{
	real millenia = date.J2000m();

	calculateHeliocentricEclipticCoords(millenia);
	calculateGeocentricCartesianCoords();
	calculateGeocentricEclipticCoords();
	calculateGeocentricEquatorialCoords();
	calculateLightDelay(date);
	calculateIlluminatedFraction();
	calcMag();
}

EclipticCoords Planet::getHeliocentricEclipticCoords()
{
	return _heliocentricEcliptic;
}

EclipticCoords Planet::getGeocentricEclipticCoords()
{
	return _geocentricEcliptic;
}

CartesianCoords Planet::getGeocentricCartesianCoords()
{
	return _geocentricCartesian;
}

real Planet::getLightDelay()
{
	return _dt;
}

real Planet::getIlluminatedFraction()
{
	return _k;
}

Degree Planet::getPhaseAngle()
{
	return _i;
}

real Planet::sumTerms(vector<vector<OrbitalTerm> > terms, real millenia)
{
	real total = 0.0;

	for (size_t i = 0; i < terms.size(); i++)
	{
		real subTerm = 0.0;
		for (size_t j = 0; j < terms[i].size(); j++)
		{
			real A = terms[i][j].A;
			real B = terms[i][j].B;
			real C = terms[i][j].C;
			subTerm += A*AstroMath::cosine(B + C*millenia);
		}
		total += subTerm*AstroMath::pow(millenia, static_cast<real>(i));
	}

	return total/(AstroMath::pow(10.0,8.0));
}

void Planet::calculateHeliocentricEclipticCoords(real millenia)
{
	Degree l, b;
	real r;

	l = Degree::fromRad(Planet::sumTerms(_LTerms, millenia));
	b = Degree::fromRad(Planet::sumTerms(_BTerms, millenia));
	r = Planet::sumTerms(_RTerms, millenia);

	_heliocentricEcliptic.lambda = l;
	_heliocentricEcliptic.beta = b;
	_heliocentricEcliptic.delta = r;
}

void Planet::calculateGeocentricCartesianCoords()
{
	EclipticCoords earthCoords;// = _earth.getHeliocentricEclipticCoords();
	real x, y, z;

	x = _heliocentricEcliptic.delta*Degree::cos(_heliocentricEcliptic.beta)*Degree::cos(_heliocentricEcliptic.lambda) - earthCoords.delta*Degree::cos(earthCoords.beta)*Degree::cos(earthCoords.lambda);

	y = _heliocentricEcliptic.delta*Degree::cos(_heliocentricEcliptic.beta)*Degree::sin(_heliocentricEcliptic.lambda) - earthCoords.delta*Degree::cos(earthCoords.beta)*Degree::sin(earthCoords.lambda);

	z = _heliocentricEcliptic.delta*Degree::sin(_heliocentricEcliptic.beta) - earthCoords.delta*Degree::sin(earthCoords.beta);

	_geocentricCartesian.x = x;
	_geocentricCartesian.y = y;
	_geocentricCartesian.z = z;
}

void Planet::calculateGeocentricEclipticCoords()
{
	real x = _geocentricCartesian.x;
	real y = _geocentricCartesian.y;
	real z = _geocentricCartesian.z;
	_geocentricEcliptic.lambda = Degree::atan2(y, x);
	_geocentricEcliptic.lambda.normalize();

	_geocentricEcliptic.beta = Degree::atan2(z, AstroMath::sqrt(x*x + y*y));

	_geocentricEcliptic.delta = AstroMath::sqrt(x*x + y*y + z*z);
}

void Planet::calculateGeocentricEquatorialCoords()
{
	Degree ec(23.4392911);
	Degree ra, dec, l, b;

	l = _geocentricEcliptic.lambda;
	b = _geocentricEcliptic.beta;

	ra = Degree::atan2(Degree::sin(l)*Degree::cos(ec) - Degree::tan(b)*Degree::sin(ec), Degree::cos(l));
	ra.normalize();

	dec = Degree::asin(Degree::sin(b)*Degree::cos(ec) + Degree::cos(b)*Degree::sin(ec)*Degree::sin(l));

	_geocentricEquatorial.ra = ra;
	_geocentricEquatorial.dec = dec;
}

void Planet::calculateLightDelay(Stardate date)
{

}

void Planet::calculateIlluminatedFraction()
{
	EclipticCoords earthCoords;// = _earth.getHeliocentricEclipticCoords();

	_i = Degree::acos((AstroMath::pow(_heliocentricEcliptic.delta,2) + AstroMath::pow(_geocentricEcliptic.delta,2) - AstroMath::pow(earthCoords.delta,2))/(2*_heliocentricEcliptic.delta*_geocentricEcliptic.delta));

	_k = (1 + Degree::cos(_i))/2;
}
			

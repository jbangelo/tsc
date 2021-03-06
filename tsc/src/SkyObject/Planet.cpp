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
#include <iostream>
#include <string>
#include "SkyObject/Planet.h"
#include "Math/AstroMath.h"
#include "Utils/ToString.h"

using std::vector;
using tsc::Math::AstroMath;
using tsc::Math::CartesianCoords;
using tsc::Math::Degree;
using tsc::Math::EquatorialCoords;
using tsc::Math::EclipticCoords;
using tsc::Math::OrbitalTerm;
using tsc::SkyObject::Planet;
using tsc::SkyObject::SkyObject;
using tsc::Utils::IDataStorage;

Planet::Planet(PlanetCode pid, IDataStorage& dataStorage, Planet& earth)
        : SkyObject(),
          _pid(pid),
          _dataStorage(dataStorage),
          _earth(earth),
          _isEarth(false),
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
          _RTerms()
{
    loadData();
}

Planet::~Planet()
{

}

void Planet::calculatePosition(Stardate date)
{
	if (!_isEarth)
	{
		_earth.calculatePosition(date);
	}

    real millenia = date.J2000m();

    _heliocentricEcliptic = calculateHeliocentricEclipticCoords(millenia);
    _geocentricCartesian = calculateGeocentricCartesianCoords(
            _heliocentricEcliptic);
    _geocentricEcliptic = calculateGeocentricEclipticCoords(
            _geocentricCartesian);
    _geocentricEquatorial = calculateGeocentricEquatorialCoords(
            _geocentricEcliptic);
    calculateLightDelay(date);
    calculateIlluminatedFraction();
    calcMag();

    _dist = _geocentricEclipticDelay.delta;
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

real Planet::sumTerms(vector<vector<OrbitalTerm>*> terms, real millenia)
{
    real total = 0.0;

    for (size_t i = 0; i < terms.size(); i++)
    {
        real subTerm = 0.0;
        for (size_t j = 0; j < terms[i]->size(); j++)
        {
            real A = terms[i]->at(j).A;
            real B = terms[i]->at(j).B;
            real C = terms[i]->at(j).C;
            subTerm += A * AstroMath::cosine(B + C * millenia);
        }
        //std::cout << subTerm << std::endl;
        total += subTerm * AstroMath::power(millenia, static_cast<real>(i));
    }

    return total;
}

EclipticCoords Planet::calculateHeliocentricEclipticCoords(real millenia)
{
    EclipticCoords newCoords;

    newCoords.lambda = Degree::fromRad(sumTerms(_LTerms, millenia));
    newCoords.lambda.normalize();
    newCoords.beta = Degree::fromRad(sumTerms(_BTerms, millenia));
    newCoords.beta.normalizeLatitude();
    newCoords.delta = sumTerms(_RTerms, millenia);

    return newCoords;
}

CartesianCoords Planet::calculateGeocentricCartesianCoords(
        EclipticCoords heliocentricCoords)
{
    EclipticCoords earthCoords;
    CartesianCoords newCoords;

    if (!_isEarth)
    {
        earthCoords = _earth.getGeocentricEclipticCoords();
    }
    else
    {
    	earthCoords = EclipticCoords(0.0, 0.0, 0.0);
    }

    newCoords.x = _heliocentricEcliptic.delta
            * Degree::cos(_heliocentricEcliptic.beta)
            * Degree::cos(_heliocentricEcliptic.lambda)
            - earthCoords.delta * Degree::cos(earthCoords.beta)
                    * Degree::cos(earthCoords.lambda);

    newCoords.y = _heliocentricEcliptic.delta
            * Degree::cos(_heliocentricEcliptic.beta)
            * Degree::sin(_heliocentricEcliptic.lambda)
            - earthCoords.delta * Degree::cos(earthCoords.beta)
                    * Degree::sin(earthCoords.lambda);

    newCoords.z = _heliocentricEcliptic.delta
            * Degree::sin(_heliocentricEcliptic.beta)
            - earthCoords.delta * Degree::sin(earthCoords.beta);

    return newCoords;
}

EclipticCoords Planet::calculateGeocentricEclipticCoords(
        CartesianCoords geocentricCoords)
{
    EclipticCoords newCoords;

    newCoords.lambda = Degree::atan2(geocentricCoords.y, geocentricCoords.x);
    newCoords.lambda.normalize();

    newCoords.beta = Degree::atan2(
            geocentricCoords.z,
            AstroMath::squareRoot(
                    geocentricCoords.x * geocentricCoords.x
                            + geocentricCoords.y * geocentricCoords.y));

    newCoords.delta = AstroMath::squareRoot(
            geocentricCoords.x * geocentricCoords.x
                    + geocentricCoords.y * geocentricCoords.y
                    + geocentricCoords.z * geocentricCoords.z);

    return newCoords;
}

EquatorialCoords Planet::calculateGeocentricEquatorialCoords(
        EclipticCoords geocentricCoords)
{
    Degree ec(23.4392911);
    Degree l, b;
    EquatorialCoords newCoords;

    l = geocentricCoords.lambda;
    b = geocentricCoords.beta;

    newCoords.ra = Degree::atan2(
            Degree::sin(l) * Degree::cos(ec) - Degree::tan(b) * Degree::sin(ec),
            Degree::cos(l));
    newCoords.ra.normalize();

    newCoords.dec = Degree::asin(
            Degree::sin(b) * Degree::cos(ec)
                    + Degree::cos(b) * Degree::sin(ec) * Degree::sin(l));

    return newCoords;
}

void Planet::calculateLightDelay(Stardate date)
{
    EclipticCoords heliocentricCoordsDelay = _heliocentricEcliptic;
    //EclipticCoords earthHeliocenticCoords = _earth->getHeliocentricEclipticCoords();
    CartesianCoords geocentricCartesianDelay;
    EclipticCoords geocentricEclipticDelay;

    real dt = 0.0, dtPrev = 1.0;

    while (dt != dtPrev)
    {
        dtPrev = dt;
        real t = date.J2000m(dt);

        heliocentricCoordsDelay = calculateHeliocentricEclipticCoords(t);
        geocentricCartesianDelay = calculateGeocentricCartesianCoords(
                heliocentricCoordsDelay);
        geocentricEclipticDelay = calculateGeocentricEclipticCoords(
                geocentricCartesianDelay);
        dt = 0.0057755 * geocentricEclipticDelay.delta;
    }

    _dt = dt;
    _heliocentricEclipticDelay = heliocentricCoordsDelay;
    _geocentricCartesianDelay = geocentricCartesianDelay;
    _geocentricEclipticDelay = geocentricEclipticDelay;
}

void Planet::calculateIlluminatedFraction()
{
    EclipticCoords earthCoords;

    if (!_isEarth)
    {
        earthCoords = _earth.getHeliocentricEclipticCoords();
    }
    else
    {
    	earthCoords = EclipticCoords(0.0, 0.0, 0.0);
    }

    _i = Degree::acos(
            (AstroMath::power(_heliocentricEcliptic.delta, 2)
                    + AstroMath::power(_geocentricEcliptic.delta, 2)
                    - AstroMath::power(earthCoords.delta, 2))
                    / (2 * _heliocentricEcliptic.delta
                            * _geocentricEcliptic.delta));

    _k = (1 + Degree::cos(_i)) / 2;
}

void Planet::calcMag()
{

}

bool Planet::loadData()
{
    for (int lbr = 0; lbr < 3; lbr++)
    {
        int order = 0;
        do
        {
            int tid = 4000 + static_cast<int>(_pid) + ((lbr + 1) * 10) + order;
            bool returnCode;

            vector<OrbitalTerm> *orderNTerms = new vector<OrbitalTerm>;
            returnCode = _dataStorage.getOrbitalTerms(tid, *orderNTerms);

            switch (lbr)
            {
                case 0:
                    _LTerms.push_back(orderNTerms);
                    break;
                case 1:
                    _BTerms.push_back(orderNTerms);
                    break;
                case 2:
                    _RTerms.push_back(orderNTerms);
                    break;
            }
            orderNTerms = NULL;

            if (returnCode)
            {
                order++;
            }
            else
            {
                std::cerr << "Error accessing data." << std::endl;
                return false;
            }
        } while (order < 6);
    }
    return true;
}

/**
 * File: Sun.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines an interface for all Sun objects to follow
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
#include "SkyObject/Sun.h"
#include "Math/AstroMath.h"

using std::vector;
using tsc::Math::AstroMath;
using tsc::Math::CartesianCoords;
using tsc::Math::Degree;
using tsc::Math::EquatorialCoords;
using tsc::Math::EclipticCoords;
using tsc::Math::OrbitalTerm;
using tsc::SkyObject::Sun;
using tsc::SkyObject::Planet;
using tsc::SkyObject::SkyObject;
using tsc::Utils::IDataStorage;

Sun::Sun(IDataStorage& dataStorage, Planet& earth)
        : Planet(SUN, dataStorage, earth)
{

}

Sun::~Sun()
{

}

void Sun::calculatePosition(Stardate date)
{
    _heliocentricEcliptic = calculateHeliocentricEclipticCoords();
    _geocentricEcliptic = calculateGeocentricEclipticCoords();
    _geocentricCartesian = calculateGeocentricCartesianCoords(
            _geocentricEcliptic, date.meanObliquity());
    _geocentricEquatorial = calculateGeocentricEquatorialCoords(
            _geocentricEcliptic);
    calculateLightDelay(date);
    calculateIlluminatedFraction();
    calcMag();
}

EclipticCoords Sun::calculateHeliocentricEclipticCoords()
{
    EclipticCoords newCoords(0.0, 0.0, 0.0);

    return newCoords;
}

CartesianCoords Sun::calculateGeocentricCartesianCoords(
        EclipticCoords geocentricCoords, Degree meanObliquity)
{
    EclipticCoords earthCoords(0.0, 0.0, 0.0);
    CartesianCoords newCoords;

    newCoords.x = geocentricCoords.delta * Degree::cos(geocentricCoords.beta)
            * Degree::cos(geocentricCoords.lambda);
    newCoords.y = geocentricCoords.delta
            * (Degree::cos(geocentricCoords.beta)
                    * Degree::sin(geocentricCoords.lambda)
                    * Degree::cos(meanObliquity)
                    - Degree::sin(geocentricCoords.beta)
                            * Degree::sin(meanObliquity));
    newCoords.z = geocentricCoords.delta
            * (Degree::cos(geocentricCoords.beta)
                    * Degree::sin(geocentricCoords.lambda)
                    * Degree::sin(meanObliquity)
                    + Degree::sin(geocentricCoords.beta)
                            * Degree::cos(meanObliquity));

    return newCoords;
}

EclipticCoords Sun::calculateGeocentricEclipticCoords()
{
    EclipticCoords newCoords;
    EclipticCoords earthCoords = _earth.getHeliocentricEclipticCoords();

    newCoords.lambda = earthCoords.lambda + Degree(180.0);
    newCoords.beta = earthCoords.beta * -1;
    newCoords.delta = earthCoords.delta;

    return newCoords;
}

void Sun::calculateLightDelay(Stardate date)
{
    EclipticCoords heliocentricCoordsDelay = _heliocentricEcliptic;
    CartesianCoords geocentricCartesianDelay;
    EclipticCoords geocentricEclipticDelay;

    real dt = 0.0, dtPrev = 1.0;

    while (dt != dtPrev)
    {
        dtPrev = dt;

        heliocentricCoordsDelay = calculateHeliocentricEclipticCoords();
        geocentricEclipticDelay = calculateGeocentricEclipticCoords();
        geocentricCartesianDelay = calculateGeocentricCartesianCoords(
                heliocentricCoordsDelay, date.meanObliquity());
        dt = 0.0057755 * geocentricEclipticDelay.delta;
    }

    _dt = dt;
    _heliocentricEclipticDelay = heliocentricCoordsDelay;
    _geocentricCartesianDelay = geocentricCartesianDelay;
    _geocentricEclipticDelay = geocentricEclipticDelay;
}

void Sun::calculateIlluminatedFraction()
{
    _k = 1.0;
}


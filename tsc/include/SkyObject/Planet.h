/**
 * File: Planet.h
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
#ifndef PLANET_H_
#define PLANET_H_

#include <vector>
#include <sqlite3.h>
#include "SkyObject/SkyObject.h"
#include "Math/Degree.h"
#include "Math/Units.h"

using std::vector;
using tsc::SkyObject::SkyObject;
using tsc::Math::Degree;
using tsc::Math::EquatorialCoords;
using tsc::Math::EclipticCoords;
using tsc::Math::CartesianCoords;
using tsc::Math::OrbitalTerm;

namespace tsc
{
namespace SkyObject
{
class Planet : public SkyObject
{
 public:
    enum PlanetCode
    {
        SUN = -100,
        MERCURY = 100,
        VENUS = 200,
        EARTH = 300,
        MARS = 400,
        JUPITER = 500,
        SATURN = 600,
        URANUS = 700,
        NEPTUNE = 800,
    };

    Planet(PlanetCode pid, sqlite3* db, Planet* earth);
    ~Planet();
    virtual void calculatePosition(Stardate date);
    virtual EclipticCoords getHeliocentricEclipticCoords();
    virtual EclipticCoords getGeocentricEclipticCoords();
    virtual CartesianCoords getGeocentricCartesianCoords();
    virtual real getLightDelay();
    virtual real getIlluminatedFraction();
    virtual Degree getPhaseAngle();

 protected:
    virtual bool loadData();
    static real sumTerms(vector<vector<OrbitalTerm>*> terms, real millenia);
    virtual EclipticCoords calculateHeliocentricEclipticCoords(real millenia);
    virtual CartesianCoords calculateGeocentricCartesianCoords(
            EclipticCoords heliocentricCoords);
    virtual EclipticCoords calculateGeocentricEclipticCoords(
            CartesianCoords geocentricCoords);
    virtual EquatorialCoords calculateGeocentricEquatorialCoords(
            EclipticCoords geocentricCoords);
    virtual void calculateLightDelay(Stardate date);
    virtual void calculateIlluminatedFraction();
    virtual void calcMag();

    PlanetCode _pid;
    sqlite3* _db;
    Planet* _earth;

    // Heliocentric Coordinates
    EclipticCoords _heliocentricEcliptic;

    // Geocentric Coordinates
    CartesianCoords _geocentricCartesian;
    EclipticCoords _geocentricEcliptic;

    // Phase angle to earth
    Degree _i;

    // Illuminated portion (in %)
    real _k;

    // Light-time delay (in days)
    real _dt;

    // Light-time delay adjusted variables

    EclipticCoords _heliocentricEclipticDelay;
    CartesianCoords _geocentricCartesianDelay;
    EclipticCoords _geocentricEclipticDelay;

    vector<vector<OrbitalTerm>*> _LTerms;
    vector<vector<OrbitalTerm>*> _BTerms;
    vector<vector<OrbitalTerm>*> _RTerms;
};
}
}

#endif

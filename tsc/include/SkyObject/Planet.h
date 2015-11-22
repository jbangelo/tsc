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
#include "SkyObject/IPlanet.h"
#include "SkyObject/SkyObject.h"
#include "Math/Degree.h"
#include "Math/Units.h"
#include "Utils/IDataStorage.h"

namespace tsc
{
namespace SkyObject
{
class Planet : public SkyObject, public IPlanet
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

    Planet(PlanetCode pid, tsc::Utils::IDataStorage& dataStorage, IPlanet& earth);
    ~Planet();
    virtual void calculatePosition(tsc::Time::Stardate date);
    virtual tsc::Math::EclipticCoords getHeliocentricEclipticCoords();
    virtual tsc::Math::EclipticCoords getGeocentricEclipticCoords();
    virtual tsc::Math::CartesianCoords getGeocentricCartesianCoords();
    virtual real getLightDelay();
    virtual real getIlluminatedFraction();
    virtual tsc::Math::Degree getPhaseAngle();

 protected:
    virtual bool loadData();
    real sumTerms(std::vector<std::vector<tsc::Math::OrbitalTerm>*> terms, real millenia);
    virtual tsc::Math::EclipticCoords calculateHeliocentricEclipticCoords(real millenia);
    virtual tsc::Math::CartesianCoords calculateGeocentricCartesianCoords(tsc::Math::EclipticCoords heliocentricCoords);
    virtual tsc::Math::EclipticCoords calculateGeocentricEclipticCoords(tsc::Math::CartesianCoords geocentricCoords);
    virtual tsc::Math::EquatorialCoords calculateGeocentricEquatorialCoords(tsc::Math::EclipticCoords geocentricCoords);
    virtual void calculateLightDelay(tsc::Time::Stardate date);
    virtual void calculateIlluminatedFraction();
    virtual void calcMag();

    PlanetCode _pid;
    tsc::Utils::IDataStorage& _dataStorage;
    IPlanet& _earth;
    bool _isEarth;

    // Heliocentric Coordinates
    tsc::Math::EclipticCoords _heliocentricEcliptic;

    // Geocentric Coordinates
    tsc::Math::CartesianCoords _geocentricCartesian;
    tsc::Math::EclipticCoords _geocentricEcliptic;

    // Phase angle to earth
    tsc::Math::Degree _i;

    // Illuminated portion (in %)
    real _k;

    // Light-time delay (in days)
    real _dt;

    // Light-time delay adjusted variables

    tsc::Math::EclipticCoords _heliocentricEclipticDelay;
    tsc::Math::CartesianCoords _geocentricCartesianDelay;
    tsc::Math::EclipticCoords _geocentricEclipticDelay;

    std::vector<std::vector<tsc::Math::OrbitalTerm>*> _LTerms;
    std::vector<std::vector<tsc::Math::OrbitalTerm>*> _BTerms;
    std::vector<std::vector<tsc::Math::OrbitalTerm>*> _RTerms;
};
}
}

#endif

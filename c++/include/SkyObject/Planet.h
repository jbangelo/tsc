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
#include "sqlite3.h"
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
				MERCURY = 100,
				VENUS = 200,
				EARTH = 300,
				MARS = 400,
				JUPITER = 500,
				SATURN = 600,
				URANUS = 700,
				NEPTUNE = 800,
			};

			Planet(PlanetCode pid, sqlite3* db);
			~Planet();
			void calculatePosition(Stardate date);
			EclipticCoords getHeliocentricEclipticCoords();
			EclipticCoords getGeocentricEclipticCoords();
			CartesianCoords getGeocentricCartesianCoords();
			real getLightDelay();
			real getIlluminatedFraction();
			Degree getPhaseAngle();
			
		protected:
			bool loadData();
			static real sumTerms(vector<vector<OrbitalTerm>*> terms, real millenia);
			void calculateHeliocentricEclipticCoords(real millenia);
			void calculateGeocentricCartesianCoords();
			void calculateGeocentricEclipticCoords();
			void calculateGeocentricEquatorialCoords();
			void calculateLightDelay(Stardate date);
			void calculateIlluminatedFraction();
			void calcMag();

			PlanetCode _pid;
			sqlite3* _db;
			
			// Heliocentric Ecliptic Coordinates
			EclipticCoords _heliocentricEcliptic;

			// Geocentric Ecliptic Coordinates
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
			//OrbitalTerm** _LTerms;
			//OrbitalTerm** _BTerms;
			//OrbitalTerm** _RTerms;

			Stardate _lastUsedDate;	};
}
}

#endif

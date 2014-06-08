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

using tsc::SkyObject::Planet;
using tsc::Math::AstroMath;

Planet::Planet(PlanetCode pid, sqlite3* db) : 
	SkyObject(),
	_pid(pid),
	_db(db),
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
	//vector<OrbitalTerm> l,b,r;
	//_LTerms.push_back(l);
	//_BTerms.push_back(b);
	//_RTerms.push_back(r);
	_LTerms.resize(5);
	_BTerms.resize(5);
	_RTerms.resize(5);
	
	loadData();
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

void Planet::calcMag()
{

}

bool Planet::loadData()
{
	sqlite3_stmt *preparedStatement;
	const std::string sqlStatement1("SELECT rank,A,B,C FROM planets WHERE tid=");
	const std::string sqlStatement2(" ORDER BY rank DESC;");

	for (int lbr = 0; lbr < 3; lbr++)
	{
		int order = 0;
		do
		{
			int tid = 4000 + static_cast<int>(_pid) + ((lbr+1)*10) + order;
			std::string sqlStatement = sqlStatement1 + std::to_string(tid) + sqlStatement2;
			int returnCode;

			if (sqlite3_prepare_v2(_db, sqlStatement.c_str(), sqlStatement.length(), &preparedStatement, NULL) != SQLITE_OK)
			{
				return false;
			}
			if (preparedStatement == NULL)
			{
				return false;
			}

			vector<OrbitalTerm> *orderNTerms = new vector<OrbitalTerm>;
			returnCode = sqlite3_step(preparedStatement);
			while (returnCode == SQLITE_ROW)
			{
				unsigned int rank;
				OrbitalTerm term;
				rank = sqlite3_column_int(preparedStatement, 0);
				term.A = sqlite3_column_double(preparedStatement, 1);
				term.B = sqlite3_column_double(preparedStatement, 2);
				term.C = sqlite3_column_double(preparedStatement, 3);

				if (rank > orderNTerms->capacity())
				{
					orderNTerms->resize(rank);
				}

				orderNTerms->at(rank-1) = term;
				returnCode = sqlite3_step(preparedStatement);
			}

			std::cout << "Order " << order << " terms are " << orderNTerms->size() << " elements long." << std::endl;

			switch(lbr)
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

			sqlite3_finalize(preparedStatement);

			if (returnCode == SQLITE_DONE)
			{
				order++;
			}
			else
			{
				std::cerr << "Error accessing database: " << /*sqlite3_errstr(returnCode) <<*/ std::endl;
				return false;
			}
		} while (order < 6);
	}
	return true;
}

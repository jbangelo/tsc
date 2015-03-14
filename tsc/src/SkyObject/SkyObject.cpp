/**
 * File: SkyObject.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines an interface for all sky object objects
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
#include "SkyObject/SkyObject.h"
#include "Math/AstroMath.h"

using tsc::SkyObject::SkyObject;
using tsc::Math::AstroMath;

SkyObject::SkyObject()
        : _name(""),
          _geocentricEquatorial(0.0, 0.0),
          _M(0.0),
          _dist(0.0)
{

}

SkyObject::SkyObject(string name, real RA, real Dec, real M, real dist)
        : _name(name),
          _geocentricEquatorial(RA, Dec),
          _M(M),
          _dist(dist)
{

}

SkyObject::~SkyObject()
{

}

std::string SkyObject::getName()
{
    return _name;
}

HorizontalCoords SkyObject::getHorizontalCoords(LatLng location, Stardate date)
{
    HorizontalCoords horiz;
    real x, y;

    Degree H = date.apparentSidereal() - location.lng
            - _geocentricEquatorial.ra;
    H.normalize();

    y = Degree::sin(H);
    x = Degree::cos(H) * Degree::sin(location.lat)
            - Degree::tan(_geocentricEquatorial.dec)
                    * Degree::cos(location.lat);
    horiz.az = Degree::atan2(y, x);
    horiz.alt = Degree::asin(
            Degree::sin(location.lat) * Degree::sin(_geocentricEquatorial.dec)
                    + Degree::cos(location.lat)
                            * Degree::cos(_geocentricEquatorial.dec)
                            * Degree::cos(H));

    return horiz;
}

EquatorialCoords SkyObject::getGeocentricEquatorialCoords()
{
    return _geocentricEquatorial;
}

real SkyObject::getMag()
{
    return _M;
}

real SkyObject::getDistance()
{
    return _dist;
}


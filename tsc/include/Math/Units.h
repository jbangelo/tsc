/**
 * File: Units.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines several common units for general use
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
#ifndef UNITS_H_
#define UNITS_H_

#include "Math/Degree.h"

using tsc::Math::Degree;

namespace tsc
{
namespace Math
{
typedef struct HorizontalCoords
{
    Degree alt;
    Degree az;

    HorizontalCoords()
            : alt(0.0),
              az(0.0)
    {
    }
    ;
    HorizontalCoords(Degree _alt, Degree _az)
            : alt(_alt),
              az(_az)
    {
    }
    ;
    HorizontalCoords(real _alt, real _az)
            : alt(_alt),
              az(_az)
    {
    }
    ;
} HorizontalCoords;

typedef struct EquatorialCoords
{
    Degree ra;
    Degree dec;  // Dec

    EquatorialCoords()
            : ra(0.0),
              dec(0.0)
    {
    }
    ;
    EquatorialCoords(Degree _ra, Degree _dec)
            : ra(_ra),
              dec(_dec)
    {
    }
    ;
} EquatorialCoords;

typedef struct EclipticCoords
{
    Degree lambda;  // longitude
    Degree beta;  // latitude
    real delta;  // distace

    EclipticCoords()
            : lambda(0.0),
              beta(0.0),
              delta(0.0)
    {
    }
    ;
    EclipticCoords(Degree _lambda, Degree _beta)
            : lambda(_lambda),
              beta(_beta),
              delta(0.0)
    {
    }
    ;
    EclipticCoords(Degree _lambda, Degree _beta, real _delta)
            : lambda(_lambda),
              beta(_beta),
              delta(_delta)
    {
    }
    ;
} EclipticCoords;

typedef struct CartesianCoords
{
    real x;
    real y;
    real z;

    CartesianCoords()
            : x(0.0),
              y(0.0),
              z(0.0)
    {
    }
    ;
    CartesianCoords(real _x, real _y, real _z)
            : x(_x),
              y(_y),
              z(_z)
    {
    }
    ;
} CartesianCoords;

typedef struct LatLng
{
    Degree lat;
    Degree lng;

    LatLng()
            : lat(0.0),
              lng(0.0)
    {
    }
    ;
    LatLng(Degree _lat, Degree _lng)
            : lat(_lat),
              lng(_lng)
    {
    }
    ;
    LatLng(real _lat, real _lng)
            : lat(_lat),
              lng(_lng)
    {
    }
    ;
} LatLng;

typedef struct OrbitalTerm
{
    real A;
    real B;
    real C;

    OrbitalTerm()
            : A(0.0),
              B(0.0),
              C(0.0)
    {
    }
    ;
    OrbitalTerm(real _A, real _B, real _C)
            : A(_A),
              B(_B),
              C(_C)
    {
    }
    ;
} OrbitalTerm;

}
}

#endif

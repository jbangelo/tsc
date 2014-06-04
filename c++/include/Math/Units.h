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
	typedef struct AltAz
	{
		Degree alt;
		Degree az;

		AltAz() : alt(0.0), az(0.0) { };
		AltAz(Degree _alt, Degree _az) : alt(_alt), az(_az) { };
		AltAz(real _alt, real _az) : alt(_alt), az(_az) { };
	} AltAz;

	typedef struct RaDec
	{
		Degree alpha; // RA
		Degree delta; // Dec

		RaDec() : alpha(0.0), delta(0.0) { };
		RaDec(Degree _alpha, Degree _delta) : alpha(_alpha), delta(_delta) { };
		RaDec(real _alpha, real _delta) : alpha(_alpha), delta(_delta) { };
	} RaDec;

	typedef struct LatLng
	{
		Degree lat;
		Degree lng;

		LatLng() : lat(0.0), lng(0.0) { };
		LatLng(Degree _lat, Degree _lng) : lat(_lat), lng(_lng) { };
		LatLng(real _lat, real _lng) : lat(_lat), lng(_lng) { };
	} LatLng;
}
}

#endif

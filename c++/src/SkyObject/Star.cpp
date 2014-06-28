/**
 * File: Star.cpp
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines an interface for Star objects to follow
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

#include "SkyObject/Star.h"
#include "Math/AstroMath.h"

using tsc::SkyObject::Star;
using tsc::Math::AstroMath;

Star::Star(integer starID, integer hip, integer hd, integer hr, string gliese, string bayer, string pName, real RA, real Dec, real dist, real absM) : 
	SkyObject(pName, RA, Dec, 0.0f, 0.0f), 
	_starID(starID),
	_hip(hip),
	_hd(hd),
	_hr(hr),
	_gliese(gliese),
	_bayerFlamsteed(bayer),
	_absM(absM)
{
	// Get the apparent magnitude from the absolute magnitude
	_M = _absM - 5.0l*(1.0l - AstroMath::log10(dist));

	// Convert the dist (in parsecs) to _dist (in A.U.)
	_dist = dist*206264.806248l;
}

Star::~Star()
{
	
}

integer Star::getStarID()
{
	return _starID;
}

integer Star::getHIP()
{
	return _hip;
}

integer Star::getHD()
{
	return _hd;
}

integer Star::getHR()
{
	return _hr;
}

string Star::getGliese()
{
	return _gliese;
}

string Star::getBayerFlamsteed()
{
	return _bayerFlamsteed;
}

real Star::getAbsMag()
{
	return _absM;
}


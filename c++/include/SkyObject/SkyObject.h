/**
 * File: SkyObject.h
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
#ifndef SKYOBJECT_H_
#define SKYOBJECT_H_

#include <string>
#include "Math/Units.h"
#include "Time/Stardate.h"

using tsc::Math::EquatorialCoords;
using tsc::Math::HorizontalCoords;
using tsc::Math::LatLng;
using tsc::Time::Stardate;

namespace tsc
{
namespace SkyObject
{
	class SkyObject
	{
		public:
			SkyObject();
			virtual ~SkyObject();
			std::string getName();
			virtual HorizontalCoords getHorizontalCoords(LatLng location, Stardate date);
			EquatorialCoords getGeocentricEquatorialCoords();
			real getMag();
			real getDistance();
		protected:
			std::string _name;
			EquatorialCoords _geocentricEquatorial;
			real _M;
			real _dist;
	};
}
}

#endif

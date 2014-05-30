/**
 * File: Stardate.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Declares a class that keeps track of time that can be represented
 *		in several different caledars and time zones.
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
#ifndef STARDATE_H_
#define STARDATE_H_

#include <stdint>
#include "Math/Degree.h"

usign tsc::Math::Degree;

namespace tsc
{
namespace Time
{
	class Stardate
	{
		public:
			Stardate(long int date, int time);
			~Stardate();
			void addDays(long int days);
			float toJulianDate();
			long int toJulianDate();
			long long int J2000();
			long int J2000c();
			long int J2000m();
			bool isJulian();
			bool isGregorian();
			Degree meanSidereal();
			void nutation(double& dPsi, double& dE);
			double meanObliquity();
			double apparentSidereal();
		private:
			long int _date;
			long int _time;
	};
}
}

#endif

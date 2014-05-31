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

#include <stdint.h>
#include <string>
#include "Math/AstroMath.h"
#include "Math/Degree.h"

using tsc::Math::Degree;

namespace tsc
{
namespace Time
{
	typedef struct ChristianDate
	{
		integer year;
		integer month;
		integer day;
		integer hour;
		integer minute;
		integer second;

		ChristianDate(integer _year, integer _month, integer _day, integer _hour, integer _minute, integer _second) : year(_year), month(_month), day(_day), hour(_hour), minute(_minute), second(_second) { };
		ChristianDate(integer _year, integer _month, integer _day) : year(_year), month(_month), day(_day), hour(0), minute(0), second(0) { };
	} ChristianDate;

	class Stardate
	{
		public:
			Stardate(real JD);
			~Stardate();
			static Stardate fromDate(ChristianDate date);
			static Stardate fromJulianDate(ChristianDate date);
			static Stardate fromGregorianDate(ChristianDate date);
			void addDays(integer days);
			real toJD();
			real J2000();
			real J2000c();
			real J2000m();
			bool isJulian();
			bool isGregorian();
			Degree meanSidereal();
			void nutation(Degree& Psi, Degree& dE);
			void nutation(Degree& Psi, Degree& dE, bool trueObliq);
			Degree meanObliquity();
			Degree apparentSidereal();

			ChristianDate toGregorianDate();
			std::string toGregorianDateStr();

			bool operator==(Stardate& param);
			bool operator!=(Stardate& param);
			bool operator<(Stardate& param);
			bool operator>(Stardate& param);
			bool operator<=(Stardate& param);
			bool operator>=(Stardate& param);
			bool operator==(const Stardate& param);
			bool operator!=(const Stardate& param);
			bool operator<(const Stardate& param);
			bool operator>(const Stardate& param);
			bool operator<=(const Stardate& param);
			bool operator>=(const Stardate& param);
		private:
			real _JD;
	};

	const Stardate GREGORIAN_START(2298883.5);
	extern real nutationTerms[63][9];
}
}

#endif

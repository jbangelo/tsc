/**
 * File: Degree.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Declares a class used to store and manipulate values in degrees
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
#ifndef DEGREE_H_
#define DEGREE_H_

#include <string>
#include "Math/AstroMath.h"

namespace tsc
{
namespace Math
{
	/**
	 * A representation of a degree value in floating point representation
	 */
	class Degree
	{
		public:
			/**
			 * Creates a Degree object from a raw degree value
			 */
			Degree(real value);

			/**
			 * Destroys a Degree object
			 */
			~Degree();

			/**
			 * Creates a Degree object from a raw radian value
			 */
			static Degree fromRad(real value);

			/**
			 * Retrieves the raw floating point value of the Degree object
			 */
			real deg();

			/**
			 * Retreives the raw floating point value of the Degree object converted into radians
			 */
			real rad();

			/**
			 * Changes the value of the Degree object to be the absolute value of itself
			 */
			void abs();

			/**
			 * Retreives the arcMinute value of the Degree object
			 */
			integer arcMinute();

			/**
			 * Retrieves the arcSecond value of the Degree object
			 */
			real arcSecond();

			/**
			 * Retreives the hour value of the Degree object
			 */
			integer hour();

			/**
			 * Retrieves the minute value of the Degree object
			 */
			integer minute();

			/**
			 * Retreives the second value of the Degree object
			 */
			real second();

			/**
			 * Gets the string representation of the Degree object
			 */
			std::string degStr();

			/**
			 * Gets the string representation of the degree and minute values of the Degree object
			 */
			std::string dmStr();

			/**
			 * Gets the string representation of the degree, minute, and secon values of the Degree object
			 */
			std::string dmsStr();

			/**
			 * Gets the string representation of the hour value of the Degree object
			 */
			std::string hourStr();

			/**
			 * Gets the string representation of the hour and minute values of the Degree object
			 */
			std::string hmStr();

			/**
			 * Gets the string representation of the hour, minute, and second values of the Degree object
			 */
			std::string hmsStr();

			/**
			 * Rounds the value of the Degree object such that 0.0 < value < 360.0
			 */
			void normalize();

			static real sin(Degree& param);
			static real cos(Degree& param);
			static real tan(Degree& param);
			static Degree asin(real param);
			static Degree acos(real param);
			static Degree atan(real param);
			static Degree atan2(real param1, real param2);
			Degree operator+(const Degree& param);
			Degree operator-(const Degree& param);
			Degree operator*(const Degree& param);
			Degree operator/(const Degree& param);
			bool operator<=(const Degree& param);
			bool operator>=(const Degree& param);
			bool operator==(const Degree& param);
		private:
			void updateDMS();
			void updateHMS();
			real _value;

			integer _degree;
			real _arcFraction;
			integer _arcMinute;
			real _arcSecond;

			integer _hour;
			real _fraction;
			integer _minute;
			real _second;
	};
}
}

#endif

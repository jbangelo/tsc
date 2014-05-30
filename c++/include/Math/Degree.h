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
			Degree(long double value);

			/**
			 * Destroys a Degree object
			 */
			~Degree();

			/**
			 * Retrieves the raw floating point value of the Degree object
			 */
			long double deg();

			/**
			 * Retreives the raw floating point value of the Degree object converted into radians
			 */
			long double rad();

			/**
			 * Changes the value of the Degree object to be the absolute value of itself
			 */
			void abs();

			/**
			 * Retreives the arcMinute value of the Degree object
			 */
			long int arcMinute();

			/**
			 * Retrieves the arcSecond value of the Degree object
			 */
			long double arcSecond();

			/**
			 * Retreives the hour value of the Degree object
			 */
			long int hour();

			/**
			 * Retrieves the minute value of the Degree object
			 */
			long int minute();

			/**
			 * Retreives the second value of the Degree object
			 */
			long double second();

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

			static long double sin(Degree& param);
			static long double cos(Degree& param);
			static long double tan(Degree& param);
			static Degree asin(long double param);
			static Degree acos(long double param);
			static Degree atan(long double param);
			static Degree atan2(long double param1, long double param2);
			Degree operator+(const Degree& param);
			Degree operator-(const Degree& param);
			Degree operator*(const Degree& param);
			Degree operator/(const Degree& param);
			Degree operator<=(const Degree& param);
			Degree operator>=(const Degree& param);
			Degree operator==(const Degree& param);
		private:
			long double _value;

			long int _degree;
			long double _arcFraction;
			long int _arcMinute;
			long double _arcSecond;

			long int _hour;
			long double _fraction;
			long int _minute;
			long double _second;
	};
}
}

#endif

/**
 * File: AstroMath.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines several math functions for use in astronomical calculations
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
#ifndef ASTROMATH_H_
#define ASTROMATH_H_

typedef long double real;
typedef long int integer;

namespace tsc
{
namespace Math
{
    class AstroMath
    {
        public:
            static const real pi = 3.14159265358979323846264338327950288419716939937510582L;
            static const real ParsecToAU = 206264.806248L;

            static integer FIX(real x);
            static integer INT(real x);
            static real absoluteValue(real x);
            static real sign(real x);
            static real sine(real x);
            static real cosine(real x);
            static real tangent(real x);
            static real arcsine(real x);
            static real arccosine(real x);
            static real arctangent(real x);
            static real arctangent2(real x, real y);
            static real squareRoot(real x);
            static real log10(real x);
            static real power(real base, real power);
    };
}
}

#endif

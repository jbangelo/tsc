/**
 * File: AstroMath.cpp
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

#include <cmath>
#include "Math/AstroMath.h"

using tsc::Math::AstroMath;

integer AstroMath::FIX(real x)
{
    return int(x);
}

integer AstroMath::INT(real x)
{
    return floor(x);
}

real AstroMath::absoluteValue(real x)
{
    return fabs(x);
}

real AstroMath::sign(real x)
{
    if (x == 0)
    {
        return 1;
    }
    else
    {
        return (x/absoluteValue(x));
    }
}

real AstroMath::sine(real x)
{
    return sin(x);
}

real AstroMath::cosine(real x)
{
    return cos(x);
}

real AstroMath::tangent(real x)
{
    return tan(x);
}

real AstroMath::arcsine(real x)
{
    return asin(x);
}

real AstroMath::arccosine(real x)
{
    return acos(x);
}

real AstroMath::arctangent(real x)
{
    return atan(x);
}

real AstroMath::arctangent2(real x, real y)
{
    return atan2(x,y);
}

real AstroMath::squareRoot(real x)
{
    return sqrt(x);
}

real AstroMath::log10(real x)
{
    return log10(x);
}

real AstroMath::power(real base, real power)
{
    if (power == 0.0)
    {
        return 1.0;
    }
    return pow(base,power);
}


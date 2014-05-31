/**
 * File: NutationTerms.h
 * Project: tsc - TinyStarChart
 * Creator: jbangelo
 *
 * Description: Defines the terms used to determine the nutation of the earth
 *
 * The MIT License {MIT}
 *
 * Copyright {c} 2014 jbangelo
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files {the "Software"}, to deal
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
#ifndef NUTATIONTERMS_H_
#define NUTATIONTERMS_H_

#include "Math/AstroMath.h"

namespace tsc
{
namespace Time
{
	const int NutationTermCount = 63;
	real NutationTerms[NutationTermCount][9] = {
		//D M  M' F  O	      dPsi             dE
		{0, 0, 0, 0, 1, -171996, -174.2, +92025, +8.9},
		{-2,0, 0, 2, 2,  -13187,   -1.6,  +5736, -3.1},
		{0, 0, 0, 2, 2,   -2274,   -0.2,   +977, -0.5},
		{0, 0, 0, 0, 2,   +2062,   +0.2,   -895, +0.5},
		{0, 1, 0, 0, 0,   +1426,   -3.4,    +54, -0.1},
		{0, 0, 1, 0, 0,    +712,   +0.1,     -7,    0},
		{-2,1, 0, 2, 2,    -517,   +1.2,   +224, -0.6},
		{0, 0, 0, 2, 1,    -386,   -0.4,   +200,    0},
		{0, 0, 1, 2, 2,    -301,      0,   +129, -0.1},
		{-2,-1,0, 2, 2,    +217,   -0.5,    -95, +0.3},
		{-2,0, 1, 0, 0,    -158,      0,      0,    0},
		{-2,0, 0, 2, 1,    +129,   +0.1,    -70,    0},
		{0, 0,-1, 2, 2,    +123,      0,    -53,    0},
		{2, 0, 0, 0, 0,     +63,      0,      0,    0},
		{0, 0, 1, 0, 1,     +63,   +0.1,    -33,    0},
		{2, 0,-1, 2, 2,     -59,      0,    +26,    0},
		{0, 0,-1, 0, 1,     -58,   -0.1,    +32,    0},
		{0, 0, 1, 2, 1,     -51,      0,    +27,    0},
		{-2,0, 2, 0, 0,     +48,      0,      0,    0},
		{0, 0,-2, 2, 1,     +46,      0,    -24,    0},
		{2, 0, 0, 2, 2,     -38,      0,    +16,    0},
		{0, 0, 2, 2, 2,     -31,      0,    +13,    0},
		{0, 0, 2, 0, 0,     +29,      0,      0,    0},
		{-2,0, 1, 2, 2,     +29,      0,    -12,    0},
		{0, 0, 0, 2, 0,     +26,      0,      0,    0},
		{-2,0, 0, 2, 0,     -22,      0,      0,    0},
		{0, 0,-1, 2, 1,     +21,      0,    -10,    0},
		{0, 2, 0, 0, 0,     +17,   -0.1,      0,    0},
		{2, 0,-1, 0, 1,     +16,      0,     -8,    0},
		{-2,2, 0, 2, 2,     -16,   +0.1,     +7,    0},
		{0, 1, 0, 0, 1,     -15,      0,     +9,    0},
		{-2,0, 1, 0, 1,     -13,      0,     +7,    0},
		{0,-1, 0, 0, 1,     -12,      0,     +6,    0},
		{0, 0, 2,-2, 0,     +11,      0,      0,    0},
		{2, 0,-1, 2, 1,     -10,      0,     +5,    0},
		{2, 0, 1, 2, 2,      -8,      0,     +3,    0},
		{0, 1, 0, 2, 2,      +7,      0,     -3,    0},
		{-2,1, 1, 0, 0,      -7,      0,      0,    0},
		{0,-1, 0, 2, 2,      -7,      0,     +3,    0},
		{2, 0, 0, 2, 1,      -7,      0,     +3,    0},
		{2, 0, 1, 0, 0,      +6,      0,      0,    0},
		{-2,0, 2, 2, 2,      +6,      0,     -3,    0},
		{-2,0, 1, 2, 1,      +6,      0,     -3,    0},
		{2, 0,-2, 0, 1,      -6,      0,     +3,    0},
		{2, 0, 0, 0, 1,      -6,      0,     +3,    0},
		{0,-1, 1, 0, 0,      +5,      0,      0,    0},
		{-2,-1,0, 2, 1,      -5,      0,     +3,    0},
		{-2,0, 0, 0, 1,      -5,      0,     +3,    0},
		{0, 0, 2, 2, 1,      -5,      0,     +3,    0},
		{-2,0, 2, 0, 1,      +4,      0,      0,    0},
		{-2,1, 0, 2, 1,      +4,      0,      0,    0},
		{0, 0, 1,-2, 0,      +4,      0,      0,    0},
		{-1,0, 1, 0, 0,      -4,      0,      0,    0},
		{-2,1, 0, 0, 0,      -4,      0,      0,    0},
		{1, 0, 0, 0, 0,      -4,      0,      0,    0},
		{0, 0, 1, 2, 0,      +3,      0,      0,    0},
		{0, 0,-2, 2, 2,      -3,      0,      0,    0},
		{-1,-1,1, 0, 0,      -3,      0,      0,    0},
		{0, 1, 1, 0, 0,      -3,      0,      0,    0},
		{0,-1, 1, 2, 2,      -3,      0,      0,    0},
		{2,-1,-1, 2, 2,      -3,      0,      0,    0},
		{0, 0, 3, 2, 2,      -3,      0,      0,    0},
		{2,-1, 0, 2, 2,      -3,      0,      0,    0}
	}; // nutationTerms[][]
}
}

#endif

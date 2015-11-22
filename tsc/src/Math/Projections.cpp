/*
 * Projections.cpp
 *
 *  Created on: Nov 22, 2015
 *      Author: ben
 */

#include "Math/Projections.h"

using tsc::Math::Projections;
using tsc::Math::CartesianCoords;
using tsc::Math::HorizontalCoords;

CartesianCoords Projections::simpleCircularProjection(HorizontalCoords in, real circleRadius)
{
	CartesianCoords out;

	// First transform the horizontal coords to polar coords.
	real r = ((in.alt.deg() - 90.0) / -90.0) * circleRadius;
	Degree q = (in.az - 90.0) * -1.0;
	// An alternative approach would be to set r = cos(alt),
	// but this would crowd the edge of the circle.

	// Then transform the polar coords to planar coords
	out.x = r * Degree::cos(q);
	out.y = r * Degree::sin(q);
	out.z = 0;

	return out;
}



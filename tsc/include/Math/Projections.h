/*
 * Projections.h
 *
 *  Created on: Nov 22, 2015
 *      Author: ben
 */

#ifndef PROJECTIONS_H_
#define PROJECTIONS_H_

#include "Math/Units.h"

namespace tsc
{
namespace Math
{

class Projections
{
	public:
		/**
		 * Performs a simple projection from Alt/Az coords to a circular plane (the z coord will always be 0).
		 * In this projection North (azimuth = 0 degrees) will be placed at the top of the circle.
		 */
		static tsc::Math::CartesianCoords simpleCircularProjection(tsc::Math::HorizontalCoords in, real circleRadius);
};

}
}



#endif /* PROJECTIONS_H_ */

/*
 * IPlanet.h
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#ifndef IPLANET_H_
#define IPLANET_H_

#include "Math/Degree.h"
#include "Math/Units.h"
#include "Time/Stardate.h"

namespace tsc
{
namespace SkyObject
{

class IPlanet
{
	public:
		virtual ~IPlanet() { };
	    virtual void calculatePosition(tsc::Time::Stardate date) = 0;
	    virtual tsc::Math::EclipticCoords getHeliocentricEclipticCoords() = 0;
	    virtual tsc::Math::EclipticCoords getGeocentricEclipticCoords() = 0;
	    virtual tsc::Math::CartesianCoords getGeocentricCartesianCoords() = 0;
	    virtual real getLightDelay() = 0;
	    virtual real getIlluminatedFraction() = 0;
	    virtual tsc::Math::Degree getPhaseAngle() = 0;
};

}
}



#endif /* IPLANET_H_ */

/*
 * PlanetFactory.h
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#ifndef PLANETFACTORY_H_
#define PLANETFACTORY_H_

#include "Utils/IDataStorage.h"
#include "SkyObject/Planet.h"

namespace tsc
{
namespace SkyObject
{

class PlanetFactory
{
	public:
		enum Planets
		{
			SUN = 0,
			MERCURY,
			VENUS,
			EARTH,
			MARS,
			JUPITER,
			SATURN,
			URANUS,
			NEPTUNE,
			PLANET_COUNT,
		};
		PlanetFactory(tsc::Utils::IDataStorage& dataStorage);
		~PlanetFactory();
		Planet& getPlanet(Planets planet);
	private:

		tsc::Utils::IDataStorage& _dataStorage;
		Planet* _planets[PLANET_COUNT];
};

}
}



#endif /* PLANETFACTORY_H_ */

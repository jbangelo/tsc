/*
 * PlanetFactory.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#include "SkyObject/Earth.h"
#include "SkyObject/Planet.h"
#include "SkyObject/PlanetFactory.h"
#include "SkyObject/Sun.h"
#include "Utils/SqliteStorage.h"

using tsc::SkyObject::IPlanet;
using tsc::SkyObject::Earth;
using tsc::SkyObject::Planet;
using tsc::SkyObject::PlanetFactory;
using tsc::SkyObject::Sun;
using tsc::Utils::IDataStorage;
using tsc::Utils::SqliteStorage;

PlanetFactory::PlanetFactory(IDataStorage& dataStorage) :
		_dataStorage(dataStorage)
{
	_planets[EARTH] = new Earth(_dataStorage);
	_planets[SUN] = new Sun(_dataStorage, *_planets[EARTH]);
	_planets[MERCURY] = new Planet(Planet::MERCURY, _dataStorage, *_planets[EARTH]);
	_planets[VENUS] = new Planet(Planet::VENUS, _dataStorage, *_planets[EARTH]);
	_planets[MARS] = new Planet(Planet::MARS, _dataStorage, *_planets[EARTH]);
	_planets[JUPITER] = new Planet(Planet::JUPITER, _dataStorage, *_planets[EARTH]);
	_planets[SATURN] = new Planet(Planet::SATURN, _dataStorage, *_planets[EARTH]);
	_planets[URANUS] = new Planet(Planet::URANUS, _dataStorage, *_planets[EARTH]);
	_planets[NEPTUNE] = new Planet(Planet::NEPTUNE, _dataStorage, *_planets[EARTH]);
}

PlanetFactory::~PlanetFactory()
{
	for (int i = 0; i < PLANET_COUNT; i++)
	{
		//delete _planets[i];
	}
}

IPlanet& PlanetFactory::getPlanet(Planets planet)
{
	return *_planets[planet];
}



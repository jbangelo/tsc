/*
 * Earth.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#include "SkyObject/Earth.h"

using tsc::SkyObject::Earth;
using tsc::Utils::IDataStorage;

Earth::Earth(IDataStorage& dataStorage) :
		Planet(EARTH, dataStorage, *this)
{
	_isEarth = true;
}

Earth::~Earth()
{

}



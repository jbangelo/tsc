/*
 * Earth.h
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#ifndef EARTH_H_
#define EARTH_H_

#include "SkyObject/Planet.h"

namespace tsc
{
namespace SkyObject
{

class Earth : public tsc::SkyObject::Planet
{
	public:
		Earth(tsc::Utils::IDataStorage& dataStorage);
		~Earth();
};

}
}



#endif /* EARTH_H_ */

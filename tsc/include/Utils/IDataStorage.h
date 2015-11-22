/*
 * IDataStorage.h
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#ifndef IDATASTORAGE_H_
#define IDATASTORAGE_H_

#include <vector>
#include "Math/Units.h"

namespace tsc
{
namespace Utils
{

class IDataStorage
{
	public:
		virtual ~IDataStorage() { };
		virtual bool getOrbitalTerms(const int tid, std::vector<tsc::Math::OrbitalTerm>& terms) = 0;
};

}
}



#endif /* IDATASTORAGE_H_ */

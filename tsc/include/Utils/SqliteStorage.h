/*
 * SqliteStorage.h
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#ifndef SQLITESTORAGE_H_
#define SQLITESTORAGE_H_

#include <string>
//#include <sqlite3.h>
#include "Utils/IDataStorage.h"

struct sqlite3;

namespace tsc
{
namespace Utils
{

class SqliteStorage : public IDataStorage
{
	public:
		SqliteStorage(std::string filename);
		~SqliteStorage();
		bool getOrbitalTerms(const int tid, std::vector<tsc::Math::OrbitalTerm>& terms);

	private:
		bool _dbOpened;
		sqlite3 *_db;
};

}
}



#endif /* SQLITESTORAGE_H_ */

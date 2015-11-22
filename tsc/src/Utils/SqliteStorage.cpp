/*
 * SqliteStorage.cpp
 *
 *  Created on: Nov 21, 2015
 *      Author: ben
 */

#include <iostream>
#include <sqlite3.h>
#include "Utils/SqliteStorage.h"

using std::string;
using std::vector;
using tsc::Math::OrbitalTerm;
using tsc::Utils::SqliteStorage;


SqliteStorage::SqliteStorage(string filename)
{
	if (sqlite3_open_v2(filename.c_str(), &_db, SQLITE_OPEN_READONLY, NULL) != SQLITE_OK)
	{
		std::cerr << "Failed to open the database file " << filename << std::endl;
		_dbOpened = false;
		_db = NULL;
	}
	else
	{
		_dbOpened = true;
	}
}

SqliteStorage::~SqliteStorage()
{
	if (_dbOpened)
	{
		sqlite3_close_v2(_db);
		_db = NULL;
	}
}

bool SqliteStorage::getOrbitalTerms(const int tid, vector<OrbitalTerm>& terms)
{
	if (!_dbOpened)
	{
		return false;
	}
    const std::string sqlStatement = "SELECT rank,A,B,C FROM planets WHERE tid=? ORDER BY rank DESC;";
	sqlite3_stmt *preparedStatement = NULL;

	if (sqlite3_prepare_v2(_db, sqlStatement.c_str(), sqlStatement.length(), &preparedStatement, NULL) != SQLITE_OK)
	{
		return false;
	}

	if (preparedStatement == NULL)
	{
		return false;
	}

	if(sqlite3_bind_int(preparedStatement, 1, tid) != SQLITE_OK)
	{
        sqlite3_finalize(preparedStatement);
		return false;
	}

	while (sqlite3_step(preparedStatement) == SQLITE_ROW)
	{
		unsigned int rank;
		OrbitalTerm term;
		rank = sqlite3_column_int(preparedStatement, 0);
		term.A = sqlite3_column_double(preparedStatement, 1);
		term.B = sqlite3_column_double(preparedStatement, 2);
		term.C = sqlite3_column_double(preparedStatement, 3);

		if (rank > terms.capacity())
		{
			terms.resize(rank);
		}

		terms.at(rank - 1) = term;
	}

    sqlite3_finalize(preparedStatement);
    return true;
}



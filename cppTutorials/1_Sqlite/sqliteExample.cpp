/**
 * mht
 *
 * begin to work with sqlite, and initial point of code starts from stackoverflow as always
 * 
 * https://stackoverflow.com/questions/10850375/c-create-database-using-sqlite-for-insert-update
 *
 * table in the database is created from outside and this code will insert lines while parsing csv file 
 *
 * to be honest, this code is pretty neat and practitaly useless due to write time to database
 * it could have been more effective if sql statement code was created more intelligently moreover, optimization is needed for sql write process
 *
 * enough for beginning !
 *
 */

#include <iostream>
#include <sstream>
#include <sqlite3.h>
#include "csv.h"

using namespace std;

void createDb()
{
	sqlite3* pDb = NULL;
	sqlite3_stmt* query = NULL;
	int ret = 0;

	// initialize engine
	if (SQLITE_OK != (ret = sqlite3_initialize()))
	{
		printf("Failed to initialize library: %d\n", ret);
	}
	// open connection to a DB
	if (SQLITE_OK != (ret = sqlite3_open_v2("test.db", &pDb, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)))
	{
		printf("Failed to open conn: %d\n", ret);
	}
	sqlite3_finalize(query);
    sqlite3_close(pDb);
	sqlite3_shutdown();
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for (i = 0; i < argc; i++)
	{
		cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << "\n";
	}
	cout << "\n";
	return 0;
}

static int clbk(void *NotUsed, int argc, char **argv, char **azColName)
{
	return 0;
}

void fillDb()
{
	const int STATEMENTS = 2;
	sqlite3 *db;
	char *zErrMsg = 0;
	const char *pSQL[STATEMENTS];
	int rc;

	rc = sqlite3_open("test2.db", &db);

	if (rc)
	{
		cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
	}
	else
	{
		cout << "Open database successfully\n\n";
	}

	pSQL[0] = "insert into LandsatIndex (SCENE_ID, PRODUCT_ID, SPACECRAFT_ID) values ('SCENE_ID_3', 'PRODUCT_ID_3', 'SPACECRAFT_ID_3')";

	pSQL[1] = "select * from LandsatIndex";

	for (int i = 0; i < STATEMENTS; i++)
	{
		rc = sqlite3_exec(db, pSQL[i], callback, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			cout << "SQL error: " << sqlite3_errmsg(db) << "\n";
			sqlite3_free(zErrMsg);
			break;
		}
	}

	sqlite3_close(db);
}

void clearDb(sqlite3 *db)
{
	char *zErrMsg = 0;
	int rc;
	string statement = "delete from LandsatIndex";
	rc = sqlite3_exec(db, statement.c_str(), clbk, 0, &zErrMsg);
	if (rc != SQLITE_OK)
	{
		cout << "SQL error: " << sqlite3_errmsg(db) << "\n";
		sqlite3_free(zErrMsg);
		return;
	}
}

void fillDb2()
{
	io::CSVReader<18> in("index.csv");
	in.read_header(io::ignore_extra_column,
		"SCENE_ID",
		"PRODUCT_ID",
		"SPACECRAFT_ID",
		"SENSOR_ID",
		"DATE_ACQUIRED",
		"COLLECTION_NUMBER",
		"COLLECTION_CATEGORY",
		"SENSING_TIME",
		"DATA_TYPE",
		"WRS_PATH",
		"WRS_ROW",
		"CLOUD_COVER",
		"NORTH_LAT",
		"SOUTH_LAT",
		"WEST_LON",
		"EAST_LON",
		"TOTAL_SIZE",
		"BASE_URL");

	std::string SCENE_ID;
	std::string PRODUCT_ID;
	std::string SPACECRAFT_ID;
	std::string SENSOR_ID;
	std::string DATE_ACQUIRED;
	std::string COLLECTION_NUMBER;
	std::string COLLECTION_CATEGORY;
	std::string SENSING_TIME;
	std::string DATA_TYPE;
	std::string WRS_PATH;
	std::string WRS_ROW;
	std::string CLOUD_COVER;
	std::string NORTH_LAT;
	std::string SOUTH_LAT;
	std::string WEST_LON;
	std::string EAST_LON;
	std::string TOTAL_SIZE;
	std::string BASE_URL;

	sqlite3 *db;
	char *zErrMsg = 0;
	int rc;

	rc = sqlite3_open("test.db", &db);

	if (rc)
	{
		cout << "Can't open database: " << sqlite3_errmsg(db) << "\n";
	}
	else
	{
		cout << "Open database successfully\n\n";
	}

	clearDb(db);

	int i = 0;
	while (in.read_row(SCENE_ID,
		PRODUCT_ID,
		SPACECRAFT_ID,
		SENSOR_ID,
		DATE_ACQUIRED,
		COLLECTION_NUMBER,
		COLLECTION_CATEGORY,
		SENSING_TIME,
		DATA_TYPE,
		WRS_PATH,
		WRS_ROW,
		CLOUD_COVER,
		NORTH_LAT,
		SOUTH_LAT,
		WEST_LON,
		EAST_LON,
		TOTAL_SIZE,
		BASE_URL))
	{
		stringstream statement;
		statement << "insert into LandsatIndex (SCENE_ID,";
		statement <<" PRODUCT_ID,";
		statement <<" SPACECRAFT_ID,";
		statement <<" SENSOR_ID,";
		statement <<" DATE_ACQUIRED,";
		statement <<" COLLECTION_NUMBER,";
		statement <<" COLLECTION_CATEGORY,";
		statement <<" SENSING_TIME,";
		statement <<" DATA_TYPE,";
		statement <<" WRS_PATH,";
		statement <<" WRS_ROW,";
		statement <<" CLOUD_COVER,";
		statement <<" NORTH_LAT,";
		statement <<" SOUTH_LAT,";
		statement <<" WEST_LON,";
		statement <<" EAST_LON,";
		statement <<" TOTAL_SIZE,";
		statement << " BASE_URL)";
		statement << " values(";
		statement << "'" << SCENE_ID << "',";
		statement << "'" << PRODUCT_ID << "',";
		statement << "'" << SPACECRAFT_ID << "',";
		statement << "'" << SENSOR_ID << "',";
		statement << "'" << DATE_ACQUIRED << "',";
		statement << "'" << COLLECTION_NUMBER << "',";
		statement << "'" << COLLECTION_CATEGORY << "',";
		statement << "'" << SENSING_TIME << "',";
		statement << "'" << DATA_TYPE << "',";
		statement << "'" << WRS_PATH << "',";
		statement << "'" << WRS_ROW << "',";
		statement << "'" << CLOUD_COVER<< "',";
		statement << "'" << NORTH_LAT << "',";
		statement << "'" << SOUTH_LAT << "',";
		statement << "'" << WEST_LON << "',";
		statement << "'" << EAST_LON << "',";
		statement << "'" << TOTAL_SIZE << "',";
		statement << "'" << BASE_URL << "'";
		statement <<")";

		if (i++ % 10000 == 0)
		{
			cout << i << endl;
			cout << statement.str() << endl;
		}

		rc = sqlite3_exec(db, statement.str().c_str(), clbk, 0, &zErrMsg);
		if (rc != SQLITE_OK)
		{
			cout << "SQL error: " << sqlite3_errmsg(db) << "\n";
			sqlite3_free(zErrMsg);
			break;
		}
	}

	sqlite3_close(db);
}

int main()
{
	fillDb2();
	return 0;
}
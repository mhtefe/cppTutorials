/**
 * mht
 *
 * a csv parser header only project I found while wandering in github
 * https://github.com/ben-strasser/fast-cpp-csv-parser
 * 
 * pretty well designed and written neat
 * I'll try to use it to parse landsat imageries index file (~3 Gb txt file) published on google services.
 * 
 * here's the link
 * https://cloud.google.com/storage/docs/public-datasets/landsat
 *
 */

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include "csv.h"

using namespace std;

int main()
{
	string csvF = "index.csv";

	/**
	 * before iteration check file length
	 */
	ifstream fin(csvF, ios::ate); 
	int size = fin.tellg();   // is this the length of lines ?

	vector<string> ss;
	io::CSVReader<18> in(csvF);
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
		if (i++ % 10000 == 0)
			std::cout << i << " - " << BASE_URL << "/" << PRODUCT_ID << std::endl;
	}

	return 0;
}
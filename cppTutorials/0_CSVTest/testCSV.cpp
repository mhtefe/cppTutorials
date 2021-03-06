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

#define gcs_ls8
///#define gcs_s2

int main()
{

	// 13.9M record
	string csv_google_LS8 = "C:/Users/memo/Desktop/landsat-sentinel/LS_S2downloader/LS_S2downloader/indexLS8.csv";
	string csv_google_S2 = "C:/Users/memo/Desktop/landsat-sentinel/LS_S2downloader/LS_S2downloader/indexS2.csv";
	string csv_aws_LS8 = "C:/Users/memo/Desktop/landsat-sentinel/LS_S2downloader/LS_S2downloader/scene_list";

	int i = 0;
	time_t _tic, _toc;

	////////////////////////////////////////////////////////////////////////// google landsat 8 //////////////////////////////////////////////////////////////////////////
#ifdef gcs_ls8
	ifstream fin(csv_google_LS8, ios::ate);
	unsigned long long size = fin.tellg();   // is this the length of lines ?

	io::CSVReader<18> inLS8(csv_google_LS8);
	inLS8.read_header(io::ignore_extra_column,
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

	std::string LS8_SCENE_ID;
	std::string LS8_PRODUCT_ID;
	std::string LS8_SPACECRAFT_ID;
	std::string LS8_SENSOR_ID;
	std::string LS8_DATE_ACQUIRED;
	std::string LS8_COLLECTION_NUMBER;
	std::string LS8_COLLECTION_CATEGORY;
	std::string LS8_SENSING_TIME;
	std::string LS8_DATA_TYPE;
	std::string LS8_WRS_PATH;
	std::string LS8_WRS_ROW;
	std::string LS8_CLOUD_COVER;
	std::string LS8_NORTH_LAT;
	std::string LS8_SOUTH_LAT;
	std::string LS8_WEST_LON;
	std::string LS8_EAST_LON;
	std::string LS8_TOTAL_SIZE;
	std::string LS8_BASE_URL;

	
	_tic = time(0);
	while (inLS8.read_row(LS8_SCENE_ID,
		LS8_PRODUCT_ID,
		LS8_SPACECRAFT_ID,
		LS8_SENSOR_ID,
		LS8_DATE_ACQUIRED,
		LS8_COLLECTION_NUMBER,
		LS8_COLLECTION_CATEGORY,
		LS8_SENSING_TIME,
		LS8_DATA_TYPE,
		LS8_WRS_PATH,
		LS8_WRS_ROW,
		LS8_CLOUD_COVER,
		LS8_NORTH_LAT,
		LS8_SOUTH_LAT,
		LS8_WEST_LON,
		LS8_EAST_LON,
		LS8_TOTAL_SIZE,
		LS8_BASE_URL))
	{
		if (i++ % 100000 == 0)
			std::cout <<"LS8: " << i << " - "  << LS8_DATE_ACQUIRED  << " - "<< LS8_BASE_URL << "/" << LS8_PRODUCT_ID << std::endl;
	}
	_toc = time(0);
	std::cout <<"Elapsed Time: " << difftime(_toc, _tic) << " sec. " <<std::endl;
#endif
	////////////////////////////////////////////////////////////////////////// google sentinel 2 //////////////////////////////////////////////////////////////////////////
#ifdef gcs_s2
	io::CSVReader<14> inS2(csv_google_S2);
	inS2.read_header(io::ignore_extra_column,
		"GRANULE_ID",
		"PRODUCT_ID",
		"DATATAKE_IDENTIFIER",
		"MGRS_TILE",
		"SENSING_TIME",
		"TOTAL_SIZE",
		"CLOUD_COVER",
		"GEOMETRIC_QUALITY_FLAG",
		"GENERATION_TIME",
		"NORTH_LAT",
		"SOUTH_LAT",
		"WEST_LON",
		"EAST_LON",
		"BASE_URL");

	std::string S2_GRANULE_ID;
	std::string S2_PRODUCT_ID;
	std::string S2_DATATAKE_IDENTIFIER;
	std::string S2_MGRS_TILE;
	std::string S2_SENSING_TIME;
	std::string S2_TOTAL_SIZE;
	std::string S2_CLOUD_COVER;
	std::string S2_GEOMETRIC_QUALITY_FLAG;
	std::string S2_GENERATION_TIME;
	std::string S2_NORTH_LAT;
	std::string S2_SOUTH_LAT;
	std::string S2_WEST_LON;
	std::string S2_EAST_LON;
	std::string S2_BASE_URL;

	i = 0;

    _tic = time(0);
	while (inS2.read_row(S2_GRANULE_ID,
		S2_PRODUCT_ID,
		S2_DATATAKE_IDENTIFIER,
		S2_MGRS_TILE,
		S2_SENSING_TIME,
		S2_TOTAL_SIZE,
		S2_CLOUD_COVER,
		S2_GEOMETRIC_QUALITY_FLAG,
		S2_GENERATION_TIME,
		S2_NORTH_LAT,
		S2_SOUTH_LAT,
		S2_WEST_LON,
		S2_EAST_LON,
		S2_BASE_URL))
	{
		if (i++ % 100000 == 0)
			std::cout << "S2: " << i << " - " << S2_BASE_URL << "/" << S2_PRODUCT_ID << std::endl;
	}

	_toc = time(0);
	std::cout << "Elapsed Time: " << difftime(_toc, _tic) << " sec. " << std::endl;
#endif
	return 0;
}
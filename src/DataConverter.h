/*
 * DataConverter.h
 *
 *  Created on: 28 Nov 2016
 *      Author: andrew
 */

#ifndef DATACONVERTER_H_
#define DATACONVERTER_H_

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include "FileHandler.h"
#include "DataStore.h"
#include <string>
#include <vector>

class DataConverter : public FileHandler
{
	public:
		DataConverter();
		virtual ~DataConverter();

		bool convertFile();
		virtual bool setOutputFilename(std::string);

	private:
		bool readRouteFile();
		bool parseData();
		bool writeData();

		std::string _strRawData;
		std::vector<DataStore> _vData;
};


#endif /* DATACONVERTER_H_ */

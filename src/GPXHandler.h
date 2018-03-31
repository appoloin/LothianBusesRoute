/*
 * GPXHandler.h
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */

#ifndef GPXHANDLER_H_
#define GPXHANDLER_H_

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include "FileHandler.h"

class GPXHandler: public FileHandler
{
	public:
		GPXHandler();
		virtual ~GPXHandler();
		virtual bool setOutputFilename(std::string);

		void setOutputFileFormat(std::string);
		std::string getOutputFileFormat();
		void setRouteNumber(std::string);
		std::string getRouteNumber();
		bool convertRoute();

	private:
		std::string createCommand();
		std::string _strRouteNumber;
		std::string _strFileFormat;
};



#endif /* GPXHANDLER_H_ */

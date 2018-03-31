/*
 * ArgHandler.h
 *
 *  Created on: 26 Nov 2016
 *      Author: andrew
 */

#ifndef ARGHANDLER_H_
#define ARGHANDLER_H_

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include <string>
#include <iostream>
#include <vector>



class ArgHandler
{
	public:
		ArgHandler();
		~ArgHandler();
		int parseCommandLine(int argc, char *argv[]);	//parse command line args
		std::string getOutputFolder();  					//folder for gpx file
		std::string getOutputFilename();  					// gpx filename
		std::vector<std::string> getBusRouteNumber(); 				//bus number
		std::string getOutputFormat();						//output file format

	private:
		std::string _strDestFolder;
		std::vector<std::string> _vBusRouteNumber;
		std::string _strFormat;
};


#endif /* ARGHANDLER_H_ */

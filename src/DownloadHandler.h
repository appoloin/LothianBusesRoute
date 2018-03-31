/*
 * DownloadHandler.h
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */

#ifndef DOWNLOADHANDLER_H_
#define DOWNLOADHANDLER_H_

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include "FileHandler.h"
#include <string>



class DownloadHandler: public FileHandler
{
	public:
		DownloadHandler();
		virtual ~DownloadHandler();

		bool  setRoute(std::string);
		virtual bool setPath(std::string);
		virtual bool setOutputFilename(std::string);
		bool downloadRoute();


	private:
		std::string createCommand();


		std::string _strBusRoute;

};



#endif /* DOWNLOADHANDLER_H_ */

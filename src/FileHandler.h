/*
 * FileHandler.h
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */

#ifndef FILEHANDLER_H_
#define FILEHANDLER_H_

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include <string>
#include <iostream>

class FileHandler
{
	public:
		FileHandler();
		virtual ~FileHandler();

		void setDeleteFlag(bool);

		virtual bool setPath(std::string);
		std::string getPath();

		virtual bool setOutputFilename(std::string);
		std::string getOutputFilename();
		std::string getFullOutputPath();

		bool setInputFilename(std::string);
		std::string getInputFilename();
		std::string getFullInputPath();

	private:
		bool _bDeleteFlag;
		std::string _strPath;
		std::string _strOutputFilename;
		std::string _strInputFilename;
};



#endif /* FILEHANDLER_H_ */

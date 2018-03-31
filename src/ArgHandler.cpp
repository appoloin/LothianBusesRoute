/*
 * ArgHandler.cpp
 *
 *  Created on: 26 Nov 2016
 *      Author: andrew
 */

#include "ArgHandler.h"
#include <boost/filesystem.hpp>
#include "boost/program_options.hpp"
namespace po = boost::program_options;


ArgHandler::ArgHandler()
{
	_strDestFolder.empty();
	_vBusRouteNumber.empty();
	_strFormat.empty();
}

ArgHandler::~ArgHandler()
{
	_strDestFolder.empty();
	_vBusRouteNumber.empty();
	_strFormat.empty();
}


int ArgHandler::parseCommandLine(int argc, char *argv[])
{
	int iReturn = -1;

	boost::program_options::options_description desc("Options");
	try
	{
		desc.add_options()
						("help,h", "Print this help message")
						("version,v", "Version number")
						("route,r", po::value<std::vector<std::string>>(&_vBusRouteNumber)->required()
									,"Bus route number ie N19 X37 60")
						("output,o", po::value<std::string>(&_strDestFolder),
									"Location of gpx file ie /home/USER/Downloads/10.gpx")
						("format,f", po::value<std::string>(&_strFormat),
									"Output format ie GPX, KML");;

		po::positional_options_description pos;
		pos.add("route", -1);

		po::variables_map vm;
		po::store(po::command_line_parser(argc, argv).options(desc).positional(pos).run(), vm);

		if (vm.count("help")||vm.count("version"))
		{
			if (vm.count("help")) std::cout << desc << std::endl;
			if (vm.count("version")) std::cout << "version 1" << std::endl;
		}
		else
		{
			po::notify(vm);
			if (vm.count("route"))
			{
				iReturn =1;
				//Debug( "Number of Routes " << _vBusRouteNumber.size());
			}
			if (vm.count("output"))
			{
				iReturn =1;
				//Debug( "Output " << _strDestFolder);
			}
		}
	}
	catch(po::error& e)
	{
		iReturn =-2;
		Error ("ERROR: " << e.what());
		Error (desc);
	}

	return iReturn;
}



std::string ArgHandler::getOutputFolder()
{
	std::string strReturn;
	strReturn.empty();

	try
	{
		boost::filesystem::path path(_strDestFolder);
		strReturn = path.parent_path().c_str();   //input=/test1/test2/test3.xml  result=/test1/test2
		Debug("ArgHandler::getOutputFolder " <<strReturn);
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
	}
	return strReturn;
}


std::string ArgHandler::getOutputFilename()
{//stem //extension //has_filename()
	std::string strReturn;
	strReturn.empty();

	try
	{
		boost::filesystem::path path(_strDestFolder);
		if (path.has_filename())
		{
			strReturn = path.filename().c_str();   //input=/test1/test2/test3.xml  result=test3.xml
			Debug("ArgHandler::getOutputFilename " <<strReturn);
		}
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
	}
	return strReturn;
}


std::vector<std::string> ArgHandler::getBusRouteNumber()
{
	return _vBusRouteNumber;
}



std::string ArgHandler::getOutputFormat()
{
	return _strFormat;
}




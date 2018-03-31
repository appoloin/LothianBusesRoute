/*
 * GPXHandler..cpp
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */


#include "GPXHandler.h"
#include <cerrno>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/date_time/posix_time/posix_time_io.hpp>


GPXHandler :: GPXHandler()
{
	_strRouteNumber.empty();
	_strFileFormat="gpx";
}



GPXHandler :: ~GPXHandler()
{
	_strRouteNumber.empty();
	_strFileFormat.empty();
}



bool GPXHandler :: convertRoute()
{
	bool bResult = false;

	bool bFileTest = false;
	//check filename has been set.
	if (getOutputFilename().length()==0)
	{
		Debug (" DownloadHandler :: convertRoute - OutputFileName not found");
		std::string strDummy;
		bFileTest = setOutputFilename(strDummy);
	}
	else
		bFileTest = true;

	if (bFileTest)
	{
		//download file
		int iResult = std::system(createCommand().c_str()); //Execute strCommand
		Debug (" DownloadHandler :: convertRoute = iResult " << iResult);
		if(iResult >0)
		{
			if (WIFEXITED(iResult))
			{
				Error (" DownloadHandler :: convertRoute -- Exit code " << WEXITSTATUS(iResult));
			}
		}
		else
			bResult= true;
	}
	return bResult;
}




std::string GPXHandler :: createCommand()
{
	// gpsbabel -i unicsv,fields=lat+lon+description -f file.csv -o gpx -F file.gpx
	//construct download command
	std::string strCommand = "gpsbabel "; 						//Executable
	strCommand +="-i unicsv,fields=lat+lon+name ";				//input file format
	//strCommand +="-x transform,trk=wpt  ";						//transform waypoints to route
	//strCommand +="-x nuketypes,waypoints ";						//remove waypoints
	//strCommand +="-x simplify,error ";					///
	strCommand +="-f ";											//input filename
	strCommand +="\""+getFullInputPath()+"\"";     				 //source folder and filename
	strCommand +=" -o ";										//output
	strCommand +=getOutputFileFormat();							//get output format
	strCommand +=" -F ";										//Output filename
	strCommand +="\""+getFullOutputPath()+"\"";					//destination folder and filename
	Debug (" GPXHandler :: createCommand = strCommand " << strCommand);

	return strCommand;
}




bool GPXHandler::setOutputFilename(std::string strName)
{
	bool bResult = false;
	Debug ("GPXHandler::setOutputFilename Start " << strName);

	bResult = FileHandler::setOutputFilename(strName);
	if (bResult ==false) //file exists or name not set - try something else
	{
		//Lothian Buses Route - ROUTENUMBER - DATE - HH/MM/SS YYYY
		std::string strFileName;
		strFileName = "Lothian Buses Route - ";
		strFileName += getRouteNumber();
		strFileName += " - ";

		strFileName += boost::posix_time::to_simple_string(boost::posix_time::second_clock::local_time());

		strFileName += "."+getOutputFileFormat();

		bResult = FileHandler::setOutputFilename(strFileName);
		Debug ("GPXHandler::setOutputFilename Start " << strFileName);
	}
	return bResult;
}



void GPXHandler::setRouteNumber(std::string strRoute)
{
	_strRouteNumber = strRoute;
}


std::string GPXHandler::getRouteNumber()
{
	return _strRouteNumber;
}


void GPXHandler::setOutputFileFormat(std::string strFormat)
{
	Debug ("GPXHandler::setOutputFileFormat Start " << strFormat);
	if (strFormat.length()>0)
	{
		boost::algorithm::to_lower(strFormat);
		_strFileFormat = strFormat;
		Debug ("GPXHandler::setOutputFileFormat _strFileFormat " << _strFileFormat);
	}
	else //default
		_strFileFormat = "gpx";
}

std::string GPXHandler::getOutputFileFormat()
{
	return _strFileFormat;
}





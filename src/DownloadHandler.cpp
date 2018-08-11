/*
 * DownloadHandler.cpp
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <cstdlib>
#include <stdlib.h>
#include <cerrno>
#include <fstream>
#include <iostream>
#include <cstring>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>
#include "DownloadHandler.h"


DownloadHandler::DownloadHandler()
{
	_strBusRoute.empty();
}



DownloadHandler::~DownloadHandler()
{
}



bool DownloadHandler::setRoute(std::string strRoute)
{
	Debug ("DownloadHandler::SetRoute " << strRoute);

	int bResult = false;
	//basic route number check;  bus numbers examples 1  112  N34 X47
	if (strRoute.length()>0 && strRoute.length()<4)
	{
		_strBusRoute = strRoute;
		bResult = true;
	}

	return bResult;
}




bool DownloadHandler::setPath(std::string strPath)
{
	Debug ("DownloadHandler::setOutputPath Start " << strPath);
	bool bResult = false;

	if (FileHandler::setPath(strPath))
	{
		Debug ("DownloadHandler::setOutputPath folder path set");
		bResult = true;
	}
	else
	{
		Debug ("DownloadHandler::setOutputPath folder not found");

		// try the $HOME environment variable
		std::string strHome = std::getenv("HOME");
		if (strHome.size()==0)
		{
			struct passwd* pwd = getpwuid(getuid());
			if (pwd) strHome = pwd->pw_dir;
		}
		Debug ("DownloadHandler::setOutputPath $HOME " <<strHome);
		if (FileHandler::setPath(strHome))
		{
			Debug ("DownloadHandler::setOutputPath folder path set");
			bResult = true;
		}
	}
	return bResult;
}




bool DownloadHandler::setOutputFilename(std::string strFilename)
{
	bool bResult = false;
	Debug ("DownloadHandler::setOutputFilename Start " << strFilename);
	bResult = FileHandler::setOutputFilename(strFilename);
	if (bResult ==false) //file exists - try something else
	{
		std::string strTempName;
		std::string chars("abcdefghijklmnopqrstuvwxyz"
						  "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
						  "1234567890");

		boost::random::random_device rng;
		boost::random::uniform_int_distribution<> index_dist(0, chars.size() - 1);
		for(int i = 0; i < 10; ++i)
		{
			strTempName+= chars[index_dist(rng)];
		}

		bResult = FileHandler::setOutputFilename(strFilename + strTempName);
	}
	return bResult;
}



std::string DownloadHandler :: createCommand()
{
	//construct download command
	std::string strCommand = "wget "; 		//downloader
	strCommand +="--no-check-certificate ";
	strCommand +="--show-progress "; 		//show download progress
	strCommand +="--output-document=";		//destination
	strCommand +=getFullOutputPath();     		//destination folder and filename

	//new url https://tfeapp.com/api/website/route.php?service_name=140
	//strCommand +=" https://lothianbuses.co.uk/tfeopendata/service/"; //target url
	strCommand +=" https://tfeapp.com/api/website/route.php?service_name=";
	strCommand += _strBusRoute;			    ///route to download
	Debug (" DownloadHandler :: createCommand = strCommand " << strCommand);

	return strCommand;
}



bool DownloadHandler :: downloadRoute()
{
	bool bResult = false;
	bool bFileTest = false;
	//check filename has been set. If not try using route number
	if (getOutputFilename().length()==0)
		bFileTest = setOutputFilename(_strBusRoute);
	else
		bFileTest = true;

	if (bFileTest)
	{
		//download file
		int iResult = std::system(createCommand().c_str()); //Execute strCommand
		Debug (" DownloadHandler :: createCommand = iResult " << iResult);
		if(iResult >0)
		{
			if (WIFEXITED(iResult))
			{
				Error (" DownloadHandler :: downloadRoute -- Exit code " << WEXITSTATUS(iResult));
			}
		}
		else
			bResult= true;
	}
	return bResult;
}

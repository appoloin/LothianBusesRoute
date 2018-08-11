/*
 * DataConverter.cpp
 *
 *  Created on: 28 Nov 2016
 *      Author: andrew
 */

#include "DataConverter.h"
#include <iostream>
#include <fstream>
#include <string>
#include <boost/regex.hpp>
#include <boost/random/random_device.hpp>
#include <boost/random/uniform_int_distribution.hpp>



DataConverter ::DataConverter()
{
	_strRawData.empty();
	_vData.empty();
}


DataConverter :: ~DataConverter()
{
	_strRawData.empty();
	_vData.empty();
}



bool DataConverter :: convertFile()
{
	Debug("DataConverter :: convertFile - Start");
	bool bResult = false;
	if (readRouteFile())
	{
		Debug("DataConverter :: convertFile - data loaded");
		if(parseData())
		{
			Debug("DataConverter :: convertFile - data parsed");
			if(writeData())
			{
				Debug("DataConverter :: convertFile - data written");

				bResult=true;
			}
		}
	}
	return bResult;
}




bool  DataConverter :: readRouteFile ()
{
	Debug("DataConverter :: readRouteFile - Start");
	bool bResult = false;

	try
	{
		std::ifstream fileData;
		fileData.open (getFullInputPath());

		std::string strTemp;
		while(std::getline(fileData,strTemp))
		{
			_strRawData+=strTemp;
		}

		fileData.close();

		//Debug("DataConverter :: readRouteFile" << _strRawData );
		if (_strRawData.length()>0) bResult = true;
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
	}
	return bResult;
}



bool DataConverter :: parseData()
{
	Debug("DataConverter :: parseData - Start");
	bool bResult = false;

	try
	{
		boost::regex regExp("\"latitude\":(.*?),\"longitude\":(.*?)},"); //break down into data rows
		boost::match_results<std::string::const_iterator> match;
		std::string::const_iterator start = _strRawData.begin();
		std::string::const_iterator end = _strRawData.end();
		while (boost::regex_search(start,end,match,regExp))
		{
			std::string::difference_type position = match.position();
			start += position + 1;
			std::string strFound = match.str();  //found row
		//	Debug("DataConverter :: parseData - data " << strFound);

			/*Example output
			*{"id":"6280302490","name":"Penicuik Centre","sms":"64324373","identifier":null,"direction":"E","latitude":55.82796,"longitude":-3.221642},
			*{"id":"6280325170","name":"Penicuik Centre","sms":"64324374","identifier":null,"direction":"W","latitude":55.82784,"longitude":-3.221526}
			*/

			//get elements
			boost::regex regExp2("\"latitude\":(.*?),\"longitude\":(.*?)}|],");
			boost::match_results<std::string::const_iterator> match2;
			if (boost::regex_search(strFound ,match2,regExp2))
			{
				/*Example output
				 * "lat":"55.90131","lng":"-3.259438"
				 * "lat":"55.90138","lng":"-3.258641","stop":{"sms":"36243574","atco_code":"6200248525","name":"Bonaly",
				*/
				std::string strLat = match2[1].str();
				std::string strLng = match2[2].str();
				std::string strName;
				if (match2.length()>3) strName = match2[3].str();
			//	Debug("DataConverter :: parseData - data2 - Lat " << strLat << " Lng " << strLng << " Name " << strName);

				DataStore Data;
				Data.setLatitude(strLat);
				Data.setLongitude(strLng);
				Data.setName(strName);
				_vData.push_back(Data);
				bResult=true; //data found
			}

		}
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
		bResult=false;
	}
	return bResult;
}



bool DataConverter :: writeData()
{
	Debug("DataConverter :: writeData - Start");
	bool bResult = false;

	try
	{
		bool bFileSet = false;

		//create/check output filename
		if (getOutputFilename().length()==0)
		{	//filename not set
			std::string strDummy;
			if (setOutputFilename(strDummy)) bFileSet= true;
		}
		else
			bFileSet= true;

		if (bFileSet)
		{
			Debug("DataConverter :: writeData - Output file Set");
			/*File Format unicvs
			* No,Latitude,Longitude,Name
			*/

			std::ofstream fileData;
			fileData.open (getFullOutputPath());
			//first line data description
		//	fileData<<"No,Latitude,Longitude,Name"<<std::endl;

			int i=1;
			for(auto line : _vData)
			{
				fileData<<i;
				fileData<<",";
				fileData<<line.getLatitude();
				fileData<<",";
				fileData<<line.getLongitude();
				fileData<<",";
				fileData<<"\""<<line.getName()<<"\"";
				fileData<<std::endl;
				i++;
			}
			fileData.flush();
			fileData.close();
			bResult = true;
		}
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
	}

	return bResult;
}



bool DataConverter::setOutputFilename(std::string strFilename)
{
	bool bResult = false;
	Debug ("DataConverter::setOutputFilename Start " << strFilename);
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

		bResult = FileHandler::setOutputFilename(strTempName +".csv");
	}
	return bResult;
}


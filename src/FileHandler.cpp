/*
 * FileHandler.cpp
 *
 *  Created on: 27 Nov 2016
 *      Author: andrew
 */



#include "FileHandler.h"
#include <boost/filesystem.hpp>

FileHandler :: FileHandler()
{
	_bDeleteFlag =false;
	_strPath.empty();
    _strOutputFilename.empty();
    _strInputFilename.empty();
}


FileHandler :: ~FileHandler()
{
	if (_bDeleteFlag)
	{
		boost::filesystem::path path(_strPath);
		path.append(_strOutputFilename);
		if (exists(path) &&   is_regular_file(path)) // exists and is a file
			boost::filesystem::remove(path);	//delete
	}
	_strPath.empty();
	_strOutputFilename.empty();
	_strInputFilename.empty();
}


//if set file will be delete on destruction
void FileHandler :: setDeleteFlag(bool bFlag)
{
	_bDeleteFlag = bFlag;
}



bool FileHandler :: setPath(std::string strPath)
{
	Debug ("FileHandler :: setPath - Start " << strPath);

	bool bResult= false;

	if (strPath.length()>0)  ///there's something here
	{
		boost::filesystem::path path(strPath);
		if (exists(path) && is_directory(path))
		{
			Debug("FileHandler::setPath - folder found" );
			_strPath = path.c_str();
			bResult= true;
		}
	}
	return bResult;
}




bool FileHandler :: setOutputFilename(std::string strFilename)
{
	Debug ("FileHandler::setOutputFilename Start " << strFilename);
	bool bResult = false;

	if (strFilename.length()>0 && _strPath.length()>0 )
	{
		boost::filesystem::path path(_strPath);
		path.append(strFilename);
		if (!exists(path)) //path doesn't exist
		{
			Debug("FileHandler::setOutputFilename - file not found" );
			_strOutputFilename = strFilename;
			bResult= true;
		}
	}
	return bResult;
}



std::string FileHandler :: getPath()
{
	return _strPath;
}



std::string FileHandler :: getOutputFilename()
{
	return _strOutputFilename;
}



std::string FileHandler :: getFullOutputPath()
{
	std::string strPath;
	strPath.empty();

	if (_strPath.length()>0 && _strOutputFilename.length()>0 )
	{
		boost::filesystem::path path(_strPath);
		path.append(_strOutputFilename);
		strPath=path.c_str();
	}
	Debug("FileHandler::getFullOutputPath - " << strPath );
	return strPath;
}



bool FileHandler :: setInputFilename(std::string strFilename)
{
	Debug("FileHandler::setInputFilename - start " << strFilename );
	bool bResult = false;

	if (strFilename.length()>0 && _strPath.length()>0 )
	{
		boost::filesystem::path path(_strPath);
		path.append(strFilename);
		if (exists(path)) //path   exist
		{
			Debug("FileHandler::setInputFilename - file  found" );
			_strInputFilename = strFilename;
			bResult= true;
		}
	}

	return bResult;
}


std::string FileHandler :: getFullInputPath()
{
	std::string strPath;
	strPath.empty();

	if (_strPath.length()>0 && _strInputFilename.length()>0 )
	{
		boost::filesystem::path path(_strPath);
		path.append(_strInputFilename);
		strPath=path.c_str();
	}
	Debug("FileHandler::_strInputFilename - " << strPath );
	return strPath;
}



/*
 * DataStore.cpp
 *
 *  Created on: 28 Nov 2016
 *      Author: andrew
 */

#include "DataStore.h"

DataStore::DataStore()
{
	_strLng.empty();
	_strLat.empty();
	_strName.empty();
}

DataStore::~DataStore()
{
	_strLng.empty();
	_strLat.empty();
	_strName.empty();
}

void DataStore::setLatitude(std::string strLat)
{
	_strLat = strLat;
}


void DataStore::setLongitude(std::string strLng)
{
	_strLng = strLng;
}


void DataStore::setName(std::string strName)
{
	_strName = strName;
}


std::string DataStore::getLatitude()
{
	return _strLat;
}


std::string DataStore::getLongitude()
{
	return _strLng;
}


std::string DataStore::getName()
{
	return _strName;
}

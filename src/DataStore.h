/*
 * DataStore.h
 *
 *  Created on: 28 Nov 2016
 *      Author: andrew
 */

#ifndef DATASTORE_H_
#define DATASTORE_H_

#include <string>


class DataStore
{
	public:
		DataStore();
		~DataStore();

		void setLongitude(std::string);
		std::string getLongitude();

		void setLatitude(std::string);
		std::string getLatitude();

		void setName(std::string);
		std::string getName();

	private:
		std::string _strLng;
		std::string _strLat;
		std::string _strName;
};

#endif /* DATASTORE_H_ */

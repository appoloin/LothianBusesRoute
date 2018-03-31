//============================================================================
// Name        : LothianBusRoute.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#ifndef NDEBUG
	#define Debug(msg)  std::cout << msg << std::endl
#else
	#define Debug(msg)
#endif
#define Error(msg) std::cerr << msg << std::endl


#include <iostream>
#include <string>
#include <vector>
#include "ArgHandler.h"
#include "DownloadHandler.h"
#include "GPXHandler.h"
#include "DataConverter.h"

int main(int argc, char* argv[])
{
	try
	{
		ArgHandler Args;
		if (Args.parseCommandLine(argc, argv)>0) //parse the arguments
		{
			//check for routes
			std::vector<std::string> vBus = Args.getBusRouteNumber();
			if (vBus.size()==0) Error("No Bus Routes entered");


			for(auto bus : vBus)
			{
				DownloadHandler Download;
				if (!Download.setRoute(bus))
				{
					Error ("Invalid bus number");
					break; //exit loop
				}

				Download.setDeleteFlag(true);
				if (!Download.setPath(Args.getOutputFolder()))
				{
					Error ("Output folder not found");
					break; //exit loop
				}

				//download file from Lothian Bus Server
				if (!Download.downloadRoute())
				{
					Error ("Route not found");
					break; //exit loop
				}

				//Simplify data
				DataConverter DataConverter;
				DataConverter.setDeleteFlag(true);
				DataConverter.setPath(Download.getPath());
				if (!DataConverter.setInputFilename(Download.getOutputFilename()))
				{
					Error ("Route file not found");
					break; //exit loop
				}

				if (!DataConverter.convertFile())
				{
					Error ("Route file conversion has failed");
					break; //exit loop
				}

				//convert to gpx format
				GPXHandler GpxHandler;
				GpxHandler.setPath(DataConverter.getPath());
				GpxHandler.setRouteNumber(bus);
				GpxHandler.setOutputFileFormat(Args.getOutputFormat());
				GpxHandler.setOutputFilename(Args.getOutputFilename());
				if(!GpxHandler.setInputFilename(DataConverter.getOutputFilename()))
				{
					Error ("Route file not found");
					break; //exit loop
				}

				if (GpxHandler.convertRoute())
				{
					std::cout << "GPX file created : "<< GpxHandler.getFullOutputPath()<<std::endl;
				}
				else
					Error ("GPX file creation has failed");
			}
		}
	}
	catch(std::exception &e)
	{
		Error ("ERROR: " << e.what());
	}
	return 0;
}

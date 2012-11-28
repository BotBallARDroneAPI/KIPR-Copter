/// Drone.cpp
#include "Drone.h"
#include "DroneConstants.h"

namespace ARDrone
{
	
Drone::Drone()
{
	
}

Drone::~Drone()
{
    
}

bool Drone::start()
{
    try 
    {
		myController = new ARDrone::Controller;
		myVideoDataReceiver = new ARDrone::VideoDataReceiver(myController,  DRONE_IP.c_str()); 
		myNavigationDataReceiver = new ARDrone::NavigationDataReceiver(myController,  DRONE_IP.c_str());
		
		
		myController->connectWithDroneAtAddress(DRONE_IP.c_str());
		ccxx::Thread::sleep(200);
		
		myNavigationDataReceiver->start();
		ccxx::Thread::sleep(200);
		
		myVideoDataReceiver->start();
		ccxx::Thread::sleep(200);
		return true;
    }
    catch(ccxx::Exception& ex) 
    {
		std::cout << ex.what() << std::endl;
		delete myVideoDataReceiver;
		delete myNavigationDataReceiver;
		delete myController;
		return false;
    }
}

void Drone::stop()
{
    try 
    {
		myNavigationDataReceiver->stop();
		myVideoDataReceiver->stop();
    }
    catch(ccxx::Exception& ex) 
    {
		std::cout << ex.what() << std::endl;
    }
    
    delete myVideoDataReceiver;
    delete myNavigationDataReceiver;
    delete myController;
}
	ARDrone::Controller& ARDrone::Drone::controller()
	{
		return *myController;
	}
	
	ARDrone::VideoDataReceiver& Drone::videoDataReceiver()
	{
		return *myVideoDataReceiver;
	}
	
	ARDrone::NavigationDataReceiver& Drone::navigationDataReceiver()
	{
		return *myNavigationDataReceiver;
	}
	
}//ARDrone
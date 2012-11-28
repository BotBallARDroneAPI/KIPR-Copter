/// Drone.h
#ifndef DRONE_H
#define DRONE_H

#include "Controller.h"
#include "VideoDataReceiver.h"
#include "NavigationDataReceiver.h"

namespace ARDrone
{
  class Drone
  {
	/**
	@brief A pointer to this drones controller (Sends commands to the Drone)
	**/
    ARDrone::Controller* myController;
	  
	/**
	@brief A pointer to this drones video data receiver (Receives data from the Drone)
	**/
    ARDrone::VideoDataReceiver* myVideoDataReceiver;
	  
	/**
	@brief A pointer to this drones video data receiver (Receives data from the Drone)
	**/
    ARDrone::NavigationDataReceiver* myNavigationDataReceiver;
    
  public:
	/**
	@brief Default Constructor for the Drone
	**/
    Drone();
	
	/**
	@brief Drone Destructor
	**/
    ~Drone();
    
	/**
	 @brief Sets up the connections to the Drone and starts the nav and video data receivers
	 **/
    bool start();
	  
	/**
	 @brief Stops the nav and video receivers and deletes the dynamic memory
	 **/
    void stop();
	
	/**
	@brief Returns a reference to the Drone's Controller so the API can manipulate it 
	**/
    ARDrone::Controller& controller();
	
	/**
	@brief Returns a reference to the Drone's Video Data Receiver so the API can manipulate it 
	**/
    ARDrone::VideoDataReceiver& videoDataReceiver();
	
	/**
	@brief Returns a reference to the Drone's Navigation Data Receiver so the API can manipulate it 
	**/
    ARDrone::NavigationDataReceiver& navigationDataReceiver();
  };
}//namespace ARDrone
#endif

/// NavigationDataReceiver.h
#ifndef NAVIGATIONDATARECEIVER_H
#define NAVIGATIONDATARECEIVER_H

#include <commonc++/Mutex.h++>
#include <commonc++/Thread.h++>
#include <string>
#include "MemoryLibrary.h"
#include "NavigationData.h"
#include "Controller.h"

namespace ARDrone
{
	
  typedef float float32_t;
	
  class NavigationDataReceiver :public ccxx::Thread
  {
  private:
	/**
	 @brief A CommunicationChannel specifically for receiving Navigation Data
	 **/
    ARDrone::CommunicationChannel myCommunicationChannel;
	
	/**
	 A buffer that will contain the most recent Navigation Data
	 **/
    NavigationData myNavData;
	  
	/**
	 @brief A variable to ensure Mutual Exclusion to prevent reading and updating the buffer at the same time
	 **/
    ccxx::Mutex myMutex;
	
	/**
	 The Address of the Drone
	 **/
    std::string myDroneAddress;
	
	/**
	 A pointer to a Drone's Controller
	 **/
    ARDrone::Controller* myController;
	
  public:
	/**
	 @brief A Timestamp to ensure that the NavData is updated in a timely manner
	 **/
	long navTimestamp;
	  
	/**
	 @brief A constructor for a Navigation Data Receiver that also initializes the Controller and Drone IP
	 @param pController A pointer to a controller that is able to send ATCommands
	 @param	szDroneIpAddress A string representing the Drone's IP Address so we can connect to get NavData
	 **/
    NavigationDataReceiver(ARDrone::Controller* pController, const char* szDroneIpAddress);
	
	/**
	 @brief Destructor that ensures that the Receiver Stops and closes its connections if the object is destroyed
	 **/
    ~NavigationDataReceiver() throw ();
	
	/**
	 @brief Copies the internal NavData buffer to the parameterized buffer
	 @param data A reference to a Navigation Data object that will be filled with the data stored in the myNavData member
	 **/
    void copyDataTo(ARDrone::NavigationData& data);
	  
  protected:
	/**
	@brief Runs the NavDataReceiver thread to establish a connection to the Drone to receive Navigation Data
	**/
    void run();
	/**
	 @brief Parses the Navigation Data into a NavigationData object
	 @param buffer A data buffer that has been received and needs parsing
	**/
    bool parse(MemoryLibrary::Buffer& buffer);
	/**
	 @brief Parses the state data from the given state integer
	 @param state A binary string received from the drone that can be parsed to state data 
	**/
    bool parseState(int state);
	/**
	 @brief Parses an option tag to identify the navigation data out of it
	 @param buffer A data buffer that has been received
	 @param offset the byte offset into the buffer of the option tag we are parsing 
	 **/
    void parseNavigation(MemoryLibrary::Buffer& buffer, int offset);
	/**
	 @brief Parses an option tag to identify the vision data contained in it
	 @param buffer A data buffer that has been received and needs parsing
	 @param offset the byte offset into the buffer of the option tag we are parsing 
	 **/
    bool parseVision(MemoryLibrary::Buffer& buffer, int offset);
  };
}//namespace ARDrone
#endif

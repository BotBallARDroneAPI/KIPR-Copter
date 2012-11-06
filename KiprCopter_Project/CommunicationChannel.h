/// CommunicationChannel.h
#ifndef COMMUNICATIONCHANNEL_H
#define COMMUNICATIONCHANNEL_H

#include "commonc++/DatagramSocket.h++"
#include "commonc++/Mutex.h++"

#include "ATCommand.h"

namespace ARDrone
{
    
  class CommunicationChannel
  {
    ccxx::DatagramSocket myDatagram;
    ccxx::Mutex myMutex;
    
  public:
	/**
	 @brief Constructor for a Communication Channel that sets the internal values to zero
	 **/
    CommunicationChannel();
	  
	/**
	@brief Communication Channel Destructor that is responsible for ensuring we disconnect from the drone
	**/
    ~CommunicationChannel();
	  
	/**
	@brief Function for connecting this CommChannel to the drone on the given IP and Port
	@param szDroneIPAddress A string representing the IPAddress of the Drone
	@param iPort An integer representing the port for this CommChannel
	**/
    void connectWithDroneAtAddress(const char* szDroneIpAddress, int iPort);
	
	/**
	@brief Disconnects the Communication Channel from the Drone
	**/	  
    void disconnectFromDrone();
	/**
	 @brief Determines if this Channel is connected to the drone
	 @return true to indicate it has been connected
	 **/
    bool isConnectedWithDrone();
    
	/**
	@brief Sets the timeout before this communication channel throws an exception
	@param The timeout in seconds before an exception is thrown
	**/
    void setTimeout(int t);
	  
    /**
	 @brief Sends a buffer on this communication channel
	 @param bytes A buffer of information to send
	 @param bufferLength the length of the buffer we are sending in bytes
	 **/
    void send(unsigned char* bytes, unsigned int length);
	  
	/**
	@brief Receives a buffer on this communication channel
	@param bytes A buffer of information that was received on this Channel
	@param bufferLength the length of the buffer we received in bytes
	**/
    void receive(unsigned char* bytes, unsigned int& bufferLength);
	  
	/**
	 @brief Sends an AT Command to the drone.
	 @param szHeader The Command part of the AT Command
	 @param szDetail The Arguments that are being passed to the command
	 @param mssleep The amount of time to sleep after this command has been sent.
			Default is 100.
	 **/
    void sendAT(const char* szHeader, const char* szDetail, unsigned int mssleep=100);
    
	/**
	 @brief Gets the sequence number of the next ATCommand
	 **/
    unsigned int nextATSequence();
	  
	/**
	@brief Gets the sequence number of the last ATCommand that was sent
	**/
    ARDrone::ATCommand lastATCommand();
  };
}//namespace ARDrone

#endif

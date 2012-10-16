/// CommunicationChannel.cpp
#include "CommunicationChannel.h"
#include <commonc++/Thread.h++>
#include <commonc++/ScopedLock.h++>

namespace ARDrone
{
	/**
	 @brief A Variable representing the next sequence number for an AT Command
	 TODO: Move this somewhere so it is more encapsulated
	 **/
	unsigned int myNextATSequence;
	/**
	 @brief A Variable representing the last sequence number for an AT Command
	TODO: Move this somewhere so it is more encapsulated
	 **/
	unsigned int myLastATSequence;
	/**
	 @brief An object representeing the last ATCommand that was sent so it may be sent continuously.
	TODO: Move this somewhere so it is more encapsulated
	 **/
	ATCommand myLastATCommand;
	CommunicationChannel::CommunicationChannel()
	{
		myNextATSequence = 1;
		myLastATSequence = 1;
		myDatagram.init();
	}

	CommunicationChannel::~CommunicationChannel()
	{
		disconnectFromDrone();
	}
	
	void CommunicationChannel::connectWithDroneAtAddress(const char* szDroneIpAddress, int iPort)
	{
		ccxx::String strAddr(szDroneIpAddress);
		myDatagram.connect(strAddr, iPort);
		myDatagram.setTimeout(3000);
	}
	
	void CommunicationChannel::disconnectFromDrone()
	{
		if(isConnectedWithDrone())
		{
			/*
			Jeremy Mod
			char buffer[255];
			sprintf(buffer, ",\"network:owner_mac\",\"%s\"", pairMAC);
			
			sendAT("AT*CONFIG=", buffer);
			 */
			//sendAT("AT*CONFIG=", ",\"network:owner_mac\",\"00:00:00:00:00:00\"");
			myDatagram.shutdown();
		}
	}
	
	bool CommunicationChannel::isConnectedWithDrone()
	{
		return myDatagram.isConnected();
	}
	
	void CommunicationChannel::setTimeout(int t)
	{
		myDatagram.setTimeout(t);
	}
	
	void CommunicationChannel::send(unsigned char* bytes, unsigned int length)
	{
		synchronized(myMutex)
		{
			myDatagram.send(bytes, length);
		}
	}
	
	void CommunicationChannel::receive(unsigned char* bytes, unsigned int& bufferLength)
	{  
		int actualReceivedLength = myDatagram.receive(bytes, bufferLength);
		bufferLength = actualReceivedLength;
	}
	
	void CommunicationChannel::sendAT(const char* szHeader, const char* szDetail, unsigned int mssleep)
	{
			std::stringstream strStm;
			strStm << szHeader << nextATSequence() << szDetail << '\r';
			std::string strATCmd = strStm.str();
			myLastATCommand.strCommandHeader = szHeader;
			myLastATCommand.strCommandData = szDetail;
			myDatagram.send((unsigned char*)strATCmd.c_str(), strATCmd.length());
			if(mssleep > 0)
				ccxx::Thread::sleep(mssleep);
	}
	
	unsigned int CommunicationChannel::nextATSequence()
	{
		synchronized(myMutex)
		{
			return myNextATSequence++;
		}
	}
	
	ARDrone::ATCommand CommunicationChannel::lastATCommand()
	{
		synchronized(myMutex)
		{
			return myLastATCommand;
		}
	}
}//namespace ARDrone

/// VideoDataReceiver.cpp
#ifndef VIDEODATARECEIVER_H
#define VIDEODATARECEIVER_H

#include "Controller.h"
#include "VideoDecoder.h"
#include "commonc++/Thread.h++"

#define BUFFERSIZE 921600   //640x480x3 MAX out

namespace ARDrone
{
	class VideoDataReceiver : public ccxx::Thread
	{
	private:
		ARDrone::CommunicationChannel myCommunicationChannel;
		ccxx::Mutex myMutex;
		std::string myDroneAddress;
		ARDrone::Controller* myController;
		unsigned char myVideoData[BUFFERSIZE];
		unsigned int videoDataLength;
		//Mod by Jeremy Rand
		VideoDecoder::Image videoBuffer[2];
		long videoTimestamp[2]; 
		int safeBufferIndex;
		bool enableCbcuiVision;
		//End Mod
		
	public:

		VideoDataReceiver(ARDrone::Controller* pController, const char* szDroneIpAddress);
		~VideoDataReceiver() throw ();
		void copyDataTo(ARDrone::VideoDecoder::Image& resultImage);
		//Jeremy Rand Mod
		void setEnableCbcuiVision(bool enable);
		void copyDataTo(ARDrone::VideoDecoder::Image& resultImage, long& timestamp);
		//End Mod
	protected:
		void run();
	};
}//namespace ARDrone

#endif

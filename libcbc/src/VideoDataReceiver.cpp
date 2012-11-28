/// VideoDataReceiver.cpp
#include "VideoDataReceiver.h"
#include "DroneConstants.h"
#include <commonc++/ScopedLock.h++>
#include "compat.h"
#include <fcntl.h>

#define EXTERNAL_CAMERA_BUFFER "/tmp/external_camera_buffer"
#define EXTERNAL_CAMERA_READY "/tmp/external_camera_ready"

namespace ARDrone
{
	VideoDataReceiver::VideoDataReceiver(ARDrone::Controller* pController, const char* szDroneIpAddress)
	{
		myDroneAddress = szDroneIpAddress;
		myController = pController;
		safeBufferIndex = 1;
		videoBuffer[0].height = videoBuffer[0].width = videoBuffer[1].height = videoBuffer[1].width = 0;
		videoTimestamp[0] = videoTimestamp[1] = 0;
		enableCbcuiVision = false;
	}
	
	VideoDataReceiver::~VideoDataReceiver() throw ()
	{
		if(true == isRunning())
		{
			try
			{
				stop();
				join();
				myCommunicationChannel.disconnectFromDrone();
			}
			catch (ccxx::Exception& ex) 
			{
				std::cout << ex.what() << std::endl;
			}
		}
	}
	
	void VideoDataReceiver::run()
	{
		std::cout << "VideoDataReceiver started\n";
		try 
		{
			myCommunicationChannel.connectWithDroneAtAddress(myDroneAddress.c_str(), VIDEO_DATA_PORT);
			myCommunicationChannel.setTimeout(3000);
			myController->disableAdaptiveVideo();
			unsigned char trigger[4] = {0x01, 0x00, 0x00, 0x00};
			myCommunicationChannel.send(trigger, 4);
			
			myController->requestVideoData();
			while(false == testCancel())
			{
				try 
				{
					
					synchronized(myMutex)
					{
						videoDataLength = 921600;
						myCommunicationChannel.receive(myVideoData, videoDataLength);

						// Mod by Jeremy
						ARDrone::VideoDecoder::decodeImage(myVideoData, videoDataLength, videoBuffer[safeBufferIndex^1]);
						videoTimestamp[safeBufferIndex^1] = (long)(seconds() * 1000);
						safeBufferIndex ^= 1;
						
						if(enableCbcuiVision)
						{
							//CBC Function Call
							write_external_camera_data();
						}
						else
						{
							//CBC Function Call
							delete_external_camera_data();
						}

						msleep(20);
					}
				}
				catch (ccxx::TimeoutException& timeoutEx) 
				{
					std::cout << "VideoDataReceiver TIMEOUT exception thrown.." << timeoutEx.what() << std::endl;
				}
				catch (ccxx::Exception& ex) 
				{
					std::cout << "VideoDataReceiver exception thrown.." << ex.what() << std::endl;
				}
			}//while
		}
		catch (ccxx::Exception& ex) 
		{
			std::cout << "VideoDataReceiver exception thrown.." << ex.what() << std::endl;
		}
		
		std::cout << "VideoDataReceiver stopped\n";
	}
	
	void VideoDataReceiver::copyDataTo(ARDrone::VideoDecoder::Image& resultImage)
	{
		synchronized(myMutex)
		{
			ARDrone::VideoDecoder::decodeImage(myVideoData, videoDataLength, resultImage);
		}
	}
	
	void VideoDataReceiver::write_external_camera_data()
	{
		// If Ready Flag is not present, or if buffer is not present
		if( ! (access(EXTERNAL_CAMERA_READY, F_OK) != -1) || ! (access(EXTERNAL_CAMERA_BUFFER, F_OK) != -1) )
		{
			VideoDecoder::Image * videoData = new VideoDecoder::Image();
			long timestamp;
			
			int srcw, srch, destw, desth;
			int x, y, srcx, srcy;
			int src_index;
			
			int buffer_file;
			int ready_file;
			
			copyDataTo(*videoData, timestamp);
			
			srcw = videoData->width;
			srch = videoData->height;
			
			destw = 160;
			desth = 120;
			
			buffer_file = open(EXTERNAL_CAMERA_BUFFER, O_WRONLY | O_CREAT | O_TRUNC, 0666);
			
			for(y=0; y<desth; y++)
			{
				srcy = y * srch / desth;
				
				for(x=0; x<destw; x++)
				{
					srcx = x * srcw / destw;
					src_index = ((srcy*srcw)+srcx)*3;
					
					write(buffer_file, videoData->data + src_index+2, 1); // B
					write(buffer_file, videoData->data + src_index+1, 1); // G
					write(buffer_file, videoData->data + src_index+0, 1); // R
				}
			}
			
			close(buffer_file);
			
			delete videoData;
			
			ready_file = open(EXTERNAL_CAMERA_READY, O_WRONLY | O_CREAT, 0666);
			close(ready_file);
			
		}
	}
	void VideoDataReceiver::delete_external_camera_data()
	{
		remove(EXTERNAL_CAMERA_BUFFER);
		remove(EXTERNAL_CAMERA_READY);
	}
	
	void VideoDataReceiver::copyDataTo(ARDrone::VideoDecoder::Image& resultImage, long& timestamp)
	{		
		if(safeBufferIndex == 0 || safeBufferIndex == 1)
		{
			resultImage = videoBuffer[safeBufferIndex];
			timestamp = videoTimestamp[safeBufferIndex];
		}
	}
 
	void VideoDataReceiver::setEnableCbcuiVision(bool enable)
	{
		enableCbcuiVision = enable;
	}
//End Mod
}//namespace ARDrone

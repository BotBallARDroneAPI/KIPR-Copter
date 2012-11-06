/// NavigationDataReceiver.cpp
#include "NavigationDataReceiver.h"
#include "DroneConstants.h"
#include <commonc++/ScopedLock.h++>
#include "compat.h"

namespace ARDrone
{
	NavigationDataReceiver::NavigationDataReceiver(Controller* pController, const char* szDroneIpAddress)
	{
		myDroneAddress = szDroneIpAddress;
		myController = pController;
		
		navTimestamp = 0;
	}
	
	NavigationDataReceiver::~NavigationDataReceiver() throw ()
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
	void NavigationDataReceiver::copyDataTo(ARDrone::NavigationData& data)
	{
		synchronized(myMutex)
		{
			data = myNavData;
		}
	}
	
	void NavigationDataReceiver::run()
	{
		std::cout << "NavigationDataReceiver started\n";
		int cnt = 0;
		try 
		{
			myCommunicationChannel.connectWithDroneAtAddress(myDroneAddress.c_str(), NAVIGATION_DATA_PORT);
			myCommunicationChannel.setTimeout(3000);
			
			unsigned char trigger[4] = {0x01, 0x00, 0x00, 0x00};
			myCommunicationChannel.send(trigger, 4);
						
			unsigned char navDataDemo[10240];
			unsigned int navDataLength = 10240;
			while(false == testCancel())
			{
				try 
				{
					myController->requestNavigationData(DEMO);
					myCommunicationChannel.receive(navDataDemo, navDataLength);
					cnt++;
					if(cnt >= 5)
					{
						cnt = 0;
						synchronized(myMutex)
						{
							MemoryLibrary::Buffer navDataBuffer(navDataDemo, navDataLength);
							parse(navDataBuffer);
							
							//Jeremy Rand Mod
							navTimestamp = (long)(seconds() * 1000.0);
							
						}
					}
				}
				catch (ccxx::TimeoutException& timeoutEx) 
				{
					std::cout << "NavigationDataReceiver TIMEOUT exception thrown.." << timeoutEx.what() << std::endl;
				}
				catch (ccxx::Exception& ex) 
				{
					std::cout << "NavigationDataReceiver exception thrown.." << ex.what() << std::endl;
				}
			}//while
		}
		catch (ccxx::Exception& ex) 
		{
			std::cout << "NavigationDataReceiver exception thrown.." << ex.what() << std::endl;
		}
		
		std::cout << "NavigationDataReceiver stopped\n";
	}

	bool NavigationDataReceiver::parse(MemoryLibrary::Buffer& buffer)
	{
		int offset = 0;
		int header = buffer.MakeValueFromOffset<int32_t>(offset);
		if(header != 0x55667788)
		{
			std::cout << "NavigationDataReceiver FAIL, because the header != 0x55667788\n";
			return false;
		}
		
		offset += 4;
		int state = buffer.MakeValueFromOffset<int32_t>(offset);
		parseState(state);
		
		offset += 4;
		myNavData.sequence = buffer.MakeValueFromOffset<int32_t>(offset);
		
		offset += 4;
		// int vision_tag;
		
		offset += 4;
		while(offset < buffer.Size())
		{
			int option_tag = (int)buffer.MakeValueFromOffset<unsigned short>(offset);
			offset += 2;
			int option_len = (int)buffer.MakeValueFromOffset<unsigned short>(offset);
			offset += 2;
			
			if(option_len == 0)
			{
				std::cout << "NavigationDataReceiver FAIL, option_len == 0\n";
				return false;
			}
			
			switch(option_tag)
			{
				case NAVDATA_DEMO_TAG: parseNavigation(buffer, offset); break;
				case NAVDATA_CKS_TAG:  break;
				case NAVDATA_VISION_DETECT_TAG: parseVision(buffer, offset); break;
			}
			
			offset = offset + option_len - 4;
		} //while
		
		return true;
	}
	
	bool NavigationDataReceiver::parseState(int state)
	{
		myNavData.flags.flying = (state & 1) != 0;
		myNavData.flags.videoEnabled = (state & (1 << 1)) != 0;
		myNavData.flags.visionEnabled = (state & (1 << 2)) != 0;
		myNavData.controlAlgorithm = (state & (1 << 3)) != 0 ? ARDrone::eAugularSpeedControl : ARDrone::eEulerAnglesControl;
		myNavData.flags.altitudeControlActive = (state & (1 << 4)) != 0;
		myNavData.flags.userFeedbackOn = (state & (1 << 5)) != 0;
		myNavData.flags.controlReceived = (state & (1 << 6)) != 0;
		myNavData.flags.trimReceived = (state & (1 << 7)) != 0;
		myNavData.flags.trimRunning = (state & (1 << 8)) != 0;
		myNavData.flags.trimSucceeded = (state & (1 << 9)) != 0;
		myNavData.flags.navDataDemoOnly = (state & (1 << 10)) != 0;
		myNavData.flags.navDataBootstrap = (state & (1 << 11)) != 0;
		myNavData.flags.motorsDown = (state & (1 << 12)) != 0;
		myNavData.flags.gyrometersDown = (state & (1 << 14)) != 0;
		myNavData.flags.batteryTooLow = (state & (1 << 15)) != 0;
		myNavData.flags.batteryTooHigh = (state & (1 << 16)) != 0;
		myNavData.flags.timerElapsed = (state & (1 << 17)) != 0;
		myNavData.flags.notEnoughPower = (state & (1 << 18)) != 0;
		myNavData.flags.angelsOutOufRange = (state & (1 << 19)) != 0;
		myNavData.flags.tooMuchWind = (state & (1 << 20)) != 0;
		myNavData.flags.ultrasonicSensorDeaf = (state & (1 << 21)) != 0;
		myNavData.flags.cutoutSystemDetected = (state & (1 << 22)) != 0;
		myNavData.flags.PICVersionNumberOK = (state & (1 << 23)) != 0;
		myNavData.flags.ATCodedThreadOn = (state & (1 << 24)) != 0;
		myNavData.flags.navDataThreadOn = (state & (1 << 25)) != 0;
		myNavData.flags.videoThreadOn = (state & (1 << 26)) != 0;
		myNavData.flags.acquisitionThreadOn = (state & (1 << 27)) != 0;
		myNavData.flags.controlWatchdogDelayed = (state & (1 << 28)) != 0;
		myNavData.flags.ADCWatchdogDelayed = (state & (1 << 29)) != 0;
		myNavData.flags.communicationProblemOccurred = (state & (1 << 30)) != 0;
		myNavData.flags.emergency = (state & (1 << 31)) != 0;
		return true;
	}
	
	void NavigationDataReceiver::parseNavigation(MemoryLibrary::Buffer& buffer, int offset)
	{
		int temp = buffer.MakeValueFromOffset<int32_t>(offset);
		myNavData.controlState = (ARDrone::eControlState)(temp >> 16);
		offset += 4;
		myNavData.batteryLevel = buffer.MakeValueFromOffset<int32_t>(offset);
		offset += 4;
		myNavData.orientation.pitch = buffer.MakeValueFromOffset<float32_t>(offset) / 1000.0f;
		offset += 4;
		myNavData.orientation.roll = buffer.MakeValueFromOffset<float32_t>(offset) / 1000.0f;
		offset += 4;
		myNavData.orientation.yaw = buffer.MakeValueFromOffset<float32_t>(offset) / 1000.0f;
		offset += 4;
		myNavData.altitude = (float)buffer.MakeValueFromOffset<int32_t>(offset) / 1000.0f;
		offset += 4;
		myNavData.speed.vx = buffer.MakeValueFromOffset<float32_t>(offset);
		offset += 4;
		myNavData.speed.vy = buffer.MakeValueFromOffset<float32_t>(offset);
		offset += 4;
		myNavData.speed.vz = buffer.MakeValueFromOffset<float32_t>(offset);
		offset += 4;
	}
	
	bool NavigationDataReceiver::parseVision(MemoryLibrary::Buffer& buffer, int offset)
	{
		int nbDetected = buffer.MakeValueFromOffset<int32_t>(offset);
		offset += 4;
		
		if(0 == nbDetected) // not detecting anything
			return true;
		myNavData.visionTagVector.resize(0);
		for(int i = 0; i < nbDetected; i++)
		{
			ARDrone::VisionTag visionTag;
			
			visionTag.type = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i);
			visionTag.x = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i + 1 * nbDetected * 4);
			visionTag.y = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i + 2 * nbDetected * 4);
			visionTag.width = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i + 3 * nbDetected * 4);
			visionTag.height = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i + 4 * nbDetected * 4);
			visionTag.distance = buffer.MakeValueFromOffset<int32_t>(offset + 4 * i + 5 * nbDetected * 4);
			
			myNavData.visionTagVector.push_back(visionTag);
		}
		return true;
	}
}//namespace ARDrone

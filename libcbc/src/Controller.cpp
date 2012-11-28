///Controller.cpp
#include "Controller.h"
#include "Drone.h"
#include "DroneConstants.h"

namespace ARDrone
{
	inline int floatToIntegerByteByByte(float f)
	{
		int result;
		::memcpy(&result, &f, sizeof(int));
		return result;
	}
	
	Controller::Controller()
	{
	}
	
	Controller::~Controller()
	{
	}
	void Controller::connectWithDroneAtAddress(const char* szDroneIpAddress)
	{
		
		if(myCommunicationChannel.isConnectedWithDrone())
			return;
		myCommunicationChannel.connectWithDroneAtAddress(szDroneIpAddress, ATCOMMAND_PORT);
		sendEmergencyToggle();
		sendWatchDog();
		setMaxAltitude(DEFAULT_MAX_ALTITUDE);
		setMaxEulerAngle(DEFAULT_MAX_EULER_ANGLE);
		setMaxVerticalSpeed(DEFAULT_MAX_VERTICAL_SPEED);
		setMaxYawSpeed(DEFAULT_MAX_YAW_SPEED);
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), SHELL_INSIDE_MODE_ARG.c_str()); // inform control loop that indoor shell is in use

		setControlLevel(BEGINNER);
		requestNavigationData(DEMO);
		requestVideoData();

		setBitrate(DEFAULT_VIDEO_BITRATE); //scale the video bit_rate down from default
		disableAdaptiveVideo();
		setUltrasoundFrequency(CHANNEL_22_5MHZ);
		sendFlatTrim();
		//printf("Completed Drone Connection\n");
	}
	void Controller::takeOff()
	{
		myCommunicationChannel.sendAT(ATSTATE_COMMAND.c_str(), TAKEOFF_ARG.c_str());
	}
	void Controller::land()
	{
		myCommunicationChannel.sendAT(ATSTATE_COMMAND.c_str(), LAND_ARG.c_str());
	}	
	void Controller::hover()
	{
		sendControlParameters(0, 0, 0, 0, 0);
	}
	void Controller::setFlyingMode(FlyMode mode)
	{
		switch(mode)
		{
			case (NORMAL):
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), FLYING_MODE_NORMAL_ARG.c_str());
				break;
			case (HOVER_ON_ROUNDEL): //ARDrone doc has this enum = 1 << 0....
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), FLYING_MODE_HOVER_ON_ROUNDEL_ARG.c_str());
				break;
			//TODO If these both work remove the one above
			case (HOVER_ON_ORIENTED_ROUNDEL): //ARDrone doc has this enum = 1 << 1....
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), FLYING_MODE_HOVER_ON_ORIENTED_ROUNDEL_ARG.c_str());
				break;
		}
	}
	void Controller::requestNavigationData(NavDataSize size)
	{
		if (size == DEMO)
		{
			myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), MINIMAL_NAV_DATA_ARG.c_str(), 20);
		}
		else if (size == FULL)
		{
			myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ALL_NAV_DATA_ARG.c_str(), 20);
		}
	}
	void Controller::requestNavigationVisionTagData()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), REQUEST_VISION_TAG_DATA_ARG.c_str(), 20);
	}
	void Controller::requestVideoData()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), VIDEO_ENABLE_ARG.c_str(), 10);
	}
	void Controller::disableAdaptiveVideo()
	{		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), VIDEO_CONTROL_MODE_DISABLE_ARG.c_str());		 
	}
	void Controller::switchToFrontCamera()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), FRONT_CAMERA.c_str());	
	}
	void Controller::switchToDownCamera()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), DOWN_CAMERA.c_str());
	}
	void Controller::sendControlParameters(int enable, float pitch, float roll, float yaw, float gaz)
	{
		std::stringstream strStm;
		strStm << "," << enable << ','
		<< floatToIntegerByteByByte(roll) << ','
		<< floatToIntegerByteByByte(pitch) << ','
		<< floatToIntegerByteByByte(gaz) << ','
		<< floatToIntegerByteByByte(yaw);
		
		myCommunicationChannel.sendAT(ATMOVE_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::sendAnimationControl(AnimationCmd myAnim)
	{
		std::stringstream strStm;
		strStm << ANIMATION_CONTROL_ARG.c_str() << "\"" << myAnim << ",\"" << 50 << "\""; 
		myCommunicationChannel.sandAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::sendWatchDog()
	{
		myCommunicationChannel.sendAT(ATWATCHDOG_COMMAND.c_str(), "");
	}
	void Controller::sendFlatTrim()
	{
		myCommunicationChannel.sendAT(ATFLAT_TRIM_COMMAND.c_str(), "");
	}
	void Controller::sendEmergencyToggle()
	{
		myCommunicationChannel.sendAT(ATSTATE_COMMAND.c_str(), EMERGENCY_ARG.c_str()); //toggle Emergency
	}
	void Controller::sendLastCommand()
	{
		ARDrone::ATCommand cmd = myCommunicationChannel.lastATCommand();
		myCommunicationChannel.sendAT(cmd.strCommandHeader.c_str(), cmd.strCommandData.c_str());
	}
	void Controller::setMaxAltitude(int altitudeInMillimeters)
	{
		std::stringstream strStm;
		strStm << MAX_ALTITUDE_ARG << altitudeInMillimeters << "\"";
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::setUltrasoundFrequency(UltrasoundChannel channel)
	{
		if(channel == CHANNEL_22_5MHZ)
			myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ULTRASOUND_CHANNEL_A_ARG.c_str());
		else
			myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ULTRASOUND_CHANNEL_B_ARG.c_str());
	}
	void Controller::setBitrate(int bitrate)
	{
		std::stringstream strStm;
		strStm << VIDEO_BITRATE << bitrate << "\"";

		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::setMaxEulerAngle(float max)
	{
		std::stringstream strStm;
		strStm << MAX_EULER_ANGLE << max << "\"";
		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}	
	void Controller::setMaxVerticalSpeed(int max)
	{
		std::stringstream strStm;
		strStm << MAX_VERTICAL_SPEED << max << "\"";
		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::setMaxYawSpeed(float max)
	{
		std::stringstream strStm;
		strStm << MAX_YAW_SPEED << max << "\"";
		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::setMacAddress(std::string macAddress)
	{		
		std::stringstream strStm;
		strStm << MAC_ADDRESS << macAddress << "\"";
		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::setControlLevel(ControlLevel controlLevel)
	{
		std::stringstream strStm;
		strStm<< CONTROL_LEVEL << controlLevel << "\"";
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), strStm.str().c_str());
	}
	void Controller::detectColor(DetectedTag detect_color)
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), DETECT_TYPE_ENEMIES_FRONT_CAMERA_ARG.c_str()); //13 equates to CAD_TYPE_VISION_V2 from ardrone_api.h
		
		switch (detect_color)
		{
			case GREEN:
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ENEMY_COLOR_GREEN_ARG.c_str());
				break;
			case YELLOW:
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ENEMY_COLOR_YELLOW_ARG.c_str());
				break;
			case BLUE:
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), ENEMY_COLOR_BLUE_ARG.c_str());
				break;
		}
	}
	void Controller::detectGroundStripe(DetectedTag detect_color)
	{
		
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), DETECT_TYPE_STRIPE_ARG.c_str()); //6 equates to CAD_TYPE_STRIPE from ardrone_api.h
		switch (detect_color)
		{
			case ORANGE_GREEN:
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), GROUND_STRIPE_ORANGE_GREEN_ARG.c_str());
				break;
			case YELLOW_BLUE:
				myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), GROUND_STRIPE_YELLOW_BLUE_ARG.c_str());
				break;
		}
	}
	void Controller::detectRoundel_BW()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), DETECT_TYPE_ROUNDEL_ARG.c_str()); //12 equates to CAD_TYPE_ORIENTED_COCARDE_BW from ardrone_api.h
	}	
	void Controller::disableDroneTagging()
	{
		myCommunicationChannel.sendAT(ATCONFIG_COMMAND.c_str(), DETECT_TYPE_NONE_ARG.c_str()); //3 equates to CAD_TYPE_NONE from ardrone_api.h
	}			
}//namespace ARDrone

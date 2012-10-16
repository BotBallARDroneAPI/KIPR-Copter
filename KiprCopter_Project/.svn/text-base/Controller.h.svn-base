///Controller.h
#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "CommunicationChannel.h"
#include "NavigationData.h"
#include "DroneConstants.h"

namespace ARDrone
{  
	//TODO these should probably be better integrated into stuff.. I dont think they apply to a controller..
	
	/** 
	 @brief An Enum to provide a textual parameter to feed into the setUltrasoundFrequency Command
	 **/
	enum UltrasoundChannel 
	{
		CHANNEL_22_5MHZ = 1,
		CHANNEL_22MHZ = 2
	};
	
	/** 
	 @brief An Enum to provide a textual parameter to feed into the detectColor Command
	 **/
	enum EnemyColor
	{
		GREEN = 1,
		YELLOW = 2,
		BLUE = 3
	};
	
	/**
	 @brief An Enum to provide a textual parameter to feed into the ControlLevel Command
	 **/
	enum ControlLevel
	{
		BEGINNER = 1,
		ACE = 2,
		MAX = 3
	};
	
	/** 
	 @brief An Enum to provide a textual parameter to feed into the detectGroundStripe Command
	 **/
	enum GroundStripeColor
	{
		ORANGE_GREEN = 1,
		YELLOW_BLUE = 2
	};
	
	/** 
	 @brief An Enum to provide a textual parameter to feed into the requestNavigationData Command
	 **/
	enum FlyMode
	{
		NORMAL = 0,
		HOVER_ON_ROUNDEL = 1,
		HOVER_ON_ORIENTED_ROUNDEL = 2
	};

	/** 
	 @brief An Enum to provide a textual parameter to feed into the NavDataSend Command
	 **/
	enum NavDataSize
	{
		DEMO = 0,
		FULL = 1
	};
	
	class Controller
		{
			ARDrone::CommunicationChannel myCommunicationChannel;
		public:
			/**
			@brief Default constructor for a Controller Object
			**/
			Controller();
			/**
			@brief Controller destructor
			**/
			~Controller();
			/**
			@brief Function responsible for establishing a connection to the AR Drone
					This function also takes care of establishing the default values for the drone.
			@param szDroneIpAddress A string representing the IP address of the drone we are connecting to
			**/
			void connectWithDroneAtAddress(const char* szDroneIpAddress);
			
			/**
			@brief Sends the drone the takeoff AT Command telling it to takeoff from its current position
			**/
			void takeOff();
			/**
			@brief Sends the drone the land AT Command telling it to safely land in it's current position
			**/
			void land();
			/**
			@brief Sends the drone a movement command with all zeros telling it to stay in place
			**/
			void hover();
			
			/**
			@brief Sends the drone an AT command corresponding with the given parameter.  The two interesting commands
					make the drone hover over a black and white roundel (Circle with a Line) and then 
			@param mode An enum that defines the different flying modes
					NORMAL - Normal Flying controls
					HOVER_ON_ROUNDEL - Deprecated command that will make the drone hover over a roundel
					HOVER_ON_ORIENTED_ROUNDEL - Command that tells the drone to hover on a roundel and 
												face the direction it is facing
			@pre Oriented Roundel detection must be activated 
			@pre A Roundel must already be detected in the navigation data
			**/
			void setFlyingMode(FlyMode mode);
			
			/**
			@brief Tells the drone to send navigation data on port 5554.  NavData contains drone information like 
					(roll, pitch, yaw, battery life, etc)
			@param size Specifies a size for the requested NavData
					FULL - Request all NavData possible (Includes debugging information that is normally not useful)
					DEMO - Requests minimal NavData but is the recommended amount specified in the Parrot SDK
			**/
			void requestNavigationData(NavDataSize size);

			/**
			@brief Sends an AT Command to the drone requesting it to include any 
					detected vision tag data in the NavData
			**/
			void requestNavigationVisionTagData();
			
			/**
			@brief Sends an AT Command to the drone requesting it transmits video data
			**/
			void requestVideoData();
			
			/**
			@brief TODO Figure out what this does
			**/
			void disableAdaptiveVideo();
			
			/**
			@brief Tells the drone to send imgaes from the front facing camera
			**/
			void switchToFrontCamera();
			
			/**
			@brief Tells the drone to send imgaes from the downward facing camera
			**/
			void switchToDownCamera();
			
			/**
			@brief Sends the given parameters as a movement command to the Drone
			@param enable A value indicating if movement is enabled. 0 - True 1 - False
			@param pitch A value from zero to one indicating the percentage of maximum tilt in the left or right direction
				negative values are left and positive values are right. Ex: -.5 means Half of the total tilt left
			@param roll A value from zero to one indicating the percentage of maximum tilt in the forward or backward direction
				negative values are left and positive values are right. Ex: -.5 means Half of the total tilt backwards.
			@param yaw A value indicating the rotational velocity of the dronein milieters per second
			@param gaz A value indicating the change in altitude in milimeters per second
			**/
			void sendControlParameters(int enable, float pitch, float roll, float yaw, float gaz);
			
			/**
			@brief Sends a "Watchdog" (AT Command to ensure constant communication) command to the drone 
			**/
			void sendWatchDog();

			/**
			@brief Sends a Trim command to the drone which indicates the Drone is on a flat stable
					surface to set a basis for the drone's sensors
			**/
			void sendFlatTrim();
			/**
			@brief Sends the Emergency Toggle command to change the state of the Drones internal flag
			**/
			void sendEmergencyToggle();
			
			/**
			@brief This acts as a cacheing mechanism to ensure the drone is always receiving a command.
					This essentially resends the previous command.
			**/
			void sendLastCommand();
			
			/**
			@brief Sends an AT Command to the drone to set the maximum altitude
			@param altitudeInMillimeters The highest altitude in millimeters
			**/
			void setMaxAltitude(int altitudeInMillimeters);

			/**
			@brief Sets the drone's Ultrasound frequency
			@param channel A value indicating the channel we would like our ultrasound sensor to use.
					CHANNEL_22_5MHZ - Uses the 22.5 MHZ Frequency
					CHANNEL_22MHZ = - Uses the 25 MHZ Frequency
			**/
			void setUltrasoundFrequency(UltrasoundChannel channel);
			
			/**
			@brief Sets the drone's bitrate to the given value
			@param bitrate The number of bits per second the drone can transmit
			**/
			void setBitrate(int bitrate);
			
			/**
			@brief Sets the drone's Maximum Euler Angle to the given value
			@param A parameter between 0 and 1 that indicates the percentage
			**/
			void setMaxEulerAngle(float max);

			/**
			@brief Sets the drone's maximum vertical speed
			@param max speed in milimeters per second
			**/
			void setMaxVerticalSpeed(int max);

			/**
			@brief Sets the drones maximum rotational speed
			@param max Rotational speed in meters per second
			**/
			void setMaxYawSpeed(float max);

			/**
			@brief Sets the Source MAC Address on the drone to prevent extra connections
			@param macAddress Your CBC's MAC Address
			**/
			void setMacAddress(std::string macAddress);
			
			/**
			 @brief Sets the Drone's Control Level
			 @param controlLevel The Drone's level of control
					BEGINNER	- Limited Control
					ACE			- More Control
					MAX			- All Control
			 **/
			void setControlLevel(ControlLevel controlLevel);

			/**
			@brief Detects "Enemy" colors on the forward facing camera
			@param detect_color The color that we would like to find
			**/
			void detectColor(EnemyColor detect_color);

			/**
			@brief Detects Ground Stripe tags on the ground facing camera
			@param detect_color The color that we would like to find
			**/
			void detectGroundStripe(GroundStripeColor detect_color);
			/**
			@brief Detects Roundels on the ground facing camera
			**/
			void detectRoundel_BW();

			/** 
			@brief Disables all drone tagging systems
			**/
			void disableDroneTagging();
		};
}//namespace ARDrone
#endif

/// NavigationData.h 
#ifndef NAVIGATIONDATA_H
#define NAVIGATIONDATA_H

#include <vector>
#include <sstream>

#define NAVDATA_DEMO_TAG (0)
#define NAVDATA_TIME_TAG (1)
#define NAVDATA_RAW_MEASURES_TAG (2)
#define NAVDATA_PHYS_MEASURES_TAG (3) 
#define NAVDATA_GYROS_OFFSETS_TAG (4)
#define NAVDATA_EULER_ANGLES_TAG (5)
#define NAVDATA_REFERENCES_TAG (6)
#define NAVDATA_TRIMS_TAG (7)
#define NAVDATA_RC_REFERENCES_TAG (8)
#define NAVDATA_PWM_TAG (9)
#define NAVDATA_ALTITUDE_TAG (10)
#define NAVDATA_VISION_RAW_TAG (11)
#define NAVDATA_VISION_OF_TAG (12)
#define NAVDATA_VISION_TAG (13)
#define NAVDATA_VISION_PERF_TAG (14)
#define NAVDATA_TRACKERS_SEND_TAG (15)
#define NAVDATA_VISION_DETECT_TAG (16)
#define NAVDATA_WATCHDOG_TAG (17)
#define NAVDATA_ADC_DATA_FRAME_TAG (18)
#define NAVDATA_VIDEO_STREAM_TAG (19)
#define NAVDATA_CKS_TAG (0xFFFF)

namespace ARDrone
{
	/** 
	 @brief An Enum to provide a textual parameter to feed into the setUltrasoundFrequency Command
	 **/
	enum eControlState
	{
		eDEFAULT = 0, 
		eINIT = 1, 
		eLANDED = 2,
		eFLYING = 3, 
		eHOVERING= 4, 
		eTEST = 5, 
		eTAKEOFF = 6, 
		eGOTOFIX = 7, 
		eLANDING = 8
	};
	
	enum eControlAlgorithm
	{
		eEulerAnglesControl=0, eAugularSpeedControl=1
	};
	
	struct Orientation
	{
		float pitch;
		float roll;
		float yaw;
		
		std::string orientationAsString()
		{
			std::ostringstream oss;
			oss <<  "->" << pitch << " , " << roll << " , " << yaw;
			return oss.str();
		}
	};
	
	struct Speed
	{
		float vx;
		float vy;
		float vz;
	};
	
	struct VisionTag
	{
		int type;
		int x;
		int y;
		int width;
		int height;
		int distance;
	};
	
	struct State_Flags
	{
		bool flying;
		bool videoEnabled;
		bool visionEnabled;
		bool altitudeControlActive;
		bool userFeedbackOn;           
		bool controlReceived;
		bool trimReceived;
		bool trimRunning;
		bool trimSucceeded;
		bool navDataDemoOnly;
		bool navDataBootstrap;
		bool motorsDown;
		bool gyrometersDown;
		bool batteryTooLow;
		bool batteryTooHigh;
		bool timerElapsed;
		bool notEnoughPower;
		bool angelsOutOufRange;
		bool tooMuchWind;
		bool ultrasonicSensorDeaf;
		bool cutoutSystemDetected;
		bool PICVersionNumberOK;
		bool ATCodedThreadOn;
		bool navDataThreadOn;
		bool videoThreadOn;
		bool acquisitionThreadOn;
		bool controlWatchdogDelayed;
		bool ADCWatchdogDelayed;
		bool communicationProblemOccurred;
		bool emergency;
	};
  class NavigationData
  {
  public: 
	  const char* controlStateToString(eControlState cs);
	  const char* controlStateAsString();
	  const char* visionTagAsString();
	  Orientation GetOrientation();
	  //TODO Make private for encapsulation
	  int sequence;
	  State_Flags flags;
	  
	  unsigned int batteryLevel;
	  float altitude;
	  Orientation orientation;
	  Speed speed;
	  eControlState controlState;
	  eControlAlgorithm controlAlgorithm;
	  std::vector<VisionTag> visionTagVector;

  };
	
}//namespace ARDrone
#endif

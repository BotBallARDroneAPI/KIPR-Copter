/// NavigationData.cpp

#include "NavigationData.h"

namespace ARDrone
{ 
	const char* NavigationData::controlStateToString(eControlState cs)
	{
		switch(cs)
		{
			case  eDEFAULT: return "DEFAULT";
			case  eINIT: return "INIT";
			case  eLANDED: return "LANDED";
			case  eFLYING: return "FLYING";
			case  eHOVERING: return "HOVERING";
			case  eTEST: return "TEST";
			case  eTAKEOFF: return "TAKEOFF";
			case  eGOTOFIX: return "GOTOFIX";
			case  eLANDING: return "LANDING";
		}
		
		return "DONT KNOW";
	}
	const char* NavigationData::controlStateAsString()
	{
		return controlStateToString(controlState);
	}
	
	//TO DO
	//Implement this function
	const char* NavigationData::visionTagAsString()
	{
		return NULL;
	}
}//namespace ARDrone

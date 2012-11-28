// ARDroneAPI.cpp

#include "ARDroneAPI.h"
#include "Controller.h"
#include "compat.h"
#include "process.h"
#include "Drone.h"

#include <math.h>
#include <fcntl.h>

using namespace ARDrone;
using namespace std;


#define	LOCKED 1
#define UNLOCKED 0

enum movement_types{
	MOVEMENT = 0,
	ANIMATION = 1
};

Drone * myDrone;
bool drone_connected = false;

bool watchdog_enable = false;
int watchdog_pid;

int move_type = MOVEMENT;
int anim_type = 0;
int locker = UNLOCKED;

int cached_battery = 0;
float x,y,z,yaw;
float vx, vy, vz;
float last_nav_receive;
float last_nav_calc;
int sensors_pid;

int requested_enable_move = 0;
float requested_x_tilt = 0.0;
float requested_y_tilt = 0.0;
float requested_yaw_vel = 0.0;
float requested_z_vel = 0.0;
int control_pid;

std::vector<VisionTag> visionTagVector;

void monitor_sensors(); //Process
void init_position_tracking();
void update_position_tracking();
void move_control_thread(); //Process

void send_control_parameters(int enable, float x_tilt, float y_tilt, float yaw_vel, float z_vel);

void set_drone_Mac_Address(char * macAddress)
{
	if (drone_connected)
	{
		myDrone->controller().setMacAddress(macAddress);
	}
}

void monitor_sensors()
{
	while(true)
	{
		drone_get_battery();
		update_position_tracking();
		msleep(15);
	}
}

void drone_connect()
{
	if(!drone_connected)
	{
		myDrone = new Drone();
		myDrone->start();
		
		watchdog_enable = true;
		
		cached_battery = 0;
		init_position_tracking();
		
		sensors_pid = start_process(monitor_sensors);
		
		control_pid = start_process(move_control_thread);
		
		drone_connected = true;
	}
}

void drone_disconnect()
{
	if(drone_connected)
	{
		kill_process(control_pid);
		kill_process(sensors_pid);
		
		watchdog_enable = false;
		
		myDrone->stop();
		delete myDrone;
		
		drone_connected = false;
	}
}

void drone_takeoff()
{
	if(drone_connected)
	{
		myDrone->controller().takeOff();
	}
}

void drone_land()
{
	if(drone_connected)
	{
		myDrone->controller().land();
	}
}

void drone_emergency()
{
	if(drone_connected)
	{
		myDrone->controller().sendEmergencyToggle();
	}
}

// The Drone doesn't always report a valid battery level (it instead reports 0), so we cache it.
int drone_get_battery()
{
	if(drone_connected)
	{
		NavigationData batteryNavData;
		myDrone->navigationDataReceiver().copyDataTo(batteryNavData);
		
		if(batteryNavData.batteryLevel)
		{
			cached_battery = batteryNavData.batteryLevel;
		}
		
		return cached_battery;
	}
    
    return 0;

}

void init_position_tracking()
{
    x=0;
    y=0;
    z=0;
    yaw=0;
    vx=0;
    vy=0;
    vz=0;
	
    last_nav_receive=seconds();
    last_nav_calc=seconds();
	
	requested_enable_move = 0;
	requested_x_tilt = 0.0;
	requested_y_tilt = 0.0;
	requested_yaw_vel = 0.0;
	requested_z_vel = 0.0;
}

void update_position_tracking()
{
	NavigationData latest_data;
	
	myDrone->navigationDataReceiver().copyDataTo(latest_data);
	
	float current_receive_time = myDrone->navigationDataReceiver().navTimestamp * TIMESTAMP_PER_SECOND;
	float current_time = seconds();

	//copy vision tag vector
	visionTagVector = latest_data.visionTagVector;


	//for testing.... output visionTagVector types
	for(int i = 0; i < visionTagVector.size(); i++)
	{
		printf("Index: %d, Type: %d\n", i, visionTagVector.at(i).type);
	}


	bool zero_vx = false;
	bool zero_vy = false;
	bool zero_z = false;
	bool zero_yaw = false;
	
	
	if(latest_data.speed.vx < DRIFT_TOLERANCE && latest_data.speed.vx > -DRIFT_TOLERANCE)
	{
		zero_vx = true;
	}
	if(latest_data.speed.vy < DRIFT_TOLERANCE && latest_data.speed.vy > -DRIFT_TOLERANCE)
	{
		zero_vy = true;
	}
	
	if(latest_data.altitude < DRIFT_TOLERANCE && latest_data.altitude > -DRIFT_TOLERANCE)
	{
		zero_z = true;
	}
	
	if(latest_data.orientation.yaw < DRIFT_TOLERANCE && latest_data.orientation.yaw > -DRIFT_TOLERANCE)
	{
		zero_yaw = true;
	}
	
	if(! zero_vx || ! requested_enable_move) vx = latest_data.speed.vx;
	if(! zero_vy || ! requested_enable_move) vy = -latest_data.speed.vy;
	if(! zero_z)
	{
		vz = (latest_data.altitude * MILIMETERS_PER_METER - z) * (current_receive_time - last_nav_receive) * TIMESTAMP_PER_SECOND;
		z = latest_data.altitude * MILIMETERS_PER_METER; // this returns mm
	}
	else
	{
		z += vz * (current_time-last_nav_calc);
	}
	
	x += vx * (current_time-last_nav_calc);
	y += (vy ) * (current_time-last_nav_calc);
	
	if(! zero_yaw) yaw = -latest_data.orientation.yaw; // this returns deg
	
	last_nav_calc = current_time;
	last_nav_receive = current_receive_time;
}

float drone_get_x()
{
	return x;
}

float drone_get_y()
{
	return y;
}

float drone_get_z()
{
	return z;
}

float drone_get_yaw()
{
	return yaw;
}

float drone_get_x_velocity()
{
	return vx;
}

float drone_get_y_velocity()
{
	return vy;
}

float drone_get_z_velocity()
{
	return vz;
}

void drone_front_camera()
{
	myDrone->controller().switchToFrontCamera();
}

void drone_down_camera()
{
	myDrone->controller().switchToDownCamera();
}

void enable_drone_vision()
{
	myDrone->videoDataReceiver().write_external_camera_data();
	myDrone->videoDataReceiver().setEnableCbcuiVision(true);
}

void disable_drone_vision()
{
	myDrone->videoDataReceiver().setEnableCbcuiVision(false);
	myDrone->videoDataReceiver().delete_external_camera_data();
}

void move_control_thread()
{
	int request;
	int anim_request;
	while(true)
	{
		while(locker==LOCKED) {}
		locker = LOCKED;
		request = move_type;
		anim_request = anim_type;
		locker = UNLOCKED;

		switch(request)
		{
			case MOVEMENT:
			{
				myDrone->controller().sendControlParameters(requested_enable_move, requested_x_tilt, requested_y_tilt, requested_yaw_vel, requested_z_vel);
				myDrone->controller().sendWatchDog();//ensures the drone doesn't lose connection
				msleep(5);
				break;
			}
			case ANIMATION:
			{
				myDrone->controller().sendAnimationControl(anim_request);
				myDrone->controller().sendWatchDog();//ensures the drone doesn't lose connection
				msleep(5);
				break;
			}
			default:
			{
				myDrone->controller().sendWatchDog();//ensures the drone doesn't lose connection
				break;
			}
		}	

		
	}
}
void drone_move(float x_tilt, float y_tilt, float yaw_vel, float z_vel)
{
	requested_enable_move = true;
	requested_x_tilt = x_tilt;
	requested_y_tilt = y_tilt;
	requested_yaw_vel = yaw_vel;
	requested_z_vel = z_vel;
}

void drone_hover()
{
	requested_enable_move = false;
}


void drone_hover_on_roundel(int shouldHover)
{
	if(shouldHover == 0)
		myDrone->controller().setFlyingMode(HOVER_ON_ORIENTED_ROUNDEL);
	else if(shouldHover == 1)
		myDrone->controller().setFlyingMode(NORMAL);
	else
	{
		printf("\n Hover Failed.\n Command recieved %i. Input of 0 or 1 is accepted", shouldHover);
	}
}

void drone_set_ultrasound_channel(int channel)
{
	if(channel == CHANNEL_22_5MHZ)
		myDrone->controller().setUltrasoundFrequency(CHANNEL_22_5MHZ);
	else if(channel == 2)
		myDrone->controller().setUltrasoundFrequency(CHANNEL_22MHZ);		
}


void drone_set_detection(int detectType)
{
	switch (detectType)
	{
		case NONE:
			myDrone->controller().disableDroneTagging();
			break;
		case GREEN:
			myDrone->controller().detectColor(GREEN);
			break;
		case YELLOW:
			myDrone->controller().detectColor(YELLOW);
			break;
		case BLUE:
			myDrone->controller().detectColor(BLUE);
			break;
		case ORANGE_GREEN:
			myDrone->controller().detectGroundStripe(ORANGE_GREEN);
			break;
		case YELLOW_BLUE:
			myDrone->controller().detectGroundStripe(YELLOW_BLUE);
			break;
		case ROUNDEL:
			myDrone->controller().detectRoundel_BW();
			break;
	}
}

void drone_animation(int animationType, int tInterval)
{
	while(locker==LOCKED) {}
	locker = LOCKED;
	move_type = MOVEMENT;
	anim_type = animationType;
	locker = UNLOCKED;

	msleep(tInterval);
}


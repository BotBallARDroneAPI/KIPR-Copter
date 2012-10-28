// ARDroneAPI.cpp

#include "ARDroneAPI.h"

#include "compat.h"
#include "process.h"
#include "Drone.h"

#include <math.h>
#include <fcntl.h>

#define EXTERNAL_CAMERA_BUFFER "/tmp/external_camera_buffer"
#define EXTERNAL_CAMERA_READY "/tmp/external_camera_ready"

using namespace ARDrone;
using namespace std;

Drone * myDrone;
bool drone_connected = false;

bool watchdog_enable = false;
int watchdog_pid;

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

void watchdog(); //Process
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

void watchdog()
{
	while(1)
	{
		if(watchdog_enable)
		{
			myDrone->controller().sendWatchDog();
		}
		
		msleep(50);
	}
}

void monitor_sensors()
{
	while(1)
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
		
		//watchdog_pid = start_process(watchdog);
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
		//kill_process(watchdog_pid);
		
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
	else
	{
		return 0;
	}
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
	
	float current_receive_time = myDrone->navigationDataReceiver().navTimestamp / 1000.0;
	float current_time = seconds();

	//check for watchdog flag
	if(latest_data.flags.controlWatchdogDelayed)
		myDrone->controller().sendWatchDog();
	
	
	bool zero_vx = false;
	bool zero_vy = false;
	bool zero_z = false;
	bool zero_yaw = false;
	
	
	if(latest_data.speed.vx < 0.001 && latest_data.speed.vx > -0.001)
	{
		//printf("Zero vx\n");
		zero_vx = true;
	}
	if(latest_data.speed.vy < 0.001 && latest_data.speed.vy > -0.001)
	{
		//printf("Zero vy\n");
		zero_vy = true;
	}
	
	if(latest_data.altitude < 0.001 && latest_data.altitude > -0.001)
	{
		//printf("Zero z\n");
		zero_z = true;
	}
	
	if(latest_data.orientation.yaw < 0.001 && latest_data.orientation.yaw > -0.001)
	{
		//printf("Zero z\n");
		zero_yaw = true;
	}
	
	if(! zero_vx || ! requested_enable_move) vx = latest_data.speed.vx;
	if(! zero_vy || ! requested_enable_move) vy = -latest_data.speed.vy;
	if(! zero_z)
	{
		//if(fabs(latest_data.altitude * 1000.0 - z)>0.001)
		//{
		vz = (latest_data.altitude * 1000.0 - z) * (current_receive_time - last_nav_receive) / 1000.0;
		z = latest_data.altitude * 1000.0; // this returns mm
		//}
	}
	else
	{
		z += vz * (current_time-last_nav_calc);
	}
	
	x += vx * (current_time-last_nav_calc);
	y += (vy /* * 7.3 / 1.256 */ ) * (current_time-last_nav_calc);
	
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
	//printf("Writing initial camera data\n");
	write_external_camera_data();
	//printf("Enabling Drone vision\n");
	myDrone->videoDataReceiver().setEnableCbcuiVision(true);
	//printf("enable_drone_vision exit\n");
}

void disable_drone_vision()
{
	myDrone->videoDataReceiver().setEnableCbcuiVision(false);
	delete_external_camera_data();
}

void write_external_camera_data()
{
	//printf("write_external_camera_data enter\n");
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
		
		//printf("Image created\n");
		
		myDrone->videoDataReceiver().copyDataTo(*videoData, timestamp);
		
		//printf("Copied data\n");
		
		//printf("Dimensions: %d by %d\n", videoData->width, videoData->height);
		
		srcw = videoData->width;
		srch = videoData->height;
		
		destw = 160;
		desth = 120;
		
		buffer_file = open(EXTERNAL_CAMERA_BUFFER, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		
		//printf("Opened buffer, %d\n", buffer_file);	
		
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
		
		//printf("Closed buffer\n");
		
		delete videoData;
		
		//printf("Writing ready flag\n");
		
		ready_file = open(EXTERNAL_CAMERA_READY, O_WRONLY | O_CREAT, 0666);
		close(ready_file);
		
		//printf("ready_file %d\n", ready_file);
	}
	
	//printf("write_external_camera_data exit\n");	
}

void delete_external_camera_data()
{
	remove(EXTERNAL_CAMERA_BUFFER);
	remove(EXTERNAL_CAMERA_READY);
}

void move_control_thread()
{
	while(1)
	{
		myDrone->controller().sendControlParameters(requested_enable_move, requested_x_tilt, requested_y_tilt, requested_yaw_vel, requested_z_vel);
		msleep(5);
	}
}
void drone_move(float x_tilt, float y_tilt, float yaw_vel, float z_vel)
{
	requested_enable_move = 1;
	requested_x_tilt = x_tilt;
	requested_y_tilt = y_tilt;
	requested_yaw_vel = yaw_vel;
	requested_z_vel = z_vel;
}

void drone_hover()
{
	requested_enable_move = 0;
}


void drone_hover_on_roundel(int shouldHover)
{
	if(shouldHover == 1)
		myDrone->controller().setFlyingMode(HOVER_ON_ORIENTED_ROUNDEL);
	else if(shouldHover == 0)
		myDrone->controller().setFlyingMode(NORMAL);
	else
	{
		printf("Unsupported drone_hover_on_roundel parameter %i", shouldHover);
	}
}

void drone_set_ultrasound_channel(int channel)
{
	if(channel)
		myDrone->controller().setUltrasoundFrequency(CHANNEL_22_5MHZ);
	else
		myDrone->controller().setUltrasoundFrequency(CHANNEL_22MHZ);		
}



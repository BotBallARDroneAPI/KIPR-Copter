
#include "ARDroneAPI.h"
#include "compat.h"
#include <iostream>

using namespace std;


void vision_test_cbc();
void connect_takeoff();
void land_disconnect();
void takeoff_test(int hover_time);
void move_test(double speed, int movement_time);
void navdata_test();
void emergency_test();
void flying_mode_test(int flying_time);

int main(int argc, char** argv)
{
	connect_takeoff();
	
	move_test(.025, 2);
	
	land_disconnect();
	
	return 0;
}

// This barebones vision test simply outputs the
// the x,y coordinates on the cbc screen of where
// a blob is detected at.
void vision_test_cbc()
{
	int x, y;
	enable_drone_vision(); //gets the most recent camera image and process it
	//give time to setup vision tracking
	//while(black_button() != 1) {}
	
	drone_front_camera();
	//main loop
	//while(black_button() == 0)
	{
		//x = track_x(0,0);
		//y = track_y(0,0);
		//if(track_count(0) > 0)
		{
			printf("Blob is at (%d,%d)\n", x, y);
		}
		//else
			printf("No Object Detected");
		sleep(0.2); //dont rush update
	}
	
	//disable_drone_vision();
	
	//test complete
}

//This function wraps the connect takeoff and initial hover for me
void connect_takeoff()
{
	drone_connect();
	drone_takeoff();
	drone_takeoff();
	drone_takeoff();
	drone_hover();
	sleep(4); //sleep to ensure drone is up before moving
}

//this function wraps the land and disconnect for me
void land_disconnect()
{
	drone_land();
	drone_disconnect();
}

/////////////////////////////////////////////////////////////////////////////////
//									TEST CASES								   //
//									----------								   //
//	The following test cases assume the drone is connected to already and that //
//  the main process lands the drone and disconnects after the test case is    //
//  complete. This allows multiple test routines on a single flight and thus   //
//  a greater flexibility in testing and more diverse behaviours and values.   //
//																			   //
/////////////////////////////////////////////////////////////////////////////////

//this test case connects to the drone and
//takes off and hovers and then lands and disconnects
void takeoff_test(int hover_time)
{
	connect_takeoff();
	
	sleep(hover_time);
	
	land_disconnect();
}

//This function tests all of the functionality of the drone_move function
//speed must be between -1 and 1.
void move_test(double speed, int movement_time)
{	
	//test x direction
	drone_move(speed, 0.0, 0.0, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test -x direction
	drone_move(-speed, 0.0, 0.0, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test y direction
	drone_move(0.0, speed, 0.0, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test -y direction
	drone_move(0.0, -speed, 0.0, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test yaw 
	drone_move(0.0, 0.0, speed, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test -yaw
	drone_move(0.0, 0.0, -speed, 0.0);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test z direction 
	drone_move(0.0, 0.0, 0.0, speed);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
	
	//test -z direction
	drone_move(0.0, 0.0, 0.0, -speed);
	sleep(movement_time);
	
	drone_hover();
	sleep(1);
}

//This function tests out our navdata accessor functions
//by using the movement test function. We expect that the values should be near 0
//it will also check the battery state at the end.
void navdata_test()
{
	move_test(0.1, 2);
	cout << "x: " << drone_get_x() << endl;
	cout << "y: " << drone_get_y() << endl;
	cout << "z: " << drone_get_z() << endl;
	cout << "yaw: " << drone_get_yaw() << endl;
	cout << "bat: " << drone_get_battery() << endl;
}

//This function simply tests the emergency command.
//It should land the drone turning the lights red and then
//should reset the lights to green.
void emergency_test()
{
	drone_emergency();
	sleep(2);
	
	drone_emergency();
}

void flying_mode_test(int flying_time)
{
	//ensure drone is able to move
	drone_move(0,0,0.05,0);
	sleep(2);
	
	drone_hover_on_roundel(true);
	sleep(flying_time);
	
	//see if the drone ignores move commands now?
	drone_move(0,0,0.05,0);
	sleep(2);
	
	drone_hover_on_roundel(false);
	sleep(flying_time);
	
	//see if the drone ignores move commands now?
	drone_move(0,0,0.05,0);
	sleep(2);
}

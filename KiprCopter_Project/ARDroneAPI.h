// ARDroneAPI.h
#ifndef ARDRONEAPI_H
#define ARDRONEAPI_H

#ifdef __cplusplus
extern "C" {
#endif
	/**
	 @brief This function will establish a connection between the drone and the CBC for transmitting information.
	 **/
	void drone_connect();
	
	/**
	 @brief This function will be used to disconnect the drone from the CBC.
	 **/
	void drone_disconnect();
	
	/**
	 @brief This function will be used to make the drone takeoff and stabilize itself.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @post The drone should reach its normal operating height
	 **/
	void drone_takeoff();
	
	/**
	 @brief This function will be used to land the drone at its current position.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @post The drone should slowly descend to the ground from its current height.
	 **/
	void drone_land();
	
	/**
	 @brief This function will be used to immediately turn off the drone rotors or reset the emergency toggle
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @post The drone will stop moving and fall to the ground.
	 **/
	void drone_emergency();
	
	/**
	@brief retrieves the cached battery value
	@pre drone_connect must have been previously called to establish a connection to the drone.
	@return An integer representing the current battery level 
	@TODO Specify the range in the above comment 
	**/
	int drone_get_battery();
	
	/**
	 @brief Retrieves the x value relative to the drones starting position.  Negative values indicate
			the drone has moved to the left of it's starting position.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return x value away from the drones starting position in milimeters
	 @TODO verify it is in fact milimeters
	 **/
	float drone_get_x();
	
	/**
	 @brief Retrieves the y value relative to the drones starting position.  Negative values indicate
			the drone has moved backwards from it's starting position.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return y value away from the drones starting position in milimeters
	 @TODO verify it is in fact milimeters
	 **/
	float drone_get_y();
	
	/**
	 @brief Retrieves the y value relative to the drones starting position.  Negative values indicate
			the drone has moved down from it's starting position.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return z value away from the drones starting position in milimeters
	 @TODO verify it is in fact milimeters also verify that the z can be negative is it negative from the ground or its air starting position
	 **/
	float drone_get_z();
	
	/**
	 @brief Retrieves the current velocity in the right or left direction.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return A float indicating the millimeters per second 
	 **/
	float drone_get_x_velocity();
	
	/**
	 @brief Retrieves the current velocity in the forward or backwards direction.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return A float indicating the velocity in millimeters per second 
	 **/
	float drone_get_y_velocity();
	
	/**
	 @brief Retrieves the current velocity in the upward or downwards direction.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return A float indicating the velocity in millimeters per second 
	 **/
	float drone_get_z_velocity();
	
	/**
	 @brief Retrieves the current rotation in the clockwise (positive) or counterclockwise (negative) direction.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @return A float indicating the degrees rotated from the original orientation
	 **/
	float drone_get_yaw();
	
	/**
	 @brief Switches the drone vision feed to the front facing camera
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 **/
	void drone_front_camera();
	
	/**
	 @brief Switches the drone vision feed to the downward facing camera
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 **/
	void drone_down_camera();
	
	/**
	 @brief Starts sending video data to the cbc for vision tracking.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 **/
	void enable_drone_vision();
	/**
	 @brief Stops the drone from sending data to the cbc for vision tracking.
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 **/
	void disable_drone_vision();
	/** 
	 @brief Sends the vision data to the CBC's vision library for vision tracking
	 **/
	void write_external_camera_data();
	/**
	 @brief Deletes the vision data from the CBC'c vision library to stop vision tracking
	 **/
	void delete_external_camera_data();
	/**
	 @brief Sets the Drone's Mac Address Pair to be the given string
	 @param macAddress A string representing the Mac Address of your CBC
	 **/
	void set_drone_Mac_Address(char * macAddress);
	/**
	 @brief Tells the drone to move with the given parameters
	 @param enable A value indicating if movement is enabled. 0 - True 1 - False
	 @param x_tilt A value from zero to one indicating the percentage of maximum tilt in the left or right direction
			negative values are left and positive values are right. Ex: -.5 means Half of the total tilt left
	 @param y_tilt A value from zero to one indicating the percentage of maximum tilt in the forward or backward direction
			negative values are left and positive values are right. Ex: -.5 means Half of the total tilt backwards.
	 @param yaw_vel A value indicating the rotational velocity of the dronein milieters per second
	 @param z_vel A value indicating the change in altitude in milimeters per second
	 **/
	void drone_move(float x_tilt, float y_tilt, float yaw_vel, float z_vel);
	
	/**
	 @brief Tells the drone that it should stop moving and hover at its current location
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	**/
	void drone_hover();
	
	/**
	 @brief Tells the drone to hover over the Roundel that it has detected
	 @param shouldHover A integer representing if the drone should hover or not 
						1 == True meaning the drone will attempt to hover on a roundel
						0 == False meaning the drone will resume normal flight
	 @pre drone_connect must have been previously called to establish a connection to the drone.
	 @pre A roundel must have been detected in the drones vision tags
	 **/
	void drone_hover_on_roundel(int shouldHover);
	
	
#ifdef __cplusplus
}
#endif

#endif
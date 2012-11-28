void drone_remote_control(float max_tilt, float max_yaw_vel, float max_z_vel)
{
	int in_air = 0;
	int enable_move;
	float x_tilt, y_tilt, yaw_vel, z_vel;
	
	// This loop will continue forever; put it in a dedicated program and use the CBC's E-Stop to exit.
	while(1)
	{
		if(a_button())
		{
			if(in_air)
			{
				drone_land();
			}
			else
			{
				drone_takeoff();
			}
			in_air = !in_air;

			while(a_button()) msleep(5);
		}
		if(black_button())
		{
			drone_emergency();
			while(black_button()) msleep(5);
		}
		x_tilt = (float)(b_button()) * (float)(-accel_x() / 65.0 * max_tilt);
		y_tilt = (float)(b_button()) * (float)(-accel_y() / 65.0 * max_tilt);
		yaw_vel = max_yaw_vel * (float)(left_button() - right_button());
		z_vel = max_z_vel * (float)(up_button() - down_button());

		enable_move = b_button() || left_button() || right_button() || up_button() || down_button();
		
		if(enable_move)
			drone_move(x_tilt, y_tilt, yaw_vel, z_vel);
		else
			drone_move(0,0,0,0);

		cbc_display_clear();
		printf("A=Tkf/Lnd Blk=Emg B=TiltXY Arrow=Yaw/Z\nControl= %d %.2f %.2f %.2f %.2f\nBat=%d Pos=%d %d %d Vel=%d %d %d Yaw=%d    \n", enable_move, x_tilt, y_tilt, yaw_vel, z_vel, drone_get_battery(), (int)(drone_get_x()), (int)(drone_get_y()), (int)(drone_get_z()), (int)(drone_get_x_velocity()), (int)(drone_get_y_velocity()), (int)(drone_get_z_velocity()), (int)(drone_get_yaw()));

		msleep(25);
	}
}

int main()
{
	printf("Connecting to Drone...\n");
	drone_connect();
	printf("Connected!\n");

	drone_remote_control(0.1, 0.1, 0.1);
	
}

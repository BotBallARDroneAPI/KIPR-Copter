/*
 *  track_test.cpp
 *  
 * This test case tracks a blob setup prior to running on channel 0
 *
 */


int main ()
{
	float CENTER = 79.5;
	float OFFSET = 0.05;
	
	drone_connect();
	
	enable_drone_vision();	
	drone_front_camera();
	
	sleep(2);
	
	drone_takeoff();
	
	printf("Black button to exit test loop and land the drone");
	
	float x, y;
	
	track_update();
	while(!black_button())
	{
		x = OFFSET * ((track_x(0,0) - CENTER) / CENTER);
		y = OFFSET * ((track_y(0,0) - CENTER) / CENTER);
		
		if(track_count(0) > 0)
		{
			printf("Items tracking: %d\n", track_count(0));
			drone_move(0,0, x, y);
		}
		els	
		{
			printf("No items: Hovering \n");
			drone_hover();
		}
		sleep(4);
		track_update();
	}
		
	printf("Landing");
	drone_move(0,0,0,-.25);
	sleep(0.5);
	
	drone_land();
	
	drone_disconnect();
	
	return 0;
}

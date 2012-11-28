int main()
{
	printf("Connecting to Drone...\n");
	drone_connect();
	printf("Connected!\n");

	printf("Black = exit\nLeft=CBC Right=Drone\nUp=Front Down=Vertical");

	while(! black_button())
	{
		if(left_button())
		{
			disable_drone_vision();
			while(left_button()) msleep(20);
		}
		if(right_button())
		{
			enable_drone_vision();
			while(right_button()) msleep(20);
		}
		if(up_button())
		{
			drone_front_camera();
			while(up_button()) msleep(20);
		}
		if(down_button())
		{
			drone_down_camera();
			while(down_button()) msleep(20);
		}
		
		msleep(20);
	}
	
}

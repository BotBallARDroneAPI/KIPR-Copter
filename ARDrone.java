


public class ARDrone{
	public native void  connect();
	public native void  disconnect();
	public native void  takeoff();
	public native void  land();
	public native void  emergency();
	public native int   get_battery();
	public native float get_x();
	public native float get_y();
	public native float get_z();
	public native float get_x_velocity();
	public native float get_y_velocity();
	public native float get_z_velocity();
	public native float get_yaw();
	public native void  front_camera();
	public native void  down_camera();
	public native void  enable_drone_vision();
	public native void  disable_drone_vision();
	public native void  write_external_camera_data();
	public native void  delete_external_camera_data();
	public native void  set_Mac_Address(String macAddress);
	public native void  move(float x_tilt, float y_tilt, float yaw_vel, float z_vel);
	public native void  hover();
	public native void  hover_on_roundel(boolean enable);
	public native void  set_ultrasound_channel(int channel);
	public native void  set_detection(int detectType);
	
	static
	{
			System.load("/mnt/kiss/jvm/cbc/ARDrone.so");
	}
};

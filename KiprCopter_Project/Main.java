
public class Main {

    public static void main(String[] argv) {
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

        print_battery(myDrone);

        connect_takeoff_land_disconnect(myDrone);
        
//        move_test(myDrone, (float) .025, 2);

        System.out.println("  Ending testflight ");
    }

    public static void connect_takeoff_land_disconnect(ARDrone dro) {
        System.out.println("connect();");
        dro.connect();
        System.out.println("takeOff();");
        dro.takeoff();
        System.out.println("land();");
        dro.land();
        System.out.println("disconnect();");
        dro.disconnect();
    }

    // I wonder what will happen?
    public static void disconnect_wo_land(ARDrone dro) {
        dro.connect();
        dro.takeoff();
        dro.disconnect();
        System.out.println("Drone disconnected without calling land first");
        System.out.println("What happened?");
        Thread.sleep(8000);
    }

    public static void print_battery(ARDrone dro) {
        System.out.println(dro.get_battery());
    }

    //This function simply tests the emergency command.
    //It should land the drone turning the lights red and then
    //should reset the lights to green.
    public static void emergency_test(ARDrone dro) {
        dro.emergency();
        Thread.sleep(2000);
        dro.emergency();
    }

    //This function tests all of the functionality of the drone_move function
    //speed must be between -1 and 1.
    public static void move_test(ARDrone dro, float speed, int movement_time) {
        //test x direction
        dro.move(speed, (float) 0.0, (float) 0.0, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1000);

        //test -x direction
        dro.move(-speed, (float) 0.0, (float) 0.0, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test y direction
        dro.move((float) 0.0, speed, (float) 0.0, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test -y direction
        dro.move((float) 0.0, -speed, (float) 0.0, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test yaw 
        dro.move((float) 0.0, (float) 0.0, speed, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test -yaw
        dro.move((float) 0.0, (float) 0.0, -speed, (float) 0.0);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test z direction 
        dro.move((float) 0.0, (float) 0.0, (float) 0.0, speed);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1);

        //test -z direction
        dro.move((float) 0.0, (float) 0.0, (float) 0.0, -speed);
        Thread.sleep(movement_time);

        dro.hover();
        Thread.sleep(1000);
    }

    public static void flying_mode_test(ARDrone dro) {
        //ensure drone is able to move
        dro.move(0, 0, 0, (float) 0.02);
        Thread.sleep(2000);

        System.out.println("Entering roundel mode");
        dro.hover_on_roundel(true);
        Thread.sleep(10000);

        //see if the drone ignores move commands now?
        System.out.println("Are move commands ignored while in roundel mode?");
        System.out.println("spin = fail");
        dro.move(0, 0, (float)0.05, 0);
        Thread.sleep(5000);


        System.out.println("Leaving roundel mode");
        dro.hover_on_roundel(false);

        //see if the drone ignores move commands now?
        System.out.println("Are move commands ignored while in roundel mode?");
        System.out.println("spin = pass");
        dro.move(0, 0, (float)0.05, 0);
        Thread.sleep(5000);
    }

    public static void measure_X(ARDrone dro) {

        int numMeasurements = 5;
        float testspeed = (float) .02;
        int sleeptime = 1500;

        System.out.println("Measuring X tilt precision");

        float posXAccelerometer = 0;
        float negXAccelerometer = 0;


        // move in x direction, measure x tilt along the way.
        dro.connect();
        dro.takeoff();
        dro.move(testspeed, (float) .0, (float) .0, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        posXAccelerometer = dro.get_x();
        for (int i = 0; i < numMeasurements; i++) {
            posXAccelerometer = (posXAccelerometer + dro.get_x()) / (float) i;
        }

        System.out.println("+X :" + Math.abs(posXAccelerometer - testspeed));
        System.out.println("+vX :" + dro.get_x_velocity());

        //stabilize
        dro.hover();
        Thread.sleep(5000);

        //move back to origional position, measure -x along the way
        dro.move(-testspeed, (float) .0, (float) .0, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        negXAccelerometer = dro.get_x();
        for (int i = 0; i < numMeasurements; i++) {
            negXAccelerometer = (negXAccelerometer + dro.get_x()) / (float) i;
        }

        System.out.println("-X :" + Math.abs(posXAccelerometer - testspeed));
        System.out.println("-vX :" + dro.get_x_velocity());


        dro.land();
        dro.disconnect();
    }

    public static void measure_Y(ARDrone dro) {

        int numMeasurements = 5;
        float testspeed = (float) .02;
        int sleeptime = 1500;

        System.out.println("Measuring Y");

        float posYAccelerometer = 0;
        float negYAccelerometer = 0;

        // move in Y direction, measure x tilt along the way.
        dro.connect();
        dro.takeoff();
        dro.move((float) .0, testspeed, (float) .0, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        posYAccelerometer = dro.get_y();
        for (int i = 0; i < numMeasurements; i++) {
            posYAccelerometer = (posYAccelerometer + dro.get_y()) / (float) i;
        }

        System.out.println("+Y :" + Math.abs(posYAccelerometer - testspeed));
        System.out.println("+vY :" + dro.get_y_velocity());


        //move back to origional position, measure -x along the way
        dro.hover();
        Thread.sleep(sleeptime);
        dro.move((float) .0, -testspeed, (float) .0, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        negYAccelerometer = dro.get_y();
        for (int i = 0; i < numMeasurements; i++) {
            negYAccelerometer = (negYAccelerometer + dro.get_y()) / (float) i;
        }

        System.out.println("-Y :" + Math.abs(posYAccelerometer + testspeed));
        System.out.println("-vY :" + dro.get_y_velocity());



        dro.land();
        dro.disconnect();
    }

    public static void measure_Z(ARDrone dro) {

        int numMeasurements = 5;
        float testspeed = (float) .02;
        int sleeptime = 1500;

        System.out.println("Measuring Z");

        // move in +Z direction, measure Z along the way.
        dro.connect();
        dro.takeoff();
        dro.move((float) .0, (float) .0, (float) .0, testspeed);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        float posZAccelerometer = dro.get_z();
        for (int i = 0; i < numMeasurements; i++) {
            posZAccelerometer = (posZAccelerometer + dro.get_z()) / (float) i;
        }

        System.out.println("+vZ :" + dro.get_z_velocity());
        System.out.println("+Z :" + Math.abs(posZAccelerometer - testspeed));


        //move back to origional position, measure -Z along the way
        dro.hover();
        Thread.sleep(sleeptime);
        dro.move((float) .0, (float) .0, (float) .0, -testspeed);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        float negZAccelerometer = dro.get_z();
        for (int i = 0; i < numMeasurements; i++) {
            negZAccelerometer = (negZAccelerometer + dro.get_z()) / (float) i;
        }

        System.out.println("-vZ :" + dro.get_z_velocity());
        System.out.println("-Z :" + Math.abs(posZAccelerometer + testspeed));

        dro.land();
        dro.disconnect();
    }

    public static void measure_yaw(ARDrone dro) {

        int numMeasurements = 5;
        float testspeed = (float) .5;
        int sleeptime = 1500;

        System.out.println("Measuring YAW");

        // move in +yaw direction, measure yaw along the way.
        dro.connect();
        dro.takeoff();
        dro.move((float) .0, (float) .0, testspeed, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        float posYAWAccelerometer = dro.get_yaw();
        for (int i = 0; i < numMeasurements; i++) {
            posYAWAccelerometer = (posYAWAccelerometer + dro.get_yaw()) / (float) i;
        }

        System.out.println("+YAW :" + Math.abs(posYAWAccelerometer - testspeed));


        //move back to origional position, measure -yaw along the way
        dro.hover();
        Thread.sleep(sleeptime);
        dro.move((float) .0, (float) .0, -testspeed, (float) .0);
        Thread.sleep(sleeptime);

        //take some measurements and get the average
        float negYAWAccelerometer = dro.get_yaw();
        for (int i = 0; i < numMeasurements; i++) {
            negYAWAccelerometer = (negYAWAccelerometer + dro.get_yaw()) / (float) i;
        }

        System.out.println("-YAW :" + Math.abs(posYAWAccelerometer + testspeed));

        dro.land();
        dro.disconnect();
    }
}

public class ARDrone {

    public native void connect();

    public native void disconnect();

    public native void takeoff();

    public native void land();

    public native void emergency();

    public native int get_battery();

    public native float get_x();

    public native float get_y();

    public native float get_z();

    public native float get_x_velocity();

    public native float get_y_velocity();

    public native float get_z_velocity();

    public native float get_yaw();

    public native void front_camera();

    public native void down_camera();

    public native void enable_drone_vision();

    public native void disable_drone_vision();

    public native void write_external_camera_data();

    public native void delete_external_camera_data();

    public native void set_Mac_Address(String macAddress);

    public native void move(float x_tilt, float y_tilt, float yaw_vel, float z_vel);

    public native void hover();

    public native void hover_on_roundel(boolean enable);

    public native void set_detection(int detectType);

    static {
        System.loadLibrary("ARDrone");
    }
};
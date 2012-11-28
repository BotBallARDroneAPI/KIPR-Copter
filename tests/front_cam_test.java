import cbccore.ARDrone

public class front_cam_test {

    public static void main(String[] argv) {
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

        connect_front_cam_test(myDrone);

        System.out.println("  Ending testflight ");
    }

    public static void connect_takeoff_land_disconnect(ARDrone dro) {
        System.out.println("connect();");
        dro.connect();
        System.out.println("front_camera(); for 15 sec");
        dro.front_camera();
        try {
			Thread.sleep(15000);
		} catch(InterruptedException ex) {
			Thread.currentThread().interrupt();
		}
        System.out.println("disconnect();");
        dro.disconnect();
    }
}
import cbccore.ARDrone;

public class takeoff_without_connect {

    public static void main(String[] argv) {
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

        connect_takeoff_wthout_connect(myDrone);

        System.out.println("  Ending testflight ");
    }

    public static void connect_takeoff_land_disconnect(ARDrone dro) {
        System.out.println("takeOff();");
        dro.takeoff();
        // what happens?
    }
}
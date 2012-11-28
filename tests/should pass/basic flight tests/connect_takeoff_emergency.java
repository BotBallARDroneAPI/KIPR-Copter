import cbccore.ARDrone;

public class connect_takeoff_land_emergency {

    public static void main(String[] argv) {
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

        connect_takeoff_land_emergency(myDrone);

        System.out.println("  Ending testflight ");
    }

    public static void connect_takeoff_land_disconnect(ARDrone dro) {
        System.out.println("connect();");
        dro.connect();
        System.out.println("takeOff();");
        dro.takeoff();
        System.out.println("land();");
        dro.land();
        System.out.println("emergency();");
        dro.emergency();
    }
}
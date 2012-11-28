
import cbccore.ARDrone;

public class connect_get_battery_disconnect {

    public static void main(String[] argv) {
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

        connect_get_battery_disconnect(myDrone);

        System.out.println("  Ending testflight ");
    }

    public static void connect_takeoff_land_disconnect(ARDrone dro) {
        System.out.println("connect();");
        dro.connect();
        System.out.println("get_battery();");
        System.out.println(dro.get_battery());
        System.out.println("disconnect();");
        dro.disconnect();
    }
}
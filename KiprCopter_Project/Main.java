

public class Main {

   public static void main(String[] argv)
	{
        System.out.println("  Beginning testflight ");
		ARDrone myDrone = new ARDrone();
		myDrone.connect();
		myDrone.takeoff();
		myDrone.land();
		myDrone.disconnect();
        System.out.println("  Ending testflight ");
   }
}

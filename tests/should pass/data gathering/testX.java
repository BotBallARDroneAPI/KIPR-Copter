
// get an idea of the drones accuracy and tilt vs velocity
// write to a file named data.txt in the same directory.

import java.io.*;
import cbccore.ARDrone;

public class testX {

    public static void main(String[] argv) {
		
		try{
        System.out.println("  Beginning testflight ");

        ARDrone myDrone = new ARDrone();

		System.out.println("connect();");
        dro.connect();
		
		System.out.println("x @ ground: " + dro.get_x());
		
        System.out.println("takeOff();");
        dro.takeoff();
		
		dro.hover();
		System.out.println("x @ hover: " + dro.get_x());
		
		//for 11 speeds. record tilt vs velocity
		for (int i=0; i<11; i++){
			
			dro.move(i/10.0, 0, 0, 0);
			
			FileWriter fstream = new FileWriter("data.txt");
			BufferedWriter out = new BufferedWriter(fstream);
			out.write("X tilt vs velocity");
			
			//measure + direction

			//take 10 measurements
			float tiltmeasurements[10];
			float velmeasurements[10];
			for (int j=0; j<10; j++){
				try {
					Thread.sleep(100);
				} catch(InterruptedException ex) {
					Thread.currentThread().interrupt();
				}
				tiltmeasurements[i] = dro.get_x();
			}
			
			
			// average the measurements
			float avgtilt = 0;
			float avgvel = 0;
			for (int j=0; j<10; j++){
				avgtilt = avgtilt + tiltmeasurements[j];
				avgvel = avgvel + velmeasurements[j];
			}
			avgtilt = avgtilt/10.0;
			avgvel = avgvel/10.0;
			
			//write data to disk
			out.write("tilt @: " + avgtilt + " ~ vel @: " + avgvel);
			

			
			// measure - direction
			dro.move(-(i/10.0), 0, 0, 0);
			
			//take 10 measurements
			for (int j=0; j<10; j++){
				try {
					Thread.sleep(100);
				} catch(InterruptedException ex) {
					Thread.currentThread().interrupt();
				}
				tiltmeasurements[i] = dro.get_x();
			}
			
			// average the measurements
			float avgtilt = 0;
			float avgvel = 0;
			for (int j=0; j<10; j++){
				avgtilt = avgtilt + tiltmeasurements[j];
				avgvel = avgvel + velmeasurements[j];
			}
			avgtilt = avgtilt/10.0;
			avgvel = avgvel/10.0;
			
			//write data to disk
			out.write("tilt @: " + avgtilt + " ~ vel @: " + avgvel);
		}
		
		
		System.out.println("land();");
        dro.land();
        System.out.println("disconnect();");
        dro.disconnect();
		
        System.out.println("  Ending testflight ");
		
	}catch (Exception e){//Catch exception if any
		System.err.println("Error: " + e.getMessage());
	}
}
    }

}
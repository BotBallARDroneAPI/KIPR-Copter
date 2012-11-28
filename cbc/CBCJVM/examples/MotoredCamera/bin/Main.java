import cbccore.movement.DriveTrain;
import cbccore.movement.plugins.motor.MotorMovementPlugin;
import cbccore.movement.plugins.motor.Wheel;
import cbccore.sensors.vision.*;

public class Main {
	public static void main(String [] args) {
		cbccore.Device.init();
		DriveTrain dt = new DriveTrain(
			new MotorMovementPlugin(
				new Wheel(0, 15.5744, 1.), new Wheel(1, 15.5744, 1.), 11.
			)
		);
		Camera c = new Camera();
		Blob mostProbable = null;
		int bestConfidence = 0;
		BlobList bList = new BlobList(c, 0);
		System.out.println(bList.size() + ", " + c.getAvailableBlobLength(0));
		for(Object i : bList) {
			if(((Blob)i).getConfindence()  > bestConfidence) {
				bestConfidence = ((Blob)i).getConfindence();
				mostProbable = ((Blob)i);
			}
		}
		
		int destination = 100;
		
		while(true) {
			while(!mostProbable.update()) { c.update(); }
			if(Math.sqrt(mostProbable.getSize()) > 100) {
				dt.moveAtCmps(
					-dt.getMaxCmps() *
					Math.abs((double)mostProbable.getSize() - destination) /
					320.);
			} else {
				dt.moveAtCmps(
					dt.getMaxCmps() *
					Math.abs((double)mostProbable.getSize() - destination) /
					320.);
			}
		}
	}
}

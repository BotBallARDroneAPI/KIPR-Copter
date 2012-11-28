import cbccore.movement.DriveTrain;
import cbccore.movement.plugins.motor.MotorMovementPlugin;
import cbccore.movement.plugins.motor.Wheel;

public class Main {
	public static void main(String [] args) {
		cbccore.Device.init();
		DriveTrain dt = new DriveTrain(
			new MotorMovementPlugin(
				new Wheel(0, 15.5744, 1.), new Wheel(1, 15.5744, 1.), 11.
			)
		);
		
		dt.moveCm(100., dt.getMaxCmps());
		
		System.out.println("moved forward!");
		
		dt.rotateDegrees(180., dt.getMaxDegreesPerSec());
		//dt.moveCurveRadians(20., 100., dt.getMaxCmps(100.));
	}
}

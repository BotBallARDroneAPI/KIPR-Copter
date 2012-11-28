/*
 * This file is part of CBCJVM.
 * CBCJVM is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * CBCJVM is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with CBCJVM.  If not, see <http://www.gnu.org/licenses/>.
 */

import cbccore.movement.DriveTrain;
import cbccore.movement.plugins.create.CreateMovementPlugin;
import cbccore.create.Create;
import cbccore.create.CreateConnectException;

public class Main {
	public static void main(String [] args) {
		cbccore.Device.init();
		
		DriveTrain dt = null;
		try {
			dt = new DriveTrain(
				new CreateMovementPlugin(new Create(), 1., 1., false)
			);
		} catch(CreateConnectException e) {
			System.out.println("Create failed to connect.");
			System.exit(1);
		}
		// dt.moveCm(100., dt.getMaxCmps()*.8);
		// dt.rotateDegrees(180., dt.getMaxDegreesPerSec()*.8);
		dt.moveCurveDegrees(360., 50., 0.5*dt.getMaxCmps(50.));
		dt.moveCurveDegrees(360., -50., 0.5*dt.getMaxCmps(-50.));
	}
}

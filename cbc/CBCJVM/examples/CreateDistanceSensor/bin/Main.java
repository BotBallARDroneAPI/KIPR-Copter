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

import cbccore.sensors.*;
import cbccore.sensors.analog.*;
import cbccore.sensors.buttons.*;
import cbccore.movement.DriveTrain;
import cbccore.movement.plugins.create.CreateMovementPlugin;
import cbccore.create.Create;
import cbccore.create.CreateConnectException;
import cbccore.events.*;
import java.util.Arrays;
import java.util.ArrayList;

public class Main {
	public static void main(String [] args) {
		
		cbccore.Device.init();
		
		System.out.println("Please press the Black Hardware Button to start.");
		
		EventManager.get().connect(ButtonEmitter.BlackButtonReleased,
		                           new StartListener(0));
		ButtonEmitter.get().start();
	}
	
	//****************************
	//*** Begin actual program ***
	
	public static class StartListener implements IEventListener {
		
		ETSensor distSensor;
		DriveTrain dt;
		
		public StartListener(int port) {
			distSensor = new ETSensor(port);
			try {
				dt = new DriveTrain(
					new CreateMovementPlugin(new Create(), 1., false)
				);
			} catch(CreateConnectException ex) {
				System.out.println("Create connection failed.");
			}
		}
		
		public void event(Event e) {
			EventManager.get().disconnect(ButtonEmitter.BlackButtonReleased,
			                              this);
			ButtonEmitter.get().exit();
			
			double dist = distSensor.getCm(50, 10);
			System.out.println("Distance is: " + dist + "cm");
			System.out.println("Moving to 5cm away");
			dt.moveCm(-dist*.5+5., dt.getMaxCmps()*.5);
			dist = distSensor.getCm(50, 10);
			dt.moveCm(-dist+5., dt.getMaxCmps()*.5);
			
			/*while(true) {
				System.out.println(""+distSensor.getValueHigh());
				try { Thread.sleep(200); } catch(Exception ex) { return; }
			}*/
		}
	}
}

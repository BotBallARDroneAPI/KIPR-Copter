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

package cbccore.low.simulator;

import cbccore.NotImplemented;
import cbccore.low.Sensor;

/**
 * 
 * @author Braden McDorman / Benjamin Woodruff
 *
 */

public class SimulatedSensor extends Sensor {
	
	@NotImplemented public SimulatedSensor() {
	}
	
	@NotImplemented public int digital(int port) {
		return 0;
	}
	
	// sets port (0 to 7)to value (0 or 1)
	@NotImplemented public int set_digital_output_value(int port, int value) {
		return 0;
	}
	
	// returns 10-bit value from analog port (ports 8 to 15)
	@NotImplemented public int analog10(int port) {
		return 0;
	}
	
	// returns 8-bit value from analog port (ports 8 to 15)
	@NotImplemented public int analog(int port) {
		return 0;
	}
	
	// returns x acceleration (-2047 to 2047, +/- 1.5 gee)
	@NotImplemented public int accel_x() {    
		return 0;
	}
	
	// returns y acceleration (-2047 to 2047, +/- 1.5 gee)
	@NotImplemented public int accel_y() {
		return -(int)(2047./1.5*1.);
	}
	
	// returns z acceleration (-2047 to 2047, +/- 1.5 gee)
	@NotImplemented public int accel_z() {
		return 0;
	}
	
	// returns range in mm for sonar plugged into port (13-15)
	@NotImplemented public int sonar(int port) {
		return 0; //stub
	}
	
	// returns range in whole inches for sonar plugged into port (13-15)
	@NotImplemented public int sonar_inches(int port) {
		return 0;
	}
	
	@NotImplemented public void set_analog_floats(int mask) {
		set_each_analog_state((mask >> 0) & 1, (mask >> 1) & 1, (mask >> 2) & 1,
		                      (mask >> 3) & 1, (mask >> 4) & 1, (mask >> 5) & 1,
		                      (mask >> 6) & 1, (mask >> 7) & 1);
	}
	
	@NotImplemented public void set_each_analog_state(int a0, int a1, int a2,
	                                                  int a3, int a4, int a5,
	                                                  int a6, int a7) {
	}
}

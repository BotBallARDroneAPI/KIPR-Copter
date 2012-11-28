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

package cbccore.motors.statemotors.composed;

import cbccore.motors.statemotors.IAdvancedStateMotor;
import cbccore.motors.statemotors.offset.OffsetAdvancedStateMotor;

/**
 * 
 * @author Benjamin Woodruff
 *
 */

public class ComposedAdvancedStateMotor<E extends IAdvancedStateMotor>
             extends ComposedStateMotor<E> implements IAdvancedStateMotor {
	
	public ComposedAdvancedStateMotor(E ... motors) {
		super(motors);
	}
	
	public ComposedAdvancedStateMotor(E[] motors, int ... offsets) {
		super(motors, offsets);
	}
	
	protected E offsetMotorFactory(E baseMotor, int offset) {
		return (E)(new OffsetAdvancedStateMotor(baseMotor, offset));
	}
	
	public void setPositionTime(int pos, int ms) {
		for(E i:getMotors()) {
			i.setPositionTime(pos, ms);
		}
	}
	
	public void setPositionTime(int pos, double sec) {
		for(E i:getMotors()) {
			i.setPositionTime(pos, sec);
		}
	}
	
	public void setPositionSpeed(int pos, int speed) {
		for(E i:getMotors()) {
			i.setPositionSpeed(pos, speed);
		}
	}
}

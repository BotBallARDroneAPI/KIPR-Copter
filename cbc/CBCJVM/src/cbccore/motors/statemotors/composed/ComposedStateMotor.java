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

import cbccore.motors.statemotors.IStateMotor;
import cbccore.motors.statemotors.offset.OffsetStateMotor;

/**
 * 
 * @author Benjamin Woodruff
 *
 */

public class ComposedStateMotor<E extends IStateMotor> implements IStateMotor {
	
	private E[] motors;
	
	public ComposedStateMotor(E ... motors) {
		this(motors, getEmptyOffsetArray(motors.length));
	}
	
	private static int[] getEmptyOffsetArray(int length) {
		int[] offsets = new int[length];
		for(int i = 0; i < length; ++i) {
			offsets[i] = 0;
		}
		return offsets;
	}
	
	public ComposedStateMotor(E[] motors, int ... offsets) {
		for(int i = 0; i < motors.length; ++i) {
			if(offsets[i] != 0) {
				motors[i] = offsetMotorFactory(motors[i], offsets[i]);
			}
		}
		this.motors = motors;
	}
	
	protected E offsetMotorFactory(E baseMotor, int offset) {
		return (E)(new OffsetStateMotor(baseMotor, offset));
	}
	
	public E[] getMotors() {
		return motors;
	}
	
	public void syncMotors() { sync(); }
	public void syncPositions() { sync(); }
	
	public void sync() {
		setPosition(getPosition());
	}
	
	public boolean isSynced(int threshold) {
		int p = getPosition();
		for(E i:getMotors()) {
			if(Math.abs(i.getPosition() - p) > threshold) {
				return false;
			}
		}
		return true;
	}
	
	public int getPosition() {
		int sum = 0;
		for(E i:getMotors()) {
			sum += i.getPosition();
		}
		return (int)Math.round((double)sum / getMotors().length);
	}
	
	public void setPosition(int pos) {
		for(E i:getMotors()) {
			i.setPosition(pos);
		}
	}
}

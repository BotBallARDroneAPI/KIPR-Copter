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

package cbccore.motors.statemotors;

/**
 * 
 * @author Benjamin Woodruff
 *
 */

public abstract class AbstractAdvancedStateMotor implements IAdvancedStateMotor{
	public void setPositionTime(int pos, int ms) {
		setPositionTime(pos, ms / 1000.);
	}
	
	public void setPositionTime(int pos, double sec) {
		setPositionTime(pos, (int)(sec * 1000.));
	}
	
	public void setPositionSpeed(int pos, int ticksPerSec) {
		int ms = Math.abs((pos - getPosition()) * 1000 / ticksPerSec);
		setPositionTime(pos, ms);
	}
	
	public void setPosition(int pos) {
		setPositionSpeed(pos, getDefaultSpeed());
	}
	
	protected abstract int getDefaultSpeed();
}

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

package cbccore.motors.statemotors.offset;

import cbccore.motors.statemotors.IBlockingAdvancedStateMotor;

/**
 * A wrapper for an <code>IBlockingAdvancedStateMotor</code> that is useful for
 * plugging into a <code>ComposedBlockingAdvancedStateMotor</code>.
 * 
 * @author Benjamin Woodruff
 *
 */

public class OffsetBlockingAdvancedStateMotor
             <E extends IBlockingAdvancedStateMotor>
             extends OffsetAdvancedStateMotor<E>
             implements IBlockingAdvancedStateMotor {
	
	public OffsetBlockingAdvancedStateMotor(E baseMotor, int offset) {
		super(baseMotor, offset);
	}
	
	public void setPositionTime(int pos, int ms, boolean blocking) {
		getBaseMotor().setPositionTime(pos - getOffset(), ms, blocking);
	}
	
	public void setPositionTime(int pos, double sec, boolean blocking) {
		getBaseMotor().setPositionTime(pos - getOffset(), sec, blocking);
	}
	
	public void setPositionSpeed(int pos, int speed, boolean blocking) {
		getBaseMotor().setPositionSpeed(pos - getOffset(), speed, blocking);
	}
	
	public void setPosition(int pos, boolean blocking) {
		getBaseMotor().setPosition(pos - getOffset(), blocking);
	}
}

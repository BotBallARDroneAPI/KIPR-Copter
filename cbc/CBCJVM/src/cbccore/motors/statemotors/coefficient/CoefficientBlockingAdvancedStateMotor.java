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

package cbccore.motors.statemotors.coefficient;

import cbccore.motors.statemotors.IBlockingAdvancedStateMotor;

/**
 * A wrapper for an <code>IBlockingAdvancedStateMotor</code> that is useful for
 * plugging into a <code>ComposedBlockingAdvancedStateMotor</code>.
 * 
 * @author Benjamin Woodruff
 *
 */

public class CoefficientBlockingAdvancedStateMotor
             <E extends IBlockingAdvancedStateMotor>
             extends CoefficientAdvancedStateMotor<E>
             implements IBlockingAdvancedStateMotor {
	
	public CoefficientBlockingAdvancedStateMotor(E baseMotor,
	                                             double coefficient) {
		super(baseMotor, coefficient);
	}
	
	public CoefficientBlockingAdvancedStateMotor(E baseMotor,
	                                             double coefficient,
	                                             boolean changeSpeed) {
		super(baseMotor, coefficient, changeSpeed);
	}
	
	public void setPositionTime(int pos, int ms, boolean blocking) {
		getBaseMotor().setPositionTime((int)(pos * getCoefficient()),
		                               (int)(ms / getSpeedCoefficient()),
		                               blocking);
	}
	
	public void setPositionTime(int pos, double sec, boolean blocking) {
		getBaseMotor().setPositionTime((int)(pos * getCoefficient()),
		                               sec / getSpeedCoefficient(), blocking);
	}
	
	public void setPositionSpeed(int pos, int speed, boolean blocking) {
		getBaseMotor().setPositionSpeed((int)(pos * getCoefficient()),
		                                (int)(speed * getSpeedCoefficient()),
		                                blocking);
	}
	
	public void setPosition(int pos, boolean blocking) {
		getBaseMotor().setPosition((int)(pos * getCoefficient()), blocking);
	}
}

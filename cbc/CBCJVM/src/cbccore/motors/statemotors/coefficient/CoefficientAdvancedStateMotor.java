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

import cbccore.motors.statemotors.IAdvancedStateMotor;

/**
 * A wrapper for an <code>IAdvancedStateMotor</code> that is useful for plugging
 * into a <code>ComposedAdvancedStateMotor</code>.
 * 
 * @author Benjamin Woodruff
 *
 */

public class CoefficientAdvancedStateMotor<E extends IAdvancedStateMotor>
             extends CoefficientStateMotor<E> implements IAdvancedStateMotor {
	
	private boolean changeSpeed;
	
	public CoefficientAdvancedStateMotor(E baseMotor, double coefficient) {
		this(baseMotor, coefficient, true);
	}
	
	public CoefficientAdvancedStateMotor(E baseMotor, double coefficient,
	                                     boolean changeSpeed) {
		super(baseMotor, coefficient);
		this.changeSpeed = changeSpeed;
	}
	
	public boolean getChangeSpeed() {
		return changeSpeed;
	}
	
	protected double getSpeedCoefficient() {
		if(getChangeSpeed()) {
			return getCoefficient();
		}
		return 1.;
	}
	
	public void setPositionTime(int pos, int ms) {
		getBaseMotor().setPositionTime((int)(pos * getCoefficient()),
		                               (int)(ms / getSpeedCoefficient()));
	}
	
	public void setPositionTime(int pos, double sec) {
		getBaseMotor().setPositionTime((int)(pos * getCoefficient()),
		                               sec / getSpeedCoefficient());
	}
	
	public void setPositionSpeed(int pos, int speed) {
		getBaseMotor().setPositionSpeed((int)(pos * getCoefficient()),
		                                (int)(speed * getSpeedCoefficient()));
	}
}

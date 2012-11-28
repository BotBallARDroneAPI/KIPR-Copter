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

import cbccore.motors.statemotors.IStateMotor;

/**
 * A wrapper for an <code>IStateMotor</code> that is useful for plugging into a
 * <code>ComposedStateMotor</code>.
 * 
 * @author Benjamin Woodruff
 *
 */

public class CoefficientStateMotor<E extends IStateMotor>
             implements IStateMotor {
	
	private E baseMotor;
	private double coefficient;
	
	public CoefficientStateMotor(E baseMotor, double coefficient) {
		this.baseMotor = baseMotor;
		this.coefficient = coefficient;
	}
	
	public E getBaseMotor() {
		return baseMotor;
	}
	
	public double getCoefficient() {
		return coefficient;
	}
	
	public int getPosition() {
		return (int)(getBaseMotor().getPosition() / getCoefficient());
	}
	
	public void setPosition(int pos) {
		getBaseMotor().setPosition((int)(pos * getCoefficient()));
	}
}

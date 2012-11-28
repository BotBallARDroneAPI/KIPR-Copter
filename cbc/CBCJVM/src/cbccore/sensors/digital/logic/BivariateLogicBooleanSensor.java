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

package cbccore.sensors.digital.logic;

import cbccore.sensors.digital.IBooleanSensor;

/**
 * @author Benjamin Woodruff
 * @see    cbccore.sensors.digital.logic.UnivariateLogicBooleanSensor
 */
public abstract class BivariateLogicBooleanSensor extends LogicBooleanSensor {
	private IBooleanSensor leftSensor;
	private IBooleanSensor rightSensor;
	
	/**
	 * Constructs a new <code>BivariateLogicBooleanSensor</code>
	 * 
	 * @param  leftSensor  The left argument of the boolean expression. (Order
	 *                     doesn't matter for most boolean operations, such as
	 *                     <code>AND</code> or <code>OR</code>, but it can for
	 *                     other operations. See subclasses for more usage
	 *                     information)
	 * @param  rightSensor The right argument of the boolean expression.
	 */
	public BivariateLogicBooleanSensor(IBooleanSensor leftSensor,
	                                   IBooleanSensor rightSensor) {
		this.leftSensor = leftSensor;
		this.rightSensor = rightSensor;
	}
	
	/**
	 * The <code>IBooleanSensor</code> that acts as the left argument for the
	 * boolean expression. (Order doesn't matter for most boolean operations,
	 * such as <code>AND</code> or <code>OR</code>, but it can for other
	 * operations. See subclasses for more usage information)
	 * 
	 * @return  The left argument for the boolean expression
	 * @see     #getRightSensor
	 * @see     #getLeftSensorValue
	 */
	public IBooleanSensor getLeftSensor() {
		return leftSensor;
	}
	
	/**
	 * The <code>IBooleanSensor</code> that acts as the right argument for the
	 * boolean expression. (Order doesn't matter for most boolean operations,
	 * such as <code>AND</code> or <code>OR</code>, but it can for other
	 * operations. See subclasses for more usage information)
	 * 
	 * @return  The left argument for the boolean expression
	 * @see     #getLeftSensor
	 * @see     #getRightSensorValue
	 */
	public IBooleanSensor getRightSensor() {
		return rightSensor;
	}
	
	/**
	 * The value of the left <code>IBooleanSensor</code>
	 * 
	 * @see #getLeftSensor
	 * @see #getRightSensorValue
	 */
	public boolean getLeftSensorValue() {
		return getLeftSensor().getValue();
	}
	
	/**
	 * The value of the right <code>IBooleanSensor</code>
	 * 
	 * @see #getRightSensor
	 * @see #getLeftSensorValue
	 */
	public boolean getRightSensorValue() {
		return getRightSensor().getValue();
	}
}

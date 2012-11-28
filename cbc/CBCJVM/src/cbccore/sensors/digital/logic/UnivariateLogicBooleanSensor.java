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
 * @see    cbccore.sensors.digital.logic.BivariateLogicBooleanSensor
 */
public abstract class UnivariateLogicBooleanSensor extends LogicBooleanSensor {
	IBooleanSensor parent;
	
	/**
	 * Constructs a new <code>UnivariateLogicBooleanSensor</code>
	 * 
	 * @param  parent  The sensor that determines the output of this
	 *                 <code>LogicBooleanSensor</code>.
	 */
	public UnivariateLogicBooleanSensor(IBooleanSensor parent) {
		this.parent = parent;
	}
	
	/**
	 * This is similar to <code>BivariateLogicBooleanSensor</code>'s
	 * <code>getLeftSensor</code> and <code>getRightSensor</code> functions, but
	 * as there is only one determining parent sensor, it is just called the
	 * "parent" <code>IBooleanSensor</code>.
	 * 
	 * @return  The parent <code>IBooleanSensor</code>
	 * @see     cbccore.sensors.digital.logic.BivariateLogicBooleanSensor
	 *              #getLeftSensor
	 * @see     cbccore.sensors.digital.logic.BivariateLogicBooleanSensor
	 *              #getRightSensor
	 * @see     #getSensor
	 */
	public IBooleanSensor getParent() { return this.parent; }
	
	/**
	 * A convenience alias function for <code>getParent</code>.
	 * 
	 * @see #getParent
	 */
	public IBooleanSensor getSensor() { return getParent(); }
	
	/**
	 * A shortcut for extracting the value of the parent
	 * <code>IBooleanSensor</code>.
	 * 
	 * @return  <code>getParent().getValue()</code>
	 */
	public boolean getParentValue() { return getParent().getValue(); }
}

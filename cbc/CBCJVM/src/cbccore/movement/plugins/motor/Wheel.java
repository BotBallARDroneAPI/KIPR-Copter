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

package cbccore.movement.plugins.motor;

import cbccore.motors.Motor;
import cbccore.movement.efficiency.IEfficiencyCalibrator;
import cbccore.movement.efficiency.SingleValueEfficiencyCalibrator;

/**
 * A wheel class used by MotorDriveTrain
 * 
 * @author Benjamin Woodruff
 * @author Jonathan Frias
 */

public class Wheel extends Motor {
	private IEfficiencyCalibrator efficiency;
	private double circumference;
	private double minCmps;
	private double maxCmps;
	private double currentCmps;
	private double cmCount = 0.;
	
	public Wheel(int port, double circumference) {
		this(port, circumference, 1.);
	}
	
	public Wheel(int port, double circumference, double efficiency) {
		this(port, circumference,
		     new SingleValueEfficiencyCalibrator(efficiency));
	}
	
	public Wheel(int port, double circumference,
	             IEfficiencyCalibrator efficiency) {
		super(port);
		this.circumference = circumference;
		this.efficiency = efficiency;
		double baseMaxCmps = getCircumference()
		                     * MotorMovementPlugin.ticksPerRotation
		                     / 1000.; // max is 1000 ticks per second
		this.maxCmps = this.efficiency.getMaxCmps(baseMaxCmps);
		this.minCmps = this.efficiency.getMinCmps(-baseMaxCmps);
	}
	
	/**
	 * Takes centimeters and converts it to ticks, for this wheel.
	 * 
	 * @see #toCm
	 */
	public int toTicks(double centimeters) {
		return (int)(MotorMovementPlugin.ticksPerRotation * centimeters /
		             getCircumference());
	}
	
	/**
	 * Takes ticks and converts it to centimeters, for this wheel.
	 * 
	 * @see #toTicks
	 */
	public double toCm(int ticks) {
		return ticks * getCircumference() /
		       MotorMovementPlugin.ticksPerRotation;
	}
	
	/**
	 * Gets the minimum velocity in centimeters-per-second for the wheel (read:
	 * <code>&lt; 0</code>).
	 */
	public double getMinCmps() {
		return minCmps;
	}
	
	/**
	 * Gets the maximum velocity in centimeters-per-second for the wheel
	 */
	public double getMaxCmps() {
		return maxCmps;
	}
	
	/**
	 * Gets the minimum velocity in ticks-per-second for the wheel (read:
	 * <code>&lt; 0</code>).
	 */
	public int getMinTps() {
		return toTicks(getMinCmps());
	}
	
	/**
	 * Gets the maximum velocity in ticks-per-second for the wheel
	 */
	public double getMaxTps() {
		return toTicks(getMaxCmps());
	}
	
	/**
	 * Gets the current tangential (linear/translational) velocity of the wheel
	 * in centimeters-per-second.
	 */
	public double getCurrentCmps() {
		return currentCmps;
	}
	
	/**
	 * Gets the current tangential (linear/translational) velocity of the wheel
	 * in ticks-per-second.
	 */
	public int getCurrentTps() {
	    return toTicks(getCurrentCmps());
	}
	
	public double getCircumference() {
		return circumference;
	}
	
	public void moveAtTps(int tps) throws IllegalArgumentException {
		moveAtCmps(toCm(tps));
	}
	
	public void moveAtCmps(double cmps) throws IllegalArgumentException {
		cmCount = getCmCounter();
		clearPositionCounter(); //work-around for CBOBv2 motor bug
		super.moveAtVelocity(toTicks(efficiency.translateCmps(cmps)));
		currentCmps = cmps;
	}
	
	/**
	 * Returns the number of ticks that this wheel has moved since it was
	 * constructed.
	 */
	public int getTickCounter() {
		return toTicks(getCmCounter());
	}
	
	/**
	 * Returns the number of centimeters that this wheel has moved since it was
	 * constructed.
	 */
	public double getCmCounter() {
		return cmCount + toCm(getTickCounter());
	}
	
	/**
	 * Depreciated
	 */
	public int moveAtVelocity(int tps) {
		moveAtTps(tps);
		return 0;
	}
}

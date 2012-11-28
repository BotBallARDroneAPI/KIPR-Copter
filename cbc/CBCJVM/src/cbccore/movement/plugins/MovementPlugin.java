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

package cbccore.movement.plugins;

/**
 * The base for a CBCJVM movement library plugin. If you have a new type of
 * chasis, extend this (or one of it's subclasses) and fill in the abstract api
 * stubs.
 * 
 * @author Benjamin Woodruff
 * @see	cbccore.movement.plugins
 * @see	cbccore.movement.plugins.create.CreateMovementPlugin
 * @see	cbccore.movement.DriveTrain
 */

public abstract class MovementPlugin {
	
	private double trainWidth;
	
	/**
	 * When extending, call this as <code>super</code> to initialize this
	 * abstract superclass.
	 * 
	 * @param  trainWidth  The distance between the robot's two wheels in
	 *                     centimeters
	 */
	public MovementPlugin(double trainWidth) {
		this.trainWidth = trainWidth;
	}
	
	/**
	 * Directly move the robot at said speed, called by DriveTrain. You _must_
	 * fill this in. Otherwise the robot will not be able to move.
	 * 
	 * @param  leftCmps   The desired speed of the left wheel in
	 *                        centimeters-per-second
	 * @param  rightCmps  The desired speed of the right wheel in
	 *                        centimeters-per-second
	 */
	public abstract void directDrive(double leftCmps, double rightCmps);
	
	
	
	/**
	 * Just mirrors (calls) <code>freeze()</code>
	 * 
	 * @see	#stop
	 * @see	#kill	
	 */
	public void stop() {
		freeze();
	}
	
	/**
	 * Should lock both the robot's motors if possible, otherwise it should call
	 * <code>kill()</code>
	 * 
	 * @see	#stop
	 * @see	#kill
	 */
	public abstract void freeze();
	
	
	/**
	 * Stops the robot by setting the speed to zero. If a different mechanism is
	 * needed for stopping, you can override this method.
	 * 
	 * @see	#stop
	 * @see	#freeze
	 */
	public void kill() {
		directDrive(0, 0);
	}
	
	/**
	 * Should get the minimum velocity in centimeters-per-second for the right
	 * wheel of the robot. (read: <code>&lt; 0</code>) By default returns the
	 * negative value of <code>getLeftMaxCmps</code>.
	 * 
	 * @return  The speed in cmps
	 * @see     #getLeftMaxCmps
	 * @see     #getRightMinCmps
	 * @see     #getRightMaxCmps
	 */
	public double getLeftMinCmps() {
		return -getLeftMaxCmps();
	}
	
	/**
	 * Should get the maximum velocity in centimeters-per-second for the left
	 * wheel of the robot.
	 * 
	 * @return    The speed in cmps
	 * @see       #getLeftMinCmps
	 * @see       #getRightMaxCmps
	 * @see       #getRightMinCmps
	 */
	public abstract double getLeftMaxCmps();
	
	/**
	 * Should get the minimum velocity in centimeters-per-second for the right
	 * wheel of the robot. (read: <code>&lt; 0</code>) By default returns the
	 * negative value of <code>getRightMaxCmps</code>.
	 * 
	 * @return  The speed in cmps
	 * @see     #getRightMaxCmps
	 * @see     #getLeftMinCmps
	 * @see     #getLeftMaxCmps
	 */
	public double getRightMinCmps() {
		return -getRightMaxCmps();
	}
	
	/**
	 * Should get the maximum velocity in centimeters-per-second for the right
	 * wheel of the robot.
	 * 
	 * @return  The speed in cmps
	 * @see     #getRightMinCmps
	 * @see     #getLeftMaxCmps
	 * @see     #getLeftMinCmps
	 */
	public abstract double getRightMaxCmps();
	
	/**
	 * Gets the distance between the robot's two wheels in centimeters.
	 * 
	 * @return  The distance in cm
	 */
	public double getTrainWidth() {
		return trainWidth;
	}
}

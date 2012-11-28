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

package cbccore.motors;

import cbccore.Device;
import cbccore.InvalidPortException;
import cbccore.motors.statemotors.AbstractBlockingAdvancedStateMotor;

/**
 * Adds a clean API to replace cbccore.low.Motor, and even adds a few minor
 * features & workarounds for known motor controlling issues.
 * 
 * @author Braden McDorman, Benjamin Woodruff
 * @see cbccore.movement.plugins.motor.Wheel
 * 
 */

public class Motor extends AbstractBlockingAdvancedStateMotor {
	private int port = 0;
	private static cbccore.low.Motor lowMotor = Device.getLowMotorController();
	private long destTime = -1;
	
	/**
	 * Constructs a Motor which is used to power the robot. Motors are
	 *  high range (meaning they can rotate an arbitrary amount)
	 *  low torque (meaning they don't have as much movement power)
	 * 
	 * @param  port  The port number that the motor is plugged in to
	 *  
	 */
	public Motor(int port) throws InvalidPortException {
		if(port < 0 || port > 4) throw new InvalidPortException();
		this.port = port;
	}
	
	/**
	 * Set motor speed. It's recommended you use a Back-EMF based function 
	 *  instead. A Back-EMF function is one that reads the voltage return from
	 *  the motor so you can better determine the speed and increase the power
	 *  if neccesary.
	 * 
	 * @param  percent  percent % of full (-100 to 100)
	 * 
	 * @see #forward
	 * @see #backward
	 * @see #moveAtVelocity
	 */
	public void motor(int percent) {
		lowMotor.motor(port, percent);
	}
	
	/**
	 * Clears the position counter of the motor. The position is counted in
	 *  ticks.
	 * 
	 */
	public int clearPositionCounter() {
		return lowMotor.clear_motor_position_counter(port);
	}

	/**
	 * Moves at a velocity in ticks per second
	 * 
	 * @param  velocity  The velocity to move in ticks per second
	 *  (-1000 to 1000)
	 * 
	 */
	public int moveAtVelocity(int velocity) {
		return lowMotor.mav(port, velocity);
	}
	
	/**
	 * Moves to an absolute position in ticks at full speed
	 * 
	 * @param  pos    The goal position to move toward
	 * 
	 */
	public void setPosition(int pos) {
		moveToPosition(1000, pos);
	}
	
	/**
	 * Moves to an absolute position in ticks
	 *
	 * @param  speed  The speed in ticks per second
	 * @param  pos    The goal position to move toward
	 *
	 */
	public void setPositionSpeed(int pos, int speed, boolean blocking) {
		moveToPosition(speed, pos);
		if(blocking) { waitForDone(); }
	}
	
	/**
	 * Moves to an absolute position in ticks
	 *
	 * @param  time   The movement time in milliseconds
	 * @param  pos    The goal position to move toward
	 *
	 */
	public void setPositionTime(int pos, int time, boolean blocking) {
		setPositionSpeed(pos, (pos - getPosition()) * 1000 / time,
		                 blocking);
	}
	
	/**
	 * Moves to an absolute position in ticks
	 *
	 * @param  speed    The speed in ticks per second
	 * @param  goalPos  The goal position to move toward
	 *
	 */
	public int moveToPosition(int speed, int goalPos) {
		setDestTime(speed, goalPos-getPositionCounter());
		return lowMotor.mtp(port, speed, goalPos);
	}

	/**
	 * Moves to a relative position in ticks
	 *
	 * @param  speed     The speed in ticks per second
	 * @param  deltaPos  The relative goal position in ticks to move toward
	 *
	 */
	public int moveRelativePosition(int speed, int deltaPos) {
		setDestTime(speed, deltaPos);
		return lowMotor.mrp(port, speed, deltaPos);
	}
	
	//a helper method
	private void setDestTime(int speed, int deltaPos) {
		destTime = System.currentTimeMillis() + Math.abs(deltaPos*1000/speed);
	}
	
	/**
	 * A safer "blockMotorDone()", does not present the possiblity of a program
	 * locking up because a motor might get stuck. The only downside is that a
	 * motor might not have finished it's movements by the time the function has
	 * returned. Might return before the motor has actually stopped moving. If
	 * you want to ensure if has stopped, you can call <code>off()</code> or
	 * <code>freeze()</code>.
	 * 
	 * @see     #blockMotorDone
	 * @see     #moveToPosition
	 * @see     #moveRelativePosition
	 * @see     #off
	 * @see     #freeze
	 */
	public void waitForDone() {
		long time = destTime-System.currentTimeMillis();
		if(time > 0l) {
			try {
				Thread.sleep(time);
			} catch (Exception e) { return; }
		}
	}
	
	public void setPidGains(int p, int i, int d, int pd, int id, int dd) {
		lowMotor.set_pid_gains(port, p, i, d, pd, id, dd);
	}

	/**
	 * Actively attempts to keep the motor at the current position
	 *  (Warning: continues to draw current)
	 *  Imagine the motors are your legs, <code>freeze()</code> is you
	 *  attempting to stand in place and resist someone pushing you.
	 *
	 * @see #off
	 *
	 */
	public int freeze() {
		return lowMotor.freeze(port);
	}

	/**
	 * Checks if the motor is moving toward a goal.
	 *
	 * @return  moving  True: The motor is moving toward a goal, False: It isn't
	 */
	public boolean getDone() {
		return lowMotor.get_motor_done(port)!=0;
	}

    /**
     * Checks the motor position
     *
     * @return  position  The motor position in ticks (to +/-2147483647)
     */
	public int getPositionCounter() {
		return lowMotor.get_motor_position_counter(port);
	}
	
	/**
     * Checks the motor position
     *
     * @return  position  The motor position in ticks (to +/-2147483647)
     */
	public int getPosition() {
		return getPositionCounter();
	}
	
    /**
     * Stops until the motor is done moving to it's goal.
     */
	public void blockMotorDone() {
		lowMotor.bmd(port);
	}

    /**
     * <code>motor()</code> only from (+/-255).
     *
     * @param  pwm  The the motor power (+/-255)
     * @see    #motor
     * @see    #getPwm
     */
	public int setPwm(int pwm) {
		return lowMotor.setpwm(port, pwm);
	}

    /**
     * Checks the current motor power.
     *
     * @return  pwm  Returns the current pwm setting (+/-255)
     * @see     #setPwm
     */
	public int getPwm() {
		return lowMotor.getpwm(port);
	}

    /**
     * Moves the motor forward at full power. Not a Back-EMF function.<p>
     * 
     * A Back-EMF fuction such as <code>moveAtVelocity(tps)</code> is
     * recommended.
     *
     * @see #moveAtVelocity
     * @see #backward
     */
	public void forward() {
		lowMotor.fd(port);
	}
	
	/**
     * Moves the motor backward at full power. Not a Back-EMF function.<p>
     * 
     * A Back-EMF fuction such as <code>moveAtVelocity(tps)</code> is
     * recommended.
     *
     * @see #moveAtVelocity
     * @see #forward
     */
	public void backward() {
		lowMotor.bk(port);
	}
	
	/**
	 * Cut power to this motor
	 */
	public void off() {
		lowMotor.off(port);
	}
	
	/**
	 * Turn off all motors
	 */
	public static void allOff() {
		lowMotor.ao();
	}
	
	/**
	 * An alias for <code>allOff</code>
	 * 
	 * @see #allOff
	 */
	public static void disableAll() {
		allOff();
	}
	
	/**
	 * @see #freeze
	 */
	public static void allFreeze() {
		for(int i = 0; i < 4; ++i) {
			lowMotor.freeze(i);
		}
	}
	
	/**
	 * The default speed is half of maximum (500 ticks per second)
	 */
	public int getDefaultSpeed() {
		return 1000/2;
	}
}

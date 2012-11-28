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

import java.util.ArrayList;

import cbccore.Device;
import cbccore.InvalidPortException;
import cbccore.motors.statemotors.AbstractBlockingAdvancedStateMotor;

/**
 * 
 * @author Benjamin Woodruff, Braden McDorman
 *
 */

public class Servo extends AbstractBlockingAdvancedStateMotor {
	private int port = 0;
	private static cbccore.low.Servo lowServo = Device.getLowServoController();
	
	// variables for advanced motion
	private long beginTime = 0;
	private int ms = 0;
	private int deltaPos = 0;
	private int startPos = 0;
	private boolean moving = false;
	private int timingCoefficient = 500; // approx millisecs for full sweep
	
	/**
	 * Create a new servo object in the desired port
	 * @param  port  The port that the desired servo is plugged into
	 */
	public Servo(int port) throws InvalidPortException {
		if(port < 0 || port > 4) throw new InvalidPortException();
		this.port = port;
	}
	
	/**
	 * Cuts power to the servo
	 */
	public void disable() {
		lowServo.set_servo_position(port, -1);
	}
	
	/**
	 * Sets the servo to the middle position, thereby giving it power, unless it
	 * is already enabled/powered
	 */
	public void enable() {
		if(!isEnabled()) {
			setPosition((getMinPosition() + getMaxPosition()) / 2);
		}
	}
	
	/**
	 * Returns true if there is power being supplied to the servo, false
	 * otherwise
	 */
	public boolean isEnabled() {
		return getPosition() >= 0;
	}
	
	/**
	 * Cuts power to all the servos
	 */
	public static void disableAll() {
		lowServo.disable_servos();
	}
	
	/**
	 * An alias for <code>disableAll</code>
	 * 
	 * @see #disableAll
	 */
	public static void allOff() {
		disableAll();
	}
	
	/**
	 * Enables all the servos by setting them to their middle/center positions,
	 * unless they are already enabled, in which case it leaves them alone.
	 */
	public static void enableAll() {
		lowServo.enable_servos();
	}
	
	/**
	 * An alias for <code>enableAll</code>
	 * 
	 * @see #enableAll
	 */
	public static void allOn() {
		enableAll();
	}
	
	/**
	 * Gets the current servo's position.
	 * 
	 * @return  -1 if the servo is disabled, otherwise the current position.
	 */
	public int getPosition() {
		return lowServo.get_servo_position(port);
	}
	
	/**
	 * Move the Servo to a specified position.
	 * 
	 * @param  pos  The position value from 0 to 2048 to move to
	 */
	public void setPosition(int pos) {
		rawSetPosition(pos);
		moving = false;
	}
	
	/**
	 * Change the position of the servo without touching the isMoving value
	 */
	protected void rawSetPosition(int pos) {
		if(pos < getMinPosition() || pos > getMaxPosition()) {
			throw new IllegalArgumentException("Position: " + pos +
			                                   " is out of range");
		}
		lowServo.set_servo_position(port, pos);
	}
	
	/**
	 * Moves the servo to the desired position, waiting for it to finish moving
	 * before stopping.<p>
	 * 
	 * <b>Implementation Note:</b> As we have no api for actually determining
	 * when a servo is done moving, an forumula respecting the distance to be
	 * traveled is used to approximate the time, and then the function sleeps
	 * for that desired time.
	 * 
	 * @param  pos  The position value from 0 to 2048 to move to
	 */
	public void setPosition(int pos, boolean blocking) {
		rawSetPosition(pos);
		moving = true;
		try {
			Thread.sleep(Math.abs(pos - getPosition()) * timingCoefficient
			             / getMaxPosition());
		} catch(InterruptedException ex) {
			// do nothing
		}
		moving = false;
	}
	
	/**
	 * Returns a boolean that tells if the servo is moving or not.
	 * 
	 * @return  True is moving, false is not moving
	 */
	public boolean isMoving() {
		return moving;
	}
	
	/**
	 * Moves to a new servo position in a designated amount of time in
	 * milliseconds. The speed of the movement is simulated by running quickly
	 * changing the motor positions to intermediate places over time.
	 * 
	 * @param  ms      the allotted amount of time to move
	 * @param  newPos  the new servo position
	 */
	public void setPositionTime(int newPos, int ms, boolean blocking) {
		if(!isEnabled()) {
			setPosition(newPos);
			if(blocking) {
				try {
					Thread.sleep(ms);
				} catch(InterruptedException ex) {
					return;
				}
			}
			return;
		}
		startPos = getPosition();
		deltaPos = newPos - startPos;
		if(deltaPos == 0) {
			return;
		}
		beginTime = System.currentTimeMillis();
		moving = true;
		this.ms = ms;
		if(!blocking) {
			ServoThread.get().addServo(this);
		} else {
			while(isMoving()) {
				update();
				Thread.yield();
			}
		}
	}
	
	/**
	 * Do not use.
	 */
	public void update() {
		if(!moving) {
			return;
		}
		int time = (int)(System.currentTimeMillis() - beginTime);
		if(time > ms) {
			rawSetPosition(startPos + deltaPos);
			moving = false;
			return;
		}
		
		int y = (int)(deltaPos * time / ms + startPos);
		
		if((deltaPos > 0 && y > startPos + deltaPos) ||
		   (deltaPos < 0 && y < startPos + deltaPos)) {
			y = startPos + deltaPos;
			moving = false;
		}
		rawSetPosition(y);
	}
	
	/**
	 * Needed to extend <code>AbstractBlockingAdvancedStateMotor</code>. It
	 * makes little sense in this context.
	 * 
	 * @return  Some really big number.
	 */
	public int getDefaultSpeed() {
		return 100000;
	}
	
	/**
	 * Gives the minimum rotational position that the the servo can move to.
	 * 
	 * @return  Zero. Always zero. Zip. Nothing. Nada. 0.
	 */
	public int getMinPosition() {
		return 0;
	}
	
	/**
	 * Gives the maximum rotational position that the the servo can move to.
	 * 
	 * @return  2048
	 */
	public int getMaxPosition() {
		return 2048;
	}
	
	/**
	 * The port that the servo that this object is addressing should be plugged
	 * into.
	 */
	public int getPort() {
		return port;
	}
	
	private static class ServoThread extends Thread {
		public static ServoThread get() {
			if (instance == null) {
				instance = new ServoThread();
				instance.start();
			}
			return instance;
		}
		
		private ArrayList<Servo> servos = new ArrayList<Servo>();
		
		private boolean exit = false;
		
		private static ServoThread instance = null;
		
		public ServoThread() {
			setDaemon(true);
		}
		
		public void addServo(Servo servo) {
			synchronized(servos) {
				servos.add(servo);
			}
		}
		
		public void exit() {
			exit = true;
		}
		
		@Override
		public void run() {
			ArrayList<Servo> removes = new ArrayList<Servo>();
			while (!exit) {
				removes.clear();
				synchronized(servos) {
					for(Servo s: servos) {
						s.update();
						if(!s.isMoving()) {
							removes.add(s);
						}
					}
					servos.removeAll(removes);
				}
			}
		}
	}
}

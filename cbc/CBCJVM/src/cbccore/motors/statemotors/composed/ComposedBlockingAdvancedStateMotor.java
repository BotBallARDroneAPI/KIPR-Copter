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

package cbccore.motors.statemotors.composed;

import cbccore.motors.statemotors.IBlockingAdvancedStateMotor;
import cbccore.motors.statemotors.offset.OffsetBlockingAdvancedStateMotor;

/**
 * 
 * @author Benjamin Woodruff
 *
 */

public class ComposedBlockingAdvancedStateMotor
             <E extends IBlockingAdvancedStateMotor>
             extends ComposedAdvancedStateMotor<E>
             implements IBlockingAdvancedStateMotor {
	
	public ComposedBlockingAdvancedStateMotor(E ... motors) {
		super(motors);
	}
	
	public ComposedBlockingAdvancedStateMotor(E[] motors, int ... offsets) {
		super(motors, offsets);
	}
	
	protected E offsetMotorFactory(E baseMotor, int offset) {
		return (E)(new OffsetBlockingAdvancedStateMotor(baseMotor, offset));
	}
	
	public void setPositionTime(int pos, int ms, boolean blocking) {
		BlockingMotorRunnable[] runners = getRunnerArray();
		for(int i = 0; i < getMotors().length; ++i) {
			runners[i] = new SetPositionTimeMillisecondsAction(
				getMotors()[i], pos, ms, blocking
			);
		}
		waitForRunners(runners, blocking);
	}
	
	public void setPositionTime(int pos, double sec, boolean blocking) {
		BlockingMotorRunnable[] runners = getRunnerArray();
		for(int i = 0; i < getMotors().length; ++i) {
			runners[i] = new SetPositionTimeSecondsAction(
				getMotors()[i], pos, sec, blocking
			);
		}
		waitForRunners(runners, blocking);
	}
	
	public void setPositionSpeed(int pos, int speed, boolean blocking) {
		BlockingMotorRunnable[] runners = getRunnerArray();
		for(int i = 0; i < getMotors().length; ++i) {
			runners[i] = new SetPositionSpeedAction(
				getMotors()[i], pos, speed, blocking
			);
		}
		waitForRunners(runners, blocking);
	}
	
	public void setPosition(int pos, boolean blocking) {
		BlockingMotorRunnable[] runners = getRunnerArray();
		for(int i = 0; i < getMotors().length; ++i) {
			runners[i] = new SetPositionAction(
				getMotors()[i], pos, blocking
			);
		}
		waitForRunners(runners, blocking);
	}
	
	private BlockingMotorRunnable[] getRunnerArray() {
		return new BlockingMotorRunnable[getMotors().length];
	}
	
	protected void waitForRunners(BlockingMotorRunnable[] runners,
	                              boolean blocking) {
		if(blocking) {
			Thread[] threads = new Thread[runners.length];
			for(int i = 0; i < runners.length; ++i) {
				threads[i] = new Thread(runners[i]);
				threads[i].start();
			}
			for(Thread t: threads) {
				while(t.isAlive()) {
					Thread.yield();
				}
			}
		} else {
			for(BlockingMotorRunnable i: runners) {
				i.run();
			}
		}
	}
	
	protected static abstract class BlockingMotorRunnable
	                                <E extends IBlockingAdvancedStateMotor>
	                                implements Runnable {
		private E motor;
		private boolean blocking;
		
		protected BlockingMotorRunnable(E motor, boolean blocking) {
			this.motor = motor;
		}
		
		public E getMotor() {
			return motor;
		}
		
		public boolean isBlocking() {
			return blocking;
		}
		
		public void run() {
			doAction();
		}
		
		protected abstract void doAction();
		
	}
	
	protected static class SetPositionAction extends BlockingMotorRunnable {
		private int position;
		
		public SetPositionAction(IBlockingAdvancedStateMotor motor,
		                         int position, boolean blocking) {
			super(motor, blocking);
			this.position = position;
		}
		
		protected int getPosition() {
			return position;
		}
		
		protected void doAction() {
			getMotor().setPosition(getPosition(), isBlocking());
		}
	}
	
	protected static class SetPositionTimeMillisecondsAction
	                       extends SetPositionAction {
		private int ms;
		
		public SetPositionTimeMillisecondsAction(
		       IBlockingAdvancedStateMotor motor, int ms, int position,
		       boolean blocking) {
			super(motor, position, blocking);
			this.ms = ms;
		}
		
		protected void doAction() {
			getMotor().setPositionTime(getPosition(), ms, isBlocking());
		}
	}
	
	protected static class SetPositionTimeSecondsAction
	                       extends SetPositionAction {
		private double secs;
		
		public SetPositionTimeSecondsAction(IBlockingAdvancedStateMotor motor,
		                                    int position, double secs,
		                                    boolean blocking) {
			super(motor, position, blocking);
			this.secs = secs;
		}
		
		protected void doAction() {
			getMotor().setPositionTime(getPosition(), secs, isBlocking());
		}
	}
	
	protected static class SetPositionSpeedAction extends SetPositionAction {
		private int speed;
		
		public SetPositionSpeedAction(IBlockingAdvancedStateMotor motor,
		                              int speed, int position,
		                              boolean blocking) {
			super(motor, position, blocking);
			this.speed = speed;
		}
		
		protected void doAction() {
			getMotor().setPositionSpeed(getPosition(), speed, isBlocking());
		}
	}
}

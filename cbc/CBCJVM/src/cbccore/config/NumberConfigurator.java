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

package cbccore.config;

import cbccore.sensors.digital.IBooleanSensor;
import cbccore.sensors.buttons.UpButton;
import cbccore.sensors.buttons.DownButton;
import cbccore.sensors.buttons.AButton;

/**
 * @author Benjamin Woodruff
 */

public class NumberConfigurator extends AbstractConfigurator {
	private IBooleanSensor increment, decrement, select;
	private int min, max, step, start;
	
	public NumberConfigurator() {
		this(new UpButton(), new DownButton(), new AButton());
	}
	
	public NumberConfigurator(IBooleanSensor increment,
	                          IBooleanSensor decrement, IBooleanSensor select) {
		this(increment, decrement, select, Integer.MIN_VALUE,
		     Integer.MAX_VALUE);
	}
	
	public NumberConfigurator(int min, int max) {
		this(new UpButton(), new DownButton(), new AButton(), min, max);
	}
	
	public NumberConfigurator(IBooleanSensor increment,
	                          IBooleanSensor decrement, IBooleanSensor select,
	                          int min, int max) {
		this(increment, decrement, select, min, max, 1);
	}
	
	public NumberConfigurator(int min, int max, int step) {
		this(new UpButton(), new DownButton(), new AButton(), min, max, step);
	}
	
	public NumberConfigurator(IBooleanSensor increment,
	                          IBooleanSensor decrement, IBooleanSensor select,
	                          int min, int max, int step) {
		this(increment, decrement, select, min, max, step, 0);
	}
	
	public NumberConfigurator(int min, int max, int step, int start) {
		this(new UpButton(), new DownButton(), new AButton(), min, max, step,
		     start);
	}
	
	public NumberConfigurator(IBooleanSensor increment,
	                          IBooleanSensor decrement, IBooleanSensor select,
	                          int min, int max, int step, int start) {
		this.increment = increment;
		this.decrement = decrement;
		this.select = select;
		this.min = min;
		this.max = max;
		this.step = step;
		this.start = start;
	}
	
	@Override
	public int ask() {
		IBooleanSensor[] buttons = {increment, decrement, select};
		int state = start;
		IBooleanSensor pressed = null;
		printState(state);
		while(true) {
			pressed = waitForInput(buttons);
			if(pressed == increment) {
				if(state < max) {
					state += step;
				}
			} else if(pressed == decrement) {
				if(state > min) {
					state -= step;
				}
			} else {
				return state;
			}
			clearScreen();
			printState(state);
		}
	}
	
	private void clearScreen() {
		for(int i = 0; i < 5; ++i) {
			System.out.println();
		}
	}
	
	private void printState(int state) {
		if(state < max) {
			System.out.println("+ Press " + increment + " to increase by " +
			                   step);
		}
		if(state > min) {
			System.out.println("- Press " + decrement + " to decrease by " +
			                   step);
		}
		System.out.println("o Press " + select + " to select");
		System.out.println("Number: " + state);
	}
}

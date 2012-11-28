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

import java.util.HashMap;
import java.util.Iterator;
import java.util.Set;

import cbccore.sensors.digital.IBooleanSensor;

/**
 * @author Braden McDorman, Benjamin Woodruff
 */

public class ChoiceConfigurator extends AbstractConfigurator {
	private Choices choices;
	private IBooleanSensor[] sensors;
	
	public ChoiceConfigurator(IBooleanSensor[] sensors, Choices choices) {
		this.choices = choices;
		this.sensors = sensors;
	}
	
	@Override
	public int ask() {
		HashMap<IBooleanSensor, Integer> elements = new HashMap<IBooleanSensor, Integer>();
		int i = 0;
		for(IBooleanSensor sensor : sensors) {
			elements.put(sensor, (Integer) choices.keySet().toArray()[i++]);
			if(i > choices.size() - 1) break;
		}
		
		Iterator<IBooleanSensor> it = elements.keySet().iterator();
		while(it.hasNext()) {
			IBooleanSensor sensor = it.next();
			System.out.println("Press " + sensor + " to " + choices.get(elements.get(sensor)));
		}
		IBooleanSensor sensor = waitForInput(elements.keySet());
		return elements.get(sensor);
	}
}

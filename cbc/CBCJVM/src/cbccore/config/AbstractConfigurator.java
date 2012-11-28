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

import java.util.Set;
import cbccore.sensors.digital.IBooleanSensor;

/**
 * @author Braden McDorman, Benjamin Woodruff
 */

public abstract class AbstractConfigurator implements Configurator {
	
	protected IBooleanSensor waitForInput(IBooleanSensor... sensors) {
		while(true) {
			for(IBooleanSensor s: sensors) {
				if(s.getValue()) {
					while(s.getValue()) {
						try {
							Thread.yield();
						} catch(Exception ex) {}
					}
					return s;
				}
				try {
					Thread.yield();
				} catch(Exception ex) {}
			}
		}
	}
	
	protected IBooleanSensor waitForInput(Set<IBooleanSensor> sensors) {
		return waitForInput(
			sensors.toArray(new IBooleanSensor[sensors.size()])
		);
	}
}

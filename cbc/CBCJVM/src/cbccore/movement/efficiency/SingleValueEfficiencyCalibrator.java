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

package cbccore.movement.efficiency;

public class SingleValueEfficiencyCalibrator implements IEfficiencyCalibrator {
	
	private double efficiency;
	
	public SingleValueEfficiencyCalibrator(double efficiency) {
		this.efficiency = efficiency;
	}
	
	public double translateCmps(double oldCmps) {
		return oldCmps / efficiency;
	}
	
	public double getMaxCmps(double oldMaxCmps) {
		return oldMaxCmps * efficiency;
	}
	
	public double getMinCmps(double oldMinCmps) {
		return oldMinCmps * efficiency;
	}
}

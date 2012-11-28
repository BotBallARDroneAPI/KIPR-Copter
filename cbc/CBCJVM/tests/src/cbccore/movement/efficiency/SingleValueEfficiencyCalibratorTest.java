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

import org.testng.annotations.Test;
import java.util.Random;

/*
 * @author Benjamin Woodruff
 */
public class SingleValueEfficiencyCalibratorTest {
	private Random rand = new Random();
	private SingleValueEfficiencyCalibrator lowCalibration =
	        new SingleValueEfficiencyCalibrator(.9);
	private SingleValueEfficiencyCalibrator simpleCalibration =
	        new SingleValueEfficiencyCalibrator(1.);
	private SingleValueEfficiencyCalibrator highCalibration =
	        new SingleValueEfficiencyCalibrator(1.1);
	private SingleValueEfficiencyCalibrator[] variousCalibrations =
	        new SingleValueEfficiencyCalibrator[100];
	
	public SingleValueEfficiencyCalibratorTest() {
		for(int i = 0; i < variousCalibrations.length; i++) {
			variousCalibrations[i] = new SingleValueEfficiencyCalibrator(
				0.7 + 0.6 * ((double)i) / variousCalibrations.length
			);
		}
	}
	
	@Test
	public void signMatchesTest() {
		for(SingleValueEfficiencyCalibrator i: variousCalibrations) {
			assert i.getMaxCmps(rand.nextDouble() * 500. + 0.01) > 0;
			assert i.getMinCmps(-rand.nextDouble() * 500. - 0.01) < 0;
			assert i.translateCmps(rand.nextDouble() * 500. + 0.01) > 0;
			assert i.translateCmps(-rand.nextDouble() * 500. - 0.01) < 0;
			assert Math.abs(i.translateCmps(0.)) < 0.001;
		}
	}
	
	@Test
	public void efficiencyTest() {
		assert lowCalibration.getEfficiencyAt(
			rand.nextDouble() * 500. + 0.01
		) < 1.;
		assert Math.abs(simpleCalibration.getEfficiencyAt(
			rand.nextDouble() * 500. + 0.01
		) - 1.) < .001;
		assert highCalibration.getEfficiencyAt(
			rand.nextDouble() * 500. + 0.01
		) > 1.;
	}
}

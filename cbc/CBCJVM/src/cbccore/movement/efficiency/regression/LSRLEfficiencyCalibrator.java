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

package cbccore.movement.efficiency.regression;

/**
 * Uses a Least-Squares Regression Line to solve for efficiency. (A simple
 * linear regression model)
 */
public class LSRLEfficiencyCalibrator extends BaseLSRLEfficiencyCalibrator {
	
	private double slope;
	private double invSlope;
	private double intercept;
	private double invIntercept;
	
	/**
	 * Generates a LSRL through the given points of data.
	 */
	public LSRLEfficiencyCalibrator(double[] target, double[] actual) {
		super(target, actual);
	}
	
	/**
	 * Generates a LSRL from given slope and intercept data. The r-value is set
	 * to <code>null</code>.
	 */
	public LSRLEfficiencyCalibrator(double slope, double intercept) {
		super(slope, intercept);
	}
	
	/**
	 * Generates a LSRL from given slope, intercept, and r-value.
	 */
	public LSRLEfficiencyCalibrator(double slope, double intercept,
	                                double rValue) {
		super(slope, intercept, rValue);
	}
	
	/**
	 * @return  The slope of the regression line.
	 */
	public double getSlope() {
		return getBaseSlope();
	}
	
	/**
	 * @return  The y-intercept of the regression line.
	 */
	public double getIntercept() {
		return getBaseIntercept();
	}
	
	public String toString() {
		return "new LSRLEfficiencyCalibrator(" + getSlope() + ", " +
		       getIntercept() + ", " + getRValue() + ");";
	}
}

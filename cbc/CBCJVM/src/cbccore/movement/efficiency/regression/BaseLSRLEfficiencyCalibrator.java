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
 * Not intended to be used directly, but rather overridden by other classes
 * using a LSRL as their mathematical base. In these overriding classes, you
 * will most likely want to override <code>translateCmps</code> and
 * <code>inverseTranslateCmps</code>.<p/>
 * 
 * Unlike <code>LSRLEfficiencyCalibrator</code>, this class does not publicly
 * expose the slope and intercept information.
 */
public abstract class BaseLSRLEfficiencyCalibrator
                      extends AbstractRegressionEfficiencyCalibrator {
	
	private double slope, invSlope, intercept, invIntercept, rValue;
	
	/**
	 * Generates a LSRL through the given points of data.
	 */
	public BaseLSRLEfficiencyCalibrator(double[] target, double[] actual) {
		this(findSlope(target, actual), findIntercept(target, actual),
		     findRValue(target, actual));
	}
	
	/**
	 * Generates a LSRL from given slope and intercept data. The r-value is set
	 * to <code>NaN</code>.
	 */
	public BaseLSRLEfficiencyCalibrator(double slope, double intercept) {
		this(slope, intercept, Double.NaN);
	}
	
	/**
	 * Generates a LSRL from given slope, intercept, and r-value.
	 */
	public BaseLSRLEfficiencyCalibrator(double slope, double intercept,
	                                    double rValue) {
		this.slope = slope;
		this.intercept = intercept;
		this.rValue = rValue;
		invSlope = -1./slope;
		invIntercept = intercept * invSlope;
	}
	
	private static double findMean(double ... data) {
		double sum = 0.;
		for(double i: data) {
			sum += i;
		}
		return sum / data.length;
	}
	
	private static double findStdDev(double ... data) {
		double mean = findMean(data);
		double sum = 0;
		for(double i: data) {
			sum += Math.abs(mean - i);
		}
		return sum / (data.length - 1);
	}
	
	private static double findSlope(double[] x, double[] y) {
		return findStdDev(y) / findStdDev(x);
	}
	
	private static double findIntercept(double[] x, double[] y) {
		return findMean(y) - findMean(x) * findSlope(x, y);
	}
	
	private static double findRValue(double[] x, double[] y) {
		double sum = 0.;
		double xMean = findMean(x); double yMean = findMean(y);
		double xStdDev = findStdDev(x); double yStdDev = findStdDev(y);
		for(int i = 0; i < x.length; ++i) {
			sum += (x[i] - xMean) * (y[i] - yMean) / xStdDev / yStdDev;
		}
		return sum / (x.length - 1);
	}
	
	/**
	 * @return  The slope of the regression line.
	 */
	protected double getBaseSlope() {
		return slope;
	}
	
	/**
	 * @return  The slope of the inverse of the LSRL.
	 */
	protected double getBaseInverseSlope() {
		return invSlope;
	}
	
	/**
	 * @return  The y-intercept of the regression line.
	 */
	protected double getBaseIntercept() {
		return intercept;
	}
	
	/**
	 * @return  The y-intercept of the inverse of the LSRL.
	 */
	protected double getBaseInverseIntercept() {
		return invIntercept;
	}
	
	/**
	 * Gets the Pearson product-moment correlation coefficient, or "r" value.
	 * The value is from -1 to 1. A high magnitude (close to -1 or 1) means a
	 * strong correlation. A value close to zero means a weak correlation. You
	 * want a high r-value.
	 * 
	 * @return  The r-value if it is defined for this LSRL, otherwise
	 *           <code>NaN</code>.
	 */
	public double getRValue() {
		return rValue;
	}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public double translateCmps(double oldCmps) {
		return oldCmps * slope + intercept;
	}
	
	/**
	 * @inheritDoc
	 */
	@Override
	public double inverseTranslateCmps(double cmps) {
		return cmps * invSlope + invIntercept;
	}
}

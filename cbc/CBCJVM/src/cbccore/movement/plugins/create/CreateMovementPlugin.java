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

package cbccore.movement.plugins.create;

import cbccore.create.Create;
import cbccore.create.CreateConnectException;
import cbccore.movement.plugins.MovementPlugin;
import cbccore.movement.efficiency.IEfficiencyCalibrator;
import cbccore.movement.efficiency.SingleValueEfficiencyCalibrator;

/**
 * A DriveTrain class for the iRobot Create
 * 
 * @author Benjamin Woodruff
 */

public class CreateMovementPlugin extends MovementPlugin {
	
	private static final double DEFAULT_TRAIN_WIDTH = 25.5;
	//private static final double wheelCircumference = 10.;
	private IEfficiencyCalibrator leftEfficiency;
	private IEfficiencyCalibrator rightEfficiency;
	//private double leftCmps = 0.;
	//private double rightCmps = 0.;
	private Create create = null;
	
	public CreateMovementPlugin(Create create) throws CreateConnectException {
		this(create, 1., 1.);
	}
	
	public CreateMovementPlugin(Create create, double leftEfficiency,
	                            double rightEfficiency)
	                            throws CreateConnectException {
		this(create, new SingleValueEfficiencyCalibrator(leftEfficiency),
		     new SingleValueEfficiencyCalibrator(rightEfficiency));
	}
	
	public CreateMovementPlugin(Create create,
	                            IEfficiencyCalibrator leftEfficiency,
	                            IEfficiencyCalibrator rightEfficiency)
	                            throws CreateConnectException {
		this(create, leftEfficiency, rightEfficiency, false);
	}
	
	public CreateMovementPlugin(Create create,
	                            IEfficiencyCalibrator leftEfficiency,
	                            IEfficiencyCalibrator rightEfficiency,
	                            boolean fullMode)
	                            throws CreateConnectException {
		this(create, leftEfficiency, rightEfficiency, DEFAULT_TRAIN_WIDTH,
		     fullMode);
	}
	
	public CreateMovementPlugin(Create create,
	                            IEfficiencyCalibrator leftEfficiency,
	                            IEfficiencyCalibrator rightEfficiency,
	                            double trainWidth, boolean fullMode)
	                            throws CreateConnectException {
		super(trainWidth);
		this.create = create;
		create.connect();
		this.leftEfficiency = leftEfficiency;
		this.rightEfficiency = rightEfficiency;
		setFullMode(fullMode);
	}
	
	public void setFullMode(boolean fullMode) {
		if(fullMode) {
			create.setMode(Create.Mode.Full); 
		} else {
			create.setMode(Create.Mode.Safe); 
		}
	}
	
	public void setSafeMode(boolean safeMode) {
		setFullMode(!safeMode);
	}
	
	public boolean isFullMode() {
		return create.getMode() == Create.Mode.Full;
	}
	
	public boolean isSafeMode() {
		return create.getMode() == Create.Mode.Safe;
	}
	
	/** {@inheritDoc} */
	public void directDrive(double leftCmps, double rightCmps) {
		// As a note: create.driveDirect oddly takes right first then left
		create.driveDirect(
			(int)(rightEfficiency.translateCmps(rightCmps) * 10.),
			(int)(leftEfficiency.translateCmps(leftCmps) * 10.)
		);
	}
	
	/**
	 * The create has no freeze api. So this essentially calls <code>kill()</code>
	 * 
	 * @see      #kill
	 */
	public void freeze() {
		kill(); //no such api
	}
	
	/** {@inheritDoc} */
	public double getLeftMinCmps() {
		return leftEfficiency.getMinCmps(-50.);
	}
	
	/** {@inheritDoc} */
	public double getRightMinCmps() {
		return rightEfficiency.getMinCmps(-50.);
	}
	
	/** {@inheritDoc} */
	public double getLeftMaxCmps() {
		return leftEfficiency.getMaxCmps(50.);
	}
	
	/** {@inheritDoc} */
	public double getRightMaxCmps() {
		return rightEfficiency.getMaxCmps(50.);
	}
}

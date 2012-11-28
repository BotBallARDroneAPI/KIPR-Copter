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

package cbccore.low.simulator;

import cbccore.display.SimulatedFramebuffer;
import cbccore.low.*;

import javax.swing.JFrame;
import javax.swing.JScrollPane;
import javax.swing.JLabel;
import javax.swing.UIManager;

import java.awt.BorderLayout;
import java.awt.Container;
import java.awt.ComponentOrientation;
import java.awt.FlowLayout;
import java.awt.GridLayout;
import java.awt.Dimension;
import java.awt.Toolkit;

import java.io.PrintStream;

/**
 * Do not instanciate this class. It will automatically be created the first
 * time a CBCJVM API method and/or class is used. It is handled by
 * cbccore.Device
 * 
 * @author Benjamin Woodruff, Braden McDorman
 */

public class CBCSimulator extends Simulator {
	
	public SimulatedCBOB cbob;
	
	//sidebar things
	Container sidebar = new Container();
	Container sidebarMotors = new Container();
	JLabel[] motorSpeedLabels = new JLabel[8];
	private boolean framebuffersAdded = false;
	
	//Main text area stuff
	public static PrintStream stdOut;
	
	//Root frame
	private JFrame frame = new JFrame("CBCJVM-Simulator-11.2-devel");
	
	public CBCSimulator() {
		
		super(new SimulatedSound(), new SimulatedSensor(),
		      new SimulatedDevice(), new SimulatedDisplay(),
		      new SimulatedInput(), new SimulatedServo(), new SimulatedMotor(),
		      new SimulatedCamera(), new SimulatedCreate());
		
		//create simulated devices, to replace CBC methods
		cbob = new SimulatedCBOB();
		((SimulatedMotor)getMotor()).setCbob(cbob);
		for(int i = 0; i < motorSpeedLabels.length; ++i) {
			motorSpeedLabels[i] = new JLabel();
		}
		
		//Blend in with Native look
		try {
			UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		} catch(Exception e) {
			System.out.println("Error setting native LAF: " + e);
		}
		
		//stdOut: redirect System.out.println to the builtin console
		if(stdOut == null) { stdOut = System.out; }
		System.out.println("Welcome to CBCJava");
		frame.getContentPane().add(
		    new JScrollPane(((SimulatedDisplay)getDisplay()).getTextBox()),
		    BorderLayout.CENTER);
		System.setOut(((SimulatedDisplay)getDisplay()).getPrintStream());
		
		//Create sidebar
		addSidebar();
		addMotorLabels();
		
		//buttons
		addButtons();
		
		//Setup visibility settings for root pane
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		Dimension screenSize = Toolkit.getDefaultToolkit().getScreenSize();
		//Make sure the window isn't too big for the person's screen
		frame.setSize(Math.min(1024, (int)(screenSize.width*.7)), Math.min(768, (int)(screenSize.height*.7)));
		frame.setVisible(true);
		
		new MotorSpeedUpdater(this, 100).start();
	}
	
	private void addSidebar() {
		GridLayout sidebarLayout = new GridLayout(2, 1);
		sidebar.setLayout(sidebarLayout);
		frame.getContentPane().add(sidebar, BorderLayout.EAST);
		sidebar.add(new Container()); sidebar.add(new Container());
	}
	
	private void addMotorLabels() {
		GridLayout motorInfoLayout = new GridLayout(motorSpeedLabels.length, 1);
		sidebarMotors.setLayout(motorInfoLayout);
		for(JLabel label : motorSpeedLabels) {
			sidebarMotors.add(label);
		}
		sidebar.add(sidebarMotors, 1);
	}
	
	private void addButtons() {
		FlowLayout buttonLayout = new FlowLayout();
		Container buttonContainer = new Container();
		buttonContainer.setComponentOrientation(ComponentOrientation.LEFT_TO_RIGHT);
		buttonContainer.setLayout(buttonLayout);
		SimulatedInput input = (SimulatedInput)getInput();
		buttonContainer.add(input.ub);
		buttonContainer.add(input.db);
		buttonContainer.add(input.lb);
		buttonContainer.add(input.rb);
		buttonContainer.add(input.ab);
		buttonContainer.add(input.bb);
		buttonContainer.add(input.blb);
		frame.getContentPane().add(buttonContainer, BorderLayout.SOUTH);
	}
	
	/**
	 * Checks to see if the framebuffer has already been added. If not, it adds
	 * it.
	 */
	public void addFramebuffers() {
		if(framebuffersAdded) return;
		framebuffersAdded = true;
		sidebar.add(((SimulatedFramebuffer)
			cbccore.display.Display.getFramebuffer()).getPanel(), 0);
	}
	
	private class MotorSpeedUpdater extends Thread {
		protected CBCSimulator root;
		protected SimulatedCBOB cbob;
		protected int refreshRate;
		
		public MotorSpeedUpdater(CBCSimulator root, int refreshRate) {
			super();
			this.root = root;
			this.cbob = root.cbob;
			this.refreshRate = refreshRate;
			setDaemon(true);
		}
		
		public void run() {
			while(true) {
				try {
					Thread.yield();
					for(int i = 0; i < (root.motorSpeedLabels.length>>1); i++) {
						//System.out.println(i);
						root.motorSpeedLabels[i<<1].setText(
							"Motor #"+(i)+": " +
							Integer.toString(cbob.getMotorSpeed(i).speed) +
							(cbob.getMotorSpeed(i).bemf?" tps":" %"));
						root.motorSpeedLabels[(i<<1)+1].setText(
							"Pos: " + Integer.toString(cbob.getMotorPosition(i))
						);
					}
					Thread.sleep(refreshRate);
				} catch(InterruptedException ex) {
					return;
				}
			}
		}
	}

	public static void NYI(String string) {
		System.out.println("Not Yet Implemented: " + string);
	}
}

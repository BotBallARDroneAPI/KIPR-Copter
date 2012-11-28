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

import cbccore.low.Display;

import java.io.IOException;
import java.io.OutputStream;
import java.io.PrintStream;
 
import javax.swing.JTextArea;

/**
 * 
 * @author Benjamin Woodruff (Based on code by Braden McDorman)
 *
 */

public class SimulatedDisplay extends Display {
	
	private PrintStream out;
	private JTextArea textBox;
	
	public SimulatedDisplay() {
		textBox = new JTextArea("On Simulator!\n");
		textBox.setLineWrap(true);
		out = new PrintStream(new TextAreaOutputStream(textBox, TextAreaOutputStream.DEFAULT_BUFFER_SIZE));
	}
	
	public void display_clear() { /* Clears display and pust cursor in upper left*/
		for(int i = 0; i < 50; ++i) System.out.println("");
	}
	
	public void cbc_display_clear() { /*Clears console display on CBC*/
		display_clear();
	}
	
	public PrintStream getPrintStream() {
		return out;
	}
	
	public JTextArea getTextBox() {
		return textBox;
	}
}

/*TextAreaOutputStream.java
======================
 * Created on Mar 13, 2005 by @author Tom Jacobs
 * stolen from: http://forums.sun.com/thread.jspa?threadID=709187&messageID=4105977#4105977
 */
 
class TextAreaOutputStream extends OutputStream {
	public static final int DEFAULT_BUFFER_SIZE = 1;
	
	JTextArea mText;
	byte mBuf[];
	int mLocation;
	public TextAreaOutputStream(JTextArea component) {
		this(component, DEFAULT_BUFFER_SIZE);
	}
 
	public TextAreaOutputStream(JTextArea component, int bufferSize) {
		mText = component;
		if (bufferSize < 1) bufferSize = 1;
		mBuf = new byte[bufferSize];
		mLocation = 0;
	}
	
	//@Override
	public void write(int arg0) throws IOException {
		//System.err.println("arg = "  + (char) arg0);
		mBuf[mLocation++] = (byte)arg0;
		if (mLocation == mBuf.length) {
			flush();
		}
	}
	
	public void flush() {
		mText.append(new String(mBuf, 0, mLocation));
		mLocation = 0;
		try {
			Thread.sleep(1);
		}
		catch (Exception ex) {}
	}
}

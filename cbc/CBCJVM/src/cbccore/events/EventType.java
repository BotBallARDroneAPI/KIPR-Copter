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

package cbccore.events;

/**
 * Every type of event should subclass this. Event types may be dynamic,
 * and you can decide how to deal with this, or they can be static (most
 * common).
 * 
 * @author Benjamin Woodruff
 */

public class EventType {
	private long handle;
	
	public EventType() {
		handle = EventManager.__getUniqueHandle();
	}
	
	/**
	 * This should be unnecessary for you, our end user. Don't call this.
	 */
	public long getHandle() {
		return handle;
	}
	
	public int hashCode() {
		return (int)getHandle();
	}
	
	public boolean equals(Object obj) {
		return obj instanceof EventType && ((EventType)obj).getHandle() == getHandle();
	}
}

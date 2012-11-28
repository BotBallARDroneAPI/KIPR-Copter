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
 * Every event should subclass this. Event types may be dynamic, and you can
 * decide how to deal with this, or they can be static (most common). Look at
 * the example code in the "tests" folder included in the CBCJVM distribution.
 * This class also contains a public "data" variable of type "E" for easy ad-hoc
 * expandablity.
 * 
 * @author Braden McDorman, Benjamin Woodruff
 * @see    EventManager
 * @see    EventType
 */

public class Event<E> { // extends java.util.EventObject
                        // EventObject requires source to be filled
	private EventType handle;
	private Object source;
	public E data;
	
	/**
	 * Constructs a new Event object.
	 * 
	 * @param  handle  What type of event is this?
	 * @see    cbccore.events.EventType
	 */
	public Event(EventType handle) {
		this(handle, null);
	}
	
	/**
	 * Constructs a new Event object.
	 * 
	 * @param  handle  What type of event is this?
	 * @param  source  What object is emitting this event?
	 * @see    cbccore.events.EventType
	 */
	public Event(EventType handle, Object source) {
		this.handle = handle;
		this.source = source;
	}
	
	/**
	 * returns the object that has emitted/will be emitting this event.
	 * 
	 * @return <code>null</code> if the source was left unspecified
	 */
	public Object getSource() {
		return source;
	}
	
	
	/**
	 * Get the <code>EventType</code> for this object
	 * 
	 * @see cbccore.events.EventType
	 */
	public EventType getType() {
		return handle;
	}
	
	
	/**
	 * Contacts all <code>IEventListener</code> objects connected to this
	 * Event's <code>EventType</code>, calling their <code>event</code> method,
	 * (uses default singleton <code>EventManager</code>).
	 * 
	 * @see cbccore.events.EventManager
	 * @see cbccore.events.EventManager#connect
	 * @see cbccore.events.IEventListener
	 * @see cbccore.events.EventType
	 */
	public void emit() {
		emit(EventManager.get());
	}
	
	/**
	 * Contacts all <code>IEventListener</code> objects connected to this
	 * Event's <code>EventType</code>, calling their <code>event</code> method.
	 * 
	 * @param  em  The <code>EventManager</code> to use for emitting
	 * @see    cbccore.events.EventManager
	 * @see    cbccore.events.EventManager#connect
	 * @see    cbccore.events.IEventListener
	 * @see    cbccore.events.EventType
	 */
	public void emit(EventManager em) {
		em.__emit(this);
	}
	
	/**
	 * Gets the ad-hoc data variable (exists for easy expandability, when
	 * extending is too much work)
	 * 
	 * @return The value stored in the ad-hoc data variable
	 */
	public E getData() {
		return data;
	}
	
	/**
	 * Sets the ad-hoc data variable (exists for easy expandability, when
	 * extending is too much work)
	 * 
	 * @param  data  The value to set the ad-hoc data variable to
	 */
	public void setData(E data) {
		this.data = data;
	}
	
	//this function would mess up static event types, by removing all of a type
	//suspending until we find a cleaner way of doing this
	/*public void dispose() {
		EventManager.get().__dispose(this);
		handle = -1;
	}*/
}

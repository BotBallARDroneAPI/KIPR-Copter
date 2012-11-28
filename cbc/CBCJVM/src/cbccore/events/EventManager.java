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

/*
 * Current development status:
 *      Preparing to manage EventListeners that are added during the processing
 *        of events to a separate queue. This queue will be managed after the
 *        current list of listeners by copying it to a local variable, and
 *        clearing the queue. This is done in a loop until nothing is added to
 *        the queue. Before we can do this though, we must ensure the class is
 *        fully thread-safe for this type of operations. Each thread will have
 *        its own queue via java.lang.ThreadLocal . This may seem complicated,
 *        but it is a neccicary step. In the meantime, we must attempt to keep
 *        from breaking builds, as the Event system is a central part of our
 *        libraries
 */

package cbccore.events;

import java.util.concurrent.ConcurrentHashMap;
import java.util.ArrayList;
//import java.util.WeakHashMap
import java.util.HashMap;
import java.util.HashSet;
import java.util.Set;
import java.util.Collections;
//ThreadLocal could be useful too.

/**
 * An event system based roughly on ActionScript's (Adobe Flash) and awt's event
 * dispatching system. (yes, you may now toss insults at me based on your hate
 * of FlashPlayer. They will all be redirected to /dev/null). Anything that
 * dispatches an event should subclass this. Generally maintains O(1) time
 * thanks to HashMaps! Yay HashMaps<p>
 * <a href="http://www.adobe.com/livedocs/flash/9.0/ActionScriptLangRefV3/flash/events/EventDispatcher.html">http://www.adobe.com/livedocs/flash/9.0/ActionScriptLangRefV3/flash/events/EventDispatcher.html</a>
 * <p>I'm hoping this class is thread safe, I syncronized a few things,
 * but no guarentees. Shouldn't matter on the CBC, as there is only one
 * core.
 * @author Braden McDorman, Benjamin Woodruff
 */

@SuppressWarnings("unused")
public class EventManager {
	private HashMap<EventType, Set<IEventListener>> events = new HashMap<EventType, Set<IEventListener>>();
	private static EventManager instance = null;
	private ThreadLocal<EventType> currentEventType;
	private ConcurrentHashMap<EventType, Set<IEventListener>> queue; //can't be thread local- some threads may be using the same type
	private ConcurrentHashMap<EventType, Integer> refcount; //keep references of num of objects
	private ConcurrentHashMap<EventType, Integer> mergecount; //must wait for reaching 0 before continueing
	private static long it = Long.MIN_VALUE; // making this static lets us have
	                                         // universal identifiers, for any
	                                         // EventManager
	
	
	/**
	 * Gets the main instance of EventManager. You can have more than one, but
	 * it is suggested that you just use this one with a call to
	 * <code>getUniqueEventType()</code>
	 * 
	 * @return        The singleton style instance variable of EventManager
	 * @see           #getUniqueEventType
	 */
	public static EventManager get() {
		if (instance == null)
			instance = new EventManager();
		return instance;
	}
	
	/**
	 * Adds an event listener to the list of listeners for a specific
	 * <code>EventType</code>.
	 *
	 * @param  type      The <code>EventType</code> that IEventListener will be
	 *                       listening for.
	 * @param  listener  The listening function/object
	 * @see    cbccore.events.IEventListener
	 * @see    cbccore.events.EventType
	 * @see    #disconnect
	 * @see    cbccore.events.Event#emit
	 */
	public synchronized void connect(EventType type, IEventListener listener) {
		Set<IEventListener> listeners = getListeners(type);
		listeners.add(listener);
		events.put(type, listeners);
	}
	
	/**
	 * Removes an event listener from the list of listeners for a specific
	 * <code>EventType</code>.
	 *
	 * @param  type      The <code>EventType</code> that IEventListener has been
	 *                       listening for.
	 * @param  listener  The listening function/object
	 * @see    cbccore.events.IEventListener
	 * @see    cbccore.events.EventType
	 * @see    #connect
	 * @see    cbccore.events.Event#emit
	 */
	public synchronized void disconnect(EventType type,
	                                    IEventListener listener) {
		Set<IEventListener> listeners = getListeners(type);
		listeners.remove(listener);
	}
	
	/**
	 * Do not call this directly
	 */
	@SuppressWarnings("unchecked")
	public void __emit(Event e) { // This CANNOT be an EventType
		Set<IEventListener> listeners = getListeners(e.getType());
		for (IEventListener i : listeners) {
			i.event(e);
		}
	}
	
	// Gets all the listeners for a specific event type
	private Set<IEventListener> getListeners(EventType type) {
		Set<IEventListener> listeners = events.get(type);
		if (listeners == null) {
			listeners = Collections.synchronizedSet(
				new HashSet<IEventListener>()
			);
			events.put(type, listeners);
		}
		return listeners;
	}
	
	/**
	 * Gets a new <code>Event</code> with an EventType guarenteed to be never
	 * have been made before by the EventManager class. (note: if you create an
	 * Event without this it could have a duplicate EventType, which is not
	 * reccommended if that is not what you are going for)
	 */
	@SuppressWarnings("unchecked")
	public static Event getUniqueEvent() {
		return new Event(getUniqueEventType());
	}
	
	/**
	 * Gets a new <code>EventType</code> guarenteed to be never have been made
	 * before by the EventManager class.<p/>
	 * <b>Calling <code>new EventType()</code> will have the same exact effect.
	 * </b> This is just an alterative way of doing that
	 */
	public static EventType getUniqueEventType() {
		return new EventType();
	}
	
	/**
	 * Do not call this directly
	 */
	public static long __getUniqueHandle() {
		return it++;
	}
	
	/**
	 * Do not call this directly
	 */
	public void __dispose(EventType e) {
		events.remove(e);
	}
}

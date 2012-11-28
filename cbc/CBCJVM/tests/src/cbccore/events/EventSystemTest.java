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

import org.testng.annotations.Test;
import java.util.HashSet;

/*
 * @author Benjamin Woodruff
 */
public class EventSystemTest {
	@Test
	public void getUniqueEventTypeTest() {
		EventManager em = EventManager.get();
		int testSize = 100000;
		HashSet<EventType> hs = new HashSet<EventType>(testSize);
		for(int i = 0; i < testSize; ++i) {
			assert hs.add(em.getUniqueEventType());
		}
	}
	
	@Test(dependsOnMethods={"getUniqueEventTypeTest"})
	public void eventDispatchTest() throws InterruptedException {
		// Tries with both the default and custom EventManagers
		eventDispatchTestHelper(EventManager.get());
		eventDispatchTestHelper(new EventManager());
	}
	
	// Emits an event and checks that it gets passed properly
	private void eventDispatchTestHelper(EventManager em)
			throws InterruptedException {
		
		final Event ev = em.getUniqueEvent();
		ev.data = "TestString";
		IEventListener eventListener =
			new EventListenerAdapter() {
				private boolean alreadyExecuted = false;
				// this should only be executed _once_
				@Override
				public void event(Event e) {
					assert !alreadyExecuted;
					alreadyExecuted = true;
					assert e == ev;
					assert e.getData().equals("TestString");
				}
			};
		em.connect(ev.getType(), eventListener);
		// Fire of some other events
		for(int i = 0; i < 100; ++i) {
			em.getUniqueEvent().emit(em);
		}
		// Make sure they don't activate us and give threads time to die
		em.disconnect(ev.getType(), eventListener);
		ev.emit(em);
		Thread.sleep(10L);
		em.connect(ev.getType(), eventListener);
		ev.emit(em);
	}
}

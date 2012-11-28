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


/**
 * Provides boolean algebra operations for digital (boolean) sensors. Each
 * implimenter of <code>LogicBooleanSensor</code> is both a wrapper for and a
 * <code>IBooleanSensor</code>, making them stackable.<p/>
 * For example:<br/>
 * <code>IBooleanSensor myModifiedSensor =
 *       new NotBooleanSensor(new AndBooleanSensor(sensorOne, sensorTwo));<code>
 */
package cbccore.sensors.digital.logic;

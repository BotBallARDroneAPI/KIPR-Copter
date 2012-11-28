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
 * A plug-in based movement library for navigating yourself around the board,
 * with little more code than simply:<br>
 * <code>driveTrainObject.moveCm(5., driveTrainObject.getMaxCmps() * .5);</code>
 * <p>
 * 
 * After you write your program, it can be used interchangeably on a create,
 * with a simple lego base, or with whatever other device you wish, given that
 * you create your own plug-in by providing minimal API translation.<p>
 * 
 * The package also offers basic position tracking, and will eventually support
 * pathfinding via an advanced geometrical algorithm.
 */
package cbccore.movement;

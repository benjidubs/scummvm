/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#ifndef ACCESS_COUNTDOWN_ROOM_H
#define ACCESS_COUNTDOWN_ROOM_H

#include "access/room.h"

namespace Access {

namespace Countdown {

class CountdownRoom : public Room {
protected:
	void reloadRoom() override;
	void reloadRoom1() override;
	void mainAreaLClick() override {}
public:
	CountdownRoom(AccessEngine *vm) : Room(vm) {}

	void showRoom();
	void drawRoom();
	void clearRoom() override;
	void roomMenu() override {}
	void init4Quads() override {}
};

} // End of namespace Countdown

} // End of namespace Access

#endif /* ACCESS_COUNTDOWN_ROOM_H */

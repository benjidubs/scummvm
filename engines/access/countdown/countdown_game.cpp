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

#include "access/countdown/countdown_game.h"
#include "access/countdown/countdown_resources.h"
#include "access/countdown/countdown_room.h"

namespace Access {

namespace Countdown {

CountdownEngine::CountdownEngine(OSystem *syst, const AccessGameDescription *gameDesc) : AccessEngine(syst, gameDesc) {
}

void CountdownEngine::initObjects() {
	_room = new CountdownRoom(this);
}

void CountdownEngine::setupGame() {
	CountdownResources &res = *((CountdownResources *)_res);
	_fonts.load(res._font1, res._font2, res._bitFont);
	_player->_roomNumber = 14;
	_player->_position = Common::Point(100, 45);
	Resource *sprites = _files->loadFile(19, 6);
	_player->_playerSprites = new SpriteResource(this, sprites);
	delete sprites;
	_startup = -1;
}

void CountdownEngine::playGame() {
	// TODO: Implement introduction
	((CountdownRoom *)_room)->showRoom();
	_events->forceSetCursor(CURSOR_CROSSHAIRS);
	_events->showCursor();

	while (!shouldQuit()) {
		_events->pollEventsAndWait();
		if (shouldQuit())
			break;
		((CountdownRoom *)_room)->drawRoom();
		_screen->update();
	}
}

void CountdownEngine::dead(int deathId) {
	error("CountdownEngine::dead not implemented");
}

void CountdownEngine::establish(int estabIndex, int sub) {
	error("CountdownEngine::establish not implemented");
}

} // End of namespace Countdown

} // End of namespace Access

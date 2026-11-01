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

#include "access/countdown/countdown_player.h"
#include "access/access.h"
#include "access/countdown/countdown_resources.h"

namespace Access {

namespace Countdown {

void CountdownPlayer::load() {
	Resource *sprites = _vm->_files->loadFile(19, 6);
	_playerSprites1 = new SpriteResource(_vm, sprites);
	delete sprites;
	Player::load();

	_leftDelta = -9;
	_rightDelta = 33;
	_upDelta = 5;
	_downDelta = -5;
	_scrollConst = 5;

	for (uint8 i = 0; i < _vm->_playerDataCount; ++i) {
		_walkOffRight[i] = SIDEOFFR[i];
		_walkOffLeft[i] = SIDEOFFL[i];
		_walkOffUp[i] = SIDEOFFU[i];
		_walkOffDown[i] = SIDEOFFD[i];
	}

	_sideWalkMin = 0;
	_sideWalkMax = 8;
	_upWalkMin = 9;
	_upWalkMax = 17;
	_downWalkMin = 18;
	_downWalkMax = 25;

	calcManScale();
	_rawPlayer = _position;
	_rawPlayer.y += _playerOffset.y;
}

void CountdownPlayer::calcManScale() {
	_vm->_scale = _vm->_scaleI;
	_vm->_screen->setScaleTable(_vm->_scale);
	_playerOffset.x = _vm->_screen->_scaleTable1[20];
	_playerOffset.y = _vm->_screen->_scaleTable1[62];
	_inactiveYOff = _playerOffset.y;
}

void CountdownPlayer::walk() {
	if (_move > RIGHT)
		_move = NONE;
	Player::walk();
}

void CountdownPlayer::checkMove() {
	Player::checkMove();
	if (_playerMove && _xFlag == 2 && _yFlag == 0)
		_yFlag = 1;
}

} // End of namespace Countdown

} // End of namespace Access

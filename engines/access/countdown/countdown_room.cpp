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

#include "access/countdown/countdown_room.h"
#include "access/countdown/countdown_resources.h"
#include "access/access.h"
#include "common/memstream.h"

namespace Access {

namespace Countdown {

class CountdownRoomInfo {
public:
	byte _roomFlag;
	FileIdent _playFieldFile;
	Common::Array<CellIdent> _cells;
	FileIdent _scriptFile;
	FileIdent _animFile;
	byte _scaleI;
	byte _scrollThreshold;
	FileIdent _paletteFile;
	int _startColor, _numColors;
	Common::Array<RoomInfo::SoundIdent> _sounds;

	CountdownRoomInfo(Common::SeekableReadStream &s, const CountdownResources &res) {
		_roomFlag = s.readByte();
		_playFieldFile.load(s);
		_cells = res.loadCells(s);
		_scriptFile.load(s);
		_animFile.load(s);
		_scaleI = s.readByte();
		_scrollThreshold = s.readByte();
		_paletteFile._fileNum = s.readSint16LE();
		_startColor = _numColors = 0;
		if (_paletteFile._fileNum != -1) {
			_paletteFile._subFile = s.readSint16LE();
			_startColor = s.readUint16LE();
			_numColors = s.readUint16LE();
		}
		for (int16 fileNum = s.readSint16LE(); fileNum != -1; fileNum = s.readSint16LE()) {
			RoomInfo::SoundIdent sound;
			sound._fileNum = fileNum;
			sound._subFile = s.readSint16LE();
			sound._priority = s.readUint16LE();
			_sounds.push_back(sound);
		}
	}
};

void CountdownRoom::showRoom() {
	const Common::Array<byte> &data = _vm->_res->ROOMTBL[_vm->_player->_roomNumber]._data;
	Common::MemoryReadStream s(data.data(), data.size());
	CountdownRoomInfo roomInfo(s, *((CountdownResources *)_vm->_res));
	_roomFlag = roomInfo._roomFlag;
	loadPlayField(roomInfo._playFieldFile);
	_vm->loadCells(roomInfo._cells);

	Resource *anim = _vm->_files->loadFile(roomInfo._animFile);
	_vm->_animation->loadAnimations(anim);
	delete anim;
	_vm->_scale = _vm->_scaleI = roomInfo._scaleI;
	_vm->_screen->setScaleTable(_vm->_scale);
	_vm->_player->_scrollThreshold = roomInfo._scrollThreshold;
	_vm->_player->_offsetY = _vm->_screen->_scaleTable1[62];

	Screen &screen = *_vm->_screen;
	if (roomInfo._paletteFile._fileNum != -1) {
		screen._startColor = roomInfo._startColor;
		screen._numColors = roomInfo._numColors;
		screen.loadPalette(roomInfo._paletteFile._fileNum, roomInfo._paletteFile._subFile);
	}
	screen._startColor = 128;
	screen._numColors = 32;
	screen.loadPalette(19, 8, 384);
	Common::MemoryReadStream palette(SYSTEM_PALETTE, sizeof(SYSTEM_PALETTE));
	screen.loadRawPalette(&palette, sizeof(SYSTEM_PALETTE));

	// TODO: Remove (Initial MASONCEL intializer for bug/key/guard)
	_vm->_animation->setAnimTimer(_vm->_animation->setAnimation(4));
	_vm->_animation->setAnimTimer(_vm->_animation->setAnimation(1));
	_vm->_animation->setAnimTimer(_vm->_animation->setAnimation(5));

	buildScreen();
	drawRoom();
	screen.setPalette();
	screen.update();
}

void CountdownRoom::drawRoom() {
	_vm->_images.clear();
	_vm->_oldRects.clear();
	_vm->_newRects.clear();
	_vm->copyBF1BF2();

	ImageEntry player = *_vm->_player;
	player._spritesPtr = _vm->_player->_playerSprites;
	_vm->_images.addToList(player);
	_vm->_animation->animate(2);
	_vm->_animation->animate(0);
	_vm->_animation->animate(4);
	_vm->_animation->animate(1);
	_vm->plotList1();
	_vm->copyBF2Vid();
}

void CountdownRoom::reloadRoom() {
	clearRoom();
	showRoom();
}

void CountdownRoom::clearRoom() {
	_vm->_animation->clearTimers();
	_vm->_animation->freeAnimationData();
	_vm->freeCells();
	freePlayField();
	freeTileData();
}

void CountdownRoom::reloadRoom1() {
	reloadRoom();
}

} // End of namespace Countdown

} // End of namespace Access

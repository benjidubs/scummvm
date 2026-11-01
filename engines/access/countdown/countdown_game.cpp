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
	_timers.resize(1);
	_timers[0]._initTm = _timers[0]._timer = 4;
	_timers[0]._flag = 1;
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
		((CountdownRoom *)_room)->doCommands();
		((CountdownRoom *)_room)->drawRoom();
		_screen->update();
	}
}

void CountdownEngine::plotList1() {
	for (ImageEntry &image : _images) {
		const SpriteFrame *frame = image._spritesPtr->getFrame(image._frameNumber);
		Common::Point pt = image._position - _screen->_bufferStart;
		bool unscaled = (image._flags & IMGFLAG_UNSCALED) != 0;
		int scale = image._scaleOverride ? image._scaleOverride : _scale;
		Common::Rect bounds(pt.x, pt.y, pt.x + frame->w, pt.y + frame->h);
		if (!unscaled) {
			bounds.setWidth(frame->w * scale >> 8);
			bounds.setHeight(frame->h * scale >> 8);
		}

		if (_buffer2.clip(bounds)) {
			image._flags |= IMGFLAG_CROPPED;
			continue;
		}
		image._flags &= ~IMGFLAG_CROPPED;
		if (_buffer2._leftSkip || _buffer2._rightSkip || _buffer2._topSkip || _buffer2._bottomSkip)
			image._flags |= IMGFLAG_CROPPED;
		_newRects.push_back(bounds);

		bool backwards = (image._flags & IMGFLAG_BACKWARDS) != 0;
		if (unscaled) {
			if (backwards)
				_buffer2.plotB(frame, pt);
			else
				_buffer2.plotF(frame, pt);
		} else {
			plotScaledSprite(frame, bounds, scale, backwards);
		}
		image._flags |= IMGFLAG_DRAWN;
	}
}

void CountdownEngine::plotScaledSprite(const SpriteFrame *frame, const Common::Rect &bounds, byte scale, bool backwards) {
	if (!scale || frame->w > 255 || frame->h > 255 || bounds.isEmpty())
		return;

	// The DOS caller uses byte division to convert the right crop to source units.
	uint right = (byte)_buffer2._rightSkip * 257 / scale;
	uint width = ((byte)bounds.width() * 256 + right) / scale;
	if (right > 255 || width > 255)
		return;

	byte vertical = 2 + _buffer2._topSkip * scale;
	int destY = bounds.top;
	for (int y = _buffer2._topSkip; y < frame->h && destY < bounds.bottom; ++y) {
		int next = vertical + scale;
		vertical = next;
		if (next < 256)
			continue;

		const Common::Point &span = frame->getRowSpan(y);
		byte skip = backwards ? frame->w - span.x - span.y : span.x;
		int count = span.y;
		int first = backwards ? span.x + span.y - 1 : span.x;
		int step = backwards ? -1 : 1;
		bool mirrorLeftOverlap = false;
		if (byte left = _buffer2._leftSkip) {
			if (skip < left) {
				int removed = left - skip;
				first += removed * step;
				count -= removed;
				skip = 0;
				mirrorLeftOverlap = backwards;
			} else {
				skip -= left;
			}
		}
		if (_buffer2._rightSkip && !mirrorLeftOverlap)
			count = MIN(count, (int)width - skip);

		int destX = bounds.left + (skip * scale >> 8);

		byte horizontal = mirrorLeftOverlap ? 0 : (skip * scale >> 8) + 2;
		for (int i = 0; i < count; ++i) {
			int advance = horizontal + scale;
			horizontal = advance;
			if (advance < 256)
				continue;

			int sourceX = first + i * step;
			if (sourceX >= 0 && sourceX < frame->w && destX <= _screen->_clipWidth) {
				byte pixel = *(const byte *)frame->getBasePtr(sourceX, y);
				if (pixel)
					*(byte *)_buffer2.getBasePtr(destX, destY) = pixel;
			}
			++destX;
		}
		++destY;
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

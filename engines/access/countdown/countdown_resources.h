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

#ifndef ACCESS_COUNTDOWN_RESOURCES_H
#define ACCESS_COUNTDOWN_RESOURCES_H

#include "access/resources.h"
#include "access/font.h"

namespace Access {

namespace Countdown {

extern const byte SYSTEM_PALETTE[24];

class CountdownResources : public Resources {
private:
	Common::Array<Common::Array<byte> > _cursors;
protected:
	void load(Common::SeekableReadStream &s) override;
public:
	MartianFont *_font1;
	MartianFont *_font2;
	MartianBitFont *_bitFont;

	CountdownResources(AccessEngine *vm) : Resources(vm), _font1(nullptr), _font2(nullptr), _bitFont(nullptr) {}
	~CountdownResources() override;

	Common::Array<CellIdent> loadCells(Common::SeekableReadStream &s) const;
	CharEntry loadCharEntry(const byte *data) const override;
	const byte *getCursor(int num) const override;
	const char *getEgoName() const override { return "MASON"; }
	int getRMouse(int i, int j) const override;
	int inButtonXRange(int x) const override;
};

} // End of namespace Countdown

} // End of namespace Access

#endif /* ACCESS_COUNTDOWN_RESOURCES_H */

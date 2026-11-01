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

#ifndef __COUNTDOWN_RESOURCES_H__
#define __COUNTDOWN_RESOURCES_H__

#include "common/scummsys.h"

namespace Countdown {

#define COUNTDOWN_NUM_CURSORS 4
extern const byte *const CURSORS[COUNTDOWN_NUM_CURSORS];
extern const uint CURSOR_SIZES[COUNTDOWN_NUM_CURSORS];

extern const char *const ROOM_DESCR[52];

extern const char *const DEATH_TEXT_ENG[24];
extern const byte DEATH_SCREENS_ENG[24];
extern const char *const INVENTORY_NAMES_ENG[70];

extern const char *const FLASHBACK_TEXT_ENG[10];
extern const char *const ENDING_TEXT_ENG[3];
extern const char *const ENDING_SCORE_TEXT_ENG;
extern const char *const VERB_LABELS_ENG[9];
extern const char *const VERB_DEFAULTS_ENG[9];
extern const char *const USE_CONNECTORS_ENG[2];
extern const char *const SCORE_TEXT_ENG;
extern const char *const TIME_TEXT_ENG;
extern const char *const DATE_TEXT_ENG;

extern const char *const ASK_TOPICS_ENG[32];
extern const char *const TALK_TEXT_ENG[3];
extern const char *const SAVELOAD_TEXT_ENG[6];
extern const char *const INTRO_TEXT_ENG;
extern const char *const NPC_TEXT_ENG[17];
extern const char *const BLACKJACK_TEXT_ENG[2];

extern const char *const TRAVEL_TITLE_ENG;
extern const char *const DESTINATION_CITIES_ENG[20];
extern const char *const DESTINATION_PLACES_ENG[20];
extern const char *const TRANSPORT_TITLE_ENG;
extern const char *const CASH_TEXT_ENG;
extern const char *const TRANSPORT_OPTIONS_ENG[3];
extern const char *const TRANSPORT_FARES_ENG[3];
extern const char *const CAD_TEXT_ENG[21];
extern const char *const PAYMENT_TEXT_ENG[2];

} // End of namespace Countdown

#endif

/*
 * Copyright 2018 Jack Humbert <jack.humb@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef REV6_CONFIG_H
#define REV6_CONFIG_H

#include "../../config.h"

/* Debounce reduces chatter (unintended double-presses) - set 0 if debouncing is not needed */
#define DEBOUNCE 20

/* Prevent modifiers from being stuck on after layer changes. */
#define PREVENT_STUCK_MODIFIERS

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
#define NO_DEBUG

/* disable print */
#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

/*
 * MIDI options
 */

/* Prevent use of disabled MIDI features in the keymap */
//#define MIDI_ENABLE_STRICT 1

/* enable basic MIDI features:
   - MIDI notes can be sent when in Music mode is on
*/
//#define MIDI_BASIC

/* enable advanced MIDI features:
   - MIDI notes can be added to the keymap
   - Octave shift and transpose
   - Virtual sustain, portamento, and modulation wheel
   - etc.
*/
#define MIDI_ADVANCED

/* override number of MIDI tone keycodes (each octave adds 12 keycodes and allocates 12 bytes) */
#define MIDI_TONE_KEYCODE_OCTAVES 6

#define MOUSEKEY_DELAY             200
#define MOUSEKEY_INTERVAL          50
#define MOUSEKEY_MAX_SPEED         10
#define MOUSEKEY_TIME_TO_MAX       12
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 40

#define TAPPING_TERM 333

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_DEFAULT 216.0f

#define PITCH_STANDARD_A 432.0f

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ZELDA_PUZZLE)
#endif

#endif

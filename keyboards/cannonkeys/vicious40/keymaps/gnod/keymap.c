/* Copyright 2017 Wunder
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
#include "xd75.h"

// tap-hold settings
#define LONGPRESS_DELAY 450
#define TH_EVENTS_COUNT 13

enum my_keys {
    TH_F1 = SAFE_RANGE,
    TH_F2,
    TH_F3,
    TH_F4,
    TH_F5,
    TH_F6,
    TH_F7,
    TH_F8,
    TH_F9,
    TH_F10,
    TH_F11,
    TH_F12,
    TH_PGUP,
    TH_PGDN,
};

// Layer shorthand
#define _QW 0
#define _FN 1

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_QW] = { /* QWERTY */
  { KC_ESC,  TH_F1,    TH_F2,    TH_F3,    TH_F4,    TH_F5,   TH_F6,    TH_F7,    TH_F8,    TH_F9,    TH_F10, TH_F11,  TH_F12, KC_GRV,  KC_DEL  },
  { KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC,  KC_RBRC,  KC_BSPC, KC_BSPC  },
  { KC_CAPS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_ENT, KC_ENT, TH_PGUP   },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT, KC_BSLS, KC_UP, TH_PGDN  },
  { KC_LCTL, KC_LGUI, KC_LALT, TG(_FN), KC_SPC,  KC_SPC, KC_SPC,  KC_SPC, KC_SPC, KC_RALT, KC_RGUI, KC_RCTL, KC_LEFT, KC_DOWN, KC_RIGHT },
 },

 [_FN] = { /* FUNCTION */
  { KC_INS, _______, _______, _______, _______, _______, KC_NLCK, KC_PSLS, KC_PAST, KC_MINS, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS    },
  { KC_MSEL, KC_CALC, KC_MYCM, KC_MAIL, _______, _______, KC_P7, KC_P8, KC_P9, KC_PPLS, _______, _______, KC_PSCR, KC_SLCK, KC_PAUS  },
  { KC_MPRV, KC_MPLY, KC_MNXT, KC_MSTP, _______, _______, KC_P4, KC_P5, KC_P6, KC_PENT, _______, _______,   _______, _______, RGB_MOD  },
  { KC_VOLD, KC_MUTE, KC_VOLU, KC_APP, _______, _______, KC_P1, KC_P2, KC_P3, KC_DOT, _______, _______, RGB_TOG, RGB_VAI, RGB_RMOD  },
  { RESET, _______, _______, _______, _______, _______, _______, KC_P0, _______, _______, _______, _______, RGB_HUD, RGB_VAD, RGB_HUI  },
 }
};

typedef struct {
    bool is_pressed;
    uint16_t timer;
    uint16_t kc_tap;
    uint16_t kc_hold;
} tap_hold_t;

static tap_hold_t th_events[] = {
    { .is_pressed = false, .timer = 0, .kc_tap = KC_1, .kc_hold = KC_F1 }, // TH_F1
    { .is_pressed = false, .timer = 0, .kc_tap = KC_2, .kc_hold = KC_F2 }, // TH_F2
    { .is_pressed = false, .timer = 0, .kc_tap = KC_3, .kc_hold = KC_F3 }, // TH_F3
    { .is_pressed = false, .timer = 0, .kc_tap = KC_4, .kc_hold = KC_F4 }, // TH_F4
    { .is_pressed = false, .timer = 0, .kc_tap = KC_5, .kc_hold = KC_F5 }, // TH_F5
    { .is_pressed = false, .timer = 0, .kc_tap = KC_6, .kc_hold = KC_F6 }, // TH_F6
    { .is_pressed = false, .timer = 0, .kc_tap = KC_7, .kc_hold = KC_F7 }, // TH_F7
    { .is_pressed = false, .timer = 0, .kc_tap = KC_8, .kc_hold = KC_F8 }, // TH_F8
    { .is_pressed = false, .timer = 0, .kc_tap = KC_9, .kc_hold = KC_F9 }, // TH_F9
    { .is_pressed = false, .timer = 0, .kc_tap = KC_0, .kc_hold = KC_F10 }, // TH_F10
    { .is_pressed = false, .timer = 0, .kc_tap = KC_MINS, .kc_hold = KC_F11 }, // TH_F11
    { .is_pressed = false, .timer = 0, .kc_tap = KC_EQL, .kc_hold = KC_F12 }, // TH_F12
    { .is_pressed = false, .timer = 0, .kc_tap = KC_PGUP, .kc_hold = KC_HOME }, // TH_PGUP
    { .is_pressed = false, .timer = 0, .kc_tap = KC_PGDN, .kc_hold = KC_END } // TH_PGDN
};

void taphold_tapped(uint8_t index, bool pressed) {
    if (index >= TH_EVENTS_COUNT) { return; }

    tap_hold_t *th_event = &th_events[index];

    if (pressed) {
        th_event->timer = timer_read();
        th_event->is_pressed = true;
    } else if (th_event->is_pressed) {
        register_code(th_event->kc_tap);
        unregister_code(th_event->kc_tap);
        th_event->is_pressed = false;
    }
}

void matrix_scan_user() {
    for (uint8_t index = 0 ; index < TH_EVENTS_COUNT ; ++index ) {
        tap_hold_t *th_event = &th_events[index];
        if ( th_event->is_pressed && timer_elapsed(th_event->timer) > LONGPRESS_DELAY) {
            register_code(th_event->kc_hold);
            unregister_code(th_event->kc_hold);
            th_event->is_pressed = false;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case TH_F1 ... TH_PGDN:
        taphold_tapped(keycode - TH_F1, record->event.pressed);
        return false;
    }

    return true;
}

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
#include "mousekey.h"

// Layer shorthand
#define _CO 0
#define _FN 1
#define _MS 2

enum planck_keycodes {
  MO_UL = SAFE_RANGE,
  MO_UR,
  MO_DL,
  MO_DR
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_CO] = { /* COLEMAK */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_MINS, KC_GRV,  KC_EQL,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12  },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_INS, KC_HOME, KC_PGUP, KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN,    KC_GRV  },
  { LCTL_T(KC_ESC), LALT_T(KC_A),  KC_R,  KC_S,  KC_T,  KC_D,  KC_DEL, KC_END,  KC_PGDN, KC_H,    KC_N,    KC_E,    KC_I,    LALT_T(KC_O), RCTL_T(KC_QUOT)   },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_BSLS,   KC_RBRC, KC_K,    KC_M,    KC_COMM, KC_DOT,  LCA_T(KC_SLSH), KC_SFTENT  },
  { KC_LCTL, KC_LALT, KC_LGUI, OSL(_FN), KC_SPC,  KC_SPC,  KC_SPC,  TG(_MS), KC_BSPC, KC_BSPC,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  },
 },

 [_FN] = { /* FUNCTION */
  { _______, _______, _______, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS,  _______, _______, _______, _______, _______, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_7, KC_8, KC_9, KC_0, _______  },
  { KC_CLCK, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_4, KC_5, KC_6, KC_MINS, KC_EQL  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_1, KC_2, KC_3, KC_LBRC,  KC_RBRC  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

[_MS] = { /* MOUSE */
  { _______, _______, _______, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS,  _______, _______, _______, _______, _______, RESET },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO_UL, MO_UR,   _______, KC_WH_U, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO_DL,  MO_DR,  KC_BTN2, KC_BTN3, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______  },
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
          if (record->event.pressed) {
            register_code(KC_RSFT);
            #ifdef BACKLIGHT_ENABLE
              backlight_step();
            #endif
          } else {
            unregister_code(KC_RSFT);
          }
        break;
      }
    return MACRO_NONE;
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
//----MOUSEKEYS thanks to bbaserdem
#ifdef MOUSEKEY_ENABLE
        case MO_UR:
            if( record->event.pressed ) {
                mousekey_on(KC_MS_U);
                mousekey_on(KC_MS_R);
                mousekey_send();
              } else {
                mousekey_off(KC_MS_U);
                mousekey_off(KC_MS_R);
                mousekey_send();
            }
            return false;
            break;
        case MO_UL:
            if( record->event.pressed ) {
                mousekey_on(KC_MS_U);
                mousekey_on(KC_MS_L);
                mousekey_send();
              } else {
                mousekey_off(KC_MS_U);
                mousekey_off(KC_MS_L);
                mousekey_send();
            }
            return false;
            break;
        case MO_DR:
            if( record->event.pressed ) {
                mousekey_on(KC_MS_D);
                mousekey_on(KC_MS_R);
                mousekey_send();
              } else {
                mousekey_off(KC_MS_D);
                mousekey_off(KC_MS_R);
                mousekey_send();
	            }
            return false;
            break;
        case MO_DL:
            if( record->event.pressed ) {
                mousekey_on(KC_MS_D);
                mousekey_on(KC_MS_L);
                mousekey_send();
              } else {
                mousekey_off(KC_MS_D);
                mousekey_off(KC_MS_L);
                mousekey_send();
	            }
            return false;
	    break;
#endif			
	}
  return true;
}


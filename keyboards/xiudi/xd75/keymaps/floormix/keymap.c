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
#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "hidd.c"

// Layer shorthand
#define _COLE 0
#define _NUM 1
#define _SYM 2
#define _EDIT 3

enum _keycodes {
  MO_UL = SAFE_RANGE,
  MO_UR,
  MO_DL,
  MO_DR,
  MO_DC,
  SC_VIW,
  SC_VIQ,
  MODF,
  WORD,
  WORDT,
  KC_DNEN,
  KC_UPHO,
  MOV,
  MOUS
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLE] = { /* COLEMAK */
  { KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_0, KC_MINS,  KC_EQUAL,    KC_F7,    KC_F8,    KC_F9,    KC_F10, KC_F11, KC_F12, },
  { KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,   KC_7,  KC_8, KC_9, KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCOLON,  KC_BSPC, KC_BSLS  },
  { KC_A,  KC_R,  KC_S,  KC_T,  KC_D,   KC_4,    KC_5,  KC_6, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT, KC_ENT  },
  { KC_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,  KC_1,   KC_2   KC_3, KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_UP, KC_GRV  },
  { MOUS, KC_RCTL, MOV, KC_NO, KC_NO, KC_NO, S(KC_SPC), KC_NO, KC_NO, KC_NO, MODF, KC_LALT, KC_LEFT, KC_DOWN, KC_RGHT  },
 },

 [_MOV] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, _______,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_INS,    KC_F12 },
  { _______, _______,  SC_VIW, SC_VIQ,   _______, _______, _______, DBL_PAR, KC_NO, KC_NO, KC_NO,  KC_UPHO,  KC_DEL, DBL_GRV  },
  { _______, _______, _______, _______, _______, _______, _______, DBL_SQR,  KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DNEN, DBL_QUO, _______ },
  { _______, _______, _______, _______, KC_NO, KC_NO, _______, DBL_ANG,  KC_LBRC,  KC_VOLD, KC_VOLU,  KC_NO,  KC_RBRC,  _______, KC_CAPS },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

[_MOUS] = { /* MOUSE */
  { WORD, WORDT, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS, _______, _______, _______, _______, _______, _______, RESET },
  { _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, KC_ESC,  _______ },
  { RGB_TOG, RGB_RMOD, RGB_MOD, RGB_SAD, RGB_SAI, _______, _______, KC_VOLD, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, KC_NO, KC_ENT  },
  { _______, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, _______, _______, _______, MO_DC, MO_DL,  MO_DR,  KC_BTN2, KC_BTN3, KC_TAB, KC_NO },
  { _______, _______, _______, _______, _______, _______, KC_BTN1, _______, _______,  _______, KC_BTN2, _______, _______, _______, _______  },
}


};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static bool ms_lock = false;

  switch(keycode) {
// Sticky shift
    case KC_CAPS:
      if (record->event.pressed){
        register_code(KC_RSFT);
      }
    return false;
    break;

// layer switch w/shift
    case KC_L:
      if (record->event.pressed){
        key_timer = timer_read();
        layer_on(_MOV);
      } else {
	layer_off(_MOV);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(keycode);
          }
        }
        return false;
	break;
    case MOV:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_RSFT) ) {
		register_code(KC_LSFT);
	}
        layer_on(_MOV);
      } else {
	layer_off(_r_on(_MOV);
	unregister_code(KC_LSFT);
      }
	break;
    case MOUS:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_RSFT) ) {
		register_code(KC_LSFT);
	}
        layer_on(_MOUS);
      } else {
	layer_off(_MOUS);
	unregister_code(KC_LSFT);
      }
	break;
// One key pgup/home
    case KC_UPHO:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {
        tap_code(KC_HOME);
      } else {
        if (get_mods() & MOD_BIT(KC_LALT)) {
	  clear_mods();
	  tap_code(KC_INSERT);
	  register_code(KC_LALT);
	} else {
	  tap_code(KC_PGUP);
	}
      }
    }
    break;
// One key pgdn/end
    case KC_DNEN:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {
        tap_code(KC_END);
      } else {
        if (get_mods() & MOD_BIT(KC_LALT)) {
	  clear_mods();
	  tap_code(KC_DELETE);
	  register_code(KC_LALT);
	} else {
	  tap_code(KC_PGDN);
	}
      }
    }
    break;
// guictlalt + lcl
    case MODF:
      if(record->event.pressed) {
	key_timer = timer_read();
	if (get_mods() & MOD_BIT(KC_LSFT)) {
	  register_code(KC_RALT);
	} else {
	  register_code(KC_LCTL);
	}
      } else {
	 unregister_code(KC_RALT);
	 unregister_code(KC_LCTL);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {
	    set_oneshot_mods(MOD_BIT(KC_LGUI));
	  }
	}
      break;
// One key left click hold
    case KC_BTN1:
      if(record->event.pressed){
        key_timer = timer_read();
	if(!ms_lock) {
          register_code(KC_BTN1);
        }
      } else {
        if (ms_lock) {
          ms_lock = false;
     	  unregister_code(KC_BTN1);
        } else if (timer_elapsed(key_timer) > TAPPING_TERM) {
	  ms_lock = true;
       	} else {
          unregister_code(KC_BTN1);
        }
      }
    return false;
    break;
//mouse doubleclick
	case MO_DC:
      	    if( record->event.pressed ) {
	        tap_code(KC_BTN1);
	    } else {
	        tap_code(KC_BTN1);
	    }
	    return false;
	    break;
//----DIAGONAL MOUSEKEYS thanks to bbaserdem
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
//------DOUBLE PRESS, with added left navigation, thanks to bbaserdem again.
        case DBL_ANG:
            if( record->event.pressed ) {
                SEND_STRING("<>"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_PAR:
            if( record->event.pressed ) {
                SEND_STRING("()"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_SQR:
            if( record->event.pressed ) {
                SEND_STRING("[]");
		unregister_code(KC_LSFT);
		tap_code(KC_LEFT);
            }
            return false;
            break;
        case DBL_QUO:
            if( record->event.pressed ) {
                SEND_STRING("\'\'"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_GRV:
            if( record->event.pressed ) {
                tap_code(KC_GRV);
                tap_code(KC_GRV);
                tap_code(KC_LEFT);
            }
            return false;
            break;
	case WORD:
	    if( record->event.pressed ) {
		SEND_STRING(HIDD);
	    }
	    break;
	case WORDT:
	    if( record->event.pressed ) {
		SEND_STRING(MAIL);
	    }
	    break;
// vim and screen shortcuts
	case SC_VIW:
	    if( record->event.pressed ) {
		register_code(KC_ESCAPE);
		unregister_code(KC_ESCAPE);
		register_code(KC_LSHIFT);
		register_code(KC_SCOLON);
		unregister_code(KC_SCOLON);
		unregister_code(KC_LSHIFT);
		register_code(KC_W);
		unregister_code(KC_W);
		register_code(KC_ENTER);
		unregister_code(KC_ENTER);
	    }
	    return false;
	    break;
	case SC_VIQ:
	    if( record->event.pressed ) {
		register_code(KC_ESCAPE);
		unregister_code(KC_ESCAPE);
		register_code(KC_LSHIFT);
		register_code(KC_SCOLON);
		unregister_code(KC_SCOLON);
		unregister_code(KC_LSHIFT);
		register_code(KC_Q);
		unregister_code(KC_Q);
		tap_code(KC_A);
		register_code(KC_ENTER);
		unregister_code(KC_ENTER);
	    }
	    return false;
	    break;
  }
  return true;
}


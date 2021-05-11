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
  WORD
};


void matrix_init_user(void) {
  _delay_ms(20); // Gets rid of tick
  rgblight_mode_noeeprom(RGBLIGHT_MODE_BREATHING);
  rgblight_set();

};  

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLE] = { /* COLEMAK */
  { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_BSLS  },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_INS, KC_HOME, KC_PGUP, KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCOLON,  KC_BSPC  },
  { KC_ESC, KC_A,  KC_R,  KC_S,  KC_T,  KC_D,  KC_DEL, KC_END,  KC_PGDN, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT  },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_BSLS,   KC_RBRC, KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,  RSFT_T(KC_ENT)  },
  { MO(_EDIT), KC_LCTL, KC_LALT, KC_LGUI, KC_NO, KC_NO, KC_NO,  LSFT_T(KC_SPACE), KC_NO, KC_NO, MODF, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  },
 },

 [_NUM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { KC_CAPS, _______,  KC_PSCR, KC_SLCK,  KC_PAUS, KC_INS, _______, _______, _______, _______, KC_7, KC_8,  KC_9, KC_0, KC_GRV  },
  { CTL_T(KC_ESC), _______, _______, _______, _______, _______, _______, _______, _______,  _______, KC_4, KC_5, KC_6, RALT_T(KC_MINS), RCTL_T(KC_EQUAL)  },
  { _______, _______, _______, _______, SC_VIW, SC_VIQ, _______, _______, _______,  _______,  KC_1, KC_2,  KC_3, KC_LBRC,  KC_RBRC  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

 [_SYM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD  },
  { CTL_T(KC_ESC), _______, _______, _______, _______, _______,  _______, _______, _______, KC_INS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, KC_PLUS  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_EXLM,  KC_AT, KC_HASH, KC_LCBR,  KC_RCBR  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

[_EDIT] = { /* MOUSE */
  { WORD, _______, _______, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS,  _______, _______, _______, _______, _______, RESET },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO_UL, MO_UR, _______, KC_WH_U, KC_HOME  },
  { RGB_TOG, RGB_RMOD, RGB_MOD, RGB_SAD, RGB_SAI, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, KC_PGUP  },
  { _______, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, MO_DL,  MO_DR,  KC_BTN2, KC_BTN3, KC_PGDN  },
  { _______, _______, _______, _______, _______, _______, _______, KC_BTN1, _______, _______, KC_BTN2, _______, _______, _______, _______  },
 }

};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static bool ms_lock = false;

  switch(keycode) {
// layer switch w/shift
    case KC_A: case KC_O:
      if (record->event.pressed){
        key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
        layer_on(_SYM);
	}
        layer_on(_NUM);
      } else {
	layer_clear();
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode);
        }
      }
      return false;
	break;
// Sticky shift
    case KC_CAPS:
      if (record->event.pressed){
        register_code(KC_RSFT);
      }
    return false;
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
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(beep);
#endif   
       	} else {
          unregister_code(KC_BTN1);
        }
      }
    return false;
    break; 
// guictlalt + lctl
    case MODF:
      if(record->event.pressed) {
	key_timer = timer_read();
	if (get_mods() & MOD_BIT(KC_LSFT)) {
	  register_code(KC_RALT);
	} else { 
	  register_code(KC_LCTL);
	}
      } else {
	clear_mods();
          if (timer_elapsed(key_timer) < TAPPING_TERM) {
	    set_oneshot_mods(MOD_BIT(KC_LGUI));
	  }
	}
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
	case WORD:
	    if( record->event.pressed ) {
		SEND_STRING(HIDD);
	    }
	    break;
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
//doubles on open keys--
	case KC_LPRN: case KC_LBRC: case KC_LCBR: 
	    if( record->event.pressed ) {
		key_timer = timer_read();
	    } else {
        	if (timer_elapsed(key_timer) > TAPPING_TERM) {   
                   tap_code(keycode);
                   tap_code(keycode + 1);
                   tap_code(KC_LEFT);
                } else {                               
	           tap_code(keycode);
  		}
	    return false;
	    break;
  }
  }
  return true;
}


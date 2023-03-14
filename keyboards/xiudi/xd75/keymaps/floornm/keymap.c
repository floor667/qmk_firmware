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
#define _MSE 3
#define _MOV 4

enum _keycodes {
  MO_UL = SAFE_RANGE,
  MO_UR,
  MO_DL,
  MO_DR,
  MO_DC,
  SC_VIW,
  SC_VIQ,
  SC_CTW,
  MODF,
  WORD,
  WORDT,
  KC_LSS,
  KC_LES,
  KC_LAYR,
  KC_MLAYR,
  DBL_PAR,
  DBL_BRC,
  DBL_SQR,
  DBL_QUO,
  DBL_DQT,
  DBL_ANG
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLE] = { /* COLEMAK */
  { KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_DEL },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_INS, KC_HOME, KC_PGUP, KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCOLON,  KC_BSPC  },
   { KC_ESC, KC_A,  KC_R,  KC_S,  KC_T,  KC_D,  KC_DEL, KC_END,  KC_PGDN, KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT  },
  { KC_CAPS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_BSLS,   KC_RBRC, KC_K,    KC_M,    KC_COMM, KC_DOT, KC_SLSH, KC_ENT},
  { MO(_MSE), KC_LCTL, KC_LALT, KC_MLAYR,  KC_LAYR, MT(MOD_LSFT,KC_SPC),  MO(_SYM), C(KC_LALT), MO(_SYM), KC_RSFT, KC_LAYR, MODF, KC_LGUI, KC_RCTL, KC_RALT  },
 },

 [_NUM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { _______, _______,  _______, SC_VIW,  SC_VIQ, SC_CTW, _______, _______, DBL_PAR, KC_GRV, KC_7, KC_8,  KC_9, KC_0, _______  },
  { CTL_T(KC_ESC), _______, _______, _______, KC_NO, _______, _______, _______, DBL_SQR,  KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,  DBL_QUO  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_LBRC,  KC_1, KC_2,  KC_3,  KC_RBRC, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DOT, _______,  _______, _______, _______, TG(_SYM)  },
 },

 [_SYM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { _______, _______, KC_PSCR, KC_SLCK,  KC_PAUS, KC_INS, _______, _______, DBL_PAR, KC_TILD, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______  },
  { CTL_T(KC_ESC), _______, _______, _______, _______, _______,  _______, _______, DBL_BRC, KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, DBL_DQT
  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_LCBR,  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR, _______  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

[_MSE] = { /* MOUSE */
  { WORD, WORDT, _______, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS,  _______, _______, _______, _______, _______, RESET },
  { _______, _______, _______, _______, _______, _______, _______, _______, KC_VOLU, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, _______ },
  { RGB_TOG, RGB_RMOD, RGB_MOD, RGB_SAD, RGB_SAI, _______, _______, _______, KC_VOLD, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______  },
  { _______, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, _______, _______, _______, _______, MO_DC, MO_DL,  MO_DR,  KC_NO, KC_BTN3, _______ },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN2,  _______, _______, _______, _______  },
},

 [_MOV] = { /* movement */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { _______, _______, KC_PSCR, KC_SLCK,  KC_PAUS, KC_INS, _______, _______, _______, KC_TILD, KC_END, KC_HOME, KC_NO, KC_PGUP, KC_TAB  },
  { CTL_T(KC_ESC), _______, _______, _______, KC_NO, _______,  _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_PGDN, KC_ESC  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  KC_VOLD,  KC_VOLU, KC_NO,  KC_NO, KC_ENT  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 }

};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static bool ms_lock = false;
static bool lsfton = false;
static bool rsfton = false;
static bool modshft = false;

  switch(keycode) {
// layer space shift
    case KC_LSS:
      if (record->event.pressed){
      key_timer = timer_read();
      lsfton = true;
      if(modshft) {
        register_code(KC_NO);
      } else if(rsfton) {
        clear_mods();
        layer_on(_NUM);
        modshft = true;
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(homeb);
#endif
      } else {
        register_code(KC_LSFT);
      }
    } else {
      lsfton = false;
      if(modshft) {
        if(!(lsfton || rsfton)) {
	  layer_clear();
	  modshft = false;
        } else {
	  unregister_code(KC_NO);
	}
      } else {
          unregister_code(KC_LSFT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
            tap_code(KC_SPC);
	  }
      }
    }
    break;
// layer enter shift
    case KC_LES:
      if (record->event.pressed){
      key_timer = timer_read();
      rsfton = true;
      if(modshft) {
	  register_code(KC_NO);
      } else if(lsfton) {
        clear_mods();
        layer_on(_SYM);
        modshft = true;
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(endb);
#endif
      } else {
        register_code(KC_RSFT);
      }
    } else {
      rsfton = false;
      if(modshft) {
        if(!(lsfton || rsfton)) {
	  layer_clear();
	  modshft = false;
        } else {
	  unregister_code(KC_NO);
	}
      } else {
          unregister_code(KC_RSFT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
            tap_code(KC_NO);
	 }
      }
    }
    break;
    case KC_LAYR:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          clear_mods();
          layer_on(_SYM);
        } else {
          layer_on(_NUM);
        }
      } else {
        layer_clear();
      }
      break;
    case KC_MLAYR:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_RSFT)) {
          layer_on(_MOV);
          register_code(KC_LSFT);
        } else {
          layer_on(_MOV);
        }
      } else {
        layer_clear();
       // clear_mods();
        unregister_code(KC_LSFT);
      }
      break;
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
                SEND_STRING("[]"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_BRC:
            if( record->event.pressed ) {
                SEND_STRING("{}"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_QUO:
            if( record->event.pressed ) {
                SEND_STRING("\'\'"SS_TAP(X_LEFT));
            }
            return false;
            break;
        case DBL_DQT:
            if( record->event.pressed ) {
                SEND_STRING("\"\""SS_TAP(X_LEFT));
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
	case WORDT:
	    if( record->event.pressed ) {
		SEND_STRING(MAIL);
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
        case SC_CTW:
            if( record->event.pressed) {
                register_code(KC_LCTL);
                tap_code(KC_W);
                unregister_code(KC_LCTL);
            }
            return false;
            break;
  }
  return true;
}


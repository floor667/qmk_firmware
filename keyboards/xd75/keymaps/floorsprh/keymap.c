/* Copyright 2019 IOD & floor667
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

#define _COLE 0
#define _QWER 1
#define _FUNC 2
#define _NUMB 3
#define _MOUS 4

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes { 
  MO_UL = SAFE_RANGE,
  MO_UR,
  MO_DL,
  MO_DR,
  MO_DC,
  DBL_ANG,
  DBL_PAR,
  DBL_SQR,
  DBL_BRC,
  DBL_QUO,
  DBL_DQT,
  DBL_GRV,
  SC_VIW,
  SC_VIQ,
  SC_VIS,
  SC_SCTAB,
  SC_SCQ,
  SC_SCN,
  SC_GNX,
  SC_GTB,
  SC_GON,
  SC_GCL,
  SC_GRE,
  KC_UPHO,
  KC_DNEN,
  MOV,
  PAD
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLE] = LAYOUT(/* Colemak Base */
               KC_NO, KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC, \
               KC_UPHO, KC_TAB,    KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,  KC_SCLN,  KC_BSPC, KC_LBRC, KC_BSLS, \
             KC_DNEN, PAD,     KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O, KC_QUOT,       KC_ENT, KC_NO, \
           KC_NO, KC_LSFT,       KC_Z,    KC_X,    LSFT_T(KC_C),    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,              KC_RSFT, KC_NO, KC_DELETE,\
          TT(_MOUS),  MOV, KC_NO,  LALT_T(KC_TAB),     KC_NO,  KC_NO,  KC_NO,       KC_SPC,     KC_NO,  KC_NO,                 KC_LGUI,       KC_RCTL, KC_RALT,    KC_LOCK, MO(_FUNC)\
				 ),
				 
    [_QWER] = LAYOUT(/* Base */
            KC_NO,     KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,   KC_BSPC, \
            KC_UPHO,   KC_TAB,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS, \
           KC_DNEN,  KC_CAPS,     KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,       KC_ENT,  KC_NO,\
           KC_NO, KC_LSFT,       KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,              KC_RSFT, KC_NO, KC_UP,\
           KC_NO, TT(_MOUS),  MOV, LALT_T(KC_TAB),     KC_NO,  KC_NO,  KC_NO,       KC_SPC,     KC_NO,  KC_NO,                 KC_LGUI,       KC_RCTL, KC_RALT,    KC_LOCK, MO(_FUNC)\
				 ),
				 
    [_FUNC] = LAYOUT(/* Movement + Shortcuts */
              KC_NO,    DBL_GRV,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11, KC_F12,   KC_DEL, \
           KC_NO,   _______,    _______,   KC_PSCR, KC_SLCK,    KC_PAUS, _______,  DBL_PAR, DBL_SQR, DBL_ANG, _______, KC_UPHO, _______, _______, KC_INS, \
          KC_NO,  _______, SC_SCTAB, C(KC_W), SC_VIW, SC_VIQ,  _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_DNEN, DBL_QUO,      KC_ENT,  KC_NO,\
         KC_NO, _______,       SC_GCL, SC_GRE, SC_GNX, SC_GTB, SC_GON,    _______, KC_MINS, KC_EQL,    _______,    _______,    _______, KC_NO, _______,\
           KC_NO, _______,     _______,    _______,  KC_NO, KC_NO, KC_NO,      _______,    KC_NO, KC_NO,          _______,    _______,       _______, KC_NO, _______\
				 ),
				 
    [_NUMB] = LAYOUT(
               KC_NO,  KC_GRV,  KC_F13,    KC_F14,    KC_F15,    KC_F16,    KC_F17,    KC_F18,    KC_F19,    KC_F20,    KC_F21,    KC_F22,    KC_F23, KC_F24,   KC_DEL, \
           KC_NO,  _______, _______,    _______,   _______,  _______,    DBL_BRC, DBL_PAR, KC_7, KC_8,  KC_9, KC_0,    _______, KC_BRID, KC_BRIU, \
          KC_NO,  _______,       _______,    _______,   _______,    _______,   DBL_QUO, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,     _______,       KC_ENT,  KC_NO,\
         KC_NO, _______,       _______,    _______,   _______,    _______,    DBL_SQR,  KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC, _______,  KC_NO, _______,\
           KC_NO, _______,     _______,    _______,  KC_NO, KC_NO, KC_NO,      _______,    KC_NO, KC_NO,          _______,    _______,       _______,  KC_NO, _______\
				 ),

    [_MOUS] = LAYOUT(/* Squeak Squeeek */
                KC_NO, KC_GRV,  KC_F13,    KC_F14,    KC_F15,    KC_F16,    KC_F17,    KC_F18,    KC_F19,    KC_F20,    KC_F21,    KC_F22,    KC_F23, KC_F24,   KC_DEL, \
            KC_NO, _______, _______,    _______,   _______,  _______,    KC_MNXT,    _______, MO_UL, MO_UR, KC_WH_L, KC_WH_U, KC_WH_R, KC_BRID, KC_BRIU, \
            KC_NO, RESET,   _______,    _______,  DF(_QWER), DF(_COLE),    KC_MPRV,    KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,     _______,       KC_ENT,  KC_NO,\
           KC_NO,_______,       _______,    _______,   _______,    _______,    KC_MPLY,    MO_DC, MO_DL, MO_DR, KC_BTN2, KC_BTN3,  _______, KC_NO,KC_PGUP,\
           KC_NO, _______,     _______,    _______,  KC_NO, KC_NO, KC_NO,      KC_BTN1,    KC_NO, KC_NO,          KC_BTN2,    _______,       _______,  KC_NO, _______\
				 )

};



// mouse lock indicator	
static bool ms_lock = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;


  switch(keycode) {
// layer switch w/shift
    case KC_L:
      if (record->event.pressed){
        key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_RSFT) ) {
		register_code(KC_LSFT);
	}
        layer_on(_FUNC);
      } else {
	layer_off(_FUNC);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode); 
        } else {
	unregister_code(KC_LSFT);
	}
      }
        return false;
	break;
    case MOV:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_RSFT) ) {
		register_code(KC_LSFT);
	}
        layer_on(_FUNC);
      } else {
	layer_off(_FUNC);
	unregister_code(KC_LSFT);
      }
	break;
    case PAD:
      if (record->event.pressed){
        key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_RSFT) ) {
		register_code(KC_LSFT);
	}
        layer_on(_NUMB);
      } else {
	layer_off(_NUMB);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(KC_ESC); 
        }
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
// One key bracket
    case KC_LBRC:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_RBRC);
      } else {                               
        if (get_mods() & MOD_BIT(KC_LALT)) {
	  unregister_code(KC_LALT);
                SEND_STRING("[]"SS_TAP(X_LEFT));
	  register_code(KC_LALT);
	} else {
	  tap_code(KC_LBRC);
	}
      }
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
       	} else {
          unregister_code(KC_BTN1);
        }
      }
    return false;
    break; 
// guictlalt
    case KC_LGUI:
      if(record->event.pressed) {
	key_timer = timer_read();
	register_code(KC_RCTL);
	register_code(KC_RALT);
      } else {
	unregister_code(KC_RCTL);
	unregister_code(KC_RALT);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	  tap_code(KC_LGUI);
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
        case DBL_GRV:
            if( record->event.pressed ) {
                tap_code(KC_GRV);
                tap_code(KC_GRV);
                tap_code(KC_LEFT);
            }
            return false;
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
	 case SC_SCTAB:
	    if( record->event.pressed ) {
		register_code(KC_LCTRL);
		register_code(KC_A);
		unregister_code(KC_A);
		unregister_code(KC_LCTRL);
		register_code(KC_TAB);
		unregister_code(KC_TAB);
	    }
	    return false;
	    break;              
	 case SC_SCN:
	    if( record->event.pressed ) {
		register_code(KC_LCTRL);
		register_code(KC_A);
		unregister_code(KC_A);
		unregister_code(KC_LCTRL);
		register_code(KC_C);
		unregister_code(KC_C);
	    }
	    return false;
	    break;              
	 case SC_SCQ:
	    if( record->event.pressed ) {
		register_code(KC_LCTRL);
		register_code(KC_A);
		unregister_code(KC_A);
		unregister_code(KC_LCTRL);
		register_code(KC_BSLASH);
		unregister_code(KC_BSLASH);
	    }
	    return false;
	    break;              
	  case SC_GNX:
	    if( record->event.pressed ) {
	        tap_code(KC_LGUI);
	        tap_code(KC_SPC);
		}
	    return false;
	    break;              
	  case SC_GTB:
	    if( record->event.pressed ) {
	        tap_code(KC_LGUI);
		tap_code(KC_TAB);
		}
	    return false;
	    break;              
	  case SC_GON:
	    if( record->event.pressed ) {
	        tap_code(KC_LGUI);
		register_code(KC_LSFT);
		tap_code(KC_Q);
		unregister_code(KC_LSFT);
		}
	    return false;
	    break;              
	  case SC_GRE:
	    if( record->event.pressed ) {
	        tap_code(KC_LGUI);
		register_code(KC_LSFT);
		tap_code(KC_R);
		unregister_code(KC_LSFT);
		}
	    return false;
	    break;              
	  case SC_GCL:
	    if( record->event.pressed ) {
	        tap_code(KC_LGUI);
		tap_code(KC_MINS);
		}
	    return false;
	    break;              
    }
    return true;
}

void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

void led_set_user(uint8_t usb_led) {

}

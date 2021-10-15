/* Copyright 2019
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
 */

#include QMK_KEYBOARD_H
//#include "xd75.h"
#include "mousekey.h"

enum layers {
  _COLE,
  _NUM,
  _SYM,
  _EDIT,
};

enum keycodes {
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
  KC_GUCA,
  KC_ALLK,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_COLE] = { 
  { KC_F1, KC_F2,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,  KC_TILD, KC_6,    KC_7,    KC_8,    KC_9,    KC_0, KC_TAB, KC_GRV,  },
 {   KC_F3, KC_F4, KC_Q,  KC_W,  KC_F, KC_P,  KC_G, KC_UPHO,  KC_J,  KC_L,  KC_U,  KC_Y, KC_SCOLON, KC_ESC, KC_BSPC, },
 {  KC_F5, KC_F6,  KC_A,  KC_R,  KC_S,  KC_T,  KC_D, KC_DNEN,  KC_H,  KC_N,  KC_E,  KC_I, KC_O, KC_NO, KC_QUOT, },
 {   KC_F7, KC_F8, KC_Z,  KC_X, LSFT_T(KC_C),  LT(_NUM,KC_V),  LT(_SYM,KC_B), KC_ALLK, LT(_SYM,KC_K), LT(_NUM,KC_M),  RSFT_T(KC_COMM), KC_DOT, KC_SLSH, KC_ENTER, KC_BSLS, },
 {   KC_F9, KC_F10, XXXXXXX, XXXXXXX, LT(_EDIT,KC_TAB), KC_LALT, KC_SPACE, KC_BSPC, KC_NO, KC_RCTL, KC_RALT,  KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  },
},

[_NUM] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 {  _______, _______,   _______, _______, _______, _______, _______, DBL_BRC, DBL_PAR, KC_P7, KC_P8,  KC_P9, KC_NLCK, _______, _______,  },
 {  _______, _______,    SC_SCTAB, SC_SCQ, SC_VIS, SC_VIW, SC_VIQ, DBL_QUO, KC_EQUAL, KC_P4, KC_P5, KC_P6, KC_MINS, _______, _______,  },
 {  _______, _______,   SC_GCL, SC_GRE, SC_GON, SC_GTB, SC_GNX, DBL_SQR,  KC_LBRC,  KC_P1, KC_P2,  KC_P3, KC_RBRC, _______, _______,  },
 {  _______, _______,   _______, _______, KC_LCTL, _______, _______, _______, _______,  KC_P0, KC_DOT, _______, _______, _______,  _______ },
},

[_SYM] = {
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { _______, _______,  KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, DBL_ANG, DBL_PAR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______, _______,  },
  { _______, _______,  KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK, DBL_DQT, KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, _______, _______,  },
  { _______, _______,  KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,  DBL_BRC, KC_LCBR,  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR, _______, _______,  },
  { _______, _______,  _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,  _______ },
},

[_EDIT] = {
  { RGB_RMOD, RGB_MOD, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
  { RGB_SAD, RGB_SAI,  AU_TOG, CK_TOGG, CK_DOWN, CK_UP,  RESET, _______, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, _______, _______,  },
  { RGB_HUD, RGB_HUI, _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______, _______,  },
  { RGB_VAD, RGB_VAI,  _______, _______, _______, _______, _______, _______, MO_DC, MO_DL, MO_DR, KC_BTN2, KC_BTN3,  _______, _______,  },
  { _______, RGB_TOG,  _______, _______, _______, _______, _______, KC_NO, KC_BTN1, KC_BTN2, _______, _______, _______, _______,  _______ },
},
  
};

// odd mods - defines in macros - by canatella
#define maybe_add_weak_mods(keycode, mod)                               \
  if (keycode < QK_MODS_MAX &&                                          \
      (keycode & 0xff00) == QK_ ## mod)                                 \
    add_weak_mods(MOD_BIT(KC_ ## mod))

static bool alternate_modifier(uint16_t modifier, uint16_t keycode, keyrecord_t *record) {
  static bool in_alternate_modifier;

  /* when it's a key press and modifier state is pressed */
  if (record->event.pressed && (get_mods() & MOD_BIT(modifier))) {
    in_alternate_modifier = true;

    /* will send modifier up so that the os won't shift the keycode we will send */
    del_mods(MOD_BIT(modifier));

    /* send mods if keycode needs it */
    maybe_add_weak_mods(keycode, LCTL);
    maybe_add_weak_mods(keycode, LSFT);
    maybe_add_weak_mods(keycode, LALT);
    maybe_add_weak_mods(keycode, LGUI);
    maybe_add_weak_mods(keycode, RCTL);
    maybe_add_weak_mods(keycode, RSFT);
    maybe_add_weak_mods(keycode, RALT);
    maybe_add_weak_mods(keycode, RGUI);

    /* send mods modifications */
    send_keyboard_report();

    /* send alternate key code */
    register_code(keycode);

    /* we changed the internal state by releasing the modifier key, marked against
       as pressed so that we are back in the real state */
    add_mods(MOD_BIT(modifier));

    return false;
  }

  /* when releasing the key and we activated alternate modifier */
  if (!record->event.pressed && in_alternate_modifier) {
    in_alternate_modifier = false;

    /* release the alternate key */
    unregister_code(keycode);

    /* make sure all mods we sat up earlier are released */
    clear_weak_mods();

    /* send mods modification */
    send_keyboard_report();

    return false;
  }


  return true;
}

// mouse lock indicator	
static bool ms_lock = false;
static bool false_def = false;
//static bool shifted_l = false;
static bool alt_lock = false;
static bool allkon = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static uint8_t layer_lock;

  if(false_def && biton32(layer_state) != layer_lock) {
    layer_on(layer_lock);
  }
  if(alt_lock && !(keyboard_report->mods & MOD_BIT(KC_LALT)) ) {
    register_code(KC_LALT);
  }

  switch(keycode) {
// One key pgup/home
    case KC_UPHO:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > 343) {   
        tap_code(KC_HOME);
      } else {                               
        if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
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
      if (timer_elapsed(key_timer) > 343) {   
        tap_code(KC_END);
      } else {                               
        if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
	  clear_mods();
	  tap_code(KC_DELETE);
	  register_code(KC_LALT);
	} else {
	  tap_code(KC_PGDN);
	}
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
        } else if (timer_elapsed(key_timer) > 343) {   
	  ms_lock = true;
       	} else {
          unregister_code(KC_BTN1);
        }
      }
    return false;
    break; 
// guictl
    case KC_GUCA:
      if(record->event.pressed) {
	key_timer = timer_read();
	register_code(KC_RCTL);
	register_code(KC_RALT);
      } else {
	unregister_code(KC_RCTL);
	unregister_code(KC_RALT);
        if (timer_elapsed(key_timer) < 343) {   
	  tap_code(KC_LGUI);
	}
      }
      break;
// caps sounds and layer locking
    case KC_ALLK:
      if(record->event.pressed) {
if (keyboard_report->mods & MOD_BIT(KC_RCTL)) {
	    tap_code(KC_CLCK);
	  } else if(allkon) {
	       allkon = false;
        if (alt_lock) {
	  unregister_code(KC_LALT);
	  alt_lock = false;
	} else if ( layer_state != _COLE ) {
	    false_def = false;
	    layer_off(layer_lock);
	  } 

       } else {
	       allkon = true;
        if (keyboard_report->mods & MOD_BIT(KC_LALT)) {
	  alt_lock = true;
//    register_code(KC_LALT);
	} else if ( layer_state != _COLE ) {
	    layer_lock = biton32(layer_state);
	    layer_clear();
	    false_def = true;
    layer_on(layer_lock);
	   } else {
	       allkon = false;
	key_timer = timer_read();
	register_code(KC_RCTL);
	register_code(KC_RALT);
	}
	} 
      } else {
	  unregister_code(KC_RCTL);
	  unregister_code(KC_RALT);
          if (timer_elapsed(key_timer) < 343) {   
	    tap_code(KC_LGUI);
	  }
	}
     
      return false;
      break;
    case KC_NLCK:
      if(record->event.pressed) {
        if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
	} else {
	}
      }
      return true;
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
	case SC_VIS:
	    if( record->event.pressed ) {
		register_code(KC_LCTRL);
		register_code(KC_W);
		unregister_code(KC_W);
		unregister_code(KC_LCTRL);
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
// Irregular mod effects
    case KC_H:
      return alternate_modifier(KC_LALT, KC_LEFT, record);
    case KC_N:
      return alternate_modifier(KC_LALT, KC_DOWN, record);
    case KC_E:
      return alternate_modifier(KC_LALT, KC_UP, record);
    case KC_I:
      return alternate_modifier(KC_LALT, KC_RIGHT, record);
    case KC_O:
      return alternate_modifier(KC_LALT, KC_QUOT, record);
    case KC_ESC:
      return alternate_modifier(KC_LALT, KC_GRV, record);
//    case KC_SCOLON:
//      return alternate_modifier(KC_LALT, KC_ESC, record);
    case KC_SLSH:
      return alternate_modifier(KC_LALT, KC_BSLS, record);
//    case KC_BSPC:
//      return alternate_modifier(KC_LALT, KC_ENTER, record);
  }
  return true;
}


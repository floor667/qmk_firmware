#include QMK_KEYBOARD_H
#include "mousekey.h"

enum layers{
  _BASE,
  _NUM,
  _SYM,
  _NAV,
  _MSE
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,  KC_W,  KC_F, KC_P, KC_G, KC_ESC,  KC_J,  KC_L,  KC_U,  KC_Y, KC_BSPC,
    KC_A,  KC_R,  KC_S, KC_T, KC_D,          KC_H,  KC_N,  KC_E,  KC_I, KC_O,
    KC_Z,  KC_X,  KC_C, KC_V, KC_B,          KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH,
                        NAMS, LSFT_T(KC_SPC),            KC_RSFT, MODF
  ),

[_NUM] = LAYOUT(
    SC_SCQ, SC_VIS, SC_VIW, SC_VIQ, KC_NO, _______, KC_SCLN, KC_7, KC_8,  KC_9, KC_BSPC,
     SC_GCL, SC_GRE, SC_GNX, SC_GTB, SC_GON,        KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,
    _______, _______, _______, _______, _______,    KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC,
                                KC_CAPS,   KC_TRNS,            KC_0,  KC_DOT
  ),

[_SYM] = LAYOUT_planck_grid(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_NO, DBL_PAR, KC_AMPR, KC_ASTR, KC_LPRN, KC_BSPC,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK,           KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,           KC_LCBR,  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR,
                        OSM(MOD_LALT), KC_TRNS,           KC_RPRN,  KC_TRNS
),

  [_NAV] = LAYOUT(
      RESET,  _______,  KC_NO,  KC_NO,  _______, KC_TRNS,   KC_TAB,  KC_PGDN,  KC_PGUP,  KC_BSLS,   KC_ESC,
    RGB_TOG, KC_NO,  KC_NO,  KC_NO,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   KC_ENT,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,           KC_DOT,    KC_QUOT,  KC_GRV,   KC_DOT,  KC_BSLS,
                                  KC_TRNS,KC_TRNS,           KC_TRNS,  KC_TRNS
  ),

[_MSE] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,    RESET,  KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   AU_TOG,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,
    WORD, _______, _______, _______, KC_MUTE, _______, MO_DC, MO_DL, MO_DR, KC_BTN2, KC_BTN3,  _______,
    _______, _______, _______, _______, _______, KC_NO, _______, KC_BTN1, KC_BTN2, _______, _______, _______
),
};

/*static bool lsfton = false;
static bool rsfton = false;
static bool modshft = false;*/

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
	clear_mods();
        register_code(KC_LSFT);
	}
        layer_on(NUM);
      } else {
	layer_off(NUM);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode);
        } else {
          unregister_code(KC_LSFT);
	}
      }
      return false;
	break;
// nav (+ shift) and mouse w/ esc
    case NAMS:
      if (record->event.pressed){
	key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_LCTL)) {
	  layer_on(_MSE);
	} else if (get_mods() & MOD_BIT(KC_RSFT)) {
	  register_code(KC_LSFT);
	  layer_on(_NAV);
	} else {
	  layer_on(_NAV);
	}
      } else {
	layer_clear();
	clear_mods();
        /*if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	  tap_code(KC_ESC);
	} */
      }
      break;
// layer space shift
/*    case KC_LSS:
      if (record->event.pressed){
      key_timer = timer_read();
      lsfton = true;
      if(modshft) {
	//register_code(KC_SPC);
	layer_on(_MSE);
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
	  layer_off(_MSE);
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
	if(layer_state == _NUM) {
	  register_code(KC_0);
	} else {
	  register_code(KC_RPRN);
	}
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
	if(layer_state == _NUM) {
	  unregister_code(KC_0);
	} else {
	  unregister_code(KC_RPRN);
	}
	}
      } else {
          unregister_code(KC_RSFT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
            tap_code(KC_ENT);
	  }
      }
    }
    break;*/
// Sticky shift
    case KC_CAPS:
      if (record->event.pressed){
        register_code(KC_RSFT);
      }
    return false;
    break;
// One key pgup/home
    case KC_PGUP:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_HOME);
      } else {                               
	  tap_code(KC_PGUP);
      }
	}
    return false;
    break;
// One key pgdn/end
    case KC_PGDN:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_END);
      } else {                               
	  tap_code(KC_PGDN);
      }
    }
    return false;
    break;
// One key q/esc
/*    case KC_Q:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_ESC);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(beep);
#endif
      } else {                               
	  tap_code(KC_Q);
      }
    }
    return false;
    break;
// One key colon
    case KC_SCOLON:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
	register_code(KC_LSFT);
        tap_code(KC_SCOLON);
	unregister_code(KC_LSFT);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(beep);
#endif
      } else {                               
	  tap_code(KC_SCOLON);
      }
    }
    return false;
    break;*/
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
	register_code(KC_LCTL);
	if (get_mods() & MOD_BIT(KC_LSFT)) {
	  register_code(KC_RALT);
	}
      } else {
	unregister_code(KC_LCTL);
	if (get_mods() & MOD_BIT(KC_RALT)) {
	  unregister_code(KC_RALT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	    unregister_code(KC_LSFT);
	    tap_code(KC_LGUI);
	  }
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
  return true;
}

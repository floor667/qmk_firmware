#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "hidd.c"

extern keymap_config_t keymap_config;

enum _layers{
  _BASE,
  _NUM,
  _SYM,
  _NAV,
  _MSE
};

enum _keycodes {
  MO_UL = SAFE_RANGE,
  MO_UR,
  MO_DL,
  MO_DR,
  MO_DC,
  SC_VIW,
  SC_VIQ,
  MODF,
  NAMS,
  WORD,
  WORDT,
  KC_LSS,
  KC_LES,
  KC_LAYR
};

enum _td {
  CT_MVMT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,  KC_W,  KC_F, KC_P, KC_G, KC_NO, KC_J,  KC_L,  KC_U,  KC_Y, KC_BSPC, KC_NO,
    KC_A,  KC_R,  KC_S, KC_T, KC_D, KC_NO, KC_H,  KC_N,  KC_E,  KC_I, KC_O, KC_NO,
    KC_Z,  KC_X,  KC_C, KC_V, KC_B, KC_NO, KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_NO,
    MO(_MSE), KC_RCTL, TD(CT_MVMT), KC_LAYR, MT(MOD_LSFT,KC_SPC), KC_NO, KC_NO, KC_LAYR, MODF, KC_LCTL, KC_LALT, KC_NO
  ),

[_NUM] = LAYOUT(
    KC_NO, KC_NO, SC_VIW, SC_VIQ, KC_NO, KC_NO, KC_SCLN, KC_7, KC_8,  KC_9, KC_BSPC, KC_NO,
    KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS, KC_NO,
    _______, _______, C(A(KC_C)), C(A(KC_V)), _______, KC_NO,   KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC, KC_NO, 
    _______, _______, KC_CAPS, _______,  KC_NO, _______, KC_0, KC_TRNS,  KC_TRNS, _______, _______, _______
  ),

[_SYM] = LAYOUT(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_NO, KC_COLON, KC_AMPR, KC_ASTR, S(KC_9), KC_BSPC, KC_NO,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK,  KC_NO,       KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, KC_NO,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,  KC_NO,         S(KC_LBRC),  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR, KC_NO,
    KC_NO, KC_NO, OSM(MOD_LALT), KC_TRNS, KC_NO, KC_NO, KC_RPAR, KC_TRNS,  KC_TRNS, KC_NO, KC_NO, KC_NO
),

  [_NAV] = LAYOUT(
    RESET,  _______,  KC_NO,  KC_NO,  LCA(KC_ESC), KC_NO, KC_GRV,  KC_PGDN,  KC_PGUP,  KC_NO,   KC_ESC, KC_NO,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,          KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   KC_ENT, KC_NO,
    KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,   KC_NO,        KC_QUOT,    KC_VOLD,  KC_VOLU,   KC_BSLS,   KC_TAB, KC_NO,
    _______, _______, _______, _______,  _______, _______, _______, KC_TRNS,  KC_TRNS, _______, _______, _______
  ),

[_MSE] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, KC_NO,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, KC_NO,
    KC_NO, WORD, WORDT, _______, KC_NO, KC_NO,       MO_DC, MO_DL, MO_DR, KC_NO, KC_BTN3, KC_NO,
      _______, KC_NO, KC_NO, _______, KC_NO, KC_NO, KC_BTN1, KC_BTN2, KC_NO, KC_NO, KC_NO, KC_NO
),
};

void dance_mvmt_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count <= 4) {
        if (get_mods() & MOD_BIT(KC_LCTL)) {
	  layer_on(_MSE);
	  } else if (get_mods() & MOD_BIT(KC_RSFT)) {
	  register_code(KC_LSFT);
	  layer_on(_NAV);
	} else {
	  layer_on(_NAV);
        }
  }
  if (state->count >= 3) {
    layer_on(_MSE);
  }
}

void dance_mvmt_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 1) {
  layer_clear();
  unregister_code(KC_LSFT);
  }
  }

qk_tap_dance_action_t tap_dance_actions[] = {
    [CT_MVMT] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_mvmt_finished, dance_mvmt_reset),
};

static bool lsfton = false;
static bool rsfton = false;
static bool modshft = false;
static bool rfrst = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static bool ms_lock = false;

  switch(keycode) {
// layer switch w/shift
/*    case KC_A: case KC_O:
      if (record->event.pressed){
        key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
        layer_on(_SYM);
	} else {
        layer_on(_NUM);
	}
      } else {
	layer_clear();
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode);
        }
      }
      return false;
	break; */
// nav (+ shift) and mouse w/ esc
    case NAMS:
      if (record->event.pressed){
	key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_LGUI)) {
          clear_mods();
	  layer_on(_MSE);
	  } else if (get_mods() & MOD_BIT(KC_RSFT)) {
	  register_code(KC_LSFT);
	  layer_on(_NAV);
	} else {
	  layer_on(_NAV);
	}
      } else {
	layer_clear();
        unregister_code(KC_LSFT);
        /*if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	  tap_code(KC_ESC);
	} */
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
    break;*/
// One key colon
    case KC_J:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_SCOLON);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(beep);
#endif
      } else {                               
	  tap_code(KC_J);
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
	 unregister_code(KC_LCTL);
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
//doubles on open keys--
/*	case KC_LBRC: case KC_9:
	    if( record->event.pressed ) {
		key_timer = timer_read();
	    } else {
        	if (timer_elapsed(key_timer) > TAPPING_TERM) {   
                   tap_code(keycode);
                   tap_code(keycode + 1);
		   clear_mods();
                   tap_code(KC_LEFT);
                } else {                               
	    	       tap_code(keycode);
		}
	    }
	    
	    return false;
	    break;*/
  }
  return true;
}



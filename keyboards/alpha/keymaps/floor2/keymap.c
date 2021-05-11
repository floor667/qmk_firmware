#include QMK_KEYBOARD_H

enum layer_names {
    HOME,
    NAV,
    NUM,
    MSE,
};

enum custom_keycodes {
  DBL_ANG = SAFE_RANGE,
  DBL_PAR,
  DBL_SQR,
  DBL_BRC,
  DBL_QUO,
  DBL_DQT,
  SC_VIW,
  SC_VIQ,
  SC_VIS,
  SC_GNX,
  SC_GTB,
  SC_GON,
  SC_GCL,
  SC_GRE,
  KC_UPHO,
  KC_DNEN,
  KC_GUCA
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

static uint16_t key_timer;

		switch (keycode) {
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
        }
        unregister_code(KC_LSFT);
      }
      return false;
	break;
// layer switch w/shift
    case KC_C:
      if (record->event.pressed){
        key_timer = timer_read();
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)){
	clear_mods();
        register_code(KC_LSFT);
	}
        layer_on(NAV);
      } else {
	layer_off(NAV);
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode);
        }
        unregister_code(KC_LSFT);
      }
      return false;
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
// vim and screen shortcuts
	case SC_VIW:
	    if( record->event.pressed ) {
		tap_code(KC_ESCAPE);
		register_code(KC_LSHIFT);
		tap_code(KC_SCOLON);
		unregister_code(KC_LSHIFT);
		tap_code(KC_W);
		tap_code(KC_ENTER);
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
// One key pgup/home
    case KC_UPHO:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_HOME);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(homeb);
#endif
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
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_END);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(endb);
#endif
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
// guictl
    case KC_GUCA:
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
      break;
	}
	return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
	[HOME] = LAYOUT(
		KC_Q, KC_W, KC_F, KC_P, KC_G, LT(MSE,KC_J), KC_L, KC_U, KC_Y, KC_BSPC,
		KC_A, KC_R, KC_S, KC_T, KC_D, KC_H, KC_N, KC_E, KC_I, KC_O,
		KC_Z, MT(MOD_LSFT,KC_X), KC_C, LT(MSE,KC_V), KC_SPC, MT(MOD_RCTL,KC_K), MT(MOD_RSFT,KC_M), KC_B),

	[NAV] = LAYOUT(
		KC_NO, KC_NO, RESET, KC_INS, KC_UPHO, KC_QUOT, KC_TAB, KC_GRV, KC_BSLS, KC_ESC,
		KC_NO, KC_NO, KC_END, KC_DEL, KC_DNEN, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, KC_ENT,
		_______, _______, _______, KC_LGUI, KC_NO, KC_COMM, KC_DOT, KC_SLSH),

	[NUM] = LAYOUT(
		KC_NO, SC_VIS, SC_VIW, SC_VIQ,  KC_SCLN, DBL_SQR, KC_7, KC_8, KC_9, KC_0,
		KC_NO, KC_NO, KC_NO, KC_NO,  KC_SCLN, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,
		OSM(MOD_LCTL), OSM(MOD_LALT), OSM(MOD_LGUI), TG(MSE), _______, KC_1, KC_2, KC_3),

	[MSE] = LAYOUT(
		KC_F9, KC_F10, KC_F11, KC_F12, KC_NO, TG(MSE), KC_NO, KC_WH_L, KC_WH_R, KC_WH_U,
		KC_F5, KC_F6, KC_F7, KC_F8, KC_PSCR, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,
		KC_F1, KC_F2, KC_F3, KC_F4, KC_BTN1, KC_BTN2, KC_BTN3, KC_NO),
};
	
void matrix_init_user(void) {
}

void matrix_scan_user(void) {
}

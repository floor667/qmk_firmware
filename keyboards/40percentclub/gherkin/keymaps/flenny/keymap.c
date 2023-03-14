#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "hidd.c"

enum _layers{
  _BASE,
  _NUM,
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
  WORD,
  WORDT,
  NAMS
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_3x10(
    KC_Q,  KC_W,  KC_F, KC_P, KC_G, KC_J,  KC_L,  KC_U,  KC_Y, KC_BSPC,
    KC_A,  KC_R,  LT(_NUM,KC_S),  MT(MOD_LSFT,KC_T), KC_D, KC_H,    MT(MOD_RSFT,KC_N),  LT(_NUM,KC_E),  KC_I, KC_O,
    LT(_MSE,KC_Z),  MT(MOD_LALT,KC_X), NAMS, KC_V, KC_B, KC_SPC, KC_M, KC_COMM, MT(MOD_LCTL,KC_DOT), MT(MOD_RALT,KC_SLSH)
  ),

  [_NUM] = LAYOUT_ortho_3x10(
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8,  KC_9, KC_0,
    KC_Z, KC_X,  KC_C,  KC_V,  KC_B, KC_K, KC_M, KC_COMM, KC_DOT, KC_SLSH,
    KC_F11, KC_F12, KC_LSFT, _______,  _______, KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC
  ),

  [_NAV] = LAYOUT_ortho_3x10(
    RESET,  _______,  SC_VIW,  SC_VIQ,  LCA(KC_ESC), KC_GRV,  KC_PGDN,  KC_PGUP,  KC_NO,   KC_ESC,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   KC_ENT,
    OSM(MOD_LCTL), OSM(MOD_LALT),  _______,  LM(_NUM,MOD_LSFT), OSM(MOD_LSFT),   KC_QUOT,    KC_VOLD,  KC_VOLU,   KC_BSLS,   KC_TAB
  ),

  [_MSE] = LAYOUT_ortho_3x10(
    KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U,
    KC_NO, KC_NO,   KC_NO,   KC_NO,   MO_DC,        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,
    KC_NO, WORD, WORDT, _______, KC_NO,       KC_BTN1, MO_DL, MO_DR, KC_BTN3, KC_BTN2
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static bool ms_lock = false;

  switch(keycode) {
    case KC_CAPS:
      if (record->event.pressed){
        register_code(KC_RSFT);
      }
    return false;
    break;
// One key pgup/home
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
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	  tap_code(KC_C);
	}
      }
      break;
    case KC_S: case KC_E:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LSFT) || get_mods() & MOD_BIT(KC_RSFT)) {
          clear_mods();
         //layer_on(_SYM);
        } else {
          layer_on(_NUM);
        }
      } else {
        layer_clear();
        if (timer_elapsed(key_timer) < TAPPING_TERM) {
          tap_code(keycode);
        }
      }
      break;
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
 // One key pgdn/end
    case KC_M:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_K);
      } else {                               
	  tap_code(KC_M);
      }
    }
    return false;
    break;
    case KC_1:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_0);
      } else {                               
	  tap_code(KC_1);
      }
    }
    return false;
    break;
    case KC_COMM: case KC_2:
      if (record->event.pressed){
      key_timer = timer_read();
    } else {
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
	    set_oneshot_mods(MOD_BIT(KC_LGUI));
      } else {                               
	  tap_code(keycode);
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


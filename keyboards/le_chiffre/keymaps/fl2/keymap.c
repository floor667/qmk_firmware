#include QMK_KEYBOARD_H
#include "mousekey.h"
#include "hidd.c"

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
};

enum _td {
  CT_MVMT
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_BASE] = LAYOUT(
    KC_Q,  KC_W,  KC_F, KC_P, KC_G, KC_ESC,  KC_J,  KC_L,  KC_U,  KC_Y, KC_BSPC,
    KC_A,  KC_R,  KC_S, KC_T, KC_D,          KC_H,  KC_N,  KC_E,  KC_I, KC_O,
    KC_Z,  KC_X,  KC_C, KC_V, KC_B,          KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH,
                          TD(CT_MVMT), KC_LSS,            KC_LES, MODF
  ),

[_NUM] = LAYOUT(
    KC_NO, KC_NO, SC_VIW, SC_VIQ, KC_NO, _______, KC_SCLN, KC_7, KC_8,  KC_9, KC_BSPC,
   KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,        KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,
   _______, _______, C(A(KC_C)), C(A(KC_V)), _______,    KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC,
                                KC_CAPS,  _______,            KC_TRNS,  KC_TRNS
  ),

[_SYM] = LAYOUT(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_NO, KC_COLON, KC_AMPR, KC_ASTR, S(KC_9), KC_BSPC,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK,           KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,           S(KC_LBRC),  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR,
                        OSM(MOD_LALT), KC_TRNS,           KC_TRNS,  KC_TRNS
),

  [_NAV] = LAYOUT(
      RESET,  _______,  KC_NO,  KC_NO,  LCA(KC_ESC), KC_NO,   KC_GRV,  KC_PGDN,  KC_PGUP,  KC_NO,   KC_ESC,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,            KC_LEFT,  KC_DOWN,  KC_UP,    KC_RGHT,   KC_ENT,
    KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,           KC_QUOT,    KC_VOLD,  KC_VOLU,   KC_BSLS,   KC_TAB,
                                  KC_TRNS,KC_TRNS,           KC_TRNS,  KC_TRNS
  ),

[_MSE] = LAYOUT(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,         KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,
    WORD, WORDT, _______, _______,  RGB_TOG,         MO_DC, MO_DL, MO_DR, KC_NO, KC_BTN3,
                               _______, KC_NO,         KC_BTN1, KC_BTN2
),
};

void dance_mvmt_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
        if (get_mods() & MOD_BIT(KC_LCTL)) {
	  layer_on(_MSE);
	  } else if (get_mods() & MOD_BIT(KC_RSFT)) {
	  register_code(KC_LSFT);
	  layer_on(_NAV);
	} else {
	  layer_on(_NAV);
        }
  }
  if (state->count >= 2) {
    layer_on(_MSE);
  }
}

void dance_mvmt_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count >= 1) {
  layer_clear();
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
     <> } else {
	layer_clear();
        if (timer_elapsed(key_timer) < TAPPING_TERM) {   
          tap_code(keycode);
        }
      }
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
        /*if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	  tap_code(KC_ESC);
	} */
      }
      break;
// layer space shift
    case KC_LSS:
      if (record->event.pressed){
      key_timer = timer_read();
      lsfton = true;
      if(modshft) {
	//register_code(KC_SPC);
	register_code(KC_RSFT);
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
	  register_code(KC_LSFT);
          tap_code(KC_0);
          unregister_code(KC_LSFT);
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
	  
	}
	}
      } else {
          unregister_code(KC_RSFT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
            tap_code(KC_NO);
	  }
      }
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

//  const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {200, 70, 189};

// Light LEDs 6 to 9 and 12 to 15 red when caps lock is active. Hard to ignore!
const rgblight_segment_t PROGMEM capslock_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {1, 1, HSV_RED}       // Light 4 LEDs, starting with LED 6
);
// Light LEDs 9 & 10 in cyan when keyboard layer 1 is active
const rgblight_segment_t PROGMEM base_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {0, 1, HSV_BLUE}
);
// Light LEDs 11 & 12 in purple when keyboard layer 2 is active
const rgblight_segment_t PROGMEM layer2_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_GREEN}
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM layer3_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_ORANGE}
);
const rgblight_segment_t PROGMEM layer4_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_MAGENTA} 
);
// Light LEDs 13 & 14 in green when keyboard layer 3 is active
const rgblight_segment_t PROGMEM layer5_layer[] = RGBLIGHT_LAYER_SEGMENTS(
    {9, 1, HSV_BLUE}
);

// Now define the array of layers. Later layers take precedence
const rgblight_segment_t* const PROGMEM rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    base_layer,    // Overrides caps lock layer
    capslock_layer,
    layer2_layer,    // overrides other layers
    layer3_layer,     // overrides other layers
    layer4_layer,    // overrides other layers
    layer5_layer     // overrides other layers
);

void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = rgb_layers;
 // rgblight_enable_noeeprom();
  rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_SWIRL);
  rgblight_sethsv_noeeprom(98, 200, 190);
}

bool led_update_user(led_t led_state) {
    rgblight_set_layer_state(1, led_state.caps_lock);
    return true;
}

/*layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _BASE));
    return state;
} */

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(4, layer_state_cmp(state, _NAV));
    rgblight_set_layer_state(5, layer_state_cmp(state, _MSE));
    rgblight_set_layer_state(2, layer_state_cmp(state, _NUM));
    rgblight_set_layer_state(3, layer_state_cmp(state, _SYM));
    return state;
}

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
#include "muse.h"
#include "mousekey.h"
#include "qmk_midi.h"
#include "midch.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLE,
  _NUM,
  _MOV,
  _EDIT,
  _MIDI
};

enum planck_keycodes {
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
  MAJ_B,
  MAJ_Fs, 
  MAJ_Cs, 
  MAJ_Gs, 
  MAJ_Ds
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_COLE] = LAYOUT_planck_grid(
    KC_Q,  KC_W,  LT(_MOV,KC_F),  LT(_NUM,KC_P), KC_G, KC_UPHO,  KC_J,  LT(_NUM,KC_L),  LT(_MOV,KC_U),  KC_Y, KC_SCOLON, KC_ESC,
    LSFT_T(KC_A),  KC_R,  KC_S,  KC_T,  KC_D, KC_DNEN,  KC_H,  KC_N,  KC_E,  KC_I, RSFT_T(KC_O), KC_NO,
    KC_Z,  LT(_MIDI,KC_X), KC_C, KC_V,  KC_B, KC_ALLK, KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_ENTER,
    XXXXXXX, XXXXXXX, LT(_EDIT,KC_TAB), KC_LALT, KC_SPACE, KC_BSPC, KC_NO, KC_RCTL, KC_RALT, XXXXXXX, XXXXXXX, XXXXXXX
),

[_NUM] = LAYOUT_planck_grid(
    _______, _______, _______, _______, _______, DBL_ANG, DBL_PAR, KC_7, KC_8,  KC_9, KC_0, _______,
     SC_SCTAB, SC_SCQ, SC_VIS, SC_VIW, SC_VIQ, DBL_QUO, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS, _______,
    SC_GCL, SC_GRE, SC_GON, SC_GTB, SC_GNX, DBL_SQR,  KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC, _______,
    _______, _______, KC_LCTL, _______, _______, _______, _______,  KC_0, KC_DOT, _______, _______, _______
),

[_MOV] = LAYOUT_planck_grid(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, _______, _______, KC_TAB, _______, _______, _______, KC_GRV,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT, KC_QUOT, _______,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,  _______, _______, _______,  _______, _______,  KC_BSLS, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_EDIT] = LAYOUT_planck_grid(
    AU_TOG, CK_TOGG, CK_DOWN, CK_UP,  RESET, _______, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, _______,
    _______, _______, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______,
    _______, _______, _______, _______, _______, _______, MO_DC, MO_DL, MO_DR, KC_BTN2, KC_BTN3,  _______,
    _______, _______, _______, _______, _______, KC_NO, KC_BTN1, KC_BTN2, _______, _______, _______, _______
),
  
[_MIDI] = LAYOUT_planck_grid(
      MI_B, MI_Fs, MI_Cs, MI_Gs, MI_Ds, MI_TRNSU, MI_As_2,  MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3, MI_ALLOFF,
      MI_B_1,   MI_Fs_1, MI_Cs_1, MI_Gs_1, MI_Ds_1, MI_TRNSD,   MI_F_2,   MI_Fs_2, MI_G_2,    MI_Gs_2,   MI_A_2, _______,
      MAJ_B,   MAJ_Fs, MAJ_Cs, MAJ_Gs, MAJ_Ds, _______,   MI_C_2,   MI_Cs_2, MI_D_2,    MI_Ds_2,   MI_E_2, _______,  
    _______, _______, XXXXXXX, MI_SUS, MI_VELD, MI_VELU, MI_VELU, MI_OCTD, MI_OCTU, _______,_______, _______
)
  
};

#ifdef AUDIO_ENABLE
   float beep[][2]    = SONG(TERM_SOUND);
   float enter[][2]    = SONG(EXECUTE);
   float homeb[][2]    = SONG(RAISE);
   float endb[][2]    = SONG(LOWER);
   float capson[][2]    = SONG(CAPS_LOCK_ON_TWO);
   float capsoff[][2]    = SONG(CAPS_LOCK_OFF_TWO);
   float lockon[][2]    = SONG(CAPS_LOCK_ON_SOUND);
   float lockoff[][2]    = SONG(CAPS_LOCK_OFF_SOUND);
   float numon[][2]    = SONG(NUM_LOCK_ON_SOUND);
   float numoff[][2]    = SONG(NUM_LOCK_OFF_SOUND);
   float midlay[][2]    = SONG(EOCENE);
#endif



// mouse lock indicator	
static bool ms_lock = false;
static bool false_def = false;
//static bool shifted_l = false;
static bool maj = false;
static bool allkon = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static uint8_t layer_lock;

  if(false_def && biton32(layer_state) != layer_lock) {
    layer_on(layer_lock);
  }

  switch(keycode) {
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
// caps sounds and layer locking
    case KC_ALLK:
      if(record->event.pressed) {
if (keyboard_report->mods & MOD_BIT(KC_RCTL)) {
	    tap_code(KC_CLCK);
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(capsoff);
#endif   
	} else if ( layer_state != _COLE ) {
	    false_def = false;
	    layer_off(layer_lock);
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(lockoff);
#endif   
	   
       } else {
	       allkon = true;
	if ( layer_state != _COLE ) {
	    layer_lock = biton32(layer_state);
	    layer_clear();
	    false_def = true;
    layer_on(layer_lock);
            if(layer_lock == _MIDI) {
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(midlay);
#endif   
	    } else {
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(lockon);
#endif   
	    }	    
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
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
	    tap_code(KC_LGUI);
	  }
	}
     
      return false;
      break;
    case KC_NLCK:
      if(record->event.pressed) {
        if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(numon);
#endif   
	} else {
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(numoff);
#endif   
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
// midi chords - use octave 1 for chords, 0 (blank) for bass notes ( octaves )
    case MI_C_1 ... MI_B_1:  //minor, majors use individual codes
	    if( record->event.pressed ) {
		/*if( row == 2 ) {
		  maj = true;
		} else {
		  maj = false;
		}*/
	        chordon(keycode,maj);
	    } else {
	        chordoff(keycode,maj);
	    }
      return false;
      break;
    case MI_C ... MI_B:
	    if( record->event.pressed ) {
	        basson(keycode);
	    } else {
	        bassoff(keycode);
	    }
      return false;
      break;
    case MAJ_B:
	    if( record->event.pressed ) {
	        chordon(MI_B_1,true);
	    } else {
	        chordoff(MI_B_1,true);
	    }
      return false;
      break;
    case MAJ_Fs: 
	    if( record->event.pressed ) {
	        chordon(MI_Fs_1,true);
	    } else {
	        chordoff(MI_Fs_1,true);
	    }
      return false;
      break;
    case MAJ_Cs:
	    if( record->event.pressed ) {
	        chordon(MI_Cs_1,true);
	    } else {
	        chordoff(MI_Cs_1,true);
	    }
      return false;
      break;
    case MAJ_Gs: 
	    if( record->event.pressed ) {
	        chordon(MI_Gs_1,true);
	    } else {
	        chordoff(MI_Gs_1,true);
	    }
      return false;
      break;
    case MAJ_Ds:
	    if( record->event.pressed ) {
	        chordon(MI_Ds_1,true);
	    } else {
	        chordoff(MI_Ds_1,true);
	    }
      return false;
      break;
  }
  return true;
}

void matrix_scan_user(void) {


}

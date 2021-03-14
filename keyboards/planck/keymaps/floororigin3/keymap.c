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
#include "hidd.c"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLE,
  _NUM,
  _SYM,
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
  MAJ_Ds,
  KC_LSS,
  KC_LES,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_COLE] = LAYOUT_planck_grid(
    KC_Q,  KC_W,  KC_F, KC_P, KC_G, KC_ESC,  KC_J,  KC_L,  KC_U,  KC_Y, KC_SCLN, KC_BSPC,
    KC_A,  KC_R,  KC_S,  KC_T,  KC_D, KC_QUOT,  KC_H,  KC_N,  KC_E,  KC_I, KC_O, KC_NO,
    KC_Z,  LT(_MIDI,KC_X), KC_C, KC_V,  KC_B, KC_ALLK, KC_K, KC_M,  KC_COMM, KC_DOT, KC_SLSH, KC_ENTER,
    XXXXXXX, XXXXXXX, KC_LALT, KC_LSS, KC_NO, MO(_EDIT), KC_DEL, KC_LES, KC_LCTL, XXXXXXX, XXXXXXX, XXXXXXX
),

[_NUM] = LAYOUT_planck_grid(
    SC_SCQ, SC_VIS, SC_VIW, SC_VIQ, KC_NO, DBL_BRC, DBL_PAR, KC_7, KC_8,  KC_9, KC_0, _______,
     SC_GCL, SC_GRE, SC_GNX, SC_GTB, SC_GON, DBL_QUO, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS, _______,
    _______, _______, _______, _______, _______, DBL_SQR,  KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC, _______,
    _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______
),

[_SYM] = LAYOUT_planck_grid(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, DBL_ANG, DBL_PAR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK, DBL_DQT, KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, _______,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS,  DBL_BRC, KC_LCBR,  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR, _______,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_EDIT] = LAYOUT_planck_grid(
    KC_NO,   KC_NO,   KC_NO,   KC_NO,    RESET, KC_VOLU, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U, _______,
    KC_NO,   KC_NO,   KC_NO,   KC_NO,   AU_TOG, KC_VOLD, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, _______,
    WORD, _______, _______, _______, KC_MUTE, _______, MO_DC, MO_DL, MO_DR, KC_BTN2, KC_BTN3,  _______,
    _______, _______, _______, _______, _______, KC_NO, _______, KC_BTN1, KC_BTN2, _______, _______, _______
),
  
[_MIDI] = LAYOUT_planck_grid(
      MI_B, MI_Fs, MI_Cs, MI_Gs, MI_Ds, MI_TRNSU, MI_As_2,  MI_B_2,  MI_C_3,  MI_Cs_3, MI_D_3, MI_ALLOFF,
      MI_B_1,   MI_Fs_1, MI_Cs_1, MI_Gs_1, MI_Ds_1, MI_TRNSD,   MI_F_2,   MI_Fs_2, MI_G_2,    MI_Gs_2,   MI_A_2, _______,
      MAJ_B,   MAJ_Fs, MAJ_Cs, MAJ_Gs, MAJ_Ds, _______,   MI_C_2,   MI_Cs_2, MI_D_2,    MI_Ds_2,   MI_E_2, _______,  
    _______, _______, XXXXXXX, MI_SUS, MI_VELD, KC_NO, MI_VELU, MI_OCTD, MI_OCTU, _______,_______, _______
)
  
};

#ifdef AUDIO_ENABLE
   float beep[][2]    = SONG(TERM_SOUND);
   float enter[][2]    = SONG(EXECUTE);
   float homeb[][2]    = SONG(RAISEN);
   float endb[][2]    = SONG(LOWERN);
   float capson[][2]    = SONG(CAPS_LOCK_ON_TWO);
   float capsoff[][2]    = SONG(CAPS_LOCK_OFF_TWO);
   float lockon[][2]    = SONG(CAPS_LOCK_ON_SOUND);
   float lockoff[][2]    = SONG(CAPS_LOCK_OFF_SOUND);
   float numon[][2]    = SONG(NUM_LOCK_ON_SOUND);
   float numoff[][2]    = SONG(NUM_LOCK_OFF_SOUND);
   float midlay[][2]    = SONG(EOCENE);
#endif

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

void chordon(uint16_t keycode, bool maj)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteon(&midi_device, 0, note, velocity - 14);
    midi_send_noteon(&midi_device, 0, note + 3 + maj, velocity - 14);
    midi_send_noteon(&midi_device, 0, note - 5, velocity - 14);
}

void chordoff(uint16_t keycode, bool maj)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteoff(&midi_device, 0, note, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note + 3 + maj, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note - 5, velocity - 14);
}

void basson(uint16_t keycode)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteon(&midi_device, 0, note, velocity - 14);
    midi_send_noteon(&midi_device, 0, note + 12, velocity - 14);
}

void bassoff(uint16_t keycode)
{
    uint8_t note = midi_compute_note(keycode);
    uint8_t velocity = (midi_config.velocity + 1) * (128 / (MIDI_VELOCITY_MAX - MIDI_VELOCITY_MIN + 1));
    midi_send_noteoff(&midi_device, 0, note, velocity - 14);
    midi_send_noteoff(&midi_device, 0, note + 12, velocity - 14);
}

// mouse lock indicator	
static bool ms_lock = false;
static bool false_def = false;
//static bool shifted_l = false;
static bool alt_lock = false;
static bool maj = false;
static bool allkon = false;

static bool lsfton = false;
static bool rsfton = false;
static bool modshft = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

      //timer
static uint16_t key_timer;
static uint8_t layer_lock;

  if(false_def && biton32(layer_state) != layer_lock) {
    layer_on(layer_lock);
  }
  if(alt_lock && !(get_mods() & MOD_BIT(KC_LALT)) ) {
    register_code(KC_LALT);
  }

  switch(keycode) {
// layer space shift
    case KC_LSS:
      if (record->event.pressed){
      key_timer = timer_read();
      lsfton = true;
      if(modshft) {
	layer_on(_EDIT);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(numoff);
#endif
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
	  layer_off(_EDIT);	  
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
	  register_code(KC_ESC);
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
	  unregister_code(KC_ESC);
	}
      } else {
          unregister_code(KC_RSFT);
          if (timer_elapsed(key_timer) < TAPPING_TERM) {   
            tap_code(KC_NO);
	 }
      }
    }
    break;
// layer switch w/shift
/*    case KC_A : case KC_L:
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
	break;
	*/
// One key pgup/home
    case KC_SCLN:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LALT)) {
      key_timer = timer_read();
	} else {
	  register_code(keycode);
	}
    } else {
        if (get_mods() & MOD_BIT(KC_LALT)) {
	unregister_code(KC_LALT);
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_HOME);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(homeb);
#endif
      } else {                               
	  tap_code(KC_PGUP);
      }
	register_code(KC_LALT);
    } else {
	unregister_code(keycode);
    }
	}
    return false;
    break;
// One key pgdn/end
    case KC_O:
      if (record->event.pressed){
        if (get_mods() & MOD_BIT(KC_LALT)) {
      key_timer = timer_read();
	} else {
	  register_code(keycode);
	}
    } else {
        if (get_mods() & MOD_BIT(KC_LALT)) {
	unregister_code(KC_LALT);
      if (timer_elapsed(key_timer) > TAPPING_TERM) {   
        tap_code(KC_END);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(endb);
#endif
      } else {                               
	  tap_code(KC_PGDN);
      }
	register_code(KC_LALT);
    } else {
	unregister_code(keycode);
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
if (get_mods() & MOD_BIT(KC_RCTL)) {
	    tap_code(KC_CLCK);
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(capsoff);
#endif   
	  } else if(allkon) {
	       allkon = false;
        if (alt_lock) {
	  unregister_code(KC_LALT);
	  alt_lock = false;
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(lockoff);
#endif   
	} else if ( layer_state != _COLE ) {
	    false_def = false;
	    layer_off(layer_lock);
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(lockoff);
#endif   
	  } 

       } else {
	       allkon = true;
        if (get_mods() & MOD_BIT(KC_LALT)) {
	  alt_lock = true;
    register_code(KC_LALT);
#ifdef AUDIO_ENABLE
	  stop_all_notes();
	  PLAY_SONG(lockon);
#endif   
	} else if ( layer_state != _COLE ) {
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
	case WORD:
	    if( record->event.pressed ) {
		SEND_STRING(HIDD);
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
// Irregular mod effects
    case KC_H:
      return alternate_modifier(KC_LALT, KC_LEFT, record);
    case KC_N:
      return alternate_modifier(KC_LALT, KC_DOWN, record);
    case KC_E:
      return alternate_modifier(KC_LALT, KC_UP, record);
    case KC_I:
     return alternate_modifier(KC_LALT, KC_RIGHT, record);
    case KC_L:
     return alternate_modifier(KC_LALT, KC_TAB, record);
    case KC_ESC:
      return alternate_modifier(KC_LALT, KC_GRV, record);
    case KC_DELETE:
      return alternate_modifier(KC_LALT, KC_INSERT, record);
//    case KC_SCOLON:
//      return alternate_modifier(KC_LALT, KC_ESC, record);
    case KC_SLSH:
      return alternate_modifier(KC_LALT, KC_BSLS, record);
//    case KC_BSPC:
//      return alternate_modifier(KC_LALT, KC_ENTER, record);
  }
  return true;
}

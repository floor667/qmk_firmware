/* Copyright 2018
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
//#include "floor667.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLE = SAFE_RANGE,
  _NUM,
  _SYM,
  _EDIT,
  _MIDI
};

enum planck_keycodes {
  EDIT = SAFE_RANGE,
  MIDI,
  MO_UL,
  MO_UR,
  MO_DL,
  MO_DR,
  DBL_ANG,
  DBL_PAR,
  DBL_SQR,
  DBL_BRC,
  DBL_QUO,
  DBL_DQT,
  SC_VIW,
  SC_VIQ,
  SC_SCTAB,
  SC_SCQ,
  KC_UPHO,
  KC_DNEN
};

/*
enum tap_dance {
  TD_GUIEDIT = 0, 
  TD_NUMSYM,
  TD_ALTUND,
  TD_CTLPLUS,
  TD_UPHO,
  TD_DNEN 
};
*/

#define MIDI TG(_MIDI)

#define PHY_DEG UC(0x00b0)
#define CUR_BIT UC(0x20bf)
#define CUR_EUR UC(0x20ac)
#define CUR_BPN UC(0x00a3)
#define CHA_OM  UC(0x0950)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_COLE] = LAYOUT_planck_grid(
    KC_Q,  KC_W,  KC_F,  KC_P,  KC_G, KC_GRV, KC_UPHO,  KC_J,  KC_L,  KC_U,  KC_Y, KC_SCOLON,
    KC_A,  KC_R,  KC_S,  KC_T,  KC_D, KC_TAB, KC_DNEN,  KC_H,  KC_N,  KC_E,  KC_I, KC_O, 
    KC_Z,  KC_X,  KC_C,  KC_V,  KC_B, KC_LSFT, KC_LGUI, KC_K,  KC_M,  KC_COMM, KC_DOT, KC_SLSH,
    XXXXXXX, XXXXXXX, TT(_EDIT), LALT_T(KC_ESC), LSFT_T(KC_SPACE), TT(_NUM), TT(_SYM) RSFT_T(KC_BSPC), RCTL_T(KC_ENT), LCA_T(KC_QUOTE), XXXXXXX, XXXXXXX
),

// LSFT substituted for LCAP to give shifted numbers also with locking. Test.
// If it works locking switch could be used as layer lock on each layer via MO()?
// This would allow TT() to be exchanged for LT().
// > then rsft and tab (and so bsls into its place) could be moved if required.
// And sustain lock for MIDI.

[_NUM] = LAYOUT_planck_grid(
    PHY_DEG, CUR_BPN, CUR_BIT, CUR_EUR, CHA_OM, _______, DBL_PAR, KC_DOT, KC_7, KC_8,  KC_9, KC_0,
     SC_SCTAB, SC_SCQ, SC_SCN, SC_VIW, SC_VIQ, SC_VIS, DBL_QUO, KC_EQUAL, KC_4, KC_5, KC_6, KC_MINS,
    _______, _______, _______, _______, _______, _______,  DBL_SQR,  KC_LBRC,  KC_1, KC_2,  KC_3, KC_RBRC,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_SYM] = LAYOUT_planck_grid(
    KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, _______, DBL_ANG, DBL_PAR, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN,
    KC_F5, KC_F6, KC_F7, KC_F8, KC_SLCK, _______, DBL_DQT, KC_PLUS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS,
    KC_F1, KC_F2, KC_F3, KC_F4, KC_PAUS, _______,  DBL_BRC, KC_LCBR,  KC_EXLM,  KC_AT, KC_HASH,  KC_RCBR,
    _______, _______, _______, _______, _______, ______, _______, _______, _______, _______, _______, _______
),

[_EDIT] = LAYOUT_planck_grid(
    RESET, KC_MS_U, KC_VOLD, KC_VOLU, _______, EEP_RST, MIDI, KC_WH_L, MO_UL, MO_UR, KC_WH_R, KC_WH_U,
    KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D,
    AU_TOG, CK_TOGG, CK_DOWN, CK_UP, _______, _______, _______, _______, MO_DL, MO_DR, KC_BTN2, KC_BTN3, 
    _______, _______, _______, _______, _______, _______, _______, KC_BTN1, _______, _______, _______, _______
),

[_MIDI] = LAYOUT_planck_grid(
    MI_As,  MI_B,  MI_C_1,  MI_Cs_1, MI_D_1, MI_ALLOFF,  MIDI, MI_Ds_1, MI_E_1, MI_F_1,  MI_Fs_1, MI_G_1,
      MI_F,   MI_Fs, MI_G,    MI_Gs,   MI_A, MI_TRNS_0,  MI_TRNSU,   MI_As,   MI_B,   MI_C_1,  MI_Cs_1, MI_D_1,
      MI_C,   MI_Cs, MI_D,    MI_Ds,   MI_E, _______,  MI_TRNSD,   MI_F,    MI_Fs,  MI_G,    MI_Gs,   MI_A,  
    MI_OCTD, MI_OCTU, MI_CHD, MI_CHU,  MI_SOFT, MI_OCTD, MI_OCTU,  MI_SUS, MI_VELD, MI_VELU, KC_NO, MI_TRNS_0
)
  
};

#ifdef AUDIO_ENABLE
   float mi_on[][2]     = SONG(ZELDA_STORMS);
   float mi_off[][2]    = SONG(ZELDA_STREV);
   float beep[][2]    = SONG(TERM_SOUND);
#endif

// odd mods - defines in macros - by canatella
define maybe_add_weak_mods(keycode, mod)                               \
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch(keycode) {
// Irregular mod effects
    case KC_H:
      return alternate_modifier(KC_LALT, KC_LEFT, record);
    case KC_N:
      return alternate_modifier(KC_LALT, KC_DOWN, record);
    case KC_E:
      return alternate_modifier(KC_LALT, KC_UP, record);
    case KC_I:
      return alternate_modifier(KC_LALT, KC_RIGHT, record);
    case KC_PGUP:
      return alternate_modifier(KC_LALT, KC_INSERT, record);
    case KC_PGDN:
      return alternate_modifier(KC_LALT, KC_DELETE, record);
    case KC_SLSH:
      return alternate_modifier(KC_LALT, KC_BSLS, record);
      return alternate_modifier(KC_RCTL, KC_PIPE, record);
    case KC_BSPC:
      return alternate_modifier(KC_LALT, KC_DELETE, record);
    case KC_GRV:
      return alternate_modifier(KC_LALT, KC_PIPE, record);
    case KC_LSFT: // shifts lalt into lockable position
      return alternate_modifier(KC_RCTL, KC_LALT, record);
// One key pgup/home - should output as soon as term is reached
    case KC_UPHO:
      if(record->event.pressed){
        uphome_timer = timer_read();
        if (timer_elapsed(uphome_timer) > TAPPING_TERM) {   
          tap_code(KC_HOME);
#ifdef AUDIO_ENABLE
          stop_all_notes();
	  PLAY_SONG(beep);
#endif
	  break;
        }
      } else {
        tap_code(KC_PGUP);
      }
      break;
// One key pgdn/end - old method, waits for keyup
    case KC_DNEN:
      if(record->event.pressed){
      dnend_timer = timer_read();
    } else {
      if (timer_elapsed(dnend_timer) > TAPPING_TERM) {   
        tap_code(KC_END);
#ifdef AUDIO_ENABLE
        stop_all_notes();
	PLAY_SONG(beep);
#endif
      } else {                               
        tap_code(KC_PGDN);
      }
    }
    break;
// One key left click hold
    case KC_BTN1:
      if(state->pressed){
        unregister_code(KC_BTN1);
      } else {
        if(record->event.pressed){
          clkhold_timer = timer_read();
          if (timer_elapsed(clkhold_timer) > TAPPING_TERM) {   
            register_code(KC_BTN1);
#ifdef AUDIO_ENABLE
	    stop_all_notes();
	    PLAY_SONG(beep);
#endif
	    return false;
	    break;
	  }
        } else {
          tap_code(KC_BTN1);
        }
      }
    return false;
    break;
// MIDI layer on/off sounds
#ifdef AUDIO_ENABLE
    case MIDI:
      if (record->event.pressed) {
	if (layer_state_is(_MIDI)) {
	  stop_all_notes();
	  PLAY_SONG(mi_off);
	} else {
	  stop_all_notes();
	  PLAY_SONG(mi_on);
      }
      return true;
      break;
#endif
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
		register_code(KC_ESCAPE);
		unregister_code(KC_ESCAPE);
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
		register_code(KC_A);
		unregister_code(KC_A);
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
	}
  return true;
}


void encoder_update(bool clockwise) {
    if (clockwise) {
      register_code(KC_PGDN);
      unregister_code(KC_PGDN);
    } else {
      register_code(KC_PGUP);
      unregister_code(KC_PGUP);
    }
}

void matrix_scan_user(void) {

}

//set_unicode_input_mode(UC_LNX); //needed ?

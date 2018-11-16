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

#include "planck.h"
#include "muse.h"
#include "mousekey.h"

extern keymap_config_t keymap_config;

enum planck_layers {
  _COLE,
  _NUM,
  _SYM,
  _EDIT,
  _MIDI
};

enum planck_keycodes {
  SYM = SAFE_RANGE,
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
  SC_SCQ
};

enum tap_dance {
  TD_GUIEDIT = 0, 
  TD_NUMSYM,
  TD_ALTUND,
  TD_CTLPLUS,
  TD_UPHO,
  TD_DNEN 
};

#define EDIT TG(_EDIT)
#define MIDI TG(_MIDI)

#define PHY_DEG UC(0x00b0)
#define CUR_BIT UC(0x20bf)
#define CUR_EUR UC(0x20ac)
#define CUR_BPN UC(0x00a3)
#define CHA_OM  UC(0x0950)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  
[_COLE] = LAYOUT_planck_grid(
    KC_TAB,  KC_Q,  KC_W,  KC_F,  KC_P,  KC_G,  KC_J,  KC_L,  KC_U,  KC_Y, KC_SCOLON, KC_BSLS,
    KC_ESC,  KC_A,  KC_R,  KC_S,  KC_T,  KC_D,  KC_H,  KC_N,  KC_E,  KC_I, RALT_T(KC_O), RCTL_T(KC_QUOT),
    KC_LSFT, KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,  KC_K,  KC_M,  KC_COMM, KC_DOT, LCA_T(KC_SLSH), KC_SFTENT,
    KC_LCTL, KC_LALT, TD(TD_GUIEDIT), TD(TD_NUMSYM), LSFT_T(KC_SPACE), LSFT_T(KC_SPACE), KC_BSPC, KC_BSPC,   KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT
),

[_NUM] = LAYOUT_planck_grid(
    KC_CLCK, _______,  KC_PSCR, KC_SLCK,  KC_PAUS, KC_INS, DBL_PAR, KC_7, KC_8,  KC_9, KC_0, KC_GRV,
    LCTL_T(KC_ESC), LALT_T(PHY_DEG), CUR_BPN, CUR_BIT, CUR_EUR, KC_DEL, DBL_BRC, KC_4, KC_5, KC_6, RALT_T(KC_MINS), RCTL_T(KC_EQUAL),
    _______, SC_SCTAB, SC_SCQ, _______, SC_VIW, SC_VIQ,  DBL_SQR,  KC_1, KC_2,  KC_3, KC_LBRC,  KC_RBRC,
    _______, _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGUP, KC_PGDN, KC_END
),

[_SYM] = LAYOUT_planck_grid(
    KC_CLCK, CHA_OM, _______, _______, _______, _______, DBL_QUO, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD,
    LCTL_T(KC_F1), LALT_T(KC_F2), KC_F3, KC_F4, KC_F5, KC_F6, DBL_DQT, KC_DLR, KC_PERC, KC_CIRC, TD(TD_ALTUND), TD(TD_CTLPLUS),
    KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12,  DBL_ANG,  KC_EXLM,  KC_AT, KC_HASH, KC_LCBR,  KC_RCBR,
    _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______
),

[_EDIT] = LAYOUT_planck_grid(
    RESET, _______, KC_MS_U, KC_VOLD, KC_VOLU, _______, _______, MO_UL, MO_UR, KC_WH_L, KC_WH_U, KC_WH_R,
    _______, KC_MS_L, KC_MS_D, KC_MS_R, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, TD(TD_UPHO),
     AU_TOG, CK_TOGG, CK_DOWN, CK_UP, _______, _______, _______, MO_DL, MO_DR, KC_BTN2, KC_BTN3, TD(TD_DNEN), 
    _______, _______, _______, _______,  _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______
),

[_MIDI] = LAYOUT_planck_grid(
    MI_ALLOFF, MI_As,  MI_B,  MI_C_1,  MI_Cs_1, MI_D_1, MI_Ds_1, MI_E_1, MI_F_1,  MI_Fs_1, MI_G_1,  MIDI,
    MI_OCTU,   MI_F,   MI_Fs, MI_G,    MI_Gs,   MI_A,   MI_As,   MI_B,   MI_C_1,  MI_Cs_1, MI_D_1,  MI_TRNSU,
    MI_OCTD,   MI_C,   MI_Cs, MI_D,    MI_Ds,   MI_E,   MI_F,    MI_Fs,  MI_G,    MI_Gs,   MI_A,    MI_TRNSD,
    KC_NO, KC_NO, MI_CHD, MI_CHU,  MI_SOFT, MI_SOFT, MI_SUS,  MI_SUS, KC_NO,   MI_VELD, MI_VELU, MI_TRNS_0
)
  
};


#ifdef AUDIO_ENABLE
   float mi_on[][2]     = SONG(ZELDA_STORMS);
   float mi_off[][2]    = SONG(ZELDA_STREV);
   float beep[][2]    = SONG(TERM_SOUND);

#endif

// tapdance..
void td_numsym (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      layer_on(_NUM);
    } else {
      layer_off(_NUM);
      layer_off(_SYM);
      layer_off(_EDIT);
    }
  } else if (state->count == 2) {
    if (state->pressed) {
      layer_on(_SYM);
    } else {
      layer_on(_NUM);
    stop_all_notes();
    PLAY_SONG(beep);
    }
  } else {
    layer_on(_SYM);
    stop_all_notes();
    PLAY_SONG(beep);
  }
}

void td_numsym_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_NUM);
  } else if (state->count == 2) {
    layer_off(_SYM);
  } else {
  }
}

void td_guiedit (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      layer_on(_EDIT);
    } else {
      register_code (KC_LGUI);
//      wait_ms(130);
      unregister_code (KC_LGUI);
    }  
  } else if (state->count == 2) {
    layer_on(_EDIT);
    stop_all_notes();
    PLAY_SONG(beep);
  } else {
    layer_on(_MIDI);
    stop_all_notes();
    PLAY_SONG(mi_on);
  }
}

void td_guiedit_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_EDIT);
  } else {
//    layer_off(_EDIT);
  }
}

void td_altund (qk_tap_dance_state_t *state, void *user_data) {
  if(state->pressed) {
    register_code(KC_RALT);
  } else {
    register_code(KC_LSHIFT);
    register_code(KC_MINUS);
  }
}

void td_altund_reset (qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_RALT);
    unregister_code(KC_MINUS);
    unregister_code(KC_LSHIFT);
  }

void td_ctlplus (qk_tap_dance_state_t *state, void *user_data) {
  if(state->pressed) {
    register_code(KC_RCTL);
  } else {
    register_code(KC_LSHIFT);
    register_code(KC_EQUAL);
  }
}

void td_ctlplus_reset (qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_RCTL);
    unregister_code(KC_EQUAL);
    unregister_code(KC_LSHIFT);
  }

void td_upho (qk_tap_dance_state_t *state, void *user_data) {
  if(state->pressed) {
    register_code(KC_HOME);
  } else {
    register_code(KC_PGUP);
  }
}

void td_upho_reset (qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_HOME);
    unregister_code(KC_PGUP);
  }

void td_dnen (qk_tap_dance_state_t *state, void *user_data) {
  if(state->pressed) {
    register_code(KC_END);
  } else {
    register_code(KC_PGDOWN);
  }
}

void td_dnen_reset (qk_tap_dance_state_t *state, void *user_data) {
    unregister_code(KC_END);
    unregister_code(KC_PGDOWN);
  }

qk_tap_dance_action_t tap_dance_actions[] = {
 [TD_NUMSYM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_numsym, td_numsym_reset),
 [TD_GUIEDIT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_guiedit, td_guiedit_reset),
 [TD_ALTUND] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_altund, td_altund_reset),
 [TD_CTLPLUS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_ctlplus, td_ctlplus_reset),
 [TD_UPHO]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_upho, td_upho_reset),
 [TD_DNEN]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_dnen, td_dnen_reset)
};


bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
// MIDI layer on/off sounds
    case MIDI:
      if (record->event.pressed) {
	stop_all_notes();
	PLAY_SONG(mi_off);
      }
      return true;
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
// floor custom
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

//set_unicode_input_mode(UC_LNX); //needed ?

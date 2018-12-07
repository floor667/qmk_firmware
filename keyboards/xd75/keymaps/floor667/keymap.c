/* Copyright 2017 Wunder
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
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "xd75.h"
#include "mousekey.h"

// Layer shorthand
#define _COLE 0
#define _NUM 1
#define _SYM 2
#define _EDIT 3
#define _MIDI 4

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
  TD_UPHO,
  TD_DNEN 
};

// tapdance..
void td_numsym_finished (qk_tap_dance_state_t *state, void *user_data) {
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
    }
  } else {
    layer_on(_SYM);
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

void td_guiedit_finished (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    if (state->pressed) {
      layer_on(_EDIT);
    } else {
      register_code (KC_LGUI);
      wait_ms(130);
      unregister_code (KC_LGUI);
    }  
  } else if (state->count == 2) {
    layer_on(_EDIT);
  } else {
    layer_on(_MIDI);
  }
}

void td_guiedit_reset (qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 1) {
    layer_off(_EDIT);
  } else {
//    layer_off(_EDIT);
  }
}

void td_upho_finished (qk_tap_dance_state_t *state, void *user_data) {
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

void td_dnen_finished (qk_tap_dance_state_t *state, void *user_data) {
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
 [TD_NUMSYM] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_numsym_finished, td_numsym_reset),
 [TD_GUIEDIT] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_guiedit_finished, td_guiedit_reset),
 [TD_UPHO]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_upho_finished, td_upho_reset),
 [TD_DNEN]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_dnen_finished, td_dnen_reset)
};

#define EDIT TG(_EDIT)
#define MIDI TG(_MIDI)

#define PHY_DEG UC(0x00b0)
#define CUR_BIT UC(0x20bf)
#define CUR_EUR UC(0x20ac)
#define CUR_BPN UC(0x00a3)
#define CHA_OM  UC(0x0950)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

 [_COLE] = { /* COLEMAK */
  { MO(_EDIT),  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_GRV,  KC_EQL,  KC_6,    KC_7,    KC_8,    KC_9,    KC_0, MIDI  },
  { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_INS, KC_HOME, KC_PGUP, KC_J,    KC_L,    KC_U,    KC_Y,   KC_SCOLON,  KC_BSLS  },
  { KC_ESC, KC_A,  KC_R,  KC_S,  KC_T,  KC_D,  KC_DEL, KC_END,  KC_PGDN, KC_H,    KC_N,    KC_E,    KC_I,    LALT_T(KC_O), RCTL_T(KC_QUOT)   },
  { KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LBRC,  KC_BSLS,   KC_RBRC, KC_K,    KC_M,    KC_COMM, KC_DOT,  LCA_T(KC_SLSH), KC_SFTENT  },
  { KC_LCTL, KC_LALT, TD(TD_GUIEDIT), TD(TD_NUMSYM), LSFT_T(KC_SPACE), LSFT_T(KC_SPACE),  LSFT_T(KC_SPACE), EDIT, KC_BSPC, KC_BSPC,  KC_BSPC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT  },
 },

 [_NUM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { KC_CLCK, _______,  KC_PSCR, KC_SLCK,  KC_PAUS, KC_INS, _______, _______, _______, DBL_PAR, KC_7, KC_8,  KC_9, KC_0, KC_GRV  },
  { LCTL_T(KC_ESC), LALT_T(PHY_DEG), CUR_BPN, CUR_BIT, CUR_EUR, KC_DEL, _______, _______, _______, DBL_BRC, KC_4, KC_5, KC_6, RALT_T(KC_MINS), RCTL_T(KC_EQUAL)  },
  { _______, SC_SCTAB, SC_SCQ, _______, SC_VIW, SC_VIQ, _______, _______, _______, DBL_SQR,  KC_1, KC_2,  KC_3, KC_LBRC,  KC_RBRC  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

 [_SYM] = { /* FUNCTION */
  { KC_F1,  KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6, KC_PSCR,  KC_SLCK,  KC_PAUS,  KC_F7,    KC_F8,    KC_F9,    KC_F10,    KC_F11,    KC_F12 },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, MIDI, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_TILD  },
  { LCTL_T(KC_CLCK), LALT_T(PHY_DEG), CUR_BPN, CUR_BIT, CUR_EUR, DBL_BRC, _______, _______, _______, KC_INS, KC_DLR, KC_PERC, KC_CIRC, KC_UNDS, KC_PLUS  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_EXLM,  KC_AT, KC_HASH, KC_LCBR,  KC_RCBR  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______  },
 },

[_EDIT] = { /* MOUSE */
  { _______, _______, _______, _______, _______, _______, KC_PSCR,  KC_SLCK,  KC_PAUS,  _______, _______, _______, _______, _______, RESET },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, MO_UL, MO_UR, _______, KC_WH_U, KC_HOME  },
  { RGB_TOG, RGB_RMOD, RGB_MOD, RGB_SAD, RGB_SAI, _______, _______, _______, _______, KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_WH_D, KC_PGUP  },
  { _______, RGB_HUD, RGB_HUI, RGB_VAD, RGB_VAI, _______, _______, _______, _______, _______, MO_DL,  MO_DR,  KC_BTN2, KC_BTN3, KC_PGDN  },
  { _______, _______, _______, _______, _______, _______, _______, _______, _______, KC_BTN1, KC_BTN1, _______, _______, _______, _______  },
 },

 [_MIDI] = { /* MIDI */
  { MIDI,  MI_Ds_1, MI_E_1, MI_F_1,  MI_Fs_1, MI_G_1,  MI_Gs_1, MI_A_1, MI_As_1,  MI_B_1,  MI_C_2, MI_Cs_2,  MI_D_2, MI_Ds_2, MI_ALLOFF },
  { KC_NO, MI_As,  MI_B,  MI_C_1,  MI_Cs_1, MI_D_1, MI_Ds_1, MI_E_1, MI_F_1,  MI_Fs_1, MI_G_1,  MI_Gs_1, MI_A_1, MI_As_1, KC_NO  },
  { MI_OCTU,   MI_F,   MI_Fs, MI_G,    MI_Gs,   MI_A,   MI_As,   MI_B,   MI_C_1,  MI_Cs_1, MI_D_1, MI_Ds_1, MI_E_1, MI_F_1, MI_TRNSU  },
  { MI_OCTD,   MI_C,   MI_Cs, MI_D,    MI_Ds,   MI_E,   MI_F,    MI_Fs,  MI_G,    MI_Gs,   MI_A,  MI_As, MI_B, MI_C_1,  MI_TRNSD  },
  { KC_NO, KC_NO, MI_CHD, MI_CHU,  MI_SOFT, MI_SOFT, MI_SOFT, KC_NO, MI_SUS, MI_SUS,  MI_SUS, KC_NO,   MI_VELD, MI_VELU, MI_TRNS_0  },
 }
};

const uint16_t PROGMEM fn_actions[] = {

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
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



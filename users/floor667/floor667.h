#pragma once

#include "quantum.h"
#include "process_keycode/process_tap_dance.h"

typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

enum planck_layers {
  _COLE,
  _NUM,
  _SYM,
  _EDIT,
  _MIDI
};

//Tap dance enums
enum tap_dance {
  TD_GUIEDIT = 0, 
  TD_NUMSYM,
  TD_ALTUND,
  TD_CTLPLUS,
  TD_UPHO,
  TD_DNEN 
};

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
//void x_finished (qk_tap_dance_state_t *state, void *user_data);
//void x_reset (qk_tap_dance_state_t *state, void *user_data);
void td_numsym_finished (qk_tap_dance_state_t *state, void *user_data);
void td_numsym_reset (qk_tap_dance_state_t *state, void *user_data);
void td_guiedit_finished (qk_tap_dance_state_t *state, void *user_data);
void td_guiedit_reset (qk_tap_dance_state_t *state, void *user_data);
void td_altund_finished (qk_tap_dance_state_t *state, void *user_data);
void td_altund_reset (qk_tap_dance_state_t *state, void *user_data);
void td_ctlplus_finished (qk_tap_dance_state_t *state, void *user_data);
void td_ctlplus_reset (qk_tap_dance_state_t *state, void *user_data);
void td_upho_finished (qk_tap_dance_state_t *state, void *user_data);
void td_upho_reset (qk_tap_dance_state_t *state, void *user_data);
void td_dnen_finished (qk_tap_dance_state_t *state, void *user_data);
void td_dnen_reset (qk_tap_dance_state_t *state, void *user_data);

#ifdef AUDIO_ENABLE
   float mi_on[][2]     = SONG(ZELDA_STORMS);
   float mi_off[][2]    = SONG(ZELDA_STREV);
   float beep[][2]    = SONG(TERM_SOUND);
#endif

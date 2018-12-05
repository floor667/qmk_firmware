#include "floor667.h"
#include "quantum.h"
#include "action.h"
#include "process_keycode/process_tap_dance.h"

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
    /*
     * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     * keystrokes of the key, and not the 'double tap' action/macro.
    */
    if (state->interrupted) return DOUBLE_SINGLE_TAP;
    else if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

// tapdance..
static tap numsym_state = {
  .is_press_action = true,
  .state = 0
};

void td_numsym_finished (qk_tap_dance_state_t *state, void *user_data) {
  numsym_state.state = cur_dance(state);
  switch (numsym_state.state) {
    case SINGLE_HOLD: layer_on(_NUM); break;
    case SINGLE_TAP: layer_off(_NUM); layer_off(_SYM); layer_off(_EDIT); break;
    case DOUBLE_HOLD: layer_on(_SYM); break;
    case DOUBLE_TAP: layer_on(_NUM); 
    #ifdef AUDIO_ENABLE
    stop_all_notes(); PLAY_SONG(beep);
    #endif
    break;
    case TRIPLE_TAP: layer_on(_SYM); 
    #ifdef AUDIO_ENABLE
    stop_all_notes(); PLAY_SONG(beep);
    #endif
    break;
  }
}

void td_numsym_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (numsym_state.state) {
    case SINGLE_HOLD: layer_off(_NUM); break;
    case DOUBLE_HOLD: layer_off(_SYM); break;
  }
  numsym_state.state = 0;
}

static tap guiedit_state = {
  .is_press_action = true,
  .state = 0
};

void td_guiedit_finished (qk_tap_dance_state_t *state, void *user_data) {
  numsym_state.state = cur_dance(state);
  switch (numsym_state.state) {
    case SINGLE_HOLD: layer_on(_EDIT); break;
    case SINGLE_TAP: register_code (KC_LGUI); unregister_code (KC_LGUI); break;
    case DOUBLE_TAP: layer_on(_EDIT); 
    #ifdef AUDIO_ENABLE
    stop_all_notes();
    PLAY_SONG(beep);
    #endif
    break;
    case TRIPLE_TAP: layer_on(_MIDI); 
    #ifdef AUDIO_ENABLE
    stop_all_notes(); PLAY_SONG(beep);
    #endif
    break;
  }
}

void td_guiedit_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (guiedit_state.state) {
    case SINGLE_HOLD: layer_off(_EDIT); break;
  }
  guiedit_state.state = 0;
}

void td_altund_finished (qk_tap_dance_state_t *state, void *user_data) {
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

void td_ctlplus_finished (qk_tap_dance_state_t *state, void *user_data) {
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
 [TD_ALTUND] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_altund_finished, td_altund_reset),
 [TD_CTLPLUS] = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_ctlplus_finished, td_ctlplus_reset),
 [TD_UPHO]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_upho_finished, td_upho_reset),
 [TD_DNEN]  = ACTION_TAP_DANCE_FN_ADVANCED (NULL, td_dnen_finished, td_dnen_reset)
};


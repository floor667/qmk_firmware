/* Copyright 2020 keebzdotnet
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
#include QMK_KEYBOARD_H

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _NAV,
    _MOU,
    _GUI,
    _SEL
};
enum cu_keycode {
    KC_BTNHO,
    MO_DC,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* arrow nav */
    [_NAV] = LAYOUT(
        TO(_SEL), KC_INSERT, KC_HOME, KC_PGUP, KC_UP,
        KC_DELETE, KC_END, KC_PGDN, KC_LEFT, KC_RIGHT,
        KC_ENT, KC_LGUI, KC_LSFT, KC_DOWN
    ),
    /* mouse */
    [_MOU] = LAYOUT(
        TO(_SEL), MO_DC, KC_WH_U, KC_BTN2, KC_MS_U,
        KC_BTNHO, KC_WH_D, KC_BTN1, KC_MS_L, KC_MS_R,
        KC_BTN1, KC_WH_L, KC_WH_R, KC_MS_D
    ),
    /* gui short */
    [_GUI] = LAYOUT(
        TO(_SEL), G(KC_J), G(KC_L), G(KC_SCLN), G(KC_UP),
        G(KC_R), G(S(KC_O)), G(KC_P), G(KC_LEFT), G(KC_RIGHT),
        KC_ENT, G(C(KC_SPACE)), KC_CAPS, G(KC_DOWN)
    ),
    /* layer select */
    [_SEL] = LAYOUT(
        TO(_SEL), TO(_NAV), TO(_MOU), TO(_GUI), KC_NO,
        KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
        KC_NO, RESET, KC_NO, G(C(A(KC_ESC)))
    ),
};



// mouse lock indicator	
static bool ms_lock = false;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {



  switch(keycode) {

// One key left click hold 
    case KC_BTNHO:
      if(record->event.pressed){
	if(!ms_lock) {
          register_code(KC_BTN1);
        }
      } else {
        if (ms_lock) {
          ms_lock = false;
     	  unregister_code(KC_BTN1);
        } else {   
	  ms_lock = true;
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
  }
  return true;
}

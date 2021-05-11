#pragma once 

/* Prevent modifiers from being stuck on after layer changes. */
#define PREVENT_STUCK_MODIFIERS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
//#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
//#define LOCKING_RESYNC_ENABLE
#include "../../config.h"

#define MOUSEKEY_DELAY             100
#define MOUSEKEY_INTERVAL          40
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       15
#define MOUSEKEY_WHEEL_MAX_SPEED   9
#define MOUSEKEY_WHEEL_TIME_TO_MAX 14

#define TAPPING_TERM 432
#define TAP_CODE_DELAY 100
#define PERMISSIVE_HOLD


#define RGBLIGHT_SLEEP
#define RGBLIGHT_EFFECT_BREATHING
#define RGBLIGHT_LAYERS
//  const uint8_t RGBLED_BREATHING_INTERVALS[] PROGMEM = {30, 200, 10, 432, 78, 1422};

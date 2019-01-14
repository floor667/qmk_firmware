#pragma once 

/* Prevent modifiers from being stuck on after layer changes. */
#define PREVENT_STUCK_MODIFIERS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MOUSEKEY_DELAY             140
#define MOUSEKEY_INTERVAL          50
#define MOUSEKEY_MAX_SPEED         9
#define MOUSEKEY_TIME_TO_MAX       20
#define MOUSEKEY_WHEEL_MAX_SPEED   9
#define MOUSEKEY_WHEEL_TIME_TO_MAX 20

#define TAPPING_TERM 432
#define TAP_CODE_DELAY 100
#define PERMISSIVE_HOLD

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_DEFAULT 216.0f

#define PITCH_STANDARD_A 216.0f

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(ZELDA_PUZZLE)
#endif


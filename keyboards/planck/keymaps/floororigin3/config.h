#pragma once 

/* Prevent modifiers from being stuck on after layer changes. */
#define PREVENT_STUCK_MODIFIERS

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

#define MIDI_ADVANCED

#define MOUSEKEY_DELAY             100
#define MOUSEKEY_INTERVAL          40
#define MOUSEKEY_MAX_SPEED         8
#define MOUSEKEY_TIME_TO_MAX       18
#define MOUSEKEY_WHEEL_MAX_SPEED   8
#define MOUSEKEY_WHEEL_TIME_TO_MAX 18

#define TAPPING_TERM 432
#define TAP_CODE_DELAY 100
#define PERMISSIVE_HOLD
#define TAPPING_FORCE_HOLD
//#define TAPPING_TOGGLE 1

#define AUDIO_CLICKY
#define AUDIO_CLICKY_FREQ_DEFAULT 216.0f

#define PITCH_STANDARD_A 444.0f
#define DAC_SAMPLE_MAX 44099U

#ifdef AUDIO_ENABLE
  #define STARTUP_SONG SONG(EOCENE)
#endif

//#define COMBO_COUNT 3
//#define COMBO_TERM 163

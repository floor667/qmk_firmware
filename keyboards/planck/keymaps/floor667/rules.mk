SRC += muse.c
SRC += floor667.c

# Build Options
#   comment out to disable the options.
#
BACKLIGHT_ENABLE = no
BOOTMAGIC_ENABLE = no	# Virtual DIP switch configuration
## (Note that for BOOTMAGIC on Teensy LC you have to use a custom .ld script.)
MOUSEKEY_ENABLE = yes	# Mouse keys
EXTRAKEY_ENABLE = yes 	# Audio control and System control
CONSOLE_ENABLE = no	# Console for debug
COMMAND_ENABLE = no    # Commands for debug and configuration (changed) conflict with spcenter
#SLEEP_LED_ENABLE = no  # Breathing sleep LED during USB suspend
NKRO_ENABLE = yes	    # USB Nkey Rollover
CUSTOM_MATRIX = yes # Custom matrix file
AUDIO_ENABLE = yes
RGBLIGHT_ENABLE = no
UNICODE_ENABLE = yes
TAP_DANCE_ENABLE = yes
# SERIAL_LINK_ENABLE = no
#
# (added by floor)
MIDI_ENABLE = yes
#VIBRATO_ENABLE = yes # possible error
#FAUXCLICKY_ENABLE = yes # should be enabled automatically as part of audio? no

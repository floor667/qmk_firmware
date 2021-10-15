# MCU name
MCU = atmega32u4

# Bootloader selection
BOOTLOADER = atmel-dfu

# Build Options
#   change yes to no to disable
#
<<<<<<< HEAD:keyboards/keebzdotnet/wazowski/keymaps/floor/rules.mk
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration
=======
BOOTMAGIC_ENABLE = lite     # Enable Bootmagic Lite
>>>>>>> upstream/master:keyboards/ut472/rules.mk
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = no        # Console for debug
COMMAND_ENABLE = no        # Commands for debug and configuration
# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no       # Breathing sleep LED during USB suspend
# if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
<<<<<<< HEAD:keyboards/keebzdotnet/wazowski/keymaps/floor/rules.mk
NKRO_ENABLE = no            # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
MIDI_ENABLE = no            # MIDI support
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
AUDIO_ENABLE = no           # Audio output
FAUXCLICKY_ENABLE = no      # Use buzzer to emulate clicky switches
=======
NKRO_ENABLE = yes           # USB Nkey Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
AUDIO_ENABLE = no           # Audio output
RGBLIGHT_ENABLE = yes
>>>>>>> upstream/master:keyboards/ut472/rules.mk

# MCU name
MCU = STM32F303

# Bootloader selection
BOOTLOADER = stm32-dfu

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes      # Enable Bootmagic Lite
MOUSEKEY_ENABLE = yes       # Mouse keys
EXTRAKEY_ENABLE = yes       # Audio control and System control
CONSOLE_ENABLE = yes         # Console for debug
COMMAND_ENABLE = no         # Commands for debug and configuration
NKRO_ENABLE = yes           # Enable N-Key Rollover
BACKLIGHT_ENABLE = no       # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no        # Enable keyboard RGB underglow
AUDIO_ENABLE = no           # Audio output
ENCODER_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGB_MATRIX_DRIVER = AW20216


# Enable additional features.

# Per Key Debounce algorithm
# https://beta.docs.qmk.fm/using-qmk/software-features/feature_debounce_type
DEBOUNCE_TYPE = sym_defer_pk

# VIA Support: 
# WARNING: Enabling this prevents any other changes to keymap.c from working
# Until VIA_ENABLE is set to no again.
VIA_ENABLE = no

KEY_OVERRIDE_ENABLE = yes # Enable Key overrides
TAP_DANCE_ENABLE = yes # Enable Tap Dancing (different action if tapped multiple times)

# Enable custom RGB effects
RGB_MATRIX_CUSTOM_USER = yes
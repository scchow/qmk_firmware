MOUSEKEY_ENABLE = yes
EXTRAKEY_ENABLE = yes
CONSOLE_ENABLE = no
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes
LTO_ENABLE = yes
OLED_ENABLE = yes
OLED_DRIVER = SSD1306
WPM_ENABLE = yes
NKRO_ENABLE = yes
SPLIT_KEYBOARD = yes
TAP_DANCE_ENABLE = yes

# Special commands for Elite-Pi compatibility
BOOTLOADER = rp2040
CONVERT_TO = promicro_rp2040

# Disable usb suspend check after keyboard startup
# Debugging the repeated characters on wake issue
NO_USB_STARTUP_CHECK = yes 

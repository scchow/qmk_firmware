 /* Copyright 2022 Scott Chow, 2021 Dane Evans
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


/**
 * This config was based on rgb_default/config.h
 * Applied modifications based on: https://github.com/josefadamcik/SofleKeyboard/pull/90#issuecomment-999033489
 */
#pragma once


//#define USE_MATRIX_I2C

/* Select hand configuration */

///https://thomasbaart.nl/2018/12/01/reducing-firmware-size-in-qmk/


// #define MASTER_LEFT
#define MASTER_RIGHT
// #define EE_HANDS

#define CUSTOM_FONT

#define CUSTOM_LAYER_READ //if you remove this it causes issues - needs better guarding
#define TAPPING_TOGGLE 2

// #define TAPPING_FORCE_HOLD
#ifdef TAPPING_TERM
    #undef TAPPING_TERM
    #define TAPPING_TERM 200
#endif
#define ENCODER_DIRECTION_FLIP


#define RGBLIGHT_SLEEP
//
#define RGBLIGHT_LAYERS

/* ws2812 RGB LED */
#define RGB_DI_PIN D3


#ifdef RGBLIGHT_ENABLE

    // We are using a split keyboard
    #define RGBLIGHT_SPLIT

    // RGB Timeout based on https://gist.github.com/aashreys/01cb34605a290a7cfb94a856bdabc94c
    #define RGBLIGHT_SLEEP  // allows us to use rgblight_suspend() and rgblight_wakeup() in keymap.c
    #define RGBLIGHT_TIMEOUT 60*1000    // in milliseconds

    // We have 74 LEDS on our board
    #define RGBLED_NUM 74 
    // With 37 LEDs on each side
	#define RGBLED_SPLIT { 37, 37 }

    #define RGBLIGHT_LIMIT_VAL 150 // limit the brightness
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17


    //#define RGBLIGHT_ANIMATIONS
	#define RGBLIGHT_EFFECT_BREATHING
	#define RGBLIGHT_EFFECT_RAINBOW_MOOD
	#define RGBLIGHT_EFFECT_RAINBOW_SWIRL
	#define RGBLIGHT_EFFECT_SNAKE
	#define RGBLIGHT_EFFECT_KNIGHT
	#define RGBLIGHT_EFFECT_CHRISTMAS
	#define RGBLIGHT_EFFECT_STATIC_GRADIENT
	// #define RGBLIGHT_EFFECT_RGB_TEST
	#define RGBLIGHT_EFFECT_ALTERNATING
	#define RGBLIGHT_EFFECT_TWINKLE

    // If Breathing RGB light is enabled, set it as default
    #ifdef RGBLIGHT_EFFECT_BREATHING
        #define RGBLIGHT_DEFAULT_MODE RGBLIGHT_MODE_BREATHING
    #endif

#endif

// OLED display size and timeout
#define OLED_DISPLAY_128X32  // Sofle has a 128x32 display
// Turn off oled after this many miliseconds of inactivity
// We use our own version of OLED_TIMEOUT because
// Default OLED_TIMEOUT considers changing animations
// to be activity, even idle animations!
// At least that's the working hypothesis on why
// when the screen with the bongo cat is connected to the computer (thus is master), the oled does not turn off.
#define OLED_TIMEOUT 60*1000
// #ifdef OLED_TIMEOUT
//     // We cannot rely on default OLED_TIMEOUT until it is patched.
//     #undef OLED_TIMEOUT
// #endif
// #define OLED_TIMEOUT_CUSTOM 60*1000

// Enable OLEDs and words per minute tracking for split keyboards
// Choose what to share across the board
#define SPLIT_WPM_ENABLE
#define SPLIT_OLED_ENABLE
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE
// #define SPLIT_MODS_ENABLE
#define FORCE_NKRO

// allow the keyboard to wake from sleep properly
// #define USB_SUSPEND_WAKEUP_DELAY 3000

/*
 * RGB Matrix stuff (not used for sofle)
 */

#ifdef RGB_MATRIX_ENABLE

    // Overwrite g_led_config from rev1/rev1.h

    // Physical Layout
    // Columns
    // 0  1  2  3  4  5  6  7  8  9  10 11 12 13
    //                                           ROWS
    // 12 13 22 23 32 33       33 32 23 22 13 12  0
    //    02    03    04       04    03    02
    // 11 14 21 24 31 34       34 31 24 21 14 11  1
    //                01       01
    // 10 15 20 25 30 35       35 30 25 20 15 10  2
    //
    // 09 16 19 26 29 36       36 29 26 19 16 09  3
    //
    //     08 17 18 27 28     28 27 18 17 08      4
    //    07    06    05       05    06    07

    g_led_config = {
    {
        {  11,  12,  21,  22,  31,  32 },
        {  10,  13,  20,  23,  30,  33 },
        {  9,   14,  19,  24,  29,  34},
        {  8,   15,  18,  25,  28,  35},
        {  7,   16,  17,  26,  27,  NO_LED },
        {  47,  48,  57,  58,  67,  68},
        {  46,  49,  56,  59,  66,  69},
        {  45,  50,  55,  60,  65,  70},
        {  44,  51,  54,  61,  64,  71},
        {  43,  52,  53,  62,  63,  NO_LED }
    },
    {
       // Left side underglow
        {96, 40}, {16, 20}, {48, 10}, {80, 18}, {88, 60}, {56, 57}, {24,60},
        // Left side Matrix
        {32, 57}, { 0, 48}, { 0, 36}, { 0, 24}, { 0, 12},
        {16, 12}, {16, 24}, {16, 36}, {16, 48}, {48, 55},
        {64, 57}, {32, 45}, {32, 33}, {32, 21}, {32,  9},
        {48,  7}, {48, 19}, {48, 31}, {48, 43}, {80, 59},
        {96, 64}, {64, 45}, {64, 33}, {64, 21}, {64,  9},
        {80, 10}, {80, 22}, {80, 34}, {80, 47},


        // Right side underglow
        {128, 40}, {208, 20}, {176, 10}, {144, 18}, {136, 60}, {168, 57}, {200,60},
        // Right side Matrix
        {192, 57}, {224, 48}, {224, 36}, {224, 24}, {224, 12},
        {208, 12}, {208, 24}, {208, 36}, {208, 48}, {176, 55},
        {160, 57}, {192, 45}, {192, 33}, {192, 21}, {192,  9},
        {176,  7}, {176, 19}, {176, 31}, {176, 43}, {144, 59},
        {128, 64}, {160, 45}, {160, 33}, {160, 21}, {160,  9},
        {144, 10}, {144, 22}, {144, 34}, {144, 47},
    },
    {
        LED_FLAG_INDICATOR, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_INDICATOR, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW, LED_FLAG_UNDERGLOW,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT,
        LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT, LED_FLAG_KEYLIGHT
    }
};


    // Based on https://www.reddit.com/r/olkb/comments/sbvefp/has_anyone_gotten_qmk_rgb_matrix_effects_working/
    #define RGBLED_NUM 74
    #define DRIVER_LED_TOTAL RGBLED_NUM
    #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 120 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.
    #define RGB_MATRIX_HUE_STEP 8
    #define RGB_MATRIX_SAT_STEP 8
    #define RGB_MATRIX_VAL_STEP 8
    #define RGB_MATRIX_SPD_STEP 10
    #define RGB_MATRIX_KEYPRESSES
    #define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    #define RGB_MATRIX_SPLIT {37,37}
    #define SPLIT_TRANSPORT_MIRROR


    // #define RGBLED_NUM 37    // Number of LEDs, see keymap.c for matching value
    // #define DRIVER_LED_TOTAL RGBLED_NUM

    // #   define RGB_MATRIX_KEYPRESSES // reacts to keypresses
    // // #   define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
    // // #   define RGB_DISABLE_AFTER_TIMEOUT 0 // number of ticks to wait until disabling effects
    // #   define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended
    // #   define RGB_MATRIX_FRAMEBUFFER_EFFECTS
    // // #   define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
    // // #   define RGB_MATRIX_LED_FLUSH_LIMIT 16 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
    // #    define RGB_MATRIX_MAXIMUM_BRIGHTNESS 150 // limits maximum brightness of LEDs to 150 out of 255. Higher may cause the controller to crash.

    // #define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_GRADIENT_LEFT_RIGHT

    // #    define RGB_MATRIX_HUE_STEP 8
    // #    define RGB_MATRIX_SAT_STEP 8
    // #    define RGB_MATRIX_VAL_STEP 8
    // #    define RGB_MATRIX_SPD_STEP 10

    /* Disable the animations you don't want/need.  You will need to disable a good number of these    *
    * because they take up a lot of space.  Disable until you can successfully compile your firmware. */
    // #   undef ENABLE_RGB_MATRIX_ALPHAS_MODS
    // #   undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
    // #   undef ENABLE_RGB_MATRIX_BREATHING
    // #   undef ENABLE_RGB_MATRIX_CYCLE_ALL
    // #   undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
    // #   undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
    // #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
    // #   undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
    // #   undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
    // #   undef ENABLE_RGB_MATRIX_DUAL_BEACON
    // #   undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
    // #   undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
    // #   undef ENABLE_RGB_MATRIX_RAINDROPS
    // #   undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
    // #   undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
    // #   undef ENABLE_RGB_MATRIX_DIGITAL_RAIN
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
    // #   undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
    // #   undef ENABLE_RGB_MATRIX_SPLASH
    // #   undef ENABLE_RGB_MATRIX_MULTISPLASH
    // #   undef ENABLE_RGB_MATRIX_SOLID_SPLASH
    // #   undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH
#endif



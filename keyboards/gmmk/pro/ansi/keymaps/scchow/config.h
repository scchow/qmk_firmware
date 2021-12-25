/* Copyright 2021 scchow
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


#pragma once

/*
 * Here we use disable a bunch of RGB effects by using #undef
 * because the keyboard's `config.h` has all of them defined by default
 * (there's so many of them!)
 * Feel free to comment out animations you like to keep.
 * There is also the #define DISABLE_RGB_MATRIX_* command, but it turns out
 * using #undef reduces memory usage significantly
 */ 


#define RGB_MATRIX_KEYPRESSES // reacts to keypresses
// #define RGB_MATRIX_KEYRELEASES // reacts to keyreleases (instead of keypresses)
#define RGB_MATRIX_FRAMEBUFFER_EFFECTS // enable framebuffer effects

// RGB Matrix Animation modes. Explicitly enabled
// For full list of effects, see:
// https://docs.qmk.fm/#/feature_rgb_matrix?id=rgb-matrix-effects
#undef ENABLE_RGB_MATRIX_ALPHAS_MODS
#undef ENABLE_RGB_MATRIX_GRADIENT_UP_DOWN
#undef ENABLE_RGB_MATRIX_GRADIENT_LEFT_RIGHT
// #undef ENABLE_RGB_MATRIX_BREATHING
#undef ENABLE_RGB_MATRIX_BAND_SAT
#undef ENABLE_RGB_MATRIX_BAND_VAL
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_SAT
#undef ENABLE_RGB_MATRIX_BAND_PINWHEEL_VAL
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_SAT
#undef ENABLE_RGB_MATRIX_BAND_SPIRAL_VAL
// #undef ENABLE_RGB_MATRIX_CYCLE_ALL
#undef ENABLE_RGB_MATRIX_CYCLE_LEFT_RIGHT
#undef ENABLE_RGB_MATRIX_CYCLE_UP_DOWN
#undef ENABLE_RGB_MATRIX_RAINBOW_MOVING_CHEVRON
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN
#undef ENABLE_RGB_MATRIX_CYCLE_OUT_IN_DUAL
#undef ENABLE_RGB_MATRIX_CYCLE_PINWHEEL
#undef ENABLE_RGB_MATRIX_CYCLE_SPIRAL
#undef ENABLE_RGB_MATRIX_DUAL_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_BEACON
#undef ENABLE_RGB_MATRIX_RAINBOW_PINWHEELS
#undef ENABLE_RGB_MATRIX_RAINDROPS
#undef ENABLE_RGB_MATRIX_JELLYBEAN_RAINDROPS
// #undef ENABLE_RGB_MATRIX_HUE_BREATHING
#undef ENABLE_RGB_MATRIX_HUE_PENDULUM
#undef ENABLE_RGB_MATRIX_HUE_WAVE
#undef ENABLE_RGB_MATRIX_PIXEL_RAIN
#undef ENABLE_RGB_MATRIX_PIXEL_FLOW
#undef ENABLE_RGB_MATRIX_PIXEL_FRACTAL

// enabled only if RGB_MATRIX_FRAMEBUFFER_EFFECTS is defined
#undef ENABLE_RGB_MATRIX_TYPING_HEATMAP
#undef ENABLE_RGB_MATRIX_DIGITAL_RAIN

// enabled only if RGB_MATRIX_KEYPRESSES or RGB_MATRIX_KEYRELEASES is defined
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_WIDE
// #undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_CROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTICROSS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS
#undef ENABLE_RGB_MATRIX_SOLID_REACTIVE_NEXUS
#undef ENABLE_RGB_MATRIX_SPLASH
// #undef ENABLE_RGB_MATRIX_MULTISPLASH
#undef ENABLE_RGB_MATRIX_SOLID_SPLASH
// #undef ENABLE_RGB_MATRIX_SOLID_MULTISPLASH

/* Force NKRO on boot up regardless of the setting saved in the EEPROM (uncomment to enable it) */
// #define FORCE_NKRO

// #define RGB_MATRIX_LED_PROCESS_LIMIT (DRIVER_LED_TOTAL + 4) / 5 // limits the number of LEDs to process in an animation per task run (increases keyboard responsiveness)
#define RGB_MATRIX_LED_FLUSH_LIMIT 0 // limits in milliseconds how frequently an animation will update the LEDs. 16 (16ms) is equivalent to limiting to 60fps (increases keyboard responsiveness)
// #define RGB_MATRIX_MAXIMUM_BRIGHTNESS 200 // limits maximum brightness of LEDs to 200 out of 255. If not defined maximum brightness is set to 255
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE // Sets the default mode, if none has been set
// #define RGB_MATRIX_STARTUP_HUE 0 // Sets the default hue value, if none has been set
// #define RGB_MATRIX_STARTUP_SAT 255 // Sets the default saturation value, if none has been set
// #define RGB_MATRIX_STARTUP_VAL RGB_MATRIX_MAXIMUM_BRIGHTNESS // Sets the default brightness value, if none has been set
// #define RGB_MATRIX_STARTUP_SPD 127 // Sets the default animation speed, if none has been set


#ifdef RGB_MATRIX_ENABLE

    #define RGB_DISABLE_TIMEOUT 30*60*1000 // number of milliseconds to wait until rgb automatically turns off
    #define RGB_DISABLE_WHEN_USB_SUSPENDED // turn off effects when suspended

#endif


// Tapping toggle settings

// Number of times to tap a modifier key to toggle
#undef TAPPING_TOGGLE
#define TAPPING_TOGGLE 2
#undef TAPPING_TERM
#define TAPPING_TERM 175

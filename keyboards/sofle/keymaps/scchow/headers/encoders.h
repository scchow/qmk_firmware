#pragma once

/**
 * Many functions based on tutorial here:
 * https://docs.splitkb.com/hc/en-us/articles/360010513760-How-can-I-use-a-rotary-encoder-
 */

#include QMK_KEYBOARD_H
#include "enums.h"

#ifdef RGBLIGHT_ENABLE
    #include "rgb_light.h"
#endif

#ifdef OLED_ENABLE
    #include "oled.h"
#endif

#define ALT_TAB_TIMEOUT 1250 // time to keep alt held when scrolling in milliseconds

bool is_alt_tab_active = false;
uint16_t alt_tab_timer = 0;

void alt_tab(bool clockwise){
    // If alt tab is not active and the encoder is turned
    // Press alt
    if (!is_alt_tab_active) {
        is_alt_tab_active = true;
        register_code(KC_LALT);
    }
    // Reset timer
    alt_tab_timer = timer_read();

    if (clockwise) {
        tap_code16(KC_TAB);
    }
    else {
        tap_code16(S(KC_TAB));
    }
}

void scroll(bool clockwise){
    if (clockwise) {
        tap_code(KC_WH_D);
    } else {
        tap_code(KC_WH_U);
    }
}

bool encoder_update_user(uint8_t index, bool clockwise) {


    // Turn on RGB/OLED if they are enabled
    #if defined(RGBLIGHT_ENABLE) && defined(RGBLIGHT_TIMEOUT)
        rgb_idle_key_pressed();
    #endif
    #ifdef OLED_ENABLE
        oled_idle_key_pressed();
    #endif


    // Right encoder controls volume
    if (index == 1){
        if (clockwise) {
            tap_code(KC_VOLU);
        }
        else{
            tap_code(KC_VOLD);
        }
    }
    // Left encoder scrolls through windows (on all layers)
    else if (index == 0) {
        alt_tab(clockwise);

        /// This code scrolls depending on layer
        // switch (get_highest_layer(layer_state)) {
        //     case _BASE:
        //         break;
        //     case _BASE:
        //     		if (clockwise) {
        //     			tap_code(KC_WH_D);
        //     		} else {
        //     			tap_code(KC_WH_U);
        //     		}
        //     	break;
        //     default:
        //         if (clockwise) {
        //             tap_code(KC_WH_D);
        //         } else {
        //             tap_code(KC_WH_U);
        //         }
        //         break;
        // }
    }
    return true;
}

void matrix_scan_user_encoder(void) {
  if (is_alt_tab_active) {
    if (timer_elapsed(alt_tab_timer) > ALT_TAB_TIMEOUT) {
      unregister_code(KC_LALT);
      is_alt_tab_active = false;
    }
  }
}

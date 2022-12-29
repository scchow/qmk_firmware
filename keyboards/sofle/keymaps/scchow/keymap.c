 /* Copyright 2021 Dane Evans
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
  // SOFLE RGB

/*
Copied from rbg_default/keymap.c
Applied modifications based on: https://github.com/josefadamcik/SofleKeyboard/pull/90#issuecomment-999033489
*/

#include QMK_KEYBOARD_H

#include "headers/enums.h"
#include "headers/tap_dance.h"
#include "headers/layers.h"

#ifdef RGBLIGHT_ENABLE
    #include "headers/rgb_light.h"
#endif

#ifdef OLED_ENABLE
    #include "headers/oled.h"
#endif


#ifdef ENCODER_ENABLE
    #include "headers/encoders.h"
#endif


void keyboard_post_init_user() {
    #ifdef RGBLIGHT_ENABLE
        // initialize RGBLight layers
        rgb_init();
    #endif
}

void matrix_scan_user(void) {
    #ifdef RGBLIGHT_ENABLE
        rgb_idle_check_timer();
    #endif
    #ifdef OLED_ENABLE
        oled_idle_check_timer();
    #endif
    matrix_scan_user_encoder();
}

layer_state_t layer_state_set_user(layer_state_t state) {

    // state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    #ifdef RGBLIGHT_ENABLE
        rgblight_set_based_on_layer(state);
    #endif

    return state;
}



bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    // For LED turn off feature
    if (record->event.pressed) {
        #ifdef RGBLIGHT_ENABLE
            rgb_idle_key_pressed();
        #endif
        #ifdef OLED_ENABLE
            oled_idle_key_pressed();
        #endif
    }



    switch (keycode) {
        case KC_BASE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
            }
            return false;
        // // Tri layer handed in layer_state_set_user() to enable use with LT()
        // case KC_LOWER:
        //     if (record->event.pressed) {
        //         layer_on(_LOWER);
        //         // update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     } else {
        //         layer_off(_LOWER);
        //         // update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     }
        //     return false;
        // case KC_RAISE:
        //     if (record->event.pressed) {
        //         layer_on(_RAISE);
        //         // update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     } else {
        //         layer_off(_RAISE);
        //         // update_tri_layer(_LOWER, _RAISE, _ADJUST);
        //     }
        //     return false;
        // // We have to turn on layers _LOWER and _RAISE to trigger _ADJUST
        // case KC_ADJUST:
        //     if (record->event.pressed) {
        //         layer_on(_LOWER);
        //         layer_on(_RAISE);
        //     } else {
        //         layer_off(_LOWER);
        //         layer_off(_RAISE);
        //     }
        //     return false;
        // //
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
    }
    return true;
}

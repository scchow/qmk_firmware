#pragma once

#include QMK_KEYBOARD_H
#include "enums.h"

bool encoder_update_user(uint8_t index, bool clockwise) {
    // Right encoder controls volume
    if (index == 1){
        if (clockwise) {
            tap_code(KC_VOLU);
        }
        else{
            tap_code(KC_VOLD);
        }
		}
    // Left encoder scrolls (on all layers)
    else if (index == 0) {
        // switch (get_highest_layer(layer_state)) {
            // case _BASE:
            //     break;
            // case _BASE:
            // 		if (clockwise) {
            // 			tap_code(KC_WH_D);
            // 		} else {
            // 			tap_code(KC_WH_U);
            // 		}
            // 	break;
            // default:
                if (clockwise) {
                    tap_code(KC_WH_D);
                } else {
                    tap_code(KC_WH_U);
                }
                // break;
        // }
    }
    return true;
}


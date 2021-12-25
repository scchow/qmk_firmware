/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
             2022 scchow

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "rgb.h"


// Custom keycodes definition
// Tap Dance declarations

enum custom_keycodes{
    RESET_LAYERS = SAFE_RANGE,
    RGB_HUE_BREATHE,
    RGB_CYCLE_ALL,
    RGB_SOLID_REACTIVE_MULTIWIDE,
    RGB_MULTISPLASH,
    RGB_SOLID_MULTISPLASH,
    RGB_SET_OFF,
    RGB_CUSTOM_SOLID_REACTIVE_MULTIWIDE,
    RGB_CUSTOM_RANDOM_REACTIVE,
};

enum{
    TD_RESET_CAPS,
};

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_RESET_CAPS] = ACTION_TAP_DANCE_DOUBLE(RESET_LAYERS, KC_CAPS),
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

//      ESC      F1       F2       F3       F4       F5       F6       F7       F8       F9       F10      F11      F12	     Prt           Rotary(Mute)
//      ~        1        2        3        4        5        6        7        8        9        0         -       (=)	     BackSpc           Del
//      Tab      Q        W        E        R        T        Y        U        I        O        P        [        ]        \                 PgUp
//      Caps     A        S        D        F        G        H        J        K        L        ;        "                 Enter             PgDn
//      Sh_L              Z        X        C        V        B        N        M        ,        .        ?                 Sh_R     Up       End
//      Ct_L     Win_L    Alt_L                               SPACE                               Alt_R    FN       Ct_R     Left     Down     Right


    // The FN key by default maps to a momentary toggle to layer 1 to provide access to the RESET key (to put the board into bootloader mode). Without
    // this mapping, you have to open the case to hit the button on the bottom of the PCB (near the USB cable attachment) while plugging in the USB
    // cable to get the board into bootloader mode - definitely not fun when you're working on your QMK builds. Remove this and put it back to KC_RGUI
    // if that's your preference.
    //
    // To put the keyboard in bootloader mode, use FN+ESC. If you accidentally put it into bootloader, you can just unplug the USB cable and
    // it'll be back to normal when you plug it back in.
    //
    // This keyboard defaults to 6KRO instead of NKRO for compatibility reasons (some KVMs and BIOSes are incompatible with NKRO).
    // Since this is, among other things, a "gaming" keyboard, a key combination to enable NKRO on the fly is provided for convenience.
    // Press Fn+N to toggle between 6KRO and NKRO. This setting is persisted to the EEPROM and thus persists between restarts.
    [0] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  RESET_LAYERS,    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_DEL,
        TT(2),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,           KC_HOME,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [1] = LAYOUT(
        EEPROM_RESET , KC_CALC, KC_MYCM, KC_WHOM, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        RGB_TOG, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_HUE_BREATHE, RGB_CYCLE_ALL, RGB_SOLID_REACTIVE_MULTIWIDE, RGB_MULTISPLASH, RGB_SOLID_MULTISPLASH, RGB_CUSTOM_RANDOM_REACTIVE, RGB_CUSTOM_SOLID_REACTIVE_MULTIWIDE, RGB_SET_OFF, _______, _______, _______,          _______,
        RGB_MOD, RGB_HUI, RGB_VAI, RGB_SPI, _______, _______, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, RGB_HUD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, NK_TOGG, _______, _______, _______, _______,          _______, RGB_MOD, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    // Define 2 and 3, even if empty, for VIA
    // Navigation keys (triggered by CAPS LOCK key)
    // jkl; for Up/Down/Left/Right
    // ui for Home/End
    // nm for Page Up/Down
    // [2] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_UP, KC_BSPC, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______,  _______,          _______,          _______,
    //     _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, KC_PGUP, _______,
    //     _______, _______, MO(3),                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    // ),
    // [3] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, KC_DEL, KC_PGUP, KC_BSPC, _______, _______, _______, _______,            _______,
    //     _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END, _______, _______,          _______,          _______,
    //     _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, _______, _______,
    //     _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    // ),

    [2] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_DEL,  KC_PGUP, KC_BSPC, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END, _______,  _______,          _______,          KC_PGUP,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, KC_PGUP, KC_PGDN,
        _______, _______, MO(3),                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [3] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_DEL, KC_UP, KC_BSPC, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // [4] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______,    KC_7,    KC_8,    KC_9, KC_PPLS, _______, _______, _______, _______,            _______,
    //     _______, _______, _______, _______, _______, _______,    KC_4,    KC_5,    KC_6, KC_PMNS, _______, _______,          _______,          _______,
    //     _______,          _______, _______, _______, _______,    KC_1,    KC_2,    KC_3, KC_PENT, _______, _______,          _______, _______, _______,
    //     _______, _______, _______,                            KC_0,                            _______, _______, _______, _______, _______, _______
    // ),

};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
      tap_code(KC_VOLU);
    } else {
      tap_code(KC_VOLD);
    }
    return true;
}
#endif // ENCODER_ENABLE


// set_single_persistent_default_layer(0);

// Turn on a sequence of RGB
void rgb_light_sequence(const uint16_t *led_arr, int led_arr_len, int r, int g, int b, uint8_t led_min, uint8_t led_max){
    for (size_t i=0; i < led_arr_len; ++i){
        RGB_MATRIX_INDICATOR_SET_COLOR(led_arr[i], r, g, b);
    }
}

// Set all RGB to off
void rgb_turn_off(uint8_t led_min, uint8_t led_max){
    for (size_t i = 0; i < DRIVER_LED_TOTAL; ++i){
        RGB_MATRIX_INDICATOR_SET_COLOR(i, 0, 0, 0);
    }
}

void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {

    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK) || get_highest_layer(layer_state) > 0){
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_PSCR, 75, 75, 75); //Light up Reset layer key
    }

    // Light up shifts if Caps lock is on
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)){
        // RGB_MATRIX_INDICATOR_SET_COLOR(4, 0, 100, 0); //Light up left shift key
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_RSFT, 0, 100, 0); //Light up right shift key
        rgb_light_sequence(LED_SIDE_RIGHT, LED_SIDE_RIGHT_SIZE, 0, 100, 0, led_min, led_max);
    }

    // Light up Caps lock key if we are in navigation mode (layer 2)
    switch(get_highest_layer(layer_state)){  // special handling per layer
            case 1:  //layer one
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_TAB, 75, 75, 75); // Tab - White
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_Q, 255, 0, 255); // Q - Purple - Change Hue
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_A, 0, 255, 255); // A - Teal - Change Hue
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_W, 255, 255, 255); // W - Brightness
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_S, 50, 50, 50); // S - Brightness
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_E, 0, 255, 0); // E - Green - Speed
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_D, 255, 0, 0); // D - Red - Speed
                break;
            // Use same lighting for layer 2/3
            case 2:
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_LALT, 0, 50, 0); // Left Alt key
            case 3:
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 255, 0, 0); // Caps lock
                rgb_light_sequence(LED_SIDE_LEFT, LED_SIDE_LEFT_SIZE, 255, 0, 0, led_min, led_max);
                rgb_light_sequence(LED_LIST_IJKL, LED_LIST_IJKL_SIZE, 75, 75, 75, led_min, led_max);
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_U, 255, 0, 0); // U key
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_O, 0, 0, 255); // O key
                RGB_MATRIX_INDICATOR_SET_COLOR(LED_RSFT, 75, 0, 0); // Right Shift key
                break;
            default:
                break;
            break;
    }
}

/* Macros
 */


bool process_record_user(uint16_t keycode, keyrecord_t *record)  {
    // Store the current modifier state in the variable for later reference
    switch(keycode){
        case RESET_LAYERS:
            if (record->event.pressed) {
                layer_clear(); // disable all layers
                // If Caps lock is on, disable it
                if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)){
                    tap_code(KC_CAPS);
                }
            }
            return true;

        case RGB_HUE_BREATHE:
            rgb_matrix_mode(RGB_MATRIX_HUE_BREATHING);
            break;
        case RGB_SOLID_REACTIVE_MULTIWIDE:
            rgb_matrix_mode(RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE);
            break;
        case RGB_MULTISPLASH:
            rgb_matrix_mode(RGB_MATRIX_MULTISPLASH);
            break;
        case RGB_SOLID_MULTISPLASH:
            rgb_matrix_mode(RGB_MATRIX_SOLID_MULTISPLASH);
            break;
        case RGB_CYCLE_ALL:
            rgb_matrix_mode(RGB_MATRIX_CYCLE_ALL);
            break;
        case RGB_CUSTOM_SOLID_REACTIVE_MULTIWIDE:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_my_solid_reactive_wide);
            break;
        case RGB_CUSTOM_RANDOM_REACTIVE:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_random_color_reactive);
            break;
        // RGB Set OFF does not work at the moment
        case RGB_SET_OFF:
            rgb_matrix_set_color_all(0, 0, 0);
            // rgb_matrix_mode(RGB_MATRIX_NONE);
            break;
    }

    return true;
};

// const key_override_t left_home_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_LEFT, KC_HOME, 2);
// const key_override_t right_end_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_RIGHT, KC_END, 2);
// const key_override_t up_pgup_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_UP, KC_PGUP, 2);
// const key_override_t down_pgdn_override = ko_make_with_layers(MOD_MASK_SHIFT, KC_DOWN, KC_PGDN, 2);

// const key_override_t **key_overrides = (const key_override_t *[]){
//     &ko_make_with_layers(MOD_BIT(KC_RSFT), KC_LEFT, KC_HOME, 1<<2),
//     &ko_make_with_layers(MOD_BIT(KC_RSFT), KC_RIGHT, KC_END, 1<<2),
//     &ko_make_with_layers(MOD_BIT(KC_RSFT), KC_UP, KC_PGUP, 1<<2),
//     &ko_make_with_layers(MOD_BIT(KC_RSFT), KC_DOWN, KC_PGDN, 1<<2),
//     NULL
// };

// #ifdef KEY_OVERRIDE_ENABLE
// const key_override_t ALT_LEFT_HOME_key_override = ko_make_basic(MOD_MASK_ALT, KC_LEFT, KC_HOME);
// const key_override_t ALT_RIGHT_HOME_key_override = ko_make_basic(MOD_MASK_ALT, KC_RIGHT, KC_END);


// // This globally defines all key overrides to be used
// const key_override_t **key_overrides = (const key_override_t *[]){
//     &ALT_LEFT_HOME_key_override,
//     &ALT_RIGHT_HOME_key_override,
//     NULL // Null terminate the array of overrides!
// };

// #endif // KEY_OVERRIDE_ENABLE

// bool check_mod_pressed(uint8_t mod_state, uint16_t keycode){
//     return (mod_state & MOD_BIT(keycode)) == MOD_BIT(keycode);
// }


// // Initialize variable holding the binary
// // representation of active modifiers.
// uint8_t mod_state;

// bool process_record_user(uint16_t keycode, keyrecord_t *record) {
//     // Store the current modifier state in the variable for later reference
//     mod_state = get_mods();
//     switch (keycode) {

//     // Macro for binding `HOME` to `ALT`+`LEFT`
//     case KC_LEFT:
//         // Detect the activation of Left Alt
//         if (check_mod_pressed(mod_state, KC_LALT)){
//             if (record->event.pressed) {
//                 // First temporarily canceling both alt
//                 del_mods(MOD_MASK_ALT);
//                 register_code(KC_HOME);
//                 // Reapplying modifier state so that the held alt key(s)
//                 // still work even after having tapped the Left Arrow key.
//                 set_mods(mod_state);
//             } else {
//                 unregister_code(KC_HOME);
//             }
//             // Do not let QMK process the keycode further
//             return false;
//         }

//     return true;
// };


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

#include "print.h"

#include "rgb.h"

// Define each layer with a name for readibility
#define _DEFAULT 0
#define _RGB 1
#define _NAV_0 2
#define _NAV_1 3
#define _NAV_0_VIM 4
#define _NAV_1_VIM 5
#define _NUM_PAD 6

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
    RGB_CUSTOM_BREATHING,
};

// Tap Dancing Enums
enum tap_dances{
    TD_RESET_CAPS,
    TD_F12_NUMPAD,
    TD_RESET_CAPS_HOLD,
    TD_DEL_PRSC_HOLD,
};

// Enum states for complex type dancing
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP,
    TD_DOUBLE_HOLD,
    TD_DOUBLE_SINGLE_TAP, // Send two single taps
    TD_TRIPLE_TAP,
    TD_TRIPLE_HOLD
} td_state_t;

// Struct for managing current tap status
typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

/// Define some functions to be used in Tap Dancing

// Managing current dance 
td_state_t cur_dance(qk_tap_dance_state_t *state);

// For the F12-Numpad tap dance. 
void td_f12_num_finished(qk_tap_dance_state_t *state, void *user_data);
void td_f12_num_reset(qk_tap_dance_state_t *state, void *user_data);

// For the Delete-PrintScreen tap dance.
void td_del_print_finished(qk_tap_dance_state_t *state, void *user_data);
void td_del_print_reset(qk_tap_dance_state_t *state, void *user_data);

// For the Reset-Capslock tap dance.
void td_reset_caps_finished(qk_tap_dance_state_t *state, void *user_data);
void td_reset_caps_reset(qk_tap_dance_state_t *state, void *user_data);

// Reset layers back to default and Caps lock off
void reset_layers_and_caps(void){
    layer_clear(); // disable all layers
    // If Caps lock is on, disable it
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)){
        tap_code(KC_CAPS);
    }
}

// Tap Dance function for Layer Reset/Caps Lock key
void td_caps_reset(qk_tap_dance_state_t *state, void *user_data){
    // If its tapped twice, act as Caps Lock
    #ifdef CONSOLE_ENABLE
        dprintf("td_caps_reset called with count: %d\n", state->count);
    #endif

    if (state->count == 2){
        tap_code(KC_CAPS);
    } else{
        // default act as reset key
        reset_layers_and_caps();
    }
}

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_RESET_CAPS] = ACTION_TAP_DANCE_FN(td_caps_reset),
    [TD_F12_NUMPAD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_f12_num_finished, td_f12_num_reset),
    [TD_RESET_CAPS_HOLD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_reset_caps_finished, td_reset_caps_reset),
    [TD_DEL_PRSC_HOLD] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, td_del_print_finished, td_del_print_reset),
};

// indicator light for print screen
static bool print_screen_held = false;

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
    [_DEFAULT] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  TD(TD_F12_NUMPAD),  TD(TD_RESET_CAPS_HOLD),    KC_MUTE,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          KC_DEL,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC, KC_BSLS,          KC_HOME,
        TT(_NAV_0_VIM),   KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,          KC_ENT,  KC_END,
        KC_LSFT,          KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   LT(_NAV_0_VIM, KC_ESC),
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(1),   KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    [_RGB] = LAYOUT(
        EEPROM_RESET , KC_CALC, KC_MYCM, KC_WHOM, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_MUTE, KC_VOLD, KC_VOLU, _______, _______,          _______,
        RGB_TOG, RGB_MODE_PLAIN, RGB_MODE_BREATHE, RGB_HUE_BREATHE, RGB_CYCLE_ALL, RGB_SOLID_REACTIVE_MULTIWIDE, RGB_MULTISPLASH, RGB_SOLID_MULTISPLASH, RGB_CUSTOM_RANDOM_REACTIVE, RGB_CUSTOM_BREATHING, RGB_SET_OFF, _______, _______, _______,          _______,
        RGB_MOD, RGB_HUI, RGB_VAI, RGB_SPI, _______, RGB_CUSTOM_SOLID_REACTIVE_MULTIWIDE, _______, _______, _______, _______, _______, _______, _______, RESET,            _______,
        _______, RGB_HUD, RGB_VAD, RGB_SPD, _______, _______, _______, _______, _______, _______, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, NK_OFF, NK_ON, _______, _______, _______, _______,          _______, RGB_MOD, _______,
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

    [_NAV_0] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC,  KC_PGUP, KC_DEL, _______, _______, _______, _______,          KC_PGUP,
        _______, _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_END, _______,  _______,          _______,          KC_PGDN,
        KC_CAPS,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          KC_CAPS, KC_PGUP, _______,
        _______, _______, MO(_NAV_1),                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_NAV_1] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_UP, KC_DEL, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    // VIM version of layouts 2/3 - HJKL
    [_NAV_0_VIM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC,  KC_DEL, _______, _______, _______, _______, _______,          KC_PGUP,
        TO(_DEFAULT), _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT, _______,  _______,          _______,           KC_PGDN,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,                 KC_CAPS, KC_PGUP, _______,
        _______, _______, MO(_NAV_1_VIM),                            _______,                            _______, _______, _______, KC_HOME, KC_PGDN, KC_END
    ),

    [_NAV_1_VIM] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, _______, _______, _______, _______, _______, _______, KC_BSPC, KC_DEL, _______, _______, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, KC_HOME, KC_PGDN, KC_PGUP, KC_END, _______, _______,          _______,          _______,
        _______,          _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______, _______, _______,
        _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    ),

    [_NUM_PAD] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,           _______,
        _______, _______, _______, _______, _______, _______, KC_BSPC, KC_PSLS, KC_PAST, KC_PMNS, KC_DEL, _______, _______, _______,           _______,
        _______, _______, _______, _______, _______, _______, KC_PCMM,   KC_7,    KC_8,    KC_9,  KC_PPLS, _______, _______, _______,            _______,
        _______, _______, _______, _______, _______, _______, KC_SPC,   KC_4,    KC_5,    KC_6,  KC_PPLS, _______,          _______,           _______,
        _______, _______, _______, _______, _______, _______, KC_PDOT,    KC_1,    KC_2,    KC_3,  _______, _______,         _______,   _______,
        _______, _______, _______,                            KC_0,                               KC_PDOT, _______, _______, _______, _______, _______
    ),
    // [_NUM_PAD2] = LAYOUT(
    //     _______, _______, _______, _______, _______, _______, _______,   KC_P7,    KC_P8,   KC_P9, KC_PAST, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______,   KC_P4,    KC_P5,   KC_P6, _______, _______, _______, _______,          _______,
    //     _______, _______, _______, _______, _______, _______, _______,   KC_P1,    KC_P2,   KC_P3, _______, _______, _______, _______,            _______,
    //     _______, _______, _______, _______, _______, _______, _______,   KC_P0,  _______, _______, _______, _______,          _______,          _______,
    //     _______,          _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______,          _______, _______, _______,
    //     _______, _______, _______,                            _______,                            _______, _______, _______, _______, _______, _______
    // ),

};

#ifdef ENCODER_ENABLE
bool encoder_update_user(uint8_t index, bool clockwise) {
    if (clockwise) {
        tap_code(KC_VOLU);
        #ifdef CONSOLE_ENABLE
            dprint("Volume up\n");
        #endif            
    } else {
        tap_code(KC_VOLD);
        #ifdef CONSOLE_ENABLE
            dprint("Volume down\n");
        #endif
    }
    return true;
}
#endif // ENCODER_ENABLE

void keyboard_post_init_user(void) {
  // Customise these values to desired behaviour
  debug_enable = false;
//   debug_matrix=true;
//   debug_keyboard=true;
  //debug_mouse=true;
}

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
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_PSCR, 0, 100, 100); //Light up Reset layer key
    }

    if (print_screen_held){
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_END, 153, 51, 255);
    }

    // Light up Caps lock key if we are in navigation mode (layer 2)
    if (layer_state_is(_RGB)){
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_TAB, 255, 255, 255); // Tab - White
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_Q, 255, 0, 255); // Q - Purple - Change Hue
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_A, 0, 255, 255); // A - Teal - Change Hue
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_W, 255, 255, 255); // W - Brightness
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_S, 50, 50, 50); // S - Brightness
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_E, 0, 255, 0); // E - Green - Speed
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_D, 255, 0, 0); // D - Red - Speed
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_N, 0, 255, 0); // N - N-key-rollover on - Green
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_B, 255, 0, 0); // B - N-key-rollover off- Red
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_BSLS, 255, 0, 0); // \ - Reset on Red
    }

    if (layer_state_is(_NAV_0) || layer_state_is(_NAV_1) || layer_state_is(_NAV_0_VIM) || layer_state_is(_NAV_1_VIM)){

        const uint16_t *NAV_KEY_LEDS = LED_LIST_IJKL;
        int NAV_KEY_LEDS_SIZE = LED_LIST_IJKL_SIZE;
        int DELETE_KEY_LED = LED_O;
        // If we are in vim mode
        if (layer_state_is(_NAV_0_VIM) || layer_state_is(_NAV_1_VIM)){
            NAV_KEY_LEDS = LED_LIST_HJKL;
            NAV_KEY_LEDS_SIZE = LED_LIST_HJKL_SIZE;
            DELETE_KEY_LED = LED_I;
        }

        // if we are in the layer 1 of navigation
        if (layer_state_is(_NAV_1) || layer_state_is(_NAV_1_VIM)){
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_LALT, 28, 127, 232); // Left Alt key in teal
            rgb_light_sequence(NAV_KEY_LEDS, NAV_KEY_LEDS_SIZE, 28, 127, 232, led_min, led_max); // HJKL in teal blue
            rgb_light_sequence(LED_LIST_ARROWS, LED_LIST_ARROWS_SIZE, 153, 51, 255, led_min, led_max); // Arrows in purple
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_PGUP, 28, 127, 232); // Page Up key in teal
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_PGDN, 28, 127, 232); // Page Down key in teal
        }
        else {
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_LALT, 153, 51, 255); // Left Alt key in purple
            rgb_light_sequence(NAV_KEY_LEDS, NAV_KEY_LEDS_SIZE, 153, 51, 255, led_min, led_max); // HJKL in purple
            rgb_light_sequence(LED_LIST_ARROWS, LED_LIST_ARROWS_SIZE, 153, 51, 255, led_min, led_max); // Arrows in purple
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_PGUP, 28, 127, 232); // Page Up key in teal
            RGB_MATRIX_INDICATOR_SET_COLOR(LED_PGDN, 28, 127, 232); // Page Down key in teal
        }

        // Light up navigation lights that are the same across all layers
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_CAPS, 28, 127, 232); // Caps lock in teal blue
        rgb_light_sequence(LED_SIDE_LEFT, LED_SIDE_LEFT_SIZE, 28, 127, 232, led_min, led_max); // Indicator in teal blue
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_U, 255, 0, 0); // U key - Backspace - Red
        RGB_MATRIX_INDICATOR_SET_COLOR(DELETE_KEY_LED, 255, 0, 0); // O key - Delete - Blue

    }

    // Light up the numpad keys if we're on numpad layer
    if (layer_state_is(_NUM_PAD)){
        rgb_light_sequence(LED_LIST_NUMPAD_NUM, LED_LIST_NUMPAD_NUM_SIZE, 28, 127, 232, led_min, led_max); // light up numpad in blue
        rgb_light_sequence(LED_LIST_NUMPAD_MODS, LED_LIST_NUMPAD_MODS_SIZE, 204, 102, 0, led_min, led_max); // light up modifier in orange
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_6, 128, 0, 0); //Light up 6 - Backspace
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_0, 0, 0, 255); //Light up 0 - Delete
    }
        
    // Light up shifts and side indicator light if Caps lock is on
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)){
        // RGB_MATRIX_INDICATOR_SET_COLOR(4, 0, 100, 0); //Light up left shift key
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_RSFT, 204, 102, 0); //Light up right shift key in orange
        // RGB_MATRIX_INDICATOR_SET_COLOR(LED_LSFT, 204, 102, 0); //Light up left shift key in orange
        RGB_MATRIX_INDICATOR_SET_COLOR(LED_SPC, 204, 102, 0); //Light up Space key in orange
        rgb_light_sequence(LED_SIDE_RIGHT, LED_SIDE_RIGHT_SIZE, 204, 102, 0, led_min, led_max);
    }
}

/* Macros
 */


bool process_record_user(uint16_t keycode, keyrecord_t *record)  {
    switch(keycode){
        case RESET_LAYERS:
            if (record->event.pressed) {
                reset_layers_and_caps();
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
        case RGB_CUSTOM_BREATHING:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_better_breathing);
            break;
        case RGB_SET_OFF:
            rgb_matrix_mode(RGB_MATRIX_CUSTOM_turn_effects_off);
            // rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
            // rgb_matrix_sethsv_noeeprom(HSV_OFF);
            // rgb_matrix_mode(RGB_MATRIX_NONE);
            break;
    }

    return true;
};

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'TD_DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed){
            return TD_SINGLE_TAP;
        }
        
        // Key has not been interrupted, but the key is still held. Means you want to send a 'HOLD'.
        else{
            return TD_SINGLE_HOLD;
        }
    } 
    return TD_UNKNOWN;
    //     else if (state->count == 2) {
    //     // TD_DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
    //     // action when hitting 'pp'. Suggested use case for this return value is when you want to send two
    //     // keystrokes of the key, and not the 'double tap' action/macro.
    //     if (state->interrupted) return TD_DOUBLE_SINGLE_TAP;
    //     else if (state->pressed) return TD_DOUBLE_HOLD;
    //     else return TD_DOUBLE_TAP;
    // }

    // // Assumes no one is trying to type the same letter three times (at least not quickly).
    // // If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    // // an exception here to return a 'TD_TRIPLE_SINGLE_TAP', and define that enum just like 'TD_DOUBLE_SINGLE_TAP'
    // if (state->count == 3) {
    //     if (state->interrupted || !state->pressed) return TD_TRIPLE_TAP;
    //     else return TD_TRIPLE_HOLD;
    // } else return TD_UNKNOWN;
}

// Create an instance of 'td_tap_t' for the 'f12_num' tap dance.
static td_tap_t td_f12_num_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void td_f12_num_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_f12_num_tap_state.state = cur_dance(state);
    switch (td_f12_num_tap_state.state) {
        case TD_SINGLE_TAP: 
            #ifdef CONSOLE_ENABLE
                dprint("Press F12\n");
            #endif
            // Allow single click disable of numpad 
            if (layer_state_is(_NUM_PAD)){
                dprint("Numpad on, read tap, turning off numpad.\n");
                layer_off(_NUM_PAD);
            } else{
                dprint("Numpad off, read tap, sending F12.\n");
                register_code(KC_F12);
            }
            break;
        case TD_SINGLE_HOLD: 
            #ifdef CONSOLE_ENABLE
                dprint("Hold F12\n");
            #endif
            if (!layer_state_is(_NUM_PAD)){
                dprint("Numpad off, read hold, turning on numpad.\n");
                layer_on(_NUM_PAD);
            }
            // Expose a way to press F12 if numpad is on (by double tap) 
            else{
                dprint("Numpad on, read hold, sending F12.\n");
                register_code(KC_F12);
            }
            // layer_invert(_NUM_PAD); 
            break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // // Last case is for fast typing. Assuming your key is `f`:
        // // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;
    }
}

void td_f12_num_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_f12_num_tap_state.state) {
        case TD_SINGLE_TAP: 
            // If we are not in numpad mode,
            // Pressing F12 results in normal F12 press
            // So on release, stop pressing F12 
            if (!layer_state_is(_NUM_PAD)){
                unregister_code(KC_F12); 
            }
            // Otherwise we are in numpad mode
            // and on downpress, we stopped being in numpad mode
            // So no keys need to be unregistered.
            break;
        case TD_SINGLE_HOLD: 
            // If we are in numpad mode, 
            // Holding F12 resulted in normal F12 press
            // So on release, stop pressing F12
            if (layer_state_is(_NUM_PAD)){
                unregister_code(KC_F12); 
            }
            // Otherwise we are not in numpad mode,
            // and on downpress, we moved to being in numpad mode.
            // So no keys need to be unregistered.
            break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
        default: break;
    }
    td_f12_num_tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'f12_num' tap dance.
static td_tap_t td_reset_caps_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void td_reset_caps_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_reset_caps_tap_state.state = cur_dance(state);
    switch (td_reset_caps_tap_state.state) {
        case TD_SINGLE_TAP: 
            #ifdef CONSOLE_ENABLE
                dprint("Press Reset\n");
            #endif
            reset_layers_and_caps();
            break;
        case TD_SINGLE_HOLD: 
            #ifdef CONSOLE_ENABLE
                dprint("Hold Reset for caps\n");
            #endif
            register_code(KC_CAPS);
            // if (!layer_state_is(_NUM_PAD)){
            //     dprint("Numpad off, read hold, turning on numpad.\n");
            //     layer_on(_NUM_PAD);
            // }
            // // Expose a way to press F12 if numpad is on (by double tap) 
            // else{
            //     dprint("Numpad on, read hold, sending F12.\n");
            //     register_code(KC_F12);
            // }
            // // layer_invert(_NUM_PAD); 
            // break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // // Last case is for fast typing. Assuming your key is `f`:
        // // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;
    }
}

void td_reset_caps_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_reset_caps_tap_state.state) {
        case TD_SINGLE_TAP: 
            // Nothing to do on release, as reset state already sent
            break;
        case TD_SINGLE_HOLD: 
            // Stop holding down caps lock
            unregister_code(KC_CAPS);
            break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
        default: break;
    }
    td_reset_caps_tap_state.state = TD_NONE;
}

// Create an instance of 'td_tap_t' for the 'f12_num' tap dance.
static td_tap_t td_del_print_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

void td_del_print_finished(qk_tap_dance_state_t *state, void *user_data) {
    td_del_print_tap_state.state = cur_dance(state);
    switch (td_del_print_tap_state.state) {
        case TD_SINGLE_TAP: 
            #ifdef CONSOLE_ENABLE
                dprint("Press Delete\n");
            #endif
            register_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD: 
            #ifdef CONSOLE_ENABLE
                dprint("Hold Delete for Print Screen\n");
            #endif
            register_code(KC_PSCR);
            print_screen_held = true;
            // if (!layer_state_is(_NUM_PAD)){
            //     dprint("Numpad off, read hold, turning on numpad.\n");
            //     layer_on(_NUM_PAD);
            // }
            // // Expose a way to press F12 if numpad is on (by double tap) 
            // else{
            //     dprint("Numpad on, read hold, sending F12.\n");
            //     register_code(KC_F12);
            // }
            // // layer_invert(_NUM_PAD); 
            // break;
        // case TD_DOUBLE_TAP: register_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: register_code(KC_LALT); break;
        // // Last case is for fast typing. Assuming your key is `f`:
        // // For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        // // In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        // case TD_DOUBLE_SINGLE_TAP: tap_code(KC_X); register_code(KC_X);
        default: break;
    }
}

void td_del_print_reset(qk_tap_dance_state_t *state, void *user_data) {
    switch (td_reset_caps_tap_state.state) {
        case TD_SINGLE_TAP: 
            unregister_code(KC_DEL);
            break;
        case TD_SINGLE_HOLD: 
            // Stop holding down caps lock
            unregister_code(KC_PSCR);
            print_screen_held = false;
            break;
        // case TD_DOUBLE_TAP: unregister_code(KC_ESC); break;
        // case TD_DOUBLE_HOLD: unregister_code(KC_LALT);
        // case TD_DOUBLE_SINGLE_TAP: unregister_code(KC_X);
        default: break;
    }
    td_reset_caps_tap_state.state = TD_NONE;
}
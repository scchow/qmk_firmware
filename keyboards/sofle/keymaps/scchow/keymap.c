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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/*
 * QWERTY
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |LShift|   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
 * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
 * | LCTR |   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |LShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
  [_BASE] = LAYOUT(
  //,------------------------------------------------.          ,---------------------------------------------------.
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|---------------+-------+--------+--------+-------+------|  |--------+-------+--------+--------+--------+---------|
  LT(_NUMPAD,KC_TAB), KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_ENT,
  //|---------------+-------+--------+--------+-------+------|  |--------+-------+--------+--------+--------+---------|
  LT(_NAV2,KC_ESC),  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+-------+--------+--------+--------+------|  ===  |  |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LCTL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  QK_BOOT,    QK_BOOT, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
  //|------+-------+--------+--------+--------+------|  ===  |  |  ===  |--------+-------+----------+--------+--------+---------|
                 KC_LALT,  KC_LGUI,  MO(_NAV2),     MO(_NAV),  KC_LSFT,   KC_RSFT, KC_SPC, MO(3), MO(4), TG(_GAME)
  //            \--------+--------+--------+---------+-------|  |-------+--------+--------+---------+-------/
),

/* NAV
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NAV] = LAYOUT(
  //,------+-----------+-----------+-----------+--------+-------.                     ,---------------------------------------------------.
 LALT(KC_F4),     KC_F1,      KC_F2,      KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL,
  //-------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
 LCA(KC_DEL),     KC_NO,      KC_NO,      KC_NO,   KC_NO,   KC_NO,                      LCTL(KC_Y), KC_NO,  KC_UP, KC_LBRC, KC_RBRC, KC_F11,
  //|------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
     _______,LCTL(KC_A),      KC_NO,      KC_NO,   KC_NO,   KC_NO,                      KC_NO,  KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_F12,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
     _______,LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,    _______,  KC_NO, KC_MINS,  KC_EQL,   KC_NO,   KC_NO,    KC_NO,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* NAV2
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NAV2] = LAYOUT(
  //,------+-----------+-----------+-----------+--------+-------.                     ,---------------------------------------------------.
 LALT(KC_F4),     KC_F1,      KC_F2,      KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_DEL,
  //-------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
 LCA(KC_DEL),     KC_NO,      KC_UP,      KC_NO,   KC_NO,   KC_NO,                      LCTL(KC_Y), KC_NO,  KC_PGUP, KC_LBRC, KC_RBRC, KC_F11,
  //|------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
     _______,   KC_LEFT,    KC_DOWN,   KC_RIGHT,   KC_NO,   KC_NO,                      KC_NO,  KC_HOME, KC_PGDN, KC_END, KC_NO,   KC_F12,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
 _______,LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,    _______,  KC_NO, KC_UNDS,  KC_PLUS,   KC_NO,   KC_NO,    KC_NO,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* GAME
 * ,----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Esc  | Ins  | Pscr | Menu |      |      |                    |      | PWrd |  Up  | NWrd | DLine| Bspc |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|      | Left | Down | Rigth|  Del | Bspc |
 * |------+------+------+------+------+------|  MUTE  |    |       |------+------+------+------+------+------|
 * |Shift | Undo |  Cut | Copy | Paste|      |-------|    |-------|      | LStr |      | LEnd |      | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_GAME] = LAYOUT(
    //,----------------------------------------------------------.                     ,-----------------------------------------------------------------.
         KC_GRV,    KC_1,     KC_2,     KC_3,     KC_4,      KC_5,                            KC_6,      KC_7,      KC_8,      KC_9,      KC_0,   KC_BSPC,
    //|--------+--------+---------+---------+---------+----------|                     |----------+----------+----------+----------+----------+----------|
         KC_TAB,    KC_Q,     KC_W,     KC_E,     KC_R,      KC_T,                            KC_Y,      KC_U,      KC_I,      KC_O,      KC_P,   KC_BSLS,
    //|--------+--------+---------+---------+---------+----------|                     |----------+----------+----------+----------+----------+----------|
LT(_GAME2,KC_ESC),  KC_A,     KC_S,     KC_D,     KC_F,      KC_G,                            KC_H,      KC_J,      KC_K,      KC_L,   KC_SCLN,   KC_QUOT,
    //|--------+--------+---------+---------+---------+----------|   ===  |   |  ===   |----------+----------+----------+----------+----------+----------|
        KC_LSFT,    KC_Z,     KC_X,     KC_C,      KC_V,     KC_B, KC_MUTE,   KC_D_MUTE,      KC_N,      KC_M,   KC_COMM,    KC_DOT,   KC_SLSH,    KC_ENT,
    //|--------+--------+---------+---------+---------+----------|   ===  |   |  ===   |----------+----------+----------+----------+----------+----------|
                               KC_LALT, KC_LGUI,  KC_SPC,  KC_LSFT,KC_LCTL,     KC_RSFT,   KC_SPC,   MO(3),    MO(4), TG(_GAME)
  //                         \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* GAME2
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE |RAISE | RCTR | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_GAME2] = LAYOUT(
    //|--------+--------+---------+---------+---------+----------|                     |----------+----------+----------+----------+----------+----------|
        _______,   KC_F1,    KC_F2,    KC_F3,    KC_F4,     KC_F5,                           KC_F6,     KC_F7,     KC_F8,     KC_F9,    KC_F10,    KC_DEL,
    //|--------+--------+---------+---------+---------+----------|                     |----------+----------+----------+----------+----------+----------|
        _______, _______,  _______,  _______,  _______,   _______,                         _______,   _______,   _______,   _______,   _______,    KC_F11,
    //|--------+--------+---------+---------+---------+----------|                     |----------+----------+----------+----------+----------+----------|
        _______, _______,  _______,  _______,  _______,   _______,                         _______,   _______,   _______,   _______,   _______,    KC_F12,
    //|--------+--------+---------+---------+---------+----------|   ===  |   |  ===   |----------+----------+----------+----------+----------+----------|
        _______, _______,  _______,  _______,  _______,   _______, _______,     _______,   _______,   _______,   _______,   _______,   _______,   _______,
    //|--------+--------+---------+---------+---------+----------|   ===  |   |  ===   |----------+----------+----------+----------+----------+----------|
                               _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //                         \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
/* NUMPAD
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | trans|      |      |      |      |      |                    |      |NumLck|      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |  `   |      |      |      |      |      |                    |   ^  |   7  |   8  |   9  |   *  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------.    ,-------|   -  |   4  |   5  |   6  |      |   |  |
 * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
 * | trans|      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |   \  | Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
 *            |      |      |      |      |/       /         \      \ |      |      |      |      |
 *            `----------------------------------'           '------''---------------------------'
 */
[_NUMPAD] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NUM, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_P7,  KC_P8,   KC_P9,   KC_ASTR, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_P4,  KC_P5,   KC_P6,   KC_EQL,  KC_PIPE,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,   _______,KC_PLUS, KC_P1,  KC_P2,   KC_P3,   KC_SLSH, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
              _______, OSM(MOD_MEH), _______, _______, _______,   _______, _______,  KC_P0,   KC_PDOT, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
)
};

#ifdef RGBLIGHT_ENABLE
    #include "headers/rgb.h"
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

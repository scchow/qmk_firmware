
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

#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 30
#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)


/* LED Indices for Sofle RGB v3.0
 *
 * Front
 *                         LEFT SIDE                                                      RIGHT SIDE 
 *                                                       NOTE: added a +1 offset to values below so that it works, idk why it's needed)
 *                 Column Number
 *                  0     1      2      3      4     5       6          13      12     11     10     9      8       7  
 * Row Num    ,-----------------------------------------.                    ,-----------------------------------------.
 *    0       |  11  |  12  |  21  |  22  |  31  |  32  |                    |  68  |  67  |  58  |  57  |  48  |  47  |
 *            |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *    1       |  10  |  13  |  20  |  23  |  30  |  33  |                    |  69  |  66  |  59  |  56  |  49  |  46  |
 *            |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *    2       |  9   |  14  |  19  |  24  |  29  |  34  |-------.    ,-------|  70  |  65  |  60  |  55  |  50  |  45  |
 *            |------+------+------+------+------+------|   0   |    |   36   |------+------+------+------+------+-----|
 *    3       |  8   |  15  |  18  |  25  |  28  |  35  |-------|    |-------|  71  |  64  |  61  |  54  |  51  |  44  |
 *            `-----------------------------------------/       /    \      \-----------------------------------------'
 *    4              |  7   |  17  |  18  |  26  |     /   27  /      \  63  \      |  62  |  53  |  52  |   43  |
 *                   |      |      |      |      |    /       /        \      \     |      |      |      |      |
 *                     `-------------------------------------'          '------''-------------------------------'
 * Back underglow
 *                          RIGHT SIDE                                                    LEFT SIDE
 *  NOTE: added a +1 offset to values below so that it works, idk why it's needed)
 *                                                          
 * Column Num    0     1      2      3      4     5       6          13      12     11     10     9      8       7  
 *   Row Num  ,-----------------------------------------.                    ,-----------------------------------------.
 *      0     |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 *            |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *      1     |      |  37  |      | 38   |      |  39  |                    |  3  |      |  2  |      |  1  |      |
 *            |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 *      2     |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |      |
 *            |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 *      3     |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 *            `-----------------------------------------/       /     \      \-----------------------------------------'
 *      4            | 42   |   41 |      |      |   40/       /       \      \ 4  |      |   5 |      |   6 |
 *                   |      |      |      |      |    /       /         \      \    |      |      |      |      |
 *                   `---------------------------------------'           '------''------------------------------'
 */


// Number of Indicator Lights
#define NUM_INDICATORS 1
// Number of underglow LEDs
#define NUM_UNDERGLOW 6
// Number of Per-Key RGB Backlighting
#define NUM_BACKLIGHT 29
// Number of LEDs in each half of board
#define NUM_PER_SIDE NUM_INDICATORS + NUM_UNDERGLOW + NUM_BACKLIGHT + 1 // 1+6+29 +1 = 36 + 1 = 37 (I am not sure why there is an extra +1 offset for leds on right side)
// Number of outer column keys
#define NUM_OUTER_FN_KEYS 4

// Starting index of underglow lighting
#define START_UNDERGLOW 1
// Starting LED number of all Per-Key RGB Backlighting  (should match key at front: (row4, col0))
#define START_PER_KEY_RGB NUM_INDICATORS + NUM_UNDERGLOW  // 1 + 6 = 7
// Starting index of outer column keys (Columns 0 and 7) (number of key at (row3, col7))
#define START_OUTER_FN_KEYS 8 // 7+1 = 9; Offset the outer thumb row key

// Light combinations
// Set the LEDs for the indicator leds
#define SET_INDICATORS(hsv) \
    {0, NUM_INDICATORS, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
    {NUM_PER_SIDE, NUM_INDICATORS, hsv}

// Set the LEDs for the underglow leds
#define SET_UNDERGLOW(hsv) \
	{START_UNDERGLOW, NUM_UNDERGLOW, hsv}, \
    {NUM_PER_SIDE+START_UNDERGLOW, NUM_UNDERGLOW, hsv}

// Set the LEDs for the underglow leds
#define SET_NUMPAD(hsv)     \
	{NUM_PER_SIDE+16, 5, hsv},\
	{NUM_PER_SIDE+25, 3, hsv},\
	{NUM_PER_SIDE+28, 3, hsv}

// Set the LEDs for the numrow leds
#define SET_NUMROW(hsv) \
	{11, 2, hsv}, \
	{21, 2, hsv}, \
	{31, 2, hsv}, \
	{NUM_PER_SIDE+ 11, 2, hsv}, \
	{NUM_PER_SIDE+ 21, 2, hsv}, \
	{NUM_PER_SIDE+ 31, 2, hsv}

/*
// Set the LEDs for the outside column (columns 0 and 7)
#define SET_OUTER_COL(hsv) \
	{START_OUTER_FN_KEYS, NUM_OUTER_FN_KEYS, hsv},\
	  {NUM_PER_SIDE + START_OUTER_FN_KEYS, NUM_OUTER_FN_KEYS, hsv}
*/

// Set the LEDs for the thumb cluster (only 2 keys near knob)
#define SET_THUMB_CLUSTER(hsv) 	\
    {26, 2, hsv}
    // {NUM_PER_SIDE + 26, 2, hsv}

// Set the LEDs for the thumb cluster
#define SET_THUMB_CLUSTER_FULL(hsv) 	\
    {7, 1, hsv},\
    {16, 2, hsv},\
    {26, 2, hsv}
    // {NUM_PER_SIDE + 7, 1, hsv},
    // {NUM_PER_SIDE + 16, 2, hsv},
    // {NUM_PER_SIDE + 26, 2, hsv}

// Set all LEDs outside of alpha keys
#define SET_LAYER_ID(hsv) 	\
	{0, NUM_INDICATORS, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
	{START_UNDERGLOW, NUM_UNDERGLOW, hsv}, \
	{START_OUTER_FN_KEYS, NUM_OUTER_FN_KEYS, hsv}, \
    {7, 1, hsv},\
    {16, 2, hsv},\
    {26, 2, hsv},\
      {NUM_PER_SIDE+0, NUM_INDICATORS, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, \
      {NUM_PER_SIDE+START_UNDERGLOW, NUM_UNDERGLOW, hsv},\
	  {NUM_PER_SIDE + START_OUTER_FN_KEYS, NUM_OUTER_FN_KEYS, hsv},\
    {NUM_PER_SIDE + 7, 1, hsv},\
    {NUM_PER_SIDE + 16, 2, hsv},\
    {NUM_PER_SIDE + 26, 2, hsv}

enum sofle_layers {
    _DEFAULTS = 0,
    _BASE = 0,
    _NAV,
    _NAV2,
    _GAME,
    _GAME2,
    _LOWER,
    _RAISE,
    _ADJUST,
    _NUMPAD,
    _SWITCH
};

enum custom_keycodes {
    KC_BASE = SAFE_RANGE,
    KC_LOWER,
    KC_RAISE,
    KC_ADJUST,
    KC_D_MUTE
};

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
  //,------------------------------------------------.                    ,---------------------------------------------------.
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,             LT(_SWITCH,KC_6), KC_7,   KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|---------------+-------+--------+--------+-------+------|                   |--------+-------+--------+--------+--------+---------|
  LT(_NUMPAD,KC_TAB), KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,                      KC_Y,    KC_U,   KC_I,    KC_O,    KC_P,    KC_BSLS,
  //|---------------+-------+--------+--------+-------+------|                   |--------+-------+--------+--------+--------+---------|
  LT(_LOWER,KC_ESC),  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,                      KC_H,    KC_J,   KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LCTRL, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  KC_MUTE,    KC_D_MUTE,KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH, KC_LSFT,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                  KC_LGUI, KC_LALT, KC_LSFT, KC_SPC,  KC_DEL,     KC_ENT,  KC_SPC, KC_RSFT, KC_RAISE,  KC_LOWER
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* LOWER
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
[_LOWER] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______,  KC_F1,  KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,  KC_F11,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                      KC_6,    KC_7,    KC_8,    KC_9,    KC_0,   KC_F12,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_NO,   KC_WH_U, KC_PGUP,                   KC_LEFT, KC_DOWN, KC_UP,  KC_RGHT, KC_NO,   KC_DEL,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,  KC_NO,  KC_NO,   KC_NO,   KC_WH_D, KC_PGDN,_______,    _______,KC_HOME, KC_PGDN, KC_PGUP,  KC_END,  KC_NO,    _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),

/* RAISE
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
[_RAISE] = LAYOUT(
  //,------------------------------------------------.                    ,---------------------------------------------------.
  _______, _______ , _______ , _______ , _______ , _______,               _______,  _______  , _______,  _______ ,  _______ ,_______,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______,  KC_INS,  KC_PSCR,   KC_APP,  XXXXXXX, XXXXXXX,                KC_CIRC, KC_AMPR,KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  _______, KC_LALT,  KC_LCTL,  KC_LSFT,  XXXXXXX, KC_CAPS,                KC_MINS, KC_EQL, KC_LCBR, KC_RCBR, KC_PIPE, KC_GRV,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  _______,KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX,_______,    _______,KC_UNDS, KC_PLUS,KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                 _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
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
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NLCK, XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX,
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

layer_state_t layer_state_set_user(layer_state_t state) {

    state = update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);

    #ifdef RGBLIGHT_ENABLE
	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_BASE));
	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
    #endif
    return state;
}

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_RED)

);

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_TEAL)

);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_BLUE)

    );
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(
  SET_LAYER_ID(HSV_PURPLE)
);

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_INDICATORS(HSV_ORANGE),
    SET_UNDERGLOW(HSV_ORANGE),
	SET_NUMPAD(HSV_BLUE),
    SET_THUMB_CLUSTER(HSV_ORANGE)
    );
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(
	SET_LAYER_ID(HSV_GREEN),
	SET_NUMROW(HSV_GREEN)
);

const rgblight_segment_t* const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(
    layer_qwerty_lights,
	layer_num_lights,// overrides layer 1
	layer_symbol_lights,
    layer_command_lights,
	layer_numpad_lights,
	layer_switcher_lights  // Overrides other layers
);

// layer_state_t layer_state_set_user(layer_state_t state) {
// 	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_BASE));
// 	rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
// 	rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
// 	rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
// 	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
// 	rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
//     return state;
// }
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

}
#endif

#ifdef OLED_ENABLE

static void render_logo(void) {
    static const char PROGMEM qmk_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xA0, 0xA1, 0xA2, 0xA3, 0xA4, 0xA5, 0xA6, 0xA7, 0xA8, 0xA9, 0xAA, 0xAB, 0xAC, 0xAD, 0xAE, 0xAF, 0xB0, 0xB1, 0xB2, 0xB3, 0xB4,
        0xC0, 0xC1, 0xC2, 0xC3, 0xC4, 0xC5, 0xC6, 0xC7, 0xC8, 0xC9, 0xCA, 0xCB, 0xCC, 0xCD, 0xCE, 0xCF, 0xD0, 0xD1, 0xD2, 0xD3, 0xD4, 0x00
    };

    oled_write_P(qmk_logo, false);
}

static void print_status_narrow(void) {
    // Print current mode
    oled_write_P(PSTR("\n\n"), false);
    oled_write_ln_P(PSTR("Scott\nChow"), false);

    oled_write_ln_P(PSTR(""), false);

	//snprintf(layer_state_str, sizeof(layer_state_str), "Layer: Undef-%ld", layer_state)


    switch (get_highest_layer(default_layer_state)) {
        case _BASE:
            oled_write_ln_P(PSTR("Qwrt"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
    oled_write_P(PSTR("\n\n"), false);
    // Print current layer
    oled_write_ln_P(PSTR("LAYER"), false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
        case _RAISE:
            oled_write_P(PSTR("Raise"), false);
            break;
        case _LOWER:
            oled_write_P(PSTR("Lower"), false);
            break;
        case _ADJUST:
            oled_write_P(PSTR("Adj\n"), false);
            break;
        case _NUMPAD:
            oled_write_P(PSTR("Nump\n"), false);
            break;
        case _SWITCH:
            oled_write_P(PSTR("Swit\n"), false);
            break;
        default:
            oled_write_ln_P(PSTR("Undef"), false);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation;
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        print_status_narrow();
    } else {
        render_logo();
    }
    return false;
}

#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_BASE:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_BASE);
            }
            return false;
        // Tri layer handed in layer_state_set_user() to enable use with LT()
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                // update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                // update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                // update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                // update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        // We have to turn on layers _LOWER and _RAISE to trigger _ADJUST
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_LOWER);
                layer_on(_RAISE);
            } else {
                layer_off(_LOWER);
                layer_off(_RAISE);
            }
            return false;
        //
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

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
		} else if (index == 1) {
			switch (get_highest_layer(layer_state)) {
				case _BASE:
				break;
			case _RAISE:
			case _LOWER:
					if (clockwise) {
						tap_code(KC_DOWN);
					} else {
						tap_code(KC_UP);
					}
				break;
			default:
					if (clockwise) {
						tap_code(KC_WH_D);
					} else {
						tap_code(KC_WH_U);
					}
				break;
		}
    }
    return true;
}

#endif

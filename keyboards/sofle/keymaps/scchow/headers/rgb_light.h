#pragma once

#include QMK_KEYBOARD_H
#include "rgblight.h"
#include "enums.h"

#define INDICATOR_BRIGHTNESS 30
#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s , Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv,Override)


#ifdef RGBLIGHT_TIMEOUT
    #include "idle_timer.h"
    // RGB timeout feature
    static bool rgb_on = true;
#endif




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
// TODO: Check these because they might be incorrect
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

// char layer_state_str[70];
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



void rgblight_set_based_on_layer(layer_state_t state){
	rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state,_BASE));
	rgblight_set_layer_state(1, layer_state_cmp(state, _NAV));
	rgblight_set_layer_state(2, layer_state_cmp(state, _NAV2));
	rgblight_set_layer_state(3, layer_state_cmp(state, _GAME));
	rgblight_set_layer_state(5, layer_state_cmp(state, _GAME2));
	rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
	// rgblight_set_layer_state(5, layer_state_cmp(state, _SWITCH));
}


#ifdef RGBLIGHT_TIMEOUT
void rgb_idle_key_pressed(void){
    // we just pressed a key, so turn on rgb if it was off
    if (!rgb_on) {
        rgblight_enable_noeeprom();
        rgb_on = true;
    }

    // reset the idle timer
    idle_timer_reset();
}

void rgb_idle_check_timer(void){

    // If the leds are on and no key has been pressed for since the timeout
    // save the rgb states, turn the leds off
    if ( rgb_on && idle_timer_check(RGBLIGHT_TIMEOUT)) {
        rgblight_disable_noeeprom();
        rgb_on = false;
    }
}
#endif

void rgb_init(void){
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

	rgblight_mode(10);// haven't found a way to set this in a more useful way

    #ifdef RGBLIGHT_TIMEOUT

        // start the idle timer
        idle_timer_init();

    #endif
}

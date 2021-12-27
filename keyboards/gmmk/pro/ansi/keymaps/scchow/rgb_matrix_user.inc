// Based on code from 
// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED // We can only use these custom effects if Key Reactive effects is enabled

// Copying the SOLID_REACTIVE_WIDE effect to ensure
// I know what the functions do
RGB_MATRIX_EFFECT(my_solid_reactive_wide)

// Random Reactive Fade
// On a keypress - light up the key with a random color
// and slowly fade
RGB_MATRIX_EFFECT(random_color_reactive)

// Turn off all RGB effects, but keep indicator lights
RGB_MATRIX_EFFECT(turn_effects_off)

// Step 2.
// Define effects inside the `RGB_MATRIX_CUSTOM_EFFECT_IMPLS` ifdef block
#ifdef RGB_MATRIX_CUSTOM_EFFECT_IMPLS

/// First thing we want to do is try to recreate SOLID_REACTIVE_MULTIWIDE

/* SOLID_REACTIVE_WIDE_math
 * Args:
 *  hsv (HSV): Hue/Saturation/Value object to return
 *  dx, dy: x,y displacement between current LED to consider and LED of key pressed
 *  dist: distance between current LED and LED of key pressed
 *  tick: some measurement of how long it's been since the key was pressed?
 */
static HSV my_SOLID_REACTIVE_WIDE_math(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick) {
    // how weak the lighting effect is proportional to how long its been and how far away the pressed key was
    // 5 is probably a magic number
    uint16_t effect = tick + dist * 5;
    // Cap effect to 255
    if (effect > 255) effect = 255;
    // The actual brightness of LED is max brightness - lighting effect
    // Add to current hsv.v value so if you press multiple keys, next to each other,
    // the effects overlap
    hsv.v = qadd8(hsv.v, 255 - effect);
    // Return the updated HSV of the LED
    return hsv;
}

// Create a function type that takes in HSV, int16_t, int16_t, uint8_t, uint16_t and outputs an HSV
// Notice this matches the function definition of SOLID_REACTIVE_WIDE_math
typedef HSV (*reactive_splash_f)(HSV hsv, int16_t dx, int16_t dy, uint8_t dist, uint16_t tick);

// The heavy lifting function of computing the HSV of all the LEDS
// Takes in our SOLID_REACTIVE_WIDE_math as a function in our use case,
// But is general enough that it could take in any function to 
// determine RGB values, as long as it fits the reactive_splash_f function signature 
// defined above.
bool my_effect_runner_reactive_splash(uint8_t start, effect_params_t* params, reactive_splash_f effect_func) {
    // Use led_min, led_max to determine min and max indices of LEDs
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // grab the number of previous key presses tracked
    uint8_t count = g_last_hit_tracker.count;

    // For every LED
    for (uint8_t i = led_min; i < led_max; i++) {
        // DO something with TEST LED flags???
        RGB_MATRIX_TEST_LED_FLAGS();
        // Grab HSV from matrix config
        HSV hsv = rgb_matrix_config.hsv;
        // Set brightness to 0 by default
        hsv.v   = 0;
        // Loop through every one of our previous presses that we are tracking
        for (uint8_t j = start; j < count; j++) {
            // compute displacement and distance between current i-th LED and our j-th pressed key
            int16_t  dx   = g_led_config.point[i].x - g_last_hit_tracker.x[j];
            int16_t  dy   = g_led_config.point[i].y - g_last_hit_tracker.y[j];
            uint8_t  dist = sqrt16(dx * dx + dy * dy);

            // Some sort of math is going on here
            // We are adding 1 to our rgb_matrix_config.speed (maybe in case speed set to 0)
            // Now we scale the time elapsed by this modified speed (larger the speed, the larger output)
            uint16_t tick = scale16by8(g_last_hit_tracker.tick[j], qadd8(rgb_matrix_config.speed, 1));
            // We use our effect function to update HSV value
            hsv           = effect_func(hsv, dx, dy, dist, tick);
        }
        // Scale down hsv.v by the brightness allowed by the configuration file
        hsv.v   = scale8(hsv.v, rgb_matrix_config.hsv.v);
        // convert to RGB and send the value
        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

// The main function that calls the main heavylifting function
// Provides are LED lighting function as an input to be called 
// to compute LED values
bool my_solid_reactive_wide(effect_params_t* params) {
     return my_effect_runner_reactive_splash(qsub8(g_last_hit_tracker.count, 1), params, &my_SOLID_REACTIVE_WIDE_math); 
}


// Create a struct keeping track of color for key and brightness/time since last pressed
struct key_color { 
    int h;          // hue - color of key
    uint16_t last_hit;   // time since last press
}; 

// Create an array to track each key
static struct key_color color_map[DRIVER_LED_TOTAL]; 

// Randomly assign a color to each key
void populate_map(void){
    srand(osalOsGetSystemTimeX());
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        int h = rand() % 256;
        color_map[i].h = h;
        color_map[i].last_hit = 65535; //Max time since last hit
    }
}

/* random_color_reactive: my custom function for a reactive RGB scheme
 *  where colors are randomly changed with every keypress
 *
 * This was created by modifying functions from
 * `solid_reactive_simple_anim.h` and `effect_runner_reactive.h` 
 * to additionally track an array of hues/tick last pressed.
 * Based on: https://www.reddit.com/r/MechanicalKeyboards/comments/hx5v2x/my_adventure_with_custom_lighting_effects_in_qmk/
 */
bool random_color_reactive(effect_params_t* params) {
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // If this is the first time start up, randomize the color scheme.
    // and initialize the array
    if (params->init){
        populate_map();
    }

    srand(osalOsGetSystemTimeX());

    // Maximum amount of ticks before effect is over (I think?)
    uint16_t max_tick = 65535 / qadd8(rgb_matrix_config.speed, 1);

    // Predeclare tick variable
    uint16_t tick;

    // Loop through LEDS
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        // Last time we saw this key was max_ticks before by default
        tick = max_tick;

        // Reverse search to find most recent key hit
        // Go backwards through the list of keys pressed history
        for (int8_t j = g_last_hit_tracker.count - 1; j >= 0; j--) {
            // If we have pressed the current key recently
            // AND it hasn't been long enough for the effect to end
            // then we still need to process the key to determine its brightness
            if (g_last_hit_tracker.index[j] == i && g_last_hit_tracker.tick[j] < tick) {
                tick = g_last_hit_tracker.tick[j];
                // If this is the most recently pressed key, we need to check
                if (j == g_last_hit_tracker.count - 1){
                    // If we have not changed the Hue of this key since it's been last pressed
                    // then we need to reroll the key's hue
                    if (tick < color_map[i].last_hit){
                        color_map[i].h = rand() % 256;
                    }
                    color_map[i].last_hit = tick;
                }
                break;
            }
        }

        uint16_t offset = scale16by8(tick, qadd8(rgb_matrix_config.speed, 1));

        HSV hsv = {.h = color_map[i].h, 
                   .s = rgb_matrix_config.hsv.s, 
                   .v = scale8(255 - offset, rgb_matrix_config.hsv.v)};

        RGB rgb = rgb_matrix_hsv_to_rgb(hsv);

        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

bool turn_effects_off(effect_params_t* params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // We can't use rgb_matrix_set_color_all 
    // because it will also
    // turn off indicator light effects
    // rgb_matrix_set_color_all(0,0,0);

    // Loop through LEDS
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, 0, 0, 0);
    }
    return rgb_matrix_check_finished_leds(led_max);
}

#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED

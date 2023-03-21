// !!! DO NOT ADD #pragma once !!! //

// Step 1.
// Declare custom effects using the RGB_MATRIX_EFFECT macro
// (note the lack of semicolon after the macro!)

// Copying the SOLID_REACTIVE_WIDE effect to ensure
// I know what the functions do
RGB_MATRIX_EFFECT(my_solid_reactive_wide)

// Random Reactive Fade
// On a keypress - light up the key with a random color
// and slowly fade
RGB_MATRIX_EFFECT(random_color_reactive)

// Turn off all RGB effects, but keep indicator lights
RGB_MATRIX_EFFECT(turn_effects_off)

// Better breathing effect
RGB_MATRIX_EFFECT(better_breathing)

#ifdef RGB_MATRIX_KEYREACTIVE_ENABLED // We can only use these custom effects if Key Reactive effects is enabled

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
static struct key_color color_map[RGB_MATRIX_LED_COUNT];

// Randomly assign a color to each key
void populate_map(void){
    srand(osalOsGetSystemTimeX());
    for (int i = 0; i < RGB_MATRIX_LED_COUNT; i++) {
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

#define RGBLIGHT_BREATHE_TABLE_SIZE 256


// http://sean.voisen.org/blog/2011/10/breathing-led-with-arduino/
// Table generated by plugging in equation in link,
// V = (exp(sin(w*t-(pi/2))) - (1/e)) * 255/(e-1/e)
// Where V is the brightness value
// s = 128 is the speed setting at which there is 1 breath every 3 seconds
// w = (pi/2) * 1/1000 (accounting for ms and periodicity)
// t = time in ms
// distributing across 3000 second period across 255 steps
const uint8_t rgblight_effect_breathe_table[] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x01,
    0x01, 0x01, 0x01, 0x02, 0x02, 0x02, 0x03, 0x03,
    0x04, 0x04, 0x05, 0x05, 0x06, 0x06, 0x07, 0x07,
    0x08, 0x09, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E,
    0x0F, 0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x17,
    0x18, 0x19, 0x1B, 0x1C, 0x1E, 0x1F, 0x21, 0x22,
    0x24, 0x26, 0x28, 0x2A, 0x2C, 0x2E, 0x30, 0x32,
    0x34, 0x36, 0x39, 0x3B, 0x3D, 0x40, 0x43, 0x45,
    0x48, 0x4B, 0x4E, 0x51, 0x54, 0x57, 0x5A, 0x5D,
    0x60, 0x63, 0x67, 0x6A, 0x6E, 0x71, 0x75, 0x78,
    0x7C, 0x80, 0x83, 0x87, 0x8B, 0x8F, 0x93, 0x97,
    0x9A, 0x9E, 0xA2, 0xA6, 0xAA, 0xAE, 0xB2, 0xB6,
    0xB9, 0xBD, 0xC1, 0xC5, 0xC8, 0xCC, 0xCF, 0xD3,
    0xD6, 0xD9, 0xDC, 0xDF, 0xE2, 0xE5, 0xE8, 0xEA,
    0xED, 0xEF, 0xF1, 0xF3, 0xF5, 0xF7, 0xF9, 0xFA,
    0xFB, 0xFC, 0xFD, 0xFE, 0xFE, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFE, 0xFE, 0xFD, 0xFC, 0xFB, 0xFA, 0xF9,
    0xF7, 0xF5, 0xF3, 0xF1, 0xEF, 0xED, 0xEA, 0xE8,
    0xE5, 0xE2, 0xDF, 0xDC, 0xD9, 0xD6, 0xD3, 0xCF,
    0xCC, 0xC8, 0xC5, 0xC1, 0xBD, 0xB9, 0xB6, 0xB2,
    0xAE, 0xAA, 0xA6, 0xA2, 0x9E, 0x9A, 0x97, 0x93,
    0x8F, 0x8B, 0x87, 0x83, 0x80, 0x7C, 0x78, 0x75,
    0x71, 0x6E, 0x6A, 0x67, 0x63, 0x60, 0x5D, 0x5A,
    0x57, 0x54, 0x51, 0x4E, 0x4B, 0x48, 0x45, 0x43,
    0x40, 0x3D, 0x3B, 0x39, 0x36, 0x34, 0x32, 0x30,
    0x2E, 0x2C, 0x2A, 0x28, 0x26, 0x24, 0x22, 0x21,
    0x1F, 0x1E, 0x1C, 0x1B, 0x19, 0x18, 0x17, 0x15,
    0x14, 0x13, 0x12, 0x11, 0x10, 0x0F, 0x0E, 0x0D,
    0x0C, 0x0B, 0x0A, 0x09, 0x09, 0x08, 0x07, 0x07,
    0x06, 0x06, 0x05, 0x05, 0x04, 0x04, 0x03, 0x03,
    0x02, 0x02, 0x02, 0x01, 0x01, 0x01, 0x01, 0x01,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

bool better_breathing(effect_params_t *params){
    RGB_MATRIX_USE_LIMITS(led_min, led_max);

    // g_rgb_timer is the time in ms represented by a uint32_t
    // rgb_matrix_config.speed is a uint8_t where the higher the value, the faster the animation should be


    // We see this scale16by8 a bunch,
    // We are actually just truncating the 32-bit timer to its last 16 bits
    // and then performing a scaling:
    // scaled_time = timer * (rgb_matrix_config.speed / 256)
    // So why not just directly cast g_rgb_timer straight into uint8_t
    // and scale by speed
    // Divide speed by 8 to slow down the animation time because we are working
    // in milliseconds

    // Tried this but was unable to get it to work at the moment.
    // uint8_t time = (uint16_t) ((delta_frequency * (floatf) rgb_matrix_config.speed  + min_frequency) * (float) g_rgb_timer) % 255;

    static uint16_t period;
    static uint8_t time;
    static HSV      hsv;
    static RGB rgb;

    // The /4 is to make it so that the effect never goes too quickly
    // Tuned by adjusting it until the effect looked right
    period = 25*(256-rgb_matrix_config.speed/4);

    hsv = rgb_matrix_config.hsv;

    // If period = 0 due to speed == 255, we could get divide by 0 error
    // So add a specific check here.
    // If period is somehow 0, then we will have the light on all the time.
    if (period > 0){
        time = floor((255.0/period) * (g_rgb_timer % period));
        hsv.v = scale8(rgblight_effect_breathe_table[time], (rgb_matrix_config.hsv.v));
    }

    // double val = ((exp(sin( (double) g_rgb_timer* time_multiplier * (double) rgb_matrix_config.speed)) - 0.25751560882)*105.0);
    // hsv.v  = (uint8_t) val;


    rgb = rgb_matrix_hsv_to_rgb(hsv);
    for (uint8_t i = led_min; i < led_max; i++) {
        RGB_MATRIX_TEST_LED_FLAGS();
        rgb_matrix_set_color(i, rgb.r, rgb.g, rgb.b);
    }

    #ifdef CONSOLE_ENABLE
    // dprintf("%u,  ", rgb_matrix_config.speed);
    // dprintf("%u,", g_rgb_timer);
    // dprintf("%u, ", time);
    // dprintf("%u\n", hsv.v);
    // dprintf("%u, %u, %u\n", rgb_matrix_config.speed, time, hsv.v);
    #endif // CONSOLE_ENABLE

    return rgb_matrix_check_finished_leds(led_max);
}
#endif // RGB_MATRIX_CUSTOM_EFFECT_IMPLS
#endif          // RGB_MATRIX_KEYREACTIVE_ENABLED

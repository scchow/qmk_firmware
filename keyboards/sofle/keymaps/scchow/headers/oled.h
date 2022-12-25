#pragma once

// include oled driver from qmk_firmware/drivers/oled/oled_driver.h
#include "oled_driver.h"

// Include layer names
#include "enums.h"

// Include bongo cat data
#include "data/bongo_cat.h"

// int/char arr for holding WPM
uint8_t wpm_int = 0;
char wpm_str[4] = {'0', '0', '0', '\0'};

// TODO: Change name here if you want to use my code :)
const PROGMEM char *wpm_status_str = PSTR("\n\nScottChow\n\n\nWPM\n\n");
const PROGMEM char *layer_status_str = PSTR("\n\nLAYER\n");


// Print the status bar message
static void print_status_narrow(uint8_t wpm){
    // Print status message
    oled_write_P(wpm_status_str, false);

    // Safer wpm printing from:
    //https://github.com/saikocat/keebs/blob/master/docs/qmk_missing_guide/oled.md#wpm-display-optimization
    wpm_str[0] = '0' + wpm / 100; // hundreds digit
    wpm_str[1] = '0' + (wpm / 10) % 10; // tens digit
    wpm_str[2] = '0' + wpm % 10; // ones digit
    oled_write_ln(wpm_str, false);

    // Print current layer
    oled_write_P(layer_status_str, false);
    switch (get_highest_layer(layer_state)) {
        case _BASE:
            oled_write_ln("Base", false);
            break;
        case _NAV:
            oled_write_ln("Nav", false);
            break;
        case _NAV2:
            oled_write_ln("Nav2", false);
            break;
        case _GAME:
            oled_write_ln("Game", false);
            break;
        case _GAME2:
            oled_write_ln("Game2", false);
            break;
        case _NUMPAD:
            oled_write_ln("Nump", false);
            break;
        default:
            oled_write_ln("Undef", false);
    }
}

#ifdef USE_QMK_LOGO
    #include "data/qmk_logo.h"
#endif


// Render the image
//   assumes animation_phase(wpm) has been defined in
//   data/bongo_cat.h or whichever animation file you use
static void render_anim(uint8_t wpm) {
    //   Credit to obosob for initial animation approach.
    if(timer_elapsed32(anim_timer) > ANIM_FRAME_DURATION) {
        anim_timer = timer_read32();
        animation_phase(wpm);
    }
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (is_keyboard_master()) {
        return OLED_ROTATION_270;
    }
    return rotation + OLED_ROTATION_180;
}

// Actually render the oled images
bool oled_task_user(void) {
    wpm_int = get_current_wpm();

    // render status on master
    if (is_keyboard_master()) {
        print_status_narrow(wpm_int);
    }

    // render logo on secondary
    else {
        render_anim(wpm_int);
    }

    return false;
}

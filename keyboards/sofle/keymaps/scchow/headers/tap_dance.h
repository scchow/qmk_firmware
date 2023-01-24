#pragma once

#include QMK_KEYBOARD_H

enum {
    TD_LCTL_LALT,
    TD_LALT_LCTL,
};

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    // Tap once for CTRL, twice for ALT
    [TD_LCTL_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LALT),
    // Tap once for ALT, twice for CTRL
    [TD_LALT_LCTL] = ACTION_TAP_DANCE_DOUBLE(KC_LALT, KC_LCTL),
};

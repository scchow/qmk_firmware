#pragma once

#include QMK_KEYBOARD_H
#include "enums.h"

// Tap Dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
    // Tap once for Escape, twice for Caps Lock
    [TD_LCTL_LALT] = ACTION_TAP_DANCE_DOUBLE(KC_LCTL, KC_LALT),
};

#pragma once

enum sofle_layers {
    _DEFAULTS = 0,
    _BASE = 0,
    _LOWER,
    _RAISE,
    _COMB, // Must have higher layer number than _LOWER/_RAISE
    _GAME,
    _GAME2,
    _NUMPAD,
    _SWITCH,
    _CONFIG
};

enum custom_keycodes {
    KC_BASE = SAFE_RANGE,
    KC_D_MUTE,
    KC_LOWER,
    KC_RAISE
};


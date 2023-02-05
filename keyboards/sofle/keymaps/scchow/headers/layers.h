#pragma once

#include "../../sofle.h"

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
  KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    LT(_CONFIG, KC_5),LT(_CONFIG,KC_6),    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  //|---------------+-------+--------+--------+-------+------|  |--------+-------+--------+--------+--------+---------|
  KC_TAB, KC_Q,   KC_W,   KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  //|---------------+-------+--------+--------+-------+------|  |--------+-------+--------+--------+--------+---------|
  LT(_NAV2,KC_ESC),  KC_A,   KC_S,   KC_D,    KC_F,    KC_G,     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  //|------+-------+--------+--------+--------+------|  ===  |  |  ===  |--------+-------+--------+--------+--------+---------|
  KC_LSFT, KC_Z,   KC_X,    KC_C,    KC_V,    KC_B,  QK_BOOT,    KC_MUTE, KC_N,    KC_M,   KC_COMM, KC_DOT,  KC_SLSH,  KC_ENT,
  //|------+-------+--------+--------+--------+------|  ===  |  |  ===  |--------+-------+----------+--------+--------+---------|
         KC_LALT, KC_LGUI, TT(_NAV), KC_SPC, TD(TD_LCTL_LALT),   KC_BSPC, KC_SPC,  KC_ENT, TT(_NAV), TG(_GAME)
  //    \-------+--------+---------+-------+-----------------|  |-------+--------+--------+---------+-------/
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
 LCA(KC_DEL),LCTL(KC_Q),      KC_NO,      KC_UP,LCTL(KC_R),LCTL(KC_T),               LCTL(KC_Y), KC_EQL, KC_MINS,  KC_LBRC, KC_RBRC, KC_F11,
  //|------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
     _______,LCTL(KC_A),    KC_LEFT,    KC_DOWN,KC_RIGHT,   KC_NO,                      KC_LEFT,KC_DOWN,   KC_UP, KC_RGHT, KC_NO,   KC_F12,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
_______,LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), LCTL(KC_S), _______,   _______,   KC_NO, KC_UNDS,KC_PLUS, KC_LCBR, KC_RCBR,    KC_NO,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
                               _______, _______, TG(_NAV), _______,  _______,    KC_DEL,  _______,   _______, TG(_NAV), _______
  //                         \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
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
 LCA(KC_DEL),     KC_NO,      KC_NO,    KC_PGUP,   KC_NO,   KC_NO,                   LCTL(KC_Y), KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_F11,
  //|------+-----------+-----------+-----------+--------+--------|                    |--------+-------+--------+--------+--------+---------|
     _______,   KC_NO, KC_HOME,    KC_PGDN,    KC_END,     KC_NO,                     KC_HOME, KC_PGDN, KC_PGUP, KC_END, KC_NO,   KC_F12,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
 _______,LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), _______, _______,    _______,    KC_NO, KC_UNDS,KC_PLUS, KC_LCBR, KC_RCBR,    KC_NO,
  //|------+-----------+-----------+-----------+--------+--------|  ====  |   |  ===  |--------+-------+--------+--------+--------+---------|
                              _______, _______, _______, _______, _______,     KC_DEL, _______, _______, _______, _______
  //                         \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
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
                               KC_LSFT , KC_LGUI,  KC_SPC, KC_LALT,KC_LCTL,     KC_RSFT,   KC_SPC,   MO(3),    MO(4), TG(_GAME)
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
  _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC, KC_P7,  KC_P8,   KC_P9,   KC_ASTR, XXXXXXX,
  //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS, KC_P4,  KC_P5,   KC_P6,   KC_EQL,  KC_PIPE,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,_______,   _______,KC_PLUS, KC_P1,  KC_P2,   KC_P3,   KC_SLSH, _______,
  //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
              _______, OSM(MOD_MEH), _______, _______, _______,   _______, _______,  KC_P0,   KC_PDOT, _______
  //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
),
[_CONFIG] = LAYOUT(
  //|--------+--------+---------+---------+---------+----------|                      |----------+----------+----------+----------+----------+----------|
      RGB_TOG, RGB_M_P,  RGB_M_B,  RGB_M_R, RGB_M_SW,  _______,                           _______,  RGB_M_SN,   _______,   _______,   _______,   RGB_TOG,
  //|--------+--------+---------+---------+---------+----------|                      |----------+----------+----------+----------+----------+----------|
      RGB_MOD, RGB_M_K,  RGB_M_X,  RGB_M_G,  RGB_M_T,  RGB_M_TW,                          _______,   _______,   _______,   _______,   _______,   _______,
  //|--------+--------+---------+---------+---------+----------|                      |----------+----------+----------+----------+----------+----------|
     RGB_RMOD,   KC_NO,  RGB_HUI,  RGB_SAI,  RGB_VAI,     KC_NO,                          _______,   _______,   _______,   _______,   _______,   _______,
  //|--------+--------+---------+---------+---------+----------|   ===   |   |   ===   |----------+----------+----------+----------+----------+----------|
      KC_LSFT,   KC_NO,  RGB_HUI,  RGB_SAD,  RGB_VAD,     KC_NO,  QK_BOOT,      QK_BOOT,   NK_TOGG,   _______,   _______,   _______,   _______,   KC_LSFT,
  //|--------+--------+---------+---------+---------+----------|   ===   |   |   ===   |----------+----------+----------+----------+----------+----------|
                             EH_LEFT, EH_RGHT, _______,  _______, EE_CLR,      EE_CLR,   _______, _______,  EH_RGHT, EH_LEFT
  //                       \--------+--------+--------+---------+--------|   |--------+----------+--------+---------+--------/
),
};

/* Copyright 2021 weteor
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

#include QMK_KEYBOARD_H
#include "os_detection.h"

enum layers
{
    _COLEMAK_PC = 0,
    _COLEMAK_MAC,
    _QWERTY_GAMING,
    _SYMBOLS_PC,
    _SYMBOLS_MAC,
    _BRACKETS_PC,
    _BRACKETS_MAC,
    _NAVIGATION_PC,
    _NAVIGATION_MAC,
    _NUMBERS,
    _SHORTCUTS_PC,
    _SHORTCUTS_MAC,
    _FUNCTION,
};

void keyboard_post_init_user(void) {
    // Set initial RGB mode to solid color and color to blue (PC default)
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv(HSV_BLUE);
}

// Function to handle OS detection changes
bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            // Switch to Mac layer
            default_layer_set(1UL << _COLEMAK_MAC);
            rgb_matrix_sethsv(HSV_WHITE);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        default:
            // Switch to PC layer
            default_layer_set(1UL << _COLEMAK_PC);
            rgb_matrix_sethsv(HSV_BLUE);
            break;
    }
    return true;
}

// Function to handle manual layer changes (for gaming mode)
layer_state_t default_layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
        case _COLEMAK_PC:
            rgb_matrix_sethsv(HSV_BLUE);
            break;
        case _COLEMAK_MAC:
            rgb_matrix_sethsv(HSV_WHITE);
            break;
        case _QWERTY_GAMING:
            rgb_matrix_sethsv(HSV_RED);
            break;
    }
    return state;
}

#define TH_ESC_PC LT(_SHORTCUTS_PC,KC_ESC)
#define TH_ESC_MAC LT(_SHORTCUTS_MAC,KC_ESC)
#define TH_SPC_PC LT(_BRACKETS_PC,KC_SPC)
#define TH_SPC_MAC LT(_BRACKETS_MAC,KC_SPC)
#define TH_TAB_PC LT(_NAVIGATION_PC, KC_TAB)
#define TH_TAB_MAC LT(_NAVIGATION_MAC, KC_TAB)
#define TH_ENT LT(_NUMBERS, KC_ENT)
#define TH_BSPC_PC LT(_SYMBOLS_PC, KC_BSPC)
#define TH_BSPC_MAC LT(_SYMBOLS_MAC, KC_BSPC)
#define TH_DEL LT(_FUNCTION, KC_DEL)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_PC] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,                 KC_J,    KC_L,         KC_U,         KC_Y,         KC_QUOT,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,                 KC_M,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O),
        KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,                 KC_K,    KC_H,         KC_COMM,      KC_DOT,       KC_SLSH,
                                           TH_ESC_PC, TH_SPC_PC, TH_TAB_PC,     TH_ENT, TH_BSPC_PC, TH_DEL
    ),
    [_COLEMAK_MAC] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,         KC_F,         KC_P,         KC_B,                 KC_J,    KC_L,    KC_U,    KC_Y,    KC_QUOT,
        LGUI_T(KC_A), LALT_T(KC_R), LCTL_T(KC_S), LSFT_T(KC_T), KC_G,                 KC_M,    RSFT_T(KC_N), RCTL_T(KC_E), RALT_T(KC_I), RGUI_T(KC_O),
        KC_Z,         KC_X,         KC_C,         KC_D,         KC_V,                 KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH,
                                       TH_ESC_MAC,  TH_SPC_MAC, TH_TAB_MAC,     TH_ENT, TH_BSPC_MAC, TH_DEL
    ),
    [_QWERTY_GAMING] = LAYOUT_split_3x5_3(
        KC_Q,         KC_W,    KC_E,    KC_R,    KC_T,                   KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
        KC_A,         KC_S,    KC_D,    KC_F,    KC_G,                   KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN,
        KC_Z,         KC_X,    KC_C,    KC_V,    KC_B,                   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                                      KC_ESC, KC_SPC, KC_TAB,     TH_ENT, KC_BSPC, TH_DEL
    ),
    [_SYMBOLS_PC] = LAYOUT_split_3x5_3(
        LSFT(KC_2),   LSFT(KC_4),    LSFT(KC_3), LSFT(KC_5),    LSFT(KC_8),                LSFT(KC_8),    LSFT(KC_5),    LSFT(KC_3), LSFT(KC_4),    LSFT(KC_2),
        LSFT(KC_7),   LSFT(KC_BSLS), LSFT(KC_6), KC_BSLS,       KC_SLSH,                   KC_SLSH,       KC_BSLS,       LSFT(KC_6), LSFT(KC_BSLS), LSFT(KC_7),
        LSFT(KC_GRV), LSFT(KC_EQL),  KC_MINS,    LSFT(KC_MINS), LSFT(KC_SLSH),             LSFT(KC_SLSH), LSFT(KC_MINS), KC_MINS,    LSFT(KC_EQL),  LSFT(KC_GRV),
                                                               KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),
    [_SYMBOLS_MAC] = LAYOUT_split_3x5_3(
        LSFT(KC_2),   LSFT(KC_4),    LSFT(KC_3), LSFT(KC_5),    LSFT(KC_8),                LSFT(KC_8),    LSFT(KC_5),    LSFT(KC_3), LSFT(KC_4),    LSFT(KC_2),
        LSFT(KC_7),   LSFT(KC_BSLS), LSFT(KC_6), KC_BSLS,       KC_SLSH,                   KC_SLSH,       KC_BSLS,       LSFT(KC_6), LSFT(KC_BSLS), LSFT(KC_7),
        LSFT(KC_GRV), LSFT(KC_EQL),  KC_MINS,    LSFT(KC_MINS), LSFT(KC_SLSH),             LSFT(KC_SLSH), LSFT(KC_MINS), KC_MINS,    LSFT(KC_EQL),  LSFT(KC_GRV),
                                                               KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),
    [_BRACKETS_PC] = LAYOUT_split_3x5_3(
        KC_LBRC,         KC_RBRC,       LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_SCLN),         LSFT(KC_SCLN), LSFT(KC_COMM), LSFT(KC_DOT),  KC_LBRC,       KC_RBRC,
        LSFT(KC_LBRC),   LSFT(KC_RBRC), LSFT(KC_9),    LSFT(KC_0),   KC_SCLN,               KC_SCLN,       LSFT(KC_9),    LSFT(KC_0),    LSFT(KC_LBRC), LSFT(KC_RBRC),
        KC_GRV,          KC_QUOT,       LSFT(KC_QUOT), LSFT(KC_1),   KC_EQL,                KC_EQL,        LSFT(KC_1),    LSFT(KC_QUOT), KC_QUOT,       KC_GRV,
                                                               KC_NO, KC_NO, KC_NO,      KC_NO, KC_BSPC, KC_DEL
    ),
    [_BRACKETS_MAC] = LAYOUT_split_3x5_3(
        KC_LBRC,         KC_RBRC,       LSFT(KC_COMM), LSFT(KC_DOT), LSFT(KC_SCLN),         LSFT(KC_SCLN), LSFT(KC_COMM), LSFT(KC_DOT),  KC_LBRC,       KC_RBRC,
        LSFT(KC_LBRC),   LSFT(KC_RBRC), LSFT(KC_9),    LSFT(KC_0),   KC_SCLN,               KC_SCLN,       LSFT(KC_9),    LSFT(KC_0),    LSFT(KC_LBRC), LSFT(KC_RBRC),
        KC_GRV,          KC_QUOT,       LSFT(KC_QUOT), LSFT(KC_1),   KC_EQL,                KC_EQL,        LSFT(KC_1),    LSFT(KC_QUOT), KC_QUOT,       KC_GRV,
                                                              KC_NO, KC_NO, KC_NO,       KC_NO, KC_BSPC, KC_DEL
    ),
    [_NAVIGATION_PC] = LAYOUT_split_3x5_3(
        LCTL(KC_Z), LCTL(KC_X),    LCTL(KC_C),    LCTL(KC_V), LCTL(KC_Y),           LCTL(KC_Y), LCTL(KC_V), LCTL(KC_C),    LCTL(KC_X),    LCTL(KC_Z),
        KC_LEFT,    KC_DOWN,       KC_UP,         KC_RIGHT,   LCTL(KC_P),           LCTL(KC_P), KC_LEFT,    KC_DOWN,       KC_UP,         KC_RIGHT,
        LCTL(KC_G), LCTL(KC_MINS), C(S(KC_MINS)), C(S(KC_O)), C(S(KC_P)),           C(S(KC_P)), C(S(KC_O)), C(S(KC_MINS)), LCTL(KC_MINS), LCTL(KC_G),
                                             LCTL(KC_A), LCTL(KC_S), KC_NO,       KC_NO, KC_BSPC, KC_DEL
    ),
    [_NAVIGATION_MAC] = LAYOUT_split_3x5_3(
        LGUI(KC_Z), LGUI(KC_X),    LGUI(KC_C),    LGUI(KC_V), LGUI(KC_Y),           LGUI(KC_Y), LGUI(KC_V), LGUI(KC_C),    LGUI(KC_X),    LGUI(KC_Z),
        KC_LEFT,    KC_DOWN,       KC_UP,         KC_RIGHT,   LGUI(KC_P),           LGUI(KC_P), KC_LEFT,    KC_DOWN,       KC_UP,         KC_RIGHT,
        LCTL(KC_G), LCTL(KC_MINS), C(S(KC_MINS)), SGUI(KC_O), SGUI(KC_P),           SGUI(KC_P), SGUI(KC_O), C(S(KC_MINS)), LCTL(KC_MINS), LCTL(KC_G),
                                              LGUI(KC_A), LGUI(KC_S), KC_NO,     KC_NO, KC_BSPC, KC_DEL
    ),
    [_NUMBERS] = LAYOUT_split_3x5_3(
        LSFT(KC_8), KC_7, KC_8, KC_9, LSFT(KC_EQL),                  LSFT(KC_EQL), KC_7, KC_8, KC_9, LSFT(KC_8),
        KC_SLSH,    KC_4, KC_5, KC_6, KC_MINS,                       KC_MINS,      KC_4, KC_5, KC_6, KC_SLSH,
        KC_0,       KC_1, KC_2, KC_3, KC_EQL,                        KC_EQL,       KC_1, KC_2, KC_3, KC_0,
                                   KC_COMM, KC_DOT, KC_ENT,     KC_NO, KC_DOT, KC_COMM
    ),
    [_SHORTCUTS_PC] = LAYOUT_split_3x5_3(
        C(S(KC_F)), C(KC_F4), C(S(KC_MINS)), C(KC_MINS), LCA(KC_I),           LCA(KC_I),       C(KC_MINS),    C(S(KC_MINS)),  C(KC_F4),         C(S(KC_F)),
        LGUI(S(KC_S)), LSA(KC_F), C(S(KC_O)), C(KC_F), C(S(KC_SLSH)),         C(S(KC_SLSH)),   C(KC_F),       C(S(KC_O)),     LSA(KC_F),        LGUI(S(KC_S)),
        KC_TRNS, C(KC_TAB), C(S(KC_TAB)), C(S(KC_H)), C(KC_H),                C(KC_H),         C(S(KC_H)),    C(S(KC_TAB)),   C(KC_TAB),        KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_SHORTCUTS_MAC] = LAYOUT_split_3x5_3(
        G(S(KC_F)), G(KC_W), LGUI(KC_EQL), LGUI(KC_MINS), G(A(KC_I)),         G(A(KC_I)),      LGUI(KC_MINS), LGUI(KC_EQL),  G(KC_W),          G(S(KC_F)),
        G(S(KC_4)), G(S(A(KC_F))), G(S(KC_O)), G(KC_F), G(S(KC_SLSH)),        G(S(KC_SLSH)),   G(KC_F),       G(S(KC_O)),    G(S(A(KC_F))),    G(S(KC_4)),
        KC_TRNS, C(KC_TAB), C(S(KC_TAB)), G(S(KC_H)), G(A(KC_F)),             G(A(KC_F)),      G(S(KC_H)),    C(S(KC_TAB)),  C(KC_TAB),        KC_TRNS,
                                           KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_FUNCTION] = LAYOUT_split_3x5_3(
        KC_NO, KC_F9, KC_F10, KC_F11, KC_F12,                 KC_F9, KC_F10, KC_F11, KC_F12, DF(_COLEMAK_PC),
        KC_NO, KC_F5, KC_F6,  KC_F7,  KC_F8,                  KC_F5, KC_F6,  KC_F7,  KC_F8,  DF(_COLEMAK_MAC),
        KC_NO, KC_F1, KC_F2,  KC_F3,  KC_F4,                  KC_F1, KC_F2,  KC_F3,  KC_F4,  DF(_QWERTY_GAMING),
                              KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),
};

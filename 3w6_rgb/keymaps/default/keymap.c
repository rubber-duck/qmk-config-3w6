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
    _BRACKETS,
    _NAVIGATION_PC,
    _NAVIGATION_MAC,
    _NUMBERS,
    _FUNCTION,
    _SYMBOLS,
    _SHORTCUTS_PC,
    _SHORTCUTS_MAC,
};

#define TH_ESC_PC LT(_SHORTCUTS_PC,KC_ESC)
#define TH_ESC_MAC LT(_SHORTCUTS_MAC,KC_ESC)
#define TH_SPC LT(_BRACKETS,KC_SPC)
#define TH_TAB_PC LT(_NAVIGATION_PC, KC_TAB)
#define TH_TAB_MAC LT(_NAVIGATION_MAC, KC_TAB)
#define TH_ENT LT(_NUMBERS, KC_ENT)
#define TH_BSPC LT(_SYMBOLS, KC_BSPC)
#define TH_DEL LT(_FUNCTION, KC_DEL)

#define HR_A LGUI_T(KC_A)
#define HR_R LALT_T(KC_R)
#define HR_S LCTL_T(KC_S)
#define HR_T LSFT_T(KC_T)
#define HR_N RSFT_T(KC_N)
#define HR_E RCTL_T(KC_E)
#define HR_I RALT_T(KC_I)
#define HR_O RGUI_T(KC_O)

#define SYM_AT LSFT(KC_2)
#define SYM_DLR LSFT(KC_4)
#define SYM_HASH LSFT(KC_3)
#define SYM_PERC LSFT(KC_5)
#define SYM_ASTR LSFT(KC_8)
#define SYM_AMPR LSFT(KC_7)
#define SYM_PIPE LSFT(KC_BSLS)
#define SYM_CARET LSFT(KC_6)
#define SYM_BSLS KC_BSLS
#define SYM_SLSH KC_SLSH
#define SYM_TILD LSFT(KC_GRV)
#define SYM_PLUS LSFT(KC_EQL)
#define SYM_MINS KC_MINS
#define SYM_UNDS LSFT(KC_MINS)
#define SYM_QUES LSFT(KC_SLSH)
#define SYM_LBRC KC_LBRC
#define SYM_RBRC KC_RBRC
#define SYM_LABR LSFT(KC_COMM)
#define SYM_RABR LSFT(KC_DOT)
#define SYM_LCBR LSFT(KC_LBRC)
#define SYM_RCBR LSFT(KC_RBRC)
#define SYM_LPRN LSFT(KC_9)
#define SYM_RPRN LSFT(KC_0)
#define SYM_SCLN KC_SCLN
#define SYM_CLN LSFT(KC_SCLN)
#define SYM_GRV KC_GRV
#define SYM_QUOT KC_QUOT
#define SYM_DQUO LSFT(KC_QUOT)
#define SYM_EXCL LSFT(KC_1)
#define SYM_EQL KC_EQL
#define SYM_MUL_NUM LSFT(KC_8)
#define SYM_PLUS_NUM LSFT(KC_EQL)

// PC Navigation
#define NAP_UNDO C(KC_Z)
#define NAP_CUT C(KC_X)
#define NAP_COPY C(KC_C)
#define NAP_PASTE C(KC_V)
#define NAP_REDO C(S(KC_Z))
#define NAP_QUICKOPEN C(KC_P)
#define NAP_GOTOLINE C(KC_G)
#define NAP_BACK C(KC_MINS)
#define NAP_FORWARD C(S(KC_MINS))
#define NAP_SYMBOLS C(S(KC_O))
#define NAP_CMDPALETTE C(S(KC_P))
#define NAP_SELECTALL C(KC_A)
#define NAP_SAVE C(KC_S)

// Mac Navigation
#define NAM_UNDO G(KC_Z)
#define NAM_CUT G(KC_X)
#define NAM_COPY G(KC_C)
#define NAM_PASTE G(KC_V)
#define NAM_REDO G(S(KC_Z))
#define NAM_QUICKOPEN G(KC_P)
#define NAM_GOTOLINE C(KC_G)
#define NAM_BACK C(KC_MINS)
#define NAM_FORWARD C(S(KC_MINS))
#define NAM_SYMBOLS G(S(KC_O))
#define NAM_CMDPALETTE G(S(KC_P))
#define NAM_SELECTALL G(KC_A)
#define NAM_SAVE G(KC_S)

// PC Shortcuts
#define SCP_OS_SCREENSHOOT KC_PSCR
#define SCP_VSC_LINE_COMMENT C(KC_SLSH)
#define SCP_VSC_REPLACE_ALL C(S(KC_H))
#define SCP_VSC_FIND_ALL C(S(KC_F))
#define SCP_VSC_ZOOM_IN C(S(KC_EQL))
#define SCP_OS_SCREEN_REGION LGUI(S(KC_S))
#define SCP_VSC_FORMAT_DOCUMENT LSA(KC_F)
#define SCP_VSC_REPLACE C(KC_H)
#define SCP_VSC_FIND C(KC_F)
#define SCP_VSC_ZOOM_OUT C(KC_MINS)
#define SCP_OS_SCREEN_RECORD LGUI(A(KC_R))
#define SCP_VSC_GO_TO_DEFINITION KC_F12
#define SCP_VSC_GOTO_IMPLEMENTATION C(KC_F12)
#define SCP_VSC_QUICKFIX C(KC_DOT)
#define SCP_VSC_CLOSE_TAB C(KC_W)

// Mac Shortcuts
#define SCM_OS_SCREENSHOOT G(S(KC_3))
#define SCM_VSC_LINE_COMMENT G(KC_SLSH)
#define SCM_VSC_REPLACE_ALL G(S(KC_H))
#define SCM_VSC_FIND_ALL G(S(KC_F))
#define SCM_VSC_ZOOM_IN G(S(KC_EQL))
#define SCM_OS_SCREEN_REGION G(S(KC_4))
#define SCM_VSC_FORMAT_DOCUMENT S(A(KC_F))
#define SCM_VSC_REPLACE G(A(KC_F))
#define SCM_VSC_FIND G(KC_F)
#define SCM_VSC_ZOOM_OUT G(KC_MINS)
#define SCM_OS_SCREEN_RECORD G(S(KC_5))
#define SCM_VSC_GO_TO_DEFINITION KC_F12
#define SCM_VSC_GOTO_IMPLEMENTATION G(KC_F12)
#define SCM_VSC_QUICKFIX G(KC_DOT)
#define SCM_VSC_CLOSE_TAB G(KC_W)

#define LAYOUT_split_3x5_3_mirrored( \
    k00, k01, k02, k03, k04, \
    k10, k11, k12, k13, k14, \
    k20, k21, k22, k23, k24, \
    t0, t1, t2, t3, t4, t5 \
) \
LAYOUT_split_3x5_3( \
    k00, k01, k02, k03, k04,    k04, k03, k02, k01, k00, \
    k10, k11, k12, k13, k14,    k14, k13, k12, k11, k10, \
    k20, k21, k22, k23, k24,    k24, k23, k22, k21, k20, \
    t0, t1, t2,    t3, t4, t5 \
)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_COLEMAK_PC] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_F, KC_P, KC_B,                  KC_J, KC_L, KC_U,    KC_Y,   KC_QUOT,
        HR_A, HR_R, HR_S, HR_T, KC_G,                  KC_M, HR_N, HR_E,    HR_I,   HR_O,
        KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT, KC_SLSH,
                 TH_ESC_PC, TH_SPC, TH_TAB_PC,    TH_ENT, TH_BSPC, TH_DEL
    ),
    [_COLEMAK_MAC] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_F, KC_P, KC_B,                  KC_J, KC_L, KC_U,    KC_Y,    KC_QUOT,
        HR_A, HR_R, HR_S, HR_T, KC_G,                  KC_M, HR_N, HR_E,    HR_I,    HR_O,
        KC_Z, KC_X, KC_C, KC_D, KC_V,                  KC_K, KC_H, KC_COMM, KC_DOT,  KC_SLSH,
              TH_ESC_MAC,  TH_SPC, TH_TAB_MAC,    TH_ENT, TH_BSPC, TH_DEL
    ),
    [_QWERTY_GAMING] = LAYOUT_split_3x5_3(
        KC_Q, KC_W, KC_E, KC_R, KC_T,                 KC_Y, KC_U, KC_I,    KC_O,   KC_P,
        KC_A, KC_S, KC_D, KC_F, KC_G,                 KC_H, KC_J, KC_K,    KC_L,   KC_SCLN,
        KC_Z, KC_X, KC_C, KC_V, KC_B,                 KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH,
                    KC_ESC, KC_SPC, KC_TAB,     TH_ENT, KC_BSPC, TH_DEL
    ),
    [_NAVIGATION_PC] = LAYOUT_split_3x5_3(
        NAP_UNDO,     NAP_CUT,  NAP_COPY,    NAP_PASTE,   NAP_REDO,                        NAP_REDO,        NAP_PASTE,   NAP_COPY,    NAP_CUT,  NAP_UNDO,
        KC_LEFT,      KC_DOWN,  KC_UP,       KC_RIGHT,    NAP_QUICKOPEN,                   NAP_QUICKOPEN,   KC_LEFT,     KC_DOWN,     KC_UP,    KC_RIGHT,
        NAP_GOTOLINE, NAP_BACK, NAP_FORWARD, NAP_SYMBOLS, NAP_CMDPALETTE,                  NAP_CMDPALETTE,  NAP_SYMBOLS, NAP_FORWARD, NAP_BACK, NAP_GOTOLINE,
                                                NAP_SELECTALL, NAP_SAVE, KC_NO,       KC_NO, KC_BSPC, KC_DEL
    ),
    [_NAVIGATION_MAC] = LAYOUT_split_3x5_3(
        NAM_UNDO,     NAM_CUT,  NAM_COPY,    NAM_PASTE,   NAM_REDO,                      NAM_REDO,       NAM_PASTE,   NAM_COPY,    NAM_CUT,  NAM_UNDO,
        KC_LEFT,      KC_DOWN,  KC_UP,       KC_RIGHT,    NAM_QUICKOPEN,                 NAM_QUICKOPEN,  KC_LEFT,     KC_DOWN,     KC_UP,    KC_RIGHT,
        NAM_GOTOLINE, NAM_BACK, NAM_FORWARD, NAM_SYMBOLS, NAM_CMDPALETTE,                NAM_CMDPALETTE, NAM_SYMBOLS, NAM_FORWARD, NAM_BACK, NAM_GOTOLINE,
                                                NAM_SELECTALL, NAM_SAVE, KC_NO,     KC_NO, KC_BSPC, KC_DEL
    ),
    [_BRACKETS] = LAYOUT_split_3x5_3(
        SYM_LBRC, SYM_RBRC, SYM_LABR, SYM_RABR, SYM_CLN,                    SYM_CLN,  SYM_LABR, SYM_RABR,  SYM_LBRC, SYM_RBRC,
        SYM_LCBR, SYM_RCBR, SYM_LPRN, SYM_RPRN, SYM_SCLN,                   SYM_SCLN, SYM_LPRN, SYM_RPRN,  SYM_LCBR, SYM_RCBR,
        SYM_GRV,  SYM_QUOT, SYM_DQUO, SYM_EXCL, SYM_EQL,                    SYM_EQL,  SYM_EXCL, SYM_DQUO,  SYM_QUOT, SYM_GRV,
                                           KC_NO, KC_NO, KC_NO,        KC_NO, KC_BSPC, KC_DEL
    ),
    [_NUMBERS] = LAYOUT_split_3x5_3_mirrored(
        SYM_MUL_NUM, KC_9, KC_8, KC_7, SYM_PLUS_NUM,
        KC_SLSH,     KC_6, KC_5, KC_4, KC_MINS,
        KC_0,        KC_3, KC_2, KC_1, KC_EQL,
                              KC_COMM, KC_DOT, KC_ENT,           KC_NO, KC_DOT, KC_COMM
    ),
    [_FUNCTION] = LAYOUT_split_3x5_3_mirrored(
        DF(_COLEMAK_PC),    KC_F9, KC_F8, KC_F7, KC_F10,
        DF(_COLEMAK_MAC),   KC_F6, KC_F5, KC_F4, KC_F11,
        DF(_QWERTY_GAMING), KC_F3, KC_F2, KC_F1, KC_F12,
                                          KC_NO, KC_NO, KC_NO,     KC_NO, KC_NO, KC_NO
    ),
    [_SYMBOLS] = LAYOUT_split_3x5_3_mirrored(
        SYM_AT,   SYM_DLR,  SYM_HASH,  SYM_PERC, SYM_ASTR,
        SYM_AMPR, SYM_PIPE, SYM_CARET, SYM_BSLS, SYM_SLSH,
        SYM_TILD, SYM_PLUS, SYM_MINS,  SYM_UNDS, SYM_QUES,
                                           KC_NO, KC_NO, KC_NO,        KC_NO, KC_NO, KC_NO
    ),
    [_SHORTCUTS_PC] = LAYOUT_split_3x5_3_mirrored(
        SCP_OS_SCREENSHOOT,   SCP_VSC_LINE_COMMENT,     SCP_VSC_REPLACE_ALL,         SCP_VSC_FIND_ALL, SCP_VSC_ZOOM_IN,
        SCP_OS_SCREEN_REGION, SCP_VSC_FORMAT_DOCUMENT,  SCP_VSC_REPLACE,             SCP_VSC_FIND,     SCP_VSC_ZOOM_OUT,
        SCP_OS_SCREEN_RECORD, SCP_VSC_GO_TO_DEFINITION, SCP_VSC_GOTO_IMPLEMENTATION, SCP_VSC_QUICKFIX, SCP_VSC_CLOSE_TAB,
        KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [_SHORTCUTS_MAC] = LAYOUT_split_3x5_3_mirrored(
        SCM_OS_SCREENSHOOT,   SCM_VSC_LINE_COMMENT,     SCM_VSC_REPLACE_ALL,         SCM_VSC_FIND_ALL, SCM_VSC_ZOOM_IN,
        SCM_OS_SCREEN_REGION, SCM_VSC_FORMAT_DOCUMENT,  SCM_VSC_REPLACE,             SCM_VSC_FIND,     SCM_VSC_ZOOM_OUT,
        SCM_OS_SCREEN_RECORD, SCM_VSC_GO_TO_DEFINITION, SCM_VSC_GOTO_IMPLEMENTATION, SCM_VSC_QUICKFIX, SCM_VSC_CLOSE_TAB,
        KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS, KC_TRNS, KC_TRNS
    ),
};


// Define colors for layers
#define BASE_COLEMAK_PC_COLOR (RGB){0, 0, 50}          // Dim blue
#define BASE_COLEMAK_MAC_COLOR (RGB){50, 50, 50}       // Dim white
#define BASE_QWERTY_GAMING_COLOR (RGB){50, 0, 0}       // Dim red
#define BASE_DEFAULT_COLOR (RGB){50, 25, 0}            // Dim orange for base layer non-thumb keys
#define NUMBERS_LAYER_COLOR (RGB){255, 128, 0}         // Orange
#define FUNCTION_LAYER_COLOR (RGB){50, 50, 0}          // Dim yellow
#define SYMBOLS_LAYER_COLOR (RGB){0, 50, 0}            // Dim green
#define BRACKETS_LAYER_COLOR (RGB){0, 50, 50}          // Dim cyan
#define NAVIGATION_LAYER_COLOR (RGB){50, 0, 50}        // Dim magenta
#define SHORTCUTS_LAYER_COLOR (RGB){25, 0, 50}         // Dim purple
#define MODIFIER_COLOR (RGB){80, 0, 0}                 // Slightly brighter red for visibility

// LED indices for thumb keys
const uint8_t thumb_keys[] = {15, 16, 17, 18, 19, 20};

// LED indices for home row modifier keys (based on HR_A, HR_R, HR_S, HR_T on left, HR_N, HR_E, HR_I, HR_O on right)
const uint8_t gui_keys[] = {9, 26};
const uint8_t alt_keys[] = {8, 27};
const uint8_t ctrl_keys[] = {7, 28};
const uint8_t shift_keys[] = {6, 29};

// LED indices for function layer base layer switch keys
const uint8_t fn_pc_key[] = {0, 35};
const uint8_t fn_mac_key[] = {9, 26};
const uint8_t fn_gaming_key[] = {10, 25};

// Helper function to set a uniform color
void set_color(RGB rgb) {
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

// Set color for a specific set of keys
void set_keys_color(const uint8_t* keys, uint8_t num_keys, RGB rgb) {
    for (uint8_t i = 0; i < num_keys; i++) {
        rgb_matrix_set_color(keys[i], rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_user(void) {
    RGB base_color;
    uint8_t current_base_layer = get_highest_layer(default_layer_state);

    // Determine base layer color (for thumb keys)
    switch (current_base_layer) {
        case _COLEMAK_MAC:
            base_color = BASE_COLEMAK_MAC_COLOR;
            break;
        case _QWERTY_GAMING:
            base_color = BASE_QWERTY_GAMING_COLOR;
            break;
        case _COLEMAK_PC:
        default:
            base_color = BASE_COLEMAK_PC_COLOR;
            break;
    }

    uint8_t current_layer = get_highest_layer(layer_state);
    RGB layer_color;

    switch (current_layer) {
        case _NUMBERS:
            layer_color = NUMBERS_LAYER_COLOR;
            break;
        case _FUNCTION:
            layer_color = FUNCTION_LAYER_COLOR;
            break;
        case _SYMBOLS:
            layer_color = SYMBOLS_LAYER_COLOR;
            break;
        case _BRACKETS:
            layer_color = BRACKETS_LAYER_COLOR;
            break;
        case _NAVIGATION_PC:
        case _NAVIGATION_MAC:
            layer_color = NAVIGATION_LAYER_COLOR;
            break;
        case _SHORTCUTS_PC:
        case _SHORTCUTS_MAC:
            layer_color = SHORTCUTS_LAYER_COLOR;
            break;
        default:
            layer_color = BASE_DEFAULT_COLOR;
            break;
    }

    // Set layer color for all keys
    set_color(layer_color);

    // Always set thumb keys to base layer color
    set_keys_color(thumb_keys, ARRAY_SIZE(thumb_keys), base_color);

    // light up base layer switch keys
    if (current_layer == _FUNCTION) {
        set_keys_color(fn_pc_key, ARRAY_SIZE(fn_pc_key), BASE_COLEMAK_PC_COLOR);
        set_keys_color(fn_mac_key, ARRAY_SIZE(fn_mac_key), BASE_COLEMAK_MAC_COLOR);
        set_keys_color(fn_gaming_key, ARRAY_SIZE(fn_gaming_key), BASE_QWERTY_GAMING_COLOR);
    }

    // Check for modifiers and light up specific modifier keys
    uint8_t mods = get_mods();
    if (mods & MOD_MASK_SHIFT) {
        set_keys_color(shift_keys, ARRAY_SIZE(shift_keys), MODIFIER_COLOR);
    }
    if (mods & MOD_MASK_CTRL) {
        set_keys_color(ctrl_keys, ARRAY_SIZE(ctrl_keys), MODIFIER_COLOR);
    }
    if (mods & MOD_MASK_ALT) {
        set_keys_color(alt_keys, ARRAY_SIZE(alt_keys), MODIFIER_COLOR);
    }
    if (mods & MOD_MASK_GUI) {
        set_keys_color(gui_keys, ARRAY_SIZE(gui_keys), MODIFIER_COLOR);
    }
    
    return false;
}

void keyboard_post_init_user(void) {
    // Set initial RGB mode to solid color and color to blue (PC default)
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_flags(LED_FLAG_ALL);
    rgb_matrix_indicators_user();
}

// Process key presses to update RGB instantly on modifier and layer changes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        // Home row mods
        case HR_A:
        case HR_R:
        case HR_S:
        case HR_T:
        case HR_N:
        case HR_E:
        case HR_I:
        case HR_O:
        // Layer tap keys
        case TH_ESC_PC:
        case TH_ESC_MAC:
        case TH_SPC:
        case TH_TAB_PC:
        case TH_TAB_MAC:
        case TH_ENT:
        case TH_BSPC:
        case TH_DEL:
            rgb_matrix_indicators_user();
            break;
    }
    return true;
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
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        default:
            // Switch to PC layer
            default_layer_set(1UL << _COLEMAK_PC);
            break;
    }
    rgb_matrix_indicators_user();
    return true;
}

// Function to handle manual layer changes (for gaming mode)
layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_indicators_user();
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgb_matrix_indicators_user();
    return state;
}

// Enable permissive hold for shift and thumb cluster 
bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HR_T:
        case HR_N:
        case TH_ESC_PC:
        case TH_ESC_MAC:
        case TH_SPC:
        case TH_TAB_PC:
        case TH_TAB_MAC:
        case TH_ENT:
        case TH_BSPC:
        case TH_DEL:
            return true;
        default:
            return false;
    }
}

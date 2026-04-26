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
    _SYMBOLS,
    _BRACKETS_PC,
    _BRACKETS_MAC,
    _NUMBERS,
    _NAVIGATION_PC,
    _NAVIGATION_MAC,
    _SHORTCUTS_PC,
    _SHORTCUTS_MAC,
    _TMUX,
    _FUNCTION,
};

// Custom keycodes for multi-key macros
enum custom_keycodes {
    CK_PC_DLLS = SAFE_RANGE, // Delete to line start (Shift+Home, Backspace)
    CK_PC_DLLE,              // Delete to line end (Shift+End, Delete)
    TM_WN1,
    TM_WN2,
    TM_WN3,
    TM_WN4,
    TM_WN5,
    TM_WN6,
    TM_WN7,
    TM_WN8,
    TM_WN9,
    TM_WN0,
    TM_NEW,
    TM_PREV,
    TM_NEXT,
    TM_LAST,
    TM_TREE,
    TM_LEFT,
    TM_DOWN,
    TM_UP,
    TM_RGHT,
    TM_SPLH,
    TM_SPLV,
    TM_ZOOM,
    TM_KILL,
    TM_RENM,
    TM_DET,
    TM_RLFT,
    TM_RDWN,
    TM_RUP,
    TM_RRGT,
};

// Layer-tap: PC
#define TH_ESC_PC LT(_SHORTCUTS_PC, KC_ESC)
#define TH_SPC_PC LT(_BRACKETS_PC, KC_SPC)
#define TH_TAB_PC LT(_NAVIGATION_PC, KC_TAB)

// Layer-tap: Mac
#define TH_ESC_MAC LT(_SHORTCUTS_MAC, KC_ESC)
#define TH_SPC_MAC LT(_BRACKETS_MAC, KC_SPC)
#define TH_TAB_MAC LT(_NAVIGATION_MAC, KC_TAB)

// Layer-tap: shared
#define TH_ENT LT(_NUMBERS, KC_ENT)
#define TH_BSPC LT(_SYMBOLS, KC_BSPC)
#define TH_DEL LT(_FUNCTION, KC_DEL)

// Layer-tap: tmux, positioned on the inner top-row index keys
#define TMUX_L LT(_TMUX, KC_B)
#define TMUX_R LT(_TMUX, KC_J)

// Home row mods
#define HR_A LGUI_T(KC_A)
#define HR_R LALT_T(KC_R)
#define HR_S LCTL_T(KC_S)
#define HR_T LSFT_T(KC_T)
#define HR_N RSFT_T(KC_N)
#define HR_E RCTL_T(KC_E)
#define HR_I RALT_T(KC_I)
#define HR_O RGUI_T(KC_O)

// Symbols
#define YM_AT LSFT(KC_2)
#define YM_DLR LSFT(KC_4)
#define YM_HASH LSFT(KC_3)
#define YM_PERC LSFT(KC_5)
#define YM_ASTR LSFT(KC_8)
#define YM_AMPR LSFT(KC_7)
#define YM_PIPE LSFT(KC_BSLS)
#define YM_CRET LSFT(KC_6)
#define YM_BSLS KC_BSLS
#define YM_SLSH KC_SLSH
#define YM_TILD LSFT(KC_GRV)
#define YM_PLUS LSFT(KC_EQL)
#define YM_MINS KC_MINS
#define YM_UNDS LSFT(KC_MINS)
#define YM_QUES LSFT(KC_SLSH)
#define YM_LBRC KC_LBRC
#define YM_RBRC KC_RBRC
#define YM_LABR LSFT(KC_COMM)
#define YM_RABR LSFT(KC_DOT)
#define YM_LCBR LSFT(KC_LBRC)
#define YM_RCBR LSFT(KC_RBRC)
#define YM_LPRN LSFT(KC_9)
#define YM_RPRN LSFT(KC_0)
#define YM_SCLN KC_SCLN
#define YM_CLN LSFT(KC_SCLN)
#define YM_GRV KC_GRV
#define YM_QUOT KC_QUOT
#define YM_DQUO LSFT(KC_QUOT)
#define YM_EXCL LSFT(KC_1)
#define YM_EQL KC_EQL

// PC Navigation
#define NP_UNDO C(KC_Z)
#define NP_CUT C(KC_X)
#define NP_COPY C(KC_C)
#define NP_PSTE C(KC_V)
#define NP_REDO C(S(KC_Z))
#define NP_GOBK A(KC_LEFT)
#define NP_WDLT C(KC_LEFT)
#define NP_WDRT C(KC_RIGHT)
#define NP_GTBR C(S(KC_BSLS))
#define NP_PRNT C(KC_P)
#define NP_GTLN C(KC_G)
#define NP_NVBK C(KC_MINS)
#define NP_NVFW C(KC_EQL)
#define NP_SWFL C(S(KC_O))
#define NP_CMDP C(S(KC_P))
#define NP_SELA C(KC_A)
#define NP_SAVE C(KC_S)
#define NP_DLWD C(KC_BSPC)
#define NP_DLFW C(KC_DEL)

// Mac Navigation
#define NM_UNDO G(KC_Z)
#define NM_CUT G(KC_X)
#define NM_COPY G(KC_C)
#define NM_PSTE G(KC_V)
#define NM_REDO G(S(KC_Z))
#define NM_GOBK C(KC_MINS)
#define NM_WDLT A(KC_LEFT)
#define NM_WDRT A(KC_RIGHT)
#define NM_GTBR G(S(KC_BSLS))
#define NM_PRNT G(KC_P)
#define NM_GTLN C(KC_G)
#define NM_NVBK G(KC_MINS)
#define NM_NVFW G(KC_EQL)
#define NM_SWFL G(S(KC_O))
#define NM_CMDP G(S(KC_P))
#define NM_SELA G(KC_A)
#define NM_SAVE G(KC_S)
#define NM_DLWD A(KC_BSPC)
#define NM_DLFW A(KC_DEL)
#define NM_DLLS G(KC_BSPC)
#define NM_DLLE C(KC_K)

// PC Shortcuts
#define SP_SCRN KC_PSCR
#define SP_LCMT C(KC_SLSH)
#define SP_RPLA C(S(KC_H))
#define SP_FNDA C(S(KC_F))
#define SP_ZMIN C(S(KC_EQL))
#define SP_SREG LGUI(S(KC_S))
#define SP_FMTD LSA(KC_F)
#define SP_RPLC C(KC_H)
#define SP_FIND C(KC_F)
#define SP_ZMOT C(KC_MINS)
#define SP_SREC LGUI(A(KC_R))
#define SP_GDEF KC_F12
#define SP_IMPL C(KC_F12)
#define SP_QFIX C(KC_DOT)
#define SP_CTAB C(KC_W)

// Mac Shortcuts
#define SM_SCRN G(S(KC_3))
#define SM_LCMT G(KC_SLSH)
#define SM_RPLA G(S(KC_H))
#define SM_FNDA G(S(KC_F))
#define SM_ZMIN G(S(KC_EQL))
#define SM_SREG G(S(KC_4))
#define SM_FMTD S(A(KC_F))
#define SM_RPLC G(A(KC_F))
#define SM_FIND G(KC_F)
#define SM_ZMOT G(KC_MINS)
#define SM_SREC G(S(KC_5))
#define SM_GDEF KC_F12
#define SM_IMPL G(KC_F12)
#define SM_QFIX G(KC_DOT)
#define SM_CTAB G(KC_W)

#define TMUX_FIRST TM_WN1
#define TMUX_LAST TM_RRGT

static const uint16_t tmux_command_keys[] = {
    KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0,
    KC_C, KC_P, KC_N, KC_L, KC_W,
    KC_LEFT, KC_DOWN, KC_UP, KC_RIGHT,
    KC_H, KC_V, KC_Z, KC_X, KC_COMM, KC_D,
    S(KC_H), S(KC_J), S(KC_K), S(KC_L),
};

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
        KC_Q,  KC_W,  KC_F,       KC_P,       TMUX_L,         TMUX_R,  KC_L,     KC_U,     KC_Y,    KC_QUOT,
        HR_A,  HR_R,  HR_S,       HR_T,       KC_G,           KC_M,    HR_N,     HR_E,     HR_I,    HR_O,
        KC_Z,  KC_X,  KC_C,       KC_D,       KC_V,           KC_K,    KC_H,     KC_COMM,  KC_DOT,  KC_SLSH,
                      TH_ESC_PC,  TH_SPC_PC,  TH_TAB_PC,      TH_ENT,  TH_BSPC,  TH_DEL
    ),

    [_COLEMAK_MAC] = LAYOUT_split_3x5_3(
        KC_Q,  KC_W,  KC_F,        KC_P,        TMUX_L,          TMUX_R,  KC_L,     KC_U,     KC_Y,    KC_QUOT,
        HR_A,  HR_R,  HR_S,        HR_T,        KC_G,            KC_M,    HR_N,     HR_E,     HR_I,    HR_O,
        KC_Z,  KC_X,  KC_C,        KC_D,        KC_V,            KC_K,    KC_H,     KC_COMM,  KC_DOT,  KC_SLSH,
                      TH_ESC_MAC,  TH_SPC_MAC,  TH_TAB_MAC,      TH_ENT,  TH_BSPC,  TH_DEL
    ),

    [_QWERTY_GAMING] = LAYOUT_split_3x5_3(
        KC_Q,  KC_W,  KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,     KC_I,     KC_O,    KC_P,
        KC_A,  KC_S,  KC_D,    KC_F,    KC_G,        KC_H,    KC_J,     KC_K,     KC_L,    KC_SCLN,
        KC_Z,  KC_X,  KC_C,    KC_V,    KC_B,        KC_N,    KC_M,     KC_COMM,  KC_DOT,  KC_SLSH,
                      KC_ESC,  KC_SPC,  KC_TAB,      KC_ENT,  KC_BSPC,  KC_DEL
    ),

    [_SYMBOLS] = LAYOUT_split_3x5_3_mirrored(
        YM_AT,    YM_DLR,   YM_HASH,  YM_PERC,  YM_ASTR,
        YM_AMPR,  YM_PIPE,  YM_CRET,  YM_BSLS,  YM_SLSH,
        YM_TILD,  YM_PLUS,  YM_MINS,  YM_UNDS,  YM_QUES,
                            KC_NO,    KC_NO,    KC_NO,        KC_NO,  KC_NO,  KC_NO
    ),

    [_BRACKETS_PC] = LAYOUT_split_3x5_3(
        YM_LBRC,  YM_RBRC,  YM_LABR,  YM_RABR,  YM_CLN,       YM_CLN,   YM_LABR,  YM_RABR,  YM_LBRC,  YM_RBRC,
        YM_LCBR,  YM_RCBR,  YM_LPRN,  YM_RPRN,  YM_SCLN,      YM_SCLN,  YM_LPRN,  YM_RPRN,  YM_LCBR,  YM_RCBR,
        YM_GRV,   YM_QUOT,  YM_DQUO,  YM_EXCL,  YM_EQL,       YM_EQL,   YM_EXCL,  YM_DQUO,  YM_QUOT,  YM_GRV,
                            KC_NO,    KC_NO,    KC_NO,        KC_NO,    NP_DLWD,  NP_DLFW
    ),

    [_BRACKETS_MAC] = LAYOUT_split_3x5_3(
        YM_LBRC,  YM_RBRC,  YM_LABR,  YM_RABR,  YM_CLN,       YM_CLN,   YM_LABR,  YM_RABR,  YM_LBRC,  YM_RBRC,
        YM_LCBR,  YM_RCBR,  YM_LPRN,  YM_RPRN,  YM_SCLN,      YM_SCLN,  YM_LPRN,  YM_RPRN,  YM_LCBR,  YM_RCBR,
        YM_GRV,   YM_QUOT,  YM_DQUO,  YM_EXCL,  YM_EQL,       YM_EQL,   YM_EXCL,  YM_DQUO,  YM_QUOT,  YM_GRV,
                            KC_NO,    KC_NO,    KC_NO,        KC_NO,    NM_DLWD,  NM_DLFW
    ),

    [_NUMBERS] = LAYOUT_split_3x5_3_mirrored(
        YM_ASTR,  KC_9,  KC_8,     KC_7,    YM_PLUS,
        KC_SLSH,  KC_6,  KC_5,     KC_4,    KC_MINS,
        KC_0,     KC_3,  KC_2,     KC_1,    KC_EQL,
                         KC_COMM,  KC_DOT,  KC_ENT,       KC_NO,  KC_DOT,  KC_COMM
    ),

    [_NAVIGATION_PC] = LAYOUT_split_3x5_3(
        NP_UNDO,  NP_CUT,   NP_COPY,  NP_PSTE,  NP_REDO,      NP_GOBK,  NP_WDLT,     NP_GTBR,     NP_GTBR,  NP_WDRT,
        KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   NP_PRNT,      NP_PRNT,  KC_LEFT,     KC_DOWN,     KC_UP,    KC_RIGHT,
        NP_GTLN,  NP_NVBK,  NP_NVFW,  NP_SWFL,  NP_CMDP,      NP_CMDP,  NP_SWFL,     NP_NVFW,     NP_NVBK,  NP_GTLN,
                            NP_SELA,  NP_SAVE,  KC_NO,        KC_NO,    CK_PC_DLLS,  CK_PC_DLLE
    ),

    [_NAVIGATION_MAC] = LAYOUT_split_3x5_3(
        NM_UNDO,  NM_CUT,   NM_COPY,  NM_PSTE,  NM_REDO,      NM_GOBK,  NM_WDLT,  NM_GTBR,  NM_GTBR,  NM_WDRT,
        KC_HOME,  KC_PGDN,  KC_PGUP,  KC_END,   NM_PRNT,      NM_PRNT,  KC_LEFT,  KC_DOWN,  KC_UP,    KC_RIGHT,
        NM_GTLN,  NM_NVBK,  NM_NVFW,  NM_SWFL,  NM_CMDP,      NM_CMDP,  NM_SWFL,  NM_NVFW,  NM_NVBK,  NM_GTLN,
                            NM_SELA,  NM_SAVE,  KC_NO,        KC_NO,    NM_DLLS,  NM_DLLE
    ),

    [_SHORTCUTS_PC] = LAYOUT_split_3x5_3_mirrored(
        SP_SCRN,  SP_LCMT,  SP_RPLA,  SP_FNDA,  SP_ZMIN,
        SP_SREG,  SP_FMTD,  SP_RPLC,  SP_FIND,  SP_ZMOT,
        SP_SREC,  SP_GDEF,  SP_IMPL,  SP_QFIX,  SP_CTAB,
                            KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    [_SHORTCUTS_MAC] = LAYOUT_split_3x5_3_mirrored(
        SM_SCRN,  SM_LCMT,  SM_RPLA,  SM_FNDA,  SM_ZMIN,
        SM_SREG,  SM_FMTD,  SM_RPLC,  SM_FIND,  SM_ZMOT,
        SM_SREC,  SM_GDEF,  SM_IMPL,  SM_QFIX,  SM_CTAB,
                            KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    [_TMUX] = LAYOUT_split_3x5_3(
        TM_WN1,   TM_WN2,   TM_WN3,   TM_WN4,   TM_WN5,       TM_WN6,   TM_WN7,   TM_WN8,   TM_WN9,  TM_WN0,
        TM_NEW,   TM_PREV,  TM_NEXT,  TM_LAST,  TM_TREE,      TM_TREE,  TM_LEFT,  TM_DOWN,  TM_UP,   TM_RGHT,
        TM_SPLH,  TM_SPLV,  TM_ZOOM,  TM_KILL,  TM_RENM,      TM_DET,   TM_RLFT,  TM_RDWN,  TM_RUP,  TM_RRGT,
                            KC_TRNS,  KC_TRNS,  KC_TRNS,      KC_TRNS,  KC_TRNS,  KC_TRNS
    ),

    [_FUNCTION] = LAYOUT_split_3x5_3_mirrored(
        DF(_COLEMAK_PC),     KC_F9,  KC_F8,  KC_F7,  KC_F10,
        DF(_COLEMAK_MAC),    KC_F6,  KC_F5,  KC_F4,  KC_F11,
        DF(_QWERTY_GAMING),  KC_F3,  KC_F2,  KC_F1,  KC_F12,
                                     KC_NO,  KC_NO,  KC_NO,       KC_NO,  KC_NO,  KC_NO
    ),
};

// Define colors for layers
#define BASE_COLEMAK_PC_COLOR (RGB){0, 0, 50}
#define BASE_COLEMAK_MAC_COLOR (RGB){50, 50, 50}
#define BASE_QWERTY_GAMING_COLOR (RGB){50, 0, 0}
#define NUMBERS_LAYER_COLOR (RGB){255, 128, 0}
#define FUNCTION_LAYER_COLOR (RGB){50, 50, 0}
#define SYMBOLS_LAYER_COLOR (RGB){0, 50, 0}
#define BRACKETS_LAYER_COLOR (RGB){0, 50, 50}
#define NAVIGATION_LAYER_COLOR (RGB){50, 0, 50}
#define SHORTCUTS_LAYER_COLOR (RGB){25, 0, 50}
#define TMUX_LAYER_COLOR (RGB){80, 45, 0}
#define MODIFIER_COLOR (RGB){80, 0, 0}

// LED indices for thumb keys
const uint8_t thumb_keys[] = {15, 16, 17, 18, 19, 20};

// LED indices for home row modifier keys
const uint8_t gui_keys[] = {9, 26};
const uint8_t alt_keys[] = {8, 27};
const uint8_t ctrl_keys[] = {7, 28};
const uint8_t shift_keys[] = {6, 29};

// LED indices for function layer base layer switch keys
const uint8_t fn_pc_key[] = {0, 35};
const uint8_t fn_mac_key[] = {9, 26};
const uint8_t fn_gaming_key[] = {10, 25};

void set_color(RGB rgb) {
    rgb_matrix_set_color_all(rgb.r, rgb.g, rgb.b);
}

void set_keys_color(const uint8_t* keys, uint8_t num_keys, RGB rgb) {
    for (uint8_t i = 0; i < num_keys; i++) {
        rgb_matrix_set_color(keys[i], rgb.r, rgb.g, rgb.b);
    }
}

bool rgb_matrix_indicators_user(void) {
    RGB base_color;
    uint8_t current_base_layer = get_highest_layer(default_layer_state);

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
        case _BRACKETS_PC:
        case _BRACKETS_MAC:
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
        case _TMUX:
            layer_color = TMUX_LAYER_COLOR;
            break;
        default:
            layer_color = base_color;
            break;
    }

    set_color(layer_color);
    set_keys_color(thumb_keys, ARRAY_SIZE(thumb_keys), base_color);

    if (current_layer == _FUNCTION) {
        set_keys_color(fn_pc_key, ARRAY_SIZE(fn_pc_key), BASE_COLEMAK_PC_COLOR);
        set_keys_color(fn_mac_key, ARRAY_SIZE(fn_mac_key), BASE_COLEMAK_MAC_COLOR);
        set_keys_color(fn_gaming_key, ARRAY_SIZE(fn_gaming_key), BASE_QWERTY_GAMING_COLOR);
    }

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
    rgb_matrix_enable();
    rgb_matrix_mode(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_set_flags(LED_FLAG_ALL);
    rgb_matrix_indicators_user();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode >= TMUX_FIRST && keycode <= TMUX_LAST) {
        if (record->event.pressed) {
            tap_code16(C(KC_A));
            tap_code16(tmux_command_keys[keycode - TMUX_FIRST]);
        }
        return false;
    }

    switch (keycode) {
        // Multi-key macros
        case CK_PC_DLLS:
            if (record->event.pressed) {
                tap_code16(S(KC_HOME));
                tap_code(KC_BSPC);
            }
            return false;
        case CK_PC_DLLE:
            if (record->event.pressed) {
                tap_code16(S(KC_END));
                tap_code(KC_DEL);
            }
            return false;
        // RGB update triggers
        case HR_A:
        case HR_R:
        case HR_S:
        case HR_T:
        case HR_N:
        case HR_E:
        case HR_I:
        case HR_O:
        case TH_ESC_PC:
        case TH_ESC_MAC:
        case TH_SPC_PC:
        case TH_SPC_MAC:
        case TH_TAB_PC:
        case TH_TAB_MAC:
        case TH_ENT:
        case TH_BSPC:
        case TH_DEL:
        case TMUX_L:
        case TMUX_R:
            rgb_matrix_indicators_user();
            break;
    }
    return true;
}

bool process_detected_host_os_kb(os_variant_t detected_os) {
    if (!process_detected_host_os_user(detected_os)) {
        return false;
    }

    switch (detected_os) {
        case OS_MACOS:
        case OS_IOS:
            default_layer_set(1UL << _COLEMAK_MAC);
            break;
        case OS_WINDOWS:
        case OS_LINUX:
        default:
            default_layer_set(1UL << _COLEMAK_PC);
            break;
    }
    rgb_matrix_indicators_user();
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    rgb_matrix_indicators_user();
    return state;
}

layer_state_t default_layer_state_set_user(layer_state_t state) {
    rgb_matrix_indicators_user();
    return state;
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case HR_T:
        case HR_N:
        case TH_ESC_PC:
        case TH_ESC_MAC:
        case TH_SPC_PC:
        case TH_SPC_MAC:
        case TH_TAB_PC:
        case TH_TAB_MAC:
        case TH_ENT:
        case TH_BSPC:
        case TH_DEL:
        case TMUX_L:
        case TMUX_R:
            return true;
        default:
            return false;
    }
}

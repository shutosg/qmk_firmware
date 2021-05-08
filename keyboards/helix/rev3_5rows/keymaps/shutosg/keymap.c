/* Copyright 2020 yushakobo
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


// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _BASE = 0,
  _SUB,
  _FUNC,
  _ADJUST
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  SLEEP = SAFE_RANGE,
  RGBRST
};

#define LOWER FN_MO13
#define RAISE FN_MO23

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Bksp |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Tab  |   Q  |   W  |   E  |   R  |   T  |             |   Y  |   U  |   I  |   O  |   P  |   -  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * | Ctrl |   A  |   S  |   D  |   F  |   G  |             |   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Shift|   Z  |   X  |   C  |   V  |   B  |      |   =  |   N  |   M  |   ,  |   .  |   /  |Enter |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | Esc. |Adjust| SUB  | Alt  | GUI  | Func |Space |Space |   [  |   ]  | Left | Down |  Up  |Right |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_BASE] = LAYOUT( \
    KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7, KC_8, KC_9, KC_0, KC_BSPC, \
    KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I, KC_O, KC_P, KC_MINUS, \
    KC_LCTL, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K, KC_L, KC_SCLN, KC_QUOT, \
    KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_NO, KC_EQUAL, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH, KC_ENT, \
    KC_ESC, MO(_ADJUST), MO(_SUB), KC_LALT, KC_LGUI, MO(_FUNC), KC_SPC, KC_SPC, KC_LBRC, KC_RBRC, KC_LEFT, KC_DOWN, KC_UP, KC_RGHT \
    ),
    /* Sub
     * ,-----------------------------------------.             ,-----------------------------------------.
     * | Esc. |      |      |      |      |      |             |      |      |      |      |      |  Del |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |  F7  |  F8  |  F9  | F10  | F11  | F12  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |      |   -  |   =  |   \  |  '   |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |      |      |      |      |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_SUB] = LAYOUT( \
    KC_ESC, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, \
    KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7, KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, \
    _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_MINUS, KC_EQUAL, KC_BSLS, KC_QUOT, KC_NO, \
    _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, \
    _______, KC_NO, KC_NO, _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO \
    ),

    /* Func
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |      |      |      |      |      |      |             |      |      |      |      |      | Bksp |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |   `  |   1  |   2  |   3  |   4  |   5  |             |   6  |   7  |   8  |   9  |   0  | Del  |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |             |  F6  |   -  |   =  |   [  |   ]  |  \   |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * | CAPS |  F7  |  F8  |  F9  |  F10 |  F11 |      |      |  F12 |      |      |PageDn|PageUp|      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      | Next | Vol- | Vol+ | Play |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_FUNC] = LAYOUT( \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \
    _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, \

    _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO, \
    _______, KC_NO, KC_NO, _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,  KC_NO, KC_NO \
    ),

    /* Adjust
     * ,-----------------------------------------.             ,-----------------------------------------.
     * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |             |Brigh-|Brigh+| Mute | Vol+ | Vol+ | EJCT |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      | Reset|RGBRST|      |      |      |             |      |      |      |      |      |  Del |
     * |------+------+------+------+------+------|             |------+------+------+------+------+------|
     * |      |      |      |      |      |      |             |      | EJCT |      |      |      |      |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      |RGB ON| HUE+ | SAT+ | VAL+ |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+------|
     * |      |      |      |      |      |      |      |      |      |      | MODE | HUE- | SAT- | VAL- |
     * `-------------------------------------------------------------------------------------------------'
     */
    [_ADJUST] = LAYOUT( \
        KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_BRID, KC_BRIU, KC__MUTE, KC__VOLDOWN, KC__VOLUP, KC_EJCT, \
        KC_NO, RESET, RGBRST, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_DEL, \
        _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_EJCT, KC_NO, KC_NO, KC_NO, KC_NO, \
        _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, \
        _______, KC_NO, KC_NO, _______, _______, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD\
    )

};

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* Left side encoder */
        switch (get_highest_layer(layer_state))
        {
        case _BASE:
            if (clockwise) {
                tap_code(KC_WH_U);
            } else {
                tap_code(KC_WH_D);
            }
            break;
        case _SUB:
            if (clockwise) {
                tap_code16(LCTL(KC_EQUAL));
            } else {
                tap_code16(LCTL(KC_MINUS));
            }
            break;
        default:
            break;
        }
    } else if (index == 1) { /* Right side encoder */
        if (clockwise) {
            tap_code(KC_DOWN);
        } else {
            tap_code(KC_UP);
        }
    }
}

#include "print.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RGBRST:
#ifdef RGBLIGHT_ENABLE
            if (record->event.pressed) {
               eeconfig_update_rgblight_default();
               rgblight_enable();
            }
            #endif
            break;
    }
  return true;
}

void keyboard_post_init_user(void) {
//   Customise these values to desired behaviour
//   debug_enable=true;
//   debug_matrix=true;
//   debug_keyboard=true;
}

/*
void matrix_init_user(void) {

}

void matrix_scan_user(void) {

}

bool led_update_user(led_t led_state) {
    return true;
}
*/

// void suspend_power_down_user(void) {
//     rgb_matrix_set_suspend_state(true);
// }

// void suspend_wakeup_init_user(void) {
//     rgb_matrix_set_suspend_state(false);
// }

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
    _BASE,
    _FUNC1
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    YUSHAURL = SAFE_RANGE//,
    // LIGHT_OFF
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT(
        KC_LSFT, KC_LALT, MO(_FUNC1),
        KC_HOME,   KC_UP,    KC_END,
        KC_LEFT,   KC_DOWN,  KC_RGHT
    ),
    [_FUNC1] = LAYOUT(
        RESET,   KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO,
        KC_NO, KC_NO, KC_NO
    )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case YUSHAURL:
            if (record->event.pressed) {
                // when keycode QMKURL is pressed
                SEND_STRING("https://yushakobo.jp/\n");
            } else {
                // when keycode QMKURL is released
            }
            break;
        // case LIGHT_OFF:
        //     if (record->event.pressed) {
        //         tap_code(RGB_TOG);
        //     }
        //     break;
    }
    return true;
}

void encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { // Left encoder
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    else if (index == 1) { // Right encoder
        switch (get_highest_layer(layer_state))
        {
            case _BASE:
                if (clockwise) {
                    // rgblight_decrease_hue_noeeprom();
                    tap_code(KC__VOLUP);
                } else {
                    // rgblight_increase_hue_noeeprom();
                    tap_code(KC__VOLDOWN);
                }
                break;
            case _FUNC1:
                if (clockwise) {
                    // rgblight_decrease_hue_noeeprom();
                    tap_code(KC_BRIU);
                } else {
                    // rgblight_increase_hue_noeeprom();
                    tap_code(KC_BRID);
                }
                break;
        }
    }
}

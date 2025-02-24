/* Copyright 2015-2017 Jack Humbert
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
#include "keycodes.h"
#include "keymap_russian.h"


enum layers {
    _RU,
    _EN,
    _NUMPAD_MACROS,
    _SPECIAL,
};

enum tap_dances {
    ENC_TAP
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [_RU] = LAYOUT(
        KC_ESC,   RU_SHTI,  RU_TSE,   RU_U,     RU_KA,    RU_IE,    RU_EN,    RU_GHE,   RU_SHA,   RU_SHCH,  RU_ZE,    KC_BSPC, TD(ENC_TAP),
        KC_TAB,   RU_EF,    RU_YERU,  RU_VE,    RU_A,     RU_PE,    RU_ER,    RU_O,     RU_EL,    RU_DE,    RU_ZHE,   RU_E,
        KC_LSFT,  RU_YA,    RU_CHE,   RU_ES,    RU_EM,    RU_I,     RU_TE,    RU_SOFT,  RU_BE,    RU_YU,    KC_SLSH,  KC_ENT,
        TG(1),    KC_LCTL,  KC_LALT,  KC_LGUI,  MO(2),    KC_SPC,   KC_SPC,   MO(3),    KC_LEFT,  KC_UP,    KC_DOWN,  KC_RGHT
    ),

    [_EN] = LAYOUT(
        KC_ESC,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,    KC_I,      KC_O,     KC_P,     KC_BSPC, TD(ENC_TAP),
        KC_TAB,   KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,    KC_K,      KC_L,     KC_SCLN,  KC_QUOT,
        KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,    KC_COMM,   KC_DOT,   KC_SLSH,  KC_ENT,
        TG(1),    KC_LCTL,  KC_LALT,  KC_LGUI,  MO(2),    KC_SPC,   KC_SPC,   MO(3),   KC_LEFT,   KC_UP,    KC_DOWN,  KC_RGHT
    ),

    [_NUMPAD_MACROS] = LAYOUT(
        C(G(KC_Q)), LSG(KC_3),   LSG(KC_4),   LSG(KC_4),     LSG(KC_R),  KC_NO,      KC_NO,    KC_NO,    KC_7,     KC_8,     KC_9,     RU_HA,   TD(ENC_TAP),
        KC_NO,      KC_NO,       G(KC_SLSH),  C(G(KC_SPC)),  KC_NO,      LSG(KC_G),  KC_NO,    KC_NO,    KC_4,     KC_5,     KC_6,     RU_YO,
        KC_LSFT,    G(KC_BSLS),  KC_NO,       LAG(KC_C),     LSG(KC_V),  LAG(KC_V),  KC_NO,    KC_NO,    KC_3,     KC_2,     KC_1,     RU_HARD,
        _______,    _______,     _______,     _______,       _______,    _______,    _______,  _______,  _______,  KC_0,     KC_NO,    KC_NO
    ),

    [_SPECIAL] = LAYOUT(
        KC_TILD,  KC_GRV,   KC_HASH,  KC_LCBR,  KC_RCBR,  KC_AMPR,  KC_AT,    KC_LPRN,  KC_RPRN,  KC_QUOT,  KC_DQUO,  KC_PIPE, TD(ENC_TAP),
        KC_PERC,  KC_NO  ,  KC_DLR,   KC_SCLN,  KC_NO  ,  KC_NO  ,  KC_MINS,  KC_DOT,   KC_COMM,  KC_EXLM,  KC_QUES,  KC_UNDS,
        KC_BSLS,  KC_LABK,  KC_RABK,  KC_LBRC,  KC_NO  ,  KC_NO  ,  KC_SLSH,  KC_PLUS,  KC_MINS,  KC_ASTR,  KC_EQL,   KC_NO,
        _______,  KC_CIRC,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______,  _______
    )
};


#ifdef ENCODER_MAP_ENABLE
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [_RU] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_EN] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_NUMPAD_MACROS] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU) },
    [_SPECIAL]  = { ENCODER_CCW_CW(KC_PGDN, KC_PGUP) },
};
#endif
// clang-format on

void dance_enc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        register_code(KC_MPLY);
    } else if (state->count == 2) {
        register_code(KC_MNXT);
    } else {
        register_code(KC_MPRV);
    }
}

void dance_enc_reset(tap_dance_state_t *state, void *user_data) {
    if (state->count == 1) {
        unregister_code(KC_MPLY);
    } else if (state->count == 2) {
        unregister_code(KC_MNXT);
    } else {
        unregister_code(KC_MPRV);
    }
}

// Tap Dance definitions
tap_dance_action_t tap_dance_actions[] = {
    [ENC_TAP] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_enc_finished, dance_enc_reset),
};

typedef union {
    uint32_t raw;
    struct {
        uint8_t led_level : 3;
    };
} work_louder_config_t;

work_louder_config_t work_louder_config;

static bool switched_to_english = false; // Remember current language

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (keycode == QK_KB_9) {
        preprocess_tap_dance(TD(ENC_TAP), record);
        return process_tap_dance(TD(ENC_TAP), record);
    } else if (keycode == QK_KB_10 && record->event.pressed) {
        work_louder_config.led_level ^= true;
        eeconfig_update_user(work_louder_config.raw);
        layer_state_set_kb(layer_state);
    }

    return true; // Process all keycodes normally
}

layer_state_t layer_state_set_user(layer_state_t state) {
    if (layer_state_cmp(state, _RU)) {
        tap_code16(RALT(KC_R));
        switched_to_english = false;
    } else if (layer_state_cmp(state, _EN) || layer_state_cmp(state, _SPECIAL)) {
        tap_code16(RALT(KC_E));
        switched_to_english = true;
    }
    return state;
}

void eeconfig_init_user(void) {
    work_louder_config.raw       = 0;
    work_louder_config.led_level = true;
    eeconfig_update_user(work_louder_config.raw);
}

void keyboard_post_init_user(void) {
    work_louder_config.raw = eeconfig_read_user();
}

enum via_indicator_value {
    id_wl_brightness = 1,
    id_wl_layer, // placeholder
};

void wl_config_set_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            work_louder_config.led_level = (bool)*value_data;
            layer_state_set_kb(layer_state);
            break;
            // case id_wl_layer:
            //     layer_move(*value_data);
            //     break;
    }
}

void wl_config_get_value(uint8_t *data) {
    // data = [ value_id, value_data ]
    uint8_t *value_id   = &(data[0]);
    uint8_t *value_data = &(data[1]);

    switch (*value_id) {
        case id_wl_brightness:
            *value_data = work_louder_config.led_level;
            break;
            // case id_wl_layer:
            //     *value_data = get_highest_layer(layer_state);
            //     break;
    }
}

void wl_config_save(void) {
    eeconfig_update_user(work_louder_config.raw);
}

void via_custom_value_command_kb(uint8_t *data, uint8_t length) {
    uint8_t *command_id        = &(data[0]);
    uint8_t *channel_id        = &(data[1]);
    uint8_t *value_id_and_data = &(data[2]);

    if (*channel_id == id_custom_channel) {
        switch (*command_id) {
            case id_custom_set_value: {
                wl_config_set_value(value_id_and_data);
                break;
            }
            case id_custom_get_value: {
                wl_config_get_value(value_id_and_data);
                break;
            }
            case id_custom_save: {
                wl_config_save();
                break;
            }
            default: {
                // Unhandled message.
                *command_id = id_unhandled;
                break;
            }
        }
        return;
    }
    *command_id = id_unhandled;
}

bool via_layout_2u = false;

void via_set_layout_options_kb(uint32_t value) {
    via_layout_2u = (bool)value;
}

#ifdef RGB_MATRIX_ENABLE
bool rgb_matrix_indicators_user(void) {
    if (via_layout_2u) {
        rgb_matrix_set_color(5, 0, 0, 0);
        rgb_matrix_set_color(7, 0, 0, 0);
    } else {
        rgb_matrix_set_color(6, 0, 0, 0);
    }
    return false;
}
#endif


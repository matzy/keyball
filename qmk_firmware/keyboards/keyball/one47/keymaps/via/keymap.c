/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

#include "quantum.h"

extern void keyball_scrollball_inhibitor_typing_extend(int32_t extend_time);

enum custom_keycodes {
    MY_TGAM = SAFE_RANGE,   // toggle auto mouse mode.
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_right_ball(
    KC_DEL   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                            KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_INT3  ,
    KC_TAB   , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                            KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  , S(KC_7)  ,
    MO(1)    , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_RBRC  ,      KC_NUHS,   KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  , KC_RSFT  ,
             KC_LCTL , KC_LALT ,KC_LGUI ,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),  KC_BSPC,   KC_ENT   ,                                  KC_RALT
  ),

  [1] = LAYOUT_right_ball(
    S(KC_DEL), S(KC_Q)  , S(KC_W)  , S(KC_E)  , S(KC_R)  , S(KC_T)  ,                            S(KC_Y)  , S(KC_U)  , S(KC_I)  , S(KC_O)  , S(KC_P)  ,S(KC_INT3),
    S(KC_TAB), S(KC_A)  , S(KC_S)  , S(KC_D)  , S(KC_F)  , S(KC_G)  ,                            S(KC_H)  , S(KC_J)  , S(KC_K)  , S(KC_L)  , KC_QUOT  , S(KC_2)  ,
    _______  , S(KC_Z)  , S(KC_X)  , S(KC_C)  , S(KC_V)  , S(KC_B)  ,S(KC_RBRC),      S(KC_NUHS),S(KC_N)  , S(KC_M)  ,S(KC_COMM), S(KC_DOT),S(KC_SLSH),S(KC_RSFT),
              S(KC_LCTL),S(KC_LALT),S(KC_LGUI), _______  , _______  , _______  ,    _______     , _______ ,                                 S(KC_RALT)
  ),

  [2] = LAYOUT_right_ball(
    _______  , _______  , KC_7     , KC_8     , KC_9     , _______  ,                            _______  , KC_LEFT  , KC_UP    , KC_RGHT  , _______  , _______  ,
    _______  , _______  , KC_4     , KC_5     , KC_6     ,S(KC_SCLN),                            KC_PGUP  , KC_BTN1  , KC_DOWN  , KC_BTN2  , KC_BTN3  , _______  ,
    _______  , _______  , KC_1     , KC_2     , KC_3     ,S(KC_MINS), S(KC_8)  ,      S(KC_9)  , KC_PGDN  , _______  , _______  , _______  , _______  , _______  ,
               _______  , KC_0     , KC_DOT   , _______  , _______  ,   _______  ,  KC_DEL     , _______  ,                                  _______
  ),

  [3] = LAYOUT_right_ball(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                            RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , RGB_HUI  , RGB_SAI  , RGB_VAI  , _______  , SCRL_DVI ,                            RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , _______  , _______  ,
    RGB_RMOD , RGB_HUD  , RGB_SAD  , RGB_VAD  , _______  , SCRL_DVD , QK_BOOT    ,      EE_CLR  , CPI_D1K  , CPI_D100 , CPI_I100 , CPI_I1K  , KBC_SAVE , KBC_RST  ,
               _______  , _______  , _______  , _______  , _______  ,   _______  ,  _______    , _______  ,                                  _______
  ),
};
// clang-format on

bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {

        keyball_scrollball_inhibitor_typing_extend(10);
    }

    switch (keycode) {
        case KC_LWIN:
        case KC_RWIN:
            if (record->event.pressed) {
                auto_mouse_layer_off();
            }
            break;

        case MY_TGAM: {
            static uint16_t time_on_pressed;
            static bool was_enabled;
            uint16_t const now = timer_read();

            bool const is_enable = get_auto_mouse_enable();
            if (record->event.pressed) {
                was_enabled = is_enable;
                time_on_pressed = now;
                if (is_enable) {
                    auto_mouse_layer_off();
                    set_auto_mouse_enable(false);
                }
                break;
            }
            // event.released.
            if (TIMER_DIFF_16(now, time_on_pressed) < MY_AUTO_MOUSE_TOGGLE_TIME) {
                if (was_enabled) {
                    set_auto_mouse_enable(true);
                }
                break;
            }
            set_auto_mouse_enable(!was_enabled);
            break;
        }
        default:
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    switch(get_highest_layer(remove_auto_mouse_layer(state, true))) {
        // only be able to change auto mouse mode when they are in layer 0.
        case 0:
            // set_auto_mouse_enable(true);
            keyball_set_scroll_mode(false);
            break;            
        case 3:
            keyball_set_scroll_mode(true);
            break;
        default:
            // other layers can't hold auto mouse mode.
            // avoid any trouble cause they use a keycode on high pirority layer (ex.layer 4: auto mouse layer)
            state = remove_auto_mouse_layer(state, false);
            break;
    }

    return state;
}

uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_LNG2):
        case LT(2,KC_ENT):
        case LT(3,KC_LNG1):
        case LT(3,KC_BSLS):
            return 120;  // 130;
        default:
            return TAPPING_TERM;
    }
}

void pointing_device_init_user(void) {
    // set_auto_mouse_layer(4); // only required if AUTO_MOUSE_DEFAULT_LAYER is not set to index of <mouse_layer>
    set_auto_mouse_enable(true);         // always required before the auto mouse feature will work
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

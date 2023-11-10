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

#define LCG(kc) (QK_LCTL | QK_LGUI | (kc))
#define RCG(kc) (QK_LCTL | QK_LGUI | (kc))

extern void keyball_scrollball_inhibitor_typing_extend(int32_t extend_time);

enum custom_keycodes {
    MY_TGAM = SAFE_RANGE,   // toggle auto mouse mode.
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                      KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_DEL   ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                      KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS   ,
    KC_LCTL  , KC_A     , KC_S     , KC_D     , KC_F     , KC_G     ,                                      KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  ,RALT_T(KC_QUOT),
    KC_LSFT  , KC_Z     , KC_X     , KC_C     , KC_V     , KC_B     , KC_B     ,                  KC_B   , KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,RSFT_T(KC_EQL),
    KC_LCTL  , MY_TGAM  , KC_LGUI ,LALT_T(KC_ESC),LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1), LT(1,KC_BSPC), MO(2) ,LT(1,KC_LNG2), KC_RGUI  , _______  , KC_RALT  , MO(3)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                      KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    KC_ESC   , KC_QUES  , XXXXXXX  , KC_EXLM  , KC_PERC  , KC_TILD  ,                                      KC_INT3  , KC_LPRN  , KC_RPRN  , XXXXXXX  , KC_PIPE  , KC_F12   ,
    _______  , KC_AT    , KC_SLSH  , KC_DLR   , XXXXXXX  , KC_GRV   ,                                      KC_HASH  , KC_LCBR  , KC_RCBR  , KC_LBRC  , KC_RBRC  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_CIRC  , XXXXXXX  , KC_BSLS  , KC_LNG3  ,                 KC_LNG4 , KC_AMPR  , KC_ASTR  , KC_LABK  , KC_RABK  , XXXXXXX  , _______  ,
    _______  , _______  , _______  , _______  , KC_BSPC  , _______  , KC_DEL   ,                 KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

#if 0
  [2] = LAYOUT_universal(
    _______  , LSG(KC_1), LSG(KC_2), LSG(KC_5), XXXXXXX  , KC_SLSH  ,                                      KC_CAPS  , KC_PSCR  , KC_SCRL  , KC_PAUS  , XXXXXXX  , KC_INS   ,
    _______  , KC_COMM  , KC_7     , KC_8     , KC_9     , KC_ASTR  ,                                      KC_HOME  , KC_END   , KC_BTN3  , KC_BTN4  , KC_BTN5  , _______  ,
    _______  , KC_DOT   , KC_4     , KC_5     , KC_6     , KC_MINS  ,                                      KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , XXXXXXX  , _______  ,
    _______  , KC_0     , KC_1     , KC_2     , KC_3     , KC_PLUS  , KC_ASTR  ,                KC_LPRN  , KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , XXXXXXX  , _______  ,
    _______  , _______  , KC_0     , _______  , _______  , _______  , _______  ,                KC_RGUI  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , KC_BTN1  , _______  , KC_BTN2  , SCRL_MO  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
#elif 0  // mixed.
  [2] = LAYOUT_universal(
    _______  , LSG(KC_1), LSG(KC_2), LSG(KC_5), XXXXXXX  , KC_SLSH  ,                                      KC_CAPS  , KC_PSCR  , KC_SCRL  , KC_PAUS  , XXXXXXX  , KC_INS   ,
    KC_ESC   , KC_COMM  , KC_7     , KC_8     , KC_9     , KC_ASTR  ,                                      KC_PGUP  , XXXXXXX  , KC_BTN3  , KC_BTN4  , KC_BTN5  , _______  ,
    _______  , KC_DOT   , KC_4     , KC_5     , KC_6     , KC_MINS  ,                                      KC_PGDN  , KC_BTN1  , KC_UP    , KC_BTN2  , KC_ENT   , _______  ,
    _______  , KC_0     , KC_1     , KC_2     , KC_3     , KC_PLUS  , KC_ASTR  ,                KC_LPRN  , KC_HOME  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_END   , _______  ,
    _______  , _______  , _______  , _______  , KC_BSPC  , _______  , KC_DEL   ,             _______ ,RGUI_T(KC_ENT), _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , KC_BTN1  , KC_BTN2  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
#elif 0 // another.
  [2] = LAYOUT_universal(
    _______  , LSG(KC_1), LSG(KC_2), LSG(KC_5), XXXXXXX  , KC_SLSH  ,                                      KC_CAPS  , KC_PSCR  , KC_SCRL  , KC_PAUS  , XXXXXXX  , KC_INS   ,
    KC_ESC   , KC_COMM  , KC_7     , KC_8     , KC_9     , KC_ASTR  ,                                      KC_PGUP  , KC_HOME  , KC_UP    , KC_END   , XXXXXXX  , _______  ,
    _______  , KC_DOT   , KC_4     , KC_5     , KC_6     , KC_MINS  ,                                      KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , KC_ENT   , _______  ,
    _______  , KC_0     , KC_1     , KC_2     , KC_3     , KC_PLUS  , KC_ASTR  ,                KC_LPRN  , KC_BTN3  , KC_BTN4  , KC_BTN1  , KC_BTN2  , KC_BTN5  , _______  ,
    _______  , _______  , KC_0     , _______  , KC_BSPC  , _______  , KC_DEL   ,            _______  ,RGUI_T(KC_ENT), _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , KC_BTN1  , KC_BTN2  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
#else // like a vim style.
  [2] = LAYOUT_universal(
    _______  , LSG(KC_1), LSG(KC_2), LSG(KC_5), XXXXXXX  , KC_SLSH  ,                                      KC_CAPS  , KC_PSCR  , KC_SCRL  , KC_PAUS  , XXXXXXX  , _______  ,
    _______  , KC_COMM  , KC_7     , KC_8     , KC_9     , KC_ASTR  ,                                      KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , KC_INS   , KC_DEL   ,
    _______  , KC_DOT   , KC_4     , KC_5     , KC_6     , KC_MINS  ,                                      KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , KC_ENT   , _______  ,
    _______  , KC_0     , KC_1     , KC_2     , KC_3     , KC_PLUS  , KC_ASTR  ,                KC_LPRN  , KC_BTN3  , KC_BTN4  , KC_BTN1  , KC_BTN2  , KC_BTN5  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [4] = LAYOUT_universal(
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  ,                                      _______  , _______  , _______  , _______  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , KC_BTN1  , KC_BTN2  , _______  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),
#endif
  [3] = LAYOUT_universal(
    _______  , RGB_TOG  , RGB_MOD  , RGB_RMOD ,LCG(KC_LEFT),LCG(KC_RIGHT),                                 XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , _______  ,
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , XXXXXXX  ,                                      CPI_I1K  , CPI_I100 , CPI_D100 , CPI_D1K  , KBC_SAVE , KBC_RST  ,
    _______  , KC_F5    , KC_F6    , KC_F7    , KC_F8    , KC_MPLY  ,                                      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , SCRL_DVI , _______  ,
    _______  , KC_F9    , KC_F10   , KC_F11   , KC_F12   , XXXXXXX  , _______  ,                _______  , KC_HOME  , KC_PGDN  , KC_PGUP  , KC_END   , SCRL_DVD , _______ ,
    QK_BOOT  , EE_CLR   , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,                _______  , _______  , _______  , _______  , _______  , _______  , _______
  ),

};
// clang-format on
 
bool process_record_user(uint16_t keycode, keyrecord_t *record) {

    if (record->event.pressed) {

        keyball_scrollball_inhibitor_typing_extend(KEYBALL_SCROLLBALL_INHIBITOR_TYPING_STEP);
    }

    switch (keycode) {
#if !0
        case KC_LWIN:
        case KC_RWIN:
            if (record->event.pressed) {
                auto_mouse_layer_off();
            }
            break;
#endif

        case MY_TGAM: {
            static uint16_t s_time_on_pressed;
            static bool s_was_enabled;
            uint16_t const now = timer_read();

            bool const is_enable = get_auto_mouse_enable();
            if (record->event.pressed) {
                // record some states for auto_mouse toggling.
                s_was_enabled = is_enable;
                s_time_on_pressed = now;
            }
            
            if (TIMER_DIFF_16(now, s_time_on_pressed) < MY_AUTO_MOUSE_TOGGLE_TIME) {

                if (record->event.pressed) {
                    if (is_enable) {
                        auto_mouse_layer_off();
                        set_auto_mouse_enable(false);
                    }
                    break;
                }
                // event.released.
                
                if (s_was_enabled) {
                    set_auto_mouse_enable(true);
                }
                else {
                    // toggle layer 2 when auto_mouse is disabled.
                    layer_invert(2);
                }
                break;
            }
            set_auto_mouse_enable(!s_was_enabled);
            break;
        }
        default:
            break;
    }
    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {

    // bool const ison_layer4 = layer_state_is(4);

    // changed a simple that is safe.
    // will be highest_layer is 3 when call this funciton at changed to layer 3 and 4.
    // but a simple code is going to safe.
    uint8_t const highest_layer = get_highest_layer(remove_auto_mouse_layer(state, true));
    if (highest_layer != 3) {
        keyball_set_scroll_mode(false);
    }
    else {
        keyball_set_scroll_mode(true);
    }

#if 0
    if (highest_layer != 0 && highest_layer != 3) {
        // other layers can't hold auto mouse mode.
        // avoid any trouble cause they use a keycode on high pirority layer (ex.layer 4: auto mouse layer)
        return remove_auto_mouse_layer(state, false);
    }
    return state;
#else
    // no more drops the auto_mouse layer.
    return state;
#endif
}

#if defined(TAPPING_TERM_PER_KEY)
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case LT(1,KC_LNG2):
        case LT(2,KC_ENT):
        case LT(3,KC_LNG1):
        case LT(3,KC_BSLS):
            return 130;  // 120;
        default:
            return TAPPING_TERM;
    }
}
#endif// defined(TAPPING_TERM_PER_KEY)

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

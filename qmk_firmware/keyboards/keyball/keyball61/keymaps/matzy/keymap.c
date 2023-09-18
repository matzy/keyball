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

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    KC_ESC   , KC_1     , KC_2     , KC_3     , KC_4     , KC_5     ,                                      KC_6     , KC_7     , KC_8     , KC_9     , KC_0     , KC_DEL   ,
    KC_TAB   , KC_Q     , KC_W     , KC_E     , KC_R     , KC_T     ,                                      KC_Y     , KC_U     , KC_I     , KC_O     , KC_P     , KC_MINS  ,
    LCTL_T(KC_ESC), KC_A, KC_S     , KC_D     , KC_F     , KC_G     ,                                      KC_H     , KC_J     , KC_K     , KC_L     , KC_SCLN  ,RALT_T(KC_QUOT),
    LSFT_T(KC_GRV), KC_Z, KC_X     , KC_C     , KC_V     , KC_B     , _______  ,                  _______, KC_N     , KC_M     , KC_COMM  , KC_DOT   , KC_SLSH  ,RSFT_T(KC_EQL),
    KC_LCTL  , KC_LGUI  , TG(2)    , KC_LALT  ,LT(1,KC_LNG2),LT(2,KC_SPC),LT(3,KC_LNG1),  LT(1,KC_BSPC),LT(2,KC_ENT),LT(1,KC_LNG2),KC_RGUI, _______  , KC_RALT  ,LT(3,KC_BSLS)
  ),

  [1] = LAYOUT_universal(
    _______  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , KC_F5    ,                                      KC_F6    , KC_F7    , KC_F8    , KC_F9    , KC_F10   , KC_F11   ,
    _______  , KC_QUES  , XXXXXXX  , KC_EXLM  , XXXXXXX  , KC_TILD  ,                                      KC_INT3  , KC_LPRN  , KC_RPRN  , XXXXXXX  , KC_PERC  , KC_F12   ,
    _______  , KC_AT    , KC_SLSH  , KC_DLR   , XXXXXXX  , XXXXXXX  ,                                      KC_HASH  , KC_LCBR  , KC_RCBR  , KC_LBRC  , KC_RBRC  , _______  ,
    _______  , XXXXXXX  , XXXXXXX  , KC_CIRC  , XXXXXXX  , KC_GRV   , KC_LNG3  ,                 KC_LNG4 , KC_AMPR  , KC_ASTR  , KC_LABK  , KC_RABK  , XXXXXXX  , _______  ,
    _______  , _______  , _______  , _______  , _______  , _______  , KC_BSPC  ,                 KC_DEL  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [2] = LAYOUT_universal(
    _______  , LSG(KC_4), LSG(KC_5), XXXXXXX  , XXXXXXX  , KC_SLSH  ,                                      XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , XXXXXXX  , KC_INS   ,
    _______  , KC_COMM  , KC_7     , KC_8     , KC_9     , KC_ASTR  ,                                      KC_HOME  , KC_END   , KC_BTN3  , KC_BTN4  , KC_BTN5  , _______  ,
    _______  , KC_DOT   , KC_4     , KC_5     , KC_6     , KC_MINS  ,                                      KC_PGUP  , KC_BTN1  , KC_UP    , KC_BTN2  , XXXXXXX  , _______  ,
    _______  , KC_0     , KC_1     , KC_2     , KC_3     , KC_PLUS  , KC_ASTR  ,                KC_LPRN  , KC_PGDN  , KC_LEFT  , KC_DOWN  , KC_RGHT  , XXXXXXX  , _______  ,
    _______  , _______  , KC_0     , _______  , _______  , _______  , _______  ,                KC_RGUI  , _______  , _______  , _______  , _______  , _______  , _______
  ),

  [3] = LAYOUT_universal(
    RGB_TOG  , _______  , _______  , _______  , _______  , _______  ,                                      RGB_M_P  , RGB_M_B  , RGB_M_R  , RGB_M_SW , RGB_M_SN , RGB_M_K  ,
    RGB_MOD  , KC_F1    , KC_F2    , KC_F3    , KC_F4    , XXXXXXX  ,                                      RGB_M_X  , RGB_M_G  , RGB_M_T  , RGB_M_TW , XXXXXXX  , _______  ,
    RGB_RMOD , KC_F5    , KC_F6    , KC_F7    , KC_F8    , XXXXXXX  ,                                      CPI_I1K  , CPI_I100 , CPI_D100 , CPI_D1K  , KBC_SAVE , KBC_RST  ,
    _______  , KC_F9    , KC_F10   , KC_F11   , KC_F12   , XXXXXXX  , EE_CLR  ,                  EE_CLR  , KC_HOME  , KC_PGUP  , KC_PGDN  , KC_END   , SCRL_DVI , SCRL_DVD ,
    QK_BOOT  , _______  , KC_LEFT  , KC_DOWN  , KC_UP    , KC_RGHT  , _______  ,                _______  , KC_BSPC  , _______  , _______  , _______  , _______  , QK_BOOT
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 3);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
    keyball_oled_render_layerinfo();
}
#endif

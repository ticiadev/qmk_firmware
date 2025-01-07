#include QMK_KEYBOARD_H
#include <stdio.h>

enum layers {
    _DEFAULT,
    _NAV
};

enum custom_keycodes {
    KC_DBL0 = SAFE_RANGE,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap _DEFAULT:
 * ,-------------------.
 * | -  | /  | *  | NAV|
 * |----|----|----|----|
 * | 7  | 8  | 9  |    |
 * |----|----|----| +  |
 * | 4  | 5  | 6  |    |
 * |----|----|----|----|
 * | 1  | 2  | 3  |    |
 * |----|----|----| En |
 * | 0  | 00 | .  |    |
 * `-------------------'
 */
  [_DEFAULT] = LAYOUT(
    KC_PMNS,  KC_PSLS,  KC_PAST,   TT(_NAV),
    KC_P7,    KC_P8,    KC_P9,
    KC_P4,    KC_P5,    KC_P6,     KC_PPLS,
    KC_P1,    KC_P2,    KC_P3,
    KC_P0,    KC_DBL0,  KC_PDOT,   KC_PENT
  ),

/* Keymap _NV: Navigation layer
 * ,-------------------.
 * |INS |HOME|PGUP| DEF|
 * |----|----|----|----|
 * |DEL |END |PGDN|    |
 * |----|----|----|    |
 * |RMOD|RTOG|RBUP|    |
 * |----|----|----|----|
 * |RMOD| UP |RBDN|    |
 * |----|----|----|BKSP|
 * |LEFT|DOWN|RIGH|    |
 * `-------------------'
 */
  [_NAV] = LAYOUT(
    KC_INS,   KC_HOME,  KC_PGUP,   KC_TRNS,
    KC_DEL,   KC_END,   KC_PGDN,
    RGB_MOD,  RGB_TOG,  RGB_VAI,   XXXXXXX,
    RGB_RMOD, KC_UP,    RGB_VAD,
    KC_LEFT,  KC_DOWN,  KC_RGHT,   KC_BSPC
  ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case KC_DBL0:
      if (record->event.pressed) {
        SEND_STRING("00");
      } else {
        //release keypress
      }
      break;

  }
  return true;
};

#ifdef OLED_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_270;   //vertical orientation
}

bool oled_task_user(void) {
  // Host Keyboard Layer Status
  oled_write_P(PSTR("Layer"), false);
  switch (get_highest_layer(layer_state)) {
    case _DEFAULT:
      oled_write_ln_P(PSTR(" DEF"), false);
      break;
    case _NAV:
      oled_write_ln_P(PSTR(" NAV"), false);
      break;
    default:
      oled_write_ln_P(PSTR(" UND"), false);
  }

  // Host Keyboard LED Status
  led_t led_state = host_keyboard_led_state();
  oled_write_P(PSTR("-----"), false);
  oled_write_P(PSTR("Stats"), false);
  oled_write_P(led_state.num_lock ? PSTR("num:*") : PSTR("num:."), false);
  oled_write_P(led_state.caps_lock ? PSTR("cap:*") : PSTR("cap:."), false);
  oled_write_P(led_state.scroll_lock ? PSTR("scr:*") : PSTR("scr:."), false);

  // Host Keyboard RGB backlight status
  oled_write_P(PSTR("-----"), false);
  oled_write_P(PSTR("Light"), false);

  static char led_buf[30];
  snprintf(led_buf, sizeof(led_buf) - 1, "RGB:%cM: %2d\nh: %2ds: %2dv: %2d\n",
      rgblight_is_enabled() ? '*' : '.', (uint8_t)rgblight_get_mode(),
      (uint8_t)(rgblight_get_hue() / RGBLIGHT_HUE_STEP),
      (uint8_t)(rgblight_get_sat() / RGBLIGHT_SAT_STEP),
      (uint8_t)(rgblight_get_val() / RGBLIGHT_VAL_STEP));
  oled_write(led_buf, false);

    return false;
}
#endif

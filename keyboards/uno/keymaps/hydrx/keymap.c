#include QMK_KEYBOARD_H

enum uno_keycode
{
  UNO = SAFE_RANGE
};

#define GITHUB "https://github.com/hydrx"
#define RESET_LENGTH 3000
const uint8_t PROGMEM RGBLED_RAINBOW_MOOD_INTERVALS[] = { 10, 25, 50 };

char stringToSend[2] = "a";
char maxLetter = 'z';

uint8_t presetCounter = 0;

#define COUNTER X_A


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
      [0] = LAYOUT(
            UNO
          )
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
	switch (keycode) {
	case UNO:
        if (record->event.pressed) {
            //when key is pressed
            SEND_STRING(GITHUB);
            rgblight_sethsv_noeeprom(255, 255, 255);
            rgblight_mode_noeeprom(RGBLIGHT_MODE_RAINBOW_MOOD);
        }
         else {
            //when key is released
        }
        break;
    }
    return true;
};


void keyboard_post_init_user(void) {
    rgblight_enable_noeeprom();
    rgblight_sethsv_noeeprom(0, 0, 0);
    rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
}

/* 2021 hydrx
 */
#include QMK_KEYBOARD_H

// layers:
#define _CK 0
#define _FN 1
#define _MC 2

enum custom_keycodes {
  CK = SAFE_RANGE,
  FN,
  MC,
};

// tap dance declarations
enum {
  C_Z = 0,
  C_X,
  C_V,
  C_S,
  M_Z,
  M_X,
  M_V,
  M_S,
  S_C,
};

// define a type containing as many tapdance states as you need
typedef enum {
  SINGLE_TAP,
  SINGLE_HOLD,
  DOUBLE_SINGLE_TAP
} td_state_t;

// create a global instance of the tapdance state type
static td_state_t td_state_sft;
static bool caps_lock = false;

// declare your tapdance functions:

// function to determine the current tapdance state
int cur_dance (qk_tap_dance_state_t *state);

// `finished` and `reset` functions for each tapdance keycode
void sft_finished (qk_tap_dance_state_t *state, void *user_data);
void sft_reset (qk_tap_dance_state_t *state, void *user_data);


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* COLEMAK
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | \      | 6      | 7      | 8      | 9      | 0      | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | G      | P7     | P8     | P9     | J      | L      | U      | Y      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN     | A      | R      | S      | T      | D      | P4     | P5     | P6     | H      | N      | E      | I      | O      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | SHIFT  | Z      | X      | C      | V      | B      | P1     | P2     | P3     | K      | M      | ,      | .      |  /     | SFL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LCTRL  | LGUI   | LALT   | CTRL+S | [      | SPACE  | BKSP   | P0     | ENTER  | SPACE  | ]      |  LEFT  |  DOWN  |  UP    | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_CK] = { /* COLEMAK */
   { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV   },
   { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_P7,   KC_P8,   KC_P9,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT  },
   { TT(_FN), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_P4,   KC_P5,   KC_P6,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT   },
   { KC_LSFT, TD(C_Z), TD(C_X), KC_C,    TD(C_V), KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(S_C)  },
   { KC_LCTL, KC_LGUI, KC_LALT, TD(C_S), KC_LBRC, KC_SPC,  KC_BSPC, KC_P0,   KC_ENT,  KC_SPC,  KC_RBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  },
  },

/* FUNCTION LAYER - arrows, fn keys, media keys
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | MAC    | F1     | F2     | F3     | F4     | F5     | F11    | F12    |        | F6     | F7     | F8     | F9     | F10    | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * |        |        |   UP   |        |        |        | RESET  |RGB_TOG |RGB_MOD |        |        |        |        |        |        |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * |        |  LEFT  |  DOWN  | RIGHT  |        |        |  ASRP  |  ASTG  |  ASUP  |        |        |        |        |        | MUTE   |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * |        |        |        |        |        |        |  INS   |  HOME  |  ASDN  |        |        |        |        |        | PLAY   |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * |        |        |        |        |        |        |  DEL   |  END   |  NLCK  |        |        | RW     | VOLD   | VOLU   | FW     |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_FN] = { /* FUNCTION */
   { TO(_MC), KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F11,  KC_F12,  KC_TRNS, KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_TRNS  },
   { KC_TRNS, KC_TRNS, KC_UP,   KC_TRNS, KC_TRNS, KC_TRNS, RESET,   RGB_TOG, RGB_MOD, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS  },
   { KC_TRNS, KC_LEFT, KC_DOWN, KC_RGHT, KC_TRNS, KC_TRNS, KC_ASRP, KC_ASTG, KC_ASUP, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MUTE  },
   { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_INS,  KC_HOME, KC_ASDN, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_MPLY  },
   { KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_DEL,  KC_END,  KC_NLCK, KC_TRNS, KC_TRNS, KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT  },
  },

 /* MACOS LAYER - switch CTRL, GUI, TD CTRL
 * .--------------------------------------------------------------------------------------------------------------------------------------.
 * | ESC    | 1      | 2      | 3      | 4      | 5      | -      | =      | \      | 6      | 7      | 8      | 9      | 0      | `      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------|
 * | TAB    | Q      | W      | F      | P      | G      | P7     | P8     | P9     | J      | L      | U      | Y      | ;      | '      |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+-----------------+--------|
 * | FN     | A      | R      | S      | T      | D      | P4     | P5     | P6     | H      | N      | E      | I      | O      | ENTER  |
 * |--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------+--------------------------+--------|
 * | SHIFT  | Z      | X      | C      | V      | B      | P1     | P2     | P3     | K      | M      | ,      | .      |  /     | SFL    |
 * |--------+--------+--------+--------+--------+-----------------+--------+--------+--------+--------+-----------------+--------+--------|
 * | LGUI   | LCTRL  | LALT   | CMD+S  | [      | SPACE  | BKSP   | P0     | ENTER  | SPACE  | ]      |  LEFT  |  DOWN  |  UP    | RIGHT  |
 * '--------------------------------------------------------------------------------------------------------------------------------------'
 */

  [_MC] = { /* MACOS */
   { KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_MINS, KC_EQL,  KC_BSLS, KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_GRV   },
   { KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_P7,   KC_P8,   KC_P9,   KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_QUOT  },
   { TT(_FN), KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_P4,   KC_P5,   KC_P6,   KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_ENT   },
   { KC_LSFT, TD(M_Z), TD(M_X), KC_C,    TD(M_V), KC_B,    KC_P1,   KC_P2,   KC_P3,   KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, TD(S_C)  },
   { KC_LGUI, KC_LCTL, KC_LALT, TD(M_S), KC_LBRC, KC_SPC,  KC_BSPC, KC_P0,   KC_ENT,  KC_SPC,  KC_RBRC, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT  },
  }
 };

// determine the tapdance state to return
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    if (state->interrupted || !state->pressed) { return SINGLE_TAP; }
    else { return SINGLE_HOLD; }
  }
  if (state->count == 2) { return DOUBLE_SINGLE_TAP; }
  else { return 3; } // any number higher than the maximum state value you return above
}

#define DEBOUNCE_CAPS_DELAY 100

//add triple tap dance
void triple_tap_dance_pair_on_each_tap(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 3) {
        // immediately finish on third press
        register_code16(pair->kc2);
        state->finished = true;
    }
}

void triple_tap_dance_pair_finished(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1) {
        register_code16(pair->kc1);
    } else if (state->count == 2) {
        // tap plus hold
        tap_code16(pair->kc1);
        register_code16(pair->kc1);
    } else if (state->count == 3) {
        register_code16(pair->kc2);
    }
}

void triple_tap_dance_pair_reset(qk_tap_dance_state_t *state, void *user_data) {
    qk_tap_dance_pair_t *pair = (qk_tap_dance_pair_t *)user_data;

    if (state->count == 1 || state->count == 2) {
        // 1-tap and 2-tap both result in `kc1` pressed so release it
        unregister_code16(pair->kc1);
    } else if (state->count == 3) {
        unregister_code16(pair->kc2);
    }
}

#define TRIPLE_TAP_DANCE_DOUBLE(kc1, kc2) \
        { .fn = {triple_tap_dance_pair_on_each_tap, triple_tap_dance_pair_finished, triple_tap_dance_pair_reset}, .user_data = (void *)&((qk_tap_dance_pair_t){kc1, kc2}), }

// handle the possible states for each tapdance keycode you define:

void sft_finished (qk_tap_dance_state_t *state, void *user_data) {
  td_state_sft = cur_dance(state);
    if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            register_code(KC_CAPSLOCK);
            return;
        }
    }
   
    if (caps_lock) {
        register_code(KC_CAPSLOCK);
    } else {
        register_code(KC_LSFT);
    }
}

void sft_reset (qk_tap_dance_state_t *state, void *user_data) {
     if (td_state_sft == DOUBLE_SINGLE_TAP) {
        if (!caps_lock) {
            caps_lock = true;
            wait_ms(DEBOUNCE_CAPS_DELAY);
            unregister_code(KC_CAPSLOCK);
            return;
        }
    }

    if (caps_lock) {
        caps_lock = false;
        wait_ms(DEBOUNCE_CAPS_DELAY);
        unregister_code(KC_CAPSLOCK);
    } else {
        unregister_code(KC_LSFT);
    }
}

// tap dance definitions
qk_tap_dance_action_t tap_dance_actions[] = {
  [C_Z]  = TRIPLE_TAP_DANCE_DOUBLE(KC_Z, LCTL(KC_Z)),
  [C_X]  = TRIPLE_TAP_DANCE_DOUBLE(KC_X, LCTL(KC_X)),
  [C_V]  = TRIPLE_TAP_DANCE_DOUBLE(KC_V, LCTL(KC_V)),

  [M_Z]  = TRIPLE_TAP_DANCE_DOUBLE(KC_Z, LGUI(KC_Z)),
  [M_X]  = TRIPLE_TAP_DANCE_DOUBLE(KC_X, LGUI(KC_X)),
  [M_V]  = TRIPLE_TAP_DANCE_DOUBLE(KC_V, LGUI(KC_V)),

  [C_S]  = ACTION_TAP_DANCE_DOUBLE(LCTL(KC_S), LCTL(KC_C)),

  [M_S]  = ACTION_TAP_DANCE_DOUBLE(LGUI(KC_S), LGUI(KC_C)),

  [S_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, sft_finished, sft_reset)
};

  // Set numlock to always on when keyboard starts
  void matrix_init_user (void) {
    if (!(host_keyboard_leds() & (1<<USB_LED_NUM_LOCK))) {
        register_code(KC_NUMLOCK);
        unregister_code(KC_NUMLOCK);
    }
  }
#include "kinesis.h"
#include "action_layer.h"
#include "eeconfig.h"

extern keymap_config_t keymap_config;

enum kinesis_layers {
  _CMODDH,    // Colemak Mod-DH Matrix (default layer)
  _QWERTY,    // Qwerty
  _COLEMAK,   // Colemak
  _NUMBERS,   // Numbers & Symbols
  _NUMBERS2,  // Numbers & Symbols 2 (identical as _NUMBERS; basically used for tri-layer access to _ADJUST)
  _FUNCTION,  // Function
  _FUNCTION2, // Function 2 (identical as _FUNCTION; used to allow for easier use of space and backspace while using function layer arrows)
  _NUMPAD,    // Numpad
  _CMODDHGM,  // Colemak Mod-DH Matrix gaming/vanilla (no dual-role keys with layer access)
  _QWERTYGM,  // QWERTY gaming/vanilla (no dual-role keys with layer access)
  _ADJUST     // Adjust layer
};

enum kinesis_keycodes {
  CMODDH = SAFE_RANGE,
  QWERTY,
  COLEMAK,
  CMODDHGM,
  QWERTYGM,
  SPCFN  = LT(_FUNCTION, KC_SPC),
  BSPCFN = LT(_FUNCTION2, KC_BSPC),
  ENTNS  = LT(_NUMBERS, KC_ENT),
  DELNS  = LT(_NUMBERS2, KC_DEL),
  CTLESC = CTL_T(KC_ESC),
  NKROTG = MAGIC_TOGGLE_NKRO
};

#define _______ KC_TRNS
#define XXXXXXX KC_NO

//Tap Dance Declarations
enum {
  ADJ = 0,
  LBCB,
  RBCB,
  EQPL,
  PLEQ,
  MNUN,
  SLAS,
  GVTL,
  PPLEQ,
  PMNUN,
  PSLPAS
};

void dance_LAYER_finished(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_on(_ADJUST);
     set_oneshot_layer(_ADJUST, ONESHOT_START);
  }
}
void dance_LAYER_reset(qk_tap_dance_state_t *state, void *user_data) {
  if (state->count == 2) {
     layer_off(_ADJUST);
     clear_oneshot_layer_state(ONESHOT_PRESSED);
  }
}

qk_tap_dance_action_t tap_dance_actions[] = {
[ADJ]    = ACTION_TAP_DANCE_FN_ADVANCED(NULL, dance_LAYER_finished, dance_LAYER_reset),  //  Double-tap to activate Adjust layer via oneshot layer 
[LBCB]   = ACTION_TAP_DANCE_DOUBLE(KC_LBRC, KC_LCBR),  // Left bracket on a single-tap, left brace on a double-tap
[RBCB]   = ACTION_TAP_DANCE_DOUBLE(KC_RBRC, KC_RCBR),  // Right bracket on a single-tap, right brace on a double-tap
[EQPL]   = ACTION_TAP_DANCE_DOUBLE(KC_EQL, KC_PLUS),   // Plus sign on a single-tap, equal sign on a double-tap
[PLEQ]   = ACTION_TAP_DANCE_DOUBLE(KC_PLUS, KC_EQL),   // Equal sign on a single-tap, plus sign on a double-tap
[MNUN]   = ACTION_TAP_DANCE_DOUBLE(KC_MINS, KC_UNDS),  // Minus sign on a single-tap, underscore on a double-tap
[SLAS]   = ACTION_TAP_DANCE_DOUBLE(KC_SLSH, KC_ASTR),  // Slash in a single-tap, asterisk in a double-tap
[GVTL]   = ACTION_TAP_DANCE_DOUBLE(KC_GRV, KC_TILD),   // Grave on a single-tap, tilde on a double-tap
[PPLEQ]  = ACTION_TAP_DANCE_DOUBLE(KC_PPLS, KC_EQL),   // Numpad plus sign on a single-tap, equal sign on a double-tap
[PMNUN]  = ACTION_TAP_DANCE_DOUBLE(KC_PMNS, KC_UNDS),  // Numpad minus sign on a single-tap, underscore on a double-tap
[PSLPAS] = ACTION_TAP_DANCE_DOUBLE(KC_PSLS, KC_PAST)   // Numpad slash on a single-tap, numpad asterisk on a double-tap
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Colemak Mod-DH Matrix
*  (Defauit layer; keys separated by /: tap for first, hold for second; uses Space Cadet Shifts)
*  ,-----------------------------------------------------------------------------------------------------------.
*  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |   Tab  |   Q  |   W  |   F  |   P  |   B  |                   |   J  |   L  |   U  |   Y  |   ;  |   \    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |Esc/Ctrl|   A  |   R  |   S  |   T  |   G  |                   |   M  |   N  |   E  |   I  |   O  |   '    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |SC Shift|   Z  |   X  |   C  |   D  |   V  |                   |   K  |   H  |   ,  |   .  |   /  |SC Shift|
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |Esc/Ctl| Hyper |                   |  RAlt |  RCtl |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      | Space | Enter |App/Alt|                   |  RGUI | Delete|  Bspc |
*                      |   /   |   /   |-------|                   |-------|   /   |   /   |
*                      |  Fn   | Number|  Bspc |                   |  Tab  |Number2|  Fn2  |
*                      `-----------------------'                   `-----------------------' 
*/
[_CMODDH] = KEYMAP(
  // Left Hand
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,       KC_F8,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,
  CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_G,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,
  //Left Thumb
                                      CTLESC,  ALL_T(KC_NO),
                                               ALT_T(KC_APP),
                             SPCFN,   ENTNS,   KC_BSPC,
  //Right Hand
  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_NUMPAD), MO(_ADJUST),
  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  //Right Thumb
  KC_RALT, KC_RCTL,
  KC_RGUI,
  KC_TAB,  DELNS,   BSPCFN
),

/* QWERTY
*  (Keys separated by /: tap for first, hold for second; uses Space Cadet Shifts)
*  ,-----------------------------------------------------------------------------------------------------------.
*  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |   Tab  |   Q  |   W  |   E  |   R  |   T  |                   |   Y  |   U  |   I  |   O  |   P  |   \    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |Esc/Ctrl|   A  |   S  |   D  |   F  |   G  |                   |   H  |   J  |   K  |   L  |   ;  |   '    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |SC Shift|   Z  |   X  |   C  |   V  |   B  |                   |   N  |   M  |   ,  |   .  |   /  |SC Shift|
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |Esc/Ctl| Hyper |                   |  RAlt |  RCtl |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      | Space | Enter |App/Alt|                   |  RGUI | Delete|  Bspc |
*                      |   /   |   /   |-------|                   |-------|   /   |   /   |
*                      |  Fn   | Number|  Bspc |                   |  Tab  |Number2|  Fn2  |
*                      `-----------------------'                   `-----------------------' 
*/
[_QWERTY] = KEYMAP(
  // Left Hand
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,       KC_F8,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
  CTLESC,  KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,
  //Left Thumb                         
                                      CTLESC,  ALL_T(KC_NO),
                                               ALT_T(KC_APP),
                             SPCFN,   ENTNS,   KC_BSPC,

  //Right Hand
  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_NUMPAD), MO(_ADJUST),
  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  //Right Thumb
  KC_RALT, KC_RCTL,
  KC_RGUI,
  KC_TAB,  DELNS,   BSPCFN
),

/* Colemak
*  (Keys separated by /: tap for first, hold for second; uses Space Cadet Shifts)
*  ,-----------------------------------------------------------------------------------------------------------.
*  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |   Tab  |   Q  |   W  |   F  |   P  |   G  |                   |   J  |   L  |   U  |   Y  |   ;  |   \    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |Esc/Ctrl|   A  |   R  |   S  |   T  |   D  |                   |   H  |   N  |   E  |   I  |   O  |   '    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |SC Shift|   Z  |   X  |   C  |   V  |   B  |                   |   K  |   M  |   ,  |   .  |   /  |SC Shift|
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |Esc/Ctl| Hyper |                   |  RAlt |  RCtl |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      | Space | Enter |App/Alt|                   |  RGUI | Delete|  Bspc |
*                      |   /   |   /   |-------|                   |-------|   /   |   /   |
*                      |  Fn   | Number|  Bspc |                   |  Tab  |Number2|  Fn2  |
*                      `-----------------------'                   `-----------------------' 
*/
[_COLEMAK] = KEYMAP(
  // Left Hand
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,
  CTLESC,  KC_A,    KC_R,    KC_S,    KC_T,    KC_D,
  KC_LSPO, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,
  //Left Thumb
                                      CTLESC,  ALL_T(KC_NO),
                                               ALT_T(KC_APP),
                             SPCFN,   ENTNS,   KC_BSPC,
  //Right Hand
  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_NUMPAD), MO(_ADJUST),
  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSPC,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  //Right Thumb
  KC_RALT, KC_RCTL,
  KC_RGUI,
  KC_TAB,  DELNS,   BSPCFN
),

/* Number/symbol layer
*  (Multiple characters: single-tap for first, double-tap for second)
*  ,-----------------------------------------------------------------------------------------------------------.
*  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |   F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                   |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |   6  |   7  |   8  |   9  |   0  |                   |   ^  |   &  |   *  |   (  |   )  |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |   1  |   2  |   3  |   4  |   5  |                   |   !  |   @  |   #  |   $  |   %  |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      |   .  |  / * |  - _ |  + = |                   |  ` ~ |  [ { |  ] } |      |      |        |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |   (  |   )  |  [ { |  ] } |                                 |      |      |      |      |
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |       |       |                   |       |       |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |       |                   |       |       |       |
*                      |       |       |-------|                   |-------|       |       |
*                      |       |       |       |                   |       |       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_NUMBERS] = KEYMAP(
  // Left Hand
  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,
  KC_F12,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
  _______,  _______,  KC_DOT,   TD(SLAS), TD(MNUN), TD(PLEQ),
            KC_LPRN,  KC_RPRN,  TD(LBCB), TD(RBCB),
  // Left Thumb
                                          _______,  _______,
                                                    _______,
                                _______,  _______,  _______,
  // Right Hand
  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,
  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______, 
  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______, 
  TD(GVTL), TD(LBCB), TD(RBCB), _______,  _______,  _______,
            _______,  _______,  _______,  _______, 
  // Right Thumb
  _______,  _______,
  _______,
  _______,  _______,  _______
),

[_NUMBERS2] = KEYMAP(
  // Left Hand
  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,
  KC_F12,   KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,
  _______,  KC_6,     KC_7,     KC_8,     KC_9,     KC_0,
  _______,  KC_1,     KC_2,     KC_3,     KC_4,     KC_5,
  _______,  _______,  KC_DOT,   TD(SLAS), TD(MNUN), TD(PLEQ),
            KC_LPRN,  KC_RPRN,  TD(LBCB), TD(RBCB),
  // Left Thumb
                                          _______,  _______,
                                                    _______,
                                _______,  _______,  _______,
  // Right Hand
  _______,  _______,  _______,  _______,  _______,  _______, _______, _______, _______,
  KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,
  KC_CIRC,  KC_AMPR,  KC_ASTR,  KC_LPRN,  KC_RPRN,  _______, 
  KC_EXLM,  KC_AT,    KC_HASH,  KC_DLR,   KC_PERC,  _______, 
  TD(GVTL), TD(LBCB), TD(RBCB), _______,  _______,  _______,
            _______,  _______,  _______,  _______, 
  // Right Thumb
  _______,  _______,
  _______,
  _______,  _______,  _______
),

/* Function layer
*  ,-----------------------------------------------------------------------------------------------------------.
*  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |   F12  |  F1  |  F2  |  F3  |  F4  |  F5  |                   |  F6  |  F7  |  F8  |  F9  |  F10 |   F11  |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      |      |  Up  |      |      |                   |      |      |  Up  |Ctrl+Y|      |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |Ctrl+A| Left | Down | Right|C+A+Tb|                   | PgUp | Right| Down | Left | Home |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |Ctrl+Z|Ctrl+X|Ctrl+C|Ctrl+V| Bspc |                   | PgDn | Mute | Vol- | Vol+ |  End |        |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |      |      |      |      |                                 | Prev | Play | Next | Stop |
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |       |       |                   |       |       |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |       |                   |       |       |       |
*                      |       |       |-------|                   |-------|       |       |
*                      |       |       |       |                   |C+A+Tab|       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_FUNCTION] = KEYMAP(
  // Left Hand
  _______, _______,    _______,    _______,    _______,    _______, _______, _______, _______,
  KC_F12,  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,
  _______, _______,    _______,    KC_UP,      _______,    _______, 
  _______, LCTL(KC_A), KC_LEFT,    KC_DOWN,    KC_RGHT,    LCA(KC_TAB),
  _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_BSPC,
           _______,    _______,    _______,    _______,
  // Left Thumb
                                               _______,    _______,
                                                           _______,
                                   _______,    _______,    _______,
  // Right Hand  
  _______, _______,    _______,    _______,    _______,    _______, _______, _______, _______,
  KC_F6,   KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
  _______, _______,    KC_UP,      LCTL(KC_Y), _______,    _______,
  KC_PGUP, KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_HOME,    _______,
  KC_PGDN, KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_END,     _______,
           KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MSTP,
  // Right Thumb
  _______,     _______,
  _______,
  LCA(KC_TAB), _______, _______
),

[_FUNCTION2] = KEYMAP(
  // Left Hand
  _______, _______,    _______,    _______,    _______,    _______, _______, _______, _______,
  KC_F12,  KC_F1,      KC_F2,      KC_F3,      KC_F4,      KC_F5,
  _______, _______,    _______,    KC_UP,      _______,    _______, 
  _______, LCTL(KC_A), KC_LEFT,    KC_DOWN,    KC_RGHT,    LCA(KC_TAB),
  _______, LCTL(KC_Z), LCTL(KC_X), LCTL(KC_C), LCTL(KC_V), KC_BSPC,
           _______,    _______,    _______,    _______,
  // Left Thumb
                                               _______,    _______,
                                                           _______,
                                   _______,    _______,    _______,
  // Right Hand  
  _______, _______,    _______,    _______,    _______,    _______, _______, _______, _______,
  KC_F6,   KC_F7,      KC_F8,      KC_F9,      KC_F10,     KC_F11,
  _______, _______,    KC_UP,      LCTL(KC_Y), _______,    _______,
  KC_PGUP, KC_LEFT,    KC_DOWN,    KC_RGHT,    KC_HOME,    _______,
  KC_PGDN, KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_END,     _______,
           KC_MPRV,    KC_MPLY,    KC_MNXT,    KC_MSTP,
  // Right Thumb
  _______,     _______,
  _______,
  LCA(KC_TAB), _______, _______
),

/* Numpad layer
*  (Left side duplicates layout from the Numbers layer, just with numpad output; right side layout close to PC numpad layout)
*  ,-----------------------------------------------------------------------------------------------------------.
*  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |        | NumLk|      |      |      |      |                   |  Tab | NumLk| KP / |  kP *| KP - |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        | KP 6 | KP 7 | KP 8 | KP 9 | KP 0 |                   |      | KP 7 | KP 8 | KP 9 | KP + |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        | KP 1 | KP 2 | KP 3 | KP 4 | KP 5 |                   |      | KP 4 | KP 5 | KP 6 |  =   |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      | KP . |KP/KP*| KP- _| KP+ =|                   |      | KP 1 | KP 2 | KP 3 |KP Ent|        |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |   (  |   )  |  [ { |  ] } |                                 | KP 0 |  ,   | KP . |KP Ent|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |       |       |                   |       |       |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |       |                   |       |       |       |
*                      |       |       |-------|                   |-------|       |       |
*                      |       |       |       |                   |       |       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_NUMPAD] = KEYMAP(
  // Left Hand
  _______, _______, _______, _______,    _______,   _______, _______, _______, _______,
  _______, KC_NLCK, _______, _______,    _______,   _______,
  _______, KC_P6,   KC_P7,   KC_P8,      KC_P9,     KC_P0,
  _______, KC_P1,   KC_P2,   KC_P3,      KC_P4,     KC_P5,
  _______, _______, KC_PDOT, TD(PSLPAS), TD(PMNUN), TD(PPLEQ),
           KC_LPRN, KC_RPRN, TD(LBCB),   TD(RBCB),
  // Left Thumb
                                         _______,   _______,
                                                    _______,
                             _______,    _______,   _______,
  // Right Hand
  _______, _______, _______, _______, _______, _______, _______, _______, _______,
  KC_TAB,  KC_NLCK, KC_PSLS, KC_PAST, KC_PMNS, _______,
  _______, KC_P7,   KC_P8,   KC_P9,   KC_PPLS, _______,
  _______, KC_P4,   KC_P5,   KC_P6,   KC_EQL,  _______,
  _______, KC_P1,   KC_P2,   KC_P3,   KC_PENT, _______,
           KC_P0,   KC_COMM, KC_PDOT, KC_PENT,
  // Right Thumb
  _______, _______,
  _______,
  _______, _______, _______
),

/* Colemak Mod-DH Matrix gaming/vanilla
*  (No access to Function or Numbers layers; mainly used for gaming; double-tap the TD(ADJ) above LAlt to access Adjust layer)
*  ,-----------------------------------------------------------------------------------------------------------.
*  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |   Tab  |   Q  |   W  |   F  |   P  |   B  |                   |   J  |   L  |   U  |   Y  |   ;  |   \    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |  Ctrl  |   A  |   R  |   S  |   T  |   G  |                   |   M  |   N  |   E  |   I  |   O  |   '    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |  Shift |   Z  |   X  |   C  |   D  |   V  |                   |   K  |   H  |   ,  |   .  |   /  |  Shift |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |Esc/Ctl|TD(ADJ)|                   |  RAlt |  RCtl |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |  LAlt |                   |  RGUI |       |       |
*                      | Space | Enter |-------|                   |-------| Delete|  Bspc |
*                      |       |       |  Bspc |                   |  Tab  |       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_CMODDHGM] = KEYMAP(
  // Left Hand
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,
  KC_LCTL, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,
  //Left Thumb
                                      CTLESC,  TD(ADJ),
                                               KC_LALT,
                             KC_SPC,  KC_ENT,  KC_BSPC,
  //Right Hand
  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_NUMPAD), MO(_ADJUST),
  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_BSLS,
  KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT,
  KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  //Right Thumb
  KC_RALT, KC_RCTL,
  KC_RGUI,
  KC_TAB,  KC_DEL,  KC_BSPC
),

/* QWERTY gaming/vanilla
*  (No access to Function or Numbers layers; mainly used for gaming; double-tap the TD(ADJ) above LAlt to access Adjust layer)
*  ,-----------------------------------------------------------------------------------------------------------.
*  | ESC |  F1 |  F2 |  F3 |  F4 |  F5 |  F6 |  F7 |  F8 |  F9 | F10 | F11 | F12 | PScr| SLck| Paus|Numpd|Adjst|
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |    =   |   1  |   2  |   3  |   4  |   5  |                   |   6  |   7  |   8  |   9  |   0  |   -    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |   Tab  |   Q  |   W  |   E  |   R  |   T  |                   |   Y  |   U  |   I  |   O  |   P  |   \    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |  Ctrl  |   A  |   S  |   D  |   F  |   G  |                   |   H  |   J  |   K  |   L  |   ;  |   '    |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |  Shift |   Z  |   X  |   C  |   V  |   B  |                   |   N  |   M  |   ,  |   .  |   /  |  Shift |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |  Ins |   `  |   [  |   ]  |                                 | Left | Down |  Up  | Right|
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |Esc/Ctl|TD(ADJ)|                   |  RAlt |  RCtl |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |  LAlt |                   |  RGUI |       |       |
*                      | Space | Enter |-------|                   |-------| Delete|  Bspc |
*                      |       |       |  Bspc |                   |  Tab  |       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_QWERTYGM] = KEYMAP(
  // Left Hand
  KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,
  KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,
  KC_LCTL, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,
           KC_INS,  KC_GRV,  KC_LBRC, KC_RBRC,
  //Left Thumb
                                      CTLESC,  TD(ADJ),
                                               KC_LALT,
                             KC_SPC,  KC_ENT,  KC_BSPC,
  //Right Hand
  KC_F9,   KC_F10,  KC_F11,  KC_F12,  KC_PSCR, KC_SLCK, KC_PAUS, TG(_NUMPAD), MO(_ADJUST),
  KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
  KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
  KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT,
  //Right Thumb
  KC_RALT, KC_RCTL,
  KC_RGUI,
  KC_TAB,  KC_DEL,  KC_BSPC
),

/* Adjust layer
*  (Enter/Number + Delete/Number2 under non-gaming/vanilla layers)
*  ,-----------------------------------------------------------------------------------------------------------.
*  |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |     |
*  `-----------------------------------------------------------------------------------------------------------'
*  ,-------------------------------------------.                   ,-------------------------------------------.
*  |        |CModDH|Qwerty|Colmak|CMoDGM| QWGM |                   |Numpad|      |      |      |      | RESET  |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      |      |      |      |      |                   |      |      |      |      |      |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      |      |      |      |      |                   |      |NKROTG|      |      |      |        |
*  |--------+------+------+------+------+------|                   |------+------+------+------+------+--------|
*  |        |      |      |      |      |      |                   |      |      |      |      |      |        |
*  `--------+------+------+------+------+------'                   `------+------+------+------+------+--------'
*           |      |      |      |      |                                 |      |      |      |      |
*           `---------------------------'                                 `---------------------------'
*                              ,---------------.                   ,---------------.
*                              |       |       |                   |       |       |
*                      ,-------|-------|-------|                   |-------+-------+-------.
*                      |       |       |       |                   |       |       |       |
*                      |       |       |-------|                   |-------|       |       |
*                      |       |       |       |                   |       |       |       |
*                      `-----------------------'                   `-----------------------' 
*/
[_ADJUST] = KEYMAP(
  // Left Hand
  _______, _______, _______, _______, _______,  _______,  _______, _______, _______,
  _______, CMODDH,  QWERTY,  COLEMAK, CMODDHGM, QWERTYGM,
  _______, _______, _______, _______, _______,  _______,
  _______, _______, _______, _______, _______,  _______,
  _______, _______, _______, _______, _______,  _______,
           _______, _______, _______, _______,
  // Left Thumb
                                      _______,  _______,
                                                _______,
                             _______, _______,  _______,
  // Right Hand
  _______,     _______, _______, _______, _______,  _______,  _______, _______, _______,
  TG(_NUMPAD), _______, _______, _______, _______,  RESET,
  _______,     _______, _______, _______, _______,  _______,
  _______,     NKROTG,  _______, _______, _______,  _______,
  _______,     _______, _______, _______, _______,  _______,
               _______, _______, _______, _______, 
  // Right Thumb
  _______, _______,
  _______,
  _______, _______, _______
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _NUMBERS, _NUMBERS2, _ADJUST);
}

void persistent_default_layer_set(uint16_t default_layer) {
  eeconfig_update_default_layer(default_layer);
  default_layer_set(default_layer);
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case CMODDH:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL << _CMODDH);
        layer_off ( _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _CMODDHGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
      }
      return false;
      break;
    case QWERTY:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL << _QWERTY);
        layer_off ( _CMODDH);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _CMODDHGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
      }
      return false;
      break;
    case COLEMAK:
      if (record->event.pressed) {
        persistent_default_layer_set(1UL << _COLEMAK);
        layer_off ( _CMODDH);
        layer_off ( _QWERTY);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _CMODDHGM);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
      }
      return false;
      break;
    case CMODDHGM:
      if (record->event.pressed) {
        default_layer_set(1UL << _CMODDHGM);
        layer_off ( _CMODDH);
        layer_off ( _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _QWERTYGM);
        layer_off ( _ADJUST);
      }
      return false;
      break;
    case QWERTYGM:
      if (record->event.pressed) {
        default_layer_set(1UL << _QWERTYGM);
        layer_off ( _CMODDH);
        layer_off ( _QWERTY);
        layer_off ( _COLEMAK);
        layer_off ( _NUMBERS);
        layer_off ( _NUMBERS2);
        layer_off ( _FUNCTION);
        layer_off ( _FUNCTION2);
        layer_off ( _NUMPAD);
        layer_off ( _CMODDHGM);
        layer_off ( _ADJUST);
      }
      return false;
      break;
  }
  return true;
}
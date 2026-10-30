#include QMK_KEYBOARD_H

/*
 * Macropad15 - 15 phim + 3 encoder - Pro Micro RP2040 (Vial-QMK)
 *
 * Bo cuc theo anh: 15 phim 3x5 ben phai, 3 nut xoay ben trai
 * (1 to tren = ENC1, 2 nho duoi = ENC2 trai, ENC3 phai; moi nut xoay co nut nhan).
 *      (ENC1)         k0   k1   k2   k3   k4
 *   (ENC2)  (ENC3)    k5   k6   k7   k8   k9
 *                     k10  k11  k12  k13  k14
 * Nhan nut to ENC1 = chuyen layer nen (LCYCLE): Base -> Numpad -> Media -> Nokia.
 *
 * Ma tran (giong ban ESP32-C3, diode ROW2COL): R0..R3 x C0..C3 cho 15 phim,
 * phim Pn nam o hang n%4, cot n/4. 3 nut nhan encoder: ENC1->R0, ENC2->R1,
 * ENC3->R2, 3 chan con lai noi chung qua 1 diode vao C4.
 *
 * Layer 0 Base (giong C3) | 1 Layer1 (giong C3) | 2 Numpad | 3 Media | 4 Nokia | 5 FN
 * Layer 6, 7 de trong.
 */

enum layers { L_BASE, L_FN1, L_NUM, L_MEDIA, L_NOKIA, L_FN };

enum custom_keycodes {
    LCYCLE = QK_KB_0, /* Numpad -> Media -> Nokia -> Numpad ... */
    NK_1, NK_2, NK_3, NK_4, NK_5, NK_6, NK_7, NK_8, NK_9, NK_0, NK_DOT, /* Nokia multitap */
    TH_MIN,           /* bam = "-", giu = "/" */
    TH_PLS,           /* bam = "+", giu = "*" */
    SQ_F1F2,          /* bam: F1 roi F2 (giong ban C3) */
    SQ_F11PU,         /* bam: F11 roi Page Up */
    SQ_F11PD,         /* bam: F11 roi Page Down */
    TG_LATCH,         /* giu phim bat ky: bam 1 lan, roi bam phim can giu */
    TGL_SPC,          /* bam 1 lan = giu Space, bam lan nua = nha */
    TGL_SFT,          /* bam 1 lan = giu Shift, bam lan nua = nha */
    TGL_CTL,          /* bam 1 lan = giu Ctrl,  bam lan nua = nha */
    TGL_ALT           /* bam 1 lan = giu Alt,   bam lan nua = nha */
};

#define FN MO(L_FN)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Layer 0: A..O de test day (tam thoi); Layer 1: giong ban ESP32-C3 */
    [L_BASE] = LAYOUT(
        KC_A,    KC_B,    KC_C,    KC_D,    KC_E,
        KC_F,    KC_G,    KC_H,    KC_I,    KC_J,
        KC_K,    KC_L,    KC_M,    KC_N,    KC_O,
        LCYCLE,  KC_BSPC, KC_TAB
    ),
    [L_FN1] = LAYOUT(
        KC_V,       KC_C,     KC_X,     KC_Z,     KC_UP,
        KC_SLSH,    KC_DOT,   KC_COMM,  KC_M,     KC_LSFT,
        TO(L_BASE), SQ_F1F2,  SQ_F11PU, SQ_F11PD, KC_DEL,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [L_NUM] = LAYOUT(
        KC_P7,   KC_P8,   KC_P9,   TH_MIN,  FN,
        KC_P4,   KC_P5,   KC_P6,   KC_PENT, TH_PLS,
        KC_P1,   KC_P2,   KC_P3,   KC_P0,   KC_PDOT,
        LCYCLE, KC_BSPC, KC_TAB
    ),
    [L_MEDIA] = LAYOUT(
        KC_MPRV, KC_MPLY, KC_MNXT, KC_CALC, FN,
        KC_HOME, KC_UP,   KC_END,  KC_VOLD, KC_VOLU,
        KC_LEFT, KC_DOWN, KC_RGHT, KC_PGUP, KC_PGDN,
        LCYCLE, KC_DEL,  KC_ENT
    ),
    [L_NOKIA] = LAYOUT(
        NK_7,    NK_8,    NK_9,    CW_TOGG, FN,
        NK_4,    NK_5,    NK_6,    KC_ENT,  OSM(MOD_LSFT),
        NK_1,    NK_2,    NK_3,    NK_0,    NK_DOT,
        LCYCLE, KC_BSPC, KC_TAB
    ),
    [L_FN] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_TRNS,
        KC_F5,   KC_F6,   KC_F7,   QK_RBT,  QK_BOOT,
        KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        KC_MUTE, TG_LATCH, TGL_SPC
    ),
    /* Layer 6, 7: trong, de dung them trong Vial */
    [6] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    ),
    [7] = LAYOUT(
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
        KC_TRNS, KC_TRNS, KC_TRNS
    )
};

#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][NUM_DIRECTIONS] = {
    [L_BASE]  = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_UP,   KC_DOWN) },
    [L_FN1]   = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [L_NUM]   = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_UP,   KC_DOWN) },
    [L_MEDIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_MPRV, KC_MNXT), ENCODER_CCW_CW(KC_PGUP, KC_PGDN) },
    [L_NOKIA] = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_UP,   KC_DOWN) },
    [L_FN]    = { ENCODER_CCW_CW(KC_VOLD, KC_VOLU), ENCODER_CCW_CW(KC_LEFT, KC_RGHT), ENCODER_CCW_CW(KC_UP,   KC_DOWN) },
    [6]       = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
    [7]       = { ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS), ENCODER_CCW_CW(KC_TRNS, KC_TRNS) },
};
#endif

/* ---------- Nokia multitap ---------- */
static const char *const nokia_chars[] = {
    [NK_1 - NK_1] = "1abc",  [NK_2 - NK_1] = "2def", [NK_3 - NK_1] = "3ghi",
    [NK_4 - NK_1] = "4jkl",  [NK_5 - NK_1] = "5mno", [NK_6 - NK_1] = "6pqr",
    [NK_7 - NK_1] = "7stu",  [NK_8 - NK_1] = "8vwx", [NK_9 - NK_1] = "9yz",
    [NK_0 - NK_1] = "0 ",    [NK_DOT - NK_1] = ".,?!",
};

static void tap_nokia_char(char c, bool shift) {
    uint16_t kc;
    bool need_shift = shift;
    if (c >= 'a' && c <= 'z')      kc = KC_A + (c - 'a');
    else if (c >= '1' && c <= '9') kc = KC_1 + (c - '1');
    else if (c == '0')             kc = KC_0;
    else if (c == ' ')             kc = KC_SPC;
    else if (c == '.')             { kc = KC_DOT;  need_shift = false; }
    else if (c == ',')             { kc = KC_COMM; need_shift = false; }
    else if (c == '?')             { kc = KC_SLSH; need_shift = true;  }
    else if (c == '!')             { kc = KC_1;    need_shift = true;  }
    else return;
    /* chu so khong viet hoa: chi ap dung shift cho chu cai */
    if (c >= '0' && c <= '9') need_shift = false;
    if (c == ' ') need_shift = false;
    if (need_shift) register_weak_mods(MOD_BIT(KC_LSFT));
    tap_code(kc);
    if (need_shift) unregister_weak_mods(MOD_BIT(KC_LSFT));
}

static uint16_t nk_last_key   = 0;
static uint8_t  nk_index      = 0;
static uint16_t nk_last_time  = 0;
static bool     nk_last_shift = false;

static void nokia_press(uint16_t keycode) {
    const char *s = nokia_chars[keycode - NK_1];
    uint8_t len = 0;
    while (s[len]) len++;

    bool repeat = (nk_last_key == keycode) && (timer_elapsed(nk_last_time) < NOKIA_MULTITAP_MS);
    if (repeat) {
        nk_index = (nk_index + 1) % len;
        tap_code(KC_BSPC);
    } else {
        nk_index = 0;
        nk_last_shift = is_caps_word_on() || ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT);
        if (get_oneshot_mods() & MOD_MASK_SHIFT) {
            /* one-shot shift se bi tap_code tieu thu; weak mods ben duoi lo viec do */
            clear_oneshot_mods();
        }
    }
    tap_nokia_char(s[nk_index], nk_last_shift);
    nk_last_key  = keycode;
    nk_last_time = timer_read();
}

/* ---------- Tap / Hold cho phim - + ---------- */
static uint16_t th_timer = 0;

/* ---------- Layer cycle: Base -> Numpad -> Media -> Nokia ---------- */
static const uint8_t cycle_layers[] = { L_BASE, L_NUM, L_MEDIA, L_NOKIA };
static uint8_t cycle_idx = 0;

#ifdef OLED_ENABLE
static void oled_track_key(uint16_t keycode, bool pressed);
#endif

/* ---------- Latch / toggle phim bat ky ----------
 * TG_LATCH : bam 1 lan -> cho; bam phim X -> X duoc giu vo thoi han
 *            (nha ra khi bam TG_LATCH lan nua). Bam TG_LATCH khi dang cho
 *            ma chua chon phim -> huy.
 * TGL_xxx  : bam 1 lan = giu phim co dinh, bam lan nua = nha.
 * Chi 1 phim duoc latch tai 1 thoi diem.
 */
static uint16_t latch_target = KC_NO;
static bool     latch_armed  = false;

static void latch_release(void) {
    if (latch_target != KC_NO) {
        unregister_code16(latch_target);
#ifdef OLED_ENABLE
        oled_track_key(latch_target, false);
#endif
        latch_target = KC_NO;
    }
}

static void latch_hold(uint16_t target) {
    latch_release(); /* chi giu 1 phim mot luc */
    register_code16(target);
    latch_target = target;
#ifdef OLED_ENABLE
    oled_track_key(target, true);
#endif
}

static void latch_toggle_fixed(uint16_t target) {
    if (latch_target == target) latch_release();
    else                        latch_hold(target);
}

/* true = phim da xu ly boi latch, khong di theo duong thong thuong nua */
static bool latch_process(uint16_t keycode, keyrecord_t *record) {
    bool pressed = record->event.pressed;

    /* phim dang bi latch giu: nuot ca press lan release */
    if (keycode == latch_target) return true;

    switch (keycode) {
        case TG_LATCH:
            if (pressed) {
                if (latch_target != KC_NO) { latch_release(); latch_armed = false; }
                else                       { latch_armed = !latch_armed; }
            }
            return true;
        case TGL_SPC: if (pressed) latch_toggle_fixed(KC_SPC);  return true;
        case TGL_SFT: if (pressed) latch_toggle_fixed(KC_LSFT); return true;
        case TGL_CTL: if (pressed) latch_toggle_fixed(KC_LCTL); return true;
        case TGL_ALT: if (pressed) latch_toggle_fixed(KC_LALT); return true;
    }

    /* dang cho: phim ke tiep (phim co ban hoac co mod) se bi giu lai */
    if (latch_armed && pressed && keycode != KC_NO && keycode != KC_TRNS &&
        keycode <= QK_MODS_MAX) {
        latch_armed = false;
        latch_hold(keycode);
        return true;
    }
    return false;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    /* phai chay truoc: phim bi latch thi khong gui xuong host theo cach thuong */
    if (latch_process(keycode, record)) return false;
#ifdef OLED_ENABLE
    oled_track_key(keycode, record->event.pressed);
#endif
    switch (keycode) {
        case LCYCLE:
            if (record->event.pressed) {
                cycle_idx = (cycle_idx + 1) % (sizeof(cycle_layers) / sizeof(cycle_layers[0]));
                default_layer_set((layer_state_t)1 << cycle_layers[cycle_idx]);
            }
            return false;

        case SQ_F1F2:
            if (record->event.pressed) { tap_code(KC_F1); tap_code(KC_F2); }
            return false;

        case SQ_F11PU:
            if (record->event.pressed) { tap_code(KC_F11); tap_code(KC_PGUP); }
            return false;

        case SQ_F11PD:
            if (record->event.pressed) { tap_code(KC_F11); tap_code(KC_PGDN); }
            return false;

        case NK_1 ... NK_DOT:
            if (record->event.pressed) nokia_press(keycode);
            return false;

        case TH_MIN:
        case TH_PLS:
            if (record->event.pressed) {
                th_timer = timer_read();
            } else {
                bool hold = timer_elapsed(th_timer) >= TAPPING_TERM;
                if (keycode == TH_MIN) tap_code(hold ? KC_PSLS : KC_PMNS);
                else                   tap_code(hold ? KC_PAST : KC_PPLS);
            }
            return false;
    }
    return true;
}

/* ---------- Man hinh OLED ---------- */
#ifdef OLED_ENABLE
#include OLED_FONT_H /* dung lai font 6x8 de ve chu phong to */

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return OLED_ROTATION_0;
}

static const char *layer_name(uint8_t layer) {
    switch (layer) {
        case L_BASE:  return "BASE";
        case L_FN1:   return "LAYER1";
        case L_NUM:   return "NUMPAD";
        case L_MEDIA: return "MEDIA";
        case L_NOKIA: return "NOKIA";
        case L_FN:    return "FN";
        default:      return "LAYER";
    }
}

/* ----- Doi ma phim thanh ten ngan (toi da 5 ky tu) ----- */
static void key_label(uint16_t kc, char *out) {
    out[0] = 0;
    if (IS_QK_MODS(kc) && (kc & 0xFF) != 0) {
        /* Ctrl+C -> "C+C" ... */
        char *p = out;
        uint8_t m = (kc >> 8) & 0x1F;
        if (m & 0x01 || m & 0x10) { /* ctrl / right ctrl */
            if (m & 0x01 || m & 0x10) *p++ = 'C';
        }
        if (m & 0x02 || m & 0x12) *p++ = 'S';
        if (m & 0x04) *p++ = 'A';
        if (m & 0x08) *p++ = 'G';
        *p++ = '+';
        char sub[8];
        key_label(kc & 0xFF, sub);
        for (uint8_t i = 0; sub[i] && (p - out) < 5; i++) *p++ = sub[i];
        *p = 0;
        return;
    }
    if (IS_QK_MOMENTARY(kc)) {
        uint8_t l = kc & 0x1F;
        if (l == L_FN)       strcpy(out, "FN");
        else if (l == L_FN1) strcpy(out, "FN1");
        else                 strcpy(out, "LAYER");
        return;
    }
    if (kc >= QK_TOGGLE_LAYER && kc <= QK_TOGGLE_LAYER_MAX) { sprintf(out, "TG %d", (int)(kc & 0x1F)); return; }
    if (kc >= QK_TO && kc <= QK_TO_MAX)                     { sprintf(out, "TO %d", (int)(kc & 0x1F)); return; }
    if (kc >= QK_MACRO && kc <= QK_MACRO_MAX) { strcpy(out, "MACRO"); return; }
    if (kc >= KC_A && kc <= KC_Z)            { out[0] = 'A' + (kc - KC_A); out[1] = 0; return; }
    if (kc >= KC_1 && kc <= KC_9)            { out[0] = '1' + (kc - KC_1); out[1] = 0; return; }
    if (kc >= KC_P1 && kc <= KC_P9)          { out[0] = '1' + (kc - KC_P1); out[1] = 0; return; }
    if (kc >= KC_F1 && kc <= KC_F12)         { sprintf(out, "F%d", kc - KC_F1 + 1); return; }
    if (kc >= KC_F13 && kc <= KC_F24)        { sprintf(out, "F%d", kc - KC_F13 + 13); return; }
    switch (kc) {
        case KC_0: case KC_P0:   strcpy(out, "0"); break;
        case KC_PDOT: case KC_DOT: strcpy(out, "."); break;
        case KC_COMM:            strcpy(out, ","); break;
        case KC_PSLS: case KC_SLSH: strcpy(out, "/"); break;
        case KC_PAST:            strcpy(out, "*"); break;
        case KC_PMNS: case KC_MINS: strcpy(out, "-"); break;
        case KC_PPLS:            strcpy(out, "+"); break;
        case KC_EQL:             strcpy(out, "="); break;
        case KC_PENT: case KC_ENT: strcpy(out, "ENTER"); break;
        case KC_ESC:             strcpy(out, "ESC"); break;
        case KC_BSPC:            strcpy(out, "BKSP"); break;
        case KC_TAB:             strcpy(out, "TAB"); break;
        case KC_SPC:             strcpy(out, "SPACE"); break;
        case KC_DEL:             strcpy(out, "DEL"); break;
        case KC_INS:             strcpy(out, "INS"); break;
        case KC_HOME:            strcpy(out, "HOME"); break;
        case KC_END:             strcpy(out, "END"); break;
        case KC_PGUP:            strcpy(out, "PG UP"); break;
        case KC_PGDN:            strcpy(out, "PG DN"); break;
        case KC_UP:              strcpy(out, "UP"); break;
        case KC_DOWN:            strcpy(out, "DOWN"); break;
        case KC_LEFT:            strcpy(out, "LEFT"); break;
        case KC_RGHT:            strcpy(out, "RIGHT"); break;
        case KC_MUTE:            strcpy(out, "MUTE"); break;
        case KC_VOLU:            strcpy(out, "VOL +"); break;
        case KC_VOLD:            strcpy(out, "VOL -"); break;
        case KC_MPLY:            strcpy(out, "PLAY"); break;
        case KC_MNXT:            strcpy(out, "NEXT"); break;
        case KC_MPRV:            strcpy(out, "PREV"); break;
        case KC_CALC:            strcpy(out, "CALC"); break;
        case KC_LSFT: case KC_RSFT: strcpy(out, "SHIFT"); break;
        case KC_LCTL: case KC_RCTL: strcpy(out, "CTRL"); break;
        case KC_LALT: case KC_RALT: strcpy(out, "ALT"); break;
        case KC_LGUI: case KC_RGUI: strcpy(out, "GUI"); break;
        case QK_BOOT:            strcpy(out, "BOOT"); break;
        case QK_REBOOT:          strcpy(out, "RESET"); break;
        case CW_TOGG:            strcpy(out, "CAPSW"); break;
        case LCYCLE:             strcpy(out, "CYCLE"); break;
        case SQ_F1F2:            strcpy(out, "F1 F2"); break;
        case SQ_F11PU:           strcpy(out, "F11 PU"); break;
        case SQ_F11PD:           strcpy(out, "F11 PD"); break;
        case NK_DOT:             strcpy(out, "NK ."); break;
        case TH_MIN:             strcpy(out, "- /"); break;
        case TH_PLS:             strcpy(out, "+ *"); break;
        case TG_LATCH:           strcpy(out, "LATCH"); break;
        case TGL_SPC:            strcpy(out, "SPACE"); break;
        case TGL_SFT:            strcpy(out, "SHIFT"); break;
        case TGL_CTL:            strcpy(out, "CTRL"); break;
        case TGL_ALT:            strcpy(out, "ALT"); break;
        default:
            if (kc >= NK_1 && kc <= NK_0) { sprintf(out, "NK %d", (kc == NK_0) ? 0 : (int)(kc - NK_1 + 1)); }
            else strcpy(out, "KEY");
    }
}

/* ----- Theo doi phim dang bam ----- */
#define HELD_MAX      4
#define SHOW_AFTER_MS 700 /* giu hien ten phim them 0,7 s sau khi nha */
static uint16_t held[HELD_MAX];
static uint8_t  held_n    = 0;
static uint16_t last_kc   = 0;
static uint32_t last_time = 0;
static bool     have_last = false;

static void oled_track_key(uint16_t keycode, bool pressed) {
    if (keycode == KC_NO || keycode == KC_TRNS) return;
    if (pressed) {
        for (uint8_t i = 0; i < held_n; i++)
            if (held[i] == keycode) goto done;
        if (held_n < HELD_MAX) {
            held[held_n++] = keycode;
        } else {
            for (uint8_t i = 1; i < HELD_MAX; i++) held[i - 1] = held[i];
            held[HELD_MAX - 1] = keycode;
        }
    } else {
        for (uint8_t i = 0; i < held_n; i++) {
            if (held[i] == keycode) {
                for (uint8_t j = i + 1; j < held_n; j++) held[j - 1] = held[j];
                held_n--;
                break;
            }
        }
    }
done:
    last_kc   = keycode;
    have_last = true;
    last_time = timer_read32();
}

/* ----- Ve chu phong to: font 5x8 nhan ban s lan ----- */
static void draw_big_char(uint8_t x, uint8_t y, char c, uint8_t s) {
    for (uint8_t col = 0; col < 5; col++) {
        uint8_t bits = pgm_read_byte(&font[((uint8_t)c - OLED_FONT_START) * OLED_FONT_WIDTH + col]);
        for (uint8_t row = 0; row < 8; row++) {
            if (bits & (1 << row)) {
                for (uint8_t dx = 0; dx < s; dx++)
                    for (uint8_t dy = 0; dy < s; dy++) oled_write_pixel(x + col * s + dx, y + row * s + dy, true);
            }
        }
    }
}

static uint8_t text_width(const char *str, uint8_t s) {
    uint8_t len = strlen(str);
    return len ? (uint8_t)(len * 6 * s - s) : 0;
}

/* scale lon nhat (<= max_s) ma chuoi con vua be ngang man hinh */
static uint8_t fit_scale(const char *str, uint8_t max_s) {
    if (!str[0]) return 1;
    uint8_t s = max_s;
    while (s > 1 && text_width(str, s) > OLED_DISPLAY_WIDTH) s--;
    return s;
}

/* ve chuoi canh giua theo chieu ngang, goc tren tai y */
static void draw_big_text(const char *str, uint8_t y, uint8_t s) {
    uint8_t w = text_width(str, s);
    uint8_t x = (w < OLED_DISPLAY_WIDTH) ? (uint8_t)((OLED_DISPLAY_WIDTH - w) / 2) : 0;
    for (uint8_t i = 0; str[i]; i++) draw_big_char(x + i * 6 * s, y, str[i], s);
}

/* ----- Man hinh khi ranh: dung 2 dong chu to -----
 *   dong 1: "MACROPAD15"
 *   dong 2: ten layer dang bat (hoac "LATCH ?" khi dang cho chon phim)
 */
static void oled_draw_idle(void) {
    char line[12];

    strcpy(line, "MACROPAD15");
    draw_big_text(line, 4, fit_scale(line, 2)); /* 10 ky tu -> 16 px cao */

    if (latch_armed) {
        strcpy(line, "LATCH ?");
    } else {
        strncpy(line, layer_name(get_highest_layer(layer_state | default_layer_state)), sizeof(line) - 1);
        line[sizeof(line) - 1] = 0;
    }
    draw_big_text(line, 34, fit_scale(line, 3)); /* 24 px cao */
}

/* ----- Man hinh khi bam phim: ten TAT CA phim dang giu, chu to -----
 * 1 phim: to het man hinh, 2 phim: moi phim 32 px, 3-4 phim: moi phim 16 px.
 */
static void oled_draw_keys(void) {
    uint8_t n     = held_n ? held_n : 1;
    uint8_t row_h = OLED_DISPLAY_HEIGHT / n;
    uint8_t max_s = row_h / 8;
    if (max_s > 6) max_s = 6;

    for (uint8_t i = 0; i < n; i++) {
        /* phim bam sau cung o tren cung */
        uint16_t kc = held_n ? held[held_n - 1 - i] : last_kc;
        char     t[12];
        key_label(kc, t);

        uint8_t s = fit_scale(t, max_s);
        uint8_t y = (uint8_t)(i * row_h + (row_h - 8 * s) / 2);
        draw_big_text(t, y, s);
    }
}

static uint32_t last_sig = 0xFFFFFFFF;

bool oled_task_user(void) {
    bool show_keys = (held_n > 0) || (have_last && timer_elapsed32(last_time) < SHOW_AFTER_MS);

    /* chu ky trang thai: chi ve lai khi co thay doi */
    uint32_t sig;
    if (show_keys) {
        sig = 0x80000000u ^ ((uint32_t)held_n << 16) ^ ((uint32_t)last_kc << 4);
        for (uint8_t i = 0; i < held_n; i++) sig ^= (uint32_t)held[i] * 2654435761u;
    } else {
        uint8_t top = get_highest_layer(layer_state | default_layer_state);
        sig         = (uint32_t)top ^ ((uint32_t)latch_armed << 8) ^ ((uint32_t)(latch_target != KC_NO) << 9);
    }
    if (sig == last_sig) return false;
    last_sig = sig;

    oled_clear();
    if (show_keys) oled_draw_keys();
    else           oled_draw_idle();
    return false;
}
#endif

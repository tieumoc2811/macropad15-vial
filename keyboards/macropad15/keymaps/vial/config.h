#pragma once

/* Vial */
#define VIAL_KEYBOARD_UID {0x4D, 0x50, 0x31, 0x35, 0xA7, 0x3C, 0x19, 0xE2}

/* Giu dong thoi 2 phim nay khi cam USB (hoac bam "Unlock" trong Vial): c0r0 va c1r0 */
#define VIAL_UNLOCK_COMBO_ROWS { 0, 0 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#define DYNAMIC_KEYMAP_LAYER_COUNT 8

/* Thoi gian cho tap/giu cho phim -(/) va +(*) */
#define TAPPING_TERM 200

/* Nokia multitap: bam lien tiep cung phim trong 600 ms de doi ky tu */
#define NOKIA_MULTITAP_MS 600

/* OLED SSD1306 (I2C0): SDA = GP20 (D14), SCL = GP21 (D10) */
#define I2C_DRIVER I2CD0
#define I2C1_SDA_PIN GP20
#define I2C1_SCL_PIN GP21
#define OLED_TIMEOUT 60000
#define OLED_BRIGHTNESS 255
/* Man hinh 128x64 (0.96"). Neu dung man 128x32 thi doi thanh OLED_DISPLAY_128X32 */
#define OLED_DISPLAY_128X64

# Macropad15 - Vial (QMK) cho Pro Micro RP2040

Bo cuc theo anh: 15 phim (3 hang x 5 cot) ben phai + 3 nut xoay EC11 co nut nhan ben trai (1 to o tren, 2 nho o duoi). Cau hinh bang Vial, khong can build lai khi doi keymap/macro.

## 1. Lay file firmware (.uf2)

**Cach A - GitHub Actions (khong cai gi):**
1. Tao repo moi tren GitHub, day toan bo thu muc nay len (giu nguyen `keyboards/` va `.github/`).
2. Vao tab **Actions** -> workflow "Build Vial firmware" -> doi 5-10 phut -> tai artifact `macropad15_vial_uf2`.

**Cach B:** file `macropad15_vial.uf2` build san da bo khoi goi nay vi khong con khop voi ma tran moi; hay build lai bang Cach A.

## 2. Nap firmware
1. Nhan giu nut BOOT tren Pro Micro RP2040, cam USB (hoac bam RESET 2 lan nhanh) -> board hien o dia `RPI-RP2`.
2. Keo file `.uf2` vao o dia do. Board tu khoi dong lai.

## 3. Dung Vial
- Mo app Vial (https://get.vial.today) hoac ban web https://vial.rocks (Chrome/Edge).
- Chon Macropad15. Neu bi khoa (Locked): bam **Unlock** trong Vial, roi giu 2 phim `c0r0` (goc tren trai) va `c1r0` (goc tren phai hang 1) cho den khi mo khoa.
- **Macro chuoi ky tu:** tab *Macros* -> *Add action* -> *Text* -> go chuoi (vd `chipgenni@gmail.com`) -> keo macro (M0..M15) vao phim.
- **F11 + PageUp cung luc (giu F11 roi nhan PgUp):** macro gom *Down F11*, *Down PgUp*, *Up PgUp*, *Up F11* (hoac dung **Combo/Tap Dance** cua Vial). Phim san co o layer 1 chi bam F11 roi PgUp lan luot.
- Doi phim, layer, encoder: keo tha truc tiep, luu ngay.

## 4. Keymap mac dinh
Layer 0 Base (giong ban ESP32-C3) | 1 Layer1 (giong C3) | 2 Numpad | 3 Media | 4 Nokia | 5 FN | 6, 7 trong.
- Layer 0 (doc trai->phai, tren->duoi): Shift M , . / | Up Z X C V | Space MO(1) 3 Down TG(1). Giu MO(1) = tam sang layer 1; bam TG(1) = khoa layer 1.
- Layer 1: V C X Z Up | / . , M Shift | TO(0) [F1,F2] [F11,PgUp] [F11,PgDn] Delete. Cac phim combo bam F11 roi PgUp/PgDn lan luot (khong giu cung luc), y het ban C3.
- Nut nhan encoder (moi layer): ENC1 = LCYCLE (doi layer nen Base -> Numpad -> Media -> Nokia), ENC2 = Backspace, ENC3 = Tab.
- Layer 2 Numpad: phim `-` bam = `-`, giu = `/` ; phim `+` bam = `+`, giu = `*`. Layer 3 Media. Layer 4 Nokia: bam lien tiep cung phim trong 600 ms de doi ky tu (1abc 2def ... `.,?!`), co Caps Word va Shift one-shot. Layer 5 FN: F1..F12, RESET, BOOTLOADER, Mute (giu phim goc tren phai o layer 2-4).
- Nut xoay: to (ENC1) = **layer truoc / ke tiep** (xoay CCW/CW, cung vong Base -> Numpad -> Media -> Nokia; giu FN + xoay = am luong); nho trai (ENC2) = trai/phai; nho phai (ENC3) = len/xuong. Layer Media: ENC2 = bai truoc/sau, ENC3 = PgUp/PgDn.

## 4b. Latch / Toggle phim bat ky (moi)

Them 5 keycode tuy bien (hien thanh **Custom 17..21** trong Vial; `LNEXT`/`LPREV` = **Custom 22/23**):

| Ten trong Vial | shortName | Hanh vi |
|---|---|---|
| Latch Any Key | `LATCH` | Bam 1 lan -> cho; bam phim X bat ky -> X duoc **giu vo thoi han** |
| Toggle Space | `TGSPC` | Bam = giu Space, bam lan nua = nha |
| Toggle Shift | `TGSFT` | Bam = giu Shift, bam lan nua = nha |
| Toggle Ctrl | `TGCTL` | Bam = giu Ctrl, bam lan nua = nha |
| Toggle Alt | `TGALT` | Bam = giu Alt, bam lan nua = nha |

Mac dinh da gan o **layer FN** (giu phim goc tren phai o layer Numpad/Media/Nokia):

```
KC_MUTE   LATCH   TGSPC
  k15      k16     k17     <- 3 nut nhan encoder
```

Cach dung `LATCH` (kieu "Caps Lock nhung cho moi phim"):

1. Bam `LATCH` -> OLED hien `LATCH ?` (dang cho chon phim).
2. Bam phim can giu, vd `Shift` -> Shift duoc giu mai, OLED hien chu to `SHIFT`.
3. Bam `LATCH` lan nua -> nha phim.

Luu y:
- Chi giu **1 phim** mot luc; chon phim khac se nha phim cu.
- Bam lai dung phim dang giu **khong** co tac dung (tranh nha nham).
- Chi latch duoc phim co ban va phim co mod (`Ctrl+C`...); khong latch duoc
  macro / layer / mod-tap (MT, LT) vi cac loai do phai do firmware xu ly theo su kien.
- Bam `LATCH` khi dang cho ma chua chon phim = huy.
- Encoder quay van hoat dong binh thuong khi dang latch.

Muon gan o cho khac: trong Vial mo tab **Custom** -> keo `LATCH` / `TGSPC`...
vao phim bat ky. Sau khi nap firmware moi, neu Vial hien keymap cu thi bam
**Unlock** (2 phim `c0r0` + `c1r0`) va nap `flash_nuke.uf2` de xoa EEPROM.

## 5. Sua code
Sua `keyboards/macropad15/keymaps/vial/keymap.c` (Nokia multitap, layer cycle, tap/hold) roi push len GitHub de build lai.

## Ghi chu
- Ma tran giong ban C3, diode **ROW2COL**: duong hang -> cong tac -> anode diode, **cathode (dau co vach) ve duong cot**. Moi phim 1 diode.
- Phim Pn (doc trai->phai, tren->duoi, n = 0..14) noi vao hang n%4, cot n/4: P0=R0C0, P1=R1C0, P2=R2C0, P3=R3C0, P4=R0C1, P5=R1C1 ... P14=R2C3. O R3C3 de trong.
- 3 nut nhan encoder: ENC1 (to) -> R0, ENC2 (nho trai) -> R1, ENC3 (nho phai) -> R2 (moi cai 1 chan cong tac); 3 chan con lai noi chung, qua 1 diode (anode phia cong tac, cathode ve C4) vao C4.
- Chan: C0..C4 = GP7, GP8, GP29, GP28, GP4; R0..R3 = GP1, GP0, GP2, GP3; encoder (quay): (GP5,GP6), (GP26,GP27), (GP22,GP23).
- Sau khi nap firmware moi (doi ma tran, so layer) nen xoa bo nho EEPROM cua Vial, neu khong Vial van giu keymap cu: nap `flash_nuke.uf2` (Raspberry Pi) roi nap lai file .uf2 cua firmware.
- Neu encoder xoay nguoc chieu: doi `ENCODER_CCW_CW` trong keymap hoac doi pin_a/pin_b trong `keyboard.json`.
- Neu 1 nac nhay 2 buoc: sua `resolution` (4 -> 2) trong `keyboard.json`.

## Man hinh OLED (tuy chon)
- Loai: SSD1306 I2C, 128x64 (mac dinh; doi `OLED_DISPLAY_128X64` thanh `OLED_DISPLAY_128X32` trong `keymaps/vial/config.h`).
- Noi day: VCC -> 3V3, GND -> GND, **SDA -> D14 (GP20)**, **SCL -> D10 (GP21)**. (Nhan D10/D14 theo so do chan SparkFun, doi chieu voi chu in tren board.)
- Man hinh moi (moi nha 2 dong / ten cac phim dang giu): xem muc "Man hinh OLED (tuy chon) - THIET KET moi" o tren.
### Man hinh khi ranh
- Chi hien **ten layer** dang bat (chu lon, giua man hinh), hoac `LATCH ?` khi dang cho chon phim.
- Bam `LCYCLE` (hoac xoay ENC1): chuyen layer va hien ngay ten layer moi, khong hien chu "CYCLE".

### Man hinh khi bam phim
- Giua man hinh: phim vua bam, chu to; **ben canh la chu nho `xN`** = so lan bam lien tiep cung phim do (doi phim khac hoac het 1,2 s thi dem lai tu 1).
- **Goc duoi (phai)**: cac phim dang bi de (toi da 4), chu nho. Muon goc trai: doi `HELD_CORNER_RIGHT` thanh `false` trong `keymap.c`.

### Tinh trong man hinh
- Man hinh giu **mo lien tuc khong tat** (`OLED_TIMEOUT 0` trong `config.h`).
- Giu hien phim vua bam 1,2 giay sau khi nha roi tro ve man ranh.

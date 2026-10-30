#pragma once

#include_next <mcuconf.h>

/* I2C0 cho man hinh OLED (SDA = GP20, SCL = GP21) */
#undef RP_I2C_USE_I2C0
#define RP_I2C_USE_I2C0 TRUE

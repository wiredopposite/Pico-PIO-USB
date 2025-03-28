#pragma once

#include <stdint.h>
#include "pico/stdlib.h"

// Calc CRC5-USB of 11bit data
uint8_t calc_usb_crc5(uint16_t data);
// Calc CRC16-USB of array
uint16_t calc_usb_crc16(const uint8_t *data, uint16_t len);

extern const uint16_t crc16_tbl[256];
static inline uint16_t __time_critical_func(update_usb_crc16)(uint16_t crc, uint8_t data) {
  crc = (crc >> 8) ^ crc16_tbl[(crc ^ data) & 0xff];
  return crc;
}

#ifndef PICO_DEFAULT_TIMER_INSTANCE // not defined in sdk v1
#define PICO_DEFAULT_TIMER_INSTANCE() timer_hw
#endif

// time_us_32() not force inline and may be in flash, implement timestamp ourselves
#define get_time_us_32()  (PICO_DEFAULT_TIMER_INSTANCE()->timerawl)

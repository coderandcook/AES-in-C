#pragma once

uint32_t add_bit32(uint32_t x, uint32_t y);
uint32_t sub_bit32(uint32_t x, uint32_t y);

uint8_t xtime(uint8_t x);
uint8_t mul(uint8_t x, uint8_t y);
int findDeg(uint16_t a);
uint8_t div2(uint8_t divisor, uint16_t dividend, uint8_t *remainder);
uint8_t mulInverse(uint8_t a, uint16_t m);

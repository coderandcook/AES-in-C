#pragma once
/*
struct state{

};
struct key{

};
struct Rcon{

};
struct word{

};
struct expKey{

};
*/

uint8_t add_bit8(uint8_t x, uint8_t y);
uint32_t add_bit32(uint32_t x, uint32_t y);
uint16_t sub_bit16(uint16_t x, uint16_t y);
uint32_t sub_bit32(uint32_t x, uint32_t y);
int find_deg16(uint16_t x);
uint8_t mod_bit(uint16_t x);

uint8_t xtime(uint8_t x);
uint8_t mul(uint8_t x, uint8_t y);
int findDeg(uint16_t a);
uint8_t mulInverse(uint8_t a, uint16_t m);
uint8_t div2(uint8_t divisor, uint16_t dividend, uint8_t *remainder);
//division by shifts

int isEqual8(uint8_t x, uint8_t y);
uint8_t sub_bit2(uint8_t x, uint8_t y);

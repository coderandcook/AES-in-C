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


uint8_t mul_bit8(uint8_t x, uint8_t y);
//division by shifts

int isEqual8(uint8_t x, uint8_t y);



uint8_t sub_bit2(uint8_t x, uint8_t y);

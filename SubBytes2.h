#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

uint8_t crossMul_b2(uint8_t x, uint8_t y);
uint8_t crossMul_b(uint8_t x, uint8_t y);
uint8_t SubBytes_b(uint8_t x);
uint8_t SubBytes_table(uint8_t x);
void SubState32(struct state2 *in);

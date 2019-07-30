#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

uint8_t crossMul_b(uint8_t x, uint8_t y);
uint8_t SubBytes_b(uint8_t x);
void SubState_b(const struct state *input, struct state *output);

void SubState32(struct state2 *in);

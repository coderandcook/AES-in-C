#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

uint32_t getColumn32(const struct state2 *s, int col);
void setColumn32(struct state2 *s, int col_num, uint32_t col);

uint32_t mul32(uint32_t x, uint32_t y);
void MixColumns(struct state2 *s);

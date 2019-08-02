#include <stdint.h>
#pragma once

struct state2{
  uint32_t block[4];
};
void ShiftRows(struct state2 *s);
void printState(struct state2 *s);

//currently unused, but should be kept
//void transposeState(struct state2 *s);

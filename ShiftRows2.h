#include <stdint.h>
#pragma once

struct state2{
  uint32_t block[4];
};
void ShiftRows(struct state2 *s);
void printState32(struct state2 s);
void transposeState(struct state2 *s);

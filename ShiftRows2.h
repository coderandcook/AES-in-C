#include <stdint.h>
#pragma once

struct state{
  uint8_t block[4][4];
};
struct state* newState();
void clearState(struct state* s);
void copyState(const struct state *src, struct state *dst);
void setState(int row, int col, uint8_t new, struct state *s);
void shiftLeft(struct state* s, int row, int rounds);//no need
void printRow(const struct state* s, int row);
void printState(const struct state* s);
void ShiftRows(struct state* s);
int isEqualByte(const uint8_t num, const uint8_t num2);
int isEqualState(const struct state* s1, const struct state* s2);

void shiftLeft2(struct state* s, int row, int rounds);
void ShiftRows2(struct state* s);


struct state2{
  uint32_t block[4];
};
void clearState2(struct state2 *s);
void copyState2(const struct state2 *src, struct state2 *dst);
void setState_row(int row, uint32_t new, struct state2 *s);
void setState_col(int col, uint32_t new, struct state2 *s);

void ShiftRows32(struct state2 *s);

void printState32(struct state2 s);
void transposeState(struct state2 *s);

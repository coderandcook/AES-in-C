#include <stdint.h>
#pragma once

struct state{
  uint8_t block[4][4];
};


struct state* newState();
void clearState(struct state* s);
void copyState(const struct state *src, struct state *dst);

void clearFourBytes(uint8_t *words);
void setState(int row, int col, uint8_t new, struct state *s);
void shiftLeft(struct state* s, int row, int rounds);

void printRow(const struct state* s, int row);

void printState(const struct state* s);
void ShiftRows(struct state* s);

int isEqualByte(const uint8_t num, const uint8_t num2);
int isEqualState(const struct state* s1, const struct state* s2);

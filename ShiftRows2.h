#include <stdint.h>
#pragma once

struct state{
  uint8_t block[4][4];
};


struct state* newState();

void setState(int row, int col, uint8_t new, struct state *s);

void ShiftRows(struct state* s);

int isEqualByte(uint8_t num, uint8_t num2);
int isEqualState(struct state* s1, struct state* s2);

void shiftLeft(struct state* s, int row, int rounds);

void printRow(const struct state* s, int row);

void printState(const struct state* s);

void clearState(struct state* s);
void clearFourBytes(uint8_t *arr);

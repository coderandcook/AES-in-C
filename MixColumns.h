#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

void clearCol(uint8_t *col);
void setColumns(const struct state* s, int col, uint8_t* column);
void shiftMultiplier(uint8_t *multiplier);

//uint8_t mulTwo(uint8_t colNum);
//uint8_t mulThree(uint8_t colNum);
uint8_t mulWord(uint8_t multiplicand, uint8_t multiplier);

//updates column
uint8_t colMultiply(const uint8_t *col, const uint8_t *multiplier);
int isEqualCol(const uint8_t *col, const uint8_t *col2);
void MixColumns(struct state* s);

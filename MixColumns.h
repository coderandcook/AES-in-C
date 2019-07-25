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




uint8_t mulWord_b(uint8_t x, uint8_t y);
uint8_t colMultiply_b(uint8_t *col, uint8_t *multiplier);
void MixColumns_b(struct state* s);

uint32_t getColumn32(const struct state2 *s, int col);
uint32_t mul32(uint32_t x, uint32_t y);
uint32_t colMultiply32(uint32_t x, uint32_t y);
//void MixColumns32(const struct state2 *s1, struct state2 *s2);
void MixColumns32(struct state2 *s);

void setColumn32(struct state2 *s, int col_num, uint32_t col);

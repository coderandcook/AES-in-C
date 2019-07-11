#include <stdlib.h>
#include "ShiftRows2.h"
//uint8_t multiplier[] = {2, 3, 1, 1};


void setColumns(const struct state* s, int col, uint8_t* column);
void shiftMultiplier(uint8_t *multiplier);

uint8_t mulTwo(uint8_t colNum);
uint8_t mulThree(uint8_t colNum);

//updates column
uint8_t colMultiply(uint8_t *col, uint8_t *multiplier);


int isEqualCol(const uint8_t *col, const uint8_t *col2);
void clearCol(uint8_t *col);
void MixColumns(struct state* s);

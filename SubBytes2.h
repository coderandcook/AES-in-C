#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"
/*
struct state{
  uint8_t block[4][4];
};*/

//use row, col of the state to convert a uint8_t to int* poly
void setStateToPoly(const struct state *s, int row, int col, int *poly);
//use row, col of the original state to convert int* poly back to uint8_t
void setPolyToState(struct state *s, int row, int col, const int *poly);
void setWordToPoly(const uint8_t *bytes, int word, int *poly);
void setPolyToWord(uint8_t *bytes, int word, const int *poly);

//a function that loops around all members of the state block to do the SubBytes operation
void SubState(const struct state *input, struct state *output);

void crossMul(const int *multiplicand, int *multiplier, int *output);

void CopyWord(const uint8_t *src, uint8_t *dst);

void ClearWord(uint8_t *word);

void shift(int *poly);
int SubBytes(const int *input, int *output);

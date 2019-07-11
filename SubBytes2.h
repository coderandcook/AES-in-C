#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

//use row, col of the state to convert a uint8_t to int* poly
void setStateToPoly(const struct state *s, int row, int col, int *poly);
//use row, col of the original state to convert int* poly back to uint8_t
void setPolyToState(struct state *s, int row, int col, const int *poly);
void setWordToPoly(const uint8_t *words, int word, int *poly);

void ClearWord(uint8_t *word);
void CopyWord(const uint8_t *src, uint8_t *dst);

void setPolyToWord(uint8_t *words, int i, const int *poly);
void shift(int *poly);
void crossMul(const int *multiplicand, int *multiplier, int *output);
int SubBytes(const int *input, int *output);
//a function that loops around all members of the state block to do the SubBytes operation
void SubState(const struct state *input, struct state *output);

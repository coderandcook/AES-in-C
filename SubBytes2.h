#pragma once
#include <stdlib.h>
#include "ShiftRows2.h"

void ClearWord(uint8_t *word);
void CopyWord(const uint8_t *src, uint8_t *dst);
//use row, col of the state to convert a uint8_t to int* poly
void setStateToPoly(const struct state *s, int row, int col, int *poly);
//use row, col of the original state to convert int* poly back to uint8_t
void setPolyToState(struct state *s, int row, int col, const int *poly);
void setStateToWord(const struct state *s, int row, uint8_t *words);
void setWordToState(struct state *s, int row, const uint8_t *words);
void setWordToPoly(const uint8_t *words, int word, int *poly);

void setPolyToWord(uint8_t *words, int i, const int *poly);
void shift(int *poly);
void crossMul(const int *multiplicand, int *multiplier, int *output);
int SubBytes(const int *input, int *output);
//a function that loops around all members of the state block to do the SubBytes operation
void SubState(const struct state *input, struct state *output);


uint8_t crossMul_b(uint8_t x, uint8_t y);
uint8_t SubBytes_b(uint8_t x);
void SubState_b(const struct state *input, struct state *output);

//void SubState32(const struct state2 *in, struct state2 *out);
void SubState32(struct state2 *in);

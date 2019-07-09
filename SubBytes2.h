#include <stdlib.h>
#include "ShiftRows2.h"
/*
struct state{
  uint8_t block[4][4];
};*/

//use row, col of the state to convert a uint8_t to int* poly
void setStateToPoly(struct state *s, int row, int col, int *poly);
//use row, col of the original state to convert int* poly back to uint8_t
void setPolyToState(struct state *s, int row, int col, int *poly);
void setWordToPoly(uint8_t *bytes, int word, int *poly);
void setPolyToWord(uint8_t *bytes, int word, int *poly);

//a function that loops around all members of the state block to do the SubBytes operation
void SubState(struct state *input, struct state *output);

void crossMul(int *multiplicand, int *multiplier, int *output);

void CopyWord(uint8_t *bytes1, uint8_t *bytes2);
void ClearWord(uint8_t *word);

void shift(int *poly);
int SubBytes(int *input, int *output);

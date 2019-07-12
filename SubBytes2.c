//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "ShiftRows2.h"
#include "shifter.h"

void ClearWord(uint8_t *word){
  int i;
  for(i=0; i<4; i++) word[i] = 0;
}
void CopyWord(const uint8_t *src, uint8_t *dst){
  ClearWord(dst);
  int i;
  for(i=0; i<4; i++) dst[i] = src[i];
}
void setStateToPoly(const struct state *s, int row, int col, int *poly){
  setPoly(s->block[row][col],poly);
}
void setPolyToState(struct state *s, int row, int col, const int *poly){
  s->block[row][col] = getInt(poly);
}
void setStateToWord(const struct state *s, int row, uint8_t *words){
  ClearWord(words);
  int i;
  for(i=0; i<4; i++)words[i] = s->block[row][i];
}
void setWordToState(struct state *s, int row, const uint8_t *words){
  int i;
  for(i=0; i<4; i++) s->block[row][i] = words[i];
}
void setWordToPoly(const uint8_t *words, int word, int *poly){
  setPoly(words[word],poly);
}

void setPolyToWord(uint8_t *words, int i, const int *poly){
  words[i] = getInt(poly);
}

void shift(int *poly){//shift right
  rshiftPoly(poly,8,1);
}

void crossMul(const int *multiplicand, int *multiplier, int *output){
  clear8(output);
  int i;
  for(i=0; i<8; i++){
    int temp=0;
    int k;
    for(k=0; k<8; k++){
      temp+=multiplier[k]*multiplicand[k];
    }
    output[i] = temp & 1;
    shift(multiplier);
  }
}
int SubBytes(const int *input, int *output){
  const int m[] = {1,0,0,0,1,1,0,1,1};
  int arr_result[8];
  //take multiplicativ inverse of input
  mulInverse(m, input, arr_result);
  //crosswise multiplication
  int multiplier[] = {1,1,1,1,1,0,0,0};
  crossMul(arr_result,multiplier,output);
  //crosswise addition
  int added[]={0,1,1,0,0,0,1,1};
  addPoly(output, added);
  return getInt(output);
}

void SubState(const struct state *input, struct state *output){
  int temp[8];
  int temp2[8];

  int i;
  for(i=0; i<4; i++){
    int k;
    for(k=0; k<4; k++){
      setStateToPoly(input,i,k,temp);
      SubBytes(temp,temp2);
      setPolyToState(output,i,k,temp2);
    }
  }
}

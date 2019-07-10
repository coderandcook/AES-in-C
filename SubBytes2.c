//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "ShiftRows2.h"

void setStateToPoly(const struct state *s, int row, int col, int *poly){
  //int i;
  uint8_t temp = s->block[row][col];
  setPoly(temp,poly);
}
void setPolyToState(struct state *s, int row, int col, const int *poly){
  int temp = getInt(poly);
  s->block[row][col] = temp;
}
void setWordToPoly(const uint8_t *bytes, int word, int *poly){
  uint8_t temp = bytes[word];
  setPoly(temp,poly);
}
void CopyWord(const uint8_t *src, uint8_t *dst){
  int i;
  for(i=0; i<4; i++) dst[i] = src[i];
}

void ClearWord(uint8_t *word){
  int i;
  for(i=0; i<4; i++) word[i] = 0;
}

void setPolyToWord(uint8_t *bytes, int word, const int *poly){
  uint8_t v = getInt(poly);
  bytes[word] = v;
}


void shift(int *poly){
  int temp, i;
  temp = poly[7];
  for(i=7; i>0; i--){
    poly[i] = poly[i-1];
  }
  poly[i] = temp;
}

void crossMul(const int *multiplicand, int *multiplier, int *output){
  int i;

  for(i=0; i<8; i++){
    int temp=0;
    int k;
    for(k=0; k<8; k++){
      temp+=multiplier[k]*multiplicand[k];
      //for each k, temp+= multiplier[k]*input[k];
    }

    temp &= 1;
    output[i] = temp;
    //shift multiplier
    shift(multiplier);
  }

}
int SubBytes(const int *input, int *output){
  const int m[] = {1,0,0,0,1,1,0,1,1};
  int arr_result[8];

  //take multiplicativ inverse of input
  mulInverse(m, input, arr_result);


  //crosswise multiplication
  int temp[8]; copy8(arr_result, temp);
  int multiplier[] = {1,1,1,1,1,0,0,0};
  crossMul(temp, multiplier, output);

  //crosswise addition
  int added[]={0,1,1,0,0,0,1,1};
  addPoly(output, added);

  return getInt(output);
}

void SubState(const struct state *input, struct state *output){
  int i,k;
  int temp[8]; //clear8(temp);
  int temp2[8];

  for(i=0; i<4; i++){
    for(k=0; k<4; k++){
      clear8(temp);
      clear8(temp2);
      setStateToPoly(input,i,k,temp);
      SubBytes(temp,temp2);
      setPolyToState(output,i,k,temp2);
    }
  }

}

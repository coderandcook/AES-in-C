//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "ShiftRows2.h"

void setStateToPoly(struct state *s, int row, int col, int *poly){
  //int i;
  uint8_t temp = s->block[row][col];
  setPoly(temp,poly);
}
void setPolyToState(struct state *s, int row, int col, int *poly){
  int temp = setInt(poly);
  s->block[row][col] = temp;
}


void shift(int *poly){
  int temp, i;
  temp = poly[7];
  for(i=7; i>0; i--){
    poly[i] = poly[i-1];
  }
  poly[i] = temp;
}

void crossMul(int *multiplicand, int *multiplier, int *output){
  int i, k;
  int temp;

  for(i=0; i<8; i++){
    temp=0;
    for(k=0; k<8; k++){
      temp+=multiplier[k]*multiplicand[k];
      //for each k, temp+= multiplier[k]*input[k];
    }
    //printf("%d", temp);
    if(temp>=0) temp = temp%2;
    else if(temp==-1) temp=1;
    output[i] = temp;
    //shift multiplier
    shift(multiplier);
  }

}
int SubBytes(int *input, int *output){
  int dec_result = 0;
  int m[] = {1,0,0,0,1,1,0,1,1};
  int arr_result[8]; clear8(arr_result);

  //take mod of input
  dec_result = mod(m, input, arr_result);
  //copy(arr_result, output);


  //crosswise multiplication
  int temp[8]; copy8(arr_result, temp);
  int multiplier[] = {1,1,1,1,1,0,0,0};
  crossMul(temp, multiplier, output);


  //crosswise addition
  int added[]={0,1,1,0,0,0,1,1};
  addPoly(output, added);

  dec_result = setInt(output);

  return dec_result;
}

void SubState(struct state *input, struct state *output){
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

//additon
#include <stdio.h>
#include <math.h>
#include "SubBytes2.h"
//#include "mod3.c"

void shift(int *poly){
  int temp, i;
  temp = poly[7];
  for(i=7; i>0; i--){
    poly[i] = poly[i-1];
  }
  poly[i] = temp;
}

void crossMul(int *input, int *output){
  int i, k;
  int temp;
  int multiplier[] = {1,1,1,1,1,0,0,0};

  for(i=0; i<8; i++){
    for(k=0; k<8; k++) printf("%d", multiplier[k]);
    printf("\n");
    temp=0;
    for(k=0; k<8; k++){
      temp+=multiplier[k]*input[k];
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

/*
int SubBytes(int *input, int *output){
  int i;
  int dec_result = 0;

  //take mod of input
  int m[] = {1,0,0,0,1,1,0,1,1};
  int q[8]; clear(q);
  int rem[8]; clear(rem);
  int arr_result[8]; clear(arr_result);
  dec_result = mod(m, input, q, rem, arr_result);

  //crosswise multiplication
  int temp[8]; copy(arr_result, temp);
  int multiplier[] = {1,1,1,1,1,0,0,0};

  mulPoly(temp, multiplier);
  for(i=0; i<8; i++) printf("%d", temp[i]);
  printf("\n");

  //crosswise addition


  return dec_result;
}
*/

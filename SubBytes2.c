//additon
#include <stdio.h>
#include <math.h>
#include "SubBytes2.h"
#include "mod3.c"

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
  int arr_result[8]; clear(arr_result);

  //take mod of input
  dec_result = mod(m, input, arr_result);
  //copy(arr_result, output);


  //crosswise multiplication
  int temp[8]; copy(arr_result, temp);
  int multiplier[] = {1,1,1,1,1,0,0,0};
  crossMul(temp, multiplier, output);


  //crosswise addition
  int added[]={0,1,1,0,0,0,1,1};
  addPoly(output, added);

  dec_result = setInt(output);

  return dec_result;
}

#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "SubBytes2.h"

int InvSubBytes(const int *input, int *output){
  int m[] = {1,0,0,0,1,1,0,1,1};
  int temp[8]; copy8(input,temp);
  int temp2[8];

  //crosswise multiplication
  int multiplier[] = {0,1,0,1,0,0,1,0};
  crossMul(temp,multiplier,temp2);

  //crosswise addition
  int added[]={0,0,0,0,0,1,0,1};
  addPoly(temp2,added);

  //mulInverse
  mulInverse(m,temp2,output);

  return getInt(output);
}

void InvSubState(const struct state *input, struct state *output){
  int i,k;
  int temp[8];
  int temp2[8];

  for(i=0; i<4; i++){
    for(k=0; k<4; k++){
      setStateToPoly(input,i,k,temp);
      InvSubBytes(temp,temp2);
      setPolyToState(output,i,k,temp2);
    }
  }
}

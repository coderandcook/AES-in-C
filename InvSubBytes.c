#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "SubBytes2.h"

int InvSubBytes(const int *input, int *output){
  int m[] = {1,0,0,0,1,1,0,1,1};
  //crosswise multiplication
  int multiplier[] = {0,1,0,1,0,0,1,0};
  int temp2[8];
  crossMul(input,multiplier,temp2);
  //crosswise addition
  int added[]={0,0,0,0,0,1,0,1};
  addPoly(temp2,added);

  mulInverse(m,temp2,output);
  return getInt(output);
}

void InvSubState(const struct state *input, struct state *output){
  int temp[8];

  int i;
  for(i=0; i<4; i++){
    int k;
    for(k=0; k<4; k++){
      setStateToPoly(input,i,k,temp);
      InvSubBytes(temp,temp);
      setPolyToState(output,i,k,temp);
    }
  }
}

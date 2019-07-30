#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "SubBytes2.h"
#include "InvSubBytes.h"
#include "bit.h"

/*
int InvSubBytes(const int *input, int *output){
  //crosswise multiplication
  int multiplier[] = {0,1,0,1,0,0,1,0};
  int temp2[8];
  crossMul(input,multiplier,temp2);
  //crosswise addition
  int added[]={0,0,0,0,0,1,0,1};
  addPoly(temp2,added);

  int m[] = {1,0,0,0,1,1,0,1,1};
  mulInverse(m,temp2,output);
  return getInt(output);
}

void InvSubState(const struct state *input, struct state *output){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      int temp[8];
      setStateToPoly(input,i,k,temp);
      InvSubBytes(temp,temp);
      setPolyToState(output,i,k,temp);
    }
  }
}*/

//use crossMul_b from SubBytes2.c
uint8_t InvSubBytes_b(uint8_t x){
  uint8_t temp_res = 0;
  uint8_t multiplier = 0x52;
  temp_res = crossMul_b(x,multiplier);

  uint8_t a = 0x05;
  temp_res ^= a;

  return mulInverse(temp_res,0x11b);
}
void InvSubState_b(struct state *input, struct state *output){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) output->block[i][k] = InvSubBytes_b(input->block[i][k]);
  }
}

//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "poly.h"
#include "div_poly.h"
#include "div_generic.h"
#include "mod3.h"
#include "ShiftRows2.h"
#include "shifter.h"
#include "bit.h"
#include "SubBytes2.h"

uint8_t crossMul_b(uint8_t x, uint8_t y){
  uint8_t result=0;
  for(int i=0; i<8; i++){//travers all bits in x, shift y
    uint8_t temp = x&y; //printf("temp = %x\n",temp);
    //printf("temp = %x\n",temp);
    uint8_t bit=0;
    for(int k=0; k<8; k++){//XOR bits in x
      uint8_t sbit = temp>>(7-k);
      temp = temp^(sbit<<(7-k));
      bit^=sbit;
    }
    //printf("bit = %x\n",bit);
    result ^= bit<<(7-i); //printf("result = %x\n",result);
    y = rshift_b8(y,1);
  }
  return result;
}
uint8_t SubBytes_b(uint8_t x){
  uint8_t temp_res=0;
  //mulInverse
  temp_res = mulInverse(x,0x11b);//
  //printf("x = %x   temp_res = %x   mulInverse2(x) = %x\n",x,temp_res,mulInverse2(x,0x11b));
  //crossMul
  uint8_t multiplier = 0xf8;
  temp_res = crossMul_b(temp_res, multiplier);
  //addition
  return temp_res ^ 0x63;
}
void SubState_b(const struct state *input, struct state *output){
  //copyState(input,)
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      output->block[i][k] = SubBytes_b(input->block[i][k]);
    }
  }
}
void SubState32(struct state2 *in){//out
  for(int i=0; i<4; i++){
#if 1
    uint32_t temp = in->block[i];
    uint32_t t0 = SubBytes_b(temp>>24);
    uint32_t t1 = SubBytes_b(temp>>16);
    uint32_t t2 = SubBytes_b(temp>>8);
    uint32_t t3 = SubBytes_b(temp);
    in->block[i] = (t0<<24)|(t1<<16)|(t2<<8)|t3;
#else
    for(int k=0; k<4; k++){
      uint32_t temp = temp_s.block[i]>>(32-(k+1)*8);
      temp = SubBytes_b(temp);
      in->block[i] ^= temp<<(32-(k+1)*8);
    }
#endif
  }
}

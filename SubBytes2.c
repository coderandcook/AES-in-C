//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#include "shifter.h"
#include "bit.h"
#include "SubBytes2.h"

uint8_t crossMul_b2(uint8_t x, uint8_t y){
  uint8_t result = 0;
  for(int i=0; i<8; i++){
    uint8_t t0 = mul(x,y);
    //XOR t0
    uint8_t t1 = 0;
    for(int k=0; k<8; k++){
      t1 ^= (t0>>(7-k))&1;
    }
    result ^= t1<<(7-i);
    y = rshift_b8(y,1); //printf("y = %x\n",y);
  }
  return result;
}

uint8_t crossMul_b(uint8_t x, uint8_t y){
  uint8_t result=0;
  for(int i=0; i<8; i++){
    uint8_t temp = x&y;
    uint8_t bit=0;
    for(int k=0; k<8; k++){//XOR bits in x
      uint8_t sbit = temp>>(7-k);
      temp = temp^(sbit<<(7-k));
      bit^=sbit;
    }
    result ^= bit<<(7-i);
    y = rshift_b8(y,1);
  }
  return result;
}

uint8_t SubBytes_b(uint8_t x){
  uint8_t temp_res=0;
  //mulInverse
  temp_res = mulInverse(x,0x11b);
  uint8_t multiplier = 0xf8;
  temp_res = crossMul_b(temp_res, multiplier);
  //addition
  return temp_res ^ 0x63;
}
void SubState32(struct state2 *in){//out
  for(int i=0; i<4; i++){
    uint32_t temp = in->block[i];
    uint32_t t0 = SubBytes_b(temp>>24);
    uint32_t t1 = SubBytes_b(temp>>16);
    uint32_t t2 = SubBytes_b(temp>>8);
    uint32_t t3 = SubBytes_b(temp);
    in->block[i] = (t0<<24)|(t1<<16)|(t2<<8)|t3;
  }
}

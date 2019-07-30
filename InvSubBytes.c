#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "poly.h"
#include "div_poly.h"
#include "mod3.h"
#include "SubBytes2.h"
#include "InvSubBytes.h"
#include "bit.h"

//use crossMul_b from SubBytes2.c
uint8_t InvSubBytes_b(uint8_t x){
  uint8_t temp_res = 0;
  uint8_t multiplier = 0x52;
  temp_res = crossMul_b(x,multiplier);

  uint8_t a = 0x05;
  temp_res ^= a;

  return mulInverse(temp_res,0x11b);
}

void InvSubState32(struct state2 *s){
  for(int i=0; i<4; i++){
    uint32_t temp = s->block[i];
    uint32_t t0 = InvSubBytes_b(temp>>24);
    uint32_t t1 = InvSubBytes_b(temp>>16);
    uint32_t t2 = InvSubBytes_b(temp>>8);
    uint32_t t3 = InvSubBytes_b(temp);
    s->block[i] = (t0<<24)|(t1<<16)|(t2<<8)|t3;
  }
}

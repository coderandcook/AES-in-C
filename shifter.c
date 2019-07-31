#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shifter.h"

uint8_t rshift8(uint8_t x, int num){
  for(int i=0; i<num; i++){
    uint8_t t0 = x&1;
    x = x>>1;
    x ^= t0<<7;
  }
  return x;
}
uint32_t rshift32(uint32_t x, int num){
  for(int i=0; i<num; i++){
    uint32_t t = x&0xff;
    x = x>>8;
    x ^= t<<24;
  }
  return x;
}

uint32_t lshift32(uint32_t x, int num){
  int shift_num = num*8;
  //shift 32bits
  uint32_t temp = x>>(32-shift_num);
  uint32_t temp2 = temp<<(32-shift_num);
  x ^= temp2;
  x = x<<shift_num;
  x ^= temp;
  return x;
}

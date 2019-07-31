#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shifter.h"

uint8_t rshift_b8(uint8_t x, int num){
  uint8_t temp = x<<(8-num);
  uint8_t temp2 = temp>>(8-num);
  x = x^temp2;
  x = x>>num;
  x = x^temp;
  return x;
}


uint32_t rshift32(uint32_t x, int num){
  int shift_num = num*8;
  uint32_t temp = x<<(32-shift_num);
  uint32_t temp2 = x>>(32-shift_num);
  x ^=temp2;
  x = x>>shift_num;
  x ^= temp;
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

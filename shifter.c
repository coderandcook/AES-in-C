#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "shifter.h"

/*
uint8_t rshift8(uint8_t x, int num){
  for(int i=0; i<num; i++){
    uint8_t t0 = x&1;
    x = x>>1;
    x ^= t0<<7;
  }
  return x;
}
*/
uint32_t rotR1(uint32_t x){
  uint32_t t = x&0xff;
  x >>= 8;
  return x|(t<<24);
}
uint32_t rotR2(uint32_t x){
  uint32_t t = x&0xffff;
  x >>= 16;
  return x|(t<<16);
}
uint32_t rotR3(uint32_t x){
  uint32_t t = x&0xffffff;
  x >>= 24;
  return x|(t<<8);
}



uint32_t rotL1(uint32_t x){
  uint32_t t = x&0xff000000;
  x <<= 8;
  return x|(t>>24);
}
uint32_t rotL2(uint32_t x){
  uint32_t t = x&0xffff0000;
  x <<= 16;
  return x|(t>>16);
}
uint32_t rotL3(uint32_t x){
  uint32_t t = x&0xffffff00;
  x <<= 24;
  return x|(t>>8);
}




/*
uint32_t rshift32(uint32_t x, int num){
  //if else
  for(int i=0; i<num; i++){
    uint32_t t = x&0xff;
    x >>= 8;
    x |= t<<24;
  }
  return x;
}
*/

/*
uint32_t lshift32(uint32_t x, int num){
  for(int i=0; i<num; i++){
    uint32_t t = x&0xff000000;
    x <<= 8;
    x |= t>>24;
  }
  return x;
}
*/

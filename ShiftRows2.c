#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "ShiftRows2.h"
#include "shifter.h"
#include "SubBytes2.h"

void ShiftRows(struct state2 *s){
  s->block[1] = rotL1(s->block[1]);
  s->block[2] = rotL2(s->block[2]);
  s->block[3] = rotL3(s->block[3]);
}
void printState(struct state2 *s){
  for(int i=0; i<4; i++) printf("%x\n",s->block[i]);
}

//currently unused, but should be kept
/*
void transposeState(struct state2 *s){
  uint32_t final[4] = {0};
  for(int i=0; i<4; i++){
    uint32_t t0 = (s->block[i]>>24)<<24;
    uint32_t t1 = (s->block[i]>>16)<<24;
    uint32_t t2 = (s->block[i]>>8)<<24;
    uint32_t t3 = (s->block[i])<<24;
    final[0] |= t0>>8*i;
    final[1] |= t1>>8*i;
    final[2] |= t2>>8*i;
    final[3] |= t3>>8*i;
  }
  for(int i=0; i<4; i++) s->block[i] = final[i];
}*/

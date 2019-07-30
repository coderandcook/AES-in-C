#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KeyExpansion.h"
#include "ShiftRows2.h"
#include "AddRoundKey3.h"
#include "SubBytes2.h"
#include "MixColumns.h"
#include "cipher.h"

void cipher(const uint8_t *in, uint8_t *out, const struct expKey *ekey){
  ClearWord(out);
  int in_count=0, out_count=0;
  //convert in(length of 4*4) to state
  //struct state *s = newState();
  struct state s;
  clearState(&s);
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) setState(k,i,in[in_count++],&s);
  }
  //first addroundkey operation i=0
  AddRoundKey_generic(&s,ekey,0);//<-change this for ekey
  //for i=1 to i=9, perform SubBytes, ShiftRows, MixColumns, AddRoundKey
  //i=1
  for(int i=1; i<11; i++){
    SubState(&s,&s);
    ShiftRows(&s);
    if(i!=10) MixColumns(&s);
    AddRoundKey_generic(&s,ekey,i*4);
  }
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) out[out_count++] = s.block[k][i];
  }
  //free
}
void cipher_b(const uint8_t *in, uint8_t *out, const struct expKey *ekey){
  ClearWord(out);
  int in_count=0, out_count=0;
  struct state s;
  clearState(&s);
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) setState(k,i,in[in_count++],&s);
  }
  AddRoundKey_generic(&s,ekey,0);
  for(int i=1; i<11; i++){
    SubState_b(&s,&s);
    ShiftRows2(&s);
    if(i!=10)MixColumns_b(&s);
    AddRoundKey_generic(&s,ekey,i*4);
  }
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) out[out_count++] = s.block[k][i];
  }
}

void cipher32(const uint32_t *in, uint32_t *out, struct expKey32 ekey){
  for(int i=0; i<4; i++)out[i] = 0;
  struct state2 s; clearState2(&s);
  //adjust to input format in the official aes pdf
  for(int i=0; i<4; i++)s.block[i] = in[i];
  transposeState(&s);
  //cipher operation
  AddRoundKey32(&s,ekey,0);
  for(int i=1; i<11; i++){
    SubState32(&s);
    ShiftRows32(&s);
    if(i!=10)MixColumns32(&s);
    AddRoundKey32(&s,ekey,i*4);
  }
  //adjust to input format in the official aes pdf
  transposeState(&s);
  for(int i=0; i<4; i++)out[i] = s.block[i];
}


void cipher32_b(const uint32_t *in, uint32_t *out, struct expKey32 ekey){
  struct state2 s;

  for(int i=0; i<4; i++)s.block[i] = in[i];
  AddRoundKey32(&s,ekey,0);

  for(int i=1; i<11; i++){
    SubState32(&s);
    ShiftRows32(&s);//edit shiftrows
    if(i!=10)MixColumns32(&s);
    AddRoundKey32(&s,ekey,i*4);
  }
  for(int i=0; i<4; i++)out[i] = s.block[i];
}

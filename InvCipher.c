#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#include "KeyExpansion.h"
#include "AddRoundKey3.h"
#include "InvShiftRows.h"
#include "InvMixColumns.h"
#include "InvSubBytes.h"
#include "InvCipher.h"

void invCipher(const uint8_t *in, uint8_t *out, const struct expKey *ekey){
  ClearWord(out);
  int k,count=0,out_count=0;
  //create a state and set it to in
  struct state s;
  clearState(&s);
  int i;
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) setState(k,i,in[count++],&s);
  }
  i=10;
  AddRoundKey_generic(&s,ekey,i*4);
  //for i=10 to i=1
  //when i=1, don't do mixcolumns
  for(i=9; i>=0; i--){
    InvShiftRows(&s);
    InvSubState(&s,&s);
    AddRoundKey_generic(&s,ekey,i*4);
    if(i!=0) InvMixColumns(&s);
  }
  //set out to state
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) out[out_count++] = s.block[k][i];
  }
}
void invCipher_b(const uint8_t *in, uint8_t *out, const struct expKey *ekey){
  ClearWord(out);
  int i, count=0,out_count=0;
  //create a state and set it to in
  struct state s;
  clearState(&s);
  for(i=0; i<4; i++){
    for(int k=0; k<4; k++) setState(k,i,in[count++],&s);
  }
  i=10;
  AddRoundKey_generic(&s,ekey,i*4);

  for(i=9; i>=0; i--){
    InvShiftRows2(&s);
    InvSubState(&s,&s);
    AddRoundKey_generic(&s,ekey,i*4);
    if(i!=0)InvMixColumns_b(&s);
  }
  for(i=0; i<4; i++){
    for(int k=0; k<4; k++) out[out_count++] = s.block[k][i];
  }
}

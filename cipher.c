#include <stdio.h>
#include <stdlib.h>
#include "KeyExpansion.h"
#include "ShiftRows2.h"
#include "AddRoundKey3.h"
#include "SubBytes2.h"
#include "MixColumns.h"

void cipher(uint8_t *in, uint8_t *out, struct expKey *ekey){
  int i,k, in_count=0, out_count=0;
  //convert in(length of 4*4) to state
  struct state *s = newState();
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) setState(k,i,in[in_count++],s);
  }
  //first addroundkey operation i=0
  AddRoundKey_generic(s,ekey,0);//<-change this for ekey

  //for i=1 to i=9, perform SubBytes, ShiftRows, MixColumns, AddRoundKey
  //i=1
  for(i=1; i<11; i++){
    SubState(s,s);
    ShiftRows(s);
    if(i!=10) MixColumns(s);
    AddRoundKey_generic(s,ekey,i*4);
  }
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) printf("%x ",s->block[i][k]);
    printf("\n");
  }printf("\n");

  for(i=0; i<4; i++){
    for(k=0; k<4; k++) out[out_count++] = s->block[k][i];
  }
}

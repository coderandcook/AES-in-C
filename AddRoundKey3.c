#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "AddRoundKey3.h"

//pass state, 4 words from expkey, and 0<=i<=10
void AddRoundKey_generic(struct state *s,const struct expKey *ekey,int i){
  uint8_t temp = 0x00;

  struct state temp_state;
  clearState(&temp_state);
  for(int j=0; j<4; j++){
    for(int k=0; k<4; k++){
      temp_state.block[j][k] = ekey->wordList[j+i][k];
    }
  }
  //add extracted key to state(similar to AddRoundKey)
  for(int k=0; k<4; k++){
    for(int j=0; j<4; j++){
      temp = (s->block[k][j])^(temp_state.block[k][j]);
      setState(k,j,temp,s);
    }
  }
}
int isEqualMessage(const uint8_t *x, const uint8_t *y){
  for(int i=0; i<16; i++){
    if(x[i]!=y[i]) return 0;
  }
  return 1;
}
void AddRoundKey32(struct state2 *s, struct expKey32 ekey, int i){
  for(int j=0; j<4; j++) s->block[j] ^= ekey.block[j+i];
}

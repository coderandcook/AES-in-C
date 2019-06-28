#include <stdio.h>
#include <stdlib.h>
#include "ShiftRows2.h"

void AddRoundKey(struct state *s, struct state *key){
  int i,k;
  uint8_t temp = 0x00;

  for(i=0; i<4; i++){
    for(k=0; k<4; k++){
      temp = (s->block[i][k]) ^ (key->block[i][k]);
      setState(i,k,temp,s);
    }

  }
}

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "AddRoundKey3.h"

int isEqualMessage(const uint8_t *x, const uint8_t *y){
  for(int i=0; i<16; i++){
    if(x[i]!=y[i]) return 0;
  }
  return 1;
}
void AddRoundKey32(struct state2 *s, const struct expKey32 *ekey, int i){
  for(int j=0; j<4; j++) s->block[j] ^= ekey->block[j+i];
}

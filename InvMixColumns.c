#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "MixColumns.h"
#include "ShiftRows2.h"
#include "SubBytes2.h"

void InvMixColumns(struct state *s){
  //same direction shift
  for(int i=0; i<4; i++){
    int temp = 0x00;
    uint8_t col[4];
    setColumns(s,i,col);

    uint8_t multiplier[] = {0x0e,0x0b,0x0d,0x09};
    for(int k=0; k<4; k++){
      temp = colMultiply(col,multiplier);
      shiftMultiplier(multiplier);
      setState(k,i,temp,s);
    }
  }
}

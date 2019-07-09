#include <stdio.h>
#include <stdlib.h>
#include "ShiftRows2.h"

void shiftRight(struct state *s, int row, int rounds){
  int i,k;
  uint8_t temp = 0x00;

  for(i=0; i<rounds; i++){
    temp = s->block[row][3];
    for(k=3; k>0; k--) s->block[row][k] = s->block[row][k-1];
    s->block[row][k] = temp;
  }
}

void InvShiftRows(struct state *s){
  shiftRight(s,1,1);
  shiftRight(s,2,2);
  shiftRight(s,3,3);
}

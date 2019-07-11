#include <stdio.h>
#include <stdlib.h>
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "shifter.h"

void shiftRight(struct state *s, int row, int rounds){
  uint8_t words[4];
  setStateToWord(s,row,words);
  rshiftWord(words,rounds);

  /*
  uint8_t temp = 0x00;

  int i;
  for(i=0; i<rounds; i++){
    temp = s->block[row][3];
    int k;
    for(k=3; k>0; k--) s->block[row][k] = s->block[row][k-1];
    s->block[row][k] = temp;
  }
  */
  setWordToState(s,row,words);
}

void InvShiftRows(struct state *s){
  shiftRight(s,1,1);
  shiftRight(s,2,2);
  shiftRight(s,3,3);
}

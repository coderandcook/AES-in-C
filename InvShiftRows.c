#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "SubBytes2.h"
#include "ShiftRows2.h"
#include "shifter.h"
#include "InvShiftRows.h"

void shiftRight(struct state *s, int row, int rounds){
  uint8_t words[4];
  setStateToWord(s,row,words);
  rshiftWord(words,rounds);
  setWordToState(s,row,words);
}

void InvShiftRows(struct state *s){
  shiftRight(s,1,1);
  shiftRight(s,2,2);
  shiftRight(s,3,3);
}


void InvShiftRows2(struct state *s){
  rshiftWord(s->block[1],1);
  rshiftWord(s->block[2],2);
  rshiftWord(s->block[3],3);
}

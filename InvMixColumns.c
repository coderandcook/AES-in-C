#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "MixColumns.h"
#include "ShiftRows2.h"
#include "SubBytes2.h"

uint8_t colMultiply_generic(const uint8_t *col, const uint8_t *multiplier){
  uint8_t tempBig = 0x00;
  uint8_t temp;
  int col_poly[8];
  int multiplier_poly[8];

  int i;
  for(i=0; i<4; i++){
    temp=0;
    setWordToPoly(col,i,col_poly);
    setWordToPoly(multiplier,i,multiplier_poly);

    mulPoly(col_poly,multiplier_poly);

    temp = getInt(col_poly);
    tempBig = tempBig^temp;
  }
  return tempBig;
}

void InvMixColumns(struct state *s){
  //same direction shift
  uint8_t multiplier[] = {0x0e,0x0b,0x0d,0x09};
  uint8_t temp;
  uint8_t col[4];

  int i;
  for(i=0; i<4; i++){
    temp = 0x00;
    setColumns(s,i,col);

    int k;
    for(k=0; k<4; k++){
      temp = colMultiply_generic(col,multiplier);
      shiftMultiplier(multiplier);
      setState(k,i,temp,s);
    }
  }
}

#include <stdio.h>
#include <stdlib.h>
#include "poly.h"
#include "div_poly.h"
#include "MixColumns.h"
#include "ShiftRows2.h"
#include "SubBytes2.h"

uint8_t colMultiply_generic(uint8_t *col, uint8_t *multiplier){
  int i;
  uint8_t tempBig = 0x00;
  uint8_t temp;
  int col_poly[8];
  int multiplier_poly[8];

  for(i=0; i<4; i++){
    temp=0;
    clear8(col_poly);
    clear8(multiplier_poly);

    setWordToPoly(col,i,col_poly);
    setWordToPoly(multiplier,i,multiplier_poly);

    mul2(col_poly,multiplier_poly);

    temp = getInt(col_poly); //printf("%x ",temp);
    tempBig = tempBig^temp;
  }
  printf("%x ",tempBig);
  return tempBig;
}

void InvMixColumns(struct state *s){
  int i,k;
  //same direction shift
  uint8_t multiplier[] = {0x0e,0x0b,0x0d,0x09};
  uint8_t temp;
  uint8_t col[4];
  for(i=0; i<4; i++){
    clearCol(col);
    temp = 0x00;

    setColumns(s,i,col);

    for(k=0; k<4; k++){
      temp = colMultiply_generic(col,multiplier);
      shiftMultiplier(multiplier);
      setState(k,i,temp,s);
      //printf("%x ",temp);
    }
    printf("\n");
  }
  printf("\n");
}

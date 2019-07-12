#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ShiftRows2.h"
#include "poly.h"
#include "SubBytes2.h"
#include "shifter.h"

//uint8_t multiplier[] = {2, 3, 1, 1};
void clearCol(uint8_t *col){
  for(int i=0; i<4; i++) col[i] = 0x00;
}

//column is updated as one array
void setColumns(const struct state* s, int col, uint8_t* column){
  clearCol(column);
  for(int i=0; i<4; i++) column[i] = s->block[i][col];
}
//shift multiplier to the right
void shiftMultiplier(uint8_t *multiplier){
  rshiftWord(multiplier,1);
}
uint8_t mulWord(uint8_t multiplicand, uint8_t multiplier){
  //convert word to poly, do mulPoly
  int poly[8];
  setPoly(multiplicand,poly);

  int poly2[8];
  setPoly(multiplier,poly2);

  mulPoly(poly,poly2);
  return getInt(poly);
}

//shitMultiplier(multiplier) after function
uint8_t colMultiply(const uint8_t *col, const uint8_t *multiplier){
  uint8_t tempBig = 0x00;
  for(int i=0; i<4; i++){
    uint8_t temp = 0x00;
    temp = mulWord(col[i],multiplier[i]);
    tempBig = tempBig^temp;
  }
  return tempBig;
}

int isEqualCol(const uint8_t *col, const uint8_t *col2){
  for(int i=0; i<4; i++){
    if(col[i]!=col2[i]) return 0;
  }
  return 1;
}

void MixColumns(struct state* s){
  //uint8_t multiplier[] = {0x02, 0x03, 0x01, 0x01};
  for(int i=0; i<4; i++){//for each column
    uint8_t multiplier[] = {0x02, 0x03, 0x01, 0x01};
    uint8_t col[4];
    setColumns(s, i, col);
    for(int k=0; k<4; k++){//for each member in a column
      uint8_t temp = 0x00;
      temp = colMultiply(col, multiplier);
      shiftMultiplier(multiplier);
      setState(k, i, temp, s);
    }
  }
}

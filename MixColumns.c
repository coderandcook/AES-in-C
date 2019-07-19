#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ShiftRows2.h"
#include "poly.h"
#include "SubBytes2.h"
#include "shifter.h"
#include "bit.h"

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





uint8_t mulWord_b(uint8_t x, uint8_t y){
  return mul_bit8(x,y);
}
uint8_t colMultiply_b(uint8_t *col, uint8_t *multiplier){
  uint8_t tempBig=0;
  for(int i=0; i<4; i++){
    uint8_t temp=0;
    temp = mulWord_b(col[i],multiplier[i]);
    tempBig = tempBig^temp;
  }
  return tempBig;
}
void MixColumns_b(struct state* s){
  for(int i=0; i<4; i++){
    uint8_t multiplier[] = {0x02, 0x03, 0x01, 0x01};
    uint8_t col[4];
    setColumns(s, i, col);
    for(int k=0; k<4; k++){
      uint8_t temp = 0;
      temp = colMultiply_b(col,multiplier);
      shiftMultiplier(multiplier);
      setState(k,i,temp,s);
    }
  }
}
uint32_t getColumn32(struct state2 s, int col){
  uint32_t result=0;
  for(int i=0; i<4; i++){
    /*
    uint32_t temp = s.block[i];
    temp = temp<<col*8;
    temp = temp >> (32-8);
    result ^= temp<<(32-(i+1)*8);
    */
    result ^= ((s.block[i]<<col*8)>>(32-8))<<(32-(i+1)*8);
  }
  return result;
}

//by row
uint32_t mul32(uint32_t x, uint32_t y){
  uint32_t result = 0;

  for(int i=0; i<4; i++){
    uint32_t temp = (x<<i*8)>>(32-8);
    uint32_t temp2 = (y<<i*8)>>(32-8);


    uint8_t temp_res = mul_bit8(temp,temp2);
    result ^= temp_res<<(32-(i+1)*8);
  }
  return result;
}
uint32_t colMultiply32(uint32_t x, uint32_t y){




  return 0;
}
void MixColumns32(struct state2 *s){





}

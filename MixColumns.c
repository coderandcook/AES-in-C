#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#include "poly.h"
#include "SubBytes2.h"
#include "shifter.h"
#include "bit.h"
#include "MixColumns.h"

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
  return mul(x,y);
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
    for(int k=0; k<4; k++){//for each column
      uint8_t temp = 0;
      temp = colMultiply_b(col,multiplier);
      shiftMultiplier(multiplier);
      setState(k,i,temp,s);
    }
  }
}
uint32_t getColumn32(const struct state2 *s, int col){
  uint32_t result=0;
  for(int i=0; i<4; i++){
    uint32_t temp = s->block[i];
    temp = temp<<(8*col);
    temp = temp>>(8*3);

    result ^= temp<<(8*(3-i));

  }





  return result;
}
void setColumn32(struct state2 *s, int col_num, uint32_t col){
  for(int i=0; i<4; i++){
    uint32_t temp = col>>(8*(3-i));
    col ^= temp<<(8*(3-i));
    temp = temp<<(8*(3-col_num));

    uint32_t temp2 = s->block[i]>>(8*(3-col_num));
    temp2 = temp2>>8;
    temp2 = temp2<<(8*(3-col_num+1));

    s->block[i] = s->block[i]<<(8*(col_num));
    s->block[i] = s->block[i]<<8;
    s->block[i] = s->block[i]>>(8*(col_num+1));

    s->block[i] ^=temp2;
    s->block[i] ^= temp;
  }
}


uint32_t mul32(uint32_t x, uint32_t y){
  uint32_t result = 0;
  for(int i=0; i<4; i++){//for each 8bit of x and y
    uint32_t t1 = x>>(8*3);
    x = x<<8;

    uint32_t t2 = y>>(8*3);
    y = y<<8;

    uint32_t temp_res = mul(t1,t2);
    result ^= temp_res;
  }
  return result;
}

void MixColumns32(struct state2 *s){
  for(int i=0; i<4; i++){//for each column
    uint32_t multiplier = 0x02030101;
    uint32_t col = getColumn32(s,i);
    uint32_t temp_res = 0;
    for(int k=0; k<4; k++){//for each shift of multiplier

      uint32_t temp = mul32(col,multiplier); //printf("temp = %x\n",temp);

      //if(i==0) printf("temp: %x\n",temp);
      temp_res ^= temp<<(8*(3-k));
      multiplier = rshift32(multiplier,1);
    }
    //set temp_res to state2
    setColumn32(s,i,temp_res);
  }
}

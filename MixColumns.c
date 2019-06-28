#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ShiftRows2.h"
//uint8_t multiplier[] = {2, 3, 1, 1};

//column is updated as one array
void setColumns(struct state* s, int col, uint8_t* column){
  int i;
  for(i=0; i<4; i++) column[i] = s->block[i][col];


}
//shift multiplier to the right
void shiftMultiplier(uint8_t *multiplier){
  int i;
  uint8_t temp = multiplier[3];
  for(i=3; i>0; i--){
    multiplier[i] = multiplier[i-1];
  }
  multiplier[i] = temp;
}
uint8_t mulTwo(uint8_t colNum){
  int flag = 0;
  uint8_t test = 0x80;

  if(colNum/test == 1) flag = 1;
  colNum = colNum<<1;
  if(flag==1) colNum = colNum^0x1b;

  return colNum;
}
uint8_t mulThree(uint8_t colNum){
  //(result of mulTwo) xor (colNum)
  uint8_t temp =0x00;
  temp = mulTwo(colNum);
  //printf("temp from mulThree: %d\n", temp);//expect 101
  temp = temp^colNum;
  return temp;
}

//shitMultiplier(multiplier) after function
uint8_t colMultiply(uint8_t *col, uint8_t *multiplier){
  int i;
  uint8_t tempBig = 0x00;
  uint8_t temp;

  for(i=0; i<4; i++){
    temp = 0x00;
    if(multiplier[i]==0x01) temp = col[i];
    else if(multiplier[i]==0x02) temp = mulTwo(col[i]);
    else if(multiplier[i]==0x03) temp = mulThree(col[i]);

    tempBig = tempBig^temp;

  }
  return tempBig;
}

int isEqualCol(uint8_t *col, uint8_t *col2){
  int i;
  for(i=0; i<4; i++){
    if(col[i]!=col2[i]) return 0;
  }
  return 1;
}

void clearCol(uint8_t *col){
  int i;
  for(i=0; i<4; i++) col[i] = 0x00;
}

void MixColumns(struct state* s){
  int i, k;
  uint8_t col[4];
  uint8_t multiplier[] = {0x02, 0x03, 0x01, 0x01};
  uint8_t temp;
  for(i=0; i<4; i++){//for each column
    clearCol(col);
    temp = 0x00;

    setColumns(s, i, col);

    for(k=0; k<4; k++){//for each member in a column
      temp = colMultiply(col, multiplier);
      shiftMultiplier(multiplier);
      setState(k, i, temp, s);
    }
  }
}

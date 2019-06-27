#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "ShiftRows2.h"

//column is updated as one array of a column
void setColumns(struct state* s, int col, uint8_t* column){
  int i;
  for(i=0; i<4; i++) column[i] = s->block[i][col];


}

void MixColumns(struct state* s){
  int i, k;
  uint8_t temp[4];

  //get data of each column
  //set array for each column

  //block[row][col]
  for(i=0; i<4; i++){//column
    clearFourBytes(temp);

    setColumns(s,i,temp);
    //multiply variables of temp

  }













  

}

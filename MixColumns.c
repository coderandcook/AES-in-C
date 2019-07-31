#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "ShiftRows2.h"
#include "SubBytes2.h"
#include "shifter.h"
#include "bit.h"
#include "MixColumns.h"

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
  //for each 8bit in x and y
  uint32_t final = 0;

  for(int i=0; i<4; i++){
    uint8_t tx = (x>>(8*i))&0xff;
    uint8_t ty = (y>>(8*i))&0xff;
    final ^= mul(tx,ty);
  }
  return final;
}

void MixColumns32(struct state2 *s){
  for(int i=0; i<4; i++){//for each column
    uint32_t multiplier = 0x02030101;
    uint32_t col = getColumn32(s,i);
    uint32_t temp_res = 0;
    for(int k=0; k<4; k++){//for each shift of multiplier

      uint32_t temp = mul32(col,multiplier);

      //if(i==0) printf("temp: %x\n",temp);
      temp_res ^= temp<<(8*(3-k));
      multiplier = rshift32(multiplier,1);
    }
    //set temp_res to state2
    setColumn32(s,i,temp_res);
  }
}

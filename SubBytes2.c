//additon
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdint.h>
#include "poly.h"
#include "div_poly.h"
#include "div_generic.h"
#include "mod3.h"
#include "ShiftRows2.h"
#include "shifter.h"
#include "bit.h"
#include "SubBytes2.h"

void ClearWord(uint8_t *word){
  for(int i=0; i<4; i++) word[i] = 0;
}
void CopyWord(const uint8_t *src, uint8_t *dst){
  ClearWord(dst);
  for(int i=0; i<4; i++) dst[i] = src[i];
}
void setStateToPoly(const struct state *s, int row, int col, int *poly){
  setPoly(s->block[row][col],poly);
}
void setPolyToState(struct state *s, int row, int col, const int *poly){
  s->block[row][col] = getInt(poly);
}
void setStateToWord(const struct state *s, int row, uint8_t *words){
  ClearWord(words);
  for(int i=0; i<4; i++)words[i] = s->block[row][i];
}
void setWordToState(struct state *s, int row, const uint8_t *words){
  for(int i=0; i<4; i++) s->block[row][i] = words[i];
}
void setWordToPoly(const uint8_t *words, int word, int *poly){
  setPoly(words[word],poly);
}

void setPolyToWord(uint8_t *words, int i, const int *poly){
  words[i] = getInt(poly);
}

void shift(int *poly){//shift right
  rshiftPoly(poly,8,1);
}

void crossMul(const int *multiplicand, int *multiplier, int *output){
  clear8(output);
  for(int i=0; i<8; i++){
    int temp=0;
    for(int k=0; k<8; k++){
      temp+=multiplier[k]*multiplicand[k];
    }
    output[i] = temp & 1;
    shift(multiplier);
  }
}
int SubBytes(const int *input, int *output){
  const int m[] = {1,0,0,0,1,1,0,1,1};
  int arr_result[8];
  //take multiplicativ inverse of input
  mulInverse(m, input, arr_result);
  //crosswise multiplication
  int multiplier[] = {1,1,1,1,1,0,0,0};
  crossMul(arr_result,multiplier,output);
  //crosswise addition
  int add[]={0,1,1,0,0,0,1,1};
  addPoly(output, add);

  return getInt(output);
}
void SubState(const struct state *input, struct state *output){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      int temp[8];
      setStateToPoly(input,i,k,temp);
      int temp2[8];
      SubBytes(temp,temp2);
      setPolyToState(output,i,k,temp2);
    }
  }
}
uint8_t crossMul_b(uint8_t x, uint8_t y){
  uint8_t result=0;
  for(int i=0; i<8; i++){//travers all bits in x, shift y
    uint8_t temp = x&y; //printf("temp = %x\n",temp);
    //printf("temp = %x\n",temp);

    uint8_t bit=0;
    for(int k=0; k<8; k++){//XOR bits in x

      uint8_t sbit = temp>>(7-k);
      temp = temp^(sbit<<(7-k));

      bit^=sbit;
    }
    //printf("bit = %x\n",bit);
    result ^= bit<<(7-i); //printf("result = %x\n",result);
    y = rshift_b8(y,1);
  }
  return result;
}
uint8_t SubBytes_b(uint8_t x){
  uint8_t temp_res=0;
  //mulInverse
  temp_res = mulInverse_b(x);

  //crossMul
  uint8_t multiplier = 0xf8;
  temp_res = crossMul_b(temp_res, multiplier);

  //addition
  return temp_res ^ 0x63;
}
void SubState_b(const struct state *input, struct state *output){
  //copyState(input,)
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      output->block[i][k] = SubBytes_b(input->block[i][k]);
    }
  }
}
void SubState32(struct state2 *in){//out
  for(int i=0; i<4; i++){
#if 1
    uint32_t temp = in->block[i];
    uint32_t t0 = SubBytes_b(temp>>24);
    uint32_t t1 = SubBytes_b(temp>>16);
    uint32_t t2 = SubBytes_b(temp>>8);
    uint32_t t3 = SubBytes_b(temp);
    in->block[i] = (t0<<24)|(t1<<16)|(t2<<8)|t3;
#else
    for(int k=0; k<4; k++){
      uint32_t temp = temp_s.block[i]>>(32-(k+1)*8);
      temp = SubBytes_b(temp);
      in->block[i] ^= temp<<(32-(k+1)*8);
    }
#endif
  }

}

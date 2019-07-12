#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include "ShiftRows2.h"
#include "shifter.h"
#include "SubBytes2.h"

void clearState(struct state* s){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) s->block[i][k] = 0;
  }
}
struct state* newState(){
  struct state* s = (struct state*) malloc(sizeof(struct state));
  clearState(s);
  return s;
}
void clearFourBytes(uint8_t *words){
  int i;
  for(i=0; i<4; i++) words[i]=0;
}

void setState(int row, int col, uint8_t new, struct state *s){
  s->block[row][col] = new;
}

void shiftLeft(struct state* s, int row, int rounds){
  uint8_t words[4];
  setStateToWord(s,row,words);
  lshiftWord(words,rounds);
  setWordToState(s,row,words);
}
void printRow(const struct state* s, int row){
  int i;
  for(i=0; i<4; i++) printf("%x ", s->block[row][i]);
  printf("\n");
}

void printState(const struct state* s){
  int i;
  for(i=0; i<4; i++) printRow(s, i);
}
void ShiftRows(struct state* s){
  //leave s[0] as it is

  //one shift on s[1]
  shiftLeft(s, 1, 1);
  //two shifts on s[2]
  shiftLeft(s, 2, 2);
  //three shifts on s[3]
  shiftLeft(s, 3, 3);
}
int isEqualByte(const uint8_t num, const uint8_t num2){
  if(num==num2) return 1;
  else return 0;
}
int isEqualState(const struct state* s1, const struct state* s2){
  int i;
  for(i=0; i<4; i++){
    int k;
    for(k=0; k<4; k++){
      if(s1->block[i][k] != s2->block[i][k]) return 0;
    }
  }
  return 1;
}

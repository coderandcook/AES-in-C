#include <stdio.h>
#include <math.h>
#include <stdint.h>
#include <stdlib.h>

struct state{
  uint8_t block[4][4];
};

struct state* newState(){
  int i, k;
  struct state* s = (struct state*) malloc(sizeof(struct state));
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) s->block[i][k]=0;
  }
  return s;
}

void setState(int row, int col, uint8_t new, struct state *s){
  s->block[row][col] = new;
}

void shiftLeft(struct state* s, int row, int rounds){
  int i, k;
  uint8_t temp = 0x00;

  for(i=0; i<rounds; i++){
    temp = s->block[row][0];
    for(k=0; k<3; k++) s->block[row][k]=s->block[row][k+1];
    s->block[row][k]=temp;
  }
}
void printRow(struct state* s, int row){
  int i;
  for(i=0; i<4; i++) printf("%d", s->block[row][i]);
  printf("\n");
}

void printState(struct state* s){
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
  printState(s);
}

int isEqualState(struct state* s1, struct state* s2){
  int i,k;
  for(i=0; i<4; i++){
    for(k=0; k<4; k++){
      if(s1->block[i][k] != s2->block[i][k]) return 0;
    }
  }
  return 1;
}
void clearState(struct state* s){
  int i, k;
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) s->block[i][k] = 0;
  }

}
void clearFourBytes(uint8_t *arr){
  int i;
  for(i=0; i<4; i++) arr[i]=0;



}

#include <stdio.h>
#include <stdlib.h>

void rshiftPoly(int *poly, int size, int num){
  int temp=0;
  int i;
  for(i=0; i<num; i++){
    temp = poly[size-1];
    int k;
    for(k=size-1; k>0; k--) poly[k] = poly[k-1];
    poly[k] = temp;
  }
}
void lshiftPoly(int *poly, int size, int num){
  int temp=0;
  int i;
  for(i=0; i<num; i++){
    temp = poly[0];
    int k;
    for(k=0; k<size-1; k++) poly[k] = poly[k+1];
    poly[k] = temp;
  }
}
void rshiftWord(uint8_t *words, int num){
  uint8_t temp = 0x00;
  int i;
  for(i=0; i<num; i++){
    temp = words[3];
    int k;
    for(k=3; k>0; k--) words[k] = words[k-1];
    words[k] = temp;
  }
}
void lshiftWord(uint8_t *words, int num){
  uint8_t temp = 0x00;
  int i;
  for(i=0; i<num; i++){
    temp = words[0];
    int k;
    for(k=0; k<3; k++) words[k] = words[k+1];
    words[k] = temp;
  }
}
uint8_t rshift_b8(uint8_t x, int num){
  uint8_t temp = x<<(8-num);
  uint8_t temp2 = temp>>(8-num);
  x = x^temp2;
  x = x>>num;
  x = x^temp;
  return x;
}
uint8_t lshift_b8(uint8_t x, int num){
  uint8_t temp = x>>(8-num);
  uint8_t temp2 = temp<<(8-num);
  x = x^temp2;
  x = x<<num;
  x = x^temp;
  return x;
}

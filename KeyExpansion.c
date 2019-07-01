#include <stdio.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "div_poly.h"

struct Rcon* newRcon(){
  struct Rcon* rc = (struct Rcon*)malloc(sizeof(struct Rcon));
  int i;
  for(i=0; i<4; i++) rc->bytes[i] = 0;
  return rc;
}

void updateRcon(struct Rcon *rc, int i, int Nk){
  //uint8_t temp=Nk;
  uint8_t temp = i/Nk;
  rc->bytes[0] = temp;
}

void RotWord(uint8_t *bytes){//for a word
  //input[0] replaces input[3]
  uint8_t temp = bytes[0];
  int i;
  for(i=0; i<3; i++) bytes[i] = bytes[i+1];
  bytes[3] = temp;
}
void SubWord(uint8_t *bytes){//a word, 4bytes, 8bits
  //replace each byte with new one, using SubBytes
  int i;
  int temp[8];
  int temp2[8];
  //byte[i] = 0xff will become byte[i] = 0x1c(28)

  for(i=0; i<4; i++){
    clear8(temp);
    clear8(temp2);
    setWordToPoly(bytes,i,temp);
    SubBytes(temp,temp2);
    setPolyToWord(bytes, i, temp2);







  }








}
int isEqualWord(uint8_t *word1, uint8_t *word2){
  int i;
  for(i=0; i<4; i++){
    if(word1[i]!=word2[i]) return 0;
  }
  return 1;
}

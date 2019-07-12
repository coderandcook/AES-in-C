#include <stdio.h>
#include <math.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "div_poly.h"
#include "mod3.h"
#include "poly.h"


struct key *newKey(){
  struct key* key = (struct key*) malloc(sizeof(struct key));
  int i,k;
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) key->block[i][k] = 0;
  }
  return key;
}

void clearKey(struct key *k){
  int i,j;
  for(i=0; i<4; i++){
    for(j=0; j<4; j++) k->block[i][j] = 0;
  }
}
void setKey(struct key *k, const uint8_t *words){//4*4bytes
  clearKey(k);
  int i,j,count=0;
  for(i=0; i<4; i++){
    for(j=0; j<4; j++) k->block[j][i] = words[count++];
  }
}

struct expKey *newekey(){
  struct expKey *ekey = (struct expKey*)malloc(sizeof(struct expKey));
  int i,k;
  for(i=0; i<44; i++){
    for(k=0; k<4; k++) ekey->wordList[i][k] = 0;
  }
  return ekey;
}

struct word *newWord(){
  struct word *word = (struct word*)malloc(sizeof(struct word));
  int i;
  for(i=0; i<4; i++) word->w[i] = 0;
  return word;
}
//set a row in key
void setWord(const struct key *key, int i, struct word *word){
  int k;
  for(k=0; k<4; k++){
    word->w[k] = key->block[i][k];
  }
}
//rcon must be 01 00 00 00 in the beginning
struct Rcon* newRcon(){
  struct Rcon* rc = (struct Rcon*)malloc(sizeof(struct Rcon));
  rc->bytes[0] = 0x01;
  int i;
  for(i=1; i<4; i++)rc->bytes[i] = 0x00;
  return rc;
}

void updateRcon(struct Rcon *rc){
  int poly[8];
  int multiplier[] = {0,0,0,0,0,0,1,0};

  //convert rc->bytes[0] to array of ints
  setWordToPoly(rc->bytes,0,poly);
  mulPoly(poly,multiplier);
  setPolyToWord(rc->bytes,0,poly);
}

void RotWord(uint8_t *words){//for a word
  //input[0] replaces input[3]
  uint8_t temp = words[0];
  int i;
  for(i=0; i<3; i++) words[i] = words[i+1];
  words[3] = temp;
}

void SubWord(const uint8_t *word1, uint8_t *word2){
  int poly[8];
  int i;
  for(i=0; i<4; i++){
    setWordToPoly(word1,i,poly);//poly is cleared before set
    SubBytes(poly,poly);
    setPolyToWord(word2,i,poly);
  }
}
void SubRot(uint8_t *word1, uint8_t *word2, const struct Rcon *rc){
  RotWord(word1);
  SubWord(word1, word2);//word2 is cleared before set
  int i;
  for(i=0; i<4; i++) word2[i] = word2[i]^rc->bytes[i];
}

int isEqualWord(const uint8_t *word1, const uint8_t *word2){
  int i;
  for(i=0; i<4; i++){
    if(word1[i]!=word2[i]) return 0;
  }
  return 1;
}
//set ekey
void KeyExpansion(const struct key *key, struct expKey *ekey){
  int i = 4;
  int k,h;
  uint8_t words[4][4];//4*4 bytes
  uint8_t temp[4];
  uint8_t temp2[4];
  struct Rcon *rc = newRcon();
  for(k=0; k<4; k++){//initialize
    ClearWord(words[k]);
  }
  for(k=0; k<4; k++){
    for(i=0; i<4; i++) words[i][k] = key->block[k][i];
  }
  //set w0 to w3
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) ekey->wordList[i][k] = words[k][i];
  }
  for(i=4; i<44; i++){
    h=(i-4)%4;
    //update words[]
    if(i%4==0){
      CopyWord(words[3], temp);
      //update rc
      if(i>4) updateRcon(rc);
      SubRot(temp,temp,rc);
      //always h=0
      CopyWord(words[h],temp2);
      for(k=0; k<4; k++) temp[k] = temp[k]^temp2[k];
      //copy one row
      //loop the whole block, but only set wordList[i][0]
      int count=0;
      for(k=i-i%4; k<i-i%4+4; k++) ekey->wordList[k][i%4] = temp[count++];
    }
    else{
      //update temp
      CopyWord(words[h],temp2);
      for(k=0; k<4; k++) temp[k] = temp[k]^temp2[k];

      int count=0;
      for(k=i-i%4; k<i-i%4+4; k++){
        ekey->wordList[k][i%4] = temp[count++];
      }
      if(i%4==3){
        //update words
        for(k=0; k<4; k++){
          int j;
          for(j=0; j<4; j++) words[j][k] = ekey->wordList[i-3+k][j];
        }
      }
    }
  }
}

void printekey(const struct expKey *ekey, int startRow, int endRow){
  int i;
  for(i=startRow; i<=endRow; i++){
    int k;
    for(k=0; k<4; k++) printf("%x ", ekey->wordList[i][k]);
    printf("\n");
  }
  printf("\n");
}

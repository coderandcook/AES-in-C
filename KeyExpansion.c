#include <stdio.h>
#include <math.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "div_poly.h"


struct key *newKey(){
  struct key* key = (struct key*) malloc(sizeof(struct key));
  int i,k;
  for(i=0; i<4; i++){
    for(k=0; k<4; k++) key->block[i][k] = 0;
  }
  return key;
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

void setWord(struct key *key, int i, struct word *word){
  int k;
  for(k=0; k<4; k++){
    word->w[k] = key->block[i][k];
  }
}

struct Rcon* newRcon(){
  struct Rcon* rc = (struct Rcon*)malloc(sizeof(struct Rcon));
  int i;
  for(i=0; i<4; i++) rc->bytes[i] = 0;
  return rc;
}

void updateRcon(struct Rcon *rc, int i, int Nk){
  /*
  uint8_t temp = i/Nk;
  rc->bytes[0] = temp;*/
  int temp = i/Nk-1;
  int temp2 = pow(2,temp)/1;
  if(i==36) temp2 = 27;
  else if(i==40) temp2 = 54;

  rc->bytes[0] = temp2;
}

void RotWord(uint8_t *bytes){//for a word
  //input[0] replaces input[3]
  uint8_t temp = bytes[0];
  int i;
  for(i=0; i<3; i++) bytes[i] = bytes[i+1];
  bytes[3] = temp;
}

void SubWord(uint8_t *word1, uint8_t *word2){
  int i;
  int poly[8]; clear8(poly);
  for(i=0; i<4; i++){
    setWordToPoly(word1,i,poly);
    SubBytes(poly,poly);
    setPolyToWord(word2,i,poly);
  }
}
void SubRot(uint8_t *word1, uint8_t *word2, struct Rcon *rc){
  int i;
  RotWord(word1);
  SubWord(word1, word2);
  for(i=0; i<4; i++) word2[i] = word2[i]^rc->bytes[i];
}


int isEqualWord(uint8_t *word1, uint8_t *word2){
  int i;
  for(i=0; i<4; i++){
    if(word1[i]!=word2[i]) return 0;
  }
  return 1;
}

void KeyExpansion(struct key *ky, struct expKey *ekey){
  int i = 4;
  int k,h;
  uint8_t words[4][4];//4*4 bytes
  uint8_t temp[4]; ClearWord(temp);
  uint8_t temp2[4]; ClearWord(temp2);
  struct Rcon *rc = newRcon();

  for(k=0; k<4; k++){//initialize
    ClearWord(words[k]);
  }
  for(k=0; k<4; k++){//initialize
    CopyWord(ky->block[k],words[k]);
  }//now, words == ky->block

  //set w0 to w3
  for(k=0; k<4; k++){//initial setting
    CopyWord(words[k], ekey->wordList[k]);
  }
  //for now, don't worry about i%4 output
  for(i=4; i<44; i++){
    h=(i-4)%4;
    //update words[]
    if(i%4==0){
      CopyWord(words[3], temp);//temp=words[3]

      //update rc
      updateRcon(rc,i,4);
      SubRot(temp,temp,rc);

      //always h=0
      CopyWord(words[h],temp2);//temp=words[0]
      for(k=0; k<4; k++) temp[k] = temp[k]^temp2[k];

      CopyWord(temp,ekey->wordList[i]);

      for(k=0; k<4; k++) printf("%d ",rc->bytes[k]);
      printf("\n");
    }
    else{
      //update temp
      CopyWord(words[h],temp2);
      for(k=0; k<4; k++) temp[k] = temp[k]^temp2[k];
      CopyWord(temp,ekey->wordList[i]);
      if(i%4==3){
        //update words
        for(k=0; k<4; k++) CopyWord(ekey->wordList[i-3+k],words[k]);
      }
    }
  }
}

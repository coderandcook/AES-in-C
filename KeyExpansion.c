#include <stdio.h>
#include <math.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "div_poly.h"
#include "mod3.h"
#include "poly.h"
#include "bit.h"


struct key *newKey(){
  struct key* key = (struct key*) malloc(sizeof(struct key));
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) key->block[i][k] = 0;
  }
  return key;
}

void clearKey(struct key *k){
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++) k->block[i][j] = 0;
  }
}
void setKey(struct key *k, const uint8_t *words){//4*4bytes
  clearKey(k);
  int count=0;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++) k->block[j][i] = words[count++];
  }
}
void setKey2(struct key *k, const uint8_t *words){
  clearKey(k);
  int count=0;
  for(int i=0; i<4; i++){
    for(int j=0; j<4; j++)k->block[i][j] = words[count++];
  }
}

struct expKey *newekey(){
  struct expKey *ekey = (struct expKey*)malloc(sizeof(struct expKey));
  for(int i=0; i<44; i++){
    for(int k=0; k<4; k++) ekey->wordList[i][k] = 0;
  }
  return ekey;
}

struct word *newWord(){
  struct word *word = (struct word*)malloc(sizeof(struct word));
  for(int i=0; i<4; i++) word->w[i] = 0;
  return word;
}
//set a row in key
void setWord(const struct key *key, int i, struct word *word){
  for(int k=0; k<4; k++)word->w[k] = key->block[i][k];
}
//rcon must be 01 00 00 00 in the beginning
void setRcon(struct Rcon *rc){
  rc->bytes[0] = 0x01;
  for(int i=1; i<4; i++)rc->bytes[i] = 0x00;
}

void updateRcon(struct Rcon *rc){
  int poly[8];
  //convert rc->bytes[0] to array of ints
  setWordToPoly(rc->bytes,0,poly);

  int multiplier[] = {0,0,0,0,0,0,1,0};
  mulPoly(poly,multiplier);
  setPolyToWord(rc->bytes,0,poly);
}

void RotWord(uint8_t *words){//for a word
  //input[0] replaces input[3]
  uint8_t temp = words[0];
  for(int i=0; i<3; i++) words[i] = words[i+1];
  words[3] = temp;
}

void SubWord(const uint8_t *word1, uint8_t *word2){
  for(int i=0; i<4; i++){
    int poly[8];
    setWordToPoly(word1,i,poly);//poly is cleared before set
    SubBytes(poly,poly);
    setPolyToWord(word2,i,poly);
  }
}
void SubRot(uint8_t *word1, uint8_t *word2, const struct Rcon *rc){
  RotWord(word1);
  SubWord(word1, word2);//word2 is cleared before set
  for(int i=0; i<4; i++) word2[i] = word2[i]^rc->bytes[i];
}

int isEqualWord(const uint8_t *word1, const uint8_t *word2){
  for(int i=0; i<4; i++){
    if(word1[i]!=word2[i]) return 0;
  }
  return 1;
}
//set ekey
void KeyExpansion(const struct key *key, struct expKey *ekey){
  uint8_t words[4][4];//4*4 bytes
  for(int k=0; k<4; k++)ClearWord(words[k]);
  for(int k=0; k<4; k++){
    for(int i=0; i<4; i++) words[i][k] = key->block[k][i];
  }
  //set w0 to w3
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++) ekey->wordList[i][k] = words[k][i];
  }

  uint8_t temp[4];
  struct Rcon rc;
  setRcon(&rc);

  for(int i=4; i<44; i++){
    int h=(i-4)%4;
    //update words[]
    if(i%4==0){
      CopyWord(words[3], temp);
      //update rc
      if(i>4) updateRcon(&rc);
      SubRot(temp,temp,&rc);
      //always h=0
      uint8_t temp2[4];
      CopyWord(words[h],temp2);
      for(int k=0; k<4; k++) temp[k] = temp[k]^temp2[k];
      //copy one row
      //loop the whole block, but only set wordList[i][0]
      int count=0;//=0
      for(int k=i-i%4; k<i-i%4+4; k++) ekey->wordList[k][i%4] = temp[count++];
    }
    else{
      uint8_t temp2[4];
      //update temp
      CopyWord(words[h],temp2);
      for(int k=0; k<4; k++) temp[k] = temp[k]^temp2[k];

      int count=0;
      for(int k=i-i%4; k<i-i%4+4; k++)ekey->wordList[k][i%4] = temp[count++];
      if(i%4==3){
        //update words
        for(int k=0; k<4; k++){
          for(int j=0; j<4; j++) words[j][k] = ekey->wordList[i-3+k][j];
        }
      }
    }
  }
}
void printekey(const struct expKey *ekey, int startRow, int endRow){
  for(int i=startRow; i<=endRow; i++){
    for(int k=0; k<4; k++) printf("%x ", ekey->wordList[i][k]);
    printf("\n");
  }
  printf("\n");
}



//KeyExpansion bitwise
void updateRcon_b(struct Rcon *rc){
  rc->bytes[0] = mul_bit8(rc->bytes[0],0x2);
}
void SubWord_b(uint8_t *x, uint8_t *y){//passes a row from key
  for(int i=0; i<4; i++){
    y[i] = SubBytes_b(x[i]);
  }
}
void SubRot_b(uint8_t *x, uint8_t *y, const struct Rcon *rc){
  RotWord(x);
  SubWord_b(x, y);//word2 is cleared before set
  for(int i=0; i<4; i++) y[i] ^= rc->bytes[i];
}
void KeyExpansion_b(const struct key *key, struct expKey *ekey){
  uint8_t words[4][4];
  for(int i=0; i<4; i++)ClearWord(words[i]);
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      words[k][i] = key->block[i][k];
      ekey->wordList[i][k] = key->block[i][k];
    }
  }
  uint8_t temp[4];
  struct Rcon rc;
  setRcon(&rc);

  for(int i=4; i<44; i++){
    int h=(i-4)%4;
    if(i%4==0){
      for(int k=0; k<4; k++) temp[k] = words[3][k];

      if(i>4) updateRcon_b(&rc);
      SubRot_b(temp,temp,&rc);
      //always h=0
      for(int k=0; k<4; k++) temp[k] ^= words[h][k];
      int count=0;//=0
      for(int k=i-i%4; k<i-i%4+4; k++) ekey->wordList[k][i%4] = temp[count++];
    }
    else{
      for(int k=0; k<4; k++) temp[k] ^= words[h][k];

      int count=0;
      for(int k=i-i%4; k<i-i%4+4; k++)ekey->wordList[k][i%4] = temp[count++];
      if(i%4==3){
        //update words
        for(int k=0; k<4; k++){
          for(int j=0; j<4; j++) words[j][k] = ekey->wordList[i-3+k][j];
        }
      }
    }
  }
}
//KeyExpansion in uint32_t [44]
void clearEkey(struct expKey32 *ekey){
  for(int i=0; i<44; i++) ekey->block[i] = 0;
}




uint32_t updateRcon32(uint32_t rc){
  uint8_t temp = rc>>24;
  temp = mul_bit8(temp,0x2);
  return temp<<24;
}

uint32_t RotWord32(uint32_t x){
  uint32_t temp = x>>24;//greatest byte
  uint32_t temp2 = temp<<24;
  x = sub_bit32(x,temp2);
  x = x<<8;
  x = add_bit32(x,temp);
  return x;
}
uint32_t SubWord32(uint32_t x){
  uint32_t result = 0;
  uint8_t temp = 0;
  uint32_t temp_res = 0;
  for(int i=0; i<4; i++){
    temp = x>>(8*3);
    x = x<<8;
    temp_res = SubBytes_b(temp);
    result ^= temp_res<<(8*(3-i));
  }
  return result;
}
uint32_t SubRot32(uint32_t x, uint32_t rc){
  uint32_t temp = 0;
  temp = RotWord32(x);
  temp = SubWord32(temp); //printf("temp subrot: %x\n",temp);
  return temp^rc;
}
//asummes key was set using setKey2
void setU32(union u32 *u, struct key key){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++){
      u->b[i][k] = key.block[i][3-k];
    }
  }




}


uint32_t KeyExpansion_b2(struct key32 key, struct expKey32 *ekey){



















  return 0;
}

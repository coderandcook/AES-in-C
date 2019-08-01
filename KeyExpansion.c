#include <stdio.h>
#include <math.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "bit.h"
#include "ShiftRows2.h"
#include "shifter.h"

int isEqualState(const struct state2 *s1, const struct state2 *s2){
  for(int i=0; i<4; i++){
    if(s1->block[i]!=s2->block[i]) return 0;
  }
  return 1;
}
int isEqualEkey(const struct expKey32 *ekey1, const struct expKey32 *ekey2){
  for(int i=0; i<44; i++){
    if(ekey1->block[i]!=ekey2->block[i]) return 0;
  }
  return 1;
}

int isEqualBlock(const uint32_t *x1, const uint32_t *x2){
  for(int i=0; i<4; i++){
    if(x1[i]!=x2[i])return 0;
  }
  return 1;
}

void clearEkey(struct expKey32 *ekey){
  for(int i=0; i<44; i++) ekey->block[i] = 0;
}
uint32_t updateRcon32(uint32_t rc){
  uint8_t temp = rc>>24;
  return mul(temp,0x2)<<24;
}

uint32_t RotWord32(uint32_t x){
  /*faster
  uint32_t t = x&0xff000000;
  x = x<<8;
  return x^(t>>24);
  */
  return lshift32(x,1);
}

uint32_t SubWord32(uint32_t x){
  uint32_t t0 = SubBytes_table(x>>24);
  uint32_t t1 = SubBytes_table(x>>16);
  uint32_t t2 = SubBytes_table(x>>8);
  uint32_t t3 = SubBytes_table(x);

  return (t0<<24)|(t1<<16)|(t2<<8)|t3;
}

uint32_t SubRot32(uint32_t x, uint32_t rc){
  return SubWord32(RotWord32(x))^rc;
}

void clearKey32(struct key32 *key){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++)key->block[i] = 0;
  }
}
void printKey32(struct key32 key){
  for(int i=0; i<4; i++)printf("%x\n",key.block[i]);
}

void printExpkey32(struct expKey32 *ekey){
  for(int i=0; i<44; i++){
    printf("%x\n",ekey->block[i]);
    if(i%4==3)printf("\n");
  }
}

void transposeKey(struct key32 *key){
    uint32_t final_key[4] = {0};
    for(int i=0; i<4; i++){
      uint32_t t0 = (key->block[i]>>24)<<24;
      uint32_t t1 = (key->block[i]>>16)<<24;
      uint32_t t2 = (key->block[i]>>8)<<24;
      uint32_t t3 = (key->block[i])<<24;
      final_key[0] |= t0>>8*i;
      final_key[1] |= t1>>8*i;
      final_key[2] |= t2>>8*i;
      final_key[3] |= t3>>8*i;
    }
    for(int i=0; i<4; i++) key->block[i] = final_key[i];
}
void transposeEkey(struct expKey32 *ekey){
  for(int i=0; i<44; i+=4){
    uint32_t tempBlock[4]={0};
    for(int k=0; k<4; k++){
      uint32_t t0 = (ekey->block[i+k]>>24)<<24;
      uint32_t t1 = (ekey->block[i+k]>>16)<<24;
      uint32_t t2 = (ekey->block[i+k]>>8)<<24;
      uint32_t t3 = ekey->block[i+k]<<24;
      tempBlock[0] |= t0>>8*k;
      tempBlock[1] |= t1>>8*k;
      tempBlock[2] |= t2>>8*k;
      tempBlock[3] |= t3>>8*k;
    }
    for(int k=0; k<4; k++)ekey->block[i+k] = tempBlock[k];
  }
}

void KeyExpansion32(const struct key32 *key, struct expKey32 *ekey){
  for(int i=0; i<4; i++)ekey->block[i] = key->block[i];
  uint32_t rc = 0x01000000;
  for(int i=4; i<44; i++){
    uint32_t t = ekey->block[i-1];
    if(i%4==0) {
      if(i>4) rc = updateRcon32(rc);
      //t = SubRot32(t,rc);
      t = SubWord32(RotWord32(t))^rc;
    }
    ekey->block[i] = ekey->block[i-4]^t;
  }
  //transpose block
  transposeEkey(ekey);
}

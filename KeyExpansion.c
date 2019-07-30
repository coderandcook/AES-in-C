#include <stdio.h>
#include <math.h>
#include <arpa/inet.h>
#include "KeyExpansion.h"
#include "SubBytes2.h"
#include "div_poly.h"
#include "mod3.h"
#include "poly.h"
#include "bit.h"

//KeyExpansion in uint32_t [44]
void clearEkey(struct expKey32 *ekey){
  for(int i=0; i<44; i++) ekey->block[i] = 0;
}
uint32_t updateRcon32(uint32_t rc){
  uint8_t temp = rc>>24;
  temp = mul(temp,0x2);
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

void setKey32(struct key32 *key, const uint8_t *keyarray){
  clearKey32(key);
  //int count=0;
  for(int i=0; i<16; i++){
    uint32_t temp = keyarray[i];
    key->block[i%4] ^= temp<<(8*(3-i/4));
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
      t = SubRot32(t,rc);
    }
    ekey->block[i] = ekey->block[i-4]^t;
  }
  //transpose block
  transposeEkey(ekey);
}

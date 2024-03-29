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
void clearKey32(struct key32 *key){
  for(int i=0; i<4; i++){
    for(int k=0; k<4; k++)key->block[i] = 0;
  }
}



uint32_t updateRcon(uint32_t rc){
  uint8_t temp = rc>>24;
  return mul(temp,0x2)<<24;
}
uint32_t RotWord32(uint32_t x){
  /*faster
  uint32_t t = x&0xff000000;
  x = x<<8;
  return x^(t>>24);
  */
  return rotL1(x);
}
uint32_t SubWord32(uint32_t x){
  uint32_t result = 0;
  uint8_t table[16][16] = {{0x63,0x7c,0x77,0x7b,0xf2,0x6b,0x6f,0xc5,0x30,0x01,0x67,0x2b,0xfe,0xd7,0xab,0x76},
                          {0xca,0x82,0xc9,0x7d,0xfa,0x59,0x47,0xf0,0xad,0xd4,0xa2,0xaf,0x9c,0xa4,0x72,0xc0},
                          {0xb7,0xfd,0x93,0x26,0x36,0x3f,0xf7,0xcc,0x34,0xa5,0xe5,0xf1,0x71,0xd8,0x31,0x15},
                          {0x04,0xc7,0x23,0xc3,0x18,0x96,0x05,0x9a,0x07,0x12,0x80,0xe2,0xeb,0x27,0xb2,0x75},
                          {0x09,0x83,0x2c,0x1a,0x1b,0x6e,0x5a,0xa0,0x52,0x3b,0xd6,0xb3,0x29,0xe3,0x2f,0x84},
                          {0x53,0xd1,0x00,0xed,0x20,0xfc,0xb1,0x5b,0x6a,0xcb,0xbe,0x39,0x4a,0x4c,0x58,0xcf},
                          {0xd0,0xef,0xaa,0xfb,0x43,0x4d,0x33,0x85,0x45,0xf9,0x02,0x7f,0x50,0x3c,0x9f,0xa8},
                          {0x51,0xa3,0x40,0x8f,0x92,0x9d,0x38,0xf5,0xbc,0xb6,0xda,0x21,0x10,0xff,0xf3,0xd2},
                          {0xcd,0x0c,0x13,0xec,0x5f,0x97,0x44,0x17,0xc4,0xa7,0x7e,0x3d,0x64,0x5d,0x19,0x73},
                          {0x60,0x81,0x4f,0xdc,0x22,0x2a,0x90,0x88,0x46,0xee,0xb8,0x14,0xde,0x5e,0x0b,0xdb},
                          {0xe0,0x32,0x3a,0x0a,0x49,0x06,0x24,0x5c,0xc2,0xd3,0xac,0x62,0x91,0x95,0xe4,0x79},
                          {0xe7,0xc8,0x37,0x6d,0x8d,0xd5,0x4e,0xa9,0x6c,0x56,0xf4,0xea,0x65,0x7a,0xae,0x08},
                          {0xba,0x78,0x25,0x2e,0x1c,0xa6,0xb4,0xc6,0xe8,0xdd,0x74,0x1f,0x4b,0xbe,0x8b,0x8a},
                          {0x70,0x3e,0xb5,0x66,0x48,0x03,0xf6,0x0e,0x61,0x35,0x57,0xb9,0x86,0xc1,0x1d,0x9e},
                          {0xe1,0xf8,0x98,0x11,0x69,0xd9,0x8e,0x94,0x9b,0x1e,0x87,0xe9,0xce,0x55,0x28,0xdf},
                          {0x8c,0xa1,0x89,0x0d,0xbf,0xe6,0x42,0x68,0x41,0x99,0x2d,0x0f,0xb0,0x54,0xbb,0x16}};

  for(int i=0; i<4; i++){
    uint8_t t = (x>>8*(3-i))&0xff;
    t = table[t>>4][(t&0xf)];
    result |= t<<8*(3-i);
  }
  return result;
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




void KeyExpansion(const struct key32 *key, struct expKey32 *ekey){
  for(int i=0; i<4; i++)ekey->block[i] = key->block[i];
  uint32_t rc = 0x01000000;
  for(int i=4; i<44; i++){
    uint32_t t = ekey->block[i-1];
    if(i%4==0) {
      if(i>4) rc = updateRcon(rc);
      //t = SubRot32(t,rc);
      t = SubWord32(RotWord32(t))^rc;
    }
    ekey->block[i] = ekey->block[i-4]^t;
  }
  //transpose block
  transposeEkey(ekey);
}



void printKey(struct key32 *key){
  for(int i=0; i<4; i++)printf("%x\n",key->block[i]);
}
void printExpkey(struct expKey32 *ekey){
  for(int i=0; i<44; i++){
    printf("%x\n",ekey->block[i]);
    if(i%4==3)printf("\n");
  }
}

/*
uint32_t SubWord32b(uint32_t x){

  uint32_t t0 = SubBytes_table(x>>24);
  uint32_t t1 = SubBytes_table(x>>16);
  uint32_t t2 = SubBytes_table(x>>8);
  uint32_t t3 = SubBytes_table(x);
  return (t0<<24)|(t1<<16)|(t2<<8)|t3;

}
*/

/*
uint32_t SubRot32(uint32_t x, uint32_t rc){
  return SubWord32(RotWord32(x))^rc;
}
*/

/*
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
}*/

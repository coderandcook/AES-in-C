#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "KeyExpansion.h"
#include "ShiftRows2.h"
#include "AddRoundKey3.h"
#include "SubBytes2.h"
#include "MixColumns.h"
#include "cipher.h"
/*
void cipher32b(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey){
  struct state2 s;
  for(int i=0; i<4; i++)s.block[i] = in[i];
  AddRoundKey(&s,ekey,0);
  for(int i=1; i<11; i++){
    SubBytes(&s);
    ShiftRows(&s);
    if(i!=10)MixColumns(&s);
    AddRoundKey(&s,ekey,i*4);
  }
  for(int i=0; i<4; i++)out[i] = s.block[i];
}
*/

void Cipher(const uint32_t *in, uint32_t *out, const struct expKey32 *ekey){
  struct state2 s;
  for(int i=0; i<4; i++)s.block[i] = in[i];
  AddRoundKey(&s,ekey,0);

  for(int i=1; i<10; i++){
    SubBytes(&s);
    ShiftRows(&s);
    MixColumns(&s);
    AddRoundKey(&s,ekey,i*4);
  }
  SubBytes(&s);
  ShiftRows(&s);
  AddRoundKey(&s,ekey,40);

  for(int i=0; i<4; i++)out[i] = s.block[i];
}
